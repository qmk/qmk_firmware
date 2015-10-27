/*
** ###################################################################
**     Version:             rev. 1.0, 2014-05-14
**     Build:               b140515
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright: 2014 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-05-14)
**         Customer release.
**
** ###################################################################
*/

#if !defined(__FSL_LPUART_FEATURES_H__)
#define __FSL_LPUART_FEATURES_H__

#if defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10) || \
    defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12) || \
    defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12) || defined(CPU_MK65FN2M0CAC18) || \
    defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || defined(CPU_MK66FN2M0VLQ18) || \
    defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18) || defined(CPU_MKV31F128VLH10) || \
    defined(CPU_MKV31F128VLL10) || defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12) || defined(CPU_MKV31F512VLH12) || \
    defined(CPU_MKV31F512VLL12)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_HAS_FIFO (0)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_RX_RESYNC_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_LPUART_IS_SCI (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_FIFO_SIZE (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_PARITY (9)
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_DMA_ENABLE (1)
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_LPUART_HAS_DMA_SELECT (0)
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BIT_ORDER_SELECT (1)
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_LPUART_HAS_SMART_CARD_SUPPORT (0)
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_LPUART_HAS_32BIT_REGISTERS (1)
#elif defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || defined(CPU_MKL03Z32VFG4) || \
    defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || defined(CPU_MKL03Z32VFK4)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_HAS_FIFO (0)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (0)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (0)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_RX_RESYNC_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_LPUART_IS_SCI (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_FIFO_SIZE (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_PARITY (9)
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_DMA_ENABLE (0)
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_LPUART_HAS_DMA_SELECT (0)
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BIT_ORDER_SELECT (1)
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_LPUART_HAS_SMART_CARD_SUPPORT (0)
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_LPUART_HAS_32BIT_REGISTERS (1)
#elif defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || defined(CPU_MKL13Z64VFT4) || \
    defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || \
    defined(CPU_MKL13Z256VLH4) || defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4) || \
    defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || defined(CPU_MKL23Z64VFT4) || \
    defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || \
    defined(CPU_MKL23Z256VLH4) || defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4) || \
    defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || defined(CPU_MKL33Z256VMP4) || \
    defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z64VMP4) || \
    defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_HAS_FIFO (0)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (0)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (0)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_RX_RESYNC_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_LPUART_IS_SCI (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_LPUART_FIFO_SIZE (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_LPUART_MAX_DATA_WIDTH_WITH_PARITY (9)
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_DMA_ENABLE (1)
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_LPUART_HAS_DMA_SELECT (0)
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_LPUART_HAS_BIT_ORDER_SELECT (1)
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_LPUART_HAS_SMART_CARD_SUPPORT (0)
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_LPUART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_LPUART_HAS_32BIT_REGISTERS (1)
#else
    #define MBED_NO_LPUART
#endif

#endif /* __FSL_LPUART_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
