/* Copyright 2026 NUTWANG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "ch.h"      // chVTGetSystemTimeX(), CH_CFG_ST_FREQUENCY
#include "matrix.h"  // matrix_scan_user()
#include <stdio.h>   // snprintf()

/* matrix_common.c provides this raw/debounced matrix reader as a weak helper
 * but does not expose it through a public header (dip_switch.c declares it the
 * same way).  peek_matrix(row, col, true) reads the pre-debounce state. */
extern bool peek_matrix(uint8_t row_index, uint8_t col_index, bool raw);

/* -------------------------------------------------------------------------
 *  Controlled experiment (macro-gated, compiled out for the normal firmware):
 *   - LD7_TEST_I2C_CLK : enable ONLY the I2C1 peripheral clock (RCC APB1ENR
 *                        bit 21), issue NO I2C transfer at all.
 *   - LD7_TEST_I2C_START: additionally call i2cStart() (enables the I2C1
 *                        peripheral unit incl. its pins) but still no transfer.
 *   Used to answer: does merely enabling I2C break SK32 USB enumeration,
 *   or only an actual I2C transfer to a missing device?
 * ------------------------------------------------------------------------- */
#ifdef LD7_TEST_I2C_CLK
#    include "hal.h"
void keyboard_pre_init_user(void) {
    volatile uint32_t *apb1enr = (volatile uint32_t *)0x4002101CU;
    *apb1enr |= 0x00200000U; /* RCC->APB1ENR |= RCC_APB1ENR_I2C1EN */
}
#endif
#ifdef LD7_TEST_I2C_START
#    include "hal.h"
/* Replicates i2c_lld_start() essentials with raw registers (no driver, no
 * transfer): enable+reset I2C1 clock, set PE|ACK in CR1.  GPIO AF for PB13/14
 * is left out on purpose so the test isolates "I2C unit enabled". */
void keyboard_pre_init_user(void) {
    volatile uint32_t *apb1enr = (volatile uint32_t *)0x4002101CU;
    volatile uint32_t *apb1rstr = (volatile uint32_t *)0x40021010U;
    volatile uint32_t *cr1 = (volatile uint32_t *)0x40005400U; /* I2C1_CR1 */
    *apb1enr |= 0x00200000U;        /* RCC_APB1ENR_I2C1EN */
    *apb1rstr |= 0x00200000U;       /* RCC_APB1RSTR_I2C1RST */
    *apb1rstr &= ~0x00200000U;
    *cr1 |= 0x0001U | 0x0400U;      /* I2C_CR1_PE | I2C_CR1_ACK */
}
#endif

/* LD7_OLED default keymap.
 *
 * KEY1..KEY7 = Z X C V A Ctrl Enter
 */
enum layers { _BASE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ld7(KC_Z, KC_X, KC_C, KC_V, KC_A, KC_LCTL, KC_ENT),
};

/* -------------------------------------------------------------------------
 *  Key statistics shown on the 128x32 OLED
 *
 *  Left  : average number of key triggers per second over the last 10 s
 *  Right : latency (ms, one decimal) from the latest key trigger to the HID
 *          report being sent
 * ---------------------------------------------------------------------- */

#define KEY_COUNT           MATRIX_COLS /* 7 directly wired keys */
#define RATE_WINDOW_SECONDS 4

/* The latency is reported with 0.1 ms resolution, so all timing maths is done
 * in "deci-milliseconds".  CH_CFG_ST_FREQUENCY is the ChibiOS system tick
 * frequency (100 kHz on this board), giving a 10 us time base. */
#define ST_TICKS_PER_MS (CH_CFG_ST_FREQUENCY / 1000u)
#define TICKS_TO_DMS(t) ((uint32_t)(t) * 10u / ST_TICKS_PER_MS)

/* Press-rate ring buffer: one bucket per second covering the last 10 s. */
static uint16_t rate_buckets[RATE_WINDOW_SECONDS];
static uint8_t  rate_index;
static uint16_t presses_this_second;
static uint32_t second_anchor;

/* Raw (pre-debounce) press timestamps used as the latency start point. */
static systime_t raw_press_ticks[KEY_COUNT];
static bool      raw_pressed[KEY_COUNT];

/* Latency from the latest key trigger to the report being sent, in 0.1 ms. */
static volatile uint32_t last_latency_dms;
static systime_t         pending_press_ticks;
static bool              pending_latency;

