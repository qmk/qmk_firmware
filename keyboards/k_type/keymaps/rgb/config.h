#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL

// i2c_master defines
#    define I2C1_SCL 0 // A2 on pinout = B0
#    define I2C1_SDA 1 // A2 on pinout = B1
#    define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#    define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2
//#    define I2C2_SCL 10 // A2 on pinout = C10
//#    define I2C2_SDA 11 // A2 on pinout = C11
//#    define I2C2_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
//#    define I2C2_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2

#    define DRIVER_ADDR_1 0b1010000
#    define DRIVER_ADDR_2 0b1010001
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 64
//#    define DRIVER_2_LED_TOTAL 55
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#endif
