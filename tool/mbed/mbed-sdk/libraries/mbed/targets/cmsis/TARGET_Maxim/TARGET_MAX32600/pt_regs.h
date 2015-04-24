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

#ifndef _MXC_PT_REGS_H_
#define _MXC_PT_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  pt_regs.h
 * @addtogroup pt PT
 * @{
 */

typedef struct {
    __IO uint32_t ctrl;
    __IO uint32_t resync;
} mxc_ptg_regs_t;

/*                                      Offset   Register Description
                                        ======   ================================================== */
typedef struct {
    __IO uint32_t rate_length;      /*  0x0000   Pulse train Output length and rate                 */
    __IO uint32_t train;            /*  0x0004   Pulse Train Output Pattern                         */
} mxc_pt_regs_t;

/*
   Register offsets for module PT.
*/
#define MXC_R_PTG_OFFS_CTRL                         ((uint32_t)0x00000000UL)
#define MXC_R_PTG_OFFS_RESYNC                       ((uint32_t)0x00000004UL)
#define MXC_R_PT_OFFS_RATE_LENGTH                   ((uint32_t)0x00000000UL)
#define MXC_R_PT_OFFS_TRAIN                         ((uint32_t)0x00000004UL)


/*
   Field positions and masks for module PT.
*/
#define MXC_F_PT_CTRL_ENABLE_ALL_POS                1
#define MXC_F_PT_CTRL_ENABLE_ALL                    ((uint32_t)(0x00000001UL << MXC_F_PT_CTRL_ENABLE_ALL_POS))

#define MXC_F_PT_RESYNC_PT0_POS                     0
#define MXC_F_PT_RESYNC_PT0                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT0_POS))
#define MXC_F_PT_RESYNC_PT1_POS                     1
#define MXC_F_PT_RESYNC_PT1                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT1_POS))
#define MXC_F_PT_RESYNC_PT2_POS                     2
#define MXC_F_PT_RESYNC_PT2                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT2_POS))
#define MXC_F_PT_RESYNC_PT3_POS                     3
#define MXC_F_PT_RESYNC_PT3                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT3_POS))
#define MXC_F_PT_RESYNC_PT4_POS                     4
#define MXC_F_PT_RESYNC_PT4                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT4_POS))
#define MXC_F_PT_RESYNC_PT5_POS                     5
#define MXC_F_PT_RESYNC_PT5                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT5_POS))
#define MXC_F_PT_RESYNC_PT6_POS                     6
#define MXC_F_PT_RESYNC_PT6                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT6_POS))
#define MXC_F_PT_RESYNC_PT7_POS                     7
#define MXC_F_PT_RESYNC_PT7                         ((uint32_t)(0x00000001UL << MXC_F_PT_RESYNC_PT7_POS))

#define MXC_F_PT_RATE_LENGTH_RATE_CONTROL_POS       0
#define MXC_F_PT_RATE_LENGTH_RATE_CONTROL           ((uint32_t)(0x07FFFFFFUL << MXC_F_PT_RATE_LENGTH_RATE_CONTROL_POS))
#define MXC_F_PT_RATE_LENGTH_MODE_POS               27
#define MXC_F_PT_RATE_LENGTH_MODE                   ((uint32_t)(0x0000001FUL << MXC_F_PT_RATE_LENGTH_MODE_POS))

/*
   Field values and shifted values for module PT.
*/
#define MXC_V_PT_RATE_LENGTH_MODE_32_BIT_PATTERN    ((uint32_t)(0x0x00000000UL))
#define MXC_V_PT_RATE_LENGTH_MODE_SQUARE_WAVE       ((uint32_t)(0x0x00000001UL))
#define MXC_V_PT_RATE_LENGTH_MODE_2_BIT_PATTERN     ((uint32_t)(0x0x00000002UL))
#define MXC_V_PT_RATE_LENGTH_MODE_3_BIT_PATTERN     ((uint32_t)(0x0x00000003UL))
#define MXC_V_PT_RATE_LENGTH_MODE_4_BIT_PATTERN     ((uint32_t)(0x0x00000004UL))
#define MXC_V_PT_RATE_LENGTH_MODE_5_BIT_PATTERN     ((uint32_t)(0x0x00000005UL))
#define MXC_V_PT_RATE_LENGTH_MODE_6_BIT_PATTERN     ((uint32_t)(0x0x00000006UL))
#define MXC_V_PT_RATE_LENGTH_MODE_7_BIT_PATTERN     ((uint32_t)(0x0x00000007UL))
#define MXC_V_PT_RATE_LENGTH_MODE_8_BIT_PATTERN     ((uint32_t)(0x0x00000008UL))
#define MXC_V_PT_RATE_LENGTH_MODE_9_BIT_PATTERN     ((uint32_t)(0x0x00000009UL))
#define MXC_V_PT_RATE_LENGTH_MODE_10_BIT_PATTERN    ((uint32_t)(0x0x00000010UL))
#define MXC_V_PT_RATE_LENGTH_MODE_11_BIT_PATTERN    ((uint32_t)(0x0x00000011UL))
#define MXC_V_PT_RATE_LENGTH_MODE_12_BIT_PATTERN    ((uint32_t)(0x0x00000012UL))
#define MXC_V_PT_RATE_LENGTH_MODE_13_BIT_PATTERN    ((uint32_t)(0x0x00000013UL))
#define MXC_V_PT_RATE_LENGTH_MODE_14_BIT_PATTERN    ((uint32_t)(0x0x00000014UL))
#define MXC_V_PT_RATE_LENGTH_MODE_15_BIT_PATTERN    ((uint32_t)(0x0x00000015UL))
#define MXC_V_PT_RATE_LENGTH_MODE_16_BIT_PATTERN    ((uint32_t)(0x0x00000016UL))
#define MXC_V_PT_RATE_LENGTH_MODE_17_BIT_PATTERN    ((uint32_t)(0x0x00000017UL))
#define MXC_V_PT_RATE_LENGTH_MODE_18_BIT_PATTERN    ((uint32_t)(0x0x00000018UL))
#define MXC_V_PT_RATE_LENGTH_MODE_19_BIT_PATTERN    ((uint32_t)(0x0x00000019UL))
#define MXC_V_PT_RATE_LENGTH_MODE_20_BIT_PATTERN    ((uint32_t)(0x0x00000020UL))
#define MXC_V_PT_RATE_LENGTH_MODE_21_BIT_PATTERN    ((uint32_t)(0x0x00000021UL))
#define MXC_V_PT_RATE_LENGTH_MODE_22_BIT_PATTERN    ((uint32_t)(0x0x00000022UL))
#define MXC_V_PT_RATE_LENGTH_MODE_23_BIT_PATTERN    ((uint32_t)(0x0x00000023UL))
#define MXC_V_PT_RATE_LENGTH_MODE_24_BIT_PATTERN    ((uint32_t)(0x0x00000024UL))
#define MXC_V_PT_RATE_LENGTH_MODE_25_BIT_PATTERN    ((uint32_t)(0x0x00000025UL))
#define MXC_V_PT_RATE_LENGTH_MODE_26_BIT_PATTERN    ((uint32_t)(0x0x00000026UL))
#define MXC_V_PT_RATE_LENGTH_MODE_27_BIT_PATTERN    ((uint32_t)(0x0x00000027UL))
#define MXC_V_PT_RATE_LENGTH_MODE_28_BIT_PATTERN    ((uint32_t)(0x0x00000028UL))
#define MXC_V_PT_RATE_LENGTH_MODE_29_BIT_PATTERN    ((uint32_t)(0x0x00000029UL))
#define MXC_V_PT_RATE_LENGTH_MODE_30_BIT_PATTERN    ((uint32_t)(0x0x00000030UL))
#define MXC_V_PT_RATE_LENGTH_MODE_31_BIT_PATTERN    ((uint32_t)(0x0x00000031UL))

#define MXC_S_PT_RATE_LENGTH_MODE_32_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_32_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_SQUARE_WAVE       ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_SQUARE_WAVE      << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_2_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_2_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_3_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_3_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_4_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_4_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_5_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_5_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_6_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_6_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_7_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_7_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_8_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_8_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_9_BIT_PATTERN     ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_9_BIT_PATTERN    << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_10_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_10_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_11_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_11_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_12_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_12_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_13_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_13_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_14_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_14_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_15_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_15_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_16_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_16_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_17_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_17_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_18_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_18_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_19_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_19_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_20_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_20_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_21_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_21_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_22_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_22_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_23_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_23_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_24_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_24_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_25_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_25_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_26_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_26_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_27_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_27_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_28_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_28_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_29_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_29_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_30_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_30_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))
#define MXC_S_PT_RATE_LENGTH_MODE_31_BIT_PATTERN    ((uint32_t)(MXC_V_PT_RATE_LENGTH_MODE_31_BIT_PATTERN   << MXC_F_PT_RATE_LENGTH_MODE_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_PT_REGS_H_ */
