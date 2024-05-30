#include "capsword.h"
#include "display.h"
#include "layers.h"
#include "quantum.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>

#include "images/nvlogo_small.qgf.c"

painter_image_handle_t image;
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

// layers
const char *layer_name = "------";

// standard styles
lv_style_t style_screen;
lv_style_t style_container;
lv_style_t style_container_row;
lv_style_t style_button;
lv_style_t style_button_active;

// colors
unsigned long nv_green = 0x76b900;

// events
uint32_t USER_EVENT_RGBMODE_UPDATE;

// screens
static lv_obj_t *screen_home;

// home screen content
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;
static lv_obj_t *label_capsword;
static lv_obj_t *label_curr_layer;
static lv_obj_t *label_rgb_mode;
// static lv_obj_t *label_caps;

// rgb matrix naming
extern rgb_config_t rgb_matrix_config;
#if defined(RGB_MATRIX_ENABLE)
#   include <rgb_matrix.h>

#   if defined(RGB_MATRIX_EFFECT)
#       undef RGB_MATRIX_EFFECT
#   endif

#   define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#   include "rgb_matrix_effects.inc"
#   undef RGB_MATRIX_EFFECT
};

#   define RGB_MATRIX_EFFECT(x)     \
        case RGB_MATRIX_EFFECT_##x: \
            return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#   include "rgb_matrix_effects.inc"
#   undef RGB_MATRIX_EFFECT
        default:
            return "UNKNOWN";
    }
}
#endif

void set_rgbmode_text_value(lv_obj_t *label) {
    uint8_t curr_effect = rgb_matrix_config.mode;
    if (lv_obj_is_valid(label)) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%s", rgb_matrix_name(curr_effect));
            for (int i = 1; i < sizeof(buf); ++i) {
            if (buf[i] == 0)
                break;
            else if (buf[i] == '_')
                buf[i] = ' ';
            else if (buf[i - 1] == ' ')
                buf[i] = toupper(buf[i]);
            else if (buf[i - 1] != ' ')
                buf[i] = tolower(buf[i]);
            }
        lv_label_set_text(label, buf);
    }
}

void ui_render_rgbmode(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_RGBMODE_UPDATE) {
        set_rgbmode_text_value(label_rgb_mode);
    }
}

void lvgl_event_triggers(void) {
    static uint16_t last_effect = 0xFFFF;
    uint8_t         curr_effect = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect = curr_effect;
        lv_event_send(label_rgb_mode, USER_EVENT_RGBMODE_UPDATE, NULL);
    }
}

void init_styles(void) {
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_black());
    lv_style_set_pad_all(&style_screen, 10);

    lv_style_init(&style_container);
    lv_style_set_pad_all(&style_container, 0);
    lv_style_set_bg_opa(&style_container, 0);
    lv_style_set_border_width(&style_container, 0);
    lv_style_set_width(&style_container, lv_pct(100));
    lv_style_set_height(&style_container, LV_SIZE_CONTENT);

    lv_style_init(&style_container_row);
    lv_style_set_pad_all(&style_container_row, 0);
    lv_style_set_bg_opa(&style_container_row, 0);
    lv_style_set_border_width(&style_container_row, 0);
    lv_style_set_width(&style_container_row, lv_pct(100));
    lv_style_set_height(&style_container_row, LV_SIZE_CONTENT);

    lv_style_init(&style_button);
    lv_style_set_pad_all(&style_button, 4);
    lv_style_set_radius(&style_button, 6);
    lv_style_set_text_color(&style_button, lv_color_white());

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, lv_color_hex(nv_green));
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_white());
}

