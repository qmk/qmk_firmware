#include "tap_dances.h"
#include "process_keycode/process_tap_dance.h"

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8;
}

__attribute__ ((weak))
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) { };

void td_trigger_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_trigger_layer_t *data = (qk_tap_dance_trigger_layer_t *)user_data;
    data->state = cur_dance(state);

#if RGB_ENABLE
    if ((data->layer == _LIGHT) && ((data->trigger == SINGLE_HOLD && data->state == DOUBLE_TAP) || (data->trigger == DOUBLE_TAP && data->state == TRIPLE_TAP))) {
        rgblight_toggle();
    } else if (data->state == data->trigger) {
#else
    if (data->state == data->trigger) {
#endif
        layer_on(data->layer);
    } else {
        process_tap_dance_keycode(false, data->layer);
    }

}
void td_trigger_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_trigger_layer_t *data = (qk_tap_dance_trigger_layer_t *)user_data;
    if (data->state == data->trigger) {
        switch (data->trigger) {
            case SINGLE_HOLD:
            case DOUBLE_HOLD:
            case TRIPLE_HOLD:
                layer_off(data->layer);
                break;
        }
    } else {
        process_tap_dance_keycode(true, data->layer);
    }
    data->state = 0;
}

/* Tap Dance: Layer Mod. Toggles Layer when tapped, Mod when held. */
void td_layer_mod_each(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;

    // Single tap → toggle layer, Single hold → mod
    if (state->pressed) {
        register_code(data->kc);
    } else if (state->count == 1) {
        state->finished = true;
    }
}

void td_layer_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 1 && !state->pressed) {
        layer_invert(data->layer);
    }
}

void td_layer_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        unregister_code(data->kc);
    }
}
