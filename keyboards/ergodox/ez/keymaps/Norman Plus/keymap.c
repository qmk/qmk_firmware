#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc+` |   1  |   2  |   3  |   4  |   5  |  6   |           |   7  |   8  |   9  |   0  |  -/_ |  =/+ | LEADER |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   D  |   F  |   K  |  [   |           |   ]  |   J  |   U  |   R  |   L  |   ;  |   \/|  |
 * |--------+------+------+------+------+------|  {   |           |   }  |------+------+------+------+------+--------|
 * |LCtl+Cap|   A  |   S  |   E  |   T  |   G  |------|           |------|   Y  |   N  |   I  |   O  |   H  |   '    |
 * |--------+------+------+------+------+------| Fn1  |           | Fn2  |------+------+------+------+------+--------|
 * |(/LShift|   Z  |   X  |   C  |   V  |   B  |      |           |      |   P  |   M  |   ,  |   .  |   /  |)/RShift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGui | ~F3  | Alt  | Left | Down |                                       |  Up  | Right| ~F1  | ~F3  | RGui |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Copy  |Paste |       |SelAll|UnRedo|
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |CTLALT|       |Delete|      |      |
 *                                 |LShift| Enter|------|       |------|BSpace| Space|
 *                                 |      |      | LCtl |       |  Tab |      |      |
 *                                 `--------------------'       `--------------------'
 */

	[BASE] = KEYMAP(  // layer 0 : default
		// Left hand
		TD(TD_ESC_GRV),		KC_1,    		KC_2,    		KC_3,     		KC_4,     		KC_5,			KC_6,
		KC_TAB,				KC_Q,			KC_W,    		KC_D,			KC_F,			KC_K,			TD(TD_BRACKETS_L),
		TD(TD_CTL_CAPS),	KC_A,    		KC_S,    		KC_E,    		KC_T,    	 	KC_G,
		KC_LSPO,  			KC_Z,    		KC_X,    		KC_C,     		KC_V,			KC_B,			TG(FN1),
		KC_LGUI, 			OSL(FN3),		KC_LALT,		KC_LEFT,		KC_DOWN,
		COPY,				PASTE,
		OSM(MOD_LCTL | MOD_LALT),
		KC_LSFT,   			KC_ENT,  		KC_LCTL,
		// Right hand
		KC_7,    			KC_8,		    KC_9,		    KC_0,		  	KC_MINS,  		KC_EQL, 		KC_LEAD,
		TD(TD_BRACKETS_R),  KC_J, 		  	KC_U,    		KC_R,     		KC_L,     		KC_SCLN, 		KC_BSLS,
							KC_Y,     		KC_N,    		KC_I,   		KC_O,     		KC_H,  	  		KC_QUOT,
		TG(FN2),  			KC_P,    		KC_M,    		KC_COMM,  		KC_DOT,   		KC_SLSH, 		KC_RSPC,
											KC_UP,  		KC_RIGHT,		MO(FN1),		OSL(FN3), 		KC_RGUI,
		SELECT_ALL,  		TD_UNDO_REDO,
		KC_DELETE,
		KC_TAB,  			KC_BSPC, 		KC_SPC
	),

	
