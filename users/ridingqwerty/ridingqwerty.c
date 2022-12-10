#include "ridingqwerty.h"

__attribute__((weak))
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
    matrix_init_keymap();

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    set_unicode_input_mode(UNICODE_MODE_LINUX);
#endif

    //set_single_persistent_default_layer(_QWERTY);
    default_layer_set(1U << _QWERTY);
}

__attribute__((weak))
void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
    // use for global event timers
}

__attribute__((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#if defined(CONSOLE_ENABLE)
    debug_enable = true;
    debug_matrix = true;
    //debug_keyboard=true;
    //debug_mouse=true;
#endif
}

__attribute__((weak))
layer_state_t   layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _EDITOR, _DEBUG, _SECRET);
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: %u\n", state);
#endif
    return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RC(ENT):
    case ED(ESC):
      return 225;
    default:
      return TAPPING_TERM;
  }
};

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NM(SCLN):
      return true;
    default:
      return false;
  }
}
