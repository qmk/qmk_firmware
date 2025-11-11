#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for ReloadedSplit66 V1 board with STMicroelectronics STM32L443CC MCU.
 */

/*
 * Board identifier.
 */
#define BOARD_RESPLIT66_V1
#define BOARD_NAME                  "ReloadedSplit66 V1"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32L443xx

/*
 * IO pins assignments.
 */
#define GPIOA_COL0                  0U
#define GPIOA_COL1                  1U
#define GPIOA_COL2                  2U
#define GPIOA_COL3                  3U
#define GPIOA_COL4                  4U
#define GPIOA_COL5                  5U
#define GPIOA_COL6                  6U
#define GPIOA_PIN7                  7U
#define GPIOA_PIN8                  8U
#define GPIOA_UART1_TX              9U
#define GPIOA_UART1_RX              10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_SIDE_IRQ              15U

#define GPIOB_ROW0                  0U
#define GPIOB_ROW1                  1U
#define GPIOB_ROW2                  2U
#define GPIOB_TRACESWO              3U
#define GPIOB_ROW3                  4U
#define GPIOB_ROW4                  5U
#define GPIOB_SIDE_SCL              6U
#define GPIOB_SIDE_SDA              7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_OLED_SCL              10U
#define GPIOB_OLED_SDA              11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_RGB_PWR               14U
#define GPIOB_RGB_MOSI              15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_LED1                  13U
#define GPIOC_LED2                  14U
#define GPIOC_LED3                  15U

#define GPIOH_OSC_IN                0U
#define GPIOH_SIDE_SEL              1U
#define GPIOH_PIN2                  2U
#define GPIOH_BOOT_SW               3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_COL0                   PAL_LINE(GPIOA, 0U)
#define LINE_COL1                   PAL_LINE(GPIOA, 1U)
#define LINE_COL2                   PAL_LINE(GPIOA, 2U)
#define LINE_COL3                   PAL_LINE(GPIOA, 3U)
#define LINE_COL4                   PAL_LINE(GPIOA, 4U)
#define LINE_COL5                   PAL_LINE(GPIOA, 5U)
#define LINE_COL6                   PAL_LINE(GPIOA, 6U)
#define LINE_SIDE_IRQ               PAL_LINE(GPIOA, 15U)
#define LINE_ROW0                   PAL_LINE(GPIOB, 0U)
#define LINE_ROW1                   PAL_LINE(GPIOB, 1U)
#define LINE_ROW2                   PAL_LINE(GPIOB, 2U)
#define LINE_ROW3                   PAL_LINE(GPIOB, 4U)
#define LINE_ROW4                   PAL_LINE(GPIOB, 5U)
#define LINE_SIDE_SCL               PAL_LINE(GPIOB, 6U)
#define LINE_SIDE_SDA               PAL_LINE(GPIOB, 7U)
#define LINE_OLED_SCL               PAL_LINE(GPIOB, 10U)
#define LINE_OLED_SDA               PAL_LINE(GPIOB, 11U)
#define LINE_RGB_PWR                PAL_LINE(GPIOB, 14U)
#define LINE_RGB_MOSI               PAL_LINE(GPIOB, 15U)
#define LINE_LED1                   PAL_LINE(GPIOC, 13U)
#define LINE_LED2                   PAL_LINE(GPIOC, 14U)
#define LINE_LED3                   PAL_LINE(GPIOC, 15U)
#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_SIDE_SEL               PAL_LINE(GPIOH, 1U)
#define LINE_BOOT_SW                PAL_LINE(GPIOH, 3U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))
#define PIN_ASCR_DISABLED(n)        (0U << (n))
#define PIN_ASCR_ENABLED(n)         (1U << (n))
#define PIN_LOCKR_DISABLED(n)       (0U << (n))
#define PIN_LOCKR_ENABLED(n)        (1U << (n))

/*
 * GPIOA setup:
 *
 * PA0  - COL0                (input pullup).
 * PA1  - COL1                (input pullup).
 * PA2  - COL2                (input pullup).
 * PA3  - COL3                (input pullup).
 * PA4  - COL4                (input pullup).
 * PA5  - COL5                (input pullup).
 * PA6  - COL6                (input pullup).
 * PA7  - PIN7                (analog).
 * PA8  - PIN8                (analog).
 * PA9  - UART1_TX            (alternate 7).
 * PA10 - UART1_RX            (alternate 7).
 * PA11 - USB_DM              (alternate 10).
 * PA12 - USB_DP              (alternate 10).
 * PA13 - SWDIO               (alternate 0).
 * PA14 - SWCLK               (alternate 0).
 * PA15 - SIDE_IRQ            (output pushpull low).
 */
