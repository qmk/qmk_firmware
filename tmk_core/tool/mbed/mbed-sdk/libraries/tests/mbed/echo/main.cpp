#include "mbed.h"
#include "test_env.h"

#define TXPIN     USBTX
#define RXPIN     USBRX


namespace {
    const int BUFFER_SIZE = 48;
    char buffer[BUFFER_SIZE] = {0};
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(echo);
    MBED_HOSTTEST_DESCRIPTION(Serial Echo at 115200);
    MBED_HOSTTEST_START("MBED_A9");

    Serial pc(TXPIN, RXPIN);
    pc.baud(115200);

    while (1) {
        pc.gets(buffer, BUFFER_SIZE - 1);
        pc.printf("%s", buffer);
    }
}
