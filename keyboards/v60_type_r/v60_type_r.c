/* Copyright 2017 benlyall, MechMerlin
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
#include "v60_type_r.h"

#include "quantum.h"

// if we've got an RGB underglow!
#ifdef RGBLIGHT_ENABLE

#define SOFTPWM_LED_TIMER_TOP F_CPU/(256*64)

extern rgblight_config_t rgblight_config;
static uint8_t softpwm_buff[3] = {0};

void matrix_init_kb(void) {
	rgb_init();
	matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	uint8_t r = led[0].r, g = led[0].g, b = led[0].b;
	switch(keycode) {
		case RGB_RI:
			if (record->event.pressed) {
				r += RGB_STEP;
				if (r < led[0].r) {
					r = 255;
				}
				rgblight_setrgb(r, g, b);
			}

			return false;
		case RGB_RD:
		  if (record->event.pressed) {
		  	r -= RGB_STEP;
				if (r > led[0].r) {
					r = 0;
				}
				rgblight_setrgb(r, g, b);
		  }

			return false;
		case RGB_BI:
			if (record->event.pressed) {
				b += RGB_STEP;
				if (b < led[0].b) {
					b = 255;
				}
				rgblight_setrgb(r, g, b);
			}

			return false;
		case RGB_BD:
		  if (record->event.pressed) {
		  	b -= RGB_STEP;
				if (b > led[0].b) {
					b = 0;
				}
				rgblight_setrgb(r, g, b);
		  }

			return false;
		case RGB_GI:
			if (record->event.pressed) {
				g += RGB_STEP;
				if (g < led[0].g) {
					g = 255;
				}
				rgblight_setrgb(r, g, b);
			}

			return false;
		case RGB_GD:
		  if (record->event.pressed) {
		  	g -= RGB_STEP;
				if (g > led[0].g) {
					g = 0;
				}
				rgblight_setrgb(r, g, b);
			}

			return false;
	}

	return process_record_user(keycode, record);
}


void rgb_timer_init(void) {
    /* Timer3 setup */
    /* CTC mode */
    TCCR3B |= _BV(WGM32);
    /* Clock select: clk/8 */
    TCCR3B |= _BV(CS30);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR3AH = (SOFTPWM_LED_TIMER_TOP >> 8) & 0xFF;
    OCR3AL = SOFTPWM_LED_TIMER_TOP & 0xFF;
    SREG = sreg;

    // Enable the compare match interrupt on timer 3
    TIMSK3 |= _BV(OCIE3A);
}

void rgb_init(void) {
    DDRF  |= (_BV(PF6) | _BV(PF5) | _BV(PF4));
    PORTF |= (_BV(PF6) | _BV(PF5) | _BV(PF4));

    rgb_timer_init();
}

void set_rgb_pin_on(uint8_t pin) {
	PORTF &= ~_BV(pin);
}

void set_rgb_pin_off(uint8_t pin) {
	PORTF |= _BV(pin);
}

void rgblight_set(void) {
	  // xprintf("Setting RGB underglow\n");
    if (!rgblight_config.enable) {
          led[0].r = 0;
          led[0].g = 0;
          led[0].b = 0;
          set_rgb_pin_off(RGB_RED_PIN);
          set_rgb_pin_off(RGB_GREEN_PIN);
          set_rgb_pin_off(RGB_BLUE_PIN);
    }

   //  //xprintf("Red: %u, Green: %u, Blue: %u\n", led[0].r, led[0].g, led[0].b);
}

ISR(TIMER3_COMPA_vect)
{
    static uint8_t pwm = 0;
    pwm++;

    // turn the LEDS on
    if (pwm == 0) {
    	if (softpwm_buff[0]) {
    		set_rgb_pin_on(RGB_RED_PIN);
    		softpwm_buff[0] = led[0].r;
    	}

    	if (softpwm_buff[1]) {
    		set_rgb_pin_on(RGB_GREEN_PIN);
    		softpwm_buff[1] = led[0].g;
    	}

    	if (softpwm_buff[2]) {
    		set_rgb_pin_on(RGB_BLUE_PIN);
    		softpwm_buff[2] = led[0].b;
    	}
    }

    // turn em off
  	if (pwm == softpwm_buff[0]) {
  		set_rgb_pin_off(RGB_RED_PIN);
  		softpwm_buff[0] = led[0].r;

  	}

  	if (pwm == softpwm_buff[1]) {
  		set_rgb_pin_off(RGB_GREEN_PIN);
    	softpwm_buff[1] = led[0].g;
  	}

  	if (pwm == softpwm_buff[2]) {
  		set_rgb_pin_off(RGB_BLUE_PIN);
    	softpwm_buff[2] = led[0].b;
  	}
}
#endif // RGBLIGHT_ENABLE
