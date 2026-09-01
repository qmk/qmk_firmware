/**
 * @file low_power.c
 * @brief
 * @author Joy chang.li@westberrytech.com
 * @version 1.0.0
 * @date 2022-09-16
 *
 * @copyright Copyright (c) 2022 Westberry Technology (ChangZhou) Corp., Ltd
 */

#ifdef ENTRY_STOP_MODE

#    include "quantum.h"

// #define WAKEUP_RESET

static ioline_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static const uint32_t pre_lp_code[] = {553863175u, 554459777u, 1208378049u, 4026624001u, 688390415u, 554227969u, 3204472833u, 1198571264u, 1073807360u, 1073808388u};
#    define PRE_LP() ((void (*)(void))((unsigned int)(pre_lp_code) | 0x01))()

static const uint32_t post_lp_code[] = {553863177u, 554459777u, 1208509121u, 51443856u, 4026550535u, 1745485839u, 3489677954u, 536895496u, 673389632u, 1198578684u, 1073807360u, 536866816u, 1073808388u};
#    define POST_LP() ((void (*)(void))((unsigned int)(post_lp_code) | 0x01))()

void        lp_recovery_hook(void);
static void stop_mode_entry(void);
static void exti_init(void);
#    ifdef WAKEUP_RESET
void mcu_reset(void);
#    endif

extern void matrix_init_pins(void);

void lp_system_sleep(void) {
    extern void __early_init(void);

#    ifdef WAKEUP_RESET
    PWR->GPREG0 = 0x5AA5;
#    endif

    chSysLock();
    exti_init();
    chSysUnlock();

    chSysDisable();
    stop_mode_entry();

    RCC->APB1PRE |= RCC_APB1PRE_SRCEN;
    RCC->APB1ENR |= RCC_APB1ENR_EXTIEN;

#    ifdef WAKEUP_RESET
    mcu_reset();
#    else
    __early_init();
    matrix_init_pins();
#        if WB32_SERIAL_USE_UART1
    rccEnableUART1();
#        endif
#        if WB32_SERIAL_USE_UART2
    rccEnableUART2();
#        endif
#        if WB32_SERIAL_USE_UART3
    rccEnableUART3();
#        endif
    lp_recovery_hook();
#    endif
    chSysEnable();
}

__WEAK void lp_recovery_hook(void) {
    /*
     * User implementation
     * related configuration and clock recovery
     */
}

#    ifdef WAKEUP_RESET
void mcu_reset(void) {
    NVIC_SystemReset();
    while (1)
        ;
}
#    endif

void _pal_lld_enablepadevent(ioportid_t port, iopadid_t pad, ioeventmode_t mode) {
    uint32_t padmask, cridx, croff, crmask, portidx;

    /* Enable EXTI clock.*/
    rccEnableEXTI();

    /* Mask of the pad.*/
    padmask = 1U << (uint32_t)pad;

    /* Multiple channel setting of the same channel not allowed, first
       disable it. This is done because on WB32 the same channel cannot
       be mapped on multiple ports.*/
    osalDbgAssert(((EXTI->RTSR & padmask) == 0U) && ((EXTI->FTSR & padmask) == 0U), "channel already in use");

    /* Index and mask of the SYSCFG CR register to be used.*/
    cridx  = (uint32_t)pad >> 2U;
    croff  = ((uint32_t)pad & 3U) * 4U;
    crmask = ~(0xFU << croff);

    /* Port index is obtained assuming that GPIO ports are placed at  regular
       0x400 intervals in memory space. So far this is true for all devices.*/
    portidx = (((uint32_t)port - (uint32_t)GPIOA) >> 10U) & 0xFU;

    /* Port selection in SYSCFG.*/
    AFIO->EXTICR[cridx] = (AFIO->EXTICR[cridx] & crmask) | (portidx << croff);

    /* Programming edge registers.*/
    if (mode & PAL_EVENT_MODE_RISING_EDGE)
        EXTI->RTSR |= padmask;
    else
        EXTI->RTSR &= ~padmask;

    if (mode & PAL_EVENT_MODE_FALLING_EDGE)
        EXTI->FTSR |= padmask;
    else
        EXTI->FTSR &= ~padmask;

    EXTI->PR = padmask;

    /* Programming interrupt and event registers.*/
    EXTI->IMR |= padmask;
    EXTI->EMR &= ~padmask;
}

