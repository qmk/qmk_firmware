/*
	Create By:LEdiodes
	Created On:05-07-2018 2:55 PM CST

		Wants;
			Live recording(dynamic Macros)
			Common Ticket Notes added
			more double and triple taps to complete thing

Keymap: 32 Layers
-----------------
stack of layers
       ____________ precedence
      /           / | high
  31 /___________// |
  30 /___________// |
  29 /___________/  |
   :   _:_:_:_:_:__ |
   :  / : : : : : / |
   2 /___________// |
   1 /___________// |
   0 /___________/  V low
*/

#include "dz60.h"
#include "action_layer.h"

enum custom_keycodes {
    FN0 = 0,
    FN1 = 1,
    FN2 = 2,
    FN3 = 3,
    FN4 = 4,
};

// Tap Dance & Layer Declarations
enum {
        TD_KC_ESC_F5 = 0,
        TD_WIN = 0,
        TD_QUOTE = 0,
//      TD_ESC_CAPS = 0,
//      TD_SPC_ENT = 0,
//      TD_KC_LSFT_CAPS = 0,
//      TD_KC_RSFT_CAPS = 0,
//      TD_KC_RIGHT_PLAY = 0,
//      TD_KC_WIN_WIN_E = 0,
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Esc, twice for Caps Lock
  //[TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),

  // Tap once for space, tap twice for enter
  //[TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),

  // Tap once for Left Shift, twice for Caps Lock
  //[TD_KC_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),

  // Tap once for Right Shift, twice for Caps Lock
  //[TD_KC_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),

  // Tap once for change track, twice for play
  //[TD_KC_RIGHT_PLAY]  = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_MPLY),

  // Tap once for windows, twice for windows+E to open explorer
  //[TD_KC_WIN_WIN_E]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_E)),

  // Tap once for Left Ctrl, twice for F5 to refresh webpages and the such
  [TD_KC_ESC_F5]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_F5),

  // Tap once for ', twice for "
  [TD_QUOTE]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, S(KC_QUOT)),

  // Tap once for windows, twice for windows explorer
  [TD_WIN]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_E)),

