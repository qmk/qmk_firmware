#include "combos.h"

const uint16_t PROGMEM bn_combo[]     = {KC_B,    KC_N,     COMBO_END};
const uint16_t PROGMEM vk_combo[]     = {KC_V,    KC_K,     COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [BN_MOU] = COMBO(bn_combo, MOU_TOG),
  [VK_MOU] = COMBO(vk_combo, MOU_TOG)
};