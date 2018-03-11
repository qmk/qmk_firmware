#include "talljoe.h"

void matrix_init_user(void) {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
}

uint32_t default_layer_state_set_kb(uint32_t state) {
  // persist changes to default layers
  eeconfig_update_default_layer(state);
  return state;
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.row, record->event.key.col, record->event.pressed);
#endif //CONSOLE_ENABLE

  switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
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
  }
  return process_record_keymap(keycode, record);
}
