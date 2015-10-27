#ifndef MBED_BITFIELDS_H
#define MBED_BITFIELDS_H

//! Massage  x for use in bitfield  name.
#define BFN_PREP(x, name)    ( ((x)<<name##_SHIFT) & name##_MASK )

//! Get the value of bitfield  name from  y. Equivalent to (var=) y.name
#define BFN_GET(y, name)     ( ((y) & name##_MASK)>>name##_SHIFT )

//! Set bitfield  name from  y to  x: y.name= x.
#define BFN_SET(y, x, name)  (y = ((y)&~name##_MASK) | BFN_PREP(x,name) )


/* SYSMEMREMAP, address 0x4004 8000 */
#define SYSMEMREMAP_MAP_MASK           0x0003             // System memory remap
#define SYSMEMREMAP_MAP_SHIFT          0                 

/* PRESETCTRL, address 0x4004 8004 */
#define PRESETCTRL_SSP0_RST_N          (1 << 0)           // SPI0 reset control
#define PRESETCTRL_I2C_RST_N           (1 << 1)           // I2C reset control
#define PRESETCTRL_SSP1_RST_N          (1 << 2)           // SPI1 reset control
#define PRESETCTRL_CAN_RST_N           (1 << 3)           // C_CAN reset control. See Section 3.1 for part specific details.

/* SYSPLLCTRL, address 0x4004 8008 */
#define SYSPLLCTRL_MSEL_MASK           0x001F             // Feedback divider value. The division value M is the programmed MSEL value + 1. 00000: Division ratio M = 1 to 11111: Division ratio M = 32.
#define SYSPLLCTRL_MSEL_SHIFT          0                 
#define SYSPLLCTRL_PSEL_MASK           0x0060             // Post divider ratio P. The division ratio is 2  P.
#define SYSPLLCTRL_PSEL_SHIFT          5                 

/* SYSPLLSTAT, address 0x4004 800C */
#define SYSPLLSTAT_LOCK                (1 << 0)           // PLL lock status

/* SYSOSCCTRL, address 0x4004 8020 */
#define SYSOSCCTRL_BYPASS              (1 << 0)           // Bypass system oscillator
#define SYSOSCCTRL_FREQRANGE           (1 << 1)           // Determines frequency range for Low-power oscillator.

/* WDTOSCCTRL, address 0x4004 8024 */
#define WDTOSCCTRL_DIVSEL_MASK         0x001F             // Select divider for Fclkana. wdt_osc_clk = Fclkana/ (2  (1 + DIVSEL)) 00000: 2  (1 + DIVSEL) = 2 00001: 2  (1 + DIVSEL) = 4 to 11111: 2  (1 + DIVSEL) = 64
#define WDTOSCCTRL_DIVSEL_SHIFT        0                 
#define WDTOSCCTRL_FREQSEL_MASK        0x01E0             // Select watchdog oscillator analog output frequency (Fclkana).
#define WDTOSCCTRL_FREQSEL_SHIFT       5                 

/* IRCCTRL, address 0x4004 8028 */
#define IRCCTRL_TRIM_MASK              0x00FF             // Trim value 
#define IRCCTRL_TRIM_SHIFT             0                 

/* SYSRSTSTAT, address 0x4004 8030 */
#define SYSRSTSTAT_POR                 (1 << 0)           // POR reset status
#define SYSRSTSTAT_EXTRST              (1 << 1)           // Status of the external RESET pin.
#define SYSRSTSTAT_WDT                 (1 << 2)           // Status of the Watchdog reset
#define SYSRSTSTAT_BOD                 (1 << 3)           // Status of the Brown-out detect reset
#define SYSRSTSTAT_SYSRST              (1 << 4)           // Status of the software system reset

/* SYSPLLCLKSEL, address 0x4004 8040 */
#define SYSPLLCLKSEL_SEL_MASK          0x0003             // System PLL clock source
#define SYSPLLCLKSEL_SEL_SHIFT         0                 

/* SYSPLLCLKUEN, address 0x4004 8044 */
#define SYSPLLCLKUEN_ENA               (1 << 0)           // Enable system PLL clock source update

/* MAINCLKSEL, address 0x4004 8070 */
#define MAINCLKSEL_SEL_MASK            0x0003             // Clock source for main clock
#define MAINCLKSEL_SEL_SHIFT           0                 

/* MAINCLKUEN, address 0x4004 8074 */
#define MAINCLKUEN_ENA                 (1 << 0)           // Enable main clock source update                                   0

/* SYSAHBCLKDIV, address 0x4004 8078 */
#define SYSAHBCLKDIV_DIV_MASK          0x00FF             // System AHB clock divider values 0: System clock disabled. 1: Divide by 1. to 255: Divide by 255.
#define SYSAHBCLKDIV_DIV_SHIFT         0                 

/* SYSAHBCLKCTRL, address 0x4004 8080 */
#define SYSAHBCLKCTRL_SYS              (1 << 0)           // Enables clock for AHB to APB bridge, to the AHB matrix, to the Cortex-M0 FCLK and HCLK, to the SysCon, and to the PMU. This bit is read only.
#define SYSAHBCLKCTRL_ROM              (1 << 1)           // Enables clock for ROM.
#define SYSAHBCLKCTRL_RAM              (1 << 2)           // Enables clock for RAM.
#define SYSAHBCLKCTRL_FLASHREG         (1 << 3)           // Enables clock for flash register interface.
#define SYSAHBCLKCTRL_FLASHARRAY       (1 << 4)           // Enables clock for flash array access.
#define SYSAHBCLKCTRL_I2C              (1 << 5)           // Enables clock for I2C.
#define SYSAHBCLKCTRL_GPIO             (1 << 6)           // Enables clock for GPIO.
#define SYSAHBCLKCTRL_CT16B0           (1 << 7)           // Enables clock for 16-bit counter/timer 0.
#define SYSAHBCLKCTRL_CT16B1           (1 << 8)           // Enables clock for 16-bit counter/timer 1.
#define SYSAHBCLKCTRL_CT32B0           (1 << 9)           // Enables clock for 32-bit counter/timer 0.
#define SYSAHBCLKCTRL_CT32B1           (1 << 10)          // Enables clock for 32-bit counter/timer 1.
#define SYSAHBCLKCTRL_SSP0             (1 << 11)          // Enables clock for SPI0.
#define SYSAHBCLKCTRL_UART             (1 << 12)          // Enables clock for UART. See Section 3.1 for part specific details.
#define SYSAHBCLKCTRL_ADC              (1 << 13)          // Enables clock for ADC.
#define SYSAHBCLKCTRL_WDT              (1 << 15)          // Enables clock for WDT.
#define SYSAHBCLKCTRL_IOCON            (1 << 16)          // Enables clock for I/O configuration block.
#define SYSAHBCLKCTRL_CAN              (1 << 17)          // Enables clock for C_CAN. See Section 3.1 for part specific details.
#define SYSAHBCLKCTRL_SSP1             (1 << 18)          // Enables clock for SPI1.

/* SSP0CLKDIV, address 0x4004 8094 */
#define SSP0CLKDIV_DIV_MASK            0x00FF             // SPI0_PCLK clock divider values 0: Disable SPI0_PCLK. 1: Divide by 1. to 255: Divide by 255.
#define SSP0CLKDIV_DIV_SHIFT           0                 

/* UARTCLKDIV, address 0x4004 8098 */
#define UARTCLKDIV_DIV_MASK            0x00FF             // UART_PCLK clock divider values 0: Disable UART_PCLK. 1: Divide by 1. to 255: Divide by 255.
#define UARTCLKDIV_DIV_SHIFT           0                 

/* SSP1CLKDIV, address 0x4004 809C */
#define SSP1CLKDIV_DIV_MASK            0x00FF             // SPI1_PCLK clock divider values 0: Disable SPI1_PCLK. 1: Divide by 1. to 255: Divide by 255.
#define SSP1CLKDIV_DIV_SHIFT           0                 

/* WDTCLKSEL, address 0x4004 80D0 */
#define WDTCLKSEL_SEL_MASK             0x0003             // WDT clock source
#define WDTCLKSEL_SEL_SHIFT            0                 

/* WDTCLKUEN, address 0x4004 80D4 */
#define WDTCLKUEN_ENA                  (1 << 0)           // Enable WDT clock source update

/* WDTCLKDIV, address 0x4004 80D8 */
#define WDTCLKDIV_DIV_MASK             0x00FF             // WDT clock divider values 0: Disable WDCLK. 1: Divide by 1. to 255: Divide by 255.
#define WDTCLKDIV_DIV_SHIFT            0                 

/* CLKOUTCLKSEL, address 0x4004 80E0 */
#define CLKOUTCLKSEL_SEL_MASK          0x0003             // CLKOUT clock source
#define CLKOUTCLKSEL_SEL_SHIFT         0                 

/* CLKOUTUEN, address 0x4004 80E4 */
#define CLKOUTUEN_ENA                  (1 << 0)           // Enable CLKOUT clock source update                              0

/* CLKOUTCLKDIV, address 0x4004 80E8 */
#define CLKOUTCLKDIV_DIV_MASK          0x00FF             // Clock output divider values 0: Disable CLKOUT. 1: Divide by 1. to 255: Divide by 255.
#define CLKOUTCLKDIV_DIV_SHIFT         0                 

/* PIOPORCAP0, address 0x4004 8100 */
#define PIOPORCAP0_CAPPIO0_N_MASK      0x0FFF             // Raw reset status input PIO0_n: PIO0_11 to PIO0_0
#define PIOPORCAP0_CAPPIO0_N_SHIFT     0                 
#define PIOPORCAP0_CAPPIO1_N_MASK      0xFFF000           // Raw reset status input PIO1_n: PIO1_11 to PIO1_0
#define PIOPORCAP0_CAPPIO1_N_SHIFT     12                
#define PIOPORCAP0_CAPPIO2_N_MASK      0xFF000000         // Raw reset status input PIO2_n: PIO2_7 to PIO2_0
#define PIOPORCAP0_CAPPIO2_N_SHIFT     24                

/* PIOPORCAP1, address 0x4004 8104 */
#define PIOPORCAP1_CAPPIO2_8           (1 << 0)           // Raw reset status input PIO2_8
#define PIOPORCAP1_CAPPIO2_9           (1 << 1)           // Raw reset status input PIO2_9
#define PIOPORCAP1_CAPPIO2_10          (1 << 2)           // Raw reset status input PIO2_10
#define PIOPORCAP1_CAPPIO2_11          (1 << 3)           // Raw reset status input PIO2_11
#define PIOPORCAP1_CAPPIO3_0           (1 << 4)           // Raw reset status input PIO3_0
#define PIOPORCAP1_CAPPIO3_1           (1 << 5)           // Raw reset status input PIO3_1
#define PIOPORCAP1_CAPPIO3_2           (1 << 6)           // Raw reset status input PIO3_2
#define PIOPORCAP1_CAPPIO3_3           (1 << 7)           // Raw reset status input PIO3_3
#define PIOPORCAP1_CAPPIO3_4           (1 << 8)           // Raw reset status input PIO3_4
#define PIOPORCAP1_CAPPIO3_5           (1 << 9)           // Raw reset status input PIO3_5

/* BODCTRL, address 0x4004 8150 */
#define BODCTRL_BODRSTLEV_MASK         0x0003             // BOD reset level
#define BODCTRL_BODRSTLEV_SHIFT        0                 
#define BODCTRL_BODINTVAL_MASK         0x000C             // BOD interrupt level
#define BODCTRL_BODINTVAL_SHIFT        2                 
#define BODCTRL_BODRSTENA              (1 << 4)           // BOD reset enable

/* SYSTCKCAL, address 0x4004 8154 */
#define SYSTCKCAL_CAL_MASK             0x3FFFFFF          // System tick timer calibration value
#define SYSTCKCAL_CAL_SHIFT            0                 

/* NMISRC, address 0x4004 8174 */
#define NMISRC_IRQNO_MASK              0x001F             // The IRQ number of the interrupt that acts as the Non-Maskable Interrupt 0 (NMI) if bit 31 in this register is 1. See Table 54 for the list of interrupt sources and their IRQ numbers.
#define NMISRC_IRQNO_SHIFT             0                 
#define NMISRC_NMIEN                   (1 << 31)          // Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by bits 4:0.

/* STARTAPRP0, address 0x4004 8200 */
#define STARTAPRP0_APRPIO0_N_MASK      0x0FFF             // Edge select for start logic input PIO0_n: PIO0_11 to PIO0_0 0 = Falling edge 1 = Rising edge
#define STARTAPRP0_APRPIO0_N_SHIFT     0                 
#define STARTAPRP0_APRPIO1_0           (1 << 12)          // Edge select for start logic input PIO1_0 0 = Falling edge 1 = Rising edge Reserved. Do not write a 1 to reserved bits in this register.

/* STARTERP0, address 0x4004 8204 */
#define STARTERP0_ERPIO0_N_MASK        0x0FFF             // Enable start signal for start logic input PIO0_n: PIO0_11 to PIO0_0 0 = Disabled 1 = Enabled
#define STARTERP0_ERPIO0_N_SHIFT       0                 
#define STARTERP0_ERPIO1_0             (1 << 12)          // Enable start signal for start logic input PIO1_0 0 = Disabled 1 = Enabled Reserved. Do not write a 1 to reserved bits in this register.

/* STARTRSRP0CLR, address 0x4004 8208 */
#define STARTRSRP0CLR_RSRPIO0_N_MASK   0x0FFF             // Start signal reset for start logic input PIO0_n:PIO0_11 to PIO0_0 0 = Do nothing. 1 = Writing 1 resets the start signal.
#define STARTRSRP0CLR_RSRPIO0_N_SHIFT  0                 
#define STARTRSRP0CLR_RSRPIO1_0        (1 << 12)          // Start signal reset for start logic input PIO1_0 0 = Do nothing. 1 = Writing 1 resets the start signal.

/* STARTSRP0, address 0x4004 820C */
#define STARTSRP0_SRPIO0_N_MASK        0x0FFF             // Start signal status for start logic input PIO0_n: PIO0_11 to PIO0_0 0 = No start signal received. 1 = Start signal pending.
#define STARTSRP0_SRPIO0_N_SHIFT       0                 
#define STARTSRP0_SRPIO1_0             (1 << 12)          // Start signal status for start logic input PIO1_0 0 = No start signal received. 1 = Start signal pending.

/* PDSLEEPCFG, address 0x4004 8230 */
#define PDSLEEPCFG_BOD_PD              (1 << 3)           // BOD power-down control in Deep-sleep mode, see Table 40.
#define PDSLEEPCFG_WDTOSC_PD           (1 << 6)           // Watchdog oscillator power control in Deep-sleep mode, see Table 40.

/* PDAWAKECFG, address 0x4004 8234 */
#define PDAWAKECFG_IRCOUT_PD           (1 << 0)           // IRC oscillator output wake-up configuration
#define PDAWAKECFG_IRC_PD              (1 << 1)           // IRC oscillator power-down wake-up configuration
#define PDAWAKECFG_FLASH_PD            (1 << 2)           // Flash wake-up configuration
#define PDAWAKECFG_BOD_PD              (1 << 3)           // BOD wake-up configuration
#define PDAWAKECFG_ADC_PD              (1 << 4)           // ADC wake-up configuration
#define PDAWAKECFG_SYSOSC_PD           (1 << 5)           // System oscillator wake-up configuration
#define PDAWAKECFG_WDTOSC_PD           (1 << 6)           // Watchdog oscillator wake-up configuration
#define PDAWAKECFG_SYSPLL_PD           (1 << 7)           // System PLL wake-up configuration

/* PDRUNCFG, address 0x4004 8238 */
#define PDRUNCFG_IRCOUT_PD             (1 << 0)           // IRC oscillator output power-down
#define PDRUNCFG_IRC_PD                (1 << 1)           // IRC oscillator power-down
#define PDRUNCFG_FLASH_PD              (1 << 2)           // Flash power-down
#define PDRUNCFG_BOD_PD                (1 << 3)           // BOD power-down
#define PDRUNCFG_ADC_PD                (1 << 4)           // ADC power-down
#define PDRUNCFG_SYSOSC_PD             (1 << 5)           // System oscillator power-down
#define PDRUNCFG_WDTOSC_PD             (1 << 6)           // Watchdog oscillator power-down
#define PDRUNCFG_SYSPLL_PD             (1 << 7)           // System PLL power-down

