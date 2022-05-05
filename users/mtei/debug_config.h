// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

// clang-format off

#pragma once

#ifdef AVR_UART_TX
#    ifndef __ASSEMBLER__
__attribute__((weak)) void send_avr_uart_tx(uint8_t data);
__attribute__((weak)) void init_avr_uart_tx(uint16_t data);
#    define DEBUG_UART_LOG(x)      if (send_avr_uart_tx != NULL) { send_avr_uart_tx(x); }
#    define DEBUG_UART_LOG_INIT(x) if (init_avr_uart_tx != NULL) { init_avr_uart_tx(x); }
#    endif
#endif

#ifdef KEYBOARD_helix_rev3_5rows
#    define MATRIX_DELAY_DEBUG_PIN B5
#endif
