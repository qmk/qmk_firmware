#include "edvorakjp.h"

void dvorakj_layer_off(void) {
  layer_off(_EDVORAKJ1);
  layer_off(_EDVORAKJ2);
}

void matrix_init_user(void) {
  edvorakjp_status_init();
  matrix_init_keymap();
}

__attribute__ ((weak))
void matrix_init_keymap() {}

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return layer_state_set_keymap(state);
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap(uint32_t state) {
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_keymap(keycode, record) &&\
         process_record_edvorakjp_ext(keycode, record) &&\
         process_record_edvorakjp_swap_scln(keycode, record) &&\
         process_record_edvorakjp_config(keycode, record) &&\
         process_record_layer(keycode, record) &&\
         process_record_ime(keycode, record);
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
