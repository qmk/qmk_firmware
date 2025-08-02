#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"

/**
 * @brief Debounce raw matrix events according to the choosen debounce algorithm.
 *
 * @param raw The current key state
 * @param cooked The debounced key state
 * @param num_rows Number of rows to debounce
 * @param changed True if raw has changed since the last call
 * @return true Cooked has new keychanges after debouncing
 * @return false Cooked is the same as before
 */
bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

void debounce_init(uint8_t num_rows);
