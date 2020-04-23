#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_65_ansi_blocker(
		KC_ESC,  	KC_1, 		KC_2, 		KC_3, 	 KC_4, 	  KC_5,     KC_6, 	         KC_7, 				KC_8,    KC_9,    KC_0, 	  KC_MINS, 	KC_EQL, 	KC_BSPC, 	KC_DEL,	  \
		KC_TAB,  	KC_Q, 		KC_W, 		KC_E, 	 KC_R, 	  KC_T,     KC_Y, 	         KC_U, 				KC_I,    KC_O,    KC_P, 	  KC_LBRC, 	KC_RBRC, 	KC_BSLS, 	KC_HOME,  \
		KC_CAPS, 	KC_A, 		KC_S, 		KC_D, 	 KC_F, 	  KC_G,     KC_H, 	         KC_J, 				KC_K,    KC_L,    KC_SCLN,    KC_QUOT, 				KC_ENT, 	KC_PGUP,  \
		KC_LSFT, 	KC_Z,   	KC_X,     	KC_C,    KC_V,    KC_B,     KC_N,            KC_M,  			KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,   			KC_UP, 		KC_PGDN,  \
		KC_LCTL, 	KC_LGUI,	KC_LALT, 				                KC_SPC, 	     					          		  MO(2),      MO(1), 	KC_LEFT,  	KC_DOWN,   	KC_RGHT   \
		),
	[1] = LAYOUT_65_ansi_blocker(
		KC_GRV,  	KC_F1,  	KC_F2,    	KC_F3, 	 KC_F4,   KC_F5,    KC_F6,           KC_F7,      		KC_F8,   KC_F9,   KC_F10,     KC_F11,   KC_F12,     _______,    KC_MUTE,  \
		_______, 	_______,	_______,  _______, 	 _______, _______,  _______,         _______,    		_______, _______, KC_PSCR,    KC_SLCK,  KC_PAUS,    _______,    KC_MPLY,  \
		_______, 	_______,	_______,  _______, 	 _______, _______,  _______,         _______,    		_______, _______, _______,    _______,  			_______,    KC_MFFD,  \
		_______, 	_______,	_______,  _______, 	 _______, _______,  _______,         _______,    		_______, _______, _______,    _______, 				KC_VOLU,    KC_MRWD,  \
		_______, 	_______,	_______, 				 				_______,  	     									  _______,    ______,   KC_HOME,    KC_VOLD,    KC_END    \
		),
	[2] = LAYOUT_65_ansi_blocker(
		_______, 	_______,	_______,  _______, 	 _______, _______,  _______,         _______,    		_______, _______, _______,	  RGB_RMOD, RGB_MOD,    _______,    KC_CALC,  \
		RGB_TOG, 	_______,	RGB_HUI,  _______, 	 _______, _______,  _______,         _______,    		_______, _______, _______,    _______,    			_______,  	KC_MYCM,  \
		RGB_M_P, 	RGB_SAD,	RGB_HUD,  RGB_SAI, 	 _______, _______,  _______,         _______,    		_______, _______, _______,    _______,    			_______,  	KC_WSCH,  \
		_______, 	_______,	_______,  _______, 	 _______, RESET,    MAGIC_HOST_NKRO, MAGIC_UNHOST_NKRO, _______, _______, _______, 	  _______,  			RGB_VAI,    _______,  \
		_______, _______, _______, 										_______, 											  _______, 	  _______,  RGB_SPD, 	RGB_VAD, 	RGB_SPI   \
		)
};
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL   (get_mods() & MOD_BIT(KC_LCTL)   || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT    (get_mods() & MOD_BIT(KC_LALT)   || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
