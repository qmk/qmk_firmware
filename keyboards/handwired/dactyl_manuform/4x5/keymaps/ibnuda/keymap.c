#include QMK_KEYBOARD_H

#include "ibnuda.h"

#define TAB KC_TAB
#define GUI KC_LGUI
#define MIN KC_MINS
#define SLS KC_SLSH
#define CTL KC_LCTL
#define DEL KC_DELT
#define QUE KC_QUES
#define ___ KC_NO

// clang-format off
#define LAYOUT_dm_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
              KTA, KTB, KTC, KTD, KTE, KTF            \
  ) \
  LAYOUT_wrapper( \
    K01, K02, K03, K04, K05,                   K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15,                   K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25,                   K26, K27, K28, K29, K2A, \
         TAB, KTA,                                  KTF, SLS,           \
                            KTB, KTC, KTD, KTE,                         \
                            CTL, DEL, QUE, CTL,                         \
                            ___, ___, ___, ___                          \
  )

#define LAYOUT_dm_base_wrapper(...)       LAYOUT_dm_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_dm_base_wrapper(
    LUP,    LUR,    LUM,    LUI,    LUII,       RUII,   RUI,    RUM,    RUR,    RUP,
    SHLP,   CTLR,   ALLM,   LMI,    GULII,      GURII,  RMI,    ALRM,   CTRR,   SHRP,
    LLP,    LLR,    LLM,    LLI,    LLII,       RLII,   RLI,    RLM,    RLR,    RLP,
                    CT_ESC, LW_E,   SF_BSPC,    AL_ENT, RS_SPC, TRAISE
),

[_RAISE] = LAYOUT_dm_base_wrapper(
    KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,    KC_BSLS,KC_7,   KC_8,   KC_9,   KC_ASTR ,
    KC_HASH,CT_LEFT,AL_DOWN,KC_RGHT,KC_DLR,     GU_EQL, KC_4,   AL_FIVE,CT_SIX, SH_ZERO ,
    KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,    KC_GRV, KC_1,   KC_2,   KC_3,   KC_PLUS ,
                    _______,ADDDD  ,_______,    _______,RS_SPC, _______
),
[_LOWER] = LAYOUT_dm_base_wrapper(
    KC_ESC, KC_QUES,KC_UNDS,KC_F1,  KC_F2,      KC_F3,  KC_F4,  KC_MINS,KC_SLSH,KC_BSPC ,
    KC_LSFT,KC_PSCR,KC_PGUP,KC_F5,  KC_F6,      KC_F7,  KC_F8,  KC_HOME,KC_LALT,KC_ENT  ,
    KC_CLCK,KC_SLCK,KC_PGDN,KC_F9,  KC_F10,     KC_F11, KC_F12, KC_END, KC_INS, KC_SLSH ,
                    _______,_______,_______,    _______,ADDDD,  _______
),
[_ADJUST] = LAYOUT_dm_base_wrapper(
    _______,EXPLR,  KC_UP,  PRVTAB, PRVWIN,     NXTWIN, NXTTAB, _______,_______,LCKGUI,
    TSKMGR, KC_LEFT,KC_DOWN,KC_RGHT,UPTAB,      DNTAB,  KC_ENT, KC_LGUI,_______,CALDL,
    _______,CLSGUI, _______,CONPST, RESET,      _______,_______,_______,_______,_______,
                    _______,_______,_______,    _______,_______,_______
),};
// clang-format on

