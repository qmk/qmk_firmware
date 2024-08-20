#include QMK_KEYBOARD_H
#include "version.h"

enum custom_keycodes {
    MAC_DLAY = SAFE_RANGE,
    O_LNK_DSC,
    O_NXT_VZ_HD,
    O_PRV_VZ_HD,
    O_GO_TO,
    O_MRK_TR,
    O_CT_TR,
    O_CPY_TR,
    O_PST_TR,
    O_NXT_LVL_HD,
    O_PRV_LVL_HD,
    O_BEF_SB_HD,
    O_RNM_HD,
    O_TG_CD_BF,
    YAS_EXPAND,
    SWIPER,
    RIPGREP,
    AVY,
    CNSL_IMNU,
    POS_REG_S,
    POS_REG_J,
    TXT_REG_S,
    TXT_REG_I,
    MRK_F_LOC,
    MRK_B_LOC,
    MRK_F_GLB,
    MRK_B_GLB,
    SHELL,
    MULT_SHELL,
    MC_NXT,
    MC_PREV,
    MC_ALL,
    MC_UN_NXT,
    MC_UN_PREV,
    EXP_SYM,
    EXP_WORD,
    EXP_I_PAR,
    EXP_O_PAR,
    EXP_I_QUO,
    EXP_O_QUO,
    EXP_COM,
    DRG_UP,
    DRG_DWN,
    SWITCH_BFR,
    SPLT_WND_VRT,
    SPLT_WND_HRZ,
    KLL_WND,
    ONLY_WND,
    KLL_BFF,
    KLL_FRM,
    WND_MV_UP,
    WND_MV_LFT,
    WND_MV_RT,
    WND_MV_DWN,
    SHFT_RG_F,
    SHFT_RG_B,
    SCRL_UP_1,
    SCRL_DWN_1,
    HLF_SCRL_F,
    HLF_SCRL_B,
    FOR_PAR,
    BACK_PAR,
    UNDO,
    BEACON,
    TO_26,
    DBUG_HELP,
    TOG_LIN_NUM,
    TOG_TRN_LN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_UP,          KC_DOWN,
    KC_BSPC,        LT(13, KC_Q),   MT(MOD_LGUI, KC_W), LT(15, KC_E), LT(5,KC_R),   KC_T,           KC_NO,                                          KC_NO,          KC_Y,           LT(6, KC_U),    LT(9, KC_I),    MT(MOD_RGUI, KC_O), KC_P,       UNDO,
    LT(11, KC_ESC), MT(MOD_LSFT, KC_A), MT(MOD_LCTL, KC_S), LALT_T(KC_D), LT(1,KC_F), KC_G,                                                                         KC_H,           LT(2, KC_J),    RALT_T(KC_K),   MT(MOD_RCTL, KC_L), MT(MOD_RSFT, KC_SCLN), LT(10, KC_ENTER),
    KC_HOME,        LT(12, KC_Z),   MT(MOD_LGUI | MOD_LCTL, KC_X), LT(7,KC_C), LT(3,KC_V), KC_B,    KC_NO,                                          KC_NO,          KC_N,           LT(4, KC_M),    LT(8, KC_COMM), MT(MOD_RGUI | MOD_RCTL, KC_DOT), LT(14, KC_QUOTE), KC_END,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_DEL,                                                                                                         KC_TAB,         KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                                                                                    KC_NO,          KC_NO,
                                                                                    TO_26,          MO(31),         KC_NO,          KC_NO,          MO(30),         KC_SPACE
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LGUI,        MO(15),         KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MINS,        KC_7,           LT(9, KC_8),    KC_9,           KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSFT,        KC_LCTL,        KC_LALT,        KC_TRANSPARENT, KC_NO,                                                                          KC_SLSH,        LT(2, KC_4),    KC_5,           KC_6,           KC_0,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          LGUI(KC_LCTL),  KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_COMM,        KC_1,           KC_2,           KC_3,           KC_DOT,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_INS,         KC_LPRN,        KC_UP,          KC_RPRN,        KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          MO(9),          KC_RGUI,        KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_SLSH,        KC_LEFT,        KC_DOWN,        LT(1, KC_RGHT), AVY,                                                                            KC_NO,          KC_TRANSPARENT, KC_RALT,        KC_RCTL,        KC_RSFT,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_CAPS,        KC_ASTR,        KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          RGUI(KC_RCTL),  KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LGUI,        KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSFT,        KC_LCTL,        KC_LALT,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          LGUI(KC_LCTL),  MO(7),          KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LBRC,        HLF_SCRL_B,     KC_RBRC,        KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_RGUI,        KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, BACK_PAR,       FOR_PAR,        HLF_SCRL_F,     KC_EXLM,        KC_QUES,                                                                        KC_NO,          KC_NO,          KC_RALT,        KC_RCTL,        KC_RSFT,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, MO(8),          RGUI(KC_RCTL),  KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LGUI,        MO(15),         KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          TXT_REG_S,      TXT_REG_I,      KC_NO,          KC_PGUP,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSFT,        KC_LCTL,        KC_LALT,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_HASH,        KC_BSLS,        KC_GRAVE,       KC_TILD,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          LGUI(KC_LCTL),  KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PGDN,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [6] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          POS_REG_J,      POS_REG_S,      KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, LT(9, KC_NO),   KC_RGUI,        KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_UNDS,        KC_EQUAL,       KC_MINUS,       KC_PLUS,        KC_NO,                                                                          KC_NO,          KC_NO,          KC_RALT,        KC_RCTL,        KC_RSFT,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          RGUI(KC_RCTL),  KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [7] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          CNSL_IMNU,      KC_NO,          KC_F16,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LCTL,        KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_AT,          KC_DLR,         KC_PERC,        KC_CIRC,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT, MO(3),          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [8] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LCBR,        SCRL_UP_1,      KC_RCBR,        KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          SCRL_DWN_1,     KC_PIPE,        KC_AMPR,                                                                        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          MEH(KC_PGUP),   KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          MO(4),          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [9] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, MULT_SHELL,     O_CT_TR,        O_PRV_VZ_HD,    KC_NO,          HYPR(KC_T),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          LT(6, KC_NO),   KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          HYPR(KC_S),     O_NXT_VZ_HD,    O_BEF_SB_HD,    KC_NO,                                                                          KC_NO,          LT(2, KC_NO),   KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, SHELL,          KC_NO,          O_TG_CD_BF,     KC_NO,          SWITCH_BFR,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [10] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, MC_ALL,         MC_UN_NXT,      MC_PREV,        MC_NXT,         MC_UN_PREV,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, EXP_O_QUO,      EXP_SYM,        KC_NO,          EXP_O_PAR,      KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, EXP_I_QUO,      EXP_WORD,       EXP_COM,        EXP_I_PAR,      KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [11] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, YAS_EXPAND,     KC_NO,          SPLT_WND_VRT,   ONLY_WND,       DRG_UP,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KLL_FRM,        KLL_WND,        KLL_BFF,        SPLT_WND_HRZ,   KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, DRG_DWN,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [12] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          DRG_UP,         KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          SHFT_RG_B,      DRG_DWN,        SHFT_RG_F,      KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [13] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          LCAG(KC_A),     KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          LCAG(KC_B),     LCAG(KC_C),     LCAG(KC_D),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [14] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          WND_MV_UP,      KC_NO,          TOG_TRN_LN,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          WND_MV_LFT,     WND_MV_DWN,     WND_MV_RT,      KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [15] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT, MO(5),          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F24,         LCAG(KC_P),     LCAG(KC_X),     LCAG(KC_Q),     KC_F23,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          MO(1),          KC_NO,                                                                          O_GO_TO,        LCAG(KC_M),     LCAG(KC_G),     LCAG(KC_H),     LCAG(KC_0),     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F22,         LCAG(KC_N),     LCAG(KC_O),     LCAG(KC_L),     KC_F21,         KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [16] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_MRWD,        KC_VOLU,        KC_MFFD,        KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_MPRV,        KC_VOLD,        KC_MNXT,        KC_MPLY,        QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          DBUG_HELP,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [17] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          LCAG(KC_4),     LCAG(KC_6),     LCAG(KC_5),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          LCAG(KC_1),     LCAG(KC_J),     LCAG(KC_K),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          LCAG(KC_2),     LCAG(KC_3),     LCAG(KC_Z),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [18] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          O_CPY_TR,       O_PRV_LVL_HD,   KC_NO,          TOG_LIN_NUM,    KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          O_NXT_LVL_HD,   O_MRK_TR,       KC_NO,                                                                          KC_NO,          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [19] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          LCAG(KC_V),     LCAG(KC_Y),     LCAG(KC_W),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT, KC_NO,                                                                          O_RNM_HD,       LCAG(KC_S),     LCAG(KC_F),     LCAG(KC_E),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          LCAG(KC_T),     LCAG(KC_U),     LCAG(KC_R),     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [20] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [21] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [22] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          SWIPER,         KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          RIPGREP,        KC_NO,           KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [23] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          MRK_B_GLB,      MRK_B_LOC,      KC_TRANSPARENT, KC_NO,                                                                          KC_NO,          KC_TRANSPARENT, MRK_F_LOC,      MRK_F_GLB,      KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [24] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [25] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [26] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LGUI,        KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_MS_UP,       KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSFT,        KC_LCTL,        KC_LALT,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_BTN1,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          LGUI(KC_LCTL),  TO(28),         LCAG(KC_I),     KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          TO(28),         KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_ACL0,                                                                                                 KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(0)
  ),
  [27] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [28] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_LGUI,        KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, TO_26,          KC_NO,          KC_MS_WH_UP,    KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSFT,        KC_LCTL,        KC_LALT,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          LGUI(KC_LCTL),  KC_NO,          LCAG(KC_I),     KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [29] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [30] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [31] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  )
};

