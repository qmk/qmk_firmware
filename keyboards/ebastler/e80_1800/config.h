#pragma once

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 2
#define BACKLIGHT_PAL_MODE 2


#ifdef OLED_ENABLE

/* I2C for OLED - only enable defines if driver is enabled */
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN        B10
#define I2C1_SDA_PIN        B11
#define I2C1_SCL_PAL_MODE   1
#define I2C1_SDA_PAL_MODE   1
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH   3U
#define I2C1_TIMINGR_SCLL   9U

#endif