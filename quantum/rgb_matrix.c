/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
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
#include <avr/io.h>
#include "TWIlib.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include "lufa.h"
#include <math.h>

#define BACKLIGHT_EFFECT_MAX 17

rgb_matrix_config g_config = {
	.enabled = 1,
    .brightness = 255,
    .effect = 7,
    .color_1 = { .h = 130, .s = 255, .v = 255 },
    .color_2 = { .h = 70, .s = 255, .v = 255 },
    .caps_lock_indicator = { .color = { .h = 0, .s = 0, .v = 255 }, .index = 255 },
    .layer_1_indicator = { .color = { .h = 0, .s = 0, .v = 255 }, .index = 255 },
    .layer_2_indicator = { .color = { .h = 0, .s = 0, .v = 255 }, .index = 255 },
    .layer_3_indicator = { .color = { .h = 0, .s = 0, .v = 255 }, .index = 255 },
};  

bool g_suspend_state = false;
uint8_t g_indicator_state = 0;

// Global tick at 20 Hz
uint32_t g_tick = 0;

// Ticks since this key was last hit.
uint8_t g_key_hit[DRIVER_LED_TOTAL];

// Ticks since any key was last hit.
uint32_t g_any_key_hit = 0;

#ifndef PI
#define PI 3.14159265
#endif

// Last led hit
#define LED_HITS_TO_REMEMBER 8
uint8_t g_last_led_hit[LED_HITS_TO_REMEMBER] = {255};
uint8_t g_last_led_count = 0;


void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count)
{
    is31_led led;
    *led_count = 0;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        // map_index_to_led(i, &led);
        led = g_is31_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            led_i[*led_count] = i;
            (*led_count)++;
        }
    }
}


void backlight_update_pwm_buffers(void)
{
    IS31FL3731_update_pwm_buffers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
    IS31FL3731_update_led_control_registers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
}

void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
    IS31FL3731_set_color( index, red, green, blue );
}

void backlight_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
    IS31FL3731_set_color_all( red, green, blue );
}

void backlight_set_key_hit(uint8_t row, uint8_t column)
{
    uint8_t led[8], led_count;
    map_row_column_to_led(row,column,led,&led_count);
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
}

void backlight_unset_key_hit(uint8_t row, uint8_t column)
{
    uint8_t led[8], led_count;
    map_row_column_to_led(row,column,led,&led_count);
    for(uint8_t i = 0; i < led_count; i++)
        g_key_hit[led[i]] = 255;

    g_any_key_hit = 255;
}

// This is (F_CPU/1024) / 20 Hz
// = 15625 Hz / 20 Hz
// = 781
// #define TIMER3_TOP 781

void backlight_timer_init(void)
{
    
    static uint8_t backlight_timer_is_init = 0;
    if ( backlight_timer_is_init )
    {
        return;
    }
    backlight_timer_is_init = 1;

    // Timer 3 setup
    //TCCR3B = _BV(WGM32) |             // CTC mode OCR3A as TOP
    //       _BV(CS32) | _BV(CS30); // prescale by /1024
    // Set TOP value
    //uint8_t sreg = SREG;
    //cli();

    //OCR3AH = (TIMER3_TOP >> 8) & 0xff;
    //OCR3AL = TIMER3_TOP & 0xff;
    //SREG = sreg;
    
}

void backlight_timer_enable(void)
{
    //TIMSK3 |= _BV(OCIE3A);
}

void backlight_timer_disable(void)
{
    //TIMSK3 &= ~_BV(OCIE3A);
}

void backlight_set_suspend_state(bool state)
{
    g_suspend_state = state;
}

void backlight_set_indicator_state(uint8_t state)
{
    g_indicator_state = state;
}

void backlight_effect_rgb_test(void)
{
    // Mask out bits 4 and 5
    // This 2-bit value will stay the same for 16 ticks.
    switch ( (g_tick & 0x30) >> 4 )
    {
        case 0:
        {
            backlight_set_color_all( 20, 0, 0 );
            break;
        }
        case 1:
        {
            backlight_set_color_all( 0, 20, 0 );
            break;
        }
        case 2:
        {
            backlight_set_color_all( 0, 0, 20 );
            break;
        }
        case 3:
        {
            backlight_set_color_all( 20, 20, 20 );
            break;
        }
    }
}

