// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Battery measurement, the low-battery indicator, deep sleep on battery power and
// the typed status report.
#include QMK_KEYBOARD_H
#include "tex_hw.h"

#define SLEEP_DEFAULT_MINUTES 15
#define MINUTE_MS 60000UL
#define WAKE_GRACE_MS 2000UL
#ifdef SHURA_BLE4
#    define BLE4_POST_AF_IDLE_MS 5000UL // Stock caps remaining MCU idle time at 10000 half-ms ticks.
#endif

// ADC registers (HT32F52342/52352 user manual, ADC chapter)
#define BAT_ADC_BASE 0x40010000U
#define BAT_ADC_CR (*(volatile uint32_t *)(BAT_ADC_BASE + 0x00U))
#define BAT_ADC_LST0 (*(volatile uint32_t *)(BAT_ADC_BASE + 0x04U))
#define BAT_ADC_STR (*(volatile uint32_t *)(BAT_ADC_BASE + 0x20U))
#define BAT_ADC_DR0 (*(volatile uint32_t *)(BAT_ADC_BASE + 0x30U))
#define BAT_ADC_TCR (*(volatile uint32_t *)(BAT_ADC_BASE + 0x70U))
#define BAT_ADC_TSR (*(volatile uint32_t *)(BAT_ADC_BASE + 0x74U))
#define BAT_ADC_CR_RUN 0x82U
#define BAT_ADC_ADCDIV_64 (6U << 16)
#define BAT_ADC_SAMPLE_CYCLES 16
#define BAT_ADC_VALID (1U << 31)
#define BAT_ADC_VALUE_MASK 0x0FFFU
#define BAT_SAMPLE_MS 100
#define BAT_FILTER_SCALE 16U
// The stock firmware's raw-ADC battery scale and low-battery threshold.
#define BAT_MIN_RAW 0x0A96U
#define BAT_MAX_RAW 0x0E10U
#define BAT_ZERO_RAW 0x0A8CU
#define BAT_COUNTS_PER_PERCENT 9U
#define BAT_LOW_RAW 0x0B25U

#define EXTI_WAKUPCR (*(volatile uint32_t *)(EXTI_BASE + 0x50U))
#define EXTI_WAKUPPOLR (*(volatile uint32_t *)(EXTI_BASE + 0x54U))
#define EXTI_WAKUPFLG (*(volatile uint32_t *)(EXTI_BASE + 0x58U))
#define EXTI_WAKUPCR_EVWUPIEN (1U << 31)
#define EXTI_ALL_LINES 0xFFFFU
#define EVWUP_IRQ 3
#define WDT_PR_UNLOCK 0x35CA

#define TYPE_SETTLE_MS 20
#define TYPE_SHIFT_BIT 0x80
#define TYPE_USAGE_MASK 0x7F

