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

#ifndef _MXC_CLKMAN_REGS_H_
#define _MXC_CLKMAN_REGS_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  clkman_regs.h
 * @addtogroup clkman CLKMAN
 * @{
 */

/**
 * @brief Defines clock input selections for the phase locked loop.
 */
typedef enum {
    /** Input select for high frequency crystal oscillator */
    MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX = 0,
    /** Input select for 24MHz ring oscillator */
    MXC_E_CLKMAN_PLL_INPUT_SELECT_24MHZ_RO,
} mxc_clkman_pll_input_select_t;

/**
 * @brief Defines clock input frequency for the phase locked loop.
 */
typedef enum {
    /** Input frequency of 24MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_24MHZ = 0,
    /** Input frequency of 12MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_12MHZ,
    /** Input frequency of 8MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_8MHZ,
} mxc_clkman_pll_divisor_select_t;

/**
 * @brief Defines terminal count for PLL stable.
 */
typedef enum {
    /** Clock stable after 2^8 = 256 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_8_CLKS = 0,
    /** Clock stable after 2^9 = 512 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_9_CLKS,
    /** Clock stable after 2^10 = 1024 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_10_CLKS,
    /** Clock stable after 2^11 = 2048 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_11_CLKS,
    /** Clock stable after 2^12 = 4096 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_12_CLKS,
    /** Clock stable after 2^13 = 8192 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_13_CLKS,
    /** Clock stable after 2^14 = 16384 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_14_CLKS,
    /** Clock stable after 2^15 = 32768 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_15_CLKS,
    /** Clock stable after 2^16 = 65536 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_16_CLKS,
    /** Clock stable after 2^17 = 131072 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_17_CLKS,
    /** Clock stable after 2^18 = 262144 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_18_CLKS,
    /** Clock stable after 2^19 = 524288 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_19_CLKS,
    /** Clock stable after 2^20 = 1048576 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_20_CLKS,
    /** Clock stable after 2^21 = 2097152 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_21_CLKS,
    /** Clock stable after 2^22 = 4194304 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_22_CLKS,
    /** Clock stable after 2^23 = 8388608 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_23_CLKS
} mxc_clkman_stability_count_t;

/**
 * @brief Defines clock source selections for system clock.
 */
typedef enum {
    /** Clock select for 24MHz ring oscillator divided by 8 (3MHz) */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO_DIV_8 = 0,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX,
    /** Clock select for 48MHz phase locked loop output divided by 2 (24MHz) */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2
} mxc_clkman_system_source_select_t;

/**
 * @brief Defines clock source selections for analog to digital converter clock.
 */
typedef enum {
    /** Clock select for system clock frequency */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_SYSTEM = 0,
    /** Clock select for 8MHz phase locked loop output */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_PLL_8MHZ,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_HFX,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_24MHZ_RO,
} mxc_clkman_adc_source_select_t;

/**
 * @brief Defines clock source selections for watchdog timer clock.
 */
typedef enum {
    /** Clock select for system clock frequency */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_SYSTEM = 0,
    /** Clock select for 8MHz phase locked loop output */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_RTC,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_24MHZ_RO,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_NANO,
} mxc_clkman_wdt_source_select_t;

/**
 * @brief Defines clock scales for various clocks.
 */
typedef enum {
    /** Clock disabled */
    MXC_E_CLKMAN_CLK_SCALE_DISABLED = 0,
    /** Clock enabled */
    MXC_E_CLKMAN_CLK_SCALE_ENABLED,
    /** Clock scale for dividing by 2 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_2,
    /** Clock scale for dividing by 4 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_4,
    /** Clock scale for dividing by 8 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_8,
    /** Clock scale for dividing by 16 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_16,
    /** Clock scale for dividing by 32 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_32,
    /** Clock scale for dividing by 64 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_64,
    /** Clock scale for dividing by 128 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_128,
    /** Clock scale for dividing by 256 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_256
} mxc_clkman_clk_scale_t;

/**
 * @brief Defines Setting of the Clock Gates .
 */
typedef enum {
    /** Clock Gater is Off */
    MXC_E_CLKMAN_CLK_GATE_OFF  = 0,
    /** Clock Gater is Dynamic */
    MXC_E_CLKMAN_CLK_GATE_DYNAMIC,
    /** Clock Gater is On */
    MXC_E_CLKMAN_CLK_GATE_ON
} mxc_clkman_clk_gate_t;

/*                                               Offset   Register Description
                                                 ======   ===================================================================== */
typedef struct {
    __IO uint32_t clk_config;                /*  0x0000   System Clock Configuration                                  */
    __IO uint32_t clk_ctrl;                  /*  0x0004   System Clock Controls                                                 */
    __IO uint32_t intfl;                     /*  0x0008   Interrupt Flags                                             */
    __IO uint32_t inten;                     /*  0x000C   Interrupt Enable/Disable Controls                           */
    __IO uint32_t trim_calc;                 /*  0x0010   Trim Calculation Controls                                   */
    __I uint32_t rsv0014[4];                 /*  0x0014                                                               */
    __IO uint32_t i2c_timer_ctrl;            /*  0x0024   I2C Timer Control                                           */
    __I uint32_t rsv0028[6];                 /*  0x0028                                                               */
    __IO uint32_t clk_ctrl_0_system;         /*  0x0040   Control Settings for CLK0 - System Clock                    */
    __IO uint32_t clk_ctrl_1_gpio;           /*  0x0044   Control Settings for CLK1 - GPIO Module Clock               */
    __IO uint32_t clk_ctrl_2_pt;             /*  0x0048   Control Settings for CLK2 - Pulse Train Module Clock        */
    __IO uint32_t clk_ctrl_3_spi0;           /*  0x004C   Control Settings for CLK3 - SPI0 Master Clock               */
    __IO uint32_t clk_ctrl_4_spi1;           /*  0x0050   Control Settings for CLK4 - SPI1 Master Clock               */
    __IO uint32_t clk_ctrl_5_spi2;           /*  0x0054   Control Settings for CLK5 - SPI2 Master Clock               */
    __IO uint32_t clk_ctrl_6_i2cm;           /*  0x0058   Control Settings for CLK6 - Clock for all I2C Masters       */
    __IO uint32_t clk_ctrl_7_i2cs;           /*  0x005C   Control Settings for CLK7 - I2C Slave Clock                 */
    __IO uint32_t clk_ctrl_8_lcd_chpump;     /*  0x0060   Control Settings for CLK8 - LCD Charge Pump Clock           */
    __IO uint32_t clk_ctrl_9_puf;            /*  0x0064   Control Settings for CLK9 - PUF Clock                       */
    __IO uint32_t clk_ctrl_10_prng;          /*  0x0068   Control Settings for CLK10 - PRNG Clock                     */
    __IO uint32_t clk_ctrl_11_wdt0;          /*  0x006C   Control Settings for CLK11 - Watchdog Timer 0 ScaledSysClk  */
    __IO uint32_t clk_ctrl_12_wdt1;          /*  0x0070   Control Settings for CLK12 - Watchdog Timer 1 ScaledSysClk  */
    __IO uint32_t clk_ctrl_13_rtc_int_sync;  /*  0x0074   Control Settings for CLK13 - RTC Interrupt Sync Clock       */
    __IO uint32_t clk_ctrl_14_dac0;          /*  0x0078   Control Settings for CLK14 - 12-bit DAC 0 Clock             */
    __IO uint32_t clk_ctrl_15_dac1;          /*  0x007C   Control Settings for CLK15 - 12-bit DAC 1 Clock             */
    __IO uint32_t clk_ctrl_16_dac2;          /*  0x0080   Control Settings for CLK16 - 8-bit DAC 0 Clock              */
    __IO uint32_t clk_ctrl_17_dac3;          /*  0x0084   Control Settings for CLK17 - 8-bit DAC 1 Clock              */
    __I uint32_t rsv0088[30];                /*  0x0088                                                               */
    __IO uint32_t crypt_clk_ctrl_0_aes;      /*  0x0100   Control Settings for Crypto Clock 0 - AES                   */
    __IO uint32_t crypt_clk_ctrl_1_maa;      /*  0x0104   Control Settings for Crypto Clock 1 - MAA                   */
    __IO uint32_t crypt_clk_ctrl_2_prng;     /*  0x0108   Control Settings for Crypto Clock 2 - PRNG                  */
    __I uint32_t rsv010C[13];                /*  0x010C                                                               */
    __IO uint32_t clk_gate_ctrl0;            /*  0x0140   Dynamic Clock Gating Control Register 0                     */
    __IO uint32_t clk_gate_ctrl1;            /*  0x0144   Dynamic Clock Gating Control Register 1                     */
    __IO uint32_t clk_gate_ctrl2;            /*  0x0148   Dynamic Clock Gating Control Register 2                     */
} mxc_clkman_regs_t;

/*
   Register offsets for module CLKMAN.
*/
#define MXC_R_CLKMAN_OFFS_CLK_CONFIG                ((uint32_t)0x00000000UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL                  ((uint32_t)0x00000004UL)
#define MXC_R_CLKMAN_OFFS_INTFL                     ((uint32_t)0x00000008UL)
#define MXC_R_CLKMAN_OFFS_INTEN                     ((uint32_t)0x0000000CUL)
#define MXC_R_CLKMAN_OFFS_TRIM_CALC                 ((uint32_t)0x00000010UL)
#define MXC_R_CLKMAN_OFFS_I2C_TIMER_CTRL            ((uint32_t)0x00000024UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_0_SYSTEM         ((uint32_t)0x00000040UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_1_GPIO           ((uint32_t)0x00000044UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_2_PT             ((uint32_t)0x00000048UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_3_SPI0           ((uint32_t)0x0000004CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_4_SPI1           ((uint32_t)0x00000050UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_5_SPI2           ((uint32_t)0x00000054UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_6_I2CM           ((uint32_t)0x00000058UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_7_I2CS           ((uint32_t)0x0000005CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_8_LCD_CHPUMP     ((uint32_t)0x00000060UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_9_PUF            ((uint32_t)0x00000064UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_10_PRNG          ((uint32_t)0x00000068UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_11_WDT0          ((uint32_t)0x0000006CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_12_WDT1          ((uint32_t)0x00000070UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_13_RTC_INT_SYNC  ((uint32_t)0x00000074UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_14_DAC0          ((uint32_t)0x00000078UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_15_DAC1          ((uint32_t)0x0000007CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_16_DAC2          ((uint32_t)0x00000080UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_17_DAC3          ((uint32_t)0x00000084UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_0_AES      ((uint32_t)0x00000100UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_1_MAA      ((uint32_t)0x00000104UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_2_PRNG     ((uint32_t)0x00000108UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL0            ((uint32_t)0x00000140UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL1            ((uint32_t)0x00000144UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL2            ((uint32_t)0x00000148UL)

/*
   Field positions and masks for module CLKMAN.
*/
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_ENABLE_POS                  0
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_ENABLE                      ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_HFX_ENABLE_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_BYPASS_POS                  1
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_BYPASS                      ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_HFX_BYPASS_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_TEST_ENABLE_POS             2
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_TEST_ENABLE                 ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_HFX_TEST_ENABLE_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_GM_ADJUST_POS               4
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_GM_ADJUST                   ((uint32_t)(0x0000001FUL << MXC_F_CLKMAN_CLK_CONFIG_HFX_GM_ADJUST_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_DC_CONTROL_POS              9
#define MXC_F_CLKMAN_CLK_CONFIG_HFX_DC_CONTROL                  ((uint32_t)(0x00000007UL << MXC_F_CLKMAN_CLK_CONFIG_HFX_DC_CONTROL_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_ENABLE_POS                  12
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_ENABLE                      ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_ENABLE_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_RESET_N_POS                 13
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_RESET_N                     ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_RESET_N_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_INPUT_SELECT_POS            14
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_INPUT_SELECT                ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_INPUT_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT_POS          16
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_DIVISOR_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_8MHZ_ENABLE_POS             18
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_8MHZ_ENABLE                 ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_8MHZ_ENABLE_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_BYPASS_POS                  19
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_BYPASS                      ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_PLL_BYPASS_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_STABILITY_COUNT_POS         20
#define MXC_F_CLKMAN_CLK_CONFIG_PLL_STABILITY_COUNT             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CONFIG_PLL_STABILITY_COUNT_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_ENABLE_POS               24
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_ENABLE                   ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_ENABLE_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_RESET_N_POS              25
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_RESET_N                  ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_RESET_N_POS))
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_STABILITY_COUNT_POS      28
#define MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_STABILITY_COUNT          ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CONFIG_CRYPTO_STABILITY_COUNT_POS))

#define MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT_POS          1
#define MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_CTRL_SYSTEM_SOURCE_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CTRL_AUTO_CLK_DISABLE_POS              3
#define MXC_F_CLKMAN_CLK_CTRL_AUTO_CLK_DISABLE                  ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_AUTO_CLK_DISABLE_POS))
#define MXC_F_CLKMAN_CLK_CTRL_USB_GATE_N_POS                    4
#define MXC_F_CLKMAN_CLK_CTRL_USB_GATE_N                        ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_USB_GATE_N_POS))
#define MXC_F_CLKMAN_CLK_CTRL_ADC_GATE_N_POS                    8
#define MXC_F_CLKMAN_CLK_CTRL_ADC_GATE_N                        ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_ADC_GATE_N_POS))
#define MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT_POS             9
#define MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT                 ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_CTRL_ADC_SOURCE_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CTRL_CRYPTO_GATE_N_POS                 12
#define MXC_F_CLKMAN_CLK_CTRL_CRYPTO_GATE_N                     ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_CRYPTO_GATE_N_POS))
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_GATE_N_POS              16
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_GATE_N                  ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_GATE_N_POS))
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_SOURCE_SELECT_POS       17
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_SOURCE_SELECT           ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_CTRL_WATCHDOG0_SOURCE_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_GATE_N_POS              20
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_GATE_N                  ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_GATE_N_POS))
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_SOURCE_SELECT_POS       21
#define MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_SOURCE_SELECT           ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_CTRL_WATCHDOG1_SOURCE_SELECT_POS))
#define MXC_F_CLKMAN_CLK_CTRL_RTOS_MODE_POS                     24
#define MXC_F_CLKMAN_CLK_CTRL_RTOS_MODE                         ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_CLK_CTRL_RTOS_MODE_POS))

