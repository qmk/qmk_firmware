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

#ifndef _MXC_AFE_REGS_H
#define _MXC_AFE_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  afe_regs.h
 * @addtogroup afe AFE
 * @{
 */

/**
 * @brief Defines Configure Options for the LED Ports.
 */
typedef enum {
    /** LED Sink Port 0 with OpAmp A, LED Sink Port 1 with OpAmp C */
    MXC_E_AFE_LED_CFG_PORT_OPAMP_A_C = 0,
    /** LED Sink Port 0 with OpAmp B, LED Sink Port 1 with OpAmp D */
    MXC_E_AFE_LED_CFG_PORT_OPAMP_B_D,
    /** Disable LED Sink Port 0,Disable LED Sink Port 1 */
    MXC_E_AFE_LED_CFG_PORT_DISABLED,
} mxc_afe_led_cfg_port_t;

/**
 * @brief Setup of Wake Up Detector for LPCs.
 */
typedef enum {
    /** IDLE */
    MXC_E_AFE_EN_WUD_COMP_IDLE = 0,
    /** Activate WUD for falling edges */
    MXC_E_AFE_EN_WUD_COMP_FALLING_EDGE = 2,
    /** Activate WUD for rising edges */
    MXC_E_AFE_EN_WUD_COMP_RISING_EDGE = 3
} mxc_afe_en_wud_comp_t;

/**
 * @brief LPC InMode.
 */
typedef enum {
    /** InMode: both Nch and Pch */
    MXC_E_AFE_IN_MODE_COMP_NCH_PCH = 0,
    /** InMode: only Nch  */
    MXC_E_AFE_IN_MODE_COMP_NCH,
    /** InMode: only Pch  */
    MXC_E_AFE_IN_MODE_COMP_PCH,
} mxc_afe_in_mode_comp_t;

/**
 * @brief LPC Bias.
 */
typedef enum {
    /** BIAS 0.52uA Delay 4.0us  */
    MXC_E_AFE_BIAS_MODE_COMP_0 = 0,
    /** BIAS 1.4uA Delay 1.7us  */
    MXC_E_AFE_BIAS_MODE_COMP_1,
    /** BIAS 2.8uA Delay 1.1us  */
    MXC_E_AFE_BIAS_MODE_COMP_2,
    /** BIAS 5.1uA Delay 0.7us  */
    MXC_E_AFE_BIAS_MODE_COMP_3
} mxc_afe_bias_mode_comp_t;

/**
 * @brief TMON Current Value.
 */
typedef enum {
    /** TMON Current 4uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_0 = 0,
    /** TMON Current 60uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_1,
    /** TMON Current 64uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_2,
    /** TMON Current 120uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_3
} mxc_afe_tmon_current_t;

/**
 * @brief REFADC and REFDAC Voltage Select.
 */
typedef enum {
    /** Voltage Reference = 1.024 V */
    MXC_E_AFE_REF_VOLT_SEL_1024 = 0,
    /** Voltage Reference = 1.5 V */
    MXC_E_AFE_REF_VOLT_SEL_1500,
    /** Voltage Reference = 2.048 V */
    MXC_E_AFE_REF_VOLT_SEL_2048,
    /** Voltage Reference = 2.5 V */
    MXC_E_AFE_REF_VOLT_SEL_2500
} mxc_afe_ref_volt_sel_t;

/**
 * @brief Selection for DAC VOltage Reference, REFADC or REFDAC.
 */
typedef enum {
    /** DAC Voltage Reference = REFADC */
    MXC_E_AFE_DAC_REF_REFADC = 0,
    /** DAC Voltage Reference = REFDAC */
    MXC_E_AFE_DAC_REF_REFDAC
} mxc_afe_dac_ref_t;

/**
 * @brief Selection for LPC Hysteresis.
 */
typedef enum {
    /** LPC Hysteresis = 0 mV */
    MXC_E_AFE_HYST_COMP_0 = 0,
    /** LPC Hysteresis = 7.5 mV */
    MXC_E_AFE_HYST_COMP_1,
    /** LPC Hysteresis = 15 mV */
    MXC_E_AFE_HYST_COMP_2,
    /** LPC Hysteresis = 30 mV */
    MXC_E_AFE_HYST_COMP_3
} mxc_afe_hyst_comp_t;

/**
 * @brief Selection for MUX for  SCM_or_sel.
 */
typedef enum {
    /** SCM_or = HIZ */
    MXC_E_AFE_SCM_OR_SEL_HIZ = 0,
    /** SCM_or = SCM0 */
    MXC_E_AFE_SCM_OR_SEL_SCM0,
    /** SCM_or = SCM1 */
    MXC_E_AFE_SCM_OR_SEL_SCM1,
    /** SCM_or = SCM2 */
    MXC_E_AFE_SCM_OR_SEL_SCM2,
    /** SCM_or = SCM3 */
    MXC_E_AFE_SCM_OR_SEL_SCM3
} mxc_afe_scm_or_sel_t;

/**
 * @brief Selection for MUX for  SNO_or_sel.
 */
typedef enum {
    /** SNO_or = HIZ */
    MXC_E_AFE_SNO_OR_SEL_HIZ = 0,
    /** SNO_or = SNO0 */
    MXC_E_AFE_SNO_OR_SEL_SNO0,
    /** SNO_or = SNO1 */
    MXC_E_AFE_SNO_OR_SEL_SNO1,
    /** SNO_or = SNO2 */
    MXC_E_AFE_SNO_OR_SEL_SNO2,
    /** SNO_or = SNO3 */
    MXC_E_AFE_SNO_OR_SEL_SNO3
} mxc_afe_sno_or_sel_t;

/**
 * @brief Selection for MUX  DACx_sel.
 */
typedef enum {
    /** dacx  = DACOP */
    MXC_E_AFE_DACX_SEL_P = 0,
    /** dacx  = DACON */
    MXC_E_AFE_DACX_SEL_N
} mxc_afe_dacx_sel_t;

/**
 * @brief Selection for state of Switch.
 */
typedef enum {
    /** Switch is OPEN */
    MXC_E_AFE_CLOSE_SPST_SWITCH_OPEN = 0,
    /** Switch is CLOSED */
    MXC_E_AFE_CLOSE_SPST_SWITCH_CLOSE
} mxc_afe_close_spst_t;

/**
 * @brief Switch to Connect Positive Pad to GND.
 */
typedef enum {
    /** Positive Pad GND Switch OPEN */
    MXC_E_AFE_GND_SEL_OPAMP_SWITCH_OPEN = 0,
    /** Positive Pad GND Switch CLOSED */
    MXC_E_AFE_GND_SEL_OPAMP_SWITCH_CLOSED
} mxc_afe_gnd_sel_opamp_t;

/**
 * @brief MUX Selection for OpPsel.
 */
typedef enum {
    /** OpPsel = INx+ */
    MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS = 0,
    /** OpPsel = DAC_or */
    MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR,
    /** OpPsel = SNO_or */
    MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR,
    /** OpPsel = DAC_or also output on INx+ */
    MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS
} mxc_afe_p_in_sel_opamp_t;

/**
 * @brief MUX Selection for OpNsel.
 */
typedef enum {
    /** OpNsel = INx- */
    MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS = 0,
    /** OpNsel = OUTx */
    MXC_E_AFE_N_IN_SEL_OPAMP_OUT,
    /** OpNsel = SCM_or */
    MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR,
    /**OpNsel = SCM_or also output on INx- */
    MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS,
} mxc_afe_n_in_sel_opamp_t;

/**
 * @brief MUX Selection for DAC_sel.
 */
typedef enum {
    /** DAC_or = DAC0 */
    MXC_E_AFE_DAC_SEL_DAC0 = 0,
    /** DAC_or = DAC1 */
    MXC_E_AFE_DAC_SEL_DAC1,
    /** DAC_or = DAC2P */
    MXC_E_AFE_DAC_SEL_DAC2P,
    /** DAC_or = DAC3P */
    MXC_E_AFE_DAC_SEL_DAC3P
} mxc_afe_dac_sel_t;

/**
 * @brief MUX Selection for NPAD_sel.
 */
typedef enum {
    /** NPAD_Sel = HIZ */
    MXC_E_AFE_NPAD_SEL_HIZ = 0,
    /** NPAD_Sel = LED Observe Port */
    MXC_E_AFE_NPAD_SEL_LED_OBS_PORT,
    /** NPAD_Sel = DAC_or */
    MXC_E_AFE_NPAD_SEL_DAC_OR,
    /** NPAD_Sel = DAC_or and LED Observe Port */
    MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT
} mxc_afe_npad_sel_t;

/**
 * @brief MUX Selection for CmpPSel.
 */
typedef enum {
    /** CmpPSel = INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_INPLUS = 0,
    /** CmpPSel = SCM */
    MXC_E_AFE_POS_IN_SEL_COMP_SCM,
    /** CmpPSel = dac1 */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1,
    /** CmpPSel = DAC3P */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC3P,
    /** CmpPSel = LED Observe Port */
    MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT,
    /** CmpPSel = dac1 also output on INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS,
    /** CmpPSel = DAC3P also output on INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS,
    /** CmpPSel = dac1 also output on SCM */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM
} mxc_afe_pos_in_sel_comp_t;

/**
 * @brief MUX Selection for CmpNSel.
 */
typedef enum {
    /** CmpNSel = INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS = 0,
    /** CmpNSel = SNO */
    MXC_E_AFE_NEG_IN_SEL_COMP_SNO,
    /** CmpNSel = dac0 */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC0,
    /** CmpNSel = DAC2P */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P,
    /** CmpNSel = LED Observation Port */
    MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT,
    /** CmpNSel = dac0 also output on INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS,
    /** CmpNSel = DAC2 also output on INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS,
    /** CmpNSel = DAC2 also output on SNO */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO
} mxc_afe_neg_in_sel_comp_t;

/*                                      Offset   Register Description
                                        ======   ==================================================== */
typedef struct {
    __IO uint32_t intr;             /*  0x0000   Analog Front End Interrupt Flags and Enable/Disable  */
    __IO uint32_t ctrl0;            /*  0x0004   Analog Front End Control 0                           */
    __IO uint32_t ctrl1;            /*  0x0008   Analog Front End Control 1                           */
    __IO uint32_t ctrl2;            /*  0x000C   Analog Front End Control 2                           */
    __IO uint32_t ctrl3;            /*  0x0010   Analog Front End Control 3                           */
    __IO uint32_t ctrl4;            /*  0x0014   Analog Front End Control 4                           */
    __IO uint32_t ctrl5;            /*  0x0018   Analog Front End Control 5                           */
} mxc_afe_regs_t;

/*
   Register offsets for module AFE.
*/
#define MXC_R_AFE_OFFS_INTR                   ((uint32_t)0x00000000UL)
#define MXC_R_AFE_OFFS_CTRL0                  ((uint32_t)0x00000004UL)
#define MXC_R_AFE_OFFS_CTRL1                  ((uint32_t)0x00000008UL)
#define MXC_R_AFE_OFFS_CTRL2                  ((uint32_t)0x0000000CUL)
#define MXC_R_AFE_OFFS_CTRL3                  ((uint32_t)0x00000010UL)
#define MXC_R_AFE_OFFS_CTRL4                  ((uint32_t)0x00000014UL)
#define MXC_R_AFE_OFFS_CTRL5                  ((uint32_t)0x00000018UL)

/*
   Field positions and masks for module AFE.
*/
#define MXC_F_AFE_INTR_OP_COMP0_IF_POS                      0
#define MXC_F_AFE_INTR_OP_COMP0_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP0_IF_POS))
#define MXC_F_AFE_INTR_OP_COMP1_IF_POS                      1
#define MXC_F_AFE_INTR_OP_COMP1_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP1_IF_POS))
#define MXC_F_AFE_INTR_OP_COMP2_IF_POS                      2
#define MXC_F_AFE_INTR_OP_COMP2_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP2_IF_POS))
#define MXC_F_AFE_INTR_OP_COMP3_IF_POS                      3
#define MXC_F_AFE_INTR_OP_COMP3_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP3_IF_POS))
#define MXC_F_AFE_INTR_LP_COMP0_IF_POS                      4
#define MXC_F_AFE_INTR_LP_COMP0_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP0_IF_POS))
#define MXC_F_AFE_INTR_LP_COMP1_IF_POS                      5
#define MXC_F_AFE_INTR_LP_COMP1_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP1_IF_POS))
#define MXC_F_AFE_INTR_LP_COMP2_IF_POS                      6
#define MXC_F_AFE_INTR_LP_COMP2_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP2_IF_POS))
#define MXC_F_AFE_INTR_LP_COMP3_IF_POS                      7
#define MXC_F_AFE_INTR_LP_COMP3_IF                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP3_IF_POS))
#define MXC_F_AFE_INTR_OP_COMP0_NMI_PMU_POS                 8
#define MXC_F_AFE_INTR_OP_COMP0_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP0_NMI_PMU_POS))
#define MXC_F_AFE_INTR_OP_COMP1_NMI_PMU_POS                 9
#define MXC_F_AFE_INTR_OP_COMP1_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP1_NMI_PMU_POS))
#define MXC_F_AFE_INTR_OP_COMP2_NMI_PMU_POS                 10
#define MXC_F_AFE_INTR_OP_COMP2_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP2_NMI_PMU_POS))
#define MXC_F_AFE_INTR_OP_COMP3_NMI_PMU_POS                 11
#define MXC_F_AFE_INTR_OP_COMP3_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP3_NMI_PMU_POS))
#define MXC_F_AFE_INTR_LP_COMP0_NMI_PMU_POS                 12
#define MXC_F_AFE_INTR_LP_COMP0_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP0_NMI_PMU_POS))
#define MXC_F_AFE_INTR_LP_COMP1_NMI_PMU_POS                 13
#define MXC_F_AFE_INTR_LP_COMP1_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP1_NMI_PMU_POS))
#define MXC_F_AFE_INTR_LP_COMP2_NMI_PMU_POS                 14
#define MXC_F_AFE_INTR_LP_COMP2_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP2_NMI_PMU_POS))
#define MXC_F_AFE_INTR_LP_COMP3_NMI_PMU_POS                 15
#define MXC_F_AFE_INTR_LP_COMP3_NMI_PMU                     ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP3_NMI_PMU_POS))
#define MXC_F_AFE_INTR_OP_COMP0_POL_POS                     16
#define MXC_F_AFE_INTR_OP_COMP0_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP0_POL_POS))
#define MXC_F_AFE_INTR_OP_COMP1_POL_POS                     17
#define MXC_F_AFE_INTR_OP_COMP1_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP1_POL_POS))
#define MXC_F_AFE_INTR_OP_COMP2_POL_POS                     18
#define MXC_F_AFE_INTR_OP_COMP2_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP2_POL_POS))
#define MXC_F_AFE_INTR_OP_COMP3_POL_POS                     19
#define MXC_F_AFE_INTR_OP_COMP3_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP3_POL_POS))
#define MXC_F_AFE_INTR_LP_COMP0_POL_POS                     20
#define MXC_F_AFE_INTR_LP_COMP0_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP0_POL_POS))
#define MXC_F_AFE_INTR_LP_COMP1_POL_POS                     21
#define MXC_F_AFE_INTR_LP_COMP1_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP1_POL_POS))
#define MXC_F_AFE_INTR_LP_COMP2_POL_POS                     22
#define MXC_F_AFE_INTR_LP_COMP2_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP2_POL_POS))
#define MXC_F_AFE_INTR_LP_COMP3_POL_POS                     23
#define MXC_F_AFE_INTR_LP_COMP3_POL                         ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP3_POL_POS))
#define MXC_F_AFE_INTR_OP_COMP0_IE_POS                      24
#define MXC_F_AFE_INTR_OP_COMP0_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP0_IE_POS))
#define MXC_F_AFE_INTR_OP_COMP1_IE_POS                      25
#define MXC_F_AFE_INTR_OP_COMP1_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP1_IE_POS))
#define MXC_F_AFE_INTR_OP_COMP2_IE_POS                      26
#define MXC_F_AFE_INTR_OP_COMP2_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP2_IE_POS))
#define MXC_F_AFE_INTR_OP_COMP3_IE_POS                      27
#define MXC_F_AFE_INTR_OP_COMP3_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_OP_COMP3_IE_POS))
#define MXC_F_AFE_INTR_LP_COMP0_IE_POS                      28
#define MXC_F_AFE_INTR_LP_COMP0_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP0_IE_POS))
#define MXC_F_AFE_INTR_LP_COMP1_IE_POS                      29
#define MXC_F_AFE_INTR_LP_COMP1_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP1_IE_POS))
#define MXC_F_AFE_INTR_LP_COMP2_IE_POS                      30
#define MXC_F_AFE_INTR_LP_COMP2_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP2_IE_POS))
#define MXC_F_AFE_INTR_LP_COMP3_IE_POS                      31
#define MXC_F_AFE_INTR_LP_COMP3_IE                          ((uint32_t)(0x00000001UL << MXC_F_AFE_INTR_LP_COMP3_IE_POS))

#define MXC_F_AFE_CTRL0_LED_CFG_POS                         0
#define MXC_F_AFE_CTRL0_LED_CFG                             ((uint32_t)(0x0000000FUL << MXC_F_AFE_CTRL0_LED_CFG_POS))
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP0_POS                 4
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP0                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL0_CLEAR_WUD_COMP0_POS))
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP1_POS                 5
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP1                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL0_CLEAR_WUD_COMP1_POS))
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP2_POS                 6
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP2                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL0_CLEAR_WUD_COMP2_POS))
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP3_POS                 7
#define MXC_F_AFE_CTRL0_CLEAR_WUD_COMP3                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL0_CLEAR_WUD_COMP3_POS))
#define MXC_F_AFE_CTRL0_EN_WUD_COMP0_POS                    8
#define MXC_F_AFE_CTRL0_EN_WUD_COMP0                        ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_EN_WUD_COMP0_POS))
#define MXC_F_AFE_CTRL0_EN_WUD_COMP1_POS                    10
#define MXC_F_AFE_CTRL0_EN_WUD_COMP1                        ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_EN_WUD_COMP1_POS))
#define MXC_F_AFE_CTRL0_EN_WUD_COMP2_POS                    12
#define MXC_F_AFE_CTRL0_EN_WUD_COMP2                        ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_EN_WUD_COMP2_POS))
#define MXC_F_AFE_CTRL0_EN_WUD_COMP3_POS                    14
#define MXC_F_AFE_CTRL0_EN_WUD_COMP3                        ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_EN_WUD_COMP3_POS))
#define MXC_F_AFE_CTRL0_IN_MODE_COMP0_POS                   16
#define MXC_F_AFE_CTRL0_IN_MODE_COMP0                       ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_IN_MODE_COMP0_POS))
#define MXC_F_AFE_CTRL0_IN_MODE_COMP1_POS                   18
#define MXC_F_AFE_CTRL0_IN_MODE_COMP1                       ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_IN_MODE_COMP1_POS))
#define MXC_F_AFE_CTRL0_IN_MODE_COMP2_POS                   20
#define MXC_F_AFE_CTRL0_IN_MODE_COMP2                       ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_IN_MODE_COMP2_POS))
#define MXC_F_AFE_CTRL0_IN_MODE_COMP3_POS                   22
#define MXC_F_AFE_CTRL0_IN_MODE_COMP3                       ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_IN_MODE_COMP3_POS))
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP0_POS                 24
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP0                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_BIAS_MODE_COMP0_POS))
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP1_POS                 26
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP1                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_BIAS_MODE_COMP1_POS))
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP2_POS                 28
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP2                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_BIAS_MODE_COMP2_POS))
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP3_POS                 30
#define MXC_F_AFE_CTRL0_BIAS_MODE_COMP3                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL0_BIAS_MODE_COMP3_POS))

