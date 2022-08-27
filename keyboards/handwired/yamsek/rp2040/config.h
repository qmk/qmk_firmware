#pragma once

#include "config_common.h"

#define RGB_DI_PIN GP16
//PICO_DEFAULT_WS2812_PIN
#define RGBLED_NUM 1

#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define I2C1_CLOCK_SPEED 100000

#define I2C1_SCL_PAL_MODE (PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_PUE | PAL_RP_PAD_SLEWFAST)
#define I2C1_SDA_PAL_MODE (PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_PUE | PAL_RP_PAD_SLEWFAST)
// removing 'PAL_RP_PAD_DRIVE4' which the portexpander in the left keyboard half doesn't like
// alternative solution would be to add a 100pF ceramic-capacitor between SCL and GND

