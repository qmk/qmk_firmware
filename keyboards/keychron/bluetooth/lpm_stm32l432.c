/* Copyright 2022 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/******************************************************************************
 *
 *  Filename:      lpm_stm32l432.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#include "quantum.h"
#include <usb_main.h>
#include "bluetooth.h"
#include "indicator.h"
#include "lpm.h"
#include "transport.h"
#include "battery.h"
#include "report_buffer.h"
#include "stm32_bd.inc"
#include "debounce.h"

extern pin_t                 row_pins[MATRIX_ROWS];
extern void                  select_all_cols(void);
extern bluetooth_transport_t bluetooth_transport;

static pm_t power_mode = PM_RUN;

static inline void stm32_clock_fast_init(void);

bool lpm_set(pm_t mode) {
    switch (mode) {
#ifdef LOW_POWER_RUN_MODE_ENABLE
        case PM_RUN:
            if (power_mode != PM_LOW_POWER_RUN)) return;
            /* Set main regulator */
            PWR->CR1 &= ~PWR_CR1_LPR;
            while (PWR->SR2 & PWR_SR2_REGLPF)
                ;
            // TODO: restore sysclk
            return true;
            // break;

        case PM_LOW_POWER_RUN:
            if (power_mode != PM_RUN) return;

            // FLASH->ACR |= FLASH_ACR_RUN_PD;   // Optional
            // TODO: Decrease sysclk below 2 MHz
            PWR->CR1 |= PWR_CR1_LPR;
            return true;
            // break;
#endif
        case PM_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_RUN) return false;

            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            break;

#ifdef LOW_POWER_RUN_MODE_ENABLE
        case PM_LOW_POWER_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_LOW_POWER_RUN) return; /* Can only transit from PM_LOW_POWER_RUN */

            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            __WFI();
            exit_low_power_mode();
            break;
#endif
        case PM_STOP0:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
            if (power_mode != PM_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP0;
            break;

        case PM_STOP1:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP1;
            break;

        case PM_STOP2:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx (x=1, 2), I2C3, LPUART1, LPTIM1, LPTIM2 */
            if (power_mode != PM_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP2;
            break;

        case PM_STANDBY_WITH_RAM:
            /* Wake source: Reset, 5 I/O(PA0, PC13, PE6, PA2, PC5), BOR, RTC, IWDG */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STANDBY;
            PWR->CR3 |= PWR_CR3_RRS;
            break;

        case PM_STANDBY:
            /* Wake source: Reset, 2 I/O(PA0, PA2) in STM32L432Kx,, BOR, RTC, IWDG */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STANDBY;
            PWR->CR3 &= ~PWR_CR3_RRS;
            break;

        case PM_SHUTDOWN:
            /* Wake source: Reset, 2 I/O(PA0, PA2) in STM32L432Kx, RTC */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_SHUTDOWN;
            break;

        default:
            return false;
    }

    return true;
}

static inline void enter_low_power_mode_prepare(void) {
#if defined(KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE)
    /* Usb unit is actived and running, stop and disconnect first */
    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);

    /* Isolate USB to save power.*/
    PWR->CR2 &= ~PWR_CR2_USV; /*PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
#endif

    palEnableLineEvent(BLUETOOTH_INT_INPUT_PIN, PAL_EVENT_MODE_FALLING_EDGE);
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_BOTH_EDGES);

    /* Enable key matrix wake up */
    pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            palEnableLineEvent(row_pins[x], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }

    select_all_cols();

#if defined(DIP_SWITCH_PINS)
#    define NUMBER_OF_DIP_SWITCHES (sizeof(dip_switch_pad) / sizeof(pin_t))
    static pin_t dip_switch_pad[] = DIP_SWITCH_PINS;

    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        setPinInputLow(dip_switch_pad[i]);
    }
#endif
}

static inline void lpm_wakeup(void) {
    chSysLock();
    stm32_clock_fast_init();
    chSysUnlock();

    if (bluetooth_transport.init) bluetooth_transport.init(true);

    chSysLock();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    PWR->SCR |= PWR_SCR_CWUF;
    PWR->SCR |= PWR_SCR_CSBF;

    /* TIMx is disable during stop/standby/sleep mode, init after wakeup */
    stInit();
    timer_init();
    chSysUnlock();
    battery_init();

    /* Disable all wake up pins */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            palDisableLineEvent(row_pins[x]);
        }
    }
    palDisableLineEvent(BLUETOOTH_INT_INPUT_PIN);

#ifdef USB_POWER_SENSE_PIN
    palDisableLineEvent(USB_POWER_SENSE_PIN);

