#pragma once

#ifdef SSD1306OLED
#    define USE_I2C
#endif

#if defined(OLED_DRIVER_ENABLE) && (defined(USE_I2C) || defined(USE_MATRIX_I2C))
#    error Cannot use both legacy i2c driver and new i2c_master driver at the same time. Undefine USE_I2C and/or USE_MATRIX_I2C
#endif
