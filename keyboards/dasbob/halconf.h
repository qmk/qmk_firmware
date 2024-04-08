/*
    HAL Config

    This file allows you to enable or disable various device drivers. 
    
    You may also use this file in order to override the device driver defaults.
*/

#pragma once

#undef HAL_USE_SIO
#define HAL_USE_SIO TRUE

#define HAL_USE_I2C TRUE

#define HAL_USE_PWM TRUE

#define HAL_USE_PAL TRUE

#include_next <halconf.h>
