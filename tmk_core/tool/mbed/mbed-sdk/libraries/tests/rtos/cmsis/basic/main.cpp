#include "mbed.h"
#include "cmsis_os.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

void led2_thread(void const *argument) {
    while (true) {
        led2 = !led2;
        osDelay(1000);
    }
}
osThreadDef(led2_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main() {
    osThreadCreate(osThread(led2_thread), NULL);

    while (true) {
        led1 = !led1;
        osDelay(500);
    }
}
