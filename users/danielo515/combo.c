#include "combo.h"
enum combos {
  JK_ESC,
  YU_COM,
  UI_COM,
  IO_COM,
  OP_COM,
  QW_COM
};

const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [JK_ESC] = COMBO(jk_combo, KC_ESC),
  [YU_COM] = COMBO(yu_combo, KC_CIRC),
  [UI_COM] = COMBO(ui_combo, KC_ESC),
  [IO_COM] = COMBO(io_combo, KC_TILD)
};
