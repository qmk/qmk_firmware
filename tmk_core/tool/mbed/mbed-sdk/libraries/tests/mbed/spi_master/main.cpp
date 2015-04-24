#include "mbed.h"
#include "test_env.h"

#if defined(TARGET_KL25Z)
SPI spi(PTD2, PTD3, PTD1);   // mosi, miso, sclk
DigitalOut cs(PTA13);
#elif defined(TARGET_KL05Z)
SPI spi(PTA7, PTA6, PTB0);   // mosi, miso, sclk
DigitalOut cs(PTB1);
#elif defined(TARGET_KL46Z)
SPI spi(PTD2, PTD3, PTD1);   // mosi, miso, sclk
DigitalOut cs(PTA13);
#elif defined(TARGET_FF_ARDUINO)
SPI spi(D11, D12, D13);   // mosi, miso, sclk
DigitalOut cs(D10);
#else
SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut cs(p8);
#endif

int main() {
    int data = 0;
    int res = 0;

    for(int i = 0; i < 30; i++) {

        cs = 0;
        res = spi.write(data++);
        cs = 1;

        wait_ms(0.001);

        if ((i > 1) && ((res + 2) != data))
            notify_completion(false);
    }

    notify_completion(true);
}
