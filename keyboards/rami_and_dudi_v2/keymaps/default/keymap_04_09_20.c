#include QMK_KEYBOARD_H


#define _BASE 0
#define _MY_LAYER 1

#define PASSPHRASE "poop1"
#define COMBINATION { 4, 10, 4 } //  2< 6> 2<
#define START_CW true
#define TOLERANCE 3


enum custom_keycodes {
  UP_URL = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x4
  (
    KC_MPRV, KC_MPLY, KC_MNXT,
    KC_F22, KC_F23, UP_URL,
    KC_F21, KC_F20,  TG(_MY_LAYER),
    KC_NO, TG(_MY_LAYER), KC_NO
  ),
    [_MY_LAYER] = LAYOUT_ortho_3x4
  (
    KC_1, KC_2, KC_3,
    KC_4, KC_5, KC_6,
    KC_7, KC_8, KC_TRANSPARENT,
    KC_NO, KC_NO, KC_NO
  )
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
     case UP_URL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_LSFT("t")));
		
      }	  
	  
//	        if (record->event.pressed) {
//        SEND_STRING(SS_LCTRL(SS_LSFT("t")));		
//      }	 
	  
	   else
	   case KC_F22:
      if (record->event.pressed) {
       SEND_STRING(SS_LCTRL("c"));;
	         return false;
      break;
      }
	  
	  case KC_F23:
      if (record->event.pressed) {
       SEND_STRING(SS_LCTRL("v"));;
		
      }	  
	

	  case KC_F21:
      if (record->event.pressed) {
       SEND_STRING(SS_LALT("a"));;
		
      }		
	  
	  	  case KC_F20:
      if (record->event.pressed) {
       SEND_STRING(SS_LALT("f"));;
		
      }
	  
	  
	  else
      return false;
      break;
  }
  return true;
}


void dip_switch_update_user(uint8_t index, bool active) 
{ 
 switch (index) {
        case 0:		//ENC0_SW2
        if(active) //ENC2_SW2 pressed
		{ 
			tap_code(KC_MUTE);
		} 
	else //ENC2_SW2 released
                {
					
			//do nothing
		}
		
		        case 1:		//ENC0_SW1
        if(active) //ENC2_SW1 pressed
		{ 
			tap_code(KC_F5);
		} 
	else //ENC2_SW1 released
                {
					
			//do nothing
		}
		
		
 break;
 }
}




void update_dial(bool direction) {
    const static uint8_t combo[] = COMBINATION;
    const static size_t combo_len = sizeof(combo);
    static bool direction_to_go = START_CW;
    static uint8_t state = 0, clicks = 0, grace = 0;

    if (direction == direction_to_go) {  // correct direction
        if (++clicks == combo[state] - TOLERANCE) {  // increment clicks and check if dialed enough
            clicks = grace = 0;
            direction_to_go = !direction_to_go;  // flip direction
            if (++state == combo_len) {  // increment state then check if we are at the end
                state = 0;  // reset to start
                direction_to_go = START_CW;
                SEND_STRING(PASSPHRASE);  // display passphrase
            }
        }
    } else {  // wrong direction so fail, except...
        if (clicks != 0 || ++grace > 2 * TOLERANCE) {  // a few extra ticks just after changing direction is acceptable
            state = clicks = grace = 0;  // reset to start
            direction_to_go = true;
        }
    }
}



void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
	else if (index == 1) { /* Second encoder */
	
	        if (clockwise) {

			tap_code16(C(S(KC_TAB)));
        } else {
            tap_code16(C(KC_TAB));
        }
		
        switch (get_highest_layer(layer_state)) {

            case _BASE:
                update_dial(clockwise);
                break;
            /* code for other layers... */
        }
							}
														}




