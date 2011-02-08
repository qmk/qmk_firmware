#include "usb_keycodes.h"
#include "host.h"
#include "led.h"
#include "keyboard.h"
#include "print.h"

static report_keyboard_t report0;
static report_keyboard_t report1;
report_keyboard_t *keyboard_report = &report0;
report_keyboard_t *keyboard_report_prev = &report1;


void keyboard_set_led(uint8_t usb_led)
{
    led_set(usb_led);
}

void keyboard_send(void)
{
    host_keyboard_send(keyboard_report);
}

void keyboard_add_key(uint8_t code)
{
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (keyboard_report_prev->keys[i] == code) {
            keyboard_report->keys[i] = code;
            break;
        }
        if (empty == -1 && keyboard_report_prev->keys[i] == KB_NO && keyboard_report->keys[i] == KB_NO) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS && empty != -1) {
        keyboard_report->keys[empty] = code;
    }
}

void keyboard_add_mod_bit(uint8_t mod)
{
    keyboard_report->mods |= mod;
}

void keyboard_set_mods(uint8_t mods)
{
    keyboard_report->mods = mods;
}

void keyboard_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        keyboard_add_mod_bit(MOD_BIT(code));
    } else {
        keyboard_add_key(code);
    }
}

void keyboard_swap_report(void)
{
    report_keyboard_t *tmp = keyboard_report_prev;
    keyboard_report_prev = keyboard_report;
    keyboard_report = tmp;
}

void keyboard_clear_report(void)
{
    keyboard_report->mods = 0;
    for (int8_t i = 0; i < REPORT_KEYS; i++) {
        keyboard_report->keys[i] = 0;
    }
}

uint8_t keyboard_has_anykey(void)
{
    uint8_t cnt = 0;
    for (int i = 0; i < REPORT_KEYS; i++) {
        if (keyboard_report->keys[i])
            cnt++;
    }
    return cnt;
}

uint8_t *keyboard_get_keys(void)
{
    return keyboard_report->keys;
}

uint8_t keyboard_get_mods(void)
{
    return keyboard_report->mods;
}
