#include "sigul.h"

enum planck_layers {
  _QWERTY,
  _LOWER, //symbols
  _RAISE, //numbers
  _ADJUST, //system
  _NUMPAD,
  _FN, 
  _MOUSE
};

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