void matrix_scan_user(void) {
    systime_t now = chVTGetSystemTimeX();

    /* 1) Timestamp the raw press edge (independent of debouncing) of each key
     *    so the reported latency covers the debounce delay as well. */
    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        bool pressed = peek_matrix(0, i, true);
        if (pressed && !raw_pressed[i]) {
            raw_press_ticks[i] = now;
        }
        raw_pressed[i] = pressed;
    }

    /* 2) Roll the presses-per-second ring buffer once every second. */
    uint32_t now_ms = timer_read32();
    if (now_ms - second_anchor >= 1000u) {
        rate_buckets[rate_index] = presses_this_second;
        presses_this_second       = 0;
        rate_index                = (rate_index + 1) % RATE_WINDOW_SECONDS;
        second_anchor += 1000u;
        if (now_ms - second_anchor >= 1000u) {
            second_anchor = now_ms; // catch up if the loop was blocked
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        presses_this_second++;

        uint8_t idx = record->event.key.col;
        if (idx < KEY_COUNT) {
            pending_press_ticks = raw_press_ticks[idx];
            pending_latency     = true;
        }
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* Called right after the key action has been performed and the HID report
     * queued to the host. */
    if (record->event.pressed && pending_latency) {
        last_latency_dms = TICKS_TO_DMS(chVTGetSystemTimeX() - pending_press_ticks);
        pending_latency  = false;
    }
}

/* -------------------------------- OLED ---------------------------------- */

#ifdef OLED_ENABLE
/* LD7_OLED auto-detect experiment:
 * Override the weak SSD1306 transport so that, when no SSD1306 is present on
 * the I2C bus, we NEVER issue a real I2C transfer.  This lets the same
 * firmware run on boards with and without the OLED without the I2C traffic
 * (to a non-existent device) disturbing USB enumeration.
 *
 * The probe uses i2c_ping_address() ONCE on the first transfer.  If it fails
 * the OLED is permanently disabled (all senders return false), so
 * oled_init() fails early, oled_initialized stays false and oled_task()
 * never touches I2C again. */
#include "i2c_master.h"
#include "hal.h"

/* 2x magnified rendering for the 128x32 OLED.
 * QMK's SSD1306 driver has no built-in scaling (fixed 6x8 glyphs); the font
 * bitmap is pulled into this translation unit (it is static in glcdfont.c) and
 * each 6x8 glyph is blown up to 12x16, written via oled_write_raw_byte() which
 * marks the affected blocks dirty. */
#include "glcdfont.c"
#include "oled_driver.h"

/* Draw one glyph at pixel offset (x, y).  scale==2 doubles each pixel
 * (6x8 -> 12x16) without page alignment, so content can be shifted by any
 * number of pixels vertically. */
static void oled_draw_glyph_px(uint8_t ch, uint16_t x, uint8_t y, uint8_t scale) {
    if (ch < OLED_FONT_START || ch > OLED_FONT_END) {
        ch = '?';
    }
    const unsigned char *glyph = &font[(ch - OLED_FONT_START) * OLED_FONT_WIDTH];
    for (uint8_t c = 0; c < OLED_FONT_WIDTH; c++) {
        uint8_t b = pgm_read_byte(&glyph[c]);
        for (uint8_t r = 0; r < 8; r++) {
            if (!(b & (1U << r))) {
                continue;
            }
            if (scale == 2) {
                oled_write_pixel(x + c * 2, y + r * 2, true);
                oled_write_pixel(x + c * 2 + 1, y + r * 2, true);
                oled_write_pixel(x + c * 2, y + r * 2 + 1, true);
                oled_write_pixel(x + c * 2 + 1, y + r * 2 + 1, true);
            } else {
                oled_write_pixel(x + c, y + r, true);
            }
        }
    }
}

static void oled_write_str_px(const char *s, uint16_t x, uint8_t y, uint8_t scale) {
    uint16_t adv = (scale == 2) ? 12 : 6;
    while (*s) {
        oled_draw_glyph_px((uint8_t)*s++, x, y, scale);
        x += adv;
    }
}

/* The LD7 OLED runs on I2C1 with SCL = PA2, SDA = PA3 (alternate function 13)
 * and NO external pull-ups, so the internal pull-up must be enabled on both
 * pads.  The QMK i2c_master weak i2c_init() applies the SK32 PAL mode from
 * I2C1_SCL_PAL_MODE, but that whole-value macro trips over macro-expansion
 * order in the platform driver TU (the OR-ed PAL flags resolve to the wrong
 * AF number there), so we override i2c_init() here where the SK32 PAL macros
 * are fully in scope, and configure the pads explicitly. */
void __attribute__((used)) i2c_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        /* Release the pads briefly. */
        palSetLineMode(A2, PAL_MODE_INPUT);
        palSetLineMode(A3, PAL_MODE_INPUT);
        chThdSleepMilliseconds(10);

        /* SCL=PA2, SDA=PA3 in AF13 with internal pull-up. */
        palSetLineMode(A2, PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP);
        palSetLineMode(A3, PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP);
    }
}

static bool oled_probed   = false;
static bool oled_present  = false;

