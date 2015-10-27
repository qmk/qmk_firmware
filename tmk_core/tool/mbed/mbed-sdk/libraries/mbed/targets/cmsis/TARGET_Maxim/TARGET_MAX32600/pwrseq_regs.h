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

#ifndef _MXC_PWRSEQ_REGS_H
#define _MXC_PWRSEQ_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  pwrseq_regs.h
 * @addtogroup pwrseq PWRSEQ
 * @{
 */

/*                                      Offset   Register Description
                                        ======   ================================================= */
typedef struct {
    __IO uint32_t reg0;             /*  0x0000   Power Sequencer Control Register 0                */
    __IO uint32_t reg1;             /*  0x0004   Power Sequencer Control Register 1                */
    __IO uint32_t reg2;             /*  0x0008   Power Sequencer Control Register 2                */
    __IO uint32_t reg3;             /*  0x000C   Power Sequencer Control Register 3                */
    __IO uint32_t reg4;             /*  0x0010   Power Sequencer Control Register 4                */
    __IO uint32_t reg5;             /*  0x0014   Power Sequencer Control Register 5 (Trim 0)       */
    __IO uint32_t reg6;             /*  0x0018   Power Sequencer Control Register 6 (Trim 1)       */
    __I uint32_t rsv001C;           /*  0x001C                                                     */
    __IO uint32_t flags;            /*  0x0020   Power Sequencer Flags                             */
    __IO uint32_t msk_flags;        /*  0x0024   Power Sequencer Flags Mask Register               */
} mxc_pwrseq_regs_t;


/*
   Register offsets for module PWRSEQ.
*/
#define MXC_R_PWRSEQ_OFFS_REG0                    ((uint32_t)0x00000000UL)
#define MXC_R_PWRSEQ_OFFS_REG1                    ((uint32_t)0x00000004UL)
#define MXC_R_PWRSEQ_OFFS_REG2                    ((uint32_t)0x00000008UL)
#define MXC_R_PWRSEQ_OFFS_REG3                    ((uint32_t)0x0000000CUL)
#define MXC_R_PWRSEQ_OFFS_REG4                    ((uint32_t)0x00000010UL)
#define MXC_R_PWRSEQ_OFFS_REG5                    ((uint32_t)0x00000014UL)
#define MXC_R_PWRSEQ_OFFS_REG6                    ((uint32_t)0x00000018UL)
#define MXC_R_PWRSEQ_OFFS_FLAGS                   ((uint32_t)0x00000020UL)
#define MXC_R_PWRSEQ_OFFS_MSK_FLAGS               ((uint32_t)0x00000024UL)


/*
   Field positions and masks for module PWRSEQ.
*/
#define MXC_F_PWRSEQ_REG0_PWR_LP1_POS                       0
#define MXC_F_PWRSEQ_REG0_PWR_LP1                           ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_LP1_POS))
#define MXC_F_PWRSEQ_REG0_PWR_FIRST_BOOT_POS                1
#define MXC_F_PWRSEQ_REG0_PWR_FIRST_BOOT                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_FIRST_BOOT_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SYS_REBOOT_POS                2
#define MXC_F_PWRSEQ_REG0_PWR_SYS_REBOOT                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SYS_REBOOT_POS))
#define MXC_F_PWRSEQ_REG0_PWR_LDOEN_RUN_POS                 3
#define MXC_F_PWRSEQ_REG0_PWR_LDOEN_RUN                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_LDOEN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_LDOEN_SLP_POS                 4
#define MXC_F_PWRSEQ_REG0_PWR_LDOEN_SLP                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_LDOEN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_CHZYEN_RUN_POS                5
#define MXC_F_PWRSEQ_REG0_PWR_CHZYEN_RUN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_CHZYEN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_CHZYEN_SLP_POS                6
#define MXC_F_PWRSEQ_REG0_PWR_CHZYEN_SLP                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_CHZYEN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_ROEN_RUN_POS                  7
#define MXC_F_PWRSEQ_REG0_PWR_ROEN_RUN                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_ROEN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_ROEN_SLP_POS                  8
#define MXC_F_PWRSEQ_REG0_PWR_ROEN_SLP                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_ROEN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_NREN_RUN_POS                  9
#define MXC_F_PWRSEQ_REG0_PWR_NREN_RUN                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_NREN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_NREN_SLP_POS                  10
#define MXC_F_PWRSEQ_REG0_PWR_NREN_SLP                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_NREN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN_POS                 11
#define MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_RTCEN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP_POS                 12
#define MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_RTCEN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVM3EN_RUN_POS                13
#define MXC_F_PWRSEQ_REG0_PWR_SVM3EN_RUN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVM3EN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVM3EN_SLP_POS                14
#define MXC_F_PWRSEQ_REG0_PWR_SVM3EN_SLP                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVM3EN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVM1EN_RUN_POS                15
#define MXC_F_PWRSEQ_REG0_PWR_SVM1EN_RUN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVM1EN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVM1EN_SLP_POS                16
#define MXC_F_PWRSEQ_REG0_PWR_SVM1EN_SLP                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVM1EN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_RUN_POS              17
#define MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_RUN                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_RUN_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_SLP_POS              18
#define MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_SLP                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVMRTCEN_SLP_POS))
#define MXC_F_PWRSEQ_REG0_PWR_SVMVDDA3EN_POS                19
#define MXC_F_PWRSEQ_REG0_PWR_SVMVDDA3EN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG0_PWR_SVMVDDA3EN_POS))

#define MXC_F_PWRSEQ_REG1_PWR_TRIKL_CHRG_POS                0
#define MXC_F_PWRSEQ_REG1_PWR_TRIKL_CHRG                    ((uint32_t)(0x000000FFUL << MXC_F_PWRSEQ_REG1_PWR_TRIKL_CHRG_POS))
#define MXC_F_PWRSEQ_REG1_PWR_PD_VDDA3_POS                  8
#define MXC_F_PWRSEQ_REG1_PWR_PD_VDDA3                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_PD_VDDA3_POS))
#define MXC_F_PWRSEQ_REG1_PWR_TEMP_SENSOR_PD_POS            9
#define MXC_F_PWRSEQ_REG1_PWR_TEMP_SENSOR_PD                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_TEMP_SENSOR_PD_POS))
#define MXC_F_PWRSEQ_REG1_PWR_PD_VDDIO_POS                  10
#define MXC_F_PWRSEQ_REG1_PWR_PD_VDDIO                      ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_PD_VDDIO_POS))
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW_POS              11
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW_POS))
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW2_POS             12
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW2                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW2_POS))
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW1_POS             13
#define MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW1                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_MAN_VDDIO_SW1_POS))
#define MXC_F_PWRSEQ_REG1_PWR_GPIO_FREEZE_POS               14
#define MXC_F_PWRSEQ_REG1_PWR_GPIO_FREEZE                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG1_PWR_GPIO_FREEZE_POS))

