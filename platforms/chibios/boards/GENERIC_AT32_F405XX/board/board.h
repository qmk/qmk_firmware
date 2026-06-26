#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for a Generic AT32F405 board.
 */

/*
 * Board identifier.
 */
#define BOARD_GENERIC_AT32_F405XX
#define BOARD_NAME                  "GENERIC AT32F405 board"

/*
 * MCU type, supported types are defined in
 * lib/chibios-contrib/os/common/ext/CMSIS/ArteryTek/AT32F402_405/at32f402_405.h.
 */
#define AT32F405CC

#define AT32_HAS_GPIOD TRUE

/*
 * The board uses OTG2 through an external ULPI USB HS PHY.
 */
#define BOARD_OTG2_USES_ULPI

/*
 * Board oscillators-related settings.
 */
#if !defined(AT32_LEXTCLK)
#    define AT32_LEXTCLK 32768U
#endif

#if !defined(AT32_HEXTCLK)
#    define AT32_HEXTCLK 12000000U
#endif

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_PIN3                  3U
#define GPIOA_PIN4                  4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6                  6U
#define GPIOA_PIN7                  7U
#define GPIOA_PIN8                  8U
#define GPIOA_PIN9                  9U
#define GPIOA_PIN10                 10U
#define GPIOA_PIN11                 11U
#define GPIOA_PIN12                 12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                 10U
#define GPIOB_PIN11                 11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

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
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN2                  2U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN11                 11U

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the AT32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODT_LOW(n)              (0U << (n))
#define PIN_ODT_HIGH(n)             (1U << (n))
#define PIN_OMODE_PUSHPULL(n)       (0U << (n))
#define PIN_OMODE_OPENDRAIN(n)      (1U << (n))
#define PIN_ODRVR_STRONGER(n)       (1U << ((n) * 2U))
#define PIN_ODRVR_MODERATE(n)       (3U << ((n) * 2U))
#define PIN_PULL_FLOATING(n)        (0U << ((n) * 2U))
#define PIN_PULL_PULLUP(n)          (1U << ((n) * 2U))
#define PIN_PULL_PULLDOWN(n)        (2U << ((n) * 2U))
#define PIN_MUX(n, v)               ((v) << (((n) % 8U) * 4U))
#define PIN_HDRV_NORMAL(n)          (0U << (n))
#define PIN_HDRV_STRONGEST(n)       (1U << (n))

/*
 * GPIOA setup.
 */
#define VAL_GPIOA_CFGR              (PIN_MODE_INPUT(GPIOA_PIN0) | PIN_MODE_INPUT(GPIOA_PIN1) | PIN_MODE_INPUT(GPIOA_PIN2) | PIN_MODE_INPUT(GPIOA_PIN3) | PIN_MODE_INPUT(GPIOA_PIN4) | PIN_MODE_INPUT(GPIOA_PIN5) | PIN_MODE_INPUT(GPIOA_PIN6) | PIN_MODE_INPUT(GPIOA_PIN7) | PIN_MODE_INPUT(GPIOA_PIN8) | PIN_MODE_INPUT(GPIOA_PIN9) | PIN_MODE_INPUT(GPIOA_PIN10) | PIN_MODE_INPUT(GPIOA_PIN11) | PIN_MODE_INPUT(GPIOA_PIN12) | PIN_MODE_ALTERNATE(GPIOA_SWDIO) | PIN_MODE_ALTERNATE(GPIOA_SWCLK) | PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OMODE             0x00000000U
#define VAL_GPIOA_ODRVR             0xFFFFFFFFU
#define VAL_GPIOA_PULL              0x55555555U
#define VAL_GPIOA_ODT               0xFFFFFFFFU
#define VAL_GPIOA_MUXL              0x00000000U
#define VAL_GPIOA_MUXH              (PIN_MUX(GPIOA_SWDIO, 0U) | PIN_MUX(GPIOA_SWCLK, 0U))
#define VAL_GPIOA_HDRV              0x00000000U

/*
 * GPIOB setup.
 */
#define VAL_GPIOB_CFGR              0x00000000U
#define VAL_GPIOB_OMODE             0x00000000U
#define VAL_GPIOB_ODRVR             0xFFFFFFFFU
#define VAL_GPIOB_PULL              0x55555555U
#define VAL_GPIOB_ODT               0xFFFFFFFFU
#define VAL_GPIOB_MUXL              0x00000000U
#define VAL_GPIOB_MUXH              0x00000000U
#define VAL_GPIOB_HDRV              0x00000000U

/*
 * GPIOC setup.
 */
#define VAL_GPIOC_CFGR              0x00000000U
#define VAL_GPIOC_OMODE             0x00000000U
#define VAL_GPIOC_ODRVR             0xFFFFFFFFU
#define VAL_GPIOC_PULL              0x55555555U
#define VAL_GPIOC_ODT               0xFFFFFFFFU
#define VAL_GPIOC_MUXL              0x00000000U
#define VAL_GPIOC_MUXH              0x00000000U
#define VAL_GPIOC_HDRV              0x00000000U

/*
 * GPIOD setup.
 */
#define VAL_GPIOD_CFGR              0x00000000U
#define VAL_GPIOD_OMODE             0x00000000U
#define VAL_GPIOD_ODRVR             0xFFFFFFFFU
#define VAL_GPIOD_PULL              0x55555555U
#define VAL_GPIOD_ODT               0xFFFFFFFFU
#define VAL_GPIOD_MUXL              0x00000000U
#define VAL_GPIOD_MUXH              0x00000000U
#define VAL_GPIOD_HDRV              0x00000000U

/*
 * GPIOF setup.
 */
#define VAL_GPIOF_CFGR              0x00000000U
#define VAL_GPIOF_OMODE             0x00000000U
#define VAL_GPIOF_ODRVR             0xFFFFFFFFU
#define VAL_GPIOF_PULL              0x55555555U
#define VAL_GPIOF_ODT               0xFFFFFFFFU
#define VAL_GPIOF_MUXL              0x00000000U
#define VAL_GPIOF_MUXH              0x00000000U
#define VAL_GPIOF_HDRV              0x00000000U

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
