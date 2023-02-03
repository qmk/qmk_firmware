/* Copyright 2021 Robert Verst <robert@verst.eu> @rverst
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

#include "rverst.h"

//#define CLOSED_CASE // no underglow RGB visible

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ansi(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , MO(4)  , KC_DEL ,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_PGUP,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC ,                            OSL(1) , KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[1] = LAYOUT_ansi(
        RV_SNAP, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , KC_F23 , KC_F24 , KC_TRNS, KC_MUTE,
        RV_DEG , RV_SUP1, RV_SUP2, RV_SUP3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_UNEQ, RV_PM  , KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, RV_EUR , RV_RT  , RV_TM  , KC_TRNS, RV_UUML, KC_TRNS, RV_OUML, KC_TRNS, RV_VDEC, RV_VINC, RV_SEQU, KC_VOLD,
        KC_CAPS, RV_AUML, RV_SZ  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_LOCK, KC_TRNS, RV_SINC, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, RV_CC  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_SDEC, KC_TRNS,          KC_MSTP,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_RGUI,          KC_MPRV, KC_MPLY, KC_MNXT
    ),
	[2] = LAYOUT_ansi(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_TRNS, MO(4)  , KC_MUTE,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_VOLU,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLD,
        KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC ,                            OSL(3) , KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[3] = LAYOUT_ansi(
        RV_SNAP, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , KC_F23 , KC_F24 , KC_TRNS, KC_MUTE,
        RV_DEG , RV_SUP1, RV_SUP2, RV_SUP3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_UNEQ, RV_PM  , KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_LOCK, RV_UUML, KC_TRNS, KC_TRNS, RV_VDEC, RV_VINC, RV_SEQU, KC_VOLD,
        KC_CAPS, RV_AUML, RV_RT  , RV_SZ  , RV_TM  , KC_TRNS, KC_TRNS, KC_TRNS, RV_EUR , KC_TRNS, RV_OUML, RV_SINC, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, RV_CC  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RV_SDEC, KC_TRNS,          KC_MSTP,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_RGUI,          KC_MPRV, KC_MPLY, KC_MNXT
    ),
	[4] = LAYOUT_ansi(
        DB_TOGG, RV_SM0 , RV_SM1 , RV_SM2 , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(0)  , DF(2)  , KC_TRNS, MO(5)  ,
        RV_SAYM, RV_SM3 , RV_SM4 , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          RGB_TOG,
        KC_NO  , KC_NO  , GUI_ON ,                   KC_NO  ,                            KC_NO  , RCG_SWP,          RGB_RMOD,RGB_M_P, RGB_MOD
    ),
	[5] = LAYOUT_ansi(
        QK_BOOT, RV_SM0S, RV_SM1S, RV_SM2S, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
        KC_NO  , RV_SM3S, RV_SM4S, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  ,
        KC_NO  , KC_NO  , GUI_OFF,                   KC_NO  ,                            KC_NO  , RCG_NRM,          KC_NO  , KC_NO  , KC_NO
    )
};
// clang-format on

void keyboard_post_init_keymap(void) {
#ifdef CLOSED_CASE
    if (rgblight_is_enabled()) {
        rgblight_disable();
    }
#endif
}