uint32_t ss_tap_x_a(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_A));
    return 0;
}
uint32_t ss_tap_x_b(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_B));
    return 0;
}
uint32_t ss_tap_x_c(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_C));
    return 0;
}
uint32_t ss_tap_x_d(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_D));
    return 0;
}
uint32_t ss_tap_x_e(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_E));
    return 0;
}
uint32_t ss_tap_x_f(uint32_t trigger_time, void *cb_arg) {
    SEND_STRING(SS_TAP(X_F));
    return 0;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    switch (layer) {
    case 20: // wow layers
        ergodox_right_led_1_on();
        break;
    case 24:
        ergodox_right_led_1_on();
        break;
    case 25:
        ergodox_right_led_1_on();
        break;
    case 27:
        ergodox_right_led_1_on();
        break;
    case 30:
        ergodox_right_led_1_on();
        break;
    default:
        ergodox_right_led_1_off();
        break;
    }
    state = update_tri_layer_state(state, 15, 5, 17);
    state = update_tri_layer_state(state, 7, 3, 16);
    state = update_tri_layer_state(state, 9, 2, 18);
    state = update_tri_layer_state(state, 9, 6, 22);
    state = update_tri_layer_state(state, 1, 15, 19);
    state = update_tri_layer_state(state, 1, 2, 23);
    state = update_tri_layer_state(state, 8, 4, 29);
    return state;
}

