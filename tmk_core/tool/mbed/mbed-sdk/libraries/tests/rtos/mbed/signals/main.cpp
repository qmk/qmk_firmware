#include "mbed.h"
#include "test_env.h"
#include "rtos.h"

#define SIGNALS_TO_EMIT     100
#define SIGNAL_HANDLE_DELEY 25
#define SIGNAL_SET_VALUE    0x01

/*
 * The stack size is defined in cmsis_os.h mainly dependent on the underlying toolchain and
 * the C standard library. For GCC, ARM_STD and IAR it is defined with a size of 2048 bytes
 * and for ARM_MICRO 512. Because of reduce RAM size some targets need a reduced stacksize.
 */
#if defined(TARGET_STM32L053R8) || defined(TARGET_STM32L053C8)
    #define STACK_SIZE DEFAULT_STACK_SIZE/4
#else
    #define STACK_SIZE DEFAULT_STACK_SIZE
#endif

DigitalOut led(LED1);
volatile int signal_counter = 0;

void led_thread(void const *argument) {
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(SIGNAL_SET_VALUE);
        led = !led;
        signal_counter++;
    }
}

int main (void) {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Signals messaging);
    MBED_HOSTTEST_START("RTOS_4");

    Thread thread(led_thread, NULL, osPriorityNormal, STACK_SIZE);
    bool result = true;

    while (true) {
        Thread::wait(2 * SIGNAL_HANDLE_DELEY);
        thread.signal_set(SIGNAL_SET_VALUE);
        if (signal_counter == SIGNALS_TO_EMIT) {
            printf("Handled %d signals\r\n", signal_counter);
            break;
        }
    }
    MBED_HOSTTEST_RESULT(result);
    return 0;
}
