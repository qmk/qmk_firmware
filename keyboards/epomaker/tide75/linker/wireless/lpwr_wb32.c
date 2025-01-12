// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "wireless.h"
#include "util.h"

#ifndef LPWR_UART_WAKEUP_DISABLE
#    include "uart.h"
#endif

static ioline_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

#if PAL_USE_CALLBACKS != TRUE
#    error PAL_USE_CALLBACKS must be set to TRUE!
#endif

#if !((DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW))
#    error DIODE_DIRECTION must be one of COL2ROW or ROW2COL!
#endif

// clang-format off
static const uint32_t pre_lp_code[] = {553863175u, 554459777u, 1208378049u, 4026624001u, 688390415u, 554227969u, 3204472833u, 1198571264u, 1073807360u, 1073808388u};
#define PRE_LP() ((void (*)(void))((unsigned int)(pre_lp_code) | 0x01))()

static const uint32_t post_lp_code[] = {553863177u, 554459777u, 1208509121u, 51443856u, 4026550535u, 1745485839u, 3489677954u, 536895496u, 673389632u, 1198578684u, 1073807360u, 536866816u, 1073808388u};
#define POST_LP() ((void (*)(void))((unsigned int)(post_lp_code) | 0x01))()
// clang-format on

extern void __early_init(void);
extern void matrix_init_pins(void);

void palcallback_cb(uint8_t line) __attribute__((weak));
void palcallback_cb(uint8_t line) {}

void palcallback(void *arg) {
    uint8_t line = (uint32_t)arg & 0xFF;

    switch (line) {
#ifndef LPWR_UART_WAKEUP_DISABLE
        case PAL_PAD(UART_RX_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_UART);
        } break;
#endif
        default: {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_MATRIX);
        } break;
    }

    palcallback_cb(line);

    irqDeinit();
    EXTI->PR = 0xFFFFFFFF;
}

void pal_events_init(void) {

    for (uint8_t i = 0; i < 16; i++) {
        _pal_events[i].cb  = palcallback;
        _pal_events[i].arg = (void *)(uint32_t)i;
    }
}

void lpwr_exti_init_hook(void) __attribute__((weak));
void lpwr_exti_init_hook(void) {}

void lpwr_exti_init(void) {

    pal_events_init();

#if DIODE_DIRECTION == ROW2COL
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
        if (col_pins[i] != NO_PIN) {
            setPinOutputOpenDrain(col_pins[i]);
            writePinLow(col_pins[i]);
        }
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); i++) {
        if (row_pins[i] != NO_PIN) {
            setPinInputHigh(row_pins[i]);
            waitInputPinDelay();
            palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
#elif DIODE_DIRECTION == COL2ROW
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); i++) {
        if (row_pins[i] != NO_PIN) {
            setPinOutputOpenDrain(row_pins[i]);
            writePinLow(row_pins[i]);
        }
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
        if (col_pins[i] != NO_PIN) {
            setPinInputHigh(col_pins[i]);
            waitInputPinDelay();
            palEnableLineEvent(col_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
#endif

#ifndef LPWR_UART_WAKEUP_DISABLE
    setPinInput(UART_RX_PIN);
    waitInputPinDelay();
    palEnableLineEvent(UART_RX_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

    lpwr_exti_init_hook();

    /* IRQ subsystem initialization.*/
    irqInit();
}

void lpwr_clock_enable_user(void) __attribute__((weak));
void lpwr_clock_enable_user(void) {}

void lpwr_clock_enable(void) {

    __early_init();

    rccEnableEXTI();

#if WB32_SERIAL_USE_UART1
    rccEnableUART1();
#endif
#if WB32_SERIAL_USE_UART2
    rccEnableUART2();
#endif
#if WB32_SERIAL_USE_UART3
    rccEnableUART3();
#endif
#if WB32_SPI_USE_QSPI
    rccEnableQSPI();
#endif
#if WB32_SPI_USE_SPIM2
    rccEnableSPIM2();
#endif
#if WB32_I2C_USE_I2C1
    rccEnableI2C1();
#endif
#if WB32_I2C_USE_I2C2
    rccEnableI2C2();
#endif

#ifndef LPWR_UART_WAKEUP_DISABLE
    palSetLineMode(UART_RX_PIN, PAL_MODE_ALTERNATE(UART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif

    lpwr_clock_enable_user();
}

void wb32_stop_mode(void) {

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    /* Prevent the chip from being unable to enter stop mode due to pending interrupts */
#if 1
    EXTI->PR = 0x7FFFF;
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 32; j++) {
            if (NVIC->ISPR[i] & (0x01UL < j)) {
                NVIC->ICPR[i] = (0x01UL < j);
            }
        }
    }
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk; // Clear Systick IRQ Pending
#endif

    /* Clear all bits except DBP and FCLKSD bit */
    PWR->CR0 &= 0x09U;

    // STOP LP4 MODE S32KON
    PWR->CR0 |= 0x3B004U;
    PWR->CFGR = 0x3B3;

    PRE_LP();

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Request Wait For Interrupt */
    __WFI();

    POST_LP();

    /* Clear SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (~SCB_SCR_SLEEPDEEP_Msk);

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void mcu_stop_mode(void) {

    wb32_stop_mode();
}
