/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
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

#include "light.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/*   driver
 *   |  matrix
 *   |  |  modifier
 *   |  |  |  control_index
 *   |  |  |  |  {row | col << 4}
 *   |  |  |  |  |             {x=0..224, y=0..64} */
    {0, 0, 1, 3, {0|(0<<4)},   {20.36*0, 21.33*0}},
    {0, 0, 0, 4, {0|(1<<4)},   {20.36*1, 21.33*0}},  
    {0, 0, 0, 5, {0|(2<<4)},   {20.36*2, 21.33*0}},  
    {0, 1, 0, 3, {0|(3<<4)},   {20.36*3, 21.33*0}},  
    {0, 1, 0, 4, {0|(4<<4)},   {20.36*4, 21.33*0}},
    {0, 1, 0, 5, {0|(5<<4)},   {20.36*5, 21.33*0}}, 
    {1, 0, 0, 3, {0|(6<<4)},   {20.36*6, 21.33*0}},  
    {1, 0, 0, 4, {0|(7<<4)},   {20.36*7, 21.33*0}},  
    {1, 0, 0, 5, {0|(8<<4)},   {20.36*8, 21.33*0}},  
    {1, 1, 0, 3, {0|(9<<4)},   {20.36*9, 21.33*0}},  
    {1, 1, 0, 4, {0|(10<<4)},  {20.36*10,21.33*0}},  
    {1, 1, 1, 5, {0|(11<<4)},  {20.36*11,21.33*0}},

    {0, 0, 1, 6, {1|(0<<4)},   {20.36*0, 21.33*1}},  
    {0, 0, 0, 7, {1|(1<<4)},   {20.36*1, 21.33*1}},  
    {0, 0, 0, 8, {1|(2<<4)},   {20.36*2, 21.33*1}},  
    {0, 1, 0, 6, {1|(3<<4)},   {20.36*3, 21.33*1}},  
    {0, 1, 0, 7, {1|(4<<4)},   {20.36*4, 21.33*1}}, 
    {0, 1, 0, 8, {1|(5<<4)},   {20.36*5, 21.33*1}}, 
    {1, 0, 0, 6, {1|(6<<4)},   {20.36*6, 21.33*1}},  
    {1, 0, 0, 7, {1|(7<<4)},   {20.36*7, 21.33*1}},  
    {1, 0, 0, 8, {1|(8<<4)},   {20.36*8, 21.33*1}},  
    {1, 1, 0, 6, {1|(9<<4)},   {20.36*9, 21.33*1}},  
    {1, 1, 0, 7, {1|(10<<4)},  {20.36*10,21.33*1}},  
    {1, 1, 1, 8, {1|(11<<4)},  {20.36*11,21.33*1}},

    {0, 0, 1, 9,  {2|(0<<4)},  {20.36*0, 21.33*2}},  
    {0, 0, 0, 10, {2|(1<<4)},  {20.36*1, 21.33*2}}, 
    {0, 0, 0, 11, {2|(2<<4)},  {20.36*2, 21.33*2}}, 
    {0, 1, 0, 9,  {2|(3<<4)},  {20.36*3, 21.33*2}},  
    {0, 1, 0, 10, {2|(4<<4)},  {20.36*4, 21.33*2}}, 
    {0, 1, 0, 11, {2|(5<<4)},  {20.36*5, 21.33*2}}, 
    {1, 0, 0, 9,  {2|(6<<4)},  {20.36*6, 21.33*2}},  
    {1, 0, 0, 10, {2|(7<<4)},  {20.36*7, 21.33*2}}, 
    {1, 0, 0, 11, {2|(8<<4)},  {20.36*8, 21.33*2}}, 
    {1, 1, 0, 9,  {2|(9<<4)},  {20.36*9, 21.33*2}},  
    {1, 1, 0, 10, {2|(10<<4)}, {20.36*10,21.33*2}}, 
    {1, 1, 1, 11, {2|(11<<4)}, {20.36*11,21.33*2}},

    {0, 0, 1, 12, {3|(0<<4)},  {20.36*0, 21.33*3}}, 
    {0, 0, 1, 13, {3|(1<<4)},  {20.36*1, 21.33*3}}, 
    {0, 0, 1, 14, {3|(2<<4)},  {20.36*2, 21.33*3}}, 
    {0, 1, 1, 12, {3|(3<<4)},  {20.36*3, 21.33*3}}, 
    {0, 1, 1, 13, {3|(4<<4)},  {20.36*4, 21.33*3}}, 
#ifdef PLANCK_MIT_LAYOUT
    {0, 1, 0, 14, {3|(5<<4)},  {20.36*5, 21.33*3}}, 
    {0, 1, 0, 15, {3|(5<<4)},  {20.36*5.5, 21.33*3}}, 
    {1, 0, 0, 12, {3|(5<<4)},  {20.36*6, 21.33*3}}, 
#else
    {0, 1, 0, 14, {3|(5<<4)},  {20.36*5, 21.33*3}}, 
    {0, 1, 0, 15, {0xFF},      {20.36*5.5, 21.33*3}}, 
    {1, 0, 0, 12, {3|(6<<4)},  {20.36*6, 21.33*3}}, 
#endif
    {1, 0, 1, 13, {3|(7<<4)},  {20.36*7, 21.33*3}}, 
    {1, 0, 1, 14, {3|(8<<4)},  {20.36*8, 21.33*3}}, 
    {1, 1, 1, 12, {3|(9<<4)},  {20.36*9, 21.33*3}}, 
    {1, 1, 1, 13, {3|(10<<4)}, {20.36*10,21.33*3}}, 
    {1, 1, 1, 14, {3|(11<<4)}, {20.36*11,21.33*3}}
};


void matrix_init_kb(void) {

    // Initialize LED drivers for backlight.
    backlight_init_drivers();
    
    backlight_timer_init();
    backlight_timer_enable();

    // Turn status LED on
    DDRD |= (1<<6);
    PORTD |= (1<<6);

    matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    // Record keypresses for backlight effects
    if ( record->event.pressed ) {
        backlight_set_key_hit( record->event.key.row, record->event.key.col );
    } else {
        // backlight_unset_key_hit( record->event.key.row, record->event.key.col );
    }
    
    return process_record_user(keycode, record);
}

uint16_t backlight_task_counter = 0;

void matrix_scan_kb(void)
{

    // if (backlight_task_counter == 0)
        backlight_rgb_task();
        // backlight_effect_single_LED_test();
    // backlight_task_counter = ((backlight_task_counter + 1) % 5);

    // This only updates the LED driver buffers if something has changed.
    backlight_update_pwm_buffers();

    matrix_scan_user();
}

void led_set_kb(uint8_t usb_led)
{
    backlight_set_indicator_state(usb_led);
    //backlight_debug_led(usb_led & (1<<USB_LED_CAPS_LOCK));
}

void suspend_power_down_kb(void)
{
    backlight_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    backlight_set_suspend_state(false);
}
