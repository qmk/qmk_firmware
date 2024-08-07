/* Copyright 2020 qmk */

#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 	0
#define _F_TRPT 	1
#define _SYMB   	2
#define _MOUSE 		3
#define _ADJUST 	5
#define _ARROW 		4

#ifdef TAP_DANCE_ENABLE
int cur_dance (tap_dance_state_t *state);
//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (tap_dance_state_t *state, void *user_data);
void x_reset (tap_dance_state_t *state, void *user_data);
#endif


#ifdef RGB_MATRIX_ENABLE
HSV color_my;
HSV color1 = {HSV_TURQUOISE}; 
HSV color2 = {HSV_YELLOW};
HSV color3 = {HSV_PINK};
HSV color4 = {HSV_GREEN};
HSV color5 = {HSV_RED};
HSV hsv_Orang = {HSV_ORANGE};
RGB color_my_rgb;
#endif

///////////////////////////////////////////////////
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  F4_HOLD = 0,
};




////////////////////////////////////////////////////


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
  F_TRPT,
  RGB_MyEFF,
};







bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

#ifdef RGB_MATRIX_ENABLE
	uint8_t layer = get_highest_layer(layer_state);	
	
	// определчем цвета

	// получаем яркость
	color1.v = rgb_matrix_get_val();
	color2.v = rgb_matrix_get_val();
	color3.v = rgb_matrix_get_val();
	color4.v = rgb_matrix_get_val();
	color_my.v= rgb_matrix_get_val();
	hsv_Orang.v = rgb_matrix_get_val();
	// переводим в rgb
	//RGB color1_rgb = hsv_to_rgb(color1);
	//RGB color2_rgb = hsv_to_rgb(color2);
	//RGB color3_rgb = hsv_to_rgb(color3);
	//RGB color4_rgb = hsv_to_rgb(color4);

	
	 if (get_highest_layer(layer_state) > 0) {

 			
    	switch (get_highest_layer(layer_state)) {
        	case 1:
        		color_my_rgb   = hsv_to_rgb(color1);
        		break;
        	case 2:
        		color_my_rgb   = hsv_to_rgb(color2);
        		break;
        	case 3:
        		color_my_rgb   = hsv_to_rgb(color3);
        		break;
        	case 4:
        		color_my_rgb   = hsv_to_rgb(color4);
        		break;
        	case 5:
        		color_my_rgb   = hsv_to_rgb(color5);
        		break;
        }
    	

		
		if (get_highest_layer(layer_state) == 5)  {
		
			for (uint8_t i = led_min; i <= 34; i++) 
			{
			        rgb_matrix_set_color(i, RGB_OFF);
			}
		}
		else
		{
			for (uint8_t i = led_min; i <= led_max; i++) 
			{
			        rgb_matrix_set_color(i, RGB_OFF);
			}
		}
    	
    	
        
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) 
        {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) 
            {
                uint8_t index = g_led_config.matrix_co[row][col];

				switch (layer) {
					case 5:
                		if (index >= led_min && index <= 34 && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS ) 
                		{
        					rgb_matrix_set_color(index, color_my_rgb.r, color_my_rgb.g, color_my_rgb.b);
            			}
					break;
					default:
                		if (index >= led_min && index <= led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS ) 
                		{
        					rgb_matrix_set_color(index, color_my_rgb.r, color_my_rgb.g, color_my_rgb.b);

            			}
            		}
            }
        
        }
    }
    
        if (host_keyboard_led_state().caps_lock) 
        {
        	RGB orange_1 = hsv_to_rgb(hsv_Orang);
        	rgb_matrix_set_color(14, orange_1.r, orange_1.g, orange_1.b);
    	}
    	
        if (host_keyboard_led_state().num_lock) // Num Lock status
        {
            
            if (layer == 4)  { // is layer arrow
            
            RGB orange_1 = hsv_to_rgb(hsv_Orang);
            rgb_matrix_set_color(48 , orange_1.r, orange_1.g, orange_1.b);
            }
        }



    	#endif
   return true;
}

