#ifndef VIRTUAL_KEYS_H
#define VIRTUAL_KEYS_H

#include "tapdance.h"
#define MOD_R2
//#define MOD_R1


#ifdef MOD_R2
// layer0
#define VKC_SA   LSFT_T(KC_A)
#define VKC_CS   LCTL_T(KC_S)
#define VKC_AD   LALT_T(KC_D)
#define VKC_AK   RALT_T(KC_K)
#define VKC_CL   RCTL_T(KC_L)
#define VKC_SSP  RSFT_T(KC_SPC)

// layer1
#define VKC_S6   LSFT_T(KC_6)
#define VKC_C7   LCTL_T(KC_7)
#define VKC_A8   LALT_T(KC_8)
#define VKC_AF8  RALT_T(KC_F8)
#define VKC_CF9  RCTL_T(KC_F9)
#define VKC_SF10 RSFT_T(KC_F10)

// layer2
#define VKC_SLF  LSFT_T(KC_LEFT)
#define VKC_CDN  LCTL_T(KC_DOWN)
#define VKC_ART  LALT_T(KC_RIGHT)
#define VKC_AUP  RALT_T(KC_UP)
#define VKC_CRT  RCTL_T(KC_RIGHT)
#define VKC_SGR  RSFT_T(KC_GRV)

// layer3
#define VKC_SCIR KC_CIRC
#define VKC_CAMP KC_AMPR
#define VKC_AAST KC_ASTR

// layer4
#define VKC_STLD KC_TILD
#define VKC_SHM  LSFT_T(KC_HOME)
#define VKC_CPD  LCTL_T(KC_PGDN)
#define VKC_AED  LALT_T(KC_END)
#define VKC_APU  RALT_T(KC_PGUP)
#define VKC_CED  RCTL_T(KC_END)


#else
// layer0
#define VKC_SA   KC_A
#define VKC_CS   KC_S
#define VKC_AD   KC_D
#define VKC_AK   KC_K
#define VKC_CL   KC_L
#define VKC_SSP  KC_SPC

// layer1
#define VKC_S6   KC_6
#define VKC_C7   KC_7
#define VKC_A8   KC_8
#define VKC_AF8  KC_F8
#define VKC_CF9  KC_F9
#define VKC_SF10 KC_F10

// layer2
#define VKC_SLF  KC_LEFT
#define VKC_CDN  KC_DOWN
#define VKC_ART  KC_RIGHT
#define VKC_AUP  KC_UP
#define VKC_CRT  KC_RIGHT
#define VKC_SGR  KC_GRV

// layer3
#define VKC_SCIR KC_CIRC
#define VKC_CAMP KC_AMPR
#define VKC_AAST KC_ASTR

// layer4
#define VKC_STLD KC_TILD
#define VKC_SHM  KC_HOME
#define VKC_CPD  KC_PGDN
#define VKC_AED  KC_END
#define VKC_APU  KC_PGUP
#define VKC_CED  KC_END

#endif

#ifdef MOD_R1
// layer0
#define VKC_SZ   LSFT_T(KC_Z)
#define VKC_CX   LCTL_T(KC_X)
#define VKC_AC   LALT_T(KC_C)
#define VKC_ACMM RALT_T(KC_COMM)
#define VKC_CDOT RCTL_T(KC_DOT)
#define VKC_SET  RSFT_T(KC_ENT)

// layer1
#define VKC_STB  LSFT_T(KC_TAB)
#define VKC_CPSR LCTL_T(KC_PSCR)
#define VKC_CF11 RCTL_T(KC_F11)
#define VKC_SF12 RSFT_T(KC_F12)

// layer2
#define VKC_1LSFT KC_LSFT
#define VKC_1LCTL KC_LCTL
#define VKC_1LALT KC_LALT
#define VKC_ASL  RALT_T(KC_SLSH)
#define VKC_CSC  RCTL_T(KC_SCLN)
#define VKC_SQT  RSFT_T(KC_QUOT)

// layer3
#define VKC_AQES RALT_T(KC_QUES)
#define VKC_CCLN RCTL_T(KC_COLN)
#define VKC_SDQT RSFT_T(KC_DQT)
/* #define VKC_AQES KC_QUES */
/* #define VKC_CCLN KC_COLN */
/* #define VKC_SDQT KC_DQT */
#define VKC_1RALT KC_RALT

#else
// layer0
#define VKC_SZ   KC_Z
#define VKC_CX   KC_X
#define VKC_AC   KC_C
#define VKC_ACMM KC_COMM
#define VKC_CDOT KC_DOT
#define VKC_SET  KC_ENT

// layer1
#define VKC_STB  KC_TAB
#define VKC_CPSR KC_PSCR
#define VKC_CF11 KC_F11
#define VKC_SF12 KC_F12

// layer2
#define VKC_1LSFT XXXXXXX
#define VKC_1LCTL XXXXXXX
#define VKC_1LALT XXXXXXX
#define VKC_ASL  KC_SLSH
#define VKC_CSC  KC_SCLN
#define VKC_SQT  KC_QUOT

// layer3
#define VKC_AQES KC_QUES
#define VKC_CCLN KC_COLN
#define VKC_SDQT KC_DQT
#define VKC_1RALT XXXXXXX

#endif

#define VKC_SB   LSFT_T(KC_B)
#define VKC_SN   RSFT_T(KC_N)
#define VKC_SDEL LSFT_T(KC_DEL)
#define VKC_SCMM RSFT_T(KC_COMM)
#define VKC_SLT  RSFT_T(KC_LT)

#if defined(TAP_DANCE_ENABLE)
#define VKC_Y TD(TD_YY_MINUS)
#else
#define VKC_Y KC_Y
#endif

//#define VKC_1N   LT(1,KC_N)
#define VKC_1N   KC_N
//#define VKC_2B   LT(2,KC_B)
#define VKC_2B   KC_B
#define VKC_3M   LT(3,KC_M)
#define VKC_4V   LT(4,KC_V)
#define VKC_1J   LT(1,KC_J)
#define VKC_2F   LT(2,KC_F)




#define VKC_CAD LCA(KC_DEL)

#define VKC_AL1 _______
#define VKC_4ET LT(4,KC_ENT)






#endif
