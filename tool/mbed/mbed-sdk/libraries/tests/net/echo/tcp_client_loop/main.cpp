#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"
#include <algorithm>

namespace {
    const int BUFFER_SIZE = 64;
    const int MAX_ECHO_LOOPS = 1000;
    const char ASCII_MAX = '~' - ' ';

    struct s_ip_address
    {
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
    MBED_HOSTTEST_SELECT(tcpecho_client_auto);
    MBED_HOSTTEST_DESCRIPTION(TCP client echo loop);
    MBED_HOSTTEST_START("NET_13");

    char buffer[BUFFER_SIZE] = {0};
    char out_buffer[BUFFER_SIZE] = {0};
    s_ip_address ip_addr = {0, 0, 0, 0};
    int port = 0;

    printf("MBED: TCPCllient waiting for server IP and port...\r\n");
    scanf("%d.%d.%d.%d:%d", &ip_addr.ip_1, &ip_addr.ip_2, &ip_addr.ip_3, &ip_addr.ip_4, &port);
    printf("MBED: Address received: %d.%d.%d.%d:%d\r\n", ip_addr.ip_1, ip_addr.ip_2, ip_addr.ip_3, ip_addr.ip_4, port);

    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    printf("MBED: TCPClient IP Address is %s\r\n", eth.getIPAddress());
    sprintf(buffer, "%d.%d.%d.%d", ip_addr.ip_1, ip_addr.ip_2, ip_addr.ip_3, ip_addr.ip_4);

    TCPSocketConnection socket;
    while (socket.connect(buffer, port) < 0) {
        printf("MBED: TCPCllient unable to connect to %s:%d\r\n", buffer, port);
        wait(1);
    }

    // Test loop for multiple client connections
    bool result = true;
    int count_error = 0;
    for (int i = 0; i < MAX_ECHO_LOOPS; i++) {
        std::generate(out_buffer, out_buffer + BUFFER_SIZE, char_rand);
        socket.send_all(out_buffer, BUFFER_SIZE);

        int n = socket.receive(buffer, BUFFER_SIZE);
        if (n > 0)
        {
            bool echoed = memcmp(out_buffer, buffer, BUFFER_SIZE) == 0;
            result = result && echoed;
            if (echoed == false) {
                count_error++;  // Count error messages
            }
        }
    }

    printf("MBED: Loop messages passed: %d / %d\r\n", MAX_ECHO_LOOPS - count_error, MAX_ECHO_LOOPS);

    if (notify_completion_str(result, buffer)) {
        socket.send_all(buffer, strlen(buffer));
    }
    socket.close();
    eth.disconnect();
    MBED_HOSTTEST_RESULT(result);
}
