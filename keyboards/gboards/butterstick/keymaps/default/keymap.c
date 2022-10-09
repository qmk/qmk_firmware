#include QMK_KEYBOARD_H

#include "sten.h"
/* 	 	
 *  Key names are inherited from steno machines
 *  .-----------------------------------------------------.
 *	| LSU | LFT | LP | LH | ST1 | RF | RP | RL | RT | RD  |
 *  |-----------------------------------------------------|
 *	| LSD | LK  | LW | LR | ST2 | RR | RB | RG | RS | RZ  |
 *  '-----------------------------------------------------'
 */

// Function prefixes
#define MEDIA 	(LSD | LK  | LW | LR)	
#define FUNCT 	(LSD | LK  | LP | LH)	
#define MOVE	(LSU | LFT | LP | LH)	
#define SYMB	(RD  | RZ)	
#define NUMA    (LW  | LR)	
#define NUMB    (RR  | RB)	

// QMK Layer Numbers
 #define BASE 0
 #define GAME 1

// Do not change QMK Layer 0! This is your main keyboard.
// Make your QMK modifications to the later layers, to add 
// keys/customize on the first layer modify processQwerty():
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_butter(
  	STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   	STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR
  ),
  // I don't game don't roast me thanks
  [GAME] = LAYOUT_butter(
  	KC_Q,  KC_W,  KC_E,  KC_R,  KC_T, KC_Y, KC_U, KC_I,  KC_O, KC_ENT,
  	KC_A,  KC_S,  KC_D,  KC_F,  KC_G, KC_H, KC_J, KC_K,  KC_L, TO(BASE)
  )
};

