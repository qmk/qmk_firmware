#include QMK_KEYBOARD_H


#define _BASE 0
#define _MY_LAYER 1


#define START_CW true



enum custom_keycodes {
  UP_URL = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x4
  (
    KC_F22, KC_F23, UP_URL,
    KC_MPRV, KC_MNXT, KC_F19,
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
      break;
      }
	  
	  case KC_F23:
      if (record->event.pressed) {
       SEND_STRING(SS_LCTRL("v"));; 
      break;
		
      }	  
	

	  case KC_F21:
      if (record->event.pressed) {
       SEND_STRING(SS_LALT("a"));;
	   break;
		
      }		
	  
	  case KC_F20:
      if (record->event.pressed) {
       SEND_STRING(SS_LALT("f"));;
	   break;
		
      }
	
	  case KC_F19:
      if (record->event.pressed) {
       SEND_STRING(SS_LALT("c"));;
	   break;
		
      }

	
	  
	  else
      return false;
      break;
  }
  return true;
}


void dip_switch_update_user(uint8_t index, bool active) 
{ 

         if (index == 0){		//ENC0_SW2
        if(active) //ENC2_SW2 pressed
		{ 
			tap_code(KC_MUTE);
		} 
	else //ENC2_SW2 released
                {
					
			//do nothing
		}
		 }
		 else if (index == 1){		//ENC0_SW1
        if(active) //ENC2_SW1 pressed
		{ 
			tap_code(KC_F5);
		} 
	else //ENC2_SW1 released
                {
					
			//do nothing
		}
		
		 }

 }





void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
           // tap_code(KC_VOLD);
			tap_code(KC_VOLU);
        } else {
            //tap_code(KC_VOLU);
			tap_code(KC_VOLD);
        }
    }
	else if (index == 1) { /* Second encoder */
	
	        if (clockwise) {

			//tap_code16(C(S(KC_TAB))); //big roteries 
			tap_code16(C(KC_TAB)); //small roteries 
        } else {
            //tap_code16(C(KC_TAB)); //big roteries 
			tap_code16(C(S(KC_TAB))); //small roteries 
        }
		
							}
														}




