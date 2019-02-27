/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Daniel Prilik
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

#ifndef RGB_MATRIX_SKIP_FRAMES
  #define RGB_MATRIX_SKIP_FRAMES 1
#endif

#ifndef RGB_DIGITAL_RAIN_DROPS
    // lower the number for denser effect/wider keyboard
    #define RGB_DIGITAL_RAIN_DROPS 24
#endif

#ifndef PI
#define PI 3.14159265
#endif

/*------------------------------  Local Globals  -----------------------------*/
// TODO: Refactor these away?

#define MAX_SEARCH_LEDS 8
#define LED_HITS_TO_REMEMBER 8

static uint8_t g_last_led_count = 0;
static uint8_t g_last_led_hit[LED_HITS_TO_REMEMBER] = {255};

/*----------------------------  Exported Globals  ----------------------------*/

rgb_config_t rgb_matrix_config;

bool g_suspend_state = false;

uint32_t g_tick = 0;                  // Ticks every frame
uint8_t  g_key_hit[DRIVER_LED_TOTAL]; // Ticks since this key was last hit.
uint32_t g_any_key_hit = 0;           // Ticks since any key was last hit.
uint16_t g_last_keycode;              // Last keycode hit

/*---------------------------  EEPROM Interaction  ---------------------------*/

void eeconfig_debug_rgb_matrix(void) {
    dprintf("rgb_matrix_config eprom\n");
    dprintf("rgb_matrix_config.enable = %d\n", rgb_matrix_config.enable);
    dprintf("rgb_matrix_config.mode = %d\n", rgb_matrix_config.mode);
    dprintf("rgb_matrix_config.hsv.h = %d\n", rgb_matrix_config.hsv.h);
    dprintf("rgb_matrix_config.hsv.s = %d\n", rgb_matrix_config.hsv.s);
    dprintf("rgb_matrix_config.hsv.v = %d\n", rgb_matrix_config.hsv.v);
    dprintf("rgb_matrix_config.speed = %d\n", rgb_matrix_config.speed);
}

uint32_t eeconfig_read_rgb_matrix(void) {
    return eeprom_read_dword(EECONFIG_RGB_MATRIX);
}

void eeconfig_update_rgb_matrix(uint32_t val) {
    eeprom_update_dword(EECONFIG_RGB_MATRIX, val);
    eeconfig_debug_rgb_matrix();
}

void eeconfig_update_rgb_matrix_default(void) {
    dprintf("eeconfig_update_rgb_matrix_default\n");
    rgb_matrix_config.enable = 1;
    if (rgb_matrix_custom_modes_count != 0) {
        rgb_matrix_config.mode = RGB_MATRIX_CUSTOM;
    } else {
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
        rgb_matrix_config.mode = RGB_MATRIX_CYCLE_LEFT_RIGHT;
#else
        // fallback to solid colors if RGB_MATRIX_CYCLE_LEFT_RIGHT is disabled in userspace
        rgb_matrix_config.mode = RGB_MATRIX_SOLID_COLOR;
#endif
    }
    rgb_matrix_config.hsv.h = 0;
    rgb_matrix_config.hsv.s = 255;
    rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    rgb_matrix_config.speed = 0;
    rgb_matrix_config.custom = 0;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

/*---------------------------  Driver Abstraction  ---------------------------*/

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
#ifdef RGB_MATRIX_EXTRA_TOG
    const bool is_key = g_rgb_leds[index].matrix_co.raw != 0xff;
    if ((rgb_matrix_config.enable == RGB_ZONE_KEYS && !is_key) ||
        (rgb_matrix_config.enable == RGB_ZONE_UNDER && is_key))
    {
        rgb_matrix_driver.set_color(index, 0, 0, 0);
        return;
    }
#endif

    rgb_matrix_driver.set_color(index, red, green, blue);
}

static void map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count) {
    rgb_led led;
    *led_count = 0;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL && *led_count < MAX_SEARCH_LEDS; i++) {
        // map_index_to_led(i, &led);
        led = g_rgb_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            led_i[*led_count] = i;
            (*led_count)++;
        }
    }
}

/*--------------------------------  Effects  ---------------------------------*/

// All LEDs off
void rgb_matrix_all_off(uint16_t led_i) {
    rgb_matrix_set_color(led_i, 0, 0, 0);
}