#define MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_EN_POS           0
#define MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_EN               ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_EN_POS))
#define MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_SEL_POS          1
#define MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_SEL              ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL1_TEMP_SENSE_CURRENT_SEL_POS))
#define MXC_F_AFE_CTRL1_REF_DAC_FAST_PWRDN_EN_POS           3
#define MXC_F_AFE_CTRL1_REF_DAC_FAST_PWRDN_EN               ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_DAC_FAST_PWRDN_EN_POS))
#define MXC_F_AFE_CTRL1_REF_ADC_FAST_PWRDN_EN_POS           4
#define MXC_F_AFE_CTRL1_REF_ADC_FAST_PWRDN_EN               ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_ADC_FAST_PWRDN_EN_POS))
#define MXC_F_AFE_CTRL1_REF_BANDGAP_SEL_POS                 5
#define MXC_F_AFE_CTRL1_REF_BANDGAP_SEL                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_BANDGAP_SEL_POS))
#define MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL_POS                6
#define MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL                    ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL1_REF_ADC_VOLT_SEL_POS))
#define MXC_F_AFE_CTRL1_REF_DAC_VOLT_SEL_POS                8
#define MXC_F_AFE_CTRL1_REF_DAC_VOLT_SEL                    ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL1_REF_DAC_VOLT_SEL_POS))
#define MXC_F_AFE_CTRL1_REF_SEL_POS                         10
#define MXC_F_AFE_CTRL1_REF_SEL                             ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_SEL_POS))
#define MXC_F_AFE_CTRL1_REF_ADC_POWERUP_POS                 11
#define MXC_F_AFE_CTRL1_REF_ADC_POWERUP                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_ADC_POWERUP_POS))
#define MXC_F_AFE_CTRL1_REF_DAC_POWERUP_POS                 12
#define MXC_F_AFE_CTRL1_REF_DAC_POWERUP                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_DAC_POWERUP_POS))
#define MXC_F_AFE_CTRL1_REF_BLK_POWERUP_POS                 13
#define MXC_F_AFE_CTRL1_REF_BLK_POWERUP                     ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_BLK_POWERUP_POS))
#define MXC_F_AFE_CTRL1_REF_ADC_COMP_POS                    14
#define MXC_F_AFE_CTRL1_REF_ADC_COMP                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_ADC_COMP_POS))
#define MXC_F_AFE_CTRL1_REF_DAC_COMP_POS                    15
#define MXC_F_AFE_CTRL1_REF_DAC_COMP                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_REF_DAC_COMP_POS))
#define MXC_F_AFE_CTRL1_REF_ADC_TEST_GAIN_POS               16
#define MXC_F_AFE_CTRL1_REF_ADC_TEST_GAIN                   ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL1_REF_ADC_TEST_GAIN_POS))
#define MXC_F_AFE_CTRL1_REF_DAC_TEST_GAIN_POS               18
#define MXC_F_AFE_CTRL1_REF_DAC_TEST_GAIN                   ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL1_REF_DAC_TEST_GAIN_POS))
#define MXC_F_AFE_CTRL1_ABUS_PAGE_2_0_POS                   20
#define MXC_F_AFE_CTRL1_ABUS_PAGE_2_0                       ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL1_ABUS_PAGE_2_0_POS))
#define MXC_F_AFE_CTRL1_PLL_TST_EN_POS                      23
#define MXC_F_AFE_CTRL1_PLL_TST_EN                          ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_PLL_TST_EN_POS))
#define MXC_F_AFE_CTRL1_V1EXTADJ_POS                        25
#define MXC_F_AFE_CTRL1_V1EXTADJ                            ((uint32_t)(0x0000001FUL << MXC_F_AFE_CTRL1_V1EXTADJ_POS))
#define MXC_F_AFE_CTRL1_TMON_CUR_SEL_POS                    30
#define MXC_F_AFE_CTRL1_TMON_CUR_SEL                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL1_TMON_CUR_SEL_POS))