void yasnippet_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case YAS_EXPAND:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_S));
        break;
    }
}

void mark_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MRK_F_LOC:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_Z));
        break;
    case MRK_B_LOC:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_V));
        break;
    case MRK_F_GLB:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_F));
        break;
    case MRK_B_GLB:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_U));
        break;
    }
}

void macro_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MAC_DLAY:
        _delay_ms(250);
        break;
    }
}

void register_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TXT_REG_S:
        SEND_STRING(SS_LCTL("x")"rs");
        break;
    case TXT_REG_I:
        SEND_STRING(SS_LCTL("x")"ri");
        break;
    case POS_REG_S:
        SEND_STRING(SS_LCTL("x")"r ");
        break;
    case POS_REG_J:
        SEND_STRING(SS_LCTL("x")"rj");
        break;
    }
}

void org_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case O_BEF_SB_HD:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_P));
        break;
    case O_LNK_DSC:
        SEND_STRING(SS_LCTL("cl") SS_TAP(X_ENTER));
        break;
    case O_CPY_TR:
        SEND_STRING(SS_LCTL("cx") SS_LALT("w"));
        break;
    case O_TG_CD_BF:
        SEND_STRING(SS_LCTL("c") SS_TAP(X_QUOTE));
        break;
    case O_RNM_HD:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_R));
        break;
    case O_PRV_LVL_HD:
        SEND_STRING(SS_LCTL("cb"));
        break;
    case O_NXT_LVL_HD:
        SEND_STRING(SS_LCTL("cf"));
        break;
    case O_PST_TR:
        SEND_STRING(SS_LCTL("cxy"));
        break;
    case O_CT_TR:
        SEND_STRING(SS_LCTL("cxw"));
        break;
    case O_MRK_TR:
        SEND_STRING(SS_LCTL("c") SS_LSFT("2"));
        break;
    case O_GO_TO:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_Q));
        break;
    case O_PRV_VZ_HD:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_9));
        break;
    case O_NXT_VZ_HD:
        SEND_STRING(SS_LCTL("cn"));
        break;
    }
}

