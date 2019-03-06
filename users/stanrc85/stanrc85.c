#include "stanrc85.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_MAKE:
    if (!record->event.pressed) {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      clear_mods();
      clear_oneshot_mods();
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
        if (temp_mod & MODS_SHIFT_MASK || temp_osm & MODS_SHIFT_MASK ) {
          //RESET board for flashing if SHIFT held or tapped with KC_MAKE
          #if defined(__arm__)
            send_string_with_delay_P(PSTR(":dfu-util"), 10);
            wait_ms(100);
            reset_keyboard();
          #elif defined(BOOTLOADER_DFU)
            send_string_with_delay_P(PSTR(":dfu"), 10);
          #elif defined(BOOTLOADER_HALFKAY)
            send_string_with_delay_P(PSTR(":teensy"), 10);
          #elif defined(BOOTLOADER_CATERINA)
            send_string_with_delay_P(PSTR(":avrdude"), 10);
          #else
            reset_keyboard();
          #endif // bootloader options
        }
        if (temp_mod & MODS_CTRL_MASK || temp_osm & MODS_CTRL_MASK) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10); }
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
        set_mods(temp_mod);
      }
    return false;
    break;
  }
  return process_record_keymap(keycode, record);
}
