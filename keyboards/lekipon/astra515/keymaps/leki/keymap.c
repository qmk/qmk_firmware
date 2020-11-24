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
#define RAISE   LT(_RAISE,KC_HENK) //Tap to Henkan(/w AHK Assistance)
#define LOWER   LT(_LOWER,KC_MHEN) //Tap to Muhenkan(/w AHK Assistance)
//#define RAISE MO(_RAISE) //Not Defined Tap Code
//#define LOWER MO(_LOWER) //Not Defined Tap Code
#define ADJUST  MO(_ADJUST) //Holding RAISE and LOWER
#define ANSI    TO(_ANSI)
#define JIS     TO(_JIS)
#define CTandCP LCTL_T(KC_CAPS)
#define SFandSP RSFT_T(KC_SPC)
#define SFandEN RSFT_T(KC_ENT)
#define CTandSP LCTL_T(KC_SPC)
#define KANA    LALT(KC_GRV)
#define UNDO    LCTL(KC_Z)
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define XXXXXXX KC_NO

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false; // 追加
  static bool rshift = false; // 追加

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

 /* ANSI
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * | Esc   |   1   |   2   |   3   |   4   |   5   |  Ins  | Home  | PgUP  |   6   |   7   |   8   |   9   |   0   |  B/S  |
   * |-------+-------+-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |   '   |   ,   |   .   |   P   |   Y   |  Del  |  End  | PgDN  |   F   |   G   |   C   |   R   |   L   |   \   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |CTandCP|   A   |   O   |   E   |   U   |   I   |   -   |   ~   |   =   |   D   |   H   |   T   |   N   |   S   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |   ;   |   Q   |   J   |   K   |   X   |  Esc  | Shift/|  MENU |   B   |   M   |   W   |   V   |   Z   | Enter |
   * |-------+-------+-------+-------+-----------------------| Enter |-----------------------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  |    LOWER  |  CTandSP  |       |  SFandSP  |   RAISE   | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_ANSI] = LAYOUT( /* Base ANSI */
 KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_INS , KC_HOME, KC_PGUP, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,\
 KC_TAB , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_DEL , KC_END , KC_PGDN, KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_BSLS,\
 CTandCP, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_MINS, KC_TILD, KC_EQL , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_SLSH,\
 KC_LSFT, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_ESC , SFandEN, KC_APP , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_ENT ,\
 KC_RCTL, KANA   , KC_LGUI, KC_LALT, LOWER  , XXXXXXX, CTandSP, XXXXXXX, SFandSP, XXXXXXX, RAISE  , KC_RALT, KC_RGUI, KC_APP , KC_RCTL \
),

 /* JIS
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * | Esc   |   1   |  JU2  |   3   |   4   |   5   |  Ins  | Home  | PgUP  |  JU6  |  JU7  |  JU8  |  JU9  |  JU0  |  B/S  |
   * |-------+-------+-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |  JU'  |   ,   |   .   |   P   |   Y   |  Del  |  End  | PgDN  |   F   |   G   |   C   |   R   |   L   |  JU\  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |CTandCP|   A   |   O   |   E   |   U   |   I   |  JU-  |  JU~  |  JU=  |   D   |   H   |   T   |   N   |   S   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Shift |  JU;  |   Q   |   J   |   K   |   X   |  JU[  | Shift/|  JU]  |   B   |   M   |   W   |   V   |   Z   | Enter |
   * |-------+-------+-------+-------+-----------------------| Enter |-----------------------+-------+-------+-------+-------|
   * | Ctrl  | KANA  | LGUI  | LALT  |    LOWER  |  CTandSP  |       |  SFandSP  |   RAISE   | RALT  | RGUI  | MENU  | Ctrl  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_JIS] = LAYOUT( /* JIS */
 _______, _______, JU_2   , _______, _______, _______, _______, _______, _______, JU_6   , JU_7   , JU_8   , JU_9   , JU_0   , _______,\
 _______, JU_QUOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, JU_BSLS,\
 CTandCP, _______, _______, _______, _______, _______, JU_MINS, JU_GRV , JU_EQL , _______, _______, _______, _______, _______, _______,\
 _______, JU_SCLN, _______, _______, _______, _______, JU_LBRC, _______, JU_RBRC, _______, _______, _______, _______, _______, _______,\
 _______, _______, _______, _______, LOWER  , XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, RAISE  , _______, _______, _______, _______ \
),

 /* RAISE 
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |   ~   |       |       |       |       |       | PrtSc | ScrLK | Pause |       |       |       |       |       |  Del  |
   * |-------+-------+-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |  F1   |  F2   |  F3   |  F4   |  F5   |  F11  |       |  F12  |  F6   |  F7   |  F8   |  F9   |  F10  | _____ |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Ctrl  | Home  | PgDN  | PgUP  |  End  |  Esc  | _____ | _____ | _____ |  B/S  |  Left |  Down |   Up  | Right | _____ |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | _____ | UNDO  |  CUT  | COPY  | PASTE |   [   |       |       |       |   ]   | Enter |       |       |       | _____ |
   * |-------+-------+-------+-------+-----------------------| _____ |-----------------------+-------+-------+-------+-------|
   * | _____ | CAPS  | _____ | _____ |   ADJUST  |  _______  |       |  _______  |  _______  | _____ | _____ | _____ | _____ |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_RAISE] = LAYOUT( /* RAISE */
 KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL ,\
 KC_TAB , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F11 , XXXXXXX, KC_F12 , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,\
 KC_LCTL, KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,\
 KC_LSFT, UNDO   , CUT    , COPY   , PASTE  , KC_LBRC, XXXXXXX, _______, XXXXXXX, KC_RBRC, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, _______,\
 _______, KC_CAPS, _______, _______, ADJUST , XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, _______, _______, _______, _______, _______\
),

 /* LOWER 
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |   `   |   !   |   @   |   #   |   $   |   %   | PrtSc | ScrLK | Pause |   ^   |   &   |   *   |   (   |   )   |  Ins  |
   * |-------+-------+-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------+-------|
   * | Tab   |       |       |       |       |       |       |       |       | NumLK |   7   |   8   |   9   |   -   | _____ |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | Enter |  Left |  Down |   Up  | Right |  Esc  | _____ | _____ | _____ |  B/S  |   4   |   5   |   6   |   +   |   /   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * | _____ | UNDO  |  CUT  | COPY  | PASTE |   [   |       |       |       |   ]   |   1   |   2   |   3   |   *   | Enter |
   * |-------+-------+-------+-------+-----------------------| _____ |-----------------------+-------+-------+-------+-------|
   * | _____ | CAPS  | _____ | _____ |  _______  |  _______  |       |  _______  |       0   |       |   .   |       | _____ |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */
