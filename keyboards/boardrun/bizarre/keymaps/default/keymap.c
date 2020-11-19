/*
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

#define _FUNC   MO(_FNBIZARRE)

// Layer shorthand
enum layer_names {
    _BIZARRE,
    _FNBIZARRE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*Bizarre Base Layer (defaults for "any" layout)
    * +-------+   +-----------------------+ +-------------------------------+                   +-------------------------------+ +---------------------------------------+
    * ¦ HOME  ¦   ¦ ESC   ¦ `~    ¦ 1     ¦ ¦ 2     ¦ 3     ¦ 4     ¦ 5     ¦                   ¦ 6     ¦ 7     ¦ 8     ¦ 9     ¦ ¦ 0     ¦ -     ¦ =     ¦ BKSP  ¦ DEL   ¦
    * +-------¦   +-----------------------+ +-------+-------+-------+-------¦                   +-------+-------+-------+-------¦ +---------------------------------------+
    * ¦ END   ¦     ¦ TAB       ¦ Q     ¦   ¦ W     ¦ E     ¦ R     ¦ T     ¦                   ¦ Y     ¦ U     ¦ I     ¦ O     ¦   ¦ P     ¦ [     ¦ ]     ¦ \ ANSI    ¦
    * +-------+ +-----------------------+   +-------+-------+-------+-------¦                   +-------+-------+-------+-------¦   +-----------------------------------¦
    *           ¦ CAPS        ¦ A     ¦     ¦ S     ¦ D     ¦ F     ¦ G     ¦                   ¦ H     ¦ J     ¦ K     ¦ L     ¦     ¦ ;     ¦ '     ¦ # ISO ¦ ENTER   ¦
    *     +---------------------------+     +-------+-------+-------+-------+-------+   +-------+-------+-------+-------+-------¦     +-----------------------+---------+
    *     ¦ LSHIFT  ¦ \ ISO ¦ Z     ¦       ¦ X     ¦ C     ¦ V     ¦ B     ¦ LGUI  ¦   ¦ FN    ¦ N     ¦ M     ¦ ,     ¦ .     ¦       ¦ /     ¦ RSHIFT      ¦ UP    ¦
    *     +-----------------+-------+       +-----------------------+---------------¦   +---------------------------------------+       +---------------------+-------+-------+
    *           ¦ LCTRL     ¦                           ¦ LALT      ¦ SPACE         ¦   ¦ SPACE               ¦                           ¦ RCTRL     ¦ LEFT  ¦ DOWN  ¦ RIGHT ¦
    *           +-----------+                           +---------------------------+   +---------------------+                           +-----------------------------------+
    */
    
    [_BIZARRE] = LAYOUT_all(
       KC_HOME,    KC_ESC, KC_GRV, KC_1,     KC_2,   KC_3,   KC_4,   KC_5,                       KC_6,   KC_7,   KC_8,   KC_9,     KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_DEL,
       KC_END,       KC_TAB,     KC_Q,       KC_W,   KC_E,   KC_R,   KC_T,                       KC_Y,   KC_U,   KC_I,   KC_O,       KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,
                 KC_CAPS,      KC_A,         KC_S,   KC_D,   KC_F,   KC_G,                       KC_H,   KC_J,   KC_K,   KC_L,         KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,
           KC_LSFT,  KC_NUBS,KC_Z,           KC_X,   KC_C,   KC_V,   KC_B,   KC_LGUI,    _FUNC,  KC_N,   KC_M,   KC_COMM,KC_DOT,         KC_SLSH,KC_RSFT,      KC_UP,
                 KC_LCTL,                                KC_LALT,    KC_SPC,             KC_SPC,                                           KC_RCTL,    KC_LEFT,KC_DOWN,KC_RGHT
    ), 
    
    /*Bizarre Function Layer
    * +-------+   +-----------------------+ +-------------------------------+                   +-------------------------------+ +---------------------------------------+
    * ¦ RESET ¦   ¦       ¦       ¦ F1    ¦ ¦ F2    ¦ F3    ¦ F4    ¦ F5    ¦                   ¦ F6    ¦ F7    ¦ F8    ¦ F9    ¦ ¦ F10   ¦ F11   ¦ F12   ¦ DEL   ¦       ¦
    * +-------¦   +-----------------------+ +-------+-------+-------+-------¦                   +-------+-------+-------+-------¦ +---------------------------------------+
    * ¦       ¦     ¦           ¦       ¦   ¦       ¦       ¦       ¦       ¦                   ¦       ¦       ¦ INS   ¦       ¦   ¦ PRINT ¦       ¦       ¦           ¦
    * +-------+ +-----------------------+   +-------+-------+-------+-------¦                   +-------+-------+-------+-------¦   +-----------------------------------¦
    *           ¦             ¦       ¦     ¦ SCRLL ¦       ¦       ¦       ¦                   ¦       ¦       ¦       ¦       ¦     ¦       ¦       ¦       ¦         ¦
    *     +---------------------------+     +-------+-------+-------+-------+-------+   +-------+-------+-------+-------+-------¦     +-----------------------+---------+
    *     ¦         ¦       ¦       ¦       ¦       ¦       ¦       ¦ PAUSE ¦ RGUI  ¦   ¦       ¦       ¦ MENU  ¦       ¦       ¦       ¦       ¦             ¦ PGUP  ¦
    *     +-----------------+-------+       +-----------------------+---------------¦   +---------------------------------------+       +---------------------+-------+-------+
    *           ¦           ¦                           ¦           ¦               ¦   ¦ RALT                ¦                           ¦           ¦ HOME  ¦ PGDN  ¦ END   ¦
    *           +-----------+                           +---------------------------+   +---------------------+                           +-----------------------------------+
    */
    
    [_FNBIZARRE] = LAYOUT_all(
       RESET,     _______,_______,KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,                      KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10, KC_F11, KC_F12, KC_DEL, _______,
       _______,      _______,    _______,    _______,_______,RESET,  _______,                    _______,_______,KC_INS ,_______,    KC_PSCR,_______,_______,_______,
                 _______,      _______,      KC_SLCK,_______,_______,_______,                    _______,_______,_______,_______,      _______,_______,_______,_______,
           _______,  _______,_______,        _______,_______,_______,KC_PAUS,KC_RGUI,    _______,_______,KC_MENU,_______,_______,        _______,_______,      KC_PGUP,
                 _______,                                _______,    _______,            KC_RALT,                                          _______,    KC_HOME,KC_PGDN,KC_END
    )
};