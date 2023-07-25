#include "combo.h"

const uint16_t PROGMEM commadot_combo[]     = {TR_COMM, TR_DOT,     COMBO_END};
const uint16_t PROGMEM mdot_combo[]         = {KC_M,    TR_DOT,     COMBO_END};
const uint16_t PROGMEM spacenav_combo[]     = {KC_SPC,  NAVGTIN,    COMBO_END};
const uint16_t PROGMEM op_combo[]           = {KC_O,    KC_P,       COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {

#if defined(POINTING_DEVICE_ENABLE)
  [COMDOT_DRGTOG]   = COMBO(commadot_combo, DRG_TOG),

  [MDOT_SNPTOG]     = COMBO(mdot_combo, SNP_TOG),
#else
  [COMDOT_DRGTOG]   = COMBO(commadot_combo, ___x___),

  [MDOT_SNPTOG]     = COMBO(mdot_combo, ___x___),  
#endif //POINTING_DEVICE_ENABLE

#if defined(MOUSELAYER_ENABLE)
  [SPCNAV_MB4]      = COMBO(spacenav_combo, KC_BTN4),
#else
  [SPCNAV_MB4]      = COMBO(spacenav_combo, ___x___),
#endif //MOUSELAYER_ENABLE

  [OP_CONFIG]       = COMBO(op_combo, CONFIG) 
};


bool get_combo_must_hold(uint16_t index, combo_t *combo) {
  switch (index) {
      
    case OP_CONFIG:
      return true;

    default:
      return false;
  }
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
  
  switch (index) {
      
    case COMDOT_DRGTOG:
    case MDOT_SNPTOG:
    case SPCNAV_MB4:
      return true;

    default:
      return false;
  }
}

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
  switch (combo_index) {
    /* List combos here that you want to only activate if their keys
    * are pressed in the same order as they are defined in the combo's key
    * array. */

    default:
      return false;
  }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  // or with combo index, i.e. its name from enum.
  switch (index) {
    case COMDOT_DRGTOG:
    case MDOT_SNPTOG:
    case SPCNAV_MB4:
      return COMBO_TERM;

    case OP_CONFIG:
      return COMBO_HOLD_TERM + 50;

    default:
      return COMBO_TERM;

  }   
}