[_LOWER] = LAYOUT( /* LOWER */
 KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_PSCR, KC_SLCK, KC_PAUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_INS ,\
 KC_TAB , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, _______,\
 KC_ENT , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PSLS,\
 KC_LSFT, UNDO   , CUT    , COPY   , PASTE  , KC_LBRC, XXXXXXX, _______, XXXXXXX, KC_RBRC, KC_P1  , KC_P2  , KC_P3  , KC_PAST, KC_PENT,\
 _______, KC_CAPS, _______, _______, _______, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, KC_P0  , XXXXXXX, KC_PDOT, XXXXXXX, _______
),

 /* ADJUST
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * | RGBRST|       |       |       |       |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------+-------|
   * |       |       |  HUE+ |  SAT+ |  VAL+ |  MOD+ |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |  HUE- |  SAT- |  VAL- |  MOD- |       |       |       |       |  MUTE |  VOL- |  VOL+ |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       | RGBTOG|  ANSI |       |   JIS |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-----------------------| _____ |-----------------------+-------+-------+-------+-------|
   * | _____ |       | _____ | _____ |  _______  |  _______  |       |  _______  |           |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

[_ADJUST] = LAYOUT( /* ADJUST (RAISE+LOWER)*/
 RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,\
 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, ANSI , XXXXXXX, JIS , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
 _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______
)

};


/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_RGHT);
    } else {
      tap_code(KC_LEFT);
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}



#ifdef RGBLIGHT_ENABLE
// The first three LEDs are used as indicators for CAPS_LOCK, NUM_LOCK and SCROLL_LOCK.
void keyboard_post_init_user(void) {
	rgblight_set_effect_range(3, RGBLED_NUM-3);
	
	led_set_user((1<<USB_LED_CAPS_LOCK)|(1<<USB_LED_NUM_LOCK)|(1<<USB_LED_SCROLL_LOCK));
    wait_ms(200);
    led_set_user(0);
}

#define HSV_CAPS        0, 255,  96
#define HSV_CAPS_OFF    0, 255,  16
#define HSV_NUMLK      32, 255,  96
#define HSV_NUMLK_OFF  32, 255,  16

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
#define HSV_LOWER    84, 255,  96 //Green
#define HSV_RAISE    12, 255,  96 //Orange
#define HSV_ADJUST  140, 192,  96 //Azure
#define HSV_BLACK     0,   0,   0 //OFF


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
        sethsv(HSV_BLACK, (LED_TYPE *)&led[2]);
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

