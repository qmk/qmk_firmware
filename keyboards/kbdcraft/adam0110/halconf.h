#pragma once

#define HAL_USE_I2C TRUE

#define HAL_USE_PWM TRUE
#define HAL_USE_PAL TRUE

#define HAL_USE_SERIAL TRUE
#define PAL_USE_CALLBACKS TRUE

#include_next <halconf.h>

#undef  SERIAL_USB_BUFFERS_SIZE
#define SERIAL_USB_BUFFERS_SIZE 256

#undef  SERIAL_BUFFERS_SIZE
#define SERIAL_BUFFERS_SIZE     128
