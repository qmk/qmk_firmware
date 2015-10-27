#include "mbed.h"

DigitalOut out(p5);
#if defined(TARGET_LPC1114)
AnalogIn in(p20);
#else
AnalogIn in(p19);
#endif

volatile float w, x, y, z;
int main() {
    while(1) {
        z = x * y / w;
        printf("Hello World %d %f\n", out.read(), z);
        if(in > 0.5) {
            out = !out;
        }
    }
}
