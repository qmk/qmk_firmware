#include "cu75.h"
#include <avr/wdt.h>

#ifdef AUDIO_ENABLE
float test_sound[][2] = SONG(STARTUP_SOUND);
#endif

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;


void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();

#ifdef AUDIO_ENABLE
    audio_init();
    PLAY_SONG(test_sound);
    // Fix port B5
    gpio_set_pin_input(B5);
    gpio_write_pin_high(B5);
#else
    // If we're not using the audio pin, drive it low
    gpio_set_pin_output(C6);
    gpio_write_pin_low(C6);
#endif
}

void housekeeping_task_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif
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
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);
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
