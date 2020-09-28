/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef CONSOLE_ENABLE

#    include "samd51j18a.h"
#    include "arm_atsam_protocol.h"
#    include "printf.h"
#    include <string.h>
#    include <stdarg.h>

void console_printf(char *fmt, ...) {
    while (udi_hid_con_b_report_trans_ongoing) {
    }  // Wait for any previous transfers to complete

    static char console_printbuf[CONSOLE_PRINTBUF_SIZE];  // Print and send buffer
    va_list     va;
    int         result;

    va_start(va, fmt);
    result = vsnprintf(console_printbuf, CONSOLE_PRINTBUF_SIZE, fmt, va);
    va_end(va);

    uint32_t irqflags;
    char *   pconbuf  = console_printbuf;  // Pointer to start send from
    int      send_out = CONSOLE_EPSIZE;    // Bytes to send per transfer

    while (result > 0) {  // While not error and bytes remain
        while (udi_hid_con_b_report_trans_ongoing) {
        }  // Wait for any previous transfers to complete

        irqflags = __get_PRIMASK();
        __disable_irq();
        __DMB();

        if (result < CONSOLE_EPSIZE) {                      // If remaining bytes are less than console epsize
            memset(udi_hid_con_report, 0, CONSOLE_EPSIZE);  // Clear the buffer
            send_out = result;                              // Send remaining size
        }

        memcpy(udi_hid_con_report, pconbuf, send_out);  // Copy data into the send buffer

        udi_hid_con_b_report_valid = 1;  // Set report valid
        udi_hid_con_send_report();       // Send report

        __DMB();
        __set_PRIMASK(irqflags);

        result -= send_out;   // Decrement result by bytes sent
        pconbuf += send_out;  // Increment buffer point by bytes sent
    }
}

#endif  // CONSOLE_ENABLE
