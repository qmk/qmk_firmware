// Copyright 2025 Wolf Yuan <me at wolf-yuan.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP7
#define I2C1_SDA_PIN GP6
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 3

#define WS2812_DI_PIN GP1
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 12
#define RGBLIGHT_LIMIT_VAL 45
#define RGBLIGHT_DEFAULT_SAT 0
#define RGBLIGHT_SLEEP

#define ENCODER_A_PINS { GP29 }
#define ENCODER_B_PINS { GP0 }
#define ENCODER_RESOLUTIONS { 4 }
