/*
 * bottilabo's harmonized layout
 *
 * bottilabo (twitter: @bottilabo)
 * http://github.com/bottilabo/qmk-harmonize
 */
#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


#define HAS_THUMBROW
#define IMM K_XIMMODE

/*
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
  LAYOUT( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR1, NR2, NR3, NR4, NR5,   NR6, NR7, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R01, R02, R03, R04, R05,   R06, R07, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R11, R12, R13, R14, R15,   R16     , ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R21, R22, R23, R24, R25,   R26, UP ,  ADJ,  \
LGUI,LALT,LCTL,TL1 ,TL0       ,               TR0        , TR1, LCTL,    LEFT,DOWN,RIGT  \
    )
#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)
*/


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
  LAYOUT( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR6, NR1, NR2, NR3, NR4, NR5,   NR6, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R06, R01, R02, R03, R04, R05,   R06, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R16, R11, R12, R13, R14, R15,        ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R26, R21, R22, R23, R24, R25,   UP ,  ADJ,  \
LGUI,LALT,LCTL,TL1 ,TL0       ,               TR0        , TR1, LCTL,    LEFT,DOWN,RIGT  \
    )
#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)


#include "harmonize.h"

// define variables for reactive RGB
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  HARMONIZE_PROC_RECORD_USER;
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    harmonize_init();
}

void matrix_scan_user(void) {
   HARMONIZE_MATRIX_SCAN_USER;
}

void led_set_user(uint8_t usb_led) {

}
