#include "mbed.h"

volatile int x, y, z;
int main() {
    while(1) {
        z = x * y;
    }
}
