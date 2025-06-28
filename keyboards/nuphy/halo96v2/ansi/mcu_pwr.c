/*
Copyright 2023 NuPhy, Persama (@Persama) & jincao1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "config.h"
#include "gpio.h"
#include "user_kb.h"
#include "mcu_stm32f0xx.h"
#include "mcu_pwr.h"
#include "rgb_matrix.h"

// from @adi4086
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

//------------------------------------------------
// 外部变量
extern DEV_INFO_STRUCT dev_info;

// static bool f_usb_deinit         = 0;
static bool tim6_enabled        = false;
static bool sleeping            = false;

static bool rgb_led_on = 0;

void rgb_matrix_update_pwm_buffers(void);
void clear_report_buffer_and_queue(void);

/** ================================================================
 * @brief   关闭USB
 *
 ================================================================*/
void m_deinit_usb_072(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 复位USB寄存器
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_USBRST, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1RSTR_USBRST, DISABLE);
    wait_ms(10);

    // 关闭USB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_USBEN, DISABLE);

    // GPIO恢复为悬浮状态
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init((GPIO_TypeDef *)GPIOA, &GPIO_InitStructure);
}

/** ================================================================
 * @brief   低功耗处理
 *
 ================================================================*/
#include "hal_usb.h"
#include "usb_main.h"
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex) {
    uint32_t tmp = 0x00;

    tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

#include "hal_lld.h"
#define EXTI_PortSourceGPIOA ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD ((uint8_t)0x03)

#include "usb_main.h"
/**
 * @brief  Enter deep sleep
 * @note This is Nuphy's un-released logic with some cleanup/refactoring
 *       The MCU is put on a low power mode.
 */
void enter_deep_sleep(void) {
    //------------------------ 设置RF休眠状态
    if (dev_info.rf_state == RF_CONNECT)
        uart_send_cmd(CMD_SET_CONFIG, 5, 5); // 连接状态设置深度休眠时间
    else
        uart_send_cmd(CMD_SLEEP, 5, 5); // 非连接状态直接进入深度休眠

    //------------------------ 非USB模式下关闭USB
    // TODO - do we really need to deinitialize USB?
    // Commenting this out for now. It causes USB-C chargers to crash the board on wake apparently.
    // if (dev_info.link_mode != LINK_USB) {
    //     f_usb_deinit = 1;
    //     m_deinit_usb_072(); // 关闭USB
    // }

    // 关闭定时器
    if (tim6_enabled) TIM_Cmd(TIM6, DISABLE);

    // from @adi4086
    for (int i = 0; i < ARRAY_SIZE(col_pins); i++) {
        gpio_set_pin_output(col_pins[i]);
        gpio_write_pin_high(col_pins[i]);
    }

    for (int i = 0; i < ARRAY_SIZE(row_pins); i++) {
        gpio_set_pin_input_low(row_pins[i]);
    }

    // Configure interrupt source - all 5 rows of the keyboard.
    SYSCFG_EXTILineConfig(EXTI_PORT_R0, EXTI_PIN_R0);
    SYSCFG_EXTILineConfig(EXTI_PORT_R1, EXTI_PIN_R1);
    SYSCFG_EXTILineConfig(EXTI_PORT_R2, EXTI_PIN_R2);
    SYSCFG_EXTILineConfig(EXTI_PORT_R3, EXTI_PIN_R3);
    SYSCFG_EXTILineConfig(EXTI_PORT_R4, EXTI_PIN_R4);
    SYSCFG_EXTILineConfig(EXTI_PORT_R5, EXTI_PIN_R5);

    EXTI_InitTypeDef m_exti;
    EXTI_StructInit(&m_exti);
    m_exti.EXTI_Line    = 0XFFFF; // GPIO 0-15
    m_exti.EXTI_LineCmd = ENABLE;
    m_exti.EXTI_Mode    = EXTI_Mode_Interrupt;
    m_exti.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&m_exti);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel         = EXTI4_15_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    led_pwr_sleep_handle();

    gpio_set_pin_output(DEV_MODE_PIN);
    gpio_write_pin_low(DEV_MODE_PIN);

    gpio_set_pin_output(SYS_MODE_PIN);
    gpio_write_pin_low(SYS_MODE_PIN);

    gpio_set_pin_input(RGB_DRIVER_SDB1);
    gpio_set_pin_input(RGB_DRIVER_SDB2);

    gpio_set_pin_output(NRF_TEST_PIN);
    gpio_write_pin_high(NRF_TEST_PIN);

    gpio_set_pin_input(NRF_WAKEUP_PIN);
    gpio_write_pin_low(NRF_WAKEUP_PIN);

    clear_report_buffer_and_queue();

    // Enter low power mode and wait for interrupt signal
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}

