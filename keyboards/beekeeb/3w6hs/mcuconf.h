#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C0
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C0 TRUE
#define RP_I2C_USE_I2C1 FALSE

#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SCL_PIN
#undef I2C1_SDA_PIN
#define I2C0_SDA_PIN        GP0
#define I2C0_SCL_PIN        GP1
#define I2C1_SDA_PIN        GP0
#define I2C1_SCL_PIN        GP1

