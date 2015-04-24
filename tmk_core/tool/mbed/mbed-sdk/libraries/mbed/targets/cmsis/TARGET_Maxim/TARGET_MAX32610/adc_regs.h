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

#ifndef _MXC_ADC_REGS_H
#define _MXC_ADC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  adc_regs.h
 * @addtogroup adc ADC
 * @{
 */

/**
 * @brief Defines ADC Modes.
 */
typedef enum {
    /** Single Mode Full Rate */
    MXC_E_ADC_MODE_SMPLCNT_FULL_RATE = 0,
    /** Single Mode Low Power */
    MXC_E_ADC_MODE_SMPLCNT_LOW_POWER = 1,
    /** Continuous Mode Full Rate */
    MXC_E_ADC_MODE_CONTINUOUS_FULL_RATE = 2,
    /** Continuous Mode Low Power */
    MXC_E_ADC_MODE_CONTINUOUS_LOW_POWER = 3,
    /** Single Mode Full Rate with Scan Enabled */
    MXC_E_ADC_MODE_SMPLCNT_SCAN_FULL_RATE = 8,
    /** Single Mode Low Power with Scan Enabled */
    MXC_E_ADC_MODE_SMPLCNT_SCAN_LOW_POWER = 9,
    /** Continuous Mode Full Rate with Scan Enabled */
    MXC_E_ADC_MODE_CONTINUOUS_SCAN_FULL_RATE = 10,
    /** Continuous Mode Low Power with Scan Enabled */
    MXC_E_ADC_MODE_CONTINUOUS_SCAN_LOW_POWER = 11
} mxc_adc_mode_t;

/**
 * @brief Defines ADC Range Control.
 */
typedef enum {
    /** Bi-polar Operation (-Vref/2 -> Vref/2) */
    MXC_E_ADC_RANGE_HALF = 0,
    /** Bi-polar Operation (-Vref -> Vref) */
    MXC_E_ADC_RANGE_FULL
} mxc_adc_range_t;

/**
 * @brief Defines ADC Bipolar operation.
 */
typedef enum {
    /** Uni-polar operation (0 -> Vref) */
    MXC_E_ADC_BI_POL_UNIPOLAR = 0,
    /** Bi-polar operation see ADC Range Control */
    MXC_E_ADC_BI_POL_BIPOLAR
} mxc_adc_bi_pol_t;

/**
 * @brief Defines Decimation Filter Modes.
 */
typedef enum {
    /** Decimation Filter ByPassed */
    MXC_E_ADC_AVG_MODE_FILTER_BYPASS = 0,
    /** Output Average Only*/
    MXC_E_ADC_AVG_MODE_FILTER_OUTPUT,
    /** Output Average and Raw Data (Test Mode Only) */
    MXC_E_ADC_AVG_MODE_FILTER_OUTPUT_RAW
} mxc_adc_avg_mode_t;

/**
 * @brief Defines ADC StartMode Modes.
 */
typedef enum {
    /** StarMode via Software */
    MXC_E_ADC_STRT_MODE_SOFTWARE = 0,
    /** StarMode via PulseTrain */
    MXC_E_ADC_STRT_MODE_PULSETRAIN
} mxc_adc_strt_mode_t;

/**
 * @brief Defines Mux Channel Select for the Positive Input to the ADC.
 */
typedef enum {
    /** Single Mode Input AIN0+; Diff Mode AIN0+/AIN8-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN0 = 0,
    /** Single Mode Input AIN1+; Diff Mode AIN1+/AIN9-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN1 = 1,
    /** Single Mode Input AIN2+; Diff Mode AIN2+/AIN10- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN2 = 2,
    /** Single Mode Input AIN3+; Diff Mode AIN3+/AIN11- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN3 = 3,
    /** Single Mode Input AIN4+; Diff Mode AIN4+/AIN12- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN4 = 4,
    /** Single Mode Input AIN5+; Diff Mode AIN5+/AIN13-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN5 = 5,
    /** Single Mode Input AIN6+; Diff Mode AIN6+/AIN14-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN6 = 6,
    /** Single Mode Input AIN7+; Diff Mode AIN7+/AIN15-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN7 = 7,
    /** Single Mode Input AIN8+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN8 = 8,
    /** Single Mode Input AIN9+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN9 = 9,
    /** Single Mode Input AIN10+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN10 = 10,
    /** Single Mode Input AIN11+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN11 = 11,
    /** Single Mode Input AIN12+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN12 = 12,
    /** Single Mode Input AIN13+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN13 = 13,
    /** Single Mode Input AIN14+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN14 = 14,
    /** Single Mode Input AIN15+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN15 = 15,
    /** Positive Input VSSADC */
    MXC_E_ADC_PGA_MUX_CH_SEL_VSSADC = 16,
    /** Positive Input TMON_R */
    MXC_E_ADC_PGA_MUX_CH_SEL_TMON_R = 17,
    /** Positive Input VDDA/4 */
    MXC_E_ADC_PGA_MUX_CH_SEL_VDDA4 = 18,
    /** Positive Input PWRMAN_TST */
    MXC_E_ADC_PGA_MUX_CH_SEL_PWRMON_TST = 19,
    /** Positive Input Ain0Div */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN0DIV = 20,
    /** Positive Input OpAmp OUTA */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTA = 32,
    /** Positive Input OpAmp OUTB */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTB = 33,
    /** Positive Input OpAmp OUTC */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTC = 34,
    /** Positive Input OpAmp OUTD */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTD = 35,
    /** Positive INA+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_INAPLUS = 36,
    /** Positive SNO_or */
    MXC_E_ADC_PGA_MUX_CH_SEL_SNO_OR = 37,
    /** Positive SCM_or */
    MXC_E_ADC_PGA_MUX_CH_SEL_SCM_OR = 38,
    /** Positive TPROBE_sense */
    MXC_E_ADC_PGA_MUX_CH_SEL_TPROBE_SENSE = 48,
    /** Positive VREFDAC */
    MXC_E_ADC_PGA_MUX_CH_SEL_VREFDAC = 49,
    /** Positive VREFADJ */
    MXC_E_ADC_PGA_MUX_CH_SEL_VREFADJ = 50,
    /** Positive Vdd3xtal */
    MXC_E_ADC_PGA_MUX_CH_SEL_VDD3XTAL = 51
} mxc_adc_pga_mux_ch_sel_t;

/**
 * @brief Decoded with the MUX Channel Select to enable Differential Mode Input to the ADC.
 */
typedef enum {
    /** Differential Mode Disabled */
    MXC_E_ADC_PGA_MUX_DIFF_DISABLE = 0,
    /** Differential Mode Enabled */
    MXC_E_ADC_PGA_MUX_DIFF_ENABLE
} mxc_adc_pga_mux_diff_t;

/**
 * @brief Defines the PGA Gain Options.
 */
typedef enum {
    /** PGA Gain = 1 */
    MXC_E_ADC_PGA_GAIN_1 = 0,
    /** PGA Gain = 2 */
    MXC_E_ADC_PGA_GAIN_2,
    /** PGA Gain = 4 */
    MXC_E_ADC_PGA_GAIN_4,
    /** PGA Gain = 8 */
    MXC_E_ADC_PGA_GAIN_8,
} mxc_adc_pga_gain_t;

/**
 * @brief Defines the Switch Control Mode.
 */
typedef enum {
    /** Switch Control Mode = Software */
    MXC_E_ADC_SPST_SW_CTRL_SOFTWARE = 0,
    /** Switch Control Mode = Pulse Train */
    MXC_E_ADC_SPST_SW_CTRL_PULSETRAIN
} mxc_adc_spst_sw_ctrl_t;

/**
 * @brief Defines the number of channels to scan when Scan Mode is enabled.
 */
typedef enum {
    /** Number of Channels to Scan = 1 */
    MXC_E_ADC_SCAN_CNT_1 = 0,
    /** Number of Channels to Scan = 2 */
    MXC_E_ADC_SCAN_CNT_2,
    /** Number of Channels to Scan = 3 */
    MXC_E_ADC_SCAN_CNT_3,
    /** Number of Channels to Scan = 4 */
    MXC_E_ADC_SCAN_CNT_4,
    /** Number of Channels to Scan = 5 */
    MXC_E_ADC_SCAN_CNT_5,
    /** Number of Channels to Scan = 6 */
    MXC_E_ADC_SCAN_CNT_6,
    /** Number of Channels to Scan = 7 */
    MXC_E_ADC_SCAN_CNT_7,
    /** Number of Channels to Scan = 8 */
    MXC_E_ADC_SCAN_CNT_8,
} mxc_adc_scan_cnt_t;

/*                                              Offset   Register Description
                                                ======   =================================================== */
typedef struct {
    __IO uint32_t ctrl0;                    /*  0x0000   ADC Control Register 0                              */
    __IO uint32_t pga_ctrl;                 /*  0x0004   PGA Control Register                                */
    __IO uint32_t tg_ctrl0;                 /*  0x0008   ADC Timing Generator Control 0                      */
    __IO uint32_t tg_ctrl1;                 /*  0x000C   ADC Timing Generator Control 1                      */
    __IO uint32_t limit;                    /*  0x0010   ADC Limit Settings                                  */
    __IO uint32_t intr;                     /*  0x0014   ADC Interrupt Flags and Enable/Disable Controls     */
    __IO uint32_t out;                      /*  0x0018   ADC Output Register                                 */
} mxc_adc_regs_t;

/*                                              Offset   Register Description
                                                ======   =================================================== */
typedef struct {
    __IO uint32_t ctrl1;                    /*  0x0000   ADC Control Register 1                              */
    __IO uint32_t scan1;                    /*  0x0004   ADC Auto-Scan Settings 1                            */
    __IO uint32_t scan2;                    /*  0x0008   ADC Auto-Scan Settings 2                            */
    __IO uint32_t ro_cal0;                  /*  0x000C   ADC Ring Osc Calibration 0                          */
    __IO uint32_t ro_cal1;                  /*  0x0010   ADC Ring Osc Calibration 1                          */
} mxc_adccfg_regs_t;

typedef struct {
    __IO uint16_t data;                     /*  0x0000   Read to pull sample data from ADC FIFO              */
} mxc_adc_fifo_regs_t;

/*
   Register offsets for module ADC, ADCCFG, ADC_FIFO
*/
#define MXC_R_ADC_OFFS_CTRL0                      ((uint32_t)0x00000000UL)
#define MXC_R_ADC_OFFS_PGA_CTRL                   ((uint32_t)0x00000004UL)
#define MXC_R_ADC_OFFS_TG_CTRL0                   ((uint32_t)0x00000008UL)
#define MXC_R_ADC_OFFS_TG_CTRL1                   ((uint32_t)0x0000000CUL)
#define MXC_R_ADC_OFFS_LIMIT                      ((uint32_t)0x00000010UL)
#define MXC_R_ADC_OFFS_INTR                       ((uint32_t)0x00000014UL)
#define MXC_R_ADC_OFFS_OUT                        ((uint32_t)0x00000018UL)

#define MXC_R_ADCCFG_OFFS_CTRL1                   ((uint32_t)0x00000000UL)
#define MXC_R_ADCCFG_OFFS_SCAN1                   ((uint32_t)0x00000004UL)
#define MXC_R_ADCCFG_OFFS_SCAN2                   ((uint32_t)0x00000008UL)
#define MXC_R_ADCCFG_OFFS_RO_CAL0                 ((uint32_t)0x0000000CUL)
#define MXC_R_ADCCFG_OFFS_RO_CAL1                 ((uint32_t)0x00000010UL)
#define MXC_R_ADC_FIFO_OFFS_DATA                  ((uint32_t)0x00000000UL)

/*
   Field positions and masks for module ADC.
*/
#define MXC_F_ADC_CTRL0_ADC_WAKE_CNT_POS                    0
#define MXC_F_ADC_CTRL0_ADC_WAKE_CNT                        ((uint32_t)(0x0000000FUL << MXC_F_ADC_CTRL0_ADC_WAKE_CNT_POS))
#define MXC_F_ADC_CTRL0_ADC_STRT_MODE_POS                   5
#define MXC_F_ADC_CTRL0_ADC_STRT_MODE                       ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_STRT_MODE_POS))
#define MXC_F_ADC_CTRL0_ADC_RANGE_POS                       6
#define MXC_F_ADC_CTRL0_ADC_RANGE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_RANGE_POS))
#define MXC_F_ADC_CTRL0_ADC_BI_POL_POS                      7
#define MXC_F_ADC_CTRL0_ADC_BI_POL                          ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_BI_POL_POS))
#define MXC_F_ADC_CTRL0_ADC_DV_REG_POS                      8
#define MXC_F_ADC_CTRL0_ADC_DV_REG                          ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_DV_REG_POS))
#define MXC_F_ADC_CTRL0_ADC_DV_POS                          9
#define MXC_F_ADC_CTRL0_ADC_DV                              ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_DV_POS))
#define MXC_F_ADC_CTRL0_ADC_LMT_DMODE_POS                   10
#define MXC_F_ADC_CTRL0_ADC_LMT_DMODE                       ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_LMT_DMODE_POS))
#define MXC_F_ADC_CTRL0_ADC_SMP_EXT_POS                     11
#define MXC_F_ADC_CTRL0_ADC_SMP_EXT                         ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_SMP_EXT_POS))
#define MXC_F_ADC_CTRL0_ADC_CLK_EN_POS                      12
#define MXC_F_ADC_CTRL0_ADC_CLK_EN                          ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_CLK_EN_POS))
#define MXC_F_ADC_CTRL0_CPU_ADC_RST_POS                     13
#define MXC_F_ADC_CTRL0_CPU_ADC_RST                         ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_CPU_ADC_RST_POS))
#define MXC_F_ADC_CTRL0_CPU_ADC_START_POS                   14
#define MXC_F_ADC_CTRL0_CPU_ADC_START                       ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_CPU_ADC_START_POS))
#define MXC_F_ADC_CTRL0_CPU_ADC_EN_POS                      15
#define MXC_F_ADC_CTRL0_CPU_ADC_EN                          ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_CPU_ADC_EN_POS))
#define MXC_F_ADC_CTRL0_ADC_FIFO_FULL_POS                   18
#define MXC_F_ADC_CTRL0_ADC_FIFO_FULL                       ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_FIFO_FULL_POS))
#define MXC_F_ADC_CTRL0_ADC_FIFO_EMPTY_POS                  19
#define MXC_F_ADC_CTRL0_ADC_FIFO_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_ADC_FIFO_EMPTY_POS))
#define MXC_F_ADC_CTRL0_AVG_MODE_POS                        20
#define MXC_F_ADC_CTRL0_AVG_MODE                            ((uint32_t)(0x00000003UL << MXC_F_ADC_CTRL0_AVG_MODE_POS))
#define MXC_F_ADC_CTRL0_CPU_DAC_START_POS                   22
#define MXC_F_ADC_CTRL0_CPU_DAC_START                       ((uint32_t)(0x00000001UL << MXC_F_ADC_CTRL0_CPU_DAC_START_POS))
#define MXC_F_ADC_CTRL0_ADC_CLK_MODE_POS                    24
#define MXC_F_ADC_CTRL0_ADC_CLK_MODE                        ((uint32_t)(0x00000007UL << MXC_F_ADC_CTRL0_ADC_CLK_MODE_POS))
#define MXC_F_ADC_CTRL0_ADC_MODE_POS                        28
#define MXC_F_ADC_CTRL0_ADC_MODE                            ((uint32_t)(0x0000000FUL << MXC_F_ADC_CTRL0_ADC_MODE_POS))

#define MXC_F_ADC_PGA_CTRL_PGA_GAIN_POS                     0
#define MXC_F_ADC_PGA_CTRL_PGA_GAIN                         ((uint32_t)(0x00000003UL << MXC_F_ADC_PGA_CTRL_PGA_GAIN_POS))
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_RST_CLK_EN_POS           2
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_RST_CLK_EN               ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_CPU_PGA_RST_CLK_EN_POS))
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_RST_POS                  3
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_RST                      ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_CPU_PGA_RST_POS))
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK_DELAY_POS            4
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK_DELAY                ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK_DELAY_POS))
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK_POS                  5
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK                      ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_CPU_PGA_TRK_POS))
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_BYPASS_POS               6
#define MXC_F_ADC_PGA_CTRL_CPU_PGA_BYPASS                   ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_CPU_PGA_BYPASS_POS))
#define MXC_F_ADC_PGA_CTRL_PGA_WAKE_CNT_POS                 8
#define MXC_F_ADC_PGA_CTRL_PGA_WAKE_CNT                     ((uint32_t)(0x0000001FUL << MXC_F_ADC_PGA_CTRL_PGA_WAKE_CNT_POS))
#define MXC_F_ADC_PGA_CTRL_MUX_SW_AIN_POS                   13
#define MXC_F_ADC_PGA_CTRL_MUX_SW_AIN                       ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_MUX_SW_AIN_POS))
#define MXC_F_ADC_PGA_CTRL_MUX_DIFF_POS                     14
#define MXC_F_ADC_PGA_CTRL_MUX_DIFF                         ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_MUX_DIFF_POS))
#define MXC_F_ADC_PGA_CTRL_MUX_MODE_POS                     15
#define MXC_F_ADC_PGA_CTRL_MUX_MODE                         ((uint32_t)(0x00000001UL << MXC_F_ADC_PGA_CTRL_MUX_MODE_POS))
#define MXC_F_ADC_PGA_CTRL_PGA_RST_CLK_CNT_POS              20
#define MXC_F_ADC_PGA_CTRL_PGA_RST_CLK_CNT                  ((uint32_t)(0x0000000FUL << MXC_F_ADC_PGA_CTRL_PGA_RST_CLK_CNT_POS))
#define MXC_F_ADC_PGA_CTRL_MUX_CH_SEL_POS                   24
#define MXC_F_ADC_PGA_CTRL_MUX_CH_SEL                       ((uint32_t)(0x0000003FUL << MXC_F_ADC_PGA_CTRL_MUX_CH_SEL_POS))

#define MXC_F_ADC_TG_CTRL0_PGA_TRK_CNT_POS                  0
#define MXC_F_ADC_TG_CTRL0_PGA_TRK_CNT                      ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_TG_CTRL0_PGA_TRK_CNT_POS))
#define MXC_F_ADC_TG_CTRL0_ADC_SMPL_CNT_POS                 16
#define MXC_F_ADC_TG_CTRL0_ADC_SMPL_CNT                     ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_TG_CTRL0_ADC_SMPL_CNT_POS))

#define MXC_F_ADC_TG_CTRL1_PGA_ACQ_CNT_POS                  0
#define MXC_F_ADC_TG_CTRL1_PGA_ACQ_CNT                      ((uint32_t)(0x0000000FUL << MXC_F_ADC_TG_CTRL1_PGA_ACQ_CNT_POS))
#define MXC_F_ADC_TG_CTRL1_FIFO_AF_CNT_POS                  4
#define MXC_F_ADC_TG_CTRL1_FIFO_AF_CNT                      ((uint32_t)(0x0000000FUL << MXC_F_ADC_TG_CTRL1_FIFO_AF_CNT_POS))
#define MXC_F_ADC_TG_CTRL1_ADC_BRST_CNT_POS                 8
#define MXC_F_ADC_TG_CTRL1_ADC_BRST_CNT                     ((uint32_t)(0x00000007UL << MXC_F_ADC_TG_CTRL1_ADC_BRST_CNT_POS))
#define MXC_F_ADC_TG_CTRL1_ADC_ACQ_CNT_POS                  12
#define MXC_F_ADC_TG_CTRL1_ADC_ACQ_CNT                      ((uint32_t)(0x0000000FUL << MXC_F_ADC_TG_CTRL1_ADC_ACQ_CNT_POS))
#define MXC_F_ADC_TG_CTRL1_ADC_SLP_CNT_POS                  16
#define MXC_F_ADC_TG_CTRL1_ADC_SLP_CNT                      ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_TG_CTRL1_ADC_SLP_CNT_POS))

