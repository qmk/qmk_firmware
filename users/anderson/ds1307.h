#pragma once

#include "i2c_master.h"

void ds1307_set_time(uint8_t h, uint8_t m, uint8_t s);
void ds1307_get_time(uint8_t *h, uint8_t *m, uint8_t *s);
