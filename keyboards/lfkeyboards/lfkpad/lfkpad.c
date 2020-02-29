#include "lfkpad.h"

#include "quantum.h"

#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;

void matrix_init_kb(void) {
    matrix_init_user();

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

void matrix_scan_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif

#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    static uint32_t twi_last_ready = 0;

    if (twi_last_ready > 1000) {
        // It's been way too long since the last ISSI update, reset the I2C bus and start again
        dprintf("TWI failed to recover, TWI re-init\n");
        twi_last_ready = 0;
        TWIInit();
        force_issi_refresh();
    }

    if (isTWIReady()) {
        twi_last_ready = 0;
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, issi_device);

        if (issi_device) {
            issi_device = 0;
        } else {
            issi_device = 3;
        }
    } else {
        twi_last_ready++;
    }
#endif

    matrix_scan_user();
}

void click(uint16_t freq, uint16_t duration) {
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
    /* FIXME(skullydazed):
     *     Originally this code always ran no matter what process_record_user() did.
     *     With this PR it will only run if process_record_user() returns true. We
     *     should think through the implications here.
     */
    if (click_toggle && record->event.pressed) {
        click(click_hz, click_time);
    }

    if (keycode == RESET) {
        reset_keyboard_kb();
    }

    return true;
}

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt) {
#ifdef AUDIO_ENABLE
    int8_t sign = 1;
#endif

    if (id == LFK_ESC_TILDE) {
        // Send ~ on shift-esc
        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;

        if (layer_state == 0) {
            method(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
            method(shifted ? KC_ESCAPE : KC_GRAVE);
        }
        send_keyboard_report();
    } else if (event->event.pressed) {
        switch (id) {
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
                sign = -1; // continue to next statement
            case LFK_CLICK_FREQ_HIGHER:
                click_hz += sign * 100;
                click(click_hz, click_time);
                break;
            case LFK_CLICK_TOGGLE:
                if (click_toggle) {
                    click_toggle = 0;
                    click(4000, 100);
                    click(1000, 100);
                } else {
                    click_toggle = 1;
                    click(1000, 100);
                    click(4000, 100);
                }
                break;
            case LFK_CLICK_TIME_SHORTER:
                sign = -1; // continue to next statement
            case LFK_CLICK_TIME_LONGER:
                click_time += sign;
                click(click_hz, click_time);
                break;
#endif
        }
    }
}

void reset_keyboard_kb() {
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif

    reset_keyboard();
}

// LFK lighting info
const uint8_t rgb_matrices[] = { 0, 1 };
const uint8_t rgb_sequence[] = {
    32,  1,  2,  3,
    31, 30,  5,  6,
    28, 27,  7,
    17, 18,  9,  8,
    19, 21, 11,
      22,   14, 12,

    16,         26,
     4,         25,
    13,         24,
          20
};