/* Keymap 1: mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |WhlUp |WhlDn |      |      |      |           |      |      |      |WhlUp |WhlDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   Trns |MsLeft|MsDown| MsUp |MsRght|      |------|           |------|      |MsLeft|MsDown| MsUp |MsRght|        |
 * |--------+------+------+------+------+------|Trns  |           |  Fn1 |------+------+------+------+------+--------|
 * |   Trns |      |      | MClk |      |      |      |           |      |      |      |      | MClk |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      | Trns |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Trns | Trns |       | Trns | Trns |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | LClk | RClk |------|       |------| RClk | LClk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    [FN1] = KEYMAP( // FN1 Layer
		// Left hand
		KC_NO,				KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,
		KC_NO, 				KC_NO,			KC_WH_D, 		KC_WH_U, 		KC_NO, 			KC_NO, 			KC_NO,
		KC_TRNS, 			KC_MS_L, 		KC_MS_D, 		KC_MS_U, 		KC_MS_R, 		KC_NO,
		KC_TRNS, 			KC_NO, 			KC_NO, 			KC_BTN3, 		KC_NO, 			KC_NO, 			KC_TRNS,
		KC_NO, 				KC_NO, 			KC_NO,  		KC_NO,  		KC_NO,
		KC_TRNS, 			KC_TRNS,
		KC_NO,
		KC_BTN2,   			KC_BTN1, 		KC_NO,
		// Right hand
		KC_NO, 				KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO,
		KC_NO, 				KC_NO, 			KC_NO, 			KC_WH_D, 		KC_WH_U, 		KC_NO, 			KC_NO,
							KC_NO, 			KC_MS_L, 		KC_MS_D, 		KC_MS_U, 		KC_MS_R, 		KC_NO,
		TG(FN1), 			KC_NO, 			KC_NO, 			KC_BTN3, 		KC_NO, 			KC_NO, 			KC_NO,
		KC_NO, 				KC_NO, 			KC_TRNS, 		KC_NO, 			KC_NO,
		KC_TRNS, 			KC_TRNS,
		KC_NO,
		KC_NO, 				KC_BTN1, 		KC_BTN2
	),

/* Keymap 2: Symbol and numpad keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |PScreen |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |  Up  |  7   |  8   |  9   |  *   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |  4   |  5   |  6   |  +   |   -    |
 * |--------+------+------+------+------+------|      |           | Trns |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |  1   |  2   |  3   |  \   |   /    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |  Alt |   <  |   >  |                                       |   .  |  0   |  0   |  =   |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Trns |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    [FN2] = KEYMAP( // FN2 Layer
		// Left hand
		KC_NO,				KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_PSCREEN,
		KC_NO,				KC_EXLM,		KC_AT,  		KC_LCBR,		KC_RCBR,		KC_PIPE,		KC_NO,
    	KC_NO,				KC_HASH,		KC_DLR,			KC_LPRN,		KC_RPRN,		KC_GRV,
    	KC_NO,				KC_PERC,		KC_CIRC,		KC_LBRC,		KC_RBRC,		KC_TILD,		KC_NO,
		KC_NO,				KC_NO,			KC_LALT,		KC_LT,			KC_GT,
		KC_NO,				KC_NO,
		KC_NO,
		KC_NO,				KC_NO, 			KC_NO,
		// Right hand
		KC_NO,   			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,
    	KC_NO,				KC_UP,			KC_7,			KC_8,			KC_9,			KC_ASTR,		KC_NO,
    						KC_DOWN,		KC_4,			KC_5,			KC_6,			KC_PLUS,		KC_MINS,
    	KC_TRNS,			KC_AMPR,		KC_1,			KC_2,			KC_3,			KC_BSLS,		KC_SLSH,
    	KC_DOT,				KC_0,			KC_0,			KC_EQL,			KC_NO,
		KC_NO,				KC_NO,
		KC_NO,
		KC_NO,				KC_TRNS,		KC_NO
	),

/* Keymap 3: Fn momentary layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    `   |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |  F13 |  F14 |  F15 |  F16 |Teensy  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |      |           |      |      |  F17 |  F18 |  F19 |  F20 |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F9  |  F10 |  F11 |  F12 |      |------|           |------|      |  F21 |  F22 |  F23 |  F24 |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | Trns |      |      |      |                                       |      |      |      | Trns |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    [FN3] = KEYMAP( // FN3 Layer
		// Left hand
		KC_GRV,				KC_F1,			KC_F2,			KC_F3,			KC_F4,			KC_NO,			KC_NO,
		KC_NO,				KC_F5,			KC_F6,			KC_F7,			KC_F8,			KC_NO,			KC_NO,
    	KC_NO,				KC_F9,			KC_F10,			KC_F11,			KC_F12,			KC_NO,
    	KC_NO,				KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,
		KC_NO,				KC_TRNS,		KC_NO,			KC_NO,			KC_NO,
		KC_NO,				KC_NO,
		KC_NO,
		KC_NO,				KC_NO,			KC_NO,
		// Right hand
		KC_NO,				KC_NO,			KC_F13,			KC_F14,			KC_F15,			KC_F16,			RESET,
		KC_NO,				KC_NO,			KC_F17,			KC_F18,			KC_F19,			KC_F20,			KC_NO,
							KC_NO,			KC_F21,			KC_F22,			KC_F23,			KC_F24,			KC_NO,
		KC_NO,				KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,
		KC_NO,				KC_NO,			KC_NO,			KC_TRNS,		KC_NO,
		KC_NO,				KC_NO,
		KC_NO,
		KC_NO,				KC_NO,			KC_NO
	),
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTL_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS), //Tap once for Ctl, twice for Caps Lock
  [TD_ESC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV), //Tap once for Esc, twice for grav
  [TD_UNDO_REDO] = ACTION_TAP_DANCE_DOUBLE(UNDO, REDO), // Tap once for Undo, twice for Redo
  [TD_BRACKETS_L] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LABK), // Tap once for square bracket, twice for carrot bracket
  [TD_BRACKETS_R] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RABK) // Tap once for square bracket, twice for carrot bracket
};

void matrix_init_user(void) {

};

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

	ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
    	case 1:
			ergodox_right_led_1_on();
		break;
    	case 2:
			ergodox_right_led_2_on();
		break;
		case 3:
			ergodox_right_led_3_on();
		break;
    	default:
		break;
    }
};