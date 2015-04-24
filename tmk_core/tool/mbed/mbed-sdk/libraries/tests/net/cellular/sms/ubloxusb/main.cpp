#include "UbloxUSBGSMModem.h"
#include "UbloxUSBCDMAModem.h"
#include "smstest.h"

#if !defined(MODEM_UBLOX_GSM) && !defined(MODEM_UBLOX_CDMA)
#warning No modem defined, using GSM by default
#define MODEM_UBLOX_GSM
#endif

int main()
{
#ifdef MODEM_UBLOX_GSM
    UbloxUSBGSMModem modem;
#else
    UbloxUSBCDMAModem modem(p18, true, 1);
#endif

    smstest(modem);
    while (true);
}

