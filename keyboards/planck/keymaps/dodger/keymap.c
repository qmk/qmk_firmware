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

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
bool isGame = false;
bool qwertGame = false;


enum planck_layers {
  _COLEMAK,
  _GAME,
  _QWERTGAME,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  GCTOGG,
  QGCTOGG,
  LOWER,
  RAISE,
  PAREN
};

enum {
  TD_SPC_ENT = 0,
  TD_ESC_CAPS
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |PAREN |Lower | shift|space |Raise | Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  KC_LCTL, KC_LGUI, KC_LALT, PAREN, LOWER,   RSFT_T(KC_BSPC),  TD(TD_SPC_ENT),  RAISE,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |   [  |   ]  |      |  (   |   )  |   {  |   }  |      |  +   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | left | down |  up  | right|  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |  _   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_LPRN, KC_RPRN,  KC_LCBR,    KC_RCBR, _______, S(KC_EQL),
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT,    KC_DOWN,    KC_UP, KC_RGHT,   KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    KC_MPRV,    KC_MNXT, _______, KC_UNDS,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ~   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | GCTG |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  GCTOGG
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |EEPRst| Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  EE_CLR,  QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
  _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
  _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_GAME] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  KC_LCTL, QGCTOGG, KC_LALT, LOWER, KC_SPC, RSFT_T(KC_BSPC), TD(TD_SPC_ENT), RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
),

[_QWERTGAME] = LAYOUT_planck_grid(
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
  KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
  KC_LCTL, QGCTOGG, KC_LALT, LOWER, KC_SPC, RSFT_T(KC_BSPC), TD(TD_SPC_ENT), RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef BACKLIGHT_ENABLE
		      backlight_set(0);
        #endif
      }
      return false;
      break;
	case GCTOGG:
      if (record->event.pressed) {
        if (!isGame) {
          set_single_persistent_default_layer(_GAME);
          isGame = true;
        }
        else {
          set_single_persistent_default_layer(_COLEMAK);
          isGame = false;
          qwertGame = false;
        }
      }
      return false;
      break;
    case QGCTOGG:
      if (record->event.pressed) {
        if (!qwertGame) {
          set_single_persistent_default_layer(_QWERTGAME);
          qwertGame = true;
        } else {
          set_single_persistent_default_layer(_GAME);
          qwertGame = false;
        }
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
    case PAREN:
    	if (record->event.pressed) {
    		SEND_STRING("()");
    	}
    	return false; break;
  }
  return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _GAME:
      rgblight_sethsv_noeeprom(0, UINT8_MAX, RGBLIGHT_LIMIT_VAL);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL+5);
      break;
    case _QWERTGAME:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD+2);
      break;
    case _COLEMAK:
      rgblight_sethsv_noeeprom(0, 0, 0);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    default:
      break;
  }
  return state;
}

void matrix_init_user(void) {
	set_single_persistent_default_layer(_COLEMAK);
	isGame = false;
  qwertGame = false;
  #ifdef BACKLIGHT_ENABLE
        backlight_level(0);
  #endif
}

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(0, 0, 0);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
