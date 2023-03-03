// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef union {
    uint32_t raw;
    struct {
        bool audio   : 1;
        bool matrix  : 1;
        bool sipo    : 1;
        bool touch   : 1;
        bool unicode : 1;
        bool qp_xap  : 1;
    };
} user_config_t;

uint32_t custom_eeprom_generate(void);
void custom_eeprom_draw_config(void *arg);
