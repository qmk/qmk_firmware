#include QMK_KEYBOARD_H

/*KNOPS_MISC*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*KNOPS_LAYOUT*/

};

// M10-B LEDs are all in parallel and controlled by the QMK backlight
// functionality. LED functions here are for possible future use
// as layer indicators, etc. and not implemented yet.
//
// To implement LED functions here, QMK backlight functionality
// will need to be disabled either via rules.mk or config.h
// or overriding the backlight functions to do nothing.
//
// LEDs are driven by a transistor connected to pin C6.
//

void set_led_state(int ledId, bool state)
{
}

void led_init_ports()
{
}

void led_set_layer(int layer)
{
    led_init_ports();

    led_set_layer(0);

    /*KNOPS_SIMPLELED_STATES*/
}

void matrix_init_user(void)
{
    /*KNOPS_INIT*/
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    /*KNOPS_MACRO*/
    return NULL;
}

void matrix_scan_user(void)
{
    /*KNOPS_SCAN*/
}

void led_set_user(uint8_t usb_led)
{
    /*KNOPS_FUNCTIONALLED_STATES*/
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    /*KNOPS_PROCESS_STATE*/
    return NULL;
}
