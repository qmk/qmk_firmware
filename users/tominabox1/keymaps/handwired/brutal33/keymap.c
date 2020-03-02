
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tominabox1.h"
#define RGBLIGHT_EFFECT_BREATHING

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_brutal_wrap(
	KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
	_______________HOMEROW_MOD_________________,
	_______________COLEMAK3____________________,
    KC_NAV_ENT, KC_NUM_SPC, KC_NAV_ENT
  ),

  [_NUM_SYM] = LAYOUT_brutal_wrap(
	__________________NUM_1____________________,
	__________________NUM_2____________________,
	KC_BSLS, __________________NUM_3____________________, KC_DOT, KC_GRV,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT_brutal(
    RESET,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
    SPONGEBOB,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    AESTHETIC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_COMM,   KC_DOT,  KC_BSLS,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),
  
  [_GAME] = LAYOUT_brutal(
	KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_L, KC_U, KC_Y, TO(_BASE),
	KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_N, KC_E, KC_I, KC_O,
	KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_M, KC_COMM, KC_DOT, KC_SLSH,
    KC_LSFT, KC_SPACE, KC_NAV_ENT
  ),
};

#ifdef RGBLIGHT_ENABLE 
void keyboard_post_init_keymap(void) {
  #ifdef RGBLIGHT_ENABLE
    eeconfig_init();
    setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
	setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
} 

uint32_t layer_state_set_keymap(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;
	uint8_t led2r = 0; uint8_t led2g = 0; uint8_t led2b = 0;

    if (layer_state_cmp(state, 0)) {
      led2g = 255;
    }

    if (layer_state_cmp(state, 1)) {
      led0g = 255;
    }

    if (layer_state_cmp(state, 5)) {
      led1b = 255;
    }
	
    if (layer_state_cmp(state, 7)) {
      led1r = 255;
	  led1b = 255;
    }

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
    setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
	setrgb(led2r, led2g, led2b, (LED_TYPE *)&led[2]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}

#endif //RGBLIGHT_ENABLE
