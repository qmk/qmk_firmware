#include "test_env.h"

DigitalOut myled(LED1);
DigitalOut led2(LED2);

volatile int checks = 0;
void in_handler() {
    checks++;
    led2 = !led2;
}

#if defined(TARGET_KL25Z)
#define PIN_OUT     PTC6
#define PIN_IN      PTA5

#elif defined(TARGET_KL05Z)
#define PIN_OUT     PTB11
#define PIN_IN      PTB1

#elif defined(TARGET_LPC812)
#define PIN_OUT     D10
#define PIN_IN      D11

#elif defined(TARGET_LPC1114)
#define PIN_OUT     dp1
#define PIN_IN      dp2

#elif defined(TARGET_LPC1549)
// TARGET_FF_ARDUINO cannot be used, because D0 is used as USBRX (USB serial
// port pin), D1 is used as USBTX
#define PIN_OUT     D2
#define PIN_IN      D7

#elif defined(TARGET_LPC4088)
#define PIN_IN      (p11)
#define PIN_OUT     (p12)

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
#define PIN_IN      PB_8
#define PIN_OUT     PC_7

#elif defined(TARGET_ARCH_MAX) || \
      defined(TARGET_DISCO_F407VG) || \
      defined(TARGET_DISCO_F429ZI)|| \
      defined(TARGET_DISCO_F401VC)
#define PIN_OUT    PC_12
#define PIN_IN     PD_0

#elif defined(TARGET_RZ_A1H)
#define PIN_OUT    D1
#define PIN_IN     D5

#elif defined(TARGET_FF_ARDUINO)
#define PIN_OUT    D0
#define PIN_IN     D7

#elif defined(TARGET_MAXWSNENV)
#define PIN_OUT    P0_0
#define PIN_IN     P0_1

#elif defined(TARGET_MAX32600MBED)
#define PIN_OUT    P1_0
#define PIN_IN     P4_7

#else
#define PIN_IN      (p5)
#define PIN_OUT     (p25)

#endif

DigitalOut out(PIN_OUT);
InterruptIn in(PIN_IN);

#define IN_OUT_SET      out = 1; myled = 1;
#define IN_OUT_CLEAR    out = 0; myled = 0;

void flipper() {
    for (int i = 0; i < 5; i++) {
        IN_OUT_SET;
        wait(0.2);
        IN_OUT_CLEAR;
        wait(0.2);
    }
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(InterruptIn);
    MBED_HOSTTEST_START("MBED_A7");

    IN_OUT_CLEAR;
    //Test falling edges first
    in.rise(NULL);
    in.fall(in_handler);
    flipper();

    if(checks != 5) {
        printf("MBED: falling edges test failed: %d\r\n",checks);
        MBED_HOSTTEST_RESULT(false);
    }

    //Now test rising edges
    in.rise(in_handler);
    in.fall(NULL);
    flipper();

    if (checks != 10) {
        printf("MBED: raising edges test failed: %d\r\n", checks);
        MBED_HOSTTEST_RESULT(false);
    }

    //Now test switch off edge detection
    in.rise(NULL);
    in.fall(NULL);
    flipper();

    if (checks != 10) {
        printf("MBED: edge detection switch off test failed: %d\r\n", checks);
        MBED_HOSTTEST_RESULT(false);
    }

    //Finally test both
    in.rise(in_handler);
    in.fall(in_handler);
    flipper();

    if (checks != 20) {
        printf("MBED: Simultaneous rising and falling edges failed: %d\r\n", checks);
        MBED_HOSTTEST_RESULT(false);
    }

    MBED_HOSTTEST_RESULT(true);
}