/* -------------------------------------------------------------------------
 *  OLED presence probe (no-show safe)
 *
 *  Probing with the normal driver (i2c_ping_address()) runs a real
 *  interrupt-driven I2C transfer.  On LD7 boards WITHOUT a fitted SSD1306 the
 *  I2C1 ISR can hit a fatal condition on a spurious bus event and call
 *  chSysHalt(): IRQs get disabled for good, the USB ISR is never serviced and
 *  the board enumerates as VID_0000 ("unknown USB device").  This probe below
 *  never engages the interrupt machinery:
 *    - masks the I2C1 NVIC IRQ before touching the unit,
 *    - polls SR1 directly for the ADDRESS-ACK flag with a bounded loop,
 *    - on "no display": leaves I2C1 parked (IRQ still masked, PE off) so no
 *      transfer and no interrupt can ever disturb USB again.
 *  When a display IS present the IRQ is restored and the normal
 *  interrupt-driven driver path (used successfully on OLED-fit boards) runs.
 * ------------------------------------------------------------------------- */
#define SK32_RCC_APB1ENR         (*(volatile uint32_t *)0x4002101CU)
#define SK32_RCC_APB1ENR_I2C1EN  0x00200000U
#define SK32_I2C1_BASE           0x40005400U
#define SK32_NVIC_ICER0          (*(volatile uint32_t *)0xE000E180U)
#define SK32_NVIC_ISER0          (*(volatile uint32_t *)0xE000E100U)
#define SK32_I2C1_IRQN           23U

#define SK32_I2C_CR1             (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x00U))
#define SK32_I2C_CR2             (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x04U))
#define SK32_I2C_DR              (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x10U))
#define SK32_I2C_SR1             (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x14U))
#define SK32_I2C_SR2             (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x18U))
#define SK32_I2C_CCR             (*(volatile uint32_t *)(SK32_I2C1_BASE + 0x1CU))
#define SK32_I2C_CR1_SWRST       (1U << 15)
#define SK32_I2C_CR1_PE          (1U << 0)
#define SK32_I2C_CR1_START       (1U << 8)
#define SK32_I2C_CR1_STOP        (1U << 9)
#define SK32_I2C_SR1_SB          (1U << 0)
#define SK32_I2C_SR1_ADDR        (1U << 1)
#define SK32_I2C_SR1_AF          (1U << 10)

static bool i2c_probe_ssd1306(void) {
    /* Drive SCL=PA2, SDA=PA3 in AF13 with internal pull-up (same as the
     * i2c_init() override, done here so the bus is usable even if i2c_init()
     * has not run yet). */
    palSetLineMode(A2, PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP);
    palSetLineMode(A3, PAL_MODE_ALTERNATE(13) | PAL_SK32_PUPDR_PULLUP);

    /* Enable the I2C1 clock. */
    SK32_RCC_APB1ENR |= SK32_RCC_APB1ENR_I2C1EN;

    /* Mask the I2C1 interrupt BEFORE the unit is used: a spurious event can
     * then never reach the chSysHalt() trap. */
    SK32_NVIC_ICER0 = (1U << SK32_I2C1_IRQN);

    /* Full software reset of the unit, then enable it. */
    SK32_I2C_CR1 = SK32_I2C_CR1_SWRST;
    SK32_I2C_CR1 = 0U;
    SK32_I2C_CR1 = SK32_I2C_CR1_PE;

    /* Program the SCL clock BEFORE use: the SK32 I2C is clocked by the
     * 8 MHz HSI (CR2 FREQ[5:0] = 8).  Load the same fast-mode 400 kHz CCR
     * (2/1 duty) the HAL driver programs for I2C1_CLOCK_SPEED 400000.  With
     * a zeroed FREQ/CCR the SCL would not run at a valid rate and no SSD1306
     * would ever answer the address byte. */
    SK32_I2C_CR2 = 8U;            /* FREQ[5:0] = 8 MHz. */
    SK32_I2C_CCR = 0x8006U;       /* F/S (bit15) + CCR=6 -> 400 kHz 2:1. */

    /* Generate START and wait for SB (bus idle -> start sent). */
    SK32_I2C_CR1 |= SK32_I2C_CR1_START;
    bool ok      = false;
    bool sb_ok   = false;
    for (uint32_t i = 0U; i < 40000U; i++) {
        if (SK32_I2C_SR1 & SK32_I2C_SR1_SB) {
            sb_ok = true;
            break;
        }
    }

    if (sb_ok) {
        /* Clock out the 7-bit address + write bit as the first data byte. */
        SK32_I2C_DR = (uint32_t)((OLED_DISPLAY_ADDRESS << 1) & 0xFEU);

        /* Poll SR1 for ADDR (device ACKed) or AF (no device), bounded loop. */
        for (uint32_t i = 0U; i < 40000U; i++) {
            uint32_t sr1 = SK32_I2C_SR1;
            if (sr1 & SK32_I2C_SR1_ADDR) {
                ok = true;
                break;
            }
            if (sr1 & SK32_I2C_SR1_AF) {
                break;
            }
        }
    }

    /* Close the transaction: STOP, then power the unit down. */
    SK32_I2C_CR1 = SK32_I2C_CR1_PE | SK32_I2C_CR1_STOP;
    SK32_I2C_CR1 = 0U;

    return ok;
}

