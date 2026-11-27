// Copyright 2020 Yaotian Feng / Codetector
// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include "quantum.h"
#include "sled17341.h"

// Frame header: page in the low nibble, a fixed 0x20, and bit 7 set for reads.
#define SLED_FRAME_1 0x00
#define SLED_FRAME_FUNCTION 0x0B
#define SLED_HEADER_WRITE 0x20

// Function registers
#define SLED_REG_PICTURE_DISPLAY 0x01
#define SLED_REG_SHUTDOWN 0x0A
#define SLED_REG_SLEW_RATE 0x0E
#define SLED_REG_CURRENT 0x0F
#define SLED_REG_VAF_1 0x14
#define SLED_REG_VAF_2 0x15

#define SLED_MATRIX_TYPE_2 0x08
#define SLED_POWER_OFF 0x00
#define SLED_POWER_NORMAL 0x01
#define SLED_SLEW_RATE_ENABLE 0x01
// Constant current, 8 mA + 0.5 mA per step. 25 gives 20.5 mA, as the stock firmware.
#define SLED_CURRENT_ON 0x80
#define SLED_CURRENT_MAX_STEP 25

// The chips hiss with their drive current, and dimming by PWM does not help. So
// above SLED_PWM_KNEE brightness is set by the current, from 8 mA up to the stock
// 20.5 mA, with every colour stretched to the full PWM range. Below it the current
// stays at 8 mA, where the hiss is barely audible, and PWM dims further.
#define SLED_PWM_KNEE 64
#define SLED_VAF_1_VALUE 0x44
#define SLED_VAF_2_VALUE 0x44

#define SLED_COUNT 2
#define SLED_SLOTS 144
// Each LED is three channels, 12 slots apart.
#define SLED_GREEN_OFFSET 12
#define SLED_BLUE_OFFSET 24

// Frame 1 layout: enable bits, blink bits, then one PWM byte per slot.
#define SLED_FRAME_ENABLE 0x00
#define SLED_FRAME_BLINK (SLED_SLOTS / 8)
#define SLED_FRAME_PWM (2 * SLED_SLOTS / 8)

// SCK = 48 MHz / (prescaler * (rate + 1)) = 1 MHz.
static const SPIConfig sled_spi_config = {
    .clock_divider   = 1,
    .clock_prescaler = 24,
    .clock_rate      = 1,
    .data_size       = 8,
};

static const ioline_t sled_cs[SLED_COUNT] = {LINE_LED1_CS, LINE_LED2_CS};

// Red channel slot of each RGB Matrix LED, in layout order. Slots 144 and up are on the second chip.
static const uint8_t led_slot[RGB_MATRIX_LED_COUNT] = {
    2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  36,  37,  189, 190,
    46,  47,  72,  73,  74,  75,  76,  77,  80,  151, 152, 153, 185, 154,
    81,  82,  83,  108, 109, 110, 111, 112, 113, 182, 155, 181, 180,
    114, 116, 119, 146, 147, 148, 149, 150, 186, 191, 216, 187,
    38,  41,  42,  43,  45,  44,  115, 188,
};

static uint8_t pwm[SLED_COUNT][SLED_SLOTS];
static uint8_t current_step = SLED_CURRENT_MAX_STEP;
static bool    dirty;
static bool    powered;
static bool    dark;
static uint16_t dark_since;

// The chips are shut down once every LED has been dark for this long.
#define SLED_DARK_OFF_MS 1000

static void sled_write(uint8_t chip, uint8_t page, uint8_t offset, const void *data, size_t length) {
    uint8_t header[2] = {page | SLED_HEADER_WRITE, offset};

    spiAcquireBus(&SPID1);
    palClearLine(sled_cs[chip]);
    spiSend(&SPID1, sizeof(header), header);
    spiSend(&SPID1, length, data);
    palSetLine(sled_cs[chip]);
    spiReleaseBus(&SPID1);
}

static void sled_write_register(uint8_t reg, uint8_t value) {
    for (uint8_t chip = 0; chip < SLED_COUNT; chip++) {
        sled_write(chip, SLED_FRAME_FUNCTION, reg, &value, 1);
    }
}

