/*
    Copyright (C) 2020 Yaotian Feng, Codetector<codetector@codetector.cn>

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

#include "hal.h"

/* ============ Private Defines ===================== */

/* ============ Function Prototypes ================== */

#define PBIT(PORT, LINE) ((PAL_PORT(LINE) == PORT) ? (1 << PAL_PAD(LINE)) : 0)
#define PAFIO_L(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) < 8)) ? (AF << (PAL_PAD(LINE) << 2)) : 0)
#define PAFIO_H(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) >= 8)) ? (AF << ((PAL_PAD(LINE) - 8) << 2)) : 0)
#define PAFIO(PORT, N, LINE, AF) ((N) ? PAFIO_H(PORT, LINE, AF) : PAFIO_L(PORT, LINE, AF))

#define OUT_BITS(PORT) (PBIT(PORT, B5) | PBIT(PORT, B4) | PBIT(PORT, B3) | PBIT(PORT, B2) | PBIT(PORT, D1) | 0)

#define IN_BITS(PORT) (PBIT(PORT, C4) | PBIT(PORT, C5) | PBIT(PORT, D0) | PBIT(PORT, B15) | PBIT(PORT, C11) | PBIT(PORT, A15) | PBIT(PORT, C12) | PBIT(PORT, C13) | PBIT(PORT, A8) | PBIT(PORT, A10) | PBIT(PORT, A11) | PBIT(PORT, A14) | PBIT(PORT, D2) | PBIT(PORT, D3) | 0)

// Alternate Functions
#define AF_BITS(PORT, N) (PAFIO(PORT, N, LINE_UART_RX, AFIO_USART) | PAFIO(PORT, N, LINE_UART_TX, AFIO_USART) | PAFIO(PORT, N, LINE_BT_UART_TX, AFIO_USART) | PAFIO(PORT, N, LINE_BT_UART_RX, AFIO_USART) | PAFIO(PORT, N, B5, AFIO_GPIO) | PAFIO(PORT, N, B4, AFIO_GPIO) | PAFIO(PORT, N, B3, AFIO_GPIO) | PAFIO(PORT, N, B2, AFIO_GPIO) | PAFIO(PORT, N, D1, AFIO_GPIO) | PAFIO(PORT, N, C4, AFIO_GPIO) | PAFIO(PORT, N, C5, AFIO_GPIO) | PAFIO(PORT, N, D0, AFIO_GPIO) | PAFIO(PORT, N, B15, AFIO_GPIO) | PAFIO(PORT, N, C11, AFIO_GPIO) | PAFIO(PORT, N, A15, AFIO_GPIO) | PAFIO(PORT, N, C12, AFIO_GPIO) | PAFIO(PORT, N, C13, AFIO_GPIO) | PAFIO(PORT, N, A8, AFIO_GPIO) | PAFIO(PORT, N, A10, AFIO_GPIO) | PAFIO(PORT, N, A11, AFIO_GPIO) | PAFIO(PORT, N, A14, AFIO_GPIO) | PAFIO(PORT, N, D2, AFIO_GPIO) | PAFIO(PORT, N, D3, AFIO_GPIO) | 0)

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
    // GPIO A
    .setup[0] =
        {
            .DIR    = OUT_BITS(IOPORTA),
            .INE    = IN_BITS(IOPORTA),
            .PU     = IN_BITS(IOPORTA),
            .PD     = 0x0000,
            .OD     = 0x0000,
            .DRV    = 0x0000,
            .LOCK   = 0x0000,
            .OUT    = 0x0000,
            .CFG[0] = AF_BITS(IOPORTA, 0),
            .CFG[1] = AF_BITS(IOPORTA, 1),
        },
    // GPIO B
    .setup[1] =
        {
            .DIR    = OUT_BITS(IOPORTB),
            .INE    = IN_BITS(IOPORTB),
            .PU     = IN_BITS(IOPORTB),
            .PD     = 0x0000,
            .OD     = 0x0000,
            .DRV    = 0x0000,
            .LOCK   = 0x0000,
            .OUT    = 0x0000,
            .CFG[0] = AF_BITS(IOPORTB, 0),
            .CFG[1] = AF_BITS(IOPORTB, 1),
        },
    // GPIO C
    .setup[2] =
        {
            .DIR    = OUT_BITS(IOPORTC),
            .INE    = IN_BITS(IOPORTC),
            .PU     = IN_BITS(IOPORTC),
            .PD     = 0x0000,
            .OD     = 0x0000,
            .DRV    = 0x0000,
            .LOCK   = 0x0000,
            .OUT    = 0x0000,
            .CFG[0] = AF_BITS(IOPORTC, 0),
            .CFG[1] = AF_BITS(IOPORTC, 1),
        },
    // GPIO D
    .setup[3] =
        {
            .DIR    = OUT_BITS(IOPORTD),
            .INE    = IN_BITS(IOPORTD),
            .PU     = IN_BITS(IOPORTD),
            .PD     = 0x0000,
            .OD     = 0x0000,
            .DRV    = 0x0000,
            .LOCK   = 0x0000,
            .OUT    = 0x0000,
            .CFG[0] = AF_BITS(IOPORTD, 0),
            .CFG[1] = AF_BITS(IOPORTD, 1),
        },
    .ESSR[0] = 0x00000000,
    .ESSR[1] = 0x00000000,
};

void __early_init(void) { ht32_clock_init(); }

void boardInit(void) {}
