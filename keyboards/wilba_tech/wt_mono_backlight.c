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
#include "wt_rgb_backlight_api.h" // reuse these for now
#include "wt_rgb_backlight_keycodes.h" // reuse these for now

#include <stdlib.h>
#include <avr/interrupt.h>
#include "i2c_master.h"
#include "host.h"
#include "progmem.h"
#include "eeprom.h"

#include "via.h" // uses EEPROM address, lighting value IDs
#define MONO_BACKLIGHT_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

#if VIA_EEPROM_CUSTOM_CONFIG_SIZE == 0
#error VIA_EEPROM_CUSTOM_CONFIG_SIZE was not defined to store backlight_config struct
#endif

#include "drivers/led/issi/is31fl3736-mono.h"

#define BACKLIGHT_EFFECT_MAX 3

#ifndef MONO_BACKLIGHT_COLOR_1
#define MONO_BACKLIGHT_COLOR_1 { .h = 0, .s = 255 }
#endif

backlight_config g_config = {
    .disable_when_usb_suspended = MONO_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED,
    .disable_after_timeout = MONO_BACKLIGHT_DISABLE_AFTER_TIMEOUT,
    .brightness = MONO_BACKLIGHT_BRIGHTNESS,
    .effect = MONO_BACKLIGHT_EFFECT,
    .effect_speed = MONO_BACKLIGHT_EFFECT_SPEED,
    .color_1 = MONO_BACKLIGHT_COLOR_1,
};

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

void backlight_init_drivers(void)
{
    is31fl3736_init_drivers();
}

void backlight_set_key_hit(uint8_t row, uint8_t column)
{
    g_any_key_hit = 0;
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

void backlight_set_brightness_all( uint8_t value )
{
	is31fl3736_set_value_all( value );
}

void backlight_effect_all_off(void)
{
	is31fl3736_set_value_all( 0 );
}

void backlight_effect_all_on(void)
{
	is31fl3736_set_value_all( g_config.brightness );
}

void backlight_effect_raindrops(bool initialize)
{
    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % 96 : 255;

    for ( int i=0; i<96; i++ )
    {
        // If initialize, all get set to random brightness
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            is31fl3736_set_value(i, rand() & 0xFF );
        }
    }
}

void backlight_effect_cycle_all(void)
{
	uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;

	backlight_set_brightness_all( offset );
}

// This runs after another backlight effect and replaces
// colors already set
void backlight_effect_indicators(void)
{
#if defined(MONO_BACKLIGHT_WT75_A)
    hsv_t hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    rgb_t rgb = hsv_to_rgb( hsv );
    // SW7,CS8 = (6*8+7) = 55
    // SW8,CS8 = (7*8+7) = 63
    // SW9,CS8 = (8*8+7) = 71
    is31fl3736_set_value(55, rgb.r);
    is31fl3736_set_value(63, rgb.g);
    is31fl3736_set_value(71, rgb.b);
#endif // MONO_BACKLIGHT_WT75_A

// This pairs with "All Off" already setting zero brightness,
// and "All On" already setting non-zero brightness.
#if defined(MONO_BACKLIGHT_WT60_A) || \
defined(MONO_BACKLIGHT_WT65_A) || \
defined(MONO_BACKLIGHT_WT65_B) || \
defined(MONO_BACKLIGHT_WT75_A) || \
defined(MONO_BACKLIGHT_WT75_B) || \
defined(MONO_BACKLIGHT_WT75_C) || \
defined(MONO_BACKLIGHT_WT80_A)
    if ( host_keyboard_led_state().caps_lock ) {
        // SW3,CS1 = (2*8+0) = 16
        is31fl3736_set_value(16, 255);
    }
#endif
#if defined(MONO_BACKLIGHT_WT80_A)
    if ( host_keyboard_led_state().scroll_lock ) {
        // SW7,CS7 = (6*8+6) = 54
        is31fl3736_set_value(54, 255);
    }
#endif
#if defined(MONO_BACKLIGHT_WT75_C)
    if ( host_keyboard_led_state().scroll_lock ) {
        // SW7,CS8 = (6*8+7) = 55
        is31fl3736_set_value(55, 255);
    }
#endif
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

    if ( g_any_key_hit < 0xFFFFFFFF )
    {
        g_any_key_hit++;
    }

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool suspend_backlight = ((g_suspend_state && g_config.disable_when_usb_suspended) ||
            (g_config.disable_after_timeout > 0 && g_any_key_hit > g_config.disable_after_timeout * 60 * 20));
    uint8_t effect = suspend_backlight ? 0 : g_config.effect;

    // Keep track of the effect used last time,
    // detect change in effect, so each effect can
    // have an optional initialization.
    static uint8_t effect_last = 255;
    bool initialize = effect != effect_last;
    effect_last = effect;

    // this gets ticked at 20 Hz.
    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch ( effect )
    {
        case 0:
            backlight_effect_all_off();
            break;
        case 1:
            backlight_effect_all_on();;
            break;
        case 2:
            backlight_effect_raindrops(initialize);
            break;
        default:
            backlight_effect_all_off();
            break;
	}

    if ( ! suspend_backlight )
    {
        backlight_effect_indicators();
    }
}

