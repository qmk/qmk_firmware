#include "tominabox1.h"
#include "meme_modes.c"
#include "combos.c"
#include "tap_dancing.c"

// Layer States
__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user (layer_state_t state) {
  return layer_state_set_keymap (state);
}

