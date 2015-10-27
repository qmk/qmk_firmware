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

#ifndef _MXC_I2CM_REGS_H_
#define _MXC_I2CM_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  i2cm_regs.h
 * @addtogroup i2cm I2CM
 * @{
 */

/*                                      Offset   Register Description
                                        ======   ================================================ */
typedef struct {
    __IO uint32_t fs_clk_div;       /*  0x0000   Full Speed SCL Clock Settings                    */
    __IO uint32_t hs_clk_div;       /*  0x0004   High Speed SCL Clock Settings                    */
    __I uint32_t rsv0008;           /*  0x0008                                                    */
    __IO uint32_t timeout;          /*  0x000C   [TO_CNTL] Timeout and Auto-Stop Settings         */
    __IO uint32_t ctrl;             /*  0x0010   [EN_CNTL] I2C Master Control Register            */
    __IO uint32_t trans;            /*  0x0014   [MSTR_CNTL] I2C Master Tx Start and Status Flags */
    __IO uint32_t intfl;            /*  0x0018   Interrupt Flags                                  */
    __IO uint32_t inten;            /*  0x001C   Interrupt Enable/Disable Controls                */
    __I uint32_t rsv0020[2];        /*  0x0020                                                    */
    __IO uint32_t bb;               /*  0x0028   Bit-Bang Control Register                        */
} mxc_i2cm_regs_t;

/*                                      Offset   Register Description
                                        ======   ================================================ */
typedef struct {
    __IO uint32_t trans[512];       /*  0x0000   I2C Master Transaction FIFO                      */
    __IO uint32_t rslts[512];       /*  0x0800   I2C Master Results FIFO                          */
} mxc_i2cm_fifo_regs_t;

/*
   Register offsets for module I2CM.
*/
#define MXC_R_I2CM_OFFS_FS_CLK_DIV                ((uint32_t)0x00000000UL)
#define MXC_R_I2CM_OFFS_HS_CLK_DIV                ((uint32_t)0x00000004UL)
#define MXC_R_I2CM_OFFS_TIMEOUT                   ((uint32_t)0x0000000CUL)
#define MXC_R_I2CM_OFFS_CTRL                      ((uint32_t)0x00000010UL)
#define MXC_R_I2CM_OFFS_TRANS                     ((uint32_t)0x00000014UL)
#define MXC_R_I2CM_OFFS_INTFL                     ((uint32_t)0x00000018UL)
#define MXC_R_I2CM_OFFS_INTEN                     ((uint32_t)0x0000001CUL)
#define MXC_R_I2CM_OFFS_BB                        ((uint32_t)0x00000028UL)
#define MXC_R_I2CM_OFFS_AHB_RETRY                 ((uint32_t)0x00000030UL)

#define MXC_R_I2CM_FIFO_OFFS_TRANS                ((uint32_t)0x00000000UL)
#define MXC_R_I2CM_FIFO_OFFS_RSLTS                ((uint32_t)0x00000800UL)

/*
   Field positions and masks for module I2CM.
*/
#define MXC_S_I2CM_TRANS_TAG_START                0x000
#define MXC_S_I2CM_TRANS_TAG_TXDATA_ACK           0x100
#define MXC_S_I2CM_TRANS_TAG_TXDATA_NACK          0x200
#define MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT         0x400
#define MXC_S_I2CM_TRANS_TAG_RXDATA_NACK          0x500
#define MXC_S_I2CM_TRANS_TAG_STOP                 0x700
#define MXC_S_I2CM_RSTLS_TAG_DATA                 0x100
#define MXC_S_I2CM_RSTLS_TAG_EMPTY                0x200

#define MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS               0
#define MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV                   ((uint32_t)(0x000000FFUL << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS))
#define MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS                   8
#define MXC_F_I2CM_CLK_DIV_SCL_LO_CNT                       ((uint32_t)(0x00000FFFUL << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS))
#define MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS                   20
#define MXC_F_I2CM_CLK_DIV_SCL_HI_CNT                       ((uint32_t)(0x00000FFFUL << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS))

#define MXC_F_I2CM_TIMEOUT_TX_TIMEOUT_POS                   16
#define MXC_F_I2CM_TIMEOUT_TX_TIMEOUT                       ((uint32_t)(0x000000FFUL << MXC_F_I2CM_TIMEOUT_TX_TIMEOUT_POS))
#define MXC_F_I2CM_TIMEOUT_AUTO_STOP_EN_POS                 24
#define MXC_F_I2CM_TIMEOUT_AUTO_STOP_EN                     ((uint32_t)(0x00000001UL << MXC_F_I2CM_TIMEOUT_AUTO_STOP_EN_POS))

#define MXC_F_I2CM_CTRL_TX_FIFO_EN_POS                      2
#define MXC_F_I2CM_CTRL_TX_FIFO_EN                          ((uint32_t)(0x00000001UL << MXC_F_I2CM_CTRL_TX_FIFO_EN_POS))
#define MXC_F_I2CM_CTRL_RX_FIFO_EN_POS                      3
#define MXC_F_I2CM_CTRL_RX_FIFO_EN                          ((uint32_t)(0x00000001UL << MXC_F_I2CM_CTRL_RX_FIFO_EN_POS))
#define MXC_F_I2CM_CTRL_MSTR_RESET_EN_POS                   7
#define MXC_F_I2CM_CTRL_MSTR_RESET_EN                       ((uint32_t)(0x00000001UL << MXC_F_I2CM_CTRL_MSTR_RESET_EN_POS))

#define MXC_F_I2CM_TRANS_TX_START_POS                       0
#define MXC_F_I2CM_TRANS_TX_START                           ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_START_POS))
#define MXC_F_I2CM_TRANS_TX_IN_PROGRESS_POS                 1
#define MXC_F_I2CM_TRANS_TX_IN_PROGRESS                     ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_IN_PROGRESS_POS))
#define MXC_F_I2CM_TRANS_TX_DONE_POS                        2
#define MXC_F_I2CM_TRANS_TX_DONE                            ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_DONE_POS))
#define MXC_F_I2CM_TRANS_TX_NACKED_POS                      3
#define MXC_F_I2CM_TRANS_TX_NACKED                          ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_NACKED_POS))
#define MXC_F_I2CM_TRANS_TX_LOST_ARBITR_POS                 4
#define MXC_F_I2CM_TRANS_TX_LOST_ARBITR                     ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_LOST_ARBITR_POS))
#define MXC_F_I2CM_TRANS_TX_TIMEOUT_POS                     5
#define MXC_F_I2CM_TRANS_TX_TIMEOUT                         ((uint32_t)(0x00000001UL << MXC_F_I2CM_TRANS_TX_TIMEOUT_POS))

#define MXC_F_I2CM_INTFL_TX_DONE_POS                        0
#define MXC_F_I2CM_INTFL_TX_DONE                            ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_DONE_POS))
#define MXC_F_I2CM_INTFL_TX_NACKED_POS                      1
#define MXC_F_I2CM_INTFL_TX_NACKED                          ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_NACKED_POS))
#define MXC_F_I2CM_INTFL_TX_LOST_ARBITR_POS                 2
#define MXC_F_I2CM_INTFL_TX_LOST_ARBITR                     ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_LOST_ARBITR_POS))
#define MXC_F_I2CM_INTFL_TX_TIMEOUT_POS                     3
#define MXC_F_I2CM_INTFL_TX_TIMEOUT                         ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_TIMEOUT_POS))
#define MXC_F_I2CM_INTFL_TX_FIFO_EMPTY_POS                  4
#define MXC_F_I2CM_INTFL_TX_FIFO_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_FIFO_EMPTY_POS))
#define MXC_F_I2CM_INTFL_TX_FIFO_3Q_EMPTY_POS               5
#define MXC_F_I2CM_INTFL_TX_FIFO_3Q_EMPTY                   ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_TX_FIFO_3Q_EMPTY_POS))
#define MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY_POS              6
#define MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY                  ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY_POS))
#define MXC_F_I2CM_INTFL_RX_FIFO_2Q_FULL_POS                7
#define MXC_F_I2CM_INTFL_RX_FIFO_2Q_FULL                    ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_RX_FIFO_2Q_FULL_POS))
#define MXC_F_I2CM_INTFL_RX_FIFO_3Q_FULL_POS                8
#define MXC_F_I2CM_INTFL_RX_FIFO_3Q_FULL                    ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_RX_FIFO_3Q_FULL_POS))
#define MXC_F_I2CM_INTFL_RX_FIFO_FULL_POS                   9
#define MXC_F_I2CM_INTFL_RX_FIFO_FULL                       ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTFL_RX_FIFO_FULL_POS))

#define MXC_F_I2CM_INTEN_TX_DONE_POS                        0
#define MXC_F_I2CM_INTEN_TX_DONE                            ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_DONE_POS))
#define MXC_F_I2CM_INTEN_TX_NACKED_POS                      1
#define MXC_F_I2CM_INTEN_TX_NACKED                          ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_NACKED_POS))
#define MXC_F_I2CM_INTEN_TX_LOST_ARBITR_POS                 2
#define MXC_F_I2CM_INTEN_TX_LOST_ARBITR                     ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_LOST_ARBITR_POS))
#define MXC_F_I2CM_INTEN_TX_TIMEOUT_POS                     3
#define MXC_F_I2CM_INTEN_TX_TIMEOUT                         ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_TIMEOUT_POS))
#define MXC_F_I2CM_INTEN_TX_FIFO_EMPTY_POS                  4
#define MXC_F_I2CM_INTEN_TX_FIFO_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_FIFO_EMPTY_POS))
#define MXC_F_I2CM_INTEN_TX_FIFO_3Q_EMPTY_POS               5
#define MXC_F_I2CM_INTEN_TX_FIFO_3Q_EMPTY                   ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_TX_FIFO_3Q_EMPTY_POS))
#define MXC_F_I2CM_INTEN_RX_FIFO_EMPTY_POS                  6
#define MXC_F_I2CM_INTEN_RX_FIFO_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_RX_FIFO_EMPTY_POS))
#define MXC_F_I2CM_INTEN_RX_FIFO_2Q_FULL_POS                7
#define MXC_F_I2CM_INTEN_RX_FIFO_2Q_FULL                    ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_RX_FIFO_2Q_FULL_POS))
#define MXC_F_I2CM_INTEN_RX_FIFO_3Q_FULL_POS                8
#define MXC_F_I2CM_INTEN_RX_FIFO_3Q_FULL                    ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_RX_FIFO_3Q_FULL_POS))
#define MXC_F_I2CM_INTEN_RX_FIFO_FULL_POS                   9
#define MXC_F_I2CM_INTEN_RX_FIFO_FULL                       ((uint32_t)(0x00000001UL << MXC_F_I2CM_INTEN_RX_FIFO_FULL_POS))

#define MXC_F_I2CM_BB_BB_SCL_OUT_POS                        0
#define MXC_F_I2CM_BB_BB_SCL_OUT                            ((uint32_t)(0x00000001UL << MXC_F_I2CM_BB_BB_SCL_OUT_POS))
#define MXC_F_I2CM_BB_BB_SDA_OUT_POS                        1
#define MXC_F_I2CM_BB_BB_SDA_OUT                            ((uint32_t)(0x00000001UL << MXC_F_I2CM_BB_BB_SDA_OUT_POS))
#define MXC_F_I2CM_BB_BB_SCL_IN_VAL_POS                     2
#define MXC_F_I2CM_BB_BB_SCL_IN_VAL                         ((uint32_t)(0x00000001UL << MXC_F_I2CM_BB_BB_SCL_IN_VAL_POS))
#define MXC_F_I2CM_BB_BB_SDA_IN_VAL_POS                     3
#define MXC_F_I2CM_BB_BB_SDA_IN_VAL                         ((uint32_t)(0x00000001UL << MXC_F_I2CM_BB_BB_SDA_IN_VAL_POS))
#define MXC_F_I2CM_BB_RX_FIFO_CNT_POS                       16
#define MXC_F_I2CM_BB_RX_FIFO_CNT                           ((uint32_t)(0x0000001FUL << MXC_F_I2CM_BB_RX_FIFO_CNT_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif
