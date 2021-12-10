/*
Copyright 2018 Massdrop Inc.

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

#ifndef _ARM_ATSAM_PROTOCOL_H_
#define _ARM_ATSAM_PROTOCOL_H_

#include "samd51j18a.h"

#include "timer.h"
#include "d51_util.h"
#include "clks.h"
#include "wait.h"
#include "adc.h"
#include "i2c_master.h"
#include "shift_register.h"

#include "./usb/usb_hub.h"

#ifndef MD_BOOTLOADER

#    include "main_arm_atsam.h"
#    ifdef RGB_MATRIX_ENABLE
#        include "md_rgb_matrix.h"
#        include "rgb_matrix.h"
#    endif
#    include "issi3733_driver.h"
#    include "./usb/compiler.h"
#    include "./usb/udc.h"
#    include "./usb/udi_cdc.h"

#endif  // MD_BOOTLOADER

#endif  //_ARM_ATSAM_PROTOCOL_H_
