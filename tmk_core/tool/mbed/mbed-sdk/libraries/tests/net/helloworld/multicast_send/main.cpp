#include "mbed.h"
#include "EthernetInterface.h"

const char* MCAST_GRP = "224.1.1.1";
const int MCAST_PORT = 5007;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    UDPSocket sock;
    sock.init();

    Endpoint multicast_group;
    multicast_group.set_address(MCAST_GRP, MCAST_PORT);

    char out_buffer[] = "very important data";
    while (true) {
        printf("Multicast to group: %s\n", MCAST_GRP);
        sock.sendTo(multicast_group, out_buffer, sizeof(out_buffer));
        Thread::wait(1000);
    }
}
