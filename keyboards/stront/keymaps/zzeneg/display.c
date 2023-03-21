// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "qp.h"
#include "qp_lvgl.h"
#include "raw_hid.h"
#include "lvgl_helpers.h"
#include "layers.h"

#define MODS_SHIFT ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
#define MODS_CTRL ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL)
#define MODS_ALT ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT)
#define MODS_GUI ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI)

uint16_t home_screen_timer = 0;

/* shared styles */
static lv_style_t style_screen;
static lv_style_t style_container;
static lv_style_t style_button;
static lv_style_t style_button_active;

/* screens */
static lv_obj_t *screen_home;
static lv_obj_t *screen_volume;
static lv_obj_t *screen_media;
// static lv_obj_t *screen_fine;

/* home screen content */
static lv_obj_t *label_time;
static lv_obj_t *label_volume_home;
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;
static lv_obj_t *label_layer;
static lv_obj_t *icon_layout;

/* volume screen content */
static lv_obj_t *arc_volume;
static lv_obj_t *label_volume_arc;

/* media screen content */
static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

LV_IMG_DECLARE(flag_ru);
LV_IMG_DECLARE(flag_pl);
/* can be replaced with UK flag (update rules.mk as well) */
// LV_IMG_DECLARE(flag_uk);

// LV_IMG_DECLARE(fine);
// static lv_obj_t *fine_img;

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
            lv_img_set_src(icon_layout, &flag_pl);
            break;

        case _RU:
            lv_img_set_src(icon_layout, &flag_ru);
            break;
    }
}

void read_string(uint8_t *data, char *string_data) {
    uint8_t data_length = data[1];
    memcpy(string_data, data + 2, data_length);
    string_data[data_length] = '\0';
}

void start_home_screen_timer(void) {
    dprint("reset home screen \n");
    home_screen_timer = timer_read();
}

lv_obj_t *create_button(lv_obj_t *parent, const char *text) {
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_add_style(label, &style_button, 0);
    lv_obj_add_style(label, &style_button_active, LV_STATE_PRESSED);
    return label;
}

void init_styles(void) {
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_black());

    lv_style_init(&style_container);
    lv_style_set_bg_opa(&style_container, 0);
    lv_style_set_border_width(&style_container, 0);
    lv_style_set_width(&style_container, lv_pct(100));
    lv_style_set_height(&style_container, LV_SIZE_CONTENT);

    lv_style_init(&style_button);
    lv_style_set_radius(&style_button, 6);
    lv_style_set_text_color(&style_button, lv_palette_main(LV_PALETTE_AMBER));

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, lv_palette_main(LV_PALETTE_AMBER));
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_black());
}

void init_screen_home(void) {
    screen_home = lv_scr_act();
    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    label_volume_home = lv_label_create(screen_home);
    lv_label_set_text(label_volume_home, "");

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, 0);
    use_flex_row(mods);

    label_gui   = create_button(mods, "GUI");
    label_alt   = create_button(mods, "ALT");
    label_ctrl  = create_button(mods, "CTL");
    label_shift = create_button(mods, "SFT");

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, "00:00");
    lv_obj_set_style_text_font(label_time, &montserrat_48_digits, LV_PART_MAIN);

    lv_obj_t *bottom_row = lv_obj_create(screen_home);
    lv_obj_add_style(bottom_row, &style_container, 0);

    label_layer = lv_label_create(bottom_row);
    lv_label_set_text(label_layer, "");
    lv_obj_align(label_layer, LV_ALIGN_LEFT_MID, 0, 0);
    display_process_layer_state(0);

    icon_layout = lv_img_create(bottom_row);
    lv_obj_set_style_radius(icon_layout, 4, 0);
    lv_obj_set_style_clip_corner(icon_layout, true, 0);
    lv_obj_align(icon_layout, LV_ALIGN_RIGHT_MID, 0, 0);
}

void init_screen_volume(void) {
    screen_volume = lv_obj_create(NULL);
    lv_obj_add_style(screen_volume, &style_screen, 0);

    arc_volume = lv_arc_create(screen_volume);
    lv_obj_set_size(arc_volume, 200, 200);
    lv_obj_center(arc_volume);

    label_volume_arc = lv_label_create(screen_volume);
    lv_label_set_text(label_volume_arc, "00");
    lv_obj_set_style_text_font(label_volume_arc, &montserrat_48_digits, LV_PART_MAIN);
    lv_obj_center(label_volume_arc);

    lv_obj_t *volume_text_label = lv_label_create(screen_volume);
    lv_label_set_text(volume_text_label, "Volume");
    lv_obj_align(volume_text_label, LV_ALIGN_BOTTOM_MID, 0, -10);
}

