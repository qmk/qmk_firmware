#include "mbed.h"
#include "EthernetInterface.h"

const char* MCAST_GRP = "224.1.1.1";
const int MCAST_PORT = 5007;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    UDPSocket server;
    server.bind(MCAST_PORT);
    if (server.join_multicast_group(MCAST_GRP) != 0) {
        printf("Error joining the multicast group\n");
        while (true) {}
    }

    Endpoint client;
    char buffer[256];
    while (true) {
        printf("\nWait for packet...\n");
        int n = server.receiveFrom(client, buffer, sizeof(buffer));

        printf("Packet from \"%s\": %s\n", client.get_address(), buffer);
    }
}
