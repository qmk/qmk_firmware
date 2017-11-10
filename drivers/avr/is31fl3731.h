/* Copyright 2017 Jason Williams
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


#ifndef IS31FL3731_DRIVER_H
#define IS31FL3731_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct is31_led {
	uint8_t driver:2;
	uint8_t matrix:1;
	uint8_t control_index;
} __attribute__((packed)) is31_led;

extern const is31_led g_is31_leds[DRIVER_LED_TOTAL];

void map_index_to_led( uint8_t index, is31_led *led );

void IS31FL3731_init( uint8_t addr );
void IS31FL3731_write_register( uint8_t addr, uint8_t reg, uint8_t data );
void IS31FL3731_write_pwm_buffer( uint8_t addr, uint8_t *pwm_buffer );

void IS31FL3731_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3731_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

void IS31FL3731_set_led_control_register( uint8_t index, bool red, bool green, bool blue );

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3731_update_pwm_buffers( uint8_t addr1, uint8_t addr2 );
void IS31FL3731_update_led_control_registers( uint8_t addr1, uint8_t addr2 );

#endif // IS31FL3731_DRIVER_H
