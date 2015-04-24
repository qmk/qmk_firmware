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
 
#include "cmsis_nvic.h"

#if defined(TOOLCHAIN_GCC_ARM) || defined(TOOLCHAIN_ARM_STD)
__attribute__((aligned(256)))
#endif
#if defined(TOOLCHAIN_IAR)
#pragma data_alignment=256
#endif
static void (*ramVectorTable[MXC_IRQ_COUNT])(void);

void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
    uint32_t *vectors = (uint32_t*)SCB->VTOR;
    uint32_t i;

    // Copy and switch to dynamic vectors if the first time called
    if (SCB->VTOR != (uint32_t)ramVectorTable) {
        uint32_t *old_vectors = (uint32_t*)SCB->VTOR;
        vectors = (uint32_t*)ramVectorTable;
        for (i = 0; i < NVIC_NUM_VECTORS; i++) {
            vectors[i] = old_vectors[i];
        }
        SCB->VTOR = (uint32_t)ramVectorTable;
    }
    vectors[IRQn + NVIC_USER_IRQ_OFFSET] = vector;
}

uint32_t NVIC_GetVector(IRQn_Type IRQn)
{
    uint32_t *vectors = (uint32_t*)SCB->VTOR;
    return vectors[IRQn + NVIC_USER_IRQ_OFFSET];
}
