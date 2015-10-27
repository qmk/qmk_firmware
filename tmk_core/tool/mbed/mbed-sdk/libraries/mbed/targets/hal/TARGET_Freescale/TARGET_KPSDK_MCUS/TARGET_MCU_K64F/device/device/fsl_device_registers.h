/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || \
    defined(CPU_MK02FN64VLF10) || defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10))

    #define K02F12810_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK02F12810/MK02F12810.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK02F12810/MK02F12810_adc.h"
    #include "device/MK02F12810/MK02F12810_cmp.h"
    #include "device/MK02F12810/MK02F12810_crc.h"
    #include "device/MK02F12810/MK02F12810_dac.h"
    #include "device/MK02F12810/MK02F12810_dma.h"
    #include "device/MK02F12810/MK02F12810_dmamux.h"
    #include "device/MK02F12810/MK02F12810_ewm.h"
    #include "device/MK02F12810/MK02F12810_fmc.h"
    #include "device/MK02F12810/MK02F12810_ftfa.h"
    #include "device/MK02F12810/MK02F12810_ftm.h"
    #include "device/MK02F12810/MK02F12810_gpio.h"
    #include "device/MK02F12810/MK02F12810_i2c.h"
    #include "device/MK02F12810/MK02F12810_llwu.h"
    #include "device/MK02F12810/MK02F12810_lptmr.h"
    #include "device/MK02F12810/MK02F12810_mcg.h"
    #include "device/MK02F12810/MK02F12810_mcm.h"
    #include "device/MK02F12810/MK02F12810_nv.h"
    #include "device/MK02F12810/MK02F12810_osc.h"
    #include "device/MK02F12810/MK02F12810_pdb.h"
    #include "device/MK02F12810/MK02F12810_pit.h"
    #include "device/MK02F12810/MK02F12810_pmc.h"
    #include "device/MK02F12810/MK02F12810_port.h"
    #include "device/MK02F12810/MK02F12810_rcm.h"
    #include "device/MK02F12810/MK02F12810_sim.h"
    #include "device/MK02F12810/MK02F12810_smc.h"
    #include "device/MK02F12810/MK02F12810_spi.h"
    #include "device/MK02F12810/MK02F12810_uart.h"
    #include "device/MK02F12810/MK02F12810_vref.h"
    #include "device/MK02F12810/MK02F12810_wdog.h"

#elif (defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || \
    defined(CPU_MK20DN64VMP5) || defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || \
    defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || defined(CPU_MK20DX64VLH5) || \
    defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || \
    defined(CPU_MK20DN64VFM5) || defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || \
    defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || \
    defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5))

    #define K20D5_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK20D5/MK20D5.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK20D5/MK20D5_adc.h"
    #include "device/MK20D5/MK20D5_cmp.h"
    #include "device/MK20D5/MK20D5_cmt.h"
    #include "device/MK20D5/MK20D5_crc.h"
    #include "device/MK20D5/MK20D5_dma.h"
    #include "device/MK20D5/MK20D5_dmamux.h"
    #include "device/MK20D5/MK20D5_ewm.h"
    #include "device/MK20D5/MK20D5_fmc.h"
    #include "device/MK20D5/MK20D5_ftfl.h"
    #include "device/MK20D5/MK20D5_ftm.h"
    #include "device/MK20D5/MK20D5_gpio.h"
    #include "device/MK20D5/MK20D5_i2c.h"
    #include "device/MK20D5/MK20D5_i2s.h"
    #include "device/MK20D5/MK20D5_llwu.h"
    #include "device/MK20D5/MK20D5_lptmr.h"
    #include "device/MK20D5/MK20D5_mcg.h"
    #include "device/MK20D5/MK20D5_nv.h"
    #include "device/MK20D5/MK20D5_osc.h"
    #include "device/MK20D5/MK20D5_pdb.h"
    #include "device/MK20D5/MK20D5_pit.h"
    #include "device/MK20D5/MK20D5_pmc.h"
    #include "device/MK20D5/MK20D5_port.h"
    #include "device/MK20D5/MK20D5_rcm.h"
    #include "device/MK20D5/MK20D5_rfsys.h"
    #include "device/MK20D5/MK20D5_rfvbat.h"
    #include "device/MK20D5/MK20D5_rtc.h"
    #include "device/MK20D5/MK20D5_sim.h"
    #include "device/MK20D5/MK20D5_smc.h"
    #include "device/MK20D5/MK20D5_spi.h"
    #include "device/MK20D5/MK20D5_tsi.h"
    #include "device/MK20D5/MK20D5_uart.h"
    #include "device/MK20D5/MK20D5_usb.h"
    #include "device/MK20D5/MK20D5_usbdcd.h"
    #include "device/MK20D5/MK20D5_vref.h"
    #include "device/MK20D5/MK20D5_wdog.h"

#elif (defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || \
    defined(CPU_MK22FN128VMP10))

    #define K22F12810_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK22F12810/MK22F12810.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK22F12810/MK22F12810_adc.h"
    #include "device/MK22F12810/MK22F12810_cmp.h"
    #include "device/MK22F12810/MK22F12810_crc.h"
    #include "device/MK22F12810/MK22F12810_dac.h"
    #include "device/MK22F12810/MK22F12810_dma.h"
    #include "device/MK22F12810/MK22F12810_dmamux.h"
    #include "device/MK22F12810/MK22F12810_ewm.h"
    #include "device/MK22F12810/MK22F12810_fmc.h"
    #include "device/MK22F12810/MK22F12810_ftfa.h"
    #include "device/MK22F12810/MK22F12810_ftm.h"
    #include "device/MK22F12810/MK22F12810_gpio.h"
    #include "device/MK22F12810/MK22F12810_i2c.h"
    #include "device/MK22F12810/MK22F12810_i2s.h"
    #include "device/MK22F12810/MK22F12810_llwu.h"
    #include "device/MK22F12810/MK22F12810_lptmr.h"
    #include "device/MK22F12810/MK22F12810_lpuart.h"
    #include "device/MK22F12810/MK22F12810_mcg.h"
    #include "device/MK22F12810/MK22F12810_mcm.h"
    #include "device/MK22F12810/MK22F12810_nv.h"
    #include "device/MK22F12810/MK22F12810_osc.h"
    #include "device/MK22F12810/MK22F12810_pdb.h"
    #include "device/MK22F12810/MK22F12810_pit.h"
    #include "device/MK22F12810/MK22F12810_pmc.h"
    #include "device/MK22F12810/MK22F12810_port.h"
    #include "device/MK22F12810/MK22F12810_rcm.h"
    #include "device/MK22F12810/MK22F12810_rfsys.h"
    #include "device/MK22F12810/MK22F12810_rfvbat.h"
    #include "device/MK22F12810/MK22F12810_rtc.h"
    #include "device/MK22F12810/MK22F12810_sim.h"
    #include "device/MK22F12810/MK22F12810_smc.h"
    #include "device/MK22F12810/MK22F12810_spi.h"
    #include "device/MK22F12810/MK22F12810_uart.h"
    #include "device/MK22F12810/MK22F12810_usb.h"
    #include "device/MK22F12810/MK22F12810_vref.h"
    #include "device/MK22F12810/MK22F12810_wdog.h"

#elif (defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || \
    defined(CPU_MK22FN256VMP12))

    #define K22F25612_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK22F25612/MK22F25612.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK22F25612/MK22F25612_adc.h"
    #include "device/MK22F25612/MK22F25612_cmp.h"
    #include "device/MK22F25612/MK22F25612_crc.h"
    #include "device/MK22F25612/MK22F25612_dac.h"
    #include "device/MK22F25612/MK22F25612_dma.h"
    #include "device/MK22F25612/MK22F25612_dmamux.h"
    #include "device/MK22F25612/MK22F25612_ewm.h"
    #include "device/MK22F25612/MK22F25612_fmc.h"
    #include "device/MK22F25612/MK22F25612_ftfa.h"
    #include "device/MK22F25612/MK22F25612_ftm.h"
    #include "device/MK22F25612/MK22F25612_gpio.h"
    #include "device/MK22F25612/MK22F25612_i2c.h"
    #include "device/MK22F25612/MK22F25612_i2s.h"
    #include "device/MK22F25612/MK22F25612_llwu.h"
    #include "device/MK22F25612/MK22F25612_lptmr.h"
    #include "device/MK22F25612/MK22F25612_lpuart.h"
    #include "device/MK22F25612/MK22F25612_mcg.h"
    #include "device/MK22F25612/MK22F25612_mcm.h"
    #include "device/MK22F25612/MK22F25612_nv.h"
    #include "device/MK22F25612/MK22F25612_osc.h"
    #include "device/MK22F25612/MK22F25612_pdb.h"
    #include "device/MK22F25612/MK22F25612_pit.h"
    #include "device/MK22F25612/MK22F25612_pmc.h"
    #include "device/MK22F25612/MK22F25612_port.h"
    #include "device/MK22F25612/MK22F25612_rcm.h"
    #include "device/MK22F25612/MK22F25612_rfsys.h"
    #include "device/MK22F25612/MK22F25612_rfvbat.h"
    #include "device/MK22F25612/MK22F25612_rng.h"
    #include "device/MK22F25612/MK22F25612_rtc.h"
    #include "device/MK22F25612/MK22F25612_sim.h"
    #include "device/MK22F25612/MK22F25612_smc.h"
    #include "device/MK22F25612/MK22F25612_spi.h"
    #include "device/MK22F25612/MK22F25612_uart.h"
    #include "device/MK22F25612/MK22F25612_usb.h"
    #include "device/MK22F25612/MK22F25612_vref.h"
    #include "device/MK22F25612/MK22F25612_wdog.h"

