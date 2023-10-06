// Copyright 2023 Florent Linguenheld (@FLinguenheld)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keycodes.h"

/* How to :
        - Add an entry in the enum
        - Create a new sequence of keys
        - Link the enum to this sequence in the key_combos table

   For macros :
        - Same steps
        - And add the macro in the process_combo_event() function
*/

enum combos {
  LEADER,
  BOOTLOADER,

  LAYER_ADJ,
  LAYER_FN,
  LAYER_LEFT_HAND,
  LAYER_MOUSE,
  LAYER_MOUSE_BACK,

  /* French */
  C_CEDILLA,
  E_A,
  E_O,

  A_GRAVE,
  E_GRAVE,
  U_GRAVE,

  A_CIRCUMFLEX,
  E_CIRCUMFLEX,
  I_CIRCUMFLEX,
  O_CIRCUMFLEX,
  U_CIRCUMFLEX,

  E_DIAERESIS,
  I_DIAERESIS,
  U_DIAERESIS,
  Y_DIAERESIS,

  /* -- */
  AMPERSAND,
  AT_SIGN,
  BACKSLASH,
  CIRCUMFLEX,
  COLON,
  DOLLAR,
  EQUAL,
  EXCLAMATION_MARK,
  GRAVE,
  HASH,
  MINUS,
  PERCENT,
  PIPE,
  PLUS,
  QUESTION_MARK,
  QUOTE,
  QUOTE_DOUBLE,
  SEMICOLON,
  SLASH,
  STAR,
  TILDE,
  UNDERSCORE,

  ANGLE_BRACKET_LEFT,
  ANGLE_BRACKET_RIGHT,

  BRACKET_LEFT,
  BRACKET_RIGHT,
  CURLY_BRACKET_LEFT,
  CURLY_BRACKET_RIGHT,
  PARENTHESIS_LEFT,
  PARENTHESIS_RIGHT,

  /* Non qwerty */
  EURO,

  /* One hand special */
  CONTROL_RIGHT,
  CONTROL_SHIFT_RIGHT,

  ALT_LEFT,
  SHIFT_LEFT,
  CONTROL_SHIFT_LEFT,

