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
 * cd /c/qmk_firmware-master... make planck/rev6:navi
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _ADJUST

};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNCTION
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CtlE |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  |CtlSE |  GUI |  Alt | Lower|    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 * CtlSE = Control+shift+esc/
 * CtlE = Control when held, esc when tapped
 * FN takes two taps to have it stay as FN
 */
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  TT(_FUNCTION), LCTL(LALT(KC_DEL)), KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_BSPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |  ISO |  End | Home |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Pg DN | Pg UP|      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
  KC_LSHIFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_END, KC_HOME,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, KC_PGDN  , KC_PGUP, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | End  | Home |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Pg DN |Pg UP |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  KC_LSHIFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_END, KC_HOME,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, KC_PGDN  , KC_PGUP, _______
),


/* Function
 * ,-----------------------------------------------------------------------------------.
 * | Vol- | Mute | Vol+ | 	   | 	  |      |      |   #  |  7   |  8   |  9   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Prev | Play | Next | 	   | 	  |      |      |   +  |  4   |  5   |  6   |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | CALC |  MWU |  M1  |MouseU|  M2  |      |      |   $  |  1   |  2   |  3   | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  MWD |MouseL|MouseD|MouseR|             |   *  |  0   |  .   |Numlck|  /   |
 * `-----------------------------------------------------------------------------------'
 */

[_FUNCTION] = LAYOUT_planck_grid(
  KC_VOLD, KC_MUTE, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_HASH, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC,
  KC_MPRV, KC_MPLY, KC_MNXT, AU_ON, AU_OFF, MU_ON, MU_OFF, KC_PPLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS,
  KC_CALC, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_DLR, KC_KP_1, KC_KP_2, KC_KP_3, KC_ENTER,
  KC_TRNS, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_PAST, KC_KP_0, KC_KP_DOT,KC_NUMLOCK, KC_PSLS
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
	case FUNCTION:
      if (record->event.pressed) {
        layer_on(_FUNCTION);
      } else {
        layer_off(_FUNCTION);
      }
      return false;
	  break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
