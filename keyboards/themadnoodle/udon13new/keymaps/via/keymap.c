// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Layer Names */
enum layers {
    _ZERO,
    _ONE,
    _TWO,
    _THREE
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*Layer 0*/
    [_ZERO] = LAYOUT_ortho_3x4(
  	KC_MUTE, 
		KC_MPLY, KC_MPRV, KC_MNXT, KC_MSEL, 
		KC_UNDO, KC_CALC, KC_MAIL, KC_MYCM, 
		KC_COPY, KC_CUT, KC_PSTE, TO(_THREE)
        ),

/*Layer 1*/
    [_ONE] = LAYOUT_ortho_3x4(
		RGB_TOG, 
		RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, 
		RGB_MOD, RGB_RMOD, RGB_M_P, RGB_M_B, 
		RGB_M_SW, RGB_SPD, RGB_SPI, TO(_ZERO)
        ),

/*Layer 2*/ 
    [_TWO] = LAYOUT_ortho_3x4(
		KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, TO(_ZERO)
        ),

/*Layer 3*/       
    [_THREE] = LAYOUT_ortho_3x4(
		KC_NO, 
		TO(_ONE), TO(_TWO), KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, KC_NO, 
		KC_NO, KC_NO, KC_NO, TO(_ZERO)
        ),

};

/*Encoder Mapping*/
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  {ENCODER_CCW_CW(KC_VOLD,  KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [2] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [3] =  { ENCODER_CCW_CW(KC_DOWN,   KC_UP)},
   
};
#endif



#ifdef OLED_ENABLE

/* OLED Settings */
//------------------------------------------------------------------------------------------------

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;  // flips the display 180 degrees if offhand
}
 

static void render_logo(void) {     // Render Mad Noodle logo
    static const char PROGMEM logo_1[] = {0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x06, 0x82, 0xc3, 0x43, 0x61, 0xa1, 0xa1,0xa1, 0xa1, 0x61, 0x43, 0xc3, 0x82, 0x06, 0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00};
    static const char PROGMEM logo_2[] = {0xf8, 0x1e, 0xc3, 0xf8, 0x5c, 0x76, 0x7b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x6d, 0x7b, 0x76, 0x5e,0x7e, 0x77, 0x5b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x4d, 0x7b, 0x66, 0x5c, 0xf0, 0xc3, 0x3e, 0xf0};
    static const char PROGMEM logo_3[] = {0x1f, 0x78, 0xc1, 0x0f, 0x38, 0xe0, 0xc0, 0x00, 0x00, 0x02, 0x0e, 0x0e, 0x8e, 0xc6, 0xc0, 0x40,0x40, 0xc0, 0xc6, 0x8e, 0x0e, 0x0e, 0x02, 0x00, 0x80, 0xc0, 0x60, 0x38, 0x0f, 0xc0, 0x7c, 0x0f};
    static const char PROGMEM logo_4[] = {0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x31, 0x23, 0x66, 0x44, 0x44, 0xc4, 0xc4, 0x84, 0x84,0x84, 0x84, 0xc4, 0xc4, 0x44, 0x46, 0x66, 0x23, 0x11, 0x18, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00};
    oled_set_cursor(0,0);
    oled_write_raw_P(logo_1, sizeof(logo_1));
    oled_set_cursor(0,1);
    oled_write_raw_P(logo_2, sizeof(logo_2));
    oled_set_cursor(0,2);
    oled_write_raw_P(logo_3, sizeof(logo_3));
    oled_set_cursor(0,3);
    oled_write_raw_P(logo_4, sizeof(logo_4));
}
//-----------



bool oled_task_user(void) {

    
    render_logo();
    oled_set_cursor(7,0);
    oled_write_P(PSTR("The Mad Noodle"), false);

    oled_set_cursor(7,1);
    oled_write_P(PSTR("Layer: "), false);

/* 
To chage LAYER NAMES displayed on the OLED ensure they are a total of 6 charaters, including spaces.
Example:
---------------------------------------------------
case _ZERO:
      oled_write_P(PSTR("Base  "), false);
      break;
---------------------------------------------------
"B A S E *SPACE* *SPACE*" = 6 characters
This would change layer _ZERO to Base on the OLED
*/

   switch (get_highest_layer(layer_state)) {
    case _ZERO:
      oled_write_P(PSTR("Zero  "), false);
      break;
    case _ONE:
      oled_write_P(PSTR("One   "), false);
      break;
    case _TWO:
      oled_write_P(PSTR("Two   "), false);
      break;      
    case _THREE:
      oled_write_P(PSTR("Three "), false);
      break; 
    
    
    default:
      oled_write_P(PSTR("N/A "), false);
  }
  	oled_set_cursor(7,2);
    oled_write_P(PSTR("Status: "), false);
    oled_set_cursor(7,3);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("   "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("   "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("   "), false);

return false;
}

#endif