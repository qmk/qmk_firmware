#pragma once

#include "quantum.h"

void ergodox_board_led_on(void);
void ergodox_right_led_1_on(void);
void ergodox_right_led_2_on(void);
void ergodox_right_led_3_on(void);

inline void ergodox_right_led_on(uint8_t led) {
    switch (led) {
    case 0:
        ergodox_right_led_1_on();
        break;
    case 1:
        ergodox_right_led_2_on();
        break;
    case 2:
        ergodox_right_led_3_on();
        break;
    }
}

void ergodox_board_led_off(void);
void ergodox_right_led_1_off(void);
void ergodox_right_led_2_off(void);
void ergodox_right_led_3_off(void);
inline void ergodox_right_led_off(uint8_t led) {
    switch (led) {
    case 0:
        ergodox_right_led_1_off();
        break;
    case 1:
        ergodox_right_led_2_off();
        break;
    case 2:
        ergodox_right_led_3_off();
        break;
    }
}

inline void ergodox_led_all_on(void)
{
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

inline void ergodox_led_all_off(void)
{
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

void ergodox_right_led_1_set(uint8_t n);
void ergodox_right_led_2_set(uint8_t n);
void ergodox_right_led_3_set(uint8_t n);

inline void ergodox_right_led_set(uint8_t led, uint8_t n){
    switch (led) {
    case 0:
        ergodox_right_led_1_set(n);
        break;
    case 1:
        ergodox_right_led_2_set(n);
        break;
    case 2:
        ergodox_right_led_3_set(n);
        break;
    }
}

inline void ergodox_led_all_set(uint8_t n) {
    ergodox_right_led_1_set(n);
    ergodox_right_led_2_set(n);
    ergodox_right_led_3_set(n);
}

void ergodox_infinity_lcd_color(uint16_t r, uint16_t g, uint16_t b);
