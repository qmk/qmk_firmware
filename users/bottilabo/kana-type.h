#pragma once

// 000000111111 
// 000011000000
// 111100000000

// 110000000000
// 109876543210
// youDHkstnAIU
enum {
    KP__ = 0,
    KP_A = 0,
    KP_I = 1,
    KP_U = 2,
    KP_E = 3,
    KP_O = 4,
    KP_  = (1U*5),
    KP_K = (2U*5),
    KP_S = (3U*5),
    KP_T = (4U*5),
    KP_N = (5U*5),
    KP_H = (6U*5),
    KP_M = (7U*5),
    KP_Y = (8U*5),
    KP_R = (9U*5),
    KP_W = (10U*5),
    KANA_daku = (1U<<7),
    KANA_hndk = (2U<<7),
    KANA__a = (1U<<9),
    KANA__i = (2U<<9),
    KANA__u = (3U<<9),
    KANA__e = (4U<<9),
    KANA__o = (5U<<9),
    KANA_ya = (6U<<9),
    KANA_yu = (7U<<9),
    KANA_yo = (8U<<9),
    KANA_wa = (8U<<10),
    KANA_max = 0xffff
};

#define KP_MASK_1 127
#define KP_MASK_HNDK (3U<<7)
#define KP_MASK_YOUON (15U<<9)


