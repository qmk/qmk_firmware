#include "brandonschlack.h"

// Super CMD↯TAB
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// Consolidated Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QM_MAKE: //
            if (record->event.pressed) {
                bool flash = false;
        // If is a keyboard and auto-flash is not set in rules.mk,
        // then Shift will trigger the :flash target
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
            }
            break;
        case QM_FLSH: // Sends Make command with :flash target
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                send_make_command(true);
            }
            break;
        case QM_VRSN:  // Prints firmware version
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
            }
            break;
        case QM_KYBD:  // Prints keyboard path
            if (record->event.pressed) {
                SEND_STRING("keyboards/" QMK_KEYBOARD "/");
            }
            break;
        case QM_KYMP:  // Prints keymap path
            if (record->event.pressed) {
                SEND_STRING("keyboards/" QMK_KEYBOARD "/keymaps/" QMK_KEYMAP "/keymap.c");
            }
            break;
        case CMD_TAB: // Super CMD↯TAB
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
        #if defined(RGB_THEME_ENABLE)
        case RGB_LYR:
            if (record->event.pressed) {
                user_config.rgb_layer_change ^= 1;
                dprintf("rgb layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                eeconfig_update_user(user_config.raw);
                if (user_config.rgb_layer_change) {
                    layer_state_set(layer_state);
                }
            }
            break;
        case RGB_HUI ... RGB_SAD:
            if (record->event.pressed) {
                if (user_config.rgb_layer_change) {
                    user_config.rgb_layer_change = false;
                    dprintf("rgb layer change [EEPROM]: %u\n", user_config.rgb_layer_change);
                    eeconfig_update_user(user_config.raw);
                }
            }
            break;
        case RGB_THEME_FORWARD:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
                if(shifted) {
                    rgb_theme_step_reverse();
                } else {
                    rgb_theme_step();
                }
                layer_state_set(layer_state);
            }
            break;
        case RGB_THEME_REVERSE:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
                if(shifted) {
                    rgb_theme_step();
                } else {
                    rgb_theme_step_reverse();
                }
                layer_state_set(layer_state);
            }
            break;
        #endif
    }
    return process_record_keymap(keycode, record);
}

// Super CMD↯TAB
void matrix_scan_cmd_tab(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 500) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
}

/**
 * Send Make Command
 *
 * Sends 'make keyboard:keymap command to compile firmware
 * Adds :flash target and resets keyboard, if flash_bootloader set to true
 * Sends FORCE_LAYOUT parameter if built with FORCE_LAYOUT
 */
void send_make_command(bool flash_bootloader) {
    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    if (flash_bootloader) {
#if defined(KEYBOARD_massdrop_alt) // only run for Massdrop ALT
        SEND_STRING(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP);
#else // use universal flash command
        SEND_STRING(":flash");
#endif
    }
#if defined(FORCE_LAYOUT) // Add layout string if built with FORCE_LAYOUT
    SEND_STRING(" FORCE_LAYOUT=" FORCE_LAYOUT);
#endif
#if defined(CONVERT_TO_PROTON_C) // Add CTPC if built with CONVERT_TO_PROTON_C
    SEND_STRING(" CTPC=yes");
#endif
    SEND_STRING(SS_TAP(X_ENTER));
    if (flash_bootloader) {
        reset_keyboard();
    }
}