#define MXC_F_PWRSEQ_REG2_PWR_RST3_POS                      0
#define MXC_F_PWRSEQ_REG2_PWR_RST3                          ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG2_PWR_RST3_POS))
#define MXC_F_PWRSEQ_REG2_PWR_W3_POS                        5
#define MXC_F_PWRSEQ_REG2_PWR_W3                            ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG2_PWR_W3_POS))
#define MXC_F_PWRSEQ_REG2_PWR_W1_POS                        10
#define MXC_F_PWRSEQ_REG2_PWR_W1                            ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG2_PWR_W1_POS))
#define MXC_F_PWRSEQ_REG2_PWR_W1_LOW_POS                    15
#define MXC_F_PWRSEQ_REG2_PWR_W1_LOW                        ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG2_PWR_W1_LOW_POS))
#define MXC_F_PWRSEQ_REG2_PWR_WRTC_POS                      20
#define MXC_F_PWRSEQ_REG2_PWR_WRTC                          ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG2_PWR_WRTC_POS))
#define MXC_F_PWRSEQ_REG2_PWR_WVDDA3_POS                    25
#define MXC_F_PWRSEQ_REG2_PWR_WVDDA3                        ((uint32_t)(0x0000003FUL << MXC_F_PWRSEQ_REG2_PWR_WVDDA3_POS))

