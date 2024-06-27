// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ergodox_ez.h"

void ergodox_right_led_1_set(uint8_t n) {
    OCR1A = n;
}
void ergodox_right_led_2_set(uint8_t n) {
    OCR1B = n;
}
void ergodox_right_led_3_set(uint8_t n) {
    OCR1C = n;
}

void keyboard_post_init_sub(void) {
    // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001; // set and configure fast PWM
    TCCR1B = 0b00001001; // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    setPinInput(B4);

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    setPinInputHigh(C7);
    setPinInputHigh(D4);
    setPinInputHigh(D5);
    setPinInputHigh(D7);
    setPinInputHigh(E6);

    setPinOutput(ERGODOX_LED_1_PIN);
    setPinOutput(ERGODOX_LED_2_PIN);
    setPinOutput(ERGODOX_LED_3_PIN);
}

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/*   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_1,  C2_1,  C4_1}, // LED1 on right
    {0, C6_1,  C5_1,  C7_1}, // LED2
    {0, C4_2,  C3_2,  C5_2}, // LED3
    {0, C7_2,  C6_2,  C8_2}, // LED4
    {0, C2_3,  C1_3,  C3_3}, // LED5
    {0, C5_3,  C4_3,  C6_3}, // LED6
    {0, C8_3,  C7_3,  C9_3}, // LED7
    {0, C2_4,  C1_4,  C3_4}, // LED8
    {0, C6_4,  C5_4,  C7_4}, // LED9
    {0, C2_5,  C1_5,  C3_5}, // LED10
    {0, C7_5,  C6_5,  C8_5}, // LED11
    {0, C2_6,  C1_6,  C3_6}, // LED12
    {0, C5_6,  C4_6,  C6_6}, // LED13
    {0, C8_6,  C7_6,  C9_6}, // LED14
    {0, C2_7,  C1_7,  C3_7}, // LED15
    {0, C5_7,  C4_7,  C6_7}, // LED16
    {0, C2_8,  C1_8,  C3_8}, // LED17
    {0, C5_8,  C4_8,  C6_8}, // LED18

    {0, C3_9,  C2_9,  C4_9}, // LED19
    {0, C6_9,  C5_9,  C7_9}, // LED20
    {0, C4_10, C3_10, C5_10}, // LED21
    {0, C7_10, C6_10, C8_10}, // LED22
    {0, C2_11, C1_11, C3_11}, // LED23
    {0, C5_11, C4_11, C6_11}, // LED24

    {1, C3_1,  C2_1,  C4_1}, // LED1 on left
    {1, C6_1,  C5_1,  C7_1}, // LED2
    {1, C4_2,  C3_2,  C5_2}, // LED3
    {1, C7_2,  C6_2,  C8_2}, // LED4
    {1, C2_3,  C1_3,  C3_3}, // LED5
    {1, C5_3,  C4_3,  C6_3}, // LED6
    {1, C8_3,  C7_3,  C9_3}, // LED7
    {1, C2_4,  C1_4,  C3_4}, // LED8
    {1, C6_4,  C5_4,  C7_4}, // LED9
    {1, C2_5,  C1_5,  C3_5}, // LED10
    {1, C7_5,  C6_5,  C8_5}, // LED11
    {1, C2_6,  C1_6,  C3_6}, // LED12
    {1, C5_6,  C4_6,  C6_6}, // LED13
    {1, C8_6,  C7_6,  C9_6}, // LED14
    {1, C2_7,  C1_7,  C3_7}, // LED15
    {1, C5_7,  C4_7,  C6_7}, // LED16
    {1, C2_8,  C1_8,  C3_8}, // LED17
    {1, C5_8,  C4_8,  C6_8}, // LED18

    {1, C3_9,  C2_9,  C4_9}, // LED19
    {1, C6_9,  C5_9,  C7_9}, // LED20
    {1, C4_10, C3_10, C5_10}, // LED21
    {1, C7_10, C6_10, C8_10}, // LED22
    {1, C2_11, C1_11, C3_11}, // LED23
    {1, C5_11, C4_11, C6_11} // LED24
};
#endif
