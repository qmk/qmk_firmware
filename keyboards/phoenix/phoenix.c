#include <hal.h>
#include "usb_main.h"
#include "phoenix.h"

void bootmagic_scan(void) {
    matrix_scan();
    wait_ms(5);
    matrix_scan();

    if ((matrix_get_row(0) & 1) || (matrix_get_row(6) & 1)) {
        palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPadMode(GPIOB, 5, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPadMode(GPIOB, 6, PAL_MODE_OUTPUT_PUSHPULL);
        led1_off();
        led2_off();
        led3_off();

        led3_on();
        wait_ms(50);
        led2_on();
        wait_ms(50);
        led1_on();
        wait_ms(50);

        led3_off();
        wait_ms(50);
        led2_off();
        wait_ms(50);
        led1_off();
        wait_ms(50);

        bootloader_jump();
    }
}

void keyboard_pre_init_kb(void) {
    palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 6, PAL_MODE_OUTPUT_PUSHPULL);
    led1_off();
    led2_off();
    led3_off();

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    led1_on();
    wait_ms(50);
    led2_on();
    wait_ms(50);
    led3_on();
    wait_ms(50);

    led1_off();
    wait_ms(50);
    led2_off();
    wait_ms(50);
    led3_off();
    wait_ms(50);

    keyboard_post_init_user();
}

void manipulate_led(uint32_t led, bool on) {
    switch (led) {
    case 1:
        on ? led1_on() : led1_off();
    case 2:
        on ? led2_on() : led2_off();
    case 3:
        on ? led3_on() : led3_off();
    }
}


layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);

    uint8_t layer = get_highest_layer(state);
    manipulate_led(1, layer  & 1);
    manipulate_led(2, layer >> 1 & 1);
    manipulate_led(3, layer >> 2 & 1);
    return state;
}
