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

    LAYER_ADJUST,
    LAYER_FN,
    LAYER_LEFT_HAND,

    /* French */
    E_ACUTE,
    C_CEDILLA,
    E_A,
    E_O,

    A_GRAVE,
    E_GRAVE,
    I_GRAVE,
    O_GRAVE,
    U_GRAVE,

    A_CIRCUMFLEX,
    E_CIRCUMFLEX,
    I_CIRCUMFLEX,
    O_CIRCUMFLEX,
    U_CIRCUMFLEX,

    A_DIAERESIS,
    E_DIAERESIS,
    I_DIAERESIS,
    O_DIAERESIS,
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

    /* -- */
    ALT_SHIFT,
    CONTROL_SHIFT,
    CONTROL_ALT,
    CONTROL_SHIFT_ALT,
    RIGHT_ALT,

    /* One hand special */
    CONTROL_RIGHT,
    CONTROL_SHIFT_RIGHT,

    // DEL_LEFT,
    SHIFT_LEFT,
    ALTGR_LEFT,
    CONTROL_SHIFT_LEFT,

    /* Just to replace the define in config.h */
    COMBO_LENGTH,
};
uint16_t COMBO_LEN = COMBO_LENGTH;


/* Sequences fo keys */
const uint16_t PROGMEM combo_leader[] =                 {LT(_MOUSE, KC_COMM), LT(_ARROWS, KC_DOT), COMBO_END};
const uint16_t PROGMEM combo_bootloader[] =             {KC_K, KC_TAB, KC_Z, KC_BSPC, KC_V, KC_J, COMBO_END};

const uint16_t PROGMEM combo_adjust[] =                 {KC_LCPO, LT(_NUMERIC, KC_ENT), COMBO_END};
const uint16_t PROGMEM combo_fn[] =                     {LT(_NUMERIC, KC_ENT), KC_N, COMBO_END};
const uint16_t PROGMEM combo_left_hand[] =              {KC_LCPO, GUI_T(KC_ESC), COMBO_END};

/* -- */
// const uint16_t PROGMEM combo_enter_shifted[] =          {LT(_NUMERIC, KC_ENT), KC_S, COMBO_END};
const uint16_t PROGMEM combo_control_shift[] =          {KC_LCPO, KC_S, COMBO_END};
const uint16_t PROGMEM combo_control_alt[] =            {KC_LCPO, KC_LALT, COMBO_END};
const uint16_t PROGMEM combo_control_shift_alt[] =      {KC_LCPO, KC_S, KC_A, COMBO_END};
const uint16_t PROGMEM combo_right_alt[] =              {KC_LAPO, KC_G, COMBO_END};
const uint16_t PROGMEM combo_alt_shift[] =              {KC_LALT, KC_S, COMBO_END};

/* -- */
const uint16_t PROGMEM combo_e_acute[] =                {KC_LCPO, KC_E, COMBO_END};
const uint16_t PROGMEM combo_c_cedilla[] =              {KC_LCPO, KC_I, COMBO_END};
const uint16_t PROGMEM combo_ea[] =                     {KC_LCPO, KC_A, COMBO_END};
const uint16_t PROGMEM combo_eo[] =                     {KC_LCPO, KC_O, COMBO_END};

const uint16_t PROGMEM combo_a_grave[] =                {LT(_MOUSE, KC_COMM), KC_A, COMBO_END};
const uint16_t PROGMEM combo_e_grave[] =                {LT(_MOUSE, KC_COMM), KC_E, COMBO_END};
const uint16_t PROGMEM combo_i_grave[] =                {LT(_MOUSE, KC_COMM), KC_I, COMBO_END};
const uint16_t PROGMEM combo_o_grave[] =                {LT(_MOUSE, KC_COMM), KC_O, COMBO_END};
const uint16_t PROGMEM combo_u_grave[] =                {LT(_MOUSE, KC_COMM), KC_U, COMBO_END};

const uint16_t PROGMEM combo_a_circumflex[] =           {KC_C, KC_A, COMBO_END};
const uint16_t PROGMEM combo_e_circumflex[] =           {KC_C, KC_E, COMBO_END};
const uint16_t PROGMEM combo_i_circumflex[] =           {KC_C, KC_I, COMBO_END};
const uint16_t PROGMEM combo_o_circumflex[] =           {KC_C, KC_O, COMBO_END};
const uint16_t PROGMEM combo_u_circumflex[] =           {KC_C, KC_U, COMBO_END};

const uint16_t PROGMEM combo_a_diaeresis[] =            {KC_T, KC_A, COMBO_END};
const uint16_t PROGMEM combo_e_diaeresis[] =            {KC_T, KC_E, COMBO_END};
const uint16_t PROGMEM combo_i_diaeresis[] =            {KC_T, KC_I, COMBO_END};
const uint16_t PROGMEM combo_o_diaeresis[] =            {KC_T, KC_O, COMBO_END};
const uint16_t PROGMEM combo_u_diaeresis[] =            {KC_T, KC_U, COMBO_END};
const uint16_t PROGMEM combo_y_diaeresis[] =            {KC_T, KC_Y, COMBO_END};

