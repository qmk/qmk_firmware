#pragma once
#include "nathancooke7.h"

enum userspace_custom_keycodes {
#ifndef NO_CHARYBDIS_KEYCODES
  SARCASM = CHARYBDIS_SAFE_RANGE,
#else
  SARCASM = SAFE_RANGE,
#endif // !NO_CHARYBDIS_KEYCODES
  KC_SECRET_1,
  KC_SECRET_2
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);