#define VAL_GPIOA_MODER       (PIN_MODE_INPUT(GPIOA_COL0) |			\
							   PIN_MODE_INPUT(GPIOA_COL1) |			\
							   PIN_MODE_INPUT(GPIOA_COL2) |			\
							   PIN_MODE_INPUT(GPIOA_COL3) |			\
							   PIN_MODE_INPUT(GPIOA_COL4) |			\
							   PIN_MODE_INPUT(GPIOA_COL5) |			\
							   PIN_MODE_INPUT(GPIOA_COL6) |			\
							   PIN_MODE_ANALOG(GPIOA_PIN7) |		\
							   PIN_MODE_ANALOG(GPIOA_PIN8) |		\
							   PIN_MODE_ALTERNATE(GPIOA_UART1_TX) | \
							   PIN_MODE_ALTERNATE(GPIOA_UART1_RX) | \
							   PIN_MODE_ALTERNATE(GPIOA_USB_DM) |	\
							   PIN_MODE_ALTERNATE(GPIOA_USB_DP) |	\
							   PIN_MODE_ALTERNATE(GPIOA_SWDIO) |	\
							   PIN_MODE_ALTERNATE(GPIOA_SWCLK) |	\
							   PIN_MODE_OUTPUT(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_OTYPER      (PIN_OTYPE_PUSHPULL(GPIOA_COL0) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL1) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL2) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL3) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL4) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL5) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_COL6) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_PIN7) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |		\
							   PIN_OTYPE_PUSHPULL(GPIOA_UART1_TX) | \
							   PIN_OTYPE_PUSHPULL(GPIOA_UART1_RX) | \
							   PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |	\
							   PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |	\
							   PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |	\
							   PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |	\
							   PIN_OTYPE_PUSHPULL(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_OSPEEDR     (PIN_OSPEED_VERYLOW(GPIOA_COL0) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL1) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL2) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL3) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL4) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL5) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_COL6) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_PIN7) |		\
							   PIN_OSPEED_VERYLOW(GPIOA_PIN8) |		\
							   PIN_OSPEED_HIGH(GPIOA_UART1_TX) |	\
							   PIN_OSPEED_HIGH(GPIOA_UART1_RX) |	\
							   PIN_OSPEED_HIGH(GPIOA_USB_DM) |		\
							   PIN_OSPEED_HIGH(GPIOA_USB_DP) |		\
							   PIN_OSPEED_HIGH(GPIOA_SWDIO) |		\
							   PIN_OSPEED_HIGH(GPIOA_SWCLK) |		\
							   PIN_OSPEED_HIGH(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_PUPDR       (PIN_PUPDR_PULLUP(GPIOA_COL0) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL1) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL2) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL3) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL4) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL5) |		\
							   PIN_PUPDR_PULLUP(GPIOA_COL6) |		\
							   PIN_PUPDR_FLOATING(GPIOA_PIN7) |		\
							   PIN_PUPDR_FLOATING(GPIOA_PIN8) |		\
							   PIN_PUPDR_FLOATING(GPIOA_UART1_TX) | \
							   PIN_PUPDR_FLOATING(GPIOA_UART1_RX) | \
							   PIN_PUPDR_FLOATING(GPIOA_USB_DM) |	\
							   PIN_PUPDR_FLOATING(GPIOA_USB_DP) |	\
							   PIN_PUPDR_PULLUP(GPIOA_SWDIO) |		\
							   PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |	\
							   PIN_PUPDR_FLOATING(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_ODR         (PIN_ODR_LOW(GPIOA_COL0) |		\
							   PIN_ODR_LOW(GPIOA_COL1) |		\
							   PIN_ODR_LOW(GPIOA_COL2) |		\
							   PIN_ODR_LOW(GPIOA_COL3) |		\
							   PIN_ODR_LOW(GPIOA_COL4) |		\
							   PIN_ODR_LOW(GPIOA_COL5) |		\
							   PIN_ODR_LOW(GPIOA_COL6) |		\
							   PIN_ODR_LOW(GPIOA_PIN7) |		\
							   PIN_ODR_LOW(GPIOA_PIN8) |		\
							   PIN_ODR_LOW(GPIOA_UART1_TX) |	\
							   PIN_ODR_LOW(GPIOA_UART1_RX) |	\
							   PIN_ODR_LOW(GPIOA_USB_DM) |		\
							   PIN_ODR_LOW(GPIOA_USB_DP) |		\
							   PIN_ODR_LOW(GPIOA_SWDIO) |		\
							   PIN_ODR_LOW(GPIOA_SWCLK) |		\
							   PIN_ODR_LOW(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_AFRL        (PIN_AFIO_AF(GPIOA_COL0, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL1, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL2, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL3, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL4, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL5, 0U) |	\
							   PIN_AFIO_AF(GPIOA_COL6, 0U) |	\
							   PIN_AFIO_AF(GPIOA_PIN7, 0U))
#define VAL_GPIOA_AFRH        (PIN_AFIO_AF(GPIOA_PIN8, 0U) |		\
							   PIN_AFIO_AF(GPIOA_UART1_TX, 7U) |	\
							   PIN_AFIO_AF(GPIOA_UART1_RX, 7U) |	\
							   PIN_AFIO_AF(GPIOA_USB_DM, 10U) |		\
							   PIN_AFIO_AF(GPIOA_USB_DP, 10U) |		\
							   PIN_AFIO_AF(GPIOA_SWDIO, 0U) |		\
							   PIN_AFIO_AF(GPIOA_SWCLK, 0U) |		\
							   PIN_AFIO_AF(GPIOA_SIDE_IRQ, 0U))
#define VAL_GPIOA_ASCR        (PIN_ASCR_DISABLED(GPIOA_COL0) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL1) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL2) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL3) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL4) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL5) |		\
							   PIN_ASCR_DISABLED(GPIOA_COL6) |		\
							   PIN_ASCR_DISABLED(GPIOA_PIN7) |		\
							   PIN_ASCR_DISABLED(GPIOA_PIN8) |		\
							   PIN_ASCR_DISABLED(GPIOA_UART1_TX) |	\
							   PIN_ASCR_DISABLED(GPIOA_UART1_RX) |	\
							   PIN_ASCR_DISABLED(GPIOA_USB_DM) |	\
							   PIN_ASCR_DISABLED(GPIOA_USB_DP) |	\
							   PIN_ASCR_DISABLED(GPIOA_SWDIO) |		\
							   PIN_ASCR_DISABLED(GPIOA_SWCLK) |		\
							   PIN_ASCR_DISABLED(GPIOA_SIDE_IRQ))
#define VAL_GPIOA_LOCKR       (PIN_LOCKR_DISABLED(GPIOA_COL0) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL1) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL2) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL3) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL4) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL5) |		\
							   PIN_LOCKR_DISABLED(GPIOA_COL6) |		\
							   PIN_LOCKR_DISABLED(GPIOA_PIN7) |		\
							   PIN_LOCKR_DISABLED(GPIOA_PIN8) |		\
							   PIN_LOCKR_DISABLED(GPIOA_UART1_TX) | \
							   PIN_LOCKR_DISABLED(GPIOA_UART1_RX) | \
							   PIN_LOCKR_DISABLED(GPIOA_USB_DM) |	\
							   PIN_LOCKR_DISABLED(GPIOA_USB_DP) |	\
							   PIN_LOCKR_DISABLED(GPIOA_SWDIO) |	\
							   PIN_LOCKR_DISABLED(GPIOA_SWCLK) |	\
							   PIN_LOCKR_DISABLED(GPIOA_SIDE_IRQ))

