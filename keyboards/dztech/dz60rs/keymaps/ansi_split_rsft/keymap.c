#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_LAYER0] = LAYOUT_60_ansi_split_rsft(
	KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  
	KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_BSPC,
	KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
	KC_LCTL,  KC_LGUI, KC_LALT, KC_NO,                              KC_SPC,  KC_NO,   KC_RALT, MO(1),   KC_RGUI, KC_RCTL),
 [_LAYER1] = LAYOUT_60_ansi_split_rsft(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,             KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  
	KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, RESET, 
	KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_INS,  KC_HOME, KC_PGUP, EEP_RST, KC_DEL,
	KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MAGIC_TOGGLE_NKRO, KC_TRNS, KC_DEL,  KC_END,  KC_PGDN, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,                              KC_TRNS,           KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
 [_LAYER2] = LAYOUT_60_ansi_split_rsft(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EEP_RST, KC_TRNS,
	KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,                              KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
void rgb_matrix_indicators_user(void)
{
	    if (IS_LED_ON(host_keyboard_leds(), USB_LED_CAPS_LOCK))
	    {
	      rgb_matrix_set_color(28, 0xFF, 0x00, 0x00);
	    }
}

void matrix_init_user(void)
{
  //user initialization
}

void matrix_scan_user(void)
{
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	  return true;
}