// Note: You can only use basic keycodes here!
// P() is just a wrapper to make your life easier, any C code can be executed.
// Only the longest matched chord is run!
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
    // SECRET AGENT CHORDS
    P( LSU | LK | RS | RD,    	SEND_STRING(VERSION); SEND_STRING(__DATE__));
		P( LR  | ST2| RR | RB, 		SEND(KC_BSPC));
    P( LSD | RZ,   			 	SEND(KC_SPC));

    // Dual chords
    P( LP  | LH,    			CLICK_MOUSE(KC_MS_BTN2));
    P( ST1 | RF,    			CLICK_MOUSE(KC_MS_BTN1));
    P( LSU | LFT,         SEND(KC_ESC));
		P( LSD | LK,					SEND(KC_LSFT));
		P( RZ  | RS,					SEND(KC_LSFT));
		P( ST2 | RR,					SEND(KC_SPC));
    P( RP  | RL,    			SEND(KC_LGUI));
    P( RT  | RD,    			SEND(KC_LCTL));
    P( RL  | RT,    			SEND(KC_LALT));
		P( LSU | LSD | LFT | LK,	SEND(KC_LCTL));
		P( RS  | RT  | RD  | RZ,	SEND(KC_ENT));

    // Function Layer
    P( FUNCT | RF,         SEND(KC_F1));
    P( FUNCT | RP,         SEND(KC_F2));
    P( FUNCT | RL,         SEND(KC_F3));
    P( FUNCT | RT,         SEND(KC_F4));
    P( FUNCT | RF | RR,    SEND(KC_F5));
    P( FUNCT | RP | RB,    SEND(KC_F6));
    P( FUNCT | RL | RG,    SEND(KC_F7));
    P( FUNCT | RT | RS,    SEND(KC_F8));
    P( FUNCT | RR,         SEND(KC_F9));
    P( FUNCT | RB,         SEND(KC_F10));
    P( FUNCT | RG,         SEND(KC_F11));
    P( FUNCT | RS,         SEND(KC_F12));

    // Movement Layer
    P( MOVE | RF,     SEND(KC_LEFT));
    P( MOVE | RP,     SEND(KC_DOWN));
    P( MOVE | RL,     SEND(KC_UP));
    P( MOVE | RT,     SEND(KC_RIGHT));
    P( MOVE | ST1,    SEND(KC_PGUP));
    P( MOVE | ST2,    SEND(KC_PGDN));

    // Media Layer
    P( MEDIA | RF,    SEND(KC_MPRV));
    P( MEDIA | RP,    SEND(KC_MPLY));
    P( MEDIA | RL,    SEND(KC_MPLY));
    P( MEDIA | RT,    SEND(KC_MNXT));
    P( MEDIA | RG,	  SEND(KC_VOLU));
    P( MEDIA | RB,    SEND(KC_VOLD));
    P( MEDIA | RS,    SEND(KC_MUTE));

    // Number Row, Right
    P( NUMB | LSU,    SEND(KC_1));
    P( NUMB | LFT,    SEND(KC_2));
    P( NUMB | LP,     SEND(KC_3));
    P( NUMB | LH,     SEND(KC_4));
    P( NUMB | ST1,    SEND(KC_5));
    P( NUMB | RF,     SEND(KC_6));
    P( NUMB | RP,     SEND(KC_7));
    P( NUMB | RL,     SEND(KC_8));
    P( NUMB | RT,     SEND(KC_9));
    P( NUMB | RD,     SEND(KC_0));

    // Number Row, Left
    P( NUMA | LSU,    SEND(KC_1));
    P( NUMA | LFT,    SEND(KC_2));
    P( NUMA | LP,     SEND(KC_3));
    P( NUMA | LH,     SEND(KC_4));
    P( NUMA | ST1,    SEND(KC_5));
    P( NUMA | RF,     SEND(KC_6));
    P( NUMA | RP,     SEND(KC_7));
    P( NUMA | RL,     SEND(KC_8));
    P( NUMA | RT,     SEND(KC_9));
    P( NUMA | RD,     SEND(KC_0));


    // Symbols and Numbers
    P( SYMB | LP | LW,      SEND(KC_LSFT); SEND(KC_9));       // (
    P( SYMB | LH | LR,      SEND(KC_LSFT); SEND(KC_0));       // )
    P( SYMB | ST1 | ST2,    SEND(KC_GRV));                    // `
    P( SYMB | RR  | RF,    	SEND(KC_LSFT); SEND(KC_3));       // #
    P( SYMB | LFT | LK,     SEND(KC_LSFT); SEND(KC_4));       // $
    P( SYMB | LSU,          SEND(KC_LSFT); SEND(KC_1));       // !
    P( SYMB | LSD,          SEND(KC_LSFT); SEND(KC_5));       // %
    P( SYMB | LFT,          SEND(KC_LSFT); SEND(KC_2));       // @
    P( SYMB | LK,           SEND(KC_LSFT); SEND(KC_6));       // ^
    P( SYMB | LP,           SEND(KC_LSFT); SEND(KC_LBRC));    // {
    P( SYMB | LW,           SEND(KC_LBRC));
    P( SYMB | LH,           SEND(KC_LSFT); SEND(KC_RBRC));    // }
    P( SYMB | LR,           SEND(KC_RBRC));
    P( SYMB | ST1,          SEND(KC_LSFT); SEND(KC_BSLS));    // |
    P( SYMB | ST2,          SEND(KC_LSFT); SEND(KC_GRV));     // ~
    P( SYMB | RP | RB,      SEND(KC_QUOT));
    P( SYMB | RP | RG,      SEND(KC_LSFT); SEND(KC_QUOT));    // "
    P( SYMB | RF,           SEND(KC_KP_PLUS));
    P( SYMB | RR,           SEND(KC_LSFT); SEND(KC_7));       // &
    P( SYMB | RP,           SEND(KC_MINS));
    P( SYMB | RB,           SEND(KC_EQL));
    P( SYMB | RL,           SEND(KC_SLSH));
    P( SYMB | RG,           SEND(KC_COMM));
    P( SYMB | RT,           SEND(KC_PAST));
    P( SYMB | RS,           SEND(KC_DOT));

    // Letters
    P( LSU | LSD,    SEND(KC_A));
    P( LFT | LK,     SEND(KC_S));
    P( LP  | LW,     SEND(KC_D));
    P( LH  | LR,     SEND(KC_F));
    P( ST1 | ST2,    SEND(KC_G));
    P( RF  | RR,     SEND(KC_H));
    P( RT  | RS,     SEND(KC_L));
    P( RD  | RZ,     SEND(KC_SCLN));
    P( RG  | RL,     SEND(KC_K));
    P( RP  | RB,     SEND(KC_J));
    P( LSU,          SEND(KC_Q));
    P( LSD,          SEND(KC_Z));
    P( LFT,          SEND(KC_W));
    P( LK,           SEND(KC_X));
    P( LP,           SEND(KC_E));
    P( LW,           SEND(KC_C));
    P( LH,           SEND(KC_R));
    P( LR,           SEND(KC_V));
    P( ST1,          SEND(KC_T));
    P( ST2,          SEND(KC_B));
    P( RF,          SEND(KC_Y));
    P( RR,          SEND(KC_N));
    P( RP,           SEND(KC_U));
    P( RB,           SEND(KC_M));
    P( RL,           SEND(KC_I));
    P( RG,           SEND(KC_COMM));
    P( RT,           SEND(KC_O));
    P( RS,           SEND(KC_DOT));
    P( RD,           SEND(KC_P));
    P( RZ,           SEND(KC_SLSH));

    return 0;
}

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
