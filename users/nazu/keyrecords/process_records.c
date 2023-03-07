/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "nazu.h"
#include "version.h"

/**
 * @brief Keycode handler for keymaps
 *
 * This handles the keycodes at the keymap level, useful for keyboard specific customization
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool useTapDance = true;
uint8_t mod_state;
/**
 * @brief Main user keycode handler
 *
 * This handles all of the keycodes for the user, including calling feature handlers.
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord_t data structure
 * @return true Continue processing keycode and send to host
 * @return false Stop process keycode and do not send to host
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// #ifdef OLED_ENABLE
//     process_record_user_oled(keycode, record);
// #endif // OLED_ENABLE

    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_COLEMAK_DH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
            }
            return false;
        case KC_SWAP:
            keymap_config.raw = eeconfig_read_keymap();
            if (record->event.pressed) {
                keymap_config.swap_lalt_lgui = true;
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard(); // clear to prevent stuck keys
            }
            return false;
        case KC_NORM:
            keymap_config.raw = eeconfig_read_keymap();
            if (record->event.pressed) {
                keymap_config.swap_lalt_lgui = false;
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard(); // clear to prevent stuck keys
            }
            return false;
        case KC_R2:
            if (record->event.pressed) {
                if (keymap_config.swap_lalt_lgui) {
                    register_mods(MOD_BIT(KC_RGUI));
                } else {
                    register_mods(MOD_BIT(KC_RALT));
                }
            } else {
                if (keymap_config.swap_lalt_lgui) {
                    unregister_mods(MOD_BIT(KC_RGUI));
                } else {
                    unregister_mods(MOD_BIT(KC_RALT));
                }
            }
            return true;
        case KC_R1:
            if (record->event.pressed) {
                if (keymap_config.swap_lalt_lgui) {
                    register_mods(MOD_BIT(KC_RALT));
                } else {
                    register_mods(MOD_BIT(KC_RCTL));
                }
            } else {
                if (keymap_config.swap_lalt_lgui) {
                    unregister_mods(MOD_BIT(KC_RALT));
                } else {
                    unregister_mods(MOD_BIT(KC_RCTL));
                }
            }
            return true;
        case KC_4: // Implementation of Alt F4
            // Only detect in Windows-typical config
            if (!keymap_config.swap_lalt_lgui) {
                // Detect the activation of only Left Alt
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    if (record->event.pressed) {
                        // No need to register KC_LALT because it's already active.
                        // The Alt modifier will apply on this KC_F4.
                        register_code(KC_F4);
                    } else {
                        unregister_code(KC_F4);
                    }
                    // Do not let QMK process the keycode further
                    return false;
                }
            }
            // Else, let QMK process the KC_4 keycode as usual
            return true;
        case KC_A ... KC_Z: // Hack for EurKEY on Windows, where alternate characters do not work with LALT
                // Detect the activation of only Left Alt
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    static bool raltkey_registered;
                    if (record->event.pressed) {
                        // First, canceling MOD_LALT
                        del_mods(MOD_BIT(KC_LALT));
                        // Then sending actual combo
                        register_mods(MOD_BIT(KC_RALT));
                        register_code(keycode);
                        // Update the boolean variable to reflect the status of MOD_RALT
                        raltkey_registered = true;
                        // Reapplying modifier state so that the held LALT key still work even after having tapped the key.
                        set_mods(mod_state);
                        return false;
                    } else {
                        if (raltkey_registered) {
                            raltkey_registered = false;
                            unregister_mods(MOD_BIT(KC_RALT));
                            unregister_code(keycode);
                            return false;
                        }
                    }
                    // Do not let QMK process the keycode further
                    return true;
                }
            // Else, let QMK process the keycode as usual
            return true;
        case KC_DOT:
            if (keymap_config.swap_lalt_lgui) {
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    static bool lguikey_registered;
                    if (record->event.pressed) {
                        // First, canceling MOD_LALT
                        del_mods(MOD_BIT(KC_LALT));
                        // Then sending actual combo
                        register_mods(MOD_BIT(KC_LCTL));
                        register_mods(MOD_BIT(KC_LGUI));
                        register_code(KC_SPACE);
                        // Update the boolean variable to reflect the status of MOD_RALT
                        lguikey_registered = true;
                        // Reapplying modifier state so that the held LALT key still work even after having tapped the key.
                        set_mods(mod_state);
                        return false;
                    } else {
                        if (lguikey_registered) {
                            lguikey_registered = false;
                            unregister_mods(MOD_BIT(KC_LCTL));
                            unregister_mods(MOD_BIT(KC_LGUI));
                            unregister_code(KC_SPACE);
                            return false;
                        }
                    }
                    // Do not let QMK process the keycode further
                    return true;
                }
            }
            // Else, let QMK process the keycode as usual
            return true;
        case KC_SPACE:
            if (!keymap_config.swap_lalt_lgui) {
                if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
                        static bool lguikey_registered;
                        if (record->event.pressed) {
                            // First, canceling MOD_LALT
                            del_mods(MOD_BIT(KC_LALT));
                            del_mods(MOD_BIT(KC_LCTL));
                            // Then sending actual combo
                            register_mods(MOD_BIT(KC_LGUI));
                            register_code(KC_DOT);
                            // Update the boolean variable to reflect the status of MOD_RALT
                            lguikey_registered = true;
                            // Reapplying modifier state so that the held LALT key still work even after having tapped the key.
                            set_mods(mod_state);
                            return false;
                        } else {
                            if (lguikey_registered) {
                                lguikey_registered = false;
                                unregister_mods(MOD_BIT(KC_LGUI));
                                unregister_code(KC_DOT);
                                return false;
                            }
                        }
                        // Do not let QMK process the keycode further
                        return true;
                    }
                }
            }
            // Else, let QMK process the keycode as usual
            return true;
    }
    return true;
}
