/* Copyright 2020 ipetepete
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

enum layers {
_qwerty,
_gamer,
_colemak,
_fn,
_rgb,
_spcfn
};


enum keycodes {
gamer = SAFE_RANGE,
qwerty,
colemak
};

#define KC_SPFN LT(_spcfn, KC_SPC) // press for space, hold for function layer (aka spacefn)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_qwerty] = LAYOUT_60_ansi(
        KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPFN,                             KC_RALT, KC_RCTL, MO(_fn),   MO(_rgb)
    ),
    // Gamer standard qwerty layout but with normal space for jumping etc
    [_gamer] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            KC_SPACE,                            _______, _______, _______, _______
    ),
    [_colemak] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  _______, _______, _______,
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,          _______,
        _______,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    _______, _______, _______,           _______,
        _______, _______, _______,                            KC_SPFN,                            _______, _______, _______,  _______
    ),
    [_fn] = LAYOUT_60_ansi(
        KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          _______,
        KC_MPLY,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_PGDN,          KC_MNXT,
        qwerty, colemak, gamer,                            _______,                            _______, _______, _______, _______
    ),
    [_rgb] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [_spcfn] = LAYOUT_60_ansi(
        _______, SGUI(1), SGUI(2), SGUI(3), SGUI(4), SGUI(5), SGUI(6), SGUI(7),  SGUI(8), SGUI(9), SGUI(0), _______,  _______, KC_DEL,
        _______, _______, _______, KC_PGUP, _______, KC_LBRC, KC_RBRC,  _______, KC_UP,   _______, _______, _______,  _______, _______,
        KC_CAPS, _______, _______, KC_PGDN, _______, KC_LCBR, KC_RCBR,  KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, KC_LPRN, KC_RPRN,  _______, _______, _______, _______,           _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case qwerty:
        if (record->event.pressed) {
            layer_clear();
            layer_on(_qwerty);
            set_single_persistent_default_layer(_qwerty);
        }
        return false;
        break;
      case colemak:
        if (record->event.pressed) {
            layer_clear();
            layer_on(_colemak);
        }
        return false;
        break;
      case gamer:
        if (record->event.pressed) {
            layer_clear();
            layer_on(_gamer);
        }
        return false;
        break;

  }
  return true;
}

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}


void rgb_matrix_indicators_kb(void)
{
	if (!g_suspend_state && rgb_matrix_config.enable) {
        switch (get_highest_layer(layer_state)) {
            //case _qwerty:
            //    rgb_matrix_set_color(26, 0xFF, 0x00, 0x00);
            //    break;
            case _colemak:
                rgb_matrix_set_color(55, 0xFF, 0xFF, 0xFF);
                break;
            case _spcfn:
                rgb_matrix_set_color(22, 0xFF, 0x00, 0x00);
                rgb_matrix_set_color(35, 0xFF, 0x00, 0x00);
                rgb_matrix_set_color(36, 0xFF, 0x00, 0x00);
                rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);
                break;
            case _gamer:
                rgb_matrix_set_color(16, 0xFF, 0x00, 0xFF);
                rgb_matrix_set_color(29, 0xFF, 0x00, 0xFF);
                rgb_matrix_set_color(30, 0xFF, 0x00, 0xFF);
                rgb_matrix_set_color(31, 0xFF, 0x00, 0xFF);
                break;
        }
    }
}
