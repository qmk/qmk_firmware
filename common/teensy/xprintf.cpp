#include <cstdarg>
//#include <stdarg.h>
#include "WProgram.h"
#include "teensy/xprintf.h"

/* TODO: Need small implementation for embedded */
void xprintf(const char* format, ...)
{
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, format);
    vsnprintf(buf, 128, format, args);
    va_end (args);
    Serial.print(buf);
}
