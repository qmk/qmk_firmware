 /* Copyright 2020 Ralph Azucena <ralphie02@live.com>
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

#define BASE 0
#define NAV 1

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_CAP LCTL_T(KC_CAPS)
#define ALT_BSP LALT_T(KC_BSPC)
#define LT_SCLN LT(NAV, KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_6x6(
        KC_GRV , KC_1  ,KC_2   , KC_3  , KC_4  , KC_5  ,                                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_HOME,
        KC_TAB , KC_Q  ,KC_W   , KC_E  , KC_R  , KC_T  ,                                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
        CTL_CAP, KC_A  ,KC_S   , KC_D  , KC_F  , KC_G  ,                                         KC_H  , KC_J  , KC_K  , KC_L  ,LT_SCLN,KC_QUOT,
        KC_LSFT, KC_Z  ,KC_X   , KC_C  , KC_V  , KC_B  ,                                         KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
        CTL_ESC,KC_MINS,KC_EQL ,KC_LBRC,KC_RBRC,                                                        KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,KC_END ,
                                                        TT(NAV),KC_DEL ,        KC_PGUP,KC_RCTL,
                                                                KC_LGUI,        KC_PGDN,
                                                KC_BSPC,CTL_ESC,KC_LALT,        KC_RALT,KC_ENT ,KC_SPC
    ),
    [NAV] = LAYOUT_6x6(
         QK_BOOT , KC_NO ,KC_MPRV,KC_MPLY,KC_MNXT, KC_NO ,                                        KC_BRIU,  KC_7 , KC_8  , KC_9  , KC_NO , QK_BOOT ,
        _______,KC_VOLU,KC_WBAK,MS_UP,  KC_WFWD,MS_WHLU,                                        KC_BRID,  KC_4 , KC_5  , KC_6  , KC_NO , KC_F9 ,
        _______,KC_VOLD,MS_LEFT,MS_DOWN,MS_RGHT,MS_WHLD,                                        KC_PPLS,  KC_1 , KC_2  , KC_3  ,KC_PMNS, KC_F10,
         KC_NO , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_NO ,                                        KC_PAST,  KC_0 , KC_NO ,_______,KC_PSLS, KC_F11,
        _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 ,                                                        _______,_______,_______,_______, KC_F12,
                                                        _______,_______,        KC_HOME,_______,
                                                                _______,        KC_END ,
                                                MS_BTN1,MS_BTN2,_______,        ALT_BSP,_______,_______
    )
};
