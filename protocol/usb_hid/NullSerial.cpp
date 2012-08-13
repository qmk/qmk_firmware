#include "USBAPI.h"


void NullSerial::begin(uint16_t baud_count)
{
}

void NullSerial::end(void)
{
}

void NullSerial::accept(void)
{
}

int NullSerial::available(void)
{
    return 0;
}

int NullSerial::peek(void)
{
    return -1;
}

int NullSerial::read(void)
{
    return -1;
}

void NullSerial::flush(void)
{
}

size_t NullSerial::write(uint8_t c)
{
    return 1;
}

NullSerial::operator bool() {
    return true;
}

NullSerial Serial;