// This tests the LEDs
// Note that it will change the LED control registers
// in the LED drivers, and leave them in an invalid
// state for other backlight effects.
// ONLY USE THIS FOR TESTING LEDS!
void backlight_effect_single_LED_test(void)
{
    static uint8_t color = 0; // 0,1,2 for R,G,B
    static uint8_t row = 0;
    static uint8_t column = 0;

    static uint8_t tick = 0;
    tick++;

    if ( tick > 2 )
    {
        tick = 0;
        column++;
    }
    if ( column > MATRIX_COLS )
    {
        column = 0;
        row++;
    }
    if ( row > MATRIX_ROWS )
    {
        row = 0;
        color++;
    }
    if ( color > 2 )
    {
        color = 0;
    }

    uint8_t led[8], led_count;
    map_row_column_to_led(row,column,led,&led_count);
    for(uint8_t i = 0; i < led_count; i++) {
        backlight_set_color_all( 40, 40, 40 );
        backlight_test_led( led[i], color==0, color==1, color==2 );
    }
}

// All LEDs off
void backlight_effect_all_off(void)
{
    backlight_set_color_all( 0, 0, 0 );
}

// Solid color
void backlight_effect_solid_color(void)
{
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb = hsv_to_rgb( hsv );
    backlight_set_color_all( rgb.r, rgb.g, rgb.b );
}

void backlight_effect_solid_reactive(void)
{
	// Relies on hue being 8-bit and wrapping
	for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
	{
		uint16_t offset2 = g_key_hit[i]<<2;
		offset2 = (offset2<=130) ? (130-offset2) : 0;

		HSV hsv = { .h = g_config.color_1.h+offset2, .s = 255, .v = g_config.brightness };
		RGB rgb = hsv_to_rgb( hsv );
		backlight_set_color( i, rgb.r, rgb.g, rgb.b );
	}
}

// alphas = color1, mods = color2
void backlight_effect_alphas_mods(void)
{
    RGB rgb1 = hsv_to_rgb( (HSV){ .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness } );
    RGB rgb2 = hsv_to_rgb( (HSV){ .h = g_config.color_2.h, .s = g_config.color_2.s, .v = g_config.brightness } );
    
    is31_led led;
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_is31_leds[i];
        if ( led.matrix_co.raw < 0xFF ) {
            if ( led.modifier )
            {
                backlight_set_color( i, rgb2.r, rgb2.g, rgb2.b );
            }
            else
            {
                backlight_set_color( i, rgb1.r, rgb1.g, rgb1.b );
            }
        }
    }
}

