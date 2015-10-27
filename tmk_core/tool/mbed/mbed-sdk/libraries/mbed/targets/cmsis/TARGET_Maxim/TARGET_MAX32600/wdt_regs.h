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

#ifndef _MXC_WDT_REGS_H_
#define _MXC_WDT_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  wdt_regs.h
 * @addtogroup wdt WDT
 * @{
 */

/**
 * @brief Defines watchdog timer periods
 */
typedef enum {
    /** 2^31 cycle period */
    MXC_E_WDT_PERIOD_2_31_CLKS = 0,
    /** 2^30 cycle period */
    MXC_E_WDT_PERIOD_2_30_CLKS,
    /** 2^29 cycle period */
    MXC_E_WDT_PERIOD_2_29_CLKS,
    /** 2^28 cycle period */
    MXC_E_WDT_PERIOD_2_28_CLKS,
    /** 2^27 cycle period */
    MXC_E_WDT_PERIOD_2_27_CLKS,
    /** 2^26 cycle period */
    MXC_E_WDT_PERIOD_2_26_CLKS,
    /** 2^25 cycle period */
    MXC_E_WDT_PERIOD_2_25_CLKS,
    /** 2^24 cycle period */
    MXC_E_WDT_PERIOD_2_24_CLKS,
    /** 2^23 cycle period */
    MXC_E_WDT_PERIOD_2_23_CLKS,
    /** 2^22 cycle period */
    MXC_E_WDT_PERIOD_2_22_CLKS,
    /** 2^21 cycle period */
    MXC_E_WDT_PERIOD_2_21_CLKS,
    /** 2^20 cycle period */
    MXC_E_WDT_PERIOD_2_20_CLKS,
    /** 2^19 cycle period */
    MXC_E_WDT_PERIOD_2_19_CLKS,
    /** 2^18 cycle period */
    MXC_E_WDT_PERIOD_2_18_CLKS,
    /** 2^17 cycle period */
    MXC_E_WDT_PERIOD_2_17_CLKS,
    /** 2^16 cycle period */
    MXC_E_WDT_PERIOD_2_16_CLKS,
} mxc_wdt_period_t;

/*                                  Offset   Register Description
                                    ======   ================================================ */
typedef struct {
    __IO uint32_t ctrl;         /*  0x0000   Watchdog Timer Control Register                  */
    __IO uint32_t clear;        /*  0x0004   Watchdog Clear Register (Feed Dog)               */
    __IO uint32_t int_rst_fl;   /*  0x0008   Watchdog Interrupt/Reset Flags                   */
    __IO uint32_t int_rst_en;   /*  0x000C   Interrupt/Reset Enable/Disable Controls          */
    __I uint32_t rsv0010;       /*  0x0010                                                    */
    __IO uint32_t lock_ctrl;    /*  0x0014   Lock Register Setting for WDT CTRL               */
} mxc_wdt_regs_t;

/*
   Register offsets for module WDT.
*/
#define MXC_R_WDT_OFFS_CTRL                       ((uint32_t)0x00000000UL)
#define MXC_R_WDT_OFFS_CLEAR                      ((uint32_t)0x00000004UL)
#define MXC_R_WDT_OFFS_INT_RST_FL                 ((uint32_t)0x00000008UL)
#define MXC_R_WDT_OFFS_INT_RST_EN                 ((uint32_t)0x0000000CUL)
#define MXC_R_WDT_OFFS_LOCK_CTRL                  ((uint32_t)0x00000014UL)

#define MXC_V_WDT_WDLOCK_LOCK_KEY                 ((uint8_t)0x24)
#define MXC_V_WDT_WDLOCK_UNLOCK_KEY               ((uint8_t)0x42)


/*
   Field positions and masks for module WDT.
*/
#define MXC_F_WDT_CTRL_INT_PERIOD_POS       0
#define MXC_F_WDT_CTRL_INT_PERIOD           ((uint32_t)(0x0000000FUL << MXC_F_WDT_CTRL_INT_PERIOD_POS))
#define MXC_F_WDT_CTRL_RST_PERIOD_POS       4
#define MXC_F_WDT_CTRL_RST_PERIOD           ((uint32_t)(0x0000000FUL << MXC_F_WDT_CTRL_RST_PERIOD_POS))
#define MXC_F_WDT_CTRL_EN_TIMER_POS         8
#define MXC_F_WDT_CTRL_EN_TIMER             ((uint32_t)(0x00000001UL << MXC_F_WDT_CTRL_EN_TIMER_POS))
#define MXC_F_WDT_CTRL_EN_CLOCK_POS         9
#define MXC_F_WDT_CTRL_EN_CLOCK             ((uint32_t)(0x00000001UL << MXC_F_WDT_CTRL_EN_CLOCK_POS))
#define MXC_F_WDT_CTRL_WAIT_PERIOD_POS      12
#define MXC_F_WDT_CTRL_WAIT_PERIOD          ((uint32_t)(0x0000000FUL << MXC_F_WDT_CTRL_WAIT_PERIOD_POS))

#define MXC_F_WDT_FLAGS_TIMEOUT_POS         0
#define MXC_F_WDT_FLAGS_TIMEOUT             ((uint32_t)(0x00000001UL << MXC_F_WDT_FLAGS_TIMEOUT_POS))
#define MXC_F_WDT_FLAGS_PRE_WIN_POS         1
#define MXC_F_WDT_FLAGS_PRE_WIN             ((uint32_t)(0x00000001UL << MXC_F_WDT_FLAGS_PRE_WIN_POS))
#define MXC_F_WDT_FLAGS_RESET_OUT_POS       2
#define MXC_F_WDT_FLAGS_RESET_OUT           ((uint32_t)(0x00000001UL << MXC_F_WDT_FLAGS_RESET_OUT_POS))

#define MXC_F_WDT_ENABLE_TIMEOUT_POS        0
#define MXC_F_WDT_ENABLE_TIMEOUT            ((uint32_t)(0x00000001UL << MXC_F_WDT_ENABLE_TIMEOUT_POS))
#define MXC_F_WDT_ENABLE_PRE_WIN_POS        1
#define MXC_F_WDT_ENABLE_PRE_WIN            ((uint32_t)(0x00000001UL << MXC_F_WDT_ENABLE_PRE_WIN_POS))
#define MXC_F_WDT_ENABLE_RESET_OUT_POS      2
#define MXC_F_WDT_ENABLE_RESET_OUT          ((uint32_t)(0x00000001UL << MXC_F_WDT_ENABLE_RESET_OUT_POS))

#define MXC_F_WDT_LOCK_CTRL_WDLOCK_POS      0
#define MXC_F_WDT_LOCK_CTRL_WDLOCK          ((uint32_t)(0x000000FFUL << MXC_F_WDT_LOCK_CTRL_WDLOCK_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_WDT_REGS_H_ */
