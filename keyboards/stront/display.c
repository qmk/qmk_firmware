// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "qp.h"
#include "qp_lvgl.h"
#include "raw_hid.h"
#include "lvgl_helpers.h"

uint16_t home_screen_timer = 0;

static lv_obj_t *screen_home;
static lv_obj_t *screen_volume;
static lv_obj_t *screen_media;
static lv_obj_t *screen_fine;

static lv_obj_t *label_time;
static lv_obj_t *layout_icon;
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;

static lv_obj_t *arc_volume;
static lv_obj_t *label_volume;

static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

LV_IMG_DECLARE(flag_ru);
LV_IMG_DECLARE(flag_pl);
/* can be replaced with UK flag (update rules.mk as well) */
// LV_IMG_DECLARE(flag_uk);

LV_IMG_DECLARE(fine);
static lv_obj_t *fine_img;

enum data_type {
    _TIME = 0,
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
};

enum layout { _EN = 0, _RU };

void set_layout_icon(uint8_t layout) {
    switch (layout) {
        case _EN:
            lv_img_set_src(layout_icon, &flag_pl);
            break;

        case _RU:
            lv_img_set_src(layout_icon, &flag_ru);
            break;
    }
}

void read_string(uint8_t *data, char *string_data) {
    uint8_t data_length = data[1];
    memcpy(string_data, data + 2, data_length);
    string_data[data_length] = '\0';
}

void on_home_screen_unloaded(lv_event_t *event) {
    home_screen_timer = timer_read();
}