/* DEVICE_ID, address 0x4004 83F4 */
#define DEVICE_ID_DEVICEID_MASK        0xFFFFFFFF         // Part ID numbers for LPC111x/LPC11Cxx parts
#define DEVICE_ID_DEVICEID_SHIFT       0                 

/* FLASHCFG, address 0x4003 C010 */
#define FLASHCFG_FLASHTIM_MASK         0x0003             // Flash memory access time. FLASHTIM +1 is equal to the number of system clocks used for flash access.
#define FLASHCFG_FLASHTIM_SHIFT        0                 

/* PCON, address 0x4003 8000 */
#define PCON_DPDEN                     (1 << 1)           // Deep power-down mode enable
#define PCON_SLEEPFLAG                 (1 << 8)           // Sleep mode flag
#define PCON_DPDFLAG                   (1 << 11)          // Deep power-down flag

/* GPREG0 - GPREG3, address 0x4003 8004 to 0x4003 8010 */
#define GPREGn_GPDATA_MASK             0xFFFFFFFF         // Data retained during Deep power-down mode.
#define GPREGn_GPDATA_SHIFT            0                 

/* GPREG4, address 0x4003 8014 */
#define GPREG4_WAKEUPHYS               (1 << 10)          // WAKEUP pin hysteresis enable
#define GPREG4_GPDATA_MASK             0xFFFFF800         // Data retained during Deep power-down mode.
#define GPREG4_GPDATA_SHIFT            11                

/* IOCON_PIO2_6, address 0x4004 4000 */
#define IOCON_PIO2_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_6_FUNC_SHIFT        0                 
#define IOCON_PIO2_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_6_MODE_SHIFT        3                 
#define IOCON_PIO2_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_6_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_0, address 0x4004 4008 */
#define IOCON_PIO2_0_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_0_FUNC_SHIFT        0                 
#define IOCON_PIO2_0_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_0_MODE_SHIFT        3                 
#define IOCON_PIO2_0_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_0_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_RESET_PIO0_0, address 0x4004 400C */
#define IOCON_RESET_PIO0_0_FUNC_MASK   0x0007             // Selects pin function. All other values are reserved.
#define IOCON_RESET_PIO0_0_FUNC_SHIFT  0                 
#define IOCON_RESET_PIO0_0_MODE_MASK   0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_RESET_PIO0_0_MODE_SHIFT  3                 
#define IOCON_RESET_PIO0_0_HYS         (1 << 5)           // Hysteresis.
#define IOCON_RESET_PIO0_0_OD          (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_1, address 0x4004 4010 */
#define IOCON_PIO0_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_1_FUNC_SHIFT        0                 
#define IOCON_PIO0_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_1_MODE_SHIFT        3                 
#define IOCON_PIO0_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_1_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO1_8, address 0x4004 4014 */
#define IOCON_PIO1_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_8_FUNC_SHIFT        0                 
#define IOCON_PIO1_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_8_MODE_SHIFT        3                 
#define IOCON_PIO1_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_8_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_2, address 0x4004 401C */
#define IOCON_PIO0_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_2_FUNC_SHIFT        0                 
#define IOCON_PIO0_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_2_MODE_SHIFT        3                 
#define IOCON_PIO0_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_2_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_7, address 0x4004 4020 */
#define IOCON_PIO2_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_7_FUNC_SHIFT        0                 
#define IOCON_PIO2_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_7_MODE_SHIFT        3                 
#define IOCON_PIO2_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_7_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_8, address 0x4004 4024 */
#define IOCON_PIO2_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_8_FUNC_SHIFT        0                 
#define IOCON_PIO2_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_8_MODE_SHIFT        3                 
#define IOCON_PIO2_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_8_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_1, address 0x4004 4028 */
#define IOCON_PIO2_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_1_FUNC_SHIFT        0                 
#define IOCON_PIO2_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_1_MODE_SHIFT        3                 
#define IOCON_PIO2_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_1_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_3, address 0x4004 402C */
#define IOCON_PIO0_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_3_FUNC_SHIFT        0                 
#define IOCON_PIO0_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_3_MODE_SHIFT        3                 
#define IOCON_PIO0_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_3_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_4, address 0x4004 4030 */
#define IOCON_PIO0_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_4_FUNC_SHIFT        0                 
#define IOCON_PIO0_4_I2CMODE_MASK      0x0300             // Selects I2C mode. Select Standard mode (I2CMODE = 00, 00 default) or Standard I/O functionality (I2CMODE = 01) if the pin function is GPIO (FUNC = 000).
#define IOCON_PIO0_4_I2CMODE_SHIFT     8                 

/* IOCON_PIO0_5, address 0x4004 4034 */
#define IOCON_PIO0_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_5_FUNC_SHIFT        0                 
#define IOCON_PIO0_5_I2CMODE_MASK      0x0300             // Selects I2C mode. Select Standard mode (I2CMODE = 00, default) or Standard I/O functionality (I2CMODE = 01) if the pin function is GPIO (FUNC = 000).
#define IOCON_PIO0_5_I2CMODE_SHIFT     8                 

/* IOCON_PIO1_9, address 0x4004 4038 */
#define IOCON_PIO1_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_9_FUNC_SHIFT        0                 
#define IOCON_PIO1_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_9_MODE_SHIFT        3                 
#define IOCON_PIO1_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_9_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO3_4, address 0x4004 403C */
#define IOCON_PIO3_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_4_FUNC_SHIFT        0                 
#define IOCON_PIO3_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_4_MODE_SHIFT        3                 
#define IOCON_PIO3_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_4_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_4, address 0x4004 4040 */
#define IOCON_PIO2_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_4_FUNC_SHIFT        0                 
#define IOCON_PIO2_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_4_MODE_SHIFT        3                 
#define IOCON_PIO2_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_4_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_5, address 0x4004 4044 */
#define IOCON_PIO2_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_5_FUNC_SHIFT        0                 
#define IOCON_PIO2_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_5_MODE_SHIFT        3                 
#define IOCON_PIO2_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_5_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_5, address 0x4004 4048 */
#define IOCON_PIO3_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_5_FUNC_SHIFT        0                 
#define IOCON_PIO3_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_5_MODE_SHIFT        3                 
#define IOCON_PIO3_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_5_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_6, address 0x4004 404C */
#define IOCON_PIO0_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_6_FUNC_SHIFT        0                 
#define IOCON_PIO0_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_6_MODE_SHIFT        3                 
#define IOCON_PIO0_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_6_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_7, address 0x4004 4050 */
#define IOCON_PIO0_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_7_FUNC_SHIFT        0                 
#define IOCON_PIO0_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_7_MODE_SHIFT        3                 
#define IOCON_PIO0_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_7_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_9, address 0x4004 4054 */
#define IOCON_PIO2_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_9_FUNC_SHIFT        0                 
#define IOCON_PIO2_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_9_MODE_SHIFT        3                 
#define IOCON_PIO2_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_9_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_10, address 0x4004 4058 */
#define IOCON_PIO2_10_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_10_FUNC_SHIFT       0                 
#define IOCON_PIO2_10_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_10_MODE_SHIFT       3                 
#define IOCON_PIO2_10_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO2_10_OD               (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_2, address 0x4004 405C */
#define IOCON_PIO2_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_2_FUNC_SHIFT        0                 
#define IOCON_PIO2_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_2_MODE_SHIFT        3                 
#define IOCON_PIO2_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_2_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_8, address 0x4004 4060 */
#define IOCON_PIO0_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_8_FUNC_SHIFT        0                 
#define IOCON_PIO0_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_8_MODE_SHIFT        3                 
#define IOCON_PIO0_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_8_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO0_9, address 0x4004 4064 */
#define IOCON_PIO0_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_9_FUNC_SHIFT        0                 
#define IOCON_PIO0_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_9_MODE_SHIFT        3                 
#define IOCON_PIO0_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_9_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_SWCLK_PIO0_10, address 0x4004 4068 */
#define IOCON_SWCLK_PIO0_10_FUNC_MASK  0x0007             // Selects pin function. All other values are reserved.
#define IOCON_SWCLK_PIO0_10_FUNC_SHIFT 0                 
#define IOCON_SWCLK_PIO0_10_MODE_MASK  0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_SWCLK_PIO0_10_MODE_SHIFT 3                 
#define IOCON_SWCLK_PIO0_10_HYS        (1 << 5)           // Hysteresis.
#define IOCON_SWCLK_PIO0_10_OD         (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_10, address 0x4004 406C */
#define IOCON_PIO1_10_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_10_FUNC_SHIFT       0                 
#define IOCON_PIO1_10_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_10_MODE_SHIFT       3                 
#define IOCON_PIO1_10_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO1_10_ADMODE           (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_10_OD               (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_11, address 0x4004 4070 */
#define IOCON_PIO2_11_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_11_FUNC_SHIFT       0                 
#define IOCON_PIO2_11_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_11_MODE_SHIFT       3                 
#define IOCON_PIO2_11_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO2_11_OD               (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_R_PIO0_11, address 0x4004 4074 */
#define IOCON_R_PIO0_11_FUNC_MASK      0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO0_11_FUNC_SHIFT     0                 
#define IOCON_R_PIO0_11_MODE_MASK      0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO0_11_MODE_SHIFT     3                 
#define IOCON_R_PIO0_11_HYS            (1 << 5)           // Hysteresis.
#define IOCON_R_PIO0_11_ADMODE         (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO0_11_OD             (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_R_PIO1_0, address 0x4004 4078 */
#define IOCON_R_PIO1_0_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_0_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_0_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_0_MODE_SHIFT      3                 
#define IOCON_R_PIO1_0_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_0_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_0_OD              (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_R_PIO1_1, address 0x4004 407C */
#define IOCON_R_PIO1_1_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_1_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_1_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_1_MODE_SHIFT      3                 
#define IOCON_R_PIO1_1_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_1_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_1_OD              (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_R_PIO1_2, address 0x4004 4080 */
#define IOCON_R_PIO1_2_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_2_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_2_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_2_MODE_SHIFT      3                 
#define IOCON_R_PIO1_2_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_2_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_2_OD              (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO3_0, address 0x4004 4084 */
#define IOCON_PIO3_0_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_0_FUNC_SHIFT        0                 
#define IOCON_PIO3_0_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_0_MODE_SHIFT        3                 
#define IOCON_PIO3_0_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_0_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_1, address 0x4004 4088 */
#define IOCON_PIO3_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_1_FUNC_SHIFT        0                 
#define IOCON_PIO3_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_1_MODE_SHIFT        3                 
#define IOCON_PIO3_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_1_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO2_3, address 0x4004 408C */
#define IOCON_PIO2_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_3_FUNC_SHIFT        0                 
#define IOCON_PIO2_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_3_MODE_SHIFT        3                 
#define IOCON_PIO2_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_3_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_SWDIO_PIO1_3, address 0x4004 4090 */
#define IOCON_SWDIO_PIO1_3_FUNC_MASK   0x0007             // Selects pin function. All other values are reserved.
#define IOCON_SWDIO_PIO1_3_FUNC_SHIFT  0                 
#define IOCON_SWDIO_PIO1_3_MODE_MASK   0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_SWDIO_PIO1_3_MODE_SHIFT  3                 
#define IOCON_SWDIO_PIO1_3_HYS         (1 << 5)           // Hysteresis.
#define IOCON_SWDIO_PIO1_3_ADMODE      (1 << 7)           // Selects Analog/Digital mode
#define IOCON_SWDIO_PIO1_3_OD          (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_4, address 0x4004 4094 */
#define IOCON_PIO1_4_FUNC_MASK         0x0007             // Selects pin function. This pin functions as WAKEUP pin if the 000 LPC111x/LPC11Cxx is in Deep power-down mode regardless of the value of FUNC. All other values are reserved.
#define IOCON_PIO1_4_FUNC_SHIFT        0                 
#define IOCON_PIO1_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_4_MODE_SHIFT        3                 
#define IOCON_PIO1_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_4_ADMODE            (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_4_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO1_11, address 0x4004 4098 */
#define IOCON_PIO1_11_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_11_FUNC_SHIFT       0                 
#define IOCON_PIO1_11_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_11_MODE_SHIFT       3                 
#define IOCON_PIO1_11_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO1_11_ADMODE           (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_11_OD               (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO3_2, address 0x4004 409C */
#define IOCON_PIO3_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_2_FUNC_SHIFT        0                 
#define IOCON_PIO3_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_2_MODE_SHIFT        3                 
#define IOCON_PIO3_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_2_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_5, address 0x4004 40A0 */
#define IOCON_PIO1_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_5_FUNC_SHIFT        0                 
#define IOCON_PIO1_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_5_MODE_SHIFT        3                 
#define IOCON_PIO1_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_5_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO1_6, address 0x4004 40A4 */
#define IOCON_PIO1_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_6_FUNC_SHIFT        0                 
#define IOCON_PIO1_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_6_MODE_SHIFT        3                 
#define IOCON_PIO1_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_6_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO1_7, address 0x4004 40A8 */
#define IOCON_PIO1_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_7_FUNC_SHIFT        0                 
#define IOCON_PIO1_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_7_MODE_SHIFT        3                 
#define IOCON_PIO1_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_7_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_PIO3_3, address 0x4004 40AC */
#define IOCON_PIO3_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_3_FUNC_SHIFT        0                 
#define IOCON_PIO3_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_3_MODE_SHIFT        3                 
#define IOCON_PIO3_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_3_OD                (1 << 10)          // Selects pseudo open-drain mode. See Section 7.1 for part specific details.

/* IOCON_SCK_LOC, address 0x4004 40B0 */
#define IOCON_SCK_LOC_SCKLOC_MASK      0x0003             // Selects pin location for SCK0 function.
#define IOCON_SCK_LOC_SCKLOC_SHIFT     0                 

/* IOCON_DSR_LOC, address 0x4004 40B4 */
#define IOCON_DSR_LOC_DSRLOC_MASK      0x0003             // elects pin location for DSR function.
#define IOCON_DSR_LOC_DSRLOC_SHIFT     0                 

/* IOCON_DCD_LOC, address 0x4004 40B8 */
#define IOCON_DCD_LOC_DCDLOC_MASK      0x0003             // Selects pin location for DCD function.
#define IOCON_DCD_LOC_DCDLOC_SHIFT     0                 

/* IOCON_RI_LOC, address 0x4004 40BC */
#define IOCON_RI_LOC_RILOC_MASK        0x0003             // Selects pin location for RI function.
#define IOCON_RI_LOC_RILOC_SHIFT       0                 

