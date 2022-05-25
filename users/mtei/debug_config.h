// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

// clang-format off

#pragma once

#ifdef KEYBOARD_helix_rev3_5rows

#    ifdef AVR_UART_TX
#        ifndef __ASSEMBLER__
__attribute__((weak)) void send_avr_uart_tx(uint8_t data);
__attribute__((weak)) void init_avr_uart_tx(uint16_t data);
#        endif
#        define DEBUG_UART_LOG(x)      if (send_avr_uart_tx != NULL) { send_avr_uart_tx(x); }
#        define DEBUG_UART_LOG_INIT(x) if (init_avr_uart_tx != NULL) { init_avr_uart_tx(x); }
#    else
#        define DEBUG_UART_LOG(x)
#        define DEBUG_UART_LOG_INIT(x)
#    endif

#endif