#elif (defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12))

    #define K22F51212_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK22F51212/MK22F51212.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK22F51212/MK22F51212_adc.h"
    #include "device/MK22F51212/MK22F51212_cmp.h"
    #include "device/MK22F51212/MK22F51212_crc.h"
    #include "device/MK22F51212/MK22F51212_dac.h"
    #include "device/MK22F51212/MK22F51212_dma.h"
    #include "device/MK22F51212/MK22F51212_dmamux.h"
    #include "device/MK22F51212/MK22F51212_ewm.h"
    #include "device/MK22F51212/MK22F51212_fb.h"
    #include "device/MK22F51212/MK22F51212_fmc.h"
    #include "device/MK22F51212/MK22F51212_ftfa.h"
    #include "device/MK22F51212/MK22F51212_ftm.h"
    #include "device/MK22F51212/MK22F51212_gpio.h"
    #include "device/MK22F51212/MK22F51212_i2c.h"
    #include "device/MK22F51212/MK22F51212_i2s.h"
    #include "device/MK22F51212/MK22F51212_llwu.h"
    #include "device/MK22F51212/MK22F51212_lptmr.h"
    #include "device/MK22F51212/MK22F51212_lpuart.h"
    #include "device/MK22F51212/MK22F51212_mcg.h"
    #include "device/MK22F51212/MK22F51212_mcm.h"
    #include "device/MK22F51212/MK22F51212_nv.h"
    #include "device/MK22F51212/MK22F51212_osc.h"
    #include "device/MK22F51212/MK22F51212_pdb.h"
    #include "device/MK22F51212/MK22F51212_pit.h"
    #include "device/MK22F51212/MK22F51212_pmc.h"
    #include "device/MK22F51212/MK22F51212_port.h"
    #include "device/MK22F51212/MK22F51212_rcm.h"
    #include "device/MK22F51212/MK22F51212_rfsys.h"
    #include "device/MK22F51212/MK22F51212_rfvbat.h"
    #include "device/MK22F51212/MK22F51212_rng.h"
    #include "device/MK22F51212/MK22F51212_rtc.h"
    #include "device/MK22F51212/MK22F51212_sim.h"
    #include "device/MK22F51212/MK22F51212_smc.h"
    #include "device/MK22F51212/MK22F51212_spi.h"
    #include "device/MK22F51212/MK22F51212_uart.h"
    #include "device/MK22F51212/MK22F51212_usb.h"
    #include "device/MK22F51212/MK22F51212_vref.h"
    #include "device/MK22F51212/MK22F51212_wdog.h"

#elif (defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLQ12))

    #define K24F12_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK24F12/MK24F12.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK24F12/MK24F12_adc.h"
    #include "device/MK24F12/MK24F12_aips.h"
    #include "device/MK24F12/MK24F12_axbs.h"
    #include "device/MK24F12/MK24F12_can.h"
    #include "device/MK24F12/MK24F12_cau.h"
    #include "device/MK24F12/MK24F12_cmp.h"
    #include "device/MK24F12/MK24F12_cmt.h"
    #include "device/MK24F12/MK24F12_crc.h"
    #include "device/MK24F12/MK24F12_dac.h"
    #include "device/MK24F12/MK24F12_dma.h"
    #include "device/MK24F12/MK24F12_dmamux.h"
    #include "device/MK24F12/MK24F12_ewm.h"
    #include "device/MK24F12/MK24F12_fb.h"
    #include "device/MK24F12/MK24F12_fmc.h"
    #include "device/MK24F12/MK24F12_ftfe.h"
    #include "device/MK24F12/MK24F12_ftm.h"
    #include "device/MK24F12/MK24F12_gpio.h"
    #include "device/MK24F12/MK24F12_i2c.h"
    #include "device/MK24F12/MK24F12_i2s.h"
    #include "device/MK24F12/MK24F12_llwu.h"
    #include "device/MK24F12/MK24F12_lptmr.h"
    #include "device/MK24F12/MK24F12_mcg.h"
    #include "device/MK24F12/MK24F12_mcm.h"
    #include "device/MK24F12/MK24F12_mpu.h"
    #include "device/MK24F12/MK24F12_nv.h"
    #include "device/MK24F12/MK24F12_osc.h"
    #include "device/MK24F12/MK24F12_pdb.h"
    #include "device/MK24F12/MK24F12_pit.h"
    #include "device/MK24F12/MK24F12_pmc.h"
    #include "device/MK24F12/MK24F12_port.h"
    #include "device/MK24F12/MK24F12_rcm.h"
    #include "device/MK24F12/MK24F12_rfsys.h"
    #include "device/MK24F12/MK24F12_rfvbat.h"
    #include "device/MK24F12/MK24F12_rng.h"
    #include "device/MK24F12/MK24F12_rtc.h"
    #include "device/MK24F12/MK24F12_sdhc.h"
    #include "device/MK24F12/MK24F12_sim.h"
    #include "device/MK24F12/MK24F12_smc.h"
    #include "device/MK24F12/MK24F12_spi.h"
    #include "device/MK24F12/MK24F12_uart.h"
    #include "device/MK24F12/MK24F12_usb.h"
    #include "device/MK24F12/MK24F12_usbdcd.h"
    #include "device/MK24F12/MK24F12_vref.h"
    #include "device/MK24F12/MK24F12_wdog.h"

#elif (defined(CPU_MK24FN256VDC12))

    #define K24F25612_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK24F25612/MK24F25612.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK24F25612/MK24F25612_adc.h"
    #include "device/MK24F25612/MK24F25612_aips.h"
    #include "device/MK24F25612/MK24F25612_cmp.h"
    #include "device/MK24F25612/MK24F25612_cmt.h"
    #include "device/MK24F25612/MK24F25612_crc.h"
    #include "device/MK24F25612/MK24F25612_dac.h"
    #include "device/MK24F25612/MK24F25612_dma.h"
    #include "device/MK24F25612/MK24F25612_dmamux.h"
    #include "device/MK24F25612/MK24F25612_ewm.h"
    #include "device/MK24F25612/MK24F25612_fmc.h"
    #include "device/MK24F25612/MK24F25612_ftfa.h"
    #include "device/MK24F25612/MK24F25612_ftm.h"
    #include "device/MK24F25612/MK24F25612_gpio.h"
    #include "device/MK24F25612/MK24F25612_i2c.h"
    #include "device/MK24F25612/MK24F25612_i2s.h"
    #include "device/MK24F25612/MK24F25612_llwu.h"
    #include "device/MK24F25612/MK24F25612_lptmr.h"
    #include "device/MK24F25612/MK24F25612_mcg.h"
    #include "device/MK24F25612/MK24F25612_mcm.h"
    #include "device/MK24F25612/MK24F25612_osc.h"
    #include "device/MK24F25612/MK24F25612_pdb.h"
    #include "device/MK24F25612/MK24F25612_pit.h"
    #include "device/MK24F25612/MK24F25612_pmc.h"
    #include "device/MK24F25612/MK24F25612_port.h"
    #include "device/MK24F25612/MK24F25612_rcm.h"
    #include "device/MK24F25612/MK24F25612_rfsys.h"
    #include "device/MK24F25612/MK24F25612_rfvbat.h"
    #include "device/MK24F25612/MK24F25612_rng.h"
    #include "device/MK24F25612/MK24F25612_rtc.h"
    #include "device/MK24F25612/MK24F25612_sim.h"
    #include "device/MK24F25612/MK24F25612_smc.h"
    #include "device/MK24F25612/MK24F25612_spi.h"
    #include "device/MK24F25612/MK24F25612_uart.h"
    #include "device/MK24F25612/MK24F25612_usb.h"
    #include "device/MK24F25612/MK24F25612_usbdcd.h"
    #include "device/MK24F25612/MK24F25612_vref.h"
    #include "device/MK24F25612/MK24F25612_wdog.h"

#elif (defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12))

    #define K63F12_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK63F12/MK63F12.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK63F12/MK63F12_adc.h"
    #include "device/MK63F12/MK63F12_aips.h"
    #include "device/MK63F12/MK63F12_axbs.h"
    #include "device/MK63F12/MK63F12_can.h"
    #include "device/MK63F12/MK63F12_cau.h"
    #include "device/MK63F12/MK63F12_cmp.h"
    #include "device/MK63F12/MK63F12_cmt.h"
    #include "device/MK63F12/MK63F12_crc.h"
    #include "device/MK63F12/MK63F12_dac.h"
    #include "device/MK63F12/MK63F12_dma.h"
    #include "device/MK63F12/MK63F12_dmamux.h"
    #include "device/MK63F12/MK63F12_enet.h"
    #include "device/MK63F12/MK63F12_ewm.h"
    #include "device/MK63F12/MK63F12_fb.h"
    #include "device/MK63F12/MK63F12_fmc.h"
    #include "device/MK63F12/MK63F12_ftfe.h"
    #include "device/MK63F12/MK63F12_ftm.h"
    #include "device/MK63F12/MK63F12_gpio.h"
    #include "device/MK63F12/MK63F12_i2c.h"
    #include "device/MK63F12/MK63F12_i2s.h"
    #include "device/MK63F12/MK63F12_llwu.h"
    #include "device/MK63F12/MK63F12_lptmr.h"
    #include "device/MK63F12/MK63F12_mcg.h"
    #include "device/MK63F12/MK63F12_mcm.h"
    #include "device/MK63F12/MK63F12_mpu.h"
    #include "device/MK63F12/MK63F12_nv.h"
    #include "device/MK63F12/MK63F12_osc.h"
    #include "device/MK63F12/MK63F12_pdb.h"
    #include "device/MK63F12/MK63F12_pit.h"
    #include "device/MK63F12/MK63F12_pmc.h"
    #include "device/MK63F12/MK63F12_port.h"
    #include "device/MK63F12/MK63F12_rcm.h"
    #include "device/MK63F12/MK63F12_rfsys.h"
    #include "device/MK63F12/MK63F12_rfvbat.h"
    #include "device/MK63F12/MK63F12_rng.h"
    #include "device/MK63F12/MK63F12_rtc.h"
    #include "device/MK63F12/MK63F12_sdhc.h"
    #include "device/MK63F12/MK63F12_sim.h"
    #include "device/MK63F12/MK63F12_smc.h"
    #include "device/MK63F12/MK63F12_spi.h"
    #include "device/MK63F12/MK63F12_uart.h"
    #include "device/MK63F12/MK63F12_usb.h"
    #include "device/MK63F12/MK63F12_usbdcd.h"
    #include "device/MK63F12/MK63F12_vref.h"
    #include "device/MK63F12/MK63F12_wdog.h"