/* IOCON_PIO2_6, address 0x4004 4000 */
#define IOCON_PIO2_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_6_FUNC_SHIFT        0                 
#define IOCON_PIO2_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_6_MODE_SHIFT        3                 
#define IOCON_PIO2_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_6_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_0, address 0x4004 4008 */
#define IOCON_PIO2_0_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_0_FUNC_SHIFT        0                 
#define IOCON_PIO2_0_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_0_MODE_SHIFT        3                 
#define IOCON_PIO2_0_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_0_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_RESET_PIO0_0, address 0x4004 400C */
#define IOCON_RESET_PIO0_0_FUNC_MASK   0x0007             // Selects pin function. All other values are reserved.
#define IOCON_RESET_PIO0_0_FUNC_SHIFT  0                 
#define IOCON_RESET_PIO0_0_MODE_MASK   0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_RESET_PIO0_0_MODE_SHIFT  3                 
#define IOCON_RESET_PIO0_0_HYS         (1 << 5)           // Hysteresis.
#define IOCON_RESET_PIO0_0_OD          (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_1, address 0x4004 4010 */
#define IOCON_PIO0_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_1_FUNC_SHIFT        0                 
#define IOCON_PIO0_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_1_MODE_SHIFT        3                 
#define IOCON_PIO0_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_1_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_8, address 0x4004 4014 */
#define IOCON_PIO1_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_8_FUNC_SHIFT        0                 
#define IOCON_PIO1_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_8_MODE_SHIFT        3                 
#define IOCON_PIO1_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_8_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_2, address 0x4004 401C */
#define IOCON_PIO0_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_2_FUNC_SHIFT        0                 
#define IOCON_PIO0_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_2_MODE_SHIFT        3                 
#define IOCON_PIO0_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_2_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_7, address 0x4004 4020 */
#define IOCON_PIO2_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_7_FUNC_SHIFT        0                 
#define IOCON_PIO2_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_7_MODE_SHIFT        3                 
#define IOCON_PIO2_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_7_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_8, address 0x4004 4024 */
#define IOCON_PIO2_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_8_FUNC_SHIFT        0                 
#define IOCON_PIO2_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_8_MODE_SHIFT        3                 
#define IOCON_PIO2_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_8_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_1, address 0x4004 4028 */
#define IOCON_PIO2_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_1_FUNC_SHIFT        0                 
#define IOCON_PIO2_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_1_MODE_SHIFT        3                 
#define IOCON_PIO2_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_1_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_3, address 0x4004 402C */
#define IOCON_PIO0_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_3_FUNC_SHIFT        0                 
#define IOCON_PIO0_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_3_MODE_SHIFT        3                 
#define IOCON_PIO0_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_3_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_4, address 0x4004 4030 */
#define IOCON_PIO0_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_4_FUNC_SHIFT        0                 
#define IOCON_PIO0_4_I2CMODE_MASK      0x0300             // Selects I2C mode. Select Standard mode (I2CMODE = 00, 00 default) or Standard I/O functionality (I2CMODE = 01) if the pin function is GPIO (FUNC = 000).
#define IOCON_PIO0_4_I2CMODE_SHIFT     8                 

/* IOCON_PIO0_5, address 0x4004 4034 */
#define IOCON_PIO0_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_5_FUNC_SHIFT        0                 
#define IOCON_PIO0_5_I2CMODE_MASK      0x0300             // Selects I2C mode. Select Standard mode (I2CMODE = 00, default) or Standard I/O functionality (I2CMODE = 01) if the pin function is GPIO (FUNC = 000).
#define IOCON_PIO0_5_I2CMODE_SHIFT     8                 

/* IOCON_PIO1_9, address 0x4004 4038 */
#define IOCON_PIO1_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_9_FUNC_SHIFT        0                 
#define IOCON_PIO1_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_9_MODE_SHIFT        3                 
#define IOCON_PIO1_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_9_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_4, address 0x4004 403C */
#define IOCON_PIO3_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_4_FUNC_SHIFT        0                 
#define IOCON_PIO3_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_4_MODE_SHIFT        3                 
#define IOCON_PIO3_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_4_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_4, address 0x4004 4040 */
#define IOCON_PIO2_4_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_4_FUNC_SHIFT        0                 
#define IOCON_PIO2_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_4_MODE_SHIFT        3                 
#define IOCON_PIO2_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_4_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_5, address 0x4004 4044 */
#define IOCON_PIO2_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_5_FUNC_SHIFT        0                 
#define IOCON_PIO2_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_5_MODE_SHIFT        3                 
#define IOCON_PIO2_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_5_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_5, address 0x4004 4048 */
#define IOCON_PIO3_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_5_FUNC_SHIFT        0                 
#define IOCON_PIO3_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_5_MODE_SHIFT        3                 
#define IOCON_PIO3_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_5_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_6, address 0x4004 404C */
#define IOCON_PIO0_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_6_FUNC_SHIFT        0                 
#define IOCON_PIO0_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_6_MODE_SHIFT        3                 
#define IOCON_PIO0_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_6_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_7, address 0x4004 4050 */
#define IOCON_PIO0_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_7_FUNC_SHIFT        0                 
#define IOCON_PIO0_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_7_MODE_SHIFT        3                 
#define IOCON_PIO0_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_7_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_9, address 0x4004 4054 */
#define IOCON_PIO2_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_9_FUNC_SHIFT        0                 
#define IOCON_PIO2_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_9_MODE_SHIFT        3                 
#define IOCON_PIO2_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_9_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_10, address 0x4004 4058 */
#define IOCON_PIO2_10_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_10_FUNC_SHIFT       0                 
#define IOCON_PIO2_10_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_10_MODE_SHIFT       3                 
#define IOCON_PIO2_10_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO2_10_OD               (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_2, address 0x4004 405C */
#define IOCON_PIO2_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_2_FUNC_SHIFT        0                 
#define IOCON_PIO2_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_2_MODE_SHIFT        3                 
#define IOCON_PIO2_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_2_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_8, address 0x4004 4060 */
#define IOCON_PIO0_8_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_8_FUNC_SHIFT        0                 
#define IOCON_PIO0_8_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_8_MODE_SHIFT        3                 
#define IOCON_PIO0_8_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_8_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO0_9, address 0x4004 4064 */
#define IOCON_PIO0_9_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO0_9_FUNC_SHIFT        0                 
#define IOCON_PIO0_9_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO0_9_MODE_SHIFT        3                 
#define IOCON_PIO0_9_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO0_9_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_SWCLK_PIO0_10, address 0x4004 4068 */
#define IOCON_SWCLK_PIO0_10_FUNC_MASK  0x0007             // Selects pin function. All other values are reserved.
#define IOCON_SWCLK_PIO0_10_FUNC_SHIFT 0                 
#define IOCON_SWCLK_PIO0_10_MODE_MASK  0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_SWCLK_PIO0_10_MODE_SHIFT 3                 
#define IOCON_SWCLK_PIO0_10_HYS        (1 << 5)           // Hysteresis.
#define IOCON_SWCLK_PIO0_10_OD         (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_10, address 0x4004 406C */
#define IOCON_PIO1_10_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_10_FUNC_SHIFT       0                 
#define IOCON_PIO1_10_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_10_MODE_SHIFT       3                 
#define IOCON_PIO1_10_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO1_10_ADMODE           (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_10_OD               (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_11, address 0x4004 4070 */
#define IOCON_PIO2_11_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_11_FUNC_SHIFT       0                 
#define IOCON_PIO2_11_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_11_MODE_SHIFT       3                 
#define IOCON_PIO2_11_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO2_11_OD               (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_R_PIO0_11, address 0x4004 4074 */
#define IOCON_R_PIO0_11_FUNC_MASK      0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO0_11_FUNC_SHIFT     0                 
#define IOCON_R_PIO0_11_MODE_MASK      0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO0_11_MODE_SHIFT     3                 
#define IOCON_R_PIO0_11_HYS            (1 << 5)           // Hysteresis.
#define IOCON_R_PIO0_11_ADMODE         (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO0_11_OD             (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_R_PIO1_0, address 0x4004 4078 */
#define IOCON_R_PIO1_0_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_0_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_0_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_0_MODE_SHIFT      3                 
#define IOCON_R_PIO1_0_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_0_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_0_OD              (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_R_PIO1_1, address 0x4004 407C */
#define IOCON_R_PIO1_1_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_1_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_1_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_1_MODE_SHIFT      3                 
#define IOCON_R_PIO1_1_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_1_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_1_OD              (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_R_PIO1_2, address 0x4004 4080 */
#define IOCON_R_PIO1_2_FUNC_MASK       0x0007             // Selects pin function. All other values are reserved.
#define IOCON_R_PIO1_2_FUNC_SHIFT      0                 
#define IOCON_R_PIO1_2_MODE_MASK       0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_R_PIO1_2_MODE_SHIFT      3                 
#define IOCON_R_PIO1_2_HYS             (1 << 5)           // Hysteresis.
#define IOCON_R_PIO1_2_ADMODE          (1 << 7)           // Selects Analog/Digital mode
#define IOCON_R_PIO1_2_OD              (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_0, address 0x4004 4084 */
#define IOCON_PIO3_0_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_0_FUNC_SHIFT        0                 
#define IOCON_PIO3_0_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_0_MODE_SHIFT        3                 
#define IOCON_PIO3_0_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_0_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_1, address 0x4004 4088 */
#define IOCON_PIO3_1_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_1_FUNC_SHIFT        0                 
#define IOCON_PIO3_1_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_1_MODE_SHIFT        3                 
#define IOCON_PIO3_1_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_1_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO2_3, address 0x4004 408C */
#define IOCON_PIO2_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO2_3_FUNC_SHIFT        0                 
#define IOCON_PIO2_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO2_3_MODE_SHIFT        3                 
#define IOCON_PIO2_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO2_3_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_SWDIO_PIO1_3, address 0x4004 4090 */
#define IOCON_SWDIO_PIO1_3_FUNC_MASK   0x0007             // Selects pin function. All other values are reserved.
#define IOCON_SWDIO_PIO1_3_FUNC_SHIFT  0                 
#define IOCON_SWDIO_PIO1_3_MODE_MASK   0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_SWDIO_PIO1_3_MODE_SHIFT  3                 
#define IOCON_SWDIO_PIO1_3_HYS         (1 << 5)           // Hysteresis.
#define IOCON_SWDIO_PIO1_3_ADMODE      (1 << 7)           // Selects Analog/Digital mode
#define IOCON_SWDIO_PIO1_3_OD          (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_4, address 0x4004 4094 */
#define IOCON_PIO1_4_FUNC_MASK         0x0007             // Selects pin function. This pin functions as WAKEUP pin if the 000 LPC111x/LPC11Cxx is in Deep power-down mode regardless of the value of FUNC. All other values are reserved.
#define IOCON_PIO1_4_FUNC_SHIFT        0                 
#define IOCON_PIO1_4_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_4_MODE_SHIFT        3                 
#define IOCON_PIO1_4_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_4_ADMODE            (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_4_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_11, address 0x4004 4098 */
#define IOCON_PIO1_11_FUNC_MASK        0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_11_FUNC_SHIFT       0                 
#define IOCON_PIO1_11_MODE_MASK        0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_11_MODE_SHIFT       3                 
#define IOCON_PIO1_11_HYS              (1 << 5)           // Hysteresis.
#define IOCON_PIO1_11_ADMODE           (1 << 7)           // Selects Analog/Digital mode
#define IOCON_PIO1_11_OD               (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_2, address 0x4004 409C */
#define IOCON_PIO3_2_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_2_FUNC_SHIFT        0                 
#define IOCON_PIO3_2_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_2_MODE_SHIFT        3                 
#define IOCON_PIO3_2_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_2_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_5, address 0x4004 40A0 */
#define IOCON_PIO1_5_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_5_FUNC_SHIFT        0                 
#define IOCON_PIO1_5_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_5_MODE_SHIFT        3                 
#define IOCON_PIO1_5_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_5_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_6, address 0x4004 40A4 */
#define IOCON_PIO1_6_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_6_FUNC_SHIFT        0                 
#define IOCON_PIO1_6_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_6_MODE_SHIFT        3                 
#define IOCON_PIO1_6_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_6_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO1_7, address 0x4004 40A8 */
#define IOCON_PIO1_7_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO1_7_FUNC_SHIFT        0                 
#define IOCON_PIO1_7_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO1_7_MODE_SHIFT        3                 
#define IOCON_PIO1_7_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO1_7_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_PIO3_3, address 0x4004 40AC */
#define IOCON_PIO3_3_FUNC_MASK         0x0007             // Selects pin function. All other values are reserved.
#define IOCON_PIO3_3_FUNC_SHIFT        0                 
#define IOCON_PIO3_3_MODE_MASK         0x0018             // Selects function mode (on-chip pull-up/pull-down resistor control).
#define IOCON_PIO3_3_MODE_SHIFT        3                 
#define IOCON_PIO3_3_HYS               (1 << 5)           // Hysteresis.
#define IOCON_PIO3_3_OD                (1 << 10)          // Selects pseudo open-drain mode.

/* IOCON_SCK0_LOC, address 0x4004 40B0 */
#define IOCON_SCK0_LOC_SCKLOC_MASK     0x0003             // Selects pin location for SCK0 function.
#define IOCON_SCK0_LOC_SCKLOC_SHIFT    0                 

/* IOCON_DSR_LOC, address 0x4004 40B4 */
#define IOCON_DSR_LOC_DSRLOC_MASK      0x0003             // elects pin location for DSR function.
#define IOCON_DSR_LOC_DSRLOC_SHIFT     0                 

/* IOCON_DCD_LOC, address 0x4004 40B8 */
#define IOCON_DCD_LOC_DCDLOC_MASK      0x0003             // Selects pin location for DCD function.
#define IOCON_DCD_LOC_DCDLOC_SHIFT     0                 

/* IOCON_RI_LOC, address 0x4004 40BC */
#define IOCON_RI_LOC_RILOC_MASK        0x0003             // Selects pin location for RI function.
#define IOCON_RI_LOC_RILOC_SHIFT       0                 

/* IOCON_SSEL1_LOC, address 0x4004 4018 */
#define IOCON_SSEL1_LOC_SSEL1LOC_MASK  0x0003             // Selects pin location for SSEL1 function.
#define IOCON_SSEL1_LOC_SSEL1LOC_SHIFT 0                 

/* IOCON_CT16B0_CAP0_LOC, address 0x4004 40C0 */
#define IOCON_CT16B0_CAP0_LOC_CT16B0_CAP0LOC_MASK 0x0003             // Selects pin location for CT16B0_CAP0 function.
#define IOCON_CT16B0_CAP0_LOC_CT16B0_CAP0LOC_SHIFT 0                 

/* IOCON_SCK1_LOC, address 0x4004 40C4 */
#define IOCON_SCK1_LOC_SCK1LOC_MASK    0x0003             // Selects pin location for SCK1 function.
#define IOCON_SCK1_LOC_SCK1LOC_SHIFT   0                 

/* IOCON_MISO1_LOC, address 0x4004 40C8 */
#define IOCON_MISO1_LOC_MISO1LOC_MASK  0x0003             // Selects pin location for the MISO1 function.
#define IOCON_MISO1_LOC_MISO1LOC_SHIFT 0                 

/* IOCON_MOSI1_LOC, address 0x4004 40CC */
#define IOCON_MOSI1_LOC_MOSI1LOC_MASK  0x0003             // Selects pin location for the MOSI1 function.
#define IOCON_MOSI1_LOC_MOSI1LOC_SHIFT 0                 

/* IOCON_CT32B0_CAP0_LOC, address 0x4004 40D0 */
#define IOCON_CT32B0_CAP0_LOC_CT32B0_CAP0LOC_MASK 0x0003             // Selects pin location for the CT32B0_CAP0 function.
#define IOCON_CT32B0_CAP0_LOC_CT32B0_CAP0LOC_SHIFT 0                 

/* IOCON_RXD_LOC, address 0x4004 40D4 */
#define IOCON_RXD_LOC_RXDLOC_MASK      0x0003             // Selects pin location for the RXD function.
#define IOCON_RXD_LOC_RXDLOC_SHIFT     0                 

/* GPIO0DIR, address 0x5000 8000 to GPIO3DIR, address 0x5003 8000 */
#define GPIO0DIR_IO_MASK               0x0FFF             // Selects pin x as input or output (x = 0 to 11). 0 = Pin PIOn_x is configured as input. 1 = Pin PIOn_x is configured as output.
#define GPIO0DIR_IO_SHIFT              0                 

/* GPIO0IS, address 0x5000 8004 to GPIO3IS, address 0x5003 8004 */
#define GPIO0IS_ISENSE_MASK            0x0FFF             // Selects interrupt on pin x as level or edge sensitive (x = 0 to 0x00 11). 0 = Interrupt on pin PIOn_x is configured as edge sensitive. 1 = Interrupt on pin PIOn_x is configured as level sensitive.
#define GPIO0IS_ISENSE_SHIFT           0                 

/* GPIO0IBE, address 0x5000 8008 to GPIO3IBE, address 0x5003 8008 */
#define GPIO0IBE_IBE_MASK              0x0FFF             // Selects interrupt on pin x to be triggered on both edges (x = 0 0x00 to 11). 0 = Interrupt on pin PIOn_x is controlled through register GPIOnIEV. 1 = Both edges on pin PIOn_x trigger an interrupt.
#define GPIO0IBE_IBE_SHIFT             0                 

