/*
 * Copyright 2020 Richard Sutherland (rich@brickbots.com)
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

#include "wpm.h"

#include <math.h>

// WPM Stuff
static uint8_t  current_wpm = 0;
static uint32_t wpm_timer   = 0;
#ifndef WPM_UNFILTERED
static uint32_t smoothing_timer = 0;
#endif

/* The WPM calculation works by specifying a certain number of 'periods' inside
 * a ring buffer, and we count the number of keypresses which occur in each of
 * those periods.  Then to calculate WPM, we add up all of the keypresses in
 * the whole ring buffer, divide by the number of keypresses in a 'word', and
 * then adjust for how much time is captured by our ring buffer.  Right now
 * the ring buffer is hardcoded below to be six half-second periods, accounting
 * for a total WPM sampling period of up to three seconds of typing.
 *
 * Whenever our WPM drops to absolute zero due to no typing occurring within
 * any contiguous three seconds, we reset and start measuring fresh,
 * which lets our WPM immediately reach the correct value even before a full
 * three second sampling buffer has been filled.
 */
#define MAX_PERIODS (WPM_SAMPLE_PERIODS)
#define PERIOD_DURATION (1000 * WPM_SAMPLE_SECONDS / MAX_PERIODS)
#define LATENCY (100)
static int8_t  period_presses[MAX_PERIODS] = {0};
static uint8_t current_period              = 0;
static uint8_t periods                     = 1;

#if !defined(WPM_UNFILTERED)
static uint8_t prev_wpm = 0;
static uint8_t next_wpm = 0;
#endif

void    set_current_wpm(uint8_t new_wpm) { current_wpm = new_wpm; }
uint8_t get_current_wpm(void) { return current_wpm; }

bool wpm_keycode(uint16_t keycode) { return wpm_keycode_kb(keycode); }

__attribute__((weak)) bool wpm_keycode_kb(uint16_t keycode) { return wpm_keycode_user(keycode); }

__attribute__((weak)) bool wpm_keycode_user(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLASH)) {
        return true;
    }

    return false;
}

#ifdef WPM_ALLOW_COUNT_REGRESSION
__attribute__((weak)) uint8_t wpm_regress_count(uint16_t keycode) {
    bool weak_modded = (keycode >= QK_LCTL && keycode < QK_LSFT) || (keycode >= QK_RCTL && keycode < QK_RSFT);

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if (keycode == KC_DELETE || keycode == KC_BACKSPACE) {
        if (((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) || weak_modded) {
            return WPM_ESTIMATED_WORD_SIZE;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
#endif

// Outside 'raw' mode we smooth results over time.

void update_wpm(uint16_t keycode) {
    if (wpm_keycode(keycode)) {
        period_presses[current_period]++;
    }
#ifdef WPM_ALLOW_COUNT_REGRESSION
    uint8_t regress = wpm_regress_count(keycode);
    if (regress) {
        period_presses[current_period]--;
    }
#endif
}

void decay_wpm(void) {
    int32_t presses = period_presses[0];
    for (int i = 1; i <= periods; i++) {
        presses += period_presses[i];
    }
    if (presses < 0) {
        presses = 0;
    }
    int32_t  elapsed  = timer_elapsed32(wpm_timer);
    uint32_t duration = (((periods)*PERIOD_DURATION) + elapsed);
    uint32_t wpm_now  = (60000 * presses) / (duration * WPM_ESTIMATED_WORD_SIZE);
    wpm_now           = (wpm_now > 240) ? 240 : wpm_now;

    if (elapsed > PERIOD_DURATION) {
        current_period                 = (current_period + 1) % MAX_PERIODS;
        period_presses[current_period] = 0;
        periods                        = (periods < MAX_PERIODS - 1) ? periods + 1 : MAX_PERIODS - 1;
        elapsed                        = 0;
        /* if (wpm_timer == 0) { */
        wpm_timer = timer_read32();
        /* } else { */
        /*     wpm_timer += PERIOD_DURATION; */
        /* } */
    }
    if (presses < 2)  // don't guess high WPM based on a single keypress.
        wpm_now = 0;

#if defined WPM_LAUNCH_CONTROL
    if (presses == 0) {
        current_period = 0;
        periods        = 0;
        wpm_now        = 0;
    }
#endif  // WPM_LAUNCH_CONTROL

#ifndef WPM_UNFILTERED
    int32_t latency = timer_elapsed32(smoothing_timer);
    if (latency > LATENCY) {
        smoothing_timer = timer_read32();
        prev_wpm        = current_wpm;
        next_wpm        = wpm_now;
    }

    current_wpm = prev_wpm + (latency * ((int)next_wpm - (int)prev_wpm) / LATENCY);
#else
    current_wpm = wpm_now;
#endif
}
