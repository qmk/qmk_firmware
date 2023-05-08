#include "combo.h"

const uint16_t PROGMEM commadot_combo[]     = {KC_COMM, KC_DOT,     COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [COMDOT_MOU] = COMBO(commadot_combo, MOU_TOG)
};