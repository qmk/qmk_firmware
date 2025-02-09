#include "idank.h"

enum idank_keycode {
    PIM_TOGGLE_RGB = QK_USER_0,
};

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PIM_TOGGLE_RGB:
            if (record->event.pressed) {
                SEND_STRING("abc");
            }
            return false;
            break;
    }
    return process_record_keymap(keycode, record);
}
