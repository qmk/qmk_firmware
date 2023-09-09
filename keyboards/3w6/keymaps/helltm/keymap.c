/* Copyright 2021 HellSingCoder
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

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif

enum layers
{
    _ALPHA_QWERTY = 0,
    _SYM,
    _NAV,
    _NUM,
};

enum custom_keycodes {
    KC_THUMB_SWAP,
};

/* Space Enter swap */
bool swap_space_enter = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
    * QWERTY
    *
    *                                          _____________________         _____________________
    *                                       __|__                   |       |                   __|__
    *                              _____   |     |                  v       v                  |     |   _____
    *                       .-----|  E  |-----._____                                         _____.-----|  I  |-----.
    *                 .-----|  W  |_____|  R  |  T  |  __           (       )           __  |  Y  |  U  |_____|  O  |-----.
    *             __  |  Q  |-----|  D  |-----|_____|  __|--> +                   - <--|__  |_____|-----|  K  |-----|  P  |  __
    *    ESC  <--|__  |-----|  S  |_____|  F  |  G  |               [       ]               |  H  |  J  |_____|  L  |-----|  __|--> '
    *             __  |  A  |-----|  C  |-----|_____|  __                               __  |_____|-----| , < |-----| ; : |  __
    *    TAB  <--|__  |-----|  X  |_____|  V  |  B  |  __|--> *     {       }     = <--|__  |  N  |  M  |_____| . > |-----|  __|--> "
    *                 |  Z  |-----'     '-----|_____|                                       |_____|-----'     '-----| / ? |
    *                 '-----'          .-----. _____   .-.._                           _..-.   _____ .-----.        '-----'
    *                    |             | WIN ||CTRL | /     /                         \     \ | BSp || Del |           |
    *                  SHIFT           '-----':_____|/ ENT /                           \ SPC \|_____:'-----'         SHIFT
    *                                     |         '--.._/                             \_..--'  |      |
    *                                    NUM                                                    NAV    SYM
    */
    [_ALPHA_QWERTY] = LAYOUT(
        KC_Q,         KC_W   , KC_E   , KC_R   , KC_T   ,                                    KC_Y   , KC_U   , KC_I   , KC_O   , KC_P           ,
        KC_A,         KC_S   , KC_D   , KC_F   , KC_G   ,                                    KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN        ,
        LSFT_T(KC_Z), KC_X   , KC_C   , KC_V   , KC_B   ,                                    KC_N   , KC_M   , KC_COMM, KC_DOT , RSFT_T(KC_SLSH),
                                LT(_NUM, KC_LGUI), KC_LCTL,  KC_ENT,       KC_SPC, LT(_NAV, KC_BSPC), LT(_SYM, KC_DEL)
    ),

    /*
    * Symbols
    *              _____                                                   _____
    *       .-----|  #  |-----._____                           _____.-----|  *  |-----.
    * .-----|  @  |_____|  $  |  %  |                         |  ^  |  &  |_____|  (  |-----.
    * |  !  |-----|     |-----|_____|                         |_____|-----| [ { |-----|  )  |
    * |-----|     |_____|     |     |                         |  {  |  }  |_____| ] } |-----|
    * | ` ~ |-----|     |-----|_____|                         |_____|-----|     |-----| ' " |
    * |-----|     |_____|     |     |                         | - _ | = + |_____|  |  |-----|
    * |  ~  |-----'     '-----|_____|                         |_____|-----'     '-----| \ | |
    * '-----'          .-----. _____   .-.._           _..-.   _____ .-----.          '-----'
    *  SHIFT           |     ||CTRL | /     /         \     \ | BSp ||     |           SHIFT
    *                  '-----':_____|/ ENT /           \ SPC \|_____:'-----'
    *                               '--.._/             \_..--'
    */
    [_SYM] = LAYOUT(
        KC_EXLM,         KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN        ,
        KC_GRV ,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_QUOT        ,
        LSFT_T(KC_TILD), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_MINS, KC_EQL , XXXXXXX, KC_PIPE, RSFT_T(KC_BSLS),
                                        XXXXXXX, _______, _______,                    _______, KC_BSPC, XXXXXXX
    ),

    /*
    * Navigation
    *              _____                                                   _____
    *       .-----|Mute |-----._____                           _____.-----| Up  |-----.
    * .-----|VDown|_____| VUp |     |                         |     |PDown|_____| PUp |-----.
    * | Esc |-----|Play |-----|_____|                         |_____|-----|Down |-----| BSp |
    * |-----|Prev |_____|Next |     |                         |Home |Left |_____|Right|-----|
    * | Tab |-----|Stop |-----|_____|                         |_____|-----|     |-----| ' " |
    * |-----|     |_____|     |     |                         |     |     |_____| End |-----|
    * | CPS |-----'     '-----|_____|                         |_____|-----'     '-----| Del |
    * '-----'          .-----. _____   .-.._           _..-.   _____ .-----.          '-----'
    *  SHIFT           |     ||CTRL | /     /         \     \ | BSp ||     |           SHIFT
    *                  '-----':_____|/ ENT /           \ SPC \|_____:'-----'
    *                               '--.._/             \_..--'
    */
    [_NAV] = LAYOUT(
        KC_ESC         , KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                                XXXXXXX, KC_PGDN, KC_UP  , KC_PGUP, KC_BSPC,
        KC_TAB         , KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT,
        LSFT_T(KC_CAPS), XXXXXXX, KC_MSTP, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, KC_END , RSFT_T(KC_DEL) ,
                                        XXXXXXX, _______, _______,                    _______, KC_BSPC, XXXXXXX
    ),

    /*
    * Numbers
    *              _____                                                   _____
    *       .-----|  3  |-----._____                           _____.-----|  8  |-----.
    * .-----|  2  |_____|  4  |  5  |                         |  6  |  7  |_____|  9  |-----.
    * |  1  |-----| F3  |-----|_____|                         |_____|-----| F8  |-----|  0  |
    * |-----| F2  |_____| F4  | F5  |                         | F6  | F7  |_____| F9  |-----|
    * | F1  |-----| Scr |-----|_____|                         |_____|-----|     |-----| F10 |
    * |-----| TMg |_____|     |Swap |                         |     |     |_____| F11 |-----|
    * |Shift|-----'     '-----|_____|                         |_____|-----'     '-----| F12 |
    * '-----'          .-----. _____   .-.._           _..-.   _____ .-----.          '-----'
    *                  |     ||CTRL | /     /         \     \ | BSp ||     |           SHIFT
    *                  '-----':_____|/ ENT /           \ SPC \|_____:'-----'
    *                               '--.._/             \_..--'
    */
    [_NUM] = LAYOUT(
        KC_1   , KC_2       , KC_3      , KC_4   , KC_5         ,                                KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,
        KC_F1  , KC_F2      , KC_F3     , KC_F4  , KC_F5        ,                                KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
        KC_LSFT, LCA(KC_DEL), SWIN(KC_S), XXXXXXX, KC_THUMB_SWAP,                                XXXXXXX, XXXXXXX, XXXXXXX, KC_F11 , RSFT_T(KC_F12) ,
                                             XXXXXXX, _______, _______,                    _______, KC_BSPC, XXXXXXX
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        /* Space Enter swap */
        case KC_THUMB_SWAP:
            if (record->event.pressed) {
                unregister_code(KC_SPC);
                unregister_code(KC_ENT);
                swap_space_enter = !swap_space_enter;
            }
            return false;
            break;

        case KC_ENT:
            if (swap_space_enter) {
                if (record->event.pressed) {
                    register_code(KC_SPC);
                } else {
                    unregister_code(KC_SPC);
                }
                return false;
            }
            break;
        case KC_SPC:
            if (swap_space_enter) {
                if (record->event.pressed) {
                    register_code(KC_ENT);
                } else {
                    unregister_code(KC_ENT);
                }
                return false;
            }
            break;
    }
    return true;
}
