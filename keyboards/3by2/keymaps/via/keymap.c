#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "quantum.h"

#define ____ KC_TRNS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
       	KC_F13 , KC_F14 , KC_F15,
        KC_F16 , KC_F17 , KC_F18
    ),

    [1] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____
    ),

    [2] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____
    ),

    [3] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____ 
    ),

};

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    if(data[0] == 0xFC){
        switch (data[1]) {
            case 0x01:{
                // move to layer
                data[1] = 0xFD;
                layer_move(data[2]);
                break;
            }
            case 0x02:{
                // turn on layer
                data[1] = 0xFD;
                layer_on(data[2]);
                break;
            }
            case 0x03:{
                // turn off layer
                data[1] = 0xFD;
                layer_off(data[2]);
                break;
            }
        }
    }
    raw_hid_send(data, length);
}
