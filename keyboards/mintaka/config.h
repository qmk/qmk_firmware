#pragma once
#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP8
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP9
#define OLED_DISPLAY_128X64

#define ENCODER_A_PINS { GP12, GP11 }
#define ENCODER_B_PINS { GP13, GP10 }