#define MXC_F_CLKMAN_INTFL_RING_STABLE_POS                      0
#define MXC_F_CLKMAN_INTFL_RING_STABLE                          ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTFL_RING_STABLE_POS))
#define MXC_F_CLKMAN_INTFL_PLL_STABLE_POS                       1
#define MXC_F_CLKMAN_INTFL_PLL_STABLE                           ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTFL_PLL_STABLE_POS))
#define MXC_F_CLKMAN_INTFL_CRYPTO_STABLE_POS                    2
#define MXC_F_CLKMAN_INTFL_CRYPTO_STABLE                        ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTFL_CRYPTO_STABLE_POS))

#define MXC_F_CLKMAN_INTEN_RING_STABLE_POS                      0
#define MXC_F_CLKMAN_INTEN_RING_STABLE                          ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTEN_RING_STABLE_POS))
#define MXC_F_CLKMAN_INTEN_PLL_STABLE_POS                       1
#define MXC_F_CLKMAN_INTEN_PLL_STABLE                           ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTEN_PLL_STABLE_POS))
#define MXC_F_CLKMAN_INTEN_CRYPTO_STABLE_POS                    2
#define MXC_F_CLKMAN_INTEN_CRYPTO_STABLE                        ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_INTEN_CRYPTO_STABLE_POS))

