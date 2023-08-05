// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "hid_display.h"
#include "display.h"
#include "raw_hid.h"
#include "lvgl_helpers.h"

uint16_t home_screen_timer = 0;

/* screens */
static lv_obj_t *screen_home;
static lv_obj_t *screen_volume;
static lv_obj_t *screen_media;

/* home screen content */
static lv_obj_t *label_time;
static lv_obj_t *label_volume_home;
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;
static lv_obj_t *label_layer;
static lv_obj_t *label_caps;
#ifdef CAPS_WORD_ENABLE
static lv_obj_t *label_caps_word;
#endif
static lv_obj_t *label_layout;

/* volume screen content */
static lv_obj_t *arc_volume;
static lv_obj_t *label_volume_arc;

/* media screen content */
static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

enum layout { _EN = 0, _RU };
void set_layout_label(uint8_t layout) {
    switch (layout) {
        case _EN:
            lv_label_set_text(label_layout, "EN");
            break;

        case _RU:
            lv_label_set_text(label_layout, "RU");
            break;
    }
}

void read_string(uint8_t *data, char *string_data) {
    uint8_t data_length = data[1];
    memcpy(string_data, data + 2, data_length);
    string_data[data_length] = '\0';
}

void start_home_screen_timer(void) {
    dprint("start_home_screen_timer\n");
    home_screen_timer = timer_read();
}

void init_screen_home_custom(void) {
    screen_home = lv_scr_act();
    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    label_volume_home = lv_label_create(screen_home);
    lv_label_set_text(label_volume_home, "");

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, 0);
    use_flex_row(mods);

    label_gui   = create_button(mods, "GUI", &style_button, &style_button_active);
    label_alt   = create_button(mods, "ALT", &style_button, &style_button_active);
    label_ctrl  = create_button(mods, "CTL", &style_button, &style_button_active);
    label_shift = create_button(mods, "SFT", &style_button, &style_button_active);

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, "00:00");
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_t *caps = lv_obj_create(screen_home);
    lv_obj_add_style(caps, &style_container, 0);
    use_flex_row(caps);

    label_caps = create_button(caps, "CAPS", &style_button, &style_button_active);
#ifdef CAPS_WORD_ENABLE
    label_caps_word = create_button(caps, "CAPS WORD", &style_button, &style_button_active);
#endif

    lv_obj_t *bottom_row = lv_obj_create(screen_home);
    lv_obj_add_style(bottom_row, &style_container, 0);

    label_layer = lv_label_create(bottom_row);
    lv_label_set_text(label_layer, "");
    lv_obj_align(label_layer, LV_ALIGN_LEFT_MID, 10, 0);
    display_process_layer_state(0);

    label_layout = lv_label_create(bottom_row);
    lv_label_set_text(label_layout, "");
    lv_obj_align(label_layout, LV_ALIGN_RIGHT_MID, -10, 0);
    set_layout_label(0);
}

void init_screen_volume(void) {
    screen_volume = lv_obj_create(NULL);
    lv_obj_add_style(screen_volume, &style_screen, 0);

    arc_volume = lv_arc_create(screen_volume);
    lv_obj_set_size(arc_volume, 200, 200);
    lv_obj_center(arc_volume);

    label_volume_arc = lv_label_create(screen_volume);
    lv_label_set_text(label_volume_arc, "00");
    lv_obj_set_style_text_font(label_volume_arc, &lv_font_montserrat_48, LV_PART_MAIN);
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
    lv_obj_set_width(label_media_artist, lv_pct(90));
    lv_obj_set_style_text_align(label_media_artist, LV_TEXT_ALIGN_CENTER, 0);

    label_media_title = lv_label_create(screen_media);
    lv_label_set_text(label_media_title, "N/A");
    lv_label_set_long_mode(label_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_title, lv_pct(90));
    lv_obj_set_style_text_align(label_media_title, LV_TEXT_ALIGN_CENTER, 0);
}

bool display_init_user(void) {
    init_screen_home_custom();
    init_screen_volume();
    init_screen_media();

    return false;
}

void display_process_raw_hid_data(uint8_t *data, uint8_t length) {
    uint8_t data_type = data[0];
    char    string_data[length - 2];
    dprintf("display_process_raw_hid_data - received data_type %u \n", data_type);
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
            lv_scr_load(screen_volume);
            start_home_screen_timer();
            break;

        case _LAYOUT:
            dprintf("layout %d\n", data[1]);
            set_layout_label(data[1]);
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

void display_process_layer_state(uint8_t layer) {
    switch (layer) {
        case _QWERTY:
            lv_label_set_text(label_layer, "QWERTY");
            break;
        case _GAME:
            lv_label_set_text(label_layer, "GAME");
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

void display_housekeeping_task(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        home_screen_timer = 0;
        lv_scr_load(screen_home);
    }

    toggle_state(label_shift, LV_STATE_PRESSED, MODS_SHIFT);
    toggle_state(label_ctrl, LV_STATE_PRESSED, MODS_CTRL);
    toggle_state(label_alt, LV_STATE_PRESSED, MODS_ALT);
    toggle_state(label_gui, LV_STATE_PRESSED, MODS_GUI);
}

void display_process_caps(bool active) {
    toggle_state(label_caps, LV_STATE_PRESSED, active);
}

#ifdef CAPS_WORD_ENABLE
void display_process_caps_word(bool active) {
    dprint("display_process_caps_word\n");
    toggle_state(label_caps_word, LV_STATE_PRESSED, active);
}
#endif
