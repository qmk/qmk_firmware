// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/*Device address*/
#define AW2023_ADDRESS (0x45 << 1)
/*registers*/
/*RSTR, Chip ID and Software Reset Register*/
#define RSTR 0x00
/*GCR1, Global Control Registe*/
#define GCR1 0x01
/*Chip Status Register*/
#define CSR 0x02
/*Pattern Status Register*/
#define PATST 0x03
/*LED Maximum Current Register*/
#define GCR2 0x04
/*LED Control Register*/
#define LCTR 0x30
/*LED0-2 Mode Configuration Registe*/
#define LCFG0 0x31
#define LCFG1 0x32
#define LCFG2 0x33
/*LED0-2 PWM Dimming Level Register*/
#define PWM0 0x34
#define PWM1 0x35
#define PWM2 0x36
/*LED0-2 T1 & T2 Configuration Registe*/
#define LED0T0 0x37
#define LED1T0 0x3A
#define LED2T0 0x3D
/*LED0-2 T3 & T4 Configuration Register*/
#define LED0T1 0x38
#define LED1T1 0x3B
#define LED2T1 0x3E
/*LED0-2 T0 & Repeat Times Configuration Registe*/
#define LED0T2 0x39
#define LED1T2 0x3C
#define LED2T2 0x3F

/*IMAX defines*/
#define IMAX_15MA 0x00
#define IMAX_30MA 0x01
#define IMAX_5MA 0x02
#define IMAX_10MA 0x04

/*LED switch defines*/
#define LED0_OFF 0x00
#define LED0_ON 0x01 /*0b1*/
#define LED1_OFF 0x00
#define LED1_ON 0x02 /*0b10*/
#define LED2_OFF 0x00
#define LED2_ON 0x04 /*0b100*/

#define LED_ON true
#define LED_OFF false

#define LED0 0x01
#define LED1 0x02
#define LED2 0x03

/*LED configuration defines*/
#define LED_FADEIN_DISABLE 0x00
#define LED_FADEIN_ENABLE 0x40
#define LED_FADEOUT_DISABLE 0x00
#define LED_FADEOUT_ENABLE 0x20

#define FADEIN_ENABLE true
#define FADEIN_DISABLE false
#define FADEOUT_ENABLE true
#define FADEOUT_DISABLE false

#define LED_MODE_MANUAL 0x00
#define LED_MODE_PATTERN 0x10

#define MODE_PATTERN true
#define MODE_MANUAL false

/*Single LED current*/
#define LED_CURRENT_MAX 0x0F
#define LED_CURRENT_14 0x0E
#define LED_CURRENT_13 0x0D
#define LED_CURRENT_12 0x0C
#define LED_CURRENT_11 0x0B
#define LED_CURRENT_10 0x0A
#define LED_CURRENT_9 0x09
#define LED_CURRENT_HALF 0x08
#define LED_CURRENT_7 0x07
#define LED_CURRENT_6 0x06
#define LED_CURRENT_5 0x05
#define LED_CURRENT_4 0x04
#define LED_CURRENT_3 0x03
#define LED_CURRENT_2 0x02
#define LED_CURRENT_MIN 0x01
#define LED_CURRENT_UNSET 0x00

/*Timer parameters
*/
/*
              --------
           ╱            ╲
         ╱                ╲
--------                    --------
|  T0  |  T1  |  T2  |  T3  |  T4  |
*/

/*T0 (delay time of pattern startup) selection*/
#define T0_UNSET 0x00
#define T0_40MS 0x00
#define T0_130MS 0x10
#define T0_260MS 0x20
#define T0_380MS 0x30
#define T0_510MS 0x40
#define T0_770MS 0x50
#define T0_1040MS 0x60
#define T0_1600MS 0x70
#define T0_2100MS 0x80
#define T0_2600MS 0x90
#define T0_3100MS 0xA0
#define T0_4200MS 0xB0
#define T0_5200MS 0xC0
#define T0_6200MS 0xD0
#define T0_7300MS 0xE0
#define T0_8300MS 0xF0
/*T1 (Rise-time) selection*/
#define T1_UNSET 0x00
#define T1_0MS 0x00
#define T1_130MS 0x10
#define T1_260MS 0x20
#define T1_380MS 0x30
#define T1_510MS 0x40
#define T1_770MS 0x50
#define T1_1040MS 0x60
#define T1_1600MS 0x70
#define T1_2100MS 0x80
#define T1_2600MS 0x90
#define T1_3100MS 0xA0
#define T1_4200MS 0xB0
#define T1_5200MS 0xC0
#define T1_6200MS 0xD0
#define T1_7300MS 0xE0
#define T1_8300MS 0xF0
/*T2 (On-time) selection*/
#define T2_UNSET 0x00
#define T2_40MS 0x00
#define T2_130MS 0x01
#define T2_260MS 0x02
#define T2_380MS 0x03
#define T2_510MS 0x04
#define T2_770MS 0x05
#define T2_1040MS 0x06
#define T2_1600MS 0x07
#define T2_2100MS 0x08
#define T2_2600MS 0x09
#define T2_3100MS 0x0A
#define T2_4200MS 0x0B
#define T2_5200MS 0x0C
#define T2_6200MS 0x0D
#define T2_7300MS 0x0E
#define T2_8300MS 0x0F
/*T3 (Fall-time) selection*/
#define T3_UNSET 0x00
#define T3_0MS 0x00
#define T3_130MS 0x10
#define T3_260MS 0x20
#define T3_380MS 0x30
#define T3_510MS 0x40
#define T3_770MS 0x50
#define T3_1040MS 0x60
#define T3_1600MS 0x70
#define T3_2100MS 0x80
#define T3_2600MS 0x90
#define T3_3100MS 0xA0
#define T3_4200MS 0xB0
#define T3_5200MS 0xC0
#define T3_6200MS 0xD0
#define T3_7300MS 0xE0
#define T3_8300MS 0xF0
/*T4 (Off-time) selection*/
#define T4_UNSET 0x00
#define T4_40MS 0x00
#define T4_130MS 0x01
#define T4_260MS 0x02
#define T4_380MS 0x03
#define T4_510MS 0x04
#define T4_770MS 0x05
#define T4_1040MS 0x06
#define T4_1600MS 0x07
#define T4_2100MS 0x08
#define T4_2600MS 0x09
#define T4_3100MS 0x0A
#define T4_4200MS 0x0B
#define T4_5200MS 0x0C
#define T4_6200MS 0x0D
#define T4_7300MS 0x0E
#define T4_8300MS 0x0F

/*Pattern Repeat Times*/
#define REPEAT_UNSET 0x00
#define REPEAT_ENDLESS 0x00
#define REPEAT_ONCE 0x01
#define REPEAT_TWICE 0x02
#define REPEAT_THREE_TIMES 0x03
#define REPEAT_FOUR_TIMES 0x04
#define REPEAT_FIVE_TIMES 0x05

#define AW2023_TIMEOUT 100

void aw2023_init(void);
void aw2023_reset(void);
void aw2023_limit_current(uint8_t current);
void aw2023_led_switch(bool led0_enable, bool led1_enable, bool led2_enable);
void aw2023_led_timing(uint8_t led, uint8_t t0, uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t repeat);
void aw2023_led_config(uint8_t led, bool fadeOut_enable, bool fadeIn_enable, bool mode, uint8_t current);
void aw2023_led_pwm(uint8_t led, uint8_t pwm);