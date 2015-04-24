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
#include "analogout_api.h"
#include "clkman_regs.h"
#include "pwrman_regs.h"
#include "afe_regs.h"
#include "PeripheralPins.h"

//******************************************************************************
void analogout_init(dac_t *obj, PinName pin)
{
    // Make sure pin is an analog pin we can use for ADC
    DACName dac = (DACName)pinmap_peripheral(pin, PinMap_DAC);
    MBED_ASSERT((DACName)dac != (DACName)NC);

    // Set the object pointer
    obj->dac = ((mxc_dac_regs_t*)MXC_DAC_GET_DAC((pin & 0x3)));
    obj->dac_fifo = ((mxc_dac_fifo_t*)MXC_DAC_GET_FIFO((pin & 0x3)));
    obj->index = (pin & 0x3);

    // Set the ADC clock to the system clock frequency
    MXC_SET_FIELD(&MXC_CLKMAN->clk_ctrl, MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT,
        (MXC_F_CLKMAN_CLK_CTRL_ADC_GATE_N | (MXC_E_CLKMAN_ADC_SOURCE_SELECT_SYSTEM << 
        MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT_POS)));

    
    // Setup the OPAMP in follower mode
    switch(obj->index) {
        case 0:
            // Enable DAC clock
            MXC_CLKMAN->clk_ctrl_14_dac0 = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

            // Enable OPAMP
            MXC_AFE->ctrl5 &= ~MXC_F_AFE_CTRL5_OP_CMP0;

            // Set the positive and negative inputs
            MXC_SET_FIELD(&MXC_AFE->ctrl4, (MXC_F_AFE_CTRL4_DAC_SEL_A | 
                MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP0 | MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP0), 
                ((0x1 << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP0_POS) |
                (0x1 << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP0_POS) |
                (0x0 << MXC_F_AFE_CTRL4_DAC_SEL_A_POS)));

            // Enable N and P channel inputs
            MXC_AFE->ctrl3 |= (MXC_F_AFE_CTRL3_EN_PCH_OPAMP0 | 
                MXC_F_AFE_CTRL3_EN_NCH_OPAMP0);
        break;
        case 1:
            // Enable DAC clock
            MXC_CLKMAN->clk_ctrl_15_dac1 = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

            // Enable OPAMP
            MXC_AFE->ctrl5 &= ~MXC_F_AFE_CTRL5_OP_CMP1;

            // Set the positive and negative inputs
            MXC_SET_FIELD(&MXC_AFE->ctrl4, (MXC_F_AFE_CTRL4_DAC_SEL_B | 
                MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP1 | MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP1), 
                ((0x1 << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP1_POS) |
                (0x1 << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP1_POS) |
                (0x1 << MXC_F_AFE_CTRL4_DAC_SEL_B_POS)));

            // Enable N and P channel inputs
            MXC_AFE->ctrl3 |= (MXC_F_AFE_CTRL3_EN_PCH_OPAMP1 | 
                MXC_F_AFE_CTRL3_EN_NCH_OPAMP1);

        break;
        case 2:
            // Enable DAC clock
            MXC_CLKMAN->clk_ctrl_16_dac2 = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

            // Enable OPAMP
            MXC_AFE->ctrl5 &= ~MXC_F_AFE_CTRL5_OP_CMP2;

            // Set the positive and negative inputs
            MXC_SET_FIELD(&MXC_AFE->ctrl4, (MXC_F_AFE_CTRL4_DAC_SEL_C | 
                MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP2 | MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP2), 
                ((0x1 << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP2_POS) |
                (0x1 << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP2_POS) |
                (0x2 << MXC_F_AFE_CTRL4_DAC_SEL_C_POS)));

            // Enable N and P channel inputs
            MXC_AFE->ctrl3 |= (MXC_F_AFE_CTRL3_EN_PCH_OPAMP2 | 
                MXC_F_AFE_CTRL3_EN_NCH_OPAMP2);
        break;
        case 3:
            // Enable DAC clock
            MXC_CLKMAN->clk_ctrl_17_dac3 = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

            // Enable OPAMP
            MXC_AFE->ctrl5 &= ~MXC_F_AFE_CTRL5_OP_CMP3;

            // Set the positive and negative inputs
            MXC_SET_FIELD(&MXC_AFE->ctrl4, (MXC_F_AFE_CTRL4_DAC_SEL_D | 
                MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP3 | MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP3), 
                ((0x1 << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP3_POS) |
                (0x1 << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP3_POS) |
                (0x3 << MXC_F_AFE_CTRL4_DAC_SEL_D_POS)));

            // Enable N and P channel inputs
            MXC_AFE->ctrl3 |= (MXC_F_AFE_CTRL3_EN_PCH_OPAMP3 | 
                MXC_F_AFE_CTRL3_EN_NCH_OPAMP3);
        break;
    }

    // Enable AFE power
    MXC_PWRMAN->pwr_rst_ctrl |= MXC_F_PWRMAN_PWR_RST_CTRL_AFE_POWERED;

    // Setup internal voltage references
    MXC_SET_FIELD(&MXC_AFE->ctrl1, (MXC_F_AFE_CTRL1_REF_DAC_VOLT_SEL | MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL), 
        (MXC_F_AFE_CTRL1_REF_ADC_POWERUP | MXC_F_AFE_CTRL1_REF_BLK_POWERUP |
        (MXC_E_AFE_REF_VOLT_SEL_1500 << MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL_POS)));

    // Disable interpolation
    obj->dac->ctrl0 &= MXC_F_DAC_CTRL0_INTERP_MODE;
}

