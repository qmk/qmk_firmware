#include QMK_KEYBOARD_H


static uint16_t key_timer;

bool checktime(void){
		return (timer_elapsed(key_timer) < 150) ? true : false;
	};

// general keydefs
#define norm 0		// Default layer
#define elev 1		// Layer directional keys
#define supr 2		// F-keys and mediakeys
#define spac 3		//
#define FNO1 4		//
#define FNO2 5		//
#define FNO3 6		//
#define MAC0 M(0)	//
#define MAC1 M(1)	//
#define MAC2 M(2)	//
#define MAC3 M(3)	//
#define MAC4 M(4)	//
#define MAC5 M(5)	//
#define MAC6 M(6)	//
#define MAC7 M(7)	//
#define MAC8 M(8)	//
#define MAC9 M(9)	//
#define GRAV KC_GRV //
#define MEDI F(FNO1)//

// General shortenings
#define ESCA KC_ESC
#define MINS KC_MINS
#define EQUL KC_EQL
#define BSPC KC_BSPC
#define DELE KC_DEL
#define LBRC KC_LBRC
#define RBRC KC_RBRC
#define ALTR KC_RALT
#define SCLN KC_SCLN
#define QUOT KC_QUOT
#define NUHS KC_NUHS
#define ENTE KC_ENT
#define NUBS KC_NUBS	// Less/ greater sign
#define COMM KC_COMM	// Comma
#define FSTO KC_DOT		// Full stop
#define SLSH KC_SLSH
#define ALTL KC_LALT
#define GUIL KC_LGUI
#define GUIR KC_RGUI
#define MENO KC_MENU
// The F-row/layer:
#define FK01 KC_F1
#define FK02 KC_F2
#define FK03 KC_F3
#define FK04 KC_F4
#define FK05 KC_F5
#define FK06 KC_F6
#define FK07 KC_F7
#define FK08 KC_F8
#define FK09 KC_F9
#define FK10 KC_F10
#define FK11 KC_F11
#define FK12 KC_F12
#define FK13 KC_F13
#define FK14 KC_F14
// Special Actions and Media Keys
#define INSE KC_INS  	// Insert here
#define HOME KC_HOME 	// Go to beginning of line
#define ENDI  KC_END 	// go to end of line
#define PSCR  KC_PSCR 	// Print Screen
#define SLCK  KC_SLCK 	// go to end of line
#define PGDN  KC_PGDN 	// go to end of line
#define PGUP  KC_PGUP 	// go to end of line
#define PLPS KC_MPLY 	// Play/Pause
#define PAUS KC_PAUS 	// Pause button
#define MUTE KC_MUTE 	// Mute sound
#define VOLU KC_VOLU 	// Volume increase
#define VOLD KC_VOLD 	// Volume decrease
#define MNXT KC_MNXT 	// next track
#define MPRV KC_MPRV 	// prev track
#define MSTP KC_MSTP 	// stop playing
#define MSEL KC_MSEL 	// Select media (Start playing it)
#define MAIL KC_MAIL 	// Open default mail app
#define CALC KC_CALC 	// Open default calculator app
#define MYCM KC_MYCM 	// Open default file manager
//#define LILO KC_XXXXXX	// Reserved for later
//#define LIHI KC_XXXXXX	// Reserved for later


// dual-role shortcuts
#define DUTB LT(elev, KC_TAB) 	// `tabs` layer on hold and tab on tap
#define DUSP LT(spac, KC_SPACE)	// `spce` layer on hold and space on tap
#define LOCK LGUI(KC_L)			// lock computer (win)

// Space Admiral Strokers
#define SADL MAC0 				// Hold for lshift and { on tap
#define SADR MAC1				// Hold for rshift and } on tap
#define CADL MAC2				// Hold for lctrl and [ on tap
#define CADR MAC3				// Hold for rctrl and ] on tap

// arrow cluster duality bottom right corner
#define ARLF ALT_T(KC_LEFT) // Left arrow
#define ARRT CTL_T(KC_RIGHT)// Right arrow
#define ARUP SFT_T(KC_UP)	// Up arrow
#define ARDN GUI_T(KC_DOWN) // Down arrow

