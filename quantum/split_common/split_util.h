#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

extern volatile bool isLeftHand;

void matrix_master_OLED_init(void);
void split_pre_init(void);
void split_post_init(void);

bool transport_master_if_connected(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);
bool is_transport_connected(void);
