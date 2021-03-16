
// MINI MACRO 5

#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
	_MEDIA,
	_DISCORD,
	_PHOTOSHOP
};

// Tap Dance declarations
enum tap_dances{
    TD_TO_DISCORD,
	TD_TO_PHOTOSHOP,
	TD_TO_MEDIA,
	TD_TO_MAIN,
	TD_RESET_SLIDER
	
};


void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder*/
    switch(biton32(layer_state)){
		case _MAIN:
			if (clockwise) {
			  tap_code(KC_VOLU);
			} else {
			  tap_code(KC_VOLD);
			}
			break;
		case _MEDIA:
			if (clockwise) {
			  tap_code(KC_VOLU);
			} else {
			  tap_code(KC_VOLD);
			}
			break;
		case _DISCORD:
			if (clockwise) {
			  tap_code(KC_VOLU);
			} else {
			  tap_code(KC_VOLD);
			}
			break;
		case _PHOTOSHOP:
			if (clockwise) {
			  tap_code(KC_UP);
			} else {
			  tap_code(KC_DOWN);
			}
			break;
		default:
			if (clockwise) {
			  tap_code(KC_VOLU);
			} else {
			  tap_code(KC_VOLD);
			}
			break;
	}
  }
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     TD(TD_TO_DISCORD), 	TO(_DISCORD), 	KC_C, 	RGB_TOG, 	TD(TD_TO_PHOTOSHOP)
  ),
  [_MEDIA] = LAYOUT_ortho_1x5(
     TD(TD_TO_MAIN), 	KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_STOP
  ),
  [_DISCORD] = LAYOUT_ortho_1x5(
     TD(TD_TO_MAIN), 	TD(TD_TO_MEDIA), 	KC_Q, 		KC_R, 		MEH(KC_UP)
  )
  ,
  [_PHOTOSHOP] = LAYOUT_ortho_1x5(
     TD(TD_RESET_SLIDER) , C(KC_Z),			C(KC_Y), 	KC_P, 		KC_G
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
	
	if (layer_state_cmp(state, _MAIN)) // this one not working 
		rgblight_sethsv_at(HSV_GREEN, 0);
	if (layer_state_cmp(state, _MEDIA))
		rgblight_sethsv_at(HSV_RED, 0);
	if (layer_state_cmp(state, _DISCORD))
		rgblight_sethsv_at(HSV_BLUE, 0);
	if (layer_state_cmp(state, _PHOTOSHOP))
		rgblight_sethsv_at(HSV_PURPLE, 0);
    return state;
}

void keyboard_post_init_user(void) {
	//rgblight_mode(1);
	rgblight_sethsv_at(HSV_GREEN, 0);
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_TO_DISCORD] = ACTION_TAP_DANCE_LAYER_MOVE(KC_MUTE, _DISCORD),
	[TD_TO_PHOTOSHOP] = ACTION_TAP_DANCE_LAYER_MOVE(KC_E, _PHOTOSHOP),
	[TD_TO_MEDIA] = ACTION_TAP_DANCE_LAYER_MOVE(KC_E, _MEDIA),
	[TD_TO_MAIN] = ACTION_TAP_DANCE_LAYER_MOVE(KC_MUTE, _MAIN),
	[TD_RESET_SLIDER] = ACTION_TAP_DANCE_LAYER_MOVE(KC_0, _MAIN)
};