static void pad_enbale_interrupt(ioline_t pin) {
    switch (pin) {
        case 0:
            nvicEnableVector(EXTI0_IRQn, WB32_IRQ_EXTI0_PRIORITY);
            break;
        case 1:
            nvicEnableVector(EXTI1_IRQn, WB32_IRQ_EXTI1_PRIORITY);
            break;
        case 2:
            nvicEnableVector(EXTI2_IRQn, WB32_IRQ_EXTI2_PRIORITY);
            break;
        case 3:
            nvicEnableVector(EXTI3_IRQn, WB32_IRQ_EXTI3_PRIORITY);
            break;
        case 4:
            nvicEnableVector(EXTI4_IRQn, WB32_IRQ_EXTI4_PRIORITY);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            nvicEnableVector(EXTI9_5_IRQn, WB32_IRQ_EXTI5_9_PRIORITY);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            nvicEnableVector(EXTI15_10_IRQn, WB32_IRQ_EXTI10_15_PRIORITY);
            break;
    }
}

bool low_vol_offed_sleep;

static void exti_init(void) {
    if (!low_vol_offed_sleep) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            gpio_set_pin_output_open_drain(col_pins[col]);
            gpio_write_pin_low(col_pins[col]);
        }

        for (int row = 0; row < MATRIX_ROWS; row++) {
            gpio_set_pin_input_high(row_pins[row]);
            waitInputPinDelay();
            _pal_lld_enablepadevent(PAL_PORT(row_pins[row]), PAL_PAD(row_pins[row]), PAL_EVENT_MODE_BOTH_EDGES);
            pad_enbale_interrupt(PAL_PAD(row_pins[row]));
        }

#    if defined(MM_BT_MODE_PIN) && defined(MM_2G4_MODE_PIN)
        gpio_set_pin_input_high(MM_BT_MODE_PIN);
        _pal_lld_enablepadevent(PAL_PORT(MM_BT_MODE_PIN), PAL_PAD(MM_BT_MODE_PIN), PAL_EVENT_MODE_BOTH_EDGES);
        pad_enbale_interrupt(PAL_PAD(MM_BT_MODE_PIN));
        gpio_set_pin_input_high(MM_2G4_MODE_PIN);
        _pal_lld_enablepadevent(PAL_PORT(MM_2G4_MODE_PIN), PAL_PAD(MM_2G4_MODE_PIN), PAL_EVENT_MODE_BOTH_EDGES);
        pad_enbale_interrupt(PAL_PAD(MM_2G4_MODE_PIN));
#    endif

#    ifdef ENCODER_ENABLE
        gpio_set_pin_input_high(C13);
        _pal_lld_enablepadevent(PAL_PORT(C13), PAL_PAD(C13), PAL_EVENT_MODE_BOTH_EDGES);
        pad_enbale_interrupt(PAL_PAD(C13));
#    endif
    } else {
#    ifdef MM_CABLE_PIN
        gpio_set_pin_input_high(MM_CABLE_PIN);
        _pal_lld_enablepadevent(PAL_PORT(MM_CABLE_PIN), PAL_PAD(MM_CABLE_PIN), PAL_EVENT_MODE_BOTH_EDGES);
        pad_enbale_interrupt(PAL_PAD(MM_CABLE_PIN));
#    endif
    }
}

static void stop_mode_entry(void) {
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

#    if 1
    EXTI->PR = 0x7FFFF;
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 32; j++) {
            if (NVIC->ISPR[i] & (0x01UL < j)) {
                NVIC->ICPR[i] = (0x01UL < j);
            }
        }
    }
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk; // Clear Systick IRQ Pending
#    endif

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

