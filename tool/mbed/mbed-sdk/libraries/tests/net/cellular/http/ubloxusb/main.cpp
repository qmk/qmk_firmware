#include "UbloxUSBGSMModem.h"
#include "UbloxUSBCDMAModem.h"
#include "httptest.h"

#if !defined(MODEM_UBLOX_GSM) && !defined(MODEM_UBLOX_CDMA)
#warning No modem defined, using GSM by default
#define MODEM_UBLOX_GSM
#endif

#ifndef MODEM_APN
#warning APN not specified, using "internet"
#define MODEM_APN "internet"
#endif

#ifndef MODEM_USERNAME
#warning username not specified
#define MODEM_USERNAME NULL
#endif

#ifndef MODEM_PASSWORD
#warning password not specified
#define MODEM_PASSWORD NULL
#endif

int main()
{
#ifdef MODEM_UBLOX_GSM
    UbloxUSBGSMModem modem;
#else
    UbloxUSBCDMAModem modem(p18, true, 1);
#endif
    httptest(modem, MODEM_APN, MODEM_USERNAME, MODEM_PASSWORD);
    while (true);
}

