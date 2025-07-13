#include "macro.h"


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CMT_BLK:
        if (record->event.pressed) {
            // when keycode CMT_BLK is pressed
            SEND_STRING("/*  */"); 
			tap_code(KC_LEFT);       // ← sposta il cursore
			tap_code(KC_LEFT);       // ← 
			tap_code(KC_LEFT);       // ← di altre 3 colonne
        } else {
            // when keycode CMT_BLK is released
        }
        break;
	case CMT_CLS: if (record->event.pressed) SEND_STRING(" */"); break;
	case CMT_OPN: if (record->event.pressed)SEND_STRING("/* ");	 break;
	case CMT_CMT: if (record->event.pressed)SEND_STRING("// ");  break;
	case PTR_OP:  if (record->event.pressed)SEND_STRING("->");   break;
	}
	
    return true;
}


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMT_BLK: //notice how it skips over F22
	
    break;
  }
}