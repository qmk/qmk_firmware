/*
 * Copyright 2020 bottilabo (twitter: @bottilabo)
 * http://github.com/bottilabo/qmk-harmonize
 */
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;


extern uint8_t is_master;

#define ___ _______
#define IMM K_XIMMODE

//      +    +    +    *                                 *    +    +    +
//4     4    3    2    1    1      1              1      1    1    2    3    4      4
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
  LAYOUT_wrapper( \
     ADJ,   ESC,NL5,   NL4, NL3, NL2, NL1,            NR1, NR2, NR3, NR4,   NR5, NR5, BSPC, \
     DEL,   TAB,L05,   L04, L03, L02, L01,            R01, R02, R03, R04,   R05, R05, BSLS, \
           CAPS,L15,   L14, L13, L12, L11,            R11, R12, R13, R14,   R15, R16, ENTR, \
           LGUI,L25,   L24, L23, L22, L21,            R21, R22, R23, R24,   R25,  UP, RSFT, \
             LGUI,LALT,          TL1, TL0,            TR0      ,TR1,RCTL,   LEFT,DOWN,RIGT \
)

#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)

#define HAS_THUMBROW
#include "harmonize.h"

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _Lr1, _Ll1, _ADJ);
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _Ll2:
      rgblight_sethsv_at(HSV_YELLOW, 1);
      break;
    case _Lr2:
      rgblight_sethsv_range(HSV_CYAN, 0, 2);
      break;
    case _Ll1:
      rgblight_sethsv_range(HSV_BLUE, 0, 2);
      break;
    case _Lr1:
      rgblight_sethsv_range(HSV_RED, 0, 2);
      break;
    case _ADJ:
      rgblight_sethsv_range(HSV_PURPLE, 0, 2);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_range( 0, 0, 0, 0, 2);
      break;
    }
    rgblight_set_effect_range( 2, 6);
#endif
return state;
}
