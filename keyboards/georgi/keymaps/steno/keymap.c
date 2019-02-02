/* Good on you for modifying your layout! if you don't have 
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "keymap_steno.h"

#define IGNORE_MOD_TAP_INTERRUPT
#define BASE   0 // default layer

//STKPWHRAO*EUFRPBLGTSDZ
// Keep a textual relation of chords. Max 32 keys
#define STN(n) (1L<<n)
enum ORDER { 
		FN = 0, PWR, ST1, ST2, ST3, ST4, NUM,
		LSU, LSD, LT, LK, LP, LW, LH, LR, LA, LO, 
		RE, RU, RF, RR, RP, RB, RL, RG, RT, RS, RD, RZ
};
enum MODE { STENO = 0, QWERTY, COMMAND };

// Bitfield representing the current chord
uint32_t cChord = 0;

// Current 'layer'
enum MODE cMode = STENO;
void processQwerty(void);
void processSymbol(void);

// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Steno layer
 * FN1: 		Qwerty Toggle (processQwerty)
 * PWR:		 	Symbol Momentary (Combo with press, processSymbol)
 * FN1+PWR:		Command Mode
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        | FN1  |   S  |   T  |   P  |   H  |  *   |           |  *   |   F  |   P  |   L  |   T  |   D  |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        | PWR  |   S  |   K  |   W  |   R  |  *   |           |  *   |   R  |   G  |   B  |   S  |   Z  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-----.
 *                    |          |   |   #   |                                 |      |   |     |
 *                    '----------'   '-------'                                 `------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        |       |                      |       |
 *                                 ,------|-------|                      |-------|------.
 *                                 |      |       |                      |       |      |
 *                                 |  A   |  O    |                      |  E    |  U   |
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
[BASE] = LAYOUT_GERGO(  
KC_NO,KC_NO,   KC_NO,KC_NO,KC_NO,KC_NO,                         KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, 
KC_NO,STN_FN,  STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,       STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR, KC_NO, 
KC_NO,STN_PWR, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,       STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR, KC_NO,
                                      
			                             KC_NO, STN_N1,       STN_N1, KC_NO,
                                                 KC_NO,       KC_NO,
                                		  STN_A, STN_O,       STN_E, STN_U)
};

//Instead of the usual QMK shenanigans, because the chording is ass
//we operate once the chord has been sent and work from there
//This is very UnQMK!
void processQwerty(void) {
	// QWERTY Keymap
	switch (cChord){
		case STN(LSU): 						register_code(KC_Q); break;
		case STN(LSU) | STN(LSD): 			register_code(KC_A); break;
		case STN(LSD): 						register_code(KC_Z); break;

		case STN(LT): 						register_code(KC_W); break;
		case STN(LT) | STN(LK): 			register_code(KC_S); break;
		case STN(LK): 						register_code(KC_X); break;

		case STN(LP): 						register_code(KC_E); break;
		case STN(LP) | STN(LW): 			register_code(KC_D); break;
		case STN(LW): 						register_code(KC_C); break;

		case STN(LH): 						register_code(KC_R); break;
		case STN(LH) | STN(LR): 			register_code(KC_F); break;
		case STN(LR): 						register_code(KC_V); break;

		case STN(ST1): 						register_code(KC_T); break;
		case STN(ST1) | STN(ST2): 			register_code(KC_G); break;
		case STN(ST2): 						register_code(KC_B); break;

		case STN(ST3): 						register_code(KC_Y); break;
		case STN(ST3) | STN(ST4): 			register_code(KC_H); break;
		case STN(ST4): 						register_code(KC_N); break;

		case STN(RF): 						register_code(KC_U); break;
		case STN(RF) | STN(RR): 			register_code(KC_J); break;
		case STN(RR): 						register_code(KC_M); break;

		case STN(RP): 						register_code(KC_I); break;
		case STN(RP) | STN(RB): 			register_code(KC_K); break;
		case STN(RB): 						register_code(KC_COMM); break;

		case STN(RL): 						register_code(KC_O); break;
		case STN(RG) | STN(RL): 			register_code(KC_L); break;
		case STN(RG): 						register_code(KC_DOT); break;

		case STN(RT): 						register_code(KC_P); break;
		case STN(RT) | STN(RS): 			register_code(KC_SCLN); break;
		case STN(RS): 						register_code(KC_SLSH); break;

		case STN(RD): 						register_code(KC_L); break;
		case STN(RD) | STN(RZ): 			register_code(KC_ENT); break;
		case STN(RZ): 						register_code(KC_LSFT); break;
	}

	clear_keyboard();
}

void processSymbol(void) {
	// Remove trigger
	cChord ^= STN(PWR);

	switch (cChord){
		case STN(LSU): 						register_code(KC_LSFT); register_code(KC_1); break; // !
		case STN(LSU) | STN(LSD): 			register_code(KC_LSFT); register_code(KC_3); break; // #
		case STN(LSD): 						register_code(KC_LSFT); register_code(KC_5); break; // %

		case STN(LT): 						register_code(KC_LSFT); register_code(KC_2); break; // @
		case STN(LT) | STN(LK): 			register_code(KC_LSFT); register_code(KC_4); break; // $
		case STN(LK): 						register_code(KC_LSFT); register_code(KC_6); break; // ^

		case STN(LP): 						register_code(KC_LSFT); register_code(KC_LBRC); break; // {
		case STN(LP) | STN(LW): 			register_code(KC_LSFT); register_code(KC_9); break; // (
		case STN(LW): 						register_code(KC_LBRC); break;

		case STN(LH): 						register_code(KC_LSFT); register_code(KC_RBRC); break; // }
		case STN(LH) | STN(LR): 			register_code(KC_LSFT); register_code(KC_0); break; // )
		case STN(LR): 						register_code(KC_RBRC); break;

		case STN(ST1): 						register_code(KC_LSFT); register_code(KC_BSLS); break; // |
		case STN(ST1) | STN(ST2): 			register_code(KC_GRV); break;
		case STN(ST2): 						register_code(KC_LSFT); register_code(KC_GRV); break; // ~

		case STN(ST3): 						register_code(KC_QUOT); break;
		//case STN(ST3) | STN(ST4): 			register_code(KC_H); break;
		case STN(ST4): 						register_code(KC_MINS); break;

		case STN(RF): 						register_code(KC_KP_PLUS); break;
		//case STN(RF) | STN(RR): 			register_code(); break;
		case STN(RR): 						register_code(KC_LSFT); register_code(KC_7); break; // &

		case STN(RP): 						register_code(KC_MINS); break;
		//case STN(RP) | STN(RB): 			register_code(KC_K); break;
		case STN(RB): 						register_code(KC_EQL); break;

		case STN(RL): 						register_code(KC_SLSH); break;
		//case STN(RG) | STN(RL): 			register_code(KC_L); break;
		case STN(RG): 						register_code(KC_COMM); break;

		case STN(RT): 						register_code(KC_PAST); break;
		//case STN(RT) | STN(RS): 			register_code(KC_SCLN); break;
		case STN(RS): 						register_code(KC_DOT); break;

		case STN(RD): 						register_code(KC_TAB); break;
		case STN(RD) | STN(RZ): 			register_code(KC_ESC); break;
		case STN(RZ): 						register_code(KC_LSFT); break;

		case STN(LA): 						register_code(KC_SCLN); break;
		case STN(LA) | STN(LO): 			register_code(KC_ENT); break;
		case STN(LO): 						register_code(KC_SLSH); break;

		case STN(RE): 						register_code(KC_SCLN); break;
		case STN(RE) | STN(RU): 			register_code(KC_ENT); break;
		case STN(RU): 						register_code(KC_SLSH); break;
	}

	clear_keyboard();
}

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { 
	// Lone FN press, toggle QWERTY
	if (cChord == STN(FN)) {
		uprintf("Switching to QWER\n");
		(cMode == STENO) ? (cMode = QWERTY) : (cMode = STENO);
		cChord = 0;
		return false;
	}

	// Check for Symbol combo
	if ((cChord & STN(PWR)) && !(cChord & STN(FN))) {
		processSymbol();
		cChord = 0;
		return false; 
	}

	// TODO: Do command mode
	if (cMode == QWERTY) {
		processQwerty();
		cChord = 0;
		return false;
	}

	// Hey that's a steno chord!
	cChord = 0;
	return true; 
}

// Update the current chord
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { 
	// Yes this is fucking gross
	// I'm fully aware
	// Thank you.
	bool pr = record->event.pressed;

	// Bail on keyup, TODO: Find a way to keep this together
	if (pr == false) return true;

	// Switch on the press adding to chord
	switch (keycode) {
			// Mods and stuff
			case STN_ST1:			pr ? (cChord |= STN(ST1)): (cChord &= ~STN(ST1)); break;
			case STN_ST2:			pr ? (cChord |= STN(ST2)): (cChord &= ~STN(ST2)); break;
			case STN_ST3:			pr ? (cChord |= STN(ST3)): (cChord &= ~STN(ST3)); break;
			case STN_ST4:			pr ? (cChord |= STN(ST4)): (cChord &= ~STN(ST4)); break;
			case STN_PWR:			pr ? (cChord |= STN(PWR)): (cChord &= ~STN(PWR)); break;
			case STN_N1...STN_N6: 
			case STN_N7...STN_NC: 	pr ? (cChord |= STN(NUM)): (cChord &= ~STN(NUM)); break;
			case STN_FN:			pr ? (cChord |= STN(FN)) : (cChord &= ~STN(FN)); break;

			// All the letter keys
			case STN_S1: 			pr ? (cChord |= STN(LSU)) : (cChord &= ~STN(LSU));  break;
			case STN_S2: 			pr ? (cChord |= STN(LSD)) : (cChord &= ~STN(LSD));  break;
			case STN_TL: 			pr ? (cChord |= STN(LT)) : (cChord &= ~STN(LT)); break;
			case STN_KL:			pr ? (cChord |= STN(LK)) : (cChord &= ~STN(LK)); break;
			case STN_PL:			pr ? (cChord |= STN(LP)) : (cChord &= ~STN(LP)); break;
			case STN_WL:			pr ? (cChord |= STN(LW)) : (cChord &= ~STN(LW)); break;
			case STN_HL:			pr ? (cChord |= STN(LH)) : (cChord &= ~STN(LH)); break;
			case STN_RL:			pr ? (cChord |= STN(LR)) : (cChord &= ~STN(LR)); break;
			case STN_A:				pr ? (cChord |= STN(LA)) : (cChord &= ~STN(LA)); break;
			case STN_O:				pr ? (cChord |= STN(LO)) : (cChord &= ~STN(LO)); break;
			case STN_E:				pr ? (cChord |= STN(RE)) : (cChord &= ~STN(RE)); break;
			case STN_U:				pr ? (cChord |= STN(RU)) : (cChord &= ~STN(RU)); break;
			case STN_FR:			pr ? (cChord |= STN(RF)) : (cChord &= ~STN(RF)); break;
			case STN_RR:			pr ? (cChord |= STN(RR)) : (cChord &= ~STN(RR)); break;
			case STN_PR:			pr ? (cChord |= STN(RP)) : (cChord &= ~STN(RP)); break;
			case STN_BR:			pr ? (cChord |= STN(RB)) : (cChord &= ~STN(RB)); break;
			case STN_LR:			pr ? (cChord |= STN(RL)) : (cChord &= ~STN(RL)); break;
			case STN_GR: 			pr ? (cChord |= STN(RG)) : (cChord &= ~STN(RG)); break;
			case STN_TR:			pr ? (cChord |= STN(RT)) : (cChord &= ~STN(RT)); break;
			case STN_SR:			pr ? (cChord |= STN(RS)) : (cChord &= ~STN(RS)); break;
			case STN_DR:			pr ? (cChord |= STN(RD)) : (cChord &= ~STN(RD)); break;
			case STN_ZR:			pr ? (cChord |= STN(RZ)) : (cChord &= ~STN(RZ)); break;
	}
	return true; 
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | L1/ESC |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |   D  |   F  |   G  | RMB  |           |      |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | LMB  |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-----.
 *                    | Super/Del|   |Ent/ALT|                                 | Tab  |   |BKSP |
 *                    '----------'   '-------'                                 `------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        | MMB   |                      | STENO|
 *                                 ,------|-------|                      |-------|------.
 *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
 *                                 | Space| Escape|                      | Mod   |Space |
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
/*[BASE] = LAYOUT_GERGO(  
LT(NUMB, KC_ESC),       KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                       KC_Y,    KC_U, KC_I, KC_O,   KC_P,    KC_PIPE, 
MT(MOD_LCTL, KC_BSPC),  KC_A,  KC_S,   KC_D,   KC_F, KC_G, KC_BTN2,       KC_TRNS,  KC_H,    KC_J, KC_K, KC_L,   KC_SCLN, KC_QUOT, 
KC_RSFT,                KC_Z,  KC_X,   KC_C,   KC_V, KC_B, KC_BTN1,       KC_BSPC,  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
                                      
			              MT(MOD_LGUI, KC_DEL), MT(MOD_LALT, KC_ENT),       KC_TAB, KC_BSPC,

                                                           KC_BTN3,       TG(STENO),
                                LT(SYMB, KC_SPC), LT(NUMB, KC_ESC),       LT(SYMB, KC_ENT), LT(NUMB, KC_SPC)),*/
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                         |      |      |      |      |      |  \ |   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |      |           |      |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   | DEL |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | STENO |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |   ;  |   =   |                     |   =   |   ;  |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
/*[SYMB] = LAYOUT_GERGO(  
KC_TRNS, KC_EXLM, KC_AT,  KC_LCBR,KC_RCBR, KC_PIPE,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, 
KC_TRNS, KC_HASH, KC_DLR, KC_LPRN,KC_RPRN, KC_GRV,  KC_TRNS,       KC_TRNS,  KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT, 
KC_TRNS, KC_PERC, KC_CIRC,KC_LBRC,KC_RBRC, KC_TILD, KC_TRNS,       KC_TRNS,  KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, 

                                                  KC_TRNS, KC_TRNS,       KC_TRNS, KC_DEL,
                                                           KC_TRNS,       TG(QSTENO),
                                             	  KC_SCLN, KC_EQL,        KC_EQL, KC_SCLN),*/
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   | BTN1 |           |      | LEFT | DOWN |  UP  | RIGHT|VolDn | VolUp  |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  | BTN2 |           |      | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | PgUp  |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
/*[NUMB] = LAYOUT_GERGO(  
KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS, 
KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD, KC_VOLU, 
KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_TRNS,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT, 

                                                  KC_TRNS, KC_TRNS,       KC_PGUP, KC_TRNS,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS),*/
/* Keymap 4: QWERTY Steno layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |                         |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |  [     |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |      |           |      |   H  |   J  |   K  |   L  |   ;  |  '     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-----.
 *                    |          |   |       |                                 |      |   |     |
 *                    '----------'   '-------'                                 `------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        |       |                      | STENO |
 *                                 ,------|-------|                      |-------|------.
 *                                 |      |       |                      |       |      |
 *                                 |      |       |                      |       |      |
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
/*[QSTENO] = LAYOUT_GERGO(  
KC_TRNS,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,                                 KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_TRNS, 
KC_TRNS,  KC_TRNS, KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                 KC_Y,     KC_U, KC_I, KC_O, KC_P,    KC_LBRC, KC_TRNS, 
KC_TRNS,  KC_TRNS, KC_A,  KC_S,   KC_D,   KC_F, KC_G,                 KC_BSPC,  KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_TRNS,
                                      
			                            KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
                                                 KC_TRNS,       TG(QSTENO),
                                		      KC_C, KC_V,       KC_N, KC_M),*/

/* Keymap template 
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[SYMB] = LAYOUT_GERGO(  
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, 

                                                  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS),
 */
