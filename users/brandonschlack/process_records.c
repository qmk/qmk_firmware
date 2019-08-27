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
        #if defined(RGB_THEME)
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
    send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
    if (flash_bootloader) {
#if defined(MD_BOOTLOADER) // only run for Massdrop boards
        send_string_with_delay_P(PSTR(" && mdlflash " QMK_KEYBOARD " " QMK_KEYMAP), 10);
#else // use universal flash command
        send_string_with_delay_P(PSTR(":flash"), 10);
#endif
    }
    send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
    if (flash_bootloader) {
        reset_keyboard();
    }
}
