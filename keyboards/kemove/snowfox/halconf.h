/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * Use default settings in templates/halconf.h
 */

#pragma once

#define HAL_USE_PAL                         TRUE
#define HAL_USE_SPI                         TRUE
#define HAL_USE_SERIAL                      TRUE
#define HAL_USE_USB                         TRUE

#define SERIAL_DEFAULT_BITRATE              9600
#define SERIAL_BUFFERS_SIZE                   32

#define SERIAL_USB_BUFFERS_SIZE              256
#define USB_USE_WAIT                        TRUE

#define SPI_USE_WAIT                        TRUE
#define SPI_USE_MUTUAL_EXCLUSION            TRUE

#include_next <halconf.h>

