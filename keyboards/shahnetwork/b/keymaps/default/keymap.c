#include QMK_KEYBOARD_H

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{6,5}, {5,5}, {4,5}, {3,5}, {2,5}, {1,5}, {0,5}},
    {{6,6}, {5,6}, {4,6}, {3,6}, {2,6}, {1,6}, {0,6}},
    {{6,7}, {5,7}, {4,7}, {3,7}, {2,7}, {1,7}, {0,7}},
    {{6,8}, {5,8}, {4,8}, {3,8}, {2,8}, {1,8}, {0,8}},
    {{6,9}, {5,9}, {4,9}, {3,9}, {2,9}, {1,9}, {0,9}},
    {{6,0}, {5,0}, {4,0}, {3,0}, {2,0}, {1,0}, {0,0}},
    {{6,1}, {5,1}, {4,1}, {3,1}, {2,1}, {1,1}, {0,1}},
    {{6,2}, {5,2}, {4,2}, {3,2}, {2,2}, {1,2}, {0,2}},
    {{6,3}, {5,3}, {4,3}, {3,3}, {2,3}, {1,3}, {0,3}},
    {{6,4}, {5,4}, {4,4}, {3,4}, {2,4}, {1,4}, {0,4}},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_5x7( // DWARF WIN
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINUS,
                KC_EQUAL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
        
        KC_TAB, KC_F, KC_L, KC_H, KC_D, KC_V, XXXXXXX,
                XXXXXXX, KC_Z, KC_G, KC_O, KC_U, KC_DOT, KC_BACKSPACE,
        
        OSM(MOD_LCTL), KC_S, KC_R, KC_N, KC_T, KC_M, KC_PAGE_UP,
                XXXXXXX, KC_P, KC_Y, KC_E, KC_I, KC_A, KC_SLASH,
        
        SC_LSPO, KC_X, KC_J, KC_B, KC_K, KC_Q, KC_PAGE_DOWN,
                XXXXXXX, KC_C, KC_W, KC_QUOTE, KC_COMMA, KC_SEMICOLON, SC_RSPC,
        
        KC_LCTL, KC_LGUI, KC_LALT, KC_BACKSPACE, XXXXXXX, LT(8, KC_ENT), OSL(4),
                OSL(5), KC_SPACE, TG(8), KC_BACKSPACE, KC_RALT, KC_RGUI, KC_RCTL
        
    ),
    
    [1] = LAYOUT_5x7( // QWERTY WIN
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINUS,
                KC_EQUAL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
        
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, XXXXXXX,
                XXXXXXX, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BACKSPACE,
        
        OSM(MOD_LCTL), KC_A, KC_S, KC_D, KC_F, KC_G, KC_PAGE_UP,
                XXXXXXX, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE,
        
        SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_PAGE_DOWN,
                XXXXXXX, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, SC_RSPC,
        
        KC_LCTL, KC_LGUI, KC_LALT, KC_BACKSPACE, XXXXXXX, LT(8, KC_ENT), OSL(4),
                OSL(5), KC_SPACE, TG(8), KC_BACKSPACE, KC_RALT, KC_RGUI, KC_RCTL
        
    ),
 
    [2] = LAYOUT_5x7(  // DWARF MAC
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINUS,
                KC_EQUAL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
        
        KC_TAB, KC_F, KC_L, KC_H, KC_D, KC_V, XXXXXXX,
                XXXXXXX, KC_Z, KC_G, KC_O, KC_U, KC_DOT, KC_BACKSPACE,
        
        OSM(MOD_LGUI), KC_S, KC_R, KC_N, KC_T, KC_M, KC_PAGE_UP,
                XXXXXXX, KC_P, KC_Y, KC_E, KC_I, KC_A, KC_SLASH,
        
        SC_LSPO, KC_X, KC_J, KC_B, KC_K, KC_Q, KC_PAGE_DOWN,
                XXXXXXX, KC_C, KC_W, KC_QUOTE, KC_COMMA, KC_SEMICOLON, SC_RSPC,
        
        KC_LCTL, KC_LALT, KC_LGUI, KC_BACKSPACE, XXXXXXX, LT(8, KC_ENT), OSL(6),
                OSL(7), KC_SPACE, TG(8), KC_BACKSPACE, KC_RGUI, KC_RALT, KC_RCTL
        
    ),
    
    [3] = LAYOUT_5x7( // QWERTY MAC
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINUS,
                KC_EQUAL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
        
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, XXXXXXX,
                XXXXXXX, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BACKSPACE,
        
        OSM(MOD_LGUI), KC_A, KC_S, KC_D, KC_F, KC_G, KC_PAGE_UP,
                XXXXXXX, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE,
        
        SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_PAGE_DOWN,
                XXXXXXX, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, SC_RSPC,
        
        KC_LCTL, KC_LALT, KC_LGUI, KC_BACKSPACE, XXXXXXX, LT(8, KC_ENT), OSL(6),
                OSL(7), KC_SPACE, TG(8), KC_BACKSPACE, KC_RGUI, KC_RALT, KC_RCTL
        
    ),
 
    [4] = LAYOUT_5x7( // LEFT WIN
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_ESC, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE, _______,
		        _______, KC_MPRV, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_MNXT,
		        
        _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_CAPS, _______,
		        _______, KC_DEL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
        
        _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), S(G(KC_S)), _______,
		        _______, KC_PSCR, KC_BSPC, KC_TAB, KC_ENT, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		        MO(9), _______, _______, _______, _______, _______, _______
        
    ),

 
    [5] = LAYOUT_5x7( // RIGHT WIN
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_TILD, _______,
		        _______, KC_CIRC, KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK, _______,
		        
        _______, KC_MINS, KC_ASTR, KC_EQL, KC_UNDS, KC_DLR, _______,
		        _______, KC_HASH, OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), _______,
        
        _______, KC_PLUS, KC_PIPE, KC_AT, KC_SLSH, KC_PERC, _______,
		        _______, KC_GRV, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM, _______,
        
        _______, _______, _______, _______, _______, _______, MO(9),
		_______, _______, _______, _______, _______, _______, _______
        
    ),


      [6] = LAYOUT_5x7( // LEFT MAC
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_ESC, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE, KC_BRIU,
		        _______, KC_MPRV, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_MNXT,
		        
        _______, OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LGUI), KC_CAPS, KC_BRID,
		        _______, KC_DEL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
        
        _______, G(KC_Z), G(KC_X), G(KC_C), G(KC_V), C(KC_UP), _______,
		        _______, _______, KC_BSPC, KC_TAB, KC_ENT, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		        MO(9), _______, _______, _______, _______, _______, _______
        
    ),


      [7] = LAYOUT_5x7( // RIGHT MAC
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_TILD, _______,
		        _______, KC_CIRC, KC_RPRN, KC_RBRC, KC_RCBR, KC_RABK, _______,
		        
        _______, KC_MINS, KC_ASTR, KC_EQL, KC_UNDS, KC_DLR, _______,
		        _______, KC_HASH, OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LCTL), _______,
        
        _______, KC_PLUS, KC_PIPE, KC_AT, KC_SLSH, KC_PERC, _______,
		        _______, KC_GRV, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM, _______,
        
        _______, _______, _______, _______, _______, _______, MO(9),
		_______, _______, _______, _______, _______, _______, _______
        
    ),

 
    [8] = LAYOUT_5x7( // NUMPAD
        _______, DF(0), DF(1), DF(2), DF(3), _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_F1, KC_F2, KC_F3, KC_F4, _______, _______,
		        _______, KC_COMMA, KC_7, KC_8, KC_9, KC_BSLS, _______,
		        
        _______, KC_F5, KC_F6, KC_F7, KC_F8, _______, _______,
		        _______, KC_BSPC, KC_4, KC_5, KC_6, KC_MINS, _______,
        
        _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
		        _______, KC_DOT, KC_1, KC_2, KC_3, KC_SLSH, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		        _______, KC_0, _______, _______, _______, _______, _______
        
    ),

  
    [9] = LAYOUT_5x7( // FUNCTION
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_UNDS,
		        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
		        
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS,
		        KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
        
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11,
		        KC_F12, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		        _______, _______, _______, _______, _______, _______, _______
        
    ),

 
    [10] = LAYOUT_5x7( // REPORTING
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_F, KC_L, KC_H, KC_D, KC_ESC, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, KC_6, KC_7, KC_8, KC_9, KC_0, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),

  
    [11] = LAYOUT_5x7( 
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),
    

     [12] = LAYOUT_5x7(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),
    

      [13] = LAYOUT_5x7(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),


      [14] = LAYOUT_5x7(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),
    

      [15] = LAYOUT_5x7(
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
		        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,
        
        _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______
        
    ),
  

};