#define MXC_F_ADC_LIMIT_LO_LIMIT_POS                        0
#define MXC_F_ADC_LIMIT_LO_LIMIT                            ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_LIMIT_LO_LIMIT_POS))
#define MXC_F_ADC_LIMIT_HI_LIMIT_POS                        16
#define MXC_F_ADC_LIMIT_HI_LIMIT                            ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_LIMIT_HI_LIMIT_POS))

#define MXC_F_ADC_INTR_FIFO_AF_POS                          6
#define MXC_F_ADC_INTR_FIFO_AF                              ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_AF_POS))
#define MXC_F_ADC_INTR_OUT_RNG_IF_POS                       7
#define MXC_F_ADC_INTR_OUT_RNG_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_OUT_RNG_IF_POS))
#define MXC_F_ADC_INTR_HI_RNG_IF_POS                        8
#define MXC_F_ADC_INTR_HI_RNG_IF                            ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_HI_RNG_IF_POS))
#define MXC_F_ADC_INTR_LO_RNG_IF_POS                        9
#define MXC_F_ADC_INTR_LO_RNG_IF                            ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_LO_RNG_IF_POS))
#define MXC_F_ADC_INTR_DONE_IF_POS                          10
#define MXC_F_ADC_INTR_DONE_IF                              ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_DONE_IF_POS))
#define MXC_F_ADC_INTR_FIFO_UF_IF_POS                       11
#define MXC_F_ADC_INTR_FIFO_UF_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_UF_IF_POS))
#define MXC_F_ADC_INTR_FIFO_OF_IF_POS                       12
#define MXC_F_ADC_INTR_FIFO_OF_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_OF_IF_POS))
#define MXC_F_ADC_INTR_FIFO_3Q_IF_POS                       13
#define MXC_F_ADC_INTR_FIFO_3Q_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_3Q_IF_POS))
#define MXC_F_ADC_INTR_FIFO_2Q_IF_POS                       14
#define MXC_F_ADC_INTR_FIFO_2Q_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_2Q_IF_POS))
#define MXC_F_ADC_INTR_FIFO_1Q_IF_POS                       15
#define MXC_F_ADC_INTR_FIFO_1Q_IF                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_1Q_IF_POS))
#define MXC_F_ADC_INTR_SPST0_CTRL_MODE_POS                  16
#define MXC_F_ADC_INTR_SPST0_CTRL_MODE                      ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_SPST0_CTRL_MODE_POS))
#define MXC_F_ADC_INTR_SPST1_CTRL_MODE_POS                  17
#define MXC_F_ADC_INTR_SPST1_CTRL_MODE                      ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_SPST1_CTRL_MODE_POS))
#define MXC_F_ADC_INTR_SPST2_CTRL_MODE_POS                  18
#define MXC_F_ADC_INTR_SPST2_CTRL_MODE                      ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_SPST2_CTRL_MODE_POS))
#define MXC_F_ADC_INTR_SPST3_CTRL_MODE_POS                  19
#define MXC_F_ADC_INTR_SPST3_CTRL_MODE                      ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_SPST3_CTRL_MODE_POS))
#define MXC_F_ADC_INTR_OUT_RNG_IE_POS                       23
#define MXC_F_ADC_INTR_OUT_RNG_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_OUT_RNG_IE_POS))
#define MXC_F_ADC_INTR_HI_RNG_IE_POS                        24
#define MXC_F_ADC_INTR_HI_RNG_IE                            ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_HI_RNG_IE_POS))
#define MXC_F_ADC_INTR_LO_RNG_IE_POS                        25
#define MXC_F_ADC_INTR_LO_RNG_IE                            ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_LO_RNG_IE_POS))
#define MXC_F_ADC_INTR_DONE_IE_POS                          26
#define MXC_F_ADC_INTR_DONE_IE                              ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_DONE_IE_POS))
#define MXC_F_ADC_INTR_FIFO_UF_IE_POS                       27
#define MXC_F_ADC_INTR_FIFO_UF_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_UF_IE_POS))
#define MXC_F_ADC_INTR_FIFO_OF_IE_POS                       28
#define MXC_F_ADC_INTR_FIFO_OF_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_OF_IE_POS))
#define MXC_F_ADC_INTR_FIFO_3Q_IE_POS                       29
#define MXC_F_ADC_INTR_FIFO_3Q_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_3Q_IE_POS))
#define MXC_F_ADC_INTR_FIFO_2Q_IE_POS                       30
#define MXC_F_ADC_INTR_FIFO_2Q_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_2Q_IE_POS))
#define MXC_F_ADC_INTR_FIFO_1Q_IE_POS                       31
#define MXC_F_ADC_INTR_FIFO_1Q_IE                           ((uint32_t)(0x00000001UL << MXC_F_ADC_INTR_FIFO_1Q_IE_POS))

