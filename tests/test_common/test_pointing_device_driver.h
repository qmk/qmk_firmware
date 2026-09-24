// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void pd_press_button(uint8_t btn);
void pd_release_button(uint8_t btn);
void pd_clear_all_buttons(void);

void pd_set_x(int16_t x);
void clear_x(void);

void pd_set_y(int16_t y);
void pd_clear_y(void);

void pd_set_h(int16_t h);
void pd_clear_h(void);

void pd_set_v(int16_t v);
void pd_clear_v(void);

void pd_clear_movement(void);

void pd_set_init(bool success);

#ifdef __cplusplus
}
#endif
