#pragma once

#ifdef OLED_ENABLE
    #define HAL_USE_I2C TRUE
    #define I2C_DRIVER I2CD0
    #define I2C1_SDA_PIN GP8
    #define I2C1_SCL_PIN GP9

    #define OLED_DISPLAY_128X64
    #define OLED_DISPLAY_WIDTH 128
    #define OLED_DISPLAY_HEIGHT 64

    #include_next <mcuconf.h> // for i2c
    #undef RP_I2C_USE_I2C0
    #define RP_I2C_USE_I2C0 TRUE
    #undef RP_I2C_USE_I2C1
    #define RP_I2C_USE_I2C1 FALSE
#endif