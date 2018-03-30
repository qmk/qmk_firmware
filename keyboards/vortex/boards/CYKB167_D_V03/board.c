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
    .setup[0] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL1)) |
            (1 << PAL_PAD(LINE_COL2)) |
            (1 << PAL_PAD(LINE_COL3)) |
            (1 << PAL_PAD(LINE_COL4)),
        .INE =
            (1 << PAL_PAD(LINE_ROW3)) |
            (1 << PAL_PAD(LINE_ROW5)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_COL1) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_COL2) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_COL3) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_COL4) << 2)),
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW3) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW5) - 8) << 2)),
    },
    .setup[1] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL5)),
        .INE =
            (1 << PAL_PAD(LINE_ROW4)) |
            (1 << PAL_PAD(LINE_ROW6)) |
            (1 << PAL_PAD(LINE_ROW7)) |
            (1 << PAL_PAD(LINE_ROW8)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_ROW4) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW6) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW7) << 2)) |
            (AFIO_GPIO << (PAL_PAD(LINE_ROW8) << 2)),
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_COL5) - 8) << 2)),
    },
    .setup[2] = {
        .DIR =
            (1 << PAL_PAD(LINE_COL6)) |
            (1 << PAL_PAD(LINE_COL7)) |
            (1 << PAL_PAD(LINE_COL8)),
        .INE =
            (1 << PAL_PAD(LINE_ROW2)) |
            (1 << PAL_PAD(LINE_ROW9)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_ROW2) << 2)),
        .CFG[1] =
            (AFIO_GPIO << ((PAL_PAD(LINE_COL6) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_COL7) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_COL8) - 8) << 2)) |
            (AFIO_GPIO << ((PAL_PAD(LINE_ROW9) - 8) << 2)),
    },
    .setup[3] = {
        .DIR = 0x0000,
        .INE =
            (1 << PAL_PAD(LINE_ROW1)),
        .PU = 0x0000,
        .PD = 0x0000,
        .OD = 0x0000,
        .DRV = 0x0000,
        .LOCK = 0x0000,
        .OUT = 0x0000,
        .CFG[0] =
            (AFIO_GPIO << (PAL_PAD(LINE_ROW1) << 2)),
        .CFG[1] = 0x00000000,
    },
    .ESSR[0] = 0x00000000,
    .ESSR[1] = 0x00000000,
};

void __early_init(void) {
    ht32_clock_init();
}

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
    // SPI flash
    palSetGroupMode(GPIO_B, 0x7, 7, PAL_MODE_HT32_AF(AFIO_SPI)); // SPI1
    palSetLine(LINE_SPICS);
    palSetLineMode(LINE_SPICS, PAL_MODE_OUTPUT_PUSHPULL); // CS
}

const uint8_t bootloader_magic[] __attribute__ ((section (".magic.bootloader"))) = {
    0x00, 0x00, 0x04, 0x03,
    0x01, 0x00, 0x00, 0x34,
    0x04, 0x00, 0x02, 0x00,
};