// Other declarations would go here, separated by commas, if you have them

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [FN0] = KEYMAP(
		// FN0 - All geeks know processing starts with 0 -- default layout
		//,-----------------------------------------------------------------------------------------.
		//| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  Q  |  W  |  E  |  R  |  T |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter    |
		//|-----------------------------------------------------------------------------------------+
		//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |   RShfit   | U |  1 |
		//|-----------------------------------------------------------------------------------------+
		//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  2  |  /  |  L | D |  R |
		//`-----------------------------------------------------------------------------------------'
		TD(TD_KC_ESC_F5), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,
		LT(MO(FN2), KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		LT(MO(FN4), KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSHIFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_NO, KC_RSFT, KC_UP, MO(FN1),
		KC_LCTRL, TD(TD_WIN), KC_LALT, LT(MO(FN4), KC_SPC), LT(MO(FN3), KC_SPC), LT(MO(FN1), KC_SPC), MO(FN2), TG(FN4), KC_LEFT, KC_DOWN, KC_RGHT),

 [FN1] = KEYMAP(
		// FN1 -- Function numbers and macros
		//,-----------------------------------------------------------------------------------------.
		//|  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |gmail| VRT |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  Q  |  W  |  E  |  R  |  T  | DUN |  U  |  I  |  O  |  P  |  [  |  ]  |  RESET |
		//|-----------------------------------------------------------------------------------------+
		//|   1     |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  =  |  -  |     Enter   |
		//|-----------------------------------------------------------------------------------------+
		//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  /  |  [  |  ]  |    \      |Rsft|  1 |
		//|-----------------------------------------------------------------------------------------+
		//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  Fn |  /  |  L | D |  R |
		//`-----------------------------------------------------------------------------------------'
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, M(10), M(9),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(7), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_MINS, TG(FN4),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_SLSH, KC_LBRC, KC_RBRC, KC_TRNS, KC_BSLS, KC_RSFT, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, TD(TD_QUOTE)),

 [FN2] = KEYMAP(
		// FN2 -- Macros and mouse control -- NEEDS UPDATING -- 05-01-2018 7:31 PM CST -- mkerfoot
		//,-----------------------------------------------------------------------------------------.
		//| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
		//|-----------------------------------------------------------------------------------------+
		//| 2[CAPS] |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter   |
		//|-----------------------------------------------------------------------------------------+
		//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |   RShfit   | U |  1 |
		//|-----------------------------------------------------------------------------------------+
		//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  2  | SNIP|  L | D |  R |
		//`-----------------------------------------------------------------------------------------'
		M(8), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(3), M(4),
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(7), KC_TRNS, KC_UP, KC_TRNS, M(13), M(17), KC_TRNS, DF(FN0),
		KC_CAPS, M(5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, M(16), KC_TRNS, DF(FN0),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, M(15), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,  KC_TRNS, M(8), M(2), M(1), KC_TRNS, M(6), M(12), KC_TRNS, TD(TD_QUOTE)),

 [FN3] = KEYMAP(
		// FN3 -- LEdiodes! -- NEEDS UPDATING -- 05-01-2018 7:31 PM CST -- mkerfoot
		//,-----------------------------------------------------------------------------------------.
		//| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
		//|-----------------------------------------------------------------------------------------+
		//| 2[CAPS] |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter   |
		//|-----------------------------------------------------------------------------------------+
		//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |   RShfit   | U |  1 |
		//|-----------------------------------------------------------------------------------------+
		//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  2  |  /  |  L | D |  R |
		//`-----------------------------------------------------------------------------------------'
		RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI, RGB_SAI,
		RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, RGB_SAD),

 [FN4] = KEYMAP(
		// FN4 -- mouse control like a boss
		//,-----------------------------------------------------------------------------------------.
		//| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
		//|-----------------------------------------------------------------------------------------+
		//| 2[Tab] |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
		//|-----------------------------------------------------------------------------------------+
		//| 2[CAPS] |  za  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter   |
		//|-----------------------------------------------------------------------------------------+
		//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |   RShfit   | U |  1 |
		//|-----------------------------------------------------------------------------------------+
		//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  2  |  /  |  L | D |  R |
		//`-----------------------------------------------------------------------------------------'
		KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(FN0),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2,
		DF(FN0), KC_TRNS, M(11), KC_MS_WH_LEFT, DF(FN0), M(12), MO(FN2), KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R),

};

/*
					KEYMAP(
						// TEMPLATE -- DO NOT EDIT!!!
						//,-----------------------------------------------------------------------------------------.
						//| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |Bkspc| Del |
						//|-----------------------------------------------------------------------------------------+
						//| 2[Tab] |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
						//|-----------------------------------------------------------------------------------------+
						//| 2[CAPS] |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter   |
						//|-----------------------------------------------------------------------------------------+
						//| Shift       |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |   RShfit   | U |  1 |
						//|-----------------------------------------------------------------------------------------+
						//| Ctrl |  Win  |  Alt  |   2[Space]   |  3[Space]  |  2[Space]  |  2  |  /  |  L | D |  R |
						//`-----------------------------------------------------------------------------------------'

						// TEMPLATE -- DO NOT EDIT!!!
						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
						// TEMPLATE -- DO NOT EDIT!!!
*/

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

	switch (id) {
		case 1:
			if (record->event.pressed) {
				SEND_STRING("");
			}
			break;
		case 2:
			if (record->event.pressed) {
				SEND_STRING("");
				}
			break;
		case 3:
			if (record->event.pressed) {
				SEND_STRING("");
			}
			break;
		case 4:
			if (record->event.pressed) {
				SEND_STRING("");
			}
			break;
		case 5:
			if (record->event.pressed) {
				SEND_STRING("");
				}
			break;
		case 6:
			if (record->event.pressed) {
				// screenshot with OneNote
				return MACRO( D(LSFT), D(LGUI), T(S), U(LGUI), U(LSFT), END );
			}
			break;
		case 7:
			if (record->event.pressed) {
				SEND_STRING("");
			}
			break;
		case 8:
			if (record->event.pressed) {
				// Ctrl+Alt+Del
				return MACRO( D(LALT), D(LCTL), D(DEL), U(DEL), U(LCTL), U(LALT) );
			}
			break;
		case 9:
			if (record->event.pressed) {
				// Toggle current page between Normal and Hacker Vision
				return MACRO( D(LSHIFT), D(F12), U(LSHIFT), END );
			}
			break;
		case 10:
			if (record->event.pressed) {
				// Pause & Resume Hacker Vision (daytime mode)
				return MACRO( D(LSHIFT), D(F11), U(LSHIFT), END );
			}
			break;
		case 11:
			if (record->event.pressed) {
				// Copy-paste on the same key
				return MACRO( D(LCTL), T(C), U(LCTL), END  );
            } else {
                return MACRO( D(LCTL), T(V), U(LCTL), END );
			}
			break;
		case 12:
			if (record->event.pressed) {
				        // notepad.exe
                return MACRO( D(LGUI), T(R), W(100), U(LGUI), T(N), T(O), T(T), T(E), T(P), T(A), T(D), T(DOT), T(E), T(X), T(E), T(ENT), END );
			}
      break;
		case 13:
			if (record->event.pressed) {
				        // PowerShell.exe
                return MACRO( D(LGUI), T(R), W(100), U(LGUI), D(LSFT), T(P), U(LSFT), T(O), T(W), T(E), T(R), D(LSFT), T(S), U(LSFT), T(H), T(E), T(L), T(L), T(DOT), T(E), T(X), T(E), T(ENT), END );
			}
      break;
		case 14:
			if (record->event.pressed) {
				        // Snippingtool.exe
                return MACRO( D(LGUI), T(R), W(100), U(LGUI), T(S), T(N), T(I), T(P), T(P), T(I), T(N), T(G), T(T), T(O), T(O), T(L), T(DOT), T(E), T(X), T(E), T(ENT), END );
			}
      break;
		case 15:
			if (record->event.pressed) {
                // git add .
                return MACRO( T(G), T(I), T(T), T(SPACE), T(A), T(D), T(D), T(SPACE), T(DOT), T(ENT), END );
			}
      break;
		case 16:
			if (record->event.pressed) {
				        // git commit ""
                return MACRO( T(G), T(I), T(T), T(SPACE), T(C), T(O), T(M), T(M), T(I), T(T), T(SPACE), T(MINUS), T(M), T(SPACE), D(LSFT), T(QUOTE), U(LSFT), D(LSFT), T(QUOTE), U(LSFT), T(LEFT), END );
			}
      break;
		case 17:
			if (record->event.pressed) {
                // git push
                return MACRO( T(G), T(I), T(T), T(SPACE), T(P), T(U), T(S), T(H), T(ENT), END );
			}
      break;
	}
	return MACRO_NONE;
}


uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case FN1:
        // purple -- (0x7A,  0x00, 0xFF);
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case FN2:
        //
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case FN3:
        //
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    case FN4:
        //
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    default: //  Else, default(PowerShell), any other layer not specified
        // White
        rgblight_setrgb (0xFF,  0xFF, 0xFF);
        break;
    }
  return state;
}

void matrix_scan_user(void) {
}
/*
// LED CAPS control
void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2); PORTB &= ~(1 << 2);
    } else {
        DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
    }
}
*/
