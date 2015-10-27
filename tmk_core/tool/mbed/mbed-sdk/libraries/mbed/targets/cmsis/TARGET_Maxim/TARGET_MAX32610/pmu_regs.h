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

#ifndef _MXC_PMU_REGS_H_
#define _MXC_PMU_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  pmu_regs.h
 * @addtogroup pmu PMU
 * @{
 */

/*                                     Offset   Register Description
                                       ======   ======================================================== */
typedef struct {
    __IO uint32_t dscadr;          /*  0x0000   Starting Descriptor Address                              */
    __IO uint32_t cfg;             /*  0x0004   Channel Configuration                                    */
    __IO uint32_t loop;            /*  0x0008   Channel Loop Counters                                    */
    __IO uint32_t op;              /*  0x000C   Current Descriptor DWORD 0 (OP)                          */
    __IO uint32_t dsc1;            /*  0x0010   Current Descriptor DWORD 1                               */
    __IO uint32_t dsc2;            /*  0x0014   Current Descriptor DWORD 2                               */
    __IO uint32_t dsc3;            /*  0x0018   Current Descriptor DWORD 3                               */
    __IO uint32_t dsc4;            /*  0x001C   Current Descriptor DWORD 4                               */
} mxc_pmu_regs_t;

/*
   Register offsets for module PMU.
*/
#define MXC_R_PMU_OFFS_DSCADR                     ((uint32_t)0x00000000UL)
#define MXC_R_PMU_OFFS_CFG                        ((uint32_t)0x00000004UL)
#define MXC_R_PMU_OFFS_LOOP                       ((uint32_t)0x00000008UL)
#define MXC_R_PMU_OFFS_OP                         ((uint32_t)0x0000000CUL)
#define MXC_R_PMU_OFFS_DSC1                       ((uint32_t)0x00000010UL)
#define MXC_R_PMU_OFFS_DSC2                       ((uint32_t)0x00000014UL)
#define MXC_R_PMU_OFFS_DSC3                       ((uint32_t)0x00000018UL)
#define MXC_R_PMU_OFFS_DSC4                       ((uint32_t)0x0000001CUL)

/*
   Field positions and masks for module PMU.
*/
#define MXC_F_PMU_CFG_ENABLE_POS                            0
#define MXC_F_PMU_CFG_ENABLE                                ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_ENABLE_POS))
#define MXC_F_PMU_CFG_LL_STOPPED_POS                        2
#define MXC_F_PMU_CFG_LL_STOPPED                            ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_LL_STOPPED_POS))
#define MXC_F_PMU_CFG_MANUAL_POS                            3
#define MXC_F_PMU_CFG_MANUAL                                ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_MANUAL_POS))
#define MXC_F_PMU_CFG_BUS_ERROR_POS                         4
#define MXC_F_PMU_CFG_BUS_ERROR                             ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_BUS_ERROR_POS))
#define MXC_F_PMU_CFG_TO_STAT_POS                           6
#define MXC_F_PMU_CFG_TO_STAT                               ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_TO_STAT_POS))
#define MXC_F_PMU_CFG_TO_SEL_POS                            11
#define MXC_F_PMU_CFG_TO_SEL                                ((uint32_t)(0x00000007UL << MXC_F_PMU_CFG_TO_SEL_POS))
#define MXC_F_PMU_CFG_PS_SEL_POS                            14
#define MXC_F_PMU_CFG_PS_SEL                                ((uint32_t)(0x00000003UL << MXC_F_PMU_CFG_PS_SEL_POS))
#define MXC_F_PMU_CFG_INTERRUPT_POS                         16
#define MXC_F_PMU_CFG_INTERRUPT                             ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_INTERRUPT_POS))
#define MXC_F_PMU_CFG_INT_EN_POS                            17
#define MXC_F_PMU_CFG_INT_EN                                ((uint32_t)(0x00000001UL << MXC_F_PMU_CFG_INT_EN_POS))
#define MXC_F_PMU_CFG_BURST_SIZE_POS                        24
#define MXC_F_PMU_CFG_BURST_SIZE                            ((uint32_t)(0x0000001FUL << MXC_F_PMU_CFG_BURST_SIZE_POS))

#define MXC_F_PMU_LOOP_COUNTER_0_POS                        0
#define MXC_F_PMU_LOOP_COUNTER_0                            ((uint32_t)(0x0000FFFFUL << MXC_F_PMU_LOOP_COUNTER_0_POS))
#define MXC_F_PMU_LOOP_COUNTER_1_POS                        16
#define MXC_F_PMU_LOOP_COUNTER_1                            ((uint32_t)(0x0000FFFFUL << MXC_F_PMU_LOOP_COUNTER_1_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_PMU_REGS_H_ */