/*
 * GPIOB setup:
 *
 * PB0  - ROW0                (output pushpull high).
 * PB1  - ROW1                (output pushpull high).
 * PB2  - ROW2                (output pushpull high).
 * PB3  - TRACESWO            (alternate 0).
 * PB4  - ROW3                (output pushpull high).
 * PB5  - ROW4                (output pushpull high).
 * PB6  - SIDE_SCL            (alternate 4).
 * PB7  - SIDE_SDA            (alternate 4).
 * PB8  - PIN8                (analog).
 * PB9  - PIN9                (analog).
 * PB10 - OLED_SCL            (alternate 4).
 * PB11 - OLED_SDA            (alternate 4).
 * PB12 - PIN12               (analog).
 * PB13 - PIN13               (analog).
 * PB14 - RGB_PWR             (output pushpull).
 * PB15 - RGB_MOSI            (alternate 5).
 */
#define VAL_GPIOB_MODER       (PIN_MODE_OUTPUT(GPIOB_ROW0) |		\
							   PIN_MODE_OUTPUT(GPIOB_ROW1) |		\
							   PIN_MODE_OUTPUT(GPIOB_ROW2) |		\
							   PIN_MODE_ALTERNATE(GPIOB_TRACESWO) |	\
							   PIN_MODE_OUTPUT(GPIOB_ROW3) |		\
							   PIN_MODE_OUTPUT(GPIOB_ROW4) |		\
							   PIN_MODE_ALTERNATE(GPIOB_SIDE_SCL) |	\
							   PIN_MODE_ALTERNATE(GPIOB_SIDE_SDA) |	\
							   PIN_MODE_ANALOG(GPIOB_PIN8) |		\
							   PIN_MODE_ANALOG(GPIOB_PIN9) |		\
							   PIN_MODE_ALTERNATE(GPIOB_OLED_SCL) |	\
							   PIN_MODE_ALTERNATE(GPIOB_OLED_SDA) |	\
							   PIN_MODE_ANALOG(GPIOB_PIN12) |		\
							   PIN_MODE_ANALOG(GPIOB_PIN13) |		\
							   PIN_MODE_OUTPUT(GPIOB_RGB_PWR) |		\
							   PIN_MODE_ALTERNATE(GPIOB_RGB_MOSI))
