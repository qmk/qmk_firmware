// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lvgl_helpers.h"

lv_obj_t *create_button(lv_obj_t *parent, const char *text, lv_style_t *style, lv_style_t *style_pressed) {
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_add_style(label, style, 0);
    lv_obj_add_style(label, style_pressed, LV_STATE_PRESSED);
    return label;
}

void use_flex_row(void *obj) {
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
}

void use_flex_column(void *obj) {
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
}

void toggle_state(void *obj, lv_state_t state, bool enabled) {
    if (enabled) {
        lv_obj_add_state(obj, state);
    } else {
        lv_obj_clear_state(obj, state);
    }
}

void toggle_hidden(void *obj, bool visible) {
    if (visible) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

void resize_font(void *label, int32_t font_size) {
    dprintf("font size %ld\n", font_size);
#if LV_FONT_MONTSERRAT_8
    if (font_size == 8) return lv_obj_set_style_text_font(label, &lv_font_montserrat_8, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_10
    if (font_size <= 10) return lv_obj_set_style_text_font(label, &lv_font_montserrat_8, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_12
    if (font_size <= 12) return lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_14
    if (font_size <= 14) return lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_16
    if (font_size <= 16) return lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_18
    if (font_size <= 18) return lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_20
    if (font_size <= 20) return lv_obj_set_style_text_font(label, &lv_font_montserrat_20, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_22
    if (font_size <= 22) return lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_24
    if (font_size <= 24) return lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_26
    if (font_size <= 26) return lv_obj_set_style_text_font(label, &lv_font_montserrat_26, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_28
    if (font_size <= 28) return lv_obj_set_style_text_font(label, &lv_font_montserrat_28, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_30
    if (font_size <= 30) return lv_obj_set_style_text_font(label, &lv_font_montserrat_30, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_32
    if (font_size <= 32) return lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_34
    if (font_size <= 34) return lv_obj_set_style_text_font(label, &lv_font_montserrat_34, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_36
    if (font_size <= 36) return lv_obj_set_style_text_font(label, &lv_font_montserrat_36, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_38
    if (font_size <= 38) return lv_obj_set_style_text_font(label, &lv_font_montserrat_38, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_40
    if (font_size <= 40) return lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_42
    if (font_size <= 42) return lv_obj_set_style_text_font(label, &lv_font_montserrat_42, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_44
    if (font_size <= 44) return lv_obj_set_style_text_font(label, &lv_font_montserrat_44, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_46
    if (font_size <= 46) return lv_obj_set_style_text_font(label, &lv_font_montserrat_46, LV_PART_MAIN);
#endif
#if LV_FONT_MONTSERRAT_48
    if (font_size <= 48) return lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
#endif
}

void debug_set_obj_border(lv_obj_t *obj) {
    lv_color_t red = lv_color_hex(0xFF0000);
    lv_obj_set_style_border_color(obj, red, 0);
    lv_obj_set_style_border_width(obj, 1, 0);
}
