// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <lv_conf.h>

#define QP_LVGL_TASK_PERIOD 30

/* change default font */
#undef LV_FONT_MONTSERRAT_14
#define LV_FONT_MONTSERRAT_14 0

#undef LV_FONT_MONTSERRAT_20
#define LV_FONT_MONTSERRAT_20 1

#undef LV_FONT_DEFAULT
#define LV_FONT_DEFAULT &lv_font_montserrat_20

/* add large font */
#undef LV_FONT_MONTSERRAT_48
#define LV_FONT_MONTSERRAT_48 1
