/* Copyright 2019 dnsnrk
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

#define RC_ENT RCTL_T(KC_ENT)
#define LC_CPS LCTL_T(KC_CAPS)

enum {
      _LAYER0 = 0,
      _LAYER1,
      _LAYER2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT_65_ansi_blocker( /* Base Layer */
                                       KC_ESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_GRV,
                                       KC_TAB,  KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,
                                       LC_CPS,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           RC_ENT,    KC_PGDN,
                                       KC_LSFT, KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     TT(2),
                                       KC_LCTL, KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT,           TT(1),    KC_LEFT,           KC_DOWN,   KC_RIGHT),
    [_LAYER1] = LAYOUT_65_ansi_blocker( /* FN, RGB Controls */
                                       KC_GRV,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_POWER,
                                       _______,  RGB_TOG,  RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME,
                                       _______,  RGB_RMOD, RGB_SPD, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_END,
                                       _______,  _______,  _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, _______,          _______, RGB_VAI, _______,
                                       _______,  _______,  _______,                   _______,                   _______,          _______,          RGB_HUD, RGB_VAD, RGB_HUI),
    [_LAYER2] = LAYOUT_65_ansi_blocker( /* Media, Programming */
                                       _______,  KC_BRMD, KC_BRMU, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE, KC_VOLD, KC_VOLU, KC_EJCT, _______,
                                       _______,  _______, _______, EEP_RST, QK_BOOT, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
                                       _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,          _______, _______,
                                       _______,  _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, _______,  _______,          _______, _______, _______,
                                       _______,  _______, _______,                   _______,                   _______,           _______,          _______, _______, _______)
};

void set_hsv_at(HSV hsv, uint8_t index);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_config.enable) {
        HSV hsv = rgb_matrix_config.hsv;
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            HSV hsv_inv_hue = {hsv.h + 128, hsv.s, hsv.v};
            set_hsv_at(hsv_inv_hue, 30);
        }
        // indicate which higher layer is currently active on which key
        HSV hsv1 = {hsv.h - 64, hsv.s, hsv.v};
        HSV hsv2 = {hsv.h + 64, hsv.s, hsv.v};
        // except when we are in any animated LED mode
        if (rgb_matrix_config.mode < RGB_MATRIX_BREATHING || rgb_matrix_config.mode > RGB_MATRIX_JELLYBEAN_RAINDROPS) {
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    keypos_t pos = {col, row};
                    uint8_t key_layer = layer_switch_get_layer(pos);
                    uint8_t key_led = g_led_config.matrix_co[row][col];
                    if (key_led != NO_LED) {
                        switch(key_layer) {
                        case _LAYER2:
                            set_hsv_at(hsv2, key_led);
                            break;
                        case _LAYER1:
                            set_hsv_at(hsv1, key_led);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
        // sticky layer indicators regardless of RGB mode. Hardcoded for lack of better idea.
        set_hsv_at(hsv1, 63);
        set_hsv_at(hsv2, 57);
    }
}

void set_hsv_at(HSV hsv, uint8_t index) {
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}
