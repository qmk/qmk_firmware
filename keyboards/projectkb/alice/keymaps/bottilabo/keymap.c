/*
 * bottilabo's harmonized layout
 *
 * bottilabo (twitter: @bottilabo)
 * http://github.com/bottilabo/qmk-harmonize
 */
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define ___ _______
#define IMM K_XIMMODE

//#define TRANSLATE_LAYOUT
#ifndef TRANSLATE_LAYOUT
#define STANDARD_LAYOUT
#endif



#ifdef STANDARD_LAYOUT

//      +    +    +    *                                 *    +    +    +
//4     4    3    2    1    1                            1    1    2    3    4      4
#define LAYOUT_remapper( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR1, NR2, NR3, NR4, NR5,   NR6, NR7, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R01, R02, R03, R04, R05,   R06, R07, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R11, R12, R13, R14, R15,   R16, R17, ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R21, R22, R23, R24, R25,   R26,      RSFT,  \
MOUS,  LCTL,LALT,LGUI,                                            RGUI,RALT,RCTL,   ADJ, \
                       TL2,                                   TR2,                       \
       PGUP,                TL1,                         TR1,                UP,         \
HOME,  PGDN,END ,                  TL0,           TR0,                 LEFT,DOWN,  RIGT, \
INS ,DEL   ,PRNT,BRK,                                                ZENHN,KANA,MHEN,HENK  \
  ) \
  LAYOUT_default( \
ESC ,   R17, NL5, NL4, NL3, NL2,   NL1, NR1,        NR2,   NR3, NR4, NR5, NR6, NR7,   ___,    BSPC, \
DEL ,   TAB, L05, L04, L03, L02,   L01,           R01,   R02, R03, R04, R05, R06,   R07,      BSLS, \
ADJ ,  CAPS,L15, L14, L13, L12,   L11,           R11,   R12, R13, R14, R15, R16,             ENTR,\
       LCTL , L25, L24, L23, L22,   L21,           ENTR,   R21, R22, R23, R24, R25,     RSFT,     RCTL, \
       LGUI,              LALT,TL1, TL0,                   TR0,       TR1,                     RGUI )

#endif

#ifdef TRANSLATE_LAYOUT

//      +    +    +    *                                 *    +    +    +
//4     4    3    2    1    1                            1    1    2    3    4      4
#define LAYOUT_remapper( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR1, NR2, NR3, NR4, NR5,   NR6, NR7, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R01, R02, R03, R04, R05,   R06, R07, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R11, R12, R13, R14, R15,   R16, R17, ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R21, R22, R23, R24, R25,   R26,      RSFT,  \
MOUS,  LCTL,LALT,LGUI,                                            RGUI,RALT,RCTL,   ADJ, \
                       TL2,                                   TR2,                       \
       PGUP,                TL1,                         TR1,                UP,         \
HOME,  PGDN,END ,                  TL0,           TR0,                 LEFT,DOWN,  RIGT, \
INS ,DEL   ,PRNT,BRK,                                                ZENHN,KANA,MHEN,HENK  \
  ) \
  LAYOUT_default( \
ESC ,   R17, NL5, NL4, NL3, NL2,   NL1, NR1,        NR1, NR2,   NR3, NR4, NR5, NR6, NR7,     BSPC, \
DEL ,   TAB, L05, L04, L03, L02,   L01,           RSFT, R01,   R02, R03, R04, R05, R06,      BSLS, \
ADJ ,  CAPS, L15, L14, L13, L12,   L11,             LGUI, R11,   R12, R13, R14, R15,         ENTR, \
       LCTL , L25, L24, L23, L22,   L21,     LCTL,LALT,   R21,   R22, R23, R24,    R25,      RCTL, \
       LGUI,              LALT, TL1, TL0,                   TR0,      TR1,                  RGUI )


#endif


#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)


//#define K_TR1 LT(_Lr1,KC_SPC)
#define NO_REPORT
#define HAS_THUMBROW
#include "harmonize.h"