#define MXC_F_PWRSEQ_REG3_PWR_ROSEL_POS                     0
#define MXC_F_PWRSEQ_REG3_PWR_ROSEL                         ((uint32_t)(0x00000007UL << MXC_F_PWRSEQ_REG3_PWR_ROSEL_POS))
#define MXC_F_PWRSEQ_REG3_PWR_ROSEL_QUICK_POS               3
#define MXC_F_PWRSEQ_REG3_PWR_ROSEL_QUICK                   ((uint32_t)(0x00000003UL << MXC_F_PWRSEQ_REG3_PWR_ROSEL_QUICK_POS))
#define MXC_F_PWRSEQ_REG3_PWR_SVMSEL_POS                    5
#define MXC_F_PWRSEQ_REG3_PWR_SVMSEL                        ((uint32_t)(0x00000007UL << MXC_F_PWRSEQ_REG3_PWR_SVMSEL_POS))
#define MXC_F_PWRSEQ_REG3_PWR_PWRFLTRSVMSELO_POS            8
#define MXC_F_PWRSEQ_REG3_PWR_PWRFLTRSVMSELO                ((uint32_t)(0x00000003UL << MXC_F_PWRSEQ_REG3_PWR_PWRFLTRSVMSELO_POS))
#define MXC_F_PWRSEQ_REG3_PWR_PWRFLTRROSEL_POS              10
#define MXC_F_PWRSEQ_REG3_PWR_PWRFLTRROSEL                  ((uint32_t)(0x00000007UL << MXC_F_PWRSEQ_REG3_PWR_PWRFLTRROSEL_POS))
#define MXC_F_PWRSEQ_REG3_PWR_SVM_CLK_MUX_POS               13
#define MXC_F_PWRSEQ_REG3_PWR_SVM_CLK_MUX                   ((uint32_t)(0x00000003UL << MXC_F_PWRSEQ_REG3_PWR_SVM_CLK_MUX_POS))
#define MXC_F_PWRSEQ_REG3_PWR_RO_CLK_MUX_POS                15
#define MXC_F_PWRSEQ_REG3_PWR_RO_CLK_MUX                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG3_PWR_RO_CLK_MUX_POS))
#define MXC_F_PWRSEQ_REG3_PWR_QUICK_CNT_POS                 16
#define MXC_F_PWRSEQ_REG3_PWR_QUICK_CNT                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG3_PWR_QUICK_CNT_POS))
#define MXC_F_PWRSEQ_REG3_PWR_BO_TC_POS                     17
#define MXC_F_PWRSEQ_REG3_PWR_BO_TC                         ((uint32_t)(0x00000003UL << MXC_F_PWRSEQ_REG3_PWR_BO_TC_POS))

#define MXC_F_PWRSEQ_REG4_PWR_TM_PS_2_GPIO_POS              0
#define MXC_F_PWRSEQ_REG4_PWR_TM_PS_2_GPIO                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_TM_PS_2_GPIO_POS))
#define MXC_F_PWRSEQ_REG4_PWR_TM_FAST_TIMERS_POS            1
#define MXC_F_PWRSEQ_REG4_PWR_TM_FAST_TIMERS                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_TM_FAST_TIMERS_POS))
#define MXC_F_PWRSEQ_REG4_PWR_USB_PROT_TRIM_POS             2
#define MXC_F_PWRSEQ_REG4_PWR_USB_PROT_TRIM                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_USB_PROT_TRIM_POS))
#define MXC_F_PWRSEQ_REG4_PWR_USB_DIS_COMP_POS              3
#define MXC_F_PWRSEQ_REG4_PWR_USB_DIS_COMP                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_USB_DIS_COMP_POS))
#define MXC_F_PWRSEQ_REG4_PWR_USB_TO_VDD_FAST_POS           4
#define MXC_F_PWRSEQ_REG4_PWR_USB_TO_VDD_FAST               ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_USB_TO_VDD_FAST_POS))
#define MXC_F_PWRSEQ_REG4_PWR_USB_LDO_OFF_POS               5
#define MXC_F_PWRSEQ_REG4_PWR_USB_LDO_OFF                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_USB_LDO_OFF_POS))
#define MXC_F_PWRSEQ_REG4_PWR_USB_FRC_VDD_POS               6
#define MXC_F_PWRSEQ_REG4_PWR_USB_FRC_VDD                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_REG4_PWR_USB_FRC_VDD_POS))

