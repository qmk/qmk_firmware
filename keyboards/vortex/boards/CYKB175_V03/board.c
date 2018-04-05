/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio
                        (C) 2018 Charlie Waters

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
    // GPIO A
    .setup[0] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL1)) |
            (1 << PAL_PAD(LINE_COL2)) |
            (1 << PAL_PAD(LINE_COL6)) |
            (1 << PAL_PAD(LINE_COL7)) |
            (1 << PAL_PAD(LINE_COL8)),
        .INE =
            (1 << PAL_PAD(LINE_ROW1)) |
            (1 << PAL_PAD(LINE_ROW2)) |
            (1 << PAL_PAD(LINE_ROW8)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_COL6) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_COL7) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_COL8) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW1) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW2) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW8) << 2)),
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_COL1) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_COL2) - 8) << 2)),
    },
    // GPIO B
    .setup[1] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL3)) |
            (1 << PAL_PAD(LINE_COL5)) |
            (1 << PAL_PAD(LINE_SPICS)),
        .INE = 0x0000,
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_SPICS) << 2)) |
            (AFIO_SPI << (PAD_SPI_SCK << 2)),
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_COL3) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_COL5) - 8) << 2)) |
            (AFIO_SPI << ((PAD_SPI_MOSI - 8) << 2)) |
            (AFIO_SPI << ((PAD_SPI_MISO - 8) << 2)),
    },
    // GPIO C
    .setup[2] = {
        .DIR = 0x0000,
        .INE =
            (1 << PAL_PAD(LINE_ROW3)) |
            (1 << PAL_PAD(LINE_ROW4)) |
            (1 << PAL_PAD(LINE_ROW5)) |
            (1 << PAL_PAD(LINE_ROW6)) |
            (1 << PAL_PAD(LINE_ROW7)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] = 0x00000000,
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW3) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW4) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW5) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW6) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW7) - 8) << 2)),
    },
    // GPIO D
    .setup[3] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL4)),
        .INE = 0x0000,
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_COL4) << 2)),
        .CFG[1] = 0x00000000,
    },
    .ESSR[0] = 0x00000000,
    .ESSR[1] = 0x00000000,
};

const ioline_t row_list[MATRIX_ROWS] = {
    LINE_COL1,
    LINE_COL2,
    LINE_COL3,
    LINE_COL4,
    LINE_COL5,
    LINE_COL6,
    LINE_COL7,
    LINE_COL8,
};

const ioline_t col_list[MATRIX_COLS] = {
    LINE_ROW1,
    LINE_ROW2,
    LINE_ROW3,
    LINE_ROW4,
    LINE_ROW5,
    LINE_ROW6,
    LINE_ROW7,
    LINE_ROW8,
};

void __early_init(void) {
    ht32_clock_init();
}

void spi_init(void) {
    static const SPIConfig config = {
        .end_cb = NULL,
        .cr0 = SPI_CR0_SELOEN,
        .cr1 = 8 | SPI_CR1_FORMAT_MODE0 | SPI_CR1_MODE,
        .cpr = 1,
        .fcr = 0,
    };
    spiStart(&SPID1, &config);
    palSetLine(LINE_SPICS);
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
    spi_init();
}

const uint8_t bootloader_magic[] __attribute__ ((section (".magic.bootloader"))) = {
    0x40, 0x50, 0x04, 0x03, // builtin bootloader will fail if this word is not correct
    0x01, 0x00, 0x00, 0x34,
    0x04, 0x00, 0x02, 0x00,
};
