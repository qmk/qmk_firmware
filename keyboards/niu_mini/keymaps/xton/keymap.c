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
#include "action_layer.h"

LEADER_EXTERNS();

#define X_____X KC_NO

extern keymap_config_t keymap_config;


/************************************
 * helper foo
 ************************************/

#define PRESS(kc) register_code(kc)
#define RELEASE(kc) unregister_code(kc)

void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

void CMD(uint16_t keycode) {
  PRESS(KC_LGUI);
    TAP(keycode);
  RELEASE(KC_LGUI);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTRL);
    TAP(keycode);
  RELEASE(KC_LCTRL);
}

void SHIFT(uint16_t keycode) {
  PRESS(KC_LSHIFT);
    TAP(keycode);
  RELEASE(KC_LSHIFT);
}

void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

/************************************
 * states
 ************************************/

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVE,
  _MOUSE,
  // vim layers
  _EDIT,
  _CMD
};

enum keycodes {
  DUMMY = SAFE_RANGE,
  VIM_START, // bookend for vim states
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_G,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VS, // visual-line
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_PERIOD, // to support indent/outdent
  VIM_COMMA,  // and toggle comments
  VIM_SHIFT, // avoid side-effect of supporting real shift.
  VIM_ESC // bookend
};

/************************************
 * keymaps!
 ************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  [;] |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|  Esc | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,           KC_W,    KC_E,    KC_R,          KC_T,    KC_Y,    KC_U,          KC_I,    KC_O,    KC_P,              KC_BSPC},
  {LCTL_T(KC_ESC), LT(_MOVE,KC_A), KC_S,    KC_D,    KC_F,          KC_G,    KC_H,    KC_J,          KC_K,    KC_L,    LT(_MOVE,KC_SCLN), KC_QUOT},
  {KC_LSFT, KC_Z,           KC_X,    KC_C,    KC_V,          KC_B,    KC_N,    KC_M,          KC_COMM, KC_DOT,  KC_SLSH,   RSFT_T(KC_ENT) },
  {TG(_MOUSE), VIM_START,  KC_LALT, KC_LGUI, OSL(_LOWER),   KC_SPC,  KC_SPC,  OSL(_RAISE),   KC_LGUI, KC_LALT, X_____X,   TG(_MOVE)}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_BSPC},
  {KC_DEL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME, KC_END,  _______},
  {_______, _______, _______, _______, _______, _______, _______, OSL(_ADJUST),    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Del |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSPC},
  {KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_PGDN, _______},
  {RGB_TOG, _______, _______, _______, OSL(_ADJUST), _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},


/* movement layer (hold semicolon)
 */
[_MOVE] = {
  {TO(_QWERTY), X_____X, X_____X, X_____X, X_____X, X_____X, KC_HOME, KC_PGDN, KC_PGUP, KC_END, X_____X, X_____X},
  {_______,     X_____X, LGUI(KC_LBRC), LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), LGUI(KC_RBRC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, X_____X, X_____X},
  {_______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______},
  {X_____X,     _______, _______, _______, _______, X_____X, X_____X, _______, _______, _______, _______, _______}
},

/* mouse layer
 */
[_MOUSE] = {
  {TO(_QWERTY), X_____X, X_____X, KC_MS_UP, X_____X, X_____X, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, X_____X, X_____X  },
  {_______,     X_____X, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, X_____X, X_____X, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, X_____X, X_____X},
  {_______,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______},
  {_______,     _______, _______, _______, _______, X_____X, X_____X, _______, _______, _______, _______, _______}
},

