#include "lfk78.h"
#include <avr/wdt.h>

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;

void matrix_init_kb(void) {
    matrix_init_user();

#ifndef AUDIO_ENABLE
    // If we're not using the audio pin, drive it low
    gpio_set_pin_output(C6);
    gpio_write_pin_low(C6);
#endif

#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif
}

void matrix_scan_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif

    matrix_scan_user();
}

void clicking_notes(uint16_t freq, uint16_t duration) {
#ifdef AUDIO_ENABLE
    if (freq >= 100 && freq <= 20000 && duration < 100) {
        play_note(freq, 10);
        for (uint16_t i = 0; i < duration; i++) {
            _delay_ms(1);
        }
        stop_all_notes();
    }
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (click_toggle && record->event.pressed) {
        clicking_notes(click_hz, click_time);
    }

    if (keycode == QK_BOOT) {
        reset_keyboard_kb();
    }

    return process_record_user(keycode, record);
}

void reset_keyboard_kb(void) {
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif

    reset_keyboard();
}
