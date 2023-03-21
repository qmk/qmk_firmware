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
  _BRACKET,	// 5
  _ADJUST	// 6
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
 * |      |    []|    ()|    ap|      |      |      |      |      |      |      |      |
 * |osl(5)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |osl(6)|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)|   /  | Left | Down | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    QK_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  OSL(_BRACKET),
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   OSL(_ADJUST),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Colemak layer 1
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |   Del|
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * | `~   |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |    <>|      |      |      |      |   Dnc|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Lead |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |    {}|      |      |      |      |      |      |
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * | LCtl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |    []|    ()|    ap|      |      |      |      |      |      |      |      |
 * |osl(5)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |osl(6)|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)|   /  | Left | Down | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid(
  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, QK_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  OSL(_BRACKET),
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   OSL(_ADJUST),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Dvorak layer 2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |   Del|
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * | `~   |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |    ap|      |      |   Dnc|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Lead |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |    {}|      |      |      |      |      |
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * | LCtl |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |    <>|      |    ()|      |      |      |      |    []|      |      |
 * |osl(5)|   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |  Up  |osl(6)|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | osm  | RCtl | Opt  | Cmd  |osl(4)| Entr | Spc  | tt(3)|   :  | Left | Down | Rght |
 * | Lsft |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid(
  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    QK_LEAD,
  LCTL_T(KC_ESC),
           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  OSL(_BRACKET),
           KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_UP,   OSL(_ADJUST),
  OSM(MOD_LSFT),
           KC_RCTL, KC_LOPT, KC_LCMD, OSL(_SYMBOL),
                                               KC_ENT,  KC_SPC,  TT(_NUMPAD),
                                                                          KC_COLN, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Numpad layer 3
 * ,-----------------------------------------------------------------------------------.
 * | ____ |   1  |   2  |   3  |   4  |   5  |  =+  |   7  |   8  |   9  |   ^  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |   6  |   7  |   8  |   9  |   0  |  -_  |   4  |   5  |   6  |   %  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |   1  |   2  |   3  |   4  |   5  |  *   |   1  |   2  |   3  | ____ | ____ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |   6  |   7  |   8  |   9  |   0  |  /   |   0  | ____ | ____ | PgUp | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | tg(3)| ____ | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_EQL,  KC_7,    KC_8,    KC_9,    KC_CIRC, _______,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_4,    KC_5,    KC_6,    KC_PERC, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ASTR, KC_1,    KC_2,    KC_3,    _______, _______,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH, KC_0,    _______, _______, KC_PGUP, _______,
  _______, _______, _______, _______, _______, _______, _______, TG(_NUMPAD),
                                                                          _______, KC_HOME, KC_PGDN, KC_END
),

/* Symbol layer 4
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ |      |      |   !  |   $  |   ~  |      |   _  |   |  |      |   %  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |   @  |   *  |   &  |      |   `  |   #  |   -  |      |   +  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   ^  |      |   \  |      |   =  |      |      | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | tg(4)| ____ | ____ |      |      | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_preonic_grid(
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, XXXXXXX, XXXXXXX, KC_EXLM, KC_DLR,  KC_TILD, XXXXXXX, KC_UNDS, KC_PIPE, XXXXXXX, KC_PERC, _______,
  _______, KC_AT,   KC_ASTR, KC_AMPR, XXXXXXX, KC_GRV,  KC_HASH, KC_MINS, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, XXXXXXX, KC_BSLS, XXXXXXX, KC_EQL,  XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,
  _______, _______, _______, _______, TG(_SYMBOL), _______, _______, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END
),

/* Bracket layer 5
 * ,-----------------------------------------------------------------------------------.
 * |      |plain |breath|      |      |      |      |    < | <|>  | >    |      | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |snake |knight|      | rgb  | saT+ |      |    ( | (|)  | )    |      | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |rainbw|gradnt|      |      | mod+ | Hue+ |    [ | [|]  | ]    |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | tg(5)|swirl | Xmas | test |      | Brt+ |      |    { | {|}  | }    |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BRACKET] = LAYOUT_preonic_grid(
  XXXXXXX, RGB_M_P,  RGB_M_B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LABK, ABKPAIR, KC_RABK, XXXXXXX, _______,
  XXXXXXX, RGB_M_SN, RGB_M_K, XXXXXXX, RGB_TOG, RGB_SAI, XXXXXXX, KC_LPRN, RBKPAIR, KC_RPRN, XXXXXXX, _______,
  XXXXXXX, RGB_M_R,  RGB_M_G, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUI, KC_LBRC, SBKPAIR, KC_RBRC, XXXXXXX, XXXXXXX,
  TG(_BRACKET),
           RGB_M_SW, RGB_M_X, RGB_M_T, XXXXXXX, RGB_VAI, XXXXXXX, KC_LCBR, CBKPAIR, KC_RCBR, XXXXXXX, XXXXXXX,
  _______, _______,  _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust layer 6
 *
 * The control sequences are highly personal.  Please change to adapt to your own system.
 *
 * ,-----------------------------------------------------------------------------------.
 * |      | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Qwerty|Colemk|Dvorak|      |      |      |      |      |      |Print |QK_BOOT |
 * |      |      |      |      |      |      |      |      |      |      |screen|QK_BOOT |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Sleep |show  |      |      |finder|mv win|      |Lock  |      |      |
 * |      |      |      |Dsktp |      |      |Hddn  |clkw  |      |screen|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | Caps |Virus |      |      | Mute | vol+ |      | dsp+ | tg(6)|
 * |      |      |      |      |scan  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ |      |      |      |      | vol- |      | dsp- |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  XXXXXXX, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  XXXXXXX,
  XXXXXXX, QWERTY,  COLEMAK, DVORAK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SCMD(KC_5), QK_BOOT,
  XXXXXXX, XXXXXXX, C(LCMD(KC_PAUSE)),
                             LCMD(KC_F4),
                                      XXXXXXX, XXXXXXX, SCMD(KC_DOT),
                                                                 LCA(KC_J), XXXXXXX, C(LCMD(KC_Q)), XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, SCMD(KC_V),
                                               XXXXXXX, XXXXXXX, KC_MUTE,  KC_VOLU,     XXXXXXX, LCAG(KC_UP), TG(_ADJUST),
  _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_VOLD,     XXXXXXX, LCAG(KC_DOWN), XXXXXXX
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

  The two numbers: starting LED number, number of LEDs
*/
const rgblight_segment_t PROGMEM my_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 3, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 3, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM my_bracket_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 3, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 3, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_PINK}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_numpad_layer,
    my_symbol_layer,
    my_bracket_layer,
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
    rgblight_set_layer_state(_ADJUST - _NUMPAD + 1, led_state.caps_lock);

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