/* GPIO0IEV, address 0x5000 800C to GPIO3IEV, address 0x5003 800C */
#define GPIO0IEV_IEV_MASK              0x0FFF             // Selects interrupt on pin x to be triggered rising or falling edges (x = 0 to 11). 0 = Depending on setting in register GPIOnIS (see Table 175), falling edges or LOW level on pin PIOn_x trigger an interrupt. 1 = Depending on setting in register GPIOnIS (see Table 175), rising edges or HIGH level on pin PIOn_x trigger an interrupt.
#define GPIO0IEV_IEV_SHIFT             0                 

/* GPIO0IE, address 0x5000 8010 to GPIO3IE, address 0x5003 8010 */
#define GPIO0IE_MASK_MASK              0x0FFF             // Selects interrupt on pin x to be masked (x = 0 to 11). 0 = Interrupt on pin PIOn_x is masked. 1 = Interrupt on pin PIOn_x is not masked.
#define GPIO0IE_MASK_SHIFT             0                 

/* GPIO0RIS, address 0x5000 8014 to GPIO3RIS, address 0x5003 8014 */
#define GPIO0RIS_RAWST_MASK            0x0FFF             // Raw interrupt status (x = 0 to 11). 0 = No interrupt on pin PIOn_x. 1 = Interrupt requirements met on PIOn_x.
#define GPIO0RIS_RAWST_SHIFT           0                 

/* GPIO0MIS, address 0x5000 8018 to GPIO3MIS, address 0x5003 8018 */
#define GPIO0MIS_MASK_MASK             0x0FFF             // Selects interrupt on pin x to be masked (x = 0 to 11). 0 = No interrupt or interrupt masked on pin PIOn_x. 1 = Interrupt on PIOn_x.
#define GPIO0MIS_MASK_SHIFT            0                 

/* GPIO0IC, address 0x5000 801C to GPIO3IC, address 0x5003 801C */
#define GPIO0IC_CLR_MASK               0x0FFF             // Selects interrupt on pin x to be cleared (x = 0 to 11). Clears 0x00 the interrupt edge detection logic. This register is write-only. Remark: The synchronizer between the GPIO and the NVIC blocks causes a delay of 2 clocks. It is recommended to add two NOPs after the clear of the interrupt edge detection logic before the exit of the interrupt service routine. 0 = No effect. 1 = Clears edge detection logic for pin PIOn_x.
#define GPIO0IC_CLR_SHIFT              0                 

/* U0IIR - address 0x4004 8008, Read Only */
#define U0IIR_INTSTATUS                (1 << 0)           // Interrupt status. Note that U0IIR[0] is active low. The pending interrupt can be determined by evaluating U0IIR[3:1].
#define U0IIR_INTID_MASK               0x000E             // Interrupt identification. U0IER[3:1] identifies an interrupt 0 corresponding to the UART Rx FIFO. All other combinations of U0IER[3:1] not listed below are reserved (100,101,111).
#define U0IIR_INTID_SHIFT              1                 
#define U0IIR_FIFOENABLE_MASK          0x00C0             // These bits are equivalent to U0FCR[0].
#define U0IIR_FIFOENABLE_SHIFT         6                 
#define U0IIR_ABEOINT                  (1 << 8)           // End of auto-baud interrupt. True if auto-baud has finished successfully and interrupt is enabled.
#define U0IIR_ABTOINT                  (1 << 9)           // Auto-baud time-out interrupt. True if auto-baud has timed out and interrupt is enabled. Reserved, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.

/* U0FCR - address 0x4000 8008, Write Only */
#define U0FCR_FIFOEN                   (1 << 0)           // FIFO Enable
#define U0FCR_RXFIFORES                (1 << 1)           // RX FIFO Reset
#define U0FCR_TXFIFORES                (1 << 2)           // TX FIFO Reset
#define U0FCR_RXTL_MASK                0x00C0             // RX Trigger Level. These two bits determine how many     0 receiver UART FIFO characters must be written before an interrupt is activated.
#define U0FCR_RXTL_SHIFT               6                 

/* U0LCR - address 0x4000 800C */
#define U0LCR_WLS_MASK                 0x0003             // Word Length Select
#define U0LCR_WLS_SHIFT                0                 
#define U0LCR_SBS                      (1 << 2)           // Stop Bit Select
#define U0LCR_PE                       (1 << 3)           // Parity Enable
#define U0LCR_PS_MASK                  0x0030             // Parity Select 0x0         Odd parity. Number of 1s in the transmitted character and the attached parity bit will be odd. 0x1         Even Parity. Number of 1s in the transmitted character and the attached parity bit will be even. 0x2         Forced 1 stick parity. 0x3         Forced 0 stick parity.
#define U0LCR_PS_SHIFT                 4                 
#define U0LCR_BC                       (1 << 6)           // Break Control
#define U0LCR_DLAB                     (1 << 7)           // Divisor Latch Access Bit

/* U0MCR - address 0x4000 8010 */
#define U0MCR_DTRC                     (1 << 0)           // DTR Control. Source for modem output pin, DTR. This bit reads as 0 when modem loopback mode is active.
#define U0MCR_RTSC                     (1 << 1)           // RTS Control. Source for modem output pin RTS. This bit reads as 0 0 when modem loopback mode is active.
#define U0MCR_LMS                      (1 << 4)           // Loopback Mode Select. The modem loopback mode provides a 0 mechanism to perform diagnostic loopback testing. Serial data from the transmitter is connected internally to serial input of the receiver. Input pin, RXD, has no effect on loopback and output pin, TXD is held in marking state. The four modem inputs (CTS, DSR, RI and DCD) are disconnected externally. Externally, the modem outputs (RTS, DTR) are set inactive. Internally, the four modem outputs are connected to the four modem inputs. As a result of these connections, the upper four bits of the U0MSR will be driven by the lower four bits of the U0MCR rather than the four modem inputs in normal mode. This permits modem status interrupts to be generated in loopback mode by writing the lower four bits of U0MCR.
#define U0MCR_RTSEN                    (1 << 6)           // RTS flow control
#define U0MCR_CTSEN                    (1 << 7)           // CTS flow control

/* U0LSR - address 0x4000 8014, Read Only */
#define U0LSR_RDR                      (1 << 0)           // Receiver Data Ready. U0LSR[0] is set when the U0RBR holds 0 an unread character and is cleared when the UART RBR FIFO is empty.
#define U0LSR_OE                       (1 << 1)           // Overrun Error. The overrun error condition is set as soon as it 0 occurs. A U0LSR read clears U0LSR[1]. U0LSR[1] is set when UART RSR has a new character assembled and the UART RBR FIFO is full. In this case, the UART RBR FIFO will not be overwritten and the character in the UART RSR will be lost.
#define U0LSR_PE                       (1 << 2)           // Parity Error. When the parity bit of a received character is in the wrong state, a parity error occurs. A U0LSR read clears U0LSR[2]. Time of parity error detection is dependent on U0FCR[0]. Note: A parity error is associated with the character at the top of the UART RBR FIFO.
#define U0LSR_FE                       (1 << 3)           // Framing Error. When the stop bit of a received character is a 0 logic 0, a framing error occurs. A U0LSR read clears U0LSR[3]. The time of the framing error detection is dependent on U0FCR0. Upon detection of a framing error, the RX will attempt to re-synchronize to the data and assume that the bad stop bit is actually an early start bit. However, it cannot be assumed that the next received byte will be correct even if there is no Framing Error. Note: A framing error is associated with the character at the top of the UART RBR FIFO.
#define U0LSR_BI                       (1 << 4)           // Break Interrupt. When RXD1 is held in the spacing state (all zeros) for one full character transmission (start, data, parity, stop), a break interrupt occurs. Once the break condition has been detected, the receiver goes idle until RXD1 goes to marking state (all ones). A U0LSR read clears this status bit. The time of break detection is dependent on U0FCR[0]. Note: The break interrupt is associated with the character at the top of the UART RBR FIFO.
#define U0LSR_THRE                     (1 << 5)           // Transmitter Holding Register Empty. THRE is set immediately 1 upon detection of an empty UART THR and is cleared on a U0THR write.
#define U0LSR_TEMT                     (1 << 6)           // Transmitter Empty. TEMT is set when both U0THR and            1 U0TSR are empty; TEMT is cleared when either the U0TSR or the U0THR contain valid data. This bit is updated as soon as 50 % of the first stop bit has been transmitted or a byte has been written into the THR.
#define U0LSR_RXFE                     (1 << 7)           // Error in RX FIFO. U0LSR[7] is set when a character with a RX 0 error such as framing error, parity error or break interrupt, is loaded into the U0RBR. This bit is cleared when the U0LSR register is read and there are no subsequent errors in the UART FIFO.

/* U0MSR - address 0x4000 8018 */
#define U0MSR_DCTS                     (1 << 0)           // Delta CTS. Set upon state change of input CTS. Cleared on a U0MSR read. 0         No change detected on modem input CTS. 1         State change detected on modem input CTS.
#define U0MSR_DDSR                     (1 << 1)           // Delta DSR. Set upon state change of input DSR. Cleared on a U0MSR read. 0         No change detected on modem input DSR. 1         State change detected on modem input DSR.
#define U0MSR_TERI                     (1 << 2)           // Trailing Edge RI. Set upon low to high transition of input RI. Cleared 0 on a U0MSR read. 0         No change detected on modem input, RI. 1         Low-to-high transition detected on RI.
#define U0MSR_DDCD                     (1 << 3)           // Delta DCD. Set upon state change of input DCD. Cleared on a U0MSR read. 0         No change detected on modem input DCD. 1         State change detected on modem input DCD.
#define U0MSR_CTS                      (1 << 4)           // Clear To Send State. Complement of input signal CTS. This bit is connected to U0MCR[1] in modem loopback mode.
#define U0MSR_DSR                      (1 << 5)           // Data Set Ready State. Complement of input signal DSR. This bit is connected to U0MCR[0] in modem loopback mode.
#define U0MSR_RI                       (1 << 6)           // Ring Indicator State. Complement of input RI. This bit is connected to U0MCR[2] in modem loopback mode.
#define U0MSR_DCD                      (1 << 7)           // Data Carrier Detect State. Complement of input DCD. This bit is connected to U0MCR[3] in modem loopback mode.

/* U0SCR - address 0x4000 801C */
#define U0SCR_PAD_MASK                 0x00FF             // A readable, writable byte.
#define U0SCR_PAD_SHIFT                0                 

/* U0ACR - address 0x4000 8020 */
#define U0ACR_START                    (1 << 0)           // Start bit. This bit is automatically cleared after auto-baud completion.
#define U0ACR_MODE                     (1 << 1)           // Auto-baud mode select
#define U0ACR_AUTORESTART              (1 << 2)           // Restart enable
#define U0ACR_ABEOINTCLR               (1 << 8)           // End of auto-baud interrupt clear (write only accessible)
#define U0ACR_ABTOINTCLR               (1 << 9)           // Auto-baud time-out interrupt clear (write only accessible)

/* U0TER - address 0x4000 8030 */
#define U0TER_TXEN                     (1 << 7)           // When this bit is 1, as it is after a Reset, data written to the THR 1 is output on the TXD pin as soon as any preceding data has been sent. If this bit cleared to 0 while a character is being sent, the transmission of that character is completed, but no further characters are sent until this bit is set again. In other words, a 0 in this bit blocks the transfer of characters from the THR or TX FIFO into the transmit shift register. Software can clear this bit when it detects that the a hardware-handshaking TX-permit signal (CTS) has gone false, or with software handshaking, when it receives an XOFF character (DC3). Software can set this bit again when it detects that the TX-permit signal has gone true, or when it receives an XON (DC1) character. Reserved

/* U0RS485CTRL - address 0x4000 804C */
#define U0RS485CTRL_NMMEN              (1 << 0)           // NMM enable.
#define U0RS485CTRL_RXDIS              (1 << 1)           // Receiver enable.
#define U0RS485CTRL_AADEN              (1 << 2)           // AAD enable.
#define U0RS485CTRL_SEL                (1 << 3)           // Select direction control pin
#define U0RS485CTRL_DCTRL              (1 << 4)           // Auto direction control enable.
#define U0RS485CTRL_OINV               (1 << 5)           // Polarity control. This bit reverses the polarity of the direction control signal on the RTS (or DTR) pin.

/* U0RS485ADRMATCH - address 0x4000 8050 */
#define U0RS485ADRMATCH_ADRMATCH_MASK  0x00FF             // Contains the address match value.                                        0
#define U0RS485ADRMATCH_ADRMATCH_SHIFT 0                 

/* U0RS485DLY - address 0x4000 8054 */
#define U0RS485DLY_DLY_MASK            0x00FF             // Contains the direction control (RTS or DTR) delay value. This register works in conjunction with an 8-bit counter.
#define U0RS485DLY_DLY_SHIFT           0                 

/* SSP0CR0 - address 0x4004 0000, SSP1CR0 - address 0x4005 8000 */
#define SSP0CR0_DSS_MASK               0x000F             // Data Size Select. This field controls the number of bits transferred in each frame. Values 0000-0010 are not supported and should not be used.
#define SSP0CR0_DSS_SHIFT              0                 
#define SSP0CR0_FRF_MASK               0x0030             // Frame Format.
#define SSP0CR0_FRF_SHIFT              4                 
#define SSP0CR0_CPOL                   (1 << 6)           // Clock Out Polarity. This bit is only used in SPI mode.
#define SSP0CR0_CPHA                   (1 << 7)           // Clock Out Phase. This bit is only used in SPI mode.
#define SSP0CR0_SCR_MASK               0xFF00             // Serial Clock Rate. The number of prescaler output clocks per 0x00 bit on the bus, minus one. Given that CPSDVSR is the prescale divider, and the APB clock PCLK clocks the prescaler, the bit frequency is PCLK / (CPSDVSR  [SCR+1]). Reserved
#define SSP0CR0_SCR_SHIFT              8                 

/* SSP0CR1 - address 0x4004 0004, SSP1CR1 - address 0x4005 8004 */
#define SSP0CR1_LBM                    (1 << 0)           // Loop Back Mode.
#define SSP0CR1_SSE                    (1 << 1)           // SPI Enable.
#define SSP0CR1_MS                     (1 << 2)           // Master/Slave Mode.This bit can only be written when the SSE bit is 0.
#define SSP0CR1_SOD                    (1 << 3)           // Slave Output Disable. This bit is relevant only in slave        0 mode (MS = 1). If it is 1, this blocks this SPI controller from driving the transmit data line (MISO).

/* SSP0DR - address 0x4004 0008, SSP1DR - address 0x4005 8008 */
#define SSP0DR_DATA_MASK               0xFFFF             // Write: software can write data to be sent in a future frame to this 0x0000 register whenever the TNF bit in the Status register is 1, indicating that the Tx FIFO is not full. If the Tx FIFO was previously empty and the SPI controller is not busy on the bus, transmission of the data will begin immediately. Otherwise the data written to this register will be sent as soon as all previous data has been sent (and received). If the data length is less than 16 bit, software must right-justify the data written to this register. Read: software can read data from this register whenever the RNE bit in the Status register is 1, indicating that the Rx FIFO is not empty. When software reads this register, the SPI controller returns data from the least recent frame in the Rx FIFO. If the data length is less than 16 bit, the data is right-justified in this field with higher order bits filled with 0s. Reserved.
#define SSP0DR_DATA_SHIFT              0                 

/* SSP0SR - address 0x4004 000C, SSP1SR - address 0x4005 800C */
#define SSP0SR_TFE                     (1 << 0)           // Transmit FIFO Empty. This bit is 1 is the Transmit FIFO is empty, 0 if not.
#define SSP0SR_TNF                     (1 << 1)           // Transmit FIFO Not Full. This bit is 0 if the Tx FIFO is full, 1 if not. 1
#define SSP0SR_RNE                     (1 << 2)           // Receive FIFO Not Empty. This bit is 0 if the Receive FIFO is empty, 1 if not.
#define SSP0SR_RFF                     (1 << 3)           // Receive FIFO Full. This bit is 1 if the Receive FIFO is full, 0 if not.
#define SSP0SR_BSY                     (1 << 4)           // Busy. This bit is 0 if the SPI controller is idle, 1 if it is currently sending/receiving a frame and/or the Tx FIFO is not empty.

