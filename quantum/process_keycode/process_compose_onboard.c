#include "process_compose_onboard.h"

__attribute__((weak)) bool compose_onboard_mapping(uint16_t* sequence, uint8_t len) {
    return false;
}

static bool composing_onboard = false;
static uint16_t compose_onboard_sequence[COMPOSE_ONBOARD_LEN] = {0, 0, 0, 0, 0};
static uint8_t compose_onboard_len = 0;

void compose_onboard_start() {
    composing_onboard = true;
    compose_onboard_sequence = {0};
    compose_onboard_len = 0;
}
void compose_onboard_stop() {
    composing_onboard = false;
}

bool process_compose_onboard(uint16_t keycode, keyrecord_t* record) {
    if (!composing_onboard && keycode == KC_COMPOSE_ONBOARD && record->event.pressed) {
        compose_onboard_start();
        return false;
    }
    if (!composing_onboard || !record->event.pressed) {
        return true;
    }
    // we are composing and a non-layer-modifying key was pressed
    if (keycode == COMPOSE_ONBOARD_ABORT) {
        composing_onboard = false;
        return false;
    }


    // this shouldn't happen, but check it for safety reasons
    if (compose_onboard_len >= COMPOSE_ONBOARD_LEN) {
        compose_onboard_stop();
    }

    compose_onboard_sequence[compose_onboard_len] = keycode;
    compose_onboard_len += 1;
    if (!compose_onboard_mapping(compose_onboard_sequence, compose_onboard_len)) {
        compose_onboard_stop();
    }

    // Leader key set-up
#    ifndef LEADER_KEY_STRICT_KEY_PROCESSING
                if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
                    keycode = keycode & 0xFF;
                }
#    endif  // LEADER_KEY_STRICT_KEY_PROCESSING
    return false;
}

size_t compose_onboard_memcmp_index(uint16_t* seq, uint16_t* input, size_t len) {
    size_t i = 0;
    for (; i < len; i++) {
        if (seq[i] != input[i]) {
            return i;
        }
    }
    return i;
}
