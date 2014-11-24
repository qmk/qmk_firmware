/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "util.h"
#include "keymap.h"




/* PC-9801-98-S02   Raku Raku keyboard(Luckyboard) Normal Mode
  ,---------------------------------------------------------------.
  | 60| 61| 62| 63| 64| 65| 66| 67| 68| 69| 6A| 6B| 36| 37| 3F| 3E|
  `---------------------------------------------------------------'
  ,---------------------------------------------------------------.
  |    00| 01| 02| 03| 04| 05|  58|  71| 06| 07| 08| 09| 0A|    0E|
  |---------------------------------------------------------------|
  |   0F| 10| 11| 12| 13| 14|    3A     | 15| 16| 17| 18| 19|   1C|
  |---------------------------------------------------------'.    |
  |  74| 20| 21| 22| 23| 24|  3B  |  3C  | 25| 26| 27| 28| 29|    |
  |---------------------------------------------------------------|
  | 70| 2A| 2B| 2C| 2D| 2E| 38|  3D   | 39| 2F| 30| 31| 32| 33| 70|
  `---------------------------------------------------------------'
          | 73|   51|   5B|   59|       34|   5A|   35| xx|
          `-----------------------------------------------'
  xx: 74 35 F4 B5
*/
#define KEYMAP( \
    K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K36, K37, K3F, K3E, \
      K00,  K01, K02, K03, K04, K05,  K58, K71,   K06, K07, K08, K09, K0A,    K0E,  \
      K0F,  K10, K11, K12, K13, K14,     K3A,     K15, K16, K17, K18, K19,    K1C,  \
      K74, K20, K21, K22, K23, K24,   K3B,  K3C,   K25, K26, K27, K28, K29,         \
      K70,K2A, K2B, K2C, K2D, K2E, K38,  K3D,  K39, K2F, K30, K31, K32, K33,        \
               K73,  K51, K5B, K59,        K34,        K5A,  K35                    \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_NO,    KC_NO,    KC_NO,    KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_NO,    KC_NO,    KC_##K1C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##K51, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K70, KC_##K71, KC_NO,    KC_##K73, KC_##K74, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}



static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
  ,---------------------------------------------------------------.
  | 60| 61| 62| 63| 64| 65| 66| 67| 68| 69| 6A| 6B| 36| 37| 3F| 3E|
  `---------------------------------------------------------------'
  ,---------------------------------------------------------------.
  |    00| 01| 02| 03| 04| 05|  58|  71| 06| 07| 08| 09| 0A|    0E|
  |---------------------------------------------------------------|
  |   0F| 10| 11| 12| 13| 14|    3A     | 15| 16| 17| 18| 19|   1C|
  |---------------------------------------------------------------|
  |  74| 20| 21| 22| 23| 24|  MINS|   EQL| 25| 26| 27| 28| 29|    |
  |---------------------------------------------------------------|
  | 70| 2A| 2B| 2C| 2D| 2E| 38|  3D   | 39| 2F| 30| 31| 32| 33| 70|
  `---------------------------------------------------------------'
          | 73|   51|   5B|   59|       34|   5A|   35| xx|
          `-----------------------------------------------'
    */
    KEYMAP(
  CANCEL,COPY,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, F13, FN6,
      ESC,    1,   2,   3,   4,   5,   FN4, FN5,    6,   7,   8,   9,   0,   BSPC,
      TAB,    Q,   W,   E,   R,   T,      UP,       Y,   U,   I,   O,   P,   ENT,
      LCTL,  A,   S,   D,   F,   G,  MINS,  EQL,     H,   J,   K,   L, FN2,
      LSFT, Z,   X,   C,   V,   B, GRV, BSLS, QUOT,   N,   M,COMM, DOT, FN1,
              LGUI, LALT, LCTL, LSFT,      SPC,      SPC,   RALT
    ),
    KEYMAP(
    PAUS,COPY,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, F13, F14,
      GRV,   F1,  F2,  F3,  F4,  F5,    NO, NO,    F6,  F7,  F8,  F9, F10,    DEL,
      TAB,    Q,   W,   E,   R,   T,      UP,    HOME,PGDN,PGUP, END,   P,   ENT,
      LCTL,  A,   S,   D,   F,   G,  MINS,  EQL,  LEFT,DOWN,  UP,RGHT,SCLN,
      LSFT, Z,   X,   C,   V,   B, INS, DOWN,  DEL,HOME,PGDN,PGUP, END,TRNS,
              LGUI, LALT, LCTL, LSFT,      SPC,      SPC,   RALT
    ),
    KEYMAP(
    PAUS,COPY,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, F13, F14,
      GRV,   F1,  F2,  F3,  F4,  F5,    NO, NO,    F6,  F7,  F8,  F9, F10,    DEL,
      TAB,    Q,   W,   E,   R,   T,      UP,    WH_L,WH_D,WH_U,WH_R,   P,   ENT,
      LCTL,  A,   S,   D,   F,   G,  MINS,  EQL,  MS_L,MS_D,MS_U,MS_R,TRNS,
      LSFT, Z,   X,   C,   V,   B, INS, DOWN, BTN3,BTN2,BTN1,BTN4,BTN5,TRNS,
              LGUI, LALT, LCTL, LSFT,      SPC,      SPC,   RALT
    ),
};
static const uint8_t PROGMEM overlays[][MATRIX_ROWS][MATRIX_COLS] = {};

/*
 * Macro definition
 */
enum macro_id {
    LBRACKET,
    RBRACKET,
    DUMMY,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    //uint8_t tap_count = record->tap_count;

    switch (id) {
        case LBRACKET:
            return (event.pressed ?
                    MACRO( T(LBRC), END ) :
                    MACRO( T(LBRC), END ) );
        case RBRACKET:
            return (event.pressed ?
                    MACRO( T(RBRC), END ) :
                    MACRO( T(RBRC), END ) );
    }
    return MACRO_NONE;
}

/*
 * Action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
/*
    keyevent_t event = record->event;
    uint8_t tap_count = record->tap_count;
    switch (id) {
        case 0xFF:
            action_macro_play(get_macro(opt, event.pressed));
            break;
    }
*/
}


/*
 * Fn actions
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_TAP_TOGGLE(0),                  // FN0
    ACTION_LAYER_TAP_KEY(1, KC_SLASH),           // FN1
    ACTION_LAYER_TAP_KEY(2, KC_SCLN),            // FN2
    ACTION_LAYER_MOMENTARY(2),                   // FN3
    ACTION_MACRO(LBRACKET),                      // FN4
    ACTION_MACRO(RBRACKET),                      // FN5
    ACTION_MACRO(DUMMY),                         // FN6
};






/*
 * No need to edit.
 */
#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