#define MXC_F_PWRSEQ_REG5_PWR_TRIM_SVM_BG_POS               0
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_SVM_BG                   ((uint32_t)(0x0000003FUL << MXC_F_PWRSEQ_REG5_PWR_TRIM_SVM_BG_POS))
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_REG1P8_POS               6
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_REG1P8                   ((uint32_t)(0x0000000FUL << MXC_F_PWRSEQ_REG5_PWR_TRIM_REG1P8_POS))
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_REG3P3_POS               10
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_REG3P3                   ((uint32_t)(0x0000001FUL << MXC_F_PWRSEQ_REG5_PWR_TRIM_REG3P3_POS))
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_OSC_VREF_POS             15
#define MXC_F_PWRSEQ_REG5_PWR_TRIM_OSC_VREF                 ((uint32_t)(0x0000007FUL << MXC_F_PWRSEQ_REG5_PWR_TRIM_OSC_VREF_POS))

#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_BIAS_POS             0
#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_BIAS                 ((uint32_t)(0x00000007UL << MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_BIAS_POS))
#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_PM_RES_POS           3
#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_PM_RES               ((uint32_t)(0x0000000FUL << MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_PM_RES_POS))
#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_DM_RES_POS           7
#define MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_DM_RES               ((uint32_t)(0x0000000FUL << MXC_F_PWRSEQ_REG6_PWR_TRIM_USB_DM_RES_POS))

