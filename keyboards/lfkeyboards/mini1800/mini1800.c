
#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "mini1800.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"
#include "debug.h"

#include "quantum.h"

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;
float my_song[][2] = SONG(ZELDA_PUZZLE);

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
__attribute__((weak))
const Layer_Info layer_info[] = {
    // Layer     Mask           Red     Green   Blue
    {0x00000000, 0xFFFFFFFF, {0x00, 0xFF, 0x00}}, // base layers - green
    {0x00000002, 0xFFFFFFFE, {0x00, 0x00, 0xFF}}, // function layer - blue
    {0x00000004, 0xFFFFFFFC, {0xFF, 0x00, 0xFF}}, // settings layer - magenta
    {0xFFFFFFFF, 0xFFFFFFFF, {0xFF, 0xFF, 0xFF}}, // unknown layer - REQUIRED - white
};

void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    set_rgb(31, 0x00, 0x00, 0x00);  // Caps lock
    set_rgb(32, 0xFF, 0x00, 0x00);  // Layer indicator, start red
#ifndef AUDIO_ENABLE
    // If we're not using the audio pin, drive it low
    setPinOutput(C6);
    writePinLow(C6);
#endif
    _delay_ms(500);
#ifdef ISSI_ENABLE
    issi_init();
#endif
#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif
}

void matrix_scan_kb(void)
{
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif
#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    static uint32_t twi_last_ready = 0;
    if(twi_last_ready > 1000){
        // Its been way too long since the last ISSI update, reset the I2C bus and start again
        twi_last_ready = 0;
        TWIInit();
        force_issi_refresh();
    }
    if(isTWIReady()){
        twi_last_ready = 0;
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, issi_device);
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
        for(uint32_t i=0;; i++){
            // the layer_info list should end with layer 0xFFFF
            // it will break this out of the loop and define the unknown layer color
            if((layer_info[i].layer == (layer_state & layer_info[i].mask)) || (layer_info[i].layer == 0xFFFFFFFF)){
                set_rgb(32, layer_info[i].color.red, layer_info[i].color.green, layer_info[i].color.blue);
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
    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == QK_BOOT) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}

void reset_keyboard_kb(void){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    set_rgb(31, 0x00, 0xFF, 0xFF);
    set_rgb(32, 0x00, 0xFF, 0xFF);
    force_issi_refresh();
    reset_keyboard();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // Set capslock LED to Blue
        if (led_state.caps_lock) {
            set_rgb(31, 0x00, 0x00, 0x7F);
        } else{
            set_rgb(31, 0x00, 0x00, 0x00);
        }
    }
    return res;
}

// Lighting info, see lighting.h for details
const uint8_t switch_matrices[] = {0, 1};
const uint8_t rgb_matrices[] = {6, 7};

// RGB Map:
//   27  29  10   9   8   7   6
// 26                                   5
// 25                                   4
// 24                                   3
//   23  22  21  20  14  15  11   1   2
const uint8_t rgb_sequence[] = {
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 1, 2, 3, 4, 5, 6, 7, 8, 13, 14, 15, 16
};

// Maps switch LEDs from Row/Col to ISSI matrix.
// Value breakdown:
//     Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//             |   | ISSI Col  |    ISSI Row   |
//             /   |
//             Device
const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS] = {
    {0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x99, 0x98, 0x97, 0x96, 0x00, 0x95, 0x94, 0x93, 0x92, 0x91},
    {0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xB6, 0xA4, 0xA3, 0xA2, 0xA1},
    {0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0xB9, 0xB8, 0xB7, 0x00, 0x00, 0x00, 0xB5, 0xB3, 0x49, 0x48},
    {0x47, 0x00, 0x45, 0x44, 0x43, 0x42, 0x41, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0x00, 0xC2, 0x59, 0x58, 0x57, 0x56},
    {0x55, 0x51, 0xD6, 0x00, 0x00, 0xE5, 0x00, 0x00, 0x00, 0x00, 0xE4, 0xE3, 0xE2, 0x00, 0xE1, 0x00, 0x00, 0x00, 0x00}
};
