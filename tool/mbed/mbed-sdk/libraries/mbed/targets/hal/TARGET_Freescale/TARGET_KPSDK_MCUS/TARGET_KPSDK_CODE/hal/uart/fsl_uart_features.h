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

#if !defined(__FSL_UART_FEATURES_H__)
#define __FSL_UART_FEATURES_H__

#if defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || defined(CPU_MK02FN64VLF10) || \
    defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10) || defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || \
    defined(CPU_MKV30F128VLF10) || defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : (-1)))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : (-1)))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || defined(CPU_MK20DN64VMP5) || \
    defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || \
    defined(CPU_MK20DX64VLH5) || defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || defined(CPU_MK20DN64VFT5) || \
    defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || \
    defined(CPU_MK20DX64VLF5) || defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : (-1))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : \
        ((x) == 2 ? (10) : (-1))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || defined(CPU_MK20DN64VFM5) || \
    defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : (-1)))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : (-1)))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10) || \
    defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12) || \
    defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12) || defined(CPU_MKV31F128VLH10) || \
    defined(CPU_MKV31F128VLL10) || defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12) || defined(CPU_MKV31F512VLH12) || \
    defined(CPU_MKV31F512VLL12)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : (-1))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : \
        ((x) == 2 ? (10) : (-1))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12) || defined(CPU_MK24FN256VDC12) || \
    defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || \
    defined(CPU_MK64FX512VLL12) || defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (8) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : \
        ((x) == 3 ? (9) : \
        ((x) == 4 ? (9) : \
        ((x) == 5 ? (9) : (-1)))))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : \
        ((x) == 2 ? (10) : \
        ((x) == 3 ? (10) : \
        ((x) == 4 ? (10) : \
        ((x) == 5 ? (10) : (-1)))))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || \
    defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (8) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : (-1))))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : \
        ((x) == 3 ? (9) : \
        ((x) == 4 ? (9) : (-1))))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : \
        ((x) == 2 ? (10) : \
        ((x) == 3 ? (10) : \
        ((x) == 4 ? (10) : (-1))))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : (-1))))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : (-1))))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : (-1))))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : (-1))))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (8) : \
        ((x) == 2 ? (8) : \
        ((x) == 3 ? (8) : \
        ((x) == 4 ? (8) : \
        ((x) == 5 ? (8) : (-1)))))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : \
        ((x) == 3 ? (9) : \
        ((x) == 4 ? (9) : \
        ((x) == 5 ? (9) : (-1)))))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : \
        ((x) == 2 ? (10) : \
        ((x) == 3 ? (10) : \
        ((x) == 4 ? (10) : \
        ((x) == 5 ? (10) : (-1)))))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : \
        ((x) == 3 ? (1) : \
        ((x) == 4 ? (1) : \
        ((x) == 5 ? (1) : (-1)))))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : \
        ((x) == 3 ? (0) : \
        ((x) == 4 ? (0) : \
        ((x) == 5 ? (0) : (-1)))))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || defined(CPU_MKL05Z8VLC4) || \
    defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || \
    defined(CPU_MKL05Z32VFM4) || defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (0)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (0)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (0)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (0)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (10) : (-1))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (9) : (-1))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (1)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (0)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
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
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (0)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : (-1))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : (-1))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : (-1))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (1) : (-1))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : (-1))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || defined(CPU_MKL25Z32VFT4) || \
    defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || \
    defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4) || \
    defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || \
    defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (0)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (0)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (0)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (1)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (0)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (9) : \
        ((x) == 2 ? (9) : (-1))))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (8) : \
        ((x) == 2 ? (8) : (-1))))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (1)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (1) : \
        ((x) == 2 ? (1) : (-1))))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : \
        ((x) == 2 ? (0) : (-1))))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#elif defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || defined(CPU_MKV40F256VLL15) || \
    defined(CPU_MKV40F64VLH15) || defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15) || \
    defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15) || defined(CPU_MKV45F128VLH15) || \
    defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || defined(CPU_MKV45F256VLL15) || defined(CPU_MKV46F128VLH15) || \
    defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || defined(CPU_MKV46F256VLL15)
    /* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
    #define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
    /* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_HAS_FIFO (1)
    /* @brief Hardware flow control (RTS, CTS) is supported. */
    #define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (1)
    /* @brief Infrared (modulation) is supported. */
    #define FSL_FEATURE_UART_HAS_IR_SUPPORT (1)
    /* @brief 2 bits long stop bit is available. */
    #define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate fine adjustment is available. */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (1)
    /* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (0)
    /* @brief Baud rate oversampling is available. */
    #define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (0)
    /* @brief Peripheral type. */
    #define FSL_FEATURE_UART_IS_SCI (0)
    /* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
    #define FSL_FEATURE_UART_FIFO_SIZE (8)
    #define FSL_FEATURE_UART_FIFO_SIZEn(x) \
        ((x) == 0 ? (8) : \
        ((x) == 1 ? (8) : (-1)))
    /* @brief Maximal data width without parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITY (9)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_NO_PARITYn(x) \
        ((x) == 0 ? (9) : \
        ((x) == 1 ? (9) : (-1)))
    /* @brief Maximal data width with parity bit. */
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITY (10)
    #define FSL_FEATURE_UART_MAX_DATA_WIDTH_WITH_PARITYn(x) \
        ((x) == 0 ? (10) : \
        ((x) == 1 ? (10) : (-1)))
    /* @brief Supports two match addresses to filter incoming frames. */
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (1)
    #define FSL_FEATURE_UART_HAS_ADDRESS_MATCHINGn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
    #define FSL_FEATURE_UART_HAS_DMA_ENABLEn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
    #define FSL_FEATURE_UART_HAS_DMA_SELECT (1)
    #define FSL_FEATURE_UART_HAS_DMA_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (1)
    #define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECTn(x) \
        ((x) == 0 ? (1) : \
        ((x) == 1 ? (1) : (-1)))
    /* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has improved smart card (ISO7816 protocol) support. */
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has local operation network (CEA709.1-B protocol) support. */
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
    #define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORTn(x) \
        ((x) == 0 ? (0) : \
        ((x) == 1 ? (0) : (-1)))
    /* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
    #define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_UART_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