#define MXC_F_AFE_CTRL2_HYST_COMP0_POS                      0
#define MXC_F_AFE_CTRL2_HYST_COMP0                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL2_HYST_COMP0_POS))
#define MXC_F_AFE_CTRL2_HYST_COMP1_POS                      2
#define MXC_F_AFE_CTRL2_HYST_COMP1                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL2_HYST_COMP1_POS))
#define MXC_F_AFE_CTRL2_HYST_COMP2_POS                      4
#define MXC_F_AFE_CTRL2_HYST_COMP2                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL2_HYST_COMP2_POS))
#define MXC_F_AFE_CTRL2_HYST_COMP3_POS                      6
#define MXC_F_AFE_CTRL2_HYST_COMP3                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL2_HYST_COMP3_POS))
#define MXC_F_AFE_CTRL2_HY_POL_COMP0_POS                    8
#define MXC_F_AFE_CTRL2_HY_POL_COMP0                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_HY_POL_COMP0_POS))
#define MXC_F_AFE_CTRL2_HY_POL_COMP1_POS                    9
#define MXC_F_AFE_CTRL2_HY_POL_COMP1                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_HY_POL_COMP1_POS))
#define MXC_F_AFE_CTRL2_HY_POL_COMP2_POS                    10
#define MXC_F_AFE_CTRL2_HY_POL_COMP2                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_HY_POL_COMP2_POS))
#define MXC_F_AFE_CTRL2_HY_POL_COMP3_POS                    11
#define MXC_F_AFE_CTRL2_HY_POL_COMP3                        ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_HY_POL_COMP3_POS))
#define MXC_F_AFE_CTRL2_POWERUP_COMP0_POS                   12
#define MXC_F_AFE_CTRL2_POWERUP_COMP0                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_POWERUP_COMP0_POS))
#define MXC_F_AFE_CTRL2_POWERUP_COMP1_POS                   13
#define MXC_F_AFE_CTRL2_POWERUP_COMP1                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_POWERUP_COMP1_POS))
#define MXC_F_AFE_CTRL2_POWERUP_COMP2_POS                   14
#define MXC_F_AFE_CTRL2_POWERUP_COMP2                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_POWERUP_COMP2_POS))
#define MXC_F_AFE_CTRL2_POWERUP_COMP3_POS                   15
#define MXC_F_AFE_CTRL2_POWERUP_COMP3                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_POWERUP_COMP3_POS))
#define MXC_F_AFE_CTRL2_DACOUT_EN0_POS                      16
#define MXC_F_AFE_CTRL2_DACOUT_EN0                          ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DACOUT_EN0_POS))
#define MXC_F_AFE_CTRL2_DACOUT_EN1_POS                      17
#define MXC_F_AFE_CTRL2_DACOUT_EN1                          ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DACOUT_EN1_POS))
#define MXC_F_AFE_CTRL2_DACOUT_EN2_POS                      18
#define MXC_F_AFE_CTRL2_DACOUT_EN2                          ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DACOUT_EN2_POS))
#define MXC_F_AFE_CTRL2_DACOUT_EN3_POS                      19
#define MXC_F_AFE_CTRL2_DACOUT_EN3                          ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DACOUT_EN3_POS))
#define MXC_F_AFE_CTRL2_SCM_OR_SEL_POS                      20
#define MXC_F_AFE_CTRL2_SCM_OR_SEL                          ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL2_SCM_OR_SEL_POS))
#define MXC_F_AFE_CTRL2_SNO_OR_SEL_POS                      23
#define MXC_F_AFE_CTRL2_SNO_OR_SEL                          ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL2_SNO_OR_SEL_POS))
#define MXC_F_AFE_CTRL2_DAC0_SEL_POS                        26
#define MXC_F_AFE_CTRL2_DAC0_SEL                            ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DAC0_SEL_POS))
#define MXC_F_AFE_CTRL2_DAC1_SEL_POS                        27
#define MXC_F_AFE_CTRL2_DAC1_SEL                            ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL2_DAC1_SEL_POS))

