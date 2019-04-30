#include "brandonschlack.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT )
    #endif
            { //
                #if defined(__arm__)  // only run for ARM boards
                    SEND_STRING(":dfu-util");
                #elif defined(BOOTLOADER_DFU) // only run for DFU boards
                    SEND_STRING(":dfu");
                #elif defined(BOOTLOADER_HALFKAY) // only run for teensy boards
                    SEND_STRING(":teensy");
                #elif defined(BOOTLOADER_CATERINA) // only run for Pro Micros
                    SEND_STRING(":avrdude");
                #endif // bootloader options
            }
            if ( (temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            SEND_STRING(SS_TAP(X_ENTER));
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT) {
                reset_keyboard();
            }
            set_mods(temp_mod);
        }
        break;
    case MD_MAKE:  // Compiles the firmware, and adds custom flash command for Massdrop
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT )
    #endif
            { //
                SEND_STRING(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP);
            }
            SEND_STRING(SS_TAP(X_ENTER));
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT) {
                reset_keyboard();
            }
            set_mods(temp_mod);
        }
        break;
    case OS_MAC:
        set_single_persistent_default_layer(LB_MAC);
        break;
    case OS_WIN:
        set_single_persistent_default_layer(LB_WIN);
        break;
    case OS_NIX:
        set_single_persistent_default_layer(LB_NIX);
        break;
    case WN_SLPD:
        tap_code16(G(KC_L));
        tap_code(KC_SYSTEM_POWER);
        break;

  }
  return process_record_keymap(keycode, record);
}
