#include "mbed.h"
#include "rtos.h"
#include "SDFileSystem.h"

#define FILE_LOC "/sd/test.txt"

Serial pc(USBTX, USBRX);
Serial gps(p28, p27);
Serial test(p9,p10);

SDFileSystem sd(p11, p12, p13, p14, "sd");

DigitalOut myled(LED1);
DigitalOut sdled(LED2);

void sd_thread(void const *argument) {
    while (true) {
        sdled = !sdled;
        FILE *fp = NULL;
        fp = fopen(FILE_LOC, "w");
        if( fp != NULL ) fclose(fp);
        Thread::wait(1000);
    }
}

int main() {
    Thread sdTask(sd_thread, NULL, osPriorityNormal, DEFAULT_STACK_SIZE * 2.25);
    while (true) {
        myled = !myled;
        Thread::wait(1000);
    }
}