bool display_init(void) {
    backlight_enable();

    painter_device_t display = qp_st7789_make_spi_device(240, 300, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);

    qp_set_viewport_offsets(display, 0, 20);

    if (!qp_init(display, QP_ROTATION_180) || !qp_power(display, true) || !qp_lvgl_attach(display)) return false;

    dprint("qp_init \n");

    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_AMBER), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);

    screen_home = lv_scr_act();
    lv_obj_add_event_cb(screen_home, on_home_screen_unloaded, LV_EVENT_SCREEN_UNLOADED, NULL);

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, "0000");
    lv_obj_center(label_time);
    lv_obj_set_style_text_font(label_time, &montserrat_48_digits, LV_PART_MAIN);

    layout_icon = lv_img_create(screen_home);
    lv_obj_align(layout_icon, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_radius(layout_icon, 4, 0);
    lv_obj_set_style_clip_corner(layout_icon, true, 0);

    lv_obj_t *layout_label = lv_label_create(screen_home);
    lv_label_set_text(layout_label, "Lang");
    lv_obj_align(layout_label, LV_ALIGN_BOTTOM_RIGHT, 0, -45);

    label_shift = lv_label_create(screen_home);
    lv_label_set_text(label_shift, "SHIFT");
    lv_obj_align(label_shift, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_flag(label_shift, LV_OBJ_FLAG_HIDDEN);

    label_ctrl = lv_label_create(screen_home);
    lv_label_set_text(label_ctrl, "CTRL");
    lv_obj_align(label_ctrl, LV_ALIGN_TOP_MID, -40, 0);
    lv_obj_add_flag(label_ctrl, LV_OBJ_FLAG_HIDDEN);

    label_alt = lv_label_create(screen_home);
    lv_label_set_text(label_alt, "ALT");
    lv_obj_align(label_alt, LV_ALIGN_TOP_MID, 30, 0);
    lv_obj_add_flag(label_alt, LV_OBJ_FLAG_HIDDEN);

    label_gui = lv_label_create(screen_home);
    lv_label_set_text(label_gui, "GUI");
    lv_obj_align(label_gui, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_add_flag(label_gui, LV_OBJ_FLAG_HIDDEN);

    screen_volume = lv_obj_create(NULL);

    arc_volume = lv_arc_create(screen_volume);
    lv_arc_set_value(arc_volume, 0);
    lv_obj_set_size(arc_volume, 180, 180);
    lv_obj_center(arc_volume);

    label_volume = lv_label_create(screen_volume);
    lv_label_set_text(label_volume, "00");
    lv_obj_set_style_text_font(label_volume, &montserrat_48_digits, LV_PART_MAIN);
    lv_obj_center(label_volume);

    lv_obj_t *volume_text_label = lv_label_create(screen_volume);
    lv_label_set_text(volume_text_label, "Volume");
    lv_obj_align(volume_text_label, LV_ALIGN_BOTTOM_MID, 0, 0);

    screen_media = lv_obj_create(NULL);
    lv_obj_set_layout(screen_media, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(screen_media, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen_media, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    label_media_artist = lv_label_create(screen_media);
    lv_label_set_text(label_media_artist, "N/A");
    lv_label_set_long_mode(label_media_artist, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_artist, 240);
    lv_obj_set_style_text_align(label_media_artist, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label_media_artist);

    label_media_title = lv_label_create(screen_media);
    lv_label_set_text(label_media_title, "N/A");
    lv_label_set_long_mode(label_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_title, 240);
    lv_obj_set_style_text_align(label_media_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label_media_title);

    screen_fine = lv_obj_create(NULL);

    fine_img = lv_img_create(screen_fine);
    lv_img_set_src(fine_img, &fine);
    lv_obj_center(fine_img);

    return true;
}

void display_process_raw_hid_data(uint8_t *data, uint8_t length) {
    uint8_t data_type = data[0];
    char    string_data[length - 2];
    dprintf("received data_type %u \n", data_type);
    switch (data_type) {
        case _TIME:
            dprintf("time %02d:%02d\n", data[1], data[2]);
            lv_label_set_text_fmt(label_time, "%02d:%02d", data[1], data[2]);
            break;

        case _VOLUME:
            dprintf("volume %d\n", data[1]);
            lv_arc_set_value(arc_volume, data[1]);
            lv_label_set_text_fmt(label_volume, "%02d", data[1]);
            break;

        case _LAYOUT:
            dprintf("layout %d\n", data[1]);
            set_layout_icon(data[1]);
            break;

        case _MEDIA_ARTIST:
            read_string(data, string_data);
            dprintf("media artist %s\n", string_data);
            lv_label_set_text(label_media_artist, string_data);
            dprintf("artist screen 1 %s%s\n", lv_scr_act() == screen_media ? "media" : "", lv_scr_act() == screen_home ? "home" : "");
            if (lv_scr_act() != screen_media) {
                lv_scr_load(screen_media);
                // lv_scr_load_anim(media_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
            }
            dprintf("artist screen 2 %s%s\n", lv_scr_act() == screen_media ? "media" : "", lv_scr_act() == screen_home ? "home" : "");
            home_screen_timer = timer_read();
            break;

        case _MEDIA_TITLE:
            read_string(data, string_data);
            dprintf("media title %s\n", string_data);
            lv_label_set_text(label_media_title, string_data);
            dprintf("title screen 1 %s%s\n", lv_scr_act() == screen_media ? "media" : "", lv_scr_act() == screen_home ? "home" : "");
            if (lv_scr_act() != screen_media) {
                lv_scr_load(screen_media);
                // lv_scr_load_anim(media_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
            }
            dprintf("title screen 2 %s%s\n", lv_scr_act() == screen_media ? "media" : "", lv_scr_act() == screen_home ? "home" : "");
            home_screen_timer = timer_read();
            break;
    }
}

void display_process_record(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t data[32];
        data[0] = 0;

        switch (keycode) {
            case KC_VOLU:
            case KC_VOLD:
                data[0] = _VOLUME;
                // lv_scr_load_anim(volume_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
                lv_scr_load(screen_volume);
                home_screen_timer = timer_read();
                break;
            case KC_Q:
                lv_scr_load(screen_media);
                break;
            case KC_W:
                lv_scr_load(screen_fine);
                break;
        }

        if (data[0]) {
            raw_hid_send(data, sizeof(data));
        }
    }
}

void display_refresh_data(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        lv_scr_load(screen_home);
        home_screen_timer = 0;
    }

    toggle_hidden(label_shift, MODS_SHIFT);
    toggle_hidden(label_ctrl, MODS_CTRL);
    toggle_hidden(label_alt, MODS_ALT);
    toggle_hidden(label_gui, MODS_GUI);
}
