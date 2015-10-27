#include "test_env.h"

#if defined(TARGET_K64F) || defined(TARGET_KL05Z)
#define P1_1    (1 << 16)
#define P1_2    (1 << 17)
#define PORT_1  PortC

#define P2_1    (1 << 2)
#define P2_2    (1 << 3)
#define PORT_2  PortC

#elif defined(TARGET_LPC11U24)
#define P1_1    (1 <<  9) // p0.9
#define P1_2    (1 <<  8) // p0.8
#define PORT_1  Port0

#define P2_1    (1 << 24) // p1.24
#define P2_2    (1 << 25) // p1.25
#define PORT_2  Port1

#elif defined(TARGET_LPC1768) || defined(TARGET_LPC2368)
#define P1_1    (1 << 9)  // p0.9  -> p5
#define P1_2    (1 << 8)  // p0.8  -> p6
#define PORT_1  Port0

#define P2_1    (1 << 1)  // p2.1 -> p25
#define P2_2    (1 << 0)  // p2.0 -> p26
#define PORT_2  Port2

#elif defined(TARGET_LPC4088)
#define P1_1    (1 << 7)  // p0.7  -> p13
#define P1_2    (1 << 6)  // p0.6  -> p14
#define PORT_1  Port0

#define P2_1    (1 << 2)  // p1.2 -> p30
#define P2_2    (1 << 3)  // p1.3 -> p29
#define PORT_2  Port1

#elif defined(TARGET_LPC1114)
#define P1_1    (1 <<  9) // p0.9
#define P1_2    (1 <<  8) // p0.8
#define PORT_1  Port0

#define P2_1    (1 << 1) // p1.1
#define P2_2    (1 << 0) // p1.0
#define PORT_2  Port1

#elif defined(TARGET_KL25Z)
#define P1_1    (1 << 4)  // PTA4
#define P1_2    (1 << 5)  // PTA5
#define PORT_1  PortA

#define P2_1    (1 << 5)  // PTC5
#define P2_2    (1 << 6)  // PTC6
#define PORT_2  PortC

#elif defined(TARGET_nRF51822)
#define P1_1    (1 << 4)  // p4
#define P1_2    (1 << 5)  // p5
#define PORT_1  Port0

#define P2_1    (1 << 24)  // p24
#define P2_2    (1 << 25)  // p25
#define PORT_2  Port0

#elif defined(TARGET_MAXWSNENV)
#define P1_1    (1 << 0)
#define P1_2    (1 << 1)
#define PORT_1  Port0

#define P2_1    (1 << 0)
#define P2_2    (1 << 1)
#define PORT_2  Port1

#elif defined(TARGET_MAX32600MBED)
#define P1_1    (1 << 0)  // P1_0
#define P1_2    (1 << 1)  // P1_1
#define PORT_1  Port1

#define P2_1    (1 << 7)  // P4_7
#define P2_2    (1 << 6)  // P4_6
#define PORT_2  Port4

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
#define P1_1    (1 << 6)  // PC_6
#define P1_2    (1 << 5)  // PC_5
#define PORT_1  PortC

#define P2_1    (1 << 8)  // PB_8
#define P2_2    (1 << 9)  // PB_9
#define PORT_2  PortB
#endif

#define MASK_1   (P1_1 | P1_2)
#define MASK_2   (P2_1 | P2_2)

PortOut port_out(PORT_1, MASK_1);
PortIn  port_in (PORT_2, MASK_2);

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(PortOut PortIn);
    MBED_HOSTTEST_START("MBED_A10");

    port_out = MASK_1;
    wait(0.1);
    int value = port_in.read();
    if (value != MASK_2) {
        printf("[Test high] expected (0x%x) received (0x%x)\n", MASK_2, value);
        notify_completion(false);
    }

    port_out = 0;
    wait(0.1);
    value = port_in.read();
    if (value != 0) {
        printf("[Test low] expected (0x%x) received (0x%x)\n", 0, value);
        notify_completion(false);
    }

    notify_completion(true);
}
