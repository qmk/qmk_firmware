#include "keycodes.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_colon_timer;

    switch (keycode) {
        case KC_LCCL:
            if (record->event.pressed) {
                my_colon_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(my_colon_timer) < TAPPING_TERM) {
                    SEND_STRING(":");
                }
            }
            return false;
    }
    return process_record_keymap(keycode, record);
}
