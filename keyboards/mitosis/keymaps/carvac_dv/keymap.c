// This is the Dvorak-friendly layout for the Mitosis by CarVac (/u/CarVac)

#include "mitosis.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum mitosis_layers
{
	_STD,
	_NUM,
	_FN
};

/*
enum mitosis_keycodes 
{
  FNKEY = SAFE_RANGE,
  SHIFT
};
*/


#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300
#define TAPPING_TOGGLE 1

//Mousekeys
#define MOUSEKEY_DELAY 300
#define MOUSEKEY_INTERNAL 50
#define MOUSEKEY_MAX_SPEED 20
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY WHEEL TIME TO MAX 40

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------..--------------------------------------------.
 * | Q      | W      | E      | R      | T      || Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | A      | S      | D      | F      | G      || J      | H      | K      | L      | ;      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | Z      | X      | C      | V      | B      || N      | M      | ,      | .      | /      |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          | PGUP   | PSCR   | LCTRL  | SPACE  || LSHIFT | ENTER  | UP     | BACKSP |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          | PGDN   | LGUI   | LALT   | FN     || NUM    | LEFT   | DOWN   | RIGHT  |
 *          '-----------------------------------''-----------------------------------'
 *                                       FN is momentary, NUM is tap-toggle.
 */

[_STD] = { /* Standard; as compatible with dvorak and qwerty as possible */
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    },
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN },
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH },
  {XXXXXXX, KC_PGUP, KC_PSCR, KC_LCTL, KC_SPC,         KC_LSFT, KC_ENT,  KC_UP,   KC_PGUP, XXXXXXX },
  {XXXXXXX, KC_PGDN, KC_LGUI, KC_LALT, MO(_FN),       TT(_NUM), KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX }
},

/* Number layout, for data entry and programming purposes (Dvorak result in parens)
 * .--------------------------------------------..--------------------------------------------.
 * | TAB    |   (,<) |   (.>) | - ([{) | = (]}) || ] (=+) | pad *  | pad +  | pad -  | [ (/?) |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | 1      | 2      | 3      | 4      | 5      || 6      | 7      | 8      | 9      | 0      |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | F1     | F2     | F3     | F4     | F5     || F6     | F7     | F8     | F9     | F10    |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          | F11    | F12    |        |        ||        |        |        |        |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          |        |        |        |        ||        |        |        |        |
 *          '-----------------------------------''-----------------------------------'
 */

[_NUM] = { /* Number layout along the home row for maximum speed*/
  {_______, _______, _______, KC_MINS, KC_EQL,        KC_RBRC, KC_PAST, KC_PPLS, KC_PMNS, KC_LBRC },
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0    },
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10  },
  {XXXXXXX, KC_F11,  KC_F12,  _______, _______,       _______, _______, _______, _______, XXXXXXX },
  {XXXXXXX, _______, _______, _______, _______,       _______, _______, _______, _______, XXXXXXX }
},


/* Fn layout, for typing purposes (Dvorak result in parens)
 * .--------------------------------------------..--------------------------------------------.
 * | `      |        | MS_U   |        |        || BTN4   |        | BTN3   |        | [ (/?) |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | ESC    | MS_L   | MS_D   | MS_R   |        || BTN5   | BTN1   | BTN2   |        | ' (-_) |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * | APP    | MPRV   | MPLY   | MSTP   | MNXT   || BSPC   | DEL    | INS    |        | \      |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          | VOLU   |        |        |        ||        |        | PGUP   |        |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          | VOLD   |        |        |        ||        | HOME   | PGDN   | END    |
 *          '-----------------------------------''-----------------------------------'
 */

