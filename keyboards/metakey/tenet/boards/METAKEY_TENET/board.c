// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * PAL static configuration for the Metakey Tenet 70.
 *
 * USB_DM=PA11, USB_DP=PA12 (fixed by silicon).
 * SWDIO=PA13, SWCLK=PA14 — preserved for SWD recovery.
 */

#include "hal.h"

#define PBIT(PORT, LINE) ((PAL_PORT(LINE) == PORT) ? (1 << PAL_PAD(LINE)) : 0)
#define PAFIO_L(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) < 8)) ? (AF << (PAL_PAD(LINE) << 2)) : 0)
#define PAFIO_H(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) >= 8)) ? (AF << ((PAL_PAD(LINE) - 8) << 2)) : 0)
#define PAFIO(PORT, N, LINE, AF) ((N) ? PAFIO_H(PORT, LINE, AF) : PAFIO_L(PORT, LINE, AF))

// Matrix rows (outputs, active low).
#define OUT_BITS(PORT) ( \
    PBIT(PORT, B8) | PBIT(PORT, B7) | PBIT(PORT, B6) | PBIT(PORT, C3) | PBIT(PORT, C2) | \
    0)

// Matrix cols (inputs with pull-ups). Col 17 = PA11 handled in matrix.c;
// col 14 = PA14 (SWCLK) AFIO override done in matrix_init_custom().
#define IN_BITS(PORT) ( \
    PBIT(PORT, A6) | PBIT(PORT, A7) | PBIT(PORT, A8) | PBIT(PORT, A9) | PBIT(PORT, A10) | \
    PBIT(PORT, A14) | \
    PBIT(PORT, B13) | PBIT(PORT, B14) | PBIT(PORT, B15) | \
    PBIT(PORT, C0) | PBIT(PORT, C4) | PBIT(PORT, C5) | PBIT(PORT, C8) | \
    PBIT(PORT, C10) | PBIT(PORT, C11) | PBIT(PORT, C12) | PBIT(PORT, C13) | \
    0)

#define AF_BITS(PORT, N) ( \
    PAFIO(PORT, N, B8, AFIO_GPIO) | PAFIO(PORT, N, B7, AFIO_GPIO) | PAFIO(PORT, N, B6, AFIO_GPIO) | \
    PAFIO(PORT, N, C3, AFIO_GPIO) | PAFIO(PORT, N, C2, AFIO_GPIO) | \
    PAFIO(PORT, N, A6, AFIO_GPIO) | PAFIO(PORT, N, A7, AFIO_GPIO) | PAFIO(PORT, N, A8, AFIO_GPIO) | \
    PAFIO(PORT, N, A9, AFIO_GPIO) | PAFIO(PORT, N, A10, AFIO_GPIO) | \
    PAFIO(PORT, N, A0, AFIO_GPIO) | PAFIO(PORT, N, A1, AFIO_GPIO) | PAFIO(PORT, N, A4, AFIO_GPIO) | \
    PAFIO(PORT, N, A5, AFIO_GPIO) | \
    PAFIO(PORT, N, C0, AFIO_GPIO) | PAFIO(PORT, N, C1, AFIO_GPIO) | PAFIO(PORT, N, C4, AFIO_GPIO) | \
    PAFIO(PORT, N, C5, AFIO_GPIO) | PAFIO(PORT, N, C6, AFIO_GPIO) | PAFIO(PORT, N, C7, AFIO_GPIO) | \
    PAFIO(PORT, N, D0, AFIO_GPIO) | PAFIO(PORT, N, B2, AFIO_GPIO) | \
    0)

const PALConfig pal_default_config = {
    .setup[0] = {  // GPIO A
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
    .setup[1] = {  // GPIO B
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
    .setup[2] = {  // GPIO C
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
    .setup[3] = {  // GPIO D
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
