#include "mbed.h"
#include "EthernetInterface.h"
#include "test_env.h"

namespace {
    const char *HTTP_SERVER_NAME = "utcnist.colorado.edu";
    const int HTTP_SERVER_PORT = 37;
    const float YEARS_TO_PASS = 114.0;
}


int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(NIST Internet Time Service);
    MBED_HOSTTEST_START("NET_2");

    bool result = false;
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("UDP client IP Address is %s\n", eth.getIPAddress());

    UDPSocket sock;
    sock.init();

    Endpoint nist;
    nist.set_address(HTTP_SERVER_NAME, HTTP_SERVER_PORT);

    char out_buffer[] = "plop"; // Does not matter
    sock.sendTo(nist, out_buffer, sizeof(out_buffer));

    union {
        char in_buffer_tab[4];
        unsigned int in_buffer_uint;
    };

    const int n = sock.receiveFrom(nist, in_buffer_tab, sizeof(in_buffer_tab));
    if (n > 0) {
        result = true;
        const unsigned int timeRes = ntohl(in_buffer_uint);
        const float years = timeRes / 60.0 / 60.0 / 24.0 / 365.0;
        const float days = timeRes / 24.0 / 60.0 / 60.0;
        printf("UDP: Received %d bytes from server %s on port %d\r\n", n, nist.get_address(), nist.get_port());
        printf("UDP: %u seconds since 01/01/1900 00:00 GMT ... %s\r\n", timeRes, timeRes > 0 ? "[OK]" : "[FAIL]");
        printf("UDP: %.2f days since 01/01/1900 00:00 GMT ... %s\r\n", days, timeRes > 0 ? "[OK]" : "[FAIL]");
        printf("UDP: %.2f years since 01/01/1900 00:00 GMT ... %s\r\n", years, timeRes > YEARS_TO_PASS ? "[OK]" : "[FAIL]");

        if (years < YEARS_TO_PASS) {
            result = false;
        }
    }
    sock.close();
    eth.disconnect();
    MBED_HOSTTEST_RESULT(result);
}
