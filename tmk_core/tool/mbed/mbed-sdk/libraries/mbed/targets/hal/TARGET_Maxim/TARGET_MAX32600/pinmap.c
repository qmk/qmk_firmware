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
#include "pinmap.h"
#include "objects.h"
#include "gpio_regs.h"
#include "ioman_regs.h"

void pin_function(PinName name, int function)
{
    MBED_ASSERT(name != (PinName)NC);

    if ((function >= 0) && (function <= 0xF)) {
        unsigned int port = PINNAME_TO_PORT(name);
        unsigned int pin = PINNAME_TO_PIN(name);
        uint32_t temp = MXC_GPIO->func_sel[port] & ~(0xF << (pin*4));
        MXC_GPIO->func_sel[port] = temp | ((uint32_t)function << (pin*4));
    } else {
        /* Assume this is a pointer to a pin function object */
        pin_function_t *obj = (pin_function_t*)function;

        if ((*obj->reg_ack & obj->ack_mask) != obj->req_val) {
            /* Request pin mapping */
            *obj->reg_req |= obj->req_val;

            /* Check for acknowledgment */
            MBED_ASSERT((*obj->reg_ack & obj->ack_mask) == obj->req_val);
        }
    }
}

void pin_mode(PinName name, PinMode mode)
{
    MBED_ASSERT(name != (PinName)NC);
    unsigned int port = PINNAME_TO_PORT(name);
    unsigned int pin = PINNAME_TO_PIN(name);

    /* Must set mode while retaining direction */

    /* Get the current direction */
    uint32_t out_mode = MXC_GPIO->out_mode[port];
    uint32_t curr_mode = (out_mode >> (pin*4)) & 0xF;
    PinDirection dir = PIN_OUTPUT;
    if ((curr_mode == MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP) || (curr_mode == MXC_V_GPIO_OUT_MODE_HIGH_Z)) {
        dir = PIN_INPUT;
    }

    /* Set mode based on current direction */
    uint32_t new_mode;
    if (dir == PIN_OUTPUT) {
        // PullUp      = not valid,
        // OpenDrain   = MXC_V_GPIO_OUT_MODE_OD,
        // PullNone    = MXC_V_GPIO_OUT_MODE_NORMAL,
        if (mode == OpenDrain) {
            new_mode = MXC_V_GPIO_OUT_MODE_OPEN_DRAIN;
        } else {
            new_mode = MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE;
        }
    } else {
        // PullUp      = MXC_V_GPIO_OUT_MODE_HIZPU,
        // OpenDrain   = not valid,
        // PullNone    = MXC_V_GPIO_OUT_MODE_HIZ,
        if (mode == PullUp) {
            new_mode = MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP;
        } else {
            new_mode = MXC_V_GPIO_OUT_MODE_HIGH_Z;
        }
    }

    /* Set new mode */
    out_mode &= ~(0xF << (pin*4));
    out_mode |= (new_mode << (pin*4));
    MXC_GPIO->out_mode[port] = out_mode;
}
