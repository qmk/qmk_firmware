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

    // 2. 清除 PDDS 位，选择 STOP 模式
    PWR->CR &= ~PWR_CR_PDDS;

    // 3. 根据 Regulator 参数设置电压调节模式
    // LPDS 位的选择取决于 Regulator 参数的值
    if (is_low_voltage_model) {
        PWR->CR |= PWR_CR_LPDS;  // 低功耗电压调节模式
    } else {
        PWR->CR &= ~PWR_CR_LPDS; // 正常电压调节模式
    }

    // 4. 设置 SLEEPDEEP 位以进入 STOP 模式
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // 进入等待中断模式
    __WFI();


    // 6. 清除 SLEEPDEEP 位以恢复正常模式
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
    

    My_PWR_EnterSTOPMode(true); // 等待中断指令


    chSysLock();
    stm32_clock_init();
    stInit();
    timer_init();
    chSysUnlock();


    bhq_init(false);
    report_buffer_init();
    restart_usb_driver(&USBD1);
    lpm_timer_reset();
    debounce_free();
    matrix_init();

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