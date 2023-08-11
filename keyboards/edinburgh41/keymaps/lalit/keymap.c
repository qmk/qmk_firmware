/* Copyright 2022 schwarzer-geiger
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

enum custom_keycodes {
    AE_UMLAUT = SAFE_RANGE,
    UE_UMLAUT,
    OE_UMLAUT,
    SS_UMLAUT
};

enum {
    TD_J_QUOTE,
    TD_H_DQT,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for J, twice for Semicolon
    [TD_J_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_QUOTE),
    // Tap once for K, twice for Colon
    [TD_H_DQT] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_DOUBLE_QUOTE),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Z,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LT(RAISE, KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               TD(TD_H_DQT),     TD(TD_J_QUOTE),     KC_K,     KC_L,     KC_MS_BTN1,  KC_ENTER,
    LGUI(KC_TAB),  KC_Y,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_SCLN,
                                            KC_LCTL,   KC_LSFT,    KC_NO,   KC_SPC,    LOWER
  ),

  [_LOWER] = LAYOUT(
    RGB_TOG,  KC_NO,  KC_LBRC,    KC_RBRC,  KC_NO,    KC_NO,            KC_NO,  LGUI(KC_SPC),  KC_MINUS,  LSFT(KC_EQUAL),  KC_NO,  LGUI(LSFT(KC_4)),
    _______,  KC_1,  KC_2,  KC_3,  KC_4,   KC_5,            KC_6,  KC_7,  KC_8,    KC_9,  KC_0,   KC_DEL,
    _______,  KC_NO,   LSFT(KC_LBRC),  LSFT(KC_RBRC),  KC_NO,   KC_NO,            KC_NO,  KC_EQUAL,   KC_BSLS,  KC_GRAVE,  KC_NO,  KC_NO,
                                            _______,   _______,  KC_NO,   _______,  _______
  ),

  [_RAISE] = LAYOUT(
    _______,  KC_NO,     KC_UP,     KC_NO,     KC_NO,         KC_NO,               KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    _______,  KC_LEFT,  KC_DOWN,   KC_RIGHT,  KC_NO,   KC_NO,            KC_NO,    UE_UMLAUT,    OE_UMLAUT,    AE_UMLAUT,    SS_UMLAUT,    KC_NO,
    _______,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,            KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,
                                            _______,   _______,  KC_NO,  _______,  _______
  ),

  [_ADJUST] = LAYOUT(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            QK_BOOT,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

// German Umlaute macro for Mac US keyboard

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case AE_UMLAUT:
        if (record->event.pressed) {
            // when keycode AE_UMLAUT is pressed
            SEND_STRING(SS_LALT("u") "a");
        } else {
            // when keycode AE_UMLAUT is released
        }
        break;
        case UE_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("u") "u");
        } else {
        }
        break;
        case OE_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("u") "o");
        } else {
        }
        break;
        case SS_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("s"));
        } else {
        }
        break;
    }
    return true;
};

// Thumbstick keymap, change KC_XXX to whatever you need

#define THUMBSTICK_RIGHT_TAP KC_RIGHT
#define THUMBSTICK_LEFT_TAP KC_LEFT
#define THUMBSTICK_UP_TAP KC_UP
#define THUMBSTICK_DOWN_TAP KC_DOWN

// Thumbstick code, no customisation needed

bool cursor_mode = false;
bool scrolling_mode = false;
bool tapping_mode = false;

// tracks if thumbstick was released
bool returned_to_zero = true;

// tracks how many times mouse_report.x/y have been read zero in succession
uint16_t zero_reads = 0;

// set mode depending on layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case SCROLLING_LAYER:
            if (scrolling_mode == false) {
            scrolling_mode = true;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            break;
        case TAPPING_LAYER:
            if (tapping_mode == false) {
                tapping_mode = true;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            break;
        default:
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode == false) {
                cursor_mode = true;
            }
            break;
    }
    return state;
}

// manipulate mouse report based on current mode
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (cursor_mode) {
        mouse_report.x = CURSOR_SPEED * mouse_report.x/100;
        mouse_report.y = CURSOR_SPEED * mouse_report.y/100;
    }
    if (scrolling_mode) {
        mouse_report.h = SCROLL_SPEED * mouse_report.x/100;
        mouse_report.v = SCROLL_SPEED * mouse_report.y/100;
        mouse_report.x = 0;
        mouse_report.y = 0;
        if ((mouse_report.h != 0) | (mouse_report.v != 0)) {
            _delay_ms(SCROLL_DELAY_MS);
        }

    } else if (tapping_mode) {
        if ((mouse_report.x || mouse_report.y) != 0) {
            if (returned_to_zero) {
                if (mouse_report.x > 0) {
                    tap_code16(THUMBSTICK_RIGHT_TAP);
                }
                if (mouse_report.x < 0) {
                    tap_code16(THUMBSTICK_LEFT_TAP);
                }
                if (mouse_report.y > 0) {
                    tap_code16(THUMBSTICK_DOWN_TAP);
                }
                if (mouse_report.y < 0) {
                    tap_code16(THUMBSTICK_UP_TAP);
                }
                returned_to_zero = false;
            }
            zero_reads = 0;
        } else if (zero_reads < 20) {
            zero_reads++;
        }
        if (zero_reads >= 20) {
            if (returned_to_zero == false) {
                returned_to_zero = true;
            }
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}
