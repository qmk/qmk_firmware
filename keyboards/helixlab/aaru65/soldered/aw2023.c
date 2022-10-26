// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "aw2023.h"
#include "i2c_master.h"

void aw2023_init(void) {
    i2c_init();
    aw2023_reset();
    // Set GCR1.CHIPEN=1 to enable the device
    uint8_t config = 0x01;
    i2c_writeReg(AW2023_ADDRESS, GCR1, &config, sizeof(config), AW2023_TIMEOUT);
    aw2023_limit_current(IMAX_10MA);
}

void aw2023_reset(void) {
    // Reset control. Write 0x55 will reset internal logic and register
    uint8_t config = 0x55;
    i2c_writeReg(AW2023_ADDRESS, RSTR, &config, sizeof(config), AW2023_TIMEOUT);
}

void aw2023_limit_current(uint8_t current) {
    i2c_writeReg(AW2023_ADDRESS, GCR2, &current, sizeof(current), AW2023_TIMEOUT);
}

void aw2023_led_switch(bool led0_enable, bool led1_enable, bool led2_enable) {
    uint8_t led0_config, led1_config, led2_config, lctr_config;
    led0_config = led0_enable ? LED0_ON : LED0_OFF;
    led1_config = led1_enable ? LED1_ON : LED1_OFF;
    led2_config = led2_enable ? LED2_ON : LED2_OFF;
    lctr_config = led0_config | led1_config | led2_config;
    i2c_writeReg(AW2023_ADDRESS, LCTR, &lctr_config, sizeof(lctr_config), AW2023_TIMEOUT);
}

void aw2023_led_timing(uint8_t led, uint8_t t0, uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t repeat) {
    uint8_t led_t0_config = t1 | t2;
    uint8_t led_t1_config = t3 | t4;
    uint8_t led_t2_config = t0 | repeat;
    switch (led) {
        case LED0:
            i2c_writeReg(AW2023_ADDRESS, LED0T0, &led_t0_config, sizeof(led_t0_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED0T1, &led_t1_config, sizeof(led_t1_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED0T2, &led_t2_config, sizeof(led_t2_config), AW2023_TIMEOUT);
            break;
        case LED1:
            i2c_writeReg(AW2023_ADDRESS, LED1T0, &led_t0_config, sizeof(led_t0_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED1T1, &led_t1_config, sizeof(led_t1_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED1T2, &led_t2_config, sizeof(led_t2_config), AW2023_TIMEOUT);
            break;
        case LED2:
            i2c_writeReg(AW2023_ADDRESS, LED2T0, &led_t0_config, sizeof(led_t0_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED2T1, &led_t1_config, sizeof(led_t1_config), AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED2T2, &led_t2_config, sizeof(led_t2_config), AW2023_TIMEOUT);
            break;
        default:
            break;
    }
}

void aw2023_led_config(uint8_t led, bool fadeOut_enable, bool fadeIn_enable, bool mode, uint8_t current) {
    uint8_t fadeOut_enable_config, fadeIn_enable_config, mode_config, lcfg_config;
    switch (led) {
        case LED0:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG0, &lcfg_config, sizeof(lcfg_config), AW2023_TIMEOUT);
            break;
        case LED1:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG1, &lcfg_config, sizeof(lcfg_config), AW2023_TIMEOUT);
            break;
        case LED2:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG2, &lcfg_config, sizeof(lcfg_config), AW2023_TIMEOUT);
        default:
            break;
    }
}

void aw2023_led_pwm(uint8_t led, uint8_t pwm) {
    uint8_t led_pwm_config = pwm;
    switch (led) {
        case LED0:
            i2c_writeReg(AW2023_ADDRESS, PWM0, &led_pwm_config, sizeof(led_pwm_config), AW2023_TIMEOUT);
            break;
        case LED1:
            i2c_writeReg(AW2023_ADDRESS, PWM1, &led_pwm_config, sizeof(led_pwm_config), AW2023_TIMEOUT);
            break;
        case LED2:
            i2c_writeReg(AW2023_ADDRESS, PWM2, &led_pwm_config, sizeof(led_pwm_config), AW2023_TIMEOUT);
            break;
        default:
            break;
    }
}