// Choices for SLEEP1..SLEEP9, in minutes; 0 never sleeps.
static const uint8_t sleep_minutes[]        = {1, 2, 5, 10, 15, 30, 60, 120, 0};
static const pin_t   wake_rows[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t   wake_cols[MATRIX_COLS] = MATRIX_COL_PINS;
static const char    type_punct[]           = " %";
static const uint8_t type_punct_codes[]     = {KC_SPC, TYPE_SHIFT_BIT | KC_5};
// The stock firmware's low-battery Caps Lock blink pattern, in milliseconds.
static const uint16_t low_led_ms[] = {1, 50, 50, 50, 50, 50, 150, 150, 50, 150, 50, 150, 150, 50, 50, 50, 50, 50, 2000};

static uint8_t  sleep_after_min = SLEEP_DEFAULT_MINUTES;
static bool     slept;
static uint32_t bat_filtered;
static uint16_t bat_sampled_at;
static uint32_t awake_since;
static uint32_t pointer_activity_at;
static uint32_t input_at;
static bool     low_led_active;
static uint8_t  low_led_step;
static uint16_t low_led_at;

// Restores the matrix pins after deep sleep; defined weak and non-static in quantum/matrix.c.
void matrix_init_pins(void);

static bool on_battery(void) {
    return !gpio_read_pin(SHURA_WAKEUP_PIN);
}

// PA0 (ADC channel 0), CK_AHB/64, continuous conversion.
static void adc_start(void) {
    CKCU->APBCCR1 |= CKCU_APBCCR1_ADCEN;
    CKCU->APBCFGR = (CKCU->APBCFGR & ~CKCU_APBCFGR_ADCDIV_MASK) | BAT_ADC_ADCDIV_64;
    // Analog mode selects the ADC pin mux, not a digital GPIO input.
    palSetLineMode(SHURA_BATTERY_PIN, PAL_MODE_INPUT_ANALOG);
    BAT_ADC_CR   = 0;
    BAT_ADC_LST0 = 0;
    BAT_ADC_STR  = BAT_ADC_SAMPLE_CYCLES;
    BAT_ADC_TCR  = 1;
    BAT_ADC_CR   = BAT_ADC_CR_RUN;
    BAT_ADC_TSR  = 1;
}

static void adc_stop(void) {
    BAT_ADC_CR = 0;
    CKCU->APBCCR1 &= ~CKCU_APBCCR1_ADCEN;
}

static uint16_t battery_raw(void) {
    return bat_filtered / BAT_FILTER_SCALE;
}

uint8_t battery_percent(void) {
    uint16_t raw = battery_raw();

    if (raw < BAT_MIN_RAW) {
        return 1;
    }
    if (raw >= BAT_MAX_RAW) {
        return 100;
    }
    return (raw - BAT_ZERO_RAW) / BAT_COUNTS_PER_PERCENT;
}

static void battery_task(void) {
    uint32_t result;
    uint16_t raw;

    if (timer_elapsed(bat_sampled_at) < BAT_SAMPLE_MS) {
        return;
    }
    bat_sampled_at = timer_read();
    result         = BAT_ADC_DR0;
    if (!(result & BAT_ADC_VALID)) {
        return;
    }
    raw          = result & BAT_ADC_VALUE_MASK;
    bat_filtered = bat_filtered ? bat_filtered - bat_filtered / BAT_FILTER_SCALE + raw : (uint32_t)raw * BAT_FILTER_SCALE;
    if (on_battery()) {
        ble_set_battery(battery_percent());
    }
}

static void low_battery_led_task(void) {
    bool low = on_battery() && bat_filtered != 0 && battery_raw() <= BAT_LOW_RAW;

    if (!low || ble_pairing()) {
        if (low_led_active && !ble_pairing()) {
            led_update_ports(host_keyboard_led_state());
        }
        low_led_active = false;
        low_led_step   = 0;
        return;
    }
    if (low_led_active && timer_elapsed(low_led_at) < low_led_ms[low_led_step]) {
        return;
    }
    if (low_led_active) {
        low_led_step = (low_led_step + 1) % ARRAY_SIZE(low_led_ms);
    }
    low_led_active = true;
    low_led_at     = timer_read();
    if (low_led_step & 1) {
        gpio_write_pin_low(SHURA_CAPS_LED_PIN);
    } else {
        gpio_write_pin_high(SHURA_CAPS_LED_PIN);
    }
}

void power_input(void) {
    input_at = timer_read32();
}

void power_pointer_activity(void) {
    pointer_activity_at = timer_read32();
    power_input();
}

// Columns high and rows pulled down, so any key press raises an EXTI row line.
static void prepare_wake_pins(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (col == PROFILE_SWITCH_COL) {
            gpio_set_pin_input_low(wake_cols[col]);
        } else {
            gpio_set_pin_output(wake_cols[col]);
            gpio_write_pin_high(wake_cols[col]);
        }
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        gpio_set_pin_input_low(wake_rows[row]);
    }
    // Route the wake lines to EXTI; GPIO direction alone does not select their ports.
    CKCU->APBCCR0 |= CKCU_APBCCR0_AFIOEN | CKCU_APBCCR0_EXTIEN;
    AFIO->ESSR[0] = SHURA_WAKE_ESSR0;
    AFIO->ESSR[1] = SHURA_WAKE_ESSR1;
}

static void enter_deep_sleep(void) {
    uint32_t nvic;
    uint32_t systick;
    uint16_t held;

    // Lines already high (keys held while going to sleep) wake on their falling edge.
    EXTI_WAKUPPOLR = 0;
    EXTI_WAKUPCR   = SHURA_WAKE_LINES;
    EXTI_WAKUPFLG  = EXTI_ALL_LINES;
    wait_us(1000);
    held = EXTI_WAKUPFLG & SHURA_WAKE_LINES;
#ifdef SHURA_BLE4
    // Invert only held keys. A PB10/PB12 assertion during setup is a wake request,
    // not a reason to wait for the module to finish or the USB cable to be removed.
    EXTI_WAKUPPOLR = held & SHURA_MATRIX_WAKE_LINES;
    EXTI_WAKUPFLG  = SHURA_MATRIX_WAKE_LINES;
#else
    EXTI_WAKUPPOLR = held;
    EXTI_WAKUPFLG  = EXTI_ALL_LINES;
#endif
    EXTI_WAKUPCR = SHURA_WAKE_LINES | EXTI_WAKUPCR_EVWUPIEN;

    chSysLock();
    nvic          = NVIC->ISER[0];
    systick       = SysTick->CTRL;
    NVIC->ICER[0] = UINT32_MAX;
    SysTick->CTRL = 0;
    SCB->ICSR     = SCB_ICSR_PENDSTCLR_Msk;
    NVIC->ICPR[0] = 1U << EVWUP_IRQ;
    NVIC->ISER[0] = 1U << EVWUP_IRQ;
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    TEX_WDT_RELOAD();
    __DSB();
    __WFI();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    ht32_clock_init();
    boardInit();
    EXTI_WAKUPCR  = 0;
    EXTI_WAKUPFLG = EXTI_ALL_LINES;
    NVIC->ICER[0] = 1U << EVWUP_IRQ;
    NVIC->ICPR[0] = 1U << EVWUP_IRQ;
    NVIC->ISER[0] = nvic;
    SysTick->VAL  = 0;
    SysTick->CTRL = systick;
    chSysUnlock();
}

