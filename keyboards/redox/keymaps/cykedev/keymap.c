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

#define SY_LBRC LT(_SYMBOL, KC_LBRC)
#define SY_RBRC LT(_SYMBOL, KC_RBRC)
#define SY_SPC  LT(_SYMBOL, KC_SPC)
#define A_COMM  LALT_T(KC_COMM)
#define A_DOT   LALT_T(KC_DOT)
#define ADJ     MO(_ADJUST)

enum layer_names {
    _QWERTY,
    _SYMBOL,
    _ADJUST
  };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  /* QWERTY
   * ,-----------------------------------------.                                    ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |                                    |   6  |   7  |   8  |   9  |   0  | Bsp  |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  Home |                    |  End  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |  SYM  |                    |  SYM  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|   [   |                    |   ]   |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  '----------------,  ,----------------'   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-----------------------------------------/   =   /  Bsp  /    \    +  \    -  \-----------------------------------------|
   * |  ADJ | Hypr |  Meh | Ctrl |    /  Alt  /-------/-------/      \-------\-------\  Alt  \    | Ctrl | PgUp | PgDn | ADJ  |
   * |      |      |      |      |   /   ,   /  Cmd  / Shift /        \ Shift \  SYM  \   .   \   |      |      |      |      |
   * `---------------------------'  '-------/       / Enter /          \ Enter \ Space \-------'  '---------------------------'
   *                                        '--------------'            '--------------'
   */
     KC_ESC  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                            KC_6   , KC_7   , KC_8    , KC_9    , KC_0    , KC_BSPC ,
     KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_HOME ,                         KC_END , KC_Y   , KC_U   , KC_I    , KC_O    , KC_P    , KC_BSLS ,
     KC_LCTL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , SY_LBRC ,                         SY_RBRC, KC_H   , KC_J   , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
     KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_PEQL , KC_BSPC   , KC_PPLS   , KC_MINS, KC_N   , KC_M   , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT ,
     ADJ     , KC_HYPR, KC_MEH ,KC_LCTL ,          A_COMM , KC_LGUI , SC_SENT   , SC_SENT   , SY_SPC , A_DOT  ,          KC_RCTL , KC_PGUP , KC_PGDN , ADJ
  ),

  [_SYMBOL] = LAYOUT(
  /* SYMBOL
   * ,-----------------------------------------.                                    ,-----------------------------------------.
   * |  ~   |  F1  |  F2  |  F3  |  F4  |  F5  |                                    |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * |      |   !  |   @  |   {  |   }  |   |  |   F11 |                    |  F12  |   &  |   +  |  up  |      |      |      |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * |      |   #  |   $  |   (  |   )  |   `  |       |                    |       |   =  | left | down | right|      |      |
   * |------+------+------+------+------+------|       |                    |       |------+------+------+------+------+------|
   * |      |   %  |   ^  |   [  |   ]  |   ~  '----------------,  ,----------------'   *  |   -  |      |      |      |      |
   * |-----------------------------------------/       /       /    \       \       \-----------------------------------------|
   * |      |      |      |      |    /       /-------/-------/      \-------\-------\       \    |      |      |      |      |
   * |      |      |      |      |   /       /       /       /        \       \       \       \   |      |      |      |      |
   * `---------------------------'  '-------/       /       /          \       \       \-------'  '---------------------------'
   *                                        '--------------'            '--------------'
   */
     KC_TILD , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_DEL  ,
     _______ , KC_EXLM , KC_AT   , KC_LCBR , KC_RCBR , KC_PIPE , KC_F11  ,                     KC_F12  , KC_AMPR , KC_PPLS , KC_UP   , XXXXXXX , XXXXXXX , XXXXXXX ,
     _______ , KC_HASH , KC_DLR  , KC_LPRN , KC_RPRN , KC_GRV  , _______ ,                     _______ , KC_PEQL , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX , XXXXXXX ,
     _______ , KC_PERC , KC_CIRC , KC_LBRC , KC_RBRC , KC_TILD , _______ , _______ , _______ , _______ , KC_ASTR , KC_MINS , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
     _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , XXXXXXX , XXXXXXX , _______
  ),

  [_ADJUST] = LAYOUT(
  /* ADJUST
   * ,-----------------------------------------.                                    ,-----------------------------------------.
   * | RST  |      |      |      |      |      |                                    |      |      |      |      |      | RST  |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * |      | Mod+ | H +  | S +  |  V + | Vol+ |       |                    |       |  B + |      |      |      |      |      |
   * |------+------+------+------+------+------|-------.                    ,-------|------+------+------+------+------+------|
   * |      | Mod- | H -  | S -  |  V - | Vol- |  RGB  |                    |       |  B - |  <<  | play |  >>  |      |      |
   * |------+------+------+------+------+------|       |                    |       |------+------+------+------+------+------|
   * |      |      |      |      |      | Mute '----------------,  ,----------------'      |      |      |      |      |      |
   * |-----------------------------------------/       /       /    \       \       \-----------------------------------------|
   * |      |      |      |      |    /       /-------/-------/      \-------\-------\       \    |      |      |      |      |
   * |      |      |      |      |   /       /       /       /        \       \       \       \   |      |      |      |      |
   * `---------------------------'  '-------/       /       /          \       \       \-------'  '---------------------------'
   *                                        '--------------'            '--------------'
   */
     EE_CLR  , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , EE_CLR  ,
     XXXXXXX , RGB_MOD  , RGB_HUI , RGB_SAI , RGB_VAI , KC_VOLU , XXXXXXX ,                     XXXXXXX , KC_BRIU , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
     XXXXXXX , RGB_RMOD , RGB_HUD , RGB_SAD , RGB_VAD , KC_VOLD , RGB_TOG ,                     XXXXXXX , KC_BRID , KC_MRWD , KC_MPLY , KC_MFFD , XXXXXXX , XXXXXXX ,
     XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , KC_MUTE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
     _______ , XXXXXXX  , XXXXXXX , XXXXXXX ,           XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,           XXXXXXX , XXXXXXX , XXXXXXX , _______
  )
};
