// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter SSD1351 command opcodes

// System function commands
#define SSD1351_SETCOLUMN 0x15
#define SSD1351_SETROW 0x75
#define SSD1351_WRITERAM 0x5C
#define SSD1351_READRAM 0x5D
#define SSD1351_SETREMAP 0xA0
#define SSD1351_STARTLINE 0xA1
#define SSD1351_DISPLAYOFFSET 0xA2
#define SSD1351_DISPLAYALLOFF 0xA4
#define SSD1351_DISPLAYALLON 0xA5
#define SSD1351_NORMALDISPLAY 0xA6
#define SSD1351_INVERTDISPLAY 0xA7
#define SSD1351_FUNCTIONSELECT 0xAB
#define SSD1351_DISPLAYOFF 0xAE
#define SSD1351_DISPLAYON 0xAF
#define SSD1351_PRECHARGE 0xB1
#define SSD1351_DISPLAYENHANCE 0xB2
#define SSD1351_CLOCKDIV 0xB3
#define SSD1351_SETVSL 0xB4
#define SSD1351_SETGPIO 0xB5
#define SSD1351_PRECHARGE2 0xB6
#define SSD1351_SETGRAY 0xB8
#define SSD1351_USELUT 0xB9
#define SSD1351_PRECHARGELEVEL 0xBB
#define SSD1351_VCOMH 0xBE
#define SSD1351_CONTRASTABC 0xC1
#define SSD1351_CONTRASTMASTER 0xC7
#define SSD1351_MUXRATIO 0xCA
#define SSD1351_COMMANDLOCK 0xFD
#define SSD1351_HORIZSCROLL 0x96
#define SSD1351_STOPSCROLL 0x9E
#define SSD1351_STARTSCROLL 0x9F

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SETREMAP (MADCTL) Flags
#define SSD1351_MADCTL_MY 0b00010000
#define SSD1351_MADCTL_MX 0b00000010
#define SSD1351_MADCTL_MV 0b00000001
#define SSD1351_MADCTL_RGB 0b01100000
#define SSD1351_MADCTL_BGR 0b01100100
