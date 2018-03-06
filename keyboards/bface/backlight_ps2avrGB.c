/* Copyright 2017 Sebastian Kaim
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

#ifdef BACKLIGHT_ENABLE

#include "backlight_ps2avrGB.h"
#define sbi(reg,bit)	reg |= (_BV(bit))
#define cbi(reg,bit)	reg &= (~_BV(bit))
#define PWM10	WGM10
#define PWM11	WGM11
#define COM1x1 COM1B1
#define OCR1x  OCR1B

void backlight_init_ports(void)
{
#if BACKLIGHT_ON_STATE == 0
	backlight_off();
#else
	backlight_on();
#endif

	// setup pwm
	// this bitmagic is sourced from the original firmware
	/*TCCR1B = ((TCCR1B & ~0x07) | 0x03);
	TCNT1H = 0;
	TCNT1L = 0;
	sbi(TIMSK, TOIE1);
	OCR1BH = 0;
	OCR1BL = 0;
	cbi(TCCR1A,PWM11);
	sbi(TCCR1A,PWM10);
	sbi(TCCR1A,COM1B1);
	cbi(TCCR1A,COM1B0);*/
	ICR1 = 0xFFFF;

    TCCR1A = _BV(COM1x1) | _BV(WGM11); // = 0b00001010;
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;

	backlight_init();
}

void backlight_set(uint8_t level)
{
	if( level == 0 ) {
		backlight_off();
	}
	else {
		backlight_on();
		/*uint8_t pwm = get_pwm_for_brightness(level);
		set_backlight_pwm(pwm);
		TCCR1A |= _BV(COM1x1);
		OCR1x = (level >= 2) ? 0xFFFF : 0x00FF;*/
	}
}

#define PWM_MAX 0xFF
uint8_t get_pwm_for_brightness(uint8_t level)
{
	// we need to cast up here to allow multiplication with 0xFF. We could also use floats, but this is probably a lot faster.
	uint16_t brightness = (uint16_t)level * (uint16_t)PWM_MAX / (uint16_t)BACKLIGHT_LEVELS;
	return (uint8_t)brightness;
}

void backlight_on(void)
{
	//_SFR_IO8(0x12) |= _BV(0x4);
	LED_PIN |= BACKLIGHT_PORT_NUM;
}

void backlight_off(void)
{
	//_SFR_IO8(0x12) &= ~_BV(0x4);
	LED_PIN &= ~BACKLIGHT_PORT_NUM;
}

void set_backlight_pwm(uint8_t level) {
	// this does not work (yet)
	//OCR1B = level;
}

#endif // BACKLIGHT_ENABLE
