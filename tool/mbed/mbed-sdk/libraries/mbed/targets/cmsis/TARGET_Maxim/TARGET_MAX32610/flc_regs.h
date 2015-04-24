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

#ifndef _MXC_FLC_REGS_H
#define _MXC_FLC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  flc_regs.h
 * @addtogroup flc FLC
 * @{
 */
/*                                          Offset   Register Description
                                            ======   ======================================================= */
typedef struct {
    __IO uint32_t faddr;                /*  0x0000   Flash Operation Address                                 */
    __IO uint32_t fckdiv;               /*  0x0004   Flash Clock Rate Divisor                                */
    __IO uint32_t ctrl;                 /*  0x0008   Flash Control Register                                  */
    __I uint32_t rsv000C[6];            /*  0x000C                                                           */
    __IO uint32_t intr;                 /*  0x0024   Flash Controller Interrupt Flags and Enable/Disable 0   */
    __I uint32_t rsv0028[2];            /*  0x0028                                                           */
    __IO uint32_t fdata;                /*  0x0030   Flash Operation Data Register                           */
    __I uint32_t rsv0034[7];            /*  0x0034                                                           */
    __IO uint32_t perform;              /*  0x0050   Flash Performance Settings                              */
    __I uint32_t rsv0054[11];           /*  0x0054                                                           */
    __IO uint32_t status;               /*  0x0080   Security Status Flags                                   */
    __I uint32_t rsv0084;               /*  0x0084                                                           */
    __IO uint32_t security;             /*  0x0088   Flash Controller Security Settings                      */
    __I uint32_t rsv008C[4];            /*  0x008C                                                           */
    __IO uint32_t bypass;               /*  0x009C   Status Flags for DSB Operations                         */
    __IO uint32_t user_option;          /*  0x0100   Used to set DSB Access code and Auto-Lock in info block */
    __I uint32_t rsv0104[15];           /*  0x0104                                                           */
    __IO uint32_t ctrl2;                /*  0x0140   Flash Control Register 2                                */
    __IO uint32_t intfl1;               /*  0x0144   Interrupt Flags Register 1                              */
    __IO uint32_t inten1;               /*  0x0148   Interrupt Enable/Disable Register 1                     */
    __I uint32_t rsv014C;               /*  0x014C                                                           */
    __IO uint32_t disable_xr0;          /*  0x0150   Disable Flash Page Exec/Read Register 0                 */
    __IO uint32_t disable_xr1;          /*  0x0154   Disable Flash Page Exec/Read Register 1                 */
    __IO uint32_t disable_xr2;          /*  0x0158   Disable Flash Page Exec/Read Register 2                 */
    __IO uint32_t disable_xr3;          /*  0x015C   Disable Flash Page Exec/Read Register 3                 */
    __IO uint32_t disable_we0;          /*  0x0160   Disable Flash Page Write/Erase Register 0               */
    __IO uint32_t disable_we1;          /*  0x0164   Disable Flash Page Write/Erase Register 1               */
    __IO uint32_t disable_we2;          /*  0x0168   Disable Flash Page Write/Erase Register 2               */
    __IO uint32_t disable_we3;          /*  0x016C   Disable Flash Page Write/Erase Register 3               */
} mxc_flc_regs_t;

/*
   Register offsets for module FLC.
*/
#define MXC_R_FLC_OFFS_FADDR                          ((uint32_t)0x00000000UL)
#define MXC_R_FLC_OFFS_FCKDIV                         ((uint32_t)0x00000004UL)
#define MXC_R_FLC_OFFS_CTRL                           ((uint32_t)0x00000008UL)
#define MXC_R_FLC_OFFS_INTR                           ((uint32_t)0x00000024UL)
#define MXC_R_FLC_OFFS_FDATA                          ((uint32_t)0x00000030UL)
#define MXC_R_FLC_OFFS_PERFORM                        ((uint32_t)0x00000050UL)
#define MXC_R_FLC_OFFS_STATUS                         ((uint32_t)0x00000080UL)
#define MXC_R_FLC_OFFS_SECURITY                       ((uint32_t)0x00000088UL)
#define MXC_R_FLC_OFFS_BYPASS                         ((uint32_t)0x0000009CUL)
#define MXC_R_FLC_OFFS_USER_OPTION                    ((uint32_t)0x00000100UL)
#define MXC_R_FLC_OFFS_CTRL2                          ((uint32_t)0x00000140UL)
#define MXC_R_FLC_OFFS_INTFL1                         ((uint32_t)0x00000144UL)
#define MXC_R_FLC_OFFS_INTEN1                         ((uint32_t)0x00000148UL)
#define MXC_R_FLC_OFFS_DISABLE_XR0                    ((uint32_t)0x00000150UL)
#define MXC_R_FLC_OFFS_DISABLE_XR1                    ((uint32_t)0x00000154UL)
#define MXC_R_FLC_OFFS_DISABLE_XR2                    ((uint32_t)0x00000158UL)
#define MXC_R_FLC_OFFS_DISABLE_XR3                    ((uint32_t)0x0000015CUL)
#define MXC_R_FLC_OFFS_DISABLE_WE0                    ((uint32_t)0x00000160UL)
#define MXC_R_FLC_OFFS_DISABLE_WE1                    ((uint32_t)0x00000164UL)
#define MXC_R_FLC_OFFS_DISABLE_WE2                    ((uint32_t)0x00000168UL)
#define MXC_R_FLC_OFFS_DISABLE_WE3                    ((uint32_t)0x0000016CUL)

#define MXC_V_FLC_ERASE_CODE_PAGE_ERASE               ((uint8_t)0x55)
#define MXC_V_FLC_ERASE_CODE_MASS_ERASE               ((uint8_t)0xAA)

#define MXC_V_FLC_FLSH_UNLOCK_KEY                     ((uint8_t)0x2)

/*
   Field positions and masks for module FLC.
*/
#define MXC_F_FLC_FADDR_FADDR_POS                     0
#define MXC_F_FLC_FADDR_FADDR                         ((uint32_t)(0x0003FFFFUL << MXC_F_FLC_FADDR_FADDR_POS))

#define MXC_F_FLC_FCKDIV_FCKDIV_POS                   0
#define MXC_F_FLC_FCKDIV_FCKDIV                       ((uint32_t)(0x0000001FUL << MXC_F_FLC_FCKDIV_FCKDIV_POS))

#define MXC_F_FLC_CTRL_WRITE_POS                      0
#define MXC_F_FLC_CTRL_WRITE                          ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_WRITE_POS))
#define MXC_F_FLC_CTRL_MASS_ERASE_POS                 1
#define MXC_F_FLC_CTRL_MASS_ERASE                     ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_MASS_ERASE_POS))
#define MXC_F_FLC_CTRL_PAGE_ERASE_POS                 2
#define MXC_F_FLC_CTRL_PAGE_ERASE                     ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_PAGE_ERASE_POS))
#define MXC_F_FLC_CTRL_ERASE_CODE_POS                 8
#define MXC_F_FLC_CTRL_ERASE_CODE                     ((uint32_t)(0x000000FFUL << MXC_F_FLC_CTRL_ERASE_CODE_POS))
#define MXC_F_FLC_CTRL_INFO_BLOCK_UNLOCK_POS          16
#define MXC_F_FLC_CTRL_INFO_BLOCK_UNLOCK              ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_INFO_BLOCK_UNLOCK_POS))
#define MXC_F_FLC_CTRL_WRITE_ENABLE_POS               17
#define MXC_F_FLC_CTRL_WRITE_ENABLE                   ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_WRITE_ENABLE_POS))
#define MXC_F_FLC_CTRL_PENDING_POS                    24
#define MXC_F_FLC_CTRL_PENDING                        ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_PENDING_POS))
#define MXC_F_FLC_CTRL_INFO_BLOCK_VALID_POS           25
#define MXC_F_FLC_CTRL_INFO_BLOCK_VALID               ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_INFO_BLOCK_VALID_POS))
#define MXC_F_FLC_CTRL_AUTO_INCRE_MODE_POS            27
#define MXC_F_FLC_CTRL_AUTO_INCRE_MODE                ((uint32_t)(0x00000001UL << MXC_F_FLC_CTRL_AUTO_INCRE_MODE_POS))
#define MXC_F_FLC_CTRL_FLSH_UNLOCK_POS                28
#define MXC_F_FLC_CTRL_FLSH_UNLOCK                    ((uint32_t)(0x0000000FUL << MXC_F_FLC_CTRL_FLSH_UNLOCK_POS))

#define MXC_F_FLC_INTR_FLASH_OP_DONE_IF_POS           0
#define MXC_F_FLC_INTR_FLASH_OP_DONE_IF               ((uint32_t)(0x00000001UL << MXC_F_FLC_INTR_FLASH_OP_DONE_IF_POS))
#define MXC_F_FLC_INTR_FLASH_OP_FAILED_IF_POS         1
#define MXC_F_FLC_INTR_FLASH_OP_FAILED_IF             ((uint32_t)(0x00000001UL << MXC_F_FLC_INTR_FLASH_OP_FAILED_IF_POS))
#define MXC_F_FLC_INTR_FLASH_OP_DONE_IE_POS           9
#define MXC_F_FLC_INTR_FLASH_OP_DONE_IE               ((uint32_t)(0x00000001UL << MXC_F_FLC_INTR_FLASH_OP_DONE_IE_POS))
#define MXC_F_FLC_INTR_FLASH_OP_FAILED_IE_POS         10
#define MXC_F_FLC_INTR_FLASH_OP_FAILED_IE             ((uint32_t)(0x00000001UL << MXC_F_FLC_INTR_FLASH_OP_FAILED_IE_POS))

#define MXC_F_FLC_PERFORM_FAST_READ_MODE_EN_POS       8
#define MXC_F_FLC_PERFORM_FAST_READ_MODE_EN           ((uint32_t)(0x00000001UL << MXC_F_FLC_PERFORM_FAST_READ_MODE_EN_POS))
#define MXC_F_FLC_PERFORM_DELAY_SE_EN_POS             0
#define MXC_F_FLC_PERFORM_DELAY_SE_EN                 ((uint32_t)(0x00000001UL << MXC_F_FLC_PERFORM_DELAY_SE_EN_POS))

#define MXC_F_FLC_STATUS_DEBUG_LOCK_WINDOW_POS        0
#define MXC_F_FLC_STATUS_DEBUG_LOCK_WINDOW            ((uint32_t)(0x00000001UL << MXC_F_FLC_STATUS_DEBUG_LOCK_WINDOW_POS))
#define MXC_F_FLC_STATUS_DEBUG_LOCK_STATIC_POS        1
#define MXC_F_FLC_STATUS_DEBUG_LOCK_STATIC            ((uint32_t)(0x00000001UL << MXC_F_FLC_STATUS_DEBUG_LOCK_STATIC_POS))
#define MXC_F_FLC_STATUS_AUTO_LOCK_POS                3
#define MXC_F_FLC_STATUS_AUTO_LOCK                    ((uint32_t)(0x00000001UL << MXC_F_FLC_STATUS_AUTO_LOCK_POS))

#define MXC_F_FLC_SECURITY_DEBUG_DISABLE_POS          0
#define MXC_F_FLC_SECURITY_DEBUG_DISABLE              ((uint32_t)(0x000000FFUL << MXC_F_FLC_SECURITY_DEBUG_DISABLE_POS))
#define MXC_F_FLC_SECURITY_MASS_ERASE_LOCK_POS        8
#define MXC_F_FLC_SECURITY_MASS_ERASE_LOCK            ((uint32_t)(0x0000000FUL << MXC_F_FLC_SECURITY_MASS_ERASE_LOCK_POS))
#define MXC_F_FLC_SECURITY_SECURITY_LOCK_POS          31
#define MXC_F_FLC_SECURITY_SECURITY_LOCK              ((uint32_t)(0x00000001UL << MXC_F_FLC_SECURITY_SECURITY_LOCK_POS))

#define MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_ERASE_POS    0
#define MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_ERASE        ((uint32_t)(0x00000001UL << MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_ERASE_POS))
#define MXC_F_FLC_BYPASS_SUPERWIPE_ERASE_POS          1
#define MXC_F_FLC_BYPASS_SUPERWIPE_ERASE              ((uint32_t)(0x00000001UL << MXC_F_FLC_BYPASS_SUPERWIPE_ERASE_POS))
#define MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_COMPLETE_POS 2
#define MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_COMPLETE     ((uint32_t)(0x00000001UL << MXC_F_FLC_BYPASS_DESTRUCT_BYPASS_COMPLETE_POS))
#define MXC_F_FLC_BYPASS_SUPERWIPE_COMPLETE_POS       3
#define MXC_F_FLC_BYPASS_SUPERWIPE_COMPLETE           ((uint32_t)(0x00000001UL << MXC_F_FLC_BYPASS_SUPERWIPE_COMPLETE_POS))

#define MXC_F_FLC_CTRL2_FLASH_LVE_POS                 0
#define MXC_F_FLC_CTRL2_FLASH_LVE                     ((uint32_t)(0x000000FFUL << MXC_F_FLC_CTRL2_FLASH_LVE_POS))
#define MXC_F_FLC_CTRL2_BYPASS_AHB_FAIL_POS           8
#define MXC_F_FLC_CTRL2_BYPASS_AHB_FAIL               ((uint32_t)(0x000000FFUL << MXC_F_FLC_CTRL2_BYPASS_AHB_FAIL_POS))

#define MXC_F_FLC_INTFL1_SRAM_ADDR_WRAPPED_POS        0
#define MXC_F_FLC_INTFL1_SRAM_ADDR_WRAPPED            ((uint32_t)(0x00000001UL << MXC_F_FLC_INTFL1_SRAM_ADDR_WRAPPED_POS))
#define MXC_F_FLC_INTFL1_INVALID_FLASH_ADDR_POS       1
#define MXC_F_FLC_INTFL1_INVALID_FLASH_ADDR           ((uint32_t)(0x00000001UL << MXC_F_FLC_INTFL1_INVALID_FLASH_ADDR_POS))
#define MXC_F_FLC_INTFL1_FLASH_READ_LOCKED_POS        2
#define MXC_F_FLC_INTFL1_FLASH_READ_LOCKED            ((uint32_t)(0x00000001UL << MXC_F_FLC_INTFL1_FLASH_READ_LOCKED_POS))
#define MXC_F_FLC_INTFL1_TRIM_UPDATE_DONE_POS         3
#define MXC_F_FLC_INTFL1_TRIM_UPDATE_DONE             ((uint32_t)(0x00000001UL << MXC_F_FLC_INTFL1_TRIM_UPDATE_DONE_POS))

#define MXC_F_FLC_INTEN1_SRAM_ADDR_WRAPPED_POS        0
#define MXC_F_FLC_INTEN1_SRAM_ADDR_WRAPPED            ((uint32_t)(0x00000001UL << MXC_F_FLC_INTEN1_SRAM_ADDR_WRAPPED_POS))
#define MXC_F_FLC_INTEN1_INVALID_FLASH_ADDR_POS       1
#define MXC_F_FLC_INTEN1_INVALID_FLASH_ADDR           ((uint32_t)(0x00000001UL << MXC_F_FLC_INTEN1_INVALID_FLASH_ADDR_POS))
#define MXC_F_FLC_INTEN1_FLASH_READ_LOCKED_POS        2
#define MXC_F_FLC_INTEN1_FLASH_READ_LOCKED            ((uint32_t)(0x00000001UL << MXC_F_FLC_INTEN1_FLASH_READ_LOCKED_POS))
#define MXC_F_FLC_INTEN1_TRIM_UPDATE_DONE_POS         3
#define MXC_F_FLC_INTEN1_TRIM_UPDATE_DONE             ((uint32_t)(0x00000001UL << MXC_F_FLC_INTEN1_TRIM_UPDATE_DONE_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_FLC_REGS_H_ */
