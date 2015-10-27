#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"
#include "NTPClient.h"

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(NTP client);
    MBED_HOSTTEST_START("NET_8");

    EthernetInterface eth;
    NTPClient ntp;
    eth.init(); //Use DHCP
    eth.connect();

    // NTP set time
    {
        bool result = true;
        const char *url_ntp_server = "0.pool.ntp.org";
        printf("NTP_SETTIME: Trying to update time... \r\n");
        const int ret = ntp.setTime(url_ntp_server);
        if (ret == 0) {
          time_t ctTime = time(NULL);
          printf("NTP_SETTIME: UTC Time read successfully ... [OK]\r\n");
          printf("NTP_SETTIME: %s\r\n", ctime(&ctTime));
        }
        else {
          printf("NTP_SETTIME: Error(%d) ... [FAIL]\r\n", ret);
          result = false;
        }

        if (result == false) {
            MBED_HOSTTEST_RESULT(false);
        }
    }
    eth.disconnect();
    MBED_HOSTTEST_RESULT(true);
}
