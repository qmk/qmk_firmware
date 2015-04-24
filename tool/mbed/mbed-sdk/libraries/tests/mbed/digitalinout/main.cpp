#include "test_env.h"

#if defined(TARGET_LPC1114)
DigitalInOut d1(dp1);
DigitalInOut d2(dp2);

#elif defined(TARGET_LPC1549)
// TARGET_FF_ARDUINO cannot be used, because D0 is used as USBRX (USB serial
// port pin), D1 is used as USBTX
DigitalInOut d1(D2);
DigitalInOut d2(D7);

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
DigitalInOut d1(PC_7);
DigitalInOut d2(PB_8);

#elif defined(TARGET_ARCH_MAX) || \
      defined(TARGET_DISCO_F407VG) || \
      defined(TARGET_DISCO_F429ZI)|| \
      defined(TARGET_DISCO_F401VC)
DigitalInOut d1(PC_12);
DigitalInOut d2(PD_0);

#elif defined(TARGET_FF_ARDUINO)
DigitalInOut d1(D0);
DigitalInOut d2(D7);

#elif defined(TARGET_MAXWSNENV)
DigitalInOut d1(TP3);
DigitalInOut d2(TP4);

#elif defined(TARGET_MAX32600MBED)
DigitalInOut d1(P1_0);
DigitalInOut d2(P4_7);

#else
DigitalInOut d1(p5);
DigitalInOut d2(p25);

#endif


int main()
{
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(DigitalInOut);
    MBED_HOSTTEST_START("MBED_A6");

    bool check = true;

    d1.output();
    d2.input();
    d1 = 1;
    wait(0.1);
    if (d2 != 1) {
        printf("MBED: First check failed! d2 is %d\n", (int)d2);
        check = false;
    }
    d1 = 0;
    wait(0.1);
    if (d2 != 0) {
        printf("MBED: Second check failed! d2 is %d\n", (int)d2);
        check = false;
    }

    d1.input();
    d2.output();
    d2 = 1;
    wait(0.1);
    if (d1 != 1) {
        printf("MBED: Third check failed! d1 is %d\n", (int)d1);
        check = false;
    }
    d2 = 0;
    wait(0.1);
    if (d1 != 0) {
        printf("MBED: Fourth check failed! d1 is %d\n", (int)d1);
        check = false;
    }

    MBED_HOSTTEST_RESULT(check);
}
