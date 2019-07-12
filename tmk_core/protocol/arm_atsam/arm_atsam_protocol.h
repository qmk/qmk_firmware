/*
Copyright 2019 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "samd51j18a.h"

#ifdef MD_BOOTLOADER

#include <stdlib.h> //For abs()
#include "config.h" //From keyboard's directory

#endif

#include "md_bootloader.h"
#include "d51_util.h"

#include "quantum.h"
#include "timer.h"
#include "wait.h"

#include "clks.h"
#include "adc.h"
#include "i2c_master.h"
#include "spi.h"
#include "power.h"

#include "./usb/usb2422.h"

#ifndef MD_BOOTLOADER

#include "main_arm_atsam.h"
#ifdef RGB_MATRIX_ENABLE
#include "led_matrix.h"
#include "rgb_matrix.h"
#endif
#include "issi3733_driver.h"
#include "./usb/compiler.h"
#include "./usb/udc.h"
#include "./usb/udi_cdc.h"

#endif //MD_BOOTLOADER
