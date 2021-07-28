#include "jelly.h"
#include <print.h>
#include "rgblight.h"




void led_set_kb(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

    led_set_user(usb_led);

}






bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
        
        


   
        default:
        break;
    }
  }
  return process_record_user(keycode, record);
}





void matrix_init_kb(void) {
    matrix_init_user(); 
    
}





void keyboard_post_init_kb(void){

   
    if(rgblight_get_mode()==RGBLIGHT_MODE_STATIC_LIGHT){
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    }


}



void matrix_scan_kb(void) {
    matrix_scan_user();
}



