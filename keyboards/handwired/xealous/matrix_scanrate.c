#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "timer.h"

#ifdef CONSOLE_ENABLE
static uint16_t matrix_scan_count = 0;
static uint32_t matrix_timer = 0;
void matrix_check_scan_rate(void) {    
    matrix_scan_count++;
    if (matrix_scan_count > 1000) {
        uint32_t timer_now = timer_read32();
        uint16_t ms_per_thousand = TIMER_DIFF_32(timer_now, matrix_timer);
        uint16_t rate_per_second = 1000000UL / ms_per_thousand;
        print("scan_rate: ");
        pdec(rate_per_second);
        print("\n");
        matrix_timer = timer_now;
        matrix_scan_count = 0;
    }    
}

static uint32_t last_scan_time = 0;
void matrix_time_between_scans(void) {    
    if (timer_elapsed(last_scan_time) > 1)
    {
        print(">1ms elapsed since last scan: ");
        pdec(timer_elapsed(last_scan_time));
        print("\n");
    }
    last_scan_time = timer_read();
    
}
#endif
