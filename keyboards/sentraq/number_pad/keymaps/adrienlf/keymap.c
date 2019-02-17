#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "quantum.h"
#include "sendstring_french.h"


/* source for the light code for layers = AGausmann on Github */
/* define layers */
#define AFTER 0
#define PREMIERE 1
#define PHOTOSHOP 2
#define PYTHON 3
#define NAV 4
#define NUMPAD 5
#define TECHNIQUE 6


enum custom_keycodes {
  CK_AFTER = TO(AFTER),
  CK_PREMIERE = TO(PREMIERE),
  CK_PHOTOSHOP = TO(PHOTOSHOP),
  CK_PYTHON = TO(PYTHON),
  CK_NAV = TT(NAV),
  CK_NUMPAD = TT(NUMPAD),
  CK_TECHNIQUE= TO(TECHNIQUE),
  FOLDER= SAFE_RANGE,
  DICT,

};


void persistent_default_layer_set(uint16_t after) {
  eeconfig_update_default_layer(after);
  default_layer_set(after);
}

void matrix_init_user(void) {


  rgblight_enable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case CK_PYTHON :
      if (record->event.pressed && get_mods() & MOD_BIT(CK_PREMIERE) ) {
        layer_move(6);
        return false;
      } else {
        return true;
      }
       break;

     case FOLDER:
     if (record->event.pressed) {
        SEND_STRING("for subdirs, dirs, files in os.walk(folder):\n" SS_TAP(X_TAB) "for file in files:\n" SS_TAP(X_TAB));

      } else {
        // when keycode QMKURL is released
      }
      break;

      case DICT:
     if (record->event.pressed) {
        SEND_STRING("list = [], dict = {}, \\n");

      } else {
        // when keycode QMKURL is released
      }
      break;

  }
  return true;
};

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case AFTER:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(288, 255, 255);
        break;
      case PREMIERE:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(338, 255, 255);
        break;
      case PHOTOSHOP:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(260, 255, 255);
        break;
      case PYTHON:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(120, 255, 255);
        break;
      case NAV:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(120, 0, 128);
        break;
	case NUMPAD:
	rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(120, 0, 5);
        break;
	case TECHNIQUE:
        rgblight_mode(RGBLIGHT_MODE_KNIGHT);
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}

enum {
  TD_ESC_CAPS = 0
};

/* define macros */

#define NUL M(0)
#define SOLID M(1)
#define KEYF M(2)
#define POSITION M(3)
#define SCALE M(4)
#define ROTA M(5)
#define OPAC M(6)
#define EFX M(7)
#define FONDU M(8)
#define MA_100 M(9)
#define SELAL M(10)
#define CLOSE M(11)
#define DUPL M(12)



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
              case 9:
                        return MACRO(D(KP_1), U(KP_1),D(KP_0),U(KP_0),D(KP_0),U(KP_0),END);
              case 10:
                        return MACRO(D(LCTL), D(A),U(LCTL),U(A),END);
              case 11:
                        return MACRO(D(LCTL), D(W),U(LCTL),U(W),END);
              case 12:
                        return MACRO(D(LCTL), D(D),U(LCTL),U(D),END);
        }
    }
    return MACRO_NONE;
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* AFTER */
	[0] = LAYOUT_ortho_5x4(
	FONDU, FR_U, FR_F9, DICT,
	POSITION, SCALE, ROTA, OPAC,
	NUL, SOLID, FR_UGRV, KC_ENT,
	CK_NAV, SELAL, CLOSE, DUPL,
	CK_PYTHON, CK_PREMIERE, CK_TECHNIQUE,CK_NUMPAD
),
	/* PREMIERE */
	[1] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R,
	FR_Q, FR_S, FR_D, FR_F,
	FR_W, FR_X, FR_C, FR_V,
	KC_WH_L, KC_WH_R, TO(0), KC_NO,
	CK_AFTER, CK_PHOTOSHOP, KC_NO,CK_NUMPAD
),
	/* PHOTOSHOP */
	[2] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R,
	FR_Q, FR_S, FR_D, FR_F,
	FR_W, FR_X, FR_C, FR_V,
	KC_WH_L, KC_WH_R, TO(0), KC_NO,
	CK_PREMIERE, CK_PYTHON, KC_NO,CK_NUMPAD
),
	/* PYTHON */
	[3] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FOLDER,
	FR_Q, FR_S, FR_D, FR_F,
	FR_W, FR_X, FR_C, FR_V,
	KC_WH_L, KC_WH_R, TO(0), KC_NO,
	CK_PHOTOSHOP, CK_AFTER, KC_NO,CK_NUMPAD
),
	/* NAV */
	[4] = LAYOUT_ortho_5x4(
	M(2), FR_Z, FR_E, FR_R,
	KC_NO,FR_J, KC_UP, FR_K,
	FR_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT,
	CK_NAV, KC_WH_R, TO(0), KC_NO,
	CK_PYTHON, CK_PHOTOSHOP, KC_NO,FR_LCTR

),
	/* NUMPAD */
	[5] = LAYOUT_ortho_5x4(
	KC_BSPACE, FR_Z, FR_E, FR_TAB,
	KC_KP_MINUS,KC_KP_7, KC_KP_8, KC_KP_9,
	KC_KP_PLUS, KC_KP_4, KC_KP_5, KC_KP_6,
	KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3,
	MA_100, CK_PHOTOSHOP, CK_AFTER,CK_NUMPAD
)
,
	/* TECHNIQUE */
	[6] = LAYOUT_ortho_5x4(
	BL_TOGG, BL_STEP, KC_NO, RESET,
	RGB_TOG,RGB_MODE_FORWARD, RGB_MODE_REVERSE, KC_NO,
	RGB_HUI,RGB_SAI, RGB_VAI, KC_NO,
	RGB_HUD,RGB_SAD, RGB_VAD, KC_NO,
	CK_AFTER, CK_PREMIERE, CK_PHOTOSHOP,CK_PYTHON
)
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(FR_SPAC, FR_DOT)
// Other declarations would go here, separated by commas, if you have them
};
