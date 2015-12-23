#include "ergodox_ez.h"


inline void ergodox_right_led_on(int led_num) {
    switch led_num {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }
}

inline void ergodox_right_led_off(int led_num) {
    switch led_num {
        case 1:
            ergodox_right_led_1_off();
            break;
        case 2:
            ergodox_right_led_2_off();
            break;
        case 3:
            ergodox_right_led_3_off();
            break;
        default:
            break;
    }
}

inline void ergodox_right_led_set_state(int led_num, int state) {
    if (state > 0) {
        ergodox_right_led_on(led_num);
    } else {
        ergodox_right_led_off(led_num);
    }
}
