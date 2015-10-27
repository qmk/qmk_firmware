/* mbed Microcontroller Library
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_DEVICE_H
#define MBED_DEVICE_H

#define DEVICE_PORTIN           0
#define DEVICE_PORTOUT          0
#define DEVICE_PORTINOUT        0

#define DEVICE_INTERRUPTIN      1

#define DEVICE_ANALOGIN         1
#define DEVICE_ANALOGOUT        1

#define DEVICE_SERIAL           1
#define DEVICE_SERIAL_FC        1

#define DEVICE_I2C              1
#define DEVICE_I2CSLAVE         0

#define DEVICE_SPI              1
#define DEVICE_SPISLAVE         1

#define DEVICE_CAN              1

#define DEVICE_RTC              1

#define DEVICE_ETHERNET         0

#define DEVICE_PWMOUT           1

#define DEVICE_SEMIHOST         0
#define DEVICE_LOCALFILESYSTEM  0

#define DEVICE_SLEEP            0

#define DEVICE_DEBUG_AWARENESS  0

#define DEVICE_STDIO_MESSAGES   0

#define DEVICE_ERROR_RED        0

#include "objects.h"

#endif
