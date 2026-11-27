// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later
// Ducky One 3 RGB: 3x MBI5042 (one per colour, 16 columns each) + 8 multiplexed LED rows.
// Protocol reverse engineered from stock firmware V1.15; addresses in comments refer to that image.
#include "quantum.h"
#include "led_map.h"

// Pin data registers: PDIO(port, pin), port A=0 .. F=5
#define PDIO(port, pin) (*(volatile uint32_t *)(GPIO_PIN_DATA_BASE + (port) * 0x40 + (pin) * 4))
#define DCLK PDIO(2, 0)    // PC0
#define LE PDIO(2, 2)      // PC2
#define SDI PDIO(2, 3)     // PC3
#define LED_PWR PDIO(2, 7) // PC7, active low

// LED rows, active high: PC6 PC5 PD7 PD15 PD14 PD13 PD12 PF2
static volatile uint32_t *const led_row[8] = {
    &PDIO(2, 6), &PDIO(2, 5), &PDIO(3, 7), &PDIO(3, 15), &PDIO(3, 14), &PDIO(3, 13), &PDIO(3, 12), &PDIO(5, 2),
};
static const pin_t led_row_pin[8] = {C6, C5, D7, D15, D14, D13, D12, F2};

// Full-scale 16-bit MBI5042 PWM word; stock's top brightness level (defaults routine 0x9614)
#define PWM_MAX 0xFFFF

// fb.px[row][channel][chip]; chip 0 is shifted last (nearest the MCU). Chips 0, 1, 2 drive red, green, blue.
// fb: shown by the TMR1 ISR. back: RGB Matrix draws here, and mbi_flush() publishes finished frames into fb.
// Drawing straight into fb let the ISR show half-drawn frames (e.g. Solid Color's cyan before an indicator
// hook repaints a key red: flicker). The word view lets the flush copy fast without aliasing tricks.
typedef union {
    uint16_t px[8][16][3];
    uint32_t w[8 * 16 * 3 / 2];
} frame_t;
static frame_t fb, back;
static uint8_t cur_row;

static inline void shift16(uint16_t w) {
    for (int i = 15; i >= 0; i--) {
        SDI  = (w >> i) & 1;
        DCLK = 1;
        DCLK = 0;
    }
}

// Last 16 bits of a channel: final bit clocked with LE high = MBI5042 "data latch".
static inline void shift16_latch(uint16_t w) {
    for (int i = 15; i > 0; i--) {
        SDI  = (w >> i) & 1;
        DCLK = 1;
        DCLK = 0;
    }
    SDI  = w & 1;
    LE   = 1;
    DCLK = 1;
    DCLK = 0;
    LE   = 0;
}

// 1 kHz: load the next row's 16 channels, global-latch, switch rows (same order/timing as stock).
// ponytail: bit-banged, ~0.26 ms of each 1 ms; stock uses SPI0 (32+15 bit) + 1 bit-bang per channel if CPU gets tight.
OSAL_IRQ_HANDLER(Vector64) { // TMR1
    OSAL_IRQ_PROLOGUE();
    TIMER1->INTSTS = TIMER_INTSTS_TIF_Msk;

    uint8_t next = (cur_row + 1) & 7;
    for (uint8_t ch = 0; ch < 16; ch++) {
        if (ch == 15) *led_row[cur_row] = 0;
        shift16(fb.px[next][ch][2]);
        shift16(fb.px[next][ch][1]);
        shift16_latch(fb.px[next][ch][0]);
    }
    // 2 plain clocks, then LE high for 3 clocks = "global latch"
    DCLK = 1;
    DCLK = 0;
    DCLK = 1;
    DCLK = 0;
    LE   = 1;
    for (int i = 0; i < 3; i++) {
        DCLK = 1;
        DCLK = 0;
    }
    LE             = 0;
    *led_row[next] = 1;
    cur_row        = next;

    OSAL_IRQ_EPILOGUE();
}

