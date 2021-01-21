/* Copyright (C) 2021 @filterpaper
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

/* Three custom matrix animation that were collected
   from reddit users.
 */  


// Custom RGB_MATRIX_EFFECT macro declaration 
RGB_MATRIX_EFFECT(FRACTAL)
RGB_MATRIX_EFFECT(FRACTAL_RGB)
RGB_MATRIX_EFFECT(kitt_effect)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS


/*
FRACTAL effect
by u/_GEIST_/
https://www.reddit.com/r/MechanicalKeyboards/comments/jyx2zm/i_created_a_custom_rgb_animation_two_more_in_the/
Effect is optimised for ortholinea 4x12
 */

uint32_t f_timer = 0;

uint8_t halfArray[6][4];
uint8_t fullArray[12][4];
uint8_t halfbottom[3];
uint8_t fullbottom[6];
uint8_t displArray[54];

static bool FRACTAL(effect_params_t* params) {
	uint16_t f_speed = (400 / rgb_matrix_config.speed) * 127;

	if (f_timer > g_rgb_timer) return false;

	if (params->init) srand(g_rgb_timer);

	HSV hsv = rgb_matrix_config.hsv;
	RGB rgb = hsv_to_rgb(hsv);
	RGB_MATRIX_USE_LIMITS(led_min, led_max);
	for (int j = led_min; j < led_max; j++) {
		int i = j > 41 ? j + 1 : j;
		if (displArray[i]) rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
		else rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
	}

	if (led_max == DRIVER_LED_TOTAL) {
		f_timer = g_rgb_timer + f_speed;

		// move columns
		for (uint8_t col = 5; col > 0; col--) {
			for (uint8_t row = 0; row < 4; row++) {
				halfArray[col][row] = halfArray[col-1][row];
			}
		}
		//bottom
		for (uint8_t col = 2; col > 0; col--) {
			halfbottom[col] = halfbottom[col-1];
		}

		// random fill first column
		for (uint8_t row = 0; row < 4; row++) {
			halfArray[0][row] = rand() % 2;
		}
		// bottom
		halfbottom[0] = rand() % 2;

		// transfer to big array
		for (uint8_t col = 0; col < 6; col++) {
			for (uint8_t row = 0; row < 4; row++){
				fullArray[5 - col][row] = halfArray[col][row];
				fullArray[6 + col][row] = halfArray[col][row];
			}
		}
		//bottom
		for (uint8_t col = 0; col < 3; col++){
			fullbottom[2 - col] = halfbottom[col];
			fullbottom[3 + col] = halfbottom[col];
		}

		// transfer to matrix array
		uint8_t k = 0;
		for (uint8_t row = 0; row < 4; row++) {
			for (uint8_t col = 0; col < 12; col++) {
				displArray[k] = fullArray[col][row];
				k++;
			}
		}
		//bottom
		uint8_t l = 48;
		for (uint8_t col = 0; col < 6; col++) {
			displArray[l] = fullbottom[col];
			l++;
		}
	}

	return led_max < DRIVER_LED_TOTAL;
}


/*
FRACTAL RGB
by u/_GEIST_/
https://www.reddit.com/r/MechanicalKeyboards/comments/jyx2zm/i_created_a_custom_rgb_animation_two_more_in_the/
Effect is optimised for ortholinea 4x12
 */ 

uint32_t frgb_timer = 0;

uint8_t rgb_halfArray[6][4];
uint8_t rgb_fullArray[12][4];
uint8_t rgb_halfbottom[3];
uint8_t rgb_fullbottom[6];
uint8_t rgb_displArray[54];

