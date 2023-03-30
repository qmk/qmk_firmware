/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/flash.h"
#include "pico/unique_id.h"

static_assert(PICO_UNIQUE_BOARD_ID_SIZE_BYTES == FLASH_UNIQUE_ID_SIZE_BYTES, "Board ID size must match flash ID size");

static pico_unique_board_id_t retrieved_id;

static void __attribute__((constructor)) _retrieve_unique_id_on_boot(void) {
#if PICO_NO_FLASH
    // The hardware_flash call will panic() if called directly on a NO_FLASH
    // build. Since this constructor is pre-main it would be annoying to
    // debug, so just produce something well-defined and obviously wrong.
    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; i++)
        retrieved_id.id[i] = 0xee;
#else
    flash_get_unique_id(retrieved_id.id);
#endif
}

void pico_get_unique_board_id(pico_unique_board_id_t *id_out) {
    *id_out = retrieved_id;
}

void pico_get_unique_board_id_string(char *id_out, uint len) {
    assert(len > 0);
    size_t i;
    // Generate hex one nibble at a time
    for (i = 0; (i < len - 1) && (i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2); i++) {
        int nibble = (retrieved_id.id[i/2] >> (4 - 4 * (i&1))) & 0xf;
        id_out[i] = (char)(nibble < 10 ? nibble + '0' : nibble + 'A' - 10);
    }
    id_out[i] = 0;
}
