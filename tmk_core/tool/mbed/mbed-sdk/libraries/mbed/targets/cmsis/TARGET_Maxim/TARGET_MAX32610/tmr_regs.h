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

#ifndef _MXC_TMR_REGS_H
#define _MXC_TMR_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  tmr_regs.h
 * @addtogroup tmr TMR
 * @{
 */

/**
 * @brief Defines timer modes for 16 and 32-bit timers
 */
typedef enum {
    /** 32-bit or 16-bit timer one-shot mode */
    MXC_E_TMR_MODE_ONE_SHOT = 0,
    /** 32-bit or 16-bit timer one-shot mode */
    MXC_E_TMR_MODE_CONTINUOUS,
    /** 32-bit timer counter mode */
    MXC_E_TMR_MODE_COUNTER,
    /** 32-bit timer pulse width modulation mode */
    MXC_E_TMR_MODE_PWM,
    /** 32-bit timer capture mode */
    MXC_E_TMR_MODE_CAPTURE,
    /** 32-bit timer compare mode */
    MXC_E_TMR_MODE_COMPARE,
    /** 32-bit timer gated mode */
    MXC_E_TMR_MODE_GATED,
    /** 32-bit timer measure mode */
    MXC_E_TMR_MODE_MEASURE
} mxc_tmr_mode_t;

/*                                          Offset   Register Description
                                            ======   ============================================== */
typedef struct {
    __IO uint32_t ctrl;                 /*  0x0000   Timer Control Register                         */
    __IO uint32_t count32;              /*  0x0004   [32 bit] Current Count Value                   */
    __IO uint32_t term_cnt32;           /*  0x0008   [32 bit] Terminal Count Setting                */
    __IO uint32_t pwm_cap32;            /*  0x000C   [32 bit] PWM Compare Setting or Capture/Measure Value */
    __IO uint32_t count16_0;            /*  0x0010   [16 bit] Current Count Value, 16-bit Timer0    */
    __IO uint32_t term_cnt16_0;         /*  0x0014   [16 bit] Terminal Count Setting, 16-bit Timer0 */
    __IO uint32_t count16_1;            /*  0x0018   [16 bit] Current Count Value, 16-bit Timer1    */
    __IO uint32_t term_cnt16_1;         /*  0x001C   [16 bit] Terminal Count Setting, 16-bit Timer1 */
    __IO uint32_t intfl;                /*  0x0020   Timer Module Interrupt Flags                   */
    __IO uint32_t inten;                /*  0x0024   Timer Module Interrupt Enable/Disable Settings */
} mxc_tmr_regs_t;

/*
   Register offsets for module TMR.
*/
#define MXC_R_TMR_OFFS_CTRL                       ((uint32_t)0x00000000UL)
#define MXC_R_TMR_OFFS_COUNT32                    ((uint32_t)0x00000004UL)
#define MXC_R_TMR_OFFS_TERM_CNT32                 ((uint32_t)0x00000008UL)
#define MXC_R_TMR_OFFS_PWM_CAP32                  ((uint32_t)0x0000000CUL)
#define MXC_R_TMR_OFFS_COUNT16_0                  ((uint32_t)0x00000010UL)
#define MXC_R_TMR_OFFS_TERM_CNT16_0               ((uint32_t)0x00000014UL)
#define MXC_R_TMR_OFFS_COUNT16_1                  ((uint32_t)0x00000018UL)
#define MXC_R_TMR_OFFS_TERM_CNT16_1               ((uint32_t)0x0000001CUL)
#define MXC_R_TMR_OFFS_INTFL                      ((uint32_t)0x00000020UL)
#define MXC_R_TMR_OFFS_INTEN                      ((uint32_t)0x00000024UL)

/*
   Field positions and masks for module TMR.
*/
#define MXC_F_TMR_CTRL_MODE_POS                             0
#define MXC_F_TMR_CTRL_MODE                                 ((uint32_t)(0x00000007UL << MXC_F_TMR_CTRL_MODE_POS))
#define MXC_F_TMR_CTRL_TMR2X16_POS                          3
#define MXC_F_TMR_CTRL_TMR2X16                              ((uint32_t)(0x00000001UL << MXC_F_TMR_CTRL_TMR2X16_POS))
#define MXC_F_TMR_CTRL_PRESCALE_POS                         4
#define MXC_F_TMR_CTRL_PRESCALE                             ((uint32_t)(0x0000000FUL << MXC_F_TMR_CTRL_PRESCALE_POS))
#define MXC_F_TMR_CTRL_POLARITY_POS                         8
#define MXC_F_TMR_CTRL_POLARITY                             ((uint32_t)(0x00000001UL << MXC_F_TMR_CTRL_POLARITY_POS))
#define MXC_F_TMR_CTRL_ENABLE0_POS                          12
#define MXC_F_TMR_CTRL_ENABLE0                              ((uint32_t)(0x00000001UL << MXC_F_TMR_CTRL_ENABLE0_POS))
#define MXC_F_TMR_CTRL_ENABLE1_POS                          13
#define MXC_F_TMR_CTRL_ENABLE1                              ((uint32_t)(0x00000001UL << MXC_F_TMR_CTRL_ENABLE1_POS))

#define MXC_F_TMR_COUNT16_0_VALUE_POS                       0
#define MXC_F_TMR_COUNT16_0_VALUE                           ((uint32_t)(0x0000FFFFUL << MXC_F_TMR_COUNT16_0_VALUE_POS))

#define MXC_F_TMR_TERM_CNT16_0_TERM_COUNT_POS               0
#define MXC_F_TMR_TERM_CNT16_0_TERM_COUNT                   ((uint32_t)(0x0000FFFFUL << MXC_F_TMR_TERM_CNT16_0_TERM_COUNT_POS))

#define MXC_F_TMR_COUNT16_1_VALUE_POS                       0
#define MXC_F_TMR_COUNT16_1_VALUE                           ((uint32_t)(0x0000FFFFUL << MXC_F_TMR_COUNT16_1_VALUE_POS))

#define MXC_F_TMR_TERM_CNT16_1_TERM_COUNT_POS               0
#define MXC_F_TMR_TERM_CNT16_1_TERM_COUNT                   ((uint32_t)(0x0000FFFFUL << MXC_F_TMR_TERM_CNT16_1_TERM_COUNT_POS))

#define MXC_F_TMR_INTFL_TIMER0_POS                          0
#define MXC_F_TMR_INTFL_TIMER0                              ((uint32_t)(0x00000001UL << MXC_F_TMR_INTFL_TIMER0_POS))
#define MXC_F_TMR_INTFL_TIMER1_POS                          1
#define MXC_F_TMR_INTFL_TIMER1                              ((uint32_t)(0x00000001UL << MXC_F_TMR_INTFL_TIMER1_POS))

#define MXC_F_TMR_INTEN_TIMER0_POS                          0
#define MXC_F_TMR_INTEN_TIMER0                              ((uint32_t)(0x00000001UL << MXC_F_TMR_INTEN_TIMER0_POS))
#define MXC_F_TMR_INTEN_TIMER1_POS                          1
#define MXC_F_TMR_INTEN_TIMER1                              ((uint32_t)(0x00000001UL << MXC_F_TMR_INTEN_TIMER1_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_TMR_REGS_H */
