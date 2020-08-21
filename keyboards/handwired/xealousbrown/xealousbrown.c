#include "xealousbrown.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}



#ifdef BENCHMARK_MATRIX
#    include "timer.h"
#    include <stdint.h>
#    include <stdbool.h>
#    include "wait.h"
#    include "util.h"
#    include "matrix.h"
#    include "quantum.h"

static int      scans          = 0;
static uint16_t last_print_out = 0;
static int      last_timer     = 0;
void            matrix_scan_user(void) {
    scans++;
    uint16_t timer = timer_read();
    
    if (timer != last_timer && timer != last_timer + 1) {
        print("MS:\n");
        print_dec(timer);
        print("->");
        print_dec(last_timer);
        print("\n");
    }
    
    last_timer = timer;
    if ((timer % 1000 == 0) && (timer != last_print_out)) {
        print("Benchmark:");
        print("\n");
        print_dec(timer);
        print("\n");
        print_dec(scans);
        print("\n");
        print("-------");
        scans          = 0;
        last_print_out = timer;
    }
}
#endif
