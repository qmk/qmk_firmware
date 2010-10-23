#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_mouse.h"
#include "print.h"


static bool is_sent = false;

// which buttons are currently pressed
uint8_t mouse_buttons=0;

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
uint8_t mouse_protocol=1;


// Set the mouse buttons.  To create a "click", 2 calls are needed,
// one to push the button down and the second to release it
int8_t usb_mouse_buttons(uint8_t left, uint8_t middle, uint8_t right)
{
	uint8_t mask=0;

	if (left) mask |= 1;
	if (middle) mask |= 4;
	if (right) mask |= 2;
	mouse_buttons = mask;
	return usb_mouse_move(0, 0, 0, 0);
}

// Move the mouse.  x, y and wheel are -127 to 127.  Use 0 for no movement.
int8_t usb_mouse_move(int8_t x, int8_t y, int8_t wheel, int8_t hwheel)
{
	uint8_t intr_state, timeout;

	if (!usb_configured()) return -1;
	if (x == -128) x = -127;
	if (y == -128) y = -127;
	if (wheel == -128) wheel = -127;
	if (hwheel == -128) hwheel = -127;
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
	UEDATX = mouse_buttons;
	UEDATX = x;
	UEDATX = y;
	UEDATX = wheel;
	UEDATX = hwheel;
        
	UEINTX = 0x3A;
	SREG = intr_state;
        is_sent = true;
	return 0;
}

void usb_mouse_clear(void) {
    is_sent = false;
}

bool usb_mouse_is_sent(void) {
    return is_sent;
}

void usb_mouse_print(int8_t mouse_x, int8_t mouse_y, int8_t wheel_v, int8_t wheel_h) {
    print("mouse btn|x y v h: ");
    phex(mouse_buttons); print("|");
    phex(mouse_x); print(" ");
    phex(mouse_y); print(" ");
    phex(wheel_v); print(" ");
    phex(wheel_h); print("\n");
}
