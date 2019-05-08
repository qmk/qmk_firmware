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

#include "wt_mono_backlight.h"
#include "drivers/avr/i2c_master.h"
#include "drivers/issi/is31fl3736.h"

#include <avr/interrupt.h>

#define ISSI_ADDR_DEFAULT 0x50

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;
uint8_t g_config_effect_speed = 0;
uint8_t g_config_brightness = 255;

void backlight_init_drivers(void)
{
	// Initialize I2C
	i2c_init();
	IS31FL3736_init( ISSI_ADDR_DEFAULT );

	for ( uint8_t index = 0; index < 96; index++ )	{
		IS31FL3736_mono_set_led_control_register( index, true );
	}
	IS31FL3736_update_led_control_registers( ISSI_ADDR_DEFAULT, 0x00 );
}


// This is (F_CPU/1024) / 20 Hz
// = 15625 Hz / 20 Hz
// = 781
#define TIMER3_TOP 781

void backlight_timer_init(void)
{
	static uint8_t backlight_timer_is_init = 0;
	if ( backlight_timer_is_init ) {
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
	uint8_t offset = ( g_tick << g_config_effect_speed ) & 0xFF;

	backlight_set_brightness_all( offset );
}

ISR(TIMER3_COMPA_vect)
{
	// delay 1 second before driving LEDs or doing anything else
	static uint8_t startup_tick = 0;
	if ( startup_tick < 20 ) {
		startup_tick++;
		return;
	}

	g_tick++;

	//backlight_effect_cycle_all();
	backlight_set_brightness_all( 255 );
}

void backlight_update_pwm_buffers(void)
{
	IS31FL3736_update_pwm_buffers(ISSI_ADDR_DEFAULT,0x00);
}

void backlight_set_brightness_all( uint8_t value )
{
	IS31FL3736_mono_set_brightness_all( value );
}

