#include "combo.h"

/*
comma, dot = Dragscroll toggle
left click, NUMBER = MB2
space, NAV = MB4
*/


const uint16_t PROGMEM commadot_combo[]     = {KC_COMM, KC_DOT,     COMBO_END};
const uint16_t PROGMEM numshift_combo[]     = {NUMBER,  KC_LSFT,    COMBO_END};
const uint16_t PROGMEM spacenav_combo[]     = {KC_SPC,  NAV,        COMBO_END};


combo_t key_combos[COMBO_LENGTH] = {

#if defined(POINTING_DEVICE_ENABLE)
  [COMDOT_DRGTOG] = COMBO(commadot_combo, DRG_TOG),
#else
  [COMDOT_DRGTOG] = COMBO(commadot_combo, ___x___),
#endif //POINTING_DEVICE_ENABLE

#if defined(MOUSELAYER_ENABLE)
  [NUMSFT_MB2]    = COMBO(numshift_combo, KC_BTN2),
  [SPCNAV_MB4]    = COMBO(spacenav_combo, KC_BTN4)
#else
  [NUMSFT_MB2]    = COMBO(numshift_combo, ___x___),
  [SPCNAV_MB4]    = COMBO(spacenav_combo, ___x___)
#endif //MOUSELAYER_ENABLE

};