#    if defined(KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE)
    if (usb_power_connected()) {
        hsi48_init();
        /* Remove USB isolation.*/
        // PWR->CR2 |= PWR_CR2_USV; /* PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
        usb_power_connect();
        usb_start(&USBD1);
    }
#    endif

#endif

#if defined(DIP_SWITCH_PINS)
    dip_switch_init();
    dip_switch_read(true);
#endif
}

/*
 * NOTE:
 * 1. Shall not use PM_LOW_POWER_RUN, PM_LOW_POWER_SLEEP, due to PM_LOW_POWER_RUN
 *    need to decrease system clock below 2 MHz. Dynamic clock is not yet supported
 *    for STM32L432xx in latest ChibiOS 21.6.0 so far.
 * 2. Care must be taken to use PM_STANDBY_WITH_RAM, PM_STANDBY, PM_SHUTDOWN due to
 *    limited wake source, thus can't be waken via keyscan. PM_SHUTDOWN need LSE.
 * 3. Reference from AN4621: STM32L4 and STM32L4+ ultra-low-power features overview
 *    for detail wake source
 */

void enter_power_mode(pm_t mode) {
#if defined(KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE)
    /* Don't enter low power mode if attached to the host */
    if (mode > PM_SLEEP && usb_power_connected()) return;
#endif

    if (!lpm_set(mode)) return;
    enter_low_power_mode_prepare();

    //    __DSB();
    __WFI();
    //    __ISB();

    lpm_wakeup();
    lpm_timer_reset();
    report_buffer_init();

    /* Call debounce_free() to avoid memory leak as debounce_init() invoked in matrix_init() allocates
     * new memory when using per row/key debounce
     */
    debounce_free();
    matrix_init();
    power_mode = PM_RUN;
}

void usb_power_connect(void) {
    PWR->CR2 |= PWR_CR2_USV;
}

void usb_power_disconnect(void) {
    PWR->CR2 &= ~PWR_CR2_USV;
}

/*
 * This is a simplified version of stm32_clock_init() by removing unnecessary clock initlization
 * code snippet. The original stm32_clock_init() take about 2ms, but ckbt51 sends data via uart
 * about 200us after wakeup pin is assert, it means that we must get everything ready before data
 * coming when wakeup pin interrupt of MCU is triggerred.
 * Here we reduce clock init time to less than 100us.
 */
void stm32_clock_fast_init(void) {
#if !STM32_NO_INIT
    /* Clocks setup.*/
    msi_init();   // 6.x us
    hsi16_init(); // 4.x us

    /* PLLs activation, if required.*/
    pll_init();
    pllsai1_init();
    pllsai2_init();
    /* clang-format off */
    /* Other clock-related settings (dividers, MCO etc).*/
  RCC->CFGR = STM32_MCOPRE | STM32_MCOSEL | STM32_STOPWUCK |
              STM32_PPRE2  | STM32_PPRE1  | STM32_HPRE;
    /* CCIPR register initialization, note, must take care of the _OFF
       pseudo settings.*/
    {
    uint32_t ccipr = STM32_DFSDMSEL  | STM32_SWPMI1SEL | STM32_ADCSEL    |
                     STM32_CLK48SEL  | STM32_LPTIM2SEL | STM32_LPTIM1SEL |
                     STM32_I2C3SEL   | STM32_I2C2SEL   | STM32_I2C1SEL   |
                     STM32_UART5SEL  | STM32_UART4SEL  | STM32_USART3SEL |
                     STM32_USART2SEL | STM32_USART1SEL | STM32_LPUART1SEL;
/* clang-format on */
#    if STM32_SAI2SEL != STM32_SAI2SEL_OFF
        ccipr |= STM32_SAI2SEL;
#    endif
#    if STM32_SAI1SEL != STM32_SAI1SEL_OFF
        ccipr |= STM32_SAI1SEL;
#    endif
        RCC->CCIPR = ccipr;
    }

    /* Set flash WS's for SYSCLK source */
    if (STM32_FLASHBITS > STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }

    /* Switching to the configured SYSCLK source if it is different from MSI.*/
#    if (STM32_SW != STM32_SW_MSI)
    RCC->CFGR |= STM32_SW; /* Switches on the selected clock source.   */
    /* Wait until SYSCLK is stable.*/
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW << 2))
        ;
#    endif

    /* Reduce the flash WS's for SYSCLK source if they are less than MSI WSs */
    if (STM32_FLASHBITS < STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }
#endif /* STM32_NO_INIT */
}
