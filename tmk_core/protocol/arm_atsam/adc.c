/*
Copyright 2018 Massdrop Inc.

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

uint16_t v_5v;
uint16_t v_5v_avg;
uint16_t v_con_1;
uint16_t v_con_2;
uint16_t v_con_1_boot;
uint16_t v_con_2_boot;

void ADC0_clock_init(void)
{
    DBGC(DC_ADC0_CLOCK_INIT_BEGIN);

    MCLK->APBDMASK.bit.ADC0_ = 1;                        //ADC0 Clock Enable

    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.GEN = GEN_OSC0;      //Select generator clock
    GCLK->PCHCTRL[ADC0_GCLK_ID].bit.CHEN = 1;            //Enable peripheral clock

    DBGC(DC_ADC0_CLOCK_INIT_COMPLETE);
}

void ADC0_init(void)
{
    DBGC(DC_ADC0_INIT_BEGIN);

    //MCU
    PORT->Group[1].DIRCLR.reg = 1 << 0;                   //PB00 as input 5V
    PORT->Group[1].DIRCLR.reg = 1 << 1;                   //PB01 as input CON2
    PORT->Group[1].DIRCLR.reg = 1 << 2;                   //PB02 as input CON1
    PORT->Group[1].PMUX[0].bit.PMUXE = 1;                 //PB00 mux select B ADC 5V
    PORT->Group[1].PMUX[0].bit.PMUXO = 1;                 //PB01 mux select B ADC CON2
    PORT->Group[1].PMUX[1].bit.PMUXE = 1;                 //PB02 mux select B ADC CON1
    PORT->Group[1].PINCFG[0].bit.PMUXEN = 1;              //PB01 mux ADC Enable 5V
    PORT->Group[1].PINCFG[1].bit.PMUXEN = 1;              //PB01 mux ADC Enable CON2
    PORT->Group[1].PINCFG[2].bit.PMUXEN = 1;              //PB02 mux ADC Enable CON1

    //ADC
    ADC0->CTRLA.bit.SWRST = 1;
    while (ADC0->SYNCBUSY.bit.SWRST) { DBGC(DC_ADC0_SWRST_SYNCING_1); }
    while (ADC0->CTRLA.bit.SWRST) { DBGC(DC_ADC0_SWRST_SYNCING_2); }

    //Clock divide
    ADC0->CTRLA.bit.PRESCALER = ADC_CTRLA_PRESCALER_DIV2_Val;

    //Averaging
    ADC0->AVGCTRL.bit.SAMPLENUM = ADC_AVGCTRL_SAMPLENUM_4_Val;
    while (ADC0->SYNCBUSY.bit.AVGCTRL) { DBGC(DC_ADC0_AVGCTRL_SYNCING_1); }
    if      (ADC0->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_1_Val) ADC0->AVGCTRL.bit.ADJRES = 0;
    else if (ADC0->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_2_Val) ADC0->AVGCTRL.bit.ADJRES = 1;
    else if (ADC0->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_4_Val) ADC0->AVGCTRL.bit.ADJRES = 2;
    else if (ADC0->AVGCTRL.bit.SAMPLENUM == ADC_AVGCTRL_SAMPLENUM_8_Val) ADC0->AVGCTRL.bit.ADJRES = 3;
    else                                                                 ADC0->AVGCTRL.bit.ADJRES = 4;
    while (ADC0->SYNCBUSY.bit.AVGCTRL) { DBGC(DC_ADC0_AVGCTRL_SYNCING_2); }

    //Settling
    ADC0->SAMPCTRL.bit.SAMPLEN = 45;      //Sampling Time Length: 1-63, 1 ADC CLK per
    while (ADC0->SYNCBUSY.bit.SAMPCTRL) { DBGC(DC_ADC0_SAMPCTRL_SYNCING_1); }

    //Load factory calibration data
    ADC0->CALIB.bit.BIASCOMP = ((*(uint32_t *)ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
    ADC0->CALIB.bit.BIASR2R = ((*(uint32_t *)ADC0_FUSES_BIASR2R_ADDR) & ADC0_FUSES_BIASR2R_Msk) >> ADC0_FUSES_BIASR2R_Pos;
    ADC0->CALIB.bit.BIASREFBUF = ((*(uint32_t *)ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;

    //Enable
    ADC0->CTRLA.bit.ENABLE = 1;
    while (ADC0->SYNCBUSY.bit.ENABLE) { DBGC(DC_ADC0_ENABLE_SYNCING_1); }

    DBGC(DC_ADC0_INIT_COMPLETE);
}

uint16_t adc_get(uint8_t muxpos)
{
    ADC0->INPUTCTRL.bit.MUXPOS = muxpos;
    while (ADC0->SYNCBUSY.bit.INPUTCTRL) {}

    ADC0->SWTRIG.bit.START = 1;
    while (ADC0->SYNCBUSY.bit.SWTRIG) {}
    while (!ADC0->INTFLAG.bit.RESRDY) {}

    return ADC0->RESULT.reg;
}

