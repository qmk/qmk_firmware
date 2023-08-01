/* Copyright 2020 Ibnu D. Aji
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

// enum for combos.
enum combos {
    // left hand combinations.
    Q_W,
    W_E,
    E_R,
    Z_X,
    C_X,
    C_V,

    // right hand combinations.
    P_O,
    O_U,
    U_I,
    SLASH_DOT,
    DOT_COMMA,
    COMMA_M,

    // both hands combinations.
    SLASH_Z,
    COMMA_X,
    J_F,
};

enum {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// thumb keys.
#define ALT_ENT   ALT_T(KC_ENT)
#define SFT_ESC   SFT_T(KC_ESC)

// home row mods.
#define CT_S    RCTL_T(KC_S)
#define CT_L    RCTL_T(KC_L)
#define SH_A    RSFT_T(KC_A)
#define SH_SCLN RSFT_T(KC_SCLN)
#define AL_D    RALT_T(KC_D)
#define AL_K    RALT_T(KC_K)
#define GU_G    RGUI_T(KC_G)
#define GU_H    RGUI_T(KC_H)

// layer toggle.
#define LW_BSPC  LT(_LOWER, KC_BSPC)
#define RS_SPC   LT(_RAISE, KC_SPC)

// idk, man. not used, i guess.
#define RAISE    MO(_RAISE)
#define LOWER    MO(_LOWER)
#define ADDDD    MO(_ADJUST)
#define MUIS     MO(_MUIS)

// common shortcuts for windows and linux that i use.
#define NXTTAB LCTL(KC_PGDN)
#define PRVTAB LCTL(KC_PGUP)
#define UPTAB  LCTL(LSFT(KC_PGUP))
#define DNTAB  LCTL(LSFT(KC_PGDN))
#define NXTWIN LALT(KC_TAB)
#define PRVWIN LALT(LSFT(KC_TAB))
#define CALDL  LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define EXPLR  LGUI(KC_E)
#define LCKGUI LGUI(KC_L)
#define CONPST LSFT(KC_INS)
#define CLSGUI LALT(KC_F4)

// left hand combinations.
const uint16_t PROGMEM q_w_combo[]          = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM w_e_combo[]          = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM e_r_combo[]          = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM z_x_combo[]          = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM x_c_combo[]          = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM c_v_combo[]          = {KC_C, KC_V, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM p_o_combo[]          = {KC_P,    KC_O,   COMBO_END};
const uint16_t PROGMEM o_u_combo[]          = {KC_O,    KC_U,   COMBO_END};
const uint16_t PROGMEM u_i_combo[]          = {KC_U,    KC_I,   COMBO_END};
const uint16_t PROGMEM slash_dot_combo[]    = {KC_SLSH, KC_DOT, COMBO_END};
const uint16_t PROGMEM dot_comma_combo[]    = {KC_DOT,  KC_COMM,COMBO_END};
const uint16_t PROGMEM comma_m_combo[]      = {KC_COMM, KC_M,   COMBO_END};

// both hand combinations.
const uint16_t PROGMEM z_slash_combo[]       = {KC_Z, KC_SLSH, COMBO_END};
const uint16_t PROGMEM x_comma_combo[]       = {KC_X, KC_COMM, COMBO_END};
const uint16_t PROGMEM j_f_combo[]           = {KC_F, KC_J,    COMBO_END};

combo_t key_combos[] = {
    // left hand combinations.
    [Q_W]           = COMBO(q_w_combo, KC_TAB),
    [W_E]           = COMBO(w_e_combo, KC_DQT),
    [E_R]           = COMBO(e_r_combo, KC_UNDS),
    [Z_X]           = COMBO(z_x_combo, KC_ENT),
    [C_X]           = COMBO(x_c_combo, LCTL(KC_W)),
    [C_V]           = COMBO(c_v_combo, KC_DEL),

    // right hand combinations.
    [P_O]           = COMBO(p_o_combo,       KC_BSPC),
    [O_U]           = COMBO(o_u_combo,       KC_QUOT),
    [U_I]           = COMBO(u_i_combo,       KC_MINS),
    [SLASH_DOT]     = COMBO(slash_dot_combo, KC_PIPE),
    [DOT_COMMA]     = COMBO(dot_comma_combo, KC_APP),
    [COMMA_M]       = COMBO(comma_m_combo,   KC_DEL),

    // both hand combinations.
    [SLASH_Z]       = COMBO(z_slash_combo, KC_HOME),
    [COMMA_X]       = COMBO(x_comma_combo, KC_END),
    [J_F]           = COMBO(j_f_combo,     KC_ENT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_3x5_3(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    SH_A,   CT_S,   AL_D,   KC_F,   GU_G,       GU_H,   KC_J,   AL_K,   CT_L,   SH_SCLN,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,
                    LOWER,  KC_BSPC,SFT_ESC,    ALT_ENT,KC_SPC, RAISE
),

[_RAISE] = LAYOUT_split_3x5_3(
    KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,    KC_BSLS,KC_7,   KC_8,   KC_9,   KC_ASTR ,
    KC_HASH,KC_LEFT,KC_DOWN,KC_RGHT,KC_DLR,     KC_EQL, KC_4,   KC_5,   KC_6,   KC_0 ,
    KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,    KC_GRV, KC_1,   KC_2,   KC_3,   KC_PLUS ,
                    LOWER,  ADDDD,  _______,    ALT_ENT,RS_SPC, RAISE
),
[_LOWER] = LAYOUT_split_3x5_3(
    KC_ESC, KC_QUES,KC_UNDS,KC_F1,  KC_F2,      KC_F3,  KC_F4,  KC_MINS,KC_SLSH,KC_BSPC ,
    KC_LSFT,KC_TAB, KC_PGUP,KC_F5,  KC_F6,      KC_F7,  KC_F8,  KC_HOME,KC_LALT,KC_ENT  ,
    KC_CAPS,KC_SCRL,KC_PGDN,KC_F9,  KC_F10,     KC_F11, KC_F12, KC_END, KC_INS, KC_SLSH ,
                    LOWER,  _______,_______,    _______,ADDDD,  RAISE
),
[_ADJUST] = LAYOUT_split_3x5_3(
    _______,EXPLR,  KC_UP,  PRVTAB, PRVWIN,     NXTWIN, NXTTAB, _______,_______,LCKGUI,
    TSKMGR, KC_LEFT,KC_DOWN,KC_RGHT,UPTAB,      DNTAB,  KC_ENT, KC_LGUI,_______,CALDL,
    _______,CLSGUI, _______,CONPST, QK_BOOT,      _______,_______,_______,_______,_______,
                    _______,_______,_______,    _______,_______,_______
),
};
