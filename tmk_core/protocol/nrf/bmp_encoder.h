#pragma once

#include <stdint.h>
#include <stdbool.h>

void bmp_encoder_init(void);
void bmp_encoder_read(void);

void encoder_update_kb(int8_t index, bool clockwise);
void encoder_update_user(int8_t index, bool clockwise);
