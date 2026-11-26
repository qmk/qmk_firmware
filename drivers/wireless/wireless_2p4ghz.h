// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "report.h"

void    wireless_2p4ghz_init(void);
void    wireless_2p4ghz_task(void);
bool    wireless_2p4ghz_is_connected(void);
bool    wireless_2p4ghz_can_send_nkro(void);
uint8_t wireless_2p4ghz_keyboard_leds(void);
void    wireless_2p4ghz_send_keyboard(report_keyboard_t *report);
void    wireless_2p4ghz_send_nkro(report_nkro_t *report);
void    wireless_2p4ghz_send_mouse(report_mouse_t *report);
void    wireless_2p4ghz_send_consumer(uint16_t usage);
void    wireless_2p4ghz_send_system(uint16_t usage);
void    wireless_2p4ghz_send_raw_hid(uint8_t *data, uint8_t length);
void    wireless_2p4ghz_unpair(void);
