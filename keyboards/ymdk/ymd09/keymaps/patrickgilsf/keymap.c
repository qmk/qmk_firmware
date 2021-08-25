#include QMK_KEYBOARD_H



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
    KEY18
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KEY1, KEY2, KEY3, 
               KEY4, KEY5, KEY6, 
               KEY7, KEY8, KEY9),

  [1] = LAYOUT(KEY10, KEY11, KEY12,
               KEY13, KEY14, KEY15,
               KEY16, KEY17, KEY18),

};


/*
Legend:
--Layer 1 - 
KEY1 - Mute Mic/Toggle Keyboard Light;
KEY2 - Mute Video;
KEY3 - Raise/Lower Hand;
KEY4 - Speaker/Gallery View Toggle
KEY5 - Prev Page of Gallery
KEY6 - Next Page of Gallery
KEY7 - Full Screen
KEY8 - Show/Hide Chat
KEY9 - Minimal Window

--Layer 2 - 
KEY10 - 
KEY11 - IF KEY10 IS DOWN, BACK TO LAYER 0
KEY12 - 
KEY13 - 
KEY14 - 
KEY15 - 
KEY16 - 
KEY17 - 
KEY18 - IF KEY17 IS DOWN, PUTS IT IN SETUP MODE
*/

//initialize booleans for stacked functions:
bool kp_1 = false;
    bool kp_1a = false;
bool kp_2 = false;
bool kp_3 = false;
bool kp_4 = false;
bool kp_5 = false;
bool kp_6 = false;
bool kp_7 = false;
bool kp_8 = false;
bool kp_9 = false;
bool kp_10 = false;
bool kp_11 = false;
bool kp_12 = false;
bool kp_13 = false;
bool kp_14 = false;
bool kp_15 = false;
bool kp_16 = false;
bool kp_17 = false;
bool kp_18 = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KEY1:
        if (record->event.pressed) {
            kp_1 = true;
            if (kp_1a == false) {        
                tap_code16(LSFT(LGUI(KC_A)));
                kp_1a = true;               
                rgblight_setrgb(RGB_RED);
        }   else if (kp_1a == true) {
                kp_1a = false;
                rgblight_setrgb(RGB_TEAL);
                tap_code16(LSFT(LGUI(KC_A)));

        };
        } else {
            kp_1 = false;
        }
        break;
    case KEY2:
        if (record->event.pressed) {
            //SEND_STRING(SS_LSFT(SS_LGUI("v")));
            tap_code16(LSFT(LGUI(KC_V)));
        }
        break;
    case KEY3:
        if (record->event.pressed) {
            //SEND_STRING(SS_LALT("y"));
            tap_code16(LALT(KC_Y));
        }
        break;
    case KEY4:
        if (record->event.pressed) {
            //SEND_STRING(SS_LSFT(SS_LGUI("w")));
            tap_code16(LSFT(LGUI(KC_W)));
        }
        break;
    case KEY5:
        if (record->event.pressed) {
            //SEND_STRING(SS_LCTL("p"));
            tap_code16(LCTL(KC_P));
        }
        break;
    case KEY6:
        if (record->event.pressed) {
            //SEND_STRING(SS_LCTL("n"));
            tap_code16(LCTL(KC_N));
        }
        break;
    case KEY7:
        if (record->event.pressed) {           
            kp_7 = true;
        }   else {            
            if (kp_7) {
                kp_7 = false;
                tap_code16(LSFT(LGUI(KC_F)));
            }
        }
        break;
    case KEY8:
        if (record->event.pressed) {
            if (kp_7) {
                layer_move(1);
                kp_7 = false;
                //rgblight_toggle();
                rgblight_setrgb(RGB_ORANGE);
            }   else {                
                //SEND_STRING(SS_LSFT(SS_LGUI("h")));
                tap_code16(LSFT(LGUI(KC_H)));
            }
        }
        break;
    case KEY9:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_LGUI("m")));
        }
        break;
    case KEY10:
        if (record->event.pressed) {
            kp_10 = true;
        }   else {
            kp_10 = false;
        }
        break;
    case KEY11:
        if (record->event.pressed) {
            kp_11 = true;
            if (kp_10) {
                layer_off(1);
                layer_on(0);
                if (kp_1 == false) {
                    rgblight_setrgb(RGB_TEAL);
                }   else if (kp_1) {
                    rgblight_setrgb(RGB_RED);
                }

            }
        } else {
                kp_11 = false;
            }
        break;
    case KEY12:
        if (record->event.pressed) {
            kp_12 = true;
            tap_code16(LGUI(KC_SPACE));
            SEND_STRING("zoom");
            tap_code16(KC_ENTER);

        }   else {
            kp_12 = false;
        }
        break;
    case KEY13:
        if (record->event.pressed) {
            kp_13 = true;
        }   else {
            kp_13 = false;
        }
        break;
    case KEY14:
        if (record->event.pressed) {
            kp_14 = true;
        }   else {
            kp_14 = false;
        }
        break;   
    case KEY15:
        if (record->event.pressed) {
            kp_15 = true;
        }   else {
            kp_15 = false;
        }
        break;
    case KEY16:
        if (record->event.pressed) {
            kp_16 = true;
        }   else {
            kp_16 = false;
        }
        break;
    case KEY17:
        if (record->event.pressed) {
            kp_17 = true;
        }   else {
            kp_17 = false;
        }
        break;
    case KEY18:
        if (record->event.pressed && kp_17 == true) {
            rgblight_setrgb(RGB_WHITE);
            reset_keyboard();
        }
        break;
    }
    return true;
};













/*
for when I use rawHID to add feedback:
void raw_hid_receive(uint8_t *data, uint8_t length) {
}
*/


//these are the initialization functions
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_setrgb(RGB_TEAL);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); 
  set_single_persistent_default_layer(0);
 
}