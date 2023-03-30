/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _DREQ_H_
#define _DREQ_H_

#define DREQ_PIO0_TX0 0x0
#define DREQ_PIO0_TX1 0x1
#define DREQ_PIO0_TX2 0x2
#define DREQ_PIO0_TX3 0x3
#define DREQ_PIO0_RX0 0x4
#define DREQ_PIO0_RX1 0x5
#define DREQ_PIO0_RX2 0x6
#define DREQ_PIO0_RX3 0x7
#define DREQ_PIO1_TX0 0x8
#define DREQ_PIO1_TX1 0x9
#define DREQ_PIO1_TX2 0xa
#define DREQ_PIO1_TX3 0xb
#define DREQ_PIO1_RX0 0xc
#define DREQ_PIO1_RX1 0xd
#define DREQ_PIO1_RX2 0xe
#define DREQ_PIO1_RX3 0xf
#define DREQ_SPI0_TX 0x10
#define DREQ_SPI0_RX 0x11
#define DREQ_SPI1_TX 0x12
#define DREQ_SPI1_RX 0x13
#define DREQ_UART0_TX 0x14
#define DREQ_UART0_RX 0x15
#define DREQ_UART1_TX 0x16
#define DREQ_UART1_RX 0x17
#define DREQ_PWM_WRAP0 0x18
#define DREQ_PWM_WRAP1 0x19
#define DREQ_PWM_WRAP2 0x1a
#define DREQ_PWM_WRAP3 0x1b
#define DREQ_PWM_WRAP4 0x1c
#define DREQ_PWM_WRAP5 0x1d
#define DREQ_PWM_WRAP6 0x1e
#define DREQ_PWM_WRAP7 0x1f
#define DREQ_I2C0_TX 0x20
#define DREQ_I2C0_RX 0x21
#define DREQ_I2C1_TX 0x22
#define DREQ_I2C1_RX 0x23
#define DREQ_ADC 0x24
#define DREQ_XIP_STREAM 0x25
#define DREQ_XIP_SSITX 0x26
#define DREQ_XIP_SSIRX 0x27

#endif // _DREQ_H_
