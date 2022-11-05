#include QMK_KEYBOARD_H

// Custom user includes
#include "issmirnov.h"
#include "tap_tog.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_ergodox_wrapper(
KC_ESCAPE,      KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_EXLM,
LCTL(KC_SPACE), _________________QWERTY_L1_________________,   KC_ASTR,
KC_TAB,         _________________QWERTY_L2_________________,
OSM(MOD_LSFT),  _________________QWERTY_L3_________________,   KC_SLASH,
KC_LCTL, LSFT(KC_LGUI), LSFT(KC_LALT),  KC_LALT,   KC_LGUI,
                                        XXXXXXX,  XXXXXXX,
                                                XXXXXXX,
                        KC_SPACE,   KC_BSPACE,  KC_DEL,

KC_EQL    , KC_6    , KC_7    , KC_8    , KC_9          , KC_0    , KC_ESCAPE      ,
KC_PLUS   , _________________QWERTY_R1_________________  , LGUI(KC_SPACE) ,
            _________________QWERTY_R2_________________  , MO(_NAVI) ,
KC_MINS   , _________________QWERTY_R3_________________  , KC_QUOTE       ,
KC_ESCAPE , KC_COLN , KC_PERC , XXXXXXX , LGUI(KC_L)    ,

KC_LEFT,  KC_RGHT,
KC_UP,
KC_DOWN,  KC_TAB, KC_ENTER
),

  // layer 1
[_SYMB] = LAYOUT_ergodox_wrapper(
KC_ESCAPE , KC_F1         , KC_F2         , KC_F3       , KC_F4            , KC_F5    , KC_F6    ,
XXXXXXX   , _________________SYMB_L1___________________ ,KC_ASTR  ,
KC_TAB    ,  _________________SYMB_L2___________________,
KC_LSHIFT ,  _________________SYMB_L3___________________, KC_SLASH ,
KC_LCTL   , LSFT(KC_LGUI) , LSFT(KC_LALT) , KC_LALT     , WKSP_LEFT  ,

                                              XXXXXXX,        XXXXXXX,
                                                            XXXXXXX,
                                    WKSP_RIGHT, KC_BSPACE,    KC_DEL,

KC_F7     , KC_F8    , KC_F9   , KC_F10    , KC_F11    , KC_F12  , XXXXXXX  ,
KC_PLUS   , _________________SYMB_R1___________________ , MO(_NAVI)  ,
           _________________SYMB_R2___________________  , KC_DQUO ,
KC_MINS  , _________________SYMB_R3___________________ , KC_QUOTE ,
KC_ESCAPE , KC_COLN  , KC_PERC , XXXXXXX   , XXXXXXX   ,

KC_LEFT,  KC_RGHT,
KC_UP,
KC_DOWN,  KC_TAB, KC_ENTER
),

  // layer 2
[_NUMP] = LAYOUT_ergodox_wrapper(
XXXXXXX ,  ___________________XXXXX___________________, XXXXXXX  ,
XXXXXXX , _________________NUMP_L1___________________ , KC_ASTR  ,
KC_TAB  , _________________NUMP_L2___________________ ,
XXXXXXX , _________________NUMP_L3___________________ , KC_SLASH ,
TO(0)   , XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,

                                            XXXXXXX  ,  XXXXXXX  ,
                                                        XXXXXXX  ,
                                            KC_SPACE , KC_BSPACE , KC_DEL ,

KC_EQL  , ___________________XXXXX___________________ , RESET   ,
KC_PLUS , _________________NUMP_R1___________________ , XXXXXXX ,
          _________________NUMP_R2___________________ , XXXXXXX                                     ,
KC_MINS , _________________NUMP_R3___________________ , XXXXXXX ,
                KC_0    , XXXXXXX , XXXXXXX , TO(3)   , XXXXXXX ,

KC_LEFT,  KC_RGHT,
KC_UP,
KC_DOWN,  KC_LALT, KC_LSFT
),

  // layer 3
