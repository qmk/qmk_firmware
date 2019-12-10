#include "samd51j18a.h"
#include "string.h"
#include "usb_util.h"

char digit(int d, int radix) {
    if (d < 10) {
        return d + '0';
    } else {
        return d - 10 + 'A';
    }
}

int UTIL_ltoa_radix(int64_t value, char *dest, int radix) {
    int64_t original = value;  // save original value
    char    buf[25]  = "";
    int     c        = sizeof(buf) - 1;
    int     last     = c;
    int     d;
    int     size;

    if (value < 0)  // if it's negative, take the absolute value
        value = -value;

    do  // write least significant digit of value that's left
    {
        d        = (value % radix);
        buf[--c] = digit(d, radix);
        value /= radix;
    } while (value);

    if (original < 0) buf[--c] = '-';

    size = last - c + 1;  // includes null at end
    memcpy(dest, &buf[c], last - c + 1);

    return (size - 1);  // without null termination
}

int UTIL_ltoa(int64_t value, char *dest) { return UTIL_ltoa_radix(value, dest, 10); }

int UTIL_itoa(int value, char *dest) { return UTIL_ltoa_radix((int64_t)value, dest, 10); }

int UTIL_utoa(uint32_t value, char *dest) { return UTIL_ltoa_radix((int64_t)value, dest, 10); }