void leader_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start_song);
#endif
}

void leader_end_user(void) {
  did_leader_succeed = false;

  // tap dance
  // sort by first key

  if (leader_sequence_one_key(KC_C)) {
    SEND_STRING(SS_TAP(X_CAPS));
    did_leader_succeed = true;
  }

  if (leader_sequence_one_key(KC_BSPC)) {
    SEND_STRING(SS_TAP(X_DEL));
    did_leader_succeed = true;
  }

  if (leader_sequence_one_key(KC_D)) {
    SEND_STRING("{}"SS_TAP(X_LEFT));
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_D, KC_B)) {
    SEND_STRING("Dear Brother");
    did_leader_succeed = true;
  }
  if (leader_sequence_three_keys(KC_D, KC_B, KC_S)) {
    SEND_STRING("Dear Brothers and Sister");
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_D, KC_D)) {
    SEND_STRING("{");
    did_leader_succeed = true;
  }
  if (leader_sequence_three_keys(KC_D, KC_D, KC_D)) {
    SEND_STRING("}");
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_D, KC_S)) {
    SEND_STRING("Dear Sister");
    did_leader_succeed = true;
  }

  // Html Tags
  if (leader_sequence_two_keys(KC_H, KC_T)) {
    SEND_STRING("<></>"SS_TAP(X_LEFT));
    did_leader_succeed = true;
  }

  if (leader_sequence_two_keys(KC_I, KC_C)) {
    SEND_STRING("In Christ,");
    did_leader_succeed = true;
  }

  if (leader_sequence_one_key(KC_J)) {
    SEND_STRING("<>"SS_TAP(X_LEFT));
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_J, KC_J)) {
    SEND_STRING("<");
    did_leader_succeed = true;
  }
  if (leader_sequence_three_keys(KC_J, KC_J, KC_J)) {
    SEND_STRING(">");
    did_leader_succeed = true;
  }

  if (leader_sequence_two_keys(KC_T, KC_S)) {
    SEND_STRING("Thanks!");
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_T, KC_Y)) {
    SEND_STRING("Thank you!");
    did_leader_succeed = true;
  }

  if (leader_sequence_one_key(KC_X)) {
    SEND_STRING("()"SS_TAP(X_LEFT));
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_X, KC_X)) {
    SEND_STRING("(");
    did_leader_succeed = true;
  }
  if (leader_sequence_three_keys(KC_X, KC_X, KC_X)) {
    SEND_STRING(")");
    did_leader_succeed = true;
  }

  if (leader_sequence_one_key(KC_Z)) {
    SEND_STRING("[]"SS_TAP(X_LEFT));
    did_leader_succeed = true;
  }
  if (leader_sequence_two_keys(KC_Z, KC_Z)) {
    SEND_STRING("[");
    did_leader_succeed = true;
  }
  if (leader_sequence_three_keys(KC_Z, KC_Z, KC_Z)) {
    SEND_STRING("]");
    did_leader_succeed = true;
  }

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

