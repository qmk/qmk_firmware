#include "mbed.h"

BusOut leds(P1_28, P1_29, P1_31, P2_2, P2_3, P2_4, P2_5, P2_6);
AnalogIn in(P0_25);

int main() {
    while (true) {
        float value = 8.0 * in.read();
        printf("analog in: %f\n\r", value);

        int led_mask = 0;
        if (value > 0.5) led_mask |= 1 << 0;
        if (value > 1.5) led_mask |= 1 << 1;
        if (value > 2.5) led_mask |= 1 << 2;
        if (value > 3.5) led_mask |= 1 << 3;
        if (value > 4.5) led_mask |= 1 << 4;
        if (value > 5.5) led_mask |= 1 << 5;
        if (value > 6.5) led_mask |= 1 << 6;
        if (value > 7.5) led_mask |= 1 << 7;
        leds = led_mask;

        wait(1);
    }
}