// brackets
#define NOCL RALT(KC_7)    // [
#define NOCR RALT(KC_0)    // ]
#define NOPL LSFT(KC_8)    // (
#define NOPR LSFT(KC_9)    // )
#define NOAL KC_NUBS       // <
#define NOAR LSFT(KC_NUBS) // >
#define NOBL RALT(KC_8)    // [
#define NOBR RALT(KC_9)    // ]

// increase readability
#define XXXX	KC_TRNS
#define DEAD 	KC_NO
#define SCAN	KC_TRNS // Scandinavian keys, the Row 5 key 5 is actually Row 1 key 15 on the PCB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[ norm ] = LAYOUT_all( // Normal scandinavian mapping (danish has QUOT and SCLN wapped)
        GRAV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, MINS, EQUL, BSPC, DELE,\
        DUTB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, LBRC, RBRC, DEAD,\
        ALTR, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, SCLN, QUOT, NUHS, ENTE,\
				SADL, NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, COMM, FSTO, SLSH, SADR, DEAD,\
				CADL, ALTL, GUIL,           		DUSP,             	    GUIR, MEDI, MENO, CADR),

[ elev ] = LAYOUT_all( // The f-Row (with f13-14), Special keys and media keys
				LOCK, FK01, FK02, FK03, FK04, FK05, FK06, FK07, FK08, FK09, FK10, FK11, FK12, FK13, FK14,\
				XXXX, XXXX, XXXX, XXXX, MAIL, XXXX, XXXX, HOME, INSE, PSCR, SLCK, PAUS, PGUP, XXXX,\
			    XXXX, XXXX, XXXX, XXXX, MYCM, XXXX, XXXX, MPRV, PAUS, MNXT, XXXX, XXXX, PGDN, ENDI,\
				XXXX, XXXX, XXXX, XXXX, CALC, XXXX, XXXX, XXXX, MUTE, VOLD, VOLU, XXXX, ARUP, DEAD,\
				XXXX, XXXX, XXXX, 					PLPS,			  		XXXX, ARLF, ARDN, ARRT),

[ spac ] = LAYOUT_all( // The space controls (by pressing space)
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
			    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, DEAD,\
				XXXX, XXXX, XXXX, 					XXXX,			        XXXX, XXXX, XXXX, XXXX),

[ supr ] = LAYOUT_all( // Additional layer for later use.
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
			    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,\
				XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, DEAD,\
				XXXX, XXXX, XXXX, 					XXXX,			  		XXXX, XXXX, XXXX, XXXX),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) { // MACRODOWN only works in this function
    switch(id) {
        case 0: //MAC0 - Hold for lshift and { on tap
					if (record->event.pressed) {
						key_timer = timer_read();
						return MACRO(D(LSFT), END );
					} else {
						return checktime() ? MACRO(U(LSFT),D(RALT),T(7),U(RALT),END): MACRO(U(LSFT),END);
					}; break;
			  case 1:	//MAC1 - Hold for rshift and } on tap
					if (record->event.pressed) {
						key_timer = timer_read();
						return MACRO(D(RSFT), END );
					} else {
						return checktime()  ? MACRO(U(RSFT),D(RALT),T(0),U(RALT),END): MACRO(U(RSFT),END);
					}; break;
        case 2: //MAC2 - Hold for lctrl and [ on tap
						if (record->event.pressed) {
							key_timer = timer_read();
							return MACRO(D(LCTL), END );
						} else {return checktime() ? MACRO(U(LCTL),D(RALT),T(8),U(RALT),END):MACRO(U(LCTL),END);
						}; break;
       	case 3: //MAC3 - Hold for rctrl and ] on tap
						if (record->event.pressed) {
							key_timer = timer_read();
							return MACRO(D(RCTL), END );
						} else {
							return checktime() ? MACRO(U(RCTL),D(RALT),T(9),U(RALT),END):MACRO(U(RCTL),END);
						}; break;
      	case 4: //MAC4 reserved for later.
						if (record->event.pressed) { } else { }; break;
       	case 5: //MAC5 reserved for later.
						if (record->event.pressed) { } else { }; break;
       	case 6: //MAC6 reserved for later.
						if (record->event.pressed) { } else { }; break;
    } return MACRO_NONE;
};
/*
		Later use:
		void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) { }
		enum function_id { };
		const uint16_t PROGMEM fn_actions[] = { };

*/
