#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_german_osx.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define SMLY 3 // media keys
#define NUMB 4 // number keys
#define EGOS 5 // Egoshooter layer

#define M_CTRL_CMDV 1
#define M_CTRL_CMDC 2
#define M_MEH_SH_ACUT 3
#define M_DE_PLUS_CTRLALT 12
#define M_DE_CIRC_CTRLCMD 13
#define M_TOGGLE_5 14

#define SM_SMILE 4
#define SM_SMIRK 5
#define SM_FROWN 6
#define SM_CRY 7
#define SM_KISS 8
#define SM_HEART 9
#define SM_LAUGH 10
#define SM_SAD 11


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |CMD-V |           |CMD-C |   6  |   7  |   8  |   9  |   0  |   ß    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  | CMD  |           | CMD  |   Z  |   U  |   I  |   O  |   P  |   ü    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LALT  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ö  |  ä/RALT|
 * |--------+------+------+------+------+------| LALT |           | RALT |------+------+------+------+------+--------|
 * | LShift |Y/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |-/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |</L1|  ^°  |AltShf| Left | Right|                                       |  Up  | Down | CMD-SHIFT |  +  | #/L1 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | MDIA | Meh  |       | Hyper|  NUM   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Back-|  Del |------|       |------|  Enter | Space|
 *                                 | Space|      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,                  DE_1,         DE_2,   DE_3,   DE_4,   DE_5,   M(M_CTRL_CMDV),
        KC_TAB,                  DE_Q,         DE_W,   DE_E,   DE_R,   DE_T,   KC_LGUI,
        KC_LALT,                   DE_A,         DE_S,   DE_D,   DE_F,   DE_G,
        KC_LSFT,                 CTL_T(DE_Y),  DE_X,   DE_C,   DE_V,   DE_B,   KC_LALT,
        LT(SYMB,DE_LESS),        M(M_DE_CIRC_CTRLCMD),      M(M_DE_PLUS_CTRLALT), LALT(KC_LSFT),  LGUI(KC_LSFT),
                                               			  	M(M_MEH_SH_ACUT), 	TG(2),
                                                              					KC_HOME,
                                               				KC_BSPC,KC_DEL,		LT(SMLY,KC_END),
        // right hand
             M(M_CTRL_CMDC),  DE_6,   DE_7,   DE_8,   DE_9,   DE_0,     	DE_SS,
             KC_RGUI,     DE_Z,   DE_U,   DE_I,   DE_O,   DE_P,         	DE_UE,
                          DE_H,   DE_J,   DE_K,   DE_L,   DE_OE,		ALT_T(DE_AE),
             KC_RALT,	  DE_N,   DE_M,   DE_COMM,DE_DOT, CTL_T(DE_MINS),   	KC_RSFT,
                                  KC_LEFT,  KC_UP,KC_DOWN,KC_RIGHT,        LT(SYMB,DE_HASH),
             TG(4),	  ALL_T(DE_ACUT),
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  L5  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  <   |  >   |   !  |  ?   |      |      |           |      |   \  |   [  |   ]  |   |  |   #  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   \  |   /  |   .  |------|           |------|   /  |   (  |   )  |   {  |   }  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   ^  |   %  |   |  |   ~  |      |           |      |   &  |   <  |   >  |   "  |   '  |    ?   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |   .  |   !  |      |
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
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,DE_LESS,DE_MORE,DE_EXLM,DE_QST, KC_TRNS,KC_TRNS,
       KC_TRNS,DE_HASH,DE_DLR, DE_BSLS,DE_SLSH,KC_DOT,
       KC_TRNS,KC_TRNS,DE_LESS,DE_PERC,DE_PIPE,DE_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_DEL,KC_TRNS,
       // right hand
       M(M_TOGGLE_5), KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, LALT(LSFT(KC_7)),   LALT(KC_5),   LALT(KC_6),    LALT(KC_7),    DE_HASH, KC_F12,
                DE_SLSH,   DE_LPRN,   DE_RPRN,    LALT(KC_8),    LALT(KC_9), KC_TRNS,
       KC_TRNS, DE_AMPR, KC_GRV,   LSFT(KC_GRV),    DE_DQOT,    DE_QUOT, DE_QST,
                         KC_TRNS,KC_DOT,  KC_EXLM,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           | Mute |      |      |      |      |      |  EGOS  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk | WlUp |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght| WlDw |------|           |------|VolUp |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      | MClk |      |           |      |VolDn |      | Prev | Next | Up   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      | Left | Down | Right |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
       KC_TRNS, KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_BTN3, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_MUTE,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_VOLD, KC_TRNS, KC_MPRV, KC_MNXT, KC_UP,   KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: Smiley layer
 * making it easier to type smileys... tipp: on osx you can easily replace those smileys with the UTF-8 character using
 * keyboard short commands...
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           | :-)  | ;-)  | :-D  |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | :-{  | :-(  |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|  <3  | :-*  |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |    |     |      |      |      |                                       |     |      |           |     |     r|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,
       KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       M(SM_SMILE), M(SM_SMIRK), M(SM_LAUGH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  M(SM_FROWN),    M(SM_SAD),    M(SM_CRY),    KC_TRNS,    KC_TRNS, KC_TRNS,
                 M(SM_HEART),    M(SM_KISS),    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
//number pad
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    LSFT(KC_RBRC), KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_RBRC, DE_MINS,
       KC_TRNS, LSFT(KC_6), KC_1,   KC_2,    KC_3,    LSFT(KC_7), KC_TRNS,
                         KC_0,KC_DOT,  KC_0,    DE_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Egoshooter layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |  L5  |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  SHIFT |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |      |      |      |      |                                       |     |       |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   F1 |  F2  |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  F3  |       |      |        |      |
 *                                 | SPACE|  CTRL|------|       |------|        |      |
 *                                 |      |      |  F4  |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_F1, KC_F2,
                                                    KC_F3,
                                  KC_SPC, KC_LCTL, KC_F4,
       // right hand
       M(M_TOGGLE_5), KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(SMLY)                // FN2 - Momentary Layer 2 (Smiley)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
		static uint16_t start;
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
		if (record->event.pressed) {
		  register_code(KC_RSFT);
		} else {
		  unregister_code(KC_RSFT);
		}
		break;
	case 1:
		if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL), END);
		} else {
			if (timer_elapsed(start) > 150) {
			    return MACRO(U(LCTRL), END);
			} else {
			    return MACRO(U(LCTRL), D(LGUI), T(V), U(LGUI), END);
			}
		}
		break;
	case 2:
		if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),END);
		} else {
			if (timer_elapsed(start) > 150){
				return MACRO(U(LCTRL),END);
			} else {
				return MACRO(U(LCTRL),D(LGUI),T(C),U(LGUI),END);
			}
		}
		break;
	case 3:
		if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LSFT),D(LALT),END);
		} else {
			if (timer_elapsed(start) > 150){
				return MACRO(U(LCTRL),U(LSFT),U(LALT),END);
			} else {
				return MACRO(U(LCTRL),U(LALT),T(EQL),U(LSFT),END); //cannot use DE_ACUT here, as macro needs KC_ prefix
			}
		}
		break;
	case M_DE_CIRC_CTRLCMD:
		if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LGUI),END);
		} else {
			if (timer_elapsed(start) > 150){
				return MACRO(U(LCTRL),U(LGUI),END);
			} else {
				return MACRO(U(LCTRL),U(LGUI),T(NUBS),END); 
			}
		}
		break;
	case M_DE_PLUS_CTRLALT:
		if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LALT),END);
		} else {
			if (timer_elapsed(start) > 150){
				return MACRO(U(LCTRL),U(LALT),END);
			} else {
				return MACRO(U(LCTRL),U(LALT),T(RBRC),END); 
			}
		}
		break;
	case SM_SMILE:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(9),U(LSFT),END);
		}
		break;

	case SM_SMIRK:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(COMM),U(LSFT),T(SLSH),D(LSFT),T(9),U(LSFT),END);
		}
		break;
	case SM_CRY:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(COMM),U(LSFT),T(SLSH),D(LSFT),T(8),U(LSFT),END);
		}
		break;
 
	case SM_SAD:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(8),U(LSFT),END);
		}
		break;
      
	case SM_HEART:
		if (record->event.pressed) {
			return MACRO(T(GRV),T(3),END);
		}
		break;
	case SM_LAUGH:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(D),U(LSFT),END);
		}
		break;
	case SM_KISS:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(RBRC),U(LSFT),END);
		}
		break;
	case SM_FROWN:
		if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LALT),T(8),U(LALT),END);
		}
		break;
    case M_TOGGLE_5:  
       if (record->event.pressed){
           layer_state ^= (1<<5);
           layer_state &= (1<<5);
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
        case 4:
	    ergodox_right_led_1_on();
            ergodox_right_led_3_on();
	    //ergodox_board_led_on();
            break;
        case 5: 
        	ergodox_right_led_1_on();
        	ergodox_right_led_2_on();
        	ergodox_right_led_3_on();
        	break;
        default:
            // none
            break;
    }

};
