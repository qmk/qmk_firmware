#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_swedish.h"
//#include "keymap_nordic.h"
//#include "keymap_norwegian.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // mouse keys
#define DEVL 3 // dev keys

#define MACRO_PUBLIC 10
#define MACRO_PRIVATE 11
#define MACRO_PROT 12

#define MACRO_SHARED 13
#define MACRO_CONST 14
#define MACRO_DIM 15
#define MACRO_STRING 16
#define MACRO_INT 17
#define MACRO_DEC 18
#define MACRO_BOOL 19

#define MACRO_RETURN 20
#define MACRO_NOTHING 21
#define MACRO_TODO 22

#define MACRO_SAVE 24
#define MACRO_BUILD 25
#define MACRO_DEBUG 26



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   L3   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   -  |   ,  |   .  |   P  |   Y  |  LT1 |           |  LT1 |   F  |   G  |   C  |   R  |   L  |   Å    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | WIN    |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |   Ä    |
 * |--------+------+------+------+------+------|  LT2 |           |  LT2 |------+------+------+------+------+--------|
 * | LShift |   Ö  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |Z/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |  L1  |Alt   | Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | AltShf|Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        MO(DEVL),       KC_1,           KC_2,    KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_DEL,         SE_MINS,        KC_COMM, KC_DOT, KC_P,   KC_Y,   TG(SYMB),
        KC_LGUI,        KC_A,           KC_O,    KC_E,   KC_U,   KC_I,
        KC_LSFT,        CTL_T(KC_SCLN), KC_Q,    KC_J,   KC_K,   KC_X,   TG(MDIA),
        CTL_T(KC_NO),   MO(SYMB),       KC_LALT,  KC_LEFT,KC_RGHT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_BSLASH,
             TG(1),       KC_F,   KC_G,   KC_C,   KC_R,   KC_L,             SE_AM,
                          KC_D,   KC_H,   KC_T,   KC_N,   KC_S,             SE_AE,
             TG(MDIA),KC_B,   KC_M,   KC_W,   KC_V,   CTL_T(KC_Z),      KC_RSFT,
                                  KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,          TT(SYMB),
             LALT(KC_LSFT),        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   @  |   {  |   }  |   [  |   ]  |      |           |      |   <  |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   (  |   )  |   \  |   /  |------|           |------|   >  |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ~  | UND  | CUT  | COP  | PAS  |      |           |      |   ?  |   1  |   2  |   3  |   %  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   .  |   0  |   =  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       M(0),      KC_F1,   KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_TRNS,
       KC_TRNS,   SE_AT,   ALGR(KC_7),  ALGR(KC_0),  SE_LBRC,   SE_RBRC,  KC_TRNS,
       KC_TRNS,   KC_HASH, SE_LPRN,  SE_RPRN,  ALGR(KC_MINS), SE_SLSH,
       KC_TRNS,   SE_TILD, LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C),    LCTL(KC_V),  KC_TRNS,
       KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, SE_LESS,   KC_7,   KC_8,    KC_9,    KC_KP_ASTERISK, KC_F12,
                LSFT(SE_LESS), KC_4,   KC_5,    KC_6,    KC_KP_PLUS, KC_TRNS,
       KC_TRNS, SE_QUES, KC_1,   KC_2,    KC_3,    LSFT(KC_5), KC_TRNS,
                         KC_DOT,KC_0,  LSFT(KC_0),    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
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
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Developer keys in vb.net
 * shortened in layout beneth, for example int-> integer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Save |Build |Debug |PrtScr|  $   |      |           |      | bool | int  |string| dec  | Todo |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ´  |  '   |   |  |      |  £   |------|           |------| priv | publ |shared| prot |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |  £   |      |           |      | const| dim  |return|nothin|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[DEVL] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, M(MACRO_SAVE), M(MACRO_BUILD), M(MACRO_DEBUG), KC_PSCR, ALGR(KC_4), KC_TRNS,
       KC_TRNS, SE_ACUT, SE_APOS, SE_PIPE, KC_TRNS, ALGR(KC_3),
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ALGR(KC_5), KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  M(MACRO_BOOL), M(MACRO_INT), M(MACRO_STRING), M(MACRO_DEC), M(MACRO_TODO), KC_TRNS,
                 M(MACRO_PRIVATE), M(MACRO_PUBLIC), M(MACRO_SHARED), M(MACRO_PROT), KC_TRNS, KC_TRNS,
       KC_TRNS,  M(MACRO_CONST), M(MACRO_DIM), M(MACRO_RETURN), M(MACRO_NOTHING), KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            break;
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
        case MACRO_PROT:
			if (record->event.pressed) {
				return MACRO( T(P), T(R), T(O), T(T), T(E), T(C), T(T), T(E), T(D), T(SPACE),END);
			}
			break;
		case MACRO_SHARED:
			if (record->event.pressed) {
				return MACRO( T(S), T(H), T(A), T(R), T(E), T(D), T(SPACE), END);
			}
			break;
		case MACRO_CONST:
			if (record->event.pressed) {
				return MACRO( T(C), T(O), T(N), T(S), T(T), T(SPACE), END);
			}
			break;
		case MACRO_DIM:
			if (record->event.pressed) {
				return MACRO( T(D), T(I), T(M), T(SPACE), END);
			}
			break;
		case MACRO_STRING:
			if (record->event.pressed) {
				return MACRO( T(S), T(T), T(R), T(I), T(N), T(G), T(SPACE), END);
			}
			break;
		case MACRO_BOOL:
			if (record->event.pressed) {
				return MACRO( T(B), T(O), T(O), T(L), T(E), T(A), T(N), T(SPACE), END);
			}
			break;
		case MACRO_INT:
			if (record->event.pressed) {
				return MACRO( T(I), T(N), T(T), T(SPACE), END);
			}
			break;
		case MACRO_DEC:
			if (record->event.pressed) {
				return MACRO( T(D), T(E), T(C), T(I), T(M), T(A), T(L), T(SPACE), END);
			}
			break;
		case MACRO_RETURN:
			if (record->event.pressed) {
				return MACRO( T(R), T(E), T(T), T(U),T(R),T(N), T(SPACE), END);
			}
			break;
		case MACRO_NOTHING:
			if (record->event.pressed) {
				return MACRO( T(N), T(O), T(T), T(H), T(I), T(N), T(G), T(SPACE), END);
			}
		case MACRO_TODO:
			if (record->event.pressed) {
				return MACRO( KC_BSLASH, D(LSHIFT) ,T(T), T(O), T(D), T(O), KC_DOT, U(LSHIFT),  T(SPACE),END);
			}
			break;
        case MACRO_SAVE:
			if (record->event.pressed) {
				return MACRO( D(LCTL) ,T(S), U(LCTL),END);
			}
			break;
        case MACRO_BUILD:
			if (record->event.pressed) {
				return MACRO(  D(LCTL), D(LSHIFT) ,T(B), U(LSHIFT), U(LCTL),END);
			}
			break;
        case MACRO_DEBUG:
			if (record->event.pressed) {
				return MACRO( KC_F5 ,END);
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
