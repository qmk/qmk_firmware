/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_VGABOARD_H
#define _BOARDS_VGABOARD_H

// For board detection
#define RASPBERRYPI_VGABOARD

// Audio pins. I2S BCK, LRCK are on the same pins as PWM L/R.
// - When outputting I2S, PWM sees BCK and LRCK, which should sound silent as
//   they are constant duty cycle, and above the filter cutoff
// - When outputting PWM, I2S DIN should be low, so I2S should remain silent.
#define VGABOARD_I2S_DIN_PIN 26
#define VGABOARD_I2S_BCK_PIN 27
#define VGABOARD_I2S_LRCK_PIN 28

#define VGABOARD_PWM_L_PIN 28
#define VGABOARD_PWM_R_PIN 27

#define VGABOARD_VGA_COLOR_PIN_BASE 0
#define VGABOARD_VGA_SYNC_PIN_BASE 16

// Note DAT1/2 are shared with UART TX/RX (pull jumpers off header to access
// UART pins and disconnect SD DAT1/2)
#define VGABOARD_SD_CLK_PIN 5
#define VGABOARD_SD_CMD_PIN 18
#define VGABOARD_SD_DAT0_PIN 19

// Note buttons are shared with VGA colour LSBs -- if using VGA, you can float
// the pin on VSYNC assertion and sample on VSYNC deassertion
#define VGABOARD_BUTTON_A_PIN 0
#define VGABOARD_BUTTON_B_PIN 6
#define VGABOARD_BUTTON_C_PIN 11

#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 1
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 20
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 21
#endif

#ifndef PICO_SCANVIDEO_COLOR_PIN_BASE
#define PICO_SCANVIDEO_COLOR_PIN_BASE VGABOARD_VGA_COLOR_PIN_BASE
#endif

#ifndef PICO_SCANVIDEO_SYNC_PIN_BASE
#define PICO_SCANVIDEO_SYNC_PIN_BASE VGABOARD_VGA_SYNC_PIN_BASE
#endif

#ifndef PICO_SD_CLK_PIN
#define PICO_SD_CLK_PIN VGABOARD_SD_CLK_PIN
#endif

#ifndef PICO_SD_CMD_PIN
#define PICO_SD_CMD_PIN VGABOARD_SD_CMD_PIN
#endif

#ifndef PICO_SD_DAT0_PIN
#define PICO_SD_DAT0_PIN VGABOARD_SD_DAT0_PIN
#endif

// 1 or 4
#ifndef PICO_SD_DAT_PIN_COUNT
#define PICO_SD_DAT_PIN_COUNT 4
#endif

// 1 or -1
#ifndef PICO_SD_DAT_PIN_INCREMENT
#define PICO_SD_DAT_PIN_INCREMENT 1
#endif

#ifndef PICO_AUDIO_I2S_DATA_PIN
#define PICO_AUDIO_I2S_DATA_PIN VGABOARD_I2S_DIN_PIN
#endif
#ifndef PICO_AUDIO_I2S_CLOCK_PIN_BASE
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE VGABOARD_I2S_BCK_PIN
#endif

#ifndef PICO_AUDIO_PWM_L_PIN
#define PICO_AUDIO_PWM_L_PIN VGABOARD_PWM_L_PIN
#endif

#ifndef PICO_AUDIO_PWM_R_PIN
#define PICO_AUDIO_PWM_R_PIN VGABOARD_PWM_R_PIN
#endif

#define PICO_VGA_BOARD

// vgaboard has a Pico on it, so default anything we haven't set above
#include "boards/pico.h"

#endif
