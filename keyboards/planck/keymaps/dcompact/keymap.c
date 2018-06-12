/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

// Custom Keycodes and Combinations Used
#define DEL_SHF SFT_T(KC_DEL)
#define QUAKE LCTL(KC_GRV)

#define WKSP_L LALT(LCTL(KC_LEFT))
#define WKSP_D LALT(LCTL(KC_DOWN))
#define WKSP_U LALT(LCTL(KC_UP))
#define WKSP_R LALT(LCTL(KC_RGHT))

extern keymap_config_t keymap_config;

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _FUNC,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  MOUSE,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Tab  | " '  | < ,  | > .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | ? /  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | _ -  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Del/Sf|  : ; |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Bspc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Fn  | GUI  | Alt  |Lower |Shift |Space |Raise | Alt  | GUI  |  Fn  |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = {
  {  KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH},
  {  KC_ESC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS},
  { DEL_SHF, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSPC},
  { KC_LCTL,    FUNC, KC_LGUI, KC_LALT,   LOWER,  KC_LSFT,  KC_SPC,   RAISE, KC_RALT, KC_RGUI,    FUNC,  KC_ENT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | Home |PgDwn | PgUp | End  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |PrScr | Menu |      |      |      |      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |CapsLk|NumLck| Ins  |      |      |      |WkLeft|WkDown| WkUp |WkRigh|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX},
  { XXXXXXX, KC_PSCR, KC_MENU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX},
  { XXXXXXX, KC_CAPS, KC_LNUM,  KC_INS, XXXXXXX, XXXXXXX, XXXXXXX,  WKSP_L,  WKSP_D,  WKSP_U,  WKSP_R, XXXXXXX},
  { _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |Quake |   `  |   ~  |   \  |   |  |   (  |   )  |   7  |   8  |   9  |   /  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   {  |   }  |   4  |   5  |   6  |   *  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   %  |   ^  |   &  |   *  |   [  |   ]  |   1  |   2  |   3  |   -  |Bkspc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |   <  |   >  |      |   0  |   .  |   ,  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {   QUAKE,  KC_GRV, KC_TILD, KC_BSLS, KC_PIPE, KC_LPRN, KC_RPRN,    KC_7,    KC_8,    KC_9, KC_SLSH,  KC_EQL},
  { XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PLUS},
  { XXXXXXX, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_MINS, KC_BSPC},
  { _______, XXXXXXX, _______, _______, _______, KC_LABK, KC_RABK, _______,    KC_0,  KC_DOT, KC_COMM, XXXXXXX}
},

/* Func
 * ,-----------------------------------------------------------------------------------.
 * |      |Sleep |Prev-W|Ply/Ps|Next-W|      |      |  F9  | F10  | F11  | F12  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Wake | Mute | Vol- | Vol+ |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Power |Prev-M|Ply/Ps|Next-M|      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = {
  { XXXXXXX, KC_SLEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX},
  { XXXXXXX, KC_WAKE, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX},
  { XXXXXXX,  KC_PWR, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX},
  { _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX}
},

/* Mouse (Not Reachable on Planck)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Click1|Click3|Click2|      |      |MouseL|MouseD|MouseU|MouseR|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Accel0|Accel1|Accel2|      |      |ScrllL|ScrllD|ScrllU|ScrllR|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  { XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX},
  { XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX},
  { _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  { _______,   RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
  { _______, _______, _______,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______},
  { _______,  MUV_DE,  MUV_IN,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
      } else {
        layer_off(_MOUSE);
      }
      return false;
      break;
  }
  return true;
}
