#include QMK_KEYBOARD_H
#include "xtonhasvim.h"

enum layers {
  _QWERTY,
  _FUN,
  _MOVE,
  _MOUSE,
  _CMD
};

extern uint8_t vim_cmd_layer(void) { return _CMD; }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
	  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(_MOVE,KC_SCLN), KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO,
		LSFT(KC_LALT), KC_LALT, KC_LGUI, VIM_START, TG(_MOUSE), KC_SPC, KC_RGUI, KC_RALT, X_____X, KC_RCTL, MO(_FUN)),

	[_FUN] = LAYOUT(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_DEL,
		_______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, RESET,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, BL_STEP, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY)),

	[_MOVE] = LAYOUT(
		X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X,
		X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, KC_HOME, KC_PGDN, KC_PGUP, KC_END, X_____X, X_____X, X_____X, X_____X,
		X_____X, X_____X, LGUI(KC_LBRC), LGUI(LSFT(KC_LBRC)), LGUI(LSFT(KC_RBRC)), LGUI(KC_RBRC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, X_____X, X_____X, X_____X,
		_______, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY)),


	[_MOUSE] = LAYOUT(
		X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X,
		X_____X, X_____X, X_____X, KC_MS_UP, X_____X, X_____X, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, X_____X, X_____X, X_____X, X_____X,
		X_____X, X_____X,KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, X_____X, X_____X, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, X_____X, X_____X, X_____X,
		_______, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY)),

	[_CMD] = LAYOUT(
		X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X,
		X_____X, X_____X, VIM_W, VIM_E, X_____X, X_____X, VIM_Y, VIM_U, VIM_I, VIM_O, VIM_P, X_____X, X_____X, X_____X,
		VIM_ESC,   VIM_A, VIM_S, VIM_D, X_____X, VIM_G, VIM_H, VIM_J, VIM_K, VIM_L, X_____X, X_____X, X_____X,
		VIM_SHIFT,     X_____X, X_____X, VIM_X, VIM_C, VIM_V, VIM_B, X_____X, X_____X, VIM_COMMA, VIM_PERIOD, X_____X, VIM_SHIFT,X_____X,
		_______, _______, _______, TO(_QWERTY), X_____X, X_____X, _______, _______, _______, _______, TO(_QWERTY)),

};

#define LED_BIT 1 << 2
#define LED_MASK ~(1 << 2)

void user_led_on(void) {
  DDRB |= LED_BIT;
  PORTB &= LED_MASK;
}

void user_led_off(void) {
  DDRB &= ~LED_BIT;
  PORTB &= LED_MASK;
}

void matrix_init_user(void) {
  user_led_off();
}

uint32_t layer_state_set_user(uint32_t state) {
  static uint32_t last_state = 0;

  if(last_state != state) {
    switch (biton32(state)) {
    case _CMD:
      user_led_on();
      break;
    default:
      user_led_off();
      break;
    }
    last_state = state;
  }
  return state;
}