// Solid color
void rgb_matrix_solid_color(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);

    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_solid_reactive(uint16_t led_i) {
	// Relies on hue being 8-bit and wrapping
	uint16_t offset2 = g_key_hit[led_i] << 2;
	offset2 = (offset2 <= 130) ? (130 - offset2) : 0;

	HSV hsv = { .h = rgb_matrix_config.hsv.h + offset2, .s = 255, .v = rgb_matrix_config.hsv.v };
	RGB rgb = hsv_to_rgb(hsv);
	rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

// alphas = color1, mods = color2
void rgb_matrix_alphas_mods(uint16_t led_i) {
    RGB rgb1 = hsv_to_rgb((HSV){ .h = rgb_matrix_config.hsv.h, .s = rgb_matrix_config.hsv.s, .v = rgb_matrix_config.hsv.v });
    RGB rgb2 = hsv_to_rgb((HSV){ .h = (rgb_matrix_config.hsv.h + 180) % 360, .s = rgb_matrix_config.hsv.s, .v = rgb_matrix_config.hsv.v });

    rgb_led led = g_rgb_leds[led_i];
    if (led.matrix_co.raw < 0xFF) {
        if (led.modifier)
        {
            rgb_matrix_set_color(led_i, rgb2.r, rgb2.g, rgb2.b);
        }
        else
        {
            rgb_matrix_set_color(led_i, rgb1.r, rgb1.g, rgb1.b);
        }
    }
}

void rgb_matrix_gradient_up_down(uint16_t led_i) {
    int16_t h1 = rgb_matrix_config.hsv.h;
    int16_t h2 = (rgb_matrix_config.hsv.h + 180) % 360;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if (deltaH > 127)
    {
        deltaH -= 256;
    }
    else if (deltaH < -127)
    {
        deltaH += 256;
    }
    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = rgb_matrix_config.hsv.s;
    int16_t s2 = rgb_matrix_config.hsv.h;
    int16_t deltaS = (s2 - s1) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.hsv.v };
    Point point = g_rgb_leds[led_i].point;
    // The y range will be 0..64, map this to 0..4
    uint8_t y = (point.y>>4);
    // Relies on hue being 8-bit and wrapping
    hsv.h = rgb_matrix_config.hsv.h + (deltaH * y);
    hsv.s = rgb_matrix_config.hsv.s + (deltaS * y);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_raindrops(uint16_t led_i, bool initialize) {
    int16_t h1 = rgb_matrix_config.hsv.h;
    int16_t h2 = (rgb_matrix_config.hsv.h + 180) % 360;
    int16_t deltaH = h2 - h1;
    deltaH /= 4;

    // Take the shortest path between hues
    if (deltaH > 127)
    {
        deltaH -= 256;
    }
    else if (deltaH < -127)
    {
        deltaH += 256;
    }

    int16_t s1 = rgb_matrix_config.hsv.s;
    int16_t s2 = rgb_matrix_config.hsv.s;
    int16_t deltaS = (s2 - s1) / 4;

    // Change one LED every tick, make sure speed is not 0
    static uint32_t this_tick = 0;
    static uint8_t led_to_change = 0;
    if (this_tick != g_tick) {
        this_tick = g_tick;
        led_to_change = (g_tick & 0x0A) == 0
            ? rand() % (DRIVER_LED_TOTAL)
            : 255;
    }

    // If initialize, all get set to random colors
    // If not, all but one will stay the same as before.
    if (initialize || led_i == led_to_change)
    {
        HSV hsv;
        hsv.h = h1 + (deltaH * (rand() & 0x03));
        hsv.s = s1 + (deltaS * (rand() & 0x03));
        // Override brightness with global brightness control
        hsv.v = rgb_matrix_config.hsv.v;

        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    }
}

void rgb_matrix_cycle_all(uint16_t led_i) {
    // Relies on hue being 8-bit and wrapping
    rgb_led led = g_rgb_leds[led_i];
    if (led.matrix_co.raw < 0xFF) {
        uint16_t offset2 = g_key_hit[led_i]<<2;
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        HSV hsv = { .h = g_tick + offset2, .s = 255, .v = rgb_matrix_config.hsv.v };
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    } else {
        rgb_matrix_set_color(led_i, 0, 0, 0);
    }
}

void rgb_matrix_cycle_left_right(uint16_t led_i) {
    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.hsv.v };
    rgb_led led = g_rgb_leds[led_i];
    if (led.matrix_co.raw < 0xFF) {
        uint16_t offset2 = g_key_hit[led_i]<<2;
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        Point point = g_rgb_leds[led_i].point;
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.x + g_tick + offset2;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    } else {
        rgb_matrix_set_color(led_i, 0, 0, 0);
    }
}

