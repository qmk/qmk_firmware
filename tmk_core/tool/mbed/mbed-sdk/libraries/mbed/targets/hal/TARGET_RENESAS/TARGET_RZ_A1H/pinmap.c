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
#include "pinmap.h"
#include "mbed_error.h"
#include "gpio_addrdefine.h"

PinName gpio_multi_guard = (PinName)NC; /* If set pin name here, setting of the "pin" is just one time */

void pin_function(PinName pin, int function) {
    if (pin == (PinName)NC) return;
    
    int n = pin >> 4;
    int bitmask = 1<<(pin  & 0xf);
    
    if (gpio_multi_guard != pin) {
        if (function == 0) {
            // means GPIO mode
            *PMC(n) &= ~bitmask;
        } else {
            // alt-function mode
            --function;

            if (function & (1 << 2)) { *PFCAE(n) |= bitmask;}else  { *PFCAE(n) &= ~bitmask;}
            if (function & (1 << 1)) { *PFCE(n) |= bitmask;}else  { *PFCE(n) &= ~bitmask;}
            if (function & (1 << 0)) { *PFC(n) |= bitmask;}else  { *PFC(n) &= ~bitmask;}
            *PIPC(n) |= bitmask;

            if (P1_0 <= pin && pin <= P1_7 && function == 0) {
                *PBDC(n) |= bitmask;
            }
            *PMC(n) |= bitmask;
        }
    } else {
        gpio_multi_guard = (PinName)NC;
    }
}

void pin_mode(PinName pin, PinMode mode) {
//    if (pin == (PinName)NC) { return; }
}
