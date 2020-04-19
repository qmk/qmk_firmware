/*
 * io_expander.h
 *
 *  Created on: 2018/12/21
 *      Author: sekigon-gonnoc
 */

#pragma once

#include "matrix.h"

typedef struct {
    uint8_t addr;
    uint8_t row_pins[32];
    uint8_t row_num;
    uint8_t col_pins[32];
    uint8_t col_num;
} lpme_config_t;

void     lpme_init(lpme_config_t const *const config);
uint32_t lpme_scan(lpme_config_t const *const config, matrix_row_t *rows,
                   bool wakeup);
