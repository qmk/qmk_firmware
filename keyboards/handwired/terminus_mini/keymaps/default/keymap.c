/* Copyright 2017 MogranJM
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

enum terminus_mini_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _MOUSE,
  _ADJUST
};

enum terminus_mini_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  DVORAK,
  LOWER,
  RAISE,
  FUNCTION,
  MOUSE,
  // Custom Macros
  R_PIPE,
  R_POINT
};

#define SPC_LW LT(_LOWER, KC_SPC)
#define ENT_RS LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak -
 * ,----------------------------------------------------------------------------------.
 * | Tab |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  Del |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | BS  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | LSPO|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | RSPC |
 * |-----+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl| LGUI | Lower| LAlt | Space/Lower | Enter/Raise |  Fn  | Mouse| Menu | Ctrl |
 * `----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
  KC_LCTL, KC_LGUI, LOWER,   KC_LALT,     SPC_LW,           ENT_RS,       MO(5),   MO(6),   KC_APP,  KC_RCTL
  ),

/* QWERTY -
 * ,----------------------------------------------------------------------------------.
 * | Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Del |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | BS  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | LSPO|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | RSPC |
 * |-----+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl| LGUI | Lower| LAlt | Space/Lower | Enter/Raise |  Fn  | Mouse| Menu | Ctrl |
 * `----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
  KC_LCTL, KC_LGUI, LOWER,   KC_LALT,     SPC_LW,           ENT_RS,       MO(5),   MO(6),   KC_APP,  KC_RCTL
  ),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  BS  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | LSPO |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | RSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI | Lower| LAlt | Space/Lower | Enter/Raise |  Fn  | Mouse| Menu |Ctrl  |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT(
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,
  KC_BSPC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  SC_LSPO, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    SC_RSPC,
  KC_LCTL, KC_LGUI, LOWER,   KC_LALT,     SPC_LW,           ENT_RS,       MO(5),   MO(6),   KC_APP,  KC_RCTL
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Tab | PgUp | Home |  Up  |  End |   /  |   7  |   8  |   9  |  *   |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  BS  | PgDn | Left | Down |Right |   -  |   4  |   5  |   6  |  +   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSPO |   Z  |   X  |   C  |   V  |   =  |   1  |   2  |   3  | Enter|      | RSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI | Lower| LAlt | Space/Lower |      0      |   .  |  Fn  |ADJUST| Ctrl |
 * `-----------------------------------------------------------------------------------'
 Want to add tap-dance function to 0 key: Tap=0, doubleTap=Ent
 */

[_LOWER] = LAYOUT(
  KC_TAB,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PAST, XXXXXXX, _______,
  _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS, KC_4,    KC_5,    KC_6,    KC_PPLS, XXXXXXX, _______,
  _______, _______, _______, _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_PENT, XXXXXXX, _______,
  _______, _______, _______, _______,     _______,          KC_0,         KC_DOT,  MO(5),   RAISE,   _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   +  |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  BS  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   "  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSPO |  <-  |  %>% |   {  |   [  |   `  |   \  |   ]  |   }  |   .  |   ?  | RSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI |      | LAlt | Space/Lower | Enter/Raise |  Fn  | Mouse| Raise| Ctrl |
 * `-----------------------------------------------------------------------------------'
  */

[_RAISE] = LAYOUT(
  KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, R_POINT, R_PIPE,  KC_LCBR, KC_LBRC, KC_GRV,  KC_BSLS, KC_RBRC, KC_RCBR, KC_DOT,  KC_SLSH, _______,
  _______, _______, XXXXXXX, _______,     SPC_LW,           ENT_RS,       MO(5),   MO(6),   _______, _______
   ),

/*Function
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | Mute | Vol- | Vol+ |      |      |      |  F1  |  F2  |  F3  |  F4  | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps | Stop | |<<  | >/|| |  >>| |      |      |  F5  |  F6  |  F7  |  F8  |PrtSc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSOB |      |      |      |      |      |      |  F9  | F10  | F11  | F12  |ScrLk |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI |      | Alt  | Space/Lower | Enter/Raise |  Fn  |      |      |PsBrk |
 * `-----------------------------------------------------------------------------------'
 */

[_FUNCTION] = LAYOUT(
  _______, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,
  KC_CAPS, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SCRL,
  _______, _______, XXXXXXX, _______,     _______,          _______,      _______, XXXXXXX, XXXXXXX, KC_PAUS
  ),

/* MOUSE
 * ,---------------------------------------------------------------------------------------.
 * |  Esc | WhlU  | WhlL | MsUp  | WhlR |      |      |   M1  |   M2  |  M3  |      |      |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * |      | WhlD  | MsL  | MsDn  | MsR  |      |      |LClick |RClick |      |      |      |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * | LSPO |       |      |       |      |      |      |       |       |      |      | RSCB |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * | Ctrl |       |      |       | Sensitivity |  Sensitivity |       |MOUSE |      | Ctrl |
 * `---------------------------------------------------------------------------------------'
 */

[_MOUSE] = LAYOUT(
  KC_ESC,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN4, KC_BTN5, XXXXXXX, XXXXXXX,
  KC_BSPC, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SC_RSPC,
  _______, XXXXXXX, XXXXXXX, XXXXXXX,     KC_ACL2,          KC_ACL0,      XXXXXXX, MO(6),   XXXXXXX, KC_RCTL
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |QK_BOOT |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK,  DVORAK,  _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
  _______, _______, _______, _______,     _______,          _______,      _______, _______, _______,  _______
)

};

// Cases to switch default layer to QWERTY, COLEMAK or DVORAK and to access ADJUST layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
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
    // Macros to send R pointer & dplyr pipe
    //R Pointer: <-
    case R_POINT:
      if (record->event.pressed) { // pointer
        SEND_STRING("<- ");
        //return MACRO(D(LSFT), T(COMM), U(LSFT), T(MINS), END);
      }
      break;
    //dplyr pipe: %>%
    case R_PIPE:
      if (record->event.pressed) { // dplyr pipe
        SEND_STRING("%>% ");
        //return MACRO(D(LSFT), T(5), T(DOT), T(5), U(LSFT), END);
      }
      break;
  }
  return true;
}