#elif (defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12))

    #define K64F12_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK64F12/MK64F12.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK64F12/MK64F12_adc.h"
    #include "device/MK64F12/MK64F12_aips.h"
    #include "device/MK64F12/MK64F12_axbs.h"
    #include "device/MK64F12/MK64F12_can.h"
    #include "device/MK64F12/MK64F12_cau.h"
    #include "device/MK64F12/MK64F12_cmp.h"
    #include "device/MK64F12/MK64F12_cmt.h"
    #include "device/MK64F12/MK64F12_crc.h"
    #include "device/MK64F12/MK64F12_dac.h"
    #include "device/MK64F12/MK64F12_dma.h"
    #include "device/MK64F12/MK64F12_dmamux.h"
    #include "device/MK64F12/MK64F12_enet.h"
    #include "device/MK64F12/MK64F12_ewm.h"
    #include "device/MK64F12/MK64F12_fb.h"
    #include "device/MK64F12/MK64F12_fmc.h"
    #include "device/MK64F12/MK64F12_ftfe.h"
    #include "device/MK64F12/MK64F12_ftm.h"
    #include "device/MK64F12/MK64F12_gpio.h"
    #include "device/MK64F12/MK64F12_i2c.h"
    #include "device/MK64F12/MK64F12_i2s.h"
    #include "device/MK64F12/MK64F12_llwu.h"
    #include "device/MK64F12/MK64F12_lptmr.h"
    #include "device/MK64F12/MK64F12_mcg.h"
    #include "device/MK64F12/MK64F12_mcm.h"
    #include "device/MK64F12/MK64F12_mpu.h"
    #include "device/MK64F12/MK64F12_nv.h"
    #include "device/MK64F12/MK64F12_osc.h"
    #include "device/MK64F12/MK64F12_pdb.h"
    #include "device/MK64F12/MK64F12_pit.h"
    #include "device/MK64F12/MK64F12_pmc.h"
    #include "device/MK64F12/MK64F12_port.h"
    #include "device/MK64F12/MK64F12_rcm.h"
    #include "device/MK64F12/MK64F12_rfsys.h"
    #include "device/MK64F12/MK64F12_rfvbat.h"
    #include "device/MK64F12/MK64F12_rng.h"
    #include "device/MK64F12/MK64F12_rtc.h"
    #include "device/MK64F12/MK64F12_sdhc.h"
    #include "device/MK64F12/MK64F12_sim.h"
    #include "device/MK64F12/MK64F12_smc.h"
    #include "device/MK64F12/MK64F12_spi.h"
    #include "device/MK64F12/MK64F12_uart.h"
    #include "device/MK64F12/MK64F12_usb.h"
    #include "device/MK64F12/MK64F12_usbdcd.h"
    #include "device/MK64F12/MK64F12_vref.h"
    #include "device/MK64F12/MK64F12_wdog.h"

#elif (defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || \
    defined(CPU_MK65FX1M0VMI18))

    #define K65F18_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK65F18/MK65F18.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK65F18/MK65F18_adc.h"
    #include "device/MK65F18/MK65F18_aips.h"
    #include "device/MK65F18/MK65F18_axbs.h"
    #include "device/MK65F18/MK65F18_can.h"
    #include "device/MK65F18/MK65F18_cau.h"
    #include "device/MK65F18/MK65F18_cmp.h"
    #include "device/MK65F18/MK65F18_cmt.h"
    #include "device/MK65F18/MK65F18_crc.h"
    #include "device/MK65F18/MK65F18_dac.h"
    #include "device/MK65F18/MK65F18_dma.h"
    #include "device/MK65F18/MK65F18_dmamux.h"
    #include "device/MK65F18/MK65F18_enet.h"
    #include "device/MK65F18/MK65F18_ewm.h"
    #include "device/MK65F18/MK65F18_fb.h"
    #include "device/MK65F18/MK65F18_fmc.h"
    #include "device/MK65F18/MK65F18_ftfe.h"
    #include "device/MK65F18/MK65F18_ftm.h"
    #include "device/MK65F18/MK65F18_gpio.h"
    #include "device/MK65F18/MK65F18_i2c.h"
    #include "device/MK65F18/MK65F18_i2s.h"
    #include "device/MK65F18/MK65F18_llwu.h"
    #include "device/MK65F18/MK65F18_lmem.h"
    #include "device/MK65F18/MK65F18_lptmr.h"
    #include "device/MK65F18/MK65F18_lpuart.h"
    #include "device/MK65F18/MK65F18_mcg.h"
    #include "device/MK65F18/MK65F18_mcm.h"
    #include "device/MK65F18/MK65F18_mpu.h"
    #include "device/MK65F18/MK65F18_nv.h"
    #include "device/MK65F18/MK65F18_osc.h"
    #include "device/MK65F18/MK65F18_pdb.h"
    #include "device/MK65F18/MK65F18_pit.h"
    #include "device/MK65F18/MK65F18_pmc.h"
    #include "device/MK65F18/MK65F18_port.h"
    #include "device/MK65F18/MK65F18_rcm.h"
    #include "device/MK65F18/MK65F18_rfsys.h"
    #include "device/MK65F18/MK65F18_rfvbat.h"
    #include "device/MK65F18/MK65F18_rng.h"
    #include "device/MK65F18/MK65F18_rtc.h"
    #include "device/MK65F18/MK65F18_sdhc.h"
    #include "device/MK65F18/MK65F18_sdram.h"
    #include "device/MK65F18/MK65F18_sim.h"
    #include "device/MK65F18/MK65F18_smc.h"
    #include "device/MK65F18/MK65F18_spi.h"
    #include "device/MK65F18/MK65F18_tpm.h"
    #include "device/MK65F18/MK65F18_tsi.h"
    #include "device/MK65F18/MK65F18_uart.h"
    #include "device/MK65F18/MK65F18_usb.h"
    #include "device/MK65F18/MK65F18_usbdcd.h"
    #include "device/MK65F18/MK65F18_usbhs.h"
    #include "device/MK65F18/MK65F18_usbhsdcd.h"
    #include "device/MK65F18/MK65F18_usbphy.h"
    #include "device/MK65F18/MK65F18_vref.h"
    #include "device/MK65F18/MK65F18_wdog.h"

#elif (defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || \
    defined(CPU_MK66FX1M0VMD18))

    #define K66F18_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK66F18/MK66F18.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK66F18/MK66F18_adc.h"
    #include "device/MK66F18/MK66F18_aips.h"
    #include "device/MK66F18/MK66F18_axbs.h"
    #include "device/MK66F18/MK66F18_can.h"
    #include "device/MK66F18/MK66F18_cau.h"
    #include "device/MK66F18/MK66F18_cmp.h"
    #include "device/MK66F18/MK66F18_cmt.h"
    #include "device/MK66F18/MK66F18_crc.h"
    #include "device/MK66F18/MK66F18_dac.h"
    #include "device/MK66F18/MK66F18_dma.h"
    #include "device/MK66F18/MK66F18_dmamux.h"
    #include "device/MK66F18/MK66F18_enet.h"
    #include "device/MK66F18/MK66F18_ewm.h"
    #include "device/MK66F18/MK66F18_fb.h"
    #include "device/MK66F18/MK66F18_fmc.h"
    #include "device/MK66F18/MK66F18_ftfe.h"
    #include "device/MK66F18/MK66F18_ftm.h"
    #include "device/MK66F18/MK66F18_gpio.h"
    #include "device/MK66F18/MK66F18_i2c.h"
    #include "device/MK66F18/MK66F18_i2s.h"
    #include "device/MK66F18/MK66F18_llwu.h"
    #include "device/MK66F18/MK66F18_lmem.h"
    #include "device/MK66F18/MK66F18_lptmr.h"
    #include "device/MK66F18/MK66F18_lpuart.h"
    #include "device/MK66F18/MK66F18_mcg.h"
    #include "device/MK66F18/MK66F18_mcm.h"
    #include "device/MK66F18/MK66F18_mpu.h"
    #include "device/MK66F18/MK66F18_nv.h"
    #include "device/MK66F18/MK66F18_osc.h"
    #include "device/MK66F18/MK66F18_pdb.h"
    #include "device/MK66F18/MK66F18_pit.h"
    #include "device/MK66F18/MK66F18_pmc.h"
    #include "device/MK66F18/MK66F18_port.h"
    #include "device/MK66F18/MK66F18_rcm.h"
    #include "device/MK66F18/MK66F18_rfsys.h"
    #include "device/MK66F18/MK66F18_rfvbat.h"
    #include "device/MK66F18/MK66F18_rng.h"
    #include "device/MK66F18/MK66F18_rtc.h"
    #include "device/MK66F18/MK66F18_sdhc.h"
    #include "device/MK66F18/MK66F18_sdram.h"
    #include "device/MK66F18/MK66F18_sim.h"
    #include "device/MK66F18/MK66F18_smc.h"
    #include "device/MK66F18/MK66F18_spi.h"
    #include "device/MK66F18/MK66F18_tpm.h"
    #include "device/MK66F18/MK66F18_tsi.h"
    #include "device/MK66F18/MK66F18_uart.h"
    #include "device/MK66F18/MK66F18_usb.h"
    #include "device/MK66F18/MK66F18_usbdcd.h"
    #include "device/MK66F18/MK66F18_usbhs.h"
    #include "device/MK66F18/MK66F18_usbhsdcd.h"
    #include "device/MK66F18/MK66F18_usbphy.h"
    #include "device/MK66F18/MK66F18_vref.h"
    #include "device/MK66F18/MK66F18_wdog.h"

