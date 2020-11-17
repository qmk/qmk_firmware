/* Copyright 2020 Pete Curt
 * Based on code by Jack Humbert
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
#include "muse.h"

enum preonic_layers {
  _QWERTY,	// 0
  _COLEMAK,	// 1
  _DVORAK,	// 2
  _NUMPAD,	// 3
  _SYMBOL,	// 4
  _ADJUST	// 5
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  BACKLIT,
  ABKPAIR,
  RBKPAIR,
  SBKPAIR,
  CBKPAIR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty layer 0
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |   Del|
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * | `~   |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |   Dnc|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Lead |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |    {}|      |      |      |    <>|      |      |      |      |
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * | LCtl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |    []|    ()|      |      |      |      |      |      |      |      |      |
 * |osl(5)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Caps |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)| Left | Down | Up   | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  OSL(_ADJUST),
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_CAPS),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak layer 1
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * | `~   |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Lead |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * | LCtl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |osl(5)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Caps |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)| Left | Down | Up   | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  OSL(_ADJUST),
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_CAPS),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak layer 2
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * | `~   |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Lead |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * | LCtl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |osl(5)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Caps |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)| Left | Down | Up   | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  OSL(_ADJUST),
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_CAPS),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Numpad layer 3
 * ,-----------------------------------------------------------------------------------.
 * | ____ |      |      |   <  |  <|> |  >   |  =+  |   7  |   8  |   9  |   ^  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |      |      |   (  |  (|) |  )   |  -_  |   4  |   5  |   6  |   %  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |      |      |   [  |  [|] |  ]   |  *   |   1  |   2  |   3  | ____ | ____ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |      |      |   {  |  {|} |  }   |  /   |   0  | ____ | ____ | ____ | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid(
  _______, XXXXXXX, XXXXXXX, KC_LABK, ABKPAIR, KC_RABK, KC_EQL,  KC_7,    KC_8,    KC_9,    KC_CIRC, _______,
  _______, XXXXXXX, XXXXXXX, KC_LPRN, RBKPAIR, KC_RPRN, KC_MINS, KC_4,    KC_5,    KC_6,    KC_PERC, _______,
  _______, XXXXXXX, XXXXXXX, KC_LBRC, SBKPAIR, KC_RBRC, KC_ASTR, KC_1,    KC_2,    KC_3,    _______, _______,
  _______, XXXXXXX, XXXXXXX, KC_LCBR, CBKPAIR, KC_RCBR, KC_SLSH, KC_0,    _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Symbol layer 4
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ |   =  |      |   !  |   $  |   ~  |      |   _  |   |  |      |   %  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |   @  |   *  |   &  |      |   `  |   #  |   -  |      |   +  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   ^  |      |   \  |      |      |      |      |      | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ |      | ____ | ____ |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_preonic_grid(
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, KC_EQL,  _______, KC_EXLM, KC_DLR,  KC_TILD, XXXXXXX, KC_UNDS, KC_PIPE, XXXXXXX, KC_PERC, _______,
  _______, KC_AT,   KC_ASTR, KC_AMPR, XXXXXXX, KC_GRV,  KC_HASH, KC_MINS, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, XXXXXXX, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust layer 5
 *
 * The control sequences are highly personal.  Please change to adapt to your own system.
 *
 * ,-----------------------------------------------------------------------------------.
 * |      | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Qwerty|Colemk|Dvorak| rgb  | rgb  |      |      |      |      |Print |      |
 * |      |      |      |      | 0/1  | saT+ |      |      |      |      |screen|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Sleep |show  | rgb  | rgb  |finder|mv win|      |Lock  |      |      |
 * |      |      |      |Dsktp | hue+ | mod+ |Hddn  |clkw  |      |screen|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |RESET |      |Virus | rgb  |      | Mute | vol+ |      |      | dsp+ |
 * |      |      |RESET |      |scan  | Brit+|      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ |      |      |      |      | vol- |      |      | dsp- |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  XXXXXXX, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  XXXXXXX,
  XXXXXXX, QWERTY,  COLEMAK, DVORAK,  RGB_TOG, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SCMD(KC_5), XXXXXXX,
  XXXXXXX, XXXXXXX, C(LCMD(KC_PAUSE)),
                             LCMD(KC_F4),
                                      RGB_HUI, RGB_MOD, SCMD(KC_DOT),
                                                                 LCA(KC_J), XXXXXXX, C(LCMD(KC_Q)), XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, RESET,   XXXXXXX, SCMD(KC_V),
                                               RGB_VAI, XXXXXXX, KC__MUTE, KC__VOLUP,   XXXXXXX, XXXXXXX, LCAG(KC_UP),
  _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC__VOLDOWN, XXXXXXX, XXXXXXX, LCAG(KC_DOWN)
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
        case ABKPAIR:
          if (record->event.pressed) {
              SEND_STRING("<>"SS_TAP(X_LEFT));
          }
          break;
        case RBKPAIR:
          if (record->event.pressed) {
              SEND_STRING("()"SS_TAP(X_LEFT));
          }
          break;
        case SBKPAIR:
          if (record->event.pressed) {
              SEND_STRING("[]"SS_TAP(X_LEFT));
          }
          break;
        case CBKPAIR:
          if (record->event.pressed) {
              SEND_STRING("{}"SS_TAP(X_LEFT));
          }
          break;
      }
    return true;
};

/*
 Preonic LEDs visible from the top:
 6 5 4 3
 7 8 1 2
*/
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_PINK}       // Light 2 LEDs, starting with LED 2, that is, the two on the right
);
const rgblight_segment_t PROGMEM my_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 3, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 3, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 3, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_numpad_layer,
    my_symbol_layer,
    my_adjust_layer,
    my_capslock_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    for (int i = 0; i <= _ADJUST - _NUMPAD; i++) {
        rgblight_set_layer_state(i, false);
    }
    int highest_layer = get_highest_layer(state);
    if (highest_layer >= _NUMPAD && highest_layer <= _ADJUST) {
        rgblight_set_layer_state(highest_layer-_NUMPAD, true);
    }

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_ADJUST-_NUMPAD+1, led_state.caps_lock);

    return true;
}

