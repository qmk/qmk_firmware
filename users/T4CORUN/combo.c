#include "combo.h"

const uint16_t PROGMEM commadot_combo[]     = {KC_COMM, KC_DOT,     COMBO_END};
const uint16_t PROGMEM mb2mb3_combo[]       = {KC_BTN2, KC_BTN3,    COMBO_END};

const uint16_t PROGMEM mdot_combo[]         = {KC_M,    KC_DOT,     COMBO_END};
const uint16_t PROGMEM mb1mb3_combo[]       = {KC_BTN1, KC_BTN3,    COMBO_END};

const uint16_t PROGMEM spacenav_combo[]     = {KC_SPC,  NAV,        COMBO_END};


combo_t key_combos[COMBO_LENGTH] = {

#if defined(POINTING_DEVICE_ENABLE)
  [COMDOT_DRGTOG] = COMBO(commadot_combo, DRG_TOG),
  [MB2MB3_DRGTOG] = COMBO(mb2mb3_combo, DRG_TOG),

  [MDOT_SNPTOG]   = COMBO(mdot_combo, SNP_TOG),
  [MB1MB3_SNPTOG] = COMBO(mb1mb3_combo, SNP_TOG),
#else
  [COMDOT_DRGTOG] = COMBO(commadot_combo, ___x___),
  [MB2MB3_DRGTOG] = COMBO(mb2mb3_combo, ___x___),

  [MDOT_SNPTOG]   = COMBO(mdot_combo, ___x___),
  [MB1MB3_SNPTOG] = COMBO(mb1mb3_combo, ___x___),  
#endif //POINTING_DEVICE_ENABLE

#if defined(MOUSELAYER_ENABLE)
  [SPCNAV_MB4]    = COMBO(spacenav_combo, KC_BTN4)
#else
  [SPCNAV_MB4]    = COMBO(spacenav_combo, ___x___)
#endif //MOUSELAYER_ENABLE

};


