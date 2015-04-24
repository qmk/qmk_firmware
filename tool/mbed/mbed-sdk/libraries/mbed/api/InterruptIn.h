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
#ifndef MBED_INTERRUPTIN_H
#define MBED_INTERRUPTIN_H

#include "platform.h"

#if DEVICE_INTERRUPTIN

#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "FunctionPointer.h"

namespace mbed {

/** A digital interrupt input, used to call a function on a rising or falling edge
 *
 * Example:
 * @code
 * // Flash an LED while waiting for events
 *
 * #include "mbed.h"
 *
 * InterruptIn event(p16);
 * DigitalOut led(LED1);
 *
 * void trigger() {
 *     printf("triggered!\n");
 * }
 *
 * int main() {
 *     event.rise(&trigger);
 *     while(1) {
 *         led = !led;
 *         wait(0.25);
 *     }
 * }
 * @endcode
 */
class InterruptIn {

public:

    /** Create an InterruptIn connected to the specified pin
     *
     *  @param pin InterruptIn pin to connect to
     *  @param name (optional) A string to identify the object
     */
    InterruptIn(PinName pin);
    virtual ~InterruptIn();

     int read();
#ifdef MBED_OPERATORS
    operator int();

#endif

    /** Attach a function to call when a rising edge occurs on the input
     *
     *  @param fptr A pointer to a void function, or 0 to set as none
     */
    void rise(void (*fptr)(void));

    /** Attach a member function to call when a rising edge occurs on the input
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    void rise(T* tptr, void (T::*mptr)(void)) {
        _rise.attach(tptr, mptr);
        gpio_irq_set(&gpio_irq, IRQ_RISE, 1);
    }

    /** Attach a function to call when a falling edge occurs on the input
     *
     *  @param fptr A pointer to a void function, or 0 to set as none
     */
    void fall(void (*fptr)(void));

    /** Attach a member function to call when a falling edge occurs on the input
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    void fall(T* tptr, void (T::*mptr)(void)) {
        _fall.attach(tptr, mptr);
        gpio_irq_set(&gpio_irq, IRQ_FALL, 1);
    }

    /** Set the input pin mode
     *
     *  @param mode PullUp, PullDown, PullNone
     */
    void mode(PinMode pull);

    /** Enable IRQ. This method depends on hw implementation, might enable one
     *  port interrupts. For further information, check gpio_irq_enable().
     */
    void enable_irq();

    /** Disable IRQ. This method depends on hw implementation, might disable one
     *  port interrupts. For further information, check gpio_irq_disable().
     */
    void disable_irq();

    static void _irq_handler(uint32_t id, gpio_irq_event event);

protected:
    gpio_t gpio;
    gpio_irq_t gpio_irq;

    FunctionPointer _rise;
    FunctionPointer _fall;
};

} // namespace mbed

#endif

#endif
