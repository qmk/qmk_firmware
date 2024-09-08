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

#include "ws2812.h"


static uint32_t     lpm_timer_buffer = 0;
static bool         lpm_time_up               = false;

// use for config wakeUp Pin
static const pin_t wakeUpRow_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t wakeUpCol_pins[MATRIX_COLS]   = MATRIX_COL_PINS;


void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}


void lpm_init(void)
{
    lpm_timer_reset();

    gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);

// usb
    gpio_set_pin_input_high(USB_POWER_SENSE_PIN);
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_FALLING_EDGE);

}

void ws2812power_enabled(void)
{
    ws2812_init();
    rgblight_setrgb_at(255, 60, 50, 0);
    gpio_set_pin_output(B8);        // ws2812 power
    gpio_write_pin_low(B8);
}
void ws2812power_Disabled(void)
{
    rgblight_setrgb_at(0, 0, 0, 0);
    gpio_set_pin_output(B8);        // ws2812 power
    gpio_write_pin_high(B8);

    gpio_set_pin_input(WS2812_DI_PIN);  // 设置高阻输入
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

    gpio_set_pin_input_low(BHQ_RUN_STATE_INPUT_PIN);
    palEnableLineEvent(BHQ_RUN_STATE_INPUT_PIN, PAL_EVENT_MODE_RISING_EDGE);
    gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);

// usb
    gpio_set_pin_input_high(USB_POWER_SENSE_PIN);
    palEnableLineEvent(USB_POWER_SENSE_PIN, PAL_EVENT_MODE_FALLING_EDGE);


    /* Usb unit is actived and running, stop and disconnect first */
    sdStop(&UART_DRIVER);

    usbStop(&USBD1);
    usbDisconnectBus(&USBD1);

    bhq_Disable();
    ws2812power_Disabled();
    My_PWR_EnterSTOPMode();

    stm32_clock_init();
    // Set col(low valid), read rows
    for (i = 0; i < matrix_rows(); i++)
    { // set row pull-up input 
        ATOMIC_BLOCK_FORCEON {
            palDisableLineEvent(wakeUpRow_pins[i]);
        }
    }
    halInit();


    /* Call debounce_free() to avoiding memory leak of debounce_counters as debounce_init()
    invoked in matrix_init() alloc new memory to debounce_counters */
    debounce_free();
    matrix_init();

    lpm_timer_reset();
    report_buffer_init();
    bhq_init();

    clear_keyboard();
    layer_clear();

    ws2812power_enabled();
    

    gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
}



void lpm_task(void)
{
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
