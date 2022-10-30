/* Copyright 2017 Christopher B Browne
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

/* Fillers to make layering more clear */
#define ___T___ KC_TRNS

/* Layer shorthand */

enum layers {
  _QWERTY = 0,  /* Qwerty mapping */
  _LOWER, /* Lower layer, where top line has symbols !@#$%^&*() */
  _RAISE, /* Raised layer, where top line has digits 1234567890 */
  _ADJUST, /* Special Adjust layer coming via tri-placement */
  _FUNCTION /* Function key layer */
};


/* Macros need to be uniquely identified; using an enum to do this
   automatically
 */

enum macro_id {
  M_LED = 0,
  M_USERNAME,
  M_RANDDIGIT,
  M_RANDLETTER,
  M_VERSION,
  MACRO_UPPER,
  MACRO_LOWER,
};

/* I want some short forms for keycodes so that they fit into
   limited-width cells */

#define M_LOWER M(MACRO_LOWER)
#define M_UPPER M(MACRO_UPPER)
#define ROT_LED M(M_LED)   /* Rotate LED */
#define QWERTY DF(_QWERTY)   /* Switch to QWERTY layout */
#define QCENT2 DF(_QCENT2)   /* Switch to QWERTY-with-centre layout */
#define USERNAME M(M_USERNAME) /* shortcut for username */
#define RANDDIG M(M_RANDDIGIT)
#define RANDALP M(M_RANDLETTER)
#define CTLENTER MT(MOD_RCTL, KC_ENT)
#define SHIFTQUOTE MT(MOD_RSFT, KC_QUOT)
#define ALTRIGHT MT(MOD_LALT, KC_RGHT)
#define MVERSION M(M_VERSION)
#define ALTSLASH LALT(KC_SLSH)
#define FUNCTION MO(_FUNCTION)
#define MRAISE MO(_RAISE)
#define MLOWER MO(_LOWER)
#define ALTPLUS ALT_T(KC_PLUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY - MIT ENHANCED / GRID COMPATIBLE
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | BRITE  | LCTRL  | LALT   | LGUI   | RAISE  | XXXXXX . SPACE  | LOWER  | RGUI   | RALT   | RCTRL  | FN     | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  /* layout for centred keypad + qwerty...

|ESC| 1 | 2 | 3 | 4 | 5 | ? | ? | ? | ? | 6 | 7 | 8 | 9 | 0 |
|TAB| q | w | e | r | t | ? | ? | ? | ? | y | u | i | o | p |
|CTL| a | s | d | f | g | ? | ? | ? | ? | h | j | k | l | ; |
|SHF| z | x | c | v | b | ? | ? | ? | ? | n | m | , | . | / |
|ALT|LED|   |   |   |   |   |   |   |   |   |   |   |   |   |


keys needing to be assigned:
51 - KC_TAB - tab
   - ROT_LED - rotate LED
15 - KC_LALT - Left ALT
53,55 - M_RAISE - switch to RAISE layer
5b - M_LOWER - switch to LOWER layer
56,59,5a   - KC_SPC - space
5c - KC_LEFT - famous arrows
5d - KC_DOWN - famous arrows
5e - KC_UP - famous arrows
5f - KC_RIGHT - famous arrows
3f - KC_ENT - enter
   - KC_GRV - leftwards quote
4f - KC_QUOT - rightwards quote
1f - KC_BSPC - backspace
11 - KC_ESC
19 - KC_GRV - ` - raised
19 - KC_TILD - ~ - lowered

  */

