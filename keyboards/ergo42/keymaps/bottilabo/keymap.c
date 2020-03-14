/*
 * bottilabo's harmonized layout
 *
 * bottilabo (twitter: @bottilabo)
 * http://github.com/bottilabo/qmk-harmonize
 */
#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif


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
ESC , L05, L04, L03, L02, L01, UP  ,         BSPC, R01, R02, R03, R04,   R05,    BSPC,  \
CAPS, L15, L14, L13, L12, L11, LEFT,         RIGT, R11, R12, R13, R14,   R15,    ENTR,  \
LSFT, L25, L24, L23, L22, L21, DOWN,         ENTR, R21, R22, R23, R24  , R25,    RSFT,  \
LGUI, ADJ,LALT,LCTL, TL1, TL0,  ADJ,         ADJ , TR0, TR1, RCTL,RALT,  ADJ,    RGUI \
 ) 

#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)


#define HAS_THUMBROW
#include "harmonize.h"





void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

#define CHANGE_LAYOUT_DEF(X)    \
    case X:\
      if (record->event.pressed) {\
        persistent_default_layer_set(1UL<<_##X);\
      }\
      return false;\
      break;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  HARMONIZE_PROC_RECORD_USER;

  return true;
}

void matrix_init_user(void) {
    //
    // Always init to default keyboard layout
    //
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    //eeconfig_read_keymap()
    persistent_default_layer_set(0);
    harmonize_init();
}


void matrix_scan_user(void) {
  HARMONIZE_MATRIX_SCAN_USER;
}

