/* macro.h */
#pragma once
#include QMK_KEYBOARD_H 

enum custom_keycodes {
    CMT_BLK = SAFE_RANGE,   // produce: /*  */
    CMT_OPN,                // produce: /*
    CMT_CLS,                // produce: */abort
	CMT_CMT,		  		// priduce: //
	PTR_OP
    // …altri custom keycodes qui
};

bool process_record_user(uint16_t keycode, keyrecord_t *record);
void post_process_record_user(uint16_t keycode, keyrecord_t *record);