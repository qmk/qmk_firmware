/* Copyright 2017 Wunder
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
#include "xd75.h"
#include "action_layer.h"


enum custom_keycodes {
  // TD_ESC = 0,
  TD_LOCK = 0,
};

// Layers
#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2



// Shortcuts
#define KC_____ KC_NO
#define KC_     KC_TRNS
#define KC_RST  RESET
#define KC_RASE MO(_RAISE)
#define KC_LOWR MO(_LOWER)

// RGB and Backlighting
#define KC_RGB  RGB_TOG
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_BLT  BL_TOGG
#define KC_BLS  BL_STEP
#define KC_BLI  BL_INC
#define KC_BLD  BL_DEC

// Tapdance
//#define KC_EXC TD(TD_ESC)
#define KC_LOCK TD(TD_LOCK)

// Macros
#define KC_ROOT M(0)
#define KC_PPLY M(1)
#define KC_PSEF M(2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
      ESC, 1  , 2  , 3  , 4  , 5  ,PGUP,PSCR,PGDN, 6  , 7  , 8  , 9  , 0  ,BSPC,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      TAB, Q  , W  ,  E , R  , T  , INS,BSLS, DEL, Y  , U  , I  , O  , P  ,QUOT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LCTL, A  , S  ,  D , F  , G  ,HOME,PLUS,LOCK, H  , J  , K  , L  ,SCLN, ENT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LSFT, Z  , X  ,  C , V  , B  ,LBRC,MINS,RBRC, N  , M  ,COMM, DOT,SLSH,RSFT,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LOWR,LCTL,LALT,LGUI,____, SPC,RASE, GRV,LOWR, SPC,____,LEFT,DOWN,UP  ,RGHT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

 [_LOWER] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
     ____,  F1,  F2,  F3,  F4,  F5,  F6,____,  F7,  F8,  F9, F10, F11, F12,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     ____,ROOT,PPLY,PSEF,____,____,____,____,____,____,____,____,____,____,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     ____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     ____,____,____,____,____,____,____,____,____,____,____,____,____,____,MUTE,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,____,____,____,____,____,    ,____,    ,MPLY,____,MPRV,VOLD,VOLU,MNXT
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
),

[_RAISE] = KC_KEYMAP(
//  .--------------------------------------------------------------------------.
     ____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     ____,____,____,____, RST,____,____,____,____,____,____,____,____,____,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     CAPS,____,____,____,____,____,____, BLI,____,____,____,____,____,____,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
      RGB,RHUI,RHUD,RSAI,RSAD,RVAI,RVAD, BLD,____,____,____,____,BTN1,BTN2,____,
//  |----+----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,____,____,____,____,____,    ,____,    ,____,____,MS_L,MS_D,MS_U,MS_R
//  '----+----+----+----+----+----+----+----+----+----+----+----+----+----+----'
)
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for left ctrl, twice for ESC
  //[TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_ESC),
  [TD_LOCK] = ACTION_TAP_DANCE_DOUBLE(KC_END, LGUI(KC_L))
};
void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch(id) {
      case 0:
          SEND_STRING("sudo su -\n");
          return false; break;
      case 1:
          SEND_STRING("puppet apply /etc/puppetlabs/code/environments/production/manifests/site.pp\n");
          return false; break;
      case 2:
          SEND_STRING("ps -ef | grep ");
          return false; break;
    }
  }
  return MACRO_NONE;
};
