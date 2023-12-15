#include USERSPACE_H
#include <stdbool.h>
#include <stdint.h>

bool shift_for_two(uint16_t keycode, keyrecord_t *record){
  uint16_t mod_state = get_mods();

  bool is_shifted = (get_mods() & MOD_MASK_SHIFT) ||
    (get_oneshot_mods() & MOD_MASK_SHIFT);

  if(record ->event.pressed) {
    // If shifted, double these common punctuation marks.
    if(is_shifted){
      // clear shift temporarily
      del_mods(MOD_MASK_SHIFT);
      del_oneshot_mods(MOD_MASK_SHIFT);

      tap_code16(keycode);
      tap_code16(keycode);

      // restore previous shift state
      set_mods(mod_state);
      return false;
    }
  }
  return true;
}

bool shift_for_three(uint16_t keycode, keyrecord_t *record){
  uint16_t mod_state = get_mods();

  bool is_shifted = (get_mods() & MOD_MASK_SHIFT) ||
    (get_oneshot_mods() & MOD_MASK_SHIFT);

  if(record ->event.pressed) {
    // If shifted, double these common punctuation marks.
    if(is_shifted){
      // clear shift temporarily
      del_mods(MOD_MASK_SHIFT);
      del_oneshot_mods(MOD_MASK_SHIFT);

      tap_code16(keycode);
      tap_code16(keycode);
      tap_code16(keycode);

      // restore previous shift state
      set_mods(mod_state);
      return false;
    }
  }
  return true;
  }

bool override_shift(uint16_t keycode,
                    uint16_t shift_keycode,
                    keyrecord_t *record
                    ) {

  bool is_shifted = (get_mods() & MOD_MASK_SHIFT) ||
    (get_oneshot_mods() & MOD_MASK_SHIFT);

  if (record->event.pressed) {
    if (is_shifted) {
      uint8_t mod_state = get_mods();
      del_mods(MOD_MASK_SHIFT);
      del_oneshot_mods(MOD_MASK_SHIFT);

      tap_code16(shift_keycode);

      set_mods(mod_state);
    } else {
      //tap_code16(keycode);
    }
  }
  return false;
}

// macros for use in alt_shift.defs.
#define ALT_SHIFT(KCKEY, KC01)            \
  case KCKEY:                                   \
  return override_shift(KCKEY, KC01, record);   \
  break;

#define SHIFT_FOR_2(KCKEY)                      \
  case KCKEY:                                   \
  return shift_for_two(KCKEY, record);          \
  break;

#define SHIFT_FOR_3(KCKEY)                \
  case KCKEY:                                   \
  return shift_for_three(KCKEY, record);        \
  break;

bool process_alt_shift_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
#include "alt_shift.def"
  }
  return true;
}
