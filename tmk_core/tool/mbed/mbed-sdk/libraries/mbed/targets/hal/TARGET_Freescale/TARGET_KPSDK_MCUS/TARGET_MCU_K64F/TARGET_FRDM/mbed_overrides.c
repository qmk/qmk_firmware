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
#include "gpio_api.h"

// called before main - implement here if board needs it ortherwise, let
//  the application override this if necessary
//void mbed_sdk_init()
//{
//
//}

// Change the NMI pin to an input. This allows NMI pin to 
//  be used as a low power mode wakeup.  The application will
//  need to change the pin back to NMI_b or wakeup only occurs once!
void NMI_Handler(void)
{
    gpio_t gpio;
    gpio_init_in(&gpio, PTA4);
}

// Provide ethernet devices with a semi-unique MAC address from the UUID
void mbed_mac_address(char *mac)
{
    // Fetch word 0
    uint32_t word0 = *(uint32_t *)0x40048060;
    // Fetch word 1
    // we only want bottom 16 bits of word1 (MAC bits 32-47)
    // and bit 1 forced to 1, bit 0 forced to 0
    // Locally administered MAC, reduced conflicts
    // http://en.wikipedia.org/wiki/MAC_address
    uint32_t word1 = *(uint32_t *)0x4004805C;
    word1 |= 0x00000002;
    word1 &= 0x0000FFFE;
    
    mac[0] = (word1 & 0x000000ff);
    mac[1] = (word1 & 0x0000ff00) >> 8;
    mac[2] = (word0 & 0xff000000) >> 24;
    mac[3] = (word0 & 0x00ff0000) >> 16;
    mac[4] = (word0 & 0x0000ff00) >> 8;
    mac[5] = (word0 & 0x000000ff);
}
