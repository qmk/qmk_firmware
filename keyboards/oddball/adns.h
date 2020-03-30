#pragma once

#include <stdint.h>

typedef struct {
    int16_t x;
    int16_t y;
} report_adns_t;

void adns_init(void);
report_adns_t adns_get_report(void);
void adns_clear_report(void);
