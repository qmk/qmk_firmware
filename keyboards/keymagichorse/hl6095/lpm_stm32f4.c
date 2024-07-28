/* Copyright 2024 keymagichorse
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
#include "quantum.h"
#include "lpm.h"
#include "matrix.h"
#include "gpio.h"
#include "debounce.h"
#include "usb_util.h"
#include <usb_main.h>
#include "bhq.h"
#include "report_buffer.h"


static uint32_t     lpm_timer_buffer;
static bool         lpm_time_up               = false;

// use for config wakeUp Pin
static const pin_t wakeUpRow_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t wakeUpCol_pins[MATRIX_COLS]   = MATRIX_COL_PINS;


void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = sync_timer_read32();
}

void lpm_timer_stop(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}
void lpm_init(void)
{
    lpm_timer_reset();
    // 在系统初始化代码中禁用SWD接口
    palSetPadMode(GPIOA, 13, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 14, PAL_MODE_INPUT_ANALOG);
    // 禁用调试功能以降低功耗
    DBGMCU->CR &= ~DBGMCU_CR_DBG_SLEEP;   // 禁用在Sleep模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STOP;    // 禁用在Stop模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STANDBY; // 禁用在Standby模式下的调试

}

// Disabled HSE   Enabled HSI
void switchToHSI(void) {
    // Enabled HSI
    RCC->CR |= RCC_CR_HSION;
    // wait HSI
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);
    // select HSI
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_HSI;
    // wait disabled HSI
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    

    // disabled HSE
    RCC->CR &= ~RCC_CR_HSEON;  
    // wait disabled HSE
    while ((RCC->CR & RCC_CR_HSERDY) != 0);
}
void My_PWR_EnterSTOPMode(bool is_low_voltage_model)
{

    // select STOP model
    PWR->CR &= ~PWR_CR_PDDS;

    if (is_low_voltage_model) {
        PWR->CR |= PWR_CR_LPDS;  // Low power voltage regulation mode
    } else {
        PWR->CR &= ~PWR_CR_LPDS; // Normal voltage regulation mode
    }

    // set SLEEPDEEP to STOP model
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // set mcu to wait interrupt
    __WFI();

    // clear SLEEPDEEP
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

void enter_low_power_mode_prepare(void)
{
    if (usb_connected_state()) {
        return ;
    }


    uint8_t i = 0;
#if (DIODE_DIRECTION == COL2ROW)
    // TODO: Wait implementation
#elif (DIODE_DIRECTION == ROW2COL)

    // Set col(low valid), read rows
    for (i = 0; i < matrix_rows(); i++)
    { // set row pull-up input 
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_input_high(wakeUpRow_pins[i]);
            palEnableLineEvent(wakeUpRow_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
    for (i = 0; i < matrix_cols(); i++)
    { // set col output low level
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_output(wakeUpCol_pins[i]);
            gpio_write_pin_low(wakeUpCol_pins[i]);
        }
    }
#endif

    /* Usb unit is actived and running, stop and disconnect first */
    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);
    bhq_Disable();
    switchToHSI();
    

    My_PWR_EnterSTOPMode(true); // mcu low power to stop model  

    chSysLock();
        stm32_clock_init();
        stInit();
        timer_init();
    

        bhq_init(false);
        report_buffer_init();
        restart_usb_driver(&USBD1); // TODO: read USB_POWER_SENSE_PIN
        lpm_timer_reset();
        debounce_free();
        matrix_init();
    chSysUnlock();
}


void lpm_task(void)
{
    if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > RUN_MODE_PROCESS_TIME) {
        lpm_time_up      = true;
        lpm_timer_buffer = 0;
    }
    if(lpm_time_up == false)
    {
        return;
    }
    lpm_time_up = false;
    enter_low_power_mode_prepare();
}