#include "mbed.h"
#include "EthernetInterface.h"

const int BROADCAST_PORT = 58083;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    UDPSocket socket;
    socket.bind(BROADCAST_PORT);
    socket.set_broadcasting();

    Endpoint broadcaster;
    char buffer[256];
    while (true) {
        printf("\nWait for packet...\n");
        int n = socket.receiveFrom(broadcaster, buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Packet from \"%s\": %s\n", broadcaster.get_address(), buffer);
    }
}