typedef enum KANA_t_ {
    KANA___ = 0,

    KANA__A = KP_ +KP_A, KANA__I = KP_ +KP_I, KANA__U = KP_ +KP_U, KANA__E = KP_ +KP_E, KANA__O = KP_ +KP_O,
    KANA_KA = KP_K+KP_A, KANA_KI = KP_K+KP_I, KANA_KU = KP_K+KP_U, KANA_KE = KP_K+KP_E, KANA_KO = KP_K+KP_O,
    KANA_SA = KP_S+KP_A, KANA_SI = KP_S+KP_I, KANA_SU = KP_S+KP_U, KANA_SE = KP_S+KP_E, KANA_SO = KP_S+KP_O,
    KANA_TA = KP_T+KP_A, KANA_TI = KP_T+KP_I, KANA_TU = KP_T+KP_U, KANA_TE = KP_T+KP_E, KANA_TO = KP_T+KP_O,
    KANA_NA = KP_N+KP_A, KANA_NI = KP_N+KP_I, KANA_NU = KP_N+KP_U, KANA_NE = KP_N+KP_E, KANA_NO = KP_N+KP_O,
    KANA_HA = KP_H+KP_A, KANA_HI = KP_H+KP_I, KANA_HU = KP_H+KP_U, KANA_HE = KP_H+KP_E, KANA_HO = KP_H+KP_O,
    KANA_MA = KP_M+KP_A, KANA_MI = KP_M+KP_I, KANA_MU = KP_M+KP_U, KANA_ME = KP_M+KP_E, KANA_MO = KP_M+KP_O,
    KANA_YA = KP_Y+KP_A, KANA_YI = KP_Y+KP_I, KANA_YU = KP_Y+KP_U, KANA_YE = KP_Y+KP_E, KANA_YO = KP_Y+KP_O,
    KANA_RA = KP_R+KP_A, KANA_RI = KP_R+KP_I, KANA_RU = KP_R+KP_U, KANA_RE = KP_R+KP_E, KANA_RO = KP_R+KP_O,
    KANA_WA = KP_W+KP_A, KANA_WI = KP_W+KP_I, KANA_WU = KP_W+KP_U, KANA_WE = KP_W+KP_E, KANA_WO = KP_W+KP_O,
    KANA_NN, KANA_tu,
    KANA_SPC,
    KANA_COMM,KANA_DOT,KANA_SLSH,KANA_MINS,

    KANA_GRP1_MAX,

    KANA_GA = (KANA_KA | KANA_daku),
    KANA_GI = (KANA_KI | KANA_daku),
    KANA_GU = (KANA_KU | KANA_daku),
    KANA_GE = (KANA_KE | KANA_daku),
    KANA_GO = (KANA_KO | KANA_daku),
    KANA_ZA = (KANA_SA | KANA_daku),
    KANA_JI = (KANA_SI | KANA_daku),
    KANA_ZU = (KANA_SU | KANA_daku),
    KANA_ZE = (KANA_SE | KANA_daku),
    KANA_ZO = (KANA_SO | KANA_daku),
    KANA_DA = (KANA_TA | KANA_daku),
    KANA_DI = (KANA_TI | KANA_daku),
    KANA_DU = (KANA_TU | KANA_daku),
    KANA_DE = (KANA_TE | KANA_daku),
    KANA_DO = (KANA_TO | KANA_daku),
    KANA_BA = (KANA_HA | KANA_daku),
    KANA_BI = (KANA_HI | KANA_daku),
    KANA_BU = (KANA_HU | KANA_daku),
    KANA_BE = (KANA_HE | KANA_daku),
    KANA_BO = (KANA_HO | KANA_daku),
    KANA_VA = (KANA__U | KANA_daku | KANA__a),
    KANA_VI = (KANA__U | KANA_daku | KANA__i),
    KANA_VU = (KANA__U | KANA_daku          ),
    KANA_VE = (KANA__U | KANA_daku | KANA__e),
    KANA_VO = (KANA__U | KANA_daku | KANA__o),
    KANA_PA = (KANA_HA | KANA_hndk),
    KANA_PI = (KANA_HI | KANA_hndk),
    KANA_PU = (KANA_HU | KANA_hndk),
    KANA_PE = (KANA_HE | KANA_hndk),
    KANA_PO = (KANA_HO | KANA_hndk),

    KANA_FA = (KANA_HU | KANA__a),
    KANA_FI = (KANA_HU | KANA__i),
    KANA_FU = (KANA_HU | KANA__u),
    KANA_FE = (KANA_HU | KANA__e),
    KANA_FO = (KANA_HU | KANA__o),

    KANA_JE  = (KANA_SI | KANA__e | KANA_daku),

    KANA_KYA = (KANA_KI | KANA_ya),
    KANA_KYU = (KANA_KI | KANA_yu),
    KANA_KYO = (KANA_KI | KANA_yo),
    KANA_SYA = (KANA_SI | KANA_ya),
    KANA_SYU = (KANA_SI | KANA_yu),
    KANA_SYO = (KANA_SI | KANA_yo),
    KANA_TYA = (KANA_TI | KANA_ya),
    KANA_TYU = (KANA_TI | KANA_yu),
    KANA_TYO = (KANA_TI | KANA_yo),
    KANA_NYA = (KANA_NI | KANA_ya),
    KANA_NYU = (KANA_NI | KANA_yu),
    KANA_NYO = (KANA_NI | KANA_yo),
    KANA_HYA = (KANA_HI | KANA_ya),
    KANA_HYU = (KANA_HI | KANA_yu),
    KANA_HYO = (KANA_HI | KANA_yo),
    KANA_MYA = (KANA_MI | KANA_ya),
    KANA_MYU = (KANA_MI | KANA_yu),
    KANA_MYO = (KANA_MI | KANA_yo),
    KANA_RYA = (KANA_RI | KANA_ya),
    KANA_RYU = (KANA_RI | KANA_yu),
    KANA_RYO = (KANA_RI | KANA_yo),
    KANA_GYA = (KANA_KI | KANA_ya | KANA_daku),
    KANA_GYU = (KANA_KI | KANA_yu | KANA_daku),
    KANA_GYO = (KANA_KI | KANA_yo | KANA_daku),
    KANA_JYA = (KANA_SI | KANA_ya | KANA_daku),
    KANA_JYU = (KANA_SI | KANA_yu | KANA_daku),
    KANA_JYO = (KANA_SI | KANA_yo | KANA_daku),
    KANA_DYA = (KANA_TI | KANA_ya | KANA_daku),
    KANA_DYU = (KANA_TI | KANA_yu | KANA_daku),
    KANA_DYO = (KANA_TI | KANA_yo | KANA_daku),
    KANA_BYA = (KANA_HI | KANA_ya | KANA_daku),
    KANA_BYU = (KANA_HI | KANA_yu | KANA_daku),
    KANA_BYO = (KANA_HI | KANA_yo | KANA_daku),
    KANA_PYA = (KANA_HI | KANA_ya | KANA_hndk),
    KANA_PYU = (KANA_HI | KANA_yu | KANA_hndk),
    KANA_PYO = (KANA_HI | KANA_yo | KANA_hndk),

    KANA_SYE = (KANA_SI | KANA__e),
    KANA_ULI = (KANA__U | KANA__i),
    KANA_ULE = (KANA__U | KANA__e),
    KANA_ULO = (KANA__U | KANA__o),

    KANA_DELI = (KANA_TE | KANA__i | KANA_daku),
    KANA_DEYU = (KANA_TE | KANA_yu | KANA_daku),
    KANA_DOLU = (KANA_TO | KANA__u | KANA_daku),
    KANA_TOLU = (KANA_TO | KANA__u),
    KANA_TILI = (KANA_TI | KANA__i),
    KANA_TILE = (KANA_TI | KANA__e),
    KANA_TELI = (KANA_TE | KANA__i),
    KANA_TULA = (KANA_TU | KANA__a),
    KANA_TULI = (KANA_TU | KANA__i),
    KANA_TULE = (KANA_TU | KANA__e),
    KANA_TULO = (KANA_TU | KANA__o),

    KANA__I_e = (KANA__I | KANA__e),
    KANA_NELE = (KANA_NE | KANA__e),
    KANA__ULI = (KANA__U | KANA__i),

    KANA_KIGOU = 0xff00,
    KANA_DOU,
    KANA_QUOT,
    KANA_CDOT,

    KANA_LPRN,
    KANA_RPRN,
    KANA_LBRC,
    KANA_RBRC,
    KANA_QSTN, // ?
    KANA_EXCL, // !
    KANA_ASTR, // *
    KANA_TILD,

    KANA_ENT,
    KANA_TAB,
    KANA_BSPC,
    KANA_ESC,
    KANA_LEFT,
    KANA_DOWN,
    KANA_UP,
    KANA_RIGT,
    KANA_HOME,
    KANA_END,
    KANA_PGUP,
    KANA_PGDN,

    KANA_ZENHAN,
    KANA_EISU,
    KANA_MHEN,
    KANA_HENK,
    KANA_KANA,

    KANA_MAX = 0xffff
} KANA_t;



bool type_kana(KANA_t kch);
void set_kana_mode(uint8_t modef);

