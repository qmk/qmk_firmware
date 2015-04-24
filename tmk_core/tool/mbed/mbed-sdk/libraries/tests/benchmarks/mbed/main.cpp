#include "mbed.h"

DigitalOut out(p5);
#if defined(TARGET_LPC1114)
AnalogIn in(p20);
#else
AnalogIn in(p19);
#endif

int main() {
    while(1) {
        if(in > 0.5) {
            out = !out;
        }
    }
}
