
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_brutal(
    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,KC_QUOT, //Y+QUOTE = KC_BSPC
    LGUI_T(KC_A), LALT_T(KC_R),     LCTL_T(KC_S),     LSFT_T(KC_T),     KC_D,     KC_H,     RSFT_T(KC_N),     RCTL_T(KC_E),     RALT_T(KC_I),     RGUI_T(KC_O),
    KC_Z_SF,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
    KC_ENT, KC_NUM_SPC, KC_NAV_ENT
  ),

  [_NUM_SYM] = LAYOUT_brutal(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0, //0 + 9 = KC_BSPC
    KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_EQL,  KC_MINS,
    KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,   KC_UNDS, KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_DOT,  KC_GRV,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT_brutal(
    RESET,   RGBRST,  AG_NORM,  AG_SWAP,  DEBUG,  KC_GRV ,KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  SPONGEBOB,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  AESTHETIC,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_BSLS,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),
};

#ifdef RGBLIGHT_ENABLE
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {100, 30, 5, 1};

void keyboard_post_init_user(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  // Init the LEDs to a static color
  setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
  setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
  rgblight_set();
}

uint32_t layer_state_set_keymap(uint32_t state){
  uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
  uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
  if (layer_state_cmp(state, _NUM_SYM)) {
    led0r = 25;
    led0g = 25;
  }
  if (layer_state_cmp(state, _NAV)) {
    led1g = 25;
    led1b = 25;
  }

  if (layer_state_cmp(state, _FKEY)) {
    led0b = 25;
    led0r = 25;
    led1b = 25;
    led1r = 25;
  }

  setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
  setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
  rgblight_set();

  return state;
}

bool led_update_kb(led_t led_state){
  if(led_state.caps_lock){
    rgblight_set_effect_range(2, 1);
    rgblight_sethsv_noeeprom(180, 200, 150);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_set();
  } else{
    rgblight_set_effect_range(2, 1);
    rgblight_sethsv_noeeprom(180, 200, 0);
    rgblight_set();
  }
  return true;
}
#endif //RGBLIGHT_ENABLE
