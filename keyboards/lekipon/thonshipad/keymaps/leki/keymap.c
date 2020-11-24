/* Copyright 2020 Lekipon
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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include <string.h>
  #include "print.h"
  #include "common/glcdfont.c"
  #include "sendchar.h"
  #include "common/oled_helper.h"
#endif


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  JU_2,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS
};

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _ANSI = 0,
    _JIS,
    _RAISE,
    _LOWER,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
#define RAISE LT(_RAISE,KC_HENK) //Tap to Henkan(/w AHK Assistance)
#define LOWER LT(_LOWER,KC_MHEN) //Tap to Muhenkan(/w AHK Assistance)
#define ADJUST MO(_ADJUST) //Holding RAISE and LOWER
#define ANSI   TO(_ANSI)
#define JIS    TO(_JIS)
#define CTandCP LCTL_T(KC_CAPS)
#define SFandSP RSFT_T(KC_SPC)
#define CTandSP LCTL_T(KC_SPC)
#define KANA    LALT(KC_GRV)
#define UNDO    LCTL(KC_Z)
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define XXXXXXX KC_NO

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false; 
  static bool rshift = false; 

  switch (keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
      }
      #endif
      return false;
    case JU_2:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_2);
          unregister_code(KC_2);
        }
      }
      return false;
    case JU_6:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_EQL);
          unregister_code(KC_EQL);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_6);
          unregister_code(KC_6);
        }
      }
      return false;
    case JU_7:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_6);
          unregister_code(KC_6);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_7);
          unregister_code(KC_7);
        }
      }
      return false;
    case JU_8:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_8);
          unregister_code(KC_8);
        }
      }
      return false;
    case JU_9:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_8);
          unregister_code(KC_8);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_9);
          unregister_code(KC_9);
        }
      }
      return false;
    case JU_0:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_0);
          unregister_code(KC_0);
        }
      }
      return false;
    case JU_MINS:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_INT1);
          unregister_code(KC_INT1);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_MINS);
          unregister_code(KC_MINS);
        }
      }
      return false;
    case JU_EQL:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_MINS);
          unregister_code(KC_MINS);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_LBRC:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
        }
      }
      return false;
    case JU_RBRC:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_NUHS);
          unregister_code(KC_NUHS);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_NUHS);
          unregister_code(KC_NUHS);
        }
      }
      return false;
    case JU_BSLS:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_INT3);
          unregister_code(KC_INT3);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_INT1);
          unregister_code(KC_INT1);
        }
      }
      return false;
    case JU_SCLN:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
        }
      }
      return false;
    case JU_QUOT:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_2);
          unregister_code(KC_2);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_7);
          unregister_code(KC_7);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_GRV:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_EQL);
          unregister_code(KC_EQL);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_CAPS:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
        unregister_code(KC_LSFT);
      }
      return false;
      break;
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* ANSI_MODE
   * ,-------------------------------------------------------.       ,-------------------------------------------------------.
   * | Esc   |   1   |   2   |   3   |   4   |   5   |  Ins  |       | PgUP  |   6   |   7   |   8   |   9   |   0   |  B/S  |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   '   |   ,   |   .   |   P   |   Y   |  Del  |       | PgDN  |   F   |   G   |   C   |   R   |   L   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * |CTandCP|   A   |   O   |   E   |   U   |   I   |   -   |       |   =   |   D   |   H   |   T   |   N   |   S   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   ;   |   Q   |   J   |   K   |   X   |   [   |  Up   |   ]   |   B   |   M   |   W   |   V   |   Z   | Enter |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  | LOWER |CTandSP| Left  | Down  | Right |SFandSP| RAISE | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_ANSI] = LAYOUT( /* Base ANSI */
 KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_INS ,          KC_PGUP, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,\
 KC_TAB , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_DEL ,          KC_PGDN, KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_BSLS,\
 CTandCP, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_MINS,          KC_EQL , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_SLSH,\
 KC_LSFT, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_LBRC, KC_UP  , KC_RBRC, KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_ENT ,\
 KC_RCTL, KANA   , KC_LGUI, KC_LALT, LOWER  , CTandSP, KC_LEFT, KC_DOWN, KC_RGHT, SFandSP, RAISE  , KC_RALT, KC_RGUI, KC_APP , KC_RCTL \
),

 /* JIS_MODE
   * ,-------------------------------------------------------.       ,-------------------------------------------------------.
   * | Esc   |   1   |  JU2  |   3   |   4   |   5   |  Ins  |       | PgUP  |  JU6  |  JU7  |  JU8  |  JU9  |  JU0  |  B/S  |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |  JU'  |   ,   |   .   |   P   |   Y   |  Del  |       | PgDN  |   F   |   G   |   C   |   R   |   L   |  JU\  |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * |JU_CAPS|   A   |   O   |   E   |   U   |   I   |  JU-  |       |  JU=  |   D   |   H   |   T   |   N   |   S   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |  JU;  |   Q   |   J   |   K   |   X   |  JU[  |  Up   |  JU]  |   B   |   M   |   W   |   V   |   Z   | Enter |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  | LOWER |CTandSP| Left  | Down  | Right |SFandSP| RAISE | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_JIS] = LAYOUT( /* JIS Mode */
 _______, _______, JU_2   , _______, _______, _______, _______,          _______, JU_6   , JU_7   , JU_8   , JU_9   , JU_0   , _______,\
 _______, JU_QUOT, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, JU_BSLS,\
 JU_CAPS, _______, _______, _______, _______, _______, JU_MINS,          JU_EQL , _______, _______, _______, _______, _______, _______,\
 _______, JU_SCLN, _______, _______, _______, _______, JU_LBRC, _______, JU_RBRC, _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, LOWER  , _______, _______, _______, _______, _______, RAISE  , _______, _______, _______, _______ \
),

