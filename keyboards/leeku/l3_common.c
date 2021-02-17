/* Copyright 2021 MajorKoos <https://github.com/majorkoos>
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

#include "quantum.h"
#include "l3_common.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "i2c_master.h"
#include "rgblight.h"
#include "ws2812.h"
#include "led.h"
#include "string.h"


#define KEY_LED_CHANNEL_A 0
#define KEY_LED_CHANNEL_B 1
#define KEY_LED_CHANNEL_ALL 0xFF
#define LEDMODE_INDEX_MAX 3
#define LED_BLOCK_MAX 5
#define LEDMODE_ARRAY_SIZE (LEDMODE_INDEX_MAX * LED_BLOCK_MAX)
#define I2C_RETRY_DELAY_MS 5

#ifndef RGBLED_CLIPSTART
#define RGBLED_CLIPSTART 0
#endif

#ifndef RGBLED_CLIPEND
#define RGBLED_CLIPEND 0
#endif

uint8_t localBuffer[0x4B];  // I2C_WRSIZE

void keyboard_pre_init_kb(void) {
    PORTA = 0xFF;  // pull up
    DDRA  = 0x00;  // input
    PORTB = 0xFF;  // pull up
    DDRB  = 0x00;  // input
    PORTC = 0xFF;  // pull up
    DDRC  = 0x00;  // input
    PORTD = 0xF1;  // col(pull up) D-(pull up) D+(pull up) PS2PU(low) USBSHIFT(high)
    DDRD  = 0x03;  // input
#ifdef WATCHDOG_ENABLE
    wdt_enable(WDTO_2S);
#endif
    l3_led_init();
}

void matrix_scan_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif
    matrix_scan_user();
}

#ifdef RGBLIGHT_ENABLE
void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) { l3_set_rgb(start_led, num_leds); }
#endif

#ifdef BACKLIGHT_ENABLE
void backlight_set(uint8_t level) { l3_set_backlight(level); }
#endif

void l3_led_init(void) {
    static bool s_init = false;
    if (!s_init) {
        i2c_init();
        s_init = true;
    }

    // Turn off the backlight as a safe default
    l3_set_backlight(0);  // Off by default
    wait_ms(I2C_RETRY_DELAY_MS);

    // Configure the backlight effects
#ifdef BACKLIGHT_ENABLE
    uint8_t                             led_preset[3][5]     = {{LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS},
                                                                {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS},
                                                                {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS}};
#else
    uint8_t                             led_preset[3][5]     = {{LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}};
#endif
    tinycmd_led_config_preset_req_type *p_led_cfg_preset_req = (tinycmd_led_config_preset_req_type *)localBuffer;
    p_led_cfg_preset_req->cmd_code                           = TINY_CMD_LED_CONFIG_PRESET_F;
    p_led_cfg_preset_req->pkt_len                            = sizeof(tinycmd_led_config_preset_req_type);
    memcpy(p_led_cfg_preset_req->data, led_preset, LEDMODE_ARRAY_SIZE);
    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_led_cfg_preset_req, p_led_cfg_preset_req->pkt_len, WS2812_TIMEOUT);
    wait_ms(I2C_RETRY_DELAY_MS);

    // Set max brightness
    tinycmd_config_req_type *p_cfg_req = (tinycmd_config_req_type *)localBuffer;
    p_cfg_req->cmd_code                = TINY_CMD_CONFIG_F;
    p_cfg_req->pkt_len                 = sizeof(tinycmd_config_req_type);
    p_cfg_req->rgb_num                 = RGBLED_CLIPSTART + RGBLED_CLIPEND + RGBLED_NUM;
#ifdef RGBLIGHT_ENABLE
    p_cfg_req->rgb_limit               = RGBLIGHT_LIMIT_VAL;
#else
    p_cfg_req->rgb_limit               = 0;
#endif
    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_cfg_req, p_cfg_req->pkt_len, WS2812_TIMEOUT);
    wait_ms(I2C_RETRY_DELAY_MS);

    // Turn off the RGB as a safe default
    tinycmd_rgb_all_req_type *p_rgb_all_req = (tinycmd_rgb_all_req_type *)localBuffer;
    p_rgb_all_req->cmd_code                 = TINY_CMD_RGB_ALL_F;
    p_rgb_all_req->pkt_len                  = sizeof(tinycmd_rgb_all_req_type);
    p_rgb_all_req->on                       = 0;
    p_rgb_all_req->led.g                    = 0;
    p_rgb_all_req->led.r                    = 0;
    p_rgb_all_req->led.b                    = 0;
    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_rgb_all_req, p_rgb_all_req->pkt_len, WS2812_TIMEOUT);
    wait_ms(I2C_RETRY_DELAY_MS);

    // Effect update speed
    tinycmd_rgb_effect_speed_req_type *p_rgb_effect_speed_req = (tinycmd_rgb_effect_speed_req_type *)localBuffer;
    p_rgb_effect_speed_req->cmd_code                          = TINY_CMD_RGB_EFFECT_SPEED_F;
    p_rgb_effect_speed_req->pkt_len                           = sizeof(tinycmd_rgb_effect_speed_req_type);
    p_rgb_effect_speed_req->speed                             = 3;
    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_rgb_effect_speed_req, p_rgb_effect_speed_req->pkt_len, WS2812_TIMEOUT);
    wait_ms(I2C_RETRY_DELAY_MS);

    // Turn off the effects
    tinycmd_rgb_set_preset_req_type *p_rgb_set_preset_req = (tinycmd_rgb_set_preset_req_type *)localBuffer;
    rgb_effect_param_type            p_param              = {5, 1, 5, 1};
    p_rgb_set_preset_req->cmd_code                        = TINY_CMD_RGB_SET_PRESET_F;
    p_rgb_set_preset_req->pkt_len                         = sizeof(tinycmd_rgb_set_preset_req_type);
    p_rgb_set_preset_req->index                           = RGB_EFFECT_BASIC;
    p_rgb_set_preset_req->effect_param                    = p_param;
    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_rgb_set_preset_req, p_rgb_set_preset_req->pkt_len, WS2812_TIMEOUT);
    wait_ms(I2C_RETRY_DELAY_MS);
}

void l3_set_backlight(uint8_t level) {
    tinycmd_led_level_req_type *p_led_level_req = (tinycmd_led_level_req_type *)localBuffer;
    p_led_level_req->cmd_code                   = TINY_CMD_LED_LEVEL_F;
    p_led_level_req->pkt_len                    = sizeof(tinycmd_led_level_req_type);
    p_led_level_req->channel                    = KEY_LED_CHANNEL_ALL;
    p_led_level_req->level                      = level;

    if (i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_led_level_req, p_led_level_req->pkt_len, WS2812_TIMEOUT) != I2C_STATUS_SUCCESS) {
        wait_ms(I2C_RETRY_DELAY_MS);
        i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_led_level_req, p_led_level_req->pkt_len, WS2812_TIMEOUT);
    }
}

void l3_set_rgb(LED_TYPE *ledarray, uint16_t leds) {
    tinycmd_rgb_buffer_req_type *p_rgb_buffer_req = (tinycmd_rgb_buffer_req_type *)localBuffer;
    p_rgb_buffer_req->cmd_code                    = TINY_CMD_RGB_BUFFER_F;
    p_rgb_buffer_req->pkt_len                     = sizeof(tinycmd_rgb_buffer_req_type);
    p_rgb_buffer_req->num                         = leds;
    p_rgb_buffer_req->offset                      = RGBLED_CLIPSTART;  // Do I need to do some math to figure out the offset or will the driver to it?
    memcpy(p_rgb_buffer_req->data, ledarray, sizeof(LED_TYPE) * leds);

    i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_rgb_buffer_req, p_rgb_buffer_req->pkt_len, WS2812_TIMEOUT);
};

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        uint8_t                      lock             = 0;
        tinycmd_three_lock_req_type *p_three_lock_req = (tinycmd_three_lock_req_type *)localBuffer;
        p_three_lock_req->cmd_code                    = TINY_CMD_THREE_LOCK_F;
        p_three_lock_req->pkt_len                     = sizeof(tinycmd_three_lock_req_type);
        if (led_state.num_lock) {
            lock |= (1 << 2);
        }
        if (led_state.caps_lock) {
            lock |= (1 << 1);
        }
        if (led_state.scroll_lock) {
            lock |= (1 << 0);
        }
        p_three_lock_req->lock = lock;

        if (i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_three_lock_req, p_three_lock_req->pkt_len, WS2812_TIMEOUT) != I2C_STATUS_SUCCESS) {
            wait_ms(I2C_RETRY_DELAY_MS);
            i2c_transmit(WS2812_ADDRESS, (uint8_t *)p_three_lock_req, p_three_lock_req->pkt_len, WS2812_TIMEOUT);
        }
    }

    return res;
}