#define VAL_GPIOB_OTYPER      (PIN_OTYPE_PUSHPULL(GPIOB_ROW0) |		\
							   PIN_OTYPE_PUSHPULL(GPIOB_ROW1) |		\
							   PIN_OTYPE_PUSHPULL(GPIOB_ROW2) |		\
							   PIN_OTYPE_PUSHPULL(GPIOB_TRACESWO) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_ROW3) |		\
							   PIN_OTYPE_PUSHPULL(GPIOB_ROW4) |		\
							   PIN_OTYPE_OPENDRAIN(GPIOB_SIDE_SCL) |	\
							   PIN_OTYPE_OPENDRAIN(GPIOB_SIDE_SDA) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |		\
							   PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |		\
							   PIN_OTYPE_OPENDRAIN(GPIOB_OLED_SCL) |	\
							   PIN_OTYPE_OPENDRAIN(GPIOB_OLED_SDA) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_RGB_PWR) |	\
							   PIN_OTYPE_PUSHPULL(GPIOB_RGB_MOSI))
#define VAL_GPIOB_OSPEEDR     (PIN_OSPEED_HIGH(GPIOB_ROW0) |		\
							   PIN_OSPEED_HIGH(GPIOB_ROW1) |		\
							   PIN_OSPEED_HIGH(GPIOB_ROW2) |		\
							   PIN_OSPEED_HIGH(GPIOB_TRACESWO) |	\
							   PIN_OSPEED_HIGH(GPIOB_ROW3) |		\
							   PIN_OSPEED_HIGH(GPIOB_ROW4) |		\
							   PIN_OSPEED_HIGH(GPIOB_SIDE_SCL) |	\
							   PIN_OSPEED_HIGH(GPIOB_SIDE_SDA) |	\
							   PIN_OSPEED_VERYLOW(GPIOB_PIN8) |		\
							   PIN_OSPEED_VERYLOW(GPIOB_PIN9) |		\
							   PIN_OSPEED_HIGH(GPIOB_OLED_SCL) |	\
							   PIN_OSPEED_HIGH(GPIOB_OLED_SDA) |	\
							   PIN_OSPEED_VERYLOW(GPIOB_PIN12) |	\
							   PIN_OSPEED_VERYLOW(GPIOB_PIN13) |	\
							   PIN_OSPEED_VERYLOW(GPIOB_RGB_PWR) |	\
							   PIN_OSPEED_HIGH(GPIOB_RGB_MOSI))
#define VAL_GPIOB_PUPDR       (PIN_PUPDR_FLOATING(GPIOB_ROW0) |		\
							   PIN_PUPDR_FLOATING(GPIOB_ROW1) |		\
							   PIN_PUPDR_FLOATING(GPIOB_ROW2) |		\
							   PIN_PUPDR_FLOATING(GPIOB_TRACESWO) |	\
							   PIN_PUPDR_FLOATING(GPIOB_ROW3) |		\
							   PIN_PUPDR_FLOATING(GPIOB_ROW4) |		\
							   PIN_PUPDR_FLOATING(GPIOB_SIDE_SCL) |	\
							   PIN_PUPDR_FLOATING(GPIOB_SIDE_SDA) |	\
							   PIN_PUPDR_FLOATING(GPIOB_PIN8) |		\
							   PIN_PUPDR_FLOATING(GPIOB_PIN9) |		\
							   PIN_PUPDR_FLOATING(GPIOB_OLED_SCL) |	\
							   PIN_PUPDR_FLOATING(GPIOB_OLED_SDA) |	\
							   PIN_PUPDR_FLOATING(GPIOB_PIN12) |	\
							   PIN_PUPDR_FLOATING(GPIOB_PIN13) |	\
							   PIN_PUPDR_FLOATING(GPIOB_RGB_PWR) |	\
							   PIN_PUPDR_FLOATING(GPIOB_RGB_MOSI))
