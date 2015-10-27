/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#include "mbed_assert.h"
#include "cmsis.h"
#include "pwmout_api.h"
#include "pinmap.h"
#include "ioman_regs.h"
#include "clkman_regs.h"
#include "PeripheralPins.h"

//******************************************************************************
void pwmout_init(pwmout_t* obj, PinName pin)
{
    // Make sure the pin is free for GPIO use
    unsigned int port = (unsigned int)pin >> PORT_SHIFT;
    unsigned int port_pin = (unsigned int)pin & ~(0xFFFFFFFF << PORT_SHIFT);
    MBED_ASSERT(MXC_GPIO->free[port] & (0x1 << port_pin));

    int i = 0;
    PinMap pwm = PinMap_PWM[0];

    // Check if there is a pulse train already active on this port
    int pin_func = (MXC_GPIO->func_sel[port] & (0xF << (port_pin*4))) >> (port_pin*4);
    if((pin_func > 0) && (pin_func < 4)) {
        // Search through PinMap_PWM to find the active PT
        while(pwm.pin != (PinName)NC) {
            if((pwm.pin == pin) && (pwm.function == pin_func)) {
                break;
            }
            pwm = PinMap_PWM[++i];
        }

    } else {
       // Search through PinMap_PWM to find an available PT
        int i = 0;
        while(pwm.pin != (PinName)NC && (i > -1)) {
            pwm = PinMap_PWM[i++];
            if(pwm.pin == pin) {
                // Check each instance of PT
                while(1) {
                    // Check to see if this PT instance is already in use
                    if((((mxc_pt_regs_t*)pwm.peripheral)->rate_length & 
                        MXC_F_PT_RATE_LENGTH_MODE)) {
                        i = -1;
                        break;
                    } 

                    // If all instances are in use, overwrite the last 
                    pwm = PinMap_PWM[++i];
                    if(pwm.pin != pin) {
                        pwm = PinMap_PWM[--i];
                        i = -1; 
                        break;
                    }

                }
            }
        } 
    }

    // Make sure we found an available PWM generator
    MBED_ASSERT(pwm.pin != (PinName)NC);

    // Disable all pwm output
    MXC_PTG->ctrl = 0;

    // Enable the clock
    MXC_CLKMAN->clk_ctrl_2_pt = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

    // Set the drive mode to normal
    MXC_SET_FIELD(&MXC_GPIO->out_mode[port], (0x7 << (port_pin*4)), (MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE << (port_pin*4)));

    // Set the obj pointer to the propper PWM instance
    obj->pwm = (mxc_pt_regs_t*)pwm.peripheral;

    // Initialize object period and pulse width
    obj->period = -1; 
    obj->pulse_width = -1;

    // Disable the output
    obj->pwm->train = 0x0;
    obj->pwm->rate_length = 0x0;

    // Configure the pin
    pin_mode(pin, (PinMode)PullNone);
    pin_function(pin, pwm.function);

    // default to 20ms: standard for servos, and fine for e.g. brightness control
    pwmout_period_us(obj, 20000);
    pwmout_write    (obj, 0);

    // Enable the global pwm
    MXC_PTG->ctrl = MXC_F_PT_CTRL_ENABLE_ALL;
}

//******************************************************************************
void pwmout_free(pwmout_t* obj)
{
    // Set the registers to the reset value
    obj->pwm->train = 0;
    obj->pwm->rate_length = 0x08000000;
}

//******************************************************************************
static void pwmout_update(pwmout_t* obj)
{
    // Calculate and set the divider ratio
    int div = (obj->period * (SystemCoreClock/1000000))/32;
    if (div < 2){
        div = 2;
    }
    MXC_SET_FIELD(&obj->pwm->rate_length, MXC_F_PT_RATE_LENGTH_RATE_CONTROL, div);

    // Change the duty cycle to adjust the pulse width
    obj->pwm->train = (0xFFFFFFFF << (32-((32*obj->pulse_width)/obj->period)));
}


//******************************************************************************
void pwmout_write(pwmout_t* obj, float percent)
{
    // Saturate percent if outside of range
    if(percent < 0.0) {
        percent = 0.0;
    } else if(percent > 1.0) {
        percent = 1.0;
    }

    // Resize the pulse width to set the duty cycle
    pwmout_pulsewidth_us(obj, (int)(percent*obj->period));
}

//******************************************************************************
float pwmout_read(pwmout_t* obj)
{
    // Check for when pulsewidth or period equals 0
    if((obj->pulse_width == 0) || (obj->period == 0)){
        return 0;
    }

    // Return the duty cycle
    return ((float)obj->pulse_width / (float)obj->period);
}

//******************************************************************************
void pwmout_period(pwmout_t* obj, float seconds)
{
    pwmout_period_us(obj, (int)(seconds * 1000000.0));
}

//******************************************************************************
void pwmout_period_ms(pwmout_t* obj, int ms)
{
    pwmout_period_us(obj, ms*1000);
}

//******************************************************************************
void pwmout_period_us(pwmout_t* obj, int us)
{
    // Check the range of the period
    MBED_ASSERT((us >= 0) && (us <= (int)(SystemCoreClock/32)));

    // Set pulse width to half the period if uninitialized
    if(obj->pulse_width == -1){
        obj->pulse_width = us/2;
    }

    // Save the period
    obj->period = us;

    // Update the registers
    pwmout_update(obj);
}

//******************************************************************************
void pwmout_pulsewidth(pwmout_t* obj, float seconds)
{
    pwmout_pulsewidth_us(obj, (int)(seconds * 1000000.0));
}

//******************************************************************************
void pwmout_pulsewidth_ms(pwmout_t* obj, int ms)
{
    pwmout_pulsewidth_us(obj, ms*1000);
}

//******************************************************************************
void pwmout_pulsewidth_us(pwmout_t* obj, int us)
{
    // Check the range of the pulsewidth
    MBED_ASSERT((us >= 0) && (us <= (int)(SystemCoreClock/32)));

    // Initialize period to double the pulsewidth if uninitialized
    if(obj->period == -1){
        obj->period = 2*us;
    }

    // Save the pulsewidth
    obj->pulse_width = us;

    // Update the register
    pwmout_update(obj);
}
