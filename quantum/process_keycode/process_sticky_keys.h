#include <stdint.h>

#ifndef PROCESS_STICKY_KEYS_H
#define PROCESS_STICKY_KEYS_H

#ifdef STICKY_KEYS_ENABLE

#include "quantum.h"

bool process_sticky_keys(uint16_t keycode, keyrecord_t *record);

void sticky_keys_toggle(void);
void sticky_keys_cycle_modifier_state(int modifier);
void sticky_keys_clear_modifiers(void);
void sticky_keys_clear_non_locked_modifiers(void);
int sticky_keys_get_modifiers(void);

#endif

#endif