// Some helpers for setting/getting HSV
void _set_color( HS *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HS *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

void backlight_config_set_value( uint8_t *data )
{
    bool reinitialize = false;
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_disable_when_usb_suspended:
        {
            g_config.disable_when_usb_suspended = (bool)*value_data;
            break;
        }
        case id_disable_after_timeout:
        {
            g_config.disable_after_timeout = *value_data;
            break;
        }
        case id_brightness:
        {
            g_config.brightness = *value_data;
            break;
        }
        case id_effect:
        {
            g_config.effect = *value_data;
            break;
        }
        case id_effect_speed:
        {
            g_config.effect_speed = *value_data;
            break;
        }
        case id_color_1:
        {
            _set_color( &(g_config.color_1), value_data );
            break;
        }
    }

    if ( reinitialize )
    {
        backlight_init_drivers();
    }
}

void backlight_config_get_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_disable_when_usb_suspended:
        {
            *value_data = ( g_config.disable_when_usb_suspended ? 1 : 0 );
            break;
        }
        case id_disable_after_timeout:
        {
            *value_data = g_config.disable_after_timeout;
            break;
        }
        case id_brightness:
        {
            *value_data = g_config.brightness;
            break;
        }
        case id_effect:
        {
            *value_data = g_config.effect;
            break;
        }
        case id_effect_speed:
        {
            *value_data = g_config.effect_speed;
            break;
        }
        case id_color_1:
        {
            _get_color( &(g_config.color_1), value_data );
            break;
        }
    }
}

void backlight_config_load(void)
{
    eeprom_read_block( &g_config, ((void*)MONO_BACKLIGHT_CONFIG_EEPROM_ADDR), sizeof(backlight_config) );
}

void backlight_config_save(void)
{
    eeprom_update_block( &g_config, ((void*)MONO_BACKLIGHT_CONFIG_EEPROM_ADDR), sizeof(backlight_config) );
}

void backlight_update_pwm_buffers(void)
{
    is31fl3736_flush();
}

bool process_record_backlight(uint16_t keycode, keyrecord_t *record)
{
    // Record keypresses for backlight effects
    if ( record->event.pressed )
    {
        backlight_set_key_hit( record->event.key.row, record->event.key.col );
    }

    switch(keycode)
    {
        case BR_INC:
            if (record->event.pressed)
            {
                backlight_brightness_increase();
            }
            return false;
            break;
        case BR_DEC:
            if (record->event.pressed)
            {
                backlight_brightness_decrease();
            }
            return false;
            break;
        case EF_INC:
            if (record->event.pressed)
            {
                backlight_effect_increase();
            }
            return false;
            break;
        case EF_DEC:
            if (record->event.pressed)
            {
                backlight_effect_decrease();
            }
            return false;
            break;
        case ES_INC:
            if (record->event.pressed)
            {
                backlight_effect_speed_increase();
            }
            return false;
            break;
        case ES_DEC:
            if (record->event.pressed)
            {
                backlight_effect_speed_decrease();
            }
            return false;
            break;
    }

    return true;
}

// Deals with the messy details of incrementing an integer
uint8_t increment( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value += step;
    return MIN( MAX( new_value, min ), max );
}

uint8_t decrement( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value -= step;
    return MIN( MAX( new_value, min ), max );
}

void backlight_effect_increase(void)
{
    g_config.effect = increment( g_config.effect, 1, 0, BACKLIGHT_EFFECT_MAX );
    backlight_config_save();
}

void backlight_effect_decrease(void)
{
    g_config.effect = decrement( g_config.effect, 1, 0, BACKLIGHT_EFFECT_MAX );
    backlight_config_save();
}

void backlight_effect_speed_increase(void)
{
    g_config.effect_speed = increment( g_config.effect_speed, 1, 0, 3 );
    backlight_config_save();
}

void backlight_effect_speed_decrease(void)
{
    g_config.effect_speed = decrement( g_config.effect_speed, 1, 0, 3 );
    backlight_config_save();
}

void backlight_brightness_increase(void)
{
    g_config.brightness = increment( g_config.brightness, 8, 0, 255 );
    backlight_config_save();
}

void backlight_brightness_decrease(void)
{
    g_config.brightness = decrement( g_config.brightness, 8, 0, 255 );
    backlight_config_save();
}

void backlight_device_indication(uint8_t value)
{
    static uint8_t current_effect = 0;
    static uint8_t alternate_effect = 0;
    if ( value == 0 ) {
        current_effect = g_config.effect;
        alternate_effect = g_config.effect > 0 ? 0 : 1;
    }
    g_config.effect = value % 2 == 0 ? alternate_effect : current_effect;
}
