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

#ifndef _MXC_ICC_REGS_H_
#define _MXC_ICC_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  icc_regs.h
 * @addtogroup icc ICC
 * @{
 */

/*                                              Offset   Register Description
                                                ======   =================================================== */
typedef struct {
    __IO uint32_t id;                       /*  0x0000   Device ID Register                                  */
    __IO uint32_t mem_cfg;                  /*  0x0004   Memory Configuration                                */
    __I uint32_t rsv0008[62];               /*  0x0008                                                       */
    __IO uint32_t ctrl_stat;                /*  0x0100   Control and Status                                  */
    __I uint32_t rsv0104[383];              /*  0x0104                                                       */
    __IO uint32_t invdt_all;                /*  0x0700   Invalidate (Clear) Cache Control                    */
} mxc_icc_regs_t;

/*
   Register offsets for module ICC.
*/
#define MXC_R_ICC_OFFS_ID                       ((uint32_t)0x00000000UL)
#define MXC_R_ICC_OFFS_MEM_CFG                  ((uint32_t)0x00000004UL)
#define MXC_R_ICC_OFFS_CTRL_STAT                ((uint32_t)0x00000100UL)
#define MXC_R_ICC_OFFS_INVDT_ALL                ((uint32_t)0x00000700UL)

/*
   Field positions and masks for module ICC.
*/
#define MXC_F_ICC_ID_RTL_VERSION_POS            0
#define MXC_F_ICC_ID_RTL_VERSION                ((uint32_t)(0x0000003FUL << MXC_F_ICC_ID_RTL_VERSION_POS))
#define MXC_F_ICC_ID_PART_NUM_POS               6
#define MXC_F_ICC_ID_PART_NUM                   ((uint32_t)(0x0000000FUL << MXC_F_ICC_ID_PART_NUM_POS))
#define MXC_F_ICC_ID_CACHE_ID_POS               10
#define MXC_F_ICC_ID_CACHE_ID                   ((uint32_t)(0x0000003FUL << MXC_F_ICC_ID_CACHE_ID_POS))

#define MXC_F_ICC_MEM_CFG_CACHE_SIZE_POS        0
#define MXC_F_ICC_MEM_CFG_CACHE_SIZE            ((uint32_t)(0x0000FFFFUL << MXC_F_ICC_MEM_CFG_CACHE_SIZE_POS))
#define MXC_F_ICC_MEM_CFG_MAIN_MEMORY_SIZE_POS  16
#define MXC_F_ICC_MEM_CFG_MAIN_MEMORY_SIZE      ((uint32_t)(0x0000FFFFUL << MXC_F_ICC_MEM_CFG_MAIN_MEMORY_SIZE_POS))

#define MXC_F_ICC_CTRL_STAT_ENABLE_POS          0
#define MXC_F_ICC_CTRL_STAT_ENABLE              ((uint32_t)(0x00000001UL << MXC_F_ICC_CTRL_STAT_ENABLE_POS))
#define MXC_F_ICC_CTRL_STAT_READY_POS           16
#define MXC_F_ICC_CTRL_STAT_READY               ((uint32_t)(0x00000001UL << MXC_F_ICC_CTRL_STAT_READY_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_ICC_REGS_H_ */