#define MXC_F_ADC_OUT_DATA_REG_POS                          0
#define MXC_F_ADC_OUT_DATA_REG                              ((uint32_t)(0x0000FFFFUL << MXC_F_ADC_OUT_DATA_REG_POS))

#define MXC_F_ADC_CTRL1_ADC_SCAN_CNT_POS                    16
#define MXC_F_ADC_CTRL1_ADC_SCAN_CNT                        ((uint32_t)(0x00000007UL << MXC_F_ADC_CTRL1_ADC_SCAN_CNT_POS))

#define MXC_F_ADC_SCAN1_ADC_SCAN0_POS                       0
#define MXC_F_ADC_SCAN1_ADC_SCAN0                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN1_ADC_SCAN0_POS))
#define MXC_F_ADC_SCAN1_ADC_SCAN1_POS                       8
#define MXC_F_ADC_SCAN1_ADC_SCAN1                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN1_ADC_SCAN1_POS))
#define MXC_F_ADC_SCAN1_ADC_SCAN2_POS                       16
#define MXC_F_ADC_SCAN1_ADC_SCAN2                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN1_ADC_SCAN2_POS))
#define MXC_F_ADC_SCAN1_ADC_SCAN3_POS                       24
#define MXC_F_ADC_SCAN1_ADC_SCAN3                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN1_ADC_SCAN3_POS))

