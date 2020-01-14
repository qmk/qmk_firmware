/* Copyright 2019 gtips
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

//Tap Dance Declarations
enum {
  TD_COPY_PASTE = 0
};

enum layer_names {
    _BASE,
    _NAV_MEDIA,
    _NUM_SCHAR,
    _ADJUST
};

#define KC_COPY LCMD(KC_C)
#define KC_PASTE LCMD(KC_V)
#define NAV_MEDIA  MO(_NAV_MEDIA)
#define NUM_SCHAR  MO(_NUM_SCHAR)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
    KC_GESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LSFT_T(KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_RSPC,
    KC_LCPO,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   TD(TD_COPY_PASTE),  ALT_T(KC_F6),
                                                       LT(_NUM_SCHAR, KC_ENT),    RCMD_T(KC_F3),   LT(_NAV_MEDIA, KC_SPC)
  ),
  
  [_NAV_MEDIA] = LAYOUT_reviung39(
    _______,  _______,  KC_UP,    _______,  _______,    _______,            _______,  _______,  KC__MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,   _______,            _______,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,  _______,   _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,  _______,   _______,  _______,  _______,  KC_CAPSLOCK,
                                                       _______,  _______,   _______
  ),
  
  [_NUM_SCHAR] = LAYOUT_reviung39(
    KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  _______,  _______,   KC_QUOT,  KC_LBRC,   KC_RBRC,            KC_BSLS,    KC_MINS,    KC_EQL,    KC_SLSH,    _______,    _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,    _______,    _______,    _______,   _______,   ALT_T(KC_F5),
                                                       _______,  _______,  _______
  ),
  
  [_ADJUST] = LAYOUT_reviung39(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                       _______,  XXXXXXX,  _______
  ),
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Copy, twice for Paste
  [TD_COPY_PASTE]  = ACTION_TAP_DANCE_DOUBLE(KC_COPY, KC_PASTE)
};

//Tri state allows momentary toggle of _ADJUST layer when 
//buttons are held to toggle _NAV_MEDIA and _NUM_SCHAR
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV_MEDIA, _NUM_SCHAR, _ADJUST);
}
