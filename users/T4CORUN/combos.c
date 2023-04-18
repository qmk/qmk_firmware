#include "combos.h"

const uint16_t PROGMEM wr_combo[]     = {KC_W,    KC_R,     COMBO_END};
const uint16_t PROGMEM btn45_combo[]  = {KC_BTN4, KC_BTN5,  COMBO_END};
const uint16_t PROGMEM uo_combo[]     = {KC_U,    KC_O,     COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [WR_MOU] = COMBO(wr_combo, MOU_TOG),
  [B45_MOU] = COMBO(btn45_combo, MOU_TOG),
  [UO_MOU] = COMBO(uo_combo, MOU_TOG)
};