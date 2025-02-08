#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_IC20
#define RP_I2C_USE_IC20 TRUE

// #undef RP_I2C_USE_IC21
// #define RP_I2C_USE_IC21 TRUE

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE
