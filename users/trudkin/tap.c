/* Copyright 2020 Terence Rudkin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE
#include "tap.h"
static uint8_t state_cur[MOD_LMT];




uint8_t cur_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
    case 1:
            if (state->interrupted || !state->pressed) {return SINGLE_TAP;}
            else {return SINGLE_HOLD;}
            break;
    case 2:
        // DOUBLE_SINGLE_TAP two taps and some other key before tapping term||under tapping term
            if (state->interrupted) {return DOUBLE_SINGLE_TAP;}
            else if (state->pressed) {return DOUBLE_HOLD;}
            else {return DOUBLE_TAP;}
            break;
        // Assumes no one is trying to type the same letter three times (at least not quickly).
        // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    case 3:
            if (state->interrupted || !state->pressed) {return TRIPLE_TAP;}
            else {return TRIPLE_HOLD;}
            break;
    default:  
        return FUTURE_STATE; // Magic number. At some point this method will expand to work for more presses
    }
}



// Initialize tap structure associated with example tap dance key
static tap tap_state
= {
    .is_press_action = true,
    .state = 0,    

};



void pipe_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_PIPE);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(keycode_config(KC_LGUI))); 
            break;
        case DOUBLE_SINGLE_TAP: 
            tap_code16(KC_PIPE);
            register_code16(KC_PIPE);
    }
}

void pipe_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:
            unregister_code16(KC_PIPE);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(keycode_config(KC_LGUI))); 
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_PIPE);
    }
}


// For the left brace tap dance. Put it here so it can be used in any keymap
void l_brc_finished(qk_tap_dance_state_t *state, void *user_data){
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_9);
            break;
        case SINGLE_HOLD:
            register_code16(KC_9);
            break;
        case DOUBLE_TAP: // Allow nesting of 2 nines `99` within tapping term
            register_code16(KC_LBRC);
             break;
        case DOUBLE_HOLD:
            break;
        case DOUBLE_SINGLE_TAP: // Send two single taps
            tap_code16(KC_9);
            register_code16(KC_9);
            break;
        case TRIPLE_TAP:
            register_code16(KC_LCBR);
            break;
        case TRIPLE_HOLD:
            break;
        case FUTURE_STATE:
            break;
    }
}


void l_brc_reset(qk_tap_dance_state_t *state, void *user_data){
       
    switch (tap_state.state) {
        case SINGLE_TAP:
        case DOUBLE_SINGLE_TAP:
        case SINGLE_HOLD:
            unregister_code16(KC_9);
            break;
        case DOUBLE_TAP: // Allow nesting of 2 nines `99` within tapping term
            unregister_code16(KC_LBRC);
             break;
        case DOUBLE_HOLD:

            break;
        case TRIPLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case TRIPLE_HOLD:
            break;
        case FUTURE_STATE:
            break;
    }
}

// For the right brace tap dance. Put it here so it can be used in any keymap
void r_brc_finished(qk_tap_dance_state_t *state, void *user_data){
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP:
        case SINGLE_HOLD:
            register_code16(KC_0);
            break;
        case DOUBLE_TAP: 
            register_code16(KC_RBRC);
             break;
        case DOUBLE_HOLD:
            break;
        case DOUBLE_SINGLE_TAP: 
            tap_code16(KC_0);
            register_code16(KC_0);
            break;
        case TRIPLE_TAP:
            register_code16(KC_RCBR);
            break;
        case TRIPLE_HOLD:
            break;
        case FUTURE_STATE:
            break;
    }
}

void r_brc_reset(qk_tap_dance_state_t *state, void *user_data){
       
    switch (tap_state.state) {
        case SINGLE_TAP:
        case DOUBLE_SINGLE_TAP:
        case SINGLE_HOLD:
            unregister_code16(KC_0);
            break;
        case DOUBLE_TAP: 
            unregister_code16(KC_RBRC);
             break;
        case DOUBLE_HOLD:

            break;
        case TRIPLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        case TRIPLE_HOLD:
            break;
        case FUTURE_STATE:
            break;
    }
}




void set_mod_layer(qk_tap_dance_state_t *state, void *user_data) {
    mod_layer_t *mod_layer = (mod_layer_t *)user_data;
    state_cur[(mod_layer->index)%MOD_LMT] = cur_dance(state);
    switch (state_cur[mod_layer->index]) {
        case SINGLE_TAP:
            register_code16(mod_layer->keycode);
            break;
        case SINGLE_HOLD:
            layer_on(mod_layer->layer);
            break; 
        case DOUBLE_SINGLE_TAP: // Send two single taps
            tap_code16(mod_layer->keycode);
            register_code16(mod_layer->keycode);
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

    state_cur[mod_layer->index] = 0;
    }
}
#endif //TAP_DANCE_ENABLE







