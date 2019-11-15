#include "honeycomb.h"
#include "pointing_device.h"
#include "report.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void pointing_device_task(void){
	/*report_mouse_t currentReport = {};
    SERIAL_UART_INIT();
    uint32_t timeout = 0;

    //the m character requests the RF slave to send the mouse report
    SERIAL_UART_DATA = 'm';

    //trust the external inputs completely, erase old data
    uint8_t uart_data[5] = {0};

    //there are 10 bytes corresponding to 10 columns, and an end byte
    for (uint8_t i = 0; i < 5; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
		xprintf("\r\nTIMED OUT");
                break;
            }
        }
	xprintf("\r\nGOT DATA for %d",i);
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, bytes 1-4 are movement and scroll
    //but byte 5 has bits 0-3 for the scroll button state
	//(1000 if pressed, 0000 if not) and bits 4-7 are always 1
	//We can use this to verify the report sent properly.
    if (uart_data[4] == 0x0F || uart_data[4] == 0x8F)
    {
	xprintf("\r\nREQUESTED MOUSE, RECEIVED %i, %i, %i, %i, %i",uart_data[0],uart_data[1],uart_data[2],uart_data[3],uart_data[4]);
		currentReport = pointing_device_get_report();
        //shifting and transferring the info to the mouse report varaible
        //mouseReport.x = 127 max -127 min
		currentReport.x = (int8_t) uart_data[0];
        //mouseReport.y = 127 max -127 min
		currentReport.y = (int8_t) uart_data[1];
        //mouseReport.v = 127 max -127 min (scroll vertical)
		currentReport.v = (int8_t) uart_data[2];
        //mouseReport.h = 127 max -127 min (scroll horizontal)
		currentReport.h = (int8_t) uart_data[3];
        //mouseReport.buttons = 0x31 max (bitmask for mouse buttons 1-5) 0x00 min
		//mouse buttons 1 and 2 are handled by the keymap, but not 3
		if (uart_data[4] == 0x0F) { //then 3 is not pressed
			currentReport.buttons &= ~MOUSE_BTN3; //MOUSE_BTN3 is def in report.h
		} else { //3 must be pressed
			currentReport.buttons |= MOUSE_BTN3;
		}
		pointing_device_set_report(currentReport);
    } else {
	xprintf("\r\nRequested packet, data 4 was %d",uart_data[4]);
    }*/
    pointing_device_send();
}

void led_init(void) {
  setPinOutput(D1);
  writePinHigh(D1);
  setPinOutput(F4);
  writePinHigh(F4);
  setPinOutput(F5);
  writePinHigh(F5);
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	uart_init();
	led_init();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {

}
