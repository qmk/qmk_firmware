/* Copyright 2015-2021 Jack Humbert
 * Copyright 2022 Rocco Meli <@RMeli>
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
#include "muse.h"

#include "rmeli.h"

enum preonic_layers { _QWERTY, _COLEMAK, _LOWER, _RAISE, _ADJUST };
enum preonic_keycodes { QWERTY = SAFE_RANGE, COLEMAK, LOWER, RAISE, BACKLIT };

#define ____________________BOTTOM_L_x6_____________________ BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC
#define ____________________BOTTOM_R_x6_____________________ KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT

/* LAYOUT
 *
 * ,-----------------------------------------------------------.
 * |    |    |    |    |    |    |    |    |    |    |    |    |
 * |----+----+----+----+----+----+----+----+----+----+----+----|
 * |    |    |    |    |    |    |    |    |    |    |    |    |
 * |----+----+----+----+----+----+----+----+----+----+----+----|
 * |    |    |    |    |    |    |    |    |    |    |    |    |
 * |----+----+----+----+----+----+----+----+----+----+----+----|
 * |    |    |    |    |    |    |    |    |    |    |    |    |
 * |----+----+----+----+----+----+----+----+----+----+----+----|
 * |    |    |    |    |    |    |    |    |    |    |    |    |
 * `----+----+----+----+----+----+----+----+----+----+----+----'
 */

// Define wrapper for standard CRKB layout
#define LAYOUT_wrapper(...) LAYOUT_preonic_grid(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_wrapper(
    ___________________NUMBER_LEFT_x6___________________, ___________________NUMBER_RIGHT_x6__________________,
    ___________________QWERTY_L1_x6_____________________, ___________________QWERTY_R1_x6_____________________,
    ___________________QWERTY_L2_x6_____________________, ___________________QWERTY_R2_x6_____________________,
    ___________________QWERTY_L3_x6_____________________, ___________________QWERTY_R3_x6_____________________,
    ____________________BOTTOM_L_x6_____________________, ____________________BOTTOM_R_x6_____________________
),

[_COLEMAK] = LAYOUT_wrapper(
    ___________________NUMBER_LEFT_x6___________________, ___________________NUMBER_RIGHT_x6__________________,
    ________________COLEMAK_MOD_DH_L1_x6________________, ________________COLEMAK_MOD_DH_R1_x6________________,
    ________________COLEMAK_MOD_DH_L2_x6________________, ________________COLEMAK_MOD_DH_R2_x6________________,
    ________________COLEMAK_MOD_DH_L3_x6________________, ________________COLEMAK_MOD_DH_R3_x6________________,
    ____________________BOTTOM_L_x6_____________________, ____________________BOTTOM_R_x6_____________________
),

[_LOWER] = LAYOUT_wrapper(
  ____________________FUNC_LEFT_x6____________________, ____________________FUNC_RIGHT_x6___________________,
  ___________________NUMBER_LEFT_x6___________________, ___________________NUMBER_RIGHT_x6__________________,
  _______, ______________UNICODE_L2_x5________________, ________________NAV_R2_x5__________________, XXXXXXX,
  _______, ______________UNICODE_L3_x5________________, ________________NAV_R3_x5__________________, _______,
  ______________________BLANK_6x______________________, ______________________BLANK_6x______________________
),

[_RAISE] = LAYOUT_wrapper(
  ___________________NUMBER_LEFT_x6___________________, ___________________NUMBER_RIGHT_x6__________________,
  ___________________SYMBOL_LEFT_x6___________________, ___________________SYMBOL_RIGHT_x6__________________,
  _______, ____________NAV_VIM_x4____________, XXXXXXX, ____________________SYMBOL_R2_x6____________________,
  _______, _________________NONE_5x___________________, ____________________SYMBOL_R3_x6____________________,
  ______________________BLANK_6x______________________, ______________________BLANK_6x______________________
),

[_ADJUST] = LAYOUT_wrapper(
  QK_BOOT, _________________NONE_5x___________________, ______________________NONE_6x_______________________,
  XXXXXXX, MU_ON,   AU_ON,   MI_ON,   XXXXXXX, XXXXXXX, _______________CONFIG_R1_x5________________,  QWERTY,
  QK_BOOT, MU_NEXT, AU_TOGG, MI_TOGG, XXXXXXX, XXXXXXX, _______________CONFIG_R2_x5________________, XXXXXXX,
  XXXXXXX, MU_OFF,  AU_OFF,  MI_OFF,  XXXXXXX, XXXXXXX, _______________CONFIG_R3_x5________________, COLEMAK,
  ______________________BLANK_6x______________________, ______________________BLANK_6x______________________
)
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
#ifdef RGBLIGHT_ENABLE
                rgblight_step();
#endif
#ifdef __AVR__
                writePinLow(E6);
#endif
            } else {
                unregister_code(KC_RSFT);
#ifdef __AVR__
                writePinHigh(E6);
#endif
            }
            return false;
            break;
    }
    return true;
};

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        } else {
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
