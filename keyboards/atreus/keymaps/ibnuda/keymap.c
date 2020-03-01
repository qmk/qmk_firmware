#include QMK_KEYBOARD_H

typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
} td_state_t;

static td_state_t td_state;

int current_dance(qk_tap_dance_state_t *state);

void dance_tmb_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_tmb_reset(qk_tap_dance_state_t *state, void *user_data);

// enum for tap dances.
enum {
    TD_DLT_CTLDLT = 0,
    TD_SCLN_CLN,
    TD_LEFT_THUMB,
};

// enum for combos.
enum combos {
    // left hand combinations.
    COLON_COMMA,
    COMMA_DOT,
    DOT_P,
    Q_J,
    J_K,

    // right hand combinations.
    L_R,
    R_C,
    C_G,
    V_W,
    W_M,

    // both hands combinations.
    DOT_C,
    J_W,
    P_G,
    U_H,
    K_M,
};

enum {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MUIS
};

// thumb keys.
#define ALT_ENT   ALT_T(KC_ENT)
#define SFT_ESC   SFT_T(KC_ESC)

// home row mods.
#define CT_O RCTL_T(KC_O)
#define CT_N RCTL_T(KC_N)
#define SH_A RSFT_T(KC_A)
#define SH_S RSFT_T(KC_S)
#define AL_E RALT_T(KC_E)
#define AL_T RALT_T(KC_T)
#define GU_I RGUI_T(KC_I)
#define GU_D RGUI_T(KC_D)

// layer toggle.
#define LW_BSPC  LT(_LOWER, KC_BSPC)
#define RS_SPC   LT(_RAISE, KC_SPC)
#define RS_D     LT(_RAISE, KC_D)
#define LW_I     LT(_LOWER, KC_I)
#define MU_QUOT  LT(_MUIS, KC_QUOT)
#define MU_Z     LT(_MUIS, KC_Z)

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
#define CALDL  LCTL(LALT(KC_DELT))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define EXPLR  LGUI(KC_E)
#define LCKGUI LGUI(KC_L)
#define CONPST LSFT(KC_INS)
#define CLSGUI LALT(KC_F4)

// tap dances
#define CTL_DLT TD(TD_DLT_CTLDLT)
#define SM_CLN  TD(TD_SCLN_CLN)
#define LFT_TMB TD(TD_LEFT_THUMB)

// left hand combinations.
const uint16_t PROGMEM colon_comma_combo[] = {KC_SCLN, KC_COMM, COMBO_END};
const uint16_t PROGMEM comma_dot_combo[]   = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM dot_p_combo[]       = {KC_DOT, KC_P, COMBO_END};
const uint16_t PROGMEM q_j_combo[]         = {KC_Q, KC_J, COMBO_END};
const uint16_t PROGMEM j_k_combo[]         = {KC_J, KC_K, COMBO_END};

// right hand combinations.
const uint16_t PROGMEM l_r_combo[]         = {KC_L, KC_R, COMBO_END};
const uint16_t PROGMEM r_c_combo[]         = {KC_R, KC_C, COMBO_END};
const uint16_t PROGMEM c_g_combo[]         = {KC_C, KC_G, COMBO_END};
const uint16_t PROGMEM v_w_combo[]         = {KC_V, KC_W, COMBO_END};
const uint16_t PROGMEM w_m_combo[]         = {KC_W, KC_M, COMBO_END};

// both hand combinations.
const uint16_t PROGMEM dot_c_combo[]       = {KC_DOT, KC_C, COMBO_END};
const uint16_t PROGMEM j_w_combo[]         = {KC_J, KC_W, COMBO_END};
const uint16_t PROGMEM u_h_combo[]         = {KC_U, KC_H, COMBO_END};
const uint16_t PROGMEM p_g_combo[]         = {KC_P, KC_G, COMBO_END};
const uint16_t PROGMEM k_m_combo[]         = {KC_K, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    // left hand combinations.
    [COLON_COMMA]   = COMBO(colon_comma_combo,  KC_TAB),
    [COMMA_DOT]     = COMBO(comma_dot_combo,    KC_QUES),
    [DOT_P]         = COMBO(dot_p_combo,        KC_UNDS),
    [Q_J]           = COMBO(q_j_combo,          LCTL(KC_W)),
    [J_K]           = COMBO(j_k_combo,          KC_DELT),

    // right hand combinations.
    [L_R]           = COMBO(l_r_combo,          KC_BSPC),
    [R_C]           = COMBO(r_c_combo,          KC_SLSH),
    [C_G]           = COMBO(c_g_combo,          KC_MINS),
    [V_W]           = COMBO(v_w_combo,          KC_APP),
    [W_M]           = COMBO(w_m_combo,          KC_DELT),

    // both hand combinations.
    [DOT_C]         = COMBO(dot_c_combo,        KC_PGUP),
    [J_W]           = COMBO(j_w_combo,          KC_PGDN),
    [U_H]           = COMBO(u_h_combo,          KC_ENT),
    [P_G]           = COMBO(p_g_combo,          KC_HOME),
    [K_M]           = COMBO(k_m_combo,          KC_END),
};

