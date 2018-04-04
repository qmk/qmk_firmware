#include <cstdarg>
//#include <stdarg.h>
#include "mbed.h"
#include "mbed/xprintf.h"


#define STRING_STACK_LIMIT    120

//TODO
int __xprintf(const char* format, ...) { return 0; }

#if 0
/* mbed Serial */
Serial ser(UART_TX, UART_RX);

/* TODO: Need small implementation for embedded */
int xprintf(const char* format, ...)
{
    /* copy from mbed/common/RawSerial.cpp */
    std::va_list arg;
    va_start(arg, format);
    int len = vsnprintf(NULL, 0, format, arg);
    if (len < STRING_STACK_LIMIT) {
        char temp[STRING_STACK_LIMIT];
        vsprintf(temp, format, arg);
        ser.puts(temp);
    } else {
        char *temp = new char[len + 1];
        vsprintf(temp, format, arg);
        ser.puts(temp);
        delete[] temp;
    }
    va_end(arg);
    return len;

/* Fail: __builtin_va_arg_pack?
 * https://gcc.gnu.org/onlinedocs/gcc-4.3.5/gcc/Constructing-Calls.html#Constructing-Calls
    void *arg = __builtin_apply_args();
    void *ret = __builtin_apply((void*)(&(ser.printf)), arg, 100);
    __builtin_return(ret)
*/
/* Fail: varargs can not be passed to printf
    //int r = ser.printf("test %i\r\n", 123);
    va_list arg;
    va_start(arg, format);
    int r = ser.printf(format, arg);
    va_end(arg);
    return r;
*/
}
#endif