void keyboard_post_init_user(void) {

//       for (uint8_t row = 0; row < MATRIX_ROWS; ++row) 
//       {
//           for (uint8_t col = 0; col < MATRIX_COLS; ++col) 
//           {
//               uint8_t index = g_led_config.matrix_co[row][col];

//                       if (index >= led_min && index <= led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS ) 
//                       {
//                           rgb_matrix_set_color(index, color_my_rgb.r, color_my_rgb.g, color_my_rgb.b);

//                       }
//                   
//           }
//       
//       }

    //rgb_matrix_sethsv_noeeprom(HSV_OFF);
    //rgb_matrix_set_color_all(45, 45, 45);
}








void suspend_power_down_user(void) {
	#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
    #endif
}

void suspend_wakeup_init_user(void) {
	#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
    #endif
    //NVIC_SystemReset();
}



// Shortcut to make keymap more readable
#define SYM_L   LT(_SYMB, KC_CAPS)
#define ADJT   MO(_ADJUST)
#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_F4_HOLD (KC_BSLS)

#define KC_NAGR LT(_MOUSE, KC_SPC)
#define KC_NAMI LT(_MOUSE, KC_MINS)

#define KC_ADEN LT(_ARROW, KC_SPC)
#define KC_ADPU LT(_ADJUST, KC_PGUP)





bool process_record_user(uint16_t keycode, keyrecord_t *record ) {

    switch (keycode) {
        case RGB_MyEFF:
        	#ifdef RGB_MATRIX_ENABLE
				rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
                return true; 
			#endif
        #ifdef TAP_DANCE_ENABLE
                        // Return true for normal processing of tap keycode
        case LT(0,KC_1):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F1); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_2):
            if (!record->tap.count && record->event.pressed) {
                tap_code16((KC_F2)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_3):
            if (!record->tap.count && record->event.pressed) {
                tap_code16((KC_F3)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_5):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F5); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_6):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F6); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_7):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F7); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_8):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F8); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_9):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F9); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_0):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_F10); // Intercept hold function to send Ctrl-X
                return false;
            }
            #endif
            return true;             // Return true for normal processing of tap keycode


    }
     	
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
    
    
  return true;
}


 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


#ifdef TAP_DANCE_ENABLE

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐────────┐                         ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,LT(0,KC_1),LT(0,KC_2),LT(0,KC_3),TD(F4_HOLD),LT(0,KC_5),LT(0,KC_6),       LT(0,KC_7), LT(0,KC_8),LT(0,KC_9), LT(0,KC_0),KC_MINS, KC_EQL, KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q     ,KC_W    ,KC_E    ,KC_R    ,KC_T   ,KC_PGUP ,                KC_HOME ,  KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      SYM_L  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_PGDN ,                KC_END , KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,KC_ENT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C  ,KC_V ,KC_B  , KC_SPC ,                         MO(_ADJUST) ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,MT(MOD_RSFT, KC_BSLS) ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT ,KC_ADEN ,  KC_BSPC , KC_DEL ,TG(_ADJUST) ,                 ADJT  ,KC_PSCR  ,    KC_NAGR ,     KC_RALT ,KC_APP,KC_RCTL 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

