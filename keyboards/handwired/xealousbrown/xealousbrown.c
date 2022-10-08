/* Copyright 2019 Alex Ong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xealousbrown.h"

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
        print("Scans: ");
        print_dec(scans);
        print("\n");
        scans          = 0;
        last_print_out = timer;
    }
}
#endif
