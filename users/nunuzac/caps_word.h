#pragma once

#include "quantum.h"

bool process_caps_word(uint16_t keycode, keyrecord_t* record);
#if CAPS_WORD_IDLE_TIMEOUT > 0
void caps_word_task(void);
#else
static inline void caps_word_task(void) {}
#endif
void caps_word_set(bool active);
bool caps_word_get(void);
void caps_word_set_user(bool active);
bool caps_word_press_user(uint16_t keycode);