static void mbi_init(void) {
    memset(&fb, 0, sizeof(fb));
    memset(&back, 0, sizeof(back));

    gpio_set_pin_output(C7); // LED power: keep off until the chain is clocked
    gpio_write_pin_high(C7);
    gpio_set_pin_output(E8);
    gpio_write_pin_high(E8);
    gpio_set_pin_output(F4);
    gpio_write_pin_low(F4);
    for (int i = 0; i < 8; i++) {
        gpio_set_pin_output(led_row_pin[i]);
        gpio_write_pin_low(led_row_pin[i]);
    }
    gpio_set_pin_output(C0);
    gpio_set_pin_output(C2);
    gpio_set_pin_output(C3);
    gpio_write_pin_low(C0);
    gpio_write_pin_low(C2);
    gpio_write_pin_low(C3);

    UNLOCKREG();
    // PC0/2/3/4 = GPIO, PC1 = PWM0_CH1 (GCLK)
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~0x000FFFFFul) | SYS_GPC_MFPL_PC1MFP_PWM0_CH1;
    CLK->CLKSEL1  = (CLK->CLKSEL1 & ~(CLK_CLKSEL1_PWM0SEL_Msk | CLK_CLKSEL1_TMR1SEL_Msk)) | CLK_CLKSEL1_PWM0SEL_Msk | (7ul << CLK_CLKSEL1_TMR1SEL_Pos); // PWM0 <- PCLK0, TMR1 <- HIRC
    CLK->APBCLK0 |= CLK_APBCLK0_PWM0CKEN_Msk | CLK_APBCLK0_TMR1CKEN_Msk;
    LOCKREG();

    // GCLK: PWM0 CH1, PCLK 48 MHz / 24 = 2 MHz (stock register values)
    PWM0->CTL1      = 0;
    PWM0->CLKPSC0_1 = 0;
    PWM0->PERIOD[1] = 0x17;
    PWM0->CMPDAT[1] = 1;
    PWM0->WGCTL0    = 0x8;
    PWM0->WGCTL1    = 0x4;
    PWM0->POEN      = 0x2;
    PWM0->CNTEN     = 0x2;

    // Row refresh: TMR1 periodic, HIRC 22.1184 MHz / 2 / 11059 = 1 kHz (stock values)
    TIMER1->CTL = (1ul << TIMER_CTL_OPMODE_Pos) | 1;
    TIMER1->CMP = 0x2b33;
    nvicEnableVector(TMR1_IRQn, 3); // below USB (2)
    TIMER1->CTL |= TIMER_CTL_INTEN_Msk | TIMER_CTL_CNTEN_Msk;

    gpio_write_pin_low(C7); // LED power on
}

static inline uint16_t pwm(uint8_t v) {
    return (uint32_t)v * v * PWM_MAX / (255u * 255u);
}

static void mbi_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t   hw = led_hw[index];
    uint16_t *px = back.px[hw >> 4][hw & 15];
    px[0]        = pwm(r);
    px[1]        = pwm(g);
    px[2]        = pwm(b);
}

static void mbi_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++)
        mbi_set_color(i, r, g, b);
}

// Publish a finished frame. RGB Matrix LEDs occupy rows 0-6 and row 7 ch 0-3 only (see led_map.h), one
// contiguous 174-word span; row 7 ch 4-7 are the lock indicators, written to fb directly. TMR1 is masked for the
// copy; NVIC_DisableIRQ keeps a tick that lands meanwhile pending (nvicEnableVector would clear it).
#define FLUSH_WORDS ((7 * 16 + 4) * 3 / 2)
static void mbi_flush(void) {
    NVIC_DisableIRQ(TMR1_IRQn);
    __DSB();
    __ISB();
    volatile uint32_t *dst = fb.w; // volatile: GCC would turn the loop into newlib memcpy, which copies bytes
    for (uint32_t i = 0; i < FLUSH_WORDS; i++)
        dst[i] = back.w[i];
    __DMB();
    NVIC_EnableIRQ(TMR1_IRQn);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = mbi_init,
    .set_color     = mbi_set_color,
    .set_color_all = mbi_set_color_all,
    .flush         = mbi_flush,
};

// Indicator LEDs live in LED row 7, outside the RGB-matrix map (stock render fn 0x3d64 @0x41ba):
// (7,4) Num  (7,5) Caps  (7,6) Scroll  (7,7) 4th (stock toggled mode; here: GUI lock). Stock: white, full PWM.
static bool asleep; // host suspended: indicators dark too (RGB matrix sleeps via RGB_MATRIX_SLEEP)

