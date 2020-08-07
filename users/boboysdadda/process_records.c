#include "boboysdadda.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }


    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY ... KC_DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(keycode - KC_QWERTY);
            }
            break;
        case CP_PST:
        
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("c"));
        } else {
            SEND_STRING(SS_LCTL("v"));
        }
        break;
        case KC_MAKE:
            if (!record->event.pressed) {
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
                send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT) {
                    send_string_with_delay_P(PSTR(":flash"), TAP_CODE_DELAY);
                }
                send_string_with_delay_P(PSTR(" -j8 --output-sync\n"), TAP_CODE_DELAY);
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
    }
    return process_record_keymap(keycode, record)&&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
           process_record_user_rgb(keycode, record) &&
#endif  // RGBLIGHT_ENABLE
           process_record_secrets(keycode, record);
}