#define MXC_F_PWRSEQ_FLAGS_PWR_FIRST_BOOT_POS               0
#define MXC_F_PWRSEQ_FLAGS_PWR_FIRST_BOOT                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_FIRST_BOOT_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_SYS_REBOOT_POS               1
#define MXC_F_PWRSEQ_FLAGS_PWR_SYS_REBOOT                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_SYS_REBOOT_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_PRV_PWR_FAIL_POS             2
#define MXC_F_PWRSEQ_FLAGS_PWR_PRV_PWR_FAIL                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_PRV_PWR_FAIL_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_PRV_BOOT_FAIL_POS            3
#define MXC_F_PWRSEQ_FLAGS_PWR_PRV_BOOT_FAIL                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_PRV_BOOT_FAIL_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_COMP_WAKEUP_POS              4
#define MXC_F_PWRSEQ_FLAGS_PWR_COMP_WAKEUP                  ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_COMP_WAKEUP_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_IO_WAKEUP_POS                5
#define MXC_F_PWRSEQ_FLAGS_PWR_IO_WAKEUP                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_IO_WAKEUP_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD3_RST_POS                 6
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD3_RST                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD3_RST_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD3_WARN_POS                7
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD3_WARN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD3_WARN_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_RST_POS                 8
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_RST                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD1_RST_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_LOW_RST_POS             9
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_LOW_RST                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD1_LOW_RST_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_WARN_POS                10
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD1_WARN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD1_WARN_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VRTC_WARN_POS                11
#define MXC_F_PWRSEQ_FLAGS_PWR_VRTC_WARN                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VRTC_WARN_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_POR3Z_FAIL_POS               12
#define MXC_F_PWRSEQ_FLAGS_PWR_POR3Z_FAIL                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_POR3Z_FAIL_POS))
#define MXC_F_PWRSEQ_FLAGS_RTC_CMPR0_POS                    13
#define MXC_F_PWRSEQ_FLAGS_RTC_CMPR0                        ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_RTC_CMPR0_POS))
#define MXC_F_PWRSEQ_FLAGS_RTC_CMPR1_POS                    14
#define MXC_F_PWRSEQ_FLAGS_RTC_CMPR1                        ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_RTC_CMPR1_POS))
#define MXC_F_PWRSEQ_FLAGS_RTC_PRESCALE_CMP_POS             15
#define MXC_F_PWRSEQ_FLAGS_RTC_PRESCALE_CMP                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_RTC_PRESCALE_CMP_POS))
#define MXC_F_PWRSEQ_FLAGS_RTC_ROLLOVER_POS                 16
#define MXC_F_PWRSEQ_FLAGS_RTC_ROLLOVER                     ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_RTC_ROLLOVER_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_BROWNOUT_DET_POS             17
#define MXC_F_PWRSEQ_FLAGS_PWR_BROWNOUT_DET                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_BROWNOUT_DET_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_USB_PLUG_WAKEUP_POS          18
#define MXC_F_PWRSEQ_FLAGS_PWR_USB_PLUG_WAKEUP              ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_USB_PLUG_WAKEUP_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_USB_REMOVE_WAKEUP_POS        19
#define MXC_F_PWRSEQ_FLAGS_PWR_USB_REMOVE_WAKEUP            ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_USB_REMOVE_WAKEUP_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD22_RST_POS                20
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD22_RST                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD22_RST_POS))
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD195_RST_POS               21
#define MXC_F_PWRSEQ_FLAGS_PWR_VDD195_RST                   ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_FLAGS_PWR_VDD195_RST_POS))

#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_SYS_REBOOT_POS           1
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_SYS_REBOOT               ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_SYS_REBOOT_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_PWR_FAIL_POS         2
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_PWR_FAIL             ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_PWR_FAIL_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_BOOT_FAIL_POS        3
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_BOOT_FAIL            ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_PRV_BOOT_FAIL_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_COMP_WAKEUP_POS          4
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_COMP_WAKEUP              ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_COMP_WAKEUP_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_IO_WAKEUP_POS            5
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_IO_WAKEUP                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_IO_WAKEUP_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_RST_POS             6
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_RST                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_RST_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_WARN_POS            7
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_WARN                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD3_WARN_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_RST_POS             8
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_RST                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_RST_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_LOW_RST_POS         9
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_LOW_RST             ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_LOW_RST_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_WARN_POS            10
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_WARN                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD1_WARN_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VRTC_WARN_POS            11
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VRTC_WARN                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VRTC_WARN_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_POR3Z_FAIL_POS           12
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_POR3Z_FAIL               ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_POR3Z_FAIL_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR0_POS                13
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR0                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR0_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR1_POS                14
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR1                    ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_RTC_CMPR1_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_PRESCALE_CMP_POS         15
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_PRESCALE_CMP             ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_RTC_PRESCALE_CMP_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_ROLLOVER_POS             16
#define MXC_F_PWRSEQ_MSK_FLAGS_RTC_ROLLOVER                 ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_RTC_ROLLOVER_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_BROWNOUT_DET_POS         17
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_BROWNOUT_DET             ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_BROWNOUT_DET_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_PLUG_WAKEUP_POS      18
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_PLUG_WAKEUP          ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_PLUG_WAKEUP_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_REMOVE_WAKEUP_POS    19
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_REMOVE_WAKEUP        ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_USB_REMOVE_WAKEUP_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD22_RST_POS            20
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD22_RST                ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD22_RST_POS))
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD195_RST_POS           21
#define MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD195_RST               ((uint32_t)(0x00000001UL << MXC_F_PWRSEQ_MSK_FLAGS_PWR_VDD195_RST_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_PWRSEQ_REGS_H */
