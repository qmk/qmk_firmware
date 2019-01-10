// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum mitosis_layers
{
	_MALT,
	_SHIFTED,
	_FUNCTION,
	_FUNCSHIFT
};

enum mitosis_keycodes
{
  FNKEY = SAFE_RANGE,
  SHIFT
};


// Macro definitions for readability
enum mitosis_macros
{
	VOLU,
	VOLD,
	ESCM
};

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MALT] = LAYOUT( /* Malt Layout, customised for reduced columns (ex: quote and shift locations) */
    KC_Q,    KC_P,    KC_Y,    KC_C,    KC_B,           KC_V,    KC_M,    KC_U,    KC_Z,    KC_L,
    KC_A,    KC_N,    KC_I,    KC_S,    KC_F,           KC_D,    KC_T,    KC_H,    KC_O,    KC_R,
    KC_COMM, KC_DOT,  KC_J,    KC_G,    KC_SLSH,        KC_SCLN, KC_W,    KC_K,    KC_QUOT, KC_X,
             M(VOLU), M(ESCM), KC_TAB,  KC_LCTL,        KC_LALT, KC_ENT,  KC_DEL,  KC_PGUP,
             M(VOLD), KC_LGUI, KC_E,    FNKEY,          SHIFT,   KC_SPC,  KC_BSPC, KC_PGDN
  ),


  [_SHIFTED] = LAYOUT( /* Shifted Layer, layered so that tri_layer can be used, or selectively
                                         able to modify individual key's shifted behaviour */
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
             _______, _______, _______, _______,       _______, _______, _______, _______,
             _______, _______, _______, _______,       _______, _______, _______, _______
  ),



  [_FUNCTION] = LAYOUT( /* Function Layer, primary alternative layer featuring numpad on right hand,
                                           cursor keys on left hand, and all symbols*/
    KC_AMPR, KC_PERC, KC_UP,   KC_CIRC, KC_PIPE,       KC_LBRC, KC_7,    KC_8,    KC_9,    KC_MINS,
    KC_AT,   KC_LEFT, KC_DOWN, KC_RGHT, KC_HASH,       KC_LPRN, KC_4,    KC_5,    KC_6,    KC_PLUS,
    KC_ASTR, KC_UNDS, KC_EXLM, KC_DLR,  KC_BSLS,       KC_LCBR, KC_1,    KC_2,    KC_3,    KC_ENT,
             KC_HOME, KC_GRV,  KC_PWR,  _______,       _______, KC_EQL,  KC_TILD, KC_DOT,
             KC_END,  _______, _______, _______,       _______, KC_0,    _______, KC_PSCR
  ),


  [_FUNCSHIFT] = LAYOUT( /* Function Shifted Layer, secondary alternative layer with closing brackets,
                                                    and F-keys under their numpad equivalents*/
    _______, _______, _______, _______, _______,       KC_RBRC, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, _______, _______, _______, _______,       KC_RPRN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    _______, _______, _______, _______, _______,       KC_RCBR, KC_F1,   KC_F2,   KC_F3,   KC_F12,
             _______, _______, _______, _______,       _______, _______, _______, _______,
             _______, _______, _______, _______,       _______, _______, _______, _______
  )

};

static uint16_t key_timer;

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

static bool singular_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	uint8_t layer;
  layer = biton32(layer_state);  // get the current layer

  //custom layer handling for tri_layer,
  switch (keycode) {
  case FNKEY:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_FUNCTION);
  	} else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_FUNCTION);
      }
  	}
    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
  	return false;
  	break;
  //SHIFT is handled as LSHIFT in the general case
  case SHIFT:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_SHIFTED);
    	register_code(KC_LSFT);
  	} else {
    	if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_SHIFTED);
    	  unregister_code(KC_LSFT);
      }
    }
    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
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
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
    	case _MALT:
    		set_led_off;
    		break;
        case _FUNCTION:
            set_led_blue;
            break;
        case _SHIFTED:
            set_led_red;
            break;
        case _FUNCSHIFT:
        	set_led_green;
        	break;
        default:
            break;
    }
};

