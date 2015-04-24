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

#ifndef _MXC_DAC_REGS_H
#define _MXC_DAC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  dac_regs.h
 * @addtogroup dac DAC
 * @{
 */

/**
 * @brief Defines the DAC Operational Modes.
 */
typedef enum {
    /** DAC OpMode FIFO */
    MXC_E_DAC_OP_MODE_FIFO = 0,
    /** DAC OpMode Sample Count */
    MXC_E_DAC_OP_MODE_DACSMPLCNT,
    /** DAC OpMode DAC_REG Control */
    MXC_E_DAC_OP_MODE_DAC_REG,
    /** DAC OpMode Continuous */
    MXC_E_DAC_OP_MODE_CONTINUOUS
} mxc_dac_op_mode_t;

/**
 * @brief Defines the DAC Interpolation Options.
 */
typedef enum {
    /** DAC Interpolation is Disabled */
    MXC_E_DAC_INTERP_MODE_DISABLED = 0,
    /** DAC Interpolation 2:1 */
    MXC_E_DAC_INTERP_MODE_2_TO_1,
    /** DAC Interpolation 4:1 */
    MXC_E_DAC_INTERP_MODE_4_TO_1,
    /** DAC Interpolation 8:1 */
    MXC_E_DAC_INTERP_MODE_8_TO_1
} mxc_dac_interp_mode_t;

/**
 * @brief Defines the DAC Start Modes.
 */
typedef enum {
    /** Start on FIFO Not Empty */
    MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY = 0,
    /** Start on ADC generated Start Strobe */
    MXC_E_DAC_START_MODE_ADC_STROBE,
    /** Start on DAC generated Start Strobe */
    MXC_E_DAC_START_MODE_DAC_STROBE
} mxc_dac_start_mode_t;

/*                                                  Offset   Register Description
                                                    ======   ================================================== */
typedef struct {
    __IO uint32_t ctrl0;                        /*  0x0000   DAC Control Register 0                             */
    __IO uint32_t rate;                         /*  0x0004   DAC Output Rate Control                            */
    __IO uint32_t ctrl1_int;                    /*  0x0008   DAC Control Register 1, Interrupt Flags and Enable */
    __IO uint32_t reg;                          /*  0x000C   DAC Data Register                                  */
    __IO uint32_t trm;                          /*  0x0010   DAC Trim Register */
} mxc_dac_regs_t;

/*                                                  Offset   Register Description
                                                    ======   ================================================== */
typedef struct {
    union {
        __IO uint8_t output_8;                  /*  0x0000   Write to push values to DAC output FIFO            */
        __IO uint16_t output_16;                /*  0x0000   Write to push values to DAC output FIFO            */
    };
} mxc_dac_fifo_t;

/*
   Register offsets for module DAC12.
*/
#define MXC_R_DAC_OFFS_CTRL0                    ((uint32_t)0x00000000UL)
#define MXC_R_DAC_OFFS_RATE                     ((uint32_t)0x00000004UL)
#define MXC_R_DAC_OFFS_CTRL1_INT                ((uint32_t)0x00000008UL)
#define MXC_R_DAC_FIFO_OFFS_OUTPUT              ((uint32_t)0x00000000UL)

/*
   Field positions and masks for module DAC.
*/
#define MXC_F_DAC_CTRL0_FIFO_AE_CNT_POS         0
#define MXC_F_DAC_CTRL0_FIFO_AE_CNT             ((uint32_t)(0x0000000FUL << MXC_F_DAC_CTRL0_FIFO_AE_CNT_POS))
#define MXC_F_DAC_CTRL0_FIFO_ALMOST_FULL_POS    5
#define MXC_F_DAC_CTRL0_FIFO_ALMOST_FULL        ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_FIFO_ALMOST_FULL_POS))
#define MXC_F_DAC_CTRL0_FIFO_EMPTY_POS          6
#define MXC_F_DAC_CTRL0_FIFO_EMPTY              ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_FIFO_EMPTY_POS))
#define MXC_F_DAC_CTRL0_FIFO_ALMOST_EMPTY_POS   7
#define MXC_F_DAC_CTRL0_FIFO_ALMOST_EMPTY       ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_FIFO_ALMOST_EMPTY_POS))
#define MXC_F_DAC_CTRL0_INTERP_MODE_POS         8
#define MXC_F_DAC_CTRL0_INTERP_MODE             ((uint32_t)(0x00000007UL << MXC_F_DAC_CTRL0_INTERP_MODE_POS))
#define MXC_F_DAC_CTRL0_FIFO_AF_CNT_POS         12
#define MXC_F_DAC_CTRL0_FIFO_AF_CNT             ((uint32_t)(0x0000000FUL << MXC_F_DAC_CTRL0_FIFO_AF_CNT_POS))
#define MXC_F_DAC_CTRL0_START_MODE_POS          16
#define MXC_F_DAC_CTRL0_START_MODE              ((uint32_t)(0x00000003UL << MXC_F_DAC_CTRL0_START_MODE_POS))
#define MXC_F_DAC_CTRL0_CPU_START_POS           20
#define MXC_F_DAC_CTRL0_CPU_START               ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_CPU_START_POS))
#define MXC_F_DAC_CTRL0_OP_MODE_POS             24
#define MXC_F_DAC_CTRL0_OP_MODE                 ((uint32_t)(0x00000003UL << MXC_F_DAC_CTRL0_OP_MODE_POS))
#define MXC_F_DAC_CTRL0_POWER_MODE_1_0_POS      26
#define MXC_F_DAC_CTRL0_POWER_MODE_1_0          ((uint32_t)(0x00000003UL << MXC_F_DAC_CTRL0_POWER_MODE_1_0_POS))
#define MXC_F_DAC_CTRL0_POWER_ON_POS            28
#define MXC_F_DAC_CTRL0_POWER_ON                ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_POWER_ON_POS))
#define MXC_F_DAC_CTRL0_CLOCK_GATE_EN_POS       29
#define MXC_F_DAC_CTRL0_CLOCK_GATE_EN           ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_CLOCK_GATE_EN_POS))
#define MXC_F_DAC_CTRL0_POWER_MODE_2_POS        30
#define MXC_F_DAC_CTRL0_POWER_MODE_2            ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_POWER_MODE_2_POS))
#define MXC_F_DAC_CTRL0_RESET_POS               31
#define MXC_F_DAC_CTRL0_RESET                   ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL0_RESET_POS))

#define MXC_F_DAC_RATE_RATE_CNT_POS             0
#define MXC_F_DAC_RATE_RATE_CNT                 ((uint32_t)(0x0000FFFFUL << MXC_F_DAC_RATE_RATE_CNT_POS))
#define MXC_F_DAC_RATE_SAMPLE_CNT_POS           16
#define MXC_F_DAC_RATE_SAMPLE_CNT               ((uint32_t)(0x0000FFFFUL << MXC_F_DAC_RATE_SAMPLE_CNT_POS))

#define MXC_F_DAC_CTRL1_INT_OUT_DONE_IF_POS     0
#define MXC_F_DAC_CTRL1_INT_OUT_DONE_IF         ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_OUT_DONE_IF_POS))
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW_IF_POS    1
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW_IF        ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_UNDERFLOW_IF_POS))
#define MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IF_POS 2
#define MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IF     ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IF_POS))
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW_POS       3
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW           ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_UNDERFLOW_POS))
#define MXC_F_DAC_CTRL1_INT_OUT_DONE_IE_POS     16
#define MXC_F_DAC_CTRL1_INT_OUT_DONE_IE         ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_OUT_DONE_IE_POS))
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW_IE_POS    17
#define MXC_F_DAC_CTRL1_INT_UNDERFLOW_IE        ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_UNDERFLOW_IE_POS))
#define MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IE_POS 18
#define MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IE     ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_ALMOST_EMPTY_IE_POS))
#define MXC_F_DAC_CTRL1_INT_AHB_CG_DISABLE_POS  28
#define MXC_F_DAC_CTRL1_INT_AHB_CG_DISABLE      ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_AHB_CG_DISABLE_POS))
#define MXC_F_DAC_CTRL1_INT_APB_CG_DISABLE_POS  29
#define MXC_F_DAC_CTRL1_INT_APB_CG_DISABLE      ((uint32_t)(0x00000001UL << MXC_F_DAC_CTRL1_INT_APB_CG_DISABLE_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _DAC12_REGS_H */
