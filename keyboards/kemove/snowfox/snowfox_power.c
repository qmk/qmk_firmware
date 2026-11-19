// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

// Battery level, sleep on battery and the factory reset key.

#include <string.h>
#include "snowfox.h"
#include "snowfox_power.h"
#include "snowfox_ble.h"
#include "sled17341.h"
#include "usb_util.h"

// The battery is read on AD4 (PIO0_15). Kemove's software maps these raw
// 10-bit readings to 0% and 100%.
#define BATTERY_ADC_CHANNEL 4
#define BATTERY_RAW_EMPTY 0x222
#define BATTERY_RAW_FULL 0x280
#define BATTERY_SAMPLE_MS 10000

// Lights off after this long without typing when no USB host is connected.
// Setting 0 is the default of 3 minutes, as the stock firmware.
static const uint8_t sleep_minutes[SNOWFOX_SLEEP_SETTINGS] = {3, 0, 1, 5, 10};

#define FACTORY_RESET_HOLD_MS 3000

// On battery, the main loop pauses this long between scans once no key has
// been pressed for IDLE_AFTER_MS, so the chip sleeps most of the time.
#define IDLE_AFTER_MS 500
#define IDLE_PAUSE_MS 1

#ifdef SNOWFOX_TEST
static bool     force_battery;
static uint16_t scan_rate;
#endif
static uint16_t battery_raw;
static bool     asleep;
static bool     lights_were_on;
static bool     reset_held;
static uint16_t reset_pressed_at;

#ifdef SNOWFOX_TEST
uint16_t snowfox_battery_log[32];
uint8_t  snowfox_battery_log_next;
#endif

static uint16_t battery_read_raw(void) {
    LPC_SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_ADC_PD;
    LPC_SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_ADC;

    // 48 MHz / 12 = 4 MHz ADC clock, start now.
    LPC_ADC->CR = (1U << BATTERY_ADC_CHANNEL) | (11U << 8) | (1U << 24);
    uint32_t data;
    uint16_t tries = 1000;
    do {
        data = LPC_ADC->DR[BATTERY_ADC_CHANNEL];
    } while (!(data & (1U << 31)) && --tries);
    LPC_ADC->CR = 0;

    return tries ? (data >> 6) & 0x3FF : 0;
}

bool snowfox_on_battery(void) {
#ifdef SNOWFOX_TEST
    if (force_battery) {
        return true;
    }
#endif
    return !usb_connected_state();
}

#ifdef SNOWFOX_TEST
void snowfox_power_force_battery(bool on) {
    force_battery = on;
}

uint16_t snowfox_scan_rate(void) {
    return scan_rate;
}

static void scan_rate_task(void) {
    static uint16_t scans;
    static uint16_t since;
    scans++;
    if (timer_elapsed(since) >= 1000) {
        scan_rate = scans;
        scans     = 0;
        since     = timer_read();
    }
}
#endif

static bool any_key_down(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if (matrix_get_row(row)) {
            return true;
        }
    }
    return false;
}

// A held key counts as activity too, so other keys pressed meanwhile are scanned at full speed.
static void idle_task(void) {
    if (snowfox_on_battery() && last_input_activity_elapsed() > IDLE_AFTER_MS && !any_key_down()) {
        chThdSleepMilliseconds(IDLE_PAUSE_MS);
    }
}

uint16_t snowfox_battery_raw(void) {
    return battery_raw;
}

// The lights pull the voltage down while they draw current, so a single reading
// can look several percent low. The level is the highest reading of the last
// minute, which is the closest to the battery's resting voltage.
#define BATTERY_RECENT 6

static uint16_t battery_recent[BATTERY_RECENT];

uint8_t snowfox_battery_percent(void) {
    uint16_t level = 0;
    for (uint8_t i = 0; i < BATTERY_RECENT; i++) {
        if (battery_recent[i] > level) {
            level = battery_recent[i];
        }
    }
    if (level <= BATTERY_RAW_EMPTY) {
        return 0;
    }
    if (level >= BATTERY_RAW_FULL) {
        return 100;
    }
    return (uint32_t)(level - BATTERY_RAW_EMPTY) * 100 / (BATTERY_RAW_FULL - BATTERY_RAW_EMPTY);
}

