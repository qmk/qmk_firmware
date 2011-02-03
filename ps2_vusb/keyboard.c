#include "usb_keycodes.h"
#include "host.h"
#include "keyboard.h"

static report_keyboard_t report0;
static report_keyboard_t report1;
static report_keyboard_t *report = &report0;
static report_keyboard_t *report_prev = &report1;

void keyboard_send(void)
{
    host_keyboard_send(report);
}

bool keyboard_has_key(void)
{
    for (int i = 0; i < REPORT_KEYS; i++) {
        if (report->keys[i])
            return true;
    }
    return false;
}

void keyboard_add_mod(uint8_t mod)
{
    report->mods |= mod;
}

void keyboard_add_key(uint8_t code)
{
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (report_prev->keys[i] == code) {
            report->keys[i] = code;
            break;
        }
        if (empty == -1 && report_prev->keys[i] == KB_NO && report->keys[i] == KB_NO) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS && empty != -1) {
        report->keys[empty] = code;
    }
}

void keyboard_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        keyboard_add_mod(code);
    } else {
        keyboard_add_key(code);
    }
}

void keyboard_swap_report(void)
{
    report_keyboard_t *tmp = report_prev;
    report_prev = report;
    report = tmp;
}

void keyboard_clear_report(void)
{
    report->mods = 0;
    for (int8_t i = 0; i < REPORT_KEYS; i++) {
        report->keys[i] = 0;
    }
}

report_keyboard_t *keyboard_report(void)
{
    return report;
}

report_keyboard_t *keyboard_report_prev(void)
{
    return report_prev;
}
