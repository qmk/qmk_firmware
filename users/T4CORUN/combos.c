#include "combos.h"

const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [RT_MOU] = COMBO(rt_combo, MOU_TOG),
  [PB_MOU] = COMBO(pb_combo, MOU_TOG)
};