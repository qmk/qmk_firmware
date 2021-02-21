#include QMK_KEYBOARD_H
#include <stdio.h>
#include "mcrown.h"
#include "oled.h"

//#if defined(OLED_DRIVER_ENABLE)
#if 1

char keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer = 0;
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

extern uint8_t is_master;

static uint32_t propmt_oled_timer = 0;
static uint32_t standby_oled_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    if (is_master)
    {
        return OLED_ROTATION_0;
    }
    return OLED_ROTATION_180;
}

void render_layout_state(void)
{
    oled_write_P(PSTR("Layout: "), FALSE);
    switch (biton32(default_layer_state))
    {
        case _COLEMAK:
            oled_write_P(PSTR("Colemak"), FALSE);
            break;

        case _DVORAK:
            oled_write_P(PSTR("Dvorak"), FALSE);
            break;

        case _QWERTY:
            oled_write_P(PSTR("Qwerty"), FALSE);
            break;

        default:
            oled_write_ln_P(PSTR("Undefined"), FALSE);
            break;
    }
}

void oled_white_space(void)
{
    oled_write_P(PSTR(" "), FALSE);
}

void render_layer_state(void)
{
    oled_write_P(PSTR("\nLayer:"), FALSE);
    bool lower = layer_state_is(_LOWER) & !layer_state_is(_ADJUST);
    bool raise = layer_state_is(_RAISE) & !layer_state_is(_ADJUST);
    bool adjust = layer_state_is(_ADJUST);
    bool numpad = layer_state_is(_NUMPAD);

    if(lower)
    {
        oled_write_P(PSTR(" Lower "), TRUE);
    }
    else if(raise)
    {
        oled_write_P(PSTR(" Raise "), TRUE);
    }
    else if(adjust)
    {
        oled_write_P(PSTR(" Adjust "), TRUE);
    }
    else if(numpad)
    {
        oled_write_P(PSTR(" Numpad "), TRUE);
    }
    else
    {
        oled_write_P(PSTR(" Default"), FALSE);
    }
}

void render_status(void)
{
    render_layout_state();
    oled_write_P(PSTR("\n"), FALSE);
    render_layer_state();
    render_keylogger_status();
}

static void render_logo(void)
{
    static const char PROGMEM qmk_logo[] =
    {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,  \
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,  \
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,  \
        0
    };

    oled_write_P(qmk_logo, FALSE);
}

void oled_task_user(void)
{
    if (timer_elapsed32(standby_oled_timer) > 15000)
    {
        oled_off();
    }
    else
    {
        oled_on();
        if(TRUE==is_master)
        {
            render_status();
        }
        else
        {
            render_logo();
            oled_write_P(PSTR("\n"), FALSE);
            oled_scroll_left();
        }
    }
}

void add_keylog(uint16_t keycode)
{
    uint8_t i;

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
    {
        keycode = keycode & 0xFF;
    }

    for (i = KEYLOG_LEN - 1; i > 0; i--)
    {
        keylog_str[i] = keylog_str[i - 1];
    }

    if(keycode < 60)
    {
        keylog_str[0] = code_to_name[keycode];
    }

    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();

    standby_oled_timer = timer_read32();
}

void update_log(void)
{
    if(timer_elapsed(log_timer) > 750)
    {
        add_keylog(0);
    }
}

void render_keylogger_status(void)
{
    static bool prompt=TRUE;

    if(timer_elapsed32(propmt_oled_timer) > 300)
    {
        propmt_oled_timer = timer_read32();
        prompt=(prompt^TRUE)&TRUE;
    }

    if(TRUE==prompt)
    {
        oled_write_P(PSTR("\n>: "), FALSE);
    }
    else
    {
        oled_write_P(PSTR("\n : "), FALSE);
    }
    oled_write(keylog_str, FALSE);
}

#endif
