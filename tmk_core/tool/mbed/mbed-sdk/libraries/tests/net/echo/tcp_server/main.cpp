#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"

namespace {
    const int ECHO_SERVER_PORT = 7;
    const int BUFFER_SIZE = 64;
}

int main (void) {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(tcpecho_server_auto);
    MBED_HOSTTEST_DESCRIPTION(TCP echo server);
    MBED_HOSTTEST_START("NET_3");

    char buffer[BUFFER_SIZE] = {0};
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("MBED: Server IP Address is %s:%d" NL, eth.getIPAddress(), ECHO_SERVER_PORT);

    TCPSocketServer server;
    server.bind(ECHO_SERVER_PORT);
    server.listen();

    while (true) {
        printf("MBED: Wait for new connection..." NL);
        TCPSocketConnection client;
        server.accept(client);
        client.set_blocking(false, 1500); // Timeout after (1.5)s
        printf("MBED: Connection from: %s" NL, client.get_address());

        while (true) {
            const int n = client.receive(buffer, sizeof(buffer));
            if (n <= 0) {
                break;
            }
            const int buffer_string_end_index = n >= BUFFER_SIZE ? BUFFER_SIZE-1 : n;
            buffer[buffer_string_end_index] = '\0';
            client.send_all(buffer, n);
            if (n <= 0) {
                break;
            }
        }
        client.close();
    }
}
