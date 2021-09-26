#pragma once

#include <stdint.h>

typedef struct {
    /* 100 - 12000 CPI supported */
    uint16_t cpi;
} config_pmw_t;

typedef struct {
    int16_t x;
    int16_t y;
} report_pmw_t;

void pmw_init(void);
config_pmw_t pmw_get_config(void);
void pmw_set_config(config_pmw_t);
/* Reads and clears the current delta values on the PMW sensor */
report_pmw_t pmw_get_report(void);