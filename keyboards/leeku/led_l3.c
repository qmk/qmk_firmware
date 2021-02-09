/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "wait.h"
#include <stdint.h>
#include <stdbool.h>
#include "led.h"
#include "led_l3.h"
#include "tinycmdapi.h"
#include "hwaddress.h"
#include "print.h"
#include "rgblight.h"
#include "ws2812.h"

extern rgblight_config_t rgblight_config;
#ifdef RGBLIGHT_LED_MAP
const uint8_t rgb_map[] = RGBLIGHT_LED_MAP;
#endif

#define TINY_DETECT_RETRY      20

uint8_t led_mode               = LED_EFFECT_ALWAYS;
uint8_t rgb_effect_index       = 0;

uint8_t led_sleep_preset[3][5] = {
        {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
        {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
        {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}
    };

kbd_configuration_t kbdConf =
{
    0,                  // led_preset_index
    {{LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS}, //led_preset
     {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS},
     {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS}},
    5,                  // rgb_effect_index = solid
    RGBLIGHT_LIMIT_VAL, // rgb_limit
    500,                  // rgb_speed 2: fast, 3: normal, 4: slow
    RGBLED_NUM,         // rgb_chain
    {{ RGB_EFFECT_BOOTHID, 0, 0, 0 },                                                           // RGB_EFFECT_BOOTHID
     { RGB_EFFECT_FADE_BUF, FADE_HIGH_HOLD, FADE_LOW_HOLD, FADE_IN_ACCEL },                     // RGB_EFFECT_FADE_BUF
     { RGB_EFFECT_FADE_LOOP, FADE_HIGH_HOLD, FADE_LOW_HOLD, FADE_IN_ACCEL },                    // RGB_EFFECT_FADE_LOOP
     { RGB_EFFECT_HEARTBEAT_BUF, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL }, // RGB_EFFECT_HEARTBEAT_BUF
     { RGB_EFFECT_HEARTBEAT_LOOP, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL },// RGB_EFFECT_HEARTBEAT_LOOP
     { RGB_EFFECT_BASIC, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL }}         // RGB_EFFECT_HEARTBEAT_LOOP
};

// Indicator LEDs
void led_set(uint8_t usb_led) {
    tinycmd_three_lock(usb_led & (1 << USB_LED_NUM_LOCK),
                       usb_led & (1 << USB_LED_CAPS_LOCK),
                       usb_led & (1 << USB_LED_SCROLL_LOCK),
                       false);
    wait_ms(1);
    tinycmd_three_lock(usb_led & (1 << USB_LED_NUM_LOCK),
                        usb_led & (1 << USB_LED_CAPS_LOCK),
                        usb_led & (1 << USB_LED_SCROLL_LOCK),
                        false);
    }


// In-switch LEDs
void led_off(void) {
    uint8_t led_preset[3][5] = {{LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}};
    tinycmd_led_config_preset((uint8_t *)led_preset, true);
}

void led_on(void) {
    uint8_t led_preset[3][5] = {{LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, led_mode, LED_EFFECT_NONE},
                                {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE},
                                {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE}};
    tinycmd_led_config_preset((uint8_t *)led_preset, true);
}

void led_change_mode(void) {
    if (led_mode == LED_EFFECT_ALWAYS) {
        led_mode = LED_EFFECT_FADING;
    } else if (led_mode == LED_EFFECT_FADING) {
        led_mode = LED_EFFECT_BASECAPS;
    } else if (led_mode == LED_EFFECT_BASECAPS) {
        led_mode = LED_EFFECT_NONE;
    } else if (led_mode == LED_EFFECT_NONE) {
        led_mode = LED_EFFECT_ALWAYS;
    }
    led_on();
}

void led_speed(void) {
    tinycmd_rgb_effect_speed(kbdConf.rgb_limit, true);
}

// Backlighting
void backlight_init_ports(void) {
    #ifdef RGBLIGHT_CLIP_START
    rgblight_set_clipping_range(RGBLIGHT_CLIP_START, RGBLIGHT_CLIP_LEDS);
    #endif
    // Need WDT?
    uint8_t ret = 0;
    uint16_t retry = 0;
    while(ret == 0 && (retry++ < TINY_DETECT_RETRY))
    {
        // Make sure the MCU's responding
        _delay_ms(50);
        ret = tinycmd_ver(true);
        _delay_ms(50);
        if(ret)
        {
            // If it's alive go ahead and configure it
            tinycmd_rgb_all(0, 0, 0, 0, false);
            wait_ms(5);
            tinycmd_rgb_effect_speed(kbdConf.rgb_speed, false);
            wait_ms(5);
            tinycmd_rgb_set_preset(kbdConf.rgb_effect_index, (rgb_effect_param_type *)&kbdConf.rgb_effect_param[kbdConf.rgb_effect_index], false);
            wait_ms(5);
            tinycmd_rgb_set_effect(kbdConf.rgb_effect_index, false);
            wait_ms(5);
            tinycmd_config(21, kbdConf.rgb_limit, false); // ugly hard-coded var.`
            break;
        }
    }
}

void backlight_rgblight_disable(void) {
    uint8_t ret = 0;
    uint16_t retry = 0;
    while(ret == 0 && (retry++ < TINY_DETECT_RETRY))
    {
        // Make sure the MCU's responding
        _delay_ms(50);
        ret = tinycmd_ver(true);
        _delay_ms(50);
        if(ret)
        {
            // If it's alive go ahead and configure it
            tinycmd_rgb_all(0, 0, 0, 0, false);
            wait_ms(10);
            uint8_t led_preset[3][5] = {{LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                        {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                        {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}};
            tinycmd_led_config_preset((uint8_t *)led_preset, false);
            wait_ms(10);
            tinycmd_config(21, 0, false); // ugly hard-coded var.
            break;
        }
    }
}

void backlight_set(uint8_t level) {
    if (level) {
        led_on();
    } else {
        led_off();
    }
}

#ifdef RGBLIGHT_CUSTOM_DRIVER

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        tinycmd_rgb_all(0, 0, 0, 0, false);
        return;
    }

#   ifdef RGBLIGHT_LAYERS
    if (rgblight_layers != NULL
#        if !defined(RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF)
        && rgblight_config.enable
#        elif defined(RGBLIGHT_SLEEP)
        && !is_suspended
#        endif
    ) {
        rgblight_layers_write();
    }
#    endif

#   ifdef RGBLIGHT_LED_MAP
    LED_TYPE led0[RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[rgb_map[i]];
    }
    // start_led = led0 + rgblight_ranges.clipping_start_pos;
    tinycmd_rgb_buffer(rgblight_ranges.clipping_num_leds, rgblight_ranges.clipping_start_pos, (uint8_t *)led0, false);
#    else
    // start_led = led + rgblight_ranges.clipping_start_pos;
    tinycmd_rgb_buffer(rgblight_ranges.clipping_num_leds, rgblight_ranges.clipping_start_pos, (uint8_t *)led, false);
#   endif
}
#endif

// Power management
void led_restore(void) {
    // tinycmd_sleep(0, true);
}

void led_sleep(void) {
    // tinycmd_sleep(1, true);
}