void mc_er_keycodes(uint16_t keycode, keyrecord_t *record) {
    // bool and associated code so I can quickly press these after expand region
    /* bool modded = 0; */
    /* if (keycode == MC_NXT || keycode == MC_PREV || keycode == MC_ALL || keycode == MC_UN_NXT || keycode == MC_UN_PREV) { */
    /*     if (get_mods() & MOD_MASK_CTRL) { */
    /*         modded = 1; */
    /*         del_mods(MOD_MASK_CTRL); */
    /*     } */
    /* } */
    switch (keycode) {
    case EXP_COM:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_2));
        break;
    case EXP_I_PAR:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_6));
        break;
    case EXP_O_PAR:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_5));
        break;
    case EXP_I_QUO:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_Y));
        break;
    case EXP_O_QUO:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_X));
        break;
    case EXP_WORD:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_U));
        break;
    case EXP_SYM:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_T));
        break;
    case MC_NXT:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_K));
        break;
    case MC_PREV:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_L));
        break;
    case MC_ALL:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_M));
        break;
    case MC_UN_NXT:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_N));
        break;
    case MC_UN_PREV:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_O));
        break;
    }
    /* if (modded) { */
    /*     register_mods(MOD_BIT(KC_RCTL)); */
    /* } */
}

void shell_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SHELL:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_D));
        break;
    case MULT_SHELL:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_G));
        break;
    }
}

void search_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SWIPER:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_Z));
        break;
    case CNSL_IMNU:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_S));
        break;
    case RIPGREP:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_E));
        break;
    case AVY:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_1));
        break;
    }
}

void paragraph_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case BACK_PAR:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_2));
        break;
    case FOR_PAR:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_3));
        break;
    }
}

void drag_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DRG_UP:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_X));
        break;
    case DRG_DWN:
        SEND_STRING(SS_TAP(X_F6) SS_TAP(X_Y));
        break;
    case SHFT_RG_B:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_O));
        break;
    case SHFT_RG_F:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_N));
        break;
    }
}

void window_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SWITCH_BFR:
        SEND_STRING(SS_LCTL("x") SS_TAP(X_B));
        break;
    case SCRL_DWN_1:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_W));
        break;
    case SCRL_UP_1:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_V));
        break;
    case SPLT_WND_VRT:
        SEND_STRING(SS_TAP(X_F8));
        defer_exec(20, ss_tap_x_a, NULL);
        defer_exec(40, ss_tap_x_a, NULL);
        break;
    case SPLT_WND_HRZ:
        SEND_STRING(SS_TAP(X_F8));
        defer_exec(20, ss_tap_x_a, NULL);
        defer_exec(40, ss_tap_x_b, NULL);
        break;
    case KLL_WND:
        SEND_STRING(SS_TAP(X_F8));
        defer_exec(20, ss_tap_x_a, NULL);
        defer_exec(40, ss_tap_x_c, NULL);
        break;
    case ONLY_WND:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_M));
        break;
    case KLL_BFF:
        SEND_STRING(SS_TAP(X_F8));
        defer_exec(20, ss_tap_x_a, NULL);
        defer_exec(40, ss_tap_x_f, NULL);
        break;
    case KLL_FRM:
        SEND_STRING(SS_LCTL("x")"50");
        break;
    case WND_MV_UP:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_H));
        break;
    case WND_MV_RT:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_K));
        break;
    case WND_MV_LFT:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_I));
        break;
    case WND_MV_DWN:
        SEND_STRING(SS_TAP(X_F5) SS_TAP(X_L));
        break;
    case HLF_SCRL_F:
        SEND_STRING(SS_TAP(X_F7) SS_TAP(X_F));
        break;
    case HLF_SCRL_B:
        SEND_STRING(SS_TAP(X_F7) SS_TAP(X_G));
        break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* this is for debugging */
    /* if console is enabled (in rules.mk), it will print the matrix position and status of each in hid_listen.exe */
#ifdef CONSOLE_ENABLE
    uprintf("kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

    if (record->event.pressed) {
        window_keycodes(keycode, record);
        paragraph_keycodes(keycode, record);
        drag_keycodes(keycode, record);
        mc_er_keycodes(keycode, record);
        search_keycodes(keycode, record);
        shell_keycodes(keycode, record);
        org_keycodes(keycode, record);
        mark_keycodes(keycode, record);
        register_keycodes(keycode, record);
        yasnippet_keycodes(keycode, record);
        macro_keycodes(keycode, record);
        switch (keycode) {
        case BEACON:
            SEND_STRING(SS_TAP(X_F5) SS_TAP(X_8));
            break;
        case UNDO:
            SEND_STRING(SS_TAP(X_F5) SS_TAP(X_4));
            break;
        case TOG_LIN_NUM:
            SEND_STRING(SS_TAP(X_F8));
            defer_exec(20, ss_tap_x_a, NULL);
            defer_exec(40, ss_tap_x_d, NULL);
            break;
        case TOG_TRN_LN:
            SEND_STRING(SS_TAP(X_F8));
            defer_exec(20, ss_tap_x_a, NULL);
            defer_exec(40, ss_tap_x_e, NULL);
            break;
        case TO_26:
            layer_move(26);
            break;
        case DBUG_HELP:
            break;
        }
    }

    return true;

}

