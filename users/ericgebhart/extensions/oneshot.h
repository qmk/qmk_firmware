#define ENABLE_ONESHOT
#ifdef ENABLE_ONESHOT
#pragma once

typedef enum {
  ONESHOT_LCTL = 0,
  ONESHOT_LSFT = 1,
  ONESHOT_LALT = 2,
  ONESHOT_LGUI = 3,
  ONESHOT_RCTL = 4,
  ONESHOT_RSFT = 5,
  ONESHOT_RALT = 6,
  ONESHOT_RGUI = 7,
  ONESHOT_NONE = 8,
  ONESHOT_MOD_COUNT = 8,
} oneshot_mod;


// This function should be called inside proces_record_user and does everything needed to get one shot modifiers working.
// Returns true if the keycode needs further handling, false otherwise.
int8_t update_oneshot_modifiers(uint16_t keycode, keyrecord_t *record, int8_t keycode_consumed);
int8_t turnoff_oneshot_modifiers(void);

// TO BE IMPLEMENTED BY THE USER
// This function should return one of the oneshot_mod enumerations (see keymap.c implementation)
oneshot_mod get_modifier_for_trigger_key(uint16_t keycode);

// TO BE IMPLEMENTED BY THE USER
// This function should return true for keycodes that must be ignored in the oneshot modifier behaviour.
// You probably want to ignore layer keys. Trigger keys don't need to be specified here.
bool is_oneshot_modifier_ignored_key(uint16_t keycode);

// TO BE IMPLEMENTED BY THE USER
// This function should return true for keycodes that should reset all oneshot modifiers.
bool is_oneshot_modifier_cancel_key(uint16_t keycode);

#endif