static bool oled_probe(void) {
    if (!oled_probed) {
        oled_probed = true;
        oled_present = i2c_probe_ssd1306();
        if (oled_present) {
            /* Display found: restore normal interrupt-driven I2C. */
            SK32_NVIC_ISER0 = (1U << SK32_I2C1_IRQN);
        }
    }
    return oled_present;
}

bool __attribute__((used)) oled_send_cmd(const uint8_t *data, uint16_t size) {
    if (!oled_probe()) {
        return false;
    }
    return i2c_transmit((OLED_DISPLAY_ADDRESS << 1), data, size, OLED_I2C_TIMEOUT) == I2C_STATUS_SUCCESS;
}

bool __attribute__((used)) oled_send_cmd_P(const uint8_t *data, uint16_t size) {
    if (!oled_probe()) {
        return false;
    }
    return oled_send_cmd(data, size);
}

bool __attribute__((used)) oled_send_data(const uint8_t *data, uint16_t size) {
    if (!oled_probe()) {
        return false;
    }
    /* I2C_DATA (0x40) = "data bytes follow" control byte for SSD1306. */
    return i2c_write_register((OLED_DISPLAY_ADDRESS << 1), 0x40, data, size, OLED_I2C_TIMEOUT) == I2C_STATUS_SUCCESS;
}

static void format_fixed1(char *buf, size_t size, uint32_t value_d10) {
    snprintf(buf, size, "%lu.%lu", (unsigned long)(value_d10 / 10u), (unsigned long)(value_d10 % 10u));
}

/* Erase a pixel rectangle (pixels off).  The magnified draw routine
 * (oled_draw_glyph_px) only sets the font "1" pixels and never clears, so
 * without an explicit erase a value that shrinks between updates leaves the
 * previous digit bits behind (ghosting / text stacking on the panel). */
static void oled_clear_px_region(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (uint8_t i = 0; i < w; i++) {
        for (uint8_t j = 0; j < h; j++) {
            oled_write_pixel(x + i, y + j, false);
        }
    }
}

bool oled_task_user(void) {
    static uint32_t shown_rate = 0xFFFFFFFFu;
    static uint32_t shown_lat  = 0xFFFFFFFFu;

    uint32_t total = 0;
    for (uint8_t i = 0; i < RATE_WINDOW_SECONDS; i++) {
        total += rate_buckets[i];
    }
    /* KEY/s as an integer: round to nearest, but any 0 < rate < 1 shows 1
     * (a truly idle board still shows 0, a board with traffic never rounds
     * a sub-1 rate down to "no keys"). */
    uint32_t rate_d10 = (total * 10u) / RATE_WINDOW_SECONDS; // average per second (0.1/s)
    uint32_t rate_int = (rate_d10 + 5u) / 10u;               // round half up
    if (rate_d10 > 0u && rate_int == 0u) {
        rate_int = 1u;
    }
    /* LAT capped at 9.9 ms: a blocked report slot or a slow loop can produce
     * a one-off multi-ms figure; the panel is small and 9.9 is enough to
     * show "this keypress took a long time". */
    uint32_t lat_dms = last_latency_dms;
    if (lat_dms > 99u) {
        lat_dms = 99u;
    }

    if (rate_int != shown_rate || lat_dms != shown_lat) {
        shown_rate = rate_int;
        shown_lat  = lat_dms;

        char buf[12];

        /* Values: 12x16 magnified glyphs, shifted down 4 px.
         * 128 wide: rate starts at x=0, latency at x=68 (5 zoom chars = 60 px
         * + 8 px gap).
         * Clear the full value region first (6 chars x 12 px = 72 px for rate,
         * 5 chars x 12 px = 60 px for latency) so a shrinking number cannot
         * leave stale digits behind. */
        oled_clear_px_region(0, 4, 72, 16);
        oled_clear_px_region(68, 4, 60, 16);

        snprintf(buf, sizeof(buf), "%lu", (unsigned long)rate_int);
        oled_write_str_px(buf, 0, 4, 2);
        format_fixed1(buf, sizeof(buf), lat_dms);
        oled_write_str_px(buf, 68, 4, 2);

        /* Labels: small 6x8 glyphs, shifted down 4 px more than the values
         * (y = 24 = bottom page). */
        oled_write_str_px("KEY/s", 0, 24, 1);
        oled_write_str_px("LAT/ms", 68, 24, 1);
    }
    return false;
}
#endif /* OLED_ENABLE */
