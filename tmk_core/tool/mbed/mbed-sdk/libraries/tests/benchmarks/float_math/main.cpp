#include "mbed.h"

volatile float w, x, y, z;
int main() {
    while (1) {
        z = x * y / w;
    }
}
