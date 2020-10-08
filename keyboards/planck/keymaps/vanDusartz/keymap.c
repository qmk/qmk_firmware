/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Useful Command Lines
 * make planck/rev5:vandusartz
 *
*/

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _MACQWERTY,
  _PCQWERTY,
  _SYM,
  _MCMACNUM,
  _PCMACNUM,
  _FUNAV
};

enum planck_keycodes {
  MACQWERTY = SAFE_RANGE,
  PCQWERTY,
  SYM,
  MCMACNUM,
  PCMACNUM,
  FUNAV,
  MCGSRCH,  // Mac Ctrl-c, Ctrl-t, Ctrl-v, Enter (Google Search)
  PCGSRCH,  // PC Ctrl-c, Ctrl-t, Ctrl-v, Enter (Google Search)
  MCLNUP,   // Mac Line Up (Moves Line Up)
  PCLNUP,   // PC Line Up (Moves Line Up)
  MCLNDN,   // Mac Line Down (Moves Line Down)
  PCLNDN,   // PC Line Down (Moves Line Down)
  SCRSHT    // Pastes printscreen into paint
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Mac Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   q  |   w  |   e  |   r  |   t  |      |PrtScn|   y  |   u  |   i  |   o  |   p  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   a  |   s  |   d  |   f  |   g  |      |      |   h  |   j  |   k  |   l  |   ;  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   z  |   x  |   c  |   v  |   b  | Esc  |      |   n  |   m  |   ,  |   .  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Space | Ctrl | Alt  | GUI  |Shift | Bksp | Tab  |Space |Enter | Caps |VolDn |VolUp |
 * `-----------------------------------------------------------------------------------'
 * hold down                           MacNum  FuNav         SYM
 */
[_MACQWERTY] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,              KC_PSCR,            KC_Y,   KC_U,             KC_I,    KC_O,    KC_P},
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,              XXXXXXX,            KC_H,   KC_J,             KC_K,    KC_L,    KC_SCLN},
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,               XXXXXXX,            KC_N,   KC_M,             KC_COMM, KC_DOT,  KC_QUOT},
  {KC_SPC,  KC_LCTL, KC_LALT, KC_LGUI, KC_RSFT, LT(_MCMACNUM, KC_BSPC), LT(_FUNAV, KC_TAB), KC_SPC, LT(_SYM, KC_ENT), KC_CAPS, KC_VOLD, KC_VOLU}
},

/* PC Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   q  |   w  |   e  |   r  |   t  |      |ScrSht|   y  |   u  |   i  |   o  |   p  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   a  |   s  |   d  |   f  |   g  |      |      |   h  |   j  |   k  |   l  |   ;  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   z  |   x  |   c  |   v  |   b  | Esc  |      |   n  |   m  |   ,  |   .  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Space | GUI  | Alt  | Ctrl |Shift | Bksp | Tab  |Space |Enter | Caps |VolDn |VolUp |
 * `-----------------------------------------------------------------------------------'
 * hold down                           MacNum  FuNav         SYM
 */
[_PCQWERTY] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,              SCRSHT,             KC_Y,   KC_U,             KC_I,    KC_O,    KC_P},
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,              XXXXXXX,            KC_H,   KC_J,             KC_K,    KC_L,    KC_SCLN},
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,               XXXXXXX,            KC_N,   KC_M,             KC_COMM, KC_DOT,  KC_QUOT},
  {KC_SPC,  KC_LGUI, KC_LALT, KC_LCTL, KC_RSFT, LT(_PCMACNUM, KC_BSPC), LT(_FUNAV, KC_TAB), KC_SPC, LT(_SYM, KC_ENT), KC_CAPS, KC_VOLD, KC_VOLU}
},

/* SYM
 * ,------------------------------------------------------------------------------------.
 * |      |   =  |   _  |   $   |      |      |      |      |   &  |   {  |   }  |  |   |
 * |------+------+------+-------+------+------+------+------+------+------+------+------|
 * |      |   !  |   @  |   #   |      |      |      |      |   ?  |   (  |   )  |  ~   |
 * |------+------+------+-------+------+------|-------------+------+------+------+------|
 * |      |   <  |   >  |   %   |      |      |      |      |   \  |   [  |   ]  |  ^   |
 * |------+------+------+-------+------+------+------+------+------+------+------+------|
 * |      |      |      |       |      |      |      |      | XXXX |      |      |      |
 * `------------------------------------------------------------------------------------'
 */
