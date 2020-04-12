#include QMK_KEYBOARD_H

#include "sten.h"
/* 	 	
 *  .---------------------------.
 *	| FP01 | FP02 | FP03 | FP04 | 
 *  |---------------------------|
 *	| FP11 | FP12 | FP13 | FP14 | 
 *  '---------------------------'
 */

// Chord Prefixes
#define MEDIA 	( FP11 | FP12 )
#define MOVE		( FP01 | FP11 )
#define NUM			( FP04 | FP14 )

// QMK Layer Numbers
 #define BASE 0
 #define QMK	1

// Note: You can only use basic keycodes here!
// P() is just a wrapper to make your life easier, any C code can be executed.
// Only the longest matched chord is run!
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
    // SECRET AGENT CHORDS
    P( FP01 | FP02 | FP03 | FP04 | FP11 | FP12 | FP13 | FP14,    
								SEND(KC_LCTRL); SEND(KC_LALT); SEND(KC_DEL))
    P( FP01 | FP02 | FP03 | FP04,    
								SEND_STRING(VERSION); SEND_STRING(__DATE__));
    P( FP11 | FP12 | FP13 | FP14,    
								SWITCH_LAYER(QMK));

    // Media
    P( MEDIA | FP13,					SEND(KC_MPRV));
    P( MEDIA | FP14,					SEND(KC_MNXT));
    P( MEDIA | FP04,					SEND(KC_VOLU));
    P( MEDIA | FP03,  				SEND(KC_VOLD));
    P( MEDIA | FP03 | FP04,		SEND(KC_MPLY));
    P( MEDIA | FP02,  				SEND(KC_MUTE));

    // Movement Layer
    P( MOVE | FP12,				SEND(KC_LEFT));
    P( MOVE | FP13,    		SEND(KC_DOWN));
    P( MOVE | FP03,    		SEND(KC_UP));
    P( MOVE | FP14,    		SEND(KC_RIGHT));
    P( MOVE | FP02,    		SEND(KC_PGUP));
    P( MOVE | FP04,    		SEND(KC_PGDN));

		// Numpad
    P( NUM | FP01 | FP11, 				SEND(KC_4));
    P( NUM | FP02 | FP12, 				SEND(KC_5));
    P( NUM | FP03 | FP13, 				SEND(KC_6));
    P( NUM | FP01,   							SEND(KC_1));
    P( NUM | FP02,    						SEND(KC_2));
    P( NUM | FP03,    						SEND(KC_3));
    P( NUM | FP11,     						SEND(KC_7));
    P( NUM | FP12,     						SEND(KC_8));
    P( NUM | FP13,     						SEND(KC_9));
    P( NUM | FP11 | FP12 | FP13,  SEND(KC_0));

		// Base
    P( FP01 | FP11,								SEND_STRING("https://tenor.com/ZrF5.gif"));
    P( FP02 | FP12,								SEND_STRING("https://tenor.com/MlF8.gif"));
    P( FP03 | FP13,								SEND_STRING("https://tenor.com/zFTG.gif"));
    P( FP04 | FP14,								SEND_STRING("https://tenor.com/3j1u.gif"));

    P( FP01 | FP02,								SEND_STRING("https://tenor.com/IpA4.gif"));
    P( FP02 | FP03,								SEND_STRING("https://tenor.com/Nand.gif"));
    P( FP03 | FP04,								SEND_STRING("https://tenor.com/bbldB.gif"));
    P( FP11 | FP12,								SEND_STRING("https://tenor.com/oohE.gif"));
    P( FP12 | FP13,								SEND_STRING("https://tenor.com/w1DM.gif"));
    P( FP13 | FP14,								SEND_STRING("https://tenor.com/wfEk.gif"));
    P( FP12 | FP13 |  FP02|FP03,	SEND_STRING("https://tenor.com/XL3s.gif"));

    P( FP01,											SEND_STRING("https://tenor.com/Ain1.gif"));
    P( FP02,											SEND_STRING("https://tenor.com/yiMM.gif"));
    P( FP03,											SEND_STRING("https://tenor.com/Fqdy.gif"));
    P( FP04,											SEND_STRING("https://tenor.com/2OG5.gif"));
    P( FP11,											SEND_STRING("https://tenor.com/XFgo.gif"));
    P( FP12,											SEND_STRING("https://tenor.com/uYwy.gif"));
    P( FP13,											SEND_STRING("https://tenor.com/81Qj.gif"));
		P( FP14,											SEND(KC_ENT));

    return 0;
}

// Do not change QMK Layer BASE! This is your main keyboard.
// Make your QMK modifications to the later layers, to add 
// keys/customize on the first layer modify processQwerty():

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_faunch( STN_S1,  STN_TL,  STN_PL,  STN_HL, 
   												STN_S2,  STN_KL,  STN_WL,  STN_RL),
  [QMK] = LAYOUT_faunch( 	KC_1,  KC_2,  KC_3,  KC_4,
  											 	KC_5,  KC_6,  KC_7,  TO(BASE))
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
