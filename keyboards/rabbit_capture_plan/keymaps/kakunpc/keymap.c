/* Copyright 2020 kakunpc
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


#include "paw3204.h"
#include "pointing_device.h"

enum layers{
    _BASE,
    _FN
};

#define LT_F13 LT(_FN, KC_F13)
#define LT_F14 LT(_FN, KC_F14)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
        KC_ESC, KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,             KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,               KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_LCTRL, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,                KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,   KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,  KC_DEL,    KC_UP,   
        KC_LCTRL,   KC_LGUI, KC_LALT, LT_F13, KC_SPC,                LT_F14,  KC_SPC,                                              KC_LEFT,  KC_DOWN,  KC_RIGHT
    ),
    [_FN] = LAYOUT_all(
        RESET, _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,
        _______, _______, KC_UP, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,_______,       _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, _______, _______, _______,                           _______, _______,                                           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}



#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
                                            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
                                            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}
void oled_task_user(void) { render_logo(); }
#endif

void matrix_init_user(void) {
#ifdef POINTING_DEVICE_ENABLE
    init_paw3204();
#endif
}

report_mouse_t mouse_rep;

void matrix_scan_user(void) {
#ifdef POINTING_DEVICE_ENABLE
    static int  cnt;
    static bool paw_ready;
    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;

        read_paw3204(&stat, &x, &y);
        mouse_rep.buttons = 0;
        mouse_rep.h       = 0;
        mouse_rep.v       = 0;
        mouse_rep.x       = x;
        mouse_rep.y       = y;

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
#endif
}

