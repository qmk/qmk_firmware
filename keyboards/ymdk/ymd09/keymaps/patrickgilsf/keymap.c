#include QMK_KEYBOARD_H
//#include "raw_hid.h"



enum custom_keycodes {
    KEY1 = SAFE_RANGE,
    KEY2,
    KEY3,
    KEY4,
    KEY5,
    KEY6,
    KEY7,
    KEY8,
    KEY9,
    KEY10,
    KEY11,
    KEY12,
    KEY13,
    KEY14,
    KEY15,
    KEY16,
    KEY17,
    KEY18,
    KEY19,
    KEY20,
    KEY21,
    KEY22,
    KEY23,
    KEY24,
    KEY25,
    KEY26,
    KEY27
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KEY1, KEY2, KEY3, 
               KEY4, KEY5, KEY6, 
               KEY7, KEY8, KEY9),

  [1] = LAYOUT(KEY10, KEY11, KEY12,
               KEY13, KEY14, KEY15,
               KEY16, KEY17, KEY18),

  [2] = LAYOUT(KEY19, KEY20, KEY21,
               KEY22, KEY23, KEY24,
               KEY25, KEY26, KEY27)

};

//this is the timer for flash mode sequence
//static uint32_t key_timer = 0;




/*
Legend:
--Layer 0 - [Mac OS Zoom shortcuts]
KEY1 - Mute Mic/Toggle Keyboard Light;
KEY2 - Mute Video;
KEY3 - Raise/Lower Hand;
KEY4 - Speaker/Gallery View Toggle
KEY5 - Prev Page of Gallery
KEY6 - Next Page of Gallery
KEY7 - Full Screen
KEY8 - Show/Hide Chat; // If KEY7 is down, up to layer 1.
KEY9 - Minimal Window;

--Layer 1 - 
KEY10 - Mute Mic/Toggle Keyboard Light;
KEY11 - Mute Video; // If KEY10 is down, back to layer 0
KEY12 - Raise/Lower Hand;
KEY13 - Speaker/Gallery View Toggle
KEY14 - Prev Page of Gallery
KEY15 - Next Page of Gallery
KEY16 - Full Screen
KEY17 - Show/Hide Chat; // If KEY7 is down, down to layer 0.
KEY18 - Minimal Window; // If KEY7 is down, up to layer 2

-- Layer 2 -
KEY19 - 
KEY20 - 
KEY21 - 
KEY22 -
KEY23 -
KEY24 -
KEY25 - 
KEY26 - If KEY25 is down, back to layer 1
KEY27 - If KEY25 && KEY26 are down, puts it in setup mode
*/

//initialize booleans for stacked functions:
bool kp_1 = false;
    bool kp_1a = false; //1a bounces between toggle presses
bool kp_2 = false;
bool kp_3 = false;
bool kp_4 = false;
bool kp_5 = false;
bool kp_6 = false;
bool kp_7 = false;
    bool kp_7a = false;
bool kp_8 = false;
bool kp_9 = false;

bool kp_10 = false;
    bool kp_10a = false;
bool kp_11 = false;
bool kp_12 = false;
bool kp_13 = false;
bool kp_14 = false;
bool kp_15 = false;
bool kp_16 = false;
    bool kp_16a = false;
bool kp_17 = false;
bool kp_18 = false;

bool kp_19 = false;
    bool kp_19a = false;
bool kp_20 = false;
bool kp_21 = false;
bool kp_22 = false;
bool kp_23 = false;
bool kp_24 = false;
bool kp_25 = false;
    bool kp_25a = false;
