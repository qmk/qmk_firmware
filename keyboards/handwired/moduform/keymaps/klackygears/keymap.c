
/* A QWERTY 3 Layer layout for the Dactyl Manuform 6x6 Keyboard */

#include QMK_KEYBOARD_H
#include "klackygears.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_MACBASE] = LAYOUT(
     KC_1  , KC_2  , KC_3  ,  KC_4  , KC_5  ,      KC_6  , KC_7   , KC_8   , KC_9   , KC_0,
     KC_Q  , KC_W  , KC_E  ,  KC_R  , KC_T  ,      KC_Y  , KC_U   , KC_I   , KC_O   , KC_P,
     KC_A  , KC_S  , KC_D  ,  KC_F  , KC_G  ,      KC_H  , KC_J   , KC_K   , KC_L   ,KC_SCLN,
                    KC_PSCR, KC_LGUI, KC_SPC,      KC_ENT,KC_GRAVE, KC_AT

  ),


  [_WINBASE] = LAYOUT(
     KC_1  , KC_2  , KC_3  ,  KC_4  , KC_5  ,      KC_6  , KC_7   , KC_8   , KC_9   , KC_0,
     KC_Q  , KC_W  , KC_E  ,  KC_R  , KC_T  ,      KC_Y  , KC_U   , KC_I   , KC_O   , KC_P,
     KC_A  , KC_S  , KC_D  ,  KC_F  , KC_G  ,      KC_H  , KC_J   , KC_K   , KC_L   ,KC_SCLN,
                    KC_PSCR, KC_LGUI, KC_SPC,      KC_ENT,KC_GRAVE, KC_AT

),

  [_NUMB] = LAYOUT(
     KC_1  , KC_2  , KC_3  ,  KC_4  , KC_5  ,      KC_6  , KC_7   , KC_8   , KC_9   , KC_0,
     KC_Q  , KC_W  , KC_E  ,  KC_R  , KC_T  ,      KC_Y  , KC_U   , KC_I   , KC_O   , KC_P,
     KC_A  , KC_S  , KC_D  ,  KC_F  , KC_G  ,      KC_H  , KC_J   , KC_K   , KC_L   ,KC_SCLN,
                    KC_PSCR, KC_LGUI, KC_SPC,      KC_ENT,KC_GRAVE, KC_AT
  )
  };
