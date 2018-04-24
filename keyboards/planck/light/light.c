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

// const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
// /*   driver
//  *   |  matrix
//  *   |  |  control_index
//  *   |  |  |
//  *   |  |  |  */
//     {0, 0, 3},
//     {0, 0, 4},
//     {0, 0, 5},
//     {0, 1, 3},
//     {0, 1, 4},
//     {0, 1, 5},
//     {1, 0, 3},
//     {1, 0, 4},
//     {1, 0, 5},
//     {1, 1, 3},
//     {1, 1, 4},
//     {1, 1, 5},

//     {0, 0, 6},
//     {0, 0, 7},
//     {0, 0, 8},
//     {0, 1, 6},
//     {0, 1, 7},
//     {0, 1, 8},
//     {1, 0, 6},
//     {1, 0, 7},
//     {1, 0, 8},
//     {1, 1, 6},
//     {1, 1, 7},
//     {1, 1, 8},

//     {0, 0, 9},
//     {0, 0, 10},
//     {0, 0, 11},
//     {0, 1, 9},
//     {0, 1, 10},
//     {0, 1, 11},
//     {1, 0, 9},
//     {1, 0, 10},
//     {1, 0, 11},
//     {1, 1, 9},
//     {1, 1, 10},
//     {1, 1, 11},

//     {0, 0, 12},
//     {0, 0, 13},
//     {0, 0, 14},
//     {0, 1, 12},
//     {0, 1, 13},
// #ifdef PLANCK_MIT_LAYOUT
//     {0, 1, 14},
//     {0, 1, 15},
//     {1, 0, 12},
// #else
//     {0, 1, 14},
//     {0, 1, 15},
//     {1, 0, 12},
// #endif
//     {1, 0, 13},
//     {1, 0, 14},
//     {1, 1, 12},
//     {1, 1, 13},
//     {1, 1, 14},
// };


