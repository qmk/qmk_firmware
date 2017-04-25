#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include "lfk78.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"
#include "debug.h"

#define BACKLIGHT_BREATHING
#include "quantum.h"

#ifdef AUDIO_ENABLE
float test_sound[][2] = SONG(ODE_TO_JOY);
#include <audio/audio.h>
#endif

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;


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
        dprintf("TWI failed to recover, TWI re-init\n");
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
        dprintf("%08lX(%u)\n", layer_state, biton32(layer_state));
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
    // dprintf("event: %d %d\n", record->event.key.col, record->event.key.row);
    set_backlight_by_keymap(record->event.key.col, record->event.key.row);
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
#ifdef AUDIO_ENABLE
    int8_t sign = 1;
#endif
    dprintf("action_function: %d, opt: %02X\n", id, opt);
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
            case LFK_SET_DEFAULT_LAYER:
                // set/save the current base layer to eeprom, falls through to LFK_CLEAR
                eeconfig_update_default_layer(1UL << opt);
                default_layer_set(1UL << opt);
            case LFK_CLEAR:
                // Go back to default layer
                layer_clear();
                break;
#ifdef ISSI_ENABLE
            case LFK_LED_TEST:
                led_test();
                break;
#endif
#ifdef AUDIO_ENABLE
            case LFK_CLICK_FREQ_LOWER:
                sign = -1;  // continue to next statement
            case LFK_CLICK_FREQ_HIGHER:
                click_hz += sign * 100;
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
                click(click_hz, click_time);
                break;
#endif
            case LFK_DEBUG_SETTINGS:
                dprintf("Click:\n");
                dprintf("  toggle: %d\n", click_toggle);
                dprintf("  freq(hz): %d\n", click_hz);
                dprintf("  duration(ms): %d\n", click_time);
                break;
        }
    }
}

void reset_keyboard_kb(){
    dprintf("programming!\n");
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
