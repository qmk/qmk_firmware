#pragma once
#include "quantum.h"

#include "abstraction.h"

// enum for combos.
enum combos {
    // left hand combinations.
    R_U_PINKY_RING,
    R_U_RING_MIDDLE,
    R_U_RING_INDEX,
    R_U_MIDDLE_INDEX,
    R_U_MIDDLE_INNER_INDEX,
    R_U_INDEX_INNER_INDEX,
    R_L_PINKY_RING,
    R_L_RING_MIDDLE,
    R_L_RING_INDEX,
    R_L_MIDDLE_INDEX,
    R_L_INDEX_INNER_INDEX,

    // right hand combinations.
    L_U_PINKY_RING,
    L_U_RING_MIDDLE,
    L_U_RING_INDEX,
    L_U_MIDDLE_INDEX,
    L_U_MIDDLE_INNER_INDEX,
    L_U_INNER_INNER_INDEX,
    L_L_PINKY_RING,
    L_L_RING_MIDDLE,
    L_L_MIDDLE_INDEX,
    L_L_RING_INDEX,
    L_L_INDEX_INNER_INDEX,

    // both hands combinations.
    B_L_MIDDLE_MIDDLE,
};

// left hand combinations.
const uint16_t PROGMEM lu_p_r_combo[]     = {LUP, LUR,  COMBO_END};
const uint16_t PROGMEM lu_r_m_combo[]     = {LUR, LUM,  COMBO_END};
const uint16_t PROGMEM lu_r_i_combo[]     = {LUR, LUI,  COMBO_END};
const uint16_t PROGMEM lu_m_i_combo[]     = {LUM, LUI,  COMBO_END};
const uint16_t PROGMEM lu_m_ii_combo[]    = {LUM, LUII, COMBO_END};
const uint16_t PROGMEM lu_i_ii_combo[]    = {LUI, LUII, COMBO_END};
const uint16_t PROGMEM ll_p_r_combo[]     = {LLP, LLR,  COMBO_END};
const uint16_t PROGMEM ll_r_m_combo[]     = {LLR, LLM,  COMBO_END};
const uint16_t PROGMEM ll_r_i_combo[]     = {LLR, LLI,  COMBO_END};
const uint16_t PROGMEM ll_m_i_combo[]     = {LLM, LLI,  COMBO_END};
const uint16_t PROGMEM ll_i_ii_combo[]    = {LLI, LLII, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM ru_p_r_combo[]      = {RUP, RUR, COMBO_END};
const uint16_t PROGMEM ru_r_m_combo[]      = {RUR, RUM, COMBO_END};
const uint16_t PROGMEM ru_r_i_combo[]      = {RUR, RUI, COMBO_END};
const uint16_t PROGMEM ru_m_i_combo[]      = {RUM, RUI, COMBO_END};
const uint16_t PROGMEM ru_m_ii_combo[]     = {RUM, RUII, COMBO_END};
const uint16_t PROGMEM ru_i_ii_combo[]     = {RUI, RUII, COMBO_END};
const uint16_t PROGMEM rl_p_r_combo[]      = {RLP, RLR, COMBO_END};
const uint16_t PROGMEM rl_r_m_combo[]      = {RLR, RLM, COMBO_END};
const uint16_t PROGMEM rl_r_i_combo[]      = {RLR, RLI, COMBO_END};
const uint16_t PROGMEM rl_m_i_combo[]      = {RLM, RLI, COMBO_END};
const uint16_t PROGMEM rl_i_ii_combo[]     = {RLI, RLII, COMBO_END};

// both hand combinations.
const uint16_t PROGMEM bl_m_m_combo[]      = {LLM, RLM, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // left hand combinations.
    [R_U_PINKY_RING]          = COMBO(lu_p_r_combo,  KC_TAB),
    [R_U_RING_MIDDLE]         = COMBO(lu_r_m_combo,  KC_QUES),
    [R_U_RING_INDEX]          = COMBO(lu_r_i_combo,  PRVTAB),
    [R_U_MIDDLE_INDEX]        = COMBO(lu_m_i_combo,  KC_UNDS),
    [R_U_MIDDLE_INNER_INDEX]  = COMBO(lu_m_ii_combo, KC_ENT),
    [R_U_INDEX_INNER_INDEX]   = COMBO(lu_i_ii_combo, KC_PIPE),
    [R_L_PINKY_RING]          = COMBO(ll_p_r_combo,  KC_ENT),
    [R_L_RING_MIDDLE]         = COMBO(ll_r_m_combo,  LCTL(KC_W)),
    [R_L_RING_INDEX]          = COMBO(ll_r_i_combo,  KC_TAB),
    [R_L_MIDDLE_INDEX]        = COMBO(ll_m_i_combo,  KC_DELT),
    [R_L_INDEX_INNER_INDEX]   = COMBO(ll_i_ii_combo, KC_TILD),

    // right hand combinations.
    [L_U_PINKY_RING]          = COMBO(ru_p_r_combo,  KC_BSPC),
    [L_U_RING_MIDDLE]         = COMBO(ru_r_m_combo,  KC_SLSH),
    [L_U_RING_INDEX]          = COMBO(ru_r_i_combo,  NXTTAB),
    [L_U_MIDDLE_INDEX]        = COMBO(ru_m_i_combo,  KC_MINS),
    [L_U_MIDDLE_INNER_INDEX]  = COMBO(ru_m_ii_combo, KC_ENT),
    [L_U_INNER_INNER_INDEX]   = COMBO(ru_i_ii_combo, KC_BSLS),
    [L_L_PINKY_RING]          = COMBO(rl_p_r_combo,  KC_BSLS),
    [L_L_RING_MIDDLE]         = COMBO(rl_r_m_combo,  KC_APP),
    [L_L_RING_INDEX]          = COMBO(rl_r_i_combo,  LSFT(KC_TAB)),
    [L_L_MIDDLE_INDEX]        = COMBO(rl_m_i_combo,  KC_DELT),
    [L_L_INDEX_INNER_INDEX]   = COMBO(rl_i_ii_combo, KC_GRV),

    // both hand combinations.
    [B_L_MIDDLE_MIDDLE]       = COMBO(bl_m_m_combo,  KC_ENT),
};