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

#pragma once

#ifndef RGBLIGHT_ENABLE
#include "color.h"
#endif


#define TINY_CMD_CONFIG_F               0
#define TINY_CMD_VER_F                  1
#define TINY_CMD_RESET_F                2
#define TINY_CMD_THREE_LOCK_F           3
#define TINY_CMD_SLEEP_F                5

// RGB Command
#define TINY_CMD_RGB_ALL_F              20
#define TINY_CMD_RGB_POS_F              21
#define TINY_CMD_RGB_RANGE_F            22
#define TINY_CMD_RGB_BUFFER_F           23
#define TINY_CMD_RGB_SET_EFFECT_F       24
#define TINY_CMD_RGB_SET_PRESET_F       25
#define TINY_CMD_RGB_EFFECT_SPEED_F     26
#define TINY_CMD_RGB_EFFECT_ON_F        27

// LED Command
#define TINY_CMD_LED_LEVEL_F            40
#define TINY_CMD_LED_SET_EFFECT_F       41
#define TINY_CMD_LED_SET_PRESET_F       42
#define TINY_CMD_LED_CONFIG_PRESET_F    43
#define TINY_CMD_LED_EFFECT_ON_F        44

typedef enum {
    LED_EFFECT_FADING          = 0,
    LED_EFFECT_FADING_PUSH_ON  = 1,
    LED_EFFECT_PUSHED_LEVEL    = 2,
    LED_EFFECT_PUSH_ON         = 3,
    LED_EFFECT_PUSH_OFF        = 4,
    LED_EFFECT_ALWAYS          = 5,
    LED_EFFECT_BASECAPS        = 6,
    LED_EFFECT_OFF             = 7,
    LED_EFFECT_NONE
}LED_MODE;

typedef enum {
    RGB_EFFECT_BOOTHID = 0,
    RGB_EFFECT_FADE_BUF,
    RGB_EFFECT_FADE_LOOP,
    RGB_EFFECT_HEARTBEAT_BUF,
    RGB_EFFECT_HEARTBEAT_LOOP,
    RGB_EFFECT_BASIC,
    RGB_EFFECT_MAX
}RGB_PRESET;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t data[15];
} tinycmd_led_config_preset_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t channel;
  uint8_t level;
} tinycmd_led_level_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint16_t speed; // 2: fast, 3: normal, 4: slow
} tinycmd_rgb_effect_speed_req_type;

typedef struct {
    uint8_t index;
    uint8_t high_hold;
    uint8_t low_hold;
    uint8_t accel_mode;
} rgb_effect_param_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t index;
  rgb_effect_param_type effect_param;
} tinycmd_rgb_set_preset_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t num;
  uint8_t offset;
  uint8_t data[RGBLED_NUM*3];
} tinycmd_rgb_buffer_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t rgb_num;
  uint16_t rgb_limit;
} tinycmd_config_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t on; // on or off
  LED_TYPE led;
} tinycmd_rgb_all_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t on; // 0: off, TRUE: on
} tinycmd_rgb_effect_on_req_type;

typedef struct {
  uint8_t cmd_code;
  uint8_t pkt_len;
  uint8_t lock;
} tinycmd_three_lock_req_type;

void l3_set_backlight(uint8_t level);
void l3_set_rgb(LED_TYPE *ledarray, uint16_t leds);
void l3_led_init(void);