OSAL_IRQ_HANDLER(WB32_EXTI0_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR0) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR0);
    }

    NVIC_DisableIRQ(EXTI0_IRQn);

    EXTI->PR = EXTI_PR_PR0;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI1_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR1) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR1);
    }

    NVIC_DisableIRQ(EXTI1_IRQn);

    EXTI->PR = EXTI_PR_PR1;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI2_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR2) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR2);
    }

    NVIC_DisableIRQ(EXTI2_IRQn);

    EXTI->PR = EXTI_PR_PR2;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI3_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR3) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR3);
    }

    NVIC_DisableIRQ(EXTI3_IRQn);

    EXTI->PR = EXTI_PR_PR3;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI4_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR4) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR4);
    }

    NVIC_DisableIRQ(EXTI4_IRQn);

    EXTI->PR = EXTI_PR_PR4;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI9_5_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR5) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR5);
    }

    if ((EXTI->PR & EXTI_PR_PR6) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR6);
    }

    if ((EXTI->PR & EXTI_PR_PR7) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR7);
    }

    if ((EXTI->PR & EXTI_PR_PR8) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR8);
    }

    if ((EXTI->PR & EXTI_PR_PR9) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR9);
    }

    NVIC_DisableIRQ(EXTI9_5_IRQn);

    EXTI->PR = EXTI_PR_PR5 | EXTI_PR_PR6 | EXTI_PR_PR7 | EXTI_PR_PR8 | EXTI_PR_PR9;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(WB32_EXTI15_10_IRQ_VECTOR) {
    OSAL_IRQ_PROLOGUE();

    if ((EXTI->PR & EXTI_PR_PR10) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR10);
    }

    if ((EXTI->PR & EXTI_PR_PR11) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR11);
    }

    if ((EXTI->PR & EXTI_PR_PR12) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR12);
    }

    if ((EXTI->PR & EXTI_PR_PR13) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR13);
    }

    if ((EXTI->PR & EXTI_PR_PR14) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR14);
    }

    if ((EXTI->PR & EXTI_PR_PR15) != 0) {
        EXTI->IMR &= ~(EXTI_IMR_MR15);
    }

    NVIC_DisableIRQ(EXTI15_10_IRQn);

    EXTI->PR = EXTI_PR_PR10 | EXTI_PR_PR11 | EXTI_PR_PR12 | EXTI_PR_PR13 | EXTI_PR_PR14 | EXTI_PR_PR15;

    //   exti_serve_irq(pr, 0);

    OSAL_IRQ_EPILOGUE();
}

#endif

#if defined(WAKEUP_RESET) && defined(BOOTMAGIC_LITE)
void bootmagic_lite(void) {
    if (PWR->GPREG0 != 0x5AA5) {
        // We need multiple scans because debouncing can't be turned off.
        matrix_scan();
#    if defined(DEBOUNCE) && DEBOUNCE > 0
        wait_ms(DEBOUNCE * 2);
#    else
        wait_ms(30);
#    endif
        matrix_scan();

        // If the configured key (commonly Esc) is held down on power up,
        // reset the EEPROM valid state and jump to bootloader.
        // This isn't very generalized, but we need something that doesn't
        // rely on user's keymaps in firmware or EEPROM.
        uint8_t row = BOOTMAGIC_LITE_ROW;
        uint8_t col = BOOTMAGIC_LITE_COLUMN;

#    if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_LITE_ROW_RIGHT) && defined(BOOTMAGIC_LITE_COLUMN_RIGHT)
        if (!is_keyboard_left()) {
            row = BOOTMAGIC_LITE_ROW_RIGHT;
            col = BOOTMAGIC_LITE_COLUMN_RIGHT;
        }
#    endif

        if (matrix_get_row(row) & (1 << col)) {
            eeconfig_disable();

            // Jump to bootloader.
            bootloader_jump();
        }
    }

    PWR->GPREG0 = 0x5AA5;
}
#endif
