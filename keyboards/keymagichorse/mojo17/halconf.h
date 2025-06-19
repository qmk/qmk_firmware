#pragma once

#define PAL_USE_WAIT       TRUE
#define PAL_USE_CALLBACKS  TRUE
#define HAL_USE_PWM        TRUE
#define HAL_USE_PAL        TRUE
#define HAL_USE_ADC        TRUE
#define HAL_USE_SERIAL     TRUE

#include_next <halconf.h>