const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/*   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_1,  C2_1,  C4_1}, // LED1
    {0, C6_1,  C5_1,  C7_1}, // LED2
    {0, C4_2,  C3_2,  C5_2}, // LED3
    {0, C7_2,  C6_2,  C8_2}, // LED4
    {0, C2_3,  C1_3,  C3_3}, // LED5
    {0, C5_3,  C4_3,  C6_3}, // LED6
    {0, C8_3,  C7_3,  C9_3}, // LED7
    {0, C2_4,  C1_4,  C3_4}, // LED8
    {0, C6_4,  C5_4,  C7_4}, // LED9
    {0, C2_5,  C1_5,  C3_5}, // LED10
    {0, C7_5,  C6_5,  C8_5}, // LED11
    {0, C2_6,  C1_6,  C3_6}, // LED12
    {0, C5_6,  C4_6,  C6_6}, // LED13
    {0, C8_6,  C7_6,  C9_6}, // LED14
    {0, C2_7,  C1_7,  C3_7}, // LED15
    {0, C5_7,  C4_7,  C6_7}, // LED16
    {0, C2_8,  C1_8,  C3_8}, // LED17
    {0, C5_8,  C4_8,  C6_8}, // LED18

    {0, C3_9,  C2_9,  C4_9}, // LED19
    {0, C6_9,  C5_9,  C7_9}, // LED20
    {0, C4_10, C3_10, C5_10}, // LED21
    {0, C7_10, C6_10, C8_10}, // LED22
    {0, C2_11, C1_11, C3_11}, // LED23
    {0, C5_11, C4_11, C6_11}, // LED24

    {1, C3_1,  C2_1,  C4_1}, // LED1
    {1, C6_1,  C5_1,  C7_1}, // LED2
    {1, C4_2,  C3_2,  C5_2}, // LED3
    {1, C7_2,  C6_2,  C8_2}, // LED4
    {1, C2_3,  C1_3,  C3_3}, // LED5
    {1, C5_3,  C4_3,  C6_3}, // LED6
    {1, C8_3,  C7_3,  C9_3}, // LED7
    {1, C2_4,  C1_4,  C3_4}, // LED8
    {1, C6_4,  C5_4,  C7_4}, // LED9
    {1, C2_5,  C1_5,  C3_5}, // LED10
    {1, C7_5,  C6_5,  C8_5}, // LED11
    {1, C2_6,  C1_6,  C3_6}, // LED12
    {1, C5_6,  C4_6,  C6_6}, // LED13
    {1, C8_6,  C7_6,  C9_6}, // LED14
    {1, C2_7,  C1_7,  C3_7}, // LED15
    {1, C5_7,  C4_7,  C6_7}, // LED16
    {1, C2_8,  C1_8,  C3_8}, // LED17
    {1, C5_8,  C4_8,  C6_8}, // LED18

    {1, C3_9,  C2_9,  C4_9}, // LED19
    {1, C6_9,  C5_9,  C7_9}, // LED20
    {1, C4_10, C3_10, C5_10}, // LED21
    {1, C7_10, C6_10, C8_10}, // LED22
    {1, C2_11, C1_11, C3_11}, // LED23
    {1, C5_11, C4_11, C6_11} // LED24
};



const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {

    /*{row | col << 4}
      |             {x=0..224, y=0..64}
      |              |                    modifier
      |              |                    | */
    {{0|(0<<4)},   {20.36*0, 21.33*0}, 1},
    {{0|(1<<4)},   {20.36*1, 21.33*0}, 0},
    {{0|(2<<4)},   {20.36*2, 21.33*0}, 0},
    {{0|(3<<4)},   {20.36*3, 21.33*0}, 0},
    {{0|(4<<4)},   {20.36*4, 21.33*0}, 0},
    {{0|(5<<4)},   {20.36*5, 21.33*0}, 0},
    {{0|(6<<4)},   {20.36*6, 21.33*0}, 0},
    {{0|(7<<4)},   {20.36*7, 21.33*0}, 0},
    {{0|(8<<4)},   {20.36*8, 21.33*0}, 0},
    {{0|(9<<4)},   {20.36*9, 21.33*0}, 0},
    {{0|(10<<4)},  {20.36*10,21.33*0}, 0},
    {{0|(11<<4)},  {20.36*11,21.33*0}, 1},

    {{1|(0<<4)},   {20.36*0, 21.33*1}, 1},
    {{1|(1<<4)},   {20.36*1, 21.33*1}, 0},
    {{1|(2<<4)},   {20.36*2, 21.33*1}, 0},
    {{1|(3<<4)},   {20.36*3, 21.33*1}, 0},
    {{1|(4<<4)},   {20.36*4, 21.33*1}, 0},
    {{1|(5<<4)},   {20.36*5, 21.33*1}, 0},
    {{1|(6<<4)},   {20.36*6, 21.33*1}, 0},
    {{1|(7<<4)},   {20.36*7, 21.33*1}, 0},
    {{1|(8<<4)},   {20.36*8, 21.33*1}, 0},
    {{1|(9<<4)},   {20.36*9, 21.33*1}, 0},
    {{1|(10<<4)},  {20.36*10,21.33*1}, 0},
    {{1|(11<<4)},  {20.36*11,21.33*1}, 1},

    {{2|(0<<4)},  {20.36*0, 21.33*2}, 1},
    {{2|(1<<4)},  {20.36*1, 21.33*2}, 0},
    {{2|(2<<4)},  {20.36*2, 21.33*2}, 0},
    {{2|(3<<4)},  {20.36*3, 21.33*2}, 0},
    {{2|(4<<4)},  {20.36*4, 21.33*2}, 0},
    {{2|(5<<4)},  {20.36*5, 21.33*2}, 0},
    {{2|(6<<4)},  {20.36*6, 21.33*2}, 0},
    {{2|(7<<4)},  {20.36*7, 21.33*2}, 0},
    {{2|(8<<4)},  {20.36*8, 21.33*2}, 0},
    {{2|(9<<4)},  {20.36*9, 21.33*2}, 0},
    {{2|(10<<4)}, {20.36*10,21.33*2}, 0},
    {{2|(11<<4)}, {20.36*11,21.33*2}, 1},

    {{3|(0<<4)},  {20.36*0, 21.33*3}, 1},
    {{3|(1<<4)},  {20.36*1, 21.33*3}, 1},
    {{3|(2<<4)},  {20.36*2, 21.33*3}, 1},
    {{3|(3<<4)},  {20.36*3, 21.33*3}, 1},
    {{3|(4<<4)},  {20.36*4, 21.33*3}, 1},
#ifdef PLANCK_MIT_LAYOUT
    {{3|(5<<4)},  {20.36*5, 21.33*3}, 0},
    {{3|(5<<4)},  {20.36*5.5, 21.33*3}, 0},
    {{3|(5<<4)},  {20.36*6, 21.33*3}, 0},
#else
    {{3|(5<<4)},  {20.36*5, 21.33*3}, 0},
    {{0xFF},      {20.36*5.5, 21.33*3}, 0},
    {{3|(6<<4)},  {20.36*6, 21.33*3}, 0},
#endif
    {{3|(7<<4)},  {20.36*7, 21.33*3}, 1},
    {{3|(8<<4)},  {20.36*8, 21.33*3}, 1},
    {{3|(9<<4)},  {20.36*9, 21.33*3}, 1},
    {{3|(10<<4)}, {20.36*10,21.33*3}, 1},
    {{3|(11<<4)}, {20.36*11,21.33*3}, 1}
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