#define VAL_GPIOB_ODR         (PIN_ODR_HIGH(GPIOB_ROW0) |		\
							   PIN_ODR_HIGH(GPIOB_ROW1) |		\
							   PIN_ODR_HIGH(GPIOB_ROW2) |		\
							   PIN_ODR_LOW(GPIOB_TRACESWO) |	\
							   PIN_ODR_HIGH(GPIOB_ROW3) |		\
							   PIN_ODR_HIGH(GPIOB_ROW4) |		\
							   PIN_ODR_LOW(GPIOB_SIDE_SCL) |	\
							   PIN_ODR_LOW(GPIOB_SIDE_SDA) |	\
							   PIN_ODR_LOW(GPIOB_PIN8) |		\
							   PIN_ODR_LOW(GPIOB_PIN9) |		\
							   PIN_ODR_LOW(GPIOB_OLED_SCL) |	\
							   PIN_ODR_LOW(GPIOB_OLED_SDA)  |	\
							   PIN_ODR_LOW(GPIOB_PIN12) |		\
							   PIN_ODR_LOW(GPIOB_PIN12) |		\
							   PIN_ODR_LOW(GPIOB_RGB_PWR) |		\
							   PIN_ODR_LOW(GPIOB_RGB_MOSI))
#define VAL_GPIOB_AFRL        (PIN_AFIO_AF(GPIOB_ROW0, 0U) |        \
							   PIN_AFIO_AF(GPIOB_ROW1, 0U) |        \
							   PIN_AFIO_AF(GPIOB_ROW2, 0U) |		\
							   PIN_AFIO_AF(GPIOB_TRACESWO, 0U) |	\
							   PIN_AFIO_AF(GPIOB_ROW3, 0U) |		\
							   PIN_AFIO_AF(GPIOB_ROW4, 0U) |		\
							   PIN_AFIO_AF(GPIOB_SIDE_SCL, 4U) |	\
							   PIN_AFIO_AF(GPIOB_SIDE_SDA, 4U))
#define VAL_GPIOB_AFRH        (PIN_AFIO_AF(GPIOB_PIN8, 0U) |		\
							   PIN_AFIO_AF(GPIOB_PIN9, 0U) |		\
							   PIN_AFIO_AF(GPIOB_OLED_SCL, 4U) |	\
							   PIN_AFIO_AF(GPIOB_OLED_SDA, 4U) |	\
							   PIN_AFIO_AF(GPIOB_PIN12, 0U) |		\
							   PIN_AFIO_AF(GPIOB_PIN13, 0U) |		\
							   PIN_AFIO_AF(GPIOB_RGB_PWR, 0U) |		\
							   PIN_AFIO_AF(GPIOB_RGB_MOSI, 5U))
#define VAL_GPIOB_ASCR        (PIN_ASCR_DISABLED(GPIOB_ROW0) |      \
							   PIN_ASCR_DISABLED(GPIOB_ROW1) |      \
							   PIN_ASCR_DISABLED(GPIOB_ROW2) |		\
							   PIN_ASCR_DISABLED(GPIOB_TRACESWO) |	\
							   PIN_ASCR_DISABLED(GPIOB_ROW3) |		\
							   PIN_ASCR_DISABLED(GPIOB_ROW4) |		\
							   PIN_ASCR_DISABLED(GPIOB_SIDE_SCL) |	\
							   PIN_ASCR_DISABLED(GPIOB_SIDE_SDA) |	\
							   PIN_ASCR_DISABLED(GPIOB_PIN8) |		\
							   PIN_ASCR_DISABLED(GPIOB_PIN9) |		\
							   PIN_ASCR_DISABLED(GPIOB_OLED_SCL) |	\
							   PIN_ASCR_DISABLED(GPIOB_OLED_SDA) |	\
							   PIN_ASCR_DISABLED(GPIOB_PIN12) |		\
							   PIN_ASCR_DISABLED(GPIOB_PIN13) |		\
							   PIN_ASCR_DISABLED(GPIOB_RGB_PWR) |	\
							   PIN_ASCR_DISABLED(GPIOB_RGB_MOSI))
