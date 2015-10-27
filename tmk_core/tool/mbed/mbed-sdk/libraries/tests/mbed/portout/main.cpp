#include "mbed.h"

# if defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || defined(TARGET_LPC4088)
#     define LED_PORT   Port1
#     define LED1       (1 << 18) // P1.18
#     define LED2       (1 << 20) // P1.20
#     define LED3       (1 << 21) // P1.21
#     define LED4       (1 << 23) // P1.23
# elif defined(TARGET_LPC11U24) || defined(TARGET_LPC1114)
#     define LED_PORT   Port1
#     define LED1       (1 <<  8) // P1.8
#     define LED2       (1 <<  9) // P1.9
#     define LED3       (1 << 10) // P1.10
#     define LED4       (1 << 11) // P1.11
# elif defined(TARGET_MAXWSNENV)
#     define LED_PORT   Port1
#     define LED1   (1 <<  4) // P1.4
#     define LED2   (1 <<  6) // P1.6
#     define LED3   (1 <<  7) // P1.7
#     define LED4   0
# elif defined(TARGET_MAX32600MBED)
#     define LED_PORT   Port7
#     define LED1       (1 <<  0) // P7.0
#     define LED2       (1 <<  6) // P7.6
#     define LED3       (1 <<  4) // P7.4
#     define LED4       0
# endif

#define LED_MASK    (LED1|LED2|LED3|LED4)

int mask[4] = {
    (LED1 | LED3),
    (LED2 | LED4),
    (LED1 | LED2),
    (LED3 | LED4)
};

PortOut ledport(LED_PORT, LED_MASK);

int main() {
    while (1) {
        for (int i=0; i<4; i++) {
            ledport = mask[i];
            wait(1);
        }
    }
}