#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CLK_SEL_POS                 0
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CLK_SEL                     ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_TRIM_CALC_TRIM_CLK_SEL_POS))
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_START_POS              1
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_START                  ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_START_POS))
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_COMPLETED_POS          2
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_COMPLETED              ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_COMPLETED_POS))
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_ENABLE_POS                  3
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_ENABLE                      ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_TRIM_CALC_TRIM_ENABLE_POS))
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_RESULTS_POS            16
#define MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_RESULTS                ((uint32_t)(0x000003FFUL << MXC_F_CLKMAN_TRIM_CALC_TRIM_CALC_RESULTS_POS))

#define MXC_F_CLKMAN_I2C_TIMER_CTRL_I2C_1MS_TIMER_EN_POS        0
#define MXC_F_CLKMAN_I2C_TIMER_CTRL_I2C_1MS_TIMER_EN            ((uint32_t)(0x00000001UL << MXC_F_CLKMAN_I2C_TIMER_CTRL_I2C_1MS_TIMER_EN_POS))

#define MXC_F_CLKMAN_CLK_CTRL_0_SYSTEM_SYS_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_0_SYSTEM_SYS_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_0_SYSTEM_SYS_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_1_GPIO_GPIO_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_1_GPIO_GPIO_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_1_GPIO_GPIO_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_2_PT_PULSE_TRAIN_CLK_SCALE_POS    0
#define MXC_F_CLKMAN_CLK_CTRL_2_PT_PULSE_TRAIN_CLK_SCALE        ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_2_PT_PULSE_TRAIN_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_3_SPI0_SPI0_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_3_SPI0_SPI0_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_3_SPI0_SPI0_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_4_SPI1_SPI1_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_4_SPI1_SPI1_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_4_SPI1_SPI1_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_5_SPI2_SPI2_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_5_SPI2_SPI2_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_5_SPI2_SPI2_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_6_I2CM_I2CM_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_6_I2CM_I2CM_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_6_I2CM_I2CM_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_7_I2CS_I2CS_CLK_SCALE_POS         0
#define MXC_F_CLKMAN_CLK_CTRL_7_I2CS_I2CS_CLK_SCALE             ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_7_I2CS_I2CS_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_8_LCD_CHPUMP_LCD_CLK_SCALE_POS    0
#define MXC_F_CLKMAN_CLK_CTRL_8_LCD_CHPUMP_LCD_CLK_SCALE        ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_8_LCD_CHPUMP_LCD_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_9_PUF_PUF_CLK_SCALE_POS           0
#define MXC_F_CLKMAN_CLK_CTRL_9_PUF_PUF_CLK_SCALE               ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_9_PUF_PUF_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_10_PRNG_PRNG_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_10_PRNG_PRNG_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_10_PRNG_PRNG_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_11_WDT0_WATCHDOG0_CLK_SCALE_POS   0
#define MXC_F_CLKMAN_CLK_CTRL_11_WDT0_WATCHDOG0_CLK_SCALE       ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_11_WDT0_WATCHDOG0_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_12_WDT1_WATCHDOG1_CLK_SCALE_POS   0
#define MXC_F_CLKMAN_CLK_CTRL_12_WDT1_WATCHDOG1_CLK_SCALE       ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_12_WDT1_WATCHDOG1_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_13_RTC_INT_SYNC_RTC_CLK_SCALE_POS 0
#define MXC_F_CLKMAN_CLK_CTRL_13_RTC_INT_SYNC_RTC_CLK_SCALE     ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_13_RTC_INT_SYNC_RTC_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_14_DAC0_DAC0_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_14_DAC0_DAC0_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_14_DAC0_DAC0_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_15_DAC1_DAC1_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_15_DAC1_DAC1_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_15_DAC1_DAC1_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_16_DAC2_DAC2_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_16_DAC2_DAC2_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_16_DAC2_DAC2_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_CTRL_17_DAC3_DAC3_CLK_SCALE_POS        0
#define MXC_F_CLKMAN_CLK_CTRL_17_DAC3_DAC3_CLK_SCALE            ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CLK_CTRL_17_DAC3_DAC3_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_0_AES_AES_CLK_SCALE_POS     0
#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_0_AES_AES_CLK_SCALE         ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CRYPT_CLK_CTRL_0_AES_AES_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_1_MAA_UMAA_CLK_SCALE_POS    0
#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_1_MAA_UMAA_CLK_SCALE        ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CRYPT_CLK_CTRL_1_MAA_UMAA_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_2_PRNG_PRNG_CLK_SCALE_POS   0
#define MXC_F_CLKMAN_CRYPT_CLK_CTRL_2_PRNG_PRNG_CLK_SCALE       ((uint32_t)(0x0000000FUL << MXC_F_CLKMAN_CRYPT_CLK_CTRL_2_PRNG_PRNG_CLK_SCALE_POS))

