
#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "lfk87.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"
#include "debug.h"
#include "quantum.h"

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;

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
    27, 29, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11, 15, 14, 20, 21, 22, 23, 24, 25, 26
};