void backlight_effect_gradient_up_down(void)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
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

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_led_to_point( i, &point );
        point = g_is31_leds[i].point;
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y>>4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = g_config.color_1.h + ( deltaH * y );
        hsv.s = g_config.color_1.s + ( deltaS * y );
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_raindrops(bool initialize)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
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

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % DRIVER_LED_TOTAL : 255;

    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = h1 + ( deltaH * ( rand() & 0x03 ) );
            hsv.s = s1 + ( deltaS * ( rand() & 0x03 ) );
            // Override brightness with global brightness control
            hsv.v = g_config.brightness;;

            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_cycle_all(void)
{
    uint8_t offset = g_tick & 0xFF;

    is31_led led;

    // Relies on hue being 8-bit and wrapping
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_is31_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            HSV hsv = { .h = offset+offset2, .s = 255, .v = g_config.brightness };
            RGB rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_cycle_left_right(void)
{
    uint8_t offset = g_tick & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    is31_led led;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_is31_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            // map_led_to_point( i, &point );
            point = g_is31_leds[i].point;
            // Relies on hue being 8-bit and wrapping
            hsv.h = point.x + offset + offset2;
            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_cycle_up_down(void)
{
    uint8_t offset = g_tick & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    is31_led led;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // map_index_to_led(i, &led);
        led = g_is31_leds[i];
        if (led.matrix_co.raw < 0xFF) {
            uint16_t offset2 = g_key_hit[i]<<2;
            offset2 = (offset2<=63) ? (63-offset2) : 0;

            // map_led_to_point( i, &point );
            point = g_is31_leds[i].point;
            // Relies on hue being 8-bit and wrapping
            hsv.h = point.y + offset + offset2;
            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}


void backlight_effect_dual_beacon(void) {
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb;
    is31_led led;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_is31_leds[i];
        hsv.h = ((led.point.y - 32.0)* cos(g_tick * PI / 128) / 32 + (led.point.x - 112.0) * sin(g_tick * PI / 128) / (112)) * (g_config.color_2.h - g_config.color_1.h) + g_config.color_1.h;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_rainbow_beacon(void) {
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb;
    is31_led led;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_is31_leds[i];
        hsv.h = 1.5 * (led.point.y - 32.0)* cos(g_tick * PI / 128) + 1.5 * (led.point.x - 112.0) * sin(g_tick * PI / 128) + g_config.color_1.h;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_rainbow_pinwheels(void) {
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb;
    is31_led led;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_is31_leds[i];
        hsv.h = 2 * (led.point.y - 32.0)* cos(g_tick * PI / 128) + 2 * (66 - abs(led.point.x - 112.0)) * sin(g_tick * PI / 128) + g_config.color_1.h;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_rainbow_moving_chevron(void) {
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb;
    is31_led led;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_is31_leds[i];
        // uint8_t r = g_tick;
        uint8_t r = 32;
        hsv.h = 1.5 * abs(led.point.y - 32.0)* sin(r * PI / 128) + 1.5 * (led.point.x - (g_tick / 256.0 * 224)) * cos(r * PI / 128) + g_config.color_1.h;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}


void backlight_effect_jellybean_raindrops( bool initialize )
{
    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % DRIVER_LED_TOTAL : 255;

    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = rand() & 0xFF;
            hsv.s = rand() & 0xFF;
            // Override brightness with global brightness control
            hsv.v = g_config.brightness;;

            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}

void backlight_effect_multisplash(void) {
    // if (g_any_key_hit < 0xFF) {    
        HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
        RGB rgb;
        is31_led led;
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            led = g_is31_leds[i];
            uint16_t c = 0, d = 0;
            is31_led last_led;
            // if (g_last_led_count) {
                for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
                    last_led = g_is31_leds[g_last_led_hit[last_i]];
                    uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
                    uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
                    c += MIN(MAX(effect, 0), 255);
                    d += 255 - MIN(MAX(effect, 0), 255);
                }
            // } else {
            //     d = 255;
            // }
            hsv.h = (g_config.color_1.h + c) % 256;
            hsv.v = MAX(MIN(d, 255), 0);
            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    // } else {
        // backlight_set_color_all( 0, 0, 0 );
    // }
}


void backlight_effect_splash(void) {
    g_last_led_count = MIN(g_last_led_count, 1);   
    backlight_effect_multisplash();
}


void backlight_effect_solid_multisplash(void) {
    // if (g_any_key_hit < 0xFF) {    
        HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
        RGB rgb;
        is31_led led;
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            led = g_is31_leds[i];
            uint16_t d = 0;
            is31_led last_led;
            // if (g_last_led_count) {
                for (uint8_t last_i = 0; last_i < g_last_led_count; last_i++) {
                    last_led = g_is31_leds[g_last_led_hit[last_i]];
                    uint16_t dist = (uint16_t)sqrt(pow(led.point.x - last_led.point.x, 2) + pow(led.point.y - last_led.point.y, 2));
                    uint16_t effect = (g_key_hit[g_last_led_hit[last_i]] << 2) - dist;
                    d += 255 - MIN(MAX(effect, 0), 255);
                }
            // } else {
            //     d = 255;
            // }
            hsv.v = MAX(MIN(d, 255), 0);
            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    // } else {
        // backlight_set_color_all( 0, 0, 0 );
    // }
}


void backlight_effect_solid_splash(void) {
    g_last_led_count = MIN(g_last_led_count, 1);   
    backlight_effect_solid_multisplash();
}

void backlight_effect_custom(void)
{
    HSV hsv;
    RGB rgb;
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        backlight_get_key_color(i, &hsv);
        // Override brightness with global brightness control
        hsv.v = g_config.brightness;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}

void backlight_effect_indicators_set_colors( uint8_t index, HSV hsv )
{
    RGB rgb = hsv_to_rgb( hsv );
    if ( index == 254 )
    {
        backlight_set_color_all( rgb.r, rgb.g, rgb.b );
    }
    else
    {
        backlight_set_color( index, rgb.r, rgb.g, rgb.b );

        // If the spacebar LED is the indicator,
        // do the same for the spacebar stabilizers
        if ( index == 36+0 ) // LC0
        {
#ifdef CONFIG_ZEAL65
            backlight_set_color( 36+7, rgb.r, rgb.g, rgb.b ); // LC7
            backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
#else
            backlight_set_color( 36+6, rgb.r, rgb.g, rgb.b ); // LC6
            backlight_set_color( 54+13, rgb.r, rgb.g, rgb.b ); // LD13
            if ( g_config.use_7u_spacebar )
            {
                backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
            }
#endif
        }
    }
}

// This runs after another backlight effect and replaces
// colors already set
void backlight_effect_indicators(void)
{
    if ( g_config.caps_lock_indicator.index != 255 &&
            ( g_indicator_state & (1<<USB_LED_CAPS_LOCK) ) )
    {
        backlight_effect_indicators_set_colors( g_config.caps_lock_indicator.index, g_config.caps_lock_indicator.color );
    }

    // This if/else if structure allows higher layers to
    // override lower ones. If we set layer 3's indicator
    // to none, then it will NOT show layer 2 or layer 1
    // indicators, even if those layers are on via the
    // MO13/MO23 Fn combo magic.
    //
    // Basically we want to handle the case where layer 3 is
    // still the backlight configuration layer and we don't
    // want "all LEDs" indicators hiding the backlight effect,
    // but still allow end users to do whatever they want.
    if ( IS_LAYER_ON(3) )
    {
        if ( g_config.layer_3_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_3_indicator.index, g_config.layer_3_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(2) )
    {
        if ( g_config.layer_2_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_2_indicator.index, g_config.layer_2_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(1) )
    {
        if ( g_config.layer_1_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_1_indicator.index, g_config.layer_1_indicator.color );
        }
    }
}

void backlight_rgb_task(void) {
	if (!g_config.enabled) {
    	backlight_effect_all_off();
    	return;
    }
    // delay 1 second before driving LEDs or doing anything else
    static uint8_t startup_tick = 0;
    if ( startup_tick < 20 )
    {
        startup_tick++;
        return;
    }

    g_tick++;

    if ( g_any_key_hit < 0xFFFFFFFF )
    {
        g_any_key_hit++;
    }

    for ( int led = 0; led < DRIVER_LED_TOTAL; led++ )
    {
        if ( g_key_hit[led] < 255 )
        {
            if (g_key_hit[led] == 254)
                g_last_led_count = MAX(g_last_led_count - 1, 0);
            g_key_hit[led]++;
        }
    }

    // Factory default magic value
    if ( g_config.effect == 255 )
    {
        backlight_effect_rgb_test();
        return;
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
            backlight_effect_solid_color();
            break;
        case 1:
            backlight_effect_solid_reactive();
            break;
        case 2:
            backlight_effect_alphas_mods();
            break;
        case 3:
            backlight_effect_dual_beacon();
            break;
        case 4:
            backlight_effect_gradient_up_down();
            break;
        case 5:
            backlight_effect_raindrops( initialize );
            break;
        case 6:
            backlight_effect_cycle_all();
            break;
        case 7:
            backlight_effect_cycle_left_right();
            break;
        case 8:
            backlight_effect_cycle_up_down();
            break;
        case 9:
            backlight_effect_rainbow_beacon();
            break;
        case 10:
            backlight_effect_rainbow_pinwheels();
            break;
        case 11:
            backlight_effect_rainbow_moving_chevron();
            break;
        case 12:
            backlight_effect_jellybean_raindrops( initialize );
            break;
        case 13:
            backlight_effect_splash();
            break;
        case 14:
            backlight_effect_multisplash();
            break;
        case 15:
            backlight_effect_solid_splash();
            break;
        case 16:
            backlight_effect_solid_multisplash();
            break;
        case 17:
        default:
            backlight_effect_custom();
            break;
    }

    if ( ! suspend_backlight )
    {
        backlight_effect_indicators();
    }

}

// void backlight_set_indicator_index( uint8_t *index, uint8_t row, uint8_t column )
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

void backlight_config_load(void)
{
    eeprom_read_block( &g_config, EEPROM_BACKLIGHT_CONFIG_ADDR, sizeof(rgb_matrix_config) );
}

void backlight_config_save(void)
{
    eeprom_update_block( &g_config, EEPROM_BACKLIGHT_CONFIG_ADDR, sizeof(rgb_matrix_config) );
}

void backlight_init_drivers(void)
{
    //sei();

    // Initialize TWI
    TWIInit();
    IS31FL3731_init( DRIVER_ADDR_1 );
    IS31FL3731_init( DRIVER_ADDR_2 );

    for ( int index = 0; index < DRIVER_LED_TOTAL; index++ )
    {
        bool enabled = true;
        // This only caches it for later
        IS31FL3731_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    IS31FL3731_update_led_control_registers( DRIVER_ADDR_1, DRIVER_ADDR_2 );

    // TODO: put the 1 second startup delay here?

    // clear the key hits
    for ( int led=0; led<DRIVER_LED_TOTAL; led++ )
    {
        g_key_hit[led] = 255;
    }
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

void backlight_color_1_hue_increase(void)
{
    g_config.color_1.h = increment( g_config.color_1.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_hue_decrease(void)
{
    g_config.color_1.h = decrement( g_config.color_1.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_sat_increase(void)
{
    g_config.color_1.s = increment( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_1_sat_decrease(void)
{
    g_config.color_1.s = decrement( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_hue_increase(void)
{
    g_config.color_2.h = increment( g_config.color_2.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_hue_decrease(void)
{
    g_config.color_2.h = decrement( g_config.color_2.h, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_sat_increase(void)
{
    g_config.color_2.s = increment( g_config.color_2.s, 8, 0, 255 );
    backlight_config_save();
}

void backlight_color_2_sat_decrease(void)
{
    g_config.color_2.s = decrement( g_config.color_2.s, 8, 0, 255 );
    backlight_config_save();
}

void *backlight_get_custom_key_color_eeprom_address( uint8_t led )
{
    // 3 bytes per color
    return EEPROM_BACKLIGHT_KEY_COLOR_ADDR + ( led * 3 );
}

void backlight_get_key_color( uint8_t led, HSV *hsv )
{
    void *address = backlight_get_custom_key_color_eeprom_address( led );
    hsv->h = eeprom_read_byte(address);
    hsv->s = eeprom_read_byte(address+1);
    hsv->v = eeprom_read_byte(address+2);
}

void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv )
{
    uint8_t led[8], led_count;
    map_row_column_to_led(row,column,led,&led_count);
    for(uint8_t i = 0; i < led_count; i++) {
        if ( led[i] < DRIVER_LED_TOTAL )
        {
            void *address = backlight_get_custom_key_color_eeprom_address(led[i]);
            eeprom_update_byte(address, hsv.h);
            eeprom_update_byte(address+1, hsv.s);
            eeprom_update_byte(address+2, hsv.v);
        }
    }
}

void backlight_test_led( uint8_t index, bool red, bool green, bool blue )
{
    for ( int i=0; i<DRIVER_LED_TOTAL; i++ )
    {
        if ( i == index )
        {
            IS31FL3731_set_led_control_register( i, red, green, blue );
        }
        else
        {
            IS31FL3731_set_led_control_register( i, false, false, false );
        }
    }
}

uint32_t backlight_get_tick(void)
{
    return g_tick;
}

void backlight_debug_led( bool state )
{
    // if (state)
    // {
    //  // Output high.
    //  DDRD |= (1<<6);
    //  PORTD |= (1<<6);
    // }
    // else
    // {
    //  // Output low.
    //  DDRD &= ~(1<<6);
    //  PORTD &= ~(1<<6);
    // }
}

void rgblight_toggle(void) {
	g_config.enabled ^= 1;
    backlight_config_save();
}

void rgblight_step(void) {
    g_config.effect = (g_config.effect + 1) % (BACKLIGHT_EFFECT_MAX + 1);
    backlight_config_save();
}

void rgblight_increase_hue(void) {
	backlight_color_1_hue_increase();
	backlight_color_2_hue_increase();
}

void rgblight_decrease_hue(void) {
	backlight_color_1_hue_decrease();
	backlight_color_2_hue_decrease();
}

void rgblight_increase_sat(void) {
	backlight_color_1_sat_increase();
	backlight_color_2_sat_increase();
}

void rgblight_decrease_sat(void) {
	backlight_color_1_sat_decrease();
	backlight_color_2_sat_decrease();
}

void rgblight_increase_val(void) {
    g_config.color_1.v = increment( g_config.color_1.s, 8, 0, 255 );
    g_config.color_2.v = increment( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void rgblight_decrease_val(void) {
    g_config.color_1.v = decrement( g_config.color_1.s, 8, 0, 255 );
    g_config.color_2.v = decrement( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}

void rgblight_mode(uint8_t mode) {
    g_config.effect = mode;
}

uint32_t rgblight_get_mode(void) {
    return g_config.effect;
}
