#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

void perform_mod_tap_with_mod(keyrecord_t *record, uint8_t holdMod, uint8_t tapMod, uint8_t keycode);

void toggle_superduper_mode(void);
void set_superduper_key_combo_layer(uint16_t layer);
void set_superduper_key_combos(void);
void clear_superduper_key_combos(void);

#endif
