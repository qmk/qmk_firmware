#include "compose.h"
#include "string.h"

//__attribute__((weak)) bool compose_mapping(uint16_t* sequence, uint8_t len) {
    //return false;
//}
__attribute__((weak)) void compose_start(void) {}
__attribute__((weak)) void compose_end(uint8_t state) {}

static bool composing = false;
static uint16_t compose_sequence[COMPOSE_LEN] = {0, 0, 0};
static uint8_t compose_len = 0;

void qk_compose_start(void) {
    composing = true;
    memset(compose_sequence, 0, COMPOSE_LEN * sizeof(uint16_t));
    compose_len = 0;
    compose_start();
}

void qk_compose_end(uint8_t state) {
    composing = false;
    compose_end(state);
}

bool process_compose(uint16_t keycode, keyrecord_t* record, uint16_t compose_keycode) {
    if (!composing && keycode == compose_keycode && record->event.pressed) {
        qk_compose_start();
        return false;
    }
    if (!composing || !record->event.pressed) {
        return true;
    }
    // ignore MOD-keys and layer modifiers
    if (
        // ignore (L/R)-CTRL, ALT, GUI, Shift
        IS_MODIFIER_KEYCODE(keycode)
        // ignore any layer modifiers
        || (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_MOD_MAX)
        || (QK_LAYER_TAP_TOGGLE <= keycode && keycode <= QK_LAYER_MOD_MAX)
        || (QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX)
    ) {
        return true;
    }

    // we are composing and a non-layer-modifying key was pressed

    if (keycode == compose_keycode) {
        qk_compose_end(COMPOSE_CANCELLED);
        return false;
    }

    // this shouldn't happen, but check it for safety reasons
    if (compose_len >= COMPOSE_LEN) {
        qk_compose_end(COMPOSE_ERROR);
    }

    compose_sequence[compose_len] = keycode;
    compose_len += 1;
    uint8_t state = compose_mapping(compose_sequence, compose_len);
    if (state != COMPOSE_PARTIAL) { // the only continuation state is partial
        qk_compose_end(state);
    }

    return false;
}

/*
 * determine if the given key sequences are equal, up to the length supplied
 */
bool key_seq_equal(uint16_t* seq, uint16_t* input, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (seq[i] != input[i]) {
            return false;
        }
    }
    return true;
}

/*
 * compare the input.  return of -1 is a match, 1 is a partial match and 0 is mismatch.
 */
int compose_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len) {
    // get the min length we need to compare.
    size_t test_len = input_len < seq_len ? input_len: seq_len;
    bool matches = key_seq_equal(seq, input, test_len);
    if (matches) {
        if (seq_len == input_len) { // full match
            return -1;
        } else {
            return 1;
        }
    }
    return 0;
}
