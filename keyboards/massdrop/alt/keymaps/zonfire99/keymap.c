#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
	QMKBEST,
	L_BRI,
	L_BRD,
};

   


  





keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                           KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, L_BRI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END, \
        RGB_M_B, RGB_RMOD,L_BRD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        KC_ASTG, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            LCTL(LGUI(KC_Q)), _______, KC_HOME, KC_PGDN, KC_END  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {

		case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                //if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                //if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
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
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
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
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
			case QMKBEST:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING("this is a poop emoji");
			} else {
				// when keycode QMKBEST is released
			}
      		return false;
        default:
            return true; //Process all other keycodes normally
    }
}

/*
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

void rgb_matrix_indicators_user(void)
{
	uint8_t this_led = host_keyboard_leds();

	if (!g_suspend_state && rgb_matrix_config.enable) {
		switch (biton32(layer_state)) {
		case 0:
			rgb_matrix_layer_helper(0xFF, 0x00, 0x00); break;

		case 1:
			rgb_matrix_layer_helper(0x00, 0xFF, 0x00); break;
		}
	}

	if (this_led & (1 << USB_LED_CAPS_LOCK)) {
			rgb_matrix_set_color(30, 0xFF, 0x00, 0x00);
		} else {
			rgb_matrix_set_color(30, 0xFF, 0x00, 0xFF);
		}

	switch (biton32(layer_state)) {
	case 0:
		//if (this_led & (1 << USB_LED_NUM_LOCK)) {
		//	rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
		//} else {
		//	rgb_matrix_set_color(13, 0xFF, 0xFF, 0xFF);
		//}
		
        
		
		rgb_matrix_set_color(0, 0xFF, 0x00, 0x00); //row 1 
		rgb_matrix_set_color(1, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(2, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(3, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(4, 0x00, 0xFF, 0x00);

		rgb_matrix_set_color(5, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(6, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(7, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(8, 0x00, 0xFF, 0x00);
		
		rgb_matrix_set_color(9, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(10, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(11, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(12, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(13, 0xFF, 0x00, 0x00);
		rgb_matrix_set_color(14, 0xFF, 0x00, 0xFF);


		rgb_matrix_set_color(15, 0xFF, 0x00, 0xFF); //row 2
		rgb_matrix_set_color(16, 0x00, 0xFF, 0x00); 
		rgb_matrix_set_color(17, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(18, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(19, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(20, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(21, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(22, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(23, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(24, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(25, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(26, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(27, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(28, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(29, 0xFF, 0x00, 0xFF);
		
		//rgb_matrix_set_color(30, 0xFF, 0x00, 0xFF);//row 3
		rgb_matrix_set_color(31, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(32, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(33, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(34, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(35, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(36, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(37, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(38, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(39, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(40, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(41, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(42, 0xFF, 0x00, 0x00);
		rgb_matrix_set_color(43, 0xFF, 0x00, 0xFF);

		rgb_matrix_set_color(44, 0xFF, 0x00, 0xFF);//row 4
		rgb_matrix_set_color(45, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(46, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(47, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(48, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(49, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(50, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(51, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(52, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(53, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(54, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(55, 0x00, 0xFF, 0x00);
		//rgb_matrix_set_color(56, 0xFF, 0xFF, 0xFF);

		rgb_matrix_set_color(57, 0xFF, 0x00, 0xFF);//row 5
		rgb_matrix_set_color(58, 0xFF, 0x00, 0xFF);
		rgb_matrix_set_color(59, 0xFF, 0x00, 0xFF);
		rgb_matrix_set_color(60, 0xFF, 0x00, 0xFF);
		rgb_matrix_set_color(61, 0xFF, 0x00, 0xFF);
		rgb_matrix_set_color(62, 0xFF, 0x00, 0xFF);
		rgb_matrix_set_color(63, 0xFF, 0x00, 0xFF);
		
		//arrow keys
		rgb_matrix_set_color(56, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(64, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(65, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(66, 0x00, 0xFF, 0x00);
		//arrow keys
		
		//edge corners
		rgb_matrix_set_color(100, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(86, 0xFF, 0xFF, 0xFF);
		//rgb_matrix_set_color(67, 0x00, 0xFF, 0x00);
		//rgb_matrix_set_color(81, 0x00, 0xFF, 0x00);
		//edge corners
		

		
		//front edge
		rgb_matrix_set_color(68, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(69, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(70, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(71, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(72, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(73, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(74, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(75, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(76, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(77, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(78, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(79, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(80, 0xFF, 0xFF, 0xFF);
		//front edge
		
		//left edge
		rgb_matrix_set_color(101, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(102, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(103, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(104, 0x00, 0xFF, 0x00);
		//left edge
		
		//right edge
		rgb_matrix_set_color(85, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(84, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(83, 0x00, 0xFF, 0x00);
		rgb_matrix_set_color(82, 0x00, 0xFF, 0x00);
		//right edge
		
		//back edge
		rgb_matrix_set_color(87, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(88, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(89, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(90, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(91, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(92, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(93, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(94, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(95, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(96, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(97, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(98, 0xFF, 0xFF, 0xFF);
		rgb_matrix_set_color(99, 0xFF, 0xFF, 0xFF);
		//back edge

		break;
	}
}
*/




//void matrix_init_user(void)
//{
	//user initialization
//}

//void matrix_scan_user(void)
//{
	//user matrix
//}

//bool process_record_user(uint16_t keycode, keyrecord_t* record)
//{
//	return true;
//}