  /* Just to replace the define in config.h */
  COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;

/* Sequences fo keys */
const uint16_t PROGMEM combo_leader[] = {LT(_MOUSE, KC_COMM), LT(_ARROWS, KC_DOT), COMBO_END};
const uint16_t PROGMEM combo_bootloader[] = {KC_K, KC_TAB, KC_Z, KC_BSPC, KC_V, KC_J, COMBO_END};

const uint16_t PROGMEM combo_ADJ[] = {CTL_T(KC_SPACE), LT(_NUMERIC, KC_ENT), COMBO_END};
const uint16_t PROGMEM combo_fn[] = {LT(_NUMERIC, KC_ENT), KC_N, COMBO_END};
const uint16_t PROGMEM combo_left_hand[] = {LT(_MOUSE, KC_COMM), GUI_T(KC_ESC), COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {KC_A, KC_I, KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM combo_mouse_back[] = {KC_MS_LEFT, KC_MS_UP, KC_MS_DOWN, KC_MS_RIGHT, COMBO_END};
/* -- */
const uint16_t PROGMEM combo_c_cedilla[] = {LT(_ARROWS, KC_DOT), KC_C, COMBO_END};
const uint16_t PROGMEM combo_ea[] = {US_EACU, KC_A, COMBO_END};
const uint16_t PROGMEM combo_eo[] = {US_EACU, KC_O, COMBO_END};

const uint16_t PROGMEM combo_a_grave[] = {CTL_T(KC_SPACE), KC_A, COMBO_END};
const uint16_t PROGMEM combo_e_grave[] = {CTL_T(KC_SPACE), KC_E, COMBO_END};
const uint16_t PROGMEM combo_u_grave[] = {CTL_T(KC_SPACE), KC_U, COMBO_END};

const uint16_t PROGMEM combo_a_circumflex[] = {LT(_MOUSE, KC_COMM), KC_A, COMBO_END};
const uint16_t PROGMEM combo_e_circumflex[] = {LT(_MOUSE, KC_COMM), KC_E, COMBO_END};
const uint16_t PROGMEM combo_i_circumflex[] = {LT(_MOUSE, KC_COMM), KC_I, COMBO_END};
const uint16_t PROGMEM combo_o_circumflex[] = {LT(_MOUSE, KC_COMM), KC_O, COMBO_END};
const uint16_t PROGMEM combo_u_circumflex[] = {LT(_MOUSE, KC_COMM), KC_U, COMBO_END};

const uint16_t PROGMEM combo_e_diaeresis[] = {US_EACU, KC_E, COMBO_END};
const uint16_t PROGMEM combo_i_diaeresis[] = {US_EACU, KC_I, COMBO_END};
const uint16_t PROGMEM combo_u_diaeresis[] = {US_EACU, KC_U, COMBO_END};
const uint16_t PROGMEM combo_y_diaeresis[] = {US_EACU, KC_Y, COMBO_END};

/* -- */
const uint16_t PROGMEM combo_ampersand[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM combo_at_sign[] = {KC_D, KC_L, COMBO_END};
const uint16_t PROGMEM combo_backslash[] = {KC_B, KC_E, COMBO_END};
const uint16_t PROGMEM combo_circumflex[] = {KC_B, KC_O, COMBO_END};
const uint16_t PROGMEM combo_colon[] = {KC_C, KC_G, COMBO_END};
const uint16_t PROGMEM combo_dollar[] = {KC_O, KC_W, COMBO_END};
const uint16_t PROGMEM combo_equal[] = {KC_T, KC_H, COMBO_END};
const uint16_t PROGMEM combo_exclamation_mark[] = {KC_Q, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_grave[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_hash[] = {KC_X, KC_U, COMBO_END};
const uint16_t PROGMEM combo_minus[] = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM combo_percent[] = {KC_B, KC_U, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_plus[] = {KC_T, KC_L, COMBO_END};
const uint16_t PROGMEM combo_question_mark[] = {KC_P, KC_D, COMBO_END};
const uint16_t PROGMEM combo_quote[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM combo_quote_double[] = {KC_A, KC_U, COMBO_END};
const uint16_t PROGMEM combo_semicolon[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM combo_slash[] = {KC_S, KC_L, COMBO_END};
const uint16_t PROGMEM combo_star[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_tilde[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM combo_underscore[] = {KC_S, KC_R, COMBO_END};

const uint16_t PROGMEM combo_angle_bracket_left[] = {KC_C, KC_S, COMBO_END};
const uint16_t PROGMEM combo_angle_bracket_right[] = {KC_S, KC_H, COMBO_END};
const uint16_t PROGMEM combo_bracket_left[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_bracket_right[] = {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM combo_curly_bracket_left[] = {KC_X, KC_E, COMBO_END};
const uint16_t PROGMEM combo_curly_bracket_right[] = {KC_E, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_parenthesis_left[] = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM combo_parenthesis_right[] = {KC_D, KC_R, COMBO_END};

/* Non qwerty */
const uint16_t PROGMEM combo_euro[] = {KC_X, KC_Q, COMBO_END};

/* One hand special */
const uint16_t PROGMEM combo_control_right[] = {LT(_NUMERIC, KC_ENT), KC_R, COMBO_END};
const uint16_t PROGMEM combo_control_shift_right[] = {LT(_NUMERIC, KC_ENT), KC_S, COMBO_END};

const uint16_t PROGMEM combo_shift_left[] = {LT(_MOUSE, KC_COMM), US_EACU, COMBO_END};
const uint16_t PROGMEM combo_alt_left[] = {CTL_T(KC_SPACE), US_EACU, COMBO_END};
const uint16_t PROGMEM combo_control_shift_left[] = {CTL_T(KC_SPACE), GUI_T(KC_ESC), COMBO_END};

/* Sequences fo keys */
combo_t key_combos[] = {
    [LEADER] = COMBO(combo_leader, QK_LEAD),
    [BOOTLOADER] = COMBO(combo_bootloader, QK_BOOTLOADER),

    [LAYER_ADJ] = COMBO(combo_ADJ, OSL(_ADJ)),
    [LAYER_FN] = COMBO(combo_fn, OSL(_FN)),
    [LAYER_LEFT_HAND] = COMBO(combo_left_hand, OSL(_LEFT_HAND)),
    [LAYER_MOUSE] = COMBO(combo_mouse, TG(_MOUSE)),
    [LAYER_MOUSE_BACK] = COMBO(combo_mouse_back, TG(_MOUSE)),

    /* French */
    [C_CEDILLA] = COMBO(combo_c_cedilla, US_CCED),
    [E_A] = COMBO(combo_ea, US_AE),
    [E_O] = COMBO(combo_eo, US_OE),

    [A_GRAVE] = COMBO(combo_a_grave, CS_A_GRAVE),
    [E_GRAVE] = COMBO(combo_e_grave, CS_E_GRAVE),
    [U_GRAVE] = COMBO(combo_u_grave, CS_U_GRAVE),

    [A_CIRCUMFLEX] = COMBO(combo_a_circumflex, CS_A_CIRCUMFLEX),
    [E_CIRCUMFLEX] = COMBO(combo_e_circumflex, CS_E_CIRCUMFLEX),
    [I_CIRCUMFLEX] = COMBO(combo_i_circumflex, CS_I_CIRCUMFLEX),
    [O_CIRCUMFLEX] = COMBO(combo_o_circumflex, CS_O_CIRCUMFLEX),
    [U_CIRCUMFLEX] = COMBO(combo_u_circumflex, CS_U_CIRCUMFLEX),

    [E_DIAERESIS] = COMBO(combo_e_diaeresis, CS_E_DIAERESIS),
    [I_DIAERESIS] = COMBO(combo_i_diaeresis, CS_I_DIAERESIS),
    [U_DIAERESIS] = COMBO(combo_u_diaeresis, CS_U_DIAERESIS),
    [Y_DIAERESIS] = COMBO(combo_y_diaeresis, CS_Y_DIAERESIS),

    /* -- */
    [AMPERSAND] = COMBO(combo_ampersand, KC_AMPERSAND),
    [AT_SIGN] = COMBO(combo_at_sign, KC_AT),
    [BACKSLASH] = COMBO(combo_backslash, KC_BACKSLASH),
    [CIRCUMFLEX] = COMBO(combo_circumflex, KC_CIRCUMFLEX),
    [COLON] = COMBO(combo_colon, KC_COLON),
    [DOLLAR] = COMBO(combo_dollar, KC_DOLLAR),
    [EQUAL] = COMBO(combo_equal, KC_EQUAL),
    [EXCLAMATION_MARK] = COMBO(combo_exclamation_mark, KC_EXCLAIM),
    [GRAVE] = COMBO(combo_grave, KC_GRAVE),
    [HASH] = COMBO(combo_hash, KC_HASH),
    [MINUS] = COMBO(combo_minus, KC_MINUS),
    [PERCENT] = COMBO(combo_percent, KC_PERCENT),
    [PIPE] = COMBO(combo_pipe, KC_PIPE),
    [PLUS] = COMBO(combo_plus, KC_PLUS),
    [QUESTION_MARK] = COMBO(combo_question_mark, KC_QUESTION),
    [QUOTE] = COMBO(combo_quote, KC_QUOTE),
    [QUOTE_DOUBLE] = COMBO(combo_quote_double, KC_DOUBLE_QUOTE),
    [SEMICOLON] = COMBO(combo_semicolon, KC_SEMICOLON),
    [SLASH] = COMBO(combo_slash, KC_SLASH),
    [STAR] = COMBO(combo_star, KC_ASTERISK),
    [TILDE] = COMBO(combo_tilde, KC_TILDE),
    [UNDERSCORE] = COMBO(combo_underscore, KC_UNDERSCORE),

    [ANGLE_BRACKET_LEFT] = COMBO(combo_angle_bracket_left, KC_LEFT_ANGLE_BRACKET),
    [ANGLE_BRACKET_RIGHT] = COMBO(combo_angle_bracket_right, KC_RIGHT_ANGLE_BRACKET),

    [BRACKET_LEFT] = COMBO(combo_bracket_left, KC_LEFT_BRACKET),
    [BRACKET_RIGHT] = COMBO(combo_bracket_right, KC_RIGHT_BRACKET),
    [CURLY_BRACKET_LEFT] = COMBO(combo_curly_bracket_left, KC_LEFT_CURLY_BRACE),
    [CURLY_BRACKET_RIGHT] = COMBO(combo_curly_bracket_right, KC_RIGHT_CURLY_BRACE),
    [PARENTHESIS_LEFT] = COMBO(combo_parenthesis_left, KC_LEFT_PAREN),
    [PARENTHESIS_RIGHT] COMBO(combo_parenthesis_right, KC_RIGHT_PAREN),

    /* Non qwerty */
    [EURO] COMBO(combo_euro, US_EURO),

    /* One hand special */
    [CONTROL_RIGHT] = COMBO(combo_control_right, KC_RCTL),
    [CONTROL_SHIFT_RIGHT] = COMBO(combo_control_shift_right, C(S(XXXXXXX))),

    [ALT_LEFT] = COMBO(combo_alt_left, KC_LALT),
    [SHIFT_LEFT] = COMBO(combo_shift_left, KC_LSFT),
    [CONTROL_SHIFT_LEFT] = COMBO(combo_control_shift_left, C(S(XXXXXXX))),
};