#define MXC_F_CLKMAN_CLK_GATE_CTRL0_CM3_CLK_GATER_POS           0
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_CM3_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_CM3_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSBUS_CLK_GATER_POS        2
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSBUS_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSBUS_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER_POS        4
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_ICACHE_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_FLASH_CLK_GATER_POS         6
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_FLASH_CLK_GATER             ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_FLASH_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SRAM_CLK_GATER_POS          8
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SRAM_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_SRAM_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_APB_BRIDGE_CLK_GATER_POS    10
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_APB_BRIDGE_CLK_GATER        ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_APB_BRIDGE_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSMAN_CLK_GATER_POS        12
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSMAN_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_SYSMAN_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_UART0_CLK_GATER_POS         14
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_UART0_CLK_GATER             ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_UART0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_UART1_CLK_GATER_POS         16
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_UART1_CLK_GATER             ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_UART1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER0_CLK_GATER_POS        18
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER0_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER1_CLK_GATER_POS        20
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER1_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER2_CLK_GATER_POS        22
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER2_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER2_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER3_CLK_GATER_POS        24
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER3_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_TIMER3_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG0_CLK_GATER_POS     26
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG0_CLK_GATER         ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG1_CLK_GATER_POS     28
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG1_CLK_GATER         ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_WATCHDOG1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_USB_CLK_GATER_POS           30
#define MXC_F_CLKMAN_CLK_GATE_CTRL0_USB_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL0_USB_CLK_GATER_POS))

