enum combos { _topl, _btml, _thml, _midd, _topr, _btmr, _thmr, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM cmbo_topl[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM cmbo_btml[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cmbo_thml[] = {MO(1), KC_SPC, COMBO_END};
const uint16_t PROGMEM cmbo_midd[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM cmbo_topr[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM cmbo_btmr[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM cmbo_thmr[] = {KC_RSFT, MO(2), COMBO_END};

combo_t key_combos[] = {
  [_topl] = COMBO(cmbo_topl, KC_TAB), 
  [_btml] = COMBO(cmbo_btml, KC_LCTL), 
  [_thml] = COMBO(cmbo_thml, KC_LGUI), 
  [_midd] = COMBO(cmbo_midd, KC_NO), 
  [_topr] = COMBO(cmbo_topr, KC_NO), 
  [_btmr] = COMBO(cmbo_btmr, KC_ENT), 
  [_thmr] = COMBO(cmbo_thmr, KC_LALT)};
