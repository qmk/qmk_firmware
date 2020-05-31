#pragma once

#include "quantum.h"

/* Optional big LED pins */
#define BIG_LED_R_PIN D7
#define BIG_LED_G_PIN C6
#define BIG_LED_B_PIN D0

#define LED_ON          2
#define LED_OFF         0

#define GPIO_STATE_LOW  0
#define GPIO_STATE_HIGH 1

//TODO: add PWN functionality

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