#include "mbed.h"
#include "EthernetInterface.h"

const int BROADCAST_PORT = 58083;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    UDPSocket sock;
    sock.init();
    sock.set_broadcasting();

    Endpoint broadcast;
    broadcast.set_address("255.255.255.255", BROADCAST_PORT);

    char out_buffer[] = "very important data";

    while (true) {
        printf("Broadcasting...\n");
        sock.sendTo(broadcast, out_buffer, sizeof(out_buffer));
        Thread::wait(1000);
    }
}
