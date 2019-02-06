/* Copyright 2017 Cole Markham, WoodKeys.click
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "scarletbandana.h"
#include <LUFA/Common/Common.h>

#include "quantum.h"

#ifdef AUDIO_ENABLE
    float tone_startup[][2] = SONG(STARTUP_SOUND);
    float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void shutdown_user(void) {
    #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
    #endif
}


void matrix_init_kb(void)
{
  // This is required to access the pins in the F-register
  JTAG_DISABLE();
    debug_enable=true;
    print("sb matrix_init_kb\n");
#ifdef AUDIO_ENABLE
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
#endif


    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}

void matrix_scan_kb(void)
{
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Test code that turns on the switch led for the key that is pressed
    // set_backlight_by_keymap(record->event.key.col, record->event.key.row);
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	led_set_user(usb_led);
}

//void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
//{
//#ifdef AUDIO_ENABLE
//    int8_t sign = 1;
//#endif
//    if(id == LFK_ESC_TILDE){
//        // Send ~ on shift-esc
//        void (*method)(uint8_t) = (event->event.pressed) ? &add_key : &del_key;
//        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
//        method(shifted ? KC_GRAVE : KC_ESCAPE);
//        send_keyboard_report();
//    }else if(event->event.pressed){
//        switch(id){
//            case LFK_CLEAR:
//                // Go back to default layer
//                layer_clear();
//                break;
//#ifdef ISSI_ENABLE
//            case LFK_LED_TEST:
//                led_test();
//                break;
//#endif
//        }
//    }
//}

void reset_keyboard_kb(){
    xprintf("programming!\n");
    reset_keyboard();
}
