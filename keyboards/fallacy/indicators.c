/* Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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

#include "indicators.h"
#include "drivers/issi/is31fl3731-simple.h"
#include "i2c_master.h"

/* Set up IS31FL3731 for use in powering indicator LEDs. Absolutely overkill for this job but it was already in the design.
 * init IS31FL3731 and i2c
 */
void init_fallacy_leds(void) {
    i2c_init();
    IS31FL3731_init(LED_DRIVER_ADDR_1);

    for (int i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        IS31FL3731_set_led_control_register(i, true);
    }

    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_1, 0);
}


/* update the buffer
 */
void update_fallacy_leds(void) {
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_1, 0);    
}


/* wrapper to actually set the LED PWM
 */
void set_fallacy_led(int index, bool state) {
    if (state) {
        IS31FL3731_set_value(index, 128);
    } 
    else {
        IS31FL3731_set_value(index, 0);
    }
}


/* define LED matrix
 */
const is31_led g_is31_leds[LED_DRIVER_LED_COUNT] = {
    {0, C1_1},
    {0, C2_1},
    {0, C3_1},
};
