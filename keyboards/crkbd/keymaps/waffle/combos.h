#pragma once

enum combos {
  RU_ENT
};

const uint16_t PROGMEM ru_combo[] = {KC_R, KC_U, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
[RU_ENT] = COMBO(ru_combo, KC_ENT)
};
