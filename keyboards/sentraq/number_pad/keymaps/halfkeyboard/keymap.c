#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "quantum.h"
#include "sendstring_french.h"
#include "bootmagic.c"


/* source for the light code for layers = AGausmann on Github */
/* define layers */
#define AFTER 0
#define TECHNIQUE 1


enum custom_keycodes {
  CK_AFTER = TO(AFTER),
  CK_TECHNIQUE= TO(TECHNIQUE),
  FOLDER= SAFE_RANGE,
  DICT,

};


void persistent_default_layer_set(uint16_t after) {
  eeconfig_update_default_layer(0);
  default_layer_set(0);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {

     case FOLDER:
     if (record->event.pressed) {
        SEND_STRING("for subdirs, dirs, files in os.walk(folder):\n" SS_TAP(X_TAB) "for file in files:\n" );

      } else {
        // when keycode QMKURL is released
      }
      break;

      case DICT:
     if (record->event.pressed) {
        SEND_STRING("&é\"'(-è_çà");

      } else {
        // when keycode QMKURL is released
      }
      break;

  }
  return true;
};



uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case AFTER:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(288, 255, 255);
        break;
      case TECHNIQUE:
        rgblight_mode(RGBLIGHT_MODE_KNIGHT);
        break;

    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(288, 255, 255);
        break;
    }
  return state;
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
	KC_T, KC_G, KC_B, KC_SPACE,
	KC_R, KC_F, KC_V, CK_TECHNIQUE,
	KC_E, KC_D, KC_C, FR_LALT,
	FR_Z, KC_S, KC_X, KC_LGUI,
	FR_A, FR_Q, FR_W,FR_LCTR
),

	/* TECHNIQUE */
	[1] = LAYOUT_ortho_5x4(
	BL_TOGG, BL_STEP, KC_NO, RESET,
	RGB_TOG,RGB_MODE_FORWARD, RGB_MODE_REVERSE, KC_NO,
	RGB_HUI,RGB_SAI, RGB_VAI, KC_NO,
	RGB_HUD,RGB_SAD, RGB_VAD, KC_NO,
	CK_AFTER, KC_NO, KC_NO,KC_NO
)
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(FR_SPAC, FR_DOT)
// Other declarations would go here, separated by commas, if you have them
};
