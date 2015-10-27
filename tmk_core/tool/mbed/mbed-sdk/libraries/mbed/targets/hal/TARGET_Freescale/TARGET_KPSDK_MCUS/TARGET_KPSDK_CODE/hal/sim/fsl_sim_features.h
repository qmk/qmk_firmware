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

#if !defined(__FSL_SIM_FEATURES_H__)
#define __FSL_SIM_FEATURES_H__

#if defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || defined(CPU_MK02FN64VLF10) || \
    defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (2)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (1)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (3)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (1)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (1)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (1)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (1)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (1)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK24FN256VDC12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || \
    defined(CPU_MK64FX512VLL12) || defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (1)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (3)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (1)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (1)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (1)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (1)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (1)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (1)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (1)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || \
    defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (1)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (1)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (4)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (2)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (1)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (1)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (1)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (1)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (1)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (1)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (1)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (1)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (1)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (1)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (1)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (1)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (1)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (1)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (1)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (4)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (1)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (4)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (1)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (1)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (1)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (1)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (1)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (1)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (4)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (1)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (1)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (1)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (1)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (0)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (0)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (0)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (0)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (0)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (1)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (1)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (1)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (1)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (0)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (1)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (1)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (1)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || defined(CPU_MKL03Z32VFG4) || \
    defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || defined(CPU_MKL03Z32VFK4)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (0)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (1)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (1)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (0)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (0)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (0)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (0)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (0)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (0)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (0)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (1)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (1)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (1)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (1)
#elif defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || defined(CPU_MKL05Z8VLC4) || \
    defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || \
    defined(CPU_MKL05Z32VFM4) || defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (1)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (1)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (1)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (1)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (0)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (0)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (0)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (1)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (1)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (1)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z128VFM4) || defined(CPU_MKL13Z256VFM4) || defined(CPU_MKL13Z64VFT4) || \
    defined(CPU_MKL13Z128VFT4) || defined(CPU_MKL13Z256VFT4) || defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z128VLH4) || \
    defined(CPU_MKL13Z256VLH4) || defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL13Z128VMP4) || defined(CPU_MKL13Z256VMP4) || \
    defined(CPU_MKL23Z64VFM4) || defined(CPU_MKL23Z128VFM4) || defined(CPU_MKL23Z256VFM4) || defined(CPU_MKL23Z64VFT4) || \
    defined(CPU_MKL23Z128VFT4) || defined(CPU_MKL23Z256VFT4) || defined(CPU_MKL23Z64VLH4) || defined(CPU_MKL23Z128VLH4) || \
    defined(CPU_MKL23Z256VLH4) || defined(CPU_MKL23Z64VMP4) || defined(CPU_MKL23Z128VMP4) || defined(CPU_MKL23Z256VMP4) || \
    defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || defined(CPU_MKL33Z256VMP4) || \
    defined(CPU_MKL43Z64VLH4) || defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z64VMP4) || \
    defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (1)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (1)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (1)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (1)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (1)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (1)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (1)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (0)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (0)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (0)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (0)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (0)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (0)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (0)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (2)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (2)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (1)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (1)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (1)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (1)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (1)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (1)