[_SYM] = {
  {_______, KC_EQL,  KC_UNDS, KC_DLR,  _______, _______, _______, _______, KC_AMPR, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_EXLM, KC_AT,   KC_HASH, _______, _______, _______, _______, KC_QUES, KC_LPRN, KC_RPRN, KC_TILD},
  {_______, KC_LT,   KC_GT,   KC_PERC, _______, _______, _______, _______, KC_BSLS, KC_LBRC, KC_RBRC, KC_CIRC},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Mac Macro-Num
 * ,-----------------------------------------------------------------------------------.
 * | PC Mo|      |      |      |      |      |      |   /  |   7  |   8  |   9  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | MacMo| LnDn | LnDn |GSrch |      |      |      |   .  |   4  |   5  |   6  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   ,  |   1  |   2  |   3  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | XXXX |      |   =  |   0  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MCMACNUM] = {
  {PCQWERTY,  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7, KC_8,    KC_9,    KC_ASTR},
  {MACQWERTY, MCLNDN,  MCLNUP,  MCGSRCH, _______, _______, _______, KC_DOT,  KC_4, KC_5,    KC_6,    KC_MINS},
  {_______,   _______, _______, _______, _______, _______, _______, KC_COMM, KC_1, KC_2,    KC_3,    KC_PLUS},
  {_______,   _______, _______, _______, _______, _______, _______, KC_EQL,  KC_0, _______, _______, _______}
},

