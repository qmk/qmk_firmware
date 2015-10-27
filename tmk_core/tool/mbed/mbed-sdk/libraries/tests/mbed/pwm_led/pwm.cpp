#include "mbed.h"

#if defined(TARGET_K64F)
#define TEST_LED D9

#elif defined(TARGET_NUCLEO_F030R8) || \
      defined(TARGET_NUCLEO_F070RB) || \
      defined(TARGET_NUCLEO_F072RB) || \
      defined(TARGET_NUCLEO_F091RC) || \
      defined(TARGET_NUCLEO_F103RB) || \
      defined(TARGET_NUCLEO_F302R8) || \
      defined(TARGET_NUCLEO_F303RE) || \
      defined(TARGET_NUCLEO_F334R8) || \
      defined(TARGET_NUCLEO_F401RE) || \
      defined(TARGET_NUCLEO_F411RE) || \
      defined(TARGET_NUCLEO_L053R8) || \
      defined(TARGET_NUCLEO_L073RZ) || \
      defined(TARGET_NUCLEO_L152RE)
#define TEST_LED D3

#elif defined (TARGET_K22F) || \
      defined (TARGET_LPC824)
#define TEST_LED LED_GREEN

#elif defined (TARGET_MAXWSNENV)
#define TEST_LED LED_GREEN

#elif defined (TARGET_DISCO_F407VG) 
#define TEST_LED LED1

#else
#error This test is not supported on this target.
#endif

PwmOut led(TEST_LED);

int main() {
    float crt = 1.0, delta = 0.05;

    led.period_ms(2); // 500Hz
    while (true) {
        led.write(crt);
        wait_ms(50);
        crt = crt + delta;
        if (crt > 1.0) {
            crt = 1.0;
            delta = -delta;
        }
        else if (crt < 0) {
            crt = 0;
            delta = -delta;
        }
    }
}