#define MXC_F_AFE_CTRL3_POWERUP_OPAMP0_POS                  12
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP0                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_POWERUP_OPAMP0_POS))
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP1_POS                  13
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP1                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_POWERUP_OPAMP1_POS))
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP2_POS                  14
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP2                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_POWERUP_OPAMP2_POS))
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP3_POS                  15
#define MXC_F_AFE_CTRL3_POWERUP_OPAMP3                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_POWERUP_OPAMP3_POS))
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP0_POS                  16
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP0                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_GND_SEL_OPAMP0_POS))
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP1_POS                  17
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP1                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_GND_SEL_OPAMP1_POS))
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP2_POS                  18
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP2                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_GND_SEL_OPAMP2_POS))
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP3_POS                  19
#define MXC_F_AFE_CTRL3_GND_SEL_OPAMP3                      ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_GND_SEL_OPAMP3_POS))
#define MXC_F_AFE_CTRL3_CLOSE_SPST0_POS                     20
#define MXC_F_AFE_CTRL3_CLOSE_SPST0                         ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_CLOSE_SPST0_POS))
#define MXC_F_AFE_CTRL3_CLOSE_SPST1_POS                     21
#define MXC_F_AFE_CTRL3_CLOSE_SPST1                         ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_CLOSE_SPST1_POS))
#define MXC_F_AFE_CTRL3_CLOSE_SPST2_POS                     22
#define MXC_F_AFE_CTRL3_CLOSE_SPST2                         ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_CLOSE_SPST2_POS))
#define MXC_F_AFE_CTRL3_CLOSE_SPST3_POS                     23
#define MXC_F_AFE_CTRL3_CLOSE_SPST3                         ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_CLOSE_SPST3_POS))
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP0_POS                   24
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP0                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_PCH_OPAMP0_POS))
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP1_POS                   25
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP1                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_PCH_OPAMP1_POS))
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP2_POS                   26
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP2                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_PCH_OPAMP2_POS))
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP3_POS                   27
#define MXC_F_AFE_CTRL3_EN_PCH_OPAMP3                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_PCH_OPAMP3_POS))
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP0_POS                   28
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP0                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_NCH_OPAMP0_POS))
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP1_POS                   29
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP1                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_NCH_OPAMP1_POS))
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP2_POS                   30
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP2                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_NCH_OPAMP2_POS))
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP3_POS                   31
#define MXC_F_AFE_CTRL3_EN_NCH_OPAMP3                       ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL3_EN_NCH_OPAMP3_POS))