#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F12_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK70F12/MK70F12.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK70F12/MK70F12_adc.h"
    #include "device/MK70F12/MK70F12_aips.h"
    #include "device/MK70F12/MK70F12_axbs.h"
    #include "device/MK70F12/MK70F12_can.h"
    #include "device/MK70F12/MK70F12_cau.h"
    #include "device/MK70F12/MK70F12_cmp.h"
    #include "device/MK70F12/MK70F12_cmt.h"
    #include "device/MK70F12/MK70F12_crc.h"
    #include "device/MK70F12/MK70F12_dac.h"
    #include "device/MK70F12/MK70F12_ddr.h"
    #include "device/MK70F12/MK70F12_dma.h"
    #include "device/MK70F12/MK70F12_dmamux.h"
    #include "device/MK70F12/MK70F12_enet.h"
    #include "device/MK70F12/MK70F12_ewm.h"
    #include "device/MK70F12/MK70F12_fb.h"
    #include "device/MK70F12/MK70F12_fmc.h"
    #include "device/MK70F12/MK70F12_ftfe.h"
    #include "device/MK70F12/MK70F12_ftm.h"
    #include "device/MK70F12/MK70F12_gpio.h"
    #include "device/MK70F12/MK70F12_i2c.h"
    #include "device/MK70F12/MK70F12_i2s.h"
    #include "device/MK70F12/MK70F12_lcdc.h"
    #include "device/MK70F12/MK70F12_llwu.h"
    #include "device/MK70F12/MK70F12_lmem.h"
    #include "device/MK70F12/MK70F12_lptmr.h"
    #include "device/MK70F12/MK70F12_mcg.h"
    #include "device/MK70F12/MK70F12_mcm.h"
    #include "device/MK70F12/MK70F12_mpu.h"
    #include "device/MK70F12/MK70F12_nfc.h"
    #include "device/MK70F12/MK70F12_nv.h"
    #include "device/MK70F12/MK70F12_osc.h"
    #include "device/MK70F12/MK70F12_pdb.h"
    #include "device/MK70F12/MK70F12_pit.h"
    #include "device/MK70F12/MK70F12_pmc.h"
    #include "device/MK70F12/MK70F12_port.h"
    #include "device/MK70F12/MK70F12_rcm.h"
    #include "device/MK70F12/MK70F12_rfsys.h"
    #include "device/MK70F12/MK70F12_rfvbat.h"
    #include "device/MK70F12/MK70F12_rng.h"
    #include "device/MK70F12/MK70F12_rtc.h"
    #include "device/MK70F12/MK70F12_sdhc.h"
    #include "device/MK70F12/MK70F12_sim.h"
    #include "device/MK70F12/MK70F12_smc.h"
    #include "device/MK70F12/MK70F12_spi.h"
    #include "device/MK70F12/MK70F12_tsi.h"
    #include "device/MK70F12/MK70F12_uart.h"
    #include "device/MK70F12/MK70F12_usb.h"
    #include "device/MK70F12/MK70F12_usbdcd.h"
    #include "device/MK70F12/MK70F12_usbhs.h"
    #include "device/MK70F12/MK70F12_vref.h"
    #include "device/MK70F12/MK70F12_wdog.h"

#elif (defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || \
    defined(CPU_MK70FX512VMF15) || defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || \
    defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MK70F15/MK70F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MK70F15/MK70F15_adc.h"
    #include "device/MK70F15/MK70F15_aips.h"
    #include "device/MK70F15/MK70F15_axbs.h"
    #include "device/MK70F15/MK70F15_can.h"
    #include "device/MK70F15/MK70F15_cau.h"
    #include "device/MK70F15/MK70F15_cmp.h"
    #include "device/MK70F15/MK70F15_cmt.h"
    #include "device/MK70F15/MK70F15_crc.h"
    #include "device/MK70F15/MK70F15_dac.h"
    #include "device/MK70F15/MK70F15_ddr.h"
    #include "device/MK70F15/MK70F15_dma.h"
    #include "device/MK70F15/MK70F15_dmamux.h"
    #include "device/MK70F15/MK70F15_enet.h"
    #include "device/MK70F15/MK70F15_ewm.h"
    #include "device/MK70F15/MK70F15_fb.h"
    #include "device/MK70F15/MK70F15_fmc.h"
    #include "device/MK70F15/MK70F15_ftfe.h"
    #include "device/MK70F15/MK70F15_ftm.h"
    #include "device/MK70F15/MK70F15_gpio.h"
    #include "device/MK70F15/MK70F15_i2c.h"
    #include "device/MK70F15/MK70F15_i2s.h"
    #include "device/MK70F15/MK70F15_lcdc.h"
    #include "device/MK70F15/MK70F15_llwu.h"
    #include "device/MK70F15/MK70F15_lmem.h"
    #include "device/MK70F15/MK70F15_lptmr.h"
    #include "device/MK70F15/MK70F15_mcg.h"
    #include "device/MK70F15/MK70F15_mcm.h"
    #include "device/MK70F15/MK70F15_mpu.h"
    #include "device/MK70F15/MK70F15_nfc.h"
    #include "device/MK70F15/MK70F15_nv.h"
    #include "device/MK70F15/MK70F15_osc.h"
    #include "device/MK70F15/MK70F15_pdb.h"
    #include "device/MK70F15/MK70F15_pit.h"
    #include "device/MK70F15/MK70F15_pmc.h"
    #include "device/MK70F15/MK70F15_port.h"
    #include "device/MK70F15/MK70F15_rcm.h"
    #include "device/MK70F15/MK70F15_rfsys.h"
    #include "device/MK70F15/MK70F15_rfvbat.h"
    #include "device/MK70F15/MK70F15_rng.h"
    #include "device/MK70F15/MK70F15_rtc.h"
    #include "device/MK70F15/MK70F15_sdhc.h"
    #include "device/MK70F15/MK70F15_sim.h"
    #include "device/MK70F15/MK70F15_smc.h"
    #include "device/MK70F15/MK70F15_spi.h"
    #include "device/MK70F15/MK70F15_tsi.h"
    #include "device/MK70F15/MK70F15_uart.h"
    #include "device/MK70F15/MK70F15_usb.h"
    #include "device/MK70F15/MK70F15_usbdcd.h"
    #include "device/MK70F15/MK70F15_usbhs.h"
    #include "device/MK70F15/MK70F15_vref.h"
    #include "device/MK70F15/MK70F15_wdog.h"

#elif (defined(CPU_MKL02Z32CAF4) || defined(CPU_MKL02Z8VFG4) || defined(CPU_MKL02Z16VFG4) || \
    defined(CPU_MKL02Z32VFG4) || defined(CPU_MKL02Z16VFK4) || defined(CPU_MKL02Z32VFK4) || \
    defined(CPU_MKL02Z16VFM4) || defined(CPU_MKL02Z32VFM4))

    #define KL02Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL02Z4/MKL02Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL02Z4/MKL02Z4_adc.h"
    #include "device/MKL02Z4/MKL02Z4_cmp.h"
    #include "device/MKL02Z4/MKL02Z4_fgpio.h"
    #include "device/MKL02Z4/MKL02Z4_ftfa.h"
    #include "device/MKL02Z4/MKL02Z4_gpio.h"
    #include "device/MKL02Z4/MKL02Z4_i2c.h"
    #include "device/MKL02Z4/MKL02Z4_lptmr.h"
    #include "device/MKL02Z4/MKL02Z4_mcg.h"
    #include "device/MKL02Z4/MKL02Z4_mcm.h"
    #include "device/MKL02Z4/MKL02Z4_mtb.h"
    #include "device/MKL02Z4/MKL02Z4_mtbdwt.h"
    #include "device/MKL02Z4/MKL02Z4_nv.h"
    #include "device/MKL02Z4/MKL02Z4_osc.h"
    #include "device/MKL02Z4/MKL02Z4_pmc.h"
    #include "device/MKL02Z4/MKL02Z4_port.h"
    #include "device/MKL02Z4/MKL02Z4_rcm.h"
    #include "device/MKL02Z4/MKL02Z4_rom.h"
    #include "device/MKL02Z4/MKL02Z4_sim.h"
    #include "device/MKL02Z4/MKL02Z4_smc.h"
    #include "device/MKL02Z4/MKL02Z4_spi.h"
    #include "device/MKL02Z4/MKL02Z4_tpm.h"
    #include "device/MKL02Z4/MKL02Z4_uart0.h"

#elif (defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || \
    defined(CPU_MKL03Z32VFG4) || defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || \
    defined(CPU_MKL03Z32VFK4))

    #define KL03Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL03Z4/MKL03Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL03Z4/MKL03Z4_adc.h"
    #include "device/MKL03Z4/MKL03Z4_cmp.h"
    #include "device/MKL03Z4/MKL03Z4_fgpio.h"
    #include "device/MKL03Z4/MKL03Z4_ftfa.h"
    #include "device/MKL03Z4/MKL03Z4_gpio.h"
    #include "device/MKL03Z4/MKL03Z4_i2c.h"
    #include "device/MKL03Z4/MKL03Z4_llwu.h"
    #include "device/MKL03Z4/MKL03Z4_lptmr.h"
    #include "device/MKL03Z4/MKL03Z4_lpuart.h"
    #include "device/MKL03Z4/MKL03Z4_mcg.h"
    #include "device/MKL03Z4/MKL03Z4_mcm.h"
    #include "device/MKL03Z4/MKL03Z4_mtb.h"
    #include "device/MKL03Z4/MKL03Z4_mtbdwt.h"
    #include "device/MKL03Z4/MKL03Z4_nv.h"
    #include "device/MKL03Z4/MKL03Z4_osc.h"
    #include "device/MKL03Z4/MKL03Z4_pmc.h"
    #include "device/MKL03Z4/MKL03Z4_port.h"
    #include "device/MKL03Z4/MKL03Z4_rcm.h"
    #include "device/MKL03Z4/MKL03Z4_rfsys.h"
    #include "device/MKL03Z4/MKL03Z4_rom.h"
    #include "device/MKL03Z4/MKL03Z4_rtc.h"
    #include "device/MKL03Z4/MKL03Z4_sim.h"
    #include "device/MKL03Z4/MKL03Z4_smc.h"
    #include "device/MKL03Z4/MKL03Z4_spi.h"
    #include "device/MKL03Z4/MKL03Z4_tpm.h"
    #include "device/MKL03Z4/MKL03Z4_vref.h"

