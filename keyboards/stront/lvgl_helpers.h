// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_lvgl.h"

void hide_anim_var(lv_anim_t *a);
void show_anim_var(lv_anim_t *a);
void set_obj_opacity(void *obj, int32_t v);
void toggle_hidden(void *obj, bool visible);
void resize_font(void *label, int32_t v);

void debug_set_obj_border(lv_obj_t *obj);
