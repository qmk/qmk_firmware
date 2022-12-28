// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter IL91874 command opcodes
#define IL91874_PANEL_SETTING 0x00
#define IL91874_POWER_SETTING 0x01
#define IL91874_POWER_OFF 0x02
#define IL91874_POWER_OFF_SEQUENCE 0x03
#define IL91874_POWER_ON 0x04
#define IL91874_POWER_ON_MEASURE 0x05
#define IL91874_BOOSTER_SOFT_START 0x06
#define IL91874_DEEP_SLEEP 0x07
#define IL91874_SEND_BLACK 0x10
#define IL91874_DATA_STOP 0x11
#define IL91874_DISPLAY_REFRESH 0x12
#define IL91874_SEND_RED 0x13
#define IL91874_PDTM1 0x14
#define IL91874_PDTM2 0x15
#define IL91874_PDRF 0x16
#define IL91874_LUT1 0x20
#define IL91874_LUTWW 0x21
#define IL91874_LUTBW 0x22
#define IL91874_LUTWB 0x23
#define IL91874_LUTBB 0x24
#define IL91874_PLL 0x30
#define IL91874_CDI 0x50
#define IL91874_RESOLUTION 0x61
#define IL91874_VCM_DC_SETTING 0x82
#define IL91874_MISTERY_COMMAND 0xF8 // Undocummented command on Adafruit's sample code
