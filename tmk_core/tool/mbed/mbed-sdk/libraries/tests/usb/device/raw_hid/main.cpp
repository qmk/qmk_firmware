#include "mbed.h"
#include "USBHID.h"

//We declare a USBHID device
USBHID hid;

//This report will contain data to be sent
HID_REPORT send_report;

Ticker tic;

void tic_handler();
void tic_handler() {
    hid.send(&send_report);
}

int main(void) {
    //Fill the report
    for(int i = 0; i < 64; i++)
        send_report.data[i] = i;
    send_report.length = 64;

    tic.attach(tic_handler, 1);

    while (1);
}
