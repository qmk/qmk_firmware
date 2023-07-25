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
    case TR_S:
    case TR_L:
    case TR_QT:
    //COLEMAKdh Home Row Mods
    case TR_R:
    case TR_S2:
    case TR_I:
    case TR_O:
      return TAPPING_TERM + 30;
#endif //HOMEROWMOD_ENABLE

    //layer taps
    case CONFIG:
      return TAPPING_TERM + 50;

#if defined(MOUSELAYER_ENABLE)
    case TR_MOUC:
      return TAPPING_TERM - 30;
#endif //MOUSELAYER_ENABLE


    default:
      //uprintf("tapping term: %d \n", TAPPING_TERM);
      return TAPPING_TERM;
  }
}