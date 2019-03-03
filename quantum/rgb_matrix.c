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

#include "rgb_matrix_animations/solid_color_anim.h"
#include "rgb_matrix_animations/alpha_mods_anim.h"
#include "rgb_matrix_animations/dual_beacon_anim.h"
#include "rgb_matrix_animations/gradient_up_down_anim.h"
#include "rgb_matrix_animations/raindrops_anim.h"
#include "rgb_matrix_animations/cycle_all_anim.h"
#include "rgb_matrix_animations/cycle_left_right_anim.h"
#include "rgb_matrix_animations/cycle_up_down_anim.h"
#include "rgb_matrix_animations/rainbow_beacon_anim.h"
#include "rgb_matrix_animations/rainbow_pinwheels_anim.h"
#include "rgb_matrix_animations/rainbow_moving_chevron_anim.h"
#include "rgb_matrix_animations/jellybean_raindrops_anim.h"
#include "rgb_matrix_animations/digital_rain_anim.h"
#include "rgb_matrix_animations/solid_reactive_anim.h"
#include "rgb_matrix_animations/splash_anim.h"
#include "rgb_matrix_animations/solid_splash_anim.h"

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

#if !defined(DISABLE_RGB_MATRIX_RAINDROPS) || !defined(DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS) || !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
    #define TRACK_PREVIOUS_EFFECT
#endif

bool g_suspend_state = false;

rgb_counters g_rgb_counters;

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

void rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count) {
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
        rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        if (led_count > 0) {
            for (uint8_t i = LED_HITS_TO_REMEMBER; i > 1; i--) {
                g_rgb_counters.last_led_hit[i - 1] = g_rgb_counters.last_led_hit[i - 2];
            }
            g_rgb_counters.last_led_hit[0] = led[0];
            g_rgb_counters.last_led_count = MIN(LED_HITS_TO_REMEMBER, g_rgb_counters.last_led_count + 1);
        }
        for(uint8_t i = 0; i < led_count; i++)
            g_rgb_counters.key_hit[led[i]] = 0;
        g_rgb_counters.any_key_hit = 0;
    } else {
        #ifdef RGB_MATRIX_KEYRELEASES
        uint8_t led[8], led_count;
        rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, led, &led_count);
        for(uint8_t i = 0; i < led_count; i++)
            g_rgb_counters.key_hit[led[i]] = 255;

        g_rgb_counters.any_key_hit = 255;
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
    switch ( (g_rgb_counters.tick & (0b11 << factor)) >> factor )
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

    g_rgb_counters.tick++;

    if ( g_rgb_counters.any_key_hit < 0xFFFFFFFF ) {
        g_rgb_counters.any_key_hit++;
    }

    for ( int led = 0; led < DRIVER_LED_TOTAL; led++ ) {
        if ( g_rgb_counters.key_hit[led] < 255 ) {
            if (g_rgb_counters.key_hit[led] == 254)
                g_rgb_counters.last_led_count = MAX(g_rgb_counters.last_led_count - 1, 0);
            g_rgb_counters.key_hit[led]++;
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
            (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_rgb_counters.any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));
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
                rgb_matrix_dual_beacon(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
            case RGB_MATRIX_GRADIENT_UP_DOWN:
                rgb_matrix_gradient_up_down(&g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINDROPS
            case RGB_MATRIX_RAINDROPS:
                rgb_matrix_raindrops(initialize, &g_rgb_counters, &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
            case RGB_MATRIX_CYCLE_ALL:
                rgb_matrix_cycle_all(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
            case RGB_MATRIX_CYCLE_LEFT_RIGHT:
                rgb_matrix_cycle_left_right(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
            case RGB_MATRIX_CYCLE_UP_DOWN:
                rgb_matrix_cycle_up_down(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
            case RGB_MATRIX_RAINBOW_BEACON:
                rgb_matrix_rainbow_beacon(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
            case RGB_MATRIX_RAINBOW_PINWHEELS:
                rgb_matrix_rainbow_pinwheels(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
            case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
                rgb_matrix_rainbow_moving_chevron(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
            case RGB_MATRIX_JELLYBEAN_RAINDROPS:
                rgb_matrix_jellybean_raindrops(initialize, &g_rgb_counters, &rgb_matrix_config);
                break;
        #endif
        #ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
            case RGB_MATRIX_DIGITAL_RAIN:
                rgb_matrix_digital_rain(initialize);
                break;
        #endif
        #ifdef RGB_MATRIX_KEYPRESSES
            #ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
                case RGB_MATRIX_SOLID_REACTIVE:
                    rgb_matrix_solid_reactive(&g_rgb_counters, &rgb_matrix_config);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SPLASH
                case RGB_MATRIX_SPLASH:
                    rgb_matrix_splash(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_MULTISPLASH
                case RGB_MATRIX_MULTISPLASH:
                    rgb_matrix_multisplash(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
                case RGB_MATRIX_SOLID_SPLASH:
                    rgb_matrix_solid_splash(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
                    break;
            #endif
            #ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
                case RGB_MATRIX_SOLID_MULTISPLASH:
                    rgb_matrix_solid_multisplash(&g_rgb_counters, &g_rgb_leds[0], &rgb_matrix_config);
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
//      // rgb_matrix_map_row_column_to_led(row,column,led,&led_count);
//      // for(uint8_t i = 0; i < led_count; i++)
//      rgb_matrix_map_row_column_to_led( row, column, index );
//  }
// }

void rgb_matrix_init(void) {
  rgb_matrix_driver.init();

  // TODO: put the 1 second startup delay here?

  // clear the key hits
  for ( int led=0; led<DRIVER_LED_TOTAL; led++ ) {
      g_rgb_counters.key_hit[led] = 255;
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
//     rgb_matrix_map_row_column_to_led(row,column,led,&led_count);
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
    return g_rgb_counters.tick;
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

uint8_t rgb_matrix_get_mode(void) {
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
