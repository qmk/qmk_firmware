/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
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


#include "rgb_matrix.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>

rgb_config_t rgb_matrix_config;

#ifndef MAX
    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
    #define MIN(a,b) ((a) < (b)? (a): (b))
#endif

#ifndef RGB_DISABLE_AFTER_TIMEOUT
    #define RGB_DISABLE_AFTER_TIMEOUT 0
#endif

#ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_DISABLE_WHEN_USB_SUSPENDED false
#endif

#ifndef EECONFIG_RGB_MATRIX
    #define EECONFIG_RGB_MATRIX EECONFIG_RGBLIGHT
#endif

#if !defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS) || RGB_MATRIX_MAXIMUM_BRIGHTNESS > 255
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#endif

#ifndef RGB_DIGITAL_RAIN_DROPS
    // lower the number for denser effect/wider keyboard
    #define RGB_DIGITAL_RAIN_DROPS 24
#endif

#if !defined(DISABLE_RGB_MATRIX_RAINDROPS) || !defined(DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS) || !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
    #define TRACK_PREVIOUS_EFFECT
#endif

bool g_suspend_state = false;

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[DRIVER_LED_TOTAL];

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

#ifndef PI
#define PI 3.14159265
#endif

uint32_t eeconfig_read_rgb_matrix(void) {
  return eeprom_read_dword(EECONFIG_RGB_MATRIX);
}
void eeconfig_update_rgb_matrix(uint32_t val) {
  eeprom_update_dword(EECONFIG_RGB_MATRIX, val);
}
void eeconfig_update_rgb_matrix_default(void) {
  dprintf("eeconfig_update_rgb_matrix_default\n");
  rgb_matrix_config.enable = 1;
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
  rgb_matrix_config.mode = RGB_MATRIX_CYCLE_LEFT_RIGHT;
#else
  // fallback to solid colors if RGB_MATRIX_CYCLE_LEFT_RIGHT is disabled in userspace
  rgb_matrix_config.mode = RGB_MATRIX_SOLID_COLOR;
#endif
  rgb_matrix_config.hue = 0;
  rgb_matrix_config.sat = 255;
  rgb_matrix_config.val = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
  rgb_matrix_config.speed = 0;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}
void eeconfig_debug_rgb_matrix(void) {
  dprintf("rgb_matrix_config eprom\n");
  dprintf("rgb_matrix_config.enable = %d\n", rgb_matrix_config.enable);
  dprintf("rgb_matrix_config.mode = %d\n", rgb_matrix_config.mode);
  dprintf("rgb_matrix_config.hue = %d\n", rgb_matrix_config.hue);
  dprintf("rgb_matrix_config.sat = %d\n", rgb_matrix_config.sat);
  dprintf("rgb_matrix_config.val = %d\n", rgb_matrix_config.val);
  dprintf("rgb_matrix_config.speed = %d\n", rgb_matrix_config.speed);
}

// Last led hit
#define LED_HITS_TO_REMEMBER 8
uint8_t g_last_led_hit[LED_HITS_TO_REMEMBER] = {255};
uint8_t g_last_led_count = 0;

void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count) {
    rgb_led led;
    *led_count = 0;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        // map_index_to_led(i, &led);
        led = g_rgb_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            led_i[*led_count] = i;
            (*led_count)++;
        }
    }
}

void rgb_matrix_update_pwm_buffers(void) {
    rgb_matrix_driver.flush();
}

void rgb_matrix_set_color( int index, uint8_t red, uint8_t green, uint8_t blue ) {
    rgb_matrix_driver.set_color(index, red, green, blue);
}

void rgb_matrix_set_color_all( uint8_t red, uint8_t green, uint8_t blue ) {
    rgb_matrix_driver.set_color_all(red, green, blue);
}

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    if ( record->event.pressed ) {
        uint8_t led[8], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        if (led_count > 0) {
            for (uint8_t i = LED_HITS_TO_REMEMBER; i > 1; i--) {
                g_last_led_hit[i - 1] = g_last_led_hit[i - 2];
            }
            g_last_led_hit[0] = led[0];
            g_last_led_count = MIN(LED_HITS_TO_REMEMBER, g_last_led_count + 1);
        }
        for(uint8_t i = 0; i < led_count; i++)
            g_key_hit[led[i]] = 0;
        g_any_key_hit = 0;
    } else {
        #ifdef RGB_MATRIX_KEYRELEASES
        uint8_t led[8], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        for(uint8_t i = 0; i < led_count; i++)
            g_key_hit[led[i]] = 255;

        g_any_key_hit = 255;
        #endif
    }
    return true;
}

