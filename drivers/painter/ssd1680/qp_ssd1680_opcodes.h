// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter SSD1680 command opcodes
#define SSD1680_NOP 0x00
#define SSD1680_RESOLUTION 0x01
#define SSD1680_GATE_VOLTAGE 0x03
#define SSD1680_SOURCE_VOLTAGE 0x04
#define SSD1680_DATA_ENTRY_MODE 0x11
#define SSD1680_SOFT_RESET 0x12
#define SSD1680_TEMP_SENSOR 0x18
#define SSD1680_DISPLAY_REFRESH 0x20
#define SSD1680_DISPLAY_UPDATE_CONTROL 0x21
#define SSD1680_UPDATE_MODE 0x22
#define SSD1680_SEND_BLACK 0x24
#define SSD1680_SEND_RED 0x26
#define SSD1680_VCOM_VOLTAGE 0x2C
#define SSD1680_BORDER_CONTROL 0x3C
#define SSD1680_RAM_X_SIZE 0x44
#define SSD1680_RAM_Y_SIZE 0x45
#define SSD1680_RAM_X_COUNTER 0x4E
#define SSD1680_RAM_Y_COUNTER 0x4F
