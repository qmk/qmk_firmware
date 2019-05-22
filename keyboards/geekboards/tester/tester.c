#include "tester.h"
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C1_5,   C2_5,   C3_5}, //A5
    {0, C1_6,   C2_6,   C3_6}, //A6
    {0, C1_7,   C2_7,   C3_7}, //A7
    {0, C1_8,   C2_8,   C3_8}, //A8
};

led_config_t g_led_config = { 
{
    {  0,  1,  2,  3},
    {  4,  5,  6,  7}
}, 
{
    { 0,   0 }, { 75,   0 }, { 151,   0 }, { 224,   0 }, { 0,   64 }, { 75,   64 }, { 151,   64 }, { 224,  64 }
}, 
{
    4, 4, 4, 4, 4, 4, 4, 4
} 
};



void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_user(keycode, record);
}

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
        suspend_power_down_user();
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
