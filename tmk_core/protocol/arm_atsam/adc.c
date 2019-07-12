/*
Copyright 2019 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"

//Configuration in keyboard's config_adc.h
uint8_t adc_config[][ADC_SAMPLEN + 1] = {
    {   ADC_CONFIG_5V  },
    {   ADC_CONFIG_C1A5  },
    {   ADC_CONFIG_C1B5  },
    {   ADC_CONFIG_C2A5  },
    {   ADC_CONFIG_C2B5  },
    {   ADC_CONFIG_C1I },
    {   ADC_CONFIG_C2I }
};

#ifdef ADC_USBC_RP_DELTA_MAX
uint16_t adc_usbc_rp_nominal[ADC_USBC_RP_TYPES * ADC_USBC_CON_TYPES] = { ADC_USBC_RP_NOM };
#endif

uint16_t g_v_5v;
float g_v_5v_avg;

__attribute__ ((weak))
void ADC0_clock_init(void)
{
    DBGC(DC_ADC0_CLOCK_INIT_BEGIN);

    MCLK->APBDMASK.bit.ADC0_ = 1;                        //ADC0 Clock Enable

    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.GEN = GEN_OSC0;      //Select generator clock
    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.CHEN = 1;            //Enable peripheral clock

    DBGC(DC_ADC0_CLOCK_INIT_COMPLETE);
}

__attribute__ ((weak))
void ADC1_clock_init(void)
{
    DBGC(DC_ADC1_CLOCK_INIT_BEGIN);

    MCLK->APBDMASK.bit.ADC1_ = 1;                        //ADC1 Clock Enable

    GCLK->PCHCTRL[ADC1_GCLK_ID].bit.GEN = GEN_OSC0;      //Select generator clock
    GCLK->PCHCTRL[ADC1_GCLK_ID].bit.CHEN = 1;            //Enable peripheral clock

    DBGC(DC_ADC1_CLOCK_INIT_COMPLETE);
}

__attribute__ ((weak))
void ADC0_load_cal(void)
{
    ADC0->CALIB.bit.BIASCOMP = ((*(uint32_t *)ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
    ADC0->CALIB.bit.BIASR2R = ((*(uint32_t *)ADC0_FUSES_BIASR2R_ADDR) & ADC0_FUSES_BIASR2R_Msk) >> ADC0_FUSES_BIASR2R_Pos;
    ADC0->CALIB.bit.BIASREFBUF = ((*(uint32_t *)ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
}

__attribute__ ((weak))
void ADC1_load_cal(void)
{
    ADC1->CALIB.bit.BIASCOMP = ((*(uint32_t *)ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
    ADC1->CALIB.bit.BIASR2R = ((*(uint32_t *)ADC1_FUSES_BIASR2R_ADDR) & ADC1_FUSES_BIASR2R_Msk) >> ADC1_FUSES_BIASR2R_Pos;
    ADC1->CALIB.bit.BIASREFBUF = ((*(uint32_t *)ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
}

__attribute__ ((weak))
void ADC_init(void)
{
    uint8_t adc_configured[ADC_INST_NUM] = { 0 };
    uint8_t mcu_port;
    uint8_t mcu_pin;
    uint8_t mcu_mux;
    uint8_t adc_index;
    PortGroup *port;
    uint8_t adc_row;

    for (adc_row = 0; adc_row < sizeof(adc_config) / sizeof(adc_config[0]); adc_row++)
    {
        DBGC(DC_ADC_INIT_BEGIN);

        mcu_port = adc_config[adc_row][ADC_PORT];
        if (mcu_port == (uint8_t)ADC_NA)
        {
            continue;  //ADC not available
        }

        adc_index = adc_config[adc_row][ADC_INDEX];
        mcu_pin = adc_config[adc_row][ADC_PIN];
        mcu_mux = adc_config[adc_row][ADC_MUX];
        port = &PORT->Group[mcu_port];

        //Set up MCU pins
        port->DIRCLR.reg = 1 << mcu_pin; //PIN as input
        if (mcu_pin / 2 == 0)
        {
            port->PMUX[mcu_pin / 2].bit.PMUXE = mcu_mux; //Set MUX
        }
        else
        {
            port->PMUX[mcu_pin / 2].bit.PMUXO = mcu_mux; //Set MUX
        }
        port->PINCFG[mcu_pin].bit.PMUXEN = 1; //Enable MUX

        //Configure ADC if it has not been already
        if (adc_configured[adc_index] != 1)
        {
            ADC_configure(adc_index);
            adc_configured[adc_row] = 1;
        }

        DBGC(DC_ADC_INIT_COMPLETE);
    }
}

__attribute__ ((weak))
void ADC_configure(uint8_t adc_index)
{
    Adc *adc_insts[] = ADC_INSTS;
    Adc *adc = adc_insts[adc_index];

    //Reset the ADC
    adc->CTRLA.bit.SWRST = 1;
    while (adc->SYNCBUSY.bit.SWRST) { DBGC(DC_ADC_SWRST_SYNCING_1); }
    while (adc->CTRLA.bit.SWRST) { DBGC(DC_ADC_SWRST_SYNCING_2); }

    //Configure clock divide
    adc->CTRLA.bit.PRESCALER = ADC_CTRLA_PRESCALER_DIV2_Val;

    //Load factory calibration data
    if (adc_index == 0)
    {
        ADC0_load_cal();
        ADC0_clock_init();
    }
    else if (adc_index == 1)
    {
        ADC1_load_cal();
        ADC1_clock_init();
    }

    //Enable the ADC
    adc->CTRLA.bit.ENABLE = 1;
    while (adc->SYNCBUSY.bit.ENABLE) { DBGC(DC_ADC_ENABLE_SYNCING_1); }
}

//Return ADC_NA if the ADC is not available
//Return ADC counts otherwise
__attribute__ ((weak))
uint16_t adc_get(uint8_t adc_id)
{
    uint16_t result = 0;

    //Make sure ADC is available
    if (adc_config[adc_id][ADC_PORT] == (uint8_t)ADC_NA)
    {
        result = (uint16_t)ADC_NA;
    }
    else
    {
        Adc *adc_insts[] = ADC_INSTS;
        Adc *adc = adc_insts[adc_config[adc_id][ADC_INDEX]];

        adc->INPUTCTRL.bit.MUXPOS = adc_config[adc_id][ADC_MUXPOS];
        while (adc->SYNCBUSY.bit.INPUTCTRL) { DBGC(DC_ADC_GET_INPUTCTRL_SYNCING_1); }

        //Only switch reference if not already selected
        if (adc->REFCTRL.bit.REFSEL != adc_config[adc_id][ADC_REFSEL])
        {
            adc->REFCTRL.bit.REFSEL = adc_config[adc_id][ADC_REFSEL];
            while (adc->SYNCBUSY.bit.REFCTRL) { DBGC(DC_ADC_GET_REFCTRL_SYNCING_1); }
        }

        //Configure averaging
        if (adc->AVGCTRL.bit.SAMPLENUM != adc_config[adc_id][ADC_SAMPLENUM])
        {
            adc->AVGCTRL.bit.SAMPLENUM = adc_config[adc_id][ADC_SAMPLENUM];
            while (adc->SYNCBUSY.bit.AVGCTRL) { DBGC(DC_ADC_GET_AVGCTRL_SYNCING_1); }
            if      (adc->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_1_Val) adc->AVGCTRL.bit.ADJRES = 0;
            else if (adc->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_2_Val) adc->AVGCTRL.bit.ADJRES = 1;
            else if (adc->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_4_Val) adc->AVGCTRL.bit.ADJRES = 2;
            else if (adc->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_8_Val) adc->AVGCTRL.bit.ADJRES = 3;
            else                                                                adc->AVGCTRL.bit.ADJRES = 4;
            while (adc->SYNCBUSY.bit.AVGCTRL) { DBGC(DC_ADC_GET_AVGCTRL_SYNCING_2); }
        }

        //Configure settling
        if (adc->SAMPCTRL.bit.SAMPLEN != adc_config[adc_id][ADC_SAMPLEN])
        {
            adc->SAMPCTRL.bit.SAMPLEN = adc_config[adc_id][ADC_SAMPLEN];
            while (adc->SYNCBUSY.bit.SAMPCTRL) { DBGC(DC_ADC_GET_SAMPCTRL_SYNCING_1); }
        }

        adc->SWTRIG.bit.START = 1;
        while (adc->SYNCBUSY.bit.SWTRIG) { DBGC(DC_ADC_GET_SWTRIG_SYNCING_1); }
        while (!adc->INTFLAG.bit.RESRDY) { DBGC(DC_ADC_GET_INTFLAG_RESRDY_WAITING_1); }

        result = adc->RESULT.reg;

        //In the case of a 16-bit ADC, a maxed out reading becomes a return of "ADC not available", so take off one count
        if (result == (uint16_t)ADC_NA)
        {
            result--;
        }
    }

    return result;
}
