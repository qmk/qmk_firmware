// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_ENABLE)
// clang-format off
led_config_t g_led_config = { {
    { NO_LED, 10, 11, NO_LED },
    {      9 , 8,  7, 6 },
    {      2,  3,  4, 5 },
    { NO_LED,  1,  0, NO_LED }
  }, {
                  { 122,  64 }, { 103,  64 },
    {  84,  45 }, { 103,  45 }, { 133,  45 }, { 152,  45 },
    { 152,  26 }, { 122,  26 }, { 103,  26 }, { 84,  26 },
                  { 103,   7 }, { 122,   7 }
  },
  {
       4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
       4, 4
  }
};
// clang-format on
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    }
    return true;
}
#endif

void work_louder_micro_led_1_on(void) {
    writePin(WORK_LOUDER_LED_PIN_1, true);
}
void work_louder_micro_led_2_on(void) {
    writePin(WORK_LOUDER_LED_PIN_2, true);
}
void work_louder_micro_led_3_on(void) {
    writePin(WORK_LOUDER_LED_PIN_3, true);
}

void work_louder_micro_led_1_off(void) {
    writePin(WORK_LOUDER_LED_PIN_1, false);
}
void work_louder_micro_led_2_off(void) {
    writePin(WORK_LOUDER_LED_PIN_2, false);
}
void work_louder_micro_led_3_off(void) {
    writePin(WORK_LOUDER_LED_PIN_3, false);
}

void work_louder_micro_led_all_on(void) {
    work_louder_micro_led_1_on();
    work_louder_micro_led_2_on();
    work_louder_micro_led_3_on();
}

void work_louder_micro_led_all_off(void) {
    work_louder_micro_led_1_off();
    work_louder_micro_led_2_off();
    work_louder_micro_led_3_off();
}

void work_louder_micro_led_1_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_1 == B7
    OCR1C = n;
#else
    n ? work_louder_micro_led_1_on() : work_louder_micro_led_1_off();
#endif
}
void work_louder_micro_led_2_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_2 == B6
    OCR1B = n;
#else
    n ? work_louder_micro_led_2_on() : work_louder_micro_led_2_off();
#endif
}
void work_louder_micro_led_3_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_3 == B5
    OCR1A = n;
#else
    n ? work_louder_micro_led_3_on() : work_louder_micro_led_3_off();
#endif
}

void work_louder_micro_led_all_set(uint8_t n) {
    work_louder_micro_led_1_set(n);
    work_louder_micro_led_2_set(n);
    work_louder_micro_led_3_set(n);
}

#ifdef DEFER_EXEC_ENABLE
uint32_t startup_animation(uint32_t trigger_time, void *cb_arg) {
    static uint8_t index = 0;

    switch (index) {
        case 0:
            work_louder_micro_led_1_on();
            break;
        case 1:
            work_louder_micro_led_2_on();
            break;
        case 2:
            work_louder_micro_led_3_on();
            break;
        case 3:
            work_louder_micro_led_1_off();
            break;
        case 4:
            work_louder_micro_led_2_off();
            break;
        case 5:
            work_louder_micro_led_3_off();
            break;
        default:
            return 0;
    }
    index++;
    return 100;
}
#endif

void matrix_init_kb(void) {

    setPinOutput(WORK_LOUDER_LED_PIN_1); // left led
    writePin(WORK_LOUDER_LED_PIN_1, false);
    setPinOutput(WORK_LOUDER_LED_PIN_2); // middle led
    writePin(WORK_LOUDER_LED_PIN_2, false);
    setPinOutput(WORK_LOUDER_LED_PIN_3); // right led
    writePin(WORK_LOUDER_LED_PIN_3, false);

#ifdef DEFER_EXEC_ENABLE
    defer_exec(500, startup_animation, NULL);
#else
    wait_ms(500);
    work_louder_micro_led_1_on();
    wait_ms(100);
    work_louder_micro_led_2_on();
    wait_ms(100);
    work_louder_micro_led_3_on();
    wait_ms(100);
    work_louder_micro_led_1_off();
    wait_ms(100);
    work_louder_micro_led_2_off();
    wait_ms(100);
    work_louder_micro_led_3_off();
    wait_ms(200);
#endif
    matrix_init_user();

}
