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

extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVE,
  _MOUSE,
  // vim layers
  _EDIT,
  _CMD,
  _CMD_G,
  _VISUAL
};

enum keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  BACKLIT,
  S_INSERT,
  S_APPEND,
  APPEND,
  VISUAL,
  VISUAL_LINE,
  CANCEL_VISUAL,
  YANK,
  YANK_LINE,
  INS_LINE,
  APPEND_LINE,
  PASTE,
  PASTE_BEFORE
};

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
  {TG(_MOUSE), TG(_CMD),  KC_LALT, KC_LGUI, OSL(_LOWER),   KC_SPC,  KC_SPC,  OSL(_RAISE),   KC_LGUI, KC_LALT, _______,   TG(_MOVE)}
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
  {TO(_QWERTY), _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______},
  {_______,     _______, LGUI(KC_LBRC), LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), LGUI(KC_RBRC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* mouse layer
 */
[_MOUSE] = {
  {TO(_QWERTY), _______, _______, KC_MS_UP, _______, _______, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, _______, _______  },
  {_______,     _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* vim edit mode. just has an escape -> cmd key */
[_EDIT] = {
  {TO(_QWERTY), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {TO(_CMD),    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* vim command layer. Moslty movement commands
 */
[_CMD] = {
  {TO(_QWERTY), _______, _______, LALT(KC_RIGHT), _______, _______, OSL(_CMD_G), KC_PGUP, TO(_EDIT), APPEND_LINE, PASTE, _______},
  {_______,     APPEND, _______, KC_PGDN, _______, OSL(_CMD_G), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______},
  {MO(_CMD_G),     _______, _______, _______, VISUAL, LALT(KC_LEFT), _______, _______, _______, _______, _______, MO(_CMD_G)},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
/* enable gg, ge (like G) */
[_CMD_G] = {
  {TO(_QWERTY), _______, _______, KC_END, _______, _______, YANK_LINE, _______, S_INSERT, INS_LINE, PASTE_BEFORE, _______},
  {_______,     S_APPEND, _______, _______, _______, KC_HOME, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, VISUAL_LINE, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
/* visual mode, wooo */
[_VISUAL] = {
  {TO(_QWERTY), _______, _______, _______, _______, _______, YANK, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

bool g_last_yank_was_line = false;
#define KD if(record->event.pressed)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      KD {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      KD {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      KD {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case APPEND:
      KD {
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        layer_off(_CMD_G);
        layer_off(_CMD);
        layer_on(_EDIT);
      }
      return false;
      break;
    case S_APPEND:
      KD {
        register_code(KC_LGUI);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LGUI);
        layer_off(_CMD_G);
        layer_off(_CMD);
        layer_on(_EDIT);
      }
      return false;
      break;
    case S_INSERT:
      KD {
        register_code(KC_LGUI);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LGUI);
        layer_off(_CMD_G);
        layer_off(_CMD);
        layer_on(_EDIT);
      };
      return false;
      break;
    case VISUAL:
      KD {
        register_code(KC_LSHIFT);
        layer_on(_VISUAL);
        layer_off(_CMD_G);
        g_last_yank_was_line = false;
      }
      return false;
      break;
    case VISUAL_LINE:
      KD {
        register_code(KC_LGUI);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        register_code(KC_LSHIFT);
        register_code(KC_RIGHT);
        unregister_code(KC_LGUI);
        layer_on(_VISUAL);
        layer_off(_CMD_G);
        g_last_yank_was_line = true;
      }
      return false;
      break;
    case YANK:
      KD {
        unregister_code(KC_LSHIFT);
        register_code(KC_LGUI);
        register_code(KC_C);
        unregister_code(KC_C);
        unregister_code(KC_LGUI);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        layer_off(_VISUAL);
        layer_off(_CMD_G);
        layer_on(_CMD);
      }
      return false;
      break;
    case YANK_LINE:
      KD {
        //cmd-left, shift-cmd-right, cmd-c, right
        register_code(KC_LGUI);

        register_code(KC_LEFT);
        unregister_code(KC_LEFT);

        register_code(KC_LSFT);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LSHIFT);

        register_code(KC_C);
        unregister_code(KC_C);

        unregister_code(KC_LGUI);

        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);

        layer_off(_VISUAL);
        layer_off(_CMD_G);
        layer_on(_CMD);
      }
      return false;
      break;
    case INS_LINE:
      KD {
        // cmd-left, return, up
        register_code(KC_LGUI);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LGUI);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
        register_code(KC_UP);
        unregister_code(KC_UP);
        layer_off(_CMD_G);
        layer_off(_CMD);
        layer_on(_EDIT);
      }
      return false;
      break;
    case APPEND_LINE:
      KD {
        // cmd-left, down, return
        register_code(KC_LGUI);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LGUI);
        register_code(KC_DOWN);
        unregister_code(KC_DOWN);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
        layer_off(_CMD_G);
        layer_off(_CMD);
        layer_on(_EDIT);
      }
      return false;
      break;
    case PASTE:
      KD {
        if(g_last_yank_was_line) {
          // cmd-left, down
          register_code(KC_LGUI);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
          unregister_code(KC_LGUI);
          register_code(KC_DOWN);
          unregister_code(KC_DOWN);
          g_last_yank_was_line = false;
        }
        unregister_code(KC_LSHIFT);
        register_code(KC_LGUI);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LGUI);
        layer_off(_CMD_G);
        layer_off(_VISUAL);
      }
      return false;
      break;
    case PASTE_BEFORE:
      KD {
        if(g_last_yank_was_line) {
          // cmd-left
          register_code(KC_LGUI);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
          unregister_code(KC_LGUI);
          g_last_yank_was_line = false;
        }
        unregister_code(KC_LSHIFT);
        register_code(KC_LGUI);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LGUI);
        layer_off(_CMD_G);
        layer_off(_VISUAL);
      }
      return false;
      break;
    case CANCEL_VISUAL:
      KD {
        g_last_yank_was_line = false;
        unregister_code(KC_LSHIFT);
        register_code(KC_ESCAPE);
        unregister_code(KC_ESCAPE);
        layer_off(_CMD_G);
        layer_off(_VISUAL);
      }
      return false;
      break;
  }
  return true;
}

// void matrix_scan_user(void)
// {
//   LEADER_DICTIONARY()
//   {
//     leading = false;
//     leader_end();
//     SEQ_ONE_KEY(KC_G)
//     {
//       register_code(KC_HOME);
//       unregister_code(KC_HOME);
//       // SEND_STRING(SS_TAP(X_HOME));
//     }

//     SEQ_ONE_KEY(KC_E)
//     {
//       register_code(KC_END);
//       unregister_code(KC_END);
//       // SEND_STRING(SS_TAP(X_END));
//     }
//   }
// }
