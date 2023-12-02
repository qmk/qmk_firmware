// Copyright 2023 foostan (@foostan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP12
#define SERIAL_USART_RX_PIN GP13
#define SPLIT_HAND_PIN GP21

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#define NOP_FUDGE 1

#define I2C_DRIVER I2CD1
#define OLED_UPDATE_INTERVAL 50

#define WS2812_DI_PIN GP10
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7
