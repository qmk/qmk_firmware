/* Copyright 2021 Hanachi
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

#define DUMMY KC_SPC

#define LAYOUT_test( \
    L01, L02, L03, L04, L05, L06,              R01, R02, R03, R04, R05, R06, R28, R07, R35, \
    L07, L08, L09, L10, L11, L12,              R08, R09, R10, R11, R12, R13, R34, R14, \
    L13, L14, L15, L16, L17, L18,              R15, R16, R17, R18, R19, R20, R21,  \
    L19, L20, L21, L22, L23, L24, L25,    R22, R23, R24, R25, R26, R27,        R29, \
                   L26, L27, L28, L29,    R30, R31, R32, R33                      \
    ) \
    { \
        { L01, L02, L03, L04, L05, L06, DUMMY, DUMMY  }, \
        { L07, L08, L09, L10, L11, L12, DUMMY, DUMMY  }, \
        { L13, L14, L15, L16, L17, L18, DUMMY, DUMMY  }, \
        { L19, L20, L21, L22, L23, L24, L25, DUMMY  }, \
        { DUMMY, DUMMY, DUMMY, L26, L27, L28, L29, DUMMY  }, \
        { DUMMY, R01, R02, R03, R04, R05, R06 ,R07  }, \
        { DUMMY, R08, R09, R10, R11, R12, R13, R14  }, \
        { DUMMY, R15, R16 ,R17, R18, R19, R20, R21  }, \
        { R22, R23, R24, R25, R26 ,R27, R28, R29  }, \
        { R30, R31, R32, R33, DUMMY, DUMMY, R34, R35 }  \
    }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_test(
	KC_ESC	,	KC_1	,	KC_2	,	KC_3	,	KC_4	,	KC_5	,					KC_6	,	KC_7	,	KC_8	,	KC_9	,	KC_0	,	KC_MINS	,	KC_EQL	,	KC_GRV	,	KC_BSPC	,
	KC_TAB	,	KC_Q	,	KC_W	,	KC_E	,	KC_R	,	KC_T	,					KC_Y	,	KC_U	,	KC_I	,	KC_O	,	KC_P	,	KC_LBRC	,	KC_RBRC	,			KC_BSLS	,
	KC_LCTL	,	KC_A	,	KC_S	,	KC_D	,	KC_F	,	KC_G	,					KC_H	,	KC_J	,	KC_K	,	KC_L	,	KC_SCLN	,	KC_QUOT	,					KC_ENT	,
	KC_LSFT	,	KC_Z	,	KC_X	,	KC_C	,	KC_V	,	KC_B	,	KC_DEL	,	KC_LGUI	,	KC_N	,	KC_M	,	KC_COMM	,	KC_DOT	,	KC_SLSH	,							KC_RSFT	,
							KC_LEFT   ,	KC_RIGHT,	KC_SPC	,	KC_LCTL	,	KC_ENT	,	KC_BSPC	,	KC_DOWN,	KC_UP
 )
};

void keyboard_post_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}