[_OVERWATCH] = LAYOUT_ergodox_wrapper(
KC_ESCAPE, KC_1    , KC_2 , KC_3 , KC_4 , KC_5 , TO(0) ,
______________OVERWATCH_L1_________________ , XXXXXXX ,
______________OVERWATCH_L2_________________ ,
______________OVERWATCH_L3_________________ , XXXXXXX ,
______________OVERWATCH_L4_________________ ,

XXXXXXX  , XXXXXXX ,
XXXXXXX  ,
KC_SPACE , XXXXXXX , XXXXXXX ,


_______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,

_______, _______,
_______,
_______, _______, _______

),
// layer 4
[_NAVI] = LAYOUT_ergodox_wrapper(
KC_ESCAPE, KC_1    , KC_2 , KC_3 , KC_4 , KC_5 , KC_6 ,
XXXXXXX, _________________NAVI_L1___________________ , XXXXXXX ,
XXXXXXX, _________________NAVI_L2___________________ ,
XXXXXXX, _________________NAVI_L3___________________ , XXXXXXX ,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WKSP_LEFT,

XXXXXXX  , XXXXXXX ,
XXXXXXX  ,
WKSP_RIGHT , XXXXXXX , XXXXXXX ,


_______, _______, _______, _______, _______, _______, _______,
_______, _________________NAVI_R1___________________, _______,
         _________________NAVI_R2___________________, _______,
_______, _________________NAVI_R3___________________, _______,
MODSFT, _______, _______, _______, _______,

_______, _______,
_______,
_______, _______, KC_LGUI

),
};


// called by QMK during key processing before the actual key event is handled. Useful for macros.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t layer = get_highest_layer(layer_state);
  switch (keycode) {
    case TAP_TOG_LAYER:
      process_tap_tog(_SYMB,record);
      return false;
      break;

    case WKSP_LEFT:
      // Only if TAP_TOG_LAYER is being held right now do we want to do actions.
      if (record->event.pressed && (!tap_tog_layer_toggled_on || layer == _NAVI)) {
        tap_code16(LGUI(LSFT(KC_Z)));
        tap_tog_layer_other_key_pressed = true; // Add flag so layer resets
      }
      break;
    case WKSP_RIGHT:
      // Only if TAP_TOG_LAYER is being held right now do we want to do actions.
      if (record->event.pressed && (!tap_tog_layer_toggled_on || layer == _NAVI)) {
        tap_code16(LGUI(LSFT(KC_X)));
        tap_tog_layer_other_key_pressed = true; // Add flag so layer resets
      }
      break;
    default:
      tap_tog_count = 0; // reset counter.
      tap_tog_layer_other_key_pressed = true; // always set this to true, TAP_TOG_LAYER handlers will handle interpreting this
      break;
  }
  return true;
}

// Runs constantly in the background, in a loop every 100ms or so.
// Best used for LED status output triggered when user isn't actively typing.
void matrix_scan_user(void) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer == 0) {
    // Set up LED indicators for stuck modifier keys.
    // https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/report.h#L118
    switch (keyboard_report->mods) {
      case MOD_BIT(KC_LSFT): // LSHIFT
        ergodox_right_led_1_set (LED_BRIGHTNESS_LO);
        ergodox_right_led_1_on ();
        ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
        ergodox_right_led_2_on ();
        ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
        ergodox_right_led_3_off ();
        break;

      case MOD_BIT(KC_LGUI): // LGUI
        ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
        ergodox_right_led_1_off ();
        ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
        ergodox_right_led_2_on ();
        ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
        ergodox_right_led_3_on ();
        break;

      case MOD_BIT(KC_LSFT) ^ MOD_BIT(KC_LGUI):
        ergodox_right_led_1_set (70);
        ergodox_right_led_1_on ();
        ergodox_right_led_2_set (70);
        ergodox_right_led_2_on ();
        ergodox_right_led_3_set (70);
        ergodox_right_led_3_on ();
        break;

      default: // reset leds
        ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
        ergodox_right_led_1_off ();
        ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
        ergodox_right_led_2_off ();
        ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
        ergodox_right_led_3_off ();
    }
  }
}

// only runs when when the layer is changed, good for updating LED's and clearing sticky state
layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  combo_enable(); // by default, enable combos.
  switch (layer) {
    case 0:
      break;
    case 1:
      clear_mods();
      ergodox_right_led_1_on();
      break;
    case 2:
      clear_mods();
      ergodox_right_led_2_on();
      break;
    case _OVERWATCH:
      clear_mods();
      combo_disable(); // We don't want combos in overwatch
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};
