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
#ifndef MBED_PWMOUT_H
#define MBED_PWMOUT_H

#include "platform.h"

#if DEVICE_PWMOUT
#include "pwmout_api.h"

namespace mbed {

/** A pulse-width modulation digital output
 *
 * Example
 * @code
 * // Fade a led on.
 * #include "mbed.h"
 *
 * PwmOut led(LED1);
 *
 * int main() {
 *     while(1) {
 *         led = led + 0.01;
 *         wait(0.2);
 *         if(led == 1.0) {
 *             led = 0;
 *         }
 *     }
 * }
 * @endcode
 *
 * @note
 *  On the LPC1768 and LPC2368, the PWMs all share the same
 *  period - if you change the period for one, you change it for all.
 *  Although routines that change the period maintain the duty cycle
 *  for its PWM, all other PWMs will require their duty cycle to be
 *  refreshed.
 */
class PwmOut {

public:

    /** Create a PwmOut connected to the specified pin
     *
     *  @param pin PwmOut pin to connect to
     */
    PwmOut(PinName pin) {
        pwmout_init(&_pwm, pin);
    }

    /** Set the ouput duty-cycle, specified as a percentage (float)
     *
     *  @param value A floating-point value representing the output duty-cycle,
     *    specified as a percentage. The value should lie between
     *    0.0f (representing on 0%) and 1.0f (representing on 100%).
     *    Values outside this range will be saturated to 0.0f or 1.0f.
     */
    void write(float value) {
        pwmout_write(&_pwm, value);
    }

    /** Return the current output duty-cycle setting, measured as a percentage (float)
     *
     *  @returns
     *    A floating-point value representing the current duty-cycle being output on the pin,
     *    measured as a percentage. The returned value will lie between
     *    0.0f (representing on 0%) and 1.0f (representing on 100%).
     *
     *  @note
     *  This value may not match exactly the value set by a previous <write>.
     */
    float read() {
        return pwmout_read(&_pwm);
    }

    /** Set the PWM period, specified in seconds (float), keeping the duty cycle the same.
     *
     *  @note
     *   The resolution is currently in microseconds; periods smaller than this
     *   will be set to zero.
     */
    void period(float seconds) {
        pwmout_period(&_pwm, seconds);
    }

    /** Set the PWM period, specified in milli-seconds (int), keeping the duty cycle the same.
     */
    void period_ms(int ms) {
        pwmout_period_ms(&_pwm, ms);
    }

    /** Set the PWM period, specified in micro-seconds (int), keeping the duty cycle the same.
     */
    void period_us(int us) {
        pwmout_period_us(&_pwm, us);
    }

    /** Set the PWM pulsewidth, specified in seconds (float), keeping the period the same.
     */
    void pulsewidth(float seconds) {
        pwmout_pulsewidth(&_pwm, seconds);
    }

    /** Set the PWM pulsewidth, specified in milli-seconds (int), keeping the period the same.
     */
    void pulsewidth_ms(int ms) {
        pwmout_pulsewidth_ms(&_pwm, ms);
    }

    /** Set the PWM pulsewidth, specified in micro-seconds (int), keeping the period the same.
     */
    void pulsewidth_us(int us) {
        pwmout_pulsewidth_us(&_pwm, us);
    }

#ifdef MBED_OPERATORS
    /** A operator shorthand for write()
     */
    PwmOut& operator= (float value) {
        write(value);
        return *this;
    }

    PwmOut& operator= (PwmOut& rhs) {
        write(rhs.read());
        return *this;
    }

    /** An operator shorthand for read()
     */
    operator float() {
        return read();
    }
#endif

protected:
    pwmout_t _pwm;
};

} // namespace mbed

#endif

#endif
