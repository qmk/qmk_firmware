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

#ifdef AUDIO_ENABLE
    audio_init();
    PLAY_NOTE_ARRAY(test_sound, false, STACCATO);
    // Fix port B5
    cbi(DDRB, 5);
    sbi(PORTB, 5);
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
    /* FIXME(skullydazed):
     *     Originally this code always ran no matter what process_record_user() did.
     *     With this PR it will only run if process_record_user() returns true. We
     *     should think through the implications here.
     */
    // Test code that turns on the switch led for the key that is pressed
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);
    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return true;
}

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
#ifdef AUDIO_ENABLE
    int8_t sign = 1;
#endif
    if(id == LFK_ESC_TILDE){
        // Send ~ on shift-esc
        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
        method(shifted ? KC_GRAVE : KC_ESCAPE);
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
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}

void led_set_kb(uint8_t usb_led)
{
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    led_set_user(usb_led);
}

// LFK lighting info
const uint8_t switch_matrices[] = {0, 1};
const uint8_t rgb_matrices[] = {6, 7};
const uint8_t rgb_sequence[] = {
    24, 23, 22, 21, 20, 19, 18, 17, 1, 2, 3, 4, 5,
    6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 9
};
