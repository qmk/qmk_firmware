#include "CellularModem.h"
#include "smstest.h"

void smstest(CellularModem& modem)
{
    modem.power(true);
    Thread::wait(1000);

#ifdef DESTINATION_NUMBER
    modem.sendSM(DESINATION_NUMBER, "Hello from mbed:)");
#endif

    while(true)
    {
        char num[17];
        char msg[64];
        size_t count;
        int ret = modem.getSMCount(&count);
        if(ret)
        {
          printf("getSMCount returned %d\n", ret);
          Thread::wait(3000);
          continue;
        }
        if( count > 0)
        {
          printf("%d SMS to read\n", count);
          ret = modem.getSM(num, msg, 64);
          if(ret)
          {
            printf("getSM returned %d\n", ret);
            Thread::wait(3000);
            continue;
          }

          printf("%s : %s\n", num, msg);
        }
        Thread::wait(3000);
    }
}

