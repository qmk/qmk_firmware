// Copyright 2021 Christian Eiden, cykedev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#define CM_R    LCTL_T(KC_R)
#define CM_S    LALT_T(KC_S)
#define CM_T    LGUI_T(KC_T)

#define CM_N    RGUI_T(KC_N)
#define CM_E    RALT_T(KC_E)
#define CM_I    RCTL_T(KC_I)

#define QU_S    LCTL_T(KC_S)
#define QU_D    LALT_T(KC_D)
#define QU_F    LGUI_T(KC_F)

#define QU_J    RGUI_T(KC_J)
#define QU_K    RALT_T(KC_K)
#define QU_L    RCTL_T(KC_L)

#define SPC_L   LSFT_T(KC_SPC)
#define SPC_R   RSFT_T(KC_SPC)
#define ENT_L   LSFT_T(KC_ENT)
#define ENT_R   RSFT_T(KC_ENT)

#define UNDO    LGUI(KC_Z)
#define REDO    LGUI(KC_Y)
#define CUT     LGUI(KC_X)
#define COPY    LGUI(KC_C)
#define PASTE   LGUI(KC_V)
#define ALL     LGUI(KC_A)

#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)

#define QWERT   DF(_QWERTY)
#define COLEM   DF(_COLEMAK_DH)

enum layer_names {
  _COLEMAK_DH,
  _QWERTY,
  _RAISE,
  _LOWER,
  _ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK_DH] = LAYOUT_5x6_5(
  /* COLEMAK_DH
   * .-----------------------------------------.                                  .-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  Bsp |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |                                  |   J  |   L  |   U  |   Y  |   ;  |  \   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Del  |   A  |R /CTL|S /ALT|T /CMD|   G  |                                  |   M  |N /CMD|E /ALT|I /CTL|   O  |  '   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Shft |   Z  |   X  |   C  |   D  |   V  |                                  |   K  |   H  |   ,  |   .  |   /  | Shft |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    / RAISE /---------------.    .---------------\ LOWER \    |      |      |
   *               |      |      |   /       / Space / Enter /      \ Enter \ Space \       \   |      |      |
   *               '-------------'  '-------/ Shift / Shift /        \ Shift \ Shift \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /   =   / Home  /            \  End  \   -   \
   *                                     /   +   /       /              \       \   _   \
   *                                    '---------------'                '---------------'
   */
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
   KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSLS,
   KC_DEL , KC_A   , CM_R   , CM_S   , CM_T   , KC_G   ,                                     KC_M   , CM_N   , CM_E   , CM_I   , KC_O   , KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,                                     KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     XXXXXXX, XXXXXXX,          RAISE  , SPC_L , ENT_L   , ENT_R  , SPC_R  , LOWER  ,          XXXXXXX, XXXXXXX,
                                                         KC_EQL, KC_HOME , KC_END , KC_MINS
   ),
  [_QWERTY] = LAYOUT_5x6_5(
  /* QWERTY
   * .-----------------------------------------.                                  .-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  Bsp |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Del  |   A  |S /CTL|D /ALT|F /CMD|   G  |                                  |   H  |J /CMD|K /ALT|L /CTL|   ;  |  '   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Shft |   Z  |   X  |   C  |   V  |   B  |                                  |   N  |   M  |   ,  |   .  |   /  | Shft |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    / RAISE /---------------.    .---------------\ LOWER \    |      |      |
   *               |      |      |   /       / Space / Enter /      \ Enter \ Space \       \   |      |      |
   *               '-------------'  '-------/ Shift /       /        \       \ Shift \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /   =   / Home  /            \  End  \   -   \
   *                                     /   +   /       /              \       \   _   \
   *                                    '---------------'                '---------------'
   */
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
   KC_DEL , KC_A   , QU_S   , QU_D   , QU_F   , KC_G   ,                                     KC_H   , QU_J   , QU_K   , QU_L   , KC_SCLN, KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     XXXXXXX, XXXXXXX,          RAISE  , SPC_L , ENT_L   , ENT_R  , SPC_R  , LOWER  ,          XXXXXXX, XXXXXXX,
                                                         KC_EQL, KC_HOME , KC_END , KC_MINS
   ),
  [_RAISE] = LAYOUT_5x6_5(
  /* RAISE
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | Redo |      |      |      |      |                                  |   %  |   $  |  #   |   `  |      |  F12 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | All  | Cut  | Copy | Paste|      |                                  |   ^  |   /  |  *   |   ~  |  ?   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | Undo |      |      |      |      |                                  |      |   &  |  |   |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               | RST  |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       / Page  /            \  Page \       \
   *                                     /       /  Up   /              \  Down \       \
   *                                    '---------------'                '---------------'
   */
   _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
   XXXXXXX, REDO   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_PERC, KC_DLR , KC_HASH, KC_GRV , XXXXXXX, KC_F12 ,
   XXXXXXX, ALL    , CUT    , COPY   , PASTE  , XXXXXXX,                                     KC_CIRC, KC_SLSH, KC_ASTR, KC_TILD, KC_QUES, XXXXXXX,
   _______, UNDO   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_AMPR, KC_PIPE, XXXXXXX, XXXXXXX, _______,
                     QK_BOOT, XXXXXXX,          _______, _______, _______, _______, _______, _______,          XXXXXXX, XXXXXXX,
                                                         _______, KC_PGUP, KC_PGDN, _______
   ),
  [_LOWER] = LAYOUT_5x6_5(
  /* LOWER
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |   [  |   ]  |      |                                  |      |      |  up  |      |      |  F12 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |  Ins |  !   |  @   |   (  |   )  |      |                                  |      | left | down | rght |  ?   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |   {  |   }  |      |                                  |      |      |      |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      | RST  |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       / Page  /            \  Page \       \
   *                                     /       /  Up   /              \  Down \       \
   *                                    '---------------'                '---------------'
   */
   _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
   XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, KC_F12 ,
   KC_INS , KC_EXLM, KC_AT  , KC_LPRN, KC_RPRN, XXXXXXX,                                     XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUES, XXXXXXX,
   _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                     XXXXXXX, XXXXXXX,          _______, _______, _______, _______, _______, _______,          XXXXXXX, QK_BOOT,
                                                         _______, KC_PGUP, KC_PGDN, _______
   ),
  [_ADJUST] = LAYOUT_5x6_5(
  /* ADJUST
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |      |      |      |      | QWERT|                                  |COLEM |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |  V+  |                                  |  B + |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |  V-  |                                  |  B - |  <<  | play |  >>  |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      | Mute |                                  |      |      |      |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       /       /            \       \       \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERT  ,                                     COLEM  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,                                     KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,                                     KC_BRID, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX ,
                                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
   )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SPC_L:
      return true;
   case SPC_R:
      return false;
   case ENT_L:
      return true;
   case ENT_R:
      return true;
    default:
      return false;
  }
}

// Flexible macOS-friendly Grave Escape
// https://docs.qmk.fm/#/feature_key_overrides?id=flexible-macos-friendly-grave-escape

const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRAVE));
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, KC_GRAVE);

const key_override_t **key_overrides = (const key_override_t *[]){
    &tilde_esc_override,
    &grave_esc_override,
    NULL
};
