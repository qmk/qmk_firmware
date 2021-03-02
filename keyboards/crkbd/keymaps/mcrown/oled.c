/*
 *
 * This is the c oled module
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * MCrown: mariocc@comunidad.unam.mx 2021
 *
 */

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "mcrown.h"
#include "oled.h"

#define ASCII_TABLE_LENGTH       (0x80)
#define KEYLOG_STRING_STARTUP    (KEYLOG_EOL_LEN+1)

#define SPECIAL_KEYS_SHIFT(kc)   (0x18+(kc))

#ifdef OLED_DRIVER_ENABLE

static char last_c=' ';
char keylog_str[KEYLOG_EOL_LEN] = {' '};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer = 0;

/* Provides the ASCII value or the address of the character selected of the OLED font specified in glcfont.c */
static const char ascii_t[ASCII_TABLE_LENGTH] =
{
        /*     0          1         2         3        4         5         6         7         8         9         A         B         C         D         E         F                */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            ' ',         0x1A,    0x1B,     0x19,    0x18,      ' ',      ' ',      ' ',     0x11,      0x1C,    0x97,      ' ',      ' ',      ' ',      ' ',      ' ',         /* 0 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            ' ',         ' ',      ' ',      ' ',     ' ',      ' ',      ' ',      ' ',      ' ',       ' ',     ' ',     0x1D,      ' ',      ' ',      ' ',      ' ',         /* 1 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
           0x16,         '!',      '"',      '#',     '$',      '%',      '&',     '\'',      '(',       ')',     '*',      '+',      ',',      '-',      '.',      '/',         /* 2 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '0',         '1',      '2',      '3',     '4',      '5',      '6',      '7',      '8',       '9',     ':',      ';',      '<',      '=',      '>',      '?',         /* 3 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '@',         'A',      'B',      'C',     'D',      'E',      'F',      'G',      'H',       'I',     'J',      'K',      'L',      'M',      'N',      'O',         /* 4 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            'P',         'Q',      'R',      'S',     'T',      'U',      'V',      'W',      'X',       'Y',     'Z',      '[',      '\\',     ']',      '^',      '_',         /* 5 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '`',         'a',      'b',      'c',     'd',      'e',      'f',      'g',      'h',       'i',     'j',      'k',      'l',      'm',      'n',      'o',         /* 6 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            'p',         'q',      'r',      's',     't',      'u',      'v',      'w',      'x',       'y',     'z',      '{',      '|',      '}',      '~',     0x7F,         /* 7 */
};

/* This table is to remap and get the corresponding ASCII value based on the KEYCODE (taken as the index of the array) of quatum_keycodes.h module */
static const unsigned char code_to_ascii[ASCII_TABLE_LENGTH] =
{
        /*     0          1         2         3        4         5         6         7         8         9         A         B         C         D         E         F                */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
           0x00,        0x00,     0x00,     0x00,      'a',      'b',     'c',      'd',      'e',       'f',     'g',      'h',      'i',      'j',      'k',      'l',         /* 0 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            'm',         'n',      'o',      'p',      'q',      'r',     's',      't',      'u',       'v',     'w',      'x',      'y',      'z',      '1',      '2',         /* 1 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '3',         '4',      '5',      '6',      '7',      '8',     '9',      '0',     0x0A,      0x1B,    0x08,     0x09,      ' ',      '-',      '=',      '[',         /* 2 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            ']',        '\\',     0x00,      ';',     '\'',      '`',     ',',      '.',      '/',      0x00,    0x00,     0x00,     0x00,     0x00,      '!',      '@',         /* 3 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '#',         '$',      '%',      '^',      '&',      '*',     '(',      ')',     0x00,      0x00,    0x00,     0x00,     0x7F,      '_',      '+',      '{',         /* 4 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
            '}',         '|',     0x00,     0x00,     0x00,      '~',    0x00,     0x00,     0x00,      0x00,    0x00,     0x00,     0x00,     0x00,     0x00,     0x00,         /* 5 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
           0x00,        0x00,     0x00,     0x00,     0x00,     0x00,    0x00,     0x01,     0x02,      0x03,    0x04,     0x00,     0x00,     0x00,     0x00,     0x00,         /* 6 */
        /*          |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |           */
           0x00,        0x00,     0x00,     0x00,     0x00,     0x00,    0x00,     0x00,     0x00,      0x00,    0x00,     0x00,     0x00,     0x00,     0x00,     0x00,         /* 7 */
};

inline static char get_ascii(int16_t keycode)
{
    uint8_t ascii_idx=0x00;

    if(keycode<KC_F1)
    {
        ascii_idx=code_to_ascii[(uint8_t)keycode];
    }
    else if(keycode<KC_KP_ENTER)
    {
        ascii_idx=code_to_ascii[SPECIAL_KEYS_SHIFT(keycode)];
    }
    else if( TRUE==(QK_LSFT&keycode) )
    {
        ascii_idx=code_to_ascii[RM_LSFT(keycode)];
    }
//    else if()
//    {
//
//    }
    return ascii_t[ascii_idx];
}

extern uint8_t is_master;

static uint8_t current_cursor_pos=0;
static uint32_t cursor_oled_timer = 0;
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
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
    {
        keycode&=0x00FF;
    }

    if(current_cursor_pos>(KEYLOG_LEN-1)||(current_cursor_pos>KEYLOG_STRING_STARTUP))
    {
        current_cursor_pos=0;
        last_c=get_ascii(keycode);
        current_cursor_pos++;
    }
    else
    {
        if(keycode <= KC_TILD)
        {
            keylog_str[current_cursor_pos]=last_c;
            last_c=get_ascii(keycode);
            current_cursor_pos++;
        }
        keylog_str[current_cursor_pos] = '\0';
    }

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
    static bool cursor_f=TRUE;

    if(timer_elapsed32(cursor_oled_timer) > 300)
    {
        cursor_oled_timer = timer_read32();
        cursor_f=TOGGLE_BOOL_VAR(cursor_f);
    }
    oled_write_P(PSTR("\n>:"), FALSE);
    if(current_cursor_pos>(KEYLOG_LEN-1))
    {
        current_cursor_pos=0;
        memset(keylog_str, ' ', sizeof(char)*KEYLOG_EOL_LEN);
        /* Here the EOL is to clear with white spaces all the keylog area */
        keylog_str[KEYLOG_EOL_LEN-1] = '\0';
        oled_write(keylog_str, FALSE);
        /* Reset EOL to the begining of the keylog string */
        keylog_str[0] = '\0';
    }
    oled_write(keylog_str, FALSE);
    oled_write_char(last_c, cursor_f);

}

#endif /* End of OLED_DRIVER_ENABLE */