void dance_dlt_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_DELT);
    } else {
        register_code16(C(KC_DELT));
    }
}

void dance_dlt_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_DELT);
    } else {
        unregister_code16(C(KC_DELT));
    }
}

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LSFT);
    }
    register_code(KC_SCLN);
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
    }
    unregister_code(KC_SCLN);
}

int current_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    } else {
        return 3;
    }
}

void dance_tmb_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = current_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_ESC);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
            register_code16(KC_DELT);
            break;
    }
}

void dance_tmb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_ESC);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_DELT);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_DLT_CTLDLT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dlt_finished, dance_dlt_reset),
    [TD_SCLN_CLN]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_LEFT_THUMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tmb_finished, dance_tmb_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
    SM_CLN, KC_COMM,KC_DOT, KC_P,   KC_Y,                       KC_F,   KC_G,   KC_C,   KC_R,   KC_L,
    SH_A,   CT_O,   AL_E,   KC_U,   GU_I,                       GU_D,   KC_H,   AL_T,   CT_N,   SH_S,
    MU_QUOT,KC_Q,   KC_J,   KC_K,   KC_X,                       KC_B,   KC_M,   KC_W,   KC_V,   MU_Z,
    _______,_______,_______,_______,LW_BSPC,SFT_ESC,    ALT_ENT,RS_SPC, _______,_______,_______,_______
),

[_RAISE] = LAYOUT(
    KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,                    KC_BSLS,KC_7,   KC_8,   KC_9,   KC_ASTR ,
    KC_HASH,KC_LEFT,KC_DOWN,KC_RGHT,KC_DLR,                     KC_EQL, KC_4,   KC_5,   KC_6,   KC_TILD ,
    KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,                    KC_GRV, KC_1,   KC_2,   KC_3,   KC_PLUS ,
    _______,_______,_______,_______,ADDDD,  _______,    ALT_ENT,RS_SPC, _______,KC_0,   _______,_______
),
[_LOWER] = LAYOUT(
    KC_ESC, KC_QUES,KC_UNDS,KC_F1,  KC_F2,                      KC_F3,  KC_F4,  KC_MINS,KC_SLSH,KC_BSPC ,
    KC_LSFT,KC_TAB, KC_PGUP,KC_F5,  KC_F6,                      KC_F7,  KC_F8,  KC_HOME,KC_LALT,KC_ENT  ,
    KC_CLCK,KC_SLCK,KC_PGDN,KC_F9,  KC_F10,                     KC_F11, KC_F12, KC_END, KC_INS, KC_SLSH ,
    _______,_______,_______,_______,ADDDD,  _______,    KC_DELT,ADDDD,  _______,_______,_______,_______
),
[_ADJUST] = LAYOUT(
    _______,EXPLR,  KC_UP,  PRVTAB, PRVWIN,                     NXTWIN, NXTTAB, _______,_______,LCKGUI,
    TSKMGR, KC_LEFT,KC_DOWN,KC_RGHT,UPTAB,                      DNTAB,  KC_ENT, KC_LGUI,_______,CALDL,
    _______,CLSGUI, _______,CONPST, RESET,                      _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______
),
[_MUIS] = LAYOUT(
    _______,KC_BTN2,KC_MS_U,KC_BTN1,_______,                    _______,KC_BTN1,KC_MS_U,KC_BTN2,_______,
    _______,KC_MS_L,KC_MS_D,KC_MS_R,_______,                    _______,KC_MS_L,KC_MS_D,KC_MS_R,_______,
    _______,_______,KC_WH_D,KC_WH_U,_______,                    _______,KC_WH_U,KC_WH_D,_______,_______,
    _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______
),
};
