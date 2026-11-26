// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

// Baselines and thresholds.
//
// A key's baseline is its reading while released. A reading at or above
// baseline + EC_PRESS_TICKS counts as pressed, one at or below
// baseline + EC_RELEASE_TICKS as released, and in between the key keeps its
// state (hysteresis; values in config.h).
//
// The baselines track slow drift such as temperature. Once a second, each
// baseline is compared with the average of that second's released readings
// (those at or below the release threshold). A press can only raise the
// readings, so a lower average replaces the baseline in one step, while a
// higher one raises it by a single tick.
//
// The baseline is lowered only when released readings make up more than
// half of that second's readings: while a key is held, its few released
// readings are noise, and following them could leave the key stuck pressed.

#include "ecmacro4h.h"
#include "rc_pio.h"

#define EC_BASELINE_PERIOD_MS 1000
// The highest baseline whose press threshold is still a reachable reading
#define EC_BASELINE_MAX (RC_MAX_TICKS - EC_PRESS_TICKS)

STATIC_ASSERT(EC_RELEASE_TICKS > 0 && EC_RELEASE_TICKS < EC_PRESS_TICKS, "EC_RELEASE_TICKS must lie between 0 and EC_PRESS_TICKS");

static uint16_t baseline[EC_KEY_COUNT];
// Readings in the current second: how many, how many of them were released
// readings, and the sum of those. Capped at UINT16_MAX readings, so that
// the counts cannot overflow and the sum fits in 32 bits.
static uint16_t reading_count[EC_KEY_COUNT];
static uint16_t released_count[EC_KEY_COUNT];
static uint32_t released_sum[EC_KEY_COUNT];
static uint32_t period_start;

uint16_t ec_press_threshold(uint8_t key) {
    return baseline[key] + EC_PRESS_TICKS;
}

uint16_t ec_release_threshold(uint8_t key) {
    return baseline[key] + EC_RELEASE_TICKS;
}

// Once a second: move each baseline toward its released-reading average
// (see the top of this file) and restart the counts.
static void update_baselines(void) {
    for (uint8_t key = 0; key < EC_KEY_COUNT; key++) {
        if (released_count[key] != 0) {
            const uint16_t average = (released_sum[key] + released_count[key] / 2) / released_count[key];
            if (average < baseline[key] && released_count[key] > reading_count[key] / 2) {
                baseline[key] = average;
            } else if (average > baseline[key] && baseline[key] < EC_BASELINE_MAX) {
                baseline[key]++;
            }
        }
        reading_count[key]  = 0;
        released_count[key] = 0;
        released_sum[key]   = 0;
    }
}

// Called from matrix.c with every measurement; 0 ticks means it failed.
void ec_baseline_sample(uint8_t key, uint16_t ticks) {
    if (ticks != 0 && reading_count[key] < UINT16_MAX) {
        reading_count[key]++;
        if (ticks <= ec_release_threshold(key)) {
            released_count[key]++;
            released_sum[key] += ticks;
        }
    }
    // Checked with every reading, so that the baselines keep tracking while
    // the host is suspended (the matrix is still scanned then).
    if (timer_elapsed32(period_start) >= EC_BASELINE_PERIOD_MS) {
        update_baselines();
        period_start = timer_read32();
    }
}

void keyboard_pre_init_kb(void) {
    // Keep the XIAO RP2040 LEDs dark. The user LED (GP16, GP17, GP25) is
    // active low and can glow faintly while its pins are left as inputs;
    // driving GP11 low cuts the NeoPixel's power.
    const pin_t user_led[] = {GP16, GP17, GP25};
    for (uint8_t i = 0; i < ARRAY_SIZE(user_led); i++) {
        gpio_set_pin_output(user_led[i]);
        gpio_write_pin_high(user_led[i]);
    }
    gpio_set_pin_output(GP11);
    gpio_write_pin_low(GP11);

    // Start at the top, where only a reading of RC_MAX_TICKS would count as
    // pressed, until the first second of readings sets the baselines.
    for (uint8_t key = 0; key < EC_KEY_COUNT; key++) {
        baseline[key] = EC_BASELINE_MAX;
    }
    keyboard_pre_init_user();
}
