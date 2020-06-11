#pragma once

#include <common/matrix.h>

void transport_master_init(void);
void transport_follower_init(void);

// returns false if valid data not received from follower
bool transport_master(matrix_row_t matrix[]);
void transport_follower(matrix_row_t matrix[]);