#elif (defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || \
    defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || \
    defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4))

    #define KL05Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL05Z4/MKL05Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL05Z4/MKL05Z4_adc.h"
    #include "device/MKL05Z4/MKL05Z4_cmp.h"
    #include "device/MKL05Z4/MKL05Z4_dac.h"
    #include "device/MKL05Z4/MKL05Z4_dma.h"
    #include "device/MKL05Z4/MKL05Z4_dmamux.h"
    #include "device/MKL05Z4/MKL05Z4_fgpio.h"
    #include "device/MKL05Z4/MKL05Z4_ftfa.h"
    #include "device/MKL05Z4/MKL05Z4_gpio.h"
    #include "device/MKL05Z4/MKL05Z4_i2c.h"
    #include "device/MKL05Z4/MKL05Z4_llwu.h"
    #include "device/MKL05Z4/MKL05Z4_lptmr.h"
    #include "device/MKL05Z4/MKL05Z4_mcg.h"
    #include "device/MKL05Z4/MKL05Z4_mcm.h"
    #include "device/MKL05Z4/MKL05Z4_mtb.h"
    #include "device/MKL05Z4/MKL05Z4_mtbdwt.h"
    #include "device/MKL05Z4/MKL05Z4_nv.h"
    #include "device/MKL05Z4/MKL05Z4_osc.h"
    #include "device/MKL05Z4/MKL05Z4_pit.h"
    #include "device/MKL05Z4/MKL05Z4_pmc.h"
    #include "device/MKL05Z4/MKL05Z4_port.h"
    #include "device/MKL05Z4/MKL05Z4_rcm.h"
    #include "device/MKL05Z4/MKL05Z4_rom.h"
    #include "device/MKL05Z4/MKL05Z4_rtc.h"
    #include "device/MKL05Z4/MKL05Z4_sim.h"
    #include "device/MKL05Z4/MKL05Z4_smc.h"
    #include "device/MKL05Z4/MKL05Z4_spi.h"
    #include "device/MKL05Z4/MKL05Z4_tpm.h"
    #include "device/MKL05Z4/MKL05Z4_tsi.h"
    #include "device/MKL05Z4/MKL05Z4_uart0.h"

#elif (defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || \
    defined(CPU_MKL13Z64VFT4) || defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || \
    defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || defined(CPU_MKL13Z256VLH4) || \
    defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4))

    #define KL13Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL13Z4/MKL13Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL13Z4/MKL13Z4_adc.h"
    #include "device/MKL13Z4/MKL13Z4_cmp.h"
    #include "device/MKL13Z4/MKL13Z4_dac.h"
    #include "device/MKL13Z4/MKL13Z4_dma.h"
    #include "device/MKL13Z4/MKL13Z4_dmamux.h"
    #include "device/MKL13Z4/MKL13Z4_flexio.h"
    #include "device/MKL13Z4/MKL13Z4_ftfa.h"
    #include "device/MKL13Z4/MKL13Z4_gpio.h"
    #include "device/MKL13Z4/MKL13Z4_i2c.h"
    #include "device/MKL13Z4/MKL13Z4_i2s.h"
    #include "device/MKL13Z4/MKL13Z4_llwu.h"
    #include "device/MKL13Z4/MKL13Z4_lptmr.h"
    #include "device/MKL13Z4/MKL13Z4_lpuart.h"
    #include "device/MKL13Z4/MKL13Z4_mcg.h"
    #include "device/MKL13Z4/MKL13Z4_mcm.h"
    #include "device/MKL13Z4/MKL13Z4_mtb.h"
    #include "device/MKL13Z4/MKL13Z4_mtbdwt.h"
    #include "device/MKL13Z4/MKL13Z4_nv.h"
    #include "device/MKL13Z4/MKL13Z4_osc.h"
    #include "device/MKL13Z4/MKL13Z4_pit.h"
    #include "device/MKL13Z4/MKL13Z4_pmc.h"
    #include "device/MKL13Z4/MKL13Z4_port.h"
    #include "device/MKL13Z4/MKL13Z4_rcm.h"
    #include "device/MKL13Z4/MKL13Z4_rom.h"
    #include "device/MKL13Z4/MKL13Z4_rtc.h"
    #include "device/MKL13Z4/MKL13Z4_sim.h"
    #include "device/MKL13Z4/MKL13Z4_smc.h"
    #include "device/MKL13Z4/MKL13Z4_spi.h"
    #include "device/MKL13Z4/MKL13Z4_tpm.h"
    #include "device/MKL13Z4/MKL13Z4_uart.h"
    #include "device/MKL13Z4/MKL13Z4_vref.h"

#elif (defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || \
    defined(CPU_MKL23Z64VFT4) || defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || \
    defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || defined(CPU_MKL23Z256VLH4) || \
    defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4))

    #define KL23Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL23Z4/MKL23Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL23Z4/MKL23Z4_adc.h"
    #include "device/MKL23Z4/MKL23Z4_cmp.h"
    #include "device/MKL23Z4/MKL23Z4_dac.h"
    #include "device/MKL23Z4/MKL23Z4_dma.h"
    #include "device/MKL23Z4/MKL23Z4_dmamux.h"
    #include "device/MKL23Z4/MKL23Z4_flexio.h"
    #include "device/MKL23Z4/MKL23Z4_ftfa.h"
    #include "device/MKL23Z4/MKL23Z4_gpio.h"
    #include "device/MKL23Z4/MKL23Z4_i2c.h"
    #include "device/MKL23Z4/MKL23Z4_i2s.h"
    #include "device/MKL23Z4/MKL23Z4_llwu.h"
    #include "device/MKL23Z4/MKL23Z4_lptmr.h"
    #include "device/MKL23Z4/MKL23Z4_lpuart.h"
    #include "device/MKL23Z4/MKL23Z4_mcg.h"
    #include "device/MKL23Z4/MKL23Z4_mcm.h"
    #include "device/MKL23Z4/MKL23Z4_mtb.h"
    #include "device/MKL23Z4/MKL23Z4_mtbdwt.h"
    #include "device/MKL23Z4/MKL23Z4_nv.h"
    #include "device/MKL23Z4/MKL23Z4_osc.h"
    #include "device/MKL23Z4/MKL23Z4_pit.h"
    #include "device/MKL23Z4/MKL23Z4_pmc.h"
    #include "device/MKL23Z4/MKL23Z4_port.h"
    #include "device/MKL23Z4/MKL23Z4_rcm.h"
    #include "device/MKL23Z4/MKL23Z4_rom.h"
    #include "device/MKL23Z4/MKL23Z4_rtc.h"
    #include "device/MKL23Z4/MKL23Z4_sim.h"
    #include "device/MKL23Z4/MKL23Z4_smc.h"
    #include "device/MKL23Z4/MKL23Z4_spi.h"
    #include "device/MKL23Z4/MKL23Z4_tpm.h"
    #include "device/MKL23Z4/MKL23Z4_uart.h"
    #include "device/MKL23Z4/MKL23Z4_usb.h"
    #include "device/MKL23Z4/MKL23Z4_vref.h"

#elif (defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || \
    defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4))

    #define KL25Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL25Z4/MKL25Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL25Z4/MKL25Z4_adc.h"
    #include "device/MKL25Z4/MKL25Z4_cmp.h"
    #include "device/MKL25Z4/MKL25Z4_dac.h"
    #include "device/MKL25Z4/MKL25Z4_dma.h"
    #include "device/MKL25Z4/MKL25Z4_dmamux.h"
    #include "device/MKL25Z4/MKL25Z4_fgpio.h"
    #include "device/MKL25Z4/MKL25Z4_ftfa.h"
    #include "device/MKL25Z4/MKL25Z4_gpio.h"
    #include "device/MKL25Z4/MKL25Z4_i2c.h"
    #include "device/MKL25Z4/MKL25Z4_llwu.h"
    #include "device/MKL25Z4/MKL25Z4_lptmr.h"
    #include "device/MKL25Z4/MKL25Z4_mcg.h"
    #include "device/MKL25Z4/MKL25Z4_mcm.h"
    #include "device/MKL25Z4/MKL25Z4_mtb.h"
    #include "device/MKL25Z4/MKL25Z4_mtbdwt.h"
    #include "device/MKL25Z4/MKL25Z4_nv.h"
    #include "device/MKL25Z4/MKL25Z4_osc.h"
    #include "device/MKL25Z4/MKL25Z4_pit.h"
    #include "device/MKL25Z4/MKL25Z4_pmc.h"
    #include "device/MKL25Z4/MKL25Z4_port.h"
    #include "device/MKL25Z4/MKL25Z4_rcm.h"
    #include "device/MKL25Z4/MKL25Z4_rom.h"
    #include "device/MKL25Z4/MKL25Z4_rtc.h"
    #include "device/MKL25Z4/MKL25Z4_sim.h"
    #include "device/MKL25Z4/MKL25Z4_smc.h"
    #include "device/MKL25Z4/MKL25Z4_spi.h"
    #include "device/MKL25Z4/MKL25Z4_tpm.h"
    #include "device/MKL25Z4/MKL25Z4_tsi.h"
    #include "device/MKL25Z4/MKL25Z4_uart.h"
    #include "device/MKL25Z4/MKL25Z4_uart0.h"
    #include "device/MKL25Z4/MKL25Z4_usb.h"