static void sled_set_slot(uint8_t slot, uint8_t value) {
    uint8_t *p = &pwm[slot / SLED_SLOTS][slot % SLED_SLOTS];
    if (*p != value) {
        *p    = value;
        dirty = true;
    }
}

void sled_init(void) {
    for (uint8_t chip = 0; chip < SLED_COUNT; chip++) {
        palSetLine(sled_cs[chip]);
    }
    spiStart(&SPID1, &sled_spi_config);

    sled_write_register(SLED_REG_SHUTDOWN, SLED_POWER_OFF);
    sled_write_register(SLED_REG_PICTURE_DISPLAY, SLED_MATRIX_TYPE_2);
    sled_write_register(SLED_REG_CURRENT, SLED_CURRENT_ON | current_step);
    sled_write_register(SLED_REG_SLEW_RATE, SLED_SLEW_RATE_ENABLE);
    sled_write_register(SLED_REG_VAF_1, SLED_VAF_1_VALUE);
    sled_write_register(SLED_REG_VAF_2, SLED_VAF_2_VALUE);

    // All slots enabled, none blinking, all dark.
    uint8_t bits[SLED_SLOTS / 8];
    for (uint8_t chip = 0; chip < SLED_COUNT; chip++) {
        memset(bits, 0xFF, sizeof(bits));
        sled_write(chip, SLED_FRAME_1, SLED_FRAME_ENABLE, bits, sizeof(bits));
        memset(bits, 0x00, sizeof(bits));
        sled_write(chip, SLED_FRAME_1, SLED_FRAME_BLINK, bits, sizeof(bits));
        sled_write(chip, SLED_FRAME_1, SLED_FRAME_PWM, pwm[chip], sizeof(pwm[chip]));
    }
    sled_on();
}

static uint8_t stretch(uint8_t value, uint8_t brightness) {
    uint16_t scaled = (uint16_t)value * 255 / brightness;
    return scaled > 255 ? 255 : scaled;
}

void sled_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < 0 || index >= RGB_MATRIX_LED_COUNT) {
        return;
    }
    uint8_t brightness = rgb_matrix_get_val();
    if (brightness < SLED_PWM_KNEE) {
        brightness = SLED_PWM_KNEE;
    }
    red   = stretch(red, brightness);
    green = stretch(green, brightness);
    blue  = stretch(blue, brightness);

    uint8_t slot = led_slot[index];
    sled_set_slot(slot, red);
    sled_set_slot(slot + SLED_GREEN_OFFSET, green);
    sled_set_slot(slot + SLED_BLUE_OFFSET, blue);
}

void sled_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        sled_set_color(i, red, green, blue);
    }
}

static void update_current(void) {
    uint8_t brightness = rgb_matrix_get_val();
    uint8_t step       = brightness <= SLED_PWM_KNEE ? 0 : (uint16_t)(brightness - SLED_PWM_KNEE) * SLED_CURRENT_MAX_STEP / (255 - SLED_PWM_KNEE);
    if (step != current_step) {
        current_step = step;
        sled_write_register(SLED_REG_CURRENT, SLED_CURRENT_ON | step);
    }
}

void sled_flush(void) {
    update_current();
    if (dirty) {
        dirty = false;
        dark  = true;
        for (uint8_t chip = 0; chip < SLED_COUNT; chip++) {
            sled_write(chip, SLED_FRAME_1, SLED_FRAME_PWM, pwm[chip], sizeof(pwm[chip]));
            for (uint8_t i = 0; i < SLED_SLOTS && dark; i++) {
                dark = pwm[chip][i] == 0;
            }
        }
        dark_since = timer_read();
        if (!dark && !powered) {
            sled_on();
        }
    } else if (dark && powered && timer_elapsed(dark_since) >= SLED_DARK_OFF_MS) {
        sled_off();
    }
}

#ifdef SNOWFOX_TEST
// Test builds: write one function register on both chips, for tuning by ear.
void sled_test_write_register(uint8_t reg, uint8_t value) {
    sled_write_register(reg, value);
}
#endif

void sled_on(void) {
    sled_write_register(SLED_REG_SHUTDOWN, SLED_POWER_NORMAL);
    powered = true;
}

void sled_off(void) {
    sled_write_register(SLED_REG_SHUTDOWN, SLED_POWER_OFF);
    powered = false;
}