/* void keyboard_post_init_user(void) { */
/*   debug_enable=true; */
/*   debug_matrix=true; */
/*   debug_keyboard=true; */
/*   debug_mouse=true; */
/* } */



/*
****************************************
****************************************
****************************************
****************************************
*************** BINDINGS ***************
****************************************
****************************************
****************************************
****************************************

"<f8> a a" SPLT_WND_VRT
"<f8> a b" SPLT_WND_HRZ
"<f8> a c" KLL_WND
"<f8> a d" TOG_LIN_NUM
"<f8> a e" TOG_TRN_LN
"<f8> a f" KLL_BFF

f5 g: UNDO_TREE - pass through ahk with F19 (also undo/redo)
f5 h: WND_MV_UP
f5 i: WND_MV_LFT
f5 k: WND_MV_RT
f5 l: WND_MV_DWN
f5 m: ONLY_WND
f5 j: DEL_LINE
f5 n: SHFT_RG_F
f5 o: SHFT_RG_B
f5 p: unbound
f5 q: UP_DIRED
f5 r: KILL_DIRED
f5 s: CNSL_IMNU
f5 t: EXP_SYM
f5 u: EXP_WORD
f5 v: SCRL_UP_1
f5 w: SCRL_DWN_1
f5 x: EXP_O_QUO
f5 y: EXP_I_QUO
f5 z: MRK_F_LOC
f5 1: AVY
f5 2: FOR_PAR
f5 3: BACK_PAR
f5 4: UNDO
f5 5: EXP_O_PAR
f5 6: EXP_I_PAR
f5 7: unbound
f5 8: BEACON
f5 9: O_PRV_VZ_HD

f6 c: unbound
f6 d: shell
f6 e: ripgrep
f6 f: MRK_F_GLB
f6 g: mult shell new terminal
f6 h: ahk: org toggle link display
f6 i: ahk: org store link
f6 j: ahk: org insert last stored link
f6 k: mc/mark-next-like-this
f6 l: mc/mark-previous-like-this
f6 m: mc/mark-all-like-this
f6 n: mc/unmark-next-like-this
f6 o: mc/unmark-previous-like-this
f6 p: 'end-of-heading-pre-sub-headings
f6 q: 'helm-org-in-buffer-headings
f6 r: 'rename-heading
f6 s: 'yas-expand
f6 t: ahk: org follow link
f6 u: MRK_B_GLB
f6 v: 'backward-local-mark
f6 x: 'drag up
f6 y: 'drag down
f6 z: SWIPER
f6 1: unbound
f6 2: EXP_COM
f6 3: unbound;

f6 4: ahk: ^#k

f7 f: HLF_SCRL_F, // half scroll forward
f7 g: HLF_SCRL_B // half scroll backward
_________________

WINDOW MANAGEMENT
_________________

LCAG_A resize up half
LCAG_B resize left half
LCAG_C resize down half
LCAG_D resize right half

LCAG_I move mouse to middle of active monitor

LCAG_E move frame to vert monitor
LCAG_F move frame to middle monitor
LCAG_R move frame to far right monitor
LCAG_S move frame to left monitor
LCAG_T move frame to far left monitor
LCAG_U move frame to bottom monitor
LCAG_V move frame to up left monitor
LCAG_W move frame to up right monitor
LCAG_Y move frame to up center monitor

LCAG_G activate middle monitor
LCAG_H activate right monitor
LCAG_L activate far right monitor
LCAG_M activate left monitor
LCAG_N activate far left monitor
LCAG_O activate bottom monitor
LCAG_P activate up left monitor
LCAG_Q activate up right monitor
LCAG_X activate up center

LCAG_J swap to middle
LCAG_K swap to right
LCAG_Z swap to far right
LCAG_1 swap to left
LCAG_2 swap to far left
LCAG_3 swap to bottom
LCAG_4 swap toup left
LCAG_5 swap to up right
LCAG_6 swap to up center

LCAG_0 cycle current monitor

unbound
lcag 9
lcag f1
lcag f2
lcag f etc

MEH(KC_PGUP) alacritty copy
MEH(KC_PGDN) alacritty paste

*/
