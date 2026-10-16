// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

void wb_bridge_init(void);
void wb_bridge_task(void);

void wb_bridge_keyboard(uint8_t *data);
void wb_bridge_nkro(uint8_t *data);
void wb_bridge_consumer(uint16_t usage);
void wb_bridge_system(uint8_t usage);
void wb_bridge_fn(bool pressed);
void wb_bridge_mouse(uint8_t *report);
void wb_bridge_name(const char *name);
void wb_bridge_devctrl(uint8_t cmd);

uint8_t wb_bridge_state(void);
uint8_t wb_bridge_battery(void);
uint8_t wb_bridge_indicator(void);
bool wb_bridge_busy(void);

uint8_t wb_bridge_take_devctrl_event(void);
