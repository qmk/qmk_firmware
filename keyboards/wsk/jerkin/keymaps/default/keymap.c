#include QMK_KEYBOARD_H

enum custom_keycodes {KC_PASTA = SAFE_RANGE};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_BSPC, 
		CTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, LT(2, KC_ENT), 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LT(1, KC_SPC), KC_N, KC_M, KC_COMM, ALT_T(KC_DOT), GUI_T(KC_SLSH), SFT_T(KC_DEL)),

	[1] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_RBRC, KC_BSLS, 
		KC_TRNS, KC_MINS, KC_EQL, KC_BSLS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS),

	[2] = LAYOUT(
		RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PASTA, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
    switch (keycode) {
            case KC_PASTA:
                if (record->event.pressed) {
                    SEND_STRING("You better not be fucking thinking about flipping this board. I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed trades on /r/mm.  I am trained in gorilla warfare and I'm the top typist in the entire US armed forces at over 600 wpm. If you flip this board, you are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with flipping this board over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with this PCB. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little clever sale was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.");
                } else {}
                break;
           
        }
    }
    return true;
}	

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(B2);
  writePinLow(B2);
  // set NumLock LED to output and low
  setPinOutput(B6);
  writePinLow(B6);
  
}

void matrix_scan_user(void) {

}
	
	
uint32_t layer_state_set_user(uint32_t state)
{
    if (state & (1<<1)) {
    writePinHigh(B2);
    } else if (state & (1<<2)) {
        writePinLow(B2);
        writePinHigh(B6);
    } else if (state & (1<<3)) {
        writePinHigh(B2);
        writePinHigh(B6);
    } else {
        writePinLow(B2);
        writePinLow(B6);
    }
    return state;
}