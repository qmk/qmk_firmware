/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SPI
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_SPI_DEFINED
#define HARDWARE_REGS_SPI_DEFINED
// =============================================================================
// Register    : SPI_SSPCR0
// Description : Control register 0, SSPCR0 on page 3-4
#define SPI_SSPCR0_OFFSET _u(0x00000000)
#define SPI_SSPCR0_BITS   _u(0x0000ffff)
#define SPI_SSPCR0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR0_SCR
// Description : Serial clock rate. The value SCR is used to generate the
//               transmit and receive bit rate of the PrimeCell SSP. The bit
//               rate is: F SSPCLK CPSDVSR x (1+SCR) where CPSDVSR is an even
//               value from 2-254, programmed through the SSPCPSR register and
//               SCR is a value from 0-255.
#define SPI_SSPCR0_SCR_RESET  _u(0x00)
#define SPI_SSPCR0_SCR_BITS   _u(0x0000ff00)
#define SPI_SSPCR0_SCR_MSB    _u(15)
#define SPI_SSPCR0_SCR_LSB    _u(8)
#define SPI_SSPCR0_SCR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR0_SPH
// Description : SSPCLKOUT phase, applicable to Motorola SPI frame format only.
//               See Motorola SPI frame format on page 2-10.
#define SPI_SSPCR0_SPH_RESET  _u(0x0)
#define SPI_SSPCR0_SPH_BITS   _u(0x00000080)
#define SPI_SSPCR0_SPH_MSB    _u(7)
#define SPI_SSPCR0_SPH_LSB    _u(7)
#define SPI_SSPCR0_SPH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR0_SPO
// Description : SSPCLKOUT polarity, applicable to Motorola SPI frame format
//               only. See Motorola SPI frame format on page 2-10.
#define SPI_SSPCR0_SPO_RESET  _u(0x0)
#define SPI_SSPCR0_SPO_BITS   _u(0x00000040)
#define SPI_SSPCR0_SPO_MSB    _u(6)
#define SPI_SSPCR0_SPO_LSB    _u(6)
#define SPI_SSPCR0_SPO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR0_FRF
// Description : Frame format: 00 Motorola SPI frame format. 01 TI synchronous
//               serial frame format. 10 National Microwire frame format. 11
//               Reserved, undefined operation.
#define SPI_SSPCR0_FRF_RESET  _u(0x0)
#define SPI_SSPCR0_FRF_BITS   _u(0x00000030)
#define SPI_SSPCR0_FRF_MSB    _u(5)
#define SPI_SSPCR0_FRF_LSB    _u(4)
#define SPI_SSPCR0_FRF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR0_DSS
// Description : Data Size Select: 0000 Reserved, undefined operation. 0001
//               Reserved, undefined operation. 0010 Reserved, undefined
//               operation. 0011 4-bit data. 0100 5-bit data. 0101 6-bit data.
//               0110 7-bit data. 0111 8-bit data. 1000 9-bit data. 1001 10-bit
//               data. 1010 11-bit data. 1011 12-bit data. 1100 13-bit data.
//               1101 14-bit data. 1110 15-bit data. 1111 16-bit data.
#define SPI_SSPCR0_DSS_RESET  _u(0x0)
#define SPI_SSPCR0_DSS_BITS   _u(0x0000000f)
#define SPI_SSPCR0_DSS_MSB    _u(3)
#define SPI_SSPCR0_DSS_LSB    _u(0)
#define SPI_SSPCR0_DSS_ACCESS "RW"
// =============================================================================
// Register    : SPI_SSPCR1
// Description : Control register 1, SSPCR1 on page 3-5
#define SPI_SSPCR1_OFFSET _u(0x00000004)
#define SPI_SSPCR1_BITS   _u(0x0000000f)
#define SPI_SSPCR1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR1_SOD
// Description : Slave-mode output disable. This bit is relevant only in the
//               slave mode, MS=1. In multiple-slave systems, it is possible for
//               an PrimeCell SSP master to broadcast a message to all slaves in
//               the system while ensuring that only one slave drives data onto
//               its serial output line. In such systems the RXD lines from
//               multiple slaves could be tied together. To operate in such
//               systems, the SOD bit can be set if the PrimeCell SSP slave is
//               not supposed to drive the SSPTXD line: 0 SSP can drive the
//               SSPTXD output in slave mode. 1 SSP must not drive the SSPTXD
//               output in slave mode.
#define SPI_SSPCR1_SOD_RESET  _u(0x0)
#define SPI_SSPCR1_SOD_BITS   _u(0x00000008)
#define SPI_SSPCR1_SOD_MSB    _u(3)
#define SPI_SSPCR1_SOD_LSB    _u(3)
#define SPI_SSPCR1_SOD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR1_MS
// Description : Master or slave mode select. This bit can be modified only when
//               the PrimeCell SSP is disabled, SSE=0: 0 Device configured as
//               master, default. 1 Device configured as slave.
#define SPI_SSPCR1_MS_RESET  _u(0x0)
#define SPI_SSPCR1_MS_BITS   _u(0x00000004)
#define SPI_SSPCR1_MS_MSB    _u(2)
#define SPI_SSPCR1_MS_LSB    _u(2)
#define SPI_SSPCR1_MS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR1_SSE
// Description : Synchronous serial port enable: 0 SSP operation disabled. 1 SSP
//               operation enabled.
#define SPI_SSPCR1_SSE_RESET  _u(0x0)
#define SPI_SSPCR1_SSE_BITS   _u(0x00000002)
#define SPI_SSPCR1_SSE_MSB    _u(1)
#define SPI_SSPCR1_SSE_LSB    _u(1)
#define SPI_SSPCR1_SSE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCR1_LBM
// Description : Loop back mode: 0 Normal serial port operation enabled. 1
//               Output of transmit serial shifter is connected to input of
//               receive serial shifter internally.
#define SPI_SSPCR1_LBM_RESET  _u(0x0)
#define SPI_SSPCR1_LBM_BITS   _u(0x00000001)
#define SPI_SSPCR1_LBM_MSB    _u(0)
#define SPI_SSPCR1_LBM_LSB    _u(0)
#define SPI_SSPCR1_LBM_ACCESS "RW"
// =============================================================================
// Register    : SPI_SSPDR
// Description : Data register, SSPDR on page 3-6
#define SPI_SSPDR_OFFSET _u(0x00000008)
#define SPI_SSPDR_BITS   _u(0x0000ffff)
#define SPI_SSPDR_RESET  "-"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPDR_DATA
// Description : Transmit/Receive FIFO: Read Receive FIFO. Write Transmit FIFO.
//               You must right-justify data when the PrimeCell SSP is
//               programmed for a data size that is less than 16 bits. Unused
//               bits at the top are ignored by transmit logic. The receive
//               logic automatically right-justifies.
#define SPI_SSPDR_DATA_RESET  "-"
#define SPI_SSPDR_DATA_BITS   _u(0x0000ffff)
#define SPI_SSPDR_DATA_MSB    _u(15)
#define SPI_SSPDR_DATA_LSB    _u(0)
#define SPI_SSPDR_DATA_ACCESS "RWF"
// =============================================================================
// Register    : SPI_SSPSR
// Description : Status register, SSPSR on page 3-7
#define SPI_SSPSR_OFFSET _u(0x0000000c)
#define SPI_SSPSR_BITS   _u(0x0000001f)
#define SPI_SSPSR_RESET  _u(0x00000003)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPSR_BSY
// Description : PrimeCell SSP busy flag, RO: 0 SSP is idle. 1 SSP is currently
//               transmitting and/or receiving a frame or the transmit FIFO is
//               not empty.
#define SPI_SSPSR_BSY_RESET  _u(0x0)
#define SPI_SSPSR_BSY_BITS   _u(0x00000010)
#define SPI_SSPSR_BSY_MSB    _u(4)
#define SPI_SSPSR_BSY_LSB    _u(4)
#define SPI_SSPSR_BSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPSR_RFF
// Description : Receive FIFO full, RO: 0 Receive FIFO is not full. 1 Receive
//               FIFO is full.
#define SPI_SSPSR_RFF_RESET  _u(0x0)
#define SPI_SSPSR_RFF_BITS   _u(0x00000008)
#define SPI_SSPSR_RFF_MSB    _u(3)
#define SPI_SSPSR_RFF_LSB    _u(3)
#define SPI_SSPSR_RFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPSR_RNE
// Description : Receive FIFO not empty, RO: 0 Receive FIFO is empty. 1 Receive
//               FIFO is not empty.
#define SPI_SSPSR_RNE_RESET  _u(0x0)
#define SPI_SSPSR_RNE_BITS   _u(0x00000004)
#define SPI_SSPSR_RNE_MSB    _u(2)
#define SPI_SSPSR_RNE_LSB    _u(2)
#define SPI_SSPSR_RNE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPSR_TNF
// Description : Transmit FIFO not full, RO: 0 Transmit FIFO is full. 1 Transmit
//               FIFO is not full.
#define SPI_SSPSR_TNF_RESET  _u(0x1)
#define SPI_SSPSR_TNF_BITS   _u(0x00000002)
#define SPI_SSPSR_TNF_MSB    _u(1)
#define SPI_SSPSR_TNF_LSB    _u(1)
#define SPI_SSPSR_TNF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPSR_TFE
// Description : Transmit FIFO empty, RO: 0 Transmit FIFO is not empty. 1
//               Transmit FIFO is empty.
#define SPI_SSPSR_TFE_RESET  _u(0x1)
#define SPI_SSPSR_TFE_BITS   _u(0x00000001)
#define SPI_SSPSR_TFE_MSB    _u(0)
#define SPI_SSPSR_TFE_LSB    _u(0)
#define SPI_SSPSR_TFE_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPCPSR
// Description : Clock prescale register, SSPCPSR on page 3-8
#define SPI_SSPCPSR_OFFSET _u(0x00000010)
#define SPI_SSPCPSR_BITS   _u(0x000000ff)
#define SPI_SSPCPSR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPCPSR_CPSDVSR
// Description : Clock prescale divisor. Must be an even number from 2-254,
//               depending on the frequency of SSPCLK. The least significant bit
//               always returns zero on reads.
#define SPI_SSPCPSR_CPSDVSR_RESET  _u(0x00)
#define SPI_SSPCPSR_CPSDVSR_BITS   _u(0x000000ff)
#define SPI_SSPCPSR_CPSDVSR_MSB    _u(7)
#define SPI_SSPCPSR_CPSDVSR_LSB    _u(0)
#define SPI_SSPCPSR_CPSDVSR_ACCESS "RW"
// =============================================================================
// Register    : SPI_SSPIMSC
// Description : Interrupt mask set or clear register, SSPIMSC on page 3-9
#define SPI_SSPIMSC_OFFSET _u(0x00000014)
#define SPI_SSPIMSC_BITS   _u(0x0000000f)
#define SPI_SSPIMSC_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPIMSC_TXIM
// Description : Transmit FIFO interrupt mask: 0 Transmit FIFO half empty or
//               less condition interrupt is masked. 1 Transmit FIFO half empty
//               or less condition interrupt is not masked.
#define SPI_SSPIMSC_TXIM_RESET  _u(0x0)
#define SPI_SSPIMSC_TXIM_BITS   _u(0x00000008)
#define SPI_SSPIMSC_TXIM_MSB    _u(3)
#define SPI_SSPIMSC_TXIM_LSB    _u(3)
#define SPI_SSPIMSC_TXIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPIMSC_RXIM
// Description : Receive FIFO interrupt mask: 0 Receive FIFO half full or less
//               condition interrupt is masked. 1 Receive FIFO half full or less
//               condition interrupt is not masked.
#define SPI_SSPIMSC_RXIM_RESET  _u(0x0)
#define SPI_SSPIMSC_RXIM_BITS   _u(0x00000004)
#define SPI_SSPIMSC_RXIM_MSB    _u(2)
#define SPI_SSPIMSC_RXIM_LSB    _u(2)
#define SPI_SSPIMSC_RXIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPIMSC_RTIM
// Description : Receive timeout interrupt mask: 0 Receive FIFO not empty and no
//               read prior to timeout period interrupt is masked. 1 Receive
//               FIFO not empty and no read prior to timeout period interrupt is
//               not masked.
#define SPI_SSPIMSC_RTIM_RESET  _u(0x0)
#define SPI_SSPIMSC_RTIM_BITS   _u(0x00000002)
#define SPI_SSPIMSC_RTIM_MSB    _u(1)
#define SPI_SSPIMSC_RTIM_LSB    _u(1)
#define SPI_SSPIMSC_RTIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPIMSC_RORIM
// Description : Receive overrun interrupt mask: 0 Receive FIFO written to while
//               full condition interrupt is masked. 1 Receive FIFO written to
//               while full condition interrupt is not masked.
#define SPI_SSPIMSC_RORIM_RESET  _u(0x0)
#define SPI_SSPIMSC_RORIM_BITS   _u(0x00000001)
#define SPI_SSPIMSC_RORIM_MSB    _u(0)
#define SPI_SSPIMSC_RORIM_LSB    _u(0)
#define SPI_SSPIMSC_RORIM_ACCESS "RW"
// =============================================================================
// Register    : SPI_SSPRIS
// Description : Raw interrupt status register, SSPRIS on page 3-10
#define SPI_SSPRIS_OFFSET _u(0x00000018)
#define SPI_SSPRIS_BITS   _u(0x0000000f)
#define SPI_SSPRIS_RESET  _u(0x00000008)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPRIS_TXRIS
// Description : Gives the raw interrupt state, prior to masking, of the
//               SSPTXINTR interrupt
#define SPI_SSPRIS_TXRIS_RESET  _u(0x1)
#define SPI_SSPRIS_TXRIS_BITS   _u(0x00000008)
#define SPI_SSPRIS_TXRIS_MSB    _u(3)
#define SPI_SSPRIS_TXRIS_LSB    _u(3)
#define SPI_SSPRIS_TXRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPRIS_RXRIS
// Description : Gives the raw interrupt state, prior to masking, of the
//               SSPRXINTR interrupt
#define SPI_SSPRIS_RXRIS_RESET  _u(0x0)
#define SPI_SSPRIS_RXRIS_BITS   _u(0x00000004)
#define SPI_SSPRIS_RXRIS_MSB    _u(2)
#define SPI_SSPRIS_RXRIS_LSB    _u(2)
#define SPI_SSPRIS_RXRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPRIS_RTRIS
// Description : Gives the raw interrupt state, prior to masking, of the
//               SSPRTINTR interrupt
#define SPI_SSPRIS_RTRIS_RESET  _u(0x0)
#define SPI_SSPRIS_RTRIS_BITS   _u(0x00000002)
#define SPI_SSPRIS_RTRIS_MSB    _u(1)
#define SPI_SSPRIS_RTRIS_LSB    _u(1)
#define SPI_SSPRIS_RTRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPRIS_RORRIS
// Description : Gives the raw interrupt state, prior to masking, of the
//               SSPRORINTR interrupt
#define SPI_SSPRIS_RORRIS_RESET  _u(0x0)
#define SPI_SSPRIS_RORRIS_BITS   _u(0x00000001)
#define SPI_SSPRIS_RORRIS_MSB    _u(0)
#define SPI_SSPRIS_RORRIS_LSB    _u(0)
#define SPI_SSPRIS_RORRIS_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPMIS
// Description : Masked interrupt status register, SSPMIS on page 3-11
#define SPI_SSPMIS_OFFSET _u(0x0000001c)
#define SPI_SSPMIS_BITS   _u(0x0000000f)
#define SPI_SSPMIS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPMIS_TXMIS
// Description : Gives the transmit FIFO masked interrupt state, after masking,
//               of the SSPTXINTR interrupt
#define SPI_SSPMIS_TXMIS_RESET  _u(0x0)
#define SPI_SSPMIS_TXMIS_BITS   _u(0x00000008)
#define SPI_SSPMIS_TXMIS_MSB    _u(3)
#define SPI_SSPMIS_TXMIS_LSB    _u(3)
#define SPI_SSPMIS_TXMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPMIS_RXMIS
// Description : Gives the receive FIFO masked interrupt state, after masking,
//               of the SSPRXINTR interrupt
#define SPI_SSPMIS_RXMIS_RESET  _u(0x0)
#define SPI_SSPMIS_RXMIS_BITS   _u(0x00000004)
#define SPI_SSPMIS_RXMIS_MSB    _u(2)
#define SPI_SSPMIS_RXMIS_LSB    _u(2)
#define SPI_SSPMIS_RXMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPMIS_RTMIS
// Description : Gives the receive timeout masked interrupt state, after
//               masking, of the SSPRTINTR interrupt
#define SPI_SSPMIS_RTMIS_RESET  _u(0x0)
#define SPI_SSPMIS_RTMIS_BITS   _u(0x00000002)
#define SPI_SSPMIS_RTMIS_MSB    _u(1)
#define SPI_SSPMIS_RTMIS_LSB    _u(1)
#define SPI_SSPMIS_RTMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPMIS_RORMIS
// Description : Gives the receive over run masked interrupt status, after
//               masking, of the SSPRORINTR interrupt
#define SPI_SSPMIS_RORMIS_RESET  _u(0x0)
#define SPI_SSPMIS_RORMIS_BITS   _u(0x00000001)
#define SPI_SSPMIS_RORMIS_MSB    _u(0)
#define SPI_SSPMIS_RORMIS_LSB    _u(0)
#define SPI_SSPMIS_RORMIS_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPICR
// Description : Interrupt clear register, SSPICR on page 3-11
#define SPI_SSPICR_OFFSET _u(0x00000020)
#define SPI_SSPICR_BITS   _u(0x00000003)
#define SPI_SSPICR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPICR_RTIC
// Description : Clears the SSPRTINTR interrupt
#define SPI_SSPICR_RTIC_RESET  _u(0x0)
#define SPI_SSPICR_RTIC_BITS   _u(0x00000002)
#define SPI_SSPICR_RTIC_MSB    _u(1)
#define SPI_SSPICR_RTIC_LSB    _u(1)
#define SPI_SSPICR_RTIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPICR_RORIC
// Description : Clears the SSPRORINTR interrupt
#define SPI_SSPICR_RORIC_RESET  _u(0x0)
#define SPI_SSPICR_RORIC_BITS   _u(0x00000001)
#define SPI_SSPICR_RORIC_MSB    _u(0)
#define SPI_SSPICR_RORIC_LSB    _u(0)
#define SPI_SSPICR_RORIC_ACCESS "WC"
// =============================================================================
// Register    : SPI_SSPDMACR
// Description : DMA control register, SSPDMACR on page 3-12
#define SPI_SSPDMACR_OFFSET _u(0x00000024)
#define SPI_SSPDMACR_BITS   _u(0x00000003)
#define SPI_SSPDMACR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPDMACR_TXDMAE
// Description : Transmit DMA Enable. If this bit is set to 1, DMA for the
//               transmit FIFO is enabled.
#define SPI_SSPDMACR_TXDMAE_RESET  _u(0x0)
#define SPI_SSPDMACR_TXDMAE_BITS   _u(0x00000002)
#define SPI_SSPDMACR_TXDMAE_MSB    _u(1)
#define SPI_SSPDMACR_TXDMAE_LSB    _u(1)
#define SPI_SSPDMACR_TXDMAE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPDMACR_RXDMAE
// Description : Receive DMA Enable. If this bit is set to 1, DMA for the
//               receive FIFO is enabled.
#define SPI_SSPDMACR_RXDMAE_RESET  _u(0x0)
#define SPI_SSPDMACR_RXDMAE_BITS   _u(0x00000001)
#define SPI_SSPDMACR_RXDMAE_MSB    _u(0)
#define SPI_SSPDMACR_RXDMAE_LSB    _u(0)
#define SPI_SSPDMACR_RXDMAE_ACCESS "RW"
// =============================================================================
// Register    : SPI_SSPPERIPHID0
// Description : Peripheral identification registers, SSPPeriphID0-3 on page
//               3-13
#define SPI_SSPPERIPHID0_OFFSET _u(0x00000fe0)
#define SPI_SSPPERIPHID0_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID0_RESET  _u(0x00000022)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID0_PARTNUMBER0
// Description : These bits read back as 0x22
#define SPI_SSPPERIPHID0_PARTNUMBER0_RESET  _u(0x22)
#define SPI_SSPPERIPHID0_PARTNUMBER0_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID0_PARTNUMBER0_MSB    _u(7)
#define SPI_SSPPERIPHID0_PARTNUMBER0_LSB    _u(0)
#define SPI_SSPPERIPHID0_PARTNUMBER0_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPERIPHID1
// Description : Peripheral identification registers, SSPPeriphID0-3 on page
//               3-13
#define SPI_SSPPERIPHID1_OFFSET _u(0x00000fe4)
#define SPI_SSPPERIPHID1_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID1_RESET  _u(0x00000010)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID1_DESIGNER0
// Description : These bits read back as 0x1
#define SPI_SSPPERIPHID1_DESIGNER0_RESET  _u(0x1)
#define SPI_SSPPERIPHID1_DESIGNER0_BITS   _u(0x000000f0)
#define SPI_SSPPERIPHID1_DESIGNER0_MSB    _u(7)
#define SPI_SSPPERIPHID1_DESIGNER0_LSB    _u(4)
#define SPI_SSPPERIPHID1_DESIGNER0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID1_PARTNUMBER1
// Description : These bits read back as 0x0
#define SPI_SSPPERIPHID1_PARTNUMBER1_RESET  _u(0x0)
#define SPI_SSPPERIPHID1_PARTNUMBER1_BITS   _u(0x0000000f)
#define SPI_SSPPERIPHID1_PARTNUMBER1_MSB    _u(3)
#define SPI_SSPPERIPHID1_PARTNUMBER1_LSB    _u(0)
#define SPI_SSPPERIPHID1_PARTNUMBER1_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPERIPHID2
// Description : Peripheral identification registers, SSPPeriphID0-3 on page
//               3-13
#define SPI_SSPPERIPHID2_OFFSET _u(0x00000fe8)
#define SPI_SSPPERIPHID2_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID2_RESET  _u(0x00000034)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID2_REVISION
// Description : These bits return the peripheral revision
#define SPI_SSPPERIPHID2_REVISION_RESET  _u(0x3)
#define SPI_SSPPERIPHID2_REVISION_BITS   _u(0x000000f0)
#define SPI_SSPPERIPHID2_REVISION_MSB    _u(7)
#define SPI_SSPPERIPHID2_REVISION_LSB    _u(4)
#define SPI_SSPPERIPHID2_REVISION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID2_DESIGNER1
// Description : These bits read back as 0x4
#define SPI_SSPPERIPHID2_DESIGNER1_RESET  _u(0x4)
#define SPI_SSPPERIPHID2_DESIGNER1_BITS   _u(0x0000000f)
#define SPI_SSPPERIPHID2_DESIGNER1_MSB    _u(3)
#define SPI_SSPPERIPHID2_DESIGNER1_LSB    _u(0)
#define SPI_SSPPERIPHID2_DESIGNER1_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPERIPHID3
// Description : Peripheral identification registers, SSPPeriphID0-3 on page
//               3-13
#define SPI_SSPPERIPHID3_OFFSET _u(0x00000fec)
#define SPI_SSPPERIPHID3_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPERIPHID3_CONFIGURATION
// Description : These bits read back as 0x00
#define SPI_SSPPERIPHID3_CONFIGURATION_RESET  _u(0x00)
#define SPI_SSPPERIPHID3_CONFIGURATION_BITS   _u(0x000000ff)
#define SPI_SSPPERIPHID3_CONFIGURATION_MSB    _u(7)
#define SPI_SSPPERIPHID3_CONFIGURATION_LSB    _u(0)
#define SPI_SSPPERIPHID3_CONFIGURATION_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPCELLID0
// Description : PrimeCell identification registers, SSPPCellID0-3 on page 3-16
#define SPI_SSPPCELLID0_OFFSET _u(0x00000ff0)
#define SPI_SSPPCELLID0_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID0_RESET  _u(0x0000000d)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPCELLID0_SSPPCELLID0
// Description : These bits read back as 0x0D
#define SPI_SSPPCELLID0_SSPPCELLID0_RESET  _u(0x0d)
#define SPI_SSPPCELLID0_SSPPCELLID0_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID0_SSPPCELLID0_MSB    _u(7)
#define SPI_SSPPCELLID0_SSPPCELLID0_LSB    _u(0)
#define SPI_SSPPCELLID0_SSPPCELLID0_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPCELLID1
// Description : PrimeCell identification registers, SSPPCellID0-3 on page 3-16
#define SPI_SSPPCELLID1_OFFSET _u(0x00000ff4)
#define SPI_SSPPCELLID1_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID1_RESET  _u(0x000000f0)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPCELLID1_SSPPCELLID1
// Description : These bits read back as 0xF0
#define SPI_SSPPCELLID1_SSPPCELLID1_RESET  _u(0xf0)
#define SPI_SSPPCELLID1_SSPPCELLID1_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID1_SSPPCELLID1_MSB    _u(7)
#define SPI_SSPPCELLID1_SSPPCELLID1_LSB    _u(0)
#define SPI_SSPPCELLID1_SSPPCELLID1_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPCELLID2
// Description : PrimeCell identification registers, SSPPCellID0-3 on page 3-16
#define SPI_SSPPCELLID2_OFFSET _u(0x00000ff8)
#define SPI_SSPPCELLID2_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID2_RESET  _u(0x00000005)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPCELLID2_SSPPCELLID2
// Description : These bits read back as 0x05
#define SPI_SSPPCELLID2_SSPPCELLID2_RESET  _u(0x05)
#define SPI_SSPPCELLID2_SSPPCELLID2_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID2_SSPPCELLID2_MSB    _u(7)
#define SPI_SSPPCELLID2_SSPPCELLID2_LSB    _u(0)
#define SPI_SSPPCELLID2_SSPPCELLID2_ACCESS "RO"
// =============================================================================
// Register    : SPI_SSPPCELLID3
// Description : PrimeCell identification registers, SSPPCellID0-3 on page 3-16
#define SPI_SSPPCELLID3_OFFSET _u(0x00000ffc)
#define SPI_SSPPCELLID3_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID3_RESET  _u(0x000000b1)
// -----------------------------------------------------------------------------
// Field       : SPI_SSPPCELLID3_SSPPCELLID3
// Description : These bits read back as 0xB1
#define SPI_SSPPCELLID3_SSPPCELLID3_RESET  _u(0xb1)
#define SPI_SSPPCELLID3_SSPPCELLID3_BITS   _u(0x000000ff)
#define SPI_SSPPCELLID3_SSPPCELLID3_MSB    _u(7)
#define SPI_SSPPCELLID3_SSPPCELLID3_LSB    _u(0)
#define SPI_SSPPCELLID3_SSPPCELLID3_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_SPI_DEFINED
