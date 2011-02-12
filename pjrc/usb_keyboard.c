#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "usb_keyboard.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "host.h"


// protocol setting from the host.  We use exactly the same report
// either way, so this variable only stores the setting since we
// are required to be able to report which setting is in use.
uint8_t usb_keyboard_protocol=1;

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
uint8_t usb_keyboard_idle_config=125;

// count until idle timeout
uint8_t usb_keyboard_idle_count=0;

// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
volatile uint8_t usb_keyboard_leds=0;


static inline int8_t send_report(report_keyboard_t *report, uint8_t endpoint, uint8_t keys_start, uint8_t keys_end);


int8_t usb_keyboard_send_report(report_keyboard_t *report)
{
    int8_t result = 0;

#ifdef USB_NKRO_ENABLE
    if (keyboard_nkro)
        result = send_report(report, KBD2_ENDPOINT, 0, KBD2_REPORT_KEYS);
    else
#endif
    {
        if (usb_keyboard_protocol)
            result = send_report(report, KBD_ENDPOINT, 0, KBD_REPORT_KEYS);
        else
            result = send_report(report, KBD_ENDPOINT, 0, 6);
    }

    if (result) return result;
    usb_keyboard_idle_count = 0;
    usb_keyboard_print_report(report);
    return 0;
}

void usb_keyboard_print_report(report_keyboard_t *report)
{
    if (!debug_keyboard) return;
    print("keys: ");
    for (int i = 0; i < REPORT_KEYS; i++) { phex(report->keys[i]); print(" "); }
    print(" mods: "); phex(report->mods); print("\n");
}


static inline int8_t send_report(report_keyboard_t *report, uint8_t endpoint, uint8_t keys_start, uint8_t keys_end)
{
    uint8_t intr_state, timeout;

    if (!usb_configured()) return -1;
    intr_state = SREG;
    cli();
    UENUM = endpoint;
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
            UENUM = endpoint;
    }
    UEDATX = report->mods;
    if (!keyboard_nkro)
        UEDATX = 0;
    for (uint8_t i = keys_start; i < keys_end; i++) {
            UEDATX = report->keys[i];
    }
    UEINTX = 0x3A;
    SREG = intr_state;
    return 0;
}
