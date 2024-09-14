#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _MACROPAD,
    _FN,
    _ADJ
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MACROPAD,
  FN,
  ADJ,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};



#define FN_ESC  LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns

#define BASE_LAYOUT( \
  _00, _01, _02, _03, _04, \
  _10, _11, _12, _13, _14, \
  _20, _21, _22, _23, _24, \
  _30, _31, _32, _33, _34 \
) \
LAYOUT_ortho_5x6( \
      QK_GESC, _00,     _01,     _02,     _03,     _04, \
      KC_TAB,  _10,     _11,     _12,     _13,     _14, \
      FN_CAPS, _20,     _21,     _22,     _23,     _24, \
      KC_LSFT, _30,     _31,     _32,     _33,     _34, \
      KC_LCTL, KC_LGUI, KC_LALT, UG_TOGG, ADJ,  KC_SPC \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = BASE_LAYOUT(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
  ),

  [_MACROPAD] = BASE_LAYOUT(
      KC_F13,    KC_F14,    KC_F15,    KC_F16,    KC_F17,
      KC_F18,    KC_F19,    KC_F20,    KC_F21,    KC_F22,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
  ),

  [_FN] = LAYOUT_ortho_5x6(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, UG_NEXT, _______, _______
      ),

  [_ADJ] =  LAYOUT_ortho_5x6(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      _______, UG_SATD, UG_VALU, UG_SATU, QK_BOOT, _______,
      _______, UG_HUED, UG_VALD, UG_HUEU, RGBRST,  _______,
      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, UG_NEXT, _______, _______
      )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

// Setting ADJ layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case MACROPAD:
      if(record->event.pressed) {
        set_single_persistent_default_layer(_MACROPAD);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_FN);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_FN);
        TOG_STATUS = false;
      }
      return false;
      break;
    case ADJ:
        if (record->event.pressed) {
          layer_on(_ADJ);
        } else {
          layer_off(_ADJ);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}
