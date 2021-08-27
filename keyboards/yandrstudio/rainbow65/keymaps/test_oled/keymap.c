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
#include "graph_lib/my_pic_lib.h"
#include "graph_lib/wpm_graph.h"
#include "graph_lib/kb_press_graph.h"
#include "dev_oled/oled_driver.h"

enum layer_names { _BASE, _FN, _SYS, _USER };


// Tap Dance declarations
enum {
    TD_FN_LAYER_TOG,
};

void dance_layer_to_layer_count_pre(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count <= 4) {
        layer_on(state->count);
        // reset_tap_dance(state);
    }
    uprintf("press Fn %u times\n", state->count);
}

void dance_layer_to_layer_count_finsh(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count <= 4) {
        layer_off(state->count);
        // reset_tap_dance(state);
    }
    uprintf("press Fn %u times\n", state->count);
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_LAYER_TOG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_layer_to_layer_count_pre,dance_layer_to_layer_count_finsh)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, RESET, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_VOLD, KC_VOLU, KC_SPC, KC_RALT, TD(TD_FN_LAYER_TOG), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, TO(_BASE),
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_MODE_REVERSE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_SYS] = LAYOUT(
        TO(_BASE), KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, TO(_BASE),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_MODE_REVERSE, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_USER] = LAYOUT(
        TO(_BASE), KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, TO(_BASE),
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
uint16_t oled_start_timer = 0;
uint16_t key_press_count = 0;

#define col_module_
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //   oled_scroll_set_area(0,2);
    // oled_scroll_set_speed(4);
    // oled_scroll_right();
    oled_start_timer = timer_read();
    return OLED_ROTATION_90;
}



void oled_write_ln_clo(const char *data, bool invert, uint8_t col, uint8_t line) {
    uint8_t l = strlen(data);
    const char *end = data + l;
    uint8_t i = 0;
    while (data < end) {
        oled_set_cursor(col, line+i);
        oled_write_char(*data, invert);
        data++;
        i++;
    }
    uint8_t rm = 16-(line+l);
    uint8_t j = 0;
    for(; j < rm; ++j) {
        oled_set_cursor(col, line+j+l);
        oled_write_char(' ', invert);
    }
}

void oled_write_clo(const char *data, bool invert, uint8_t col, uint8_t line) {
    uint8_t l = strlen(data);
    const char *end = data + l;
    uint8_t i = 0;
    while (data < end) {
        oled_set_cursor(col, line+i);
        oled_write_char(*data, invert);
        data++;
        i++;
    }
}