bool kp_26 = false;
bool kp_27 = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KEY1:
        if (record->event.pressed) {
            kp_1 = true;
        } else {
            kp_1 = false;
            if (kp_1a == false) {  
                kp_1a = true;       
                tap_code16(LSFT(LGUI(KC_A)));                            
                rgblight_setrgb(RGB_RED);
            }   else if (kp_1a == true) {
                    kp_1a = false;
                    tap_code16(LSFT(LGUI(KC_A)));
                    rgblight_setrgb(RGB_ORANGE);
                };
        };
        break;
    case KEY2:
        if (record->event.pressed) {
            kp_2 = true;
        }   else {
                tap_code16(LSFT(LGUI(KC_V)));
                kp_2 = false;
        }
        break;
    case KEY3:
        if (record->event.pressed) {
            kp_3 = true;
        }   else {
                tap_code16(LALT(KC_Y));
                kp_3 = false;
        }
        break;
    case KEY4:
        if (record->event.pressed) {
            kp_4 = true;
        }   else {
                tap_code16(LSFT(LGUI(KC_W)));
                kp_4 = false;
        }
        break;
    case KEY5:
        if (record->event.pressed) {
            kp_5 = true;
        }   else {
                tap_code16(LCTL(KC_P));
                kp_5 = false;
        }
        break;
    case KEY6:
        if (record->event.pressed) {
            kp_6 = true;
        }   else {
                tap_code16(LCTL(KC_N));
                kp_6 = false;
        }
        break;
    case KEY7:
        if (record->event.pressed) {           
            kp_7 = true;
        }   else { 
                kp_7 = false;           
                if (kp_7a == false) {
                    tap_code16(LSFT(LGUI(KC_F)));
                }
            }
        break;
    case KEY8:
        if (record->event.pressed) {
            kp_8 = true;
        }   else {
                kp_8 = false;
                tap_code16(LSFT(LGUI(KC_H)));                
            }
        break;
    case KEY9:
        if (record->event.pressed) {
            kp_9 = true;
            if (kp_7) {
                layer_move(1);
                kp_7a = true;
            }    
        }   else {
                kp_9 = false;
                kp_7a = false;
                SEND_STRING(SS_LSFT(SS_LGUI("m"))); 
            }
        break;
    case KEY10:
        if (record->event.pressed) {
            kp_10 = true;
        }   else {
                kp_10 = false;
                if (kp_10a == false) {        
                    tap_code16(LALT(KC_A));          
                    rgblight_setrgb(RGB_RED);
                    kp_10a = true;     
                }   else if (kp_10a == true) {
                        tap_code16(LALT(KC_A));
                        rgblight_setrgb(RGB_YELLOW);
                        kp_10a = false;
                    };
            };         
        break;
    case KEY11:
        if (record->event.pressed) {
            kp_11 = true;       
        }   else {
                kp_11 = false;
                tap_code16(LALT(KC_V));
            }
        break;
    case KEY12:
        if (record->event.pressed) {
            kp_12 = true;
            }   else {
                    kp_12 = false;
                    tap_code16(LALT(KC_Y));
                }
        break;
    case KEY13:
        if (record->event.pressed) {
            kp_13 = true;
            }   else {
                    kp_13 = false;
                    tap_code16(LALT(KC_F2));
                }
        break;
    case KEY14:
        if (record->event.pressed) {
            kp_14 = true;
            }   else {
                    kp_14 = false;
                    tap_code(KC_PGUP);
                }
        break;   
    case KEY15:
        if (record->event.pressed) {
            kp_15 = true;
            }   else {
                    kp_15 = false;
                    tap_code16(KC_PGDOWN);
                }
        break;
    case KEY16:
        if (record->event.pressed) {           
            kp_16 = true;
        }   else {
                kp_16 = false;
                if (kp_16a == false) {
                  tap_code16(LALT(KC_F));  
                }   
            };
        break;
    case KEY17:
        if (record->event.pressed) {
            kp_17 = true;
            if (kp_16) {
                layer_move(0);
                kp_16a = true;
            }   
        }   else {    
                kp_17 = false;
                kp_16a = false;            
                tap_code16(LALT(KC_H));
            }
        break;
    case KEY18:
        if (record->event.pressed) {
            kp_18 = true;
            if (kp_16) {
                layer_move(2);
                kp_16a = true;
            }
        }   else {
                kp_18 = false;
                kp_16a = false;
            }
        break;
    case KEY19:
        if (record->event.pressed) {
            kp_19 = true;
        }   else {
            kp_19 = false;
        }
        break;
    case KEY20:
        if (record->event.pressed) {
            kp_20 = true;             
        } else {
            kp_20 = false;
        }
        break;
    case KEY21:
        if (record->event.pressed) {
            kp_21 = true;
        }   else {
                kp_21 = false;
            }
        break;
    case KEY22:
        if (record->event.pressed) {
            kp_22 = true;
        }   else {
                kp_22 = false;
            }
        break;
    case KEY23:
        if (record->event.pressed) {
            kp_23 = true;
        }   else {
                kp_23 = false;
            }
        break;
    case KEY24:
        if (record->event.pressed) {
            kp_24 = true;
        }   else {
            kp_24 = false;
        }
        break;
    case KEY25:
        if (record->event.pressed) {
            kp_25 = true;
        }   else {
            kp_25 = false;
            /*if (kp_25a == false) {
                //put command here if you think of one
            }*/
        }
        break;
    case KEY26:
        if (record->event.pressed) {
            kp_26 = true;
            if (kp_25) {
                layer_move(1);
                kp_25a = true;
            }
        }   else {
            kp_26 = false;
            kp_25a = false;
            }
        break;
    case KEY27:
        if (record->event.pressed) {
            kp_27 = true;
            if (kp_25 && kp_26) {
                rgblight_setrgb(RGB_WHITE);
                reset_keyboard();
            }
       }   else {
            kp_27 = false;
        }
        break;
    }
    return true;
};


//for when I use rawHID to add feedback:
void raw_hid_receive(uint8_t *data, uint8_t length) {
}


//these are the initialization functions
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_setrgb(RGB_ORANGE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); 
  set_single_persistent_default_layer(0); 
}

//RGB control for layers
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default:
            if (kp_1a) {
                rgblight_setrgb(RGB_RED);
            }   else {
                rgblight_setrgb(RGB_ORANGE);
            };
        break;
        case 1:
            if (kp_10a) {
                rgblight_setrgb(RGB_RED); 
            }   else {
                rgblight_setrgb(RGB_YELLOW);
            }
        break;
    case 2:
        rgblight_setrgb(RGB_GREEN);
        break;
    }
return state;    
}


