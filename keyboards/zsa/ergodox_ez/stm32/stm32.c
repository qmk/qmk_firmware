// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ergodox_ez.h"
#include <ch.h>
#include <hal.h>

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

void ergodox_right_led_1_on(void) {
#ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 2, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_1_duty));
#else
    pwmEnableChannel(&PWMD8, 2, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_1_duty));
#endif
}

void ergodox_right_led_1_off(void) {
#ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 2);
#else
    pwmDisableChannel(&PWMD8, 2);
#endif
}

void ergodox_right_led_1_set(uint8_t level) {
    ergodox_right_led_1_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
    if (level == 0) {
        ergodox_right_led_1_off();
    } else {
        ergodox_right_led_1_on();
    }
}

void ergodox_right_led_2_on(void) {
#ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 3, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_2_duty));
#else
    pwmEnableChannel(&PWMD8, 1, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_2_duty));
#endif
}

void ergodox_right_led_2_off(void) {
#ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 3);
#else
    pwmDisableChannel(&PWMD8, 1);
#endif
}

void ergodox_right_led_2_set(uint8_t level) {
    ergodox_right_led_2_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
    if (level == 0) {
        ergodox_right_led_2_off();
    } else {
        ergodox_right_led_2_on();
    }
}

void ergodox_right_led_3_on(void) {
#ifdef REMAPPED_LEDS
    pwmEnableChannel(&PWMD3, 0, PWM_FRACTION_TO_WIDTH(&PWMD3, 0xFFFF, ergodox_right_led_3_duty));
#else
    pwmEnableChannel(&PWMD8, 0, PWM_FRACTION_TO_WIDTH(&PWMD8, 0xFFFF, ergodox_right_led_3_duty));
#endif
}
void ergodox_right_led_3_off(void) {
#ifdef REMAPPED_LEDS
    pwmDisableChannel(&PWMD3, 0);
#else
    pwmDisableChannel(&PWMD8, 0);
#endif
}

void ergodox_right_led_3_set(uint8_t level) {
    ergodox_right_led_3_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / 255));
    if (level == 0) {
        ergodox_right_led_3_off();
    } else {
        ergodox_right_led_3_on();
    }
}

void keyboard_post_init_sub(void) {
#ifdef REMAPPED_LEDS
    pwmStart(&PWMD3, &pwmCFG);
    palSetPadMode(GPIOB, 0, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 1, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 4, PAL_MODE_ALTERNATE(2) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
#else
    pwmStart(&PWMD8, &pwmCFG);
    palSetPadMode(GPIOB, 5, PAL_MODE_ALTERNATE(3) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 4, PAL_MODE_ALTERNATE(4) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
    palSetPadMode(GPIOB, 3, PAL_MODE_ALTERNATE(4) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_PUPDR_FLOATING);
#endif


    ergodox_right_led_1_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_right_led_2_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_right_led_3_set((uint8_t)keyboard_config.led_level * 255 / 4);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

#ifdef BOOTLOADER_CUSTOM
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
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/*   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_3,  C1_3,  C3_3}, // LED1 on right
    {0, C2_4,  C1_4,  C3_4}, // LED2
    {0, C2_5,  C1_5,  C3_5}, // LED3
    {0, C2_6,  C1_6,  C3_6}, // LED4
    {0, C2_7,  C1_7,  C3_7}, // LED5
    {0, C2_8,  C1_8,  C3_8}, // LED6
    {0, C8_1,  C7_1,  C9_1}, // LED7
    {0, C8_2,  C7_2,  C9_2}, // LED8
    {0, C8_3,  C7_3,  C9_3}, // LED9
    {0, C8_4,  C7_4,  C9_4}, // LED10
    {0, C8_5,  C7_5,  C9_5}, // LED11
    {0, C8_6,  C7_6,  C9_6}, // LED12
    {0, C2_11, C1_11, C3_11}, // LED13
    {0, C2_12, C1_12, C3_12}, // LED14
    {0, C2_13, C1_13, C3_13}, // LED15
    {0, C2_14, C1_14, C3_14}, // LED16
    {0, C2_15, C1_15, C3_15}, // LED17
    {0, C2_16, C1_16, C3_16}, // LED18

    {0, C8_9,  C7_9,  C9_9}, // LED19
    {0, C8_10, C7_10, C9_10}, // LED20
    {0, C8_11, C7_11, C9_11}, // LED21
    {0, C8_12, C7_12, C9_12}, // LED22
    {0, C8_13, C7_13, C9_13}, // LED23
    {0, C8_14, C7_14, C9_14}, // LED24

    {1, C3_1,  C2_1,  C4_1}, // LED1 on left
    {1, C6_1,  C5_1,  C7_1}, // LED2
    {1, C4_2,  C3_2,  C5_2}, // LED3
    {1, C7_2,  C6_2,  C8_2}, // LED4
    {1, C2_3,  C1_3,  C3_3}, // LED5
    {1, C5_3,  C4_3,  C6_3}, // LED6
    {1, C8_3,  C7_3,  C9_3}, // LED7
    {1, C2_4,  C1_4,  C3_4}, // LED8
    {1, C6_4,  C5_4,  C7_4}, // LED9
    {1, C2_5,  C1_5,  C3_5}, // LED10
    {1, C7_5,  C6_5,  C8_5}, // LED11
    {1, C2_6,  C1_6,  C3_6}, // LED12
    {1, C5_6,  C4_6,  C6_6}, // LED13
    {1, C8_6,  C7_6,  C9_6}, // LED14
    {1, C2_7,  C1_7,  C3_7}, // LED15
    {1, C5_7,  C4_7,  C6_7}, // LED16
    {1, C2_8,  C1_8,  C3_8}, // LED17
    {1, C5_8,  C4_8,  C6_8}, // LED18

    {1, C3_9,  C2_9,  C4_9}, // LED19
    {1, C6_9,  C5_9,  C7_9}, // LED20
    {1, C4_10, C3_10, C5_10}, // LED21
    {1, C7_10, C6_10, C8_10}, // LED22
    {1, C2_11, C1_11, C3_11}, // LED23
    {1, C5_11, C4_11, C6_11} // LED24
};
// clang-format on

#endif
