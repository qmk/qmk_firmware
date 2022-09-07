/* Copyright 2021 Ibnu D. Aji
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
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

// enum for combos.
enum combos {
    // left hand combinations.
    L_U_PINKY_RING,
    L_U_RING_MIDDLE,
    L_U_RING_INDEX,
    L_U_MIDDLE_INDEX,
    L_U_MIDDLE_INNER_INDEX,
    L_U_INDEX_INNER_INDEX,
    L_L_PINKY_RING,
    L_L_RING_MIDDLE,
    L_L_RING_INDEX,
    L_L_MIDDLE_INDEX,
    L_L_INDEX_INNER_INDEX,

    L_U_RING_MIDDLE_INDEX,
    L_L_RING_MIDDLE_INDEX,

    // right hand combinations.
    R_U_PINKY_RING,
    R_U_RING_MIDDLE,
    R_U_RING_INDEX,
    R_U_MIDDLE_INDEX,
    R_U_MIDDLE_INNER_INDEX,
    R_U_INNER_INNER_INDEX,
    R_L_PINKY_RING,
    R_L_RING_MIDDLE,
    R_L_MIDDLE_INDEX,
    R_L_RING_INDEX,
    R_L_INDEX_INNER_INDEX,

    R_U_RING_MIDDLE_INDEX,
    R_L_RING_MIDDLE_INDEX,

    // both hands combinations.
    B_L_MIDDLE_MIDDLE,
};

enum {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// keycode abstraction
#define LUP  KC_Q
#define LUR  KC_V
#define LUM  KC_C
#define LUI  KC_P
#define LUII KC_B
#define LMP  KC_R
#define LMR  KC_S
#define LMM  KC_T
#define LMI  KC_H
#define LMII KC_D
#define LLP  KC_QUOT
#define LLR  KC_J
#define LLM  KC_G
#define LLI  KC_K
#define LLII KC_X

#define RUP  KC_Z
#define RUR  KC_Y
#define RUM  KC_U
#define RUI  KC_L
#define RUII KC_DOT
#define RMP  KC_O
#define RMR  KC_I
#define RMM  KC_A
#define RMI  KC_N
#define RMII KC_F
#define RLP  KC_SLSH
#define RLR  KC_COMM
#define RLM  KC_W
#define RLI  KC_M
#define RLII KC_SCLN

// thumb keys.
#define TRAISE   TG(_RAISE)
#define AL_ENT   ALT_T(KC_ENT)
#define SF_BSPC  SFT_T(KC_BSPC)
#define CT_ESC   CTL_T(KC_ESC)

// home row mods.
#define CTLR    LCTL_T(LMR)
#define CTRR    RCTL_T(RMR)
#define CT_LEFT LCTL_T(KC_LEFT)
#define CT_SIX  RCTL_T(KC_6)

#define SHLP    LSFT_T(LMP)
#define SHRP    RSFT_T(RMP)
#define SH_HASH LSFT_T(KC_HASH)
#define SH_ZERO RSFT_T(KC_0)

#define ALLM    LALT_T(LMM)
#define ALRM    RALT_T(RMM)
#define AL_DOWN LALT_T(KC_DOWN)
#define AL_FIVE RALT_T(KC_5)

#define GULII   RGUI_T(LMII)
#define GURII   LGUI_T(RMII)
#define GU_DLR  RGUI_T(KC_DLR)
#define GU_EQL  LGUI_T(KC_EQL)

// layer toggle.
#define LW_E     LT(_LOWER, KC_E)
#define RS_SPC   LT(_RAISE, KC_SPC)
#define LW_RMI   LT(_LOWER, RMI)
#define RS_LMI   LT(_RAISE, LMI)

// idk, man. not used, i guess.
#define ADDDD    MO(_ADJUST)

// common shortcuts for windows and linux that i use.
#define NXTTAB LCTL(KC_PGDN)
#define PRVTAB LCTL(KC_PGUP)
#define UPTAB  LCTL(LSFT(KC_PGUP))
#define DNTAB  LCTL(LSFT(KC_PGDN))
#define NXTWIN LALT(KC_TAB)
#define PRVWIN LALT(LSFT(KC_TAB))
#define CALDL  LCTL(LALT(KC_DELT))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define EXPLR  LGUI(KC_E)
#define LCKGUI LGUI(KC_L)
#define CONPST LSFT(KC_INS)
#define CLSGUI LALT(KC_F4)

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

const uint16_t PROGMEM lu_r_m_i_combo[]   = {LUR, LUM, LUI, COMBO_END};
const uint16_t PROGMEM ll_r_m_i_combo[]   = {LLR, LLM, LLI, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM ru_p_r_combo[]      = {RUP, RUR,  COMBO_END};
const uint16_t PROGMEM ru_r_m_combo[]      = {RUR, RUM,  COMBO_END};
const uint16_t PROGMEM ru_r_i_combo[]      = {RUR, RUI,  COMBO_END};
const uint16_t PROGMEM ru_m_i_combo[]      = {RUM, RUI,  COMBO_END};
const uint16_t PROGMEM ru_m_ii_combo[]     = {RUM, RUII, COMBO_END};
const uint16_t PROGMEM ru_i_ii_combo[]     = {RUI, RUII, COMBO_END};
const uint16_t PROGMEM rl_p_r_combo[]      = {RLP, RLR,  COMBO_END};
const uint16_t PROGMEM rl_r_m_combo[]      = {RLR, RLM,  COMBO_END};
const uint16_t PROGMEM rl_r_i_combo[]      = {RLR, RLI,  COMBO_END};
const uint16_t PROGMEM rl_m_i_combo[]      = {RLM, RLI,  COMBO_END};
const uint16_t PROGMEM rl_i_ii_combo[]     = {RLI, RLII, COMBO_END};

const uint16_t PROGMEM ru_r_m_i_combo[]   =  {RUR, RUM, RUI, COMBO_END};
const uint16_t PROGMEM rl_r_m_i_combo[]   =  {RLR, RLM, RLI, COMBO_END};

// both hand combinations.
const uint16_t PROGMEM bl_m_m_combo[]      = {LLM, RLM, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // left hand combinations.
    [L_U_PINKY_RING]          = COMBO(lu_p_r_combo,  KC_TAB),
    [L_U_RING_MIDDLE]         = COMBO(lu_r_m_combo,  KC_QUES),
    [L_U_RING_INDEX]          = COMBO(lu_r_i_combo,  PRVTAB),
    [L_U_MIDDLE_INDEX]        = COMBO(lu_m_i_combo,  KC_UNDS),
    [L_U_MIDDLE_INNER_INDEX]  = COMBO(lu_m_ii_combo, KC_ENT),
    [L_U_INDEX_INNER_INDEX]   = COMBO(lu_i_ii_combo, KC_PIPE),
    [L_L_PINKY_RING]          = COMBO(ll_p_r_combo,  KC_ENT),
    [L_L_RING_MIDDLE]         = COMBO(ll_r_m_combo,  LCTL(KC_W)),
    [L_L_RING_INDEX]          = COMBO(ll_r_i_combo,  KC_TAB),
    [L_L_MIDDLE_INDEX]        = COMBO(ll_m_i_combo,  KC_DELT),
    [L_L_INDEX_INNER_INDEX]   = COMBO(ll_i_ii_combo, KC_TILD),

    [L_U_RING_MIDDLE_INDEX]   = COMBO(lu_r_m_i_combo, KC_PIPE),
    [L_L_RING_MIDDLE_INDEX]   = COMBO(ll_r_m_i_combo, KC_TILD),

    // right hand combinations.
    [R_U_PINKY_RING]          = COMBO(ru_p_r_combo,  KC_BSPC),
    [R_U_RING_MIDDLE]         = COMBO(ru_r_m_combo,  KC_SLSH),
    [R_U_RING_INDEX]          = COMBO(ru_r_i_combo,  NXTTAB),
    [R_U_MIDDLE_INDEX]        = COMBO(ru_m_i_combo,  KC_MINS),
    [R_U_MIDDLE_INNER_INDEX]  = COMBO(ru_m_ii_combo, KC_ENT),
    [R_U_INNER_INNER_INDEX]   = COMBO(ru_i_ii_combo, KC_BSLS),
    [R_L_PINKY_RING]          = COMBO(rl_p_r_combo,  KC_BSLS),
    [R_L_RING_MIDDLE]         = COMBO(rl_r_m_combo,  KC_APP),
    [R_L_RING_INDEX]          = COMBO(rl_r_i_combo,  LSFT(KC_TAB)),
    [R_L_MIDDLE_INDEX]        = COMBO(rl_m_i_combo,  KC_DELT),
    [R_L_INDEX_INNER_INDEX]   = COMBO(rl_i_ii_combo, KC_GRV),

    [R_U_RING_MIDDLE_INDEX]   = COMBO(ru_r_m_i_combo, KC_BSLS),
    [R_L_RING_MIDDLE_INDEX]   = COMBO(rl_r_m_i_combo, KC_GRV),

    // both hand combinations.
    [B_L_MIDDLE_MIDDLE]       = COMBO(bl_m_m_combo,  KC_ENT),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC, LUP,    LUR,    LUM,    LUI,    LUII,            RUII,   RUI,    RUM,    RUR,    RUP,   KC_BSPC, KC_BSPC,
        KC_LCTL,SHLP,   CTLR,   ALLM,   RS_LMI, GULII,           GURII,  LW_RMI, ALRM,   CTRR,   SHRP,  KC_ENT,
        KC_LSFT,LLP,    LLR,    LLM,    LLI,    LLII,            RLII,   RLI,    RLM,    RLR,    RLP,   KC_RSFT,MO(1),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_E,   SF_BSPC,         AL_ENT, RS_SPC, KC_LALT,               KC_RGUI,KC_RCTL
    ),
    [1] = LAYOUT_all(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,            KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL, KC_BSPC,
        KC_LCTL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,         KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,   KC_SCLN,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,MO(2),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_E,   SF_BSPC,         AL_ENT, RS_SPC, KC_LALT,                KC_RGUI,KC_RCTL
    ),
    [2] = LAYOUT_all(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,           KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_F13,
        KC_LCTL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,         KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,   KC_SCLN,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   QK_BOOT,         KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,MO(1),
        KC_LGUI,KC_LALT,        KC_LGUI,LW_E,   SF_BSPC,         AL_ENT, RS_SPC, KC_LALT,                KC_RGUI,KC_RCTL
    ),
};