/* SSP0CPSR - address 0x4004 0010, SSP1CPSR - address 0x4005 8010 */
#define SSP0CPSR_CPSDVSR_MASK          0x00FF             // This even value between 2 and 254, by which SPI_PCLK is divided to yield the prescaler output clock. Bit 0 always reads as 0.
#define SSP0CPSR_CPSDVSR_SHIFT         0                 

/* SSP0IMSC - address 0x4004 0014, SSP1IMSC - address 0x4005 8014 */
#define SSP0IMSC_RORIM                 (1 << 0)           // Software should set this bit to enable interrupt when a Receive        0 Overrun occurs, that is, when the Rx FIFO is full and another frame is completely received. The ARM spec implies that the preceding frame data is overwritten by the new frame data when this occurs.
#define SSP0IMSC_RTIM                  (1 << 1)           // Software should set this bit to enable interrupt when a Receive Time-out condition occurs. A Receive Time-out occurs when the Rx FIFO is not empty, and no has not been read for a time-out period. The time-out period is the same for master and slave modes and is determined by the SSP bit rate: 32 bits at PCLK / (CPSDVSR [SCR+1]).
#define SSP0IMSC_RXIM                  (1 << 2)           // Software should set this bit to enable interrupt when the Rx FIFO is at 0 least half full.
#define SSP0IMSC_TXIM                  (1 << 3)           // Software should set this bit to enable interrupt when the Tx FIFO is at 0 least half empty.

/* SSP0RIS - address 0x4004 0018, SSP1RIS - address 0x4005 8018 */
#define SSP0RIS_RORRIS                 (1 << 0)           // This bit is 1 if another frame was completely received while the 0 RxFIFO was full. The ARM spec implies that the preceding frame data is overwritten by the new frame data when this occurs.
#define SSP0RIS_RTRIS                  (1 << 1)           // This bit is 1 if the Rx FIFO is not empty, and has not been read 0 for a time-out period. The time-out period is the same for master and slave modes and is determined by the SSP bit rate: 32 bits at PCLK / (CPSDVSR  [SCR+1]).
#define SSP0RIS_RXRIS                  (1 << 2)           // This bit is 1 if the Rx FIFO is at least half full.
#define SSP0RIS_TXRIS                  (1 << 3)           // This bit is 1 if the Tx FIFO is at least half empty.

/* SSP0MIS - address 0x4004 001C, SSP1MIS - address 0x4005 801C */
#define SSP0MIS_RORMIS                 (1 << 0)           // This bit is 1 if another frame was completely received while the 0 RxFIFO was full, and this interrupt is enabled.
#define SSP0MIS_RTMIS                  (1 << 1)           // This bit is 1 if the Rx FIFO is not empty, has not been read for a time-out period, and this interrupt is enabled. The time-out period is the same for master and slave modes and is determined by the SSP bit rate: 32 bits at PCLK / (CPSDVSR [SCR+1]).
#define SSP0MIS_RXMIS                  (1 << 2)           // This bit is 1 if the Rx FIFO is at least half full, and this interrupt 0 is enabled.
#define SSP0MIS_TXMIS                  (1 << 3)           // This bit is 1 if the Tx FIFO is at least half empty, and this interrupt is enabled.

/* SSP0ICR - address 0x4004 0020, SSP1ICR - address 0x4005 8020 */
#define SSP0ICR_RORIC                  (1 << 0)           // Writing a 1 to this bit clears the "frame was received when RxFIFO was full" interrupt.
#define SSP0ICR_RTIC                   (1 << 1)           // Writing a 1 to this bit clears the Rx FIFO was not empty and has not been read for a timeout period interrupt. The timeout period is the same for master and slave modes and is determined by the SSP bit rate: 32 bits at PCLK / (CPSDVSR [SCR+1]).

/* I2C0CONSET - address 0x4000 0000 */
#define I2C0CONSET_AA                  (1 << 2)           // Assert acknowledge flag.
#define I2C0CONSET_SI                  (1 << 3)           // I2C interrupt flag.
#define I2C0CONSET_STO                 (1 << 4)           // STOP flag.
#define I2C0CONSET_STA                 (1 << 5)           // START flag.
#define I2C0CONSET_I2EN                (1 << 6)           // I2C    interface enable. Reserved. The value read from a reserved bit is not defined.

/* I2C0STAT - 0x4000 0004 */
#define I2C0STAT_STATUS_MASK           0x00F8             // These bits give the actual status information about the                      I2 C interface. Reserved. The value read from a reserved bit is not defined.
#define I2C0STAT_STATUS_SHIFT          3                 

/* I2C0DAT - 0x4000 0008 */
#define I2C0DAT_DATA_MASK              0x00FF             // This register holds data values that have been received or are to 0 be transmitted. Reserved. The value read from a reserved bit is not defined.
#define I2C0DAT_DATA_SHIFT             0                 

/* I2C0ADR0 - 0x4000 000C */
#define I2C0ADR0_GC                    (1 << 0)           // General Call enable bit.
#define I2C0ADR0_ADDRESS_MASK          0x00FE             // The I2C device address for slave mode. Reserved. The value read from a reserved bit is not defined.
#define I2C0ADR0_ADDRESS_SHIFT         1                 

/* I2C0SCLH - address 0x4000 0010 */
#define I2C0SCLH_SCLH_MASK             0xFFFF             // Count for SCL HIGH time period selection.
#define I2C0SCLH_SCLH_SHIFT            0                 

/* I2C0SCLL - 0x4000 0014 */
#define I2C0SCLL_SCLL_MASK             0xFFFF             // Count for SCL low time period selection.
#define I2C0SCLL_SCLL_SHIFT            0                 

/* I2C0CONCLR - 0x4000 0018 */
#define I2C0CONCLR_AAC                 (1 << 2)           // Assert acknowledge Clear bit.
#define I2C0CONCLR_SIC                 (1 << 3)           // I2C interrupt Clear bit.
#define I2C0CONCLR_STAC                (1 << 5)           // START flag Clear bit.
#define I2C0CONCLR_I2ENC               (1 << 6)           // I2C    interface Disable bit. Reserved. The value read from a reserved bit is not defined.

/* I2C0MMCTRL - 0x4000 001C */
#define I2C0MMCTRL_MM_ENA              (1 << 0)           // Monitor mode enable.
#define I2C0MMCTRL_ENA_SCL             (1 << 1)           // SCL output enable.

/* I2C0DATA_BUFFER - 0x4000 002C */
#define I2C0DATA_BUFFER_DATA_MASK      0x00FF             // This register holds contents of the 8 MSBs of the DAT shift register. Reserved. The value read from a reserved bit is not defined.
#define I2C0DATA_BUFFER_DATA_SHIFT     0                 

/* CANCNTL, address 0x4005 0000 */
#define CANCNTL_INIT                   (1 << 0)           // Initialization
#define CANCNTL_IE                     (1 << 1)           // Module interrupt enable
#define CANCNTL_SIE                    (1 << 2)           // Status change interrupt enable
#define CANCNTL_EIE                    (1 << 3)           // Error interrupt enable
#define CANCNTL_DAR                    (1 << 5)           // Disable automatic retransmission
#define CANCNTL_CCE                    (1 << 6)           // Configuration change enable
#define CANCNTL_TEST                   (1 << 7)           // Test mode enable

/* CANSTAT, address 0x4005 0004 */
#define CANSTAT_LEC_MASK               0x0007             // Last error code Type of the last error to occur on the CAN bus.The LEC field holds a code which indicates the type of the last error to occur on the CAN bus. This field will be cleared to `0' when a message has been transferred (reception or transmission) without error. The unused code `111' may be written by the CPU to check for updates.
#define CANSTAT_LEC_SHIFT              0                 
#define CANSTAT_TXOK                   (1 << 3)           // Transmitted a message successfully This bit must be reset by the CPU. It is never reset by the CAN controller.
#define CANSTAT_RXOK                   (1 << 4)           // Received a message successfully This bit must be reset by the CPU. It is never reset by the CAN controller.
#define CANSTAT_EPASS                  (1 << 5)           // Error passive
#define CANSTAT_EWARN                  (1 << 6)           // Warning status
#define CANSTAT_BOFF                   (1 << 7)           // Busoff status

/* CANEC, address 0x4005 0008 */
#define CANEC_TEC_MASK                 0x00FF             // Transmit error counter Current value of the transmit error counter (maximum value 255)
#define CANEC_TEC_SHIFT                0                 
#define CANEC_REC_MASK                 0x7F00             // Receive error counter Current value of the receive error counter (maximum value 127).
#define CANEC_REC_SHIFT                8                 
#define CANEC_RP                       (1 << 15)          // Receive error passive

/* CANBT, address 0x4005 000C */
#define CANBT_BRP_MASK                 0x003F             // Baud rate prescaler The value by which the oscillator frequency is divided for generating the bit time quanta. The bit time is built up from a multiple of this quanta. Valid values for the Baud Rate Prescaler are 0 to 63.[1]
#define CANBT_BRP_SHIFT                0                 
#define CANBT_SJW_MASK                 0x00C0             // (Re)synchronization jump width Valid programmed values are 0 to 3.[1]
#define CANBT_SJW_SHIFT                6                 
#define CANBT_TSEG1_MASK               0x0F00             // Time segment before the sample point Valid values are 1 to                  15.[1]
#define CANBT_TSEG1_SHIFT              8                 
#define CANBT_TSEG2_MASK               0x7000             // Time segment after the sample point Valid values are 0 to                  7.[1]
#define CANBT_TSEG2_SHIFT              12                

/* CANINT, address 0x4005 0010 */
#define CANINT_INTID_MASK              0xFFFF             // 0x0000 = No interrupt is pending.                0 0x0001 - 0x0020 = Number of message object which caused the interrupt. 0x0021 - 0x7FFF = Unused 0x8000 = Status interrupt 0x8001 - 0xFFFF = Unused
#define CANINT_INTID_SHIFT             0                 

/* CANTEST, address 0x4005 0014 */
#define CANTEST_BASIC                  (1 << 2)           // Basic mode
#define CANTEST_SILENT                 (1 << 3)           // Silent mode
#define CANTEST_LBACK                  (1 << 4)           // Loop back mode
#define CANTEST_TX_MASK                0x0060             // Control of CAN_TXD pins
#define CANTEST_TX_SHIFT               5                 
#define CANTEST_RX                     (1 << 7)           // Monitors the actual value of the CAN_RXD pin.

/* CANBRPE, address 0x4005 0018 */
#define CANBRPE_BRPE_MASK              0x000F             // Baud rate prescaler extension By programming BRPE the Baud Rate Prescaler can be extended to values up to 1023. Hardware interprets the value as the value of BRPE (MSBs) and BRP (LSBs) plus one. Allowed values are 0 to 15.
#define CANBRPE_BRPE_SHIFT             0                 

/* CANIF1_CMDREQ, address 0x4005 0020 and CANIF2_CMDREQ, address 0x4005 0080 */
#define CANIFn_CMDREQ_MN_MASK          0x003F             // Message number 0x01 - 0x20 = Valid message numbers. The message object in the message RAM is selected for data transfer. 0x00 = Not a valid message number. This value is interpreted as 0x20.[1] 0x21 - 0x3F = Not a valid message number. This value is interpreted as 0x01 - 0x1F.[1]
#define CANIFn_CMDREQ_MN_SHIFT         0                 
#define CANIFn_CMDREQ_BUSY             (1 << 15)          // BUSY flag

/* CANIF1_CMDMSK, address 0x4005 0024 and CANIF2_CMDMSK, address 0x4005 0084 */
#define CANIFn_CMDMSK_DATA_B           (1 << 0)           // Access data bytes 4-7
#define CANIFn_CMDMSK_DATA_A           (1 << 1)           // Access data bytes 0-3
#define CANIFn_CMDMSK_TXRQST           (1 << 2)           // Access transmission request bit (Write direction)
#define CANIFn_CMDMSK_NEWDAT           (1 << 2)           // Access new data bit (Read direction)
#define CANIFn_CMDMSK_CLRINTPND        (1 << 3)           // This bit is ignored in the write direction.
#define CANIFn_CMDMSK_CTRL             (1 << 4)           // Access control bits
#define CANIFn_CMDMSK_ARB              (1 << 5)           // Access arbitration bits
#define CANIFn_CMDMSK_MASK             (1 << 6)           // Access mask bits
#define CANIFn_CMDMSK_WR               (1 << 7)           // Write transfer Transfer data from the selected message buffer registers to the message object addressed by the command request register CANIFn_CMDREQ.
#define CANIFn_CMDMSK_RD               (0 << 7)           // Read transfer Read data from the selected message buffer registers to the message object addressed by the command request register CANIFn_CMDREQ.

/* CANIF1_MSK1, address 0x4005 0028 and CANIF2_MASK1, address 0x4005 0088 */
#define CANIFn_MSK1_MSK_MASK           0xFFFF             // Identifier mask
#define CANIFn_MSK1_MSK_SHIFT          0                 

/* CANIF1_MSK2, address 0x4005 002C and CANIF2_MASK2, address 0x4005 008C */
#define CANIFn_MSK2_MSK_MASK           0x1FFF             // Identifier mask
#define CANIFn_MSK2_MSK_SHIFT          0                 
#define CANIFn_MSK2_MDIR               (1 << 14)          // Mask message direction
#define CANIFn_MSK2_MXTD               (1 << 15)          // Mask extend identifier

/* CANIF1_ARB1, address 0x4005 0030 and CANIF2_ARB1, address 0x4005 0090 */
#define CANIFn_ARB1_ID_MASK            0xFFFF             // Message identifier 29-bit identifier (extended frame) 11-bit identifier (standard frame)
#define CANIFn_ARB1_ID_SHIFT           0                 

/* CANIF1_ARB2, address 0x4005 0034 and CANIF2_ARB2, address 0x4005 0094 */
#define CANIFn_ARB2_ID_MASK            0x1FFF             // Message identifier 29-bit identifier (extended frame) 11-bit identifier (standard frame)
#define CANIFn_ARB2_ID_SHIFT           0                 
#define CANIFn_ARB2_DIR                (1 << 13)          // Message direction
#define CANIFn_ARB2_XTD                (1 << 14)          // Extend identifier
#define CANIFn_ARB2_MSGVAL             (1 << 15)          // Message valid Remark: The CPU must reset the MSGVAL bit of all unused Messages Objects during the initialization before it resets bit INIT in the CAN Control Register. This bit must also be reset before the identifier ID28:0, the control bits XTD, DIR, or the Data Length Code DLC3:0 are modified, or if the Messages Object is no longer required.

/* CANIF1_MCTRL, address 0x4005 0038 and CANIF2_MCTRL, address 0x4005 0098 */
#define CANIFn_MCTRL_DLC_MASK          0x000F             // Data length code Remark: The Data Length Code of a Message Object must be defined the same as in all the corresponding objects with the same identifier at other nodes. When the Message Handler stores a data frame, it will write the DLC to the value given by the received message. 0000 - 1000 = Data frame has 0 - 8 data bytes. 1001 - 1111 = Data frame has 8 data bytes.
#define CANIFn_MCTRL_DLC_SHIFT         0                 
#define CANIFn_MCTRL_EOB               (1 << 7)           // End of buffer
#define CANIFn_MCTRL_TXRQST            (1 << 8)           // Transmit request
#define CANIFn_MCTRL_RMTEN             (1 << 9)           // Remote enable
#define CANIFn_MCTRL_RXIE              (1 << 10)          // Receive interrupt enable
#define CANIFn_MCTRL_TXIE              (1 << 11)          // Transmit interrupt enable
#define CANIFn_MCTRL_UMASK             (1 << 12)          // Use acceptance mask Remark: If UMASK is set to 1, the message object's mask bits have to be programmed during initialization of the message object before MAGVAL is set to 1.
#define CANIFn_MCTRL_INTPND            (1 << 13)          // Interrupt pending
#define CANIFn_MCTRL_MSGLST            (1 << 14)          // Message lost (only valid for message objects in the direction receive).
#define CANIFn_MCTRL_NEWDAT            (1 << 15)          // New data

