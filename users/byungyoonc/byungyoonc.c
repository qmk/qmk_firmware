#include QMK_KEYBOARD_H
#include "byungyoonc.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
static const char *const secrets[] = {"test1", "test2"};
#endif

#if !defined(MACRO_TIMER)
#   define MACRO_TIMER 20
#endif

/* replicaJunction's process_record_user_kb */
__attribute__ ((weak))
bool process_record_user_kb(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_SEC1 ... KC_SEC2: /* Secrets!  Externally defined strings, not stored in repo */
        if (!record->event.pressed) {
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            send_string_with_delay(secrets[keycode - KC_SEC1], MACRO_TIMER);
        }
        return false;
        break;
    }
    return process_record_user_kb(keycode, record);
};