#define MXC_F_ADC_SCAN2_ADC_SCAN4_POS                       0
#define MXC_F_ADC_SCAN2_ADC_SCAN4                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN2_ADC_SCAN4_POS))
#define MXC_F_ADC_SCAN2_ADC_SCAN5_POS                       8
#define MXC_F_ADC_SCAN2_ADC_SCAN5                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN2_ADC_SCAN5_POS))
#define MXC_F_ADC_SCAN2_ADC_SCAN6_POS                       16
#define MXC_F_ADC_SCAN2_ADC_SCAN6                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN2_ADC_SCAN6_POS))
#define MXC_F_ADC_SCAN2_ADC_SCAN7_POS                       24
#define MXC_F_ADC_SCAN2_ADC_SCAN7                           ((uint32_t)(0x000000FFUL << MXC_F_ADC_SCAN2_ADC_SCAN7_POS))

#define MXC_F_ADC_RO_CAL0_RO_CAL_EN_POS                     0
#define MXC_F_ADC_RO_CAL0_RO_CAL_EN                         ((uint32_t)(0x00000001UL << MXC_F_ADC_RO_CAL0_RO_CAL_EN_POS))
#define MXC_F_ADC_RO_CAL0_RO_CAL_RUN_POS                    1
#define MXC_F_ADC_RO_CAL0_RO_CAL_RUN                        ((uint32_t)(0x00000001UL << MXC_F_ADC_RO_CAL0_RO_CAL_RUN_POS))
#define MXC_F_ADC_RO_CAL0_RO_CAL_LOAD_POS                   2
#define MXC_F_ADC_RO_CAL0_RO_CAL_LOAD                       ((uint32_t)(0x00000001UL << MXC_F_ADC_RO_CAL0_RO_CAL_LOAD_POS))
#define MXC_F_ADC_RO_CAL0_TRM_MU_POS                        8
#define MXC_F_ADC_RO_CAL0_TRM_MU                            ((uint32_t)(0x00000FFFUL << MXC_F_ADC_RO_CAL0_TRM_MU_POS))
#define MXC_F_ADC_RO_CAL0_RO_TRM_POS                        23
#define MXC_F_ADC_RO_CAL0_RO_TRM                            ((uint32_t)(0x000001FFUL << MXC_F_ADC_RO_CAL0_RO_TRM_POS))

#define MXC_F_ADC_RO_CAL1_TRM_INIT_POS                      0
#define MXC_F_ADC_RO_CAL1_TRM_INIT                          ((uint32_t)(0x000001FFUL << MXC_F_ADC_RO_CAL1_TRM_INIT_POS))
#define MXC_F_ADC_RO_CAL1_TRM_MIN_POS                       10
#define MXC_F_ADC_RO_CAL1_TRM_MIN                           ((uint32_t)(0x000001FFUL << MXC_F_ADC_RO_CAL1_TRM_MIN_POS))
#define MXC_F_ADC_RO_CAL1_TRM_MAX_POS                       20
#define MXC_F_ADC_RO_CAL1_TRM_MAX                           ((uint32_t)(0x000001FFUL << MXC_F_ADC_RO_CAL1_TRM_MAX_POS))

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _MXC_ADC_REGS_H */
