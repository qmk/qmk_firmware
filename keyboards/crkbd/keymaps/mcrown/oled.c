#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "mcrown.h"
#include "oled.h"

//#if defined(OLED_DRIVER_ENABLE)
#if 1

char keylog_str[KEYLOG_LEN] = {' '};
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
    oled_rotation_t oled_rot=OLED_ROTATION_180;

    if(TRUE==is_master)
    {
#ifdef OLED_VERTICAL
        oled_rot=OLED_ROTATION_270;
#else
        oled_rot=OLED_ROTATION_0;
#endif
    }
    return oled_rot;
}

void render_layout_state(void)
{
#ifdef OLED_VERTICAL
    oled_write_P(PSTR("Lyt:\n"), FALSE);
    switch (biton32(default_layer_state))
    {
        case _COLEMAK:
            oled_write_P(PSTR("Clmak"), FALSE);
            break;

        case _DVORAK:
            oled_write_P(PSTR("Dvak"), FALSE);
            break;

        case _QWERTY:
            oled_write_P(PSTR("Qwty"), FALSE);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), FALSE);
            break;
    }
#else
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
#endif
}

void oled_white_space(void)
{
    oled_write_P(PSTR(" "), FALSE);
}

void render_layer_state(void)
{
    bool lower;
    bool raise;
    bool adjust;
    bool numpad;

    lower = layer_state_is(_LOWER) & !layer_state_is(_ADJUST);
    raise = layer_state_is(_RAISE) & !layer_state_is(_ADJUST);
    adjust = layer_state_is(_ADJUST);
    numpad = layer_state_is(_NUMPAD);

#ifdef OLED_VERTICAL
    oled_write_P(PSTR("\nLyr:\n"), FALSE);
    if(lower)
    {
        oled_write_P(PSTR("Lwr\n"), TRUE);
    }
    else if(raise)
    {
        oled_write_P(PSTR("Ris\n"), TRUE);
    }
    else if(adjust)
    {
        oled_write_P(PSTR("Adj\n"), TRUE);
    }
    else if(numpad)
    {
        oled_write_P(PSTR("Num\n"), TRUE);
    }
    else
    {
        oled_write_P(PSTR("Def\n"), FALSE);
    }
#else
    oled_write_P(PSTR("\nLayer:"), FALSE);
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
#endif
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
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
        0x00};

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
    static uint8_t current_c_pos=0;

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
    {
        keycode&=0xFF;
    }

    if(current_c_pos>=(KEYLOG_LEN-1))
    {
        current_c_pos=0;
        memset(keylog_str, ' ', sizeof(char)*KEYLOG_LEN);
    }

    if(keycode < 60)
    {
        keylog_str[current_c_pos] = code_to_name[keycode];
        current_c_pos++;
    }

    keylog_str[KEYLOG_LEN - 1] = '\0';

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