#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP0_POS                 0
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP0                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP0_POS))
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP1_POS                 2
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP1                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP1_POS))
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP2_POS                 4
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP2                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP2_POS))
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP3_POS                 6
#define MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP3                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_P_IN_SEL_OPAMP3_POS))
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP0_POS                 8
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP0                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP0_POS))
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP1_POS                 10
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP1                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP1_POS))
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP2_POS                 12
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP2                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP2_POS))
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP3_POS                 14
#define MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP3                     ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_N_IN_SEL_OPAMP3_POS))
#define MXC_F_AFE_CTRL4_DAC_SEL_A_POS                       16
#define MXC_F_AFE_CTRL4_DAC_SEL_A                           ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_DAC_SEL_A_POS))
#define MXC_F_AFE_CTRL4_DAC_SEL_B_POS                       18
#define MXC_F_AFE_CTRL4_DAC_SEL_B                           ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_DAC_SEL_B_POS))
#define MXC_F_AFE_CTRL4_DAC_SEL_C_POS                       20
#define MXC_F_AFE_CTRL4_DAC_SEL_C                           ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_DAC_SEL_C_POS))
#define MXC_F_AFE_CTRL4_DAC_SEL_D_POS                       22
#define MXC_F_AFE_CTRL4_DAC_SEL_D                           ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_DAC_SEL_D_POS))
#define MXC_F_AFE_CTRL4_NPAD_SEL_A_POS                      24
#define MXC_F_AFE_CTRL4_NPAD_SEL_A                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_NPAD_SEL_A_POS))
#define MXC_F_AFE_CTRL4_NPAD_SEL_B_POS                      26
#define MXC_F_AFE_CTRL4_NPAD_SEL_B                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_NPAD_SEL_B_POS))
#define MXC_F_AFE_CTRL4_NPAD_SEL_C_POS                      28
#define MXC_F_AFE_CTRL4_NPAD_SEL_C                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_NPAD_SEL_C_POS))
#define MXC_F_AFE_CTRL4_NPAD_SEL_D_POS                      30
#define MXC_F_AFE_CTRL4_NPAD_SEL_D                          ((uint32_t)(0x00000003UL << MXC_F_AFE_CTRL4_NPAD_SEL_D_POS))