#elif (defined(CPU_MKL26Z32VFM4) || defined(CPU_MKL26Z64VFM4) || defined(CPU_MKL26Z128VFM4) || \
    defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || defined(CPU_MKL26Z128VFT4) || \
    defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || defined(CPU_MKL26Z128VLH4) || \
    defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || \
    defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4))

    #define KL26Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL26Z4/MKL26Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL26Z4/MKL26Z4_adc.h"
    #include "device/MKL26Z4/MKL26Z4_cmp.h"
    #include "device/MKL26Z4/MKL26Z4_dac.h"
    #include "device/MKL26Z4/MKL26Z4_dma.h"
    #include "device/MKL26Z4/MKL26Z4_dmamux.h"
    #include "device/MKL26Z4/MKL26Z4_fgpio.h"
    #include "device/MKL26Z4/MKL26Z4_ftfa.h"
    #include "device/MKL26Z4/MKL26Z4_gpio.h"
    #include "device/MKL26Z4/MKL26Z4_i2c.h"
    #include "device/MKL26Z4/MKL26Z4_i2s.h"
    #include "device/MKL26Z4/MKL26Z4_llwu.h"
    #include "device/MKL26Z4/MKL26Z4_lptmr.h"
    #include "device/MKL26Z4/MKL26Z4_mcg.h"
    #include "device/MKL26Z4/MKL26Z4_mcm.h"
    #include "device/MKL26Z4/MKL26Z4_mtb.h"
    #include "device/MKL26Z4/MKL26Z4_mtbdwt.h"
    #include "device/MKL26Z4/MKL26Z4_nv.h"
    #include "device/MKL26Z4/MKL26Z4_osc.h"
    #include "device/MKL26Z4/MKL26Z4_pit.h"
    #include "device/MKL26Z4/MKL26Z4_pmc.h"
    #include "device/MKL26Z4/MKL26Z4_port.h"
    #include "device/MKL26Z4/MKL26Z4_rcm.h"
    #include "device/MKL26Z4/MKL26Z4_rom.h"
    #include "device/MKL26Z4/MKL26Z4_rtc.h"
    #include "device/MKL26Z4/MKL26Z4_sim.h"
    #include "device/MKL26Z4/MKL26Z4_smc.h"
    #include "device/MKL26Z4/MKL26Z4_spi.h"
    #include "device/MKL26Z4/MKL26Z4_tpm.h"
    #include "device/MKL26Z4/MKL26Z4_tsi.h"
    #include "device/MKL26Z4/MKL26Z4_uart.h"
    #include "device/MKL26Z4/MKL26Z4_uart0.h"
    #include "device/MKL26Z4/MKL26Z4_usb.h"

#elif (defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || \
    defined(CPU_MKL33Z256VMP4))

    #define KL33Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL33Z4/MKL33Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL33Z4/MKL33Z4_adc.h"
    #include "device/MKL33Z4/MKL33Z4_cmp.h"
    #include "device/MKL33Z4/MKL33Z4_dac.h"
    #include "device/MKL33Z4/MKL33Z4_dma.h"
    #include "device/MKL33Z4/MKL33Z4_dmamux.h"
    #include "device/MKL33Z4/MKL33Z4_flexio.h"
    #include "device/MKL33Z4/MKL33Z4_ftfa.h"
    #include "device/MKL33Z4/MKL33Z4_gpio.h"
    #include "device/MKL33Z4/MKL33Z4_i2c.h"
    #include "device/MKL33Z4/MKL33Z4_i2s.h"
    #include "device/MKL33Z4/MKL33Z4_lcd.h"
    #include "device/MKL33Z4/MKL33Z4_llwu.h"
    #include "device/MKL33Z4/MKL33Z4_lptmr.h"
    #include "device/MKL33Z4/MKL33Z4_lpuart.h"
    #include "device/MKL33Z4/MKL33Z4_mcg.h"
    #include "device/MKL33Z4/MKL33Z4_mcm.h"
    #include "device/MKL33Z4/MKL33Z4_mtb.h"
    #include "device/MKL33Z4/MKL33Z4_mtbdwt.h"
    #include "device/MKL33Z4/MKL33Z4_nv.h"
    #include "device/MKL33Z4/MKL33Z4_osc.h"
    #include "device/MKL33Z4/MKL33Z4_pit.h"
    #include "device/MKL33Z4/MKL33Z4_pmc.h"
    #include "device/MKL33Z4/MKL33Z4_port.h"
    #include "device/MKL33Z4/MKL33Z4_rcm.h"
    #include "device/MKL33Z4/MKL33Z4_rom.h"
    #include "device/MKL33Z4/MKL33Z4_rtc.h"
    #include "device/MKL33Z4/MKL33Z4_sim.h"
    #include "device/MKL33Z4/MKL33Z4_smc.h"
    #include "device/MKL33Z4/MKL33Z4_spi.h"
    #include "device/MKL33Z4/MKL33Z4_tpm.h"
    #include "device/MKL33Z4/MKL33Z4_uart.h"
    #include "device/MKL33Z4/MKL33Z4_vref.h"

#elif (defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || \
    defined(CPU_MKL43Z64VMP4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4))

    #define KL43Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL43Z4/MKL43Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL43Z4/MKL43Z4_adc.h"
    #include "device/MKL43Z4/MKL43Z4_cmp.h"
    #include "device/MKL43Z4/MKL43Z4_dac.h"
    #include "device/MKL43Z4/MKL43Z4_dma.h"
    #include "device/MKL43Z4/MKL43Z4_dmamux.h"
    #include "device/MKL43Z4/MKL43Z4_flexio.h"
    #include "device/MKL43Z4/MKL43Z4_ftfa.h"
    #include "device/MKL43Z4/MKL43Z4_gpio.h"
    #include "device/MKL43Z4/MKL43Z4_i2c.h"
    #include "device/MKL43Z4/MKL43Z4_i2s.h"
    #include "device/MKL43Z4/MKL43Z4_lcd.h"
    #include "device/MKL43Z4/MKL43Z4_llwu.h"
    #include "device/MKL43Z4/MKL43Z4_lptmr.h"
    #include "device/MKL43Z4/MKL43Z4_lpuart.h"
    #include "device/MKL43Z4/MKL43Z4_mcg.h"
    #include "device/MKL43Z4/MKL43Z4_mcm.h"
    #include "device/MKL43Z4/MKL43Z4_mtb.h"
    #include "device/MKL43Z4/MKL43Z4_mtbdwt.h"
    #include "device/MKL43Z4/MKL43Z4_nv.h"
    #include "device/MKL43Z4/MKL43Z4_osc.h"
    #include "device/MKL43Z4/MKL43Z4_pit.h"
    #include "device/MKL43Z4/MKL43Z4_pmc.h"
    #include "device/MKL43Z4/MKL43Z4_port.h"
    #include "device/MKL43Z4/MKL43Z4_rcm.h"
    #include "device/MKL43Z4/MKL43Z4_rom.h"
    #include "device/MKL43Z4/MKL43Z4_rtc.h"
    #include "device/MKL43Z4/MKL43Z4_sim.h"
    #include "device/MKL43Z4/MKL43Z4_smc.h"
    #include "device/MKL43Z4/MKL43Z4_spi.h"
    #include "device/MKL43Z4/MKL43Z4_tpm.h"
    #include "device/MKL43Z4/MKL43Z4_uart.h"
    #include "device/MKL43Z4/MKL43Z4_usb.h"
    #include "device/MKL43Z4/MKL43Z4_vref.h"

#elif (defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4))

    #define KL46Z4_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKL46Z4/MKL46Z4.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKL46Z4/MKL46Z4_adc.h"
    #include "device/MKL46Z4/MKL46Z4_cmp.h"
    #include "device/MKL46Z4/MKL46Z4_dac.h"
    #include "device/MKL46Z4/MKL46Z4_dma.h"
    #include "device/MKL46Z4/MKL46Z4_dmamux.h"
    #include "device/MKL46Z4/MKL46Z4_fgpio.h"
    #include "device/MKL46Z4/MKL46Z4_ftfa.h"
    #include "device/MKL46Z4/MKL46Z4_gpio.h"
    #include "device/MKL46Z4/MKL46Z4_i2c.h"
    #include "device/MKL46Z4/MKL46Z4_i2s.h"
    #include "device/MKL46Z4/MKL46Z4_lcd.h"
    #include "device/MKL46Z4/MKL46Z4_llwu.h"
    #include "device/MKL46Z4/MKL46Z4_lptmr.h"
    #include "device/MKL46Z4/MKL46Z4_mcg.h"
    #include "device/MKL46Z4/MKL46Z4_mcm.h"
    #include "device/MKL46Z4/MKL46Z4_mtb.h"
    #include "device/MKL46Z4/MKL46Z4_mtbdwt.h"
    #include "device/MKL46Z4/MKL46Z4_nv.h"
    #include "device/MKL46Z4/MKL46Z4_osc.h"
    #include "device/MKL46Z4/MKL46Z4_pit.h"
    #include "device/MKL46Z4/MKL46Z4_pmc.h"
    #include "device/MKL46Z4/MKL46Z4_port.h"
    #include "device/MKL46Z4/MKL46Z4_rcm.h"
    #include "device/MKL46Z4/MKL46Z4_rom.h"
    #include "device/MKL46Z4/MKL46Z4_rtc.h"
    #include "device/MKL46Z4/MKL46Z4_sim.h"
    #include "device/MKL46Z4/MKL46Z4_smc.h"
    #include "device/MKL46Z4/MKL46Z4_spi.h"
    #include "device/MKL46Z4/MKL46Z4_tpm.h"
    #include "device/MKL46Z4/MKL46Z4_tsi.h"
    #include "device/MKL46Z4/MKL46Z4_uart.h"
    #include "device/MKL46Z4/MKL46Z4_uart0.h"
    #include "device/MKL46Z4/MKL46Z4_usb.h"

