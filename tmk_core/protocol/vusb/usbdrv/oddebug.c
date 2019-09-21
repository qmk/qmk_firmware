/* Name: oddebug.c
 * Project: AVR library
 * Author: Christian Starkjohann
 * Creation Date: 2005-01-16
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: oddebug.c 692 2008-11-07 15:07:40Z cs $
 */

#include "oddebug.h"

#if DEBUG_LEVEL > 0

#    warning "Never compile production devices with debugging enabled"

static void uartPutc(char c) {
    while (!(ODDBG_USR & (1 << ODDBG_UDRE)))
        ; /* wait for data register empty */
    ODDBG_UDR = c;
}

static uchar hexAscii(uchar h) {
    h &= 0xf;
    if (h >= 10) h += 'a' - (uchar)10 - '0';
    h += '0';
    return h;
}

static void printHex(uchar c) {
    uartPutc(hexAscii(c >> 4));
    uartPutc(hexAscii(c));
}

void odDebug(uchar prefix, uchar *data, uchar len) {
    printHex(prefix);
    uartPutc(':');
    while (len--) {
        uartPutc(' ');
        printHex(*data++);
    }
    uartPutc('\r');
    uartPutc('\n');
}

#endif
