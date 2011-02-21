#include <stdint.h>
#include "usb_keycodes.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "debug.h"
#include "host.h"
#include "util.h"


#ifdef USB_NKRO_ENABLE
bool keyboard_nkro = false;
#endif

static report_keyboard_t report0;
static report_keyboard_t report1;
report_keyboard_t *keyboard_report = &report0;
report_keyboard_t *keyboard_report_prev = &report1;

static inline void add_key_byte(uint8_t code);
static inline void add_key_bit(uint8_t code);


uint8_t host_keyboard_leds(void)
{
    return usb_keyboard_leds;
}

/* keyboard report operations */
void host_add_key(uint8_t key)
{
#ifdef USB_NKRO_ENABLE
    if (keyboard_nkro) {
        add_key_bit(key);
        return;
    }
#endif
    add_key_byte(key);
}

void host_add_mod_bit(uint8_t mod)
{
    keyboard_report->mods |= mod;
}

void host_set_mods(uint8_t mods)
{
    keyboard_report->mods = mods;
}

void host_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        host_add_mod_bit(MOD_BIT(code));
    } else {
        host_add_key(code);
    }
}

void host_swap_keyboard_report(void)
{
    report_keyboard_t *tmp = keyboard_report_prev;
    keyboard_report_prev = keyboard_report;
    keyboard_report = tmp;
}

void host_clear_keyboard_report(void)
{
    keyboard_report->mods = 0;
    for (int8_t i = 0; i < REPORT_KEYS; i++) {
        keyboard_report->keys[i] = 0;
    }
}

uint8_t host_has_anykey(void)
{
    uint8_t cnt = 0;
    for (int i = 0; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i])
            cnt++;
    }
    return cnt;
}

uint8_t host_get_first_key(void)
{
#ifdef USB_NKRO_ENABLE
    if (keyboard_nkro) {
        uint8_t i = 0;
        for (; i < REPORT_KEYS && !keyboard_report->keys[i]; i++)
            ;
        return i<<3 | biton(keyboard_report->keys[i]);
    }
#endif
    return keyboard_report->keys[0];
}


void host_send_keyboard_report(void)
{
    usb_keyboard_send_report(keyboard_report);
}

void host_mouse_send(report_mouse_t *report)
{
    usb_mouse_send(report->x, report->y, report->v, report->h, report->buttons);
}


static inline void add_key_byte(uint8_t code)
{
    // TODO: fix ugly code
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (keyboard_report_prev->keys[i] == code) {
            keyboard_report->keys[i] = code;
            break;
        }
        if (empty == -1 &&
                keyboard_report_prev->keys[i] == 0 &&
                keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

static inline void add_key_bit(uint8_t code)
{
    if ((code>>3) < REPORT_KEYS) {
        keyboard_report->keys[code>>3] |= 1<<(code&7);
    } else {
        debug("add_key_bit: can't add: "); phex(code); debug("\n");
    }
}