#elif (defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || \
    defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10))

    #define KV30F12810_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV30F12810/MKV30F12810.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV30F12810/MKV30F12810_adc.h"
    #include "device/MKV30F12810/MKV30F12810_cmp.h"
    #include "device/MKV30F12810/MKV30F12810_crc.h"
    #include "device/MKV30F12810/MKV30F12810_dac.h"
    #include "device/MKV30F12810/MKV30F12810_dma.h"
    #include "device/MKV30F12810/MKV30F12810_dmamux.h"
    #include "device/MKV30F12810/MKV30F12810_ewm.h"
    #include "device/MKV30F12810/MKV30F12810_fmc.h"
    #include "device/MKV30F12810/MKV30F12810_ftfa.h"
    #include "device/MKV30F12810/MKV30F12810_ftm.h"
    #include "device/MKV30F12810/MKV30F12810_gpio.h"
    #include "device/MKV30F12810/MKV30F12810_i2c.h"
    #include "device/MKV30F12810/MKV30F12810_llwu.h"
    #include "device/MKV30F12810/MKV30F12810_lptmr.h"
    #include "device/MKV30F12810/MKV30F12810_mcg.h"
    #include "device/MKV30F12810/MKV30F12810_mcm.h"
    #include "device/MKV30F12810/MKV30F12810_nv.h"
    #include "device/MKV30F12810/MKV30F12810_osc.h"
    #include "device/MKV30F12810/MKV30F12810_pdb.h"
    #include "device/MKV30F12810/MKV30F12810_pit.h"
    #include "device/MKV30F12810/MKV30F12810_pmc.h"
    #include "device/MKV30F12810/MKV30F12810_port.h"
    #include "device/MKV30F12810/MKV30F12810_rcm.h"
    #include "device/MKV30F12810/MKV30F12810_sim.h"
    #include "device/MKV30F12810/MKV30F12810_smc.h"
    #include "device/MKV30F12810/MKV30F12810_spi.h"
    #include "device/MKV30F12810/MKV30F12810_uart.h"
    #include "device/MKV30F12810/MKV30F12810_vref.h"
    #include "device/MKV30F12810/MKV30F12810_wdog.h"

#elif (defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10))

    #define KV31F12810_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV31F12810/MKV31F12810.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV31F12810/MKV31F12810_adc.h"
    #include "device/MKV31F12810/MKV31F12810_cmp.h"
    #include "device/MKV31F12810/MKV31F12810_crc.h"
    #include "device/MKV31F12810/MKV31F12810_dac.h"
    #include "device/MKV31F12810/MKV31F12810_dma.h"
    #include "device/MKV31F12810/MKV31F12810_dmamux.h"
    #include "device/MKV31F12810/MKV31F12810_ewm.h"
    #include "device/MKV31F12810/MKV31F12810_fmc.h"
    #include "device/MKV31F12810/MKV31F12810_ftfa.h"
    #include "device/MKV31F12810/MKV31F12810_ftm.h"
    #include "device/MKV31F12810/MKV31F12810_gpio.h"
    #include "device/MKV31F12810/MKV31F12810_i2c.h"
    #include "device/MKV31F12810/MKV31F12810_llwu.h"
    #include "device/MKV31F12810/MKV31F12810_lptmr.h"
    #include "device/MKV31F12810/MKV31F12810_lpuart.h"
    #include "device/MKV31F12810/MKV31F12810_mcg.h"
    #include "device/MKV31F12810/MKV31F12810_mcm.h"
    #include "device/MKV31F12810/MKV31F12810_nv.h"
    #include "device/MKV31F12810/MKV31F12810_osc.h"
    #include "device/MKV31F12810/MKV31F12810_pdb.h"
    #include "device/MKV31F12810/MKV31F12810_pit.h"
    #include "device/MKV31F12810/MKV31F12810_pmc.h"
    #include "device/MKV31F12810/MKV31F12810_port.h"
    #include "device/MKV31F12810/MKV31F12810_rcm.h"
    #include "device/MKV31F12810/MKV31F12810_rfsys.h"
    #include "device/MKV31F12810/MKV31F12810_sim.h"
    #include "device/MKV31F12810/MKV31F12810_smc.h"
    #include "device/MKV31F12810/MKV31F12810_spi.h"
    #include "device/MKV31F12810/MKV31F12810_uart.h"
    #include "device/MKV31F12810/MKV31F12810_vref.h"
    #include "device/MKV31F12810/MKV31F12810_wdog.h"

#elif (defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12))

    #define KV31F25612_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV31F25612/MKV31F25612.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV31F25612/MKV31F25612_adc.h"
    #include "device/MKV31F25612/MKV31F25612_cmp.h"
    #include "device/MKV31F25612/MKV31F25612_crc.h"
    #include "device/MKV31F25612/MKV31F25612_dac.h"
    #include "device/MKV31F25612/MKV31F25612_dma.h"
    #include "device/MKV31F25612/MKV31F25612_dmamux.h"
    #include "device/MKV31F25612/MKV31F25612_ewm.h"
    #include "device/MKV31F25612/MKV31F25612_fmc.h"
    #include "device/MKV31F25612/MKV31F25612_ftfa.h"
    #include "device/MKV31F25612/MKV31F25612_ftm.h"
    #include "device/MKV31F25612/MKV31F25612_gpio.h"
    #include "device/MKV31F25612/MKV31F25612_i2c.h"
    #include "device/MKV31F25612/MKV31F25612_llwu.h"
    #include "device/MKV31F25612/MKV31F25612_lptmr.h"
    #include "device/MKV31F25612/MKV31F25612_lpuart.h"
    #include "device/MKV31F25612/MKV31F25612_mcg.h"
    #include "device/MKV31F25612/MKV31F25612_mcm.h"
    #include "device/MKV31F25612/MKV31F25612_nv.h"
    #include "device/MKV31F25612/MKV31F25612_osc.h"
    #include "device/MKV31F25612/MKV31F25612_pdb.h"
    #include "device/MKV31F25612/MKV31F25612_pit.h"
    #include "device/MKV31F25612/MKV31F25612_pmc.h"
    #include "device/MKV31F25612/MKV31F25612_port.h"
    #include "device/MKV31F25612/MKV31F25612_rcm.h"
    #include "device/MKV31F25612/MKV31F25612_rfsys.h"
    #include "device/MKV31F25612/MKV31F25612_rng.h"
    #include "device/MKV31F25612/MKV31F25612_sim.h"
    #include "device/MKV31F25612/MKV31F25612_smc.h"
    #include "device/MKV31F25612/MKV31F25612_spi.h"
    #include "device/MKV31F25612/MKV31F25612_uart.h"
    #include "device/MKV31F25612/MKV31F25612_vref.h"
    #include "device/MKV31F25612/MKV31F25612_wdog.h"

#elif (defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12))

    #define KV31F51212_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV31F51212/MKV31F51212.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV31F51212/MKV31F51212_adc.h"
    #include "device/MKV31F51212/MKV31F51212_cmp.h"
    #include "device/MKV31F51212/MKV31F51212_crc.h"
    #include "device/MKV31F51212/MKV31F51212_dac.h"
    #include "device/MKV31F51212/MKV31F51212_dma.h"
    #include "device/MKV31F51212/MKV31F51212_dmamux.h"
    #include "device/MKV31F51212/MKV31F51212_ewm.h"
    #include "device/MKV31F51212/MKV31F51212_fb.h"
    #include "device/MKV31F51212/MKV31F51212_fmc.h"
    #include "device/MKV31F51212/MKV31F51212_ftfa.h"
    #include "device/MKV31F51212/MKV31F51212_ftm.h"
    #include "device/MKV31F51212/MKV31F51212_gpio.h"
    #include "device/MKV31F51212/MKV31F51212_i2c.h"
    #include "device/MKV31F51212/MKV31F51212_llwu.h"
    #include "device/MKV31F51212/MKV31F51212_lptmr.h"
    #include "device/MKV31F51212/MKV31F51212_lpuart.h"
    #include "device/MKV31F51212/MKV31F51212_mcg.h"
    #include "device/MKV31F51212/MKV31F51212_mcm.h"
    #include "device/MKV31F51212/MKV31F51212_nv.h"
    #include "device/MKV31F51212/MKV31F51212_osc.h"
    #include "device/MKV31F51212/MKV31F51212_pdb.h"
    #include "device/MKV31F51212/MKV31F51212_pit.h"
    #include "device/MKV31F51212/MKV31F51212_pmc.h"
    #include "device/MKV31F51212/MKV31F51212_port.h"
    #include "device/MKV31F51212/MKV31F51212_rcm.h"
    #include "device/MKV31F51212/MKV31F51212_rfsys.h"
    #include "device/MKV31F51212/MKV31F51212_rng.h"
    #include "device/MKV31F51212/MKV31F51212_sim.h"
    #include "device/MKV31F51212/MKV31F51212_smc.h"
    #include "device/MKV31F51212/MKV31F51212_spi.h"
    #include "device/MKV31F51212/MKV31F51212_uart.h"
    #include "device/MKV31F51212/MKV31F51212_vref.h"
    #include "device/MKV31F51212/MKV31F51212_wdog.h"

#elif (defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || \
    defined(CPU_MKV40F256VLL15) || defined(CPU_MKV40F64VLH15))

    #define KV40F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV40F15/MKV40F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV40F15/MKV40F15_adc.h"
    #include "device/MKV40F15/MKV40F15_aoi.h"
    #include "device/MKV40F15/MKV40F15_can.h"
    #include "device/MKV40F15/MKV40F15_cmp.h"
    #include "device/MKV40F15/MKV40F15_crc.h"
    #include "device/MKV40F15/MKV40F15_dma.h"
    #include "device/MKV40F15/MKV40F15_dmamux.h"
    #include "device/MKV40F15/MKV40F15_enc.h"
    #include "device/MKV40F15/MKV40F15_ewm.h"
    #include "device/MKV40F15/MKV40F15_fmc.h"
    #include "device/MKV40F15/MKV40F15_ftfa.h"
    #include "device/MKV40F15/MKV40F15_ftm.h"
    #include "device/MKV40F15/MKV40F15_gpio.h"
    #include "device/MKV40F15/MKV40F15_i2c.h"
    #include "device/MKV40F15/MKV40F15_llwu.h"
    #include "device/MKV40F15/MKV40F15_lptmr.h"
    #include "device/MKV40F15/MKV40F15_mcg.h"
    #include "device/MKV40F15/MKV40F15_mcm.h"
    #include "device/MKV40F15/MKV40F15_nv.h"
    #include "device/MKV40F15/MKV40F15_osc.h"
    #include "device/MKV40F15/MKV40F15_pdb.h"
    #include "device/MKV40F15/MKV40F15_pit.h"
    #include "device/MKV40F15/MKV40F15_pmc.h"
    #include "device/MKV40F15/MKV40F15_port.h"
    #include "device/MKV40F15/MKV40F15_rcm.h"
    #include "device/MKV40F15/MKV40F15_sim.h"
    #include "device/MKV40F15/MKV40F15_smc.h"
    #include "device/MKV40F15/MKV40F15_spi.h"
    #include "device/MKV40F15/MKV40F15_uart.h"
    #include "device/MKV40F15/MKV40F15_vref.h"
    #include "device/MKV40F15/MKV40F15_wdog.h"
    #include "device/MKV40F15/MKV40F15_xbara.h"
    #include "device/MKV40F15/MKV40F15_xbarb.h"

