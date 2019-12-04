/* Copyright 2019 Dima Chechetkin
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

// Layers
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MEDIA 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MEDIA,
  BACKLIT,
  RGBRST,
  MSLU,
  MSRU,
  MSLD,
  MSRD
};

#define _____ KC_TRNS
#define XXXXX KC_NO
#define LOWER LOWER
#define RAISE RAISE
#define MEDIA TG(_MEDIA)
#define RST   RESET
#define LRST  RGBRST
#define LTOG  RGB_TOG
#define LHUI  RGB_HUI
#define LHUD  RGB_HUD
#define LSAI  RGB_SAI
#define LSAD  RGB_SAD
#define LVAI  RGB_VAI
#define LVAD  RGB_VAD
#define LMOD  RGB_MOD
#define CTLTB CTL_T(KC_TAB)
//#define CTSPC CTL_T(KC_SPC)
#define CTLEN RCTL_T(KC_ENT)
#define ZLALT LALT_T(KC_Z)
#define ZRALT RALT_T(KC_SLSH)
#define LLOW LT(_LOWER, KC_B)
#define RLOW LT(_LOWER, KC_N)
#define LRAI LT(_RAISE, KC_T)
#define RRAI LT(_RAISE, KC_Y)
#define AMUTE KC__MUTE
#define VDOWN KC__VOLDOWN
#define VUP KC__VOLUP
#define MNEXT KC_MEDIA_NEXT_TRACK
#define MPREV KC_MEDIA_PREV_TRACK
#define MPLPP KC_MEDIA_PLAY_PAUSE
#define BRIUP KC_BRIGHTNESS_UP
#define BRIDN KC_BRIGHTNESS_DOWN 
#define LBGUI MT(MOD_LGUI, KC_LBRC)
#define RBGUI MT(MOD_RGUI, KC_RBRC)
#define MSLU  MSLU
#define MSRU  MSRU
#define MSLD  MSLD
#define MSRD  MSRD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //.-----------------------------------------------------------.                ,-----------------------------------------------------------.
       KC_GESC,     KC_Q,     KC_W,     KC_E,     KC_R,     LRAI,                      RRAI,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
         CTLTB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,    CTLEN,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LSPO,    ZLALT,     KC_X,     KC_C,     KC_V,     LLOW,                      RLOW,     KC_M,  KC_COMM,   KC_DOT,    ZRALT,  KC_RSPC
  //.-----------------------------------------------------------.                ,-----------------------------------------------------------.
  ),
  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
       KC_GESC, KC_GRAVE,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,                   KC_CIRC,  KC_AMPR,  KC_ASTR, KC_MINUS,    _____,   KC_DEL,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
        KC_TAB,  KC_HOME,  KC_PGDN,  KC_PGUP,   KC_END,    XXXXX,                   KC_LEFT,  KC_DOWN,    KC_UP, KC_RIGHT,  KC_QUOT,   KC_EQL,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LBRC,    XXXXX,    XXXXX,    XXXXX,    XXXXX,    XXXXX,                   KC_UNDS,  KC_PLUS,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_RBRC
  //.-----------------------------------------------------------.                ,-----------------------------------------------------------.
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
       KC_GESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                     KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,    _____,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
         _____,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    _____,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
         _____,   KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,                     _____,    _____,    _____,    _____,    _____,    _____
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
  ),
  
  [_MEDIA] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
         _____,    XXXXX,    XXXXX,  KC_ACL0,  KC_ACL1,  KC_ACL2,                      MSLU,  KC_MS_U,     MSRU,  KC_WH_U,    XXXXX,  KC_BTN2,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
          LTOG,    XXXXX,    BRIDN,    BRIUP,     LVAI,    XXXXX,                   KC_MS_L,  KC_BTN1,  KC_MS_R,  KC_BTN2,    XXXXX,  KC_BTN1,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
          LMOD,     LHUD,     LSAD,     LVAD,    XXXXX,    XXXXX,                      MSLD,  KC_MS_D,     MSRD,  KC_WH_D,    MNEXT,  KC_BTN3\
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
/**  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
**/
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
