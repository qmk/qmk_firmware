
#include "../__init__.h"

bool proceed_mlt(uint16_t keycode, keyrecord_t *record) {
    if (!record->tap.count) {
        if (record->event.pressed) register_code(keycode);
        else unregister_code(keycode);
    }

    return true;
}

bool mlt_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = true;

    switch (keycode) {
        case LHR_T:  // STURDY
        case LHR_E:  // STURDY
        case LHR_L:  // QWERTY
            return proceed_mlt(KC_LALT, record);

        case LHR_D:  // QWERTYi/
        case LHR_K:  // QWERTY
        case LHR_R:  // STURDY
            return proceed_mlt(KC_LCTL, record);

        case LHR_S:
            return proceed_mlt(
                is_layer_on(QWERTY)
                    ? KC_LALT  // QWERTY
                    : KC_LGUI, // STURDY
                record
            );

        case LHR_A:
            return proceed_mlt(
                is_layer_on(QWERTY)
                    ? KC_LGUI  // QWERTY
                    : KC_LCTL, // STURDY
                record
            );
    }

    return false;
}
