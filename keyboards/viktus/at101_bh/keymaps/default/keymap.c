#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 				KC_PSCR,KC_SCRL, KC_PAUS,
		KC_GRV, KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,   KC_MINS,KC_EQL, KC_BSPC,		KC_INS, KC_HOME, KC_PGUP, 		KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
		KC_TAB, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, 	KC_DEL, KC_END,  KC_PGDN, 		KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
		KC_CAPS,KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K, 	KC_L,  KC_SCLN,KC_QUOT,KC_ENT, 												KC_P4, 	 KC_P5,   KC_P6,   KC_PEQL,
		KC_LSFT,KC_BSLS,KC_Z, KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_LSFT,MO(1), 				KC_UP, 					KC_P1,   KC_P2,   KC_P3,   KC_PENT,
		KC_LCTL,KC_LGUI,KC_LALT, 			KC_SPC,				 		KC_RALT, KC_RGUI,KC_MENU, KC_RCTL,			KC_LEFT,KC_DOWN, KC_RGHT,			KC_P0,		  KC_PDOT),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 			KC_TRNS, KC_TRNS, KC_TRNS, 			  
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 	KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 	KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					 						KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 			 KC_TRNS, 				KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 					 KC_TRNS, 							 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 	KC_TRNS, KC_TRNS, KC_TRNS,			KC_TRNS, 	  KC_TRNS),
};

bool led_update_user(led_t led_state) {
  gpio_set_pin_output(B4);
  gpio_set_pin_output(D6);
  gpio_set_pin_output(D7);

  if (led_state.num_lock) {
    gpio_write_pin_high(D7);
  } else {
    gpio_write_pin_low(D7);
  }

  if (led_state.caps_lock) {
    gpio_write_pin_high(B4);
  } else {
    gpio_write_pin_low(B4);
  }

  if (led_state.scroll_lock) {
    gpio_write_pin_high(D6);
  } else {
    gpio_write_pin_low(D6);
  }
  return false;
}