#define MXC_F_CLKMAN_CLK_GATE_CTRL1_TESTACC_CLK_GATER_POS       0
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_TESTACC_CLK_GATER           ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_TESTACC_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_ADC_CLK_GATER_POS           2
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_ADC_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_ADC_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_0_CLK_GATER_POS       4
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_0_CLK_GATER           ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_1_CLK_GATER_POS       6
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_1_CLK_GATER           ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC12_1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_0_CLK_GATER_POS        8
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_0_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_1_CLK_GATER_POS        10
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_1_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_DAC8_1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_PMU_CLK_GATER_POS           12
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_PMU_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_PMU_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_LCD_CLK_GATER_POS           14
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_LCD_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_LCD_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_GPIO_CLK_GATER_POS          16
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_GPIO_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_GPIO_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_PULSETRAIN_CLK_GATER_POS    18
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_PULSETRAIN_CLK_GATER        ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_PULSETRAIN_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI0_CLK_GATER_POS          20
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI0_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI1_CLK_GATER_POS          22
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI1_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI2_CLK_GATER_POS          24
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI2_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_SPI2_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM0_CLK_GATER_POS         26
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM0_CLK_GATER             ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM0_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM1_CLK_GATER_POS         28
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM1_CLK_GATER             ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CM1_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CS_CLK_GATER_POS          30
#define MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CS_CLK_GATER              ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL1_I2CS_CLK_GATER_POS))

#define MXC_F_CLKMAN_CLK_GATE_CTRL2_CRC_CLK_GATER_POS           0
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_CRC_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL2_CRC_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_TPU_CLK_GATER_POS           2
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_TPU_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL2_TPU_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_SSBMUX_CLK_GATER_POS        4
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_SSBMUX_CLK_GATER            ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL2_SSBMUX_CLK_GATER_POS))
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_PAD_CLK_GATER_POS           6
#define MXC_F_CLKMAN_CLK_GATE_CTRL2_PAD_CLK_GATER               ((uint32_t)(0x00000003UL << MXC_F_CLKMAN_CLK_GATE_CTRL2_PAD_CLK_GATER_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_CLKMAN_REGS_H_ */
