// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

// clang-format off

#pragma once

#ifdef AVR_UART_TX
#    ifndef __ASSEMBLER__
__attribute__((weak)) void send_avr_uart_tx(uint8_t data);
__attribute__((weak)) void init_avr_uart_tx(uint16_t data);
#        define DEBUG_UART_LOG(x)      if (send_avr_uart_tx != NULL) { send_avr_uart_tx(x); }
#        define DEBUG_UART_LOG_INIT(x) if (init_avr_uart_tx != NULL) { init_avr_uart_tx(x); }
#    endif
#endif

#if defined(KEYBOARD_helix_rev3_5rows) || defined(KEYBOARD_helix_rev2)
#    ifdef MATRIX_OVERRIDE
#        define MATRIX_READ_COLS_DEBUG_PIN B5
#        ifdef ENCODER_ENABLE
#            error conflict MATRIX_READ_COLS_DEBUG_PIN and ENCODER_ENABLE
#        endif
#    endif
#endif

#ifdef MATRIX_READ_COLS_DEBUG_PIN
#    define DEBUG_PIN_INIT()  setPinOutput(MATRIX_READ_COLS_DEBUG_PIN);  writePinLow(MATRIX_READ_COLS_DEBUG_PIN)
#    define DEBUG_PIN_ON()    writePinHigh(MATRIX_READ_COLS_DEBUG_PIN)
#    define DEBUG_PIN_OFF()   writePinLow(MATRIX_READ_COLS_DEBUG_PIN)
#    define DEBUG_PIN_WAIT(n) wait_cpuclock(n);
#endif

#if defined(DIFF_HAND) && (defined(KEYBOARD_helix_rev3_5rows) || defined(KEYBOARD_helix_rev2))
    /* testing for different config left&right */
#    undef SPLIT_HAND_MATRIX_GRID
#    undef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
 /* #define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B3, B1, B2 } */
#    define SWITCH_MATRIX_INPUT_1 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (F0, 0xf0), \
      (B0, 0x0e) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (1, 0x08, 0x10), \
      (1, 0x02, 0x20), \
      (1, 0x04, 0x40) )

 /* #define MATRIX_ROW_PINS_RIGHT { D4, C6, E6, D7, B4 } */
#    define SWITCH_MATRIX_OUTPUT_1 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (D0, 0x90), \
      (C0, 0x40), \
      (E0, 0x40), \
      (B0, 0x10) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (2, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (3, 0x10, 0x10) )
#endif // DIFF_HAND && (KEYBOARD_helix_rev3_5rows || KEYBOARD_helix_rev2)
