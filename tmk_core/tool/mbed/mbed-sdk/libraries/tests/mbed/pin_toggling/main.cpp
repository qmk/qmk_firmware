#include "mbed.h"

DigitalOut out(p5);

int main() {
    while (true) {
        out = 1;
        out = 0;
    }
}
