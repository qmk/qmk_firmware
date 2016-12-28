#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include "lfk78.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"

#ifdef AUDIO_ENABLE
float test_sound[][2] = SONG(ODE_TO_JOY);
#include <audio/audio.h>
#endif


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

#ifdef AUDIO_ENABLE
    audio_init();
#else
    // If we're not using the audio pin, drive it low
    sbi(DDRC, 6);
    cbi(PORTC, 6);
#endif

#ifdef ISSI_ENABLE
    issi_init();
    set_underglow(under_red, under_green, under_blue);
    set_backlight(backlight);
#endif
}

void matrix_scan_kb(void)
{
#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    if(isTWIReady()){
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, 0);
        if(issi_device){
            issi_device = 0;
        }else{
            issi_device = 3;
        }
    }
#endif
    // Update layer indicator LED
    //
    // Not sure how else to reliably do this... TMK has the 'hook_layer_change'
    // but can't find QMK equiv
    static uint32_t layer_indicator = -1;
    if(layer_indicator != layer_state){
        for(uint32_t i=0;; i++){
            // the layer_info list should end with layer 0xFFFF
            // it will break this out of the loop and define the unknown layer color
            if((layer_info[i].layer == layer_state) || (layer_info[i].layer == 0xFFFF)){
                OCR1A = layer_info[i].color.red;
                OCR1B = layer_info[i].color.green;
                OCR1C = layer_info[i].color.blue;
                break;
            }
        }
    }
    matrix_scan_user();
}

void click(uint16_t freq, uint16_t duration){
#ifdef AUDIO_ENABLE
    if(freq >= 100 && freq <= 20000 && duration < 100){
        play_note(freq, 10);
        for (uint16_t i = 0; i < duration; i++){
            _delay_ms(1);
        }
        stop_all_notes();
    }
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    // Test code that turns on the switch led for the key that is pressed
    // xprintf("event: %d %d\n", record->event.key.col, record->event.key.row);
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);

    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
#if defined(ISSI_ENABLE) || defined(AUDIO_ENABLE)
    int8_t sign = 1;
#endif
    xprintf("action_function: %d, opt: %02X\n", id, opt);
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
            case LFK_LED_TOGGLE:
                if(led_toggle == 0){
                    led_toggle = 1;
                    set_backlight(backlight);
                    set_underglow(under_red, under_green, under_blue);
                }else{
                    led_toggle = 0;
                    set_backlight(0);
                    set_underglow(0, 0, 0);
                }
                issi_devices[0]->led_dirty = 1;
                issi_devices[3]->led_dirty = 1;
                break;
            case LFK_LED_DOWN:
                sign = -1;  // continue to next statement
            case LFK_LED_UP:
                // Change LEDs
                //  opt 0 : toggle all LEDs on/off
                //  opt -1 or 1 : increase or decrease brightness
                //  mods:
                //      None-    backlight
                //      Control- Red
                //      Alt-     Green
                //      Gui-     Blue
                led_toggle = 1;
                uint8_t mods = get_mods();
                if(mods == 0){
                    backlight += 32 * sign;
                    set_backlight(backlight);
                }else{
                    if(mods & MOD_LCTL){
                        under_red += 32 * sign;
                    }
                    if(mods & MOD_LALT){
                        under_green += 32 * sign;
                    }
                    if(mods & MOD_LGUI){
                        under_blue += 32 * sign;
                    }
                    set_underglow(under_red, under_green, under_blue);
                }
                issi_devices[0]->led_dirty = 1;
                issi_devices[3]->led_dirty = 1;
                break;
            case LFK_LED_TEST:
                led_test();
                break;
#endif
#ifdef AUDIO_ENABLE
            case LFK_CLICK_FREQ_LOWER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_FREQ_HIGHER:
                click_hz += sign * 100;
                xprintf("click_hz: %d\n", click_hz);
                click(click_hz, click_time);
                break;
            case LFK_CLICK_TOGGLE:
                if(click_toggle){
                    click_toggle = 0;
                    click(4000, 100);
                    click(1000, 100);
                }else{
                    click_toggle = 1;
                    click(1000, 100);
                    click(4000, 100);
                }
                break;
            case LFK_CLICK_TIME_SHORTER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_TIME_LONGER:
                click_time += sign;
                xprintf("click_time: %d\n", click_time);
                click(click_hz, click_time);
                break;
#endif
            case LFK_DEBUG_SETTINGS:
                xprintf("Click:\n");
                xprintf("  toggle: %d\n", click_toggle);
                xprintf("  freq(hz): %d\n", click_hz);
                xprintf("  duration(ms): %d\n", click_time);
                break;
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