void init_screen_media(void) {
    screen_media = lv_obj_create(NULL);
    lv_obj_add_style(screen_media, &style_screen, 0);
    use_flex_column(screen_media);
    lv_obj_set_flex_align(screen_media, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    label_media_artist = lv_label_create(screen_media);
    lv_label_set_text(label_media_artist, "N/A");
    lv_label_set_long_mode(label_media_artist, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_artist, lv_pct(100));
    lv_obj_set_style_text_align(label_media_artist, LV_TEXT_ALIGN_CENTER, 0);

    label_media_title = lv_label_create(screen_media);
    lv_label_set_text(label_media_title, "N/A");
    lv_label_set_long_mode(label_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_title, lv_pct(100));
    lv_obj_set_style_text_align(label_media_title, LV_TEXT_ALIGN_CENTER, 0);
}

bool display_init(void) {
    backlight_enable();

    painter_device_t display = qp_st7789_make_spi_device(240, 300, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);

    qp_set_viewport_offsets(display, 0, 20);

    if (!qp_init(display, QP_ROTATION_180) || !qp_power(display, true) || !qp_lvgl_attach(display)) return false;

    dprint("qp_init \n");

    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);

    init_styles();
    init_screen_home();
    init_screen_volume();
    init_screen_media();

    // screen_fine = lv_obj_create(NULL);

    // fine_img = lv_img_create(screen_fine);
    // lv_img_set_src(fine_img, &fine);
    // lv_obj_center(fine_img);

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
            lv_label_set_text_fmt(label_volume_home, "Volume: %02d%%", data[1]);
            lv_label_set_text_fmt(label_volume_arc, "%02d", data[1]);
            lv_arc_set_value(arc_volume, data[1]);
            break;

        case _LAYOUT:
            dprintf("layout %d\n", data[1]);
            set_layout_icon(data[1]);
            break;

        case _MEDIA_ARTIST:
            read_string(data, string_data);
            dprintf("media artist %s\n", string_data);
            lv_label_set_text(label_media_artist, string_data);
            lv_scr_load(screen_media);
            start_home_screen_timer();
            break;

        case _MEDIA_TITLE:
            read_string(data, string_data);
            dprintf("media title %s\n", string_data);
            lv_label_set_text(label_media_title, string_data);
            lv_scr_load(screen_media);
            start_home_screen_timer();
            break;
    }
}

void display_process_record(uint16_t keycode, keyrecord_t *record) {
    dprintf("display_process_record %u\n", keycode);
    if (record->event.pressed) {
        uint8_t data[32];
        data[0] = 0;

        switch (keycode) {
            case KC_VOLU:
            case KC_VOLD:
            case KC_ESC:
                data[0] = _VOLUME;
                lv_scr_load(screen_volume);
                start_home_screen_timer();
                break;
            case KC_Q:
                lv_scr_load(screen_media);
                break;
                // case KC_W:
                //     lv_scr_load(screen_fine);
                //     break;
        }

        if (data[0]) {
            dprintf("raw_hid_send %u\n", data[0]);
            raw_hid_send(data, sizeof(data));
        }
    }
}

void display_refresh_data(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        home_screen_timer = 0;
        lv_scr_load(screen_home);
    }

    toggle_state(label_shift, LV_STATE_PRESSED, MODS_SHIFT);
    toggle_state(label_ctrl, LV_STATE_PRESSED, MODS_CTRL);
    toggle_state(label_alt, LV_STATE_PRESSED, MODS_ALT);
    toggle_state(label_gui, LV_STATE_PRESSED, MODS_GUI);
}

void display_process_layer_state(uint8_t layer) {
    switch (layer) {
        case _QWERTY:
            lv_label_set_text(label_layer, "QWERTY");
            break;
        case _GAME:
            lv_label_set_text(label_layer, "GAME");
            break;
        case _EU:
            lv_label_set_text(label_layer, "EU");
            break;
        case _NAV:
            lv_label_set_text(label_layer, "NAV");
            break;
        case _NUMBER:
            lv_label_set_text(label_layer, "NUMBER");
            break;
        case _SYMBOL:
            lv_label_set_text(label_layer, "SYMBOL");
            break;
        case _FUNC:
            lv_label_set_text(label_layer, "FUNC");
            break;
        case _SYS:
            lv_label_set_text(label_layer, "SYSTEM");
            break;
    }
}
