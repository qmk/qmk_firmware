#include "rupa.h"

font_t *translator = NULL;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = get_mods()&MOD_MASK_SHIFT;
    bool is_pressed = record->event.pressed;

    switch(keycode) {
        case VRSN:
            if (is_pressed) {
                send_string_with_delay_P(PSTR(
                  "# " QMK_KEYBOARD "/" QMK_KEYMAP ":" QMK_VERSION " " QMK_BUILDDATE "\n"
                ), TAP_CODE_DELAY);
            }
            return false;

        case LOD:
        case RUPA:
            if (is_pressed) {
                if (keycode == LOD) {
                    send_unicode_string((is_shifted ? "¯\\_(ツ)_/¯" : "ಠ_ಠ"));
                } else if (keycode == RUPA) {
                    send_unicode_string((is_shifted ? "rūpa" : "Śrīrūpa"));
                }
            }
            return false;

        // script modes
        case U_FRACT:
        case U_MONOS:
        case U_SCRPT:
            if (is_pressed) {
                if (keycode == U_SCRPT) {
                    translator = (translator == &script_bold ? NULL : &script_bold);
                } else if (keycode == U_FRACT) {
                    translator = (translator == &fraktu_bold ? NULL : &fraktu_bold);
                } else if (keycode == U_MONOS) {
                    translator = (translator == &monosp_bold ? NULL : &monosp_bold);
                }
            }
            return true;

        default:
            if (is_pressed && translator != NULL) {
                return script_mode_translate(translator, is_shifted, keycode);
            }
            return true;
    }
}
