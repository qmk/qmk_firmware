#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_mouse.h"
#include "print.h"
#include "debug.h"


uint8_t usb_mouse_protocol=1;


int8_t usb_mouse_send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons)
{
	uint8_t intr_state, timeout;

	if (!usb_configured()) return -1;
	if (x == -128) x = -127;
	if (y == -128) y = -127;
	if (wheel_v == -128) wheel_v = -127;
	if (wheel_h == -128) wheel_h = -127;
	intr_state = SREG;
	cli();
	UENUM = MOUSE_ENDPOINT;
	timeout = UDFNUML + 50;
	while (1) {
		// are we ready to transmit?
		if (UEINTX & (1<<RWAL)) break;
		SREG = intr_state;
		// has the USB gone offline?
		if (!usb_configured()) return -1;
		// have we waited too long?
		if (UDFNUML == timeout) return -1;
		// get ready to try checking again
		intr_state = SREG;
		cli();
		UENUM = MOUSE_ENDPOINT;
	}
	UEDATX = buttons;
	UEDATX = x;
	UEDATX = y;
        if (usb_mouse_protocol) {
            UEDATX = wheel_v;
            UEDATX = wheel_h;
        }
        
	UEINTX = 0x3A;
	SREG = intr_state;
	return 0;
}

void usb_mouse_print(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons) {
    if (!debug_mouse) return;
    print("usb_mouse[btn|x y v h]: ");
    phex(buttons); print("|");
    phex(x); print(" ");
    phex(y); print(" ");
    phex(wheel_v); print(" ");
    phex(wheel_h); print("\n");
}
