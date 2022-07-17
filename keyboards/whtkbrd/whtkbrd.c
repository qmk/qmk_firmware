/* Copyright 2022 Alexander Metz
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
#include "whtkbrd.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(LED_PWR_PIN);
    setPinOutput(LED_STAT_PIN);

    /* Turn on PWR LED to show startup. */
    pwr_led_on();
    stat_led_off();
}

void keyboard_post_init_kb(void) {
    /* Turn off PWR LED to show startup is complete. */
    pwr_led_off();
}

void pwr_led_on(void) {
    writePinHigh(LED_PWR_PIN);
}

void pwr_led_off(void) {
    writePinLow(LED_PWR_PIN);
}

void stat_led_on(void) {
    writePinHigh(LED_STAT_PIN);
}

void stat_led_off(void) {
    writePinLow(LED_STAT_PIN);
}