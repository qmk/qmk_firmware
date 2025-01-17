/* Copyright 2023 @ lokher (https://www.keychron.com)
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
 *  Filename:      lpm_stm32f401.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#include "quantum.h"
#include <usb_main.h>
#include "wireless.h"
#include "lpm.h"
#include "lpm_stm32f401.h"
#include "config.h"

static pm_t power_mode = PM_RUN;

bool lpm_set(pm_t mode) {
    bool ret = true;

    switch (mode) {
        case PM_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_RUN)
                ret = false;
            else
                SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            break;

        case PM_STOP:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
            if (power_mode != PM_RUN)
                ret = false;
            else {
                SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
                PWR->CR |=
#if STOP_MODE_MAIN_REGULATOR_LOW_VOLTAGE
                    PWR_CR_MRLVDS |
#endif
#if STOP_MODE_LOW_POWER_REGULATOR_LOW_VOLTAG
                    PWR_CR_LPLVDS |
#endif
#if STOP_MODE_FLASH_POWER_DOWN
                    PWR_CR_FPDS |
#endif
#if STOP_MODE_LOW_POWER_DEEPSLEEP
                    PWR_CR_LPDS |
#endif
                    0;
            }
            break;

        case PM_STANDBY:
            if (power_mode != PM_RUN)
                ret = false;
            else {
                SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            }
            break;

        default:
            break;
    }
    power_mode = mode;

    return ret;
}

void enter_power_mode(pm_t mode) {
#if STM32_HSE_ENABLED
    /* Switch to HSI */
    RCC->CFGR = (RCC->CFGR & (~STM32_SW_MASK)) | STM32_SW_HSI;
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW_HSI << 2))
        ;

    /* Set HSE off  */
    RCC->CR &= ~RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY))
        ;

    /* To avoid power consumption of floating GPIO */
    palSetLineMode(H0, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(H1, PAL_MODE_INPUT_PULLDOWN);
#endif

    __WFI();

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    writePinLow(BLUETOOTH_INT_OUTPUT_PIN);
    stm32_clock_init();
    writePinHigh(BLUETOOTH_INT_OUTPUT_PIN);
}

void usb_power_connect(void) {}

void usb_power_disconnect(void) {}
