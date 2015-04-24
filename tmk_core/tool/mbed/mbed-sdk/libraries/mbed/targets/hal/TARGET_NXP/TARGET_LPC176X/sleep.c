/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#include "sleep_api.h"
#include "cmsis.h"
#include "mbed_interface.h"

void sleep(void) {

#if (DEVICE_SEMIHOST == 1)
    // ensure debug is disconnected
    mbed_interface_disconnect();
#endif

    // PCON[PD] set to sleep
    LPC_SC->PCON = 0x0;
    
    // SRC[SLEEPDEEP] set to 0 = sleep
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    
    // wait for interrupt
    __WFI();
}

/*
* The mbed lpc1768 does not support the deepsleep mode
* as a debugger is connected to it (the mbed interface).
*
* As mentionned in an application note from NXP:
*
*       http://www.po-star.com/public/uploads/20120319123122_141.pdf
*
*       {{{
*       The user should be aware of certain limitations during debugging.
*       The most important is that, due to limitations of the Cortex-M3
*       integration, the LPC17xx cannot wake up in the usual manner from
*       Deep Sleep and Power-down modes. It is recommended not to use these
*       modes during debug. Once an application is downloaded via JTAG/SWD
*       interface, the USB to SWD/JTAG debug adapter (Keil ULINK2 for example)
*       should be removed from the target board, and thereafter, power cycle
*       the LPC17xx to allow wake-up from deep sleep and power-down modes
*       }}}
*
*       As the interface firmware does not reset the target when a
*       mbed_interface_disconnect() semihosting call is made, the
*       core cannot wake-up from deepsleep.
*
*       We treat a deepsleep() as a normal sleep().
*/

void deepsleep(void) {

#if (DEVICE_SEMIHOST == 1)
    // ensure debug is disconnected
    mbed_interface_disconnect();
#endif
    
    // PCON[PD] set to deepsleep
    sleep();
}