#else

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐────────┐                         ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  , KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,                               KC_7,   KC_8,     KC_9,    KC_0,   KC_MINS, KC_EQL, KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q     ,KC_W    ,KC_E    ,KC_R    ,KC_T   ,KC_PGUP ,                KC_HOME ,  KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      SYM_L  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_PGDN ,                KC_END , KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,KC_ENT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C  ,KC_V ,KC_B  , KC_SPC ,                         MO(_ADJUST) ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,MT(MOD_RSFT, KC_BSLS) ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT ,KC_ADEN ,  KC_BSPC , KC_DEL ,TG(_ADJUST) ,                 ADJT  ,KC_PSCR  ,    KC_NAGR ,     KC_RALT ,KC_APP,KC_RCTL 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  #endif

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT ,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX ,XXXXXXX  ,XXXXXXX ,                 QK_BOOT, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_MPRV ,KC_MPLY ,KC_MNXT ,XXXXXXX ,KC_VOLU ,XXXXXXX ,                 XXXXXXX , XXXXXXX, XXXXXXX  ,XXXXXXX ,XXXXXXX, XXXXXXX,XXXXXXX ,XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_VOLD,XXXXXXX ,                  XXXXXXX , XXXXXXX, XXXXXXX ,XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,       			 XXXXXXX ,XXXXXXX  ,XXXXXXX  ,XXXXXXX, XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤        ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_ADEN ,XXXXXXX, XXXXXXX ,XXXXXXX ,                 XXXXXXX  ,XXXXXXX  ,   XXXXXXX ,     XXXXXXX ,XXXXXXX  ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘        └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                 ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_BTN1 ,XXXXXXX ,KC_BTN2 ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                   LT(0,KC_7), LT(0,KC_8),LT(0,KC_9), LT(0,KC_0),KC_MINS, KC_EQL, KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,KC_WH_U ,XXXXXXX ,XXXXXXX ,               KC_HOME ,  KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                        ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,XXXXXXX ,XXXXXXX ,               KC_END , KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,KC_ENT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐      ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TG(_MOUSE),				 MO(_ADJUST) ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,MT(MOD_RSFT, KC_BSLS) ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤      ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_ADEN ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,             ADJT  ,KC_DEL  ,    KC_NAGR ,     KC_RALT ,KC_APP,KC_RCTL  
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘      └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
  [_ARROW] = LAYOUT(
 //┌────────┬────────┬────────┬────────┬────────┬────────┐                        	         ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
    LCTL(KC_GRV),KC_HOME,XXXXXXX ,KC_END ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        	  	 XXXXXXX, KC_PAST, XXXXXXX , XXXXXXX,  KC_MINS, KC_EQL, KC_BSPC ,
 //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐               	         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    XXXXXXX ,XXXXXXX ,KC_UP ,XXXXXXX ,KC_WH_U ,XXXXXXX ,KC_PGUP ,           	  	 XXXXXXX , KC_NUM , KC_P7    ,KC_P8   ,KC_P9   ,XXXXXXX ,XXXXXXX ,XXXXXXX,
 //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤               	         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    TG(_F_TRPT),KC_LEFT ,KC_DOWN ,KC_RIGHT ,KC_WH_D ,XXXXXXX ,KC_PGDN,        	  	 XXXXXXX , XXXXXXX, KC_P4    ,KC_P5   ,KC_P6   ,XXXXXXX ,XXXXXXX ,KC_ENT ,
 //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐      	┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,LCTL(KC_LEFT),XXXXXXX ,LCTL(KC_RIGHT) ,XXXXXXX ,XXXXXXX ,XXXXXXX , 	 _______ ,XXXXXXX  , KC_P1    ,KC_P2  , KC_P3 , KC_PSLS ,XXXXXXX ,
 //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤      	├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
    _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,    	 XXXXXXX  ,XXXXXXX  ,    KC_P0 ,     KC_PDOT ,XXXXXXX  ,KC_RCTL
 //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘      	└────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐────────┐                         ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     LCTL(KC_GRV) ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO,               XXXXXXX,  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG ,RGB_MyEFF,RGB_MOD ,RGB_SAD ,RGB_HUI ,RGB_VAI ,RGB_HUI ,                XXXXXXX , XXXXXXX, XXXXXXX    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX ,XXXXXXX ,XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TG(_F_TRPT),XXXXXXX ,XXXXXXX ,RGB_SAI ,RGB_HUD ,RGB_VAD ,XXXXXXX ,              XXXXXXX , XXXXXXX, XXXXXXX    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                 _______ ,XXXXXXX  , XXXXXXX    ,XXXXXXX  , XXXXXXX , XXXXXXX  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_SPI ,RGB_SPD ,XXXXXXX ,     XXXXXXX ,    XXXXXXX , TG(_ADJUST),    XXXXXXX  ,XXXXXXX  ,    XXXXXXX ,     XXXXXXX ,XXXXXXX  ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
    [_F_TRPT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐────────┐                         ┌────────┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_GESC ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6,                   KC_F7,  KC_F8    ,KC_F9    ,KC_F10 ,_______   ,_______    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                _______ , _______, _______    ,_______   ,_______    ,_______    ,_______    ,_______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                _______ , _______, _______    ,_______   ,_______    ,_______    ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                _______ ,_______  ,_______    ,_______  , _______ ,_______    ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ , _______ ,        _______  ,_______  ,    _______ ,     _______ ,_______  ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
  
  
};

#ifdef TAP_DANCE_ENABLE
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_4); break;
    case SINGLE_HOLD: register_code(KC_F4); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_4); break;
    case SINGLE_HOLD: unregister_code(KC_F4); break;
  }
  xtap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
  [F4_HOLD]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};


#endif
;