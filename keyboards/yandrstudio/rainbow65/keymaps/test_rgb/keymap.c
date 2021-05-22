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
#include "dynamic_keymap.h"
#include "raw_hid.h"
#include "print.h"
#include <string.h>
// #include "scale8.h"
enum layer_names { _BASE, _FN, _SYS, _USER };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, RESET, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
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
    uprintf("%ud raw g_rgb_time\n", g_rgb_timer);
    uprintf("%ud rgb speed\n", rgb_matrix_config.speed);

    // uprintf("%ud g_rgb_time scale8\n", scale16by8(g_rgb_timer, rgb_matrix_config.speed / 4));
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
        snprintf(rgbStatus, sizeof(rgbStatus), "RGB:o M:%d", rgb_matrix_get_mode());
        oled_write_ln(rgbStatus, false);
    } else {
        snprintf(rgbStatus, sizeof(rgbStatus), "RGB:x M:x", rgb_matrix_get_mode());
        oled_write_ln(rgbStatus, false);
    }
    snprintf(wpm_str, sizeof(wpm_str), "APM:%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
}
#endif

#define RAW_HID_CUM


#ifdef RAW_HID_CUM
extern uint8_t global_r_power_state[MATRIX_ROWS];
extern uint8_t global_c_power_state[MATRIX_COLS];
uint8_t pre_rgb_mode = 0xff;
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    // Your code goes here. data is the packet received from host.
    switch (data[0]) {
    case 60:
        switch (data[1]) {
        case 1:
            rgb_matrix_toggle_noeeprom();
            break;
        case 2:
            rgb_matrix_enable_noeeprom();
            break;
        case 3:
            rgb_matrix_disable_noeeprom();
            break;
        case 4:
            if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_COL) {
                pre_rgb_mode = rgb_matrix_get_mode();
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_COL);
            } else {
                rgb_matrix_mode(pre_rgb_mode);
            }
            break;
        case 5:
            if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_ROW) {
                pre_rgb_mode = rgb_matrix_get_mode();
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_ROW);
            } else {
                rgb_matrix_mode(pre_rgb_mode);
            }
        case 6:
            if (rgb_matrix_get_mode() == RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_ROW) {
                for (uint8_t i = 0; i < length; ++i) {
                    global_r_power_state[i] = data[2+i];
                }
            } else if (rgb_matrix_get_mode() == RGB_MATRIX_CUSTOM_AUDIO_VISUALIZATION_COL) {
                for (uint8_t i = 0; i < length; ++i) {
                    global_c_power_state[i] = data[2+i];
                }
            } else {
                dprint("BAD: not in the audio visual mod.");
            }
            break;
        case 7:
            rgb_matrix_mode(data[2]);
        default:
            break;
        }
        break;
    case 66:
        dprint("GOOD: 6666");
        break;
    default:
        break;
    }
    raw_hid_send(data, 32);
}
#endif



#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // eeconfig_init();
    // Customise these values to desired behaviour
    debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    //debug_mouse=true;
}
#endif
