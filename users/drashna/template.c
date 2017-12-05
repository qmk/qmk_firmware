#include "drashna.h"
#include "quantum.h"
#include "action.h"
#include "version.h"

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) {
  matrix_init_keymap();
}

// No global matrix scan code, so just run keymap's matix
// scan function
void matrix_scan_user(void) {
  matrix_scan_keymap();
}


// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's recod handier if not processed here,
// And use "NEWPLACEHOLDER" for new safe range
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  switch (keycode) {
  case KC_MAKE:
    if (!record->event.pressed) {
      SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
        ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
        ":teensy"
#elif defined(BOOTLOADER_CATERINA)
        ":avrdude"
#endif
        SS_TAP(X_ENTER));
    }
    return false;
    break;
  case KC_RESET:
    if (!record->event.pressed) {
      reset_keyboard();
    }
    return false;
    break;
  case EPRM:
    if (record->event.pressed) {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  }
  return process_record_keymap(keycode, record);
}

// Runs state check and changes underglow color and animation
// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user (uint32_t state) {
  return layer_state_set_keymap (state);
}
