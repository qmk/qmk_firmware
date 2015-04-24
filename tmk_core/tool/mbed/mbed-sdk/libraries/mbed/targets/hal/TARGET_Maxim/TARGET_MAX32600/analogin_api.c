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
#include "analogin_api.h"
#include "clkman_regs.h"
#include "pwrman_regs.h"
#include "afe_regs.h"
#include "PeripheralPins.h"

#define PGA_TRK_CNT     0x1F
#define ADC_ACT_CNT     0x1
#define ADC_PGA_CNT     0x1
#define ADC_ACQ_CNT     0x1
#define ADC_SLP_CNT     0x1
 
//******************************************************************************
void analogin_init(analogin_t *obj, PinName pin)
{
    // Make sure pin is an analog pin we can use for ADC
    MBED_ASSERT((ADCName)pinmap_peripheral(pin, PinMap_ADC) != (ADCName)NC);

    // Set the object pointer
    obj->adc = MXC_ADC;
    obj->adccfg = MXC_ADCCFG;
    obj->adc_fifo = MXC_ADC_FIFO;
    obj->adc_pin = pin;

    // Set the ADC clock to the system clock frequency
    MXC_SET_FIELD(&MXC_CLKMAN->clk_ctrl, MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT,
        (MXC_F_CLKMAN_CLK_CTRL_ADC_GATE_N | (MXC_E_CLKMAN_ADC_SOURCE_SELECT_SYSTEM << 
        MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT_POS)));

    // Enable AFE power
    MXC_PWRMAN->pwr_rst_ctrl |= MXC_F_PWRMAN_PWR_RST_CTRL_AFE_POWERED;

    // Setup and hold window
    MXC_SET_FIELD(&obj->adc->tg_ctrl0, MXC_F_ADC_TG_CTRL0_PGA_TRK_CNT, PGA_TRK_CNT);

    // Setup sampling count and timing
    MXC_SET_FIELD(&obj->adc->tg_ctrl1, (MXC_F_ADC_TG_CTRL1_PGA_ACQ_CNT | 
        MXC_F_ADC_TG_CTRL1_ADC_ACQ_CNT | MXC_F_ADC_TG_CTRL1_ADC_SLP_CNT),
        ((ADC_PGA_CNT << MXC_F_ADC_TG_CTRL1_PGA_ACQ_CNT_POS) | 
        (ADC_ACQ_CNT << MXC_F_ADC_TG_CTRL1_ADC_ACQ_CNT_POS) |
        (ADC_SLP_CNT << MXC_F_ADC_TG_CTRL1_ADC_SLP_CNT_POS) |
        (MXC_F_ADC_TG_CTRL1_ADC_BRST_CNT)));
}

//******************************************************************************
float analogin_read(analogin_t *obj)
{
    // Convert integer to float
    return (((float)analogin_read_u16(obj)/(float)0xFFFF));
}

//******************************************************************************
uint16_t analogin_read_u16(analogin_t *obj)
{
    // Set the pin to take readings from
    unsigned mux_pos;
    unsigned diff = 0;
    if(obj->adc_pin >> PORT_SHIFT == 0xB) {
        mux_pos = (obj->adc_pin & 0xF) + 8;
    } else {
        mux_pos = (obj->adc_pin & 0xF);
    }

    if(obj->adc_pin >> PORT_SHIFT == 0xC) {
        diff = 1;
        mux_pos = (obj->adc_pin & 0xF) + 8;
    }

    // Reset the ADC
    obj->adc->ctrl0 |= MXC_F_ADC_CTRL0_CPU_ADC_RST;

    // Enable the ADC
    obj->adc->ctrl0 |= MXC_F_ADC_CTRL0_CPU_ADC_EN;

    // Setup the ADC clock
    MXC_SET_FIELD(&obj->adc->ctrl0, (MXC_F_ADC_CTRL0_ADC_MODE | MXC_F_ADC_CTRL0_AVG_MODE |
        MXC_F_ADC_CTRL0_ADC_CLK_MODE | MXC_F_ADC_CTRL0_ADC_BI_POL),
        ((MXC_E_ADC_MODE_SMPLCNT_FULL_RATE << MXC_F_ADC_CTRL0_ADC_MODE_POS) | 
        (MXC_E_ADC_AVG_MODE_FILTER_OUTPUT << MXC_F_ADC_CTRL0_AVG_MODE_POS) |
        (0x2 << MXC_F_ADC_CTRL0_ADC_CLK_MODE_POS) |
        MXC_F_ADC_CTRL0_ADC_CLK_EN));

    // Setup the input multiplexor
    MXC_SET_FIELD(&obj->adc->pga_ctrl, (MXC_F_ADC_PGA_CTRL_MUX_CH_SEL | 
        MXC_F_ADC_PGA_CTRL_MUX_DIFF | MXC_F_ADC_PGA_CTRL_PGA_GAIN),
        ((mux_pos << MXC_F_ADC_PGA_CTRL_MUX_CH_SEL_POS) |
        (diff << MXC_F_ADC_PGA_CTRL_MUX_DIFF_POS)));

    // Setup voltage reference
    MXC_SET_FIELD(&MXC_AFE->ctrl1, MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL, 
        (MXC_F_AFE_CTRL1_REF_ADC_POWERUP | MXC_F_AFE_CTRL1_REF_BLK_POWERUP |
        (MXC_E_AFE_REF_VOLT_SEL_1500 << MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL_POS)));

    // Clear the done bit
    obj->adc->intr = MXC_F_ADC_INTR_DONE_IF;

    // Take one sample
    obj->adc->tg_ctrl0 |= (1 << MXC_F_ADC_TG_CTRL0_ADC_SMPL_CNT_POS);

    // Set the start bit to take the sample
    obj->adc->ctrl0 |= MXC_F_ADC_CTRL0_CPU_ADC_START;

    // Wait for the conversion to complete
    while(!(obj->adc->intr & MXC_F_ADC_INTR_DONE_IF)) {}

    // Get sample from the fifo
    uint16_t sample = (uint16_t)(obj->adc->out & 0xFFFF);
    
    // Disable ADC
    obj->adc->ctrl0 &= ~MXC_F_ADC_CTRL0_CPU_ADC_EN;

    return (sample - 1);
}