static void battery_task(void) {
    static uint16_t last;
    if (battery_raw != 0 && timer_elapsed(last) < BATTERY_SAMPLE_MS) {
        return;
    }
    // The radio draws bursts of current while it connects or pairs, which pulls
    // the reading down. Try again a second later.
    ble_state_t ble = snowfox_ble_handle()->state;
    if (battery_raw != 0 && (ble == CONNECTING || ble == DISCOVERING)) {
        last = timer_read() - BATTERY_SAMPLE_MS + 1000;
        return;
    }
    last = timer_read();

    uint32_t sum = 0;
    for (uint8_t i = 0; i < 8; i++) {
        sum += battery_read_raw();
    }
    battery_raw = sum / 8;

    // On USB the charger lifts the voltage, so readings from before an unplug
    // would hide the battery's real level for a minute.
    static bool    was_on_battery;
    static uint8_t next;
    bool           on_battery = snowfox_on_battery();
    if (on_battery != was_on_battery) {
        memset(battery_recent, 0, sizeof(battery_recent));
        was_on_battery = on_battery;
    }
    battery_recent[next++ % BATTERY_RECENT] = battery_raw;
#ifdef SNOWFOX_TEST
    // Test builds: the last 32 readings, top bit set when on battery.
    snowfox_battery_log[snowfox_battery_log_next++ % 32] = battery_raw | (snowfox_on_battery() ? 0x8000 : 0);
#endif
}


uint8_t snowfox_sleep_setting(void) {
    snowfox_config_t config = snowfox_config_read();
    return config.sleep < SNOWFOX_SLEEP_SETTINGS ? config.sleep : 0;
}

void snowfox_set_sleep_setting(uint8_t setting) {
    snowfox_config_t config = snowfox_config_read();
    config.sleep            = setting < SNOWFOX_SLEEP_SETTINGS ? setting : 0;
    snowfox_config_write(config);
}

static void sleep_task(void) {
    static uint8_t  setting = UINT8_MAX;
    static uint16_t checked;
    if (setting == UINT8_MAX || timer_elapsed(checked) > 1000) {
        setting = snowfox_sleep_setting();
        checked = timer_read();
    }
    uint32_t sleep_ms = sleep_minutes[setting] * 60000UL;
    bool     idle     = sleep_ms > 0 && snowfox_on_battery() && last_input_activity_elapsed() > sleep_ms;

    if (idle && !asleep) {
        asleep         = true;
        lights_were_on = rgb_matrix_is_enabled();
        rgb_matrix_disable_noeeprom();
        sled_off();
    } else if (!idle && asleep) {
        asleep = false;
        sled_on();
        if (lights_were_on) {
            rgb_matrix_enable_noeeprom();
        }
    }
}

void snowfox_factory_reset(void) {
    eeconfig_disable();
    soft_reset_keyboard();
}

static void factory_reset_task(void) {
    if (reset_held && timer_elapsed(reset_pressed_at) >= FACTORY_RESET_HOLD_MS) {
        reset_held = false;
        snowfox_factory_reset();
    }
}

void snowfox_power_task(void) {
#ifdef SNOWFOX_TEST
    scan_rate_task();
#endif
    battery_task();
    sleep_task();
    factory_reset_task();
    idle_task();
}

bool snowfox_power_asleep(void) {
    return asleep;
}

// How far the reset hold has got, 0 to 100.
uint8_t snowfox_factory_reset_progress(void) {
    if (!reset_held) {
        return 0;
    }
    uint16_t held = timer_elapsed(reset_pressed_at);
    return held >= FACTORY_RESET_HOLD_MS ? 100 : (uint32_t)held * 100 / FACTORY_RESET_HOLD_MS;
}

void snowfox_factory_reset_key(bool pressed) {
    reset_held = pressed;
    if (pressed) {
        reset_pressed_at = timer_read();
    }
}
