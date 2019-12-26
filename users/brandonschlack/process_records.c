#include "brandonschlack.h"

#if defined(TAP_CODE_DELAY)
    #define SS_DELAY TAP_CODE_DELAY
#else
    #define SS_DELAY 5
#endif

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
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), SS_DELAY);
            }
            break;
        case QM_KYBD:  // Prints keyboard path
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR("keyboards/" QMK_KEYBOARD "/"), SS_DELAY);
            }
            break;
        case QM_KYMP:  // Prints keymap path
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR("keyboards/" QMK_KEYBOARD "/keymaps/" QMK_KEYMAP "/keymap.c"), SS_DELAY);
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
                    eeconfig_update_user(user_config.raw);
                }
            }
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
    send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), SS_DELAY);
    if (flash_bootloader) {
#if defined(KEYBOARD_massdrop_alt) // only run for Massdrop ALT
        send_string_with_delay_P(PSTR(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP), SS_DELAY);
#elif defined(KEYBOARD_coseyfannitutti_discipline) // only run for Discipline 65
        send_string_with_delay_P(PSTR(":program"), SS_DELAY);
#else // use universal flash command
        send_string_with_delay_P(PSTR(":flash"), SS_DELAY);
#endif
#if defined(FORCE_LAYOUT) // Add layout string if built with FORCE_LAYOUT
        send_string_with_delay_P(PSTR(" FORCE_LAYOUT=" FORCE_LAYOUT), SS_DELAY);
#endif
#if defined(CONVERT_TO_PROTON_C) // Add CTPC if built with CONVERT_TO_PROTON_C
        send_string_with_delay_P(PSTR(" CTPC=" CONVERT_TO_PROTON_C), SS_DELAY);
#endif
    }
    send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), SS_DELAY);
    if (flash_bootloader) {
        reset_keyboard();
    }
}