/**
 * @brief Wake up from deep sleep
 * @note This is triggered by an interrupt event.
 *       This is mostly Nuphy's unreleased logic with cleanup/refactoring by me.
 */
void exit_deep_sleep(void) {
    // swap with down below when custom matrix used
    //     extern void matrix_init_custom(void);
    // matrix_init_custom();

    extern void matrix_init(void);
    matrix_init();

    // connection mode switch pin
    gpio_set_pin_input_high(DEV_MODE_PIN);
    // keyboard OS switch pin
    gpio_set_pin_input_high(SYS_MODE_PIN);

    // RF module wakeup
    gpio_set_pin_output(NRF_WAKEUP_PIN);
    gpio_write_pin_high(NRF_WAKEUP_PIN);

    // // power on LEDs This is missing from Nuphy's logic.
    // rgb_led_powered_off = 1;
    // sleeping            = false;
    led_pwr_wake_handle();

    // 重新初始化系统时钟
    stm32_clock_init();

    /* TIM6 使能 */
    if (tim6_enabled) TIM_Cmd(TIM6, ENABLE);

    // Should re-init USB regardless probably if it was deinitialized.
    uart_send_cmd(CMD_HAND, 0, 1);
    if (dev_info.link_mode == LINK_USB) {
        usb_lld_wakeup_host(&USB_DRIVER);
        restart_usb_driver(&USB_DRIVER);
    }

    // flag for RF wakeup workload.
    dev_info.rf_state = RF_WAKE;
}

/**
 * @brief  Light sleep by powering off LEDs.
 * @note This is Nuphy's "open sourced" sleep logic. It's not deep sleep.
 */
void enter_light_sleep(void) {
    dev_sts_sync();

    if (dev_info.rf_state == RF_CONNECT)
        uart_send_cmd(CMD_SET_CONFIG, 5, 5);
    else
        uart_send_cmd(CMD_SLEEP, 5, 5);

    led_pwr_sleep_handle();

    clear_report_buffer_and_queue();
    sleeping = true;
}

/**
 * @brief  Power back up LEDs on exiting light sleep.
 * @note This is Nuphy's "open sourced" wake logic. It's not deep sleep.
 */
void exit_light_sleep(void) {
    sleeping = false;
    // // NOTE: hack to force enable all leds
    // rgb_led_powered_off  = 1;

    led_pwr_wake_handle();
    uart_send_cmd(CMD_HAND, 0, 1);
    if (dev_info.link_mode == LINK_USB) {
        usb_lld_wakeup_host(&USB_DRIVER);
        restart_usb_driver(&USB_DRIVER);
    }

    // flag for RF wakeup workload.
    dev_info.rf_state = RF_WAKE;
}

void led_pwr_sleep_handle(void) {
    if (rgb_led_on) {
        pwr_rgb_led_off();
    }
}

void side_rgb_refresh(void);

void led_pwr_wake_handle(void) {
    if (!rgb_led_on) {
        pwr_rgb_led_on();
        rgb_matrix_update_pwm_buffers();
    }
}

void pwr_rgb_led_off(void) {
    if (!rgb_led_on) return;
    // LED power supply off
    gpio_set_pin_output(DC_BOOST_PIN);
    gpio_write_pin_low(DC_BOOST_PIN);
    gpio_set_pin_input(RGB_DRIVER_SDB1);
    gpio_set_pin_input(RGB_DRIVER_SDB2);
    rgb_led_on = 0;
}

