// qmk flash -kb bm40hsrgb -km sigma-squared

#include "sigma-squared.h"

//layer led colors

void rgb_matrix_indicators_user(void) {

if(IS_LAYER_ON(GAME)) {
  rgb_matrix_set_color(11, 0, 4, 5);
}

if(IS_LAYER_ON(CHAT)) {
  rgb_matrix_set_color(11, 0, 5, 0.19);
}

if(IS_LAYER_ON(SECGAME)) {
  rgb_matrix_set_color(11, 5, 0, 0);
}



if(IS_LAYER_ON(NAVR)) {
  rgb_matrix_set_color(40, 0, 4, 5);

  rgb_matrix_set_color(19, 0, 4, 5);
  rgb_matrix_set_color(20, 0, 4, 5);
  rgb_matrix_set_color(21, 0, 4, 5);
  rgb_matrix_set_color(22, 0, 4, 5);
}

if(IS_LAYER_ON(MEDR)) {
  rgb_matrix_set_color(39, 5, 1, 2);

  rgb_matrix_set_color(19, 5, 1, 2);

  rgb_matrix_set_color(22, 5, 1, 2);

  rgb_matrix_set_color(42, 5, 1, 2);
}

if(IS_LAYER_ON(FUNL)) {
  rgb_matrix_set_color(43, 5, 0, 0);

  rgb_matrix_set_color(1, 5, 0, 0);
  rgb_matrix_set_color(2, 5, 0, 0);
  rgb_matrix_set_color(3, 5, 0, 0);
  rgb_matrix_set_color(4, 5, 0, 0);

  rgb_matrix_set_color(13, 5, 0, 0);
  rgb_matrix_set_color(14, 5, 0, 0);
  rgb_matrix_set_color(15, 5, 0, 0);
  rgb_matrix_set_color(16, 5, 0, 0);

  rgb_matrix_set_color(25, 5, 0, 0);
  rgb_matrix_set_color(26, 5, 0, 0);
  rgb_matrix_set_color(27, 5, 0, 0);
  rgb_matrix_set_color(28, 5, 0, 0);
}

if(IS_LAYER_ON(NSL)) {
  rgb_matrix_set_color(42, 1, 0, 5);

  rgb_matrix_set_color(2, 1, 0, 5);
  rgb_matrix_set_color(3, 1, 0, 5);
  rgb_matrix_set_color(4, 1, 0, 5);

  rgb_matrix_set_color(14, 1, 0, 5);
  rgb_matrix_set_color(15, 1, 0, 5);
  rgb_matrix_set_color(16, 1, 0, 5);

  rgb_matrix_set_color(26, 1, 0, 5);
  rgb_matrix_set_color(27, 1, 0, 5);
  rgb_matrix_set_color(28, 1, 0, 5);

  rgb_matrix_set_color(38, 1, 0, 5);
  rgb_matrix_set_color(39, 1, 0, 5);
  rgb_matrix_set_color(40, 1, 0, 5);
}

if(IS_LAYER_ON(NSSL)) {
  rgb_matrix_set_color(41, 0, 5, 0.19);

  rgb_matrix_set_color(1, 0, 5, 0.19);
  rgb_matrix_set_color(2, 0, 5, 0.19);
  rgb_matrix_set_color(3, 0, 5, 0.19);
  rgb_matrix_set_color(4, 0, 5, 0.19);
  rgb_matrix_set_color(5, 0, 5, 0.19);

  rgb_matrix_set_color(13, 0, 5, 0.19);
  rgb_matrix_set_color(14, 0, 5, 0.19);
  rgb_matrix_set_color(15, 0, 5, 0.19);
  rgb_matrix_set_color(16, 0, 5, 0.19);
  rgb_matrix_set_color(17, 0, 5, 0.19);

  rgb_matrix_set_color(25, 0, 5, 0.19);
  rgb_matrix_set_color(26, 0, 5, 0.19);
  rgb_matrix_set_color(27, 0, 5, 0.19);
  rgb_matrix_set_color(28, 0, 5, 0.19);
  rgb_matrix_set_color(29, 0, 5, 0.19);

}

if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    rgb_matrix_set_color_all(5, 1.56, 0);
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
