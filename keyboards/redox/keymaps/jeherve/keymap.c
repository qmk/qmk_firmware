/*
Copyright 2021 Jeremy Herve <jeremy@jeremy.hu>

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

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _SYMB 1
#define _NAV 2
#define _INTER 3
#define _ADJUST 4

// Define song.
#ifdef AUDIO_ENABLE
float tone_zelda[][2] = SONG(ZELDA_TREASURE);
#endif

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    SYMB,
    NAV,
    INTER,
    ADJUST,
    // These use process_record_user()
    M_BRACKET_LEFT,
    M_BRACKET_RIGHT,
    SHRUG,
    WAVE,
    YOSHI,
    THUMB_UP,
    INV_1P,
    ALFRED
};

// Is shift being held? Let's store this in a bool.
static bool shift_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHRUG:
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            return false;
            break;
        case INV_1P:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LALT) SS_TAP(X_BSLASH) SS_UP(X_LGUI) SS_UP(X_LALT));
            }
            return false;
            break;
        case ALFRED:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_SPACE) SS_UP(X_LALT));
            }
            return false;
            break;
        case YOSHI:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_zelda);
#endif
                SEND_STRING(":yellow_yoshi:");
            }
            return false;
            break;
        case THUMB_UP:
            if (record->event.pressed) {
                register_unicode(0x1F44D);
            }
            return false;
            break;
        case WAVE:
            if (record->event.pressed) {
                register_unicode(0x1F44B);
            }
            return false;
            break;
        case KC_LSFT:
            shift_held = record->event.pressed;
            return true;
            break;
        case KC_RSFT:
            shift_held = record->event.pressed;
            return true;
            break;
        case M_BRACKET_LEFT: {
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    register_code(KC_LBRC);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_9);
                }
            } else {  // Release the key
                unregister_code(KC_LBRC);
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                unregister_code(KC_9);
            }
            return false;
            break;
        }
        case M_BRACKET_RIGHT: {
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    register_code(KC_RBRC);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_0);
                }
            } else {  // Release the key
                unregister_code(KC_RBRC);
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);
                unregister_code(KC_0);
            }
            return false;
            break;
        }
    }
    return true;
};

// Shortcut to make keymap more readable
#define KC_SYQT LT(_SYMB, KC_QUOT)
#define SYM_L   MO(_SYMB)
#define MO_INTR MO(_INTER)
#define TT_ADJ  TT(_ADJUST)

#define UC_00E0 UC(0x00E0)
#define UC_00FC UC(0x00FC)
#define UC_00E8 UC(0x00E8)
#define UC_00F6 UC(0x00F6)
#define UC_00E1 UC(0x00E1)
#define UC_00F9 UC(0x00F9)
#define UC_00E9 UC(0x00E9)
#define UC_00ED UC(0x00ED)
#define UC_00F3 UC(0x00F3)
#define UC_00E2 UC(0x00E2)
#define UC_00E7 UC(0x00E7)
#define UC_0171 UC(0x0171)
#define UC_00EA UC(0x00EA)
#define UC_0151 UC(0x0151)
// Non-breaking space.
#define UC_00A0 UC(0x00a0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G    ,KC_ESC  ,                           INV_1P ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SYM_L   ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D    ,M_BRACKET_LEFT,            M_BRACKET_RIGHT ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_SYQT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,TT(_NAV),TT(_SYMB),      TT(_SYMB),TT(_NAV),KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     MO_INTR ,KC_LCTL ,KC_HYPR ,KC_LALT ,     KC_LCMD ,    KC_BSPC ,KC_LCTL ,        KC_ENT  ,KC_SPC  ,    ALFRED  ,     TT_ADJ  ,KC_HYPR ,KC_RCTL ,MO_INTR
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______ ,                          _______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,KC_LCBR ,                          KC_RCBR ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_MINS ,KC_UNDS ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,KC_TILD ,KC_GRV , _______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_EQL  ,KC_PLUS ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_VOLD ,KC_VOLU ,KC_MUTE ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,XXXXXXX ,    XXXXXXX ,     _______ ,XXXXXXX ,XXXXXXX ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_INTER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,UC_00E0 ,WAVE    ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,UC_00FC ,UC_00E8 ,YOSHI   ,UC_00F6 ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,UC_00E1 ,XXXXXXX ,SHRUG   ,THUMB_UP,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,UC_00F9 ,UC_00E9 ,UC_00ED ,UC_00F3 ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,UC_00E2 ,XXXXXXX ,UC_00E7 ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,UC_0171 ,UC_00EA ,XXXXXXX ,UC_0151 ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,UC_00A0 ,    XXXXXXX ,     _______ ,XXXXXXX ,XXXXXXX ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,RGB_VAD ,RGB_VAI ,RGB_TOG ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,QK_BOOT,DEBUG   ,AU_TOG  ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,XXXXXXX ,    XXXXXXX ,     _______ ,XXXXXXX ,XXXXXXX ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Change LED colors depending on the layer.
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SYMB:
            rgblight_setrgb_orange();
            break;
        case _NAV:
            rgblight_setrgb_springgreen();
            break;
        case _INTER:
            rgblight_setrgb_teal();
            break;
        case _ADJUST:
            rgblight_setrgb_red();
            break;
        default:  //  for any other layers, or the default layer
            rgblight_setrgb_yellow();
            break;
    }
    return state;
};