void rgb_matrix_set_suspend_state(bool state) {
    g_suspend_state = state;
}

void rgb_matrix_test(void) {
    // Mask out bits 4 and 5
    // Increase the factor to make the test animation slower (and reduce to make it faster)
    uint8_t factor = 10;
    switch ( (g_tick & (0b11 << factor)) >> factor )
    {
        case 0:
        {
            rgb_matrix_set_color_all( 20, 0, 0 );
            break;
        }
        case 1:
        {
            rgb_matrix_set_color_all( 0, 20, 0 );
            break;
        }
        case 2:
        {
            rgb_matrix_set_color_all( 0, 0, 20 );
            break;
        }
        case 3:
        {
            rgb_matrix_set_color_all( 20, 20, 20 );
            break;
        }
    }
}

// All LEDs off
void rgb_matrix_all_off(void) {
    rgb_matrix_set_color_all( 0, 0, 0 );
}

// Solid color
void rgb_matrix_solid_color(void) {
    HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color_all( rgb.r, rgb.g, rgb.b );
}

void rgb_matrix_solid_reactive(void) {
	// Relies on hue being 8-bit and wrapping
	for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
	{
		uint16_t offset2 = g_key_hit[i]<<2;
		offset2 = (offset2<=130) ? (130-offset2) : 0;

		HSV hsv = { .h = rgb_matrix_config.hue+offset2, .s = 255, .v = rgb_matrix_config.val };
		RGB rgb = hsv_to_rgb( hsv );
		rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

// alphas = color1, mods = color2
void rgb_matrix_alphas_mods(void) {

    RGB rgb1 = hsv_to_rgb( (HSV){ .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val } );
    RGB rgb2 = hsv_to_rgb( (HSV){ .h = (rgb_matrix_config.hue + 180) % 360, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val } );

    rgb_led led;
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_rgb_leds[i];
        if ( led.matrix_co.raw < 0xFF ) {
            if ( led.modifier )
            {
                rgb_matrix_set_color( i, rgb2.r, rgb2.g, rgb2.b );
            }
            else
            {
                rgb_matrix_set_color( i, rgb1.r, rgb1.g, rgb1.b );
            }
        }
    }
}

void rgb_matrix_gradient_up_down(void) {
    int16_t h1 = rgb_matrix_config.hue;
    int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }
    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = rgb_matrix_config.sat;
    int16_t s2 = rgb_matrix_config.hue;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_led_to_point( i, &point );
        point = g_rgb_leds[i].point;
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y>>4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = rgb_matrix_config.hue + ( deltaH * y );
        hsv.s = rgb_matrix_config.sat + ( deltaS * y );
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void rgb_matrix_raindrops(bool initialize) {
    int16_t h1 = rgb_matrix_config.hue;
    int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
    int16_t deltaH = h2 - h1;
    deltaH /= 4;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }

    int16_t s1 = rgb_matrix_config.sat;
    int16_t s2 = rgb_matrix_config.sat;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv;
    RGB rgb;

    // Change one LED every tick, make sure speed is not 0
    uint8_t led_to_change = ( g_tick & ( 0x0A / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed) ) ) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;

    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = h1 + ( deltaH * ( rand() & 0x03 ) );
            hsv.s = s1 + ( deltaS * ( rand() & 0x03 ) );
            // Override brightness with global brightness control
            hsv.v = rgb_matrix_config.val;

            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void rgb_matrix_cycle_all(void) {
    uint8_t offset = ( g_tick << rgb_matrix_config.speed ) & 0xFF;

    rgb_led led;

    // Relies on hue being 8-bit and wrapping
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_rgb_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            HSV hsv = { .h = offset+offset2, .s = 255, .v = rgb_matrix_config.val };
            RGB rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void rgb_matrix_cycle_left_right(void) {
    uint8_t offset = ( g_tick << rgb_matrix_config.speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    rgb_led led;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_rgb_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            // map_led_to_point( i, &point );
            point = g_rgb_leds[i].point;
            // Relies on hue being 8-bit and wrapping
            hsv.h = point.x + offset + offset2;
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void rgb_matrix_cycle_up_down(void) {
    uint8_t offset = ( g_tick << rgb_matrix_config.speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    rgb_led led;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_rgb_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            // map_led_to_point( i, &point );
            point = g_rgb_leds[i].point;
            // Relies on hue being 8-bit and wrapping
            hsv.h = point.y + offset + offset2;
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}


void rgb_matrix_dual_beacon(void) {
    HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    double cos_value = cos(g_tick * PI / 128) / 32;
    double sin_value =  sin(g_tick * PI / 128) / 112;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = g_rgb_leds[i].point;
        hsv.h = ((point.y - 32.0)* cos_value + (point.x - 112.0) * sin_value) * (180) + rgb_matrix_config.hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void rgb_matrix_rainbow_beacon(void) {
    HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    double cos_value = cos(g_tick * PI / 128);
    double sin_value =  sin(g_tick * PI / 128);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = g_rgb_leds[i].point;
        hsv.h = (1.5 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * (point.y - 32.0)* cos_value + (1.5 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * (point.x - 112.0) * sin_value + rgb_matrix_config.hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void rgb_matrix_rainbow_pinwheels(void) {
    HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    double cos_value = cos(g_tick * PI / 128);
    double sin_value =  sin(g_tick * PI / 128);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = g_rgb_leds[i].point;
        hsv.h = (2 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * (point.y - 32.0)* cos_value + (2 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * (66 - abs(point.x - 112.0)) * sin_value + rgb_matrix_config.hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void rgb_matrix_rainbow_moving_chevron(void) {
    HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    uint8_t r = 128;
    double cos_value = cos(r * PI / 128);
    double sin_value =  sin(r * PI / 128);
    double multiplier = (g_tick / 256.0 * 224);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        point = g_rgb_leds[i].point;
        hsv.h = (1.5 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * abs(point.y - 32.0)* sin_value + (1.5 * (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed)) * (point.x - multiplier) * cos_value + rgb_matrix_config.hue;
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}


void rgb_matrix_jellybean_raindrops( bool initialize ) {
    HSV hsv;
    RGB rgb;

    // Change one LED every tick, make sure speed is not 0
    uint8_t led_to_change = ( g_tick & ( 0x0A / (rgb_matrix_config.speed == 0 ? 1 : rgb_matrix_config.speed) ) ) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;

    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = rand() & 0xFF;
            hsv.s = rand() & 0xFF;
            // Override brightness with global brightness control
            hsv.v = rgb_matrix_config.val;

            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void rgb_matrix_digital_rain( const bool initialize ) {
    // algorithm ported from https://github.com/tremby/Kaleidoscope-LEDEffect-DigitalRain
    const uint8_t drop_ticks           = 28;
    const uint8_t pure_green_intensity = 0xd0;
    const uint8_t max_brightness_boost = 0xc0;
    const uint8_t max_intensity        = 0xff;

    static uint8_t map[MATRIX_COLS][MATRIX_ROWS] = {{0}};
    static uint8_t drop = 0;

    if (initialize) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(map, 0, sizeof map);
        drop = 0;
    }
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            if (row == 0 && drop == 0 && rand() < RAND_MAX / RGB_DIGITAL_RAIN_DROPS) {
                // top row, pixels have just fallen and we're
                // making a new rain drop in this column
                map[col][row] = max_intensity;
            }
            else if (map[col][row] > 0 && map[col][row] < max_intensity) {
                // neither fully bright nor dark, decay it
                map[col][row]--;
            }
            // set the pixel colour
            uint8_t led, led_count;
            map_row_column_to_led(row, col, &led, &led_count);

            if (map[col][row] > pure_green_intensity) {
                const uint8_t boost = (uint8_t) ((uint16_t) max_brightness_boost
                        * (map[col][row] - pure_green_intensity) / (max_intensity - pure_green_intensity));
                rgb_matrix_set_color(led, boost, max_intensity, boost);
            }
            else {
                const uint8_t green = (uint8_t) ((uint16_t) max_intensity * map[col][row] / pure_green_intensity);
                rgb_matrix_set_color(led, 0, green, 0);
            }
        }
    }
    if (++drop > drop_ticks) {
        // reset drop timer
        drop = 0;
        for (uint8_t row = MATRIX_ROWS - 1; row > 0; row--) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                // if ths is on the bottom row and bright allow decay
                if (row == MATRIX_ROWS - 1 && map[col][row] == max_intensity) {
                    map[col][row]--;
                }
                // check if the pixel above is bright
                if (map[col][row - 1] == max_intensity) {
                    // allow old bright pixel to decay
                    map[col][row - 1]--;
                    // make this pixel bright
                    map[col][row] = max_intensity;
                }
            }
        }
    }
}

void rgb_matrix_multisplash(void) {
    // if (g_any_key_hit < 0xFF) {
        HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
        RGB rgb;
        rgb_led led;
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            led = g_rgb_leds[i];
            uint16_t c = 0, d = 0;
            rgb_led last_led;
            // if (g_last_led_count) {
                for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
                    last_led = g_rgb_leds[g_last_led_hit[last_i]];
                    uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
                    uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
                    c += MIN(MAX(effect, 0), 255);
                    d += 255 - MIN(MAX(effect, 0), 255);
                }
            // } else {
            //     d = 255;
            // }
            hsv.h = (rgb_matrix_config.hue + c) % 256;
            hsv.v = MAX(MIN(d, 255), 0);
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    // } else {
        // rgb_matrix_set_color_all( 0, 0, 0 );
    // }
}


void rgb_matrix_splash(void) {
    g_last_led_count = MIN(g_last_led_count, 1);
    rgb_matrix_multisplash();
}


void rgb_matrix_solid_multisplash(void) {
    // if (g_any_key_hit < 0xFF) {
        HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat, .v = rgb_matrix_config.val };
        RGB rgb;
        rgb_led led;
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            led = g_rgb_leds[i];
            uint16_t d = 0;
            rgb_led last_led;
            // if (g_last_led_count) {
                for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
                    last_led = g_rgb_leds[g_last_led_hit[last_i]];
                    uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
                    uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
                    d += 255 - MIN(MAX(effect, 0), 255);
                }
            // } else {
            //     d = 255;
            // }
            hsv.v = MAX(MIN(d, 255), 0);
            rgb = hsv_to_rgb( hsv );
            rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    // } else {
        // rgb_matrix_set_color_all( 0, 0, 0 );
    // }
}


void rgb_matrix_solid_splash(void) {
    g_last_led_count = MIN(g_last_led_count, 1);
    rgb_matrix_solid_multisplash();
}


// Needs eeprom access that we don't have setup currently

void rgb_matrix_custom(void) {
//     HSV hsv;
//     RGB rgb;
//     for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
//     {
//         backlight_get_key_color(i, &hsv);
//         // Override brightness with global brightness control
//         hsv.v = rgb_matrix_config.val;
//         rgb = hsv_to_rgb( hsv );
//         rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
//     }
}

void rgb_matrix_task(void) {
  #ifdef TRACK_PREVIOUS_EFFECT
      static uint8_t toggle_enable_last = 255;
  #endif
	if (!rgb_matrix_config.enable) {
     rgb_matrix_all_off();
     rgb_matrix_indicators();
     #ifdef TRACK_PREVIOUS_EFFECT
         toggle_enable_last = rgb_matrix_config.enable;
     #endif
     return;
    }
    // delay 1 second before driving LEDs or doing anything else
    static uint8_t startup_tick = 0;
    if ( startup_tick < 20 ) {
        startup_tick++;
        return;
    }

    g_tick++;

    if ( g_any_key_hit < 0xFFFFFFFF ) {
        g_any_key_hit++;
    }

    for ( int led = 0; led < DRIVER_LED_TOTAL; led++ ) {
        if ( g_key_hit[led] < 255 ) {
            if (g_key_hit[led] == 254)
                g_last_led_count = MAX(g_last_led_count - 1, 0);
            g_key_hit[led]++;
        }
    }

    // Factory default magic value
    if ( rgb_matrix_config.mode == 255 ) {
        rgb_matrix_test();
        return;
    }

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool suspend_backlight = ((g_suspend_state && RGB_DISABLE_WHEN_USB_SUSPENDED) ||
            (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));
    uint8_t effect = suspend_backlight ? 0 : rgb_matrix_config.mode;

    #ifdef TRACK_PREVIOUS_EFFECT
        // Keep track of the effect used last time,
        // detect change in effect, so each effect can
        // have an optional initialization.

        static uint8_t effect_last = 255;
        bool initialize = (effect != effect_last) || (rgb_matrix_config.enable != toggle_enable_last);
        effect_last = effect;
        toggle_enable_last = rgb_matrix_config.enable;
    #endif

    // this gets ticked at 20 Hz.
    // each effect can opt to do calculations
    // and/or request PWM buffer updates.
    switch ( effect ) {
        case RGB_MATRIX_SOLID_COLOR:
            rgb_matrix_solid_color();
            break;
        #ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
            case RGB_MATRIX_ALPHAS_MODS:
                rgb_matrix_alphas_mods();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
            case RGB_MATRIX_DUAL_BEACON:
                rgb_matrix_dual_beacon();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
            case RGB_MATRIX_GRADIENT_UP_DOWN:
                rgb_matrix_gradient_up_down();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINDROPS
            case RGB_MATRIX_RAINDROPS:
                rgb_matrix_raindrops( initialize );
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
            case RGB_MATRIX_CYCLE_ALL:
                rgb_matrix_cycle_all();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
            case RGB_MATRIX_CYCLE_LEFT_RIGHT:
                rgb_matrix_cycle_left_right();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
            case RGB_MATRIX_CYCLE_UP_DOWN:
                rgb_matrix_cycle_up_down();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
            case RGB_MATRIX_RAINBOW_BEACON:
                rgb_matrix_rainbow_beacon();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
            case RGB_MATRIX_RAINBOW_PINWHEELS:
                rgb_matrix_rainbow_pinwheels();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
            case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
                rgb_matrix_rainbow_moving_chevron();
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
            case RGB_MATRIX_JELLYBEAN_RAINDROPS:
                rgb_matrix_jellybean_raindrops( initialize );
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
            case RGB_MATRIX_DIGITAL_RAIN:
                rgb_matrix_digital_rain( initialize );
                break;
        #endif
        #ifdef RGB_MATRIX_KEYPRESSES
            #ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
                case RGB_MATRIX_SOLID_REACTIVE:
                    rgb_matrix_solid_reactive();
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SPLASH
                case RGB_MATRIX_SPLASH:
                    rgb_matrix_splash();
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_MULTISPLASH
                case RGB_MATRIX_MULTISPLASH:
                    rgb_matrix_multisplash();
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
                case RGB_MATRIX_SOLID_SPLASH:
                    rgb_matrix_solid_splash();
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
                case RGB_MATRIX_SOLID_MULTISPLASH:
                    rgb_matrix_solid_multisplash();
                    break;
            #endif
        #endif
        default:
            rgb_matrix_custom();
            break;
    }

    if ( ! suspend_backlight ) {
        rgb_matrix_indicators();
    }

}

void rgb_matrix_indicators(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_indicators_user();
}

__attribute__((weak))
void rgb_matrix_indicators_kb(void) {}

__attribute__((weak))
void rgb_matrix_indicators_user(void) {}


// void rgb_matrix_set_indicator_index( uint8_t *index, uint8_t row, uint8_t column )
// {
//  if ( row >= MATRIX_ROWS )
//  {
//      // Special value, 255=none, 254=all
//      *index = row;
//  }
//  else
//  {
//      // This needs updated to something like
//      // uint8_t led[8], led_count;
//      // map_row_column_to_led(row,column,led,&led_count);
//      // for(uint8_t i = 0; i < led_count; i++)
//      map_row_column_to_led( row, column, index );
//  }
// }

void rgb_matrix_init(void) {
  rgb_matrix_driver.init();

  // TODO: put the 1 second startup delay here?

  // clear the key hits
  for ( int led=0; led<DRIVER_LED_TOTAL; led++ ) {
      g_key_hit[led] = 255;
  }


  if (!eeconfig_is_enabled()) {
      dprintf("rgb_matrix_init_drivers eeconfig is not enabled.\n");
      eeconfig_init();
      eeconfig_update_rgb_matrix_default();
  }
  rgb_matrix_config.raw = eeconfig_read_rgb_matrix();
  if (!rgb_matrix_config.mode) {
      dprintf("rgb_matrix_init_drivers rgb_matrix_config.mode = 0. Write default values to EEPROM.\n");
      eeconfig_update_rgb_matrix_default();
      rgb_matrix_config.raw = eeconfig_read_rgb_matrix();
  }
  eeconfig_debug_rgb_matrix(); // display current eeprom values
}

// Deals with the messy details of incrementing an integer
static uint8_t increment( uint8_t value, uint8_t step, uint8_t min, uint8_t max ) {
    int16_t new_value = value;
    new_value += step;
    return MIN( MAX( new_value, min ), max );
}

static uint8_t decrement( uint8_t value, uint8_t step, uint8_t min, uint8_t max ) {
    int16_t new_value = value;
    new_value -= step;
    return MIN( MAX( new_value, min ), max );
}

// void *backlight_get_custom_key_color_eeprom_address( uint8_t led )
// {
//     // 3 bytes per color
//     return EECONFIG_RGB_MATRIX + ( led * 3 );
// }

// void backlight_get_key_color( uint8_t led, HSV *hsv )
// {
//     void *address = backlight_get_custom_key_color_eeprom_address( led );
//     hsv->h = eeprom_read_byte(address);
//     hsv->s = eeprom_read_byte(address+1);
//     hsv->v = eeprom_read_byte(address+2);
// }

// void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv )
// {
//     uint8_t led[8], led_count;
//     map_row_column_to_led(row,column,led,&led_count);
//     for(uint8_t i = 0; i < led_count; i++) {
//         if ( led[i] < DRIVER_LED_TOTAL )
//         {
//             void *address = backlight_get_custom_key_color_eeprom_address(led[i]);
//             eeprom_update_byte(address, hsv.h);
//             eeprom_update_byte(address+1, hsv.s);
//             eeprom_update_byte(address+2, hsv.v);
//         }
//     }
// }

uint32_t rgb_matrix_get_tick(void) {
    return g_tick;
}

void rgb_matrix_toggle(void) {
	rgb_matrix_config.enable ^= 1;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_enable(void) {
	rgb_matrix_config.enable = 1;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_enable_noeeprom(void) {
	rgb_matrix_config.enable = 1;
}

void rgb_matrix_disable(void) {
	rgb_matrix_config.enable = 0;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_disable_noeeprom(void) {
	rgb_matrix_config.enable = 0;
}

void rgb_matrix_step(void) {
    rgb_matrix_config.mode++;
    if (rgb_matrix_config.mode >= RGB_MATRIX_EFFECT_MAX)
        rgb_matrix_config.mode = 1;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_step_reverse(void) {
    rgb_matrix_config.mode--;
    if (rgb_matrix_config.mode < 1)
        rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX - 1;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_hue(void) {
    rgb_matrix_config.hue = increment( rgb_matrix_config.hue, 8, 0, 255 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_hue(void) {
    rgb_matrix_config.hue = decrement( rgb_matrix_config.hue, 8, 0, 255 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_sat(void) {
    rgb_matrix_config.sat = increment( rgb_matrix_config.sat, 8, 0, 255 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_sat(void) {
    rgb_matrix_config.sat = decrement( rgb_matrix_config.sat, 8, 0, 255 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_val(void) {
    rgb_matrix_config.val = increment( rgb_matrix_config.val, 8, 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_val(void) {
    rgb_matrix_config.val = decrement( rgb_matrix_config.val, 8, 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_speed(void) {
    rgb_matrix_config.speed = increment( rgb_matrix_config.speed, 1, 0, 3 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);//EECONFIG needs to be increased to support this
}

void rgb_matrix_decrease_speed(void) {
    rgb_matrix_config.speed = decrement( rgb_matrix_config.speed, 1, 0, 3 );
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);//EECONFIG needs to be increased to support this
}

void rgb_matrix_mode(uint8_t mode) {
    rgb_matrix_config.mode = mode;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_mode_noeeprom(uint8_t mode) {
    rgb_matrix_config.mode = mode;
}

uint32_t rgb_matrix_get_mode(void) {
    return rgb_matrix_config.mode;
}

void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) {
  rgb_matrix_config.hue = hue;
  rgb_matrix_config.sat = sat;
  rgb_matrix_config.val = val;
  eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) {
  rgb_matrix_config.hue = hue;
  rgb_matrix_config.sat = sat;
  rgb_matrix_config.val = val;
}
