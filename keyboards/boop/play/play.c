#include "quantum.h"
#include "encoder.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  matrix_init_user();
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

void keyboard_post_init_user(void) {
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    debug_enable=true;
  debug_matrix=true;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD + 4);
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE );

    // rgblight_effect_rainbow_swirl(2)

    // rgblight_sethsv_noeeprom(HSV_BLUE);



}


void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
// left encoder
    if (index == 0) {
        switch(biton32(layer_state)){
            //  case 2:
            //     if (clockwise) {
            //     register_code(KC_LCTL);
            //     tap_code(KC_3);
            //     unregister_code(KC_LCTL);
            //     } else {
            //     register_code(KC_LCTL);
            //     tap_code(KC_1);
            //     unregister_code(KC_LCTL);
            //     }
            //     break;'
            case 2:
                if (clockwise) {
                rgblight_increase_hue_noeeprom();
                } else {
                rgblight_decrease_hue_noeeprom();

                }
                break;


            case 1:
                if (clockwise) {
                rgblight_step_noeeprom();
                } else {
                rgblight_step_reverse_noeeprom();

                }
                break;
            default:
                if (clockwise){
                    tap_code(KC_VOLU);
                } else{
                    tap_code(KC_VOLD);
                }
                break;
      }
    }
}


// process_record_user -

// void encoder_update_kb(int8_t index, bool clockwise) {
//     encoder_update_user(index, clockwise);

//     // uint16_t held_keycode_timer = timer_read();
//     uint8_t keycode = clockwise ? KC_VOLU : KC_VOLD;
//     tap_code(keycode);
//     // register_code(keycode);
//     // while (timer_elapsed(held_keycode_timer) < 4);
//     // unregister_code(keycode);
// }
