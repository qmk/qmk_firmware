 /* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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
#include "sethBarberee.h"

extern backlight_config_t backlight_config;

#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_VK VLK_TOG

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_wrapper(
     KC_ECAP, ________________NUMBER_LEFT________________,                 ________________NUMBER_RIGHT_______________,      KC_MINS,
     KC_TAB , _________________QWERTY_L1_________________,                 _________________QWERTY_R1_________________,      KC_DEL ,
     KC_LSFT, _________________QWERTY_L2_________________,                 _________________QWERTY_R2_________________,
     KC_LCTL, _________________QWERTY_L3_________________, KC_SPC,         KC_RASE, _________________QWERTY_R3_________________,KC_RSFT,
                                        KC_LGUI, KC_LOWR, KC_SPC,           KC_BSPC , KC_ENT, KC_LALT
  ),

  [_LOWER] = LAYOUT(
     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,               KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,
     KC_RST ,_______,_______, KC_UP ,_______,_______,               KC_GRV , KC_P7 , KC_P8 , KC_P9 ,_______,_______,
     KC_DEL ,_______,KC_LEFT,KC_DOWN,KC_RGHT,KC_LBRC,               KC_RBRC, KC_P4 , KC_P5 , KC_P6 ,KC_PLUS,KC_PIPE,
     KC_BL_S,_______,_______,_______,_______,KC_LCBR,KC_LPRN,       KC_RPRN,KC_RCBR, KC_P1 , KC_P2 , KC_P3 ,KC_MINS,_______,
                                        _______,_______,KC_LPRN,       KC_DEL ,_______, KC_P0
  ),

  [_RAISE] = LAYOUT(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,              KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
     _______,_______,_______,_______,_______,_______,              _______, _______,_______,_______,_______,_______,
     _______,KC_MPRV,KC_MNXT,KC_VOLU,KC_PGUP,KC_UNDS,              KC_EQL ,KC_HOME,_______,_______,_______,KC_BSLS,
     KC_MUTE,KC_MSTP,KC_MPLY,KC_VOLD,KC_PGDN,KC_MINS,_______,      _______,KC_PLUS,KC_END ,_______,_______,_______,_______,
                                        _______,_______,_______,         _______,_______, _______
  ),

  [_ADJUST] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     _______,_______,_______,_______,_______,_______,               _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_RTOG,KC_RMOD,KC_RHUI,KC_RSAI,KC_RVAI,_______,               _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_VK,  _______,KC_RHUD,KC_RSAD,KC_RVAD,_______,               _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     KC_BL_S,KC_RST ,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       _______,_______,_______,         _______,_______, _______
  //                  `----+----+----'        `----+----+----'
  )

};

void suspend_power_down_keymap(void){
    backlight_config.enable = false; // disable LED backlight
}

void suspend_wakeup_init_keymap(void){
    backlight_config.enable = true; // enable LED backlight
}
