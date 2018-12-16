#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define FKEYS 1 // F keys + macros

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
 * |   (    |   1  |   2  |   3  |   4  |   5  |  "   |           | Save |   6  |   7  |   8  |   9  |   0  |   [    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   )    |   Q  |   W  |   E  |   R  |   T  |Bkspa |           | Del  |   Y  |   U  |   I  |   O  |   P  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   {    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   _  |   Redo |
 * |--------+------+------+------+------+------|   /  |           |  ;   |------+------+------+------+------+--------|
 * |   }    |Z~Alt |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   '  |   !  |   ?  |   Undo |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Tab~CL|  <   |  >   |   |  |  &   |                                       |   =  |   +  |   -  |   *  |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |. ~L1 | ,    |       |Home  |End~L1|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Copy |       | UP   |      |      |
 *                                 | Enter| Space|------|       |------| Space|Enter |
 *                                 | ~WIN | ~LSFT| Past |       | DOWN | ~LSFT| ~WIN |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_LPRN,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   LSFT(KC_QUOTE),
        KC_RPRN,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_BSPACE,
        KC_LCBR,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_RCBR,        ALT_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_SLASH,
        CTL_T(KC_TAB), LSFT(KC_COMMA),LSFT(KC_DOT),KC_PIPE,KC_AMPR, 
                                              LT(1,KC_DOT),  KC_COMM,
                                                              LCTL(KC_C),
                                               GUI_T(KC_ENTER),SFT_T(KC_SPACE),LCTL(KC_V),
        // right hand
             LCTL(KC_S)  ,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_LBRACKET,
             KC_DELETE,       KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_RBRACKET,
                          KC_H,   KC_J,   KC_K,   KC_L,   KC_UNDS,LCTL(KC_Y),
             KC_SCOLON,KC_N,   KC_M, KC_QUOTE  ,KC_EXLM , LSFT(KC_SLASH),   LCTL(KC_Z),
                                  KC_EQUAL,KC_PLUS  ,  KC_MINUS,KC_ASTR  ,     TG(1),
             KC_HOME,         LT(1,KC_END),
             KC_UP,
             KC_DOWN,SFT_T(KC_SPACE), GUI_T(KC_ENTER)
    ),

/* Keymap 1:  F keys + macros
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |  F1  |  F2  |  F3  |  F4  |  F5  |  `   |           | Calc |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |Public|Static|string|int   |return|      |           |      |//TODO|      |      |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |Privat|Const |var   |float |null  |------|           |------|new   |      |      |      |      |        |
 * |--------+------+------+------+------+------|  \   |           |  ~   |------+------+------+------+------+--------|
 * |        |      |      |void  |bool  |break;|      |           |      |();   |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |  WIN | Alt  |      |      |                                       | PgUp | PgDw | Ins  | PtSc |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | Cut  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Left | Right|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FKEYS + MACROS
[FKEYS] = LAYOUT_ergodox(
       // left hand
       KC_ESCAPE,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_GRAVE,
       KC_TAB,M(MACRO_PUBLIC),M(MACRO_STATIC),  M(MACRO_STRING),M(MACRO_INT),M(MACRO_RETURN),KC_TRNS,
       KC_TRNS,M(MACRO_PRIVATE),M(MACRO_CONST), M(MACRO_VAR),M(MACRO_FLOAT),M(MACRO_NULL),
       KC_TRNS,KC_TRNS,KC_TRNS,M(MACRO_VOID),M(MACRO_BOOL),M(MACRO_BREAK),KC_BSLASH,
       KC_TRNS,KC_LGUI,KC_LALT,KC_TRNS,KC_TRNS,
                                       KC_TRNS,LCTL(KC_X),
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_CALCULATOR, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, M(MACRO_TODO),   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_F12,
                M(MACRO_NEW), KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TILD, M(MACRO_PARENTHESE), KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                         KC_PGUP,KC_PGDOWN,  KC_INSERT,   KC_PSCREEN,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_LEFT, KC_RIGHT
),


};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(FKEYS)                // FN1 - Momentary Layer 1
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
				return MACRO(  D(LSHIFT),T(9), T(0),U(LSHIFT), T(SCOLON), END);
			} 
			break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

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
        default:
            // none
            break;
    }

};
