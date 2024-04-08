/*
   MCU Config

   The following settings override the default settings present in the various device driver implementation headers.

   Note that the settings for each driver only have effect if the whole driver is enabled in halconf.h.
*/

// https://docs.qmk.fm/#/platformdev_rp2040
// https://github.com/joshajohnson/sea-picro

#pragma once

#include_next <mcuconf.h>

#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

#undef RP_PWM_USE_PWM2
#define RP_PWM_USE_PWM2 TRUE

// I am no longer sure whether this is also used for audio
#undef RP_PWM_USE_TIM1 
#define RP_PWM_USE_TIM1 TRUE
