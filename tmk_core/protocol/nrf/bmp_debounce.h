
#pragma once

#include "matrix.h"

#include "apidef.h"

void bmp_debounce_init(void);
int bmp_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows,
              uint8_t num_cols, uint8_t debounce_value, bool changed,
              bmp_api_key_event_t *events);
