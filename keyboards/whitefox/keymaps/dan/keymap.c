/*
Copyright 2015 Jun Wako <wakojun@gmail.com>
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
#include "whitefox.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|Ins|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|PgU|
     * |------------------------------------------------------`    |---|
     * |Fn5   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |PgD|
     * |---------------------------------------------------------------|
     * |Shif|  #|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |Hom|
     * |---------------------------------------------------------------|
     * |Fn2  |  Alt|  Fn6|          Fn0        |Fn7|Fn8|Gui|Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [0] = KEYMAP_ISO( \
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,    KC_DEL, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,             KC_PGUP,\
        CTL_T(KC_F19), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,     KC_ENT, KC_PGDN,\
        KC_LSFT,KC_FN1, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,  KC_HOME,\
        CTL_T(KC_F18),KC_LALT, KC_FN6,                     LT(1, KC_SPC),              KC_FN7, KC_FN8, KC_FN10,     KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Layer 1: HHKB mode (Space)
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Backsp|Ins|
     * |---------------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus| Up|   |     |Del|
     * |------------------------------------------------------`    |---|
     * |      |VoD|VoU|Mut|   |   |   |Bsp|Del|Fn10|Lef|Rig|   |   |PgU|
     * |---------------------------------------------------------------|
     * |    |   |   |   |Fn9|   |   |   |   |   |   |Dow|      |PgU|PgD|
     * |---------------------------------------------------------------|
     * |     |  Fn4|     |                     |   |   |   |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [1] = KEYMAP_ISO( \
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12, KC_BSPC,    KC_INS, \
        KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,BL_INC, KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_TRNS,KC_PAUS,  KC_UP,             KC_DEL, \
        KC_TRNS,KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,BL_TOGG,KC_TRNS,KC_BSPC,KC_DEL, KC_FN10,KC_LEFT,KC_RGHT,KC_TRNS,     KC_PENT,KC_PGUP,\
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_FN9, BL_DEC, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_DOWN,KC_TRNS,KC_TRNS,     KC_PGUP,KC_PGDN,\
        KC_TRNS,KC_TRNS,KC_LALT,                        KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,     KC_HOME,KC_PGDN,KC_END  \
    ),
};

enum macro_id {
    CMD_TAB,
    CMD_GRAVE,
    HASH_TILDE,
    CTRL_A,
    CMD_ALT_C,
    CMD_SHIFT_L,
};

enum function_id {
    CMD_TAB_CMD,
    CMD_GRV_CMD,
};

/*
 * Fn action definition
 */
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
 //   [0]  = ACTION_LAYER_TAP_KEY(1, KC_SPC),            // function layer with Space
    [1]  = ACTION_MACRO(HASH_TILDE),                   // hash / tilde
 //   [2]  = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_F18),      // notification centre
 //   [3]  = ACTION_LAYER_TAP_KEY(2, MOD_RCTL),          // wasd mouse mode
 //   [4]  = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),          // tilde
 //   [5]  = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_F19),      // alfred
    [6]  = ACTION_FUNCTION_TAP(CMD_TAB_CMD),           // tap cmd tab or cmd
    [7]  = ACTION_FUNCTION_TAP(CMD_GRV_CMD),                    // grave tab
    [8]  = ACTION_MACRO(CTRL_A),                       // ctrl a
    [9]  = ACTION_MACRO(CMD_ALT_C),                    // cmd alt c
    [10] = ACTION_MACRO(CMD_SHIFT_L),                  // cmd shift l
};

//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CMD_TAB:
            return MACRO( D(LGUI), T(TAB), U(LGUI), END );
        case CMD_GRAVE:
            return MACRO( D(LGUI), T(GRV), U(LGUI), END );
        case HASH_TILDE:
            if (get_mods()&(MOD_LSFT|MOD_RSFT)) {
                return (record->event.pressed ?
                       MACRO( D(GRV), END ) :
                       MACRO( U(GRV), END ));
            } else {
                return (record->event.pressed ?
                       MACRO( D(LALT), D(3), U(LALT), END ) :
                       MACRO( U(LALT), U(3), END ));
            }
       case CTRL_A:
            return (record->event.pressed ?
                       MACRO( D(LCTL), T(A), U(LCTL), END ) :
                       MACRO( U(LCTL), END ));
       case CMD_ALT_C:
            return (record->event.pressed ?
                    MACRO( D(LGUI), D(LALT), T(C), U(LGUI),  U(LALT), END) :
                    MACRO( U(LGUI),  U(LALT), END ));
       case CMD_SHIFT_L:
            return (record->event.pressed ?
                    MACRO( D(LGUI), D(LSFT), T(L), U(LGUI),  U(LSFT), END) :
                    MACRO( U(LGUI),  U(LSFT), END ));
    }
    return MACRO_NONE;
}

void cmd_or_macro(keyrecord_t *record, uint16_t kc_mod, uint8_t macro_id) {
    if (record->event.pressed) {
        if (record->tap.count > 0 && !record->tap.interrupted) {
            if (record->tap.interrupted) {
                register_mods(MOD_BIT(kc_mod));
            }
        } else {
            register_mods(MOD_BIT(kc_mod));
        }
    } else {
        if (record->tap.count > 0 && !(record->tap.interrupted)) {
            action_macro_play(action_get_macro(record, macro_id, 0));
            record->tap.count = 0;  // ad hoc: cancel tap
        } else {
            unregister_mods(MOD_BIT(kc_mod));
        }
    }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CMD_TAB_CMD:
            cmd_or_macro(record, KC_LGUI, CMD_TAB);
            break;
        case CMD_GRV_CMD:
            cmd_or_macro(record, KC_RGUI, CMD_GRAVE);
            break;
    }
}