void init_screen_home(void) {
    screen_home = lv_scr_act();

    lv_obj_add_style(screen_home, &style_screen, LV_PART_MAIN);
    use_flex_column(screen_home);

    lv_obj_t *layers = lv_obj_create(screen_home);
    lv_obj_add_style(layers, &style_container, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(layers, 20, LV_PART_MAIN);
    use_flex_column(layers);

    lv_obj_t *curr_layer = lv_obj_create(layers);
    lv_obj_add_style(curr_layer, &style_container_row, LV_PART_MAIN);
    use_flex_row(curr_layer);
    label_curr_layer = create_button(curr_layer, layer_name, &style_button, &style_button_active);

    lv_obj_t *rgb = lv_obj_create(screen_home);
    lv_obj_add_style(rgb, &style_container, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(rgb, 20, LV_PART_MAIN);
    use_flex_column(rgb);

    lv_obj_t *curr_rgb = lv_obj_create(rgb);
    lv_obj_add_style(curr_rgb, &style_container_row, LV_PART_MAIN);
    use_flex_row(curr_rgb);
    label_rgb_mode = create_button(curr_rgb, "NONE", &style_button, &style_button_active);
    lv_obj_add_event_cb(label_rgb_mode, ui_render_rgbmode, USER_EVENT_RGBMODE_UPDATE, NULL);

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(mods, 20, LV_PART_MAIN);
    use_flex_column(mods);

    lv_obj_t *mods_row1 = lv_obj_create(mods);
    lv_obj_add_style(mods_row1, &style_container_row, LV_PART_MAIN);
    use_flex_row(mods_row1);
    label_gui = create_button(mods_row1, "GUI", &style_button, &style_button_active);
    label_alt = create_button(mods_row1, "ALT", &style_button, &style_button_active);

    lv_obj_t *mods_row2 = lv_obj_create(mods);
    lv_obj_add_style(mods_row2, &style_container_row, LV_PART_MAIN);
    use_flex_row(mods_row2);
    label_ctrl = create_button(mods_row2, "CTL", &style_button, &style_button_active);
    label_shift = create_button(mods_row2, "SFT", &style_button, &style_button_active);
    label_capsword = create_button(mods_row2, "CAPSWORD", &style_button, &style_button_active);

    lv_obj_t *label_zodiark = lv_label_create(screen_home);
    lv_label_set_text(label_zodiark, "zodiarkpi");

#if LV_FONT_MONTSERRAT_48
    lv_obj_set_style_text_font(label_zodiark, &lv_font_montserrat_48, LV_PART_MAIN);
#endif
}

bool display_init_kb(void) {
    painter_device_t display = qp_st7789_make_spi_device(240, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 3);

    // Initialize right side screen
    if (!is_keyboard_left()) {
        qp_power(display, true);
        qp_init(display, QP_ROTATION_90);
        image = qp_load_image_mem(gfx_nvlogo_small);
        if (image != NULL) {
            print("image was not null\n");
            qp_drawimage(display, 0, 0, image);
        }
    }

    // Initialize left side screen
    if (is_keyboard_left()) {
        qp_set_viewport_offsets(display, 0, 0);
        if (!qp_init(display, QP_ROTATION_270) || !qp_power(display, true) || !qp_lvgl_attach(display)) return false;

        lv_disp_t *lv_display = lv_disp_get_default();
        lv_theme_t *lv_theme  = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
        lv_disp_set_theme(lv_display, lv_theme);
        init_styles();

        bool res = display_init_user();
        if (res) {
            dprint("display_init_kb - adding default home screen\n");
            init_screen_home();
        }
    }

    return true;
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

__attribute__((weak)) void display_housekeeping_task(void) {
    char layer_buf[14];

    switch(get_highest_layer(layer_state)) {
        case _QWERTY:
            layer_name = "QWERTY";
            break;
        case _SYMBOL:
            layer_name = "SYMBOL";
            break;
        case _NUMPAD:
            layer_name = "NUMPAD";
            break;
        case _MAGIC:
            layer_name = "MAGIC";
            break;
        case _WINDOW:
            layer_name = "WINDOW";
            break;
        default:
            break;
    }

    toggle_state(label_shift, LV_STATE_PRESSED, MODS_SHIFT);
    toggle_state(label_ctrl, LV_STATE_PRESSED, MODS_CTRL);
    toggle_state(label_alt, LV_STATE_PRESSED, MODS_ALT);
    toggle_state(label_gui, LV_STATE_PRESSED, MODS_GUI);
    toggle_state(label_capsword, LV_STATE_PRESSED, is_capsword_enabled);
    snprintf(layer_buf, sizeof(layer_buf), "LAYER: %s", layer_name);
    lv_label_set_text(label_curr_layer, layer_buf);
}
