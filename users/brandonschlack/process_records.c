#include "brandonschlack.h"

// Super CMD↯TAB
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MAKE:
            if (!record->event.pressed) {
                bool flash = false;

        #if !defined(FLASH_BOOTLOADER) && !defined(IS_MACROPAD)
                uint8_t temp_mod = get_mods();
                uint8_t temp_osm = get_oneshot_mods();
                clear_mods();
                clear_oneshot_mods();
                if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT )
        #endif
                {
                    flash = true;
                }
                send_make_command(flash);
        #if !defined(FLASH_BOOTLOADER) && !defined(IS_MACROPAD)
                set_mods(temp_mod);
        #endif
            }
            break;
        case CMD_TAB:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        #ifdef IS_MACROPAD
        case TG_NAVI:
            if (!record->event.pressed) {
                layer_move(_NAVI);
            }
            break;
        case TG_REDR:
            if (!record->event.pressed) {
                layer_move(_REEDER);
            }
            break;
        case TG_MEDA:
            if (!record->event.pressed) {
                layer_move(_MEDIA);
            }
            break;
        case TG_KYPD:
            if (!record->event.pressed) {
                layer_move(_KEYPAD);
            }
            break;
        #endif // IS_MACROPAD
    }
    return process_record_keymap(keycode, record);
}

void matrix_scan_cmd_tab(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 500) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
}

/** Send Make Command
 * adds flash target and resets keyboard if flash_bootloader
 * set to true
 */
void send_make_command(bool flash_bootloader) {
    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    if (flash_bootloader) {
#if defined(BOOTLOADER_MDLOADER) // only run for Massdrop boards
        SEND_STRING(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP);
#elif defined(__arm__)  // only run for ARM boards
        SEND_STRING(":dfu-util");
#elif defined(BOOTLOADER_DFU) // only run for DFU boards
        SEND_STRING(":dfu");
#elif defined(BOOTLOADER_HALFKAY) // only run for teensy boards
        SEND_STRING(":teensy");
#elif defined(BOOTLOADER_CATERINA) // only run for Pro Micros
        SEND_STRING(":avrdude");
#endif // bootloader options
    }
    SEND_STRING(SS_TAP(X_ENTER));
    if (flash_bootloader) {
        reset_keyboard();
    }
}
