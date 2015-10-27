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

#if DEVICE_SLEEP

void sleep(void) {

#if (DEVICE_SEMIHOST == 1)
    // ensure debug is disconnected
    mbed_interface_disconnect();
#endif

    // PCON[PM] (bits 2:0) set to 0
    LPC_PMU->PCON &= ~0x03;

    // SRC[SLEEPDEEP] set to 0 = sleep
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    // wait for interrupt
    __WFI();
}


void deepsleep(void) {

#if (DEVICE_SEMIHOST == 1)
    // ensure debug is disconnected
    mbed_interface_disconnect();
#endif

  // PCON[PM] (bits 2:0) set to 1
  LPC_PMU->PCON &= ~0x03;
  LPC_PMU->PCON |= 0x01;

  //According to user manual it is kinda picky about reserved bits, so we follow that nicely
  //Keep WDOSC and BOD in same state as they are now during deepsleep
  LPC_SYSCON->PDSLEEPCFG = 0x00000037 | (LPC_SYSCON->PDRUNCFG & (0x00000048));

  // Power up same as before powerdown
  LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;

  // All interrupts can wake
  LPC_SYSCON->STARTERP0 = 0xFF;
  LPC_SYSCON->STARTERP1 = 0xFFFFFFFF;

  // SRC[SLEEPDEEP] set to 1 = deep sleep
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  // wait for interrupt
  __WFI();
}

#endif