[_FN] = { /* Function Layer, primary alternative layer featuring numpad on right hand,
                                   cursor keys on left hand, and all symbols*/
  {KC_GRV,  _______, KC_MS_U, _______, _______,       KC_BTN4, _______, KC_BTN3, _______, KC_LBRC },
  {KC_ESC,  KC_MS_L, KC_MS_D, KC_MS_R, _______,       KC_BTN5, KC_BTN1, KC_BTN2, _______, KC_QUOT },
  {KC_APP,  KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,       KC_BSPC, KC_DEL,  KC_INS,  _______, KC_BSLS },
  {XXXXXXX, KC_VOLU, _______, _______, _______,       _______, _______, KC_PGUP, _______, XXXXXXX },
  {XXXXXXX, KC_VOLD, _______, _______, _______,       _______, KC_HOME, KC_PGDN, KC_END,  XXXXXXX }
},

/* 
 * .--------------------------------------------..--------------------------------------------.
 * |        |        |        |        |        ||        |        |        |        |        |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * |        |        |        |        |        ||        |        |        |        |        |
 * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
 * |        |        |        |        |        ||        |        |        |        |        |
 * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
 *          |        |        |        |        ||        |        |        |        |
 *          |--------+--------+--------+--------||--------+--------+--------+--------|
 *          |        |        |        |        ||        |        |        |        |
 *          '-----------------------------------''-----------------------------------'
 */

};

/*
const uint16_t PROGMEM fn_actions[] = {

};

static uint16_t key_timer;
*/

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {

      	//switch multiplexing for media, short tap for volume up, long press for play/pause
        case VOLU:
            if (record->event.pressed) {
            	key_timer = timer_read(); // if the key is being pressed, we start the timer.
          	} else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) { // LONGPRESS_DELAY being 150ms, the threshhold we pick for counting something as a tap.
                  return MACRO(T(MPLY), END);
                } else {
                  return MACRO(T(VOLU), END);
                }
          	}
          	break;

		//switch multiplexing for media, short tap for volume down, long press for next track
        case VOLD:
            if (record->event.pressed) {
            	key_timer = timer_read();
          	} else {
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
                  return MACRO(T(MNXT), END);
                } else {
                  return MACRO(T(VOLD), END);
                }
          	}
          	break;

        //switch multiplexing for escape, short tap for escape, long press for context menu
        case ESCM:
            if (record->event.pressed) {
            	key_timer = timer_read();
          	} else {
            	if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
                  return MACRO(T(APP), END);
                } else {
                  return MACRO(T(ESC), END);
                }
          	}
          	break;     

        break;
    }
    return MACRO_NONE;
};
*/

/*
static bool singular_key = false;
*/

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	uint8_t layer;
  layer = biton32(layer_state);  // get the current layer

  //custom layer handling for tri_layer,
  switch (keycode) {
  case FNKEY:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_FN);
  	} else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_FN);
      }
  	}
    update_tri_layer(_FN, _NUM, _FUNCSHIFT);
  	return false;
  	break;
  //NUM
  case NUM:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_NUM);
  	} else {
    	if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_NUM);
      }
    }
    update_tri_layer(_FN, _NUM, _FUNCSHIFT);
  	return false;
  	break;

  //If any other key was pressed during the layer mod hold period,
  //then the layer mod was used momentarily, and should block latching
  default:
    singular_key = false;
    break;
  }

  //FUNCSHIFT has been shifted by the SHIFT handling, some keys need to be excluded
  if (layer == _FUNCSHIFT) {
  	//F1-F12 should be sent as unshifted keycodes, 
  	//and ] needs to be unshifted or it is sent as }
  	if ( (keycode >= KC_F1 && keycode <= KC_F12)
  	   || keycode == KC_RBRC ) {
  		if (record->event.pressed) {
              unregister_mods(MOD_LSFT);
          } else {
              register_mods(MOD_LSFT);
          }
  	}
  }

  return true;
};*/

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    
    switch (layer) {
    	case _STD:
    		set_led_off;
    		break;
        case _FN:
            set_led_blue;
            break;
        case _NUM:
            set_led_red;
            break;
        default:
            break;
    }
};