#elif defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || defined(CPU_MKL25Z32VFT4) || \
    defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || \
    defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (1)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (1)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (1)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (1)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (2)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (1)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (1)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (1)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (1)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKL26Z256VLK4) || defined(CPU_MKL26Z128VLL4) || defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || \
    defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (1)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (0)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (1)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (1)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (1)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (1)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (1)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (0)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (0)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (0)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (0)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (0)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (0)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (0)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (1)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (2)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (1)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (1)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (2)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (1)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (1)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (1)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (1)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (1)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (0)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (0)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (3)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (1)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (1)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (1)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || defined(CPU_MKV30F64VLF10) || \
    defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (2)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10) || defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (0)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (0)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (1)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (1)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (3)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (1)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (2)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (4)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (1)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (1)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (1)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (2)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (1)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (1)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (1)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (1)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (2)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (1)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (0)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (1)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F256VLH15) || defined(CPU_MKV40F64VLH15) || defined(CPU_MKV45F128VLH15) || \
    defined(CPU_MKV45F256VLH15) || defined(CPU_MKV46F128VLH15) || defined(CPU_MKV46F256VLH15)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (2)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (1)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (2)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (4)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (1)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLL15) || defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLL15) || \
    defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLL15)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (2)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (1)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (3)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (4)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (1)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#elif defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15) || defined(CPU_MKV44F128VLH15) || \
    defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15)
    /* @brief Has USB FS divider. */
    #define FSL_FEATURE_SIM_USBFS_USE_SPECIAL_DIVIDER (0)
    /* @brief Is PLL clock divided by 2 before MCG PLL/FLL clock selection. */
    #define FSL_FEATURE_SIM_PLLCLK_USE_SPECIAL_DIVIDER (0)
    /* @brief Has RAM size specification (register bit field SOPT1[RAMSIZE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RAMSIZE (1)
    /* @brief Has 32k oscillator clock output (register bit SOPT1[OSC32KOUT]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_OUT (0)
    /* @brief Has 32k oscillator clock selection (register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_OSC32K_SELECTION (1)
    /* @brief 32k oscillator clock selection width (width of register bit field SOPT1[OSC32KSEL]). */
    #define FSL_FEATURE_SIM_OPT_OSC32K_SELECTION_WIDTH (2)
    /* @brief Has RTC clock output selection (register bit SOPT2[RTCCLKOUTSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RTC_CLOCK_OUT_SELECTION (0)
    /* @brief Has USB voltage regulator (register bits SOPT1[USBVSTBY], SOPT1[USBSSTBY], SOPT1[USBREGEN], SOPT1CFG[URWE], SOPT1CFG[UVSWE], SOPT1CFG[USSWE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_VOLTAGE_REGULATOR (0)
    /* @brief USB has integrated PHY (register bits USBPHYCTL[USBVREGSEL], USBPHYCTL[USBVREGPD], USBPHYCTL[USB3VOUTTRG], USBPHYCTL[USBDISILIM], SOPT2[USBSLSRC], SOPT2[USBREGEN]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USB_PHY (0)
    /* @brief Has PTD7 pad drive strength control (register bit SOPT2[PTD7PAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PTD7PAD (0)
    /* @brief Has FlexBus security level selection (register bit SOPT2[FBSL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FBSL (0)
    /* @brief Has number of FlexBus hold cycle before FlexBus can release bus (register bit SOPT6[PCR]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PCR (0)
    /* @brief Has number of NFC hold cycle in case of FlexBus request (register bit SOPT6[MCC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_MCC (0)
    /* @brief Has UART open drain enable (register bits UARTnODE, where n is a number, in register SOPT5). */
    #define FSL_FEATURE_SIM_OPT_HAS_ODE (0)
    /* @brief Number of UART modules (number of register bits UARTn, where n is a number, in register SCGC4). */
    #define FSL_FEATURE_SIM_OPT_UART_COUNT (2)
    /* @brief Has LPUART0 open drain enable (register bit SOPT5[LPUART0ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_ODE (0)
    /* @brief Has LPUART1 open drain enable (register bit SOPT5[LPUART1ODE]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_ODE (0)
    /* @brief Has CMT/UART pad drive strength control (register bit SOPT2[CMTUARTPAD]). */
    #define FSL_FEATURE_SIM_OPT_HAS_CMTUARTPAD (0)
    /* @brief Has LPUART0 transmit data source selection (register bit SOPT5[LPUART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_TX_SRC (0)
    /* @brief Has LPUART0 receive data source selection (register bit SOPT5[LPUART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0_RX_SRC (0)
    /* @brief Has LPUART1 transmit data source selection (register bit SOPT5[LPUART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_TX_SRC (0)
    /* @brief Has LPUART1 receive data source selection (register bit SOPT5[LPUART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1_RX_SRC (0)
    /* @brief Has UART0 transmit data source selection (register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_TX_SRC (1)
    /* @brief UART0 transmit data source selection width (width of register bit SOPT5[UART0TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_TX_SRC_WIDTH (1)
    /* @brief Has UART0 receive data source selection (register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0_RX_SRC (1)
    /* @brief UART0 receive data source selection width (width of register bit SOPT5[UART0RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART0_RX_SRC_WIDTH (2)
    /* @brief Has UART1 transmit data source selection (register bit SOPT5[UART1TXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_TX_SRC (1)
    /* @brief Has UART1 receive data source selection (register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART1_RX_SRC (1)
    /* @brief UART1 receive data source selection width (width of register bit SOPT5[UART1RXSRC]). */
    #define FSL_FEATURE_SIM_OPT_UART1_RX_SRC_WIDTH (2)
    /* @brief Has FTM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM (1)
    /* @brief Number of FTM modules. */
    #define FSL_FEATURE_SIM_OPT_FTM_COUNT (0)
    /* @brief Number of FTM triggers with selectable source. */
    #define FSL_FEATURE_SIM_OPT_FTM_TRIGGER_COUNT (2)
    /* @brief Has FTM0 triggers source selection (register bits SOPT4[FTM0TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM0_TRIGGER (1)
    /* @brief Has FTM3 triggers source selection (register bits SOPT4[FTM3TRGnSRC], where n is a number). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_TRIGGER (1)
    /* @brief Has FTM1 channel 0 input capture source selection (register bit SOPT4[FTM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM1_CHANNELS (0)
    /* @brief Has FTM2 channel 0 input capture source selection (register bit SOPT4[FTM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNELS (0)
    /* @brief Has FTM3 channel 0 input capture source selection (register bit SOPT4[FTM3CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM3_CHANNELS (0)
    /* @brief Has FTM2 channel 1 input capture source selection (register bit SOPT4[FTM2CH1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM2_CHANNEL1 (0)
    /* @brief Number of configurable FTM0 fault detection input (number of register bits SOPT4[FTM0FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM0_FAULT_COUNT (4)
    /* @brief Number of configurable FTM1 fault detection input (number of register bits SOPT4[FTM1FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM1_FAULT_COUNT (1)
    /* @brief Number of configurable FTM2 fault detection input (number of register bits SOPT4[FTM2FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM2_FAULT_COUNT (0)
    /* @brief Number of configurable FTM3 fault detection input (number of register bits SOPT4[FTM3FLTn], where n is a number starting from zero). */
    #define FSL_FEATURE_SIM_OPT_FTM3_FAULT_COUNT (1)
    /* @brief Has FTM hardware trigger 0 software synchronization (register bit SOPT8[FTMnSYNCBIT], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_TRIGGER_SYNC (1)
    /* @brief Has FTM channels output source selection (register bit SOPT8[FTMxOCHnSRC], where x is a module instance index and n is a channel index). */
    #define FSL_FEATURE_SIM_OPT_HAS_FTM_CHANNELS_OUTPUT_SRC (1)
    /* @brief Has TPM module(s) configuration. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM (0)
    /* @brief The highest TPM module index. */
    #define FSL_FEATURE_SIM_OPT_MAX_TPM_INDEX (0)
    /* @brief Has TPM module with index 0. */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM0 (0)
    /* @brief Is TPM channels configuration in the SOPT4 (not SOPT9) register (register bits TPMnCH0SRC, TPMnCLKSEL, where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM_CHANNELS_CONFIG_IN_SOPT4_REG (0)
    /* @brief Has TPM1 channel 0 input capture source selection (register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM1_CH0_SRC_SELECTION (0)
    /* @brief TPM1 channel 0 input capture source selection width (width of register bit field SOPT4[TPM1CH0SRC] or SOPT9[TPM1CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_TPM1_CH0_SRC_SELECTION_WIDTH (0)
    /* @brief Has TPM2 channel 0 input capture source selection (register bit field SOPT4[TPM2CH0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CH0_SRC_SELECTION (0)
    /* @brief Has TPM2 clock selection (register bit field SOPT4[TPM2CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPM2_CLK_SEL (0)
    /* @brief Has PLL/FLL clock selection (register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_PLL_FLL_SELECTION (0)
    /* @brief PLL/FLL clock selection width (width of register bit field SOPT2[PLLFLLSEL]). */
    #define FSL_FEATURE_SIM_OPT_PLL_FLL_SELECTION_WIDTH (0)
    /* @brief Has NFC clock source selection (register bit SOPT2[NFCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_NFCSRC (0)
    /* @brief Has eSDHC clock source selection (register bit SOPT2[ESDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_ESDHCSRC (0)
    /* @brief Has SDHC clock source selection (register bit SOPT2[SDHCSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_SDHCSRC (0)
    /* @brief Has LCDC clock source selection (register bits SOPT2[LCDCSRC], SOPT2[LCDC_CLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LCDCSRC (0)
    /* @brief Has ENET timestamp clock source selection (register bit SOPT2[TIMESRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TIMESRC (0)
    /* @brief Has ENET RMII clock source selection (register bit SOPT2[RMIISRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_RMIISRC (0)
    /* @brief Has USB clock source selection (register bit SOPT2[USBSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBSRC (0)
    /* @brief Has USB FS clock source selection (register bit SOPT2[USBFSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBFSRC (0)
    /* @brief Has USB HS clock source selection (register bit SOPT2[USBHSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_USBHSRC (0)
    /* @brief Has LPUART clock source selection (register bit SOPT2[LPUARTSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUARTSRC (0)
    /* @brief Has LPUART0 clock source selection (register bit SOPT2[LPUART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART0SRC (0)
    /* @brief Has LPUART1 clock source selection (register bit SOPT2[LPUART1SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_LPUART1SRC (0)
    /* @brief Has FLEXIOSRC clock source selection (register bit SOPT2[FLEXIOSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_FLEXIOSRC (0)
    /* @brief Has UART0 clock source selection (register bit SOPT2[UART0SRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_UART0SRC (0)
    /* @brief Has TPM clock source selection (register bit SOPT2[TPMSRC]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TPMSRC (0)
    /* @brief Has debug trace clock selection (register bit SOPT2[TRACECLKSEL]). */
    #define FSL_FEATURE_SIM_OPT_HAS_TRACE_CLKSEL (1)
    /* @brief Number of ADC modules (register bits SOPT7[ADCnTRGSEL], SOPT7[ADCnPRETRGSEL], SOPT7[ADCnALTTRGSEL], where n is a module instance index). */
    #define FSL_FEATURE_SIM_OPT_ADC_COUNT (1)
    /* @brief Has clock 2 output divider (register bit field CLKDIV1[OUTDIV2]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV2 (1)
    /* @brief Has clock 3 output divider (register bit field CLKDIV1[OUTDIV3]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV3 (0)
    /* @brief Has clock 4 output divider (register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_OUTDIV4 (1)
    /* @brief Clock 4 output divider width (width of register bit field CLKDIV1[OUTDIV4]). */
    #define FSL_FEATURE_SIM_DIVIDER_OUTDIV4_WIDTH (4)
    /* @brief Has USB clock divider (register bit field CLKDIV2[USBDIV] and CLKDIV2[USBFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBDIV (0)
    /* @brief Has USB FS clock divider (register bit field CLKDIV2[USBFSDIV] and CLKDIV2[USBFSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBFSDIV (0)
    /* @brief Has USB HS clock divider (register bit field CLKDIV2[USBHSDIV] and CLKDIV2[USBHSFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_USBHSDIV (0)
    /* @brief Has PLL/FLL clock divider (register bit field CLKDIV3[PLLFLLDIV] and CLKDIV3[PLLFLLFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_PLLFLLDIV (0)
    /* @brief Has LCDC clock divider (register bit field CLKDIV3[LCDCDIV] and CLKDIV3[LCDCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_LCDCDIV (0)
    /* @brief Has trace clock divider (register bit field CLKDIV4[TRACEDIV] and CLKDIV4[TRACEFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_TRACEDIV (1)
    /* @brief Has NFC clock divider (register bit field CLKDIV4[NFCDIV] and CLKDIV4[NFCFRAC]). */
    #define FSL_FEATURE_SIM_DIVIDER_HAS_NFCDIV (0)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMILYID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMILYID (1)
    /* @brief Has Kinetis family ID (register bit field SDID[FAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_FAMID (0)
    /* @brief Has Kinetis sub-family ID (register bit field SDID[SUBFAMID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SUBFAMID (1)
    /* @brief Has Kinetis series ID (register bit field SDID[SERIESID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SERIESID (1)
    /* @brief Has device die ID (register bit field SDID[DIEID]). */
    #define FSL_FEATURE_SIM_SDID_HAS_DIEID (1)
    /* @brief Has system SRAM size specifier (register bit field SDID[SRAMSIZE]). */
    #define FSL_FEATURE_SIM_SDID_HAS_SRAMSIZE (0)
    /* @brief Has flash mode (register bit FCFG1[FLASHDOZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDOZE (1)
    /* @brief Has flash disable (register bit FCFG1[FLASHDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FLASHDIS (1)
    /* @brief Has FTFE disable (register bit FCFG1[FTFDIS]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_FTFDIS (0)
    /* @brief Has FlexNVM size specifier (register bit field FCFG1[NVMSIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_NVMSIZE (0)
    /* @brief Has EEPROM size specifier (register bit field FCFG1[EESIZE]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_EESIZE (0)
    /* @brief Has FlexNVM partition (register bit field FCFG1[DEPART]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_DEPART (0)
    /* @brief Maximum flash address block 0 address specifier (register bit field FCFG2[MAXADDR0]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR0 (1)
    /* @brief Maximum flash address block 1 address specifier (register bit field FCFG2[MAXADDR1]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR1 (0)
    /* @brief Maximum flash address block 0 or 1 address specifier (register bit field FCFG2[MAXADDR01]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR01 (0)
    /* @brief Maximum flash address block 2 or 3 address specifier (register bit field FCFG2[MAXADDR23]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_MAXADDR23 (0)
    /* @brief Has program flash availability specifier (register bit FCFG2[PFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH (0)
    /* @brief Has program flash swapping (register bit FCFG2[SWAPPFLSH]). */
    #define FSL_FEATURE_SIM_FCFG_HAS_PFLSH_SWAP (0)
    /* @brief Has miscellanious control register (register MCR). */
    #define FSL_FEATURE_SIM_HAS_MISC_CONTROLS (0)
    /* @brief Has COP watchdog (registers COPC and SRVCOP). */
    #define FSL_FEATURE_SIM_HAS_COP_WATCHDOG (0)
    /* @brief Has COP watchdog stop (register bits COPC[COPSTPEN], COPC[COPDBGEN] and COPC[COPCLKSEL]). */
    #define FSL_FEATURE_SIM_HAS_COP_STOP (0)
#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_SIM_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
