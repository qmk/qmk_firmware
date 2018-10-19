/* Copyright 2018 Jason Williams (Wilba)
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
#if RGB_BACKLIGHT_ENABLED

#include "rgb_backlight.h"
//#include "rgb_backlight_api.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "progmem.h"

#include "quantum/color.h"
#include "drivers/avr/i2c_master.h"
#include "drivers/issi/is31fl3218.h"

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;
uint8_t g_config_effect_speed = 0;
uint8_t g_config_brightness = 255;

void backlight_update_pwm_buffers(void)
{
	IS31FL3218_update_pwm_buffers();
}

void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
	IS31FL3218_set_color( index, red, green, blue );
}

void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
	IS31FL3218_set_color_all( red, green, blue );
}


// This is (F_CPU/1024) / 20 Hz
// = 15625 Hz / 20 Hz
// = 781
#define TIMER3_TOP 260

void backlight_timer_init(void)
{
	static uint8_t backlight_timer_is_init = 0;
	if ( backlight_timer_is_init )
	{
		return;
	}
	backlight_timer_is_init = 1;

	// Timer 3 setup
	TCCR3B = _BV(WGM32) | 			// CTC mode OCR3A as TOP
			 _BV(CS32) | _BV(CS30); // prescale by /1024
	// Set TOP value
	uint8_t sreg = SREG;
	cli();

	OCR3AH = (TIMER3_TOP >> 8) & 0xff;
	OCR3AL = TIMER3_TOP & 0xff;
	SREG = sreg;
}

void backlight_timer_enable(void)
{
	TIMSK3 |= _BV(OCIE3A);
}

void backlight_timer_disable(void)
{
	TIMSK3 &= ~_BV(OCIE3A);
}

void backlight_set_suspend_state(bool state)
{
	g_suspend_state = state;
}

void backlight_effect_cycle_all(void)
{
	uint8_t hueOffset = ( g_tick << g_config_effect_speed ) & 0xFF;
	uint8_t satOffset = 127;
	// Relies on hue being 8-bit and wrapping
	for ( int i=0; i<6; i++ )
	{
		HSV hsv = { .h = hueOffset, .s = satOffset, .v = g_config_brightness };
		RGB rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

ISR(TIMER3_COMPA_vect)
{
	// delay 1 second before driving LEDs or doing anything else
	static uint8_t startup_tick = 0;
	if ( startup_tick < 20 )
	{
		startup_tick++;
		return;
	}

	g_tick++;

	if ( g_suspend_state )
	{
		backlight_set_color_all( 0, 0, 0 );
	}
	else
	{
		//HSV hsv = { .h = 240, .s = 255, .v = g_config_brightness };
		//RGB rgb = hsv_to_rgb( hsv );
		//backlight_set_color_all( rgb.r, rgb.g, rgb.b );
		backlight_effect_cycle_all();
	}
}

void backlight_init_drivers(void)
{
	// Initialize I2C
	i2c_init();
	IS31FL3218_init();
}

#endif // RGB_BACKLIGHT_ENABLED
