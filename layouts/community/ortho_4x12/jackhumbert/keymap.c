/* Copyright 2015-2020 Jack Humbert
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


enum planck_layers {
  _COLEMAK,
  _SHIFT_COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define S_SFT MO(_SHIFT_COLEMAK)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   q  |   w  |   f  |   p  |   g  |   j  |   l  |   u  |   y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | -    |   a  |   r  |   s  |   t  |   d  |   h  |   n  |   e  |   i  |   o  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   z  |   x  |   c  |   v  |   b  |   k  |   m  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shft | Ctrl | Alt  | GUI  |Lower | Shft | Spc  |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_MINS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_ESC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   S_SFT,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak, Shifted
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  _   |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   !  |   @  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SHIFT_COLEMAK] = LAYOUT_ortho_4x12(
    S(KC_TAB), S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_G), S(KC_J), S(KC_L), S(KC_U),    S(KC_Y),    KC_COLN,  _______,
    S(KC_MINS), S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_D), S(KC_H), S(KC_N), S(KC_E),    S(KC_I),    S(KC_O),  KC_GRV,
    S(KC_ESC), S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_K), S(KC_M), KC_EXLM,    KC_AT,      KC_QUES,  _______ ,
    _______,   _______, _______, _______, _______, _______, _______, _______, S(KC_LEFT), S(KC_DOWN), S(KC_UP), S(KC_RGHT)
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   7  |   8  |   9  |      |  Del |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |   4  |   5  |   6  |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   0  |   1  |   2  |   3  |      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | Pgup | Pgdn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    _______, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, KC_DEL,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    KC_DEL,  XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
    _______, KC_0,    KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   <  |   $  |   >  |      |      |   [  |   _  |   ]  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   \  |   (  |   "  |   )  |   #  |   %  |   {  |   =  |   }  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   :  |   *  |   +  |      |      |   &  |   ^  |   ~  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    _______, XXXXXXX, KC_LT,   KC_DLR,  KC_GT,   XXXXXXX, XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, _______,
    _______, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH, KC_PERC, KC_LCBR, KC_EQL,  KC_RCBR, KC_PIPE, _______,
    _______, XXXXXXX, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX, XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
    _______, XXXXXXX, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    #ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
    #else
      tap_code(KC_PGDN);
    #endif
  } else {
    #ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
    #else
      tap_code(KC_PGUP);
    #endif
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
