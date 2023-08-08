#include "tapping.h"

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  //This is effective for all dual role keys (e.g. Mod-Taps, Layer-Taps, etc)
  switch(keycode) {
    default:
      //Disable HOLD_ON_OTHER_KEY_PRESS aka enable IGNORE_MOD_TAP_INTERRUPT 
      return false;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      return QUICK_TAP_TERM;
  }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

#if defined(HOMEROWMOD_ENABLE)
    //QWERTY Home Row Mods
    case TR_A:
    case TR_SA:
    case TR_L:
    case TR_QUOT:
    //COLEMAKdh Home Row Mods
    case TR_R:
    case TR_SC:
    case TR_I:
    case TR_O:
      return TAPPING_TERM + 30;
#endif //HOMEROWMOD_ENABLE

#if defined(MOUSELAYER_ENABLE)
    case TR_MOUC:
    case TR_MOUZ:
      return TAPPING_TERM - 30;
#endif //MOUSELAYER_ENABLE

    case NAVGTIN:
      return TAPPING_TERM - 75;

    default:
      //uprintf("tapping term: %d \n", TAPPING_TERM);
      return TAPPING_TERM;
  }
}