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

#ifndef _MXC_UART_REGS_H_
#define _MXC_UART_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  uart_regs.h
 * @addtogroup uart UART
 * @{
 */

/*                                      Offset   Register Description
                                        ======   ============================================== */
typedef struct {
    __IO uint32_t ctrl;             /*  0x0000   UART Control Register                          */
    __IO uint32_t status;           /*  0x0004   UART Status Register                           */
    __IO uint32_t inten;            /*  0x0008   Interrupt Enable/Disable Controls              */
    __IO uint32_t intfl;            /*  0x000C   Interrupt Flags                                */
    __IO uint32_t baud_int;         /*  0x0010   Baud Rate Setting (Integer Portion)            */
    __IO uint32_t baud_div_128;     /*  0x0014   Baud Rate Setting                              */
    __IO uint32_t tx_fifo_out;      /*  0x0018   TX FIFO Output End (read-only)                 */
    __IO uint32_t hw_flow_ctrl;     /*  0x001C   Hardware Flow Control Register                 */
    __IO uint32_t tx_rx_fifo;       /*  0x0020   Write to load TX FIFO, Read to unload RX FIFO  */
} mxc_uart_regs_t;


/*
    Register offsets for module UART.
*/
#define MXC_R_UART_OFFS_CTRL                      ((uint32_t)0x00000000UL)
#define MXC_R_UART_OFFS_STATUS                    ((uint32_t)0x00000004UL)
#define MXC_R_UART_OFFS_INTEN                     ((uint32_t)0x00000008UL)
#define MXC_R_UART_OFFS_INTFL                     ((uint32_t)0x0000000CUL)
#define MXC_R_UART_OFFS_BAUD_INT                  ((uint32_t)0x00000010UL)
#define MXC_R_UART_OFFS_BAUD_DIV_128              ((uint32_t)0x00000014UL)
#define MXC_R_UART_OFFS_TX_FIFO_OUT               ((uint32_t)0x00000018UL)
#define MXC_R_UART_OFFS_HW_FLOW_CTRL              ((uint32_t)0x0000001CUL)
#define MXC_R_UART_OFFS_TX_RX_FIFO                ((uint32_t)0x00000020UL)

/*
   Field positions and masks for module UART.
*/
#define MXC_F_UART_CTRL_RX_THRESHOLD_POS                    0
#define MXC_F_UART_CTRL_RX_THRESHOLD                        ((uint32_t)(0x00000007UL << MXC_F_UART_CTRL_RX_THRESHOLD_POS))
#define MXC_F_UART_CTRL_PARITY_ENABLE_POS                   4
#define MXC_F_UART_CTRL_PARITY_ENABLE                       ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_PARITY_ENABLE_POS))
#define MXC_F_UART_CTRL_PARITY_MODE_POS                     5
#define MXC_F_UART_CTRL_PARITY_MODE                         ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_PARITY_MODE_POS))
#define MXC_F_UART_CTRL_PARITY_BIAS_POS                     6
#define MXC_F_UART_CTRL_PARITY_BIAS                         ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_PARITY_BIAS_POS))
#define MXC_F_UART_CTRL_TX_FIFO_FLUSH_POS                   8
#define MXC_F_UART_CTRL_TX_FIFO_FLUSH                       ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_TX_FIFO_FLUSH_POS))
#define MXC_F_UART_CTRL_RX_FIFO_FLUSH_POS                   9
#define MXC_F_UART_CTRL_RX_FIFO_FLUSH                       ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_RX_FIFO_FLUSH_POS))
#define MXC_F_UART_CTRL_CHAR_LENGTH_POS                     10
#define MXC_F_UART_CTRL_CHAR_LENGTH                         ((uint32_t)(0x00000003UL << MXC_F_UART_CTRL_CHAR_LENGTH_POS))
#define MXC_F_UART_CTRL_STOP_BIT_MODE_POS                   12
#define MXC_F_UART_CTRL_STOP_BIT_MODE                       ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_STOP_BIT_MODE_POS))
#define MXC_F_UART_CTRL_HW_FLOW_CTRL_EN_POS                 13
#define MXC_F_UART_CTRL_HW_FLOW_CTRL_EN                     ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_HW_FLOW_CTRL_EN_POS))
#define MXC_F_UART_CTRL_BAUD_CLK_EN_POS                     14
#define MXC_F_UART_CTRL_BAUD_CLK_EN                         ((uint32_t)(0x00000001UL << MXC_F_UART_CTRL_BAUD_CLK_EN_POS))

#define MXC_F_UART_STATUS_TX_BUSY_POS                       0
#define MXC_F_UART_STATUS_TX_BUSY                           ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_TX_BUSY_POS))
#define MXC_F_UART_STATUS_RX_BUSY_POS                       1
#define MXC_F_UART_STATUS_RX_BUSY                           ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_RX_BUSY_POS))
#define MXC_F_UART_STATUS_RX_FIFO_EMPTY_POS                 4
#define MXC_F_UART_STATUS_RX_FIFO_EMPTY                     ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_RX_FIFO_EMPTY_POS))
#define MXC_F_UART_STATUS_RX_FIFO_FULL_POS                  5
#define MXC_F_UART_STATUS_RX_FIFO_FULL                      ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_RX_FIFO_FULL_POS))
#define MXC_F_UART_STATUS_TX_FIFO_EMPTY_POS                 6
#define MXC_F_UART_STATUS_TX_FIFO_EMPTY                     ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_TX_FIFO_EMPTY_POS))
#define MXC_F_UART_STATUS_TX_FIFO_FULL_POS                  7
#define MXC_F_UART_STATUS_TX_FIFO_FULL                      ((uint32_t)(0x00000001UL << MXC_F_UART_STATUS_TX_FIFO_FULL_POS))
#define MXC_F_UART_STATUS_RX_FIFO_CHARS_POS                 8
#define MXC_F_UART_STATUS_RX_FIFO_CHARS                     ((uint32_t)(0x0000000FUL << MXC_F_UART_STATUS_RX_FIFO_CHARS_POS))
#define MXC_F_UART_STATUS_TX_FIFO_CHARS_POS                 12
#define MXC_F_UART_STATUS_TX_FIFO_CHARS                     ((uint32_t)(0x0000000FUL << MXC_F_UART_STATUS_TX_FIFO_CHARS_POS))

#define MXC_F_UART_INTEN_RX_FRAME_ERROR_POS                 0
#define MXC_F_UART_INTEN_RX_FRAME_ERROR                     ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_RX_FRAME_ERROR_POS))
#define MXC_F_UART_INTEN_RX_PARITY_ERROR_POS                1
#define MXC_F_UART_INTEN_RX_PARITY_ERROR                    ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_RX_PARITY_ERROR_POS))
#define MXC_F_UART_INTEN_CTS_CHANGE_POS                     2
#define MXC_F_UART_INTEN_CTS_CHANGE                         ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_CTS_CHANGE_POS))
#define MXC_F_UART_INTEN_RX_OVERRUN_POS                     3
#define MXC_F_UART_INTEN_RX_OVERRUN                         ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_RX_OVERRUN_POS))
#define MXC_F_UART_INTEN_RX_OVER_THRESHOLD_POS              4
#define MXC_F_UART_INTEN_RX_OVER_THRESHOLD                  ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_RX_OVER_THRESHOLD_POS))
#define MXC_F_UART_INTEN_TX_ALMOST_EMPTY_POS                5
#define MXC_F_UART_INTEN_TX_ALMOST_EMPTY                    ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_TX_ALMOST_EMPTY_POS))
#define MXC_F_UART_INTEN_TX_HALF_EMPTY_POS                  6
#define MXC_F_UART_INTEN_TX_HALF_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_UART_INTEN_TX_HALF_EMPTY_POS))

#define MXC_F_UART_INTFL_RX_FRAME_ERROR_POS                 0
#define MXC_F_UART_INTFL_RX_FRAME_ERROR                     ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_RX_FRAME_ERROR_POS))
#define MXC_F_UART_INTFL_RX_PARITY_ERROR_POS                1
#define MXC_F_UART_INTFL_RX_PARITY_ERROR                    ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_RX_PARITY_ERROR_POS))
#define MXC_F_UART_INTFL_CTS_CHANGE_POS                     2
#define MXC_F_UART_INTFL_CTS_CHANGE                         ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_CTS_CHANGE_POS))
#define MXC_F_UART_INTFL_RX_OVERRUN_POS                     3
#define MXC_F_UART_INTFL_RX_OVERRUN                         ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_RX_OVERRUN_POS))
#define MXC_F_UART_INTFL_RX_OVER_THRESHOLD_POS              4
#define MXC_F_UART_INTFL_RX_OVER_THRESHOLD                  ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_RX_OVER_THRESHOLD_POS))
#define MXC_F_UART_INTFL_TX_ALMOST_EMPTY_POS                5
#define MXC_F_UART_INTFL_TX_ALMOST_EMPTY                    ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_TX_ALMOST_EMPTY_POS))
#define MXC_F_UART_INTFL_TX_HALF_EMPTY_POS                  6
#define MXC_F_UART_INTFL_TX_HALF_EMPTY                      ((uint32_t)(0x00000001UL << MXC_F_UART_INTFL_TX_HALF_EMPTY_POS))

#define MXC_F_UART_BAUD_INT_FBAUD_POS                       0
#define MXC_F_UART_BAUD_INT_FBAUD                           ((uint32_t)(0x00000FFFUL << MXC_F_UART_BAUD_INT_FBAUD_POS))

#define MXC_F_UART_BAUD_DIV_128_DIV_POS                     0
#define MXC_F_UART_BAUD_DIV_128_DIV                         ((uint32_t)(0x0000007FUL << MXC_F_UART_BAUD_DIV_128_DIV_POS))

#define MXC_F_UART_TX_FIFO_OUT_TX_FIFO_POS                  0
#define MXC_F_UART_TX_FIFO_OUT_TX_FIFO                      ((uint32_t)(0x000000FFUL << MXC_F_UART_TX_FIFO_OUT_TX_FIFO_POS))

#define MXC_F_UART_HW_FLOW_CTRL_CTS_INPUT_POS               0
#define MXC_F_UART_HW_FLOW_CTRL_CTS_INPUT                   ((uint32_t)(0x00000001UL << MXC_F_UART_HW_FLOW_CTRL_CTS_INPUT_POS))
#define MXC_F_UART_HW_FLOW_CTRL_RTS_OUTPUT_POS              1
#define MXC_F_UART_HW_FLOW_CTRL_RTS_OUTPUT                  ((uint32_t)(0x00000001UL << MXC_F_UART_HW_FLOW_CTRL_RTS_OUTPUT_POS))

#define MXC_F_UART_TX_RX_FIFO_FIFO_DATA_POS                 0
#define MXC_F_UART_TX_RX_FIFO_FIFO_DATA                     ((uint32_t)(0x000000FFUL << MXC_F_UART_TX_RX_FIFO_FIFO_DATA_POS))
#define MXC_F_UART_TX_RX_FIFO_PARITY_ERROR_POS              8
#define MXC_F_UART_TX_RX_FIFO_PARITY_ERROR                  ((uint32_t)(0x00000001UL << MXC_F_UART_TX_RX_FIFO_PARITY_ERROR_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_UART_REGS_H_ */
