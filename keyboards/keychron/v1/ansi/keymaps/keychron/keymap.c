/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

// clang-format off

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
    KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_INS,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_INS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

// clang-format on

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (!process_record_keychron(keycode, record)) {
//         return false;
//     }
//     return true;
// }

#define BUFFER_SIZE 4

static const int buffer_count = BUFFER_SIZE;

static uint16_t buffer[BUFFER_SIZE]={0};
static uint16_t count = 0;

uint16_t mapping_table[][3] = {
    {KC_C,    KC_X,    KC_H},
    {KC_E,    KC_R,    KC_I},
    {KC_C,    KC_V,    KC_J},
    {KC_F,    KC_S,    KC_K},
    {KC_D,    KC_S,    KC_L},
    {KC_E,    KC_W,    KC_M},
    {KC_D,    KC_V,    KC_N},
    {KC_V,    KC_X,    KC_O},
    {KC_R,    KC_W,    KC_P},
    {KC_F,    KC_E,    KC_U},
    {KC_F,    KC_D,    KC_Y},

    {KC_J,    KC_K,    KC_A},
    {KC_K,    KC_L,    KC_B},
    {KC_L,    KC_M,    KC_C},
    {KC_U,    KC_O,    KC_D},
    {KC_J,    KC_I,    KC_E},
    {KC_I,    KC_O,    KC_F},
    {KC_M,    KC_COMM, KC_G},
    {KC_J,    KC_L,    KC_Q},
    {KC_U,    KC_I,    KC_R},
    {KC_K,    KC_M,    KC_S},
    {KC_M,    KC_DOT,  KC_T},
    {KC_COMM, KC_DOT,  KC_V},
    {KC_K,    KC_DOT,  KC_W},
    {KC_L,    KC_I,    KC_X},
    {KC_J,    KC_O,    KC_Z},
};

uint16_t left_keycode[] = {KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_S, KC_D, KC_F, KC_G, KC_Z, KC_X, KC_C, KC_V, KC_B};

uint16_t right_keycode[] = {KC_Y, KC_U, KC_I, KC_O, KC_P, KC_H, KC_J, KC_K, KC_L, KC_N, KC_M, KC_COMM, KC_DOT};

void transfer_code(uint16_t *buffer) {
    uint16_t left_temp[BUFFER_SIZE] = {0};
    uint16_t right_temp[BUFFER_SIZE] = {0};
    uint16_t other_temp[BUFFER_SIZE] = {0};

    int left_idx = 0, right_idx = 0, other_idx = 0;
    for (int i = 0; i < buffer_count; i++) {
        uint16_t keycode = buffer[i];
        int found = 0;
        // 检查该元素是否在左侧数组中出现
        for (size_t j = 0; j < sizeof(left_keycode) / sizeof(left_keycode[0]); j++) {
            if (keycode == left_keycode[j]) {
                left_temp[left_idx++] = keycode;
                found = 1;
                break;
            }
        }
        // 检查该元素是否在右侧数组中出现
        if (!found) {
            for (size_t j = 0; j < sizeof(right_keycode) / sizeof(right_keycode[0]); j++) {
                if (keycode == right_keycode[j]) {
                    right_temp[right_idx++] = keycode;
                    found = 1;
                    break;
                }
            }
        }
        // 如果该元素既不在左侧数组中也不在右侧数组中
        if (!found) {
            other_temp[other_idx++] = keycode;
        }
    }

    // 01 02 03 12 13 23
    int result_idx = 0;

    for (int j = 0; j < sizeof(other_temp) / sizeof(other_temp[0]); ++j) {
        if (other_temp[j] != 0) {
            buffer[result_idx++] = other_temp[j];
        }
    }

    for (int i = 0; i < sizeof(mapping_table) / sizeof(mapping_table[0]); i++) {
        if ((mapping_table[i][0] == left_temp[0] && mapping_table[i][1] == left_temp[1]) ||
            (mapping_table[i][1] == left_temp[0] && mapping_table[i][0] == left_temp[1])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[0] = 0;
            left_temp[1] = 0;
        } else if ((mapping_table[i][0] == left_temp[0] && mapping_table[i][1] == left_temp[2]) ||
                   (mapping_table[i][1] == left_temp[0] && mapping_table[i][0] == left_temp[2])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[0] = 0;
            left_temp[2] = 0;
        } else if ((mapping_table[i][0] == left_temp[0] && mapping_table[i][1] == left_temp[3]) ||
                   (mapping_table[i][1] == left_temp[0] && mapping_table[i][0] == left_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[0] = 0;
            left_temp[3] = 0;
        } else if ((mapping_table[i][0] == left_temp[1] && mapping_table[i][1] == left_temp[2]) ||
                   (mapping_table[i][1] == left_temp[1] && mapping_table[i][0] == left_temp[2])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[1] = 0;
            left_temp[2] = 0;
        } else if ((mapping_table[i][0] == left_temp[1] && mapping_table[i][1] == left_temp[3]) ||
                   (mapping_table[i][1] == left_temp[1] && mapping_table[i][0] == left_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[1] = 0;
            left_temp[3] = 0;
        } else if ((mapping_table[i][0] == left_temp[2] && mapping_table[i][1] == left_temp[3]) ||
                   (mapping_table[i][1] == left_temp[2] && mapping_table[i][0] == left_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            left_temp[2] = 0;
            left_temp[3] = 0;
        }
    }

    for (int j = 0; j < sizeof(left_temp) / sizeof(left_temp[0]); ++j) {
        if (left_temp[j] != 0) {
            buffer[result_idx++] = left_temp[j];
        }
    }

    for (int i = 0; i < sizeof(mapping_table) / sizeof(mapping_table[0]); i++) {
        if ((mapping_table[i][0] == right_temp[0] && mapping_table[i][1] == right_temp[1]) ||
            (mapping_table[i][1] == right_temp[0] && mapping_table[i][0] == right_temp[1])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[0] = 0;
            right_temp[1] = 0;
        } else if ((mapping_table[i][0] == right_temp[0] && mapping_table[i][1] == right_temp[2]) ||
                   (mapping_table[i][1] == right_temp[0] && mapping_table[i][0] == right_temp[2])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[0] = 0;
            right_temp[2] = 0;
        } else if ((mapping_table[i][0] == right_temp[0] && mapping_table[i][1] == right_temp[3]) ||
                   (mapping_table[i][1] == right_temp[0] && mapping_table[i][0] == right_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[0] = 0;
            right_temp[3] = 0;
        } else if ((mapping_table[i][0] == right_temp[1] && mapping_table[i][1] == right_temp[2]) ||
                   (mapping_table[i][1] == right_temp[1] && mapping_table[i][0] == right_temp[2])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[1] = 0;
            right_temp[2] = 0;
        } else if ((mapping_table[i][0] == right_temp[1] && mapping_table[i][1] == right_temp[3]) ||
                   (mapping_table[i][1] == right_temp[1] && mapping_table[i][0] == right_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[1] = 0;
            right_temp[3] = 0;
        } else if ((mapping_table[i][0] == right_temp[2] && mapping_table[i][1] == right_temp[3]) ||
                   (mapping_table[i][1] == right_temp[2] && mapping_table[i][0] == right_temp[3])) {
            buffer[result_idx++] = mapping_table[i][2];
            right_temp[2] = 0;
            right_temp[3] = 0;
        }
    }
    for (int j = 0; j < sizeof(right_temp) / sizeof(right_temp[0]); ++j) {
        if (right_temp[j] != 0) {
            buffer[result_idx++] = right_temp[j];
        }
    }

    for (int i = result_idx; i < buffer_count; ++i) {
        buffer[i] = 0;
    }
}

bool is_keycode(uint16_t keycode) {
    for (int i = 0; i < sizeof(left_keycode)/sizeof(left_keycode[0]); ++i) {
        if (keycode == left_keycode[i])
            return true;
    }
    for (int i = 0; i < sizeof(right_keycode)/sizeof(right_keycode[0]); ++i) {
        if (keycode == right_keycode[i])
            return true;
    }
    return false;
}

bool skip_combination(uint16_t keycode, keyrecord_t *record) {
    static bool l_ctrl_pressed = false;
    static bool l_win_cmd_pressed = false;
    static bool l_sft_pressed = false;

    static bool c_pressed    = false;
    static bool v_pressed    = false;
    static bool x_pressed    = false;
    static bool a_pressed    = false;
    static bool z_pressed    = false;
    static bool y_pressed    = false;
    static bool f_pressed    = false;
    static bool p_pressed    = false;
    static bool s_pressed    = false;
    static bool n_pressed    = false;
    static bool t_pressed    = false;
    static bool d_pressed    = false;
    static bool e_pressed    = false;
    static bool l_pressed    = false;
    static bool r_pressed    = false;
    static bool i_pressed    = false;

    switch (keycode) {
        case KC_LCTL:
            l_ctrl_pressed = record->event.pressed;
            break;
        case KC_LWIN:
            l_win_cmd_pressed = record->event.pressed;
            break;
        case KC_LSFT:
            l_sft_pressed = record->event.pressed;
            break;
        case KC_C:
            c_pressed = record->event.pressed;
            break;
        case KC_V:
            v_pressed = record->event.pressed;
            break;
        case KC_X:
            x_pressed = record->event.pressed;
        break;
        case KC_A:
            a_pressed = record->event.pressed;
            break;
        case KC_Z:
            z_pressed = record->event.pressed;
            break;
        case KC_Y:
            y_pressed = record->event.pressed;
            break;
        case KC_F:
            f_pressed = record->event.pressed;
            break;
        case KC_P:
            p_pressed = record->event.pressed;
            break;
        case KC_S:
            s_pressed = record->event.pressed;
            break;
        case KC_N:
            n_pressed = record->event.pressed;
            break;
        case KC_T:
            t_pressed = record->event.pressed;
            break;
        case KC_D:
            d_pressed = record->event.pressed;
            break;
        case KC_E:
            e_pressed = record->event.pressed;
            break;
        case KC_L:
            l_pressed = record->event.pressed;
            break;
        case KC_R:
            r_pressed = record->event.pressed;
            break;
        case KC_I:
            i_pressed = record->event.pressed;
            break;
        default:
            break ;
    }
    if ((l_ctrl_pressed && c_pressed)
        || (l_ctrl_pressed && v_pressed)
        || (l_ctrl_pressed && x_pressed)
        || (l_ctrl_pressed && a_pressed)
        || (l_ctrl_pressed && z_pressed)
        || (l_ctrl_pressed && y_pressed)
        || (l_ctrl_pressed && f_pressed)
        || (l_ctrl_pressed && p_pressed)
        || (l_ctrl_pressed && s_pressed)
        || (l_ctrl_pressed && n_pressed)
        || (l_ctrl_pressed && t_pressed)
        || (l_ctrl_pressed && l_sft_pressed && v_pressed)) {
        return true;
    }
    if ((l_win_cmd_pressed && d_pressed)
        || (l_win_cmd_pressed && e_pressed)
        || (l_win_cmd_pressed && l_pressed)
        || (l_win_cmd_pressed && r_pressed)
        || (l_win_cmd_pressed && i_pressed)
        || (l_win_cmd_pressed && t_pressed)) {
        return true;
    }
    if ((l_win_cmd_pressed && c_pressed)
        || (l_win_cmd_pressed && v_pressed)
        || (l_win_cmd_pressed && x_pressed)
        || (l_win_cmd_pressed && a_pressed)
        || (l_win_cmd_pressed && z_pressed)
        || (l_win_cmd_pressed && y_pressed)
        || (l_win_cmd_pressed && f_pressed)
        || (l_win_cmd_pressed && p_pressed)
        || (l_win_cmd_pressed && s_pressed)
        || (l_win_cmd_pressed && n_pressed)
        || (l_win_cmd_pressed && t_pressed)
        || (l_win_cmd_pressed && l_sft_pressed && v_pressed)
        || (l_win_cmd_pressed && l_sft_pressed && z_pressed)) {
        return true;
    }
    return false;
}

static bool is_open = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_GRV && record->event.pressed) {
        if (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))) {
            is_open = !is_open;
            return false;
        }
    }

    if (is_open) {
        if (skip_combination(keycode,record)) return true;

        if (is_keycode(keycode)) {
            if (record->event.pressed) {
                if (count < buffer_count) {
                    buffer[count++] = keycode;
                }
                return false;
            } else {
                // 任何一个键抬起时，依次打出缓存中的所有键并释放
                transfer_code(buffer);
                for (int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++) {
                    if (buffer[i] != 0) {
                        register_code(buffer[i]);
                    }
                }
                for (int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++) {
                    if (buffer[i] != 0) {
                        unregister_code(buffer[i]);

                        buffer[i] = 0;
                    }
                }
                count = 0;
                return true;
            }
        }
        return true;
    }
    return true;
}