/* RAISE (Function)
   * ,-------------------------------------------------------.       ,-------------------------------------------------------.
   * |   ~   |       |       |       |       |       |       |       |       |       |       |       |       |       |  Del  |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |  F1   |  F2   |  F3   |  F4   |  F5   |  F11  |       |  F12  |  F6   |  F7   |  F8   |  F9   |  F10  |   \   |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * |CTandCP| Home  | PgDN  | PgUP  |  End  |       |       |       |       |  B/S  | Left  | Down  |  Up   | Right |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift | UNDO  |  CUT  | COPY  | PASTE |       |       | PgUP  |       |       | Enter |       |       |       | Enter |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | CAPS  | LGUI  | LALT  | ADJUST|CTandSP| Home  | PgDN  |  End  |SFandSP| RAISE | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_RAISE] = LAYOUT( /* RAISE */
 KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL ,\
 _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F11 ,          KC_F12 , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,\
 _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_ESC , XXXXXXX,          XXXXXXX, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,\
 _______, UNDO   , CUT    , COPY   , PASTE  , XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, _______,\
 _______, KC_CAPS, _______, _______, ADJUST , _______, KC_HOME, KC_PGDN, KC_END , _______, _______, _______, _______, _______, _______\
),

/* LOWER (Nums)
   * ,-------------------------------------------------------.       ,-------------------------------------------------------.
   * |   `   |   !   |   @   |   #   |   $   |   %   |       |       |       |   ^   |   &   |   *   |   (   |   )   |  Del  |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |       |       |       |       |       |       |       |       | NumLK |   7   |   8   |   9   |   -   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * | Enter | Left  | Down  |  Up   | Right |       |       |       |       |  B/S  |   4   |   5   |   6   |   +   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift | UNDO  |  CUT  | COPY  | PASTE |       |       | PgUP  |       |   =   |   1   |   2   |   3   |   *   | Enter |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  |       |CTandSP| Home  | PgDN  |  End  |SFandSP|   0   |       |   .   |       | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_LOWER] = LAYOUT( /* LOWER */
 KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, XXXXXXX,          XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,\
 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_NLCK, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, _______,\
 KC_ENT , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ESC , XXXXXXX,          XXXXXXX, KC_BSPC, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PSLS,\
 _______, UNDO   , CUT    , COPY   , PASTE  , XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, KC_EQL , KC_P1  , KC_P2  , KC_P3  , KC_PAST, KC_PENT,\
 _______, KC_CAPS, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END , _______, KC_P0  , XXXXXXX, KC_PDOT, XXXXXXX, _______
),

