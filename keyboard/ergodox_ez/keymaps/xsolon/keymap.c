#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define VSFN 3 // Visual Studio + FNs

#define MACRO_PUBLIC 10
#define MACRO_PRIVATE 11

#define MACRO_STATIC 12
#define MACRO_CONST 13

#define MACRO_VOID 14
#define MACRO_VAR 15
#define MACRO_STRING 16

#define MACRO_INT 17
#define MACRO_FLOAT 18
#define MACRO_BOOL 19

#define MACRO_RETURN 20
#define MACRO_NULL 21
#define MACRO_BREAK 22

#define MACRO_TODO 23
#define MACRO_NEW 24
#define MACRO_PARENTHESE 25

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  | Cut  |           |   6  |   7  |   8  |   9  |   0  |   -  | BackS  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | Paste|           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab/L2 | A    | S    |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L3|' / Cmd |
 * |--------+------+------+------+------+------| Copy |           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl  | Win  |Alt	  | L1   | Alt  |                                       |  Alt | Left |Down  | Up   | Right  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Esc  | Del  |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|BackS/|------|       |------|  Tab   |Enter/|
 *                                 | /L1  |L2    |End/L3|       | PgDn |        |L1    |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   		KC_3,   KC_4,   KC_5,   LCTL(KC_X),
        KC_TAB,         KC_Q,         KC_W,   		KC_E,   KC_R,   KC_T,   LCTL(KC_V),
        LT(MDIA,KC_TAB),KC_A,	      KC_S,	   	KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,	      KC_X,   		KC_C,   KC_V,   KC_B,   LCTL(KC_C),
        KC_LCTL,	KC_LGUI,      KC_LALT,MO(SYMB),KC_LALT,
                                              KC_ESC,  KC_DELT,
                                                              KC_HOME,
                                              LT(SYMB,KC_SPC),LT(MDIA,KC_BSPC),LT(VSFN,KC_END),
        // right hand
             KC_6,   KC_7,   KC_8,   KC_9,   KC_0,	KC_MINS,	KC_BSPC,
             TG(SYMB),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,   KC_K,   KC_L,   LT(VSFN, KC_SCLN),GUI_T(KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_LALT, KC_LEFT,KC_DOWN,KC_UP, KC_RGHT,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, LT(SYMB,KC_ENT)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   {  |   }  |  [   |   ]  |  |   |      |           |      | P Up | Home | End  |  =   |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | End  | Back | Del  |Enter | Esc  |------|           |------| Left | Down |  Up  |Right |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |Close |   ]  |   ~  |      |           |      | PDown|Menu  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F5   | F10  |       | F11  | F12  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  	KC_F3,  	KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_LCBR,KC_RCBR,	KC_LBRC,	KC_RBRC,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HOME,KC_BSPC,	KC_DELT,	KC_ENT ,KC_ESC,
       KC_TRNS,KC_PERC,KC_CIRC,	LCTL(KC_F4),	KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       					KC_F5, KC_F10,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,			KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_PGUP, KC_HOME,		KC_END,  KC_EQL,    KC_ASTR, KC_F12,
                KC_LEFT, KC_DOWN,KC_UP, KC_RGHT, KC_PLUS, KC_TRNS,
       KC_TRNS, KC_PGDN, LSFT(KC_F10),  KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,KC_0,    KC_EQL,  KC_TRNS,
       KC_F11, KC_F12,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght| Rclk |------|           |------|MsLeft|MsDown| MsUp |MsRght|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Brwser|Brwser|
 *                                 |Lclk  |      |------|       |------|Fwd   |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_WFWD, KC_WBAK
),