/* vim edit mode. just has an escape -> _CMD key */
[_EDIT] = {
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {VIM_START,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* vim command layer.
 */
[_CMD] = {
  {TO(_QWERTY), X_____X, VIM_W, VIM_E, X_____X, X_____X, VIM_Y, VIM_U, VIM_I, VIM_O, VIM_P, X_____X},
  {VIM_ESC,    VIM_A, VIM_S, VIM_D, X_____X, VIM_G, VIM_H, VIM_J, VIM_K, VIM_L, X_____X, X_____X},
  {VIM_SHIFT,     X_____X, VIM_X, VIM_C, VIM_V, VIM_B, X_____X, X_____X, VIM_COMMA, VIM_PERIOD, X_____X, VIM_SHIFT},
  {X_____X,     X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X}
}

};

uint16_t vstate = VIM_START;
bool yank_was_lines = false;
bool SHIFTED = false;

void vim_reset(void) {
  vstate = VIM_START;
  SHIFTED = false;
  yank_was_lines = false;
}

#define EDIT vstate = VIM_START; layer_on(_EDIT); layer_off(_CMD)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (VIM_START <= keycode && keycode <= VIM_ESC) {
    if(keycode == VIM_SHIFT) {
      SHIFTED = record->event.pressed;
      return false;
    }

    if (record->event.pressed) {
      if(keycode == VIM_START) {
        // entry from anywhere
        layer_on(_CMD);
        vstate = VIM_START;
        return false;
      }
      switch(vstate) {
        case VIM_START:
          switch(keycode){
            /*****************************
             * ground state
             *****************************/
            case VIM_A:
              if(SHIFTED) {
                CMD(KC_RIGHT);
              } else {
                TAP(KC_RIGHT);
              }
              EDIT;
              break;
            case VIM_B:
              // ALT(KC_LEFT);
              PRESS(KC_LALT);
              PRESS(KC_LEFT);
              break;
            case VIM_C:
              if(SHIFTED) {
                CTRL(KC_K);
                EDIT;
              } else {
                vstate = VIM_C;
              }
              break;
            case VIM_D:
              if(SHIFTED) {
                TAP(KC_K);
              } else {
                vstate = VIM_D;
              }
              break;
            case VIM_E:
              // ALT(KC_RIGHT);
              PRESS(KC_LALT);
              PRESS(KC_RIGHT);
              break;
            case VIM_G:
              if(SHIFTED) {
                TAP(KC_END);
              } else {
                vstate = VIM_G;
              }
              break;
            case VIM_H:
              // TAP(KC_LEFT);
              PRESS(KC_LEFT);
              break;
            case VIM_I:
              if(SHIFTED){
                CTRL(KC_A);
              }
              EDIT;
              break;
            case VIM_J:
              if(SHIFTED) {
                CMD(KC_RIGHT);
                TAP(KC_DEL);
              } else {
                PRESS(KC_DOWN);
                // TAP(KC_DOWN);
              }
              break;
            case VIM_K:
              // TAP(KC_UP);
              PRESS(KC_UP);
              break;
            case VIM_L:
              // TAP(KC_RIGHT);
              PRESS(KC_RIGHT);
              break;
            case VIM_O:
              if(SHIFTED) {
                // CMD(KC_LEFT);
                CTRL(KC_A);
                TAP(KC_ENTER);
                TAP(KC_UP);
                EDIT;
              } else {
                // CMD(KC_RIGHT);
                CTRL(KC_E);
                TAP(KC_ENTER);
                EDIT;
              }
              break;
            case VIM_P:
              if(SHIFTED) {
                CTRL(KC_A);
                CMD(KC_V);
              } else {
                if(yank_was_lines) {
                  CTRL(KC_E);
                  TAP(KC_RIGHT);
                  CMD(KC_V);
                } else {
                  CMD(KC_V);
                }
              }
              break;
            case VIM_S:
              // s for substitute?
              if(SHIFTED) {
                CTRL(KC_A);
                CTRL(KC_K);
                EDIT;
              } else {
                SHIFT(KC_RIGHT);
                CMD(KC_X);
                EDIT;
              }
              break;
            case VIM_U:
              if(SHIFTED) {
                PRESS(KC_LSFT);
                  CMD(KC_Z);
                RELEASE(KC_LSHIFT);
              } else {
                CMD(KC_Z);
              }
              break;
            case VIM_V:
              if(SHIFTED) {
                CTRL(KC_A);
                SHIFT(KC_DOWN);
                vstate = VIM_VS;
              } else {
                vstate = VIM_V;
              }
              break;
            case VIM_W:
              PRESS(KC_LALT);
                TAP(KC_RIGHT);
                TAP(KC_RIGHT);
                TAP(KC_LEFT);
              RELEASE(KC_LALT);
              break;
            case VIM_X:
              // SHIFT(KC_RIGHT);
              // CMD(KC_X);
              PRESS(KC_DEL);
              break;
            case VIM_Y:
              if(SHIFTED) {
                CTRL(KC_A);
                PRESS(KC_LSHIFT);
                  CMD(KC_RIGHT);
                RELEASE(KC_LSHIFT);
                CMD(KC_C);
                TAP(KC_LEFT);
              } else {
                vstate = VIM_Y;
              }
              break;
            case VIM_COMMA:
              if(SHIFTED) {
                // indent
                CMD(KC_LBRACKET);
              } else {
                // toggle comment
                CMD(KC_SLASH);
              }
              break;
            case VIM_PERIOD:
              if(SHIFTED) {
                // outdent
                CMD(KC_RBRACKET);
              }
              break;
          }
          break;
        case VIM_C:
          /*****************************
           * c-  ...for change. I never use this...
           *****************************/
          switch(keycode) {
            case VIM_B:
              PRESS(KC_LALT);
                SHIFT(KC_LEFT); // select to start of this word
              RELEASE(KC_LALT);
              CMD(KC_X);
              EDIT;
              break;
            case VIM_C:
              CTRL(KC_A);
              CTRL(KC_K);
              EDIT;
              break;
            case VIM_E:
              PRESS(KC_LALT);
                SHIFT(KC_RIGHT); // select to end of this word
              RELEASE(KC_LALT);
              CMD(KC_X);
              EDIT;
              break;
            case VIM_H:
              SHIFT(KC_LEFT);
              CMD(KC_X);
              EDIT;
              break;
            case VIM_I:
              vstate = VIM_CI;
              break;
            case VIM_J:
              // delete this line and the next line down
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              CTRL(KC_K);
              CTRL(KC_K);
              EDIT;
              break;
            case VIM_K:
              // delete this line and the one above.
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              TAP(KC_UP);
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              EDIT;
              break;
            case VIM_L:
              SHIFT(KC_RIGHT);
              CMD(KC_X);
              EDIT;
              break;
            case VIM_W:
              PRESS(KC_LALT);
              SHIFT(KC_RIGHT); // select to end of this word
              SHIFT(KC_RIGHT); // select to end of next word
              SHIFT(KC_LEFT);  // select to start of next word
              RELEASE(KC_LALT);
              CMD(KC_X); // delete selection
              EDIT;
              break;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_CI:
          /*****************************
           * ci-  ...change inner word
           *****************************/
          switch(keycode) {
            case VIM_W:
              ALT(KC_LEFT);
              PRESS(KC_LSHIFT);
                ALT(KC_RIGHT);
              RELEASE(KC_LSHIFT);
              CMD(KC_X);
              EDIT;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_D:
          /*****************************
           * d-  ...delete stuff
           *****************************/
          switch(keycode) {
            case VIM_B:
              PRESS(KC_LALT);
                SHIFT(KC_LEFT); // select to start of this word
              RELEASE(KC_LALT);
              CMD(KC_X);
              vstate = VIM_START;
              break;
            case VIM_D:
              CTRL(KC_A);
              CTRL(KC_K);
              vstate = VIM_START;
              break;
            case VIM_E:
              PRESS(KC_LALT);
                SHIFT(KC_RIGHT); // select to end of this word
              RELEASE(KC_LALT);
              CMD(KC_X);
              vstate = VIM_START;
              break;
            case VIM_H:
              SHIFT(KC_LEFT);
              CMD(KC_X);
              vstate = VIM_START;
              break;
            case VIM_I:
              vstate = VIM_DI;
              break;
            case VIM_J:
              // delete this line and the next line down
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              CTRL(KC_K);
              CTRL(KC_K);
              vstate = VIM_START;
              break;
            case VIM_K:
              // delete this line and the one above.
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              TAP(KC_UP);
              CTRL(KC_A);
              CTRL(KC_K);
              CTRL(KC_K);
              vstate = VIM_START;
              break;
            case VIM_L:
              SHIFT(KC_RIGHT);
              CMD(KC_X);
              vstate = VIM_START;
              break;
            case VIM_W:
              PRESS(KC_LALT);
              SHIFT(KC_RIGHT); // select to end of this word
              SHIFT(KC_RIGHT); // select to end of next word
              SHIFT(KC_LEFT);  // select to start of next word
              RELEASE(KC_LALT);
              CMD(KC_X); // delete selection
              vstate = VIM_START;
              break;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_DI:
          /*****************************
           * ci-  ...delete a word... FROM THE INSIDE!
           *****************************/
          switch(keycode) {
            case VIM_W:
              ALT(KC_LEFT);
              PRESS(KC_LSHIFT);
                ALT(KC_RIGHT);
              RELEASE(KC_LSHIFT);
              CMD(KC_X);
              vstate = VIM_START;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_V:
          /*****************************
           * visual!
           *****************************/
          switch(keycode) {
            case VIM_D:
            case VIM_X:
              CMD(KC_X);
              yank_was_lines = false;
              vstate = VIM_START;
              break;
            case VIM_B:
              PRESS(KC_LALT);
              PRESS(KC_LSHIFT);
              PRESS(KC_LEFT);
              // leave open for key repeat
              break;
            case VIM_E:
              PRESS(KC_LALT);
              PRESS(KC_LSHIFT);
              PRESS(KC_RIGHT);
              // leave open for key repeat
              break;
            case VIM_H:
              PRESS(KC_LSHIFT);
              PRESS(KC_LEFT);
              break;
            case VIM_I:
              vstate = VIM_VI;
              break;
            case VIM_J:
              PRESS(KC_LSHIFT);
              PRESS(KC_DOWN);
              break;
            case VIM_K:
              PRESS(KC_LSHIFT);
              PRESS(KC_UP);
              break;
            case VIM_L:
              PRESS(KC_LSHIFT);
              PRESS(KC_RIGHT);
              break;
            case VIM_W:
              PRESS(KC_LALT);
              SHIFT(KC_RIGHT); // select to end of this word
              SHIFT(KC_RIGHT); // select to end of next word
              SHIFT(KC_LEFT);  // select to start of next word
              RELEASE(KC_LALT);
              break;
            case VIM_Y:
              CMD(KC_C);
              TAP(KC_RIGHT);
              yank_was_lines = false;
              vstate = VIM_START;
              break;
            case VIM_V:
            case VIM_ESC:
              TAP(KC_RIGHT);
              vstate = VIM_START;
              break;
            default:
              // do nothing
              break;
          }
          break;
        case VIM_VI:
          /*****************************
           * vi-  ...select a word... FROM THE INSIDE!
           *****************************/
          switch(keycode) {
            case VIM_W:
              ALT(KC_LEFT);
              PRESS(KC_LSHIFT);
                ALT(KC_RIGHT);
              RELEASE(KC_LSHIFT);
              vstate = VIM_V;
            default:
              // ignore
              vstate = VIM_V;
              break;
          }
          break;
        case VIM_VS:
          /*****************************
           * visual line
           *****************************/
          switch(keycode) {
            case VIM_D:
            case VIM_X:
              CMD(KC_X);
              yank_was_lines = true;
              vstate = VIM_START;
              break;
            case VIM_J:
              PRESS(KC_LSHIFT);
              PRESS(KC_DOWN);
              break;
            case VIM_K:
              PRESS(KC_LSHIFT);
              PRESS(KC_UP);
              break;
            case VIM_Y:
              CMD(KC_C);
              yank_was_lines = true;
              TAP(KC_RIGHT);
              vstate = VIM_START;
              break;
            case VIM_V:
            case VIM_ESC:
              TAP(KC_RIGHT);
              vstate = VIM_START;
              break;
            default:
              // do nothing
              break;
          }
          break;
        case VIM_G:
          /*****************************
           * gg, and a grab-bag of other macros i find useful
           *****************************/
          switch(keycode) {
            case VIM_G:
              TAP(KC_HOME);
              break;
            // codes b
            case VIM_H:
              CTRL(KC_A);
              break;
            case VIM_J:
              PRESS(KC_PGDN);
              break;
            case VIM_K:
              PRESS(KC_PGUP);
              break;
            case VIM_L:
              CTRL(KC_E);
              break;
            default:
              // do nothing
              break;
          }
          vstate = VIM_START;
          break;
        case VIM_Y:
          /*****************************
           * just supporting yy for now...
           *****************************/
          switch(keycode) {
            case VIM_Y:
              break;
            default:
              // NOTHING
              break;
          }
          vstate = VIM_START;
          break;
      }
    } else {
      /************************
       * key release events
       ************************/
      clear_keyboard();
    }
    return false;
  } else {
    return true;
  }
}
