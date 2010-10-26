#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "usb_keyboard.h"
#include "print.h"
#include "debug.h"


static bool is_sent = false;

// which modifier keys are currently pressed
// 1=left ctrl,    2=left shift,   4=left alt,    8=left gui
// 16=right ctrl, 32=right shift, 64=right alt, 128=right gui
uint8_t keyboard_modifier_keys=0;

// which keys are currently pressed, up to 6 keys may be down at once
uint8_t keyboard_keys[6]={0,0,0,0,0,0};

// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
uint8_t keyboard_protocol=1;

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
uint8_t keyboard_idle_config=125;

// count until idle timeout
uint8_t keyboard_idle_count=0;

// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
volatile uint8_t keyboard_leds=0;


// perform a single keystroke
int8_t usb_keyboard_press(uint8_t key, uint8_t modifier)
{
	int8_t r;

	keyboard_modifier_keys = modifier;
	keyboard_keys[0] = key;
	r = usb_keyboard_send();
	if (r) return r;
	keyboard_modifier_keys = 0;
	keyboard_keys[0] = 0;
	return usb_keyboard_send();
}

// send the contents of keyboard_keys and keyboard_modifier_keys
int8_t usb_keyboard_send(void)
{
	uint8_t i, intr_state, timeout;

	if (!usb_configured()) return -1;
	intr_state = SREG;
	cli();
	UENUM = KEYBOARD_ENDPOINT;
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
		UENUM = KEYBOARD_ENDPOINT;
	}
	UEDATX = keyboard_modifier_keys;
	UEDATX = 0;
	for (i=0; i<6; i++) {
		UEDATX = keyboard_keys[i];
	}
	UEINTX = 0x3A;
	keyboard_idle_count = 0;
	SREG = intr_state;
        is_sent = true;
	return 0;
}

void usb_keyboard_init(void) {
    usb_keyboard_clear();
    is_sent = false;
}

void usb_keyboard_clear(void) {
    usb_keyboard_clear_key();
    usb_keyboard_clear_mod();
}

void usb_keyboard_clear_key(void) {
    for (int i = 0; i < 6; i++) keyboard_keys[i] = 0;
}

void usb_keyboard_clear_mod(void) {
    keyboard_modifier_keys = 0;
}

bool usb_keyboard_is_sent(void) {
    return is_sent;
}

bool usb_keyboard_has_key(void) {
    uint8_t keys = 0;    
    for (int i = 0; i < 6; i++) keys |= keyboard_keys[i];
    return keys ? true : false;
}

bool usb_keyboard_has_mod(void) {
    return keyboard_modifier_keys ? true : false;
}

void usb_keyboard_print(void) {
    if (!debug_keyboard) return;
    print("\nkeys: ");
    for (int i = 0; i < 6; i++) { phex(keyboard_keys[i]); print(" "); }
    print("\n");
    print("mods: "); phex(keyboard_modifier_keys); print("\n");
}
