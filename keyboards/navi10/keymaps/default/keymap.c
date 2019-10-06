/* Copyright 2019 Ethan Durrant (emdarcher)
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

typedef struct {
    bool is_press_action;
    int state;
} tap;

//tap dance states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3
};

//tap dance keys
enum {
    TAPPY_KEY = 0
};

//function to handle all tap dances
int cur_dance(qk_tap_dance_state_t *state);

//function for each tap dance
void tk_finished(qk_tap_dance_state_t *state, void *user_data);
void tk_reset(qk_tap_dance_state_t *state, void *user_data);

//variable to track current active layer
int active_layer;

#define INDICATOR_LED   B5

#define _ML0    1
#define _CL0    2
#define _ML1    3
//#define X0 LT( _ML0, KC_NUMLOCK )
#define X1 TG( _CL0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 TD(TAPPY_KEY),KC_HOME, KC_PGUP, 
                 KC_DEL,    KC_END,     KC_PGDN,
                 
                            KC_UP,
                 KC_LEFT,   KC_DOWN,    KC_RIGHT),
    [_ML0] = LAYOUT(/* function layer */
                 KC_TRNS,   KC_PAUS,    KC_VOLU, 
                 X1,        KC_SLCK,    KC_VOLD,
                 
                            KC_TRNS,
                 KC_TRNS,   KC_TRNS,    KC_TRNS),
    [_CL0] = LAYOUT(/* control layer */
                 KC_TRNS,   KC_TRNS,    KC_TRNS, 
                 KC_TRNS,   KC_TRNS,    KC_TRNS,
                 
                                LCTL(KC_UP),
                 LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_RIGHT) ),
    [_ML1] = LAYOUT(/* media function layer on tap (uses NUM_LOCK)*/
                 KC_TRNS,   KC_TRNS,    KC_VOLU, 
                 KC_MUTE,   KC_TRNS,    KC_VOLD,
                 
                            KC_SPC,
                 KC_MRWD,   KC_MPLY,    KC_MFFD),
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

//update the active layer
uint32_t layer_state_set_user(uint32_t state){
    switch(biton32(state)){
        case 1:
            active_layer = 1;
            break;
        case 2:
            active_layer = 2;
            break;
        case 3:
            active_layer = 3;
            break;
        default:
            active_layer = 0;
            break;
    }
    return state;
}

//determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state){
    if(state->count == 1){
        //if a tap was registered
        if(!state->pressed){
            //if not still pressed, then was a single tap
            return SINGLE_TAP;
        } else {
            //if still pressed/held down, then it's a single hold
            return SINGLE_HOLD;
        }
    } else if(state->count == 2){
        //if tapped twice, set to double tap
        return DOUBLE_TAP;
    } else {
        return 8;
    }
}


//initialize the tap structure for the tap key
static tap tk_tap_state = {
    .is_press_action = true,
    .state = 0
};

//functions that control what our tap dance key does
void tk_finished(qk_tap_dance_state_t *state, void *user_data){
    tk_tap_state.state = cur_dance(state);
    switch(tk_tap_state.state){
        case SINGLE_TAP:
            //send the code for a single tap
            tap_code(KC_INS);
            break;
        case SINGLE_HOLD:
            //set to desired layer when held:
            //setting to the function layer
            layer_on(_ML0);
            break;
        case DOUBLE_TAP:
            if(active_layer == _ML1){
                //if already active, toggle it to off
                layer_off(_ML1);
                //turn off the indicator LED
                //set LED HI to turn it off
                writePinHigh(INDICATOR_LED);
            } else {
                //turn on the media layer
                layer_on(_ML1);
                //turn on the indicator LED
                //set LED pin to LOW to turn it on
                writePinLow(INDICATOR_LED);
            }
    }
}

void tk_reset(qk_tap_dance_state_t *state, void *user_data){
    //if held and released, leave the layer
    if(tk_tap_state.state == SINGLE_HOLD){
        layer_off(_ML0);
    }
    //reset the state
    tk_tap_state.state = 0; 
}


//associate the tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TAPPY_KEY] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tk_finished, tk_reset, 275)
};
