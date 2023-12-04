// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"
#include "qp_surface.h"

extern painter_device_t      reverb_surface;
extern painter_device_t      reverb_display;
extern painter_font_handle_t roboto_font;

void display_key_counter(void);
void display_init_kb(void);
bool display_init_user(void);
void display_task_kb(void);
bool display_task_user(void);
