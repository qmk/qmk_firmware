//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "atomic_util.h"
#include "gpio.h"

#define LED_HC595_ST_PIN B5  //74HC595 storage register clock input
#define LED_HC595_SH_PIN B4  //74HC595 shift register clock input
#define LED_HC595_DS B3   // 74HC595 serial data input

/*
 *LED display driver.74HC595 Serial to parallel control LED field on/off.
 *  data(default):1-on/0-off (left low bit)
 *    bit0 --- NUM indicator
 *    bit1 --- CAPS indicator
 *    bit2 --- SCR indicator
 *    bit3 --- WinLock indicator
 *    bit4 --- Skyloong LOGO display
 *    bit5 --- Win layer indicator
 *    bit6 --- MAC layer indicator
 */
#define NUM_ON 0b10000000
#define CAPS_ON 0b01000000
#define SCR_ON 0b00100000
#define WINLK_ON 0b00010000
#define SKYLOONG 0b00001000
#define WIN_ON 0b00000010
#define MAC_ON 0b00000100

void s_serial_to_parallel(uint8_t data);
