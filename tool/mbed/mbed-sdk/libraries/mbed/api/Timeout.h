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
#ifndef MBED_TIMEOUT_H
#define MBED_TIMEOUT_H

#include "Ticker.h"

namespace mbed {

/** A Timeout is used to call a function at a point in the future
 *
 * You can use as many seperate Timeout objects as you require.
 *
 * Example:
 * @code
 * // Blink until timeout.
 *
 * #include "mbed.h"
 *
 * Timeout timeout;
 * DigitalOut led(LED1);
 *
 * int on = 1;
 *
 * void attimeout() {
 *     on = 0;
 * }
 *
 * int main() {
 *     timeout.attach(&attimeout, 5);
 *     while(on) {
 *         led = !led;
 *         wait(0.2);
 *     }
 * }
 * @endcode
 */
class Timeout : public Ticker {

protected:
    virtual void handler();
};

} // namespace mbed

#endif
