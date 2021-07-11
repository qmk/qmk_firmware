#pragma once
#include "quantum.h"

// enum for combos.
enum combos {
    // left hand combinations.
    COLON_COMMA,
    COMMA_DOT,
    DOT_P,
    QUOT_Q,
    Q_J,
    J_K,

    // right hand combinations.
    L_R,
    R_C,
    C_G,
    V_W,
    W_M,

    // both hands combinations.
    J_W,
};

// left hand combinations.
const uint16_t PROGMEM colon_comma_combo[] = {KC_SCLN, KC_COMM, COMBO_END};
const uint16_t PROGMEM comma_dot_combo[]   = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM dot_p_combo[]       = {KC_DOT, KC_P, COMBO_END};
const uint16_t PROGMEM quot_q_combo[]      = {KC_QUOT, KC_Q, COMBO_END};
const uint16_t PROGMEM q_j_combo[]         = {KC_Q, KC_J, COMBO_END};
const uint16_t PROGMEM j_k_combo[]         = {KC_J, KC_K, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM l_r_combo[]         = {KC_L, KC_R, COMBO_END};
const uint16_t PROGMEM r_c_combo[]         = {KC_R, KC_C, COMBO_END};
const uint16_t PROGMEM c_g_combo[]         = {KC_C, KC_G, COMBO_END};
const uint16_t PROGMEM v_w_combo[]         = {KC_V, KC_W, COMBO_END};
const uint16_t PROGMEM w_m_combo[]         = {KC_W, KC_M, COMBO_END};

// both hand combinations.
const uint16_t PROGMEM j_w_combo[]         = {KC_J, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // left hand combinations.
    [COLON_COMMA]   = COMBO(colon_comma_combo,  KC_TAB),
    [COMMA_DOT]     = COMBO(comma_dot_combo,    KC_QUES),
    [DOT_P]         = COMBO(dot_p_combo,        KC_UNDS),
    [QUOT_Q]        = COMBO(quot_q_combo,       KC_ENT),
    [Q_J]           = COMBO(q_j_combo,          LCTL(KC_W)),
    [J_K]           = COMBO(j_k_combo,          KC_DELT),

    // right hand combinations.
    [L_R]           = COMBO(l_r_combo,          KC_BSPC),
    [R_C]           = COMBO(r_c_combo,          KC_SLSH),
    [C_G]           = COMBO(c_g_combo,          KC_MINS),
    [V_W]           = COMBO(v_w_combo,          KC_APP),
    [W_M]           = COMBO(w_m_combo,          KC_DELT),

    // both hand combinations.
    [J_W]           = COMBO(j_w_combo,          KC_ENT),
};
