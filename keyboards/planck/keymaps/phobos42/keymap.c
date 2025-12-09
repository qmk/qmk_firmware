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


/* Keymap by:
 *            _           _               _  _  ____  
 *      _ __ | |__   ___ | |__   ___  ___| || ||___ \
 *    | '_ \| '_ \ / _ \| '_ \ / _ \/ __| || |_ __) |
 *   | |_) | | | | (_) | |_) | (_) \__ \__   _/ __/ 
 *  | .__/|_| |_|\___/|_.__/ \___/|___/  |_||_____|
 * |_|
 */

#include QMK_KEYBOARD_H


enum planck_layers {
  _QWERTY,
  _DVORAK,
  _NUMP,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  NUMP,
  LOWER,
  RAISE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | App  | Alt  |Lower |    Space    |Raise | nump | ALT  | CAPS | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */


[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_QUOT,
  KC_LCTL, KC_LGUI, KC_APP, KC_LALT,  LOWER,   KC_SPC,  KC_SPC,  RAISE,  MO(_NUMP), KC_RALT, KC_CAPS, KC_RCTL
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | /    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | App  | Alt  |Lower |    Space    |Raise | nump | ALT  | CAPS | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,      KC_R,    KC_L,    KC_BSPC,
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,      KC_N,    KC_S,    KC_ENT,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,      KC_V,    KC_Z,    KC_SLSH,
  KC_LCTL, KC_LGUI, KC_APP,  KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   MO(_NUMP), KC_RALT, KC_CAPS, KC_RCTL
),


/* NumPad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |   *  |   7  |   8  |   9  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  +   |   -  |   4  |   5  |   6  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   /  |   1  |   2  |   3  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | NUMP |   0  |   .  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMP] = LAYOUT_planck_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_ASTR, KC_7,    KC_8,    KC_9,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_EQL), KC_MINS, KC_4,    KC_5,    KC_6,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_SLSH, KC_1,    KC_2,    KC_3,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,   _______, KC_0,    KC_DOT,  KC_ENT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      | Bksp | Del  |      |   +  |   -  |   [  |   ]  |  ~   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   =  |   _  |   |  |   \  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Vol- | Vol+ | Play | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN,  KC_BSPC,
  _______, _______, KC_PSCR, _______, KC_BSPC, KC_DEL,  _______, S(KC_EQL),  KC_MINS,    KC_LBRC, KC_RBRC,  KC_TILD,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_EQL,     S(KC_MINS), KC_PIPE, KC_BSLS,  KC_GRV,
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_VOLD,    KC_VOLU, KC_MPLY,  KC_MUTE
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      | Bksp | Del  | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Vol- | Vol+ | Play | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  _______, _______, _______, _______, KC_BSPC, KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|RGBTOG|RGBMODE|COLOR-change| sat I| sat D| brightness  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Dvorak|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  _______,    QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
  _______,    _______, MU_NEXT,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  DVORAK,  _______, _______, _______,
  LED_LEVEL,  AU_PREV, AU_NEXT,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF, _______, _______, _______, _______, _______,
  _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    break;
    case DVORAK:
      if (record -> event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    break;    
  }
  return true;
}
