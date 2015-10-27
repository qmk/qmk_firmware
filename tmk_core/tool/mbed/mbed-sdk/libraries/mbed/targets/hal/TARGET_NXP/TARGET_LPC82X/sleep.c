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


//#define DEEPSLEEP
#define POWERDOWN

void sleep(void)
{
    //Normal sleep mode for PCON:
    LPC_PMU->PCON &= ~0x03;

    //Normal sleep mode for ARM core:
    SCB->SCR = 0;

    //And go to sleep
    __WFI();
}

// Deepsleep/powerdown modes assume the device is configured to use its internal RC oscillator directly
 
void deepsleep(void)
{
    //Deep sleep in PCON
    LPC_PMU->PCON &= ~0x03;

#if defined(DEEPSLEEP)
    LPC_PMU->PCON |= 0x01;
#elif defined(POWERDOWN)
    LPC_PMU->PCON |= 0x02;
#endif

    //If brownout detection and WDT are enabled, keep them enabled during sleep
    LPC_SYSCON->PDSLEEPCFG = LPC_SYSCON->PDRUNCFG;

    //After wakeup same stuff as currently enabled:
    LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;

    //All interrupts may wake up:
    LPC_SYSCON->STARTERP0 = 0xFF;
    LPC_SYSCON->STARTERP1 = 0xFFFF;

    //Deep sleep for ARM core:
    SCB->SCR = 1<<2;

    __WFI();
}