//******************************************************************************
void analogout_write(dac_t *obj, float value)
{
    analogout_write_u16(obj, (uint16_t)((value/1.0) * 0xFFFF));
}

//******************************************************************************
void analogout_write_u16(dac_t *obj, uint16_t value)
{
    // Enable the OPAMP
        // Setup the OPAMP in follower mode
    switch(obj->index) {
        case 0:
            MXC_AFE->ctrl3 |= MXC_F_AFE_CTRL3_POWERUP_OPAMP0;
        break;
        case 1:
            MXC_AFE->ctrl3 |= MXC_F_AFE_CTRL3_POWERUP_OPAMP1;
        break;
        case 2:
            MXC_AFE->ctrl3 |= MXC_F_AFE_CTRL3_POWERUP_OPAMP2;
        break;
        case 3:
            MXC_AFE->ctrl3 |= MXC_F_AFE_CTRL3_POWERUP_OPAMP3;
        break;
    }

    // Output 1 sample with minimal delay
    obj->dac->rate |= 0x1;

    // Set the start mode to output once data is in the FIFO
    obj->dac->ctrl0 &= ~(MXC_F_DAC_CTRL0_START_MODE | MXC_F_DAC_CTRL0_OP_MODE);

    // Enable the DAC
    obj->dac->ctrl0 |= (MXC_F_DAC_CTRL0_POWER_MODE_2 | 
        MXC_F_DAC_CTRL0_POWER_MODE_1_0 | MXC_F_DAC_CTRL0_POWER_ON | 
        MXC_F_DAC_CTRL0_CLOCK_GATE_EN | MXC_F_DAC_CTRL0_CPU_START);

    if(obj->index < 2) {
        obj->out = (value);
        obj->dac_fifo->output_16 = (obj->out);

    } else {
        // Convert 16 bits to 8 bits
        obj->out = (value >> 8);
        obj->dac_fifo->output_8 = (obj->out);
    }
}

//******************************************************************************
float analogout_read(dac_t *obj)
{
    return (((float)analogout_read_u16(obj) / (float)0xFFFF) * 1.5);
}

//******************************************************************************
uint16_t analogout_read_u16(dac_t *obj)
{
    if(obj->index < 2) {
        // Convert 12 bits to 16 bits
        return (obj->out << 4);
    } else {
        // Convert 8 bits to 16 bits
        return (obj->out << 8);
    }
}