static bool FRACTAL_RGB(effect_params_t* params) {
	uint16_t frgb_speed = (400 / rgb_matrix_config.speed) * 127;

	if (frgb_timer > g_rgb_timer) return false;

	if (params->init) srand(g_rgb_timer);

/*	HSV hsv  = rgb_matrix_config.hsv;
	hsv.h += frgb_timer;
	RGB rgb = hsv_to_rgb(hsv); */

	RGB_MATRIX_USE_LIMITS(led_min, led_max);
	for (int j = led_min; j < led_max; j++) {
		int i = j > 41 ? j + 1 : j;
		if (rgb_displArray[i]) {
			HSV hsv  = rgb_matrix_config.hsv;
			// hsv.h += g_led_config.point[i].x * 2 + g_rgb_timer/frgb_speed;
			hsv.h += g_led_config.point[i].x;
			RGB rgb = hsv_to_rgb(hsv);
			rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
		} else {
			rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
		}
	}

	if (led_max == DRIVER_LED_TOTAL) {
		frgb_timer = g_rgb_timer + frgb_speed;

		// move columns
		for (uint8_t col = 5; col > 0; col--) {
			for (uint8_t row = 0; row < 4; row++) {
				rgb_halfArray[col][row] = rgb_halfArray[col-1][row];
			}
		}
		//bottom
		for (uint8_t col = 2; col > 0; col--) {
			rgb_halfbottom[col] = rgb_halfbottom[col-1];
		}

		// random fill first column
		for (uint8_t row = 0; row < 4; row++) {
			rgb_halfArray[0][row] = rand() % 2;
		}
		// bottom
		rgb_halfbottom[0] = rand() % 2;

		// transfer to big array
		for (uint8_t col = 0; col < 6; col++) {
			for (uint8_t row = 0; row < 4; row++){
				rgb_fullArray[5 - col][row] = rgb_halfArray[col][row];
				rgb_fullArray[6 + col][row] = rgb_halfArray[col][row];
			}
		}
		//bottom
		for (uint8_t col = 0; col < 3; col++){
			rgb_fullbottom[2 - col] = rgb_halfbottom[col];
			rgb_fullbottom[3 + col] = rgb_halfbottom[col];
		}

		// transfer to matrix array
		uint8_t k = 0;
		for (uint8_t row = 0; row < 4; row++) {
			for (uint8_t col = 0; col < 12; col++) {
					rgb_displArray[k] = rgb_fullArray[col][row];
					k++;
			}
		}
		//bottom
		uint8_t l = 48;
		for (uint8_t col = 0; col < 6; col++) {
			rgb_displArray[l] = rgb_fullbottom[col];
			l++;
		}
	}

	return led_max < DRIVER_LED_TOTAL;
}


/*
KITT EFFECT
by u/jumper149/ (@jumper149)
https://www.reddit.com/r/MechanicalKeyboards/comments/jb0gjc/knight_industries_sixty_five/
 */

uint8_t k_led_count = 8;
uint8_t k_led_first = 14;

static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
	uint16_t led_time = k_led_count * time;
	uint16_t step = ((2 * k_led_count + (led_time / 128)) - led_behind) % (2 * k_led_count);
	uint8_t led;
	if (step < k_led_count) {
		led = step;
	} else {
		led = k_led_count - 1 - (step - k_led_count);
	}
	return led;
}

static HSV kitt_effect_math(HSV hsv, uint8_t i, uint8_t time) {

	hsv.h = 0;
	hsv.s = 255;

	if (i >= k_led_first && i < k_led_first + k_led_count) {
		uint8_t j = i - k_led_first;
		if (j == time_to_led(time, 0)) {
			hsv.v = hsv.v;
		} else if (j == time_to_led(time, 1)) {
			hsv.v = hsv.v/2;
		} else if (j == time_to_led(time, 2)) {
			hsv.v = hsv.v/4;
		} else if (j == time_to_led(time, 3)) {
			hsv.v = hsv.v/8;
		} else {
			hsv.v = 0;
		}
	} else {
		hsv.v = 0;
	}

	return hsv;
}

bool kitt_effect(effect_params_t* params) {
	return effect_runner_i(params, &kitt_effect_math);
}


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
