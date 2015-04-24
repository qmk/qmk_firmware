#include "mbed.h"
#include "cmsis_os.h"

typedef struct {
    float    voltage;   /* AD result of measured voltage */
    float    current;   /* AD result of measured current */
    uint32_t counter;   /* A counter value               */
} message_t;

osPoolDef(mpool, 16, message_t);
osPoolId  mpool;

osMessageQDef(queue, 16, message_t);
osMessageQId  queue;

void send_thread (void const *argument) {
    uint32_t i = 0;
    while (true) {
        i++; // fake data update
        message_t *message = (message_t*)osPoolAlloc(mpool);
        message->voltage = (i * 0.1) * 33;
        message->current = (i * 0.1) * 11;
        message->counter = i;
        osMessagePut(queue, (uint32_t)message, osWaitForever);
        osDelay(1000);
    }
}

osThreadDef(send_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main (void) {
    mpool = osPoolCreate(osPool(mpool));
    queue = osMessageCreate(osMessageQ(queue), NULL);

    osThreadCreate(osThread(send_thread), NULL);

    while (true) {
        osEvent evt = osMessageGet(queue, osWaitForever);
        if (evt.status == osEventMessage) {
            message_t *message = (message_t*)evt.value.p;
            printf("\nVoltage: %.2f V\n\r"   , message->voltage);
            printf("Current: %.2f A\n\r"     , message->current);
            printf("Number of cycles: %u\n\r", message->counter);

            osPoolFree(mpool, message);
        }
    }
}
