/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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
#include "sleep_api.h"
#include "cmsis.h"

//Normal wait mode
void sleep(void)
{
    SMC->PMPROT = SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLP_MASK;

    //Normal sleep mode for ARM core:
    SCB->SCR = 0;
    __WFI();
}

//Very low-power stop mode
void deepsleep(void)
{
    //Check if ADC is enabled and HS mode is set, if yes disable it (lowers power consumption by 60uA)
    uint8_t ADC_HSC = 0;
    if (SIM->SCGC6 & SIM_SCGC6_ADC0_MASK) {
        if (ADC0->CFG2 & ADC_CFG2_ADHSC_MASK) {
            ADC_HSC = 1;
            ADC0->CFG2 &= ~(ADC_CFG2_ADHSC_MASK);
        }
    }
    
    //Check if PLL/FLL is enabled:
    uint32_t PLL_FLL_en = (MCG->C1 & MCG_C1_CLKS_MASK) == MCG_C1_CLKS(0);
    
    SMC->PMPROT = SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_ALLS_MASK | SMC_PMPROT_AVLP_MASK;
    SMC->PMCTRL = SMC_PMCTRL_STOPM(2);

    //Deep sleep for ARM core:
    SCB->SCR = 1<<SCB_SCR_SLEEPDEEP_Pos;

    __WFI();
    //Switch back to PLL as clock source if needed
    //The interrupt that woke up the device will run at reduced speed
    if (PLL_FLL_en) {
        
#if defined (TARGET_K20D50M)    
        if (MCG->C6 & (1<<MCG_C6_PLLS_SHIFT) != 0) /* If PLL */
            while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U); /* Wait until locked */
        MCG->C1 &= ~MCG_C1_CLKS_MASK;
#else    
        // MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 
        MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | MCG_C1_IRCLKEN_MASK;
        // MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0   
        MCG->C6 = MCG_C6_VDIV0(0);
        while((MCG->S & MCG_S_OSCINIT0_MASK) == 0u) { } // Check that the oscillator is running 
        while((MCG->S & 0x0Cu) != 0x08u) { }            // Wait until external reference clock is selected as MCG output 
        // MCG->C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=3
        MCG->C5 = MCG_C5_PRDIV0(5);
        // MCG->C6: LOLIE=0,PLLS=1,CME=0,VDIV0=3
        MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(3);
        while((MCG->S & 0x0Cu) != 0x08u) { }            // Wait until external reference clock is selected as MCG output         
        while((MCG->S & MCG_S_PLLST_MASK) == 0u) { }    // Wait until the source of the PLLS clock has switched to the PLL 
        while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { }    // Wait until locked
        // MCG->C1: CLKS=0,FRDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0
        MCG->C1 = MCG_C1_FRDIV(2) | MCG_C1_IRCLKEN_MASK;;
        while((MCG->S & 0x0Cu) != 0x0Cu) { }            // Wait until output of the PLL is selected
        while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { }    // Wait until locked             
#endif
    }
    
    if (ADC_HSC) {
        ADC0->CFG2 |= (ADC_CFG2_ADHSC_MASK);
    }
}
