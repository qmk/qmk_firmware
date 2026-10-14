// Copyright 2020 Yaotian Feng / Codetector
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void early_hardware_init_post(void) {
    // DIP Switch
    palSetLineMode(LINE_DIP0, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);

    // Matrix GPIOs. A0 and A11 to A14 are reset and debug pins by default and need
    // function 1 to be GPIO, which is why the matrix is set up here and scanned in matrix.c.
    // Columns
    palSetLineMode(B28, MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B31, MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A22, MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B29, MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A11, MODE_FUNC_ALT1 | MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A12, MODE_FUNC_ALT1 | MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A13, MODE_FUNC_ALT1 | MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A14, MODE_FUNC_ALT1 | MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B13, MODE_DIR_OUT | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);

    // Rows
    palSetLineMode(B25, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A0 , MODE_FUNC_ALT1 | MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B20, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A5 , MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(A7 , MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B19, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B23, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);
    palSetLineMode(B24, MODE_DIR_IN | MODE_MODE_PULL_UP | MODE_AD_DIGITAL);

    // Peripherals
    palSetLineMode(LINE_SSP1_MOSI, MODE_FUNC_ALT2 | MODE_AD_DIGITAL); // SSP1 MOSI
    palSetLineMode(LINE_SSP1_MISO, MODE_FUNC_ALT2 | MODE_AD_DIGITAL); // SSP1 MISO
    palSetLineMode(LINE_SSP1_SCK, MODE_FUNC_ALT3 | MODE_AD_DIGITAL);  // SSP1 SCK
    palSetLineMode(LINE_LED1_CS, MODE_DIR_OUT | MODE_AD_DIGITAL);
    palSetLineMode(LINE_LED2_CS, MODE_DIR_OUT | MODE_AD_DIGITAL);

    palSetLineMode(LINE_UART_RX, MODE_FUNC_ALT2 | MODE_AD_DIGITAL);
    palSetLineMode(LINE_UART_TX, MODE_FUNC_ALT2 | MODE_AD_DIGITAL);

    palSetLineMode(LINE_BLE_RSTN, MODE_DIR_OUT | MODE_AD_DIGITAL);
    palClearLine(LINE_BLE_RSTN);

    // Analog
    palSetLineMode(LINE_ADC_BAT, MODE_FUNC_ALT2 | MODE_AD_ANALOG);
}
