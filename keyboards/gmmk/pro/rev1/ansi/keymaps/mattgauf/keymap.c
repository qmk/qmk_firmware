/* Copyright 2021 Matt Gauf
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

// clang-format off
#include QMK_KEYBOARD_H
#include "keymap_helpers.h"


enum custom_codes {
    SET_MP = RGB_M_P,
    SET_MB = RGB_M_B,
    SET_MR = RGB_M_R,

    MG_F17 = SAFE_RANGE,
    MG_F18,
    MG_F19
};


enum layer_names {
    _DEFAULT = 0,
    _EFFECTS,
    _UTILITY,
    _DFUMODE
};


// static uint8_t  rgb_pin_fn_column[]       = {PIN_DEL,PIN_PGUP,PIN_PGDN,PIN_END};
// static uint8_t  rgb_pin_left_underglow[]  = {PIN_LED_L01,PIN_LED_L02,PIN_LED_L03,PIN_LED_L04,PIN_LED_L05,PIN_LED_L06,PIN_LED_L07,PIN_LED_L08};
// static uint8_t  rgb_pin_right_underglow[] = {PIN_LED_L11,PIN_LED_L12,PIN_LED_L13,PIN_LED_L14,PIN_LED_L15,PIN_LED_L16,PIN_LED_L17,PIN_LED_L18};


#define MODS_SHIFT ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
#define MODS_CTRL  ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL)
#define MODS_ALT   ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT)
#define MODS_GUI   ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT(KC_ESC,   KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MG_F17,       KC_MUTE,
                      KC_GRV,   KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,      KC_HOME,
                      KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      KC_PGUP,
                      KC_CAPS,  KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                KC_PGDN,
                      KC_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,        KC_END,
                      KC_LCTL,  KC_LALT, KC_LGUI,                  KC_SPC,                    KC_RGUI, KC_RALT, MO(_EFFECTS),     KC_LEFT, KC_DOWN, KC_RGHT),

  [_EFFECTS] = LAYOUT(_______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, MG_F18,       _______,
                      _______, SET_MP,  SET_MB,  SET_MR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      RGB_MOD,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      RGB_RMOD,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               RGB_SPI,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______,          RGB_SAI,      RGB_SPD,
                      _______, _______, _______,                   _______,              TG(_UTILITY), MO(_DFUMODE), _______,     RGB_HUD, RGB_SAD, RGB_HUI),

  [_UTILITY] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______, DM_PLY1, DM_PLY2, DM_REC1, DM_REC2, DM_RSTP,      _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,      _______,
                      _______, _______, _______,                   _______,                   _______, _______, _______,          _______, _______, _______),

  [_DFUMODE] = LAYOUT(QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MG_F19,       DEBUG,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,      _______,
                      _______, _______, _______,                   _______,                   _______, _______, _______,          _______, _______, _______),
};
// Runs constantly in the background, in a loop.
void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_get_flags() & (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER)) {

        if (IS_LAYER_ON(_UTILITY)) {
            rgb_matrix_set_color(PIN_F9,    LEDGREE);
            rgb_matrix_set_color(PIN_F10,   LEDGREE);
            rgb_matrix_set_color(PIN_F11,   LED_RED);
            rgb_matrix_set_color(PIN_F12,   LED_RED);
            rgb_matrix_set_color(PIN_PRINT, LEDTEAL);
        }

        switch (get_highest_layer(layer_state)) {
            case _DFUMODE:
                rgb_matrix_set_color_all(LED_OFF);
                rgb_matrix_set_color(PIN_ESC,   LED_RED);
                rgb_matrix_set_color(PIN_PRINT, LEDORAN);
                return;
            case _EFFECTS:
                rgb_matrix_set_color(PIN_PRINT, LEDGREE);
                break;
            default:
                break;
        }

        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(PIN_CAPS, RGB_WHITE);
        }

    }
}


// Called on start
void dynamic_macro_record_start_user(void) {
    dprint("-- Recording Started\n");
    layer_on(_UTILITY);
}


// Called on end
void dynamic_macro_record_end_user(int8_t direction) {
    dprint("-- Recording Ended\n");
}


// Called on playback
void dynamic_macro_play_user(int8_t direction) {
    dprint("-- Recording Playing\n");
}


// Runs on encoder event
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t curr_mod = get_mods();

    if (IS_LAYER_ON(_EFFECTS)) {
        if (clockwise) {
            rgb_matrix_increase_val();
        } else {
            rgb_matrix_decrease_val();
        }
    } else {
        if (MODS_GUI) {
            if (MODS_GUI && MODS_SHIFT) {
                clear_mods();
                if (clockwise) {
                    tap_code16(LSG(KC_Z));
                } else {
                    tap_code16(LGUI(KC_Z));
                }
                set_mods(curr_mod);
            } else if (MODS_GUI && MODS_ALT) {
                clear_mods();
                if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
                set_mods(curr_mod);
            } else {
                if (clockwise) {
                    tap_code16(LGUI(KC_TAB));
                } else {
                    tap_code16(LSG(KC_TAB));
                }
            }
        } else {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    return true;
}


// Runs on key event
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MG_F17:
            if (record->event.pressed) {
                tap_code16(HYPR(KC_F17));
            }
            return false;
        case MG_F18:
            if (record->event.pressed) {
                tap_code16(HYPR(KC_F18));
            }
            return false;
        case MG_F19:
            if (record->event.pressed) {
                tap_code16(HYPR(KC_F19));
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        break;
                }
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
// clang-format on
