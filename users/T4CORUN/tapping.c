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
    //QWERTY Home Row Mods
    case TR_A:
    case TR_QT:
    case TR_S:
    case TR_L:
    //COLEMAKdh Home Row Mods
    case TR_O:
    case TR_R:
    case TR_I:
      return TAPPING_TERM + 30;
    //Pinky layers
    case FUN_Z:
    case AD_SLSH:
      return TAPPING_TERM + 50;
    case TR_MOUC:
      return TAPPING_TERM - 30;
    default:
      //uprintf("tapping term: %d \n", TAPPING_TERM);
      return TAPPING_TERM;
  }
}