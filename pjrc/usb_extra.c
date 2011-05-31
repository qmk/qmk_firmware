#include <util/delay.h>
#include <avr/interrupt.h>
#include "host.h"
#include "usb_extra.h"


int8_t usb_extra_send(uint8_t report_id, uint16_t data)
{
	uint8_t intr_state, timeout;

	if (!usb_configured()) return -1;
	intr_state = SREG;
	cli();
	UENUM = EXTRA_ENDPOINT;
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
		UENUM = EXTRA_ENDPOINT;
	}

	UEDATX = report_id;
        UEDATX = data&0xFF;
        UEDATX = (data>>8)&0xFF;

	UEINTX = 0x3A;
	SREG = intr_state;
	return 0;
}

int8_t usb_extra_consumer_send(uint16_t bits)
{
	return usb_extra_send(REPORT_ID_CONSUMER, bits);
}

int8_t usb_extra_system_send(uint16_t bits)
{
	return usb_extra_send(REPORT_ID_SYSTEM, bits);
}