#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP0_POS               0
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP0                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP0_POS))
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP1_POS               3
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP1                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP1_POS))
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP2_POS               6
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP2                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP2_POS))
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP3_POS               9
#define MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP3                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_P_IN_SEL_LP_COMP3_POS))
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP0_POS               12
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP0                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP0_POS))
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP1_POS               15
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP1                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP1_POS))
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP2_POS               18
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP2                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP2_POS))
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP3_POS               21
#define MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP3                   ((uint32_t)(0x00000007UL << MXC_F_AFE_CTRL5_N_IN_SEL_LP_COMP3_POS))
#define MXC_F_AFE_CTRL5_OP_CMP0_POS                         24
#define MXC_F_AFE_CTRL5_OP_CMP0                             ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL5_OP_CMP0_POS))
#define MXC_F_AFE_CTRL5_OP_CMP1_POS                         25
#define MXC_F_AFE_CTRL5_OP_CMP1                             ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL5_OP_CMP1_POS))
#define MXC_F_AFE_CTRL5_OP_CMP2_POS                         26
#define MXC_F_AFE_CTRL5_OP_CMP2                             ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL5_OP_CMP2_POS))
#define MXC_F_AFE_CTRL5_OP_CMP3_POS                         27
#define MXC_F_AFE_CTRL5_OP_CMP3                             ((uint32_t)(0x00000001UL << MXC_F_AFE_CTRL5_OP_CMP3_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_AFE_REGS_H_ */
