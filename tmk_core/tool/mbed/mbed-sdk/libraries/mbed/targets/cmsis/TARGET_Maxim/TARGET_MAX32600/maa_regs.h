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

#ifndef _MXC_MAA_REGS_H_
#define _MXC_MAA_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  maa_regs.h
 * @addtogroup maa MAA
 * @{
 */

/*                                    Offset   Register Description
                                      ======   ========================================================== */
typedef struct {
    __IO uint32_t ctrl;           /*  0x0000   MAA Control, Configuration and Status                      */
    __IO uint32_t maws;           /*  0x0004   MAA Word (Operand) Size, Big/Little Endian Mode Select     */
} mxc_maa_regs_t;

/*                                    Offset   Register Description
                                      ======   ========================================================== */
typedef struct {
    __IO uint32_t seg0[16];        /*  0x0000   [64 bytes] MAA Memory Segment 0                            */
    __IO uint32_t seg1[16];        /*  0x0040   [64 bytes] MAA Memory Segment 1                            */
    __IO uint32_t seg2[16];        /*  0x0080   [64 bytes] MAA Memory Segment 2                            */
    __IO uint32_t seg3[16];        /*  0x00C0   [64 bytes] MAA Memory Segment 3                            */
    __IO uint32_t seg4[16];        /*  0x0100   [64 bytes] MAA Memory Segment 4                            */
    __IO uint32_t seg5[16];        /*  0x0140   [64 bytes] MAA Memory Segment 5                            */
} mxc_maa_mem_regs_t;

/*
   Register offsets for module MAA.
*/
#define MXC_R_MAA_OFFS_CTRL         ((uint32_t)0x00000000UL)
#define MXC_R_MAA_OFFS_MAWS         ((uint32_t)0x00000004UL)
#define MXC_R_MAA_MEM_OFFS_SEG0     ((uint32_t)0x00000000UL)
#define MXC_R_MAA_MEM_OFFS_SEG1     ((uint32_t)0x00000040UL)
#define MXC_R_MAA_MEM_OFFS_SEG2     ((uint32_t)0x00000080UL)
#define MXC_R_MAA_MEM_OFFS_SEG3     ((uint32_t)0x000000C0UL)
#define MXC_R_MAA_MEM_OFFS_SEG4     ((uint32_t)0x00000100UL)
#define MXC_R_MAA_MEM_OFFS_SEG5     ((uint32_t)0x00000140UL)

/*
   Field positions and masks for module MAA.
*/
#define MXC_F_MAA_CTRL_START_POS    0
#define MXC_F_MAA_CTRL_START        ((uint32_t)(0x00000001UL << MXC_F_MAA_CTRL_START_POS))
#define MXC_F_MAA_CTRL_OPSEL_POS    1
#define MXC_F_MAA_CTRL_OPSEL        ((uint32_t)(0x00000007UL << MXC_F_MAA_CTRL_OPSEL_POS))
#define MXC_F_MAA_CTRL_OCALC_POS    4
#define MXC_F_MAA_CTRL_OCALC        ((uint32_t)(0x00000001UL << MXC_F_MAA_CTRL_OCALC_POS))
#define MXC_F_MAA_CTRL_INTEN_POS    5
#define MXC_F_MAA_CTRL_INTEN        ((uint32_t)(0x00000001UL << MXC_F_MAA_CTRL_INTEN_POS))
#define MXC_F_MAA_CTRL_IF_DONE_POS  6
#define MXC_F_MAA_CTRL_IF_DONE      ((uint32_t)(0x00000001UL << MXC_F_MAA_CTRL_IF_DONE_POS))
#define MXC_F_MAA_CTRL_IF_ERROR_POS 7
#define MXC_F_MAA_CTRL_IF_ERROR     ((uint32_t)(0x00000001UL << MXC_F_MAA_CTRL_IF_ERROR_POS))
#define MXC_F_MAA_CTRL_OFS_A_POS    8
#define MXC_F_MAA_CTRL_OFS_A        ((uint32_t)(0x00000003UL << MXC_F_MAA_CTRL_OFS_A_POS))
#define MXC_F_MAA_CTRL_OFS_B_POS    10
#define MXC_F_MAA_CTRL_OFS_B        ((uint32_t)(0x00000003UL << MXC_F_MAA_CTRL_OFS_B_POS))
#define MXC_F_MAA_CTRL_OFS_EXP_POS  12
#define MXC_F_MAA_CTRL_OFS_EXP      ((uint32_t)(0x00000003UL << MXC_F_MAA_CTRL_OFS_EXP_POS))
#define MXC_F_MAA_CTRL_OFS_MOD_POS  14
#define MXC_F_MAA_CTRL_OFS_MOD      ((uint32_t)(0x00000003UL << MXC_F_MAA_CTRL_OFS_MOD_POS))
#define MXC_F_MAA_CTRL_SEG_A_POS    16
#define MXC_F_MAA_CTRL_SEG_A        ((uint32_t)(0x0000000FUL << MXC_F_MAA_CTRL_SEG_A_POS))
#define MXC_F_MAA_CTRL_SEG_B_POS    20
#define MXC_F_MAA_CTRL_SEG_B        ((uint32_t)(0x0000000FUL << MXC_F_MAA_CTRL_SEG_B_POS))
#define MXC_F_MAA_CTRL_SEG_RES_POS  24
#define MXC_F_MAA_CTRL_SEG_RES      ((uint32_t)(0x0000000FUL << MXC_F_MAA_CTRL_SEG_RES_POS))
#define MXC_F_MAA_CTRL_SEG_TMP_POS  28
#define MXC_F_MAA_CTRL_SEG_TMP      ((uint32_t)(0x0000000FUL << MXC_F_MAA_CTRL_SEG_TMP_POS))

#define MXC_F_MAA_MAWS_MODLEN_POS   0
#define MXC_F_MAA_MAWS_MODLEN       ((uint32_t)(0x000003FFUL << MXC_F_MAA_MAWS_MODLEN_POS))
#define MXC_F_MAA_MAWS_BYTESWAP_POS 16
#define MXC_F_MAA_MAWS_BYTESWAP     ((uint32_t)(0x00000001UL << MXC_F_MAA_MAWS_BYTESWAP_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_MAA_REGS_H_ */
