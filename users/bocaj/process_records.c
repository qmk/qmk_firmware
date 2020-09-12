#include "bocaj.h"
#include <print.h>

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

// Defines actions tor my global custom keycodes. Defined in bocaj.h file
// Then runs the _keymap's record handler if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#ifdef RGB_MATRIX_ENABLE
        && process_record_user_rgb_matrix(keycode, record)
#endif
    ) {
        switch (keycode) {
            case KC_WORKMAN ... KC_QWERTY:
                if (record->event.pressed) {
                    uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
                    if (!mods) {
                        set_single_persistent_default_layer(keycode - KC_WORKMAN);
                    } else if (mods & MOD_MASK_SHIFT) {
                        set_single_persistent_default_layer(keycode - KC_WORKMAN + 4);
                    } else if (mods & MOD_MASK_CTRL) {
                        set_single_persistent_default_layer(keycode - KC_WORKMAN + 8);
                    }
                }
                break;

            case MC_ARRW:
                if (!record->event.pressed) {
                    clear_mods();
                    send_string_with_delay_P(PSTR("->"), TAP_CODE_DELAY);
                }
                break;

            case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
                if (!record->event.pressed) {
                    clear_mods();
                    send_string_with_delay_P(PSTR("qmk compile "), TAP_CODE_DELAY);
                    send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD), TAP_CODE_DELAY);
                    send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
                }
                break;

            case VRSN:  // Prints firmware version
                if (record->event.pressed) {
                    send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
                }
                break;
#ifdef UNICODE_ENABLE
            case UC_FLIP:  // (ノಠ痊ಠ)ノ彡┻━┻
                if (record->event.pressed) {
                    send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
                }
                break;
            case UC_TABL:  // ┬─┬ノ( º _ ºノ)
                if (record->event.pressed) {
                    send_unicode_string("┬─┬ノ( º _ ºノ)");
                }
                break;
            case UC_SHRG:  // ¯\_(ツ)_/¯
                if (record->event.pressed) {
                    send_unicode_string("¯\\_(ツ)_/¯");
                }
                break;
            case UC_DISA:  // ಠ_ಠ
                if (record->event.pressed) {
                    send_unicode_string("ಠ_ಠ");
                }
                break;
#endif
#if defined(RGB_MATRIX_ENABLE)
            case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
                if (record->event.pressed) {
                    userspace_config.rgb_layer_change ^= 1;
                    dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                    eeconfig_update_user(userspace_config.raw);
                    if (userspace_config.rgb_layer_change) {
                        rgblight_enable_noeeprom();
                        layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
                    } else {
                        rgblight_disable_noeeprom();
                    }
                }
                break;
            case RGB_TOG:
                if (record->event.pressed) {
#    if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_toggle();
#    endif
                }
                return false;
                break;
            case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
                if (record->event.pressed) {
                    bool is_eeprom_updated;
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
                    if (userspace_config.rgb_matrix_idle_anim) {
                        userspace_config.rgb_matrix_idle_anim = false;
                        dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                        is_eeprom_updated = true;
                    }
#    endif
                    if (is_eeprom_updated) {
                        eeconfig_update_user(userspace_config.raw);
                    }
                }

// #    if defined(RGB_MATRIX_DISABLE_KEYCODES)
//                 if (keycode == RGB_MODE_FORWARD && record->event.pressed) {
//                     uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
//                     if (shifted) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_step_reverse();
// #        endif
//                     } else {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_step();
// #        endif
//                     }
//                 } else if (keycode == RGB_MODE_REVERSE && record->event.pressed) {
//                     uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
//                     if (shifted) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_step();
// #        endif
//                     } else {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_step_reverse();
// #        endif
//                     }
//                 } else if (keycode == RGB_HUI) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_increase_hue();
// #        endif
//                     }
//                 } else if (keycode == RGB_HUD) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_decrease_hue();
// #        endif
//                     }
//                 } else if (keycode == RGB_SAI) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_increase_sat();
// #        endif
//                     }
//                 } else if (keycode == RGB_SAD) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_decrease_sat();
// #        endif
//                     }
//                 } else if (keycode == RGB_VAI) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_increase_val();
// #        endif
//                     }
//                 } else if (keycode == RGB_VAD) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_decrease_val();
// #        endif
//                     }
//                 } else if (keycode == RGB_SPI) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_increase_speed();
// #        endif
//                     }
//                 } else if (keycode == RGB_SPD) {
//                     if (record->event.pressed) {
// #        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
//                         rgb_matrix_decrease_speed();
// #        endif
//                     }
//                 }
//                 return false;
// #    endif
#endif
        }
    }
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
    return true;
}