static void indicator(uint8_t ch, bool on) {
    uint16_t v      = on && !asleep ? PWM_MAX : 0;
    fb.px[7][ch][0] = fb.px[7][ch][1] = fb.px[7][ch][2] = v;
}

bool led_update_kb(led_t s) {
    bool res = led_update_user(s);
    if (res) {
        indicator(4, s.num_lock);
        indicator(5, s.caps_lock);
        indicator(6, s.scroll_lock);
    }
    return res;
}

// USB suspend, as stock does: stop the refresh and GCLK, drive the chain inputs and rows low, LED power off.
static void mbi_off(void) {
    TIMER1->CTL &= ~TIMER_CTL_CNTEN_Msk;
    TIMER1->INTSTS = TIMER_INTSTS_TIF_Msk;
    NVIC_ClearPendingIRQ(TMR1_IRQn);
    PWM0->POEN &= ~0x2ul;
    SDI = 0;
    for (int i = 0; i < 8; i++)
        *led_row[i] = 0;
    LED_PWR = 1;
}

static void mbi_on(void) {
    PWM0->POEN |= 0x2;
    TIMER1->CTL |= TIMER_CTL_CNTEN_Msk;
    LED_PWR = 0;
}

void suspend_power_down_kb(void) {
    if (!asleep) mbi_off();
    asleep = true;
    for (uint8_t ch = 4; ch < 8; ch++)
        indicator(ch, false);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    if (asleep) mbi_on();
    asleep = false;
    led_update_kb(host_keyboard_led_state());
    suspend_wakeup_init_user();
}

// Crystal-less USB: HIRC48 is auto-trimmed against the host's SOF, with the stock firmware's recovery:
// arm only on a fresh SOF, restore the last good trim when a trim fails (TFAILIF1/CLKERRIF1), and keep the
// trim within 16 steps (~2%) of its boot value. SYS_BASE + 0x118 is the HIRC48 trim register (undocumented,
// write-protected, used by the BSP samples). The USB driver never clears SOFIF, so it is cleared here.
#define HIRC48_TRIM (*(volatile uint32_t *)(SYS_BASE + 0x118))
#define HIRC48_TRIM_ERRORS (SYS_IRCTISTS_TFAILIF1_Msk | SYS_IRCTISTS_CLKERRIF1_Msk)
#define HIRC48_TRIM_RANGE 16

// Stop the auto-trim and put back a known-good trim; the next fresh SOF re-arms it.
static void hirc48_trim_restore(uint32_t value) {
    SYS->IRCTCTL1   = 0;
    bool was_locked = (SYS->REGLCTL & 1u) == 0;
    if (was_locked) UNLOCKREG();
    HIRC48_TRIM = value;
    if (was_locked) LOCKREG();
    SYS->IRCTISTS = HIRC48_TRIM_ERRORS;
    USBD->INTSTS  = USBD_INTSTS_SOFIF_Msk;
}

void housekeeping_task_kb(void) {
    static bool     trim_init;
    static uint32_t trim_default, trim_last;

    indicator(7, keymap_config.no_gui);

    if (!trim_init) {
        trim_default = trim_last = HIRC48_TRIM;           // not armed yet: still the boot value
        USBD->INTSTS             = USBD_INTSTS_SOFIF_Msk; // only a SOF seen from now on may arm it
        trim_init                = true;
        return;
    }
    if (SYS->IRCTISTS & HIRC48_TRIM_ERRORS) {
        hirc48_trim_restore(trim_last);
        return;
    }
    uint32_t trim = HIRC48_TRIM;
    if (trim > trim_default + HIRC48_TRIM_RANGE || trim + HIRC48_TRIM_RANGE < trim_default) {
        hirc48_trim_restore(trim_last);
        return;
    }
    trim_last = trim;
    // FREQSEL=10 (48 MHz), LOOPSEL=01, RETRYCNT=00, CESTOPEN=1, REFCKSEL=1 (USB SOF); stock writes 0x512 too
    if ((SYS->IRCTCTL1 & SYS_IRCTCTL1_FREQSEL_Msk) != 2 && (USBD->INTSTS & USBD_INTSTS_SOFIF_Msk)) {
        USBD->INTSTS  = USBD_INTSTS_SOFIF_Msk;
        SYS->IRCTCTL1 = 0x512;
    }
}

void mcu_reset(void) {
    NVIC_SystemReset();
}
