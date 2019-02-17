#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "quantum.h"

enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  SEL_ALL,
  AFTER,
  PREMIERE,
  PHOTOSHOP,
  PYTHON,
  NAV,
  NUMPAD
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("Est-ce que au moins quand j'écris ça, ça marche ? à mon avis, bof!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
	case SEL_ALL:
	  if (record->event.pressed) {
		// when keycode QMKBEST is pressed
		SEND_STRING(SS_LCTRL("q"));
	  } else {
		// when keycode QMKBEST is released
	  }
	  break;
	 
	case AFTER:
	  if (record->event.pressed) {
		// when keycode QMKBEST is pressed
		rgblight_enable();
		rgblight_mode(1);
		rgblight_sethsv(288, 255, 255);
		layer_move(0);
		
	  } else {
		// when keycode QMKBEST is released
	  }
	  break;
	case PREMIERE:
	  if (record->event.pressed) {
		// when keycode QMKBEST is pressed
		rgblight_enable();
		rgblight_mode(1);
		rgblight_sethsv(338, 255, 255);
		layer_move(1);
		
	  } else {
		// when keycode QMKBEST is released
	  }
	  break;
	 case PHOTOSHOP:
	  if (record->event.pressed) {
		// when keycode QMKBEST is pressed
		rgblight_enable();
		rgblight_mode(1);
		rgblight_sethsv(260, 255, 255);
		layer_move(2);
		
	  } else {
		// when keycode QMKBEST is released
	  }
	  break;
	  case PYTHON:
	  if (record->event.pressed) {
		// when keycode QMKBEST is pressed
		rgblight_enable();
		rgblight_mode(1);
		rgblight_sethsv(120, 255, 255);
		layer_move(3);
		
	  } else {
		// when keycode QMKBEST is released
	  }
	  break;
	  case NAV:
	  if (record->event.pressed) {
		
		rgblight_enable();
		rgblight_mode(1);
		rgblight_sethsv(120, 0, 128);
		layer_invert(4);
		
	  } else {
		
	  }
	  break;
	  	  case NUMPAD:
	  if (record->event.pressed) {
		backlight_disable()
		layer_invert(5);
		
	  } else {
		
	  }
	  break;

  }
  return true;
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {


  rgblight_enable();
}

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case AFTER:
        rgblight_setrgb(0x00, 0x00, 0xFF);
        break;
      case PREMIERE:
        rgblight_setrgb(0x00, 0xA0, 0xFF);
        break;
      case PHOTOSHOP:
        rgblight_setrgb(0xFF, 0x00, 0x00);
        break;
      case PYTHON:
        rgblight_setrgb(0xFF, 0x20, 0x00);
        break;
      case NAV:
        rgblight_setrgb(0xFF, 0x00, 0xFF);
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

enum {
  TD_ESC_CAPS = 0
};

#define NUL M(0)
#define SOLID M(1)
#define KEYF M(2)
#define POSITION M(3)
#define SCALE M(4)
#define ROTA M(5)
#define OPAC M(6)
#define EFX M(7)
#define FONDU M(8)

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LCTRL), D(LALT),D(LSHIFT),D(Y), U(LCTRL), U(LALT),U(LSHIFT),U(Y),END);
            case 1:
                return MACRO(D(LCTRL), D(Y), U(Y), U(LCTRL),END);
			case 2:
                return MACRO(D(U), U(U),D(U),U(U),END) ;
			case 3:
                return MACRO(D(P), U(P),END) ;
			case 4:
                return MACRO(D(S), U(S),END) ;
			case 5:
                return MACRO(D(R), U(R),END) ;
			case 6:
                return MACRO(D(T), U(T),END) ;
			case 7:
				return MACRO(D(LCTRL), D(LALT),D(Y), U(LCTRL), U(LALT),U(Y),END);
			case 8:
				return MACRO(D(LALT), D(LSFT), D(T),U(LALT), U(LSFT), U(T), D(LCTL), D(LSFT), D(RIGHT), U(LCTL), U(LSFT), U(RIGHT),D(LALT), D(LSFT), D(T),U(LALT), U(LSFT), U(T),END);
				
        }
    }
    return MACRO_NONE;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* AFTER */
	[0] = LAYOUT_ortho_5x4(
	FONDU, FR_U, RGB_SPI, BL_TOGG, 
	POSITION, SCALE, ROTA, OPAC, 
	NUL, SOLID, EFX, KC_ENT, 
	NAV, RGB_VAD, TO(1), BL_OFF, 
	PYTHON, PREMIERE, KC_NO,NUMPAD
),
	/* PREMIERE */
	[1] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R, 
	FR_Q, FR_S, FR_D, FR_F, 
	FR_W, FR_X, FR_C, FR_V, 
	KC_WH_L, KC_WH_R, TO(0), KC_NO, 
	AFTER, PHOTOSHOP, FR_A, QMKBEST
),
	/* PHOTOSHOP */
	[2] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R, 
	FR_Q, FR_S, FR_D, FR_F, 
	FR_W, FR_X, FR_C, FR_V, 
	KC_WH_L, KC_WH_R, TO(0), KC_NO, 
	PREMIERE, PYTHON, FR_A, QMKBEST
),
	/* PYTHON */
	[3] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R, 
	FR_Q, FR_S, FR_D, FR_F, 
	FR_W, FR_X, FR_C, FR_V, 
	KC_WH_L, KC_WH_R, TO(0), KC_NO, 
	PHOTOSHOP, AFTER, FR_A, QMKBEST
),
	/* NAV */
	[4] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R, 
	KC_NO,KC_NO, KC_UP, FR_D, 
	FR_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT,
	AFTER, KC_WH_R, TO(0), KC_NO, 
	PYTHON, PHOTOSHOP, PREMIERE, FR_LCTR
)
	/* NUMPAD */
	[5] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R, 
	KC_NO,KC_KP_7, KC_KP_8, KC_KP_9, 
	FR_LSFT, KC_KP_4, KC_KP_5, KC_KP_6,
	AFTER, KC_KP_1, KC_KP_2, KC_KP_3, 
	PYTHON, PHOTOSHOP, PREMIERE, FR_LCTR
)
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(FR_SPAC, FR_DOT)
// Other declarations would go here, separated by commas, if you have them
};