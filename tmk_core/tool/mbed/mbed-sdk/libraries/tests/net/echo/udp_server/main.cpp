#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"

namespace {
    const int ECHO_SERVER_PORT = 7;
    const int BUFFER_SIZE = 64;
}

int main (void) {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(udpecho_server_auto);
    MBED_HOSTTEST_DESCRIPTION(UDP echo server);
    MBED_HOSTTEST_START("NET_5");

    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("MBED: Server IP Address is %s:%d\r\n", eth.getIPAddress(), ECHO_SERVER_PORT);

    UDPSocket server;
    server.bind(ECHO_SERVER_PORT);

    Endpoint client;
    char buffer[BUFFER_SIZE] = {0};
    printf("MBED: Waiting for packet...\r\n");
    while (true) {
        int n = server.receiveFrom(client, buffer, sizeof(buffer));
        if (n > 0) {
            //printf("Received packet from: %s\n", client.get_address());
            const int buffer_string_end_index = n >= BUFFER_SIZE ? BUFFER_SIZE-1 : n;
            buffer[buffer_string_end_index] = '\0';
            //printf("Server received: %s\n", buffer);
            server.sendTo(client, buffer, n);
        }
    }
}