/* PC Macro-Num
 * ,-----------------------------------------------------------------------------------.
 * | PC Mo|      |      |      |      |      |      |   /  |   7  |   8  |   9  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | MacMo| LnDn | LnDn |GSrch |      |      |      |   .  |   4  |   5  |   6  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   ,  |   1  |   2  |   3  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | XXXX |      |   =  |   0  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PCMACNUM] = {
  {PCQWERTY,  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7, KC_8,    KC_9,    KC_ASTR},
  {MACQWERTY, PCLNDN,  PCLNUP,  PCGSRCH, _______, _______, _______, KC_DOT,  KC_4, KC_5,    KC_6,    KC_MINS},
  {_______,   _______, _______, _______, _______, _______, _______, KC_COMM, KC_1, KC_2,    KC_3,    KC_PLUS},
  {_______,   _______, _______, _______, _______, _______, _______, KC_EQL,  KC_0, _______, _______, _______}
},

/* Fu-Nav
 * ,-----------------------------------------------------------------------------------.
 * |  F12 |  F9  |  F8  |  F7  |      |      |      |      |MLeft |MDown | MUp  |MRight|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F11 |  F6  |  F5  |  F4  |      |      |      |      | Left | Down |  Up  |Right |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F10 |  F3  |  F2  |  F1  |      |      |      |      | Home | PgDn | PgUp | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Shift | Del  | XXXX |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNAV] = {
  {KC_F12,  KC_F9,   KC_F8,   KC_F7,   _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R},
  {KC_F11,  KC_F6,   KC_F5,   KC_F4,   _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT},
  {KC_F10,  KC_F3,   KC_F2,   KC_F1,   _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END},
  {_______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______}
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACQWERTY:
      if (record->event.pressed) {
        print("mode just switched to mac qwerty\n");
        set_single_persistent_default_layer(_MACQWERTY);
      }
      return false;
      break;
    case PCQWERTY:
      if (record->event.pressed) {
        print("mode just switched to pc qwerty\n");
        set_single_persistent_default_layer(_PCQWERTY);
      }
      return false;
      break;
    case MCMACNUM:
      if (record->event.pressed) {
        layer_on(_MCMACNUM);
      } else {
        layer_off(_MCMACNUM);
      }
      return false;
      break;
    case PCMACNUM:
      if (record->event.pressed) {
        layer_on(_PCMACNUM);
      } else {
        layer_off(_PCMACNUM);
      }
      return false;
      break;
    case FUNAV:
      if (record->event.pressed) {
        layer_on(_FUNAV);
      } else {
        layer_off(_FUNAV);
      }
      return false;
      break;
    case SYM:
      if (record->event.pressed) {
        layer_on(_SYM);
      } else {
        layer_off(_SYM);
      }
      return false;
      break;
    case MCGSRCH:
      if (record->event.pressed){
        SEND_STRING(
          SS_LGUI("c")
          SS_DELAY(50)
          SS_LGUI("t")
          SS_DELAY(100)
          SS_LGUI("v")
          SS_TAP(X_ENTER)
        );
      }
      return false;
      break;
    case PCGSRCH:
      if (record->event.pressed){
        SEND_STRING(
          SS_LCTRL("c")
          SS_DELAY(50)
          SS_LCTRL("t")
          SS_DELAY(100)
          SS_LCTRL("v")
          SS_TAP(X_ENTER)
        );
      }
      return false;
      break;
    case MCLNUP: // LNUP and LNDN really only work in text editors
      if (record->event.pressed){
        SEND_STRING(
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_RIGHT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_DOWN(X_RSHIFT)  // SS_RSFT(X_END) or SS_RLSFT(X_HOME) do not work at all.
          SS_DELAY(20)
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_UP(X_RSHIFT)
          SS_DELAY(20)
          SS_LGUI("x")
          SS_DELAY(20)
          SS_TAP(X_DELETE)
          SS_DELAY(20)
          SS_TAP(X_UP)
          SS_DELAY(20)
          SS_TAP(X_ENTER)
          SS_DELAY(20)
          SS_TAP(X_UP)
          SS_DELAY(20)
          SS_LGUI("v")
        );
      }
      return false;
      break;
    case PCLNUP: // LNUP and LNDN really only work in text editors
      if (record->event.pressed){
        SEND_STRING(
          SS_TAP(X_END)
          SS_DOWN(X_LSHIFT)  // SS_RSFT(X_END) or SS_RLSFT(X_HOME) do not work at all.
          SS_TAP(X_HOME)
          SS_TAP(X_HOME)
          SS_UP(X_LSHIFT)
          SS_LCTRL("x")
          SS_TAP(X_DELETE)
          SS_TAP(X_UP)
          SS_TAP(X_ENTER)
          SS_TAP(X_UP)
          SS_LCTRL("v")
        );
      }
      return false;
      break;
    case MCLNDN: // line down needs to use delete instead of backspace in case you are on the top line.
      if (record->event.pressed){
        SEND_STRING(
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_RIGHT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_DOWN(X_RSHIFT)
          SS_DELAY(20)
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_UP(X_RSHIFT)
          SS_DELAY(20)
          SS_LGUI("x")
          SS_DELAY(20)
          SS_TAP(X_DELETE)
          SS_DELAY(20)
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_RIGHT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_ENTER)
          SS_DELAY(20)
          SS_DOWN(X_RSHIFT)
          SS_DELAY(20)
          SS_DOWN(X_LGUI)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_TAP(X_LEFT)
          SS_DELAY(20)
          SS_UP(X_LGUI)
          SS_DELAY(20)
          SS_UP(X_RSHIFT)
          SS_DELAY(20)
          SS_LGUI("v")
        );
      }
      return false;
      break;
    case PCLNDN: // line down needs to use delete instead of backspace in case you are on the top line.
      if (record->event.pressed){
        SEND_STRING(SS_TAP(X_END)
          SS_DOWN(X_LSHIFT)
          SS_TAP(X_HOME)
          SS_TAP(X_HOME)
          SS_UP(X_LSHIFT)
          SS_LCTRL("x")
          SS_TAP(X_DELETE)
          SS_TAP(X_END)
          SS_TAP(X_ENTER)
          SS_DOWN(X_LSHIFT)
          SS_TAP(X_HOME)
          SS_UP(X_LSHIFT)
          SS_LCTRL("v")
        );
      }
      return false;
      break;
    case SCRSHT:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_PSCREEN) SS_LGUI("r"));
        _delay_ms(500);
        SEND_STRING("mspaint" SS_TAP(X_ENTER));
        _delay_ms(500);
        SEND_STRING(SS_LCTRL("v"));
      }
      return false;
      break;
  }
  return true;
}


