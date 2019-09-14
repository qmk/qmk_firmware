/**
 * @file      microshell.c
 * @author    Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * MicroShell (Version 0.0.2)
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * The MIT License : https://opensource.org/licenses/MIT
 *
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "microshell.h"

#define PRINT_ACTION_ENABLED    (0)
#define PRINT_CODE_ENABLED      (0)

#if PRINT_ACTION_ENABLED

static void uart_puts(MICROSHELL *handle, char *str)
{
    while (*str) {
        handle->uart_putc(*str++);
    }
}

static void print_action(MICROSHELL *handle, MSCORE_ACTION action)
{
    switch (action) {
        case MSCORE_ACTION_IGNORE:      uart_puts(handle, "[IGNORE]");      break;
        case MSCORE_ACTION_DISPLAYABLE: uart_puts(handle, "[DISPLAYABLE]"); break;
        case MSCORE_ACTION_INSERT:      uart_puts(handle, "[INSERT]");      break;
        case MSCORE_ACTION_ENTER:       uart_puts(handle, "[ENTER]");       break;
        case MSCORE_ACTION_TAB:         uart_puts(handle, "[TAB]");         break;
        case MSCORE_ACTION_BS:          uart_puts(handle, "[BS]");          break;
        case MSCORE_ACTION_DEL:         uart_puts(handle, "[DEL]");         break;
        case MSCORE_ACTION_CTRL_A:      uart_puts(handle, "[Ctrl+A]");      break;
        case MSCORE_ACTION_CTRL_B:      uart_puts(handle, "[Ctrl+B]");      break;
        case MSCORE_ACTION_CTRL_C:      uart_puts(handle, "[Ctrl+C]");      break;
        case MSCORE_ACTION_CTRL_D:      uart_puts(handle, "[Ctrl+D]");      break;
        case MSCORE_ACTION_CTRL_E:      uart_puts(handle, "[Ctrl+E]");      break;
        case MSCORE_ACTION_CTRL_F:      uart_puts(handle, "[Ctrl+F]");      break;
        case MSCORE_ACTION_CTRL_G:      uart_puts(handle, "[Ctrl+G]");      break;
        case MSCORE_ACTION_CTRL_H:      uart_puts(handle, "[Ctrl+H]");      break;
        case MSCORE_ACTION_CTRL_I:      uart_puts(handle, "[Ctrl+I]");      break;
        case MSCORE_ACTION_CTRL_J:      uart_puts(handle, "[Ctrl+J]");      break;
        case MSCORE_ACTION_CTRL_K:      uart_puts(handle, "[Ctrl+K]");      break;
        case MSCORE_ACTION_CTRL_L:      uart_puts(handle, "[Ctrl+L]");      break;
        case MSCORE_ACTION_CTRL_M:      uart_puts(handle, "[Ctrl+M]");      break;
        case MSCORE_ACTION_CTRL_N:      uart_puts(handle, "[Ctrl+N]");      break;
        case MSCORE_ACTION_CTRL_O:      uart_puts(handle, "[Ctrl+O]");      break;
        case MSCORE_ACTION_CTRL_P:      uart_puts(handle, "[Ctrl+P]");      break;
        case MSCORE_ACTION_CTRL_Q:      uart_puts(handle, "[Ctrl+Q]");      break;
        case MSCORE_ACTION_CTRL_R:      uart_puts(handle, "[Ctrl+R]");      break;
        case MSCORE_ACTION_CTRL_S:      uart_puts(handle, "[Ctrl+S]");      break;
        case MSCORE_ACTION_CTRL_T:      uart_puts(handle, "[Ctrl+T]");      break;
        case MSCORE_ACTION_CTRL_U:      uart_puts(handle, "[Ctrl+U]");      break;
        case MSCORE_ACTION_CTRL_V:      uart_puts(handle, "[Ctrl+V]");      break;
        case MSCORE_ACTION_CTRL_W:      uart_puts(handle, "[Ctrl+W]");      break;
        case MSCORE_ACTION_CTRL_X:      uart_puts(handle, "[Ctrl+X]");      break;
        case MSCORE_ACTION_CTRL_Y:      uart_puts(handle, "[Ctrl+Y]");      break;
        case MSCORE_ACTION_CTRL_Z:      uart_puts(handle, "[Ctrl+Z]");      break;
        case MSCORE_ACTION_F1:          uart_puts(handle, "[F1]");          break;
        case MSCORE_ACTION_F2:          uart_puts(handle, "[F2]");          break;
        case MSCORE_ACTION_F3:          uart_puts(handle, "[F3]");          break;
        case MSCORE_ACTION_F4:          uart_puts(handle, "[F4]");          break;
        case MSCORE_ACTION_F5:          uart_puts(handle, "[F5]");          break;
        case MSCORE_ACTION_F6:          uart_puts(handle, "[F6]");          break;
        case MSCORE_ACTION_F7:          uart_puts(handle, "[F7]");          break;
        case MSCORE_ACTION_F8:          uart_puts(handle, "[F8]");          break;
        case MSCORE_ACTION_F9:          uart_puts(handle, "[F9]");          break;
        case MSCORE_ACTION_F10:         uart_puts(handle, "[F10]");         break;
        case MSCORE_ACTION_F11:         uart_puts(handle, "[F11]");         break;
        case MSCORE_ACTION_F12:         uart_puts(handle, "[F12]");         break;
        case MSCORE_ACTION_ARROW_LEFT:  uart_puts(handle, "[<]");           break;
        case MSCORE_ACTION_ARROW_RIGHT: uart_puts(handle, "[>]");           break;
        case MSCORE_ACTION_ARROW_UP:    uart_puts(handle, "[UP]");          break;
        case MSCORE_ACTION_ARROW_DOWN:  uart_puts(handle, "[DOWN]");        break;
        case MSCORE_ACTION_HOME:        uart_puts(handle, "[HOME]");        break;
        case MSCORE_ACTION_END:         uart_puts(handle, "[END]");         break;
        case MSCORE_ACTION_PAGE_UP:     uart_puts(handle, "[PAGE UP]");     break;
        case MSCORE_ACTION_PAGE_DOWN:   uart_puts(handle, "[PAGE DOWN]");   break;
    }
}

#endif

#if PRINT_CODE_ENABLED

static void print_code(MICROSHELL *handle, char c)
{
    static const char *txt = "0123456789ABCDEF";
    handle->uart_putc('[');
    handle->uart_putc('0');
    handle->uart_putc('x');
    handle->uart_putc(txt[(((unsigned char)c) >> 4) & 0x0F]);
    handle->uart_putc(txt[(((unsigned char)c) >> 0) & 0x0F]);
    handle->uart_putc(']');
}

#endif

static char *copy_forward(char *buf, int ofs_src, int ofs_des, int siz)
{
    int i;
    char *p_src = buf + ofs_src;
    char *p_des = buf + ofs_des;
    for (i = 0; i < siz; i++) {
        *p_des++ = *p_src++;
    }
    return buf;
}

static char *copy_backward(char *buf, int ofs_src, int ofs_des, int siz)
{
    int i;
    char *p_src = buf + ofs_src + siz;
    char *p_des = buf + ofs_des + siz;
    for (i = 0; i < siz; i++) {
        *p_des-- = *p_src--;
    }
    return buf;
}

static char *clean_buffer(char *buf, int siz)
{
    int i;
    char *p = buf;
    for (i = 0; i < siz; i++) {
        *p++ = 0;
    }
    return buf;
}

static int print_buffer(MICROSHELL *handle, char *buf, int ofs)
{
    int cnt = 0;
    char *p = buf + ofs;
    while (*p) {
        handle->uart_putc(*p++);
        cnt++;
    }
    return cnt;
}

static int print_char(MICROSHELL *handle, char c)
{
    handle->uart_putc(c);
    return 1;
}

static void print_return(MICROSHELL *handle)
{
    handle->uart_putc('\r');
    handle->uart_putc('\n');
}

static void cursor_left(MICROSHELL *handle, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        handle->uart_putc('\x1B');
        handle->uart_putc('[');
        handle->uart_putc('D');
    }
}

static void cursor_right(MICROSHELL *handle, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        handle->uart_putc('\x1B');
        handle->uart_putc('[');
        handle->uart_putc('C');
    }
}

void microshell_init(MICROSHELL *handle, MICROSHELL_UART_PUTC uart_putc, MICROSHELL_UART_AVAILABLE uart_available, MICROSHELL_UART_GETC uart_getc, MICROSHELL_ACTION_HOOK action_hook)
{
    mscore_init(&(handle->mscore));
    handle->uart_putc = uart_putc;
    handle->uart_available = uart_available;
    handle->uart_getc = uart_getc;
    handle->action_hook = action_hook;
}

char *microshell_getline(MICROSHELL *handle, char *buf, char *cur, int siz)
{
    char *ptr = cur;
    static int pos;
    static int len;
//    clean_buffer(buf, siz);
    while (1) {
        if (handle->uart_available()==0) return ptr;
        char c = handle->uart_getc();
        MSCORE_ACTION action = mscore_push(&(handle->mscore), c);
        if (handle->action_hook) {
            handle->action_hook(action);
        }
#if PRINT_ACTION_ENABLED
        print_action(handle, action);
#endif
#if PRINT_CODE_ENABLED
        print_code(handle, c);
#endif
        switch (action) {
            case MSCORE_ACTION_DISPLAYABLE:
                {
                    int n = 0;
                    copy_backward(buf, pos - 1, pos - 0, len - pos + 1);
                    handle->uart_putc(c);
                    *ptr++ = c;
                    pos++;
                    len++;
                    n += print_buffer(handle, buf, pos);
                    cursor_left(handle, n);
                    if (len >= siz - 1) {
                        print_return(handle);
                        goto end;
                    }
                }
                break;
            case MSCORE_ACTION_ENTER:
            case MSCORE_ACTION_CTRL_J:
                print_return(handle);
                goto end;
                break;
            case MSCORE_ACTION_CTRL_C:
                clean_buffer(buf, siz);
                print_char(handle, '^');
                print_char(handle, 'C');
                print_return(handle);
                goto end;
                break;
            case MSCORE_ACTION_BS:
            case MSCORE_ACTION_CTRL_H:
                if (pos > 0) {
                    int n = 0;
                    copy_forward(buf, pos, pos - 1, len - pos + 1);
                    ptr--;
                    pos--;
                    len--;
                    cursor_left(handle, 1);
                    n += print_buffer(handle, buf, pos);
                    n += print_char(handle, ' ');
                    cursor_left(handle, n);
                }
                break;
            case MSCORE_ACTION_DEL:
            case MSCORE_ACTION_CTRL_D:
                if (len > 0) {
                    int n = 0;
                    copy_forward(buf, pos + 1, pos + 0, len - pos + 1);
                    len--;
                    n += print_buffer(handle, buf, pos);
                    n += print_char(handle, ' ');
                    cursor_left(handle, n);
                }
                break;
            case MSCORE_ACTION_ARROW_LEFT:
            case MSCORE_ACTION_CTRL_B:
                if (pos > 0) {
                    ptr--;
                    pos--;
                    cursor_left(handle, 1);
                }
                break;
            case MSCORE_ACTION_ARROW_RIGHT:
            case MSCORE_ACTION_CTRL_F:
                if (pos < len) {
                    ptr++;
                    pos++;
                    cursor_right(handle, 1);
                }
                break;
            case MSCORE_ACTION_HOME:
            case MSCORE_ACTION_CTRL_A:
                if (pos > 0) {
                    int n = pos;
                    ptr -= n;
                    pos = 0;
                    cursor_left(handle, n);
                }
                break;
            case MSCORE_ACTION_END:
            case MSCORE_ACTION_CTRL_E:
                if (pos < len) {
                    int n = len - pos;
                    ptr += n;
                    pos = len;
                    cursor_right(handle, n);
                }
                break;
            default:
                break;
        }
    }

end:
    pos=0;
    len=0;
    return cur+siz;
}

