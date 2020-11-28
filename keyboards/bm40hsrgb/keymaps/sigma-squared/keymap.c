// qmk flash -kb bm40hsrgb -km sigma-squared

#include "sigma-squared.h"

//game and chat layer led colors

void rgb_matrix_indicators_user(void) {

if(IS_LAYER_ON(GAME)) {
  rgb_matrix_set_color(11, 0, 204, 255);
}

if(IS_LAYER_ON(CHAT)) {
  rgb_matrix_set_color(11, 0, 255, 10);
}

if(IS_LAYER_ON(SECGAME)) {
  rgb_matrix_set_color(11, 255, 0, 0);
}



if(IS_LAYER_ON(NAVR)) {
  rgb_matrix_set_color(40, 0, 204, 255);
}

if(IS_LAYER_ON(MEDR)) {
  rgb_matrix_set_color(39, 0, 204, 255);
}

if(IS_LAYER_ON(FUNL)) {
  rgb_matrix_set_color(43, 0, 204, 255);
}

if(IS_LAYER_ON(NSL)) {
  rgb_matrix_set_color(42, 0, 204, 255);
}

if(IS_LAYER_ON(NSSL)) {
  rgb_matrix_set_color(41, 0, 204, 255);
}




if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    rgb_matrix_set_color_all(255, 80, 0);
  }

}

//actions to do when certain keys are pressed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //send message when going back to game layer from chat layer
    switch (keycode) {
        case TG(CHAT):
            if (record->event.pressed) {
                tap_code(KC_ENT);
            }
            return true;
    }
    return true;
}
