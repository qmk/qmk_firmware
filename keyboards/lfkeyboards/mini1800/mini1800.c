#include "mini1800.h"
#include <avr/wdt.h>

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;
float my_song[][2] = SONG(ZELDA_PUZZLE);

void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
#ifndef AUDIO_ENABLE
    // If we're not using the audio pin, drive it low
    setPinOutput(C6);
    writePinLow(C6);
#endif
    _delay_ms(500);
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
    }
    return process_record_user(keycode, record);
}

void reset_keyboard_kb(void){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}
