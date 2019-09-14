/**
 * @file      mscore.c
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

#include "mscore.h"
#include "msconf.h"

typedef char * MSCORE_STREAM;

typedef struct {
    MSCORE_STREAM stream;
    MSCORE_ACTION action;
} MSCORE_KEYMAP;

static const MSCORE_KEYMAP kmlist[] = {
#if MSCONF_KEYMAP_SWAP_BS_DEL
    {   "\x7f",                 MSCORE_ACTION_BS            },
    {   "\x1b\x5b\x33\x7e",     MSCORE_ACTION_DEL           },
#else
    {   "\x08",                 MSCORE_ACTION_BS            },
    {   "\x7f",                 MSCORE_ACTION_DEL           },
#endif
    {   "\x09",                 MSCORE_ACTION_TAB           },
    {   "\x1b\x5b\x32\x7e",     MSCORE_ACTION_INSERT        },
    {   "\x0d",                 MSCORE_ACTION_ENTER         },
#if MSCONF_KEYMAP_USE_CTRL
    {   "\x01",                 MSCORE_ACTION_CTRL_A        },
    {   "\x02",                 MSCORE_ACTION_CTRL_B        },
    {   "\x03",                 MSCORE_ACTION_CTRL_C        },
    {   "\x04",                 MSCORE_ACTION_CTRL_D        },
    {   "\x05",                 MSCORE_ACTION_CTRL_E        },
    {   "\x06",                 MSCORE_ACTION_CTRL_F        },
    {   "\x07",                 MSCORE_ACTION_CTRL_G        },
    {   "\x08",                 MSCORE_ACTION_CTRL_H        },
    {   "\x09",                 MSCORE_ACTION_CTRL_I        },
    {   "\x0a",                 MSCORE_ACTION_CTRL_J        },
    {   "\x0b",                 MSCORE_ACTION_CTRL_K        },
    {   "\x0c",                 MSCORE_ACTION_CTRL_L        },
    {   "\x0d",                 MSCORE_ACTION_CTRL_M        },
    {   "\x0e",                 MSCORE_ACTION_CTRL_N        },
    {   "\x0f",                 MSCORE_ACTION_CTRL_O        },
    {   "\x10",                 MSCORE_ACTION_CTRL_P        },
    {   "\x11",                 MSCORE_ACTION_CTRL_Q        },
    {   "\x12",                 MSCORE_ACTION_CTRL_R        },
    {   "\x13",                 MSCORE_ACTION_CTRL_S        },
    {   "\x14",                 MSCORE_ACTION_CTRL_T        },
    {   "\x15",                 MSCORE_ACTION_CTRL_U        },
    {   "\x16",                 MSCORE_ACTION_CTRL_V        },
    {   "\x17",                 MSCORE_ACTION_CTRL_W        },
    {   "\x18",                 MSCORE_ACTION_CTRL_X        },
    {   "\x19",                 MSCORE_ACTION_CTRL_Y        },
    {   "\x1a",                 MSCORE_ACTION_CTRL_Z        },
#endif
#if MSCONF_KEYMAP_USE_FUNCTION
    {   "\x1b\x5b\x31\x31\x7e", MSCORE_ACTION_F1            },
    {   "\x1b\x5b\x31\x32\x7e", MSCORE_ACTION_F2            },
    {   "\x1b\x5b\x31\x33\x7e", MSCORE_ACTION_F3            },
    {   "\x1b\x5b\x31\x34\x7e", MSCORE_ACTION_F4            },
    {   "\x1b\x5b\x31\x35\x7e", MSCORE_ACTION_F5            },
    {   "\x1b\x5b\x31\x37\x7e", MSCORE_ACTION_F6            },
    {   "\x1b\x5b\x31\x38\x7e", MSCORE_ACTION_F7            },
    {   "\x1b\x5b\x31\x39\x7e", MSCORE_ACTION_F8            },
    {   "\x1b\x5b\x32\x30\x7e", MSCORE_ACTION_F9            },
    {   "\x1b\x5b\x32\x31\x7e", MSCORE_ACTION_F10           },
    {   "\x1b\x5b\x32\x32\x7e", MSCORE_ACTION_F11           },
    {   "\x1b\x5b\x32\x33\x7e", MSCORE_ACTION_F12           },
    {   "\x1b\x4f\x50",         MSCORE_ACTION_F1            },
    {   "\x1b\x4f\x51",         MSCORE_ACTION_F2            },
    {   "\x1b\x4f\x52",         MSCORE_ACTION_F3            },
    {   "\x1b\x4f\x53",         MSCORE_ACTION_F4            },
    {   "\x1b\x5b\x31\x35\x7e", MSCORE_ACTION_F5            },
    {   "\x1b\x5b\x31\x37\x7e", MSCORE_ACTION_F6            },
    {   "\x1b\x5b\x31\x38\x7e", MSCORE_ACTION_F7            },
    {   "\x1b\x5b\x31\x39\x7e", MSCORE_ACTION_F8            },
    {   "\x1b\x5b\x32\x31\x7e", MSCORE_ACTION_F9            },
    {   "\x1b\x5b\x32\x32\x7e", MSCORE_ACTION_F10           },
    {   "\x1b\x5b\x32\x33\x7e", MSCORE_ACTION_F11           },
    {   "\x1b\x5b\x32\x34\x7e", MSCORE_ACTION_F12           },
#endif
#if MSCONF_KEYMAP_USE_ARROW
    {   "\x1b\x5b\x41",         MSCORE_ACTION_ARROW_UP      },
    {   "\x1b\x5b\x42",         MSCORE_ACTION_ARROW_DOWN    },
    {   "\x1b\x5b\x43",         MSCORE_ACTION_ARROW_RIGHT   },
    {   "\x1b\x5b\x44",         MSCORE_ACTION_ARROW_LEFT    },
#endif
#if MSCONF_KEYMAP_USE_HOME_END
    {   "\x1b\x4f\x48",         MSCORE_ACTION_HOME          },
    {   "\x1b\x4f\x46",         MSCORE_ACTION_END           },
    {   "\x1b[1~",              MSCORE_ACTION_HOME          },
    {   "\x1b[4~",              MSCORE_ACTION_END           },
#endif
#if MSCONF_KEYMAP_USE_PAGE
    {   "\x1b\x5b\x35\x7e",     MSCORE_ACTION_PAGE_UP       },
    {   "\x1b\x5b\x36\x7e",     MSCORE_ACTION_PAGE_DOWN     },
#endif
};

static int buf_length(char *buf)
{
    int n = 0;
    while (*buf++) {
        n++;
    }
    return n;
}

static int buf_match(char *a, char *b, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (*a++ != *b++) {
            return 0;
        }
    }
    return 1;
}

static int buf_clear(char *buf, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        buf[i] = 0;
    }
    return 1;
}

void mscore_init(MSCORE *handle)
{
    buf_clear(handle->keybuf, MSCORE_BUFFER_SIZE);
    handle->keycnt = 0;
}

MSCORE_ACTION mscore_push(MSCORE *handle, char c)
{
    int match = 0;
    handle->keybuf[handle->keycnt++] = c;
    const MSCORE_KEYMAP *p = &kmlist[0];
    const int N = sizeof(kmlist) / sizeof(kmlist[0]);
    int i;
    for (i = 0; i < N; i++) {
        if (handle->keycnt == buf_length(p->stream))  {
            if (buf_match(p->stream, handle->keybuf, handle->keycnt)) {
                handle->keycnt = 0;
                buf_clear(handle->keybuf, MSCORE_BUFFER_SIZE);
                return p->action;
            }
        } else {
            if (buf_match(p->stream, handle->keybuf, handle->keycnt)) {
                match = 1;
                break;
            }
        }
        p++;
    }
    if (!match) {
        handle->keycnt = 0;
        buf_clear(handle->keybuf, MSCORE_BUFFER_SIZE);
        if ((' ' <= c) && (c <= '~')) {
            return MSCORE_ACTION_DISPLAYABLE;
        }
    }
    return MSCORE_ACTION_IGNORE;
}

