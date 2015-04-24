#include "mbed.h"

Ticker ticker;
DigitalOut led1(LED1);
DigitalOut led2(LED2);

#if defined(TARGET_LPC1549)
// LPC1549 support only single CAN channel
CAN can1(D2, D3);
#else
CAN can1(p9, p10);
#endif

#if defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)
CAN can2(p34, p33);
#elif defined (TARGET_LPC1768)
CAN can2(p30, p29);
#endif
char counter = 0;

void printmsg(char *title, CANMessage *msg) {
    printf("%s [%03X]", title, msg->id);
    for(char i = 0; i < msg->len; i++) {
        printf(" %02X", msg->data[i]);
    }
    printf("\n");
}

void send() {
    printf("send()\n");
    CANMessage msg = CANMessage(1337, &counter, 1);
    if(can1.write(msg)) {
        printmsg("Tx message:", &msg);
        counter++;
    }
    led1 = !led1;
}

int main() {
    printf("main()\n");
    ticker.attach(&send, 1);
    CANMessage msg;
    while(1) {
#if !defined(TARGET_LPC1549)
        printf("loop()\n");
        if(can2.read(msg)) {
            printmsg("Rx message:", &msg);
            led2 = !led2;
        }
#endif
        wait(0.2);
    }
}
