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
const uint16_t PROGMEM cmbo_btml[] = {KC_X,     KC_C,   COMBO_END};
const uint16_t PROGMEM cmbo_thml[] = {MO(1),    KC_SPC, COMBO_END};
const uint16_t PROGMEM cmbo_midd[] = {KC_G,     KC_H,   COMBO_END};
const uint16_t PROGMEM cmbo_topr[] = {KC_I,     KC_O,   COMBO_END};
const uint16_t PROGMEM cmbo_btmr[] = {KC_COMM,  KC_DOT, COMBO_END};
const uint16_t PROGMEM cmbo_thmr[] = {KC_RSFT,  MO(2),  COMBO_END};

// desired outputs
// enum combo_all { _mod_lctl, _mod_lsft, _mod_lalt, _mod_lgui,  _mod_rctl, 
//                  _key_tab,  _key_ent,  _key_spc,  _key_bspc,  _key_del,  
//                  _key_esc,  _key_home, _key_end,  _key_pgup,  _key_pgdn, 
//                  _key_up,   _key_down, _key_left, _key_right, ALK_LENGTH 
//                  };
// uint16_t ALK_LEN = ALK_LENGTH;

// MOD_LCTL	Left Control
// MOD_LSFT	Left Shift
// MOD_LALT	Left Alt
// MOD_LGUI	Left GUI (Windows/Command/Meta key)

combo_t key_combos[] = {
  [_topl] = COMBO(cmbo_topl, KC_TAB), 
  [_btml] = COMBO(cmbo_btml, OSM(MOD_LCTL), 
  [_thml] = COMBO(cmbo_thml, OSM(MOD_LGUI), 
  [_midd] = COMBO(cmbo_midd, KC_F1),
  [_topr] = COMBO(cmbo_topr, KC_NO),
  [_btmr] = COMBO(cmbo_btmr, OSM(KC_ENT)), 
  [_thmr] = COMBO(cmbo_thmr, OSM(MOD_LALT))
};