#elif (defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15))

    #define KV43F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV43F15/MKV43F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV43F15/MKV43F15_adc.h"
    #include "device/MKV43F15/MKV43F15_aoi.h"
    #include "device/MKV43F15/MKV43F15_can.h"
    #include "device/MKV43F15/MKV43F15_cmp.h"
    #include "device/MKV43F15/MKV43F15_crc.h"
    #include "device/MKV43F15/MKV43F15_dma.h"
    #include "device/MKV43F15/MKV43F15_dmamux.h"
    #include "device/MKV43F15/MKV43F15_enc.h"
    #include "device/MKV43F15/MKV43F15_ewm.h"
    #include "device/MKV43F15/MKV43F15_fmc.h"
    #include "device/MKV43F15/MKV43F15_ftfa.h"
    #include "device/MKV43F15/MKV43F15_gpio.h"
    #include "device/MKV43F15/MKV43F15_i2c.h"
    #include "device/MKV43F15/MKV43F15_llwu.h"
    #include "device/MKV43F15/MKV43F15_lptmr.h"
    #include "device/MKV43F15/MKV43F15_mcg.h"
    #include "device/MKV43F15/MKV43F15_mcm.h"
    #include "device/MKV43F15/MKV43F15_nv.h"
    #include "device/MKV43F15/MKV43F15_osc.h"
    #include "device/MKV43F15/MKV43F15_pdb.h"
    #include "device/MKV43F15/MKV43F15_pit.h"
    #include "device/MKV43F15/MKV43F15_pmc.h"
    #include "device/MKV43F15/MKV43F15_port.h"
    #include "device/MKV43F15/MKV43F15_pwm.h"
    #include "device/MKV43F15/MKV43F15_rcm.h"
    #include "device/MKV43F15/MKV43F15_sim.h"
    #include "device/MKV43F15/MKV43F15_smc.h"
    #include "device/MKV43F15/MKV43F15_spi.h"
    #include "device/MKV43F15/MKV43F15_uart.h"
    #include "device/MKV43F15/MKV43F15_vref.h"
    #include "device/MKV43F15/MKV43F15_wdog.h"
    #include "device/MKV43F15/MKV43F15_xbara.h"
    #include "device/MKV43F15/MKV43F15_xbarb.h"

#elif (defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15))

    #define KV44F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV44F15/MKV44F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV44F15/MKV44F15_adc.h"
    #include "device/MKV44F15/MKV44F15_aoi.h"
    #include "device/MKV44F15/MKV44F15_can.h"
    #include "device/MKV44F15/MKV44F15_cmp.h"
    #include "device/MKV44F15/MKV44F15_crc.h"
    #include "device/MKV44F15/MKV44F15_dac.h"
    #include "device/MKV44F15/MKV44F15_dma.h"
    #include "device/MKV44F15/MKV44F15_dmamux.h"
    #include "device/MKV44F15/MKV44F15_enc.h"
    #include "device/MKV44F15/MKV44F15_ewm.h"
    #include "device/MKV44F15/MKV44F15_fmc.h"
    #include "device/MKV44F15/MKV44F15_ftfa.h"
    #include "device/MKV44F15/MKV44F15_gpio.h"
    #include "device/MKV44F15/MKV44F15_i2c.h"
    #include "device/MKV44F15/MKV44F15_llwu.h"
    #include "device/MKV44F15/MKV44F15_lptmr.h"
    #include "device/MKV44F15/MKV44F15_mcg.h"
    #include "device/MKV44F15/MKV44F15_mcm.h"
    #include "device/MKV44F15/MKV44F15_nv.h"
    #include "device/MKV44F15/MKV44F15_osc.h"
    #include "device/MKV44F15/MKV44F15_pdb.h"
    #include "device/MKV44F15/MKV44F15_pit.h"
    #include "device/MKV44F15/MKV44F15_pmc.h"
    #include "device/MKV44F15/MKV44F15_port.h"
    #include "device/MKV44F15/MKV44F15_pwm.h"
    #include "device/MKV44F15/MKV44F15_rcm.h"
    #include "device/MKV44F15/MKV44F15_sim.h"
    #include "device/MKV44F15/MKV44F15_smc.h"
    #include "device/MKV44F15/MKV44F15_spi.h"
    #include "device/MKV44F15/MKV44F15_uart.h"
    #include "device/MKV44F15/MKV44F15_vref.h"
    #include "device/MKV44F15/MKV44F15_wdog.h"
    #include "device/MKV44F15/MKV44F15_xbara.h"
    #include "device/MKV44F15/MKV44F15_xbarb.h"

#elif (defined(CPU_MKV45F128VLH15) || defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || \
    defined(CPU_MKV45F256VLL15))

    #define KV45F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV45F15/MKV45F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV45F15/MKV45F15_adc.h"
    #include "device/MKV45F15/MKV45F15_aoi.h"
    #include "device/MKV45F15/MKV45F15_can.h"
    #include "device/MKV45F15/MKV45F15_cmp.h"
    #include "device/MKV45F15/MKV45F15_crc.h"
    #include "device/MKV45F15/MKV45F15_dma.h"
    #include "device/MKV45F15/MKV45F15_dmamux.h"
    #include "device/MKV45F15/MKV45F15_enc.h"
    #include "device/MKV45F15/MKV45F15_ewm.h"
    #include "device/MKV45F15/MKV45F15_fmc.h"
    #include "device/MKV45F15/MKV45F15_ftfa.h"
    #include "device/MKV45F15/MKV45F15_ftm.h"
    #include "device/MKV45F15/MKV45F15_gpio.h"
    #include "device/MKV45F15/MKV45F15_i2c.h"
    #include "device/MKV45F15/MKV45F15_llwu.h"
    #include "device/MKV45F15/MKV45F15_lptmr.h"
    #include "device/MKV45F15/MKV45F15_mcg.h"
    #include "device/MKV45F15/MKV45F15_mcm.h"
    #include "device/MKV45F15/MKV45F15_nv.h"
    #include "device/MKV45F15/MKV45F15_osc.h"
    #include "device/MKV45F15/MKV45F15_pdb.h"
    #include "device/MKV45F15/MKV45F15_pit.h"
    #include "device/MKV45F15/MKV45F15_pmc.h"
    #include "device/MKV45F15/MKV45F15_port.h"
    #include "device/MKV45F15/MKV45F15_pwm.h"
    #include "device/MKV45F15/MKV45F15_rcm.h"
    #include "device/MKV45F15/MKV45F15_sim.h"
    #include "device/MKV45F15/MKV45F15_smc.h"
    #include "device/MKV45F15/MKV45F15_spi.h"
    #include "device/MKV45F15/MKV45F15_uart.h"
    #include "device/MKV45F15/MKV45F15_vref.h"
    #include "device/MKV45F15/MKV45F15_wdog.h"
    #include "device/MKV45F15/MKV45F15_xbara.h"
    #include "device/MKV45F15/MKV45F15_xbarb.h"

#elif (defined(CPU_MKV46F128VLH15) || defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || \
    defined(CPU_MKV46F256VLL15))

    #define KV46F15_SERIES

    /* CMSIS-style register definitions */
    #include "device/MKV46F15/MKV46F15.h"

    /* Extension register headers. (These will eventually be merged into the CMSIS-style header.) */
    #include "device/MKV46F15/MKV46F15_adc.h"
    #include "device/MKV46F15/MKV46F15_aoi.h"
    #include "device/MKV46F15/MKV46F15_can.h"
    #include "device/MKV46F15/MKV46F15_cmp.h"
    #include "device/MKV46F15/MKV46F15_crc.h"
    #include "device/MKV46F15/MKV46F15_dac.h"
    #include "device/MKV46F15/MKV46F15_dma.h"
    #include "device/MKV46F15/MKV46F15_dmamux.h"
    #include "device/MKV46F15/MKV46F15_enc.h"
    #include "device/MKV46F15/MKV46F15_ewm.h"
    #include "device/MKV46F15/MKV46F15_fmc.h"
    #include "device/MKV46F15/MKV46F15_ftfa.h"
    #include "device/MKV46F15/MKV46F15_ftm.h"
    #include "device/MKV46F15/MKV46F15_gpio.h"
    #include "device/MKV46F15/MKV46F15_i2c.h"
    #include "device/MKV46F15/MKV46F15_llwu.h"
    #include "device/MKV46F15/MKV46F15_lptmr.h"
    #include "device/MKV46F15/MKV46F15_mcg.h"
    #include "device/MKV46F15/MKV46F15_mcm.h"
    #include "device/MKV46F15/MKV46F15_nv.h"
    #include "device/MKV46F15/MKV46F15_osc.h"
    #include "device/MKV46F15/MKV46F15_pdb.h"
    #include "device/MKV46F15/MKV46F15_pit.h"
    #include "device/MKV46F15/MKV46F15_pmc.h"
    #include "device/MKV46F15/MKV46F15_port.h"
    #include "device/MKV46F15/MKV46F15_pwm.h"
    #include "device/MKV46F15/MKV46F15_rcm.h"
    #include "device/MKV46F15/MKV46F15_sim.h"
    #include "device/MKV46F15/MKV46F15_smc.h"
    #include "device/MKV46F15/MKV46F15_spi.h"
    #include "device/MKV46F15/MKV46F15_uart.h"
    #include "device/MKV46F15/MKV46F15_vref.h"
    #include "device/MKV46F15/MKV46F15_wdog.h"
    #include "device/MKV46F15/MKV46F15_xbara.h"
    #include "device/MKV46F15/MKV46F15_xbarb.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
