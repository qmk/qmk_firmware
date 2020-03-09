#include "process_compose_onboard.h"

__attribute__((weak)) bool compose_onboard_mapping(uint16_t* sequence, uint8_t len) {
    return false;
}
__attribute__((weak)) void compose_onboard_start(void) {}
__attribute__((weak)) void compose_onboard_end(void) {}

static bool composing_onboard = false;
static uint16_t compose_onboard_sequence[COMPOSE_ONBOARD_LEN] = {0, 0, 0, 0, 0};
static uint8_t compose_onboard_len = 0;

void qk_compose_onboard_start(void) {
    composing_onboard = true;
    memset(compose_onboard_sequence, 0, COMPOSE_ONBOARD_LEN * sizeof(uint16_t));
    compose_onboard_len = 0;
    compose_onboard_start();
}
void qk_compose_onboard_end(void) {
    composing_onboard = false;
    compose_onboard_end();
}

bool process_compose_onboard(uint16_t keycode, keyrecord_t* record) {
    if (!composing_onboard && keycode == KC_COMPOSE_ONBOARD && record->event.pressed) {
        qk_compose_onboard_start();
        return false;
    }
    if (!composing_onboard || !record->event.pressed) {
        return true;
    }
    // ignore MOD-keys and layer modifiers
    if (
        // ignore (L/R)-CTRL, ALT, GUI, Shift
        IS_MOD(keycode)
        // ignore any layer modifiers
        || (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_MOD_MAX)
        || (QK_LAYER_TAP_TOGGLE <= keycode && keycode <= QK_LAYER_MOD_MAX)
        || (QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX)
    ) {
        return true;
    }

    // we are composing and a non-layer-modifying key was pressed

    if (keycode == COMPOSE_ONBOARD_ABORT) {
        qk_compose_onboard_end();
        return false;
    }

    // this shouldn't happen, but check it for safety reasons
    if (compose_onboard_len >= COMPOSE_ONBOARD_LEN) {
        qk_compose_onboard_end();
    }

    compose_onboard_sequence[compose_onboard_len] = keycode;
    compose_onboard_len += 1;
    if (!compose_onboard_mapping(compose_onboard_sequence, compose_onboard_len)) {
        qk_compose_onboard_end();
    }

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
int compose_onboard_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len) {
    size_t test_len = min(input_len, seq_len);
    size_t match_index = compose_onboard_memcmp_index(seq, input, test_len);
    if (seq_len == input_len && match_index == test_len) {
        return -1;
    }
    if (match_index == seq_len) {
        return 1;
    }
    return 0;
}
