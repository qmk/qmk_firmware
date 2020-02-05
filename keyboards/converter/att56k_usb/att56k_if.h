/*
Copyright (C) 2019 by  engicoder (engicoder@engicoder.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without l> imitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum att56k_click_mode_e {
    ATT56K_CLICK_MODE_OFF,
    ATT56K_CLICK_MODE_MAKE,
    ATT56K_CLICK_MODE_MAKE_BREAK,
    ATT56K_CLICK_MODE_COUNT,
} att56k_click_mode_e;

void    att56k_init(void);
bool    att56k_has_data(void);
uint8_t att56k_recv(void);
void    att56k_click_cycle(void);
bool    att56k_device_detected(void);