// Workaround for https://github.com/qmk/qmk_firmware/issues/16406
void suspend_wakeup_init_user(void) {
    NVIC_SystemReset();
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
	    // Host Keyboard Layer Status
	    oled_write_P(PSTR("Layer: "), false);

	    switch (get_highest_layer(layer_state)) {
		case 0:
		    oled_write_P(PSTR("0\n"), false);
		    break;
		case 1:
		    oled_write_P(PSTR("1\n"), false);
		    break;
		case 2:
		    oled_write_P(PSTR("2\n"), false);
		    break;
		case 3:
		    oled_write_P(PSTR("3\n"), false);
		    break;
		case 4:
		    oled_write_P(PSTR("4\n"), false);
		    break;
		case 5:
		    oled_write_P(PSTR("5\n"), false);
		    break;
		case 6:
		    oled_write_P(PSTR("6\n"), false);
		    break;
		case 7:
		    oled_write_P(PSTR("7\n"), false);
		    break;
		case 8:
		    oled_write_P(PSTR("8\n"), false);
		    break;
		case 9:
		    oled_write_P(PSTR("9\n"), false);
		    break;
		case 10:
		    oled_write_P(PSTR("10\n"), false);
		    break;
		case 11:
		    oled_write_P(PSTR("11\n"), false);
		    break;
		case 12:
		    oled_write_P(PSTR("12\n"), false);
		    break;
		case 13:
		    oled_write_P(PSTR("13\n"), false);
		    break;
		case 14:
		    oled_write_P(PSTR("14\n"), false);
		    break;
		case 15:
		    oled_write_P(PSTR("15\n"), false);
		    break;
		default:
		    // Or use the write_ln shortcut over adding '\n' to the end of your string
		    oled_write_ln_P(PSTR("Undefined"), false);
	    }

	    // Host Keyboard LED Status
	    led_t led_state = host_keyboard_led_state();
	    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
	    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
	    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	    
	    return false;
    } else {
	    oled_write_P(PSTR("Broken Keyboard\n  SHAHNETWORK"), false);
            oled_scroll_left();  // Turns on scrolling
    }
    return false;
}
#endif