/* CANIF1_DA1, address 0x4005 003C and CANIF2_DA1, address 0x4005 009C */
#define CANIFn_DA1_DATA0_MASK          0x00FF             // Data byte 0
#define CANIFn_DA1_DATA0_SHIFT         0                 
#define CANIFn_DA1_DATA1_MASK          0xFF00             // Data byte 1
#define CANIFn_DA1_DATA1_SHIFT         8                 

/* CANIF1_DA2, address 0x4005 0040 and CANIF2_DA2, address 0x4005 00A0 */
#define CANIFn_DA2_DATA2_MASK          0x00FF             // Data byte 2
#define CANIFn_DA2_DATA2_SHIFT         0                 
#define CANIFn_DA2_DATA3_MASK          0xFF00             // Data byte 3
#define CANIFn_DA2_DATA3_SHIFT         8                 

/* CANIF1_DB1, address 0x4005 0044 and CANIF2_DB1, address 0x4005 00A4 */
#define CANIFn_DB1_DATA4_MASK          0x00FF             // Data byte 4
#define CANIFn_DB1_DATA4_SHIFT         0                 
#define CANIFn_DB1_DATA5_MASK          0xFF00             // Data byte 5
#define CANIFn_DB1_DATA5_SHIFT         8                 

/* CANIF1_DB2, address 0x4005 0048 and CANIF2_DB2, address 0x4005 00A8 */
#define CANIFn_DB2_DATA6_MASK          0x00FF             // Data byte 6
#define CANIFn_DB2_DATA6_SHIFT         0                 
#define CANIFn_DB2_DATA7_MASK          0xFF00             // Data byte 7
#define CANIFn_DB2_DATA7_SHIFT         8                 

/* CANTXREQ1, address 0x4005 0100 */
#define CANTXREQ1_TXRQST_MASK          0xFFFF             // Transmission request bit of message objects 16 to 1. 0 = This message object is not waiting for transmission. 1 = The transmission of this message object is requested and not yet done. Reserved
#define CANTXREQ1_TXRQST_SHIFT         0                 

/* CANTXREQ2, address 0x4005 0104 */
#define CANTXREQ2_TXRQST_MASK          0xFFFF             // Transmission request bit of message objects 32 to 17. 0 = This message object is not waiting for transmission. 1 = The transmission of this message object is requested and not yet done. Reserved
#define CANTXREQ2_TXRQST_SHIFT         0                 

/* CANND1, address 0x4005 0120 */
#define CANND1_NEWDAT_MASK             0xFFFF             // New data bits of message objects 16 to 1. 0 = No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared by the CPU. 1 = The Message Handler or the CPU has written new data into the data portion of this Message Object.
#define CANND1_NEWDAT_SHIFT            0                 

/* CANND2, address 0x4005 0124 */
#define CANND2_NEWDAT_MASK             0xFFFF             // New data bits of message objects 32 to 17. 0 = No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared by the CPU. 1 = The Message Handler or the CPU has written new data into the data portion of this Message Object.
#define CANND2_NEWDAT_SHIFT            0                 

/* CANIR1, address 0x4005 0140 */
#define CANIR1_INTPND_INTERRUPT_MASK   0xFFFF             // pending bits of message objects 16 to 1. essage object is ignored by the message essage object is the source of an interrupt. Reserved
#define CANIR1_INTPND_INTERRUPT_SHIFT  0                 

/* CANIR2, addresses 0x4005 0144 */
#define CANIR2_INTPND_MASK             0xFFFF             // Interrupt pending bits of message objects 32 to 17. 0 = This message object is ignored by the message handler. 1 = This message object is the source of an interrupt. Reserved
#define CANIR2_INTPND_SHIFT            0                 

/* CANMSGV1, addresses 0x4005 0160 */
#define CANMSGV1_MSGVAL_MASK           0xFFFF             // Message valid bits of message objects 16 to 1. 0 = This message object is ignored by the message handler. 1 = This message object is configured and should be considered by the message handler. Reserved
#define CANMSGV1_MSGVAL_SHIFT          0                 

/* CANMSGV2, address 0x4005 0164 */
#define CANMSGV2_MSGVAL_MASK           0xFFFF             // Message valid bits of message objects 32 to 17. 0 = This message object is ignored by the message handler. 1 = This message object is configured and should be considered by the message handler. Reserved
#define CANMSGV2_MSGVAL_SHIFT          0                 

/* CANCLKDIV, address 0x4005 0180 */
#define CANCLKDIV_CLKDIVVAL_MASK       0x000F             // Clock divider value. CAN_CLK = PCLK/(CLKDIVVAL +1) 0000: CAN_CLK = PCLK divided by 1. 0001: CAN_CLK = PCLK divided by 2. 0010: CAN_CLK = PCLK divided by 3 0011: CAN_CLK = PCLK divided by 4. ... 1111: CAN_CLK = PCLK divided by 16.
#define CANCLKDIV_CLKDIVVAL_SHIFT      0                 

/* TMR16B0IR - address 0x4000 C000 and TMR16B1IR - address 0x4001 0000 */
#define TMR16B0IR_MR0                  (1 << 0)           // Interrupt flag for match channel 0.
#define TMR16B0IR_MR1                  (1 << 1)           // Interrupt flag for match channel 1.
#define TMR16B0IR_MR2                  (1 << 2)           // Interrupt flag for match channel 2.
#define TMR16B0IR_MR3                  (1 << 3)           // Interrupt flag for match channel 3.
#define TMR16B0IR_CR0                  (1 << 4)           // Interrupt flag for capture channel 0 event.

/* TMR16B0TCR - address 0x4000 C004 and TMR16B1TCR - address 0x4001 0004 */
#define TMR16B0TCR_CEN                 (1 << 0)           // Counter Enable. When one, the Timer Counter and Prescale Counter are enabled for counting. When zero, the counters are disabled.
#define TMR16B0TCR_CRST                (1 << 1)           // Counter Reset. When one, the Timer Counter and the Prescale Counter are synchronously reset on the next positive edge of PCLK. The counters remain reset until TCR[1] is returned to zero.

/* TMR16B0TC, address 0x4000 C008 and TMR16B1TC 0x4001 0008 */
#define TMR16B0TC_TC_MASK              0xFFFF             // Timer counter value.
#define TMR16B0TC_TC_SHIFT             0                 

/* TMR16B0PR, address 0x4000 C00C and TMR16B1PR 0x4001 000C */
#define TMR16B0PR_PR_MASK              0xFFFF             // Prescale max value.
#define TMR16B0PR_PR_SHIFT             0                 

/* TMR16B0PC, address 0x4001 C010 and TMR16B1PC 0x4000 0010 */
#define TMR16B0PC_PC_MASK              0xFFFF             // Prescale counter value.
#define TMR16B0PC_PC_SHIFT             0                 

/* TMR16B0MCR - address 0x4000 C014 and TMR16B1MCR - address 0x4001 0014 */
#define TMR16B0MCR_MR0I                (1 << 0)           // Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
#define TMR16B0MCR_MR0R                (1 << 1)           // Reset on MR0: the TC will be reset if MR0 matches it.
#define TMR16B0MCR_MR0S                (1 << 2)           // Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches 0 the TC.
#define TMR16B0MCR_MR1I                (1 << 3)           // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.
#define TMR16B0MCR_MR1R                (1 << 4)           // Reset on MR1: the TC will be reset if MR1 matches it.
#define TMR16B0MCR_MR1S                (1 << 5)           // Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches 0 the TC.
#define TMR16B0MCR_MR2I                (1 << 6)           // Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
#define TMR16B0MCR_MR2R                (1 << 7)           // Reset on MR2: the TC will be reset if MR2 matches it.
#define TMR16B0MCR_MR2S                (1 << 8)           // Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches 0 the TC.
#define TMR16B0MCR_MR3I                (1 << 9)           // Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
#define TMR16B0MCR_MR3R                (1 << 10)          // Reset on MR3: the TC will be reset if MR3 matches it.
#define TMR16B0MCR_MR3S                (1 << 11)          // Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches 0 the TC.

/* TMR16B0MR0 to 3, addresses 0x4000 C018 to 24 and TMR16B1MR0 to 3, addresses 0x4001 0018 to 24 */
#define TMR16B0MR0_to_3_MATCH_MASK     0xFFFF             // Timer counter match value.
#define TMR16B0MR0_to_3_MATCH_SHIFT    0                 

/* TMR16B0CCR - address 0x4000 C028 and TMR16B1CCR - address 0x4001 0028 */
#define TMR16B0CCR_CAP0RE              (1 << 0)           // Capture on CT16Bn_CAP0 rising edge: a sequence of 0 then 1 on CT16Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP0FE              (1 << 1)           // Capture on CT16Bn_CAP0 falling edge: a sequence of 1 then 0 on CT16Bn_CAP0 will 0 cause CR0 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP0I               (1 << 2)           // Interrupt on CT16Bn_CAP0 event: a CR0 load due to a CT16Bn_CAP0 event will generate an interrupt.

/* TMR16B0CR0, address 0x4000 C02C and TMR16B1CR0, address 0x4001 002C */
#define TMR16B0CR0_CAP_MASK            0xFFFF             // Timer counter capture value.
#define TMR16B0CR0_CAP_SHIFT           0                 

/* TMR16B0EMR - address 0x4000 C03C and TMR16B1EMR - address 0x4001 003C */
#define TMR16B0EMR_EM0                 (1 << 0)           // External Match 0. This bit reflects the state of output CT16B0_MAT0/CT16B1_MAT0,       0 whether or not this output is connected to its pin. When a match occurs between the TC and MR0, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[5:4] control the functionality of this output. This bit is driven to the CT16B0_MAT0/CT16B1_MAT0 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM1                 (1 << 1)           // External Match 1. This bit reflects the state of output CT16B0_MAT1/CT16B1_MAT1,       0 whether or not this output is connected to its pin. When a match occurs between the TC and MR1, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[7:6] control the functionality of this output. This bit is driven to the CT16B0_MAT1/CT16B1_MAT1 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM2                 (1 << 2)           // External Match 2. This bit reflects the state of output match channel 2, whether or not     0 this output is connected to its pin. When a match occurs between the TC and MR2, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[9:8] control the functionality of this output. Note that on counter/timer 0 this match channel is not pinned out. This bit is driven to the CT16B1_MAT2 pin if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM3                 (1 << 3)           // External Match 3. This bit reflects the state of output of match channel 3. When a match 0 occurs between the TC and MR3, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[11:10] control the functionality of this output. There is no output pin available for this channel on either of the 16-bit timers.
#define TMR16B0EMR_EMC0_MASK           0x0030             // External Match Control 0. Determines the functionality of External Match 0.
#define TMR16B0EMR_EMC0_SHIFT          4                 
#define TMR16B0EMR_EMC1_MASK           0x00C0             // External Match Control 1. Determines the functionality of External Match 1.
#define TMR16B0EMR_EMC1_SHIFT          6                 
#define TMR16B0EMR_EMC2_MASK           0x0300             // External Match Control 2. Determines the functionality of External Match 2.
#define TMR16B0EMR_EMC2_SHIFT          8                 
#define TMR16B0EMR_EMC3_MASK           0x0C00             // External Match Control 3. Determines the functionality of External Match 3.
#define TMR16B0EMR_EMC3_SHIFT          10                

/* TMR16B0CTCR - address 0x4000 C070 and TMR16B1CTCR - address 0x4001 0070 */
#define TMR16B0CTCR_CTM_MASK           0x0003             // Counter/Timer Mode. This field selects which rising PCLK    00 edges can increment Timer's Prescale Counter (PC), or clear PC and increment Timer Counter (TC).
#define TMR16B0CTCR_CTM_SHIFT          0                 

/* TMR16B0PWMC - address 0x4000 C074 and TMR16B1PWMC- address 0x4001 0074 */
#define TMR16B0PWMC_PWMEN0             (1 << 0)           // PWM channel0 enable
#define TMR16B0PWMC_PWMEN1             (1 << 1)           // PWM channel1 enable
#define TMR16B0PWMC_PWMEN2             (1 << 2)           // PWM channel2 enable
#define TMR16B0PWMC_PWMEN3             (1 << 3)           // PWM channel3 enable Note: It is recommended to use match channel 3 to set the PWM cycle because it is not pinned out.

/* TMR16B0IR - address 0x4000 C000 and TMR16B1IR - address 0x4001 0000 */
#define TMR16B0IR_MR0INT               (1 << 0)           // Interrupt flag for match channel 0.
#define TMR16B0IR_MR1INT               (1 << 1)           // Interrupt flag for match channel 1.
#define TMR16B0IR_MR2INT               (1 << 2)           // Interrupt flag for match channel 2.
#define TMR16B0IR_MR3INT               (1 << 3)           // Interrupt flag for match channel 3.
#define TMR16B0IR_CR0INT               (1 << 4)           // Interrupt flag for capture channel 0 event.
#define TMR16B0IR_CR1INT               (1 << 5)           // Interrupt flag for capture channel 1 event.

/* TMR16B0TCR - address 0x4000 C004 and TMR16B1TCR - address 0x4001 0004 */
#define TMR16B0TCR_CEN                 (1 << 0)           // Counter Enable. When one, the Timer Counter and Prescale Counter are enabled for counting. When zero, the counters are disabled.
#define TMR16B0TCR_CRST                (1 << 1)           // Counter Reset. When one, the Timer Counter and the Prescale Counter are synchronously reset on the next positive edge of PCLK. The counters remain reset until TCR[1] is returned to zero.

/* TMR16B0TC, address 0x4000 C008 and TMR16B1TC 0x4001 0008 */
#define TMR16B0TC_TC_MASK              0xFFFF             // Timer counter value.
#define TMR16B0TC_TC_SHIFT             0                 

/* TMR16B0PR, address 0x4000 C00C and TMR16B1PR 0x4001 000C */
#define TMR16B0PR_PR_MASK              0xFFFF             // Prescale max value.
#define TMR16B0PR_PR_SHIFT             0                 

/* TMR16B0PC, address 0x4001 C010 and TMR16B1PC 0x4000 0010 */
#define TMR16B0PC_PC_MASK              0xFFFF             // Prescale counter value.
#define TMR16B0PC_PC_SHIFT             0                 

/* TMR16B0MCR - address 0x4000 C014 and TMR16B1MCR - address 0x4001 0014 */
#define TMR16B0MCR_MR0I                (1 << 0)           // Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
#define TMR16B0MCR_MR0R                (1 << 1)           // Reset on MR0: the TC will be reset if MR0 matches it.
#define TMR16B0MCR_MR0S                (1 << 2)           // Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches 0 the TC.
#define TMR16B0MCR_MR1I                (1 << 3)           // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.
#define TMR16B0MCR_MR1R                (1 << 4)           // Reset on MR1: the TC will be reset if MR1 matches it.
#define TMR16B0MCR_MR1S                (1 << 5)           // Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches 0 the TC.
#define TMR16B0MCR_MR2I                (1 << 6)           // Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
#define TMR16B0MCR_MR2R                (1 << 7)           // Reset on MR2: the TC will be reset if MR2 matches it.
#define TMR16B0MCR_MR2S                (1 << 8)           // Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches 0 the TC.
#define TMR16B0MCR_MR3I                (1 << 9)           // Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
#define TMR16B0MCR_MR3R                (1 << 10)          // Reset on MR3: the TC will be reset if MR3 matches it.
#define TMR16B0MCR_MR3S                (1 << 11)          // Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches 0 the TC.

/* TMR16B0MR0 to 3, addresses 0x4000 C018 to 24 and TMR16B1MR0 to 3, addresses 0x4001 0018 to 24 */
#define TMR16B0MR0_to_3_MATCH_MASK     0xFFFF             // Timer counter match value.
#define TMR16B0MR0_to_3_MATCH_SHIFT    0                 

