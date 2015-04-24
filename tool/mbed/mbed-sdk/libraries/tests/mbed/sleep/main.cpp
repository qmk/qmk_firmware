#include "test_env.h"

#if defined(TARGET_LPC4088)
InterruptIn wkp(P2_10);
#elif defined(TARGET_K22F)
InterruptIn wkp(D0);
#elif defined(TARGET_LPC11U68)
InterruptIn wkp(P0_16);
#else
InterruptIn wkp(p14);
#endif

void flip() {
    printf("button pressed\n");
}

int main() {
#if defined(TARGET_LPC11U68)
    wkp.mode(PullUp);
#endif
    wkp.rise(&flip);

    while (true) {
        // sleep();
        deepsleep();
    }
}
