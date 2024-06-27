// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ergodox_ez.h"
#include <ch.h>
#include <hal.h>

#if HAL_USE_PWM == TRUE
static uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)    // if below 8% of max
        return v / 9; // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL) // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}

// clang-format off
static PWMConfig pwmCFG = {
    .frequency = 0xFFFF,
    .period = 256,
    .callback = NULL,
    .channels = {
#ifdef REMAPPED_LEDS
        { .mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // PB4
        { .mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        { .mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // PB0
        { .mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}  // PB1
#else
        { .mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // PB3
        { .mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // PB4
        { .mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL}, // PB5
        { .mode = PWM_OUTPUT_DISABLED, .callback = NULL}
#endif
    },
    .cr2  = 0,
    .dier = TIM_DIER_UDE
};
// clang-format on

static uint32_t ergodox_right_led_1_duty;
static uint32_t ergodox_right_led_2_duty;
static uint32_t ergodox_right_led_3_duty;
#endif

void ergodox_right_led_1_on(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 2, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_1_duty));
#    else
    pwmEnableChannel(&PWMD8, 2, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_1_duty));
#    endif
#else
    writePinHigh(ERGODOX_LED_1_PIN);
#endif
}

void ergodox_right_led_1_off(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 2);
#    else
    pwmDisableChannel(&PWMD8, 2);
#    endif
#else
    writePinLow(ERGODOX_LED_1_PIN);
#endif
}

void ergodox_right_led_1_set(uint8_t level) {
#if HAL_USE_PWM == TRUE
    ergodox_right_led_1_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
#endif
    if (level == 0) {
        ergodox_right_led_1_off();
    } else {
        ergodox_right_led_1_on();
    }
}

void ergodox_right_led_2_on(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 3, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_2_duty));
#    else
    pwmEnableChannel(&PWMD8, 1, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_2_duty));
#    endif
#else
    writePinHigh(ERGODOX_LED_2_PIN);
#endif
}

void ergodox_right_led_2_off(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 3);
#    else
    pwmDisableChannel(&PWMD8, 1);
#    endif
#else
    writePinLow(ERGODOX_LED_2_PIN);
#endif
}

void ergodox_right_led_2_set(uint8_t level) {
#if HAL_USE_PWM == TRUE
    ergodox_right_led_2_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
#endif
    if (level == 0) {
        ergodox_right_led_2_off();
    } else {
        ergodox_right_led_2_on();
    }
}

void ergodox_right_led_3_on(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 0, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_3_duty));
#    else
    pwmEnableChannel(&PWMD8, 1, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_3_duty));
#    endif
#else
    writePinHigh(ERGODOX_LED_3_PIN);
#endif
}
void ergodox_right_led_3_off(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 0);
#    else
    pwmDisableChannel(&PWMD8, 1);
#    endif
#else
    writePinLow(ERGODOX_LED_3_PIN);
#endif
}

void ergodox_right_led_3_set(uint8_t level) {
#if HAL_USE_PWM == TRUE
    ergodox_right_led_3_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
#endif
    if (level == 0) {
        ergodox_right_led_3_off();
    } else {
        ergodox_right_led_3_on();
    }
}

void keyboard_post_init_sub(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    pwmStart(&PWMD3, &pwmCFG);
    palSetPadMode(GPIOB, 0, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 1, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 4, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
#    else
    pwmStart(&PWMD8, &pwmCFG);
    palSetPadMode(GPIOB, 5, PAL_MODE_ALTERNATE(3) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 4, PAL_MODE_ALTERNATE(4) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 3, PAL_MODE_ALTERNATE(4) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
#    endif
#endif
    ergodox_right_led_1_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_right_led_2_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_right_led_3_set((uint8_t)keyboard_config.led_level * 255 / 4);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

void board_init(void) {
#if HAL_USE_PWM == TRUE
#    ifdef REMAPPED_LEDS
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
#    else
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
#    endif
#endif
}

#define APP_ADDRESS 0x08002000

__attribute__((weak)) void bootloader_jump(void) {
    // The ignition bootloader is checking for a high signal on A8 for 100ms when powering on the board.
    // Setting both A8 and A9 high will charge the capacitor quickly.
    // Setting A9 low before reset will cause the capacitor to discharge
    // thus making the bootloder unlikely to trigger twice between power cycles.
    setPinOutputPushPull(A9);
    setPinOutputPushPull(A8);
    writePinHigh(A9);
    writePinHigh(A8);
    wait_ms(500);
    writePinLow(A9);

    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    // When resetting the MCU, we want to jump to the application.
    SCB->AIRCR = APP_ADDRESS & 0xFFFF;

    // Set the stack pointer to the applications stack pointer
    __asm__ volatile("msr msp, %0" ::"g"(*(volatile uint32_t *)APP_ADDRESS));

    // Jump to the application
    (*(void (**)())(APP_ADDRESS + 4))();
    while (1)
        ;
}
