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
#include "uart.h"


#if defined(KB_CHECK_BATTERY_ENABLED)
#   include "battery.h"
#endif

static uint32_t     lpm_timer_buffer = 0;
static bool         lpm_time_up               = false;

// use for config wakeUp Pin
static const pin_t wakeUpRow_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t wakeUpCol_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

void ws2812power_enabled(void);
void ws2812power_Disabled(void);

void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}

__attribute__((weak)) void lpm_device_power_open(void) ;
__attribute__((weak)) void lpm_device_power_close(void) ;

void lpm_init(void)
{
    lpm_timer_reset();

    gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);

// usb
    gpio_set_pin_input(USB_POWER_SENSE_PIN);
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_RISING_EDGE);

    lpm_device_power_open();
}


void set_all_io_analog(void)
{
    // 禁用调试功能以降低功耗
    DBGMCU->CR &= ~DBGMCU_CR_DBG_SLEEP;   // 禁用在Sleep模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STOP;    // 禁用在Stop模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STANDBY; // 禁用在Standby模式下的调试
    // 在系统初始化代码中禁用SWD接口
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG);



    palSetLineMode(A0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A7, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A15, PAL_MODE_INPUT_ANALOG); 

    palSetLineMode(B0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B7, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B15, PAL_MODE_INPUT_ANALOG); 
}

__attribute__((weak)) bool usb_power_connected(void) {
#ifdef USB_POWER_SENSE_PIN
    return readPin(USB_POWER_SENSE_PIN) == USB_POWER_CONNECTED_LEVEL;
#else
    return true;
#endif
}

void My_PWR_EnterSTOPMode(void)
{
#if STM32_HSE_ENABLED
    /* Switch to HSI */
    RCC->CFGR = (RCC->CFGR & (~STM32_SW_MASK)) | STM32_SW_HSI;
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW_HSI << 2));

    /* Set HSE off  */
    RCC->CR &= ~RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY));

    palSetLineMode(H1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(H0, PAL_MODE_INPUT_ANALOG); 
#endif
    /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
    COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    PWR->CR |=
        PWR_CR_MRLVDS |
        PWR_CR_LPLVDS |
        PWR_CR_FPDS |
        PWR_CR_LPDS |
        0;
    __WFI();

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

void enter_low_power_mode_prepare(void)
{
    if (usb_power_connected()) 
    {
       return;
    }
    set_all_io_analog();
    uint8_t i = 0;
#if (DIODE_DIRECTION == COL2ROW)
    // Set row(low valid), read cols
    for (i = 0; i < matrix_cols(); i++)
    { // set col pull-up input
        if(wakeUpCol_pins[i] == NO_PIN)
        {
            continue;
        } 
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_input_high(wakeUpCol_pins[i]);
            palEnableLineEvent(wakeUpCol_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
    for (i = 0; i < matrix_rows(); i++)
    { // set row output low level
        if(wakeUpRow_pins[i] == NO_PIN)
        {
            continue;
        } 
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_output(wakeUpRow_pins[i]);
            gpio_write_pin_low(wakeUpRow_pins[i]);
        }
    }
#elif (DIODE_DIRECTION == ROW2COL)

    // Set col(low valid), read rows
    for (i = 0; i < matrix_rows(); i++)
    { // set row pull-up input
        if(wakeUpRow_pins[i] == NO_PIN)
        {
            continue;
        } 
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_input_high(wakeUpRow_pins[i]);
            palEnableLineEvent(wakeUpRow_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
    for (i = 0; i < matrix_cols(); i++)
    { // set col output low level
        if(wakeUpCol_pins[i] == NO_PIN)
        {
            continue;
        } 
        ATOMIC_BLOCK_FORCEON {
            gpio_set_pin_output(wakeUpCol_pins[i]);
            gpio_write_pin_low(wakeUpCol_pins[i]);
        }
    }
#endif


    gpio_set_pin_input_low(BHQ_RUN_STATE_INPUT_PIN);
    palEnableLineEvent(BHQ_RUN_STATE_INPUT_PIN, PAL_EVENT_MODE_RISING_EDGE);
    gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);

// usb 插入检测
    gpio_set_pin_input(USB_POWER_SENSE_PIN);
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_RISING_EDGE);
#if defined(KB_CHECK_BATTERY_ENABLED)
    battery_stop();
#endif

    /* Usb unit is actived and running, stop and disconnect first */
    sdStop(&UART_DRIVER);
    palSetLineMode(UART_TX_PIN, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(UART_RX_PIN, PAL_MODE_INPUT_ANALOG);

    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);

    bhq_Disable();
    lpm_device_power_close();    // 外围设备 电源 关闭
    My_PWR_EnterSTOPMode();

    chSysLock();
        stm32_clock_init();
        halInit();
        stInit();
        timer_init();
    chSysUnlock();

    /*  USB D+/D- */
    palSetLineMode(A11, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));
    palSetLineMode(A12, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));
    if (usb_power_connected()) {
        usb_event_queue_init();
        init_usb_driver(&USBD1);
    }
 
    /* Call debounce_free() to avoiding memory leak of debounce_counters as debounce_init()
    invoked in matrix_init() alloc new memory to debounce_counters */
    debounce_free();
    matrix_init();

    lpm_timer_reset();
    report_buffer_init();
    bhq_init();     // uart_init

    clear_keyboard();
    layer_clear();

    lpm_device_power_open();    // 外围设备 电源 关闭
  
    gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);

}



void lpm_task(void)
{
    if (usb_power_connected() && USBD1.state == USB_STOP) {
        usb_event_queue_init();
        init_usb_driver(&USBD1);
    }


    if(report_buffer_is_empty() == false)
    {
        lpm_time_up = false;
        lpm_timer_buffer = 0;
        return;
    }

    if(lpm_time_up == false && lpm_timer_buffer == 0)
    {
        lpm_time_up = true;
        lpm_timer_buffer = sync_timer_read32();
    }

    if (lpm_time_up == true && sync_timer_elapsed32(lpm_timer_buffer) > RUN_MODE_PROCESS_TIME) {
        lpm_time_up = false;
        lpm_timer_buffer = 0;
        enter_low_power_mode_prepare();
    }
}