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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "sleep_api.h"
#include "cmsis.h"
#include "mbed_interface.h"

void sleep(void) {
    
    // SRC[SLEEPDEEP] set to 0 = sleep
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    
    // wait for interrupt
    __WFI();
}

/*
 *  ToDo: Implement deepsleep()
 */
void deepsleep(void) {
    sleep();
}