void rgb_matrix_cycle_up_down(uint16_t led_i) {
    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.hsv.v };
    rgb_led led = g_rgb_leds[led_i];
    if (led.matrix_co.raw < 0xFF) {
        uint16_t offset2 = g_key_hit[led_i]<<2;
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        Point point = g_rgb_leds[led_i].point;
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.y + g_tick + offset2;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    }
}

void rgb_matrix_dual_beacon(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    double cos_value = cos(g_tick * PI / 128) / 32;
    double sin_value =  sin(g_tick * PI / 128) / 112;
    Point point = g_rgb_leds[led_i].point;
    hsv.h = ((point.y - 32.0)* cos_value + (point.x - 112.0) * sin_value) * 180 + rgb_matrix_config.hsv.h;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_rainbow_beacon(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    double cos_value = cos(g_tick * PI / 128);
    double sin_value =  sin(g_tick * PI / 128);
    Point point = g_rgb_leds[led_i].point;
    hsv.h = 1.5 * (point.y - 32.0)* cos_value + 1.5 * (point.x - 112.0) * sin_value + rgb_matrix_config.hsv.h;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_rainbow_pinwheels(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    double cos_value = cos(g_tick * PI / 128);
    double sin_value =  sin(g_tick * PI / 128);
    Point point = g_rgb_leds[led_i].point;
    hsv.h = 2 * (point.y - 32.0)* cos_value + 2 * (66 - abs(point.x - 112.0)) * sin_value + rgb_matrix_config.hsv.h;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_rainbow_moving_chevron(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    uint8_t r = 128;
    double cos_value = cos(r * PI / 128);
    double sin_value =  sin(r * PI / 128);
    double multiplier = (g_tick / 256.0 * 224);
    Point point = g_rgb_leds[led_i].point;
    hsv.h = 1.5 * abs(point.y - 32.0)* sin_value + 1.5 * (point.x - multiplier) * cos_value + rgb_matrix_config.hsv.h;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_jellybean_raindrops(uint16_t led_i, bool initialize) {
    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    static uint32_t this_tick = 0;
    static uint8_t led_to_change = 0;
    if (this_tick != g_tick) {
        this_tick = g_tick;
        led_to_change = (g_tick & 0x0A) == 0 ? rand() % (DRIVER_LED_TOTAL) : 255;
    }
    // If initialize, all get set to random colors
    // If not, all but one will stay the same as before.
    if (initialize || led_i == led_to_change)
    {
        hsv.h = rand() & 0xFF;
        hsv.s = rand() & 0xFF;
        // Override brightness with global brightness control
        hsv.v = rgb_matrix_config.hsv.v;

        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    }
}

// TODO: refactor to allow per-pixel updates
void rgb_matrix_digital_rain(uint16_t led_i, bool init) {
    if (led_i != 0) return;

    // algorithm ported from https://github.com/tremby/Kaleidoscope-LEDEffect-DigitalRain
    const uint8_t drop_ticks           = 28;
    const uint8_t pure_green_intensity = 0xd0;
    const uint8_t max_brightness_boost = 0xc0;
    const uint8_t max_intensity        = 0xff;

    static uint8_t map[MATRIX_COLS][MATRIX_ROWS] = {{0}};
    static uint8_t drop = 0;

    if (init) {
        rgb_matrix_set_color(led_i, 0, 0, 0);
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
            uint8_t led, leds[MAX_SEARCH_LEDS], led_count;
            map_row_column_to_led(row, col, leds, &led_count);
            led = leds[0];

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

void rgb_matrix_breathing(uint16_t led_i) {
    uint8_t breathing_step = g_tick << 1; // Going up
    if ((uint8_t)g_tick >> 7) breathing_step = 0xFF - breathing_step; // Going down
    float f_step = (float)breathing_step;
    float f_ratio = (f_step * f_step) / 65025;
    float v = (float)rgb_matrix_config.hsv.v * f_ratio;
    HSV hsv = {
        .h = rgb_matrix_config.hsv.h,
        .s = rgb_matrix_config.hsv.s,
        .v = (uint8_t)v,
    };
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_multisplash(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    rgb_led led = g_rgb_leds[led_i];
    uint16_t c = 0, d = 0;
    rgb_led last_led;
    for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
        if (g_last_led_hit[last_i] < 255) {
            last_led = g_rgb_leds[g_last_led_hit[last_i]];
            uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
            uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
            c += MIN(MAX(effect, 0), 255);
            d += 255 - MIN(MAX(effect, 0), 255);
        }
    }
    hsv.h = (rgb_matrix_config.hsv.h + c) % 256;
    hsv.v = MAX(MIN(d, 255), 0);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}


void rgb_matrix_splash(uint16_t led_i) {
    g_last_led_count = MIN(g_last_led_count, 1);
    rgb_matrix_multisplash(led_i);
}


void rgb_matrix_solid_multisplash(uint16_t led_i) {
    HSV hsv = rgb_matrix_config.hsv;
    rgb_led led = g_rgb_leds[led_i];
    uint16_t d = 0;
    rgb_led last_led;
    for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
        if (g_last_led_hit[last_i] < 255) {
            last_led = g_rgb_leds[g_last_led_hit[last_i]];
            uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
            uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
            d += 255 - MIN(MAX(effect, 0), 255);
        }
    }
    hsv.v = MAX(MIN(d, 255), 0);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
}


void rgb_matrix_solid_splash(uint16_t led_i) {
    g_last_led_count = MIN(g_last_led_count, 1);
    rgb_matrix_solid_multisplash(led_i);
}

/*---------------------------------  Tasks  ----------------------------------*/

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    g_last_keycode = keycode;
    if (record->event.pressed) {
        uint8_t led[MAX_SEARCH_LEDS], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        if (led_count > 0) {
            for (uint8_t i = LED_HITS_TO_REMEMBER; i > 1; i--) {
                g_last_led_hit[i - 1] = g_last_led_hit[i - 2] == led[0] ? 255 : g_last_led_hit[i - 2];
            }
            g_last_led_hit[0] = led[0];
            g_last_led_count = MIN(LED_HITS_TO_REMEMBER, g_last_led_count + 1);
        }
        for(uint8_t i = 0; i < led_count; i++)
            g_key_hit[led[i]] = 0;
        g_any_key_hit = 0;
    } else {
        #ifdef RGB_MATRIX_KEYRELEASES
        uint8_t led[MAX_SEARCH_LEDS], led_count;
        map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        for(uint8_t i = 0; i < led_count; i++)
            g_key_hit[led[i]] = 255;

        g_any_key_hit = 255;
        #endif
    }
    return true;
}

void rgb_matrix_indicators(uint16_t led_i) {
    rgb_matrix_indicators_kb(led_i);
    rgb_matrix_indicators_user(led_i);
}

__attribute__((weak))
void rgb_matrix_indicators_kb(uint16_t led_i) {}

__attribute__((weak))
void rgb_matrix_indicators_user(uint16_t led_i) {}

void rgb_matrix_task(void) {
    static uint32_t led_next_run = 0;
    const uint32_t timer = timer_read32();
    if (timer < led_next_run) { return; }
    led_next_run = timer + RGB_MATRIX_SKIP_FRAMES;

    static uint16_t cur_led_i = 0;
    static uint8_t  effect = 0;
    static bool     initialize = true;

    static bool     suspend_backlight = false;
    static uint8_t  toggle_enable_last = 255;

    // delay 1 second before driving LEDs or doing anything else
    static uint8_t startup_tick = 0;
    if (startup_tick < 20) {
        startup_tick++;
        return;
    }

    g_tick += rgb_matrix_config.speed + 1;
    if (g_any_key_hit < 0xFFFFFFFF)
        g_any_key_hit++;

    // A new frame is starting
    if (cur_led_i == 0) {
        // flush the old frame
        rgb_matrix_driver.flush();

        // Ideally we would also stop sending zeros to the LED driver PWM buffers
        // while suspended and just do a software shutdown. This is a cheap hack for now.
        suspend_backlight = (
            (g_suspend_state && RGB_DISABLE_WHEN_USB_SUSPENDED) ||
            (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));

        effect = suspend_backlight ? 0 : rgb_matrix_config.mode;

        // Keep track of the effect used last time,
        // detect change in effect, so each effect can
        // have an optional initialization.

        static uint8_t effect_last = 255;
        static uint8_t custom_last = 255;

        initialize = (effect != effect_last)
                  || (custom_last != rgb_matrix_config.custom)
                  || (rgb_matrix_config.enable != toggle_enable_last);

        effect_last = effect;
        custom_last = rgb_matrix_config.custom;
        toggle_enable_last = rgb_matrix_config.enable;

        if (initialize) {
            // wipe all the LEDs, since some effects never touch underglow leds,
            // resulting in a static-underglow when there shouldn't be any
            for (int i = 0; i < DRIVER_LED_TOTAL; i++)
                rgb_matrix_all_off(i);
        }
    }

    // TODO?: tweak effects and timings to works with nonstandard #leds per run
    #define LED_PER_RUN DRIVER_LED_TOTAL

    for (int i = 0; i < LED_PER_RUN; i++) {
        if (g_key_hit[cur_led_i] < 255) {
            if (g_key_hit[cur_led_i] == 254)
                g_last_led_count = MAX(g_last_led_count - 1, 0);
            g_key_hit[cur_led_i]++;
        }

        if (!rgb_matrix_config.enable) {
            rgb_matrix_all_off(cur_led_i);
            goto done_effect;
        }

        switch (effect) {
            case RGB_MATRIX_SOLID_COLOR:
                rgb_matrix_solid_color(cur_led_i);
                break;
            #ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
                case RGB_MATRIX_ALPHAS_MODS:
                    rgb_matrix_alphas_mods(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
                case RGB_MATRIX_DUAL_BEACON:
                    rgb_matrix_dual_beacon(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
                case RGB_MATRIX_GRADIENT_UP_DOWN:
                    rgb_matrix_gradient_up_down(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_RAINDROPS
                case RGB_MATRIX_RAINDROPS:
                    rgb_matrix_raindrops(cur_led_i, initialize);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
                case RGB_MATRIX_CYCLE_ALL:
                    rgb_matrix_cycle_all(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
                case RGB_MATRIX_CYCLE_LEFT_RIGHT:
                    rgb_matrix_cycle_left_right(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
                case RGB_MATRIX_CYCLE_UP_DOWN:
                    rgb_matrix_cycle_up_down(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
                case RGB_MATRIX_RAINBOW_BEACON:
                    rgb_matrix_rainbow_beacon(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
                case RGB_MATRIX_RAINBOW_PINWHEELS:
                    rgb_matrix_rainbow_pinwheels(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
                case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
                    rgb_matrix_rainbow_moving_chevron(cur_led_i);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
                case RGB_MATRIX_JELLYBEAN_RAINDROPS:
                    rgb_matrix_jellybean_raindrops(cur_led_i, initialize);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
                case RGB_MATRIX_DIGITAL_RAIN:
                    rgb_matrix_digital_rain(cur_led_i, initialize);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_BREATHING
                case RGB_MATRIX_BREATHING:
                    rgb_matrix_breathing(cur_led_i);
                    break;
            #endif
            #ifdef RGB_MATRIX_KEYPRESSES
                #ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
                    case RGB_MATRIX_SOLID_REACTIVE:
                        rgb_matrix_solid_reactive(cur_led_i);
                        break;
                #endif
                #ifndef DISABLE_RGB_MATRIX_SPLASH
                    case RGB_MATRIX_SPLASH:
                        rgb_matrix_splash(cur_led_i);
                        break;
                #endif
                #ifndef DISABLE_RGB_MATRIX_MULTISPLASH
                    case RGB_MATRIX_MULTISPLASH:
                        rgb_matrix_multisplash(cur_led_i);
                        break;
                #endif
                #ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
                    case RGB_MATRIX_SOLID_SPLASH:
                        rgb_matrix_solid_splash(cur_led_i);
                        break;
                #endif
                #ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
                    case RGB_MATRIX_SOLID_MULTISPLASH:
                        rgb_matrix_solid_multisplash(cur_led_i);
                        break;
                #endif
            #endif
            case RGB_MATRIX_CUSTOM:
                if (rgb_matrix_custom_modes_count == 0) {
                    rgb_matrix_all_off(cur_led_i);
                } else {
                    rgb_matrix_custom_mode_f custom_effect = rgb_matrix_custom_modes[rgb_matrix_config.custom];
                    custom_effect(cur_led_i, initialize);
                }
            break;
            default:
                break;
        }

        if (!suspend_backlight) {
            rgb_matrix_indicators(cur_led_i);
        }

    done_effect:
        cur_led_i++;
        cur_led_i %= DRIVER_LED_TOTAL;
    }
}

void rgb_matrix_init(void) {
    rgb_matrix_driver.init();

    // clear the key hits
    for (int led_i = 0; led_i < DRIVER_LED_TOTAL; led_i++) {
        g_key_hit[led_i] = 255;
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
static uint8_t increment(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    int16_t new_value = value;
    new_value += step;
    return MIN(MAX(new_value, min), max);
}

static uint8_t decrement(uint8_t value, uint8_t step, uint8_t min, uint8_t max) {
    int16_t new_value = value;
    new_value -= step;
    return MIN(MAX(new_value, min), max);
}

void rgb_matrix_toggle(void) {
    rgb_matrix_config.enable++;
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
    const bool on_custom = rgb_matrix_config.mode == RGB_MATRIX_CUSTOM;
    const bool has_custom = rgb_matrix_custom_modes_count > 0;
    const bool last_custom = rgb_matrix_config.custom == rgb_matrix_custom_modes_count - 1;

    // iterate through custom modes
    if (on_custom && has_custom && !last_custom) {
        rgb_matrix_config.custom++;
        goto end;
    }

    // iterate through regular modes
    rgb_matrix_config.mode++;
    if (rgb_matrix_config.mode >= RGB_MATRIX_EFFECT_MAX)
        rgb_matrix_config.mode = 1;

    // properly wrap back into custom modes
    const bool now_on_custom = rgb_matrix_config.mode == RGB_MATRIX_CUSTOM;
    if (!on_custom && now_on_custom)
        rgb_matrix_config.custom = 0;

end:
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_step_reverse(void) {
    const bool on_custom = rgb_matrix_config.mode == RGB_MATRIX_CUSTOM;
    const bool has_custom = rgb_matrix_custom_modes_count > 0;
    const bool first_custom = rgb_matrix_config.custom == 0;

    // iterate through custom modes
    if (on_custom && has_custom && !first_custom) {
        rgb_matrix_config.custom--;
        goto end;
    }

    // iterate through regular modes
    rgb_matrix_config.mode--;
    if (rgb_matrix_config.mode < 1)
        rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX - 1;

    // properly wrap back into custom modes
    const bool now_on_custom = rgb_matrix_config.mode == RGB_MATRIX_CUSTOM;
    if (!on_custom && now_on_custom)
        rgb_matrix_config.custom = rgb_matrix_custom_modes_count - 1;

end:
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_hue(void) {
    rgb_matrix_config.hsv.h += 8;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_hue(void) {
    rgb_matrix_config.hsv.h -= 8;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_sat(void) {
    rgb_matrix_config.hsv.s = increment(rgb_matrix_config.hsv.s, 8, 0, 255);
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_sat(void) {
    rgb_matrix_config.hsv.s = decrement(rgb_matrix_config.hsv.s, 8, 0, 255);
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_val(void) {
    rgb_matrix_config.hsv.v = increment(rgb_matrix_config.hsv.v, 8, 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_decrease_val(void) {
    rgb_matrix_config.hsv.v = decrement(rgb_matrix_config.hsv.v, 8, 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_increase_speed(void) {
    rgb_matrix_config.speed = increment(rgb_matrix_config.speed, 1, 0, 10);
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);//EECONFIG needs to be increased to support this
}

void rgb_matrix_decrease_speed(void) {
    rgb_matrix_config.speed = decrement(rgb_matrix_config.speed, 1, 0, 10);
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
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    rgb_matrix_config.hsv.v = val;
    eeconfig_update_rgb_matrix(rgb_matrix_config.raw);
}

void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    rgb_matrix_config.hsv.v = val;
}

void rgb_matrix_set_suspend_state(bool state) {
    g_suspend_state = state;
}

__attribute__((weak))
const rgb_matrix_custom_mode_f* rgb_matrix_custom_modes = NULL;

__attribute__((weak))
const uint8_t rgb_matrix_custom_modes_count = 0;