#define VAL_GPIOB_LOCKR       (PIN_LOCKR_DISABLED(GPIOB_ROW0) |		\
							   PIN_LOCKR_DISABLED(GPIOB_ROW1) |		\
							   PIN_LOCKR_DISABLED(GPIOB_ROW2) |		\
							   PIN_LOCKR_DISABLED(GPIOB_TRACESWO) |	\
							   PIN_LOCKR_DISABLED(GPIOB_ROW3) |		\
							   PIN_LOCKR_DISABLED(GPIOB_ROW4) |		\
							   PIN_LOCKR_DISABLED(GPIOB_SIDE_SCL) |	\
							   PIN_LOCKR_DISABLED(GPIOB_SIDE_SDA) |	\
							   PIN_LOCKR_DISABLED(GPIOB_PIN8) |		\
							   PIN_LOCKR_DISABLED(GPIOB_PIN9) |		\
							   PIN_LOCKR_DISABLED(GPIOB_OLED_SCL) |	\
							   PIN_LOCKR_DISABLED(GPIOB_OLED_SDA) |	\
							   PIN_LOCKR_DISABLED(GPIOB_PIN12) |	\
							   PIN_LOCKR_DISABLED(GPIOB_PIN13) |	\
							   PIN_LOCKR_DISABLED(GPIOB_RGB_PWR) |	\
							   PIN_LOCKR_DISABLED(GPIOB_RGB_MOSI))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                (analog).
 * PC1  - PIN1                (analog).
 * PC2  - PIN2                (analog).
 * PC3  - PIN3                (analog).
 * PC4  - PIN4                (analog).
 * PC5  - PIN5                (analog).
 * PC6  - PIN6                (analog).
 * PC7  - PIN7                (analog).
 * PC8  - PIN8                (analog).
 * PC9  - PIN9                (analog).
 * PC10 - PIN10               (analog).
 * PC11 - PIN11               (analog).
 * PC12 - PIN12               (analog).
 * PC13 - LED1                (output).
 * PC14 - LED2                (output).
 * PC15 - LED3                (output).
 */
#define VAL_GPIOC_MODER       (PIN_MODE_ANALOG(GPIOC_PIN0) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN1) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN2) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN3) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN4) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN5) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN6) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN7) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN8) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN9) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN10) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN11) |	\
							   PIN_MODE_ANALOG(GPIOC_PIN12) |	\
							   PIN_MODE_OUTPUT(GPIOC_LED1) |	\
							   PIN_MODE_OUTPUT(GPIOC_LED2) |	\
							   PIN_MODE_OUTPUT(GPIOC_LED3))
#define VAL_GPIOC_OTYPER      (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |	\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |	\
							   PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |	\
							   PIN_OTYPE_PUSHPULL(GPIOC_LED1) |		\
							   PIN_OTYPE_PUSHPULL(GPIOC_LED2) |     \
							   PIN_OTYPE_PUSHPULL(GPIOC_LED3))
#define VAL_GPIOC_OSPEEDR     (PIN_OSPEED_VERYLOW(GPIOC_PIN0) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN1) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN2) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN3) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN4) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN5) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN6) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN7) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN8) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN9) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN10) |	\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN11) |	\
							   PIN_OSPEED_VERYLOW(GPIOC_PIN12) |	\
							   PIN_OSPEED_VERYLOW(GPIOC_LED1) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_LED2) |		\
							   PIN_OSPEED_VERYLOW(GPIOC_LED3))
#define VAL_GPIOC_PUPDR       (PIN_PUPDR_FLOATING(GPIOC_PIN0) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN1) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN2) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN3) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN4) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN5) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN6) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN7) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN8) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN9) |		\
							   PIN_PUPDR_FLOATING(GPIOC_PIN10) |	\
							   PIN_PUPDR_FLOATING(GPIOC_PIN11) |	\
							   PIN_PUPDR_FLOATING(GPIOC_PIN12) |	\
							   PIN_PUPDR_FLOATING(GPIOC_LED1) |		\
							   PIN_PUPDR_FLOATING(GPIOC_LED2) |     \
							   PIN_PUPDR_FLOATING(GPIOC_LED3))
#define VAL_GPIOC_ODR         (PIN_ODR_LOW(GPIOC_PIN0) |	\
							   PIN_ODR_LOW(GPIOC_PIN1) |	\
							   PIN_ODR_LOW(GPIOC_PIN2) |	\
							   PIN_ODR_LOW(GPIOC_PIN3) |	\
							   PIN_ODR_LOW(GPIOC_PIN4) |	\
							   PIN_ODR_LOW(GPIOC_PIN5) |	\
							   PIN_ODR_LOW(GPIOC_PIN6) |	\
							   PIN_ODR_LOW(GPIOC_PIN7) |	\
							   PIN_ODR_LOW(GPIOC_PIN8) |	\
							   PIN_ODR_LOW(GPIOC_PIN9) |	\
							   PIN_ODR_LOW(GPIOC_PIN10) |	\
							   PIN_ODR_LOW(GPIOC_PIN11) |	\
							   PIN_ODR_LOW(GPIOC_PIN12) |	\
							   PIN_ODR_HIGH(GPIOC_LED1) |	\
							   PIN_ODR_HIGH(GPIOC_LED2) |	\
							   PIN_ODR_HIGH(GPIOC_LED3))
