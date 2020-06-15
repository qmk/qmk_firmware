#include "big_led.h"

void set_big_LED_r(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_R_PIN);
            writePin(BIG_LED_R_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_R_PIN);
            writePin(BIG_LED_R_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_g(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_G_PIN);
            writePin(BIG_LED_G_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_G_PIN);
            writePin(BIG_LED_G_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}

void set_big_LED_b(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(BIG_LED_B_PIN);
            writePin(BIG_LED_B_PIN, GPIO_STATE_HIGH);
        break;

        case LED_OFF:
            setPinOutput(BIG_LED_B_PIN);
            writePin(BIG_LED_B_PIN, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}