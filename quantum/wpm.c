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
static uint16_t wpm_timer   = 0;

// This smoothing is 40 keystrokes
static const float wpm_smoothing = WPM_SMOOTHING;

void set_current_wpm(uint8_t new_wpm) { current_wpm = new_wpm; }

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
    if (keycode == KC_DEL || keycode == KC_BSPC) {
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

void update_wpm(uint16_t keycode) {
    if (wpm_keycode(keycode)) {
        if (wpm_timer > 0) {
            uint16_t latest_wpm = 60000 / timer_elapsed(wpm_timer) / WPM_ESTIMATED_WORD_SIZE;
            if (latest_wpm > UINT8_MAX) {
                latest_wpm = UINT8_MAX;
            }
            current_wpm += ceilf((latest_wpm - current_wpm) * wpm_smoothing);
        }
        wpm_timer = timer_read();
    }
#ifdef WPM_ALLOW_COUNT_REGRESSION
    uint8_t regress = wpm_regress_count(keycode);
    if (regress) {
        if (current_wpm < regress) {
            current_wpm = 0;
        } else {
            current_wpm -= regress;
        }
        wpm_timer = timer_read();
    }
#endif
}

void decay_wpm(void) {
    if (timer_elapsed(wpm_timer) > 1000) {
        current_wpm += (-current_wpm) * wpm_smoothing;
        wpm_timer = timer_read();
    }
}
