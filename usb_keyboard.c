#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "usb_keyboard.h"
#include "print.h"
#include "debug.h"
#include "util.h"


// keyboard report.
static usb_keyboard_report_t _report0 = { {0}, 0, false };
static usb_keyboard_report_t _report1 = { {0}, 0, false };
usb_keyboard_report_t *usb_keyboard_report = &_report0;
usb_keyboard_report_t *usb_keyboard_report_prev = &_report1;

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

// enable NKRO
bool usb_keyboard_nkro = false;


int8_t usb_keyboard_send(void)
{
    return usb_keyboard_send_report(usb_keyboard_report);
}

static inline int8_t _send_report(usb_keyboard_report_t *report, uint8_t endpoint, uint8_t keys_start, uint8_t keys_end);
int8_t usb_keyboard_send_report(usb_keyboard_report_t *report)
{
    int8_t result = 0;

#ifdef NKRO_ENABLE
    if (usb_keyboard_nkro)
        result = _send_report(report, KBD2_ENDPOINT, 0, KBD2_REPORT_KEYS);
    else
#endif
    {
        if (usb_keyboard_protocol)
            result = _send_report(report, KBD_ENDPOINT, 0, KBD_REPORT_KEYS);
        else
            result = _send_report(report, KBD_ENDPOINT, 0, 6);
    }

    if (result) return result;
    usb_keyboard_idle_count = 0;
    report->is_sent =true;
    usb_keyboard_print_report(report);
    return 0;
}

void usb_keyboard_swap_report(void) {
    usb_keyboard_report_t *tmp = usb_keyboard_report_prev;
    usb_keyboard_report_prev = usb_keyboard_report;
    usb_keyboard_report = tmp;
}

void usb_keyboard_clear_report(void) {
    usb_keyboard_clear_keys();
    usb_keyboard_clear_mods();
    usb_keyboard_report->is_sent = false;
}

void usb_keyboard_clear_keys(void) {
    for (int i = 0; i < KEYS_MAX; i++) usb_keyboard_report->keys[i] = 0;
}

void usb_keyboard_clear_mods(void)
{
    usb_keyboard_report->mods = 0;
}

void usb_keyboard_set_keys(uint8_t *keys)
{
    for (int i = 0; i < KEYS_MAX; i++)
        usb_keyboard_report->keys[i] = keys[i];
}

void usb_keyboard_set_mods(uint8_t mods)
{
    usb_keyboard_report->mods = mods;
}

void usb_keyboard_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        usb_keyboard_add_mod(code);
    } else {
        usb_keyboard_add_key(code);
    }
}

static inline void _add_key_byte(uint8_t code);
static inline void _add_key_bit(uint8_t code);
void usb_keyboard_add_key(uint8_t code)
{
#ifdef NKRO_ENABLE
    if (usb_keyboard_nkro) {
        _add_key_bit(code);
        return;
    }
#endif
    _add_key_byte(code);
}

void usb_keyboard_add_mod(uint8_t code)
{
    usb_keyboard_report->mods |= MOD_BIT(code);
}

void usb_keyboard_del_code(uint8_t code)
{
    if (IS_MOD(code)) {
        usb_keyboard_del_mod(code);
    } else {
        usb_keyboard_del_key(code);
    }
}

void usb_keyboard_del_key(uint8_t code)
{
#ifdef NKRO_ENABLE
    if ((code>>3) < KEYS_MAX) {
        usb_keyboard_keys[code>>3] &= ~(1<<(code&7));
    }
#else
    for (int i = 0; i < KEYS_MAX; i++) {
        if (usb_keyboard_report->keys[i] == code) {
            usb_keyboard_report->keys[i] = KB_NO;
            return;
        }
    }
#endif
}

void usb_keyboard_del_mod(uint8_t code)
{
    usb_keyboard_report->mods &= ~MOD_BIT(code);
}

bool usb_keyboard_is_sent(void)
{
    return usb_keyboard_report->is_sent;
}

bool usb_keyboard_has_key(void)
{
    uint8_t keys = 0;    
    for (int i = 0; i < KEYS_MAX; i++) keys |= usb_keyboard_report->keys[i];
    return keys ? true : false;
}

bool usb_keyboard_has_mod(void)
{
    return usb_keyboard_report->mods ? true : false;
}

uint8_t usb_keyboard_get_key(void)
{
#ifdef NKRO_ENABLE
    if (usb_keyboard_nkro) {
        uint8_t i = 0;
        for (; i < KEYS_MAX && !usb_keyboard_keys[i]; i++);
        return i<<3 | biton(usb_keyboard_keys[i]);
    }
#endif
    return usb_keyboard_keys[0];
}

void usb_keyboard_print_report(usb_keyboard_report_t *report)
{
    if (!debug_keyboard) return;
    print("keys: ");
    for (int i = 0; i < KEYS_MAX; i++) { phex(report->keys[i]); print(" "); }
    print(" mods: "); phex(report->mods); print("\n");
}


static inline int8_t _send_report(usb_keyboard_report_t *report, uint8_t endpoint, uint8_t keys_start, uint8_t keys_end)
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
    UEDATX = 0;
    for (uint8_t i = keys_start; i < keys_end; i++) {
            UEDATX = report->keys[i];
    }
    UEINTX = 0x3A;
    SREG = intr_state;
    return 0;
}

static inline void _add_key_byte(uint8_t code)
{
    // TODO: fix ugly code
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < KEYS_MAX; i++) {
        if (usb_keyboard_keys_prev[i] == code) {
            usb_keyboard_keys[i] = code;
            break;
        }
        if (empty == -1 &&
                usb_keyboard_keys_prev[i] == 0 &&
                usb_keyboard_keys[i] == 0) {
            empty = i;
        }
    }
    if (i == KEYS_MAX) {
        if (empty != -1) {
            usb_keyboard_keys[empty] = code;
        }
    }
}

static inline void _add_key_bit(uint8_t code)
{
    if ((code>>3) < KEYS_MAX) {
        usb_keyboard_keys[code>>3] |= 1<<(code&7);
    }
}

