/* Copyright 2017 Mattia Dal Ben
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
    _SYMB,
    _NAV,
    _ADJUST
};

// Shortcut to make keymap more readable
#define KC_CTLD LCTL_T(KC_D)
#define KC_CTLK RCTL_T(KC_K)
#define KC_GUIA LGUI_T(KC_A)
#define KC_SFTF LSFT_T(KC_F)
#define KC_SFTJ RSFT_T(KC_J)
#define KC_ALTL RALT_T(KC_L)
#define KC_GUISCL RGUI_T(KC_SCLN)
#define KC_SFTAT LSFT_T(KC_2)

#define KC_NASPC LT(_NAV, KC_SPC)
#define KC_NAENT LT(_NAV, KC_ENT)

#define KC_ADBSPC LT(_ADJUST, KC_BSPC)
#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)
#define ADJ_L MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                         ┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
     KC_Q            ,KC_W            ,KC_E            ,KC_R            ,KC_T                                      ,KC_Y            ,KC_U            ,KC_I            ,KC_O            ,KC_P            ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┐                         ┌────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_GUIA         ,KC_S            ,KC_CTLD         ,KC_SFTF         ,KC_G                                      ,KC_H            ,KC_SFTJ         ,KC_CTLK         ,KC_ALTL         ,KC_GUISCL       ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_Z            ,KC_X            ,KC_C            ,KC_V            ,KC_B                                      ,KC_N            ,KC_M            ,KC_COMM         ,KC_DOT          ,KC_SLSH         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┴────────────────┼────────────────┤────────────────┤
                                      KC_TAB           ,KC_ADBSPC       ,KC_NAENT                                  ,ADJ_L           ,KC_NASPC        ,KC_CAPS
  //                                  └────────────────┴────────────────┴────────────────┘                         └────────────────┴────────────────┴────────────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                         ┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
     KC_TRNS         ,KC_TRNS         ,KC_UP           ,KC_TRNS         ,KC_TRNS                                   ,KC_NO           ,KC_P7           ,KC_P8           ,KC_P9           ,KC_P            ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┐                         ┌────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_TRNS         ,KC_LEFT         ,KC_DOWN         ,KC_RIGHT        ,KC_TRNS                                   ,KC_KP_MINUS     ,KC_P4           ,KC_P5           ,KC_P6           ,KC_QUOTE        ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS                                   ,KC_TRNS         ,KC_P1           ,KC_P2           ,KC_P3           ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┴────────────────┼────────────────┤────────────────┤
                                      KC_TRNS          ,KC_TRNS         ,KC_TRNS                                   ,KC_TRNS         ,KC_P0           ,KC_KP_DOT
  //                                  └────────────────┴────────────────┴────────────────┘                         └────────────────┴────────────────┴────────────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                         ┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
     KC_ESC          ,KC_7            ,KC_8            ,KC_9            ,KC_0                                      ,KC_HOME         ,KC_PGUP         ,KC_UP           ,KC_PGUP         ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┐                         ┌────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_CAPS         ,KC_4            ,KC_5            ,KC_6            ,KC_SFTAT                                  ,KC_END          ,KC_LEFT         ,KC_DOWN         ,KC_RIGHT        ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_DEL          ,KC_1            ,KC_2            ,KC_3            ,KC_TRNS                                   ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┴────────────────┼────────────────┤────────────────┤
                                       KC_TRNS         ,KC_TRNS         ,KC_TRNS                                   ,KC_TRNS         ,KC_TRNS         ,KC_TRNS
  //                                  └────────────────┴────────────────┴────────────────┘                         └────────────────┴────────────────┴────────────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                         ┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐
     KC_F1           ,KC_F2           ,KC_F3           ,KC_F4           ,KC_F5                                      ,KC_F6          ,KC_F7           ,KC_F8           ,KC_F9           ,KC_F10          ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┐                         ┌────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_LGUI         ,KC_LALT         ,KC_LCTL         ,KC_LSFT         ,KC_TRNS                                   ,KC_F11          ,KC_F12          ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤
     KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS                                   ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,
  //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                         ├────────────────┼────────────────┴────────────────┼────────────────┤────────────────┤
                                       KC_TRNS         ,KC_TRNS         ,KC_TRNS                                   ,KC_TRNS         ,KC_TRNS         ,KC_TRNS
  //                                  └────────────────┴────────────────┴────────────────┘                         └────────────────┴────────────────┴────────────────┘
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SYMB:
            writePinLow(D1);
            break;
        case _NAV:
            writePinLow(F4);
            break;
        case _ADJUST:
            writePinLow(F5);
            break;
        default:
            writePinHigh(F5);
            writePinHigh(D1);
            writePinHigh(F4);
            writePinHigh(D0);
    }
  return state;
}


