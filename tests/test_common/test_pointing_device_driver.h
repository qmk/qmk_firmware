// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void press_button(uint8_t btn);
void release_button(uint8_t btn);
void clear_all_buttons(void);

void set_x(int16_t x);
void clear_x(void);

void set_y(int16_t y);
void clear_y(void);

void set_h(int8_t h);
void clear_h(void);

void set_v(int8_t v);
void clear_v(void);

void clear_movement(void);

#ifdef __cplusplus
}
#endif