void pwr_rgb_led_on(void) {
    if (sleeping || rgb_led_on) return;
    // LED power supply on
    gpio_set_pin_output(DC_BOOST_PIN);
    gpio_write_pin_high(DC_BOOST_PIN);
    gpio_set_pin_output(RGB_DRIVER_SDB1);
    gpio_write_pin_high(RGB_DRIVER_SDB1);
    gpio_set_pin_output(RGB_DRIVER_SDB2);
    gpio_write_pin_high(RGB_DRIVER_SDB2);
    rgb_led_on = 1;
}

bool is_rgb_led_on(void) {
    return rgb_led_on;
}

/* Nuphy's implementations. */

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param  EXTI_Line: specifies the EXTI lines flags to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..19)
 * @retval None
 */
void EXTI_ClearFlag(uint32_t EXTI_Line) {
    EXTI->PR = EXTI_Line;
}

///////////////////////////////////////////////////////////////////////////////////////////

#define STM32_EXTI_0_1_HANDLER Vector54
OSAL_IRQ_HANDLER(STM32_EXTI_0_1_HANDLER) {
    EXTI->PR = 0xffff;
}

#define STM32_EXTI_2_3_HANDLER Vector58
OSAL_IRQ_HANDLER(STM32_EXTI_2_3_HANDLER) {
    EXTI->PR = 0xffff;
}

#define STM32_EXTI_4_15_HANDLER Vector5C
OSAL_IRQ_HANDLER(STM32_EXTI_4_15_HANDLER) {
    EXTI->PR = 0xffff;
}

void EXTI_DeInit(void) {
    EXTI->IMR  = 0x0F940000;
    EXTI->EMR  = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR   = 0x006BFFFF;
}

void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct) {
    uint32_t tmp = 0;

    tmp = (uint32_t)EXTI_BASE;

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE) {
        /* Clear EXTI line configuration */
        EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

        tmp += EXTI_InitStruct->EXTI_Mode;

        *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;

        /* Clear Rising Falling edge configuration */
        EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

        /* Select the trigger for the selected interrupts */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling) {
            /* Rising Falling edge */
            EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
            EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
        } else {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;

            *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;
        }
    } else {
        tmp += EXTI_InitStruct->EXTI_Mode;

        /* Disable the selected external lines */
        *(__IO uint32_t *)tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

/**
 * @brief  Fills each EXTI_InitStruct member with its reset value.
 * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
 *         be initialized.
 * @retval None
 */
void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct) {
    EXTI_InitStruct->EXTI_Line    = 0;
    EXTI_InitStruct->EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

#if (0) // this code is unused for now, keeping it here for reference/future usage.
void mcu_timer6_init(void) {
    NVIC_InitTypeDef        NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* TIM6 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /*  TIM6 中断嵌套设计*/
    NVIC_InitStructure.NVIC_IRQChannel         = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Time 定时器基础设置 */
    /* This configuration results in 1ms intervals: https://deepbluembedded.com/stm32-timer-interrupt-hal-example-timer-mode-lab/
       Tout = (ARR + 1)(PSC + 1) / Fclk (48mhz for STM32F072)
       0.001 = (1000)(48)/(48_000_000) = 1ms
    */
    TIM_TimeBaseStructure.TIM_Period        = 1000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler     = 48 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    /* TIM6 使能 */
    TIM_Cmd(TIM6, ENABLE);

    tim6_enabled = true;
}

/*
 TIM6 handler is triggered by the timer above which is used as an interrupt.
 This is every 1ms so it effectively puts the CPU sleep mode only for 1s.
*/
volatile uint8_t idle_sleep_cnt = 0;
OSAL_IRQ_HANDLER(STM32_TIM6_HANDLER) {
    if (TIM_GetFlagStatus(TIM6, TIM_FLAG_Update) != ST_RESET) {
        TIM_ClearFlag(TIM6, TIM_FLAG_Update);
        idle_sleep_cnt++;
    }
}

// For this to work you need to call m_timer6_init() in ansi.c post kb init user.
// That enables the STM32_TIM6_HANDLER but I think it runs on the interrupt interval of the TIM6 timer.
void idle_enter_sleep(void) {
    TIM6->CNT      = 0;
    idle_sleep_cnt = 0;
    while (idle_sleep_cnt < 1) {
        PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);
    }
}
#endif