static bool has_clear = false;
void oled_task_user(void) {
    if (!has_clear) {
        oled_clear();
        has_clear = true;
    }
    // if (timer_elapsed(oled_start_timer) < 1000) {
        // render_logo_yandr();
    // }
    // Layer
    const char *st_my = my_font_lib_layer;
    oled_set_cursor(0,0);
    oled_write_raw_P(st_my, 24);
    oled_set_cursor(0,1);
    oled_write_raw_P(st_my+8*8, 24);
    switch (biton32(layer_state)) {
        case 0:
            oled_set_cursor(4,0);
            oled_write_raw_P(st_my+3*8, 8);
            oled_set_cursor(4,1);
            oled_write_raw_P(st_my+11*8, 8);
            oled_set_cursor(0,2);
            break;
        case 1:
            oled_set_cursor(4,0);
            oled_write_raw_P(st_my+4*8, 8);
            oled_set_cursor(4,1);
            oled_write_raw_P(st_my+12*8, 8);
            oled_set_cursor(0,2);
            break;
        case 2:
            oled_set_cursor(4,0);
            oled_write_raw_P(st_my+5*8, 8);
            oled_set_cursor(4,1);
            oled_write_raw_P(st_my+13*8, 8);
            oled_set_cursor(0,2);
            break;
        case 3:
            oled_set_cursor(4,0);
            oled_write_raw_P(st_my+6*8, 8);
            oled_set_cursor(4,1);
            oled_write_raw_P(st_my+14*8, 8);
            oled_set_cursor(0,2);
            break;
        default:
            oled_set_cursor(4,0);
            oled_write_raw_P(st_my+7*8, 8);
            oled_set_cursor(4,1);
            oled_write_raw_P(st_my+15*8, 8);
            oled_set_cursor(0,2);
    }
    oled_set_cursor(0,2);
    if (host_keyboard_led_state().caps_lock) {
        oled_write_raw_P(my_font_lib_caps_on, 24);
        oled_set_cursor(0,3);
        oled_write_raw_P(my_font_lib_caps_on+3*8, 24);
    } else {
        oled_write_raw_P(my_font_lib_caps_off, 24);
        oled_set_cursor(0,3);
        oled_write_raw_P(my_font_lib_caps_off+3*8, 24);
    }
    oled_set_cursor(4,2);
    if ((get_mods() & MOD_MASK_SHIFT)) {
        oled_write_raw_P(my_font_lib_shift_on, 8);
        oled_set_cursor(4,3);
        oled_write_raw_P(my_font_lib_shift_on+1*8, 8);
    } else {
        oled_write_raw_P(my_font_lib_shift_off, 8);
        oled_set_cursor(4,3);
        oled_write_raw_P(my_font_lib_shift_off+1*8, 8);
    }
    oled_set_precise_cursor(4*32+1);
    if ((get_mods() & MOD_MASK_CTRL)) {
        oled_write_raw_P(my_font_lib_ctrl_on, 10);
        oled_set_precise_cursor(5*32+1);
        oled_write_raw_P(my_font_lib_ctrl_on+1*10, 10);
    } else {
        oled_write_raw_P(my_font_lib_ctrl_off, 10);
        oled_set_precise_cursor(5*32+1);
        oled_write_raw_P(my_font_lib_ctrl_off+1*10, 10);
    }
    oled_set_precise_cursor(4*32+11);
    if ((get_mods() & MOD_MASK_GUI)) {
        oled_write_raw_P(my_font_lib_gui_on, 10);
        oled_set_precise_cursor(5*32+11);
        oled_write_raw_P(my_font_lib_gui_on+1*10, 10);
    } else {
        oled_write_raw_P(my_font_lib_gui_off, 10);
        oled_set_precise_cursor(5*32+11);
        oled_write_raw_P(my_font_lib_gui_off+1*10, 10);
    }
    oled_set_precise_cursor(4*32+21);
    if ((get_mods() & MOD_MASK_ALT)) {
        oled_write_raw_P(my_font_lib_alt_on, 10);
        oled_set_precise_cursor(5*32+21);
        oled_write_raw_P(my_font_lib_alt_on+1*10, 10);
    } else {
        oled_write_raw_P(my_font_lib_alt_off, 10);
        oled_set_precise_cursor(5*32+21);
        oled_write_raw_P(my_font_lib_alt_off+1*10, 10);
    }
    // oled_write_ln_P((get_mods() & MOD_MASK_ALT) ? "\x9c" : "\x9b", false);
    oled_set_cursor(0,6);
    if (rgb_matrix_is_enabled()) {
        oled_write_raw_P(my_font_lib_rgb_on, 20);
        oled_set_precise_cursor(6*32+20);
        snprintf(rgbStatus, sizeof(rgbStatus), "%2d", rgb_matrix_get_mode());
        oled_write(rgbStatus, false);
        oled_set_cursor(0,7);
        oled_write_raw_P(my_font_lib_rgb_on+1*24, 20);
        oled_set_precise_cursor(7*32+20);
        snprintf(rgbStatus, sizeof(rgbStatus), "%2d", RGB_MATRIX_EFFECT_MAX);
        oled_write(rgbStatus, false);
    } else {
        oled_write_raw_P(my_font_lib_rgb_off, 20);
        oled_set_precise_cursor(6*32+20);
        oled_write("xx", false);
        oled_set_cursor(0,7);
        oled_write_raw_P(my_font_lib_rgb_off+1*24, 20);
        oled_set_precise_cursor(7*32+20);
        oled_write("xx", false);
    }

    // show which area is pressed
    if (key_press_count==0) {
        render_r65_kb(255, 255, 0, false, key_press_count);
    }

    oled_set_cursor(0,10);
    uint16_t cur_wpm = get_current_wpm();
    snprintf(wpm_str, sizeof(wpm_str), " %03d ", cur_wpm);
    oled_write_ln_P(wpm_str, false);
    oled_set_cursor(0,11);

    // show the wpm wave
    render_wpm_graph(cur_wpm);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch(keycode) {
    //     case MACRO_1:
    //         if (record->event.pressed) {
    //             SEND_STRING("This is macro #1.");
    //         }
    //         return false;
    // }
#ifdef OLED_DRIVER_ENABLE
    uint8_t map_col = record->event.key.col;
    uint8_t map_row = record->event.key.row;
    if (record->event.pressed) {
        key_press_count++;
        print("key_press\n");
        uprintf("col %d ", map_col);
        uprintf("row %d\n", map_row);
        render_r65_kb(map_col, map_row, keycode, true, key_press_count);
    } else {
        if (key_press_count>0) {
            key_press_count--;
        }
        render_r65_kb(map_col, map_row, keycode, false, key_press_count);
    }
#endif
    return true;
};


#endif

#define RAW_HID_CUM_


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
    debug_matrix=false;
    // debug_keyboard=true;
    //debug_mouse=true;
}
#endif
