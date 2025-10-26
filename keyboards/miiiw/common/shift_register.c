/* Copyright 2023 ArthurCyy <https://github.com/ArthurCyy>
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

#include "shift_register.h"
#include <string.h>

static void shift_out(void);

static uint8_t shift_values[SHR_SERIES_NUM] = {0};

void shift_init(void) {
#ifdef SHR_OE_PIN
    gpio_set_pin_output(SHR_OE_PIN);
    gpio_write_pin_high(SHR_OE_PIN);
#endif
    gpio_set_pin_output(SHR_DATA_PIN);
    gpio_set_pin_output(SHR_LATCH_PIN);
    gpio_set_pin_output(SHR_CLOCK_PIN);
}

void shift_enable(void) {
#ifdef SHR_OE_PIN
    gpio_write_pin_low(SHR_OE_PIN);
#endif
    gpio_write_pin_low(SHR_DATA_PIN);
    gpio_write_pin_low(SHR_LATCH_PIN);
    gpio_write_pin_low(SHR_CLOCK_PIN);
}

void shift_disable(void) {
#ifdef SHR_OE_PIN
    gpio_write_pin_high(SHR_OE_PIN);
#endif
    gpio_write_pin_low(SHR_DATA_PIN);
    gpio_write_pin_low(SHR_LATCH_PIN);
    gpio_write_pin_low(SHR_CLOCK_PIN);
}

void shift_writePin(pin_t pin, int level) {
	uint8_t group = (pin - H0) >> 3;
	uint8_t	bit = 0x01 << ((pin - H0)&0x07);

    if(group >= SHR_SERIES_NUM) 
        return;

    if(level)
        shift_values[group] |= bit;
    else
        shift_values[group] &= ~bit;
    shift_out();
}

void shift_writeGroup(int group, uint8_t value) {
    if(group >= SHR_SERIES_NUM) 
        return;

    shift_values[group] = value;
    shift_out();
}

void shift_writeAll(int level) {
    memset(shift_values, level ? 0xFF : 0, sizeof(shift_values));
    shift_out();
}

static void shift_out(void) {
    uint8_t n = SHR_SERIES_NUM;
    gpio_write_pin_low(SHR_LATCH_PIN);
    while(n--){
        for (uint8_t i = 0; i < 8; i++) {
            gpio_write_pin_low(SHR_CLOCK_PIN);
            gpio_write_pin(SHR_DATA_PIN, shift_values[n] & (0x80 >> i));
            gpio_write_pin_high(SHR_CLOCK_PIN);
	    }
    }
    gpio_write_pin_high(SHR_LATCH_PIN);
}