/* ADJUST      
   * ,-------------------------------------------------------.       ,-------------------------------------------------------.
   * |RGB_RST|       |       |       |       |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * |       |       | HUE+  | SAT+  | VAL+  | MODE+ |       |       |       |       | PrtSC | ScrLK | Pause |       |       |
   * |-------+-------+-------+-------+-------+-------+-------|       |-------+-------+-------+-------+-------+-------+-------|
   * |       |       | HUE-  | SAT-  | VAL-  | MODE- |  Win  |       |  Mac  |       | Mute  | Vol-  | Vol+  |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |RGB_TOG|  ANSI |       |  JIS  |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  |       |CTandSP|       |       |       |SFandSP|       | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_ADJUST] = LAYOUT( /* ADJUST (RAISE+LOWER)*/
 RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, XXXXXXX,          XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,AG_NORM,          AG_SWAP, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, ANSI , XXXXXXX, JIS , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
 _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______
)

};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  oled_write_P(PSTR("Layer:"), false);
  switch (biton32(layer_state)) {
    case _ANSI:
      oled_write_P(PSTR("ANSI (DVORAK)\n"), false);
      break;
    case _JIS:
      oled_write_P(PSTR("JIS (DVORAK)\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE (Func)\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER (Nums)\n"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("ADJUST\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding 'n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  oled_write_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("\n<CAPS> ") : PSTR("\n       "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_NUM_LOCK) ? PSTR("<NUM> ") : PSTR("      "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_SCROLL_LOCK) ? PSTR("<SCR> ") : PSTR("      "), false);
}
#endif


#define HSV_CAPS        0, 255, 128
#define HSV_CAPS_OFF    0, 255,  16
#define HSV_NUMLK      32, 255, 128
#define HSV_NUMLK_OFF  32, 255,  16

#ifdef RGBLIGHT_ENABLE
// The first three LEDs are used as indicators for CAPS_LOCK, NUM_LOCK and LAYER_STATE.
void keyboard_post_init_user(void) {
	rgblight_set_effect_range(3, RGBLED_NUM-3);

	led_set_user((1<<USB_LED_CAPS_LOCK)|(1<<USB_LED_NUM_LOCK));
    wait_ms(200);
    led_set_user(0);
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        sethsv(HSV_CAPS , (LED_TYPE *)&led[0]);
    } else {
        sethsv(HSV_CAPS_OFF, (LED_TYPE *)&led[0]);
    }
    	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        sethsv(HSV_NUMLK, (LED_TYPE *)&led[1]);
    } else {
        sethsv(HSV_NUMLK_OFF, (LED_TYPE *)&led[1]);
    }
    rgblight_set();
}
#endif

//A description for expressing the layer position in LED mode.
#define HSV_ANSI     84, 255,  16 //Green
#define HSV_JIS     140, 255,  16 //Blue
#define HSV_LOWER    84, 255, 128 //Green
#define HSV_RAISE    12, 255, 128 //Orange
#define HSV_ADJUST  140, 128, 128 //Azure

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _ANSI:
        sethsv(HSV_ANSI, (LED_TYPE *)&led[2]);
      break;
    case _JIS:
        sethsv(HSV_JIS, (LED_TYPE *)&led[2]);
      break;
    case _RAISE:
        sethsv(HSV_RAISE, (LED_TYPE *)&led[2]);
      break;
    case _LOWER:
        sethsv(HSV_LOWER, (LED_TYPE *)&led[2]);
      break;
    case _ADJUST:
        sethsv(HSV_ADJUST, (LED_TYPE *)&led[2]);
      break;
    default: //  for any other layers, or the default layer
        sethsv( 0, 0, 0, (LED_TYPE *)&led[2]);
      break;
    }
#endif
return state;
}


void matrix_init_user(void) {
}


void matrix_scan_user(void) {
}

bool led_update_user(led_t led_state) {
    return true;
}