#define VAL_GPIOC_AFRL        (PIN_AFIO_AF(GPIOC_PIN0, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN1, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN2, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN3, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN4, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN5, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN6, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH        (PIN_AFIO_AF(GPIOC_PIN8, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN9, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN10, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN11, 0U) |	\
							   PIN_AFIO_AF(GPIOC_PIN12, 0U) |	\
							   PIN_AFIO_AF(GPIOC_LED1, 0U) |	\
							   PIN_AFIO_AF(GPIOC_LED2, 0U) |	\
							   PIN_AFIO_AF(GPIOC_LED3, 0U))
#define VAL_GPIOC_ASCR        (PIN_ASCR_DISABLED(GPIOC_PIN0) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN1) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN2) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN3) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN4) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN5) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN6) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN7) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN8) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN9) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN10) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN11) |	\
							   PIN_ASCR_DISABLED(GPIOC_PIN12) |	\
							   PIN_ASCR_DISABLED(GPIOC_LED1) |	\
							   PIN_ASCR_DISABLED(GPIOC_LED2) |	\
							   PIN_ASCR_DISABLED(GPIOC_LED3))
#define VAL_GPIOC_LOCKR       (PIN_LOCKR_DISABLED(GPIOC_PIN0) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN1) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN2) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN3) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN4) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN5) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN6) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN7) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN8) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN9) |		\
							   PIN_LOCKR_DISABLED(GPIOC_PIN10) |	\
							   PIN_LOCKR_DISABLED(GPIOC_PIN11) |	\
							   PIN_LOCKR_DISABLED(GPIOC_PIN12) |	\
							   PIN_LOCKR_DISABLED(GPIOC_LED1) |		\
							   PIN_LOCKR_DISABLED(GPIOC_LED2) |     \
							   PIN_LOCKR_DISABLED(GPIOC_LED3))


/*
 * GPIOD setup: NONE on SPM32L443Cxx
 */
#define VAL_GPIOD_MODER       (0xffffffff)
#define VAL_GPIOD_OTYPER      (0)
#define VAL_GPIOD_OSPEEDR     (0)
#define VAL_GPIOD_PUPDR       (0)
#define VAL_GPIOD_ODR         (0)
#define VAL_GPIOD_AFRL        (0)
#define VAL_GPIOD_AFRH        (0)
#define VAL_GPIOD_ASCR        (0)
#define VAL_GPIOD_LOCKR       (0)

/*
 * GPIOE setup: NONE on SPM32L443Cxx
 */
#define VAL_GPIOE_MODER       (0xffffffff)
#define VAL_GPIOE_OTYPER      (0)
#define VAL_GPIOE_OSPEEDR     (0)
#define VAL_GPIOE_PUPDR       (0)
#define VAL_GPIOE_ODR         (0)
#define VAL_GPIOE_AFRL        (0)
#define VAL_GPIOE_AFRH        (0)
#define VAL_GPIOE_ASCR        (0)
#define VAL_GPIOE_LOCKR       (0)

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN              (alternate 0).
 * PH1  - SIDE_SEL            (input).
 * PH2  - PIN2                (analog).
 * PH3  - BOOT_SW             (input).
 * PH4  - PIN4                (analog).
 * PH5  - PIN5                (analog).
 * PH6  - PIN6                (analog).
 * PH7  - PIN7                (analog).
 * PH8  - PIN8                (analog).
 * PH9  - PIN9                (analog).
 * PH10 - PIN10               (analog).
 * PH11 - PIN11               (analog).
 * PH12 - PIN12               (analog).
 * PH13 - PIN13               (analog).
 * PH14 - PIN14               (analog).
 * PH15 - PIN15               (analog).
 */
#define VAL_GPIOH_MODER       (PIN_MODE_ANALOG(GPIOH_OSC_IN) |	\
                               PIN_MODE_INPUT(GPIOH_SIDE_SEL) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN2) |	\
                               PIN_MODE_INPUT(GPIOH_BOOT_SW) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN4) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN5) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN6) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN7) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN8) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN9) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN10) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN11) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN12) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN13) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN14) |	\
                               PIN_MODE_ANALOG(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER      (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_SIDE_SEL) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_BOOT_SW) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |		\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |	\
                               PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR     (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_SIDE_SEL) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN2) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_BOOT_SW) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN4) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN5) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN6) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN7) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN8) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN9) |		\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN10) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN11) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN12) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN13) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN14) |	\
                               PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR       (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |	\
                               PIN_PUPDR_FLOATING(GPIOH_SIDE_SEL) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN2) |		\
                               PIN_PUPDR_FLOATING(GPIOH_BOOT_SW) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN4) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN5) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN6) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN7) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN8) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN9) |		\
                               PIN_PUPDR_FLOATING(GPIOH_PIN10) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN11) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN12) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN13) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN14) |	\
                               PIN_PUPDR_FLOATING(GPIOH_PIN15))
