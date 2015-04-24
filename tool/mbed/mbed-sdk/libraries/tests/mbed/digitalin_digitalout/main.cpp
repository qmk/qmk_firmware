#include "test_env.h"

#if defined(TARGET_LPC1114)
DigitalOut out(dp1);
DigitalIn in(dp2);

#elif defined(TARGET_LPC1549)
// TARGET_FF_ARDUINO cannot be used, because D0 is used as USBRX (USB serial
// port pin), D1 is used as USBTX
DigitalOut out(D7);
DigitalIn in(D2);

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
DigitalOut out(PC_7);
DigitalIn in(PB_8);

#elif defined(TARGET_ARCH_MAX) || \
      defined(TARGET_DISCO_F407VG) || \
      defined(TARGET_DISCO_F429ZI)|| \
      defined(TARGET_DISCO_F401VC)
DigitalOut out(PC_12);
DigitalIn in(PD_0);

#elif defined(TARGET_FF_ARDUINO)
DigitalOut out(D7);
DigitalIn in(D0);

#elif defined(TARGET_MAXWSNENV)
DigitalOut out(TP3);
DigitalIn in(TP4);

#elif defined(TARGET_MAX32600MBED)
DigitalOut out(P1_0);
DigitalIn in(P4_7);

#else
DigitalOut out(p5);
DigitalIn in(p25);

#endif

int main() {
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(DigitalIn DigitalOut);
    MBED_HOSTTEST_START("MBED_A5");

    out = 0;
    wait(0.1);
    if (in != 0) {
        printf("ERROR: in != 0\n");
        MBED_HOSTTEST_RESULT(false);
    }
    out = 1;
    wait(0.1);
    if (in != 1) {
        printf("ERROR: in != 1\n");
        MBED_HOSTTEST_RESULT(false);
    }

    MBED_HOSTTEST_RESULT(true);
}