/* TMR16B0CCR - address 0x4000 C028 and TMR16B1CCR - address 0x4001 0028 */
#define TMR16B0CCR_CAP0RE              (1 << 0)           // Capture on CT16Bn_CAP0 rising edge: a sequence of 0 then 1 on CT16Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP0FE              (1 << 1)           // Capture on CT16Bn_CAP0 falling edge: a sequence of 1 then 0 on CT16Bn_CAP0 will 0 cause CR0 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP0I               (1 << 2)           // Interrupt on CT16Bn_CAP0 event: a CR0 load due to a CT16Bn_CAP0 event will generate an interrupt.
#define TMR16B0CCR_CAP1RE              (1 << 3)           // Capture on CT16Bn_CAP1 rising edge: a sequence of 0 then 1 on CT16Bn_CAP1 will cause CR1 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP1FE              (1 << 4)           // Capture on CT16Bn_CAP1 falling edge: a sequence of 1 then 0 on CT16Bn_CAP1 will 0 cause CR1 to be loaded with the contents of TC.
#define TMR16B0CCR_CAP1I               (1 << 5)           // Interrupt on CT16Bn_CAP1 event: a CR1 load due to a CT16Bn_CAP1 event will generate an interrupt.

/* TMR16B0EMR - address 0x4000 C03C and TMR16B1EMR - address 0x4001 003C */
#define TMR16B0EMR_EM0                 (1 << 0)           // External Match 0. This bit reflects the state of output CT16B0_MAT0/CT16B1_MAT0,       0 whether or not this output is connected to its pin. When a match occurs between the TC and MR0, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[5:4] control the functionality of this output. This bit is driven to the CT16B0_MAT0/CT16B1_MAT0 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM1                 (1 << 1)           // External Match 1. This bit reflects the state of output CT16B0_MAT1/CT16B1_MAT1,       0 whether or not this output is connected to its pin. When a match occurs between the TC and MR1, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[7:6] control the functionality of this output. This bit is driven to the CT16B0_MAT1/CT16B1_MAT1 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM2                 (1 << 2)           // External Match 2. This bit reflects the state of output match channel 2, whether or not     0 this output is connected to its pin. When a match occurs between the TC and MR2, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[9:8] control the functionality of this output. Note that on counter/timer 0 this match channel is not pinned out. This bit is driven to the CT16B1_MAT2 pin if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR16B0EMR_EM3                 (1 << 3)           // External Match 3. This bit reflects the state of output of match channel 3. When a match 0 occurs between the TC and MR3, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[11:10] control the functionality of this output. There is no output pin available for this channel on either of the 16-bit timers.
#define TMR16B0EMR_EMC0_MASK           0x0030             // External Match Control 0. Determines the functionality of External Match 0.
#define TMR16B0EMR_EMC0_SHIFT          4                 
#define TMR16B0EMR_EMC1_MASK           0x00C0             // External Match Control 1. Determines the functionality of External Match 1.
#define TMR16B0EMR_EMC1_SHIFT          6                 
#define TMR16B0EMR_EMC2_MASK           0x0300             // External Match Control 2. Determines the functionality of External Match 2.
#define TMR16B0EMR_EMC2_SHIFT          8                 
#define TMR16B0EMR_EMC3_MASK           0x0C00             // External Match Control 3. Determines the functionality of External Match 3.
#define TMR16B0EMR_EMC3_SHIFT          10                

/* TMR16B0CTCR - address 0x4000 C070 and TMR16B1CTCR - address 0x4001 0070 */
#define TMR16B0CTCR_CTM_MASK           0x0003             // Counter/Timer Mode. This field selects which rising PCLK    00 edges can increment Timer's Prescale Counter (PC), or clear PC and increment Timer Counter (TC).
#define TMR16B0CTCR_CTM_SHIFT          0                 
#define TMR16B0CTCR_SELCC_MASK         0x00E0             // When bit 4 is one, these bits select which capture input edge 0 will cause the timer and prescaler to be cleared. These bits have no effect when bit 4 is zero.
#define TMR16B0CTCR_SELCC_SHIFT        5                 

/* TMR16B0PWMC - address 0x4000 C074 and TMR16B1PWMC- address 0x4001 0074 */
#define TMR16B0PWMC_PWMEN0             (1 << 0)           // PWM channel0 enable
#define TMR16B0PWMC_PWMEN1             (1 << 1)           // PWM channel1 enable
#define TMR16B0PWMC_PWMEN2             (1 << 2)           // PWM channel2 enable
#define TMR16B0PWMC_PWMEN3             (1 << 3)           // PWM channel3 enable Note: It is recommended to use match channel 3 to set the PWM cycle because it is not pinned out.

/* TMR32B0IR - address 0x4001 4000 and TMR32B1IR - address 0x4001 8000 */
#define TMR32B0IR_MR0_INTERRUPT        (1 << 0)           // Interrupt flag for match channel 0.
#define TMR32B0IR_MR1_INTERRUPT        (1 << 1)           // Interrupt flag for match channel 1.
#define TMR32B0IR_MR2_INTERRUPT        (1 << 2)           // Interrupt flag for match channel 2.
#define TMR32B0IR_MR3_INTERRUPT        (1 << 3)           // Interrupt flag for match channel 3.
#define TMR32B0IR_CR0_INTERRUPT        (1 << 4)           // Interrupt flag for capture channel 0 event.

/* TMR32B0TCR - address 0x4001 4004 and TMR32B1TCR - address 0x4001 8004 */
#define TMR32B0TCR_CEN                 (1 << 0)           // When one, the Timer Counter and Prescale Counter are 0 enabled for counting. When zero, the counters are disabled.
#define TMR32B0TCR_CRST                (1 << 1)           // When one, the Timer Counter and the Prescale Counter 0 are synchronously reset on the next positive edge of PCLK. The counters remain reset until TCR[1] is returned to zero.

/* TMR32B0TC, address 0x4001 4008 and TMR32B1TC 0x4001 8008 */
#define TMR32B0TC_TC_MASK              0xFFFFFFFF         // Timer counter value.
#define TMR32B0TC_TC_SHIFT             0                 

/* TMR32B0PR, address 0x4001 400C and TMR32B1PR 0x4001 800C */
#define TMR32B0PR_PR_MASK              0xFFFFFFFF         // Prescale value.
#define TMR32B0PR_PR_SHIFT             0                 

/* TMR32B0PC, address 0x4001 4010 and TMR32B1PC 0x4001 8010 */
#define TMR32B0PC_PC_MASK              0xFFFFFFFF         // Prescale counter value.
#define TMR32B0PC_PC_SHIFT             0                 

/* TMR32B0MCR - address 0x4001 4014 and TMR32B1MCR - address 0x4001 8014 */
#define TMR32B0MCR_MR0I                (1 << 0)           // Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
#define TMR32B0MCR_MR0R                (1 << 1)           // Reset on MR0: the TC will be reset if MR0 matches it.
#define TMR32B0MCR_MR0S                (1 << 2)           // Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches 0 the TC.
#define TMR32B0MCR_MR1I                (1 << 3)           // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.
#define TMR32B0MCR_MR1R                (1 << 4)           // Reset on MR1: the TC will be reset if MR1 matches it.
#define TMR32B0MCR_MR1S                (1 << 5)           // Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches 0 the TC.
#define TMR32B0MCR_MR2I                (1 << 6)           // Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
#define TMR32B0MCR_MR2R                (1 << 7)           // Reset on MR2: the TC will be reset if MR2 matches it.
#define TMR32B0MCR_MR2S                (1 << 8)           // Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches 0 the TC.
#define TMR32B0MCR_MR3I                (1 << 9)           // Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
#define TMR32B0MCR_MR3R                (1 << 10)          // Reset on MR3: the TC will be reset if MR3 matches it.
#define TMR32B0MCR_MR3S                (1 << 11)          // Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches 0 the TC.

/* TMR32B0MR0 to 3, addresses 0x4001 4018 to 24 and TMR32B1MR0 to 3, addresses 0x4001 8018 to 24 */
#define TMR32B0MRn_MATCH_MASK          0xFFFFFFFF         // Timer counter match value.
#define TMR32B0MRn_MATCH_SHIFT         0                 

/* TMR32B0CCR - address 0x4001 4028 and TMR32B1CCR - address 0x4001 8028 */
#define TMR32B0CCR_CAP0RE              (1 << 0)           // Capture on CT32Bn_CAP0 rising edge: a sequence of 0 then 1 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP0FE              (1 << 1)           // Capture on CT32Bn_CAP0 falling edge: a sequence of 1 then 0 on CT32Bn_CAP0 will 0 cause CR0 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP0I               (1 << 2)           // Interrupt on CT32Bn_CAP0 event: a CR0 load due to a CT32Bn_CAP0 event will generate an interrupt.

/* TMR32B0CR0, addresses 0x4001 402C and TMR32B1CR0, addresses 0x4001 802C */
#define TMR32B0CR0_CAP_MASK            0xFFFFFFFF         // Timer counter capture value.
#define TMR32B0CR0_CAP_SHIFT           0                 

/* TMR32B0EMR - address 0x4001 403C and TMR32B1EMR - address0x4001 803C */
#define TMR32B0EMR_EM0                 (1 << 0)           // External Match 0. This bit reflects the state of output CT32Bn_MAT0, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR0, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[5:4] control the functionality of this output. This bit is driven to the CT32B0_MAT0/CT16B1_MAT0 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM1                 (1 << 1)           // External Match 1. This bit reflects the state of output CT32Bn_MAT1, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR1, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[7:6] control the functionality of this output. This bit is driven to the CT32B0_MAT1/CT16B1_MAT1 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM2                 (1 << 2)           // External Match 2. This bit reflects the state of output CT32Bn_MAT2, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR2, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[9:8] control the functionality of this output. This bit is driven to the CT32B0_MAT2/CT16B1_MAT2 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM3                 (1 << 3)           // External Match 3. This bit reflects the state of output CT32Bn_MAT3, whether or not this output is connected to its pin. When a match occurs between the TC and MR3, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[11:10] control the functionality of this output. This bit is driven to the CT32B0_MAT3/CT16B1_MAT3 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EMC0_MASK           0x0030             // External Match Control 0. Determines the functionality of External Match 0.
#define TMR32B0EMR_EMC0_SHIFT          4                 
#define TMR32B0EMR_EMC1_MASK           0x00C0             // External Match Control 1. Determines the functionality of External Match 1.
#define TMR32B0EMR_EMC1_SHIFT          6                 
#define TMR32B0EMR_EMC2_MASK           0x0300             // External Match Control 2. Determines the functionality of External Match 2.
#define TMR32B0EMR_EMC2_SHIFT          8                 
#define TMR32B0EMR_EMC3_MASK           0x0C00             // External Match Control 3. Determines the functionality of External Match 3.
#define TMR32B0EMR_EMC3_SHIFT          10                

/* TMR32B0CTCR - address 0x4001 4070 and TMR32B1TCR - address 0x4001 8070 */
#define TMR32B0CTCR_CTM_MASK           0x0003             // Counter/Timer Mode. This field selects which rising PCLK edges can increment Timer's Prescale Counter (PC), or clear PC and increment Timer Counter (TC). Timer Mode: every rising PCLK edge
#define TMR32B0CTCR_CTM_SHIFT          0                 
#define TMR32B0CTCR_CIS_MASK           0x000C             // Count Input Select. When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking:
#define TMR32B0CTCR_CIS_SHIFT          2                 

/* TMR32B0PWMC - 0x4001 4074 and TMR32B1PWMC - 0x4001 8074 */
#define TMR32B0PWMC_PWMEN0             (1 << 0)           // PWM channel 0 enable
#define TMR32B0PWMC_PWMEN1             (1 << 1)           // PWM channel 1 enable
#define TMR32B0PWMC_PWMEN2             (1 << 2)           // PWM channel 2 enable
#define TMR32B0PWMC_PWMEN3             (1 << 3)           // PWM channel 3 enable Note: It is recommended to use match channel 3 to set the PWM cycle.

/* TMR32B0IR - address 0x4001 4000 and TMR32B1IR - address 0x4001 8000 */
#define TMR32B0IR_MR0INT               (1 << 0)           // Interrupt flag for match channel 0.
#define TMR32B0IR_MR1INT               (1 << 1)           // Interrupt flag for match channel 1.
#define TMR32B0IR_MR2INT               (1 << 2)           // Interrupt flag for match channel 2.
#define TMR32B0IR_MR3INT               (1 << 3)           // Interrupt flag for match channel 3.
#define TMR32B0IR_CR0INT               (1 << 4)           // Interrupt flag for capture channel 0 event.
#define TMR32B0IR_CR1INT               (1 << 5)           // Interrupt flag for capture channel 1 event.

/* TMR32B0TCR - address 0x4001 4004 and TMR32B1TCR - address 0x4001 8004 */
#define TMR32B0TCR_CEN                 (1 << 0)           // When one, the Timer Counter and Prescale Counter are 0 enabled for counting. When zero, the counters are disabled.
#define TMR32B0TCR_CRST                (1 << 1)           // When one, the Timer Counter and the Prescale Counter 0 are synchronously reset on the next positive edge of PCLK. The counters remain reset until TCR[1] is returned to zero.

/* TMR32B0TC, address 0x4001 4008 and TMR32B1TC 0x4001 8008 */
#define TMR32B0TC_TC_MASK              0xFFFFFFFF         // Timer counter value.
#define TMR32B0TC_TC_SHIFT             0                 

/* TMR32B0PR, address 0x4001 400C and TMR32B1PR 0x4001 800C */
#define TMR32B0PR_PR_MASK              0xFFFFFFFF         // Prescale value.
#define TMR32B0PR_PR_SHIFT             0                 

/* TMR32B0PC, address 0x4001 4010 and TMR32B1PC 0x4001 8010 */
#define TMR32B0PC_PC_MASK              0xFFFFFFFF         // Prescale counter value.
#define TMR32B0PC_PC_SHIFT             0                 

/* TMR32B0MCR - address 0x4001 4014 and TMR32B1MCR - address 0x4001 8014 */
#define TMR32B0MCR_MR0I                (1 << 0)           // Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
#define TMR32B0MCR_MR0R                (1 << 1)           // Reset on MR0: the TC will be reset if MR0 matches it.
#define TMR32B0MCR_MR0S                (1 << 2)           // Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches 0 the TC.
#define TMR32B0MCR_MR1I                (1 << 3)           // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.
#define TMR32B0MCR_MR1R                (1 << 4)           // Reset on MR1: the TC will be reset if MR1 matches it.
#define TMR32B0MCR_MR1S                (1 << 5)           // Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches 0 the TC.
#define TMR32B0MCR_MR2I                (1 << 6)           // Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
#define TMR32B0MCR_MR2R                (1 << 7)           // Reset on MR2: the TC will be reset if MR2 matches it.
#define TMR32B0MCR_MR2S                (1 << 8)           // Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches 0 the TC.
#define TMR32B0MCR_MR3I                (1 << 9)           // Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
#define TMR32B0MCR_MR3R                (1 << 10)          // Reset on MR3: the TC will be reset if MR3 matches it.
#define TMR32B0MCR_MR3S                (1 << 11)          // Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches 0 the TC.

/* TMR32B0MR0 to 3, addresses 0x4001 4018 to 24 and TMR32B1MR0 to 3, addresses 0x4001 8018 to 24 */
#define TMR32B0MRn_MATCH_MASK          0xFFFFFFFF         // Timer counter match value.
#define TMR32B0MRn_MATCH_SHIFT         0                 

/* TMR32B0CCR - address 0x4001 4028 and TMR32B1CCR - address 0x4001 8028 */
#define TMR32B0CCR_CAP0RE              (1 << 0)           // Capture on CT32Bn_CAP0 rising edge: a sequence of 0 then 1 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP0FE              (1 << 1)           // Capture on CT32Bn_CAP0 falling edge: a sequence of 1 then 0 on CT32Bn_CAP0 will 0 cause CR0 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP0I               (1 << 2)           // Interrupt on CT32Bn_CAP0 event: a CR0 load due to a CT32Bn_CAP0 event will generate an interrupt.
#define TMR32B0CCR_CAP1RE              (1 << 3)           // Capture on CT32Bn_CAP1 rising edge: a sequence of 0 then 1 on CT32Bn_CAP1 will cause CR1 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP1FE              (1 << 4)           // Capture on CT32Bn_CAP1 falling edge: a sequence of 1 then 0 on CT32Bn_CAP1 will 0 cause CR1 to be loaded with the contents of TC.
#define TMR32B0CCR_CAP1I               (1 << 5)           // Interrupt on CT32Bn_CAP1 event: a CR1 load due to a CT32Bn_CAP1 event will generate an interrupt.

