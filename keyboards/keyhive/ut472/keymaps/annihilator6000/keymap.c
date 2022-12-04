/* Copyright 2018 Carlos Filoteo
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

#define LT3_TAB LT(3, KC_TAB)

enum ut472_layers {
  _QWERTY,
  _WORKMAN,
  _COLEMAK,
  _COLEMAK_MOD_DH,
  _DVORAK,
  _LOWER,
  _RAISE,
  _TAB,
  _ADJUST
};

enum ut472_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
  COLEMAK,
  COLEMAK_MOD_DH,
  DVORAK
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer - QWERTY
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * |Tab/L3|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '  |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Sh/En|
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt | Gui | App |  L2  |   Space   |  L1  | Left| Down|  Up |Right|
   * `-------------------------------------------------------------------------'
   */
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LT3_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  LOWER,      KC_SPC,        RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

  /* Workman
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  D  |  R  |  W  |  B  |  J  |  F  |  U  |  P  |  ;  |Bspace |
   * |-------------------------------------------------------------------------+
   * |Tab/L3|  A  |  S  |  H  |  T  |  G  |  Y  |  N  |  E  |  O  |  I  |   '  |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  M  |  C  |  V  |  K  |  L  |  ,  |  .  |  /  |Sh/En|
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt | Gui | App |  L2  |   Space   |  L1  | Left| Down|  Up |Right|
   * `-------------------------------------------------------------------------'
   */
[_WORKMAN] = LAYOUT(
  KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,    KC_BSPC,
  LT3_TAB, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  LOWER,      KC_SPC,        RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

  /* Colemak
   * ,---------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |   Bksp  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+---------|
   * |Tab/L3|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |    "   |
   * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  |  /  | Sh/En |
   * |-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-------|
   * | Ctrl| Alt | GUI | App |  L2  |   Space   | L1 | Left | Down |  Up  |Right |
   * `---------------------------------------------------------------------------'
   */
[_COLEMAK] = LAYOUT(
  KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  LT3_TAB, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  LOWER,      KC_SPC,        RAISE,  KC_LEFT,   KC_DOWN, KC_UP,   KC_RGHT
),

  /* Colemak Mod-DH
   * https://colemakmods.github.io/mod-dh/keyboards.html
   * ,---------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  F  |  P  |  B  |  J  |  L  |  U  |  Y  |  ;  |   Bksp  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+---------|
   * |Tab/L3|  A  |  R  |  S  |  T  |  G  |  K  |  N  |  E  |  I  |  O  |    '   |
   * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
   * | Shift |  X  |  C  |  D  |  V  |  Z  |  M  |  H  |  ,  |  .  |  /  | Sh/En |
   * |-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-------|
   * | Ctrl| Alt | GUI | App |  L2  |   Space   | L1 | Left | Down |  Up  |Right |
   * `---------------------------------------------------------------------------'
   */
[_COLEMAK_MOD_DH] = LAYOUT(
  KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  LT3_TAB, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  LOWER,      KC_SPC,        RAISE,  KC_LEFT,   KC_DOWN, KC_UP,  KC_RGHT
),

  /* Dvorak
   * ,--------------------------------------------------------------------------.
   * | Esc |  "  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |   Bksp |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------|
   * |Tab/L3|  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |   /   |
   * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-------|
   * | Shift |  ;  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |Sh/En |
   * |-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
   * | Ctrl| Alt | GUI | App |  L2  |   Space   | L1 | Left | Down |  Up |Right |
   * `--------------------------------------------------------------------------'
   */
[_DVORAK] = LAYOUT(
  KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
  LT3_TAB, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
  KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  LOWER,      KC_SPC,        RAISE,  KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT
),

  /* FN Layer 1 - LOWER
   * ,-------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  -  |  =  |  [  |  ]  |  \   |
   * |-------------------------------------------------------------------------+
   * |       | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */
[_LOWER] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELETE,
  _______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
  _______, _______, _______, KC_CAPS, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

  /* FN Layer 2 - RAISE
   * ,-------------------------------------------------------------------------.
   * |   ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  _  |  +  |  { |  }  |   |   |
   * |-------------------------------------------------------------------------+
   * |       | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */
[_RAISE] = LAYOUT(
  KC_TILDE, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_DELETE,
  _______, _______, _______, _______, _______, _______, _______, KC_UNDERSCORE, KC_PLUS, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, _______, _______, KC_CAPS, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

  /* FN Layer 3 - Hold Tab
   * ,-------------------------------------------------------------------------.
   * | Esc | Calc|Webhm| Mail| Comp|     |     |     |     |     |PrtSc|       |
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |     |     |     |     |      |
   * |-------------------------------------------------------------------------+
   * |       |    |     |     |     |     |     |     |     |     |      |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |MousL|MousD|MousU|MousR|
   * `-------------------------------------------------------------------------'
   */
[_TAB] = LAYOUT(
  KC_ESC,  KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,     _______,      _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R
),

  /* Adjust (L1 + L2)
   *                   v-----------------------RGB CONTROL---------------------v
   * ,--------------------------------------------------------------------------
   * |Reset|     |     | RGB |RGBMO|HUE+ |HUE- |SAT+ |SAT- |BRT+ |BRT- |   Del |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-------|
   * |      |     |     |     |     |     |Qwert|Wrkmn|ModDH|Colmk|Dvork|      |
   * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
   * |       |     |     |     |     |     |     |     |     |     |     |     |
   * |-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * | Dbg |     |     |     |      |           |      |     |     |     |     |
   * `-------------------------------------------------------------------------'
   */
[_ADJUST] = LAYOUT(
  QK_BOOT, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL,
  _______, _______, _______, _______, _______, _______, QWERTY,  WORKMAN, COLEMAK, COLEMAK_MOD_DH,   DVORAK,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  DEBUG,   _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
)
/* QWERTY    = H
   WORKMAN   = J
   COLEMAK   = K
     -MOD-DH = L
   DVORAK    = ; */
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
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case COLEMAK_MOD_DH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK_MOD_DH);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
  }
  return true;
}
