
#include QMK_KEYBOARD_H
#include "version.h"
#include "rishka.h"
enum layers {
  BASE, // default layer
  WIN, // Switch keys that are needed in windows
  SYMB, // symbols
  MDIA, // media keys
  GAME, // Gamepad setup
  FIRMWARE // Layer to trigger reset/refresh
};
enum custom_keycodes {
  VRSN = SAFE_RANGE,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox_pretty_wrapper(
  KC_EQL,  ________________NUMBERS_L__________________, TG(WIN),       OSX_LOCK, ________________NUMBERS_R__________________, KC_MINS,
  KC_DEL,  _________________QWERTY_L1_________________, TG(SYMB),      TG(SYMB), _________________QWERTY_R1_________________, KC_BSLS,
  KC_BSPC, _____________MOD_QWERTY_L2_________________,                          _____________MOD_QWERTY_R2_________________, LT(MDIA, KC_QUOT),
  OS_LSFT, _________________QWERTY_L3_________________, ALL_T(KC_NO),  TG(MDIA), _________________QWERTY_R3_________________, OS_RSFT,
  LT(SYMB,KC_GRV), KC_QUOT, LALT(KC_LSFT), KC_LEFT, KC_RGHT,                        KC_UP,   KC_DOWN, KC_LBRC,  KC_RBRC,        OSL(SYMB),
                                           ALT_T(KC_APP), TG(GAME),       KC_LALT,         CTL_T(KC_ESC),
                                            LT(FIRMWARE, KC_HOME),        KC_PGUP,
                            KC_SPC, GUI_T(KC_BSPC), ALT_T(KC_END),        GUI_T(KC_PGDN),  CTL_T(KC_TAB), ALT_T(KC_ENT)
),

[WIN] = LAYOUT_ergodox_pretty_wrapper(
  _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  KC_F1,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  KC_TAB,  _________________QWERTY_L2_________________,                       _______, _______, _______, _______, _______, _______,
  _______, _______,    _______, _______, _______, _______, KC_LGUI,  _______, _______, _______, _______, _______, _______, _______,
  KC_LCTL, _______, KC_LALT, _______, _______,                                         _______, _______, _______, _______, _______,
                                               _______, KC_ESC,      _______, _______,
                                                        _______,     _______,
                                      _______, KC_BSPC, KC_LALT,     KC_PGDN, CTL_T(KC_TAB), _______
),

[SYMB] = LAYOUT_ergodox_pretty_wrapper(
VRSN,    ______________________F_L__________________, KC_F11,       KC_F12 , ______________________F_R__________________, KC_NUM,
_______, _________________SYMBOL_L1_________________, _______,      _______, _________________SYMBOL_R1_________________, _______,
_______, _________________SYMBOL_L2_________________,                        _________________SYMBOL_R2_________________, _______,
_______, _________________SYMBOL_L3_________________, _______,      _______, _________________SYMBOL_R3_________________, _______,
_______, _______, _______, _______, _______,                                          _______, KC_P0, KC_PDOT, KC_PSLS, _______,
                                               RGB_MOD, RGB_VAI,   RGB_HUI, RGB_SLD,
                                                        RGB_VAD,   RGB_HUD,
                                      _______, _______, _______,   RGB_TOG, _______, _______
),

[MDIA] = LAYOUT_ergodox(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_MS_U, _______, KC_WH_U, _______,
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_BTN1, KC_BTN2,
                                               _______, KC_BTN5,
                                                        KC_BTN4,
                                      KC_BTN1, KC_BTN2, KC_BTN3,
  // right hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_WH_U, _______, _______, _______,
           _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, KC_MPLY,
  _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                    KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
  _______, _______,
  _______,
  KC_ACL2, KC_ACL1, KC_ACL0
),

[GAME] = LAYOUT_ergodox(
  // left hand
  KC_ESCAPE, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5,
  KC_F1, KC_Y, KC_Q, KC_W, KC_E, KC_R, KC_T,
  KC_TAB, KC_LSFT, KC_A, KC_S, KC_D, KC_F,
  KC_LCTL, KC_B, KC_Z, KC_X, KC_C, KC_V, KC_G,
  LT(BASE, KC_L), KC_J, KC_I, KC_O, KC_M,
                                               KC_ESCAPE, _______,
                                                        KC_ENTER,
                                      KC_SPACE, KC_LCTL, KC_LALT,
 // right hand
  KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_MINS,
  TG(SYMB),     KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSLS,
  KC_H,         KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), GUI_T(KC_QUOT),
  MEH_T(KC_NO), KC_N,    KC_M,    KC_COMM, KC_DOT,            CTL_T(KC_SLSH), KC_RSFT,
  KC_UP,        KC_DOWN, KC_LBRC, KC_RBRC, TT(SYMB),
  KC_LALT, CTL_T(KC_ESC),
  KC_PGUP,
  KC_PGDN, KC_TAB, KC_ENT
),

[FIRMWARE] = LAYOUT_ergodox(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,
                                               _______, _______,
                                                        _______,
                                      QK_BOOT, _______, _______,
  // right hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,
  _______, _______,
  _______,
  _______, _______, EE_CLR
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
