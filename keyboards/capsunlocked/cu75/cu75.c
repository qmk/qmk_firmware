#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "cu75.h"
#include "keymap.h"
#include "debug.h"
#include "../lfkeyboards/issi.h"
#include "../lfkeyboards/TWIlib.h"
#include "../lfkeyboards/lighting.h"

#ifdef AUDIO_ENABLE
float test_sound[][2] = SONG(STARTUP_SOUND);
#include "audio.h"
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
    setPinInput(B5);
    writePinHigh(B5);
#else
    // If we're not using the audio pin, drive it low
    setPinOutput(C6);
    writePinLow(C6);
#endif
#ifdef ISSI_ENABLE
    issi_init();
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
        dprintf("TWI failed to recover, TWI re-init\n");
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
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);
    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == QK_BOOT) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}

void reset_keyboard_kb(){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}

// LFK lighting info
const uint8_t switch_matrices[] = {0, 1};
const uint8_t rgb_matrices[] = {6, 7};
const uint8_t rgb_sequence[] = {
    24, 23, 22, 21, 20, 19, 18, 17, 1, 2, 3, 4, 5,
    6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 9
};
