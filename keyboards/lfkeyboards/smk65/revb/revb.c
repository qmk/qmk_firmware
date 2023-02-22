/*
Copyright 2020 LFKeyboards
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "smk65.h"
#include "keymap.h"
#include "debug.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"

uint16_t click_hz = CLICK_HZ;
uint16_t click_time = CLICK_MS;
uint8_t click_toggle = CLICK_ENABLED;


void matrix_init_kb(void)
{
    matrix_init_user();

#ifdef AUDIO_ENABLE
    // audio_init() sets PB5 to output and drives it low, which breaks our matrix
    // so reset PB5 to input
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
// const uint8_t rgb_sequence[] = {
//     14, 24, 23, 22, 21, 20, 19, 18, 26, 25, 28, 29,
//     30, 31, 32, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
// };
const uint8_t rgb_sequence[] = {
    25, 28, 29,
    30, 31, 32, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};
// Maps switch LEDs from Row/Col to ISSI matrix.
// Value breakdown:
//     Bit     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//            /    \ ISSI Col  |    ISSI Row   |
//          matrix idx
// const uint8_t switch_leds[MATRIX_ROWS][MATRIX_COLS] =
// KEYMAP(
//   0x19, 0x18,   0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94,   0x93,   0x92, 0x91,
//   0x29, 0x28,    0x27,  0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3,   0xA2, 0xA1,
//   0x39, 0x38,      0x37,  0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5,     0xB3,
//   0x49, 0x48,    0x47,     0x45, 0x44, 0x43, 0x42, 0x41, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5,          0xC4,   0xC2,
//   0x59, 0x58,   0x57,  0x56,  0x55,             0x51,                   0xD6, 0xE5, 0xE4,         0xE3, 0xE2, 0xE1);
