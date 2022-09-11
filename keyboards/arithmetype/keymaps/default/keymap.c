/* Copyright 2021 Richard Nunez <antebios1@gmail.com>
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layer {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  GDOCS,
  FRACT,
  RAD,
  ARC,
  SIN,
  CSC,
  COS,
  SEC,
  TAN,
  COT,
  FUNC,
  SQRT2,
  ALTPE,
};

// TAP DANCE ***********************************************************
//Tap Dance Declarations
enum {
  TD_DEL_BSPC = 0,
  TD_ESC_GRAVE,
  TD_TAB_TILDE,
  TD_MINS_UNDS,
  TD_EQL_PLUS,
  TD_LBRC_LCBR,
  TD_RBRC_RCBR,
  TD_SCLN_COLN,
  TD_QUOT_DQT,
  TD_COMM_LABK,
  TD_DOT_RABK,
  TD_SLSH_QUES,
  TD_BSLS_PIPE,
  TD_3_F3,
  TD_SHIFT_CAPS
};

//Unicode Names
enum {
    PI,
    ANG,
    DEG,
    VBAR,
    DIV,
    ABEQ,
    DELTA,
    THETA,
    LTEQ,
    GTEQ,
    CONGR,
    RAY,
    LINESEG,
    NEQ,
    SQRT,
    PLUSMIN,
    DEGREBOT,
    DHLINE,
};

// UNICODE MAP DEFINES
const uint32_t PROGMEM unicode_map[] = {
    [PI]      = 0X03C0 ,
    [ANG]     = 0x2220 ,
    [DEG]     = 0x00B0 ,
    [VBAR]    = 0x007C ,
    [DIV]     = 0x00F7 ,
    [ABEQ]    = 0x2248 ,
    [DELTA]   = 0X0394 ,
    [THETA]   = 0X0398 ,
    [LTEQ]    = 0X2264 ,
    [GTEQ]    = 0X2265 ,
    [CONGR]   = 0X2245 ,
    [RAY]     = 0X2192 ,
    [LINESEG] = 0XFFE3 ,
    [NEQ]     = 0X2260 ,
    [SQRT]    = 0X221A ,
    [PLUSMIN] = 0X00B1 ,
    [DEGREBOT]= 0X4E04 ,
    [DHLINE]  = 0X2194 ,
};


// Shift key action:
// Shift held down, then use as normal and use Shift Mode of key.
// Shift tapped, then Capitlize next keystroke only.
// Shift double-tapped, then CAPSLOCK
// Shift double-tapped again, CAPS UNLOCKED
void dance_onshot_lsft(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // =>
      set_oneshot_mods (MOD_LSFT);
      break;
    case 2:
      register_code (KC_CAPS);
      //layer_on (LAYER_NAME);
      break;
  }
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_DEL_BSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_BSPC),
   [TD_ESC_GRAVE]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
   [TD_TAB_TILDE]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_TILDE),

   [TD_MINS_UNDS]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
   [TD_EQL_PLUS]  = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),

   [TD_LBRC_LCBR]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
   [TD_RBRC_RCBR]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),

   [TD_SCLN_COLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
   [TD_QUOT_DQT]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),

   [TD_COMM_LABK]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LABK),
   [TD_DOT_RABK]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_RABK),
   [TD_SLSH_QUES]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
   [TD_BSLS_PIPE]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),

   [TD_3_F3]  = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),

   [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_FN(dance_onshot_lsft)
};

// Fillers to make layering more clear
// #define _______ KC_TRNS
// #define XXXXXXX KC_NO

#define KC_L1 LOWER
#define KC_L2 RAISE
#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)



void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(MODE_LED1);
  setPinOutput(MODE_LED2);
  setPinOutput(MODE_LED3);
  setPinOutput(LAYER_LED);
  setPinOutput(NUMLOCK_LED);
}

// MO(_LOWER)
// MO(_RAISE)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



/* Qwerty
 * ,------------------------------------------------------------------------------------.
 * | CUT  | COPY |PASTE |   $  |   (  |   )  | DEL  | GDOCS|  PI  | ANGL | 2NDLR|       |
 * |------+------+------+------+------+------+------+------+------+------+------+-------|
 * |  :   | DEG  |  |   |   %  |   /  |   *  |   -  |  AB= | DELT | THETA| RAD  | UC_MA |
 * |------+------+------+------+------+------+-------------+------+------+------+-------|
 * | LTEQ | GTEQ |ALMEQ |   7  |   8  |   9  |   +  |   ^  |ALLEQ | RAY  | LNSEG|
 * |------+------+------+------+------+------+------|------+------+------+------|
 * |   <  |   >  | NOTEQ|   4  |   5  |   6  |   =  | SQRRT|  +-  |DEGBOT|  SIN |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |  TAB |  UP  |   ,  |   1  |   2  |   3  |      |   M  |  N   |f(X)= |  COS |
 * |------+------+------+------+------+------+ ENTER+------+------+------+------|
 * | LEFT | DOWN | RIGHT| SPACE|   0  |   .  |      |   X  |  Y   |   Z  |  TAN |
 * `----------------------------------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
  KC_CUT,  KC_COPY,  KC_PASTE,   KC_DLR,   KC_LPRN,   KC_RPRN,   KC_BSPC,  GDOCS,   X(PI),        X(ANG),         OSL(_LOWER), KC_NO,
	KC_COLN, X(DEG),   X(VBAR),    KC_PERC,  KC_SLSH,   KC_PAST,   KC_MINS,  FRACT,   X(DELTA),     X(THETA),       RAD,         UC_M_WC,
	X(LTEQ), X(GTEQ),  X(ABEQ),    KC_7,     KC_8,      KC_9,      KC_PLUS,  KC_CIRC, X(CONGR),     X(RAY),         X(LINESEG),  UC_M_MA,
	KC_LABK, KC_RABK,  X(NEQ),     KC_4,     KC_5,      KC_6,      KC_EQL,   X(SQRT), X(PLUSMIN),   X(DEGREBOT),    SIN,         UC_M_LN,
	KC_TAB,  KC_UP,    KC_COMM,    KC_1,     KC_2,      KC_3,      KC_ENT,   KC_M,    KC_N,         FUNC,           COS,         KC_NO,
  KC_LEFT, KC_DOWN,  KC_RGHT,    KC_SPACE, KC_0,      KC_DOT,    KC_NO,    KC_X,    KC_Y,         KC_Z,           TAN,         KC_NO
    ),

/* Lower
 * ,-----------------------------------------------------------------------------.
 * |      |      |      | NUMLK |      |      |      |      |      |      |      |
 * |------+------+------+-------+------+------+------+-------------+------+------+
 * |      |      |      |       |      |      |      |      |      |      |  ARC |
 * |------+------+------+------ +------+------+------+-------------+------+------+
 * |UC_WIN|UC_MAC|UC_LNX|UC_WINC|      |      |      |      |      |      |  <-> |
 * |------+------+------+-------+------+------+------|------+------+------+------+
 * |      |      |      |       |      |      |      |      |      |      |  CSC |
 * |------+------+------+-------+------+------+------+------+------+------+------+
 * |      |      |      |       |      |      |      |      |      |      |  SEC |
 * |------+------+------+-------+------+------+------+------+------+------+------+
 * |      |      |      |       |      |      |      |      |      |      |  COT |
 * `-----------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, KC_NUM,  _______, _______, _______, ALTPE, _______, _______, _______,    _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ARC,        _______,
  _______, UC_M_MA, UC_M_LN, UC_M_WC, _______, _______, _______, _______, _______, _______, X(DHLINE),  _______,
  _______, _______, _______, _______, _______, _______, _______, SQRT2,   _______, _______, CSC,        _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SEC,        _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, COT,        _______
),


};

void matrix_scan_user(void){
    if (get_unicode_input_mode() == UC_MAC){
        writePinHigh(MODE_LED1);
        writePinLow(MODE_LED2);
        writePinLow(MODE_LED3);
    }
     if (get_unicode_input_mode() == UC_LNX){
        writePinHigh(MODE_LED2);
        writePinLow(MODE_LED3);
        writePinLow(MODE_LED1);
    }
     if (get_unicode_input_mode() == UC_WINC){
        writePinHigh(MODE_LED3);
        writePinLow(MODE_LED2);
        writePinLow(MODE_LED1);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _QWERTY:
        writePinLow(LAYER_LED);
        break;
    case _LOWER:
        writePinHigh(LAYER_LED);
        break;
    default: //  for any other layers, or the default layer
       writePinLow(LAYER_LED);
        break;
    }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            writePinHigh(LAYER_LED);
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            writePinLow(LAYER_LED);
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
          return false;
          break;

        case GDOCS:
            if (record->event.pressed) {
              if (get_unicode_input_mode() == UC_MAC){
                SEND_STRING(SS_LALT(SS_LCTRL("i")) SS_DELAY(250) "E");
              }
              else{
                SEND_STRING(SS_LALT("i") SS_DELAY(250) "E");
              }
          }

          break;
        case ALTPE:
            if (record->event.pressed) {

               SEND_STRING(SS_LALT("="));


          }

          break;
        case FRACT:
        if (record->event.pressed) {
                SEND_STRING("\\frac ");
          }

          break;
        case RAD:
        if (record->event.pressed) {
                SEND_STRING("rad");
          }

          break;
        case ARC:
        if (record->event.pressed) {
                SEND_STRING("arc");
          }

          break;
        case SIN:
        if (record->event.pressed) {
                SEND_STRING("sin");
          }

          break;
        case CSC:
        if (record->event.pressed) {
                SEND_STRING("csc");
          }

          break;
        case COS:
        if (record->event.pressed) {
                SEND_STRING("cos");
          }

          break;
        case SEC:
        if (record->event.pressed) {
                SEND_STRING("sec");
          }

          break;
        case TAN:
        if (record->event.pressed) {
                SEND_STRING("tan");
          }

          break;
        case COT:
        if (record->event.pressed) {
                SEND_STRING("cot");
          }

          break;
        case FUNC:
        if (record->event.pressed) {
                SEND_STRING("f(x)=");
          }

          break;
        case SQRT2:
        if (record->event.pressed) {
                SEND_STRING ("\\sqrt ");
          }

          break;

      }
    return true;
};

