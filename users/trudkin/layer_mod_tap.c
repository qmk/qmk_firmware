
#include QMK_KEYBOARD_H
#include "layer_mod_tap.h"

static uint8_t state_cur[MAX_LMT];

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return FUTURE_STATE; // At some point this method will expand to work for more presses
}


void set_mod_layer(qk_tap_dance_state_t *state, void *user_data) {
    mod_layer_t *mod_layer = (mod_layer_t *)user_data;
/* (mod_layer->index)%MOD_LMT This insures that the index is never out of bounds */
        state_cur[(mod_layer->index)%MOD_LMT] = cur_dance(state);
    switch (state_cur[mod_layer->index]) {
        case SINGLE_TAP:
            register_code16(mod_layer->keycode);
            break;
        case SINGLE_HOLD:
            layer_on(mod_layer->layer);
            break; 
        case DOUBLE_SINGLE_TAP: // Send two single taps
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;
        case DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(mod_layer->layer)) {
                layer_off(mod_layer->layer);
            } else {
                layer_on(mod_layer->layer);
            }
            break;
        case TRIPLE_TAP:
            break;
        case DOUBLE_HOLD:
            register_code16(mod_layer->mod_2_tap);
            layer_on(mod_layer->layer);
            break;
        case TRIPLE_HOLD:
            register_code16(mod_layer->mod_3_tap);
            layer_on(mod_layer->layer);
            break;
        case FUTURE_STATE:
            break;

    }
}

void reset_mod_layer(qk_tap_dance_state_t *state, void *user_data) {

    mod_layer_t *mod_layer = (mod_layer_t *)user_data;
    // If the key was held down and now is released then switch off the layer
    switch (state_cur[mod_layer->index]) {
        case SINGLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code16(mod_layer->keycode);
            break;
        case DOUBLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(mod_layer->layer);
        case DOUBLE_HOLD:            
            layer_off(mod_layer->layer);
            unregister_code16(mod_layer->mod_2_tap);
            break;
        case TRIPLE_HOLD:
            layer_off(mod_layer->layer);
            unregister_code16(mod_layer->mod_3_tap);
            break;          

    state = 0;
    }
}


