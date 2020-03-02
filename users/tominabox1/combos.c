
// Combos
enum combo_events {
  //COMBO_RESET,
  CAPS_COMBO,
  CRET,
  COMBOPP,
  COMBO_NEXT,
  COMBO_PREV,
  COMBO_BSPC,
  COMBO_NUMBAK,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_ESC2,
  COMBO_GAMER
};

//const uint16_t PROGMEM combo_reset[] = {KC_Q, KC_F, COMBO_END};
#ifdef KEYBOARD_crkbd_rev1
const uint16_t PROGMEM caps_combo[] = {KC_M, KC_V, COMBO_END};
#endif
#ifndef KEYBOARD_crkbd_rev1
const uint16_t PROGMEM caps_combo[] = {KC_K, KC_V, COMBO_END};
#endif
const uint16_t PROGMEM cret[] = {KC_QUOT, KC_O, COMBO_END};
const uint16_t PROGMEM combo_pp[] = {KC_7, KC_9, COMBO_END};
const uint16_t PROGMEM combo_next[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM combo_prev[] = {KC_7, KC_8, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_Y, KC_QUOT, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM combo_esc2[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_gamer[] = {KC_Q, KC_QUOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  //[COMBO_RESET] = COMBO_ACTION(combo_reset),
  [CAPS_COMBO] = COMBO(caps_combo, KC_CAPS),
  [CRET] = COMBO(cret, KC_ENT),
  [COMBOPP] = COMBO(combo_pp,KC_MPLY),
  [COMBO_NEXT] = COMBO(combo_next,KC_MNXT),
  [COMBO_PREV] = COMBO(combo_prev,KC_MPRV),
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_ESC2] = COMBO(combo_esc2,KC_ESC),
  [COMBO_GAMER] = COMBO_ACTION(combo_gamer),
};

__attribute__ ((weak))
void process_combo_keymap(uint8_t combo_index, bool pressed) {
}

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {

    case COMBO_GAMER:
    if (pressed) {
      layer_move(_GAME);
    }
    break;
  }
}
