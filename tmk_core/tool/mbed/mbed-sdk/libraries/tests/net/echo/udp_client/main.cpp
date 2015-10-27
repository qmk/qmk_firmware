#include "mbed.h"
#include "rtos.h"
#include "test_env.h"
#include "EthernetInterface.h"
#include <algorithm>

#define CHECK(RC, STEP)       if (RC < 0) error(STEP": %d\r\n", RC)

namespace {
    const int BUFFER_SIZE = 64;
    const int MAX_ECHO_LOOPS = 100;
    const char ASCII_MAX = '~' - ' ';

    struct s_ip_address {
        int ip_1;
        int ip_2;
        int ip_3;
        int ip_4;
    };
}

char char_rand() {
    return (rand() % ASCII_MAX) + ' ';
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(udpecho_client_auto);
    MBED_HOSTTEST_DESCRIPTION(UDP echo client);
    MBED_HOSTTEST_START("NET_6");

    char buffer[BUFFER_SIZE] = {0};
    char out_buffer[BUFFER_SIZE] = {0};
    s_ip_address ip_addr = {0, 0, 0, 0};
    int port = 0;
    bool result = true;

    printf("MBED: UDPCllient waiting for server IP and port...\r\n");
    scanf("%d.%d.%d.%d:%d", &ip_addr.ip_1, &ip_addr.ip_2, &ip_addr.ip_3, &ip_addr.ip_4, &port);
    printf("MBED: Address received: %d.%d.%d.%d:%d\r\n", ip_addr.ip_1, ip_addr.ip_2, ip_addr.ip_3, ip_addr.ip_4, port);

    EthernetInterface eth;
    int rc = eth.init(); //Use DHCP
    CHECK(rc, "eth init");

    rc = eth.connect();
    CHECK(rc, "connect");
    printf("IP: %s\n", eth.getIPAddress());

    UDPSocket socket;
    rc = socket.init();
    CHECK(rc, "socket init");

    printf("MBED: UDPClient IP Address is %s\r\n", eth.getIPAddress());
    sprintf(buffer, "%d.%d.%d.%d", ip_addr.ip_1, ip_addr.ip_2, ip_addr.ip_3, ip_addr.ip_4);

    Endpoint echo_server;
    rc = echo_server.set_address(buffer, port);
    CHECK(rc, "set_address");

    for (int i =0; i < MAX_ECHO_LOOPS; i++) {
        std::generate(out_buffer, out_buffer + BUFFER_SIZE, char_rand);
        rc = socket.sendTo(echo_server, out_buffer, sizeof(out_buffer));
        CHECK(rc, "sendTo");

        const int n = socket.receiveFrom(echo_server, buffer, sizeof(buffer));
        CHECK(n, "receiveFrom");

        if (memcmp(buffer, out_buffer, BUFFER_SIZE) != 0) {
            result = false;
            break;
        }
    }

    if (notify_completion_str(result, buffer)) {
        socket.sendTo(echo_server, buffer, strlen(buffer));
    }

    socket.close();
    eth.disconnect();
    MBED_HOSTTEST_RESULT(result);
}