bool did_leader_succeed;
#ifdef AUDIO_ENABLE
//float leader_start_song[][2] = SONG(CHROMATIC_SOUND);
float leader_start_song[][2] = SONG(NO_SOUND);
float leader_succeed_song[][2] = SONG(STARTUP_SOUND);
//float leader_fail_song[][2] = SONG(GOODBYE_SOUND);
float leader_fail_song[][2] = SONG(NO_SOUND);
#endif
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    // sort by first key

    SEQ_ONE_KEY(KC_BSPC) {
      SEND_STRING(SS_TAP(X_DEL));
      did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_D) {
      SEND_STRING("{}"SS_TAP(X_LEFT));
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_D, KC_B) {
      SEND_STRING("Dear Brother");
      did_leader_succeed = true;
    }
    SEQ_THREE_KEYS(KC_D, KC_B, KC_S) {
      SEND_STRING("Dear Brothers and Sister");
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING("{");
      did_leader_succeed = true;
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_D) {
      SEND_STRING("}");
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_D, KC_S) {
      SEND_STRING("Dear Sister");
      did_leader_succeed = true;
    }

    // Html Tags
    SEQ_TWO_KEYS(KC_H, KC_T) {
      SEND_STRING("<></>"SS_TAP(X_LEFT));
      did_leader_succeed = true;
    }

    // In Christ
    SEQ_TWO_KEYS(KC_I, KC_C) {
      SEND_STRING("In Christ,");
      did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_J) {
      SEND_STRING("<>"SS_TAP(X_LEFT));
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_J, KC_J) {
      SEND_STRING("<");
      did_leader_succeed = true;
    }
    SEQ_THREE_KEYS(KC_J, KC_J, KC_J) {
      SEND_STRING(">");
      did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_X) {
      SEND_STRING("()"SS_TAP(X_LEFT));
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_X, KC_X) {
      SEND_STRING("(");
      did_leader_succeed = true;
    }
    SEQ_THREE_KEYS(KC_X, KC_X, KC_X) {
      SEND_STRING(")");
      did_leader_succeed = true;
    }

    SEQ_ONE_KEY(KC_Z) {
      SEND_STRING("[]"SS_TAP(X_LEFT));
      did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_Z, KC_Z) {
      SEND_STRING("[");
      did_leader_succeed = true;
    }
    SEQ_THREE_KEYS(KC_Z, KC_Z, KC_Z) {
      SEND_STRING("]");
      did_leader_succeed = true;
    }


    leader_end();
  }
}

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start_song);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed_song);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail_song);
#endif
  }
}

