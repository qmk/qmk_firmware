#include "bluepad.h"
#include "issi.h"
#include <avr/sfr_defs.h>
#include "audio/audio.h"

void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();

    // Reset ISSI, wait 10ms and re-enable
    sbi(DDRF, 7);
    cbi(PORTF, 7);
    _delay_ms(10);
    sbi(PORTF, 7);
    _delay_ms(50);

    issi_init();

    // Turn on autoplay and start breathing
    // writeRegister8(0x0B, 0x00, 0x08);
    // writeRegister8(0x0B, 0x02, 0x01);
    // writeRegister8(0x0B, 0x08, 0x77);
    // writeRegister8(0x0B, 0x09, 0x11);

    activateLED(0, 2, 1, 255); // SW1 LED
    activateLED(0, 1, 1, 255); // SW2 LED
    activateLED(0, 1, 2, 255); // SW3 LED
    activateLED(0, 1, 3, 255); // SW4 LED

    activateLED(0, 1, 4, 255); // SW5 LED
    activateLED(0, 1, 5, 255); // SW6 LED
    activateLED(0, 1, 6, 255); // SW7 LED
    activateLED(0, 3, 6, 255); // SWPlus

    activateLED(0, 3, 1, 255); // SW9 LED
    activateLED(0, 3, 2, 255); // SW10
    activateLED(0, 2, 2, 255); // SW11
    activateLED(0, 3, 4, 255); // SWEnter

    activateLED(0, 2, 4, 255); // SW13
    activateLED(0, 2, 5, 255); // SW14
    activateLED(0, 2, 6, 255); // SW15
    activateLED(0, 4, 1, 255); // SW_Zero
    activateLED(0, 3, 3, 255); // SW19
    // Top Center
    // activateLED(9, 4, 64); // Red
    // activateLED(1, 8, 4, 64); // Green
    // activateLED(1, 7, 4, 255); // Blue

    // Bottom Center
    // activateLED(1, 9, 5, 64); // Red
    // activateLED(1, 8, 5, 64); // Green
    // activateLED(1, 7, 5, 64); // Blue
    // activateLED(1, 8, 4, 64); // Green
    // activateLED(1, 8, 3, 64); // Green
    // activateLED(1, 8, 2, 64); // Green
    // activateLED(1, 8, 1, 64); // Green

    activateLED(1, 9, 1, 50); // Red
    activateLED(1, 9, 2, 50); // Red
    activateLED(1, 9, 3, 50); // Red
    activateLED(1, 9, 4, 50); // Red
    activateLED(1, 9, 5, 50); // Red
    activateLED(1, 9, 6, 50); // Red

    // activateLED(1, 7, 1, 255); // Blue
    // activateLED(1, 7, 2, 255); // Blue
    // activateLED(1, 7, 3, 255); // Blue
    // activateLED(1, 7, 4, 255); // Blue
    // activateLED(1, 7, 5, 255); // Blue
    // activateLED(1, 7, 6, 255); // Blue

    // writeRegister8(0x0B, 0x08, 0x77);
    // writeRegister8(0x0B, 0x09, 0x47);

    // writeRegister8(0x0B, 0x08, 0x414);
    // writeRegister8(0x0B, 0x09, 0x17);
}

void set_underglow_rgb(uint8_t red, uint8_t green, uint8_t blue){
    for(uint8_t x = 1; x <= 6; x++){
        activateLED(1, 9, x, red);
    }
    for(uint8_t x = 1; x <= 6; x++){
        activateLED(1, 8, x, green);
    }
    for(uint8_t x = 1; x <= 6; x++){
        activateLED(1, 7, x, blue);
    }
}

void matrix_scan_kb(void)
{
    // Not sure how else to reliably do this... TMK has the 'hook_layer_change'
    // but can't find QMK equiv
    static uint32_t layer_indicator = -1;
    if(layer_indicator != layer_state){
        layer_indicator = layer_state;
        switch(layer_state){
            case 0: // default layer - green
                set_underglow_rgb(0, 255, 0);
                break;
            case 1: // phone - yellow?
                set_underglow_rgb(255, 255, 0);
                break;
            case 2: // phone - blue
                set_underglow_rgb(0, 0, 255);
                break;
            case 4: // program/debug - red
                set_underglow_rgb(255, 0, 100);
                break;
            default: // WTF? - white
                set_underglow_rgb(255, 255, 255);
        }
    }
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();

}

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware
    if (keycode == RESET) {
        // Make all LEDs flash
        writeRegister8(0x0B, 0x0A, 0x00);
        writeRegister8(0x0B, 0x05, 0b00101001);
        writeRegister8(0x0B, 0x0A, 0x01);
        xprintf("programming!\n");
    } else {
    }
    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led)
{
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}
