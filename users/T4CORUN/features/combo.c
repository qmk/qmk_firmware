#include "combo.h"

const uint16_t PROGMEM commadot_combo[]     = {KC_COMM, KC_DOT,     COMBO_END};
const uint16_t PROGMEM mdot_combo[]         = {KC_M,    KC_DOT,     COMBO_END};
const uint16_t PROGMEM kl_combo[]           = {KC_K,    KC_L,       COMBO_END};
const uint16_t PROGMEM numshft_combo[]      = {NUMBERS, TR_LSFT,    COMBO_END};
const uint16_t PROGMEM spacenav_combo[]     = {KC_SPC,  NAVGTIN,    COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {

#if defined(POINTING_DEVICE_ENABLE)
  [COMDOT_DRGTOG] = COMBO(commadot_combo, DRG_TOG),

  [MDOT_SNPTOG]   = COMBO(mdot_combo, SNP_TOG),
#else
  [COMDOT_DRGTOG] = COMBO(commadot_combo, ___x___),

  [MDOT_SNPTOG]   = COMBO(mdot_combo, ___x___),  
#endif //POINTING_DEVICE_ENABLE

#if defined(MOUSELAYER_ENABLE)
  [NUMSHFT_MB2]   = COMBO(numshft_combo, KC_BTN2),
  [SPCNAV_MB4]    = COMBO(spacenav_combo, KC_BTN4)
#else
  [NUMSHFT_MB2]   = COMBO(numshft_combo, ___x___),
  [SPCNAV_MB4]    = COMBO(spacenav_combo, ___x___)
#endif //MOUSELAYER_ENABLE

};


