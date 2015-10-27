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

#ifndef _MXC_RTC_REGS_H
#define _MXC_RTC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  rtc_regs.h
 * @addtogroup rtc RTCTMR
 * @{
 */

/**
 * @brief Defines clock divider for 4096Hz input clock.
 */
typedef enum {
    /** (4kHz) divide input clock by 2^0 = 1 */
    MXC_E_RTC_PRESCALE_DIV_2_0 = 0,
    /** (2kHz) divide input clock by 2^1 = 2 */
    MXC_E_RTC_PRESCALE_DIV_2_1,
    /** (1kHz) divide input clock by 2^2 = 4 */
    MXC_E_RTC_PRESCALE_DIV_2_2,
    /** (512Hz) divide input clock by 2^3 = 8 */
    MXC_E_RTC_PRESCALE_DIV_2_3,
    /** (256Hz) divide input clock by 2^4 = 16 */
    MXC_E_RTC_PRESCALE_DIV_2_4,
    /** (128Hz) divide input clock by 2^5 = 32 */
    MXC_E_RTC_PRESCALE_DIV_2_5,
    /** (64Hz) divide input clock by 2^6 = 64 */
    MXC_E_RTC_PRESCALE_DIV_2_6,
    /** (32Hz) divide input clock by 2^7 = 128 */
    MXC_E_RTC_PRESCALE_DIV_2_7,
    /** (16Hz) divide input clock by 2^8 = 256 */
    MXC_E_RTC_PRESCALE_DIV_2_8,
    /** (8Hz) divide input clock by 2^9 = 512 */
    MXC_E_RTC_PRESCALE_DIV_2_9,
    /** (4Hz) divide input clock by 2^10 = 1024 */
    MXC_E_RTC_PRESCALE_DIV_2_10,
    /** (2Hz) divide input clock by 2^11 = 2048 */
    MXC_E_RTC_PRESCALE_DIV_2_11,
    /** (1Hz) divide input clock by 2^12 = 4096 */
    MXC_E_RTC_PRESCALE_DIV_2_12,
} mxc_rtc_prescale_t;

/*                                          Offset   Register Description
                                            ======   ========================================= */
typedef struct {
    __IO uint32_t ctrl;                 /*  0x0000   RTC Timer Control                         */
    __IO uint32_t timer;                /*  0x0004   RTC Timer Count Value                     */
    __IO uint32_t comp[2];              /*  0x0008   RTC Alarm (0..1) Compare Registers        */
    __IO uint32_t flags;                /*  0x0010   CPU Interrupt and RTC Domain Flags        */
    __I uint32_t rsv0014;               /*  0x0014                                             */
    __IO uint32_t inten;                /*  0x0018   Interrupt Enable Controls                 */
    __IO uint32_t prescale;             /*  0x001C   RTC Timer Prescale Setting                */
    __I uint32_t rsv0020;               /*  0x0020                                             */
    __IO uint32_t prescale_mask;        /*  0x0024   RTC Timer Prescale Compare Mask           */
    __IO uint32_t trim_ctrl;            /*  0x0028   RTC Timer Trim Controls                   */
    __IO uint32_t trim_value;           /*  0x002C   RTC Timer Trim Adjustment Interval        */
} mxc_rtctmr_regs_t;

/*
   Register offsets for module RTCTMR.
*/
#define MXC_R_RTCTMR_OFFS_CTRL                    ((uint32_t)0x00000000UL)
#define MXC_R_RTCTMR_OFFS_TIMER                   ((uint32_t)0x00000004UL)
#define MXC_R_RTCTMR_OFFS_COMP_0                  ((uint32_t)0x00000008UL)
#define MXC_R_RTCTMR_OFFS_COMP_1                  ((uint32_t)0x0000000CUL)
#define MXC_R_RTCTMR_OFFS_FLAGS                   ((uint32_t)0x00000010UL)
#define MXC_R_RTCTMR_OFFS_INTEN                   ((uint32_t)0x00000018UL)
#define MXC_R_RTCTMR_OFFS_PRESCALE                ((uint32_t)0x0000001CUL)
#define MXC_R_RTCTMR_OFFS_PRESCALE_MASK           ((uint32_t)0x00000024UL)
#define MXC_R_RTCTMR_OFFS_TRIM_CTRL               ((uint32_t)0x00000028UL)
#define MXC_R_RTCTMR_OFFS_TRIM_VALUE              ((uint32_t)0x0000002CUL)

/*
   Field positions and masks for module RTCTMR.
*/
#define MXC_F_RTC_CTRL_ENABLE_POS                           0
#define MXC_F_RTC_CTRL_ENABLE                               ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_ENABLE_POS))
#define MXC_F_RTC_CTRL_CLEAR_POS                            1
#define MXC_F_RTC_CTRL_CLEAR                                ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_CLEAR_POS))
#define MXC_F_RTC_CTRL_PENDING_POS                          2
#define MXC_F_RTC_CTRL_PENDING                              ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_PENDING_POS))
#define MXC_F_RTC_CTRL_USE_ASYNC_FLAGS_POS                  3
#define MXC_F_RTC_CTRL_USE_ASYNC_FLAGS                      ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_USE_ASYNC_FLAGS_POS))
#define MXC_F_RTC_CTRL_AGGRESSIVE_RST_POS                   4
#define MXC_F_RTC_CTRL_AGGRESSIVE_RST                       ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_AGGRESSIVE_RST_POS))
#define MXC_F_RTC_CTRL_EN_ACTIVE_POS                        16
#define MXC_F_RTC_CTRL_EN_ACTIVE                            ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_EN_ACTIVE_POS))
#define MXC_F_RTC_CTRL_OSC_GOTO_LOW_ACTIVE_POS              17
#define MXC_F_RTC_CTRL_OSC_GOTO_LOW_ACTIVE                  ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_OSC_GOTO_LOW_ACTIVE_POS))
#define MXC_F_RTC_CTRL_OSC_FRCE_SM_EN_ACTIVE_POS            18
#define MXC_F_RTC_CTRL_OSC_FRCE_SM_EN_ACTIVE                ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_OSC_FRCE_SM_EN_ACTIVE_POS))
#define MXC_F_RTC_CTRL_OSC_FRCE_ST_ACTIVE_POS               19
#define MXC_F_RTC_CTRL_OSC_FRCE_ST_ACTIVE                   ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_OSC_FRCE_ST_ACTIVE_POS))
#define MXC_F_RTC_CTRL_SET_ACTIVE_POS                       20
#define MXC_F_RTC_CTRL_SET_ACTIVE                           ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_SET_ACTIVE_POS))
#define MXC_F_RTC_CTRL_CLR_ACTIVE_POS                       21
#define MXC_F_RTC_CTRL_CLR_ACTIVE                           ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_CLR_ACTIVE_POS))
#define MXC_F_RTC_CTRL_ROLLOVER_CLR_ACTIVE_POS              22
#define MXC_F_RTC_CTRL_ROLLOVER_CLR_ACTIVE                  ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_ROLLOVER_CLR_ACTIVE_POS))
#define MXC_F_RTC_CTRL_PRESCALE_CMPR0_ACTIVE_POS            23
#define MXC_F_RTC_CTRL_PRESCALE_CMPR0_ACTIVE                ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_PRESCALE_CMPR0_ACTIVE_POS))
#define MXC_F_RTC_CTRL_PRESCALE_UPDATE_ACTIVE_POS           24
#define MXC_F_RTC_CTRL_PRESCALE_UPDATE_ACTIVE               ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_PRESCALE_UPDATE_ACTIVE_POS))
#define MXC_F_RTC_CTRL_CMPR1_CLR_ACTIVE_POS                 25
#define MXC_F_RTC_CTRL_CMPR1_CLR_ACTIVE                     ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_CMPR1_CLR_ACTIVE_POS))
#define MXC_F_RTC_CTRL_CMPR0_CLR_ACTIVE_POS                 26
#define MXC_F_RTC_CTRL_CMPR0_CLR_ACTIVE                     ((uint32_t)(0x00000001UL << MXC_F_RTC_CTRL_CMPR0_CLR_ACTIVE_POS))

#define MXC_F_RTC_FLAGS_COMP0_POS                           0
#define MXC_F_RTC_FLAGS_COMP0                               ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_COMP0_POS))
#define MXC_F_RTC_FLAGS_COMP1_POS                           1
#define MXC_F_RTC_FLAGS_COMP1                               ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_COMP1_POS))
#define MXC_F_RTC_FLAGS_PRESCALE_COMP_POS                   2
#define MXC_F_RTC_FLAGS_PRESCALE_COMP                       ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_PRESCALE_COMP_POS))
#define MXC_F_RTC_FLAGS_OVERFLOW_POS                        3
#define MXC_F_RTC_FLAGS_OVERFLOW                            ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_OVERFLOW_POS))
#define MXC_F_RTC_FLAGS_TRIM_POS                            4
#define MXC_F_RTC_FLAGS_TRIM                                ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_TRIM_POS))
#define MXC_F_RTC_FLAGS_COMP0_FLAG_A_POS                    8
#define MXC_F_RTC_FLAGS_COMP0_FLAG_A                        ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_COMP0_FLAG_A_POS))
#define MXC_F_RTC_FLAGS_COMP1_FLAG_A_POS                    9
#define MXC_F_RTC_FLAGS_COMP1_FLAG_A                        ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_COMP1_FLAG_A_POS))
#define MXC_F_RTC_FLAGS_PRESCL_FLAG_A_POS                   10
#define MXC_F_RTC_FLAGS_PRESCL_FLAG_A                       ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_PRESCL_FLAG_A_POS))
#define MXC_F_RTC_FLAGS_OVERFLOW_FLAG_A_POS                 11
#define MXC_F_RTC_FLAGS_OVERFLOW_FLAG_A                     ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_OVERFLOW_FLAG_A_POS))
#define MXC_F_RTC_FLAGS_TRIM_FLAG_A_POS                     12
#define MXC_F_RTC_FLAGS_TRIM_FLAG_A                         ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_TRIM_FLAG_A_POS))
#define MXC_F_RTC_FLAGS_ASYNC_CLR_FLAGS_POS                 31
#define MXC_F_RTC_FLAGS_ASYNC_CLR_FLAGS                     ((uint32_t)(0x00000001UL << MXC_F_RTC_FLAGS_ASYNC_CLR_FLAGS_POS))

#define MXC_F_RTC_INTEN_COMP0_POS                           0
#define MXC_F_RTC_INTEN_COMP0                               ((uint32_t)(0x00000001UL << MXC_F_RTC_INTEN_COMP0_POS))
#define MXC_F_RTC_INTEN_COMP1_POS                           1
#define MXC_F_RTC_INTEN_COMP1                               ((uint32_t)(0x00000001UL << MXC_F_RTC_INTEN_COMP1_POS))
#define MXC_F_RTC_INTEN_PRESCALE_COMP_POS                   2
#define MXC_F_RTC_INTEN_PRESCALE_COMP                       ((uint32_t)(0x00000001UL << MXC_F_RTC_INTEN_PRESCALE_COMP_POS))
#define MXC_F_RTC_INTEN_OVERFLOW_POS                        3
#define MXC_F_RTC_INTEN_OVERFLOW                            ((uint32_t)(0x00000001UL << MXC_F_RTC_INTEN_OVERFLOW_POS))
#define MXC_F_RTC_INTEN_TRIM_POS                            4
#define MXC_F_RTC_INTEN_TRIM                                ((uint32_t)(0x00000001UL << MXC_F_RTC_INTEN_TRIM_POS))

#define MXC_F_RTC_PRESCALE_WIDTH_SELECTION_POS              0
#define MXC_F_RTC_PRESCALE_WIDTH_SELECTION                  ((uint32_t)(0x0000000FUL << MXC_F_RTC_PRESCALE_WIDTH_SELECTION_POS))

#define MXC_F_RTC_PRESCALE_MASK_COMP_MASK_POS               0
#define MXC_F_RTC_PRESCALE_MASK_COMP_MASK                   ((uint32_t)(0x0000000FUL << MXC_F_RTC_PRESCALE_MASK_COMP_MASK_POS))

#define MXC_F_RTC_TRIM_CTRL_TRIM_ENABLE_R_POS               0
#define MXC_F_RTC_TRIM_CTRL_TRIM_ENABLE_R                   ((uint32_t)(0x00000001UL << MXC_F_RTC_TRIM_CTRL_TRIM_ENABLE_R_POS))
#define MXC_F_RTC_TRIM_CTRL_TRIM_FASTER_OVR_R_POS           1
#define MXC_F_RTC_TRIM_CTRL_TRIM_FASTER_OVR_R               ((uint32_t)(0x00000001UL << MXC_F_RTC_TRIM_CTRL_TRIM_FASTER_OVR_R_POS))
#define MXC_F_RTC_TRIM_CTRL_TRIM_SLOWER_R_POS               2
#define MXC_F_RTC_TRIM_CTRL_TRIM_SLOWER_R                   ((uint32_t)(0x00000001UL << MXC_F_RTC_TRIM_CTRL_TRIM_SLOWER_R_POS))

#define MXC_F_RTC_TRIM_VALUE_TRIM_VALUE_POS                 0
#define MXC_F_RTC_TRIM_VALUE_TRIM_VALUE                     ((uint32_t)(0x0003FFFFUL << MXC_F_RTC_TRIM_VALUE_TRIM_VALUE_POS))
#define MXC_F_RTC_TRIM_VALUE_TRIM_CONTROL_POS               18
#define MXC_F_RTC_TRIM_VALUE_TRIM_CONTROL                   ((uint32_t)(0x00000001UL << MXC_F_RTC_TRIM_VALUE_TRIM_CONTROL_POS))

#define MXC_F_RTC_NANO_CNTR_NANORING_COUNTER_POS            0
#define MXC_F_RTC_NANO_CNTR_NANORING_COUNTER                ((uint32_t)(0x0000FFFFUL << MXC_F_RTC_NANO_CNTR_NANORING_COUNTER_POS))

#define MXC_F_RTC_CLK_CTRL_OSC1_EN_POS                      0
#define MXC_F_RTC_CLK_CTRL_OSC1_EN                          ((uint32_t)(0x00000001UL << MXC_F_RTC_CLK_CTRL_OSC1_EN_POS))
#define MXC_F_RTC_CLK_CTRL_OSC2_EN_POS                      1
#define MXC_F_RTC_CLK_CTRL_OSC2_EN                          ((uint32_t)(0x00000001UL << MXC_F_RTC_CLK_CTRL_OSC2_EN_POS))
#define MXC_F_RTC_CLK_CTRL_NANO_EN_POS                      2
#define MXC_F_RTC_CLK_CTRL_NANO_EN                          ((uint32_t)(0x00000001UL << MXC_F_RTC_CLK_CTRL_NANO_EN_POS))

#define MXC_F_RTC_DSEN_CTRL_DSEN_DISABLE_POS                0
#define MXC_F_RTC_DSEN_CTRL_DSEN_DISABLE                    ((uint32_t)(0x00000001UL << MXC_F_RTC_DSEN_CTRL_DSEN_DISABLE_POS))

#define MXC_F_RTC_OSC_CTRL_OSC_BYPASS_POS                   0
#define MXC_F_RTC_OSC_CTRL_OSC_BYPASS                       ((uint32_t)(0x00000001UL << MXC_F_RTC_OSC_CTRL_OSC_BYPASS_POS))
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_R_POS                1
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_R                    ((uint32_t)(0x00000001UL << MXC_F_RTC_OSC_CTRL_OSC_DISABLE_R_POS))
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_SEL_POS              2
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_SEL                  ((uint32_t)(0x00000001UL << MXC_F_RTC_OSC_CTRL_OSC_DISABLE_SEL_POS))
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_O_POS                3
#define MXC_F_RTC_OSC_CTRL_OSC_DISABLE_O                    ((uint32_t)(0x00000001UL << MXC_F_RTC_OSC_CTRL_OSC_DISABLE_O_POS))

/*                                      Offset   Register Description
                                        ======   ===================================================================== */
typedef struct {
    __IO uint32_t nano_counter;     /*  0x0000   Nanoring Counter Read Register                                        */
    __IO uint32_t clk_ctrl;         /*  0x0004   RTC Clock Control Settings                                            */
    __IO uint32_t dsen_ctrl;        /*  0x0008   Dynamic Tamper Sensor Control                                         */
    __IO uint32_t osc_ctrl;         /*  0x000C   RTC Oscillator Control                                                */
} mxc_rtccfg_regs_t;

/*
   Register offsets for module RTCCFG.
*/
#define MXC_R_RTCCFG_OFFS_NANO_COUNTER            ((uint32_t)0x00000000UL)
#define MXC_R_RTCCFG_OFFS_CLK_CTRL                ((uint32_t)0x00000004UL)
#define MXC_R_RTCCFG_OFFS_DSEN_CTRL               ((uint32_t)0x00000008UL)
#define MXC_R_RTCCFG_OFFS_OSC_CTRL                ((uint32_t)0x0000000CUL)

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_RTC_REGS_H */
