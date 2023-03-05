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
 
 // NAVI 10
#include QMK_KEYBOARD_H

#define INDICATOR_LED   B5


#define _ML1    2
#define _FN2    3
#define _PR3    4
#define _GI4    4


#define HS_RED  	0,255 
#define HS_WHITE 	0, 0
#define HS_ORANGE  28, 255
#define HS_GREEN   85, 255
#define HS_TURQUOISE 123, 90
#define HS_CYAN    128, 255
#define HS_AZURE   132, 102
#define HS_BLUE    170, 255
#define HS_PURPLE  191, 255
#define HS_MAGENTA 213, 255


//create the tap type
typedef struct {
    bool is_press_action;
    int state;
} tap;

//tap dance states
enum {
    // uses https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    TRIPLE_TAP = 4, 
};

//tap dance keys
enum {
    TAPPY_KEY = 0
};

enum custom_keycodes { // git macros 
    M_G_HERE = SAFE_RANGE,
    M_G_PUSH,
    M_G_PULL,
    M_G_ADD, 
    M_G_COMM 
};

//function to handle all the tap dances
int cur_dance(tap_dance_state_t *state);

//functions for each tap dance
void tk_finished(tap_dance_state_t *state, void *user_data);
void tk_reset(tap_dance_state_t *state, void *user_data);

// define the macros in here 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	// open git bash here 	
    case M_G_HERE:  
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_APP)"s");
        } else {
            // when keycode M_G_HERE is released
        }
        break;

	//git push
    case M_G_PUSH:
        if (record->event.pressed) {
            // when keycode M_G_PUSH is pressed
            SEND_STRING("git push"SS_TAP(X_ENTER));
        } else {
            // when keycode M_G_PUSH is released
        }
        break;
	
	// git pull 
    case M_G_PULL:
        if (record->event.pressed) {
           SEND_STRING("git pull"SS_TAP(X_ENTER));
        }
        break;
		
	// git add 
	case M_G_ADD:
        if (record->event.pressed) {
           SEND_STRING("git add ");
        }
        break;
		
	// git commit 	
    case M_G_COMM: // git commit 
        if (record->event.pressed) {
           SEND_STRING("git commit -m ' ");
        }
        break;
    }
    return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Base
    [0] = LAYOUT(
                 TD(TAPPY_KEY),KC_HOME, KC_PGUP,
                 KC_DEL,    KC_END,     KC_PGDN,
                 
                            KC_UP,
                 KC_LEFT,   KC_DOWN,    KC_RIGHT),
	
	// media function layer, toggled on a single tap
    [_ML1] = LAYOUT(
                 KC_TRNS,   KC_BSPC,    KC_VOLU, 
                 KC_MUTE,   KC_ENTER,    KC_VOLD,
                 
                            KC_SPC,
                 KC_MRWD,   KC_MPLY,    KC_MFFD),
                 
    // F keys, double tap to get here    
    [_FN2] = LAYOUT( 
                 TO(0),     KC_F3,    KC_F5, 
                 KC_F2,     KC_F4,    KC_F6,
                 
                            KC_F7,
                 KC_F9,     KC_F8,    KC_F10),
				 
    // programming, triple tap to get here      
    [_PR3] = LAYOUT(
                 TO(0),     A(KC_F7), S(KC_F10),    //atmel, segger, pycharm 
                 KC_F2,     KC_F4,    S(KC_F9),
                 
                            KC_UP,
                 KC_LEFT,   KC_DOWN,    KC_RIGHT),

	// git function layer, hold to get here		 
    [_GI4] = LAYOUT(
                 KC_TRNS,   M_G_PUSH,    M_G_ADD, 
                 M_G_HERE,   M_G_PULL,    M_G_COMM,
                 
                            RGB_VAI,
                 RGB_TOG,   RGB_VAD,    RGB_MOD),
		

                 
};

//determine the current tap dance state
int cur_dance (tap_dance_state_t *state){
    if(state->count == 1)
    {
        //if a tap was registered
        if(!state->pressed)
        {
            //if not still pressed, then was a single tap
            return SINGLE_TAP;
        } else 
        {
            //if still pressed/held down, then it's a single hold
            return SINGLE_HOLD;
        }
    } 
   else if (state->count == 2)
   {
       return DOUBLE_TAP;
   }
   
   else if (state->count == 3) 
   {
       return TRIPLE_TAP;
   }
   else 
   {
        return 8;
   }
}

//initialize the tap structure for the tap key
static tap tk_tap_state = {
    .is_press_action = true,
    .state = 0
};

//functions that control what our tap dance key does
void tk_finished(tap_dance_state_t *state, void *user_data){
    tk_tap_state.state = cur_dance(state);
	uint8_t val = rgblight_get_val();
    switch(tk_tap_state.state){
        case SINGLE_TAP:
            //send desired key when tapped:
            //setting to the media layer
            if(layer_state_is(_ML1)){
                //if already active, toggle it to off
                layer_off(_ML1);
                rgblight_sethsv(HS_PURPLE, val);
            } else {
                //turn on the media layer
                layer_on(_ML1);
                rgblight_sethsv_at(HS_RED, 0, 0);
                rgblight_sethsv_at(HS_GREEN, 0, 1);
                rgblight_sethsv_at(HS_BLUE, val, 2);
            }
            break;

        case DOUBLE_TAP:
            layer_on(_FN2);
            rgblight_sethsv_at(HS_RED, 0, 0);
            rgblight_sethsv_at(HS_GREEN, val, 1);
            rgblight_sethsv_at(HS_BLUE, 0, 2);
            break;
        case TRIPLE_TAP:
            layer_on(_PR3);
            rgblight_sethsv_at(HS_RED, 0, 0);
            rgblight_sethsv_at(HS_GREEN, val, 1);
            rgblight_sethsv_at(HS_BLUE, val, 2);
            break;
        case SINGLE_HOLD:
            //set to desired layer when held:
            //setting to the function layer
            layer_on(_GI4);
            rgblight_sethsv_at(HS_RED, val, 0);
            rgblight_sethsv_at(HS_GREEN, val, 1);
            rgblight_sethsv_at(HS_BLUE, val, 2);
            break;
    }
}

void tk_reset(tap_dance_state_t *state, void *user_data){
    //if held and released, leave the layer
    if(tk_tap_state.state == SINGLE_HOLD){
        layer_off(_GI4);
	uint8_t val = rgblight_get_val();
        rgblight_sethsv(HS_PURPLE, val);
    }
    //reset the state
    tk_tap_state.state = 0; 
}

//associate the tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TAPPY_KEY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tk_finished, tk_reset)
};