[_QWERTY] = LAYOUT_ortho_5x15( /* QWERTY, with keypad in the centre */
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_EQL, KC_MINS, KC_EQL,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC ,
      KC_LALT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_7,    KC_8,   KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, ALTPLUS ,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_LBRC, KC_RBRC,KC_MINS, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTLENTER ,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_PGUP, KC_EQL,   KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHIFTQUOTE ,
       KC_TAB,  FUNCTION, MRAISE,  FUNCTION, MRAISE, KC_SPC,KC_PGDN,  KC_MINS, KC_SPC, KC_SPC,  MLOWER, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* LOWER
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      | XXXXXX .        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_ortho_5x15( /* LOWERED */
    ___T___, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______, _______, KC_TILD,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 ,
    ___T___, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_INS  ,
    ___T___, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE ,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, ___T___, ___T___, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

/* RAISED
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | -      | =      | [      | ]      | \      | XXXXXX .        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        | XXXXXX .        |        |        |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | XXXXXX .        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

[_RAISE] = LAYOUT_ortho_5x15 ( /* RAISED */
   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  MVERSION, _______, KC_GRV,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___ ,
   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   USERNAME, _______, KC_7,    KC_8,    KC_LCBR, KC_RCBR,    _______, _______, KC_INS   ,
   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   RANDDIG, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, ___T___, ___T___ ,
   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RANDALP, _______, _______, _______, _______, ___T___, ___T___, _______, _______  ,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* FUNCTION
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | NUM LK | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX .        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | SCR LK | F13    | F14    | F15    | F16    | F17    | F18    | F19    | F20    | F21    | F22    | F23    | F24    | PAUSE  | PR SCR |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAP LK | MS BT5 | MS BT4 | MS BT3 | MS BT2 | SLOW M | FAST M | NEXT   | VOL+   | VOL-   | PLAY   |        | XXXXXX |        | WHEEL+ |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | RGB TG | RGB MD | RGB HI | RGB HD | RGB SI | RGB SD | RGB VI | RGB VD | BL TOG | BL INC | BL DEC | XXXXXX |        | MOUS U | WHEEL- |
 * |--------+--------+--------+--------+--------+-- 2u -----------+--------+--------+--------+--------+-----------------+--------+--------|
 * | QK_BOOT  |        | QWERTY | COLEMK | DVORAK | XXXXXX . MS BT1 |        |        |        |        |        | MOUS L | MOUS D | MOUS R |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

[_FUNCTION] = LAYOUT_ortho_5x15( /* FUNCTION */
   KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT, QK_BOOT,
   KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR  ,
   KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, ___T___, ___T___, KC_WH_U  ,
   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,   ___T___, ___T___, KC_MS_U, KC_WH_D  ,
   QK_BOOT, _______, DF(_QWERTY), DF(_QWERTY), DF(_QWERTY), KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
 )
};

/* This bit of logic seeds a wee linear congruential random number generator */
/* lots of prime numbers everywhere... */
static uint16_t random_value = 157;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  uint8_t clockbyte=0;
  clockbyte = TCNT1 % 256;
  uint8_t rval;
  /* MACRODOWN only works in this function */
  switch(id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
    } else {
      unregister_code(KC_RSFT);
    }
    break;
  case M_USERNAME:
    if (record->event.pressed) {
      SEND_STRING("cbbrowne");
    }
    break;
  case M_VERSION:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP);
    }
    break;
  case M_RANDDIGIT:
    /* Generate, based on random number generator, a keystroke for
       a numeric digit chosen at random */
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) {
      /* Here, we mix the LCRNG with low bits from one of the system
         clocks via XOR in the theory that this may be more random
         than either separately */
      rval = (random_value ^ clockbyte) % 10;
      /* Note that KC_1 thru KC_0 are a contiguous range */
      register_code (KC_1 + rval);
      unregister_code (KC_1 + rval);
    }
    break;
  case M_RANDLETTER:
    /* Generate, based on random number generator, a keystroke for
       a letter chosen at random */
    /* Here, we mix the LCRNG with low bits from one of the system
       clocks via XOR in the theory that this may be more random
       than either separately */
    random_value = ((random_value + randadd) * randmul) % randmod;
    if (record->event.pressed) {
      rval = (random_value ^ clockbyte) % 26;
      register_code (KC_A + rval);
      unregister_code (KC_A + rval);
    }
    break;
  case MACRO_UPPER:
    if (record->event.pressed)
      {
	layer_on(_RAISE);
#ifdef BACKLIGHT_ENABLE
	breathing_period_set(2);
	breathing_pulse();
#endif
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    else
      {
	layer_off(_RAISE);
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    break;
  case MACRO_LOWER:
    if (record->event.pressed)
      {
	layer_on(_LOWER);
#ifdef BACKLIGHT_ENABLE
	breathing_period_set(2);
	breathing_pulse();
#endif
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    else
      {
	layer_off(_LOWER);
	update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
    break;
  }
  return MACRO_NONE;
};

void matrix_init_user(void) {
  rgblight_enable();
  rgblight_mode(1);
  rgblight_sethsv(325,255,255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch(get_highest_layer(state)) {
  case _QWERTY:
    rgblight_sethsv_white();
    break;
  case _LOWER:
    rgblight_sethsv_blue();
    break;
  case _RAISE:
    rgblight_sethsv_green();
    break;
  case _ADJUST:
    rgblight_sethsv_orange();
    break;
  case _FUNCTION:
    rgblight_sethsv_red();
    break;
  default:
    rgblight_sethsv(325,255,255);
    break;
  }
  return state;
}