/* Keymap 3:  Visual Studio Layer
*
* ,--------------------------------------------------.           ,--------------------------------------------------.
* |        |  F1  |  F2  |  F3  |  Kill|  F5  |      |           | Calc |Build |  F7  | Build|SeeDef|  F10 |   F11  |
* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
* |        |Public|Static|string|int   |return|      |           |      |//TODO|      |      |      |      |   F12  |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |        |Privat|Const |var   |float |null  |------|           |------|new   |      |      |      |      |        |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |        |      |      |void  |bool  |break;|      |           |      |();   |      |      |      |      |        |
* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
*   |      | Alt  |      |      |      |                                       |      |      |      |      |      |
*   `----------------------------------'                                       `----------------------------------'
*                                        ,-------------.       ,-------------.
*                                        |      | Cut  |       |      |      |
*                                 ,------|------|------|       |------+------+------.
*                                 |      |      |      |       |      |      |      |
*                                 |      |      |------|       |------|      |      |
*                                 |      |      |      |       |      |      |      |
*                                 `--------------------'       `--------------------'
*/
// VS + FKEYS + MACROS
[VSFN] = KEYMAP(
	// left hand
	KC_TRNS, KC_F1, KC_F2, KC_F3, LALT(KC_F4), KC_F5, KC_TRNS,
	KC_TRNS, M(MACRO_PUBLIC), M(MACRO_STATIC), M(MACRO_STRING), M(MACRO_INT), M(MACRO_RETURN), KC_TRNS,
	KC_TRNS, M(MACRO_PRIVATE), M(MACRO_CONST), M(MACRO_VAR), M(MACRO_FLOAT), M(MACRO_NULL),
	KC_TRNS, KC_TRNS, KC_TRNS, M(MACRO_VOID), M(MACRO_BOOL), M(MACRO_BREAK), KC_TRNS,
	KC_TRNS, KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	// right hand
	KC_CALCULATOR, LSFT(KC_F6), KC_F7, LSFT(KC_F6), KC_F12, KC_F10, KC_F11,
	KC_TRNS, M(MACRO_TODO), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
	M(MACRO_NEW), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, M(MACRO_PARENTHESE), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
	),


};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
		case MACRO_PUBLIC:
			if (record->event.pressed) {
				return MACRO( T(P), T(U), T(B), T(L), T(I), T(C), T(SPACE),END);
			} 
			break;
		case MACRO_PRIVATE:
			if (record->event.pressed) {
				return MACRO( T(P), T(R), T(I), T(V), T(A), T(T), T(E), T(SPACE),END);
			} 
			break;
		case MACRO_STATIC:
			if (record->event.pressed) {
				return MACRO( T(S), T(T), T(A), T(T), T(I), T(C), T(SPACE), END);
			} 
			break;
		case MACRO_CONST:
			if (record->event.pressed) {
				return MACRO( T(C), T(O), T(N), T(S), T(T), T(SPACE), END);
			} 
			break;
		case MACRO_VOID:
			if (record->event.pressed) {
				return MACRO( T(V), T(O), T(I), T(D), T(SPACE), END);
			} 
		break;
		case MACRO_VAR:
			if (record->event.pressed) {
				return MACRO( T(V), T(A), T(R), T(SPACE), END);
			} 
			break;
		case MACRO_STRING:
			if (record->event.pressed) {
				return MACRO( T(S), T(T), T(R), T(I), T(N), T(G), T(SPACE), END);
			} 
			break;		
		case MACRO_BOOL:
			if (record->event.pressed) {
				return MACRO( T(B), T(O), T(O), T(L), T(SPACE), END);
			} 
			break;		
		case MACRO_INT:
			if (record->event.pressed) {
				return MACRO( T(I), T(N), T(T), T(SPACE), END);
			} 
			break;
		case MACRO_FLOAT:
			if (record->event.pressed) {
				return MACRO( T(F), T(L), T(O), T(A),T(T),T(SPACE), END);
			} 
			break;
		case MACRO_RETURN:
			if (record->event.pressed) {
				return MACRO( T(R), T(E), T(T), T(U),T(R),T(N), END);
			} 
			break;
		case MACRO_NULL:
			if (record->event.pressed) {
				return MACRO( T(N), T(U), T(L), T(L), END);
			} 
		case MACRO_BREAK:
			if (record->event.pressed) {
				return MACRO( T(B), T(R), T(E), T(A), T(K), T(SCOLON), END);
			} 
			break;
		case MACRO_TODO:
			if (record->event.pressed) {
				return MACRO( T(SLASH), T(SLASH), D(LSHIFT) ,T(T), T(O), T(D), T(O),U(LSHIFT), T(SPACE),END);
			} 
			break;
		case MACRO_NEW:
			if (record->event.pressed) {
				return MACRO( T(N), T(E), T(W), T(SPACE), END);
			} 
			break;
		case MACRO_PARENTHESE:
			if (record->event.pressed) {
				return MACRO(  D(LSHIFT),T(LPRN), T(RPRN),U(LSHIFT), T(SCOLON), END);
			} 
			break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
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
            // none
            break;
    }

};