/* TMR32B0EMR - address 0x4001 403C and TMR32B1EMR - address0x4001 803C */
#define TMR32B0EMR_EM0                 (1 << 0)           // External Match 0. This bit reflects the state of output CT32Bn_MAT0, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR0, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[5:4] control the functionality of this output. This bit is driven to the CT32B0_MAT0/CT16B1_MAT0 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM1                 (1 << 1)           // External Match 1. This bit reflects the state of output CT32Bn_MAT1, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR1, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[7:6] control the functionality of this output. This bit is driven to the CT32B0_MAT1/CT16B1_MAT1 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM2                 (1 << 2)           // External Match 2. This bit reflects the state of output CT32Bn_MAT2, whether or not this 0 output is connected to its pin. When a match occurs between the TC and MR2, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[9:8] control the functionality of this output. This bit is driven to the CT32B0_MAT2/CT16B1_MAT2 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EM3                 (1 << 3)           // External Match 3. This bit reflects the state of output CT32Bn_MAT3, whether or not this output is connected to its pin. When a match occurs between the TC and MR3, this bit can either toggle, go LOW, go HIGH, or do nothing. Bits EMR[11:10] control the functionality of this output. This bit is driven to the CT32B0_MAT3/CT16B1_MAT3 pins if the match function is selected in the IOCON registers (0 = LOW, 1 = HIGH).
#define TMR32B0EMR_EMC0_MASK           0x0030             // External Match Control 0. Determines the functionality of External Match 0.
#define TMR32B0EMR_EMC0_SHIFT          4                 
#define TMR32B0EMR_EMC1_MASK           0x00C0             // External Match Control 1. Determines the functionality of External Match 1.
#define TMR32B0EMR_EMC1_SHIFT          6                 
#define TMR32B0EMR_EMC2_MASK           0x0300             // External Match Control 2. Determines the functionality of External Match 2.
#define TMR32B0EMR_EMC2_SHIFT          8                 
#define TMR32B0EMR_EMC3_MASK           0x0C00             // External Match Control 3. Determines the functionality of External Match 3.
#define TMR32B0EMR_EMC3_SHIFT          10                

/* TMR32B0CTCR - address 0x4001 4070 and TMR32B1TCR - address 0x4001 8070 */
#define TMR32B0CTCR_CTM_MASK           0x0003             // Counter/Timer Mode. This field selects which rising PCLK edges can increment Timer's Prescale Counter (PC), or clear PC and increment Timer Counter (TC). Timer Mode: every rising PCLK edge
#define TMR32B0CTCR_CTM_SHIFT          0                 
#define TMR32B0CTCR_CIS_MASK           0x000C             // Count Input Select. When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking:
#define TMR32B0CTCR_CIS_SHIFT          2                 
#define TMR32B0CTCR_ENCC               (1 << 4)           // Setting this bit to one enables clearing of the timer and the prescaler when the capture-edge event specified in bits 7:5 occurs.
#define TMR32B0CTCR_SELCC_MASK         0x00E0             // When bit 4 is one, these bits select which capture input edge 0 will cause the timer and prescaler to be cleared. These bits have no effect when bit 4 is zero.
#define TMR32B0CTCR_SELCC_SHIFT        5                 

/* TMR32B0PWMC - 0x4001 4074 and TMR32B1PWMC - 0x4001 8074 */
#define TMR32B0PWMC_PWMEN0             (1 << 0)           // PWM channel 0 enable
#define TMR32B0PWMC_PWMEN1             (1 << 1)           // PWM channel 1 enable
#define TMR32B0PWMC_PWMEN2             (1 << 2)           // PWM channel 2 enable
#define TMR32B0PWMC_PWMEN3             (1 << 3)           // PWM channel 3 enable Note: It is recommended to use match channel 3 to set the PWM cycle.

/* WDMOD - 0x4000 4000 */
#define WDMOD_WDEN                     (1 << 0)           // Watchdog enable bit. This bit is Set Only. Remark: Setting this bit to one also locks the watchdog clock source. Once the watchdog timer is enabled, the watchdog timer clock source cannot be changed. If the watchdog timer is needed in Deep-sleep mode, the watchdog clock source must be changed to the watchdog oscillator before setting this bit to one.
#define WDMOD_WDRESET                  (1 << 1)           // Watchdog reset enable bit. This bit is Set Only.
#define WDMOD_WDTOF                    (1 << 2)           // Watchdog time-out flag. Set when the watchdog timer times out, by a feed error, or by events associated with WDPROTECT, cleared by software. Causes a chip reset if WDRESET = 1.
#define WDMOD_WDINT                    (1 << 3)           // Watchdog interrupt flag. Set when the timer reaches the value in WDWARNINT. Cleared by software.
#define WDMOD_WDPROTECT                (1 << 4)           // Watchdog update mode. This bit is Set Only.

/* WDTC - 0x4000 4004 */
#define WDTC_COUNT_MASK                0xFFFFFF           // Watchdog time-out interval.
#define WDTC_COUNT_SHIFT               0                 

/* WDFEED - 0x4000 4008 */
#define WDFEED_FEED_MASK               0x00FF             // Feed value should be 0xAA followed by 0x55.
#define WDFEED_FEED_SHIFT              0                 

/* WDTV - 0x4000 400C */
#define WDTV_COUNT_MASK                0xFFFFFF           // Counter timer value.
#define WDTV_COUNT_SHIFT               0                 

/* WDWARNINT - 0x4000 4014 */
#define WDWARNINT_WARNINT_MASK         0x03FF             // Watchdog warning interrupt compare value.
#define WDWARNINT_WARNINT_SHIFT        0                 

/* WDWINDOW - 0x4000 4018 */
#define WDWINDOW_WINDOW_MASK           0xFFFFFF           // Watchdog window value.
#define WDWINDOW_WINDOW_SHIFT          0                 

/* WDMOD - address 0x4000 4000 */
#define WDMOD_WDEN                     (1 << 0)           // WDEN Watchdog enable bit (Set Only). When 1, the watchdog timer is running. Remark: Setting this bit to one also locks the watchdog clock source. Once the watchdog timer is enabled, the watchdog timer clock source cannot be changed. If the watchdog timer is needed in Deep-sleep mode, the watchdog clock source must be changed to the watchdog oscillator before setting this bit to one. The clock source lock feature is not available on all parts, see Section 23.1).
#define WDMOD_WDRESET_WDRESET          (1 << 1)           // Watchdog reset enable bit (Set Only). When 1, og time-out will cause a chip reset.
#define WDMOD_WDTOF                    (1 << 2)           // WDTOF Watchdog time-out flag. Set when the watchdog
#define WDMOD_WDINT                    (1 << 3)           // WDINT Watchdog interrupt flag (Read Only, not clearable by software).

/* WDTC - address 0x4000 4004 */
#define WDTC_COUNT_MASK                0xFFFFFF           // Watchdog time-out interval.
#define WDTC_COUNT_SHIFT               0                 

/* WDFEED - address 0x4000 4008 */
#define WDFEED_FEED_MASK               0x00FF             // Feed value should be 0xAA followed by 0x55.
#define WDFEED_FEED_SHIFT              0                 

/* WDTV - address 0x4000 000C */
#define WDTV_COUNT_MASK                0xFFFFFF           // Counter timer value.
#define WDTV_COUNT_SHIFT               0                 

/* SYST_CSR - 0xE000 E010 */
#define SYST_CSR_ENABLE                (1 << 0)           // System Tick counter enable. When 1, the counter is enabled. When 0, the counter is disabled.
#define SYST_CSR_TICKINT               (1 << 1)           // System Tick interrupt enable. When 1, the System Tick interrupt 0 is enabled. When 0, the System Tick interrupt is disabled. When enabled, the interrupt is generated when the System Tick counter counts down to 0.
#define SYST_CSR_CLKSOURCE             (1 << 2)           // System Tick clock source selection. When 1, the system clock (CPU) clock is selected. When 0, the system clock/2 is selected as the reference clock.
#define SYST_CSR_COUNTFLAG             (1 << 16)          // Returns 1 if the SysTick timer counted to 0 since the last read of this register. Reserved, user software should not write ones to reserved bits. The value read from a reserved bit is not defined.

/* SYST_RVR - 0xE000 E014 */
#define SYST_RVR_RELOAD_MASK           0xFFFFFF           // This is the value that is loaded into the System Tick counter when it 0 counts down to 0.
#define SYST_RVR_RELOAD_SHIFT          0                 

/* SYST_CVR - 0xE000 E018 */
#define SYST_CVR_CURRENT_MASK          0xFFFFFF           // Reading this register returns the current value of the System Tick counter. Writing any value clears the System Tick counter and the COUNTFLAG bit in STCTRL.
#define SYST_CVR_CURRENT_SHIFT         0                 

/* SYST_CALIB - 0xE000 E01C */
#define SYST_CALIB_TENMS_MASK          0xFFFFFF           // See Table 461.
#define SYST_CALIB_TENMS_SHIFT         0                 
#define SYST_CALIB_SKEW                (1 << 30)          // See Table 461.
#define SYST_CALIB_NOREF               (1 << 31)          // See Table 461.

/* AD0CR - address 0x4001 C000 */
#define AD0CR_SEL_MASK                 0x00FF             // Selects which of the AD7:0 pins is (are) to be sampled and converted. Bit 0 selects Pin           0x00 AD0, bit 1 selects pin AD1,..., and bit 7 selects pin AD7. In software-controlled mode (BURST = 0), only one channel can be selected, i.e. only one of these bits should be 1. In hardware scan mode (BURST = 1), any numbers of channels can be selected, i.e any or all bits can be set to 1. If all bits are set to 0, channel 0 is selected automatically (SEL = 0x01).
#define AD0CR_SEL_SHIFT                0                 
#define AD0CR_CLKDIV_MASK              0xFF00             // The APB clock (PCLK) is divided by CLKDIV +1 to produce the clock for the ADC, which 0 should be less than or equal to 4.5 MHz. Typically, software should program the smallest value in this field that yields a clock of 4.5 MHz or slightly less, but in certain cases (such as a high-impedance analog source) a slower clock may be desirable.
#define AD0CR_CLKDIV_SHIFT             8                 
#define AD0CR_BURST                    (1 << 16)          // Burst mode Remark: If BURST is set to 1, the ADGINTEN bit in the AD0INTEN register (Table 365) must be set to 0.
#define AD0CR_CLKS_MASK                0xE0000            // This field selects the number of clocks used for each conversion in Burst mode, and the number of bits of accuracy of the result in the LS bits of ADDR, between 11 clocks (10 bits) and 4 clocks (3 bits).
#define AD0CR_CLKS_SHIFT               17                
#define AD0CR_START_MASK               0x7000000          // When the BURST bit is 0, these bits control whether and when an A/D conversion is started:
#define AD0CR_START_SHIFT              24                
#define AD0CR_EDGE                     (1 << 27)          // This bit is significant only when the START field contains 010-111. In these cases:

/* AD0GDR - address 0x4001 C004 */
#define AD0GDR_V_VREF_MASK             0xFFC0             // When DONE is 1, this field contains a binary fraction representing X the voltage on the ADn pin selected by the SEL field, divided by the voltage on the VDD pin. Zero in the field indicates that the voltage on the ADn pin was less than, equal to, or close to that on VSS, while 0x3FF indicates that the voltage on ADn was close to, equal to, or greater than that on VREF.
#define AD0GDR_V_VREF_SHIFT            6                 
#define AD0GDR_CHN_MASK                0x7000000          // These bits contain the channel from which the result bits V_VREF X were converted.
#define AD0GDR_CHN_SHIFT               24                
#define AD0GDR_OVERRUN                 (1 << 30)          // This bit is 1 in burst mode if the results of one or more conversions 0 was (were) lost and overwritten before the conversion that produced the result in the V_VREF bits.
#define AD0GDR_DONE                    (1 << 31)          // This bit is set to 1 when an A/D conversion completes. It is cleared 0 when this register is read and when the ADCR is written. If the ADCR is written while a conversion is still in progress, this bit is set and a new conversion is started.

/* AD0INTEN - address 0x4001 C00C */
#define AD0INTEN_ADINTEN_MASK          0x00FF             // These bits allow control over which A/D channels generate             0x00 interrupts for conversion completion. When bit 0 is one, completion of a conversion on A/D channel 0 will generate an interrupt, when bit 1 is one, completion of a conversion on A/D channel 1 will generate an interrupt, etc.
#define AD0INTEN_ADINTEN_SHIFT         0                 
#define AD0INTEN_ADGINTEN              (1 << 8)           // When 1, enables the global DONE flag in ADDR to generate an interrupt. When 0, only the individual A/D channels enabled by ADINTEN 7:0 will generate interrupts. Remark: This bit must be set to 0 in burst mode (BURST = 1 in the AD0CR register). Reserved. Unused, always 0.

/* AD0DR0 to AD0DR7 - addresses 0x4001 C010 to 0x4001 C02C */
#define AD0DRn_V_VREF_MASK             0xFFC0             // When DONE is 1, this field contains a binary fraction representing the NA voltage on the ADn pin, divided by the voltage on the VREF pin. Zero in the field indicates that the voltage on the ADn pin was less than, equal to, or close to that on VREF, while 0x3FF indicates that the voltage on AD input was close to, equal to, or greater than that on VREF. Reserved.
#define AD0DRn_V_VREF_SHIFT            6                 
#define AD0DRn_OVERRUN                 (1 << 30)          // This bit is 1 in burst mode if the results of one or more conversions was (were) lost and overwritten before the conversion that produced the result in the V_VREF bits.This bit is cleared by reading this register.
#define AD0DRn_DONE                    (1 << 31)          // This bit is set to 1 when an A/D conversion completes. It is cleared when this register is read.

/* AD0STAT - address 0x4001 C030 */
#define AD0STAT_DONE_MASK              0x00FF             // These bits mirror the DONE status flags that appear in the result register for each A/D channel n.
#define AD0STAT_DONE_SHIFT             0                 
#define AD0STAT_OVERRUN_MASK           0xFF00             // These bits mirror the OVERRRUN status flags that appear in the result register for each A/D channel n. Reading ADSTAT allows checking the status of all A/D channels simultaneously.
#define AD0STAT_OVERRUN_SHIFT          8                 
#define AD0STAT_ADINT                  (1 << 16)          // This bit is the A/D interrupt flag. It is one when any of the individual A/D channel Done flags is asserted and enabled to contribute to the A/D interrupt via the ADINTEN register. Reserved. Unused, always 0.

/* FLASHCFG, address 0x4003 C010 */
#define FLASHCFG_FLASHTIM_MASK         0x0003             // Flash memory access time. FLASHTIM +1 is equal to the number of system clocks used for flash access.
#define FLASHCFG_FLASHTIM_SHIFT        0                 

/* FMSSTART - 0x4003 C020 */
#define FMSSTART_START_MASK            0x1FFFF            // Signature generation start address (corresponds to AHB byte address bits[20:4]).
#define FMSSTART_START_SHIFT           0                 

/* FMSSTOP - 0x4003 C024 */
#define FMSSTOP_STOP_MASK              0x1FFFF            // BIST stop address divided by 16 (corresponds to AHB byte address [20:4]).
#define FMSSTOP_STOP_SHIFT             0                 
#define FMSSTOP_SIG_START              (1 << 17)          // Start control bit for signature generation.

/* FMSTAT - 0x4003 CFE0 */
#define FMSTAT_SIG_DONE                (1 << 2)           // When 1, a previously started signature generation has           0 completed. See FMSTATCLR register description for clearing this flag.

/* FMSTATCLR - 0x0x4003 CFE8 */
#define FMSTATCLR_SIG_DONE_CLR         (1 << 2)           // Writing a 1 to this bits clears the signature generation completion flag (SIG_DONE) in the FMSTAT register.


#endif
