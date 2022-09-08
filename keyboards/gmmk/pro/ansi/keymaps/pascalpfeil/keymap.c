/* Copyright 2021 Pascal Pfeil
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

enum my_keycodes {
  MY_COPY = SAFE_RANGE,
  MY_PSTE,
  MY_UNDO,
  MY_SRCH,
  MY_BGNW,
  MY_ENDW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt               Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     \                 PgUp
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        BackSpc           Del
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [0] = LAYOUT(
        KC_GESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,          KC_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,
        MO(1),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NUM,           KC_MPLY,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  BS_SWAP,          RGB_VAI,
        _______, _______, _______, KC_END,  _______, _______, MY_COPY, MY_UNDO, _______, _______, MY_PSTE, _______, _______, BS_NORM,          RGB_HUI,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          RGB_TOG,          RGB_SPI,
        _______,          _______, KC_DEL,  _______, _______, KC_HOME, _______, _______, _______, _______, MY_SRCH,          _______, _______, RGB_MOD,
        _______, AG_NORM, AG_SWAP,                            _______,                            _______, _______, _______, KC_MPRV, _______, KC_MNXT
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};

inline bool is_windows_mode(void) {
  return !keymap_config.swap_lalt_lgui;
}

#define SEND_OS_SPECIFIC(windows_modifier, mac_modifier, keycode) tap_code16(is_windows_mode() ? LCTL(keycode) : LCMD(keycode))

#define KC_SEND_OS_SPECIFIC(windows_modifier, mac_modifier, keycode)  \
if (record->event.pressed) { \
  SEND_OS_SPECIFIC(windows_modifier, mac_modifier, keycode); \
} \
return false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_COPY:
      KC_SEND_OS_SPECIFIC(LCTL, LCMD, KC_C);
    case MY_PSTE:
      KC_SEND_OS_SPECIFIC(LCTL, LCMD, KC_V);
    case MY_UNDO:
      KC_SEND_OS_SPECIFIC(LCTL, LCMD, KC_Z);
    case MY_SRCH:
      KC_SEND_OS_SPECIFIC(LCTL, LCMD, KC_F);
    case MY_BGNW:
      KC_SEND_OS_SPECIFIC(LCTL, LALT, KC_LEFT);
    case MY_ENDW:
      KC_SEND_OS_SPECIFIC(LCTL, LALT, KC_RIGHT);
    default:
      return true;
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(0)) {
      tap_code(clockwise ? KC_VOLU : KC_VOLD);
    }

    if (IS_LAYER_ON(1)) {
      tap_code(clockwise ? KC_BRIU : KC_BRID);
    }
   
    return true;
}

const uint8_t left_side_leds[] = {67, 70, 73, 76, 80, 83, 87, 91};
const uint8_t left_side_leds_size = sizeof(left_side_leds) / sizeof(uint8_t);

const uint8_t right_side_leds[] = {68, 71, 74, 77, 81, 84, 88, 92};
const uint8_t right_side_leds_size = sizeof(right_side_leds) / sizeof(uint8_t);

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK))
        for (uint8_t i = 0; i < left_side_leds_size; i++)
            RGB_MATRIX_INDICATOR_SET_COLOR(left_side_leds[i], 0xFF, 0x00, 0x00); // set to red

    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK))
        for (uint8_t i = 0; i < right_side_leds_size; i++)
            RGB_MATRIX_INDICATOR_SET_COLOR(right_side_leds[i], 0xFF, 0x00, 0x00); // set to red
}
