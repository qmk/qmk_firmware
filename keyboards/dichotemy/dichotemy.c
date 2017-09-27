#include "dichotemy.h"
#include "pointing_device.h"

void uart_init(void) {
	SERIAL_UART_INIT();
}

void pointing_device_task(void){
    SERIAL_UART_INIT();
    uint32_t timeout = 0;

    //the m character requests the RF slave to send the mouse report
    SERIAL_UART_DATA = 'm';

    //trust the external inputs completely, erase old data
    uint8_t uart_data[11] = {0};

    //there are 10 bytes corresponding to 10 columns, and an end byte
    for (uint8_t i = 0; i < 11; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
                break;
            }
        } 
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
    if (uart_data[10] == 0xE0)
    {
        //shifting and transferring the info to the mouse report varaible
        //mouseReport.x = 127 max -127 min
        //mouseReport.y = 127 max -127 min
        //mouseReport.v = 127 max -127 min (scroll vertical)
        //mouseReport.h = 127 max -127 min (scroll horizontal)
        //mouseReport.buttons = 0x31 max (bitmask for mouse buttons 1-5) 0x00 min
    }
}

void led_init(void) {
	DDRD  |= (1<<1);
	PORTD |= (1<<1);
	DDRF  |= (1<<4) | (1<<5);
	PORTF |= (1<<4) | (1<<5);
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
