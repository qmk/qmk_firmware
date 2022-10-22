/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "bn006.h"

led_config_t g_led_config = {
    {
        //Key Matrix to LED Index
        {0, 1, 2},
        {3, 4, 5}
    }, {
        //LED Index to Physical Positon
        {0, 0 }, {112, 0 }, {224, 0  },
        {0, 64}, {112, 64}, {224, 64 }
    }, {
        4, 4, 4,
        4, 4, 4
    }
};
