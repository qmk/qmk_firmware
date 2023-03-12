/* Copyright 2023 Mehmet DEĞİRMENCİOĞLU (@mechMehmet)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


#include "keymap_turkish_f.h"
#include "sendstring_turkish_f.h"

uint8_t laughVal = 1;
uint8_t ahahCount = 0;
uint8_t incTemp = 0;
enum custom_keycodes {
    SHUT = SAFE_RANGE, 

};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //  // *
    //  // * ,--------------------------------------------------.    .------,-------------------------------------------.
    //  // * | esc/ok | F    |   G  |   Ğ  |   I  |   O  | LEFT       RIGHT |   D  |   R  |   N  |   H  |   P  |   [    |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | TAB/sym| U    |   İ  |   E  |   A  |   Ü  |                  |   T  |   K  |   M  |   L  |   Y  |   Ş    |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * |shft/cps| J    |   Ö  |   V  |   C  |   Ç  |                  |   Z  |   S  |   B  |   .  |   ,  |  RShft |
    //  // * |--------+------+------+------+------+------.,------.  ,------.`-------------+------+------+------+--------|
    //  // * |  ctrl  | win  | Alt  |                     |kisayo|  | ____ |                     | oyun |museD | oklayer|
    //  // * `----------------------'              `------.------.  `------.------.              `----------------------'
    //  // *                                       |  Left| Down |  |  Left| Down |
    //  //                                         `-------------'  `-------------' 

    [0] = LAYOUT_8x6(
        LT(4,KC_ESC),    TR_F,     TR_G,     TR_GBRV,  TR_I,  TR_O,           /*‿*/       TR_D, TR_R, TR_N, TR_H,  TR_P,    TR_Q, 
        LT(3,KC_TAB),    TR_U,     TR_IDOT,  TR_E,     TR_A,  TR_UDIA,        /*‿*/       TR_T, TR_K, TR_M, TR_L,  TR_Y,    TR_SCED,
        LSFT_T(KC_CAPS), TR_J,     TR_ODIA,  TR_V,     TR_C,  TR_CCED,        /*‿*/       TR_Z, TR_S, TR_B, TR_X,  TR_W,    KC_RSFT, 
        KC_LCTL,         KC_LGUI,  KC_LALT,                             MO(6),     KC_MUTE,                  TG(1), KC_WH_D, MO(5),
                                                              KC_BSPC,  KC_SPC,    KC_ENT, KC_DEL
            
    ),
    //  // * oyun 
    //  // * ,--------------------------------------------------.    .------,-------------------------------------------.
    //  // * | esc/ok | TAB  |   Q  |   X  |   E  |   R  | LEFT       RIGHT |   Y  |   U  |   I  |   O  |   P  |  xxxx  |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | ___    | SHFT |   A  |   W  |   D  |   F  |                  |   H  |   J  |   K  |   L  |   ;  |   ~    |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * |  T     | CTRL |   Z  |   S  |   C  |   V  |                  |   N  |   M  |   ,  |   .  |   /  |   ^    |
    //  // * |--------+------+------+------+------+------.,------.  ,------.`-------------+------+------+------+--------|
    //  // * |  G     | B    |  ALT |                     |SPACE |  |SPACE |                     |   <  |   >  |   _    |
    //  // * `----------------------'              `------.------.  `------.------.              `----------------------'
    //  // *                                       | SPACE| ENT  |  | ENT  |SPACE |
    //  //                                         `-------------'  `-------------' 
    
    //oyun layerı - qwerty
    [1] = LAYOUT_8x6(
       _______,      KC_TAB,  TR_Q,   TR_X, TR_E, TR_R,         /*‿*/      TR_Y,  TR_U,  TR_I,    TR_O,    TR_P,    TR_LBRC, 
       _______,      KC_LSFT, TR_A,   TR_W, TR_D, TR_F,         /*‿*/      TR_H,  TR_J,  TR_K,    TR_L,    TR_SCLN, TR_QUOT,
       TR_T,         KC_LCTL, TR_Z,   TR_S, TR_C, TR_V,         /*‿*/      TR_N,  TR_M,  TR_COMM, TR_DOT,  TR_SLSH, KC_RSFT,
       TR_G,         TR_B,    KC_LALT,                    _______,  KC_SPC,                       _______, TG(2),  XXXXXXX,
                                                  KC_SPC, KC_ENT,   KC_ENT, KC_DEL
    
    ),

    //oyun layerı f layout
    [2] = LAYOUT_8x6(
       _______,   _______, TR_F,   TR_V,    TR_I, TR_O,        /*‿*/       TR_D,  TR_R,  TR_N, TR_H,   TR_P,    TR_Q, 
       _______,   _______, TR_U,   TR_IDOT, TR_A, TR_UDIA,     /*‿*/       TR_T,  TR_K,  TR_M, TR_L,   TR_Y,    TR_SCED,
       TR_O,      _______, TR_J,   TR_E,    TR_C, TR_CCED,     /*‿*/       TR_Z,  TR_S,  TR_B, TR_X,   TR_W,    KC_RSFT,
       TR_UDIA,   TR_CCED, _______,                     _______,   _______,                    XXXXXXX, _______, XXXXXXX,
                                               _______, _______,   _______, _______
    
    ),

        //  // *
    //  // * ,--------------------------------------------------.    .------,-------------------------------------------.
    //  // * | ?      | @    |   7  |   8  |   9  |   +  | LEFT       RIGHT |   ;  |   {  |   }  |   &  |win+. |  xxxx  |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | ___    | $    |   4  |   5  |   6  |   -  |                  |   :  |   (  |   )  |   \  |   #  |   ~    |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * |  %     | ,    |   1  |   2  |   3  |   -  |                  |   |  |   [  |   ]  |   `  |      |   ^    |
    //  // * |--------+------+------+------+------+------.,------.  ,------.`-------------+------+------+------+--------|
    //  // * |  *     | /    |   0  |                     |  =   |  | xxxx |                     |   <  |   >  |   _    |
    //  // * `----------------------'              `------.------.  `------.------.              `----------------------'
    //  // *                                       | bcksp| spac |  |  '   |  "   |
    //  //                                         `-------------'  `-------------'

    //symbol ve numpad
    [3] = LAYOUT_8x6(
        TR_QUES,     TR_AT,     KC_7,    KC_8,   KC_9,  TR_PLUS,         /*‿*/    TR_SCLN, TR_LCBR, TR_RCBR, TR_AMPR, G(TR_DOT), XXXXXXX, 
        _______,     TR_DLR,    KC_4,    KC_5,   KC_6,  TR_MINS,         /*‿*/    TR_COLN, TR_LPRN, TR_RPRN, TR_BSLS, TR_HASH,   TR_TILD,
        TR_PERC,     TR_COMM,   KC_1,    KC_2,   KC_3,  TR_DOT,          /*‿*/    TR_PIPE, TR_LBRC, TR_RBRC, TR_GRV,  KC_PDOT,   TR_CIRC,  
        TR_ASTR,     TR_SLSH,   KC_0,                             TR_EQL,     XXXXXXX,                        TR_LABK, TR_RABK,   TR_UNDS,
                                                        KC_BSPC,  KC_SPC,     TR_QUOT, TR_DQUO
                
    ),
    //ok tuşları, esc den aktive olur.
    //  // *
    //  // * ,--------------------------------------------------.    .------,-------------------------------------------.
    //  // * | ok layr| home |   ←  |   ↑  |   →  |      | LEFT       RIGHT |      |   ←  |   ↑  |   →  | home |        |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | shift  | end  |      |   ↓  |mouseU| PgUp |                  |      |      |   ↓  |      | end  |        |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | shift  |      |      |      |mouseD| PgDw |                  |      |      |      |      |      |        |
    //  // * |--------+------+------+------+------+------.,------.  ,------.`-------------+------+------+------+--------|
    //  // * | ctrl   |      |      |                     |shift |  |     k |                    |      |      |        |
    //  // * `----------------------'              `------.------.  `------.------.              `----------------------'
    //  // *                                       | alt  | ctrl |  |  '   |  "   |
    //  //                                         `-------------'  `-------------'

    [4] = LAYOUT_8x6(
       _______,     KC_HOME,  KC_LEFT, KC_UP,   KC_RGHT, XXXXXXX,      /*‿*/   XXXXXXX, KC_LEFT, KC_UP,   KC_RGHT,  KC_HOME, XXXXXXX, 
       KC_LSFT,     KC_END,   XXXXXXX, KC_DOWN, KC_WH_U, KC_PGUP,      /*‿*/   XXXXXXX, XXXXXXX, KC_DOWN,  XXXXXXX, KC_END,  XXXXXXX,
       KC_LSFT,     XXXXXXX,  XXXXXXX, XXXXXXX, KC_WH_D, KC_PGDN,      /*‿*/   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, 
       _______,     XXXXXXX,  KC_LALT,                           KC_LSFT,  XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX,
                                                        KC_LALT, KC_LCTL,  KC_LCTL, KC_LALT
    
    ),

    //yazı yazarken kolayca ok tuşlarını aktive etmek için
    [5] = LAYOUT_8x6(
       XXXXXXX,     KC_HOME,  KC_LEFT, KC_UP,   KC_RGHT, XXXXXXX,      /*‿*/   XXXXXXX, KC_LEFT, KC_UP,   KC_RGHT,  KC_HOME, XXXXXXX, 
       KC_LSFT,     KC_END,   XXXXXXX, KC_DOWN, KC_WH_U, KC_PGUP,      /*‿*/   XXXXXXX, XXXXXXX, KC_DOWN,  XXXXXXX, KC_END,  XXXXXXX,
       KC_LSFT,     XXXXXXX,  XXXXXXX, XXXXXXX, KC_WH_D, KC_PGDN,      /*‿*/   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, 
       KC_LCTL,     XXXXXXX,  KC_LALT,                           KC_LSFT,  XXXXXXX,                        XXXXXXX, XXXXXXX, _______,
                                                        KC_LALT, KC_LCTL,  KC_LCTL, KC_LALT
    
    ),

    //kısayollar
    //  // *C:ctrl, S: shft, A: alt, RCS: ctrl+shift, G: GUI(win),
    // SHUT: logoff macrosu 
    // sleep, uyku
    // RBT: mcu reset, BOOT: mcu boot a alır.
    //  // * ,--------------------------------------------------.    .------,-------------------------------------------.
    //  // * |C+S+ESC |      |      |Ctrl+E|   →  |Sf+Del| LEFT       RIGHT |  F1  |  F2  |  F3  |  F4  |      | logoff |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * | A+TAB  |Ctrl+A|Ctrl+S|Ctrl+D|Ctrl+F| Win+X|                  |  F5  |  F6  |  F7  |  F8  |alt+f4| sleep  |
    //  // * |--------+------+------+------+------+------|                  |------+------+------+------+------+--------|
    //  // * |        |Ctrl+Z|Ctrl+X|Ctrl+C|Ctrl+V|      |                  |  F9  |  F10 |  F11 |  F12 |      |        |
    //  // * |--------+------+------+------+------+------.,------.  ,------.`-------------+------+------+------+--------|
    //  // * |MouseClk|Ctrl+W|C+S+T |                     |kısayo|  |     k |                    |      | reset| boot   |
    //  // * `----------------------'              `------.------.  `------.------.              `----------------------'
    //  // *                                       | alt  | ctrl |  |  '   |  "   |
    //  //                                         `-------------'  `-------------'
    [6] = LAYOUT_8x6(
       RCS(KC_ESC), XXXXXXX, XXXXXXX, C(TR_E), XXXXXXX, S(KC_DEL),      /*‿*/       KC_F1, KC_F2,  KC_F3,  KC_F4, XXXXXXX,  SHUT, 
       A(KC_TAB),   C(TR_A), C(TR_S), C(TR_D), C(TR_F), G(TR_X),        /*‿*/       KC_F5, KC_F6,  KC_F7,  KC_8,  A(KC_F4), KC_SLEP,
       XXXXXXX,     C(TR_Z), C(TR_X), C(TR_C), C(TR_V), XXXXXXX,        /*‿*/       KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, 
       KC_BTN1,     C(TR_W), RCS(TR_T),                          _______,    XXXXXXX,                      XXXXXXX, QK_RBT, QK_BOOT,
                                                        XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
    
    ),

};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { 

    case SHUT: //oturum kapatır
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(TR_R);
            unregister_code(TR_R);
            unregister_code(KC_LGUI);
            tap_code_delay(KC_WH_U, 1000);
            SEND_STRING(" logoff");
            tap_code(KC_ENT);
        }
        break;
    }
    return true;
    
};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(ledGreen);
  writePinHigh(ledGreen);

  setPinOutput(ledBlue);
  writePinHigh(ledBlue);

  setPinOutput(ledRed);
  writePinHigh(ledRed);

  setPinOutput(ledWhite);
  writePinHigh(ledWhite);

}



layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case 1: //oyun 1 layer
            writePinHigh(ledRed);
            writePinHigh(ledBlue);
            writePinLow(ledGreen);
            break;
        case 2: //oyun 2 layer
            writePinLow(ledBlue);
            writePinLow(ledRed);
            writePinHigh(ledGreen);
            break;
        case 3: //symbol - numpad
            writePinLow(ledBlue);
            writePinHigh(ledRed);
            break;
        case 4: //ok tuşları
            writePinLow(ledBlue);
            writePinLow(ledRed);
            break;
        case 5: //ok tuşları
            writePinLow(ledRed);
            writePinHigh(ledBlue);
            break;
        case 6: //kısayollar
            writePinHigh(ledRed);
            writePinLow(ledBlue);
            writePinLow(ledGreen);

          
            //random laugh
            laughVal = laughVal+1;
            if(laughVal>6){ laughVal = 1;}
            incTemp = rand()%2;
            ahahCount = ahahCount + incTemp;
            if(ahahCount>4){ ahahCount = 1;}
            break;
        default:
            writePinHigh(ledRed);
            writePinHigh(ledBlue);
            writePinHigh(ledGreen);
            break;
    }
    return state;
}
 

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        //writePin(NUM_LOCK_LED_PIN, led_state.num_lock);
        writePin(ledWhite, !led_state.caps_lock);
        //writePin(SCROLL_LOCK_LED_PIN, led_state.scroll_lock);
    }
   return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            if (clockwise) {
               tap_code(KC_VOLU);
     

            } else {
                tap_code(KC_VOLD);

            }
            break;
        case 1:
            if (clockwise) {
               tap_code(KC_VOLU);
     

            } else {
                tap_code(KC_VOLD);

            }
            break;
        case 2:
            if (clockwise) {
               tap_code(KC_VOLU);
     

            } else {
                tap_code(KC_VOLD);

            }
            break;
         
        case 6:
            if (clockwise){ //random with encoder
                switch(ahahCount){
                    case 1:
                        tap_code(TR_A);
                        tap_code(TR_H);
                        break;
                    case 2:
                        tap_code(TR_A);
                        tap_code(TR_H);
                        tap_code(TR_A);
                        tap_code(TR_H);
                        break;
                    case 3:
                        tap_code(TR_A);
                        tap_code(TR_H);
                        tap_code(TR_A);
                        tap_code(TR_H);
                        tap_code(TR_A);
                        tap_code(TR_H);
                        break;
                }
                if(laughVal == 1){
                    for(int i=0;i<=5;i++){
                        if(i % 2 == 0){
                            int tempVal = rand() % 6;
                                switch (tempVal){
                                    case 0: 
                                        tap_code(TR_Q);
                                        break;
                                    case 1: 
                                        tap_code(TR_W);
                                        break;
                                    case 2: 
                                        tap_code(TR_E);
                                        break;
                                    case 3: 
                                        tap_code(TR_R);
                                        break;
                                    case 4: 
                                        tap_code(TR_W);
                                        break;
                                    case 5: 
                                        tap_code(TR_R);
                                        break;
                                }
                        } else if(i%2 == 1){
                            int tempVal = rand() % 6;
                            switch (tempVal){
                                case 0: 
                                    tap_code(TR_J);
                                    break;
                                case 1: 
                                    tap_code(TR_K);
                                    break;
                                case 2: 
                                    tap_code(TR_L);
                                    break;
                                case 3: 
                                    tap_code(TR_SCED);
                                    break;
                                case 4: 
                                    tap_code(TR_J);
                                    break;
                                case 5: 
                                    tap_code(TR_K);
                                    break;
                            }
                        }
                    }
                }else{
                    for(int i=0;i<=5;i++){
                        if(i % 2 == 0){
                            int tempVal = rand() % 6;
                            switch (tempVal){
                                case 0: 
                                    tap_code(TR_A);
                                    break;
                                case 1: 
                                    tap_code(TR_S);
                                    break;
                                case 2: 
                                    tap_code(TR_D);
                                    break;
                                case 3: 
                                    tap_code(TR_F);
                                    break;
                                case 4: 
                                    tap_code(TR_A);
                                    break;
                                case 5: 
                                    tap_code(TR_D);
                            break;

                            }
                        }else if(i%2 == 1){
                            int tempVal = rand() % 6;
                            switch (tempVal){
                                case 0: 
                                    tap_code(TR_J);
                                    break;
                                case 1: 
                                    tap_code(TR_K);
                                    break;
                                case 2: 
                                    tap_code(TR_L);
                                    break;
                                case 3: 
                                    tap_code(TR_SCED);
                                    break;
                                case 4: 
                                    tap_code(TR_J);
                                    break;
                                case 5: 
                                    tap_code(TR_K);
                            break;

                            }

                        }
                    }
                }       
            } else {
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
                switch(ahahCount){
                    case 1:
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);                        
                        break;
                    case 2:
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);  
                        break;
                    case 3:
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);                      
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);
                        tap_code(KC_BSPC);  
                        break;
                    }
            }
            break;
    }
    return false;
}
