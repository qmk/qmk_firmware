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
#ifndef MBED_CLK_FREQS_H
#define MBED_CLK_FREQS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "PeripheralPins.h"

//Get the peripheral bus clock frequency
static inline uint32_t bus_frequency(void) {
    return (SystemCoreClock / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1));
}

#if defined(TARGET_KL43Z)

static inline uint32_t extosc_frequency(void) {
    return CPU_XTAL_CLK_HZ;
}

static inline uint32_t fastirc_frequency(void) {
    return CPU_INT_FAST_CLK_HZ;
}

static inline uint32_t mcgirc_frequency(void) {
    uint32_t mcgirc_clock = 0;

    if (MCG->C1 & MCG_C1_IREFSTEN_MASK) {
        mcgirc_clock  = (MCG->C2 & MCG_C2_IRCS_MASK) ? 8000000u : 2000000u;
        mcgirc_clock /= 1u + ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT);
        mcgirc_clock /= 1u +  (MCG->MC & MCG_MC_LIRC_DIV2_MASK);
    }

    return mcgirc_clock;
}

#else

//Get external oscillator (crystal) frequency
static uint32_t extosc_frequency(void) {
    uint32_t MCGClock = SystemCoreClock * (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT));

    if ((MCG->C1 & MCG_C1_CLKS_MASK) == MCG_C1_CLKS(2))     //MCG clock = external reference clock
        return MCGClock;

    uint32_t divider, multiplier;
    #ifdef MCG_C5_PLLCLKEN0_MASK                            //PLL available
    if ((MCG->C1 & MCG_C1_CLKS_MASK) == MCG_C1_CLKS(0)) {   //PLL/FLL is selected
        if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) {         //FLL is selected
    #endif
            if ((MCG->S & MCG_S_IREFST_MASK) == 0x0u) {     //FLL uses external reference
                divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
                if ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u)
                    divider <<= 5u;
                /* Select correct multiplier to calculate the MCG output clock  */
                switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
                    case 0x0u:
                      multiplier = 640u;
                      break;
                    case 0x20u:
                      multiplier = 1280u;
                      break;
                    case 0x40u:
                      multiplier = 1920u;
                      break;
                    case 0x60u:
                      multiplier = 2560u;
                      break;
                    case 0x80u:
                      multiplier = 732u;
                      break;
                    case 0xA0u:
                      multiplier = 1464u;
                      break;
                    case 0xC0u:
                      multiplier = 2197u;
                      break;
                    case 0xE0u:
                    default:
                      multiplier = 2929u;
                      break;
                }

                return MCGClock * divider / multiplier;
            }
    #ifdef MCG_C5_PLLCLKEN0_MASK
        } else {             //PLL is selected
            divider = (1u + (MCG->C5 & MCG_C5_PRDIV0_MASK));
            multiplier = ((MCG->C6 & MCG_C6_VDIV0_MASK) + 24u);
            return MCGClock * divider / multiplier;
        }
    }
    #endif

    //In all other cases either there is no crystal or we cannot determine it
    //For example when the FLL is running on the internal reference, and there is also an
    //external crystal. However these are unlikely situations
    return 0;
}

//Get MCG PLL/2 or FLL frequency, depending on which one is active, sets PLLFLLSEL bit
static uint32_t mcgpllfll_frequency(void) {
    if ((MCG->C1 & MCG_C1_CLKS_MASK) != MCG_C1_CLKS(0))   //PLL/FLL is not selected
        return 0;

    uint32_t MCGClock = SystemCoreClock * (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT));
    #ifdef MCG_C5_PLLCLKEN0_MASK
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) {         //FLL is selected
        SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;        //MCG peripheral clock is FLL output
    #endif
        return MCGClock;
    #ifdef MCG_C5_PLLCLKEN0_MASK
    } else {                                            //PLL is selected
        SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;         //MCG peripheral clock is PLL output
        return (MCGClock >> 1);
    }
    #endif

    //It is possible the SystemCoreClock isn't running on the PLL, and the PLL is still active
    //for the peripherals, this is however an unlikely setup
}

#endif

#ifdef __cplusplus
}
#endif

#endif
