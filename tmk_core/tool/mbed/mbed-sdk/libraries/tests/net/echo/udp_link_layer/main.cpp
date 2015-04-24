#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include <list>
#include <string>

/**
* How to use:
* make.py -m LPC1768 -t ARM -d E:\ -n NET_14
* udp_link_layer_auto.py -p COM20 -d E:\ -t 10
*/

// Evil globals
namespace {
    // IP and port used to store HOST address info
    char host_address[32] = {0};
    volatile int host_port = 0;

    const int ECHO_SERVER_PORT = 7;
    const int BUFFER_SIZE = 64;

    // Forwarding packet queue
    std::list<std::string> datagram_queue;

    // Statistics (mbed)
    volatile int received_packets = 0;
    volatile int forwarded_packets = 0;
    volatile int max_queue_len = 0;

    Mutex cli_serv_mutex;
    // cli_serv_mutex.lock(); // LOCK
    // cli_serv_mutex.unlock(); // LOCK
}

void udp_server_task(void const *argument)
{
    DigitalOut indicator(LED1);
    UDPSocket server;

    server.bind(ECHO_SERVER_PORT);
    // printf("[udp_server_task] Start\r\n");

    Endpoint client;
    char buffer[BUFFER_SIZE] = { 0 };
    while (true) {
        //printf("[udp_server_task] Wait for packet...\r\n");
        int n = server.receiveFrom(client, buffer, sizeof(buffer));
        if (n > 0) {
            //printf("[udp_server_task] Received packet from: %s\r\n", client.get_address());
            const int buffer_string_end_index = n >= BUFFER_SIZE ? BUFFER_SIZE - 1 : n;
            buffer[buffer_string_end_index] = '\0';
            //printf("[udp_server_task] Server received: %s\r\n", buffer);
            if (host_port == 0) {
                strcpy(host_address, client.get_address());
                host_port = ECHO_SERVER_PORT + 1;
                //printf("[udp_server_task] Set host address and port: %s:%d\r\n", host_address, host_port);
            }
            // Dispatch data to client for sending to test HOST
            cli_serv_mutex.lock(); // LOCK
            // Push to datagram queue
            datagram_queue.push_front(std::string(buffer));
            max_queue_len = datagram_queue.size() > max_queue_len ? datagram_queue.size() : max_queue_len;
            received_packets++;
            cli_serv_mutex.unlock(); // LOCK
            indicator = !indicator;
        }
    }
}

void udp_client_task(void const *argument)
{
    while (host_port == 0) {
        // Waiting for HOST port notification
    }

    DigitalOut indicator(LED2);
    UDPSocket socket;
    socket.init();

    Endpoint echo_server;
    echo_server.set_address(host_address, host_port);
    //printf("[udp_client_task] Start: %s:%d\r\n", host_address, host_port);

    while (1) {
        std::string datagram;
        bool sent_datagram = false;
        cli_serv_mutex.lock(); // LOCK
        if (datagram_queue.size() > 0) {
            // POP from datagram queue
            datagram = datagram_queue.back();
            datagram_queue.pop_back();
            sent_datagram = true;
        }
        cli_serv_mutex.unlock(); // LOCK
        if (sent_datagram) {
            //printf("[udp_client_task] Forwarded datagram: %s\r\n", datagram.c_str());
            socket.sendTo(echo_server, (char *)datagram.c_str(), datagram.length());
            forwarded_packets++;
            indicator = !indicator;
        }
    }
}

int main(void)
{
    EthernetInterface eth;

    eth.init(); //Use DHCP
    eth.connect();
    printf("MBED: Server IP Address is %s:%d\r\n", eth.getIPAddress(), ECHO_SERVER_PORT);

    Thread UdpServerTask(udp_server_task, NULL, osPriorityNormal, DEFAULT_STACK_SIZE * 2.25);
    Thread UdpClientTask(udp_client_task, NULL, osPriorityNormal, DEFAULT_STACK_SIZE * 2.25);

    // Control TCP server to get MBED statistics
    {
        char buffer[BUFFER_SIZE] = {0};
        const int TELNET_SERVER_PORT = 23;
        const int BUFFER_SIZE = 256;
        TCPSocketServer server;
        server.bind(TELNET_SERVER_PORT);
        server.listen();

        while (true) {
            printf("MBED: Wait for new connection...\r\n");
            TCPSocketConnection client;
            server.accept(client);
            client.set_blocking(false, 1500); // Timeout after (1.5)s
            printf("MBED: Connection from: %s\r\n", client.get_address());

            while (true) {
                int n = client.receive(buffer, sizeof(buffer));
                //if (n <= 0) break;
                if (n > 0) {
                    // printf("Recv %d chars\r\n", n);
                    const int buffer_string_end_index = n >= BUFFER_SIZE ? BUFFER_SIZE - 1 : n;
                    buffer[buffer_string_end_index] = '\0';
                    // client.send_all(buffer, strlen(buffer));
                    if (strncmp(buffer, "stat", 4) == 0) {
                        sprintf(buffer, "received_packets %d\nforwarded_packets %d\nmax_queue_len %d",
                                received_packets, forwarded_packets, max_queue_len);
                        client.send_all(buffer, strlen(buffer));
                        // printf("%s", buffer);
                    }
                }
                //if (n <= 0) break;
            }
            client.close();
        }
    }
}