#define VAL_GPIOH_ODR         (PIN_ODR_LOW(GPIOH_OSC_IN) |		\
                               PIN_ODR_LOW(GPIOH_SIDE_SEL) |	\
                               PIN_ODR_LOW(GPIOH_PIN2) |		\
                               PIN_ODR_LOW(GPIOH_BOOT_SW) |		\
                               PIN_ODR_LOW(GPIOH_PIN4) |		\
                               PIN_ODR_LOW(GPIOH_PIN5) |		\
                               PIN_ODR_LOW(GPIOH_PIN6) |		\
                               PIN_ODR_LOW(GPIOH_PIN7) |		\
                               PIN_ODR_LOW(GPIOH_PIN8) |		\
                               PIN_ODR_LOW(GPIOH_PIN9) |		\
                               PIN_ODR_LOW(GPIOH_PIN10) |		\
                               PIN_ODR_LOW(GPIOH_PIN11) |		\
                               PIN_ODR_LOW(GPIOH_PIN12) |		\
                               PIN_ODR_LOW(GPIOH_PIN13) |		\
                               PIN_ODR_LOW(GPIOH_PIN14) |		\
                               PIN_ODR_LOW(GPIOH_PIN15))
#define VAL_GPIOH_AFRL        (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |		\
                               PIN_AFIO_AF(GPIOH_SIDE_SEL, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN2, 0U) |		\
                               PIN_AFIO_AF(GPIOH_BOOT_SW, 0U) |		\
                               PIN_AFIO_AF(GPIOH_PIN4, 0U) |		\
                               PIN_AFIO_AF(GPIOH_PIN5, 0U) |		\
                               PIN_AFIO_AF(GPIOH_PIN6, 0U) |		\
                               PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH        (PIN_AFIO_AF(GPIOH_PIN8, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN9, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN10, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN11, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN12, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN13, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN14, 0U) |	\
                               PIN_AFIO_AF(GPIOH_PIN15, 0U))
#define VAL_GPIOH_ASCR        (PIN_ASCR_DISABLED(GPIOH_OSC_IN) |	\
                               PIN_ASCR_DISABLED(GPIOH_SIDE_SEL) |	\
                               PIN_ASCR_DISABLED(GPIOH_PIN2) |		\
                               PIN_ASCR_DISABLED(GPIOH_BOOT_SW) |	\
                               PIN_ASCR_DISABLED(GPIOH_PIN4) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN5) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN6) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN7) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN8) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN9) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN10) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN11) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN12) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN13) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN14) |		\
                               PIN_ASCR_DISABLED(GPIOH_PIN15))
#define VAL_GPIOH_LOCKR       (PIN_LOCKR_DISABLED(GPIOH_OSC_IN) |	\
                               PIN_LOCKR_DISABLED(GPIOH_SIDE_SEL) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN2) |		\
                               PIN_LOCKR_DISABLED(GPIOH_BOOT_SW) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN4) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN5) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN6) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN7) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN8) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN9) |		\
                               PIN_LOCKR_DISABLED(GPIOH_PIN10) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN11) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN12) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN13) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN14) |	\
                               PIN_LOCKR_DISABLED(GPIOH_PIN15))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifndef USE_SSD1306
#define boardDisplayOn() do {} while (0)
#define boardDisplayOff() do {} while (0)
#define boardDisplayUpdate(x) do {} while (0)
#endif

#ifndef USE_RGB_LEDS
#define boardRGBLedsOn() do {} while (0)
#define boardRGBLedsOff() do {} while (0)
#define boardRGBLedsShow() do {} while (0)
#define boardRGBLedsSet(i, c) do {} while (0)
#define boardRGBLedsSetRGB(i, r, g, b) do {} while (0)
#define boardRGBLedsNum() (0)
#endif

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif

  void boardInit(void);

#ifdef USE_SSD1306
  void boardDisplayOn(void);
  void boardDisplayOff(void);
  void boardDisplayUpdate(const unsigned char *logo_data);
#endif

#ifdef USE_RGB_LEDS
  void boardRGBLedsOn(void);
  void boardRGBLedsOff(void);
  void boardRGBLedsSet(unsigned char i, unsigned long c);
  void boardRGBLedsSetRGB(unsigned char i, unsigned char r, unsigned char g,
                          unsigned char b);
  void boardRGBLedsShow(void);
  unsigned boardRGBLedsNum(void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