static void power_sleep(void) {
    tp_power_off();
    ble_sleep();
    adc_stop();
    gpio_write_pin_high(SHURA_CAPS_LED_PIN);
    prepare_wake_pins();
    // Halt the watchdog during deep sleep.
    WDT->PR  = WDT_PR_UNLOCK;
    WDT->MR0 = (WDT->MR0 & ~WDT_MR0_WDTSHLT_MASK) | WDT_MR0_WDTSHLT_MODE2;
    WDT->PR  = 0;
    enter_deep_sleep();
    matrix_init_pins();
    adc_start();
    tp_power_on();
    ble_wake();
    led_update_ports(host_keyboard_led_state());
    awake_since = timer_read32();
    slept       = true;
}

void power_init(void) {
    // Select the GPIO mux as well as enabling PB12's digital input.
    palSetLineMode(SHURA_WAKEUP_PIN, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_HT32_MODE_INE);
    adc_start();
    awake_since = timer_read32();
}

void power_task(void) {
    uint32_t idle_ms = sleep_after_min * MINUTE_MS;

    battery_task();
    low_battery_led_task();
#ifdef SHURA_BLE4
    static bool     was_asleep;
    static uint32_t af_at;
    bool            radio_asleep = ble4_radio_asleep();
    if (radio_asleep && !was_asleep) {
        af_at = timer_read32();
    }
    was_asleep = radio_asleep;
    // Sample even on USB or when sleep is disabled: PB12 is not an independent
    // USB indication until PB10 has been low for three consecutive checks.
    if (!ble4_can_sleep()) {
        return;
    }
    // Keep an earlier user deadline, but don't sleep immediately at AF just
    // because the last input was long ago. Zero means never, even after AF.
    if (radio_asleep && idle_ms > BLE4_POST_AF_IDLE_MS && timer_elapsed32(af_at) >= BLE4_POST_AF_IDLE_MS) {
        idle_ms = BLE4_POST_AF_IDLE_MS;
    }
#endif
    uint32_t grace_ms = slept ? WAKE_GRACE_MS : idle_ms;
    if (idle_ms != 0 && on_battery() && last_input_activity_elapsed() >= idle_ms && timer_elapsed32(input_at) >= idle_ms && timer_elapsed32(pointer_activity_at) >= idle_ms && timer_elapsed32(awake_since) >= grace_ms) {
        power_sleep();
    }
}

static void type_event(uint8_t code, bool pressed) {
    if (pressed) {
        register_code(code);
    } else {
        unregister_code(code);
    }
    ble_flush_keys(TYPE_SETTLE_MS);
}

static uint8_t character_code(char character) {
    if (character >= 'a' && character <= 'z') {
        return KC_A + character - 'a';
    }
    if (character >= '1' && character <= '9') {
        return KC_1 + character - '1';
    }
    if (character == '0') {
        return KC_0;
    }
    for (uint8_t i = 0; i < sizeof(type_punct_codes); i++) {
        if (character == type_punct[i]) {
            return type_punct_codes[i];
        }
    }
    return KC_NO;
}

// Types lower-case letters, digits, space and '%' (US layout) over USB or Bluetooth.
void type_text(const char *text) {
    uint8_t mods = get_mods();

    clear_mods();
    for (; *text; text++) {
        uint8_t code = character_code(*text);

        if (code == KC_NO) {
            continue;
        }
        if (code & TYPE_SHIFT_BIT) {
            type_event(KC_LSFT, true);
        }
        type_event(code & TYPE_USAGE_MASK, true);
        type_event(code & TYPE_USAGE_MASK, false);
        if (code & TYPE_SHIFT_BIT) {
            type_event(KC_LSFT, false);
        }
    }
    set_mods(mods);
    send_keyboard_report();
}

void type_number(uint16_t number, const char *after) {
    char    buffer[6];
    uint8_t i = sizeof(buffer) - 1;

    buffer[i] = '\0';
    do {
        buffer[--i] = '0' + number % 10;
        number /= 10;
    } while (number != 0);
    type_text(buffer + i);
    type_text(after);
}

static void type_sleep_time(void) {
    if (sleep_after_min != 0) {
        type_number(sleep_after_min, "m");
    } else {
        type_text("never");
    }
}

void power_set_sleep(uint8_t choice, bool announce) {
    if (choice >= ARRAY_SIZE(sleep_minutes)) {
        return;
    }
    sleep_after_min = sleep_minutes[choice];
    if (announce) {
        type_text("sleep ");
        type_sleep_time();
    }
}

// Types e.g. "bat 57% sleep 15m tp 1", or "usb sleep 15m tp 1" on USB power.
void battery_report(void) {
    if (on_battery()) {
        type_text("bat ");
        type_number(battery_percent(), "% ");
    } else {
        type_text("usb ");
    }
    type_text("sleep ");
    type_sleep_time();
    type_text(" tp ");
    type_number(tp_level + 1, "");
}
