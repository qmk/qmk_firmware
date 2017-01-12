#include "vaek.h"
#include <avr/sfr_defs.h>
#include "avr/timer_avr.h"
#include "issi.h"
#include "lighting.h"
#include "TWILib.h"

uint8_t under_red = 255;
uint8_t under_green = 255;
uint8_t under_blue = 255;
uint8_t backlight = 255;
uint8_t led_toggle = 1;

uint16_t click_hz = 500;
uint16_t click_time = 2;
uint8_t click_toggle = 0;

void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();

    // Set up 16 bit PWM: Fast PWM, mode 15, inverted
    TCCR1A = 0b11111110;
    TCCR1B = 0b00011001;
    ICR1 = 0xFFFF;
    // PWM values - 0xFFFF = off, 0x0000 = max
    OCR1C = 0x0000; // B7 - Blue
    OCR1B = 0x0000; // B6 - Green
    OCR1A = 0x0FFF; // B5 - Red
    // Set as output
    DDRB |= 0b11100000;

#ifdef ISSI_ENABLE
    issi_init();
    // set_underglow(under_red, under_green, under_blue);
    // set_backlight(backlight);
    // activateLED(0, 9, 1, 255);
    // led_test();
#endif
}

void matrix_scan_kb(void)
{
#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    static uint32_t twi_last_ready = 0;
    if(twi_last_ready > 1000){
        // Its been way too long since the last ISSI update, reset the I2C bus and start again
        xprintf("TWI failed to recover, TWI re-init\n");
        twi_last_ready = 0;
        TWIInit();
        force_issi_refresh();
    }
    if(isTWIReady()){
        twi_last_ready = 0;
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, 0);
        if(issi_device){
            issi_device = 0;
        }else{
            issi_device = 3;
        }
    }else{
        twi_last_ready++;
    }
#endif
    // Update layer indicator LED
    //
    // Not sure how else to reliably do this... TMK has the 'hook_layer_change'
    // but can't find QMK equiv
    static uint32_t layer_indicator = -1;
    if(layer_indicator != layer_state){
        xprintf("%08lX(%u)\n", layer_state, biton32(layer_state));
        for(uint32_t i=0;; i++){
            // the layer_info list should end with layer 0xFFFF
            // it will break this out of the loop and define the unknown layer color
            if((layer_info[i].layer == (layer_state & layer_info[i].mask)) || (layer_info[i].layer == 0xFFFFFFFF)){
                OCR1A = layer_info[i].color.red;
                OCR1B = layer_info[i].color.green;
                OCR1C = layer_info[i].color.blue;
                layer_indicator = layer_state;
                break;
            }
        }
    }
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    // Test code that turns on the switch led for the key that is pressed
    //
    // xprintf("event: %d %d\n", record->event.key.col, record->event.key.row);
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);

    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    // xprintf("action_function: %d, opt: %02X\n", id, opt);
    if(id == LFK_ESC_TILDE){
        // Send ~ on shift-esc
        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        if(layer_state == 0){
            method(shifted ? KC_GRAVE : KC_ESCAPE);
        }else{
            method(shifted ? KC_ESCAPE : KC_GRAVE);
        }
        send_keyboard_report();
    }else if(event->event.pressed){
        switch(id){
            case LFK_CLEAR:
                // Go back to default layer
                layer_clear();
                break;
#ifdef ISSI_ENABLE
            case LFK_LED_TEST:
                led_test();
                break;
#endif
        }
    }
}

void reset_keyboard_kb(){
    xprintf("programming!\n");
    OCR1A = 0x0000; // B5 - Red
    OCR1B = 0x0FFF; // B6 - Green
    OCR1C = 0x0FFF; // B7 - Blue
    reset_keyboard();
}

void led_set_kb(uint8_t usb_led)
{
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}
