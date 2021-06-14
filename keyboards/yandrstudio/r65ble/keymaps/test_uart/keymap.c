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
// #include <stdio.h>
#include "print.h"
#include "dynamic_keymap.h"
#include "uart.h"

enum layer_names { _BASE, _FN, _SYS, _USER };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_VOLD, KC_VOLU, KC_SPC, KC_RALT, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, TO(_BASE),
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_MODE_REVERSE, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_SYS] = LAYOUT(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_USER] = LAYOUT(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};



#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 3);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            tap_code16(keycode);
        }
    } else {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 4);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            tap_code16(keycode);
        }
    }
}
#endif

#ifdef OLED_DRIVER_ENABLE
char wpm_str[10];  // limit WPM string length.
char rgbStatus[26] = {0};

void oled_write_ln_col(const char *data, bool invert) {

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //   oled_scroll_set_area(0,2);
    // oled_scroll_set_speed(4);
    // oled_scroll_right();
    return OLED_ROTATION_0;
}
void oled_task_user(void) {
    switch (biton32(layer_state)) {
        case 0:
            oled_write_ln("Layer: Base", false);
            break;
        case 1:
            oled_write_ln("Layer: Function", false);
            break;
        case 2:
            oled_write_ln("Layer: System", false);
            break;
        case 3:
            oled_write_ln("Layer: User", false);
            break;
        default:
            oled_write_ln("Layer: Undefine", false);
    }
    oled_write_P((get_mods() & MOD_MASK_SHIFT) ? "SF>* " : "SF>x ", false);
    oled_write_P((get_mods() & MOD_MASK_CTRL) ? "CT>* " : "CT>x ", false);
    oled_write_P((get_mods() & MOD_MASK_ALT) ? "AL>* " : "AL>x ", false);
    oled_write_ln((get_mods() & MOD_MASK_GUI) ? "GU>*" : "GU>x", false);

    if (rgb_matrix_is_enabled()) {
        snprintf(rgbStatus, sizeof(rgbStatus), "RGB:<ON>  M:[%d]", rgb_matrix_get_mode());
        oled_write_ln(rgbStatus, false);
    } else {
        snprintf(rgbStatus, sizeof(rgbStatus), "RGB:<OFF> M:[x]");
        oled_write_ln(rgbStatus, false);
    }
    snprintf(wpm_str, sizeof(wpm_str), "APM:%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
}
#endif



void keyboard_post_init_user(void) {
    uart_init(115200);
  debug_enable=true;
//   debug_matrix=true;
  debug_keyboard=true;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uart_putchar(0xff);
        uart_putchar(keycode >> 8);
        uart_putchar(keycode & 0xff);
        uart_putchar(0xfe);
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    }
    return true;
    // switch (keycode) {
    //     case KC_N:
    //         if (record->event.pressed) {
    //             uart_putchar('#');
    //         } else {
    //             // Do something else when release
    //         }
    //         return false;  // Skip all further processing of this key
    //     default:
    //         return true;  // Process all other keycodes normally
    // }
}
