/* Copyright 2022~2024 @ lokher (https://www.keychron.com)
 * Adapted from  keymagichorse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef RUN_MODE_PROCESS_TIME
#    define RUN_MODE_PROCESS_TIME 10000
#endif

#ifndef USB_POWER_SENSE_PIN                         // usb insert detection 
#    define USB_POWER_SENSE_PIN     A10
#endif
#ifndef USB_POWER_CONNECTED_LEVEL                   // active level
#    define USB_POWER_CONNECTED_LEVEL 1    
#endif

#ifndef BHQ_MCU_WAKEUP_PIN                          // QMK_MCU wake up BHQ_MCU
#    define BHQ_MCU_WAKEUP_PIN          A1
#endif
#ifndef BHQ_MCU_WAKEUP_LEVEL           
#    define BHQ_MCU_WAKEUP_LEVEL        0    
#endif

#ifndef QMK_MCU_WAKEUP_PIN                          // BHQ_MCU wake up QMK_MCU
#    define QMK_MCU_WAKEUP_PIN          A0
#endif
#ifndef QMK_MCU_WAKEUP_LEVEL           
#    define QMK_MCU_WAKEUP_LEVEL        0    
#endif


void lpm_init(void);
void lpm_device_power_open(void);
void lpm_device_power_close(void);

void lpm_timer_reset(void);
void lpm_task(void);