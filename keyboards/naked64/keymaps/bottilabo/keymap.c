/*
 * Copyright 2020 bottilabo (twitter: @bottilabo)
 * http://github.com/bottilabo/qmk-harmonize
 */
#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

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





// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void matrix_init_user(void) {
    harmonize_init();

    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

/*
//A description for expressing the layer position in LED mode.
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAI, _LWR, _ADJ);
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _LWR:
      setrgb(0, 0, 150, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 150, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    case _RAI:
      setrgb(150, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(150, 0, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    case _ADJ:
      setrgb(100, 0, 100, (LED_TYPE *)&led[0]);
      setrgb(100, 0, 100, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    default: //  for any other layers, or the default layer
      setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    }
#endif
return state;
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  HARMONIZE_PROC_RECORD_USER;

  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}

void matrix_scan_user(void) {
   HARMONIZE_MATRIX_SCAN_USER;
}
