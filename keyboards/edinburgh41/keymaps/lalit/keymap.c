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
  [_BASE] = LAYOUT_edinburgh41(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Z,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LT(RAISE, KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               TD(TD_H_DQT),     TD(TD_J_QUOTE),     KC_K,     KC_L,     KC_MS_BTN1,  KC_ENTER,
    LGUI(KC_TAB),  KC_Y,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_SCLN,
                                            KC_LCTL,   KC_LSFT,    KC_NO,   KC_SPC,    LOWER
  ),

  [_LOWER] = LAYOUT_edinburgh41(
    RGB_TOG,  KC_NO,  KC_LBRC,    KC_RBRC,  KC_NO,    KC_NO,            KC_NO,  LGUI(KC_SPC),  KC_MINUS,  LSFT(KC_EQUAL),  KC_NO,  LGUI(LSFT(KC_4)),
    _______,  KC_1,  KC_2,  KC_3,  KC_4,   KC_5,            KC_6,  KC_7,  KC_8,    KC_9,  KC_0,   KC_DEL,
    _______,  KC_NO,   LSFT(KC_LBRC),  LSFT(KC_RBRC),  KC_NO,   KC_NO,            KC_NO,  KC_EQUAL,   KC_BSLS,  KC_GRAVE,  KC_NO,  KC_NO,
                                            _______,   _______,  KC_NO,   _______,  _______
  ),

  [_RAISE] = LAYOUT_edinburgh41(
    _______,  KC_NO,     KC_UP,     KC_NO,     KC_NO,         KC_NO,               KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    _______,  KC_LEFT,  KC_DOWN,   KC_RIGHT,  KC_NO,   KC_NO,            KC_NO,    UE_UMLAUT,    OE_UMLAUT,    AE_UMLAUT,    SS_UMLAUT,    KC_NO,
    _______,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,            KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,
                                            _______,   _______,  KC_NO,  _______,  _______
  ),

  [_ADJUST] = LAYOUT_edinburgh41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            QK_BOOT,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