/* -- */
const uint16_t PROGMEM combo_ampersand[] =              {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_at_sign[] =                {KC_Q, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_backslash[] =              {KC_D, KC_R, COMBO_END};
const uint16_t PROGMEM combo_circumflex[] =             {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM combo_colon[] =                  {KC_C, KC_G, COMBO_END};
const uint16_t PROGMEM combo_dollar[] =                 {KC_D, KC_L, COMBO_END};
const uint16_t PROGMEM combo_equal[] =                  {KC_T, KC_H, COMBO_END};
const uint16_t PROGMEM combo_exclamation_mark[] =       {KC_O, KC_W, COMBO_END};
const uint16_t PROGMEM combo_grave[] =                  {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_hash[] =                   {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_minus[] =                  {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM combo_percent[] =                {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM combo_pipe[] =                   {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM combo_plus[] =                   {KC_T, KC_L, COMBO_END};
const uint16_t PROGMEM combo_question_mark[] =          {KC_B, KC_O, COMBO_END};
const uint16_t PROGMEM combo_quote[] =                  {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM combo_quote_double[] =           {KC_A, KC_U, COMBO_END};
const uint16_t PROGMEM combo_semicolon[] =              {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM combo_slash[] =                  {KC_S, KC_L, COMBO_END};
const uint16_t PROGMEM combo_star[] =                   {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_tilde[] =                  {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM combo_underscore[] =             {KC_S, KC_R, COMBO_END};

const uint16_t PROGMEM combo_angle_bracket_left[] =     {KC_C, KC_S, COMBO_END};
const uint16_t PROGMEM combo_angle_bracket_right[] =    {KC_S, KC_H, COMBO_END};

const uint16_t PROGMEM combo_bracket_left[] =           {KC_Q, KC_U, COMBO_END};
const uint16_t PROGMEM combo_bracket_right[] =          {KC_E, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_curly_bracket_left[] =     {KC_X, KC_E, COMBO_END};
const uint16_t PROGMEM combo_curly_bracket_right[] =    {KC_I, KC_Q, COMBO_END};
const uint16_t PROGMEM combo_parenthesis_left[] =       {KC_X, KC_U, COMBO_END};
const uint16_t PROGMEM combo_parenthesis_right[] =      {KC_I, KC_Y, COMBO_END};

/* One hand special */
const uint16_t PROGMEM combo_control_right[] =          {LT(_NUMERIC, KC_ENT), KC_R, COMBO_END};
const uint16_t PROGMEM combo_control_shift_right[] =    {LT(_NUMERIC, KC_ENT), KC_S, COMBO_END};

const uint16_t PROGMEM combo_shift_left[] =             {KC_LCPO, KC_LALT, COMBO_END};
// const uint16_t PROGMEM combo_altgr_left[] =             {LT(_MOUSE, KC_COMM), KC_LALT, COMBO_END};
// const uint16_t PROGMEM combo_del_left[] =               {GUI_T(KC_ESC), KC_K, COMBO_END};
const uint16_t PROGMEM combo_control_shift_left[] =     {LT(_MOUSE, KC_COMM), KC_LALT, COMBO_END};


/* Sequences fo keys */
combo_t key_combos[] = {
    [LEADER] = COMBO(combo_leader,                          KC_LEAD),
    [BOOTLOADER] = COMBO(combo_bootloader,                  QK_BOOTLOADER),

    [LAYER_ADJUST] = COMBO(combo_adjust,                    OSL(_ADJUST)),
    [LAYER_FN] = COMBO(combo_fn,                            OSL(_FN)),
    [LAYER_LEFT_HAND] = COMBO(combo_left_hand,              OSL(_LEFT_HAND)),

    /* -- */
    // [ENTER_SHIFTED] = COMBO(combo_enter_shifted,            S(KC_ENT)),
    [ALT_SHIFT] = COMBO(combo_alt_shift,                    A(S(XXXXXXX))),
    [CONTROL_SHIFT] = COMBO(combo_control_shift,            C(S(XXXXXXX))),
    [CONTROL_ALT] = COMBO(combo_control_alt,                C(A(XXXXXXX))),
    [CONTROL_SHIFT_ALT] = COMBO(combo_control_shift_alt,    C(S(A(XXXXXXX)))),
    [RIGHT_ALT] = COMBO(combo_right_alt,                    KC_RALT),

    /* French */
    [E_ACUTE] = COMBO(combo_e_acute,                        CS_E_ACUTE),
    [C_CEDILLA] = COMBO(combo_c_cedilla,                    CS_C_CEDILLA),
    [E_A] = COMBO(combo_ea,                                 CS_AE),
    [E_O] = COMBO(combo_eo,                                 CS_OE),

    [A_GRAVE] = COMBO(combo_a_grave,                        CS_A_GRAVE),
    [E_GRAVE] = COMBO(combo_e_grave,                        CS_E_GRAVE),
    [I_GRAVE] = COMBO(combo_i_grave,                        CS_I_GRAVE),
    [O_GRAVE] = COMBO(combo_o_grave,                        CS_O_GRAVE),
    [U_GRAVE] = COMBO(combo_u_grave,                        CS_U_GRAVE),

    [A_CIRCUMFLEX] = COMBO(combo_a_circumflex,              CS_A_CIRCUMFLEX),
    [E_CIRCUMFLEX] = COMBO(combo_e_circumflex,              CS_E_CIRCUMFLEX),
    [I_CIRCUMFLEX] = COMBO(combo_i_circumflex,              CS_I_CIRCUMFLEX),
    [O_CIRCUMFLEX] = COMBO(combo_o_circumflex,              CS_O_CIRCUMFLEX),
    [U_CIRCUMFLEX] = COMBO(combo_u_circumflex,              CS_U_CIRCUMFLEX),

    [A_DIAERESIS] = COMBO(combo_a_diaeresis,                CS_A_DIAERESIS),
    [E_DIAERESIS] = COMBO(combo_e_diaeresis,                CS_E_DIAERESIS),
    [I_DIAERESIS] = COMBO(combo_i_diaeresis,                CS_I_DIAERESIS),
    [O_DIAERESIS] = COMBO(combo_o_diaeresis,                CS_O_DIAERESIS),
    [U_DIAERESIS] = COMBO(combo_u_diaeresis,                CS_U_DIAERESIS),
    [Y_DIAERESIS] = COMBO(combo_y_diaeresis,                CS_Y_DIAERESIS),

    /* -- */
    [AMPERSAND] = COMBO(combo_ampersand,                    KC_AMPR),
    [AT_SIGN] = COMBO(combo_at_sign,                        KC_AT),
    [BACKSLASH] = COMBO(combo_backslash,                    KC_BSLS),
    [CIRCUMFLEX] = COMBO(combo_circumflex,                  KC_CIRC),
    [COLON] = COMBO(combo_colon,                            KC_COLON),
    [DOLLAR] = COMBO(combo_dollar,                          KC_DLR),
    [EQUAL] = COMBO(combo_equal,                            KC_EQL),
    [EXCLAMATION_MARK] = COMBO(combo_exclamation_mark,      KC_EXCLAIM),
    [GRAVE] = COMBO(combo_grave,                            KC_GRV),
    [HASH] = COMBO(combo_hash,                              KC_HASH),
    [MINUS] = COMBO(combo_minus,                            KC_MINS),
    [PERCENT] = COMBO(combo_percent,                        KC_PERC),
    [PIPE] = COMBO(combo_pipe,                              KC_PIPE),
    [PLUS] = COMBO(combo_plus,                              KC_PLUS),
    [QUESTION_MARK] = COMBO(combo_question_mark,            KC_QUESTION),
    [QUOTE] = COMBO(combo_quote,                            KC_QUOTE),
    [QUOTE_DOUBLE] = COMBO(combo_quote_double,              KC_DOUBLE_QUOTE),
    [SEMICOLON] = COMBO(combo_semicolon,                    KC_SEMICOLON),
    [SLASH] = COMBO(combo_slash,                            KC_SLSH),
    [STAR] = COMBO(combo_star,                              KC_ASTR),
    [TILDE] = COMBO(combo_tilde,                            KC_TILD),
    [UNDERSCORE] = COMBO(combo_underscore,                  KC_UNDS),

    [ANGLE_BRACKET_LEFT] = COMBO(combo_angle_bracket_left,      KC_LABK),
    [ANGLE_BRACKET_RIGHT] = COMBO(combo_angle_bracket_right,    KC_RABK),

    [BRACKET_LEFT] = COMBO(combo_bracket_left,                  KC_LEFT_BRACKET),
    [BRACKET_RIGHT] = COMBO(combo_bracket_right,                KC_RIGHT_BRACKET),
    [CURLY_BRACKET_LEFT] = COMBO(combo_curly_bracket_left,      KC_LEFT_CURLY_BRACE),
    [CURLY_BRACKET_RIGHT] = COMBO(combo_curly_bracket_right,    KC_RIGHT_CURLY_BRACE),
    [PARENTHESIS_LEFT] = COMBO(combo_parenthesis_left,          KC_LEFT_PAREN),
    [PARENTHESIS_RIGHT] COMBO(combo_parenthesis_right,          KC_RIGHT_PAREN),

    /* One hand special */
    [CONTROL_RIGHT] = COMBO(combo_control_right,                KC_RCTL),
    [CONTROL_SHIFT_RIGHT] = COMBO(combo_control_shift_right,    C(S(XXXXXXX))),

    [SHIFT_LEFT] = COMBO(combo_shift_left,                      KC_LSFT),
    // [ALTGR_LEFT] = COMBO(combo_altgr_left,                      KC_ALGR),
    [CONTROL_SHIFT_LEFT] = COMBO(combo_control_shift_left,      C(S(XXXXXXX))),
    // [DEL_LEFT] = COMBO(combo_del_left,                          KC_BSPC),
};
