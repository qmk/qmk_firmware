/* Copyright 2021 JasonRen(biu)
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
#include "print.h"
#include "usb_main.h"
#include "quantum_keycodes.h"


enum custom_keycodes {
    KEY_OUT_USB = SAFE_RANGE, //SAFE_RANGE,
    KEY_OUT_BLE,
    KEY_OUT_AUTO,

    BL_SW_0,        // ble id
    BL_SW_1,
    BLE_DEL_ALL,    //删除所有绑定设备
    BLE_DEL_THIS,   //删除当前设备
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_0,
        RESET, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, RGB_TOG, RGB_MOD, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KEY_OUT_USB, KEY_OUT_BLE, KEY_OUT_AUTO,KC_PGDN,KC_PGUP, KC_SPACE, BL_SW_0, MO(1), BL_SW_1, KC_LEFT, KC_DOWN, KC_RGHT),

};
// RGB指示层
#ifdef RGBLIGHT_ENABLE
// 以下为RGB灯效分层设置：
// Light LEDs 0 to 4 in red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,3, HSV_WHITE  });

// Light LEDs 0 to 4 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,3, HSV_CYAN});

// Light LEDs 0 to 4 in green when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0,3, HSV_YELLOW});


const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer, my_layer1_layer,
    my_layer2_layer // Overrides other layers
);

layer_state_t layer_state_set_user(layer_state_t state)
{
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state)
{
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
#endif

//旋钮
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
#endif
