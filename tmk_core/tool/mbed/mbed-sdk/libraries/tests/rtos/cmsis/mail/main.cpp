#include "mbed.h"
#include "cmsis_os.h"

typedef struct {
  float    voltage; /* AD result of measured voltage */
  float    current; /* AD result of measured current */
  uint32_t counter; /* A counter value               */
} mail_t;

osMailQDef(mail_box, 16, mail_t);
osMailQId  mail_box;

void send_thread (void const *argument) {
    uint32_t i = 0;
    while (true) {
        i++; // fake data update
        mail_t *mail = (mail_t*)osMailAlloc(mail_box, osWaitForever);
        mail->voltage = (i * 0.1) * 33;
        mail->current = (i * 0.1) * 11;
        mail->counter = i;
        osMailPut(mail_box, mail);
        osDelay(1000);
    }
}

osThreadDef(send_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main (void) {
    mail_box = osMailCreate(osMailQ(mail_box), NULL);
    osThreadCreate(osThread(send_thread), NULL);

    while (true) {
        osEvent evt = osMailGet(mail_box, osWaitForever);
        if (evt.status == osEventMail) {
            mail_t *mail = (mail_t*)evt.value.p;
            printf("\nVoltage: %.2f V\n\r"   , mail->voltage);
            printf("Current: %.2f A\n\r"     , mail->current);
            printf("Number of cycles: %u\n\r", mail->counter);

            osMailFree(mail_box, mail);
        }
    }
}
