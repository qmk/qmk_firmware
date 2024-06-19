// positional descriptions
enum combo_pos {  
// ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
// │  Q    │  W    │  E    │  R    │  T    │   │  Y    │  U    │  I    │  O    │  P    │
                _topl,                                              _topr,
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │  A    │  S    │  D    │  F    │  G    │   │  H    │  J    │  K    │  L    │  ;    │
                                          _midd,
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │  Z    │  X    │  C    │  V    │  B    │   │  N    │  M    │  ,    │  .    │  /    │
                _btml,                                              _btmr,
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │  sym  │  _    │   │  ^    │  num  │       │       │       │
                                _thml,                _thmr, 
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
COMBO_LENGTH  };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM cmbo_topl[] = {KC_W,     KC_E,   COMBO_END};
const uint16_t PROGMEM cmbo_topr[] = {KC_I,     KC_O,   COMBO_END};
const uint16_t PROGMEM cmbo_midd[] = {KC_G,     KC_H,   COMBO_END};
const uint16_t PROGMEM cmbo_btml[] = {KC_X,     KC_C,   COMBO_END};
const uint16_t PROGMEM cmbo_btmr[] = {KC_COMM,  KC_DOT, COMBO_END};
const uint16_t PROGMEM cmbo_thml[] = {MO(1),    KC_SPC, COMBO_END};
const uint16_t PROGMEM cmbo_thmr[] = {KC_RSFT,  MO(2),  COMBO_END};

// positional descriptions
enum kcout_pos {  
// ┌───────┬───────┬───────┬───────┬───────┐   ┌───────┬───────┬───────┬───────┬───────┐
// │  Q    │  W    │  E    │  R    │  T    │   │  Y    │  U    │  I    │  O    │  P    │
                KC_TAB,                                              KC_NO,
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │  A    │  S    │  D    │  F    │  G    │   │  H    │  J    │  K    │  L    │  ;    │
                                          KC_F1,
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │  Z    │  X    │  C    │  V    │  B    │   │  N    │  M    │  ,    │  .    │  /    │
                OSM(MOD_LCTL),                                              OSM(KC_ENT),
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │  sym  │  _    │   │  ^    │  num  │       │       │       │
                                OSM(MOD_LGUI),                OSM(MOD_LALT), 
// ├───────┼───────┼───────┼───────┼───────┤   ├───────┼───────┼───────┼───────┼───────┤
KCOUT_LENGTH  };
uint16_t KCOUT_LEN = KCOUT_LENGTH;

combo_t key_combos[] = {
  [_topl] = COMBO(cmbo_topl, kcout_pos[_topl]), 
  [_topr] = COMBO(cmbo_topr, kcout_pos[_topr]),
  [_midd] = COMBO(cmbo_midd, kcout_pos[_midd]),
  [_btml] = COMBO(cmbo_btml, kcout_pos[_btml]), 
  [_btmr] = COMBO(cmbo_btmr, kcout_pos[_btmr]), 
  [_thml] = COMBO(cmbo_thml, kcout_pos[_thml]), 
  [_thmr] = COMBO(cmbo_thmr, kcout_pos[_thmr])
};
