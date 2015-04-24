#ifndef HTTPTEST_H_
#define HTTPTEST_H_

#include "CellularModem.h"

int httptest(CellularModem& modem, const char* apn = NULL, const char* username = NULL, const char* password= NULL);

#endif

