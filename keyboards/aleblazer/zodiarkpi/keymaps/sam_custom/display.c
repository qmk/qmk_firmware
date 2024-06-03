#include "capsword.h"
#include "display.h"
#include "layers.h"
#include "quantum.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include "ui/ui.h"

#include "images/nvlogo_small.qgf.c"

painter_image_handle_t image;
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

// layers
const char *layer_name = "------";

// hsv state
// lv_color_hsv_t col_hsv = {0, 0, 0};

// events
uint32_t USER_EVENT_RGBMODE_UPDATE;
uint32_t USER_EVENT_RGB_HUE_UPDATE;
uint32_t USER_EVENT_RGB_SAT_UPDATE;
uint32_t USER_EVENT_RGB_BRT_UPDATE;

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

void set_rgbhsv_text_value(lv_obj_t *hsvLabel, lv_obj_t *satLabel, lv_obj_t *brtLabel) {
    char hueBuf[8];
    char satBuf[8];
    char brtBuf[8];
    snprintf(hueBuf, sizeof(hueBuf), "%d", (rgb_matrix_get_hue() * 360) / 255);
    snprintf(satBuf, sizeof(satBuf), "%d", (rgb_matrix_get_sat() * 100) / 255);
    snprintf(brtBuf, sizeof(brtBuf), "%d", (rgb_matrix_get_val() * 100) / 255);
    lv_textarea_set_text(hsvLabel, hueBuf);
    lv_textarea_set_text(satLabel, satBuf);
    lv_textarea_set_text(brtLabel, brtBuf);
}

void ui_render_rgbhsv(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_RGB_HUE_UPDATE || event_code == USER_EVENT_RGB_SAT_UPDATE || event_code == USER_EVENT_RGB_SAT_UPDATE) {
        set_rgbhsv_text_value(ui_hueVal, ui_satVal, ui_brtVal);
    }
}

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
        lv_textarea_set_text(label, buf);
    }
}

void ui_render_rgbmode(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_RGBMODE_UPDATE) {
        set_rgbmode_text_value(ui_currRgb);
    }
}

void loadPage(lv_obj_t **target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void), lv_obj_t **curTarget) {
    if(*target == NULL)
        target_init();
    lv_scr_load_anim(*target, fademode, spd, delay, false);

    if(*curTarget == NULL) {
        lv_obj_del(*curTarget);
        curTarget = NULL;
    }
}

void lvgl_event_triggers(void) {
    lv_obj_t **activeScreen = (lv_obj_t**)lv_scr_act();
    switch(get_highest_layer(layer_state)) {
        case _MAGIC:
            if(lv_scr_act() != ui_Screen2) {
                loadPage(&ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_Screen2_screen_init, activeScreen);
            };
            break;
        default:
            if(lv_scr_act() != ui_Screen1) {
                loadPage(&ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_Screen1_screen_init, activeScreen);
            };
            break;
    }

    static uint16_t last_effect = 0xFFFF;
    uint8_t         curr_effect = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect = curr_effect;
        lv_event_send(ui_currRgb, USER_EVENT_RGBMODE_UPDATE, NULL);
    }

    static uint16_t last_hue = 0xFFFF;
    uint8_t         curr_hue = (rgb_matrix_get_hue() * 360) / 100;
    if (last_hue != curr_hue) {
        last_hue = curr_hue;
        lv_event_send(ui_hueVal, USER_EVENT_RGB_HUE_UPDATE, NULL);
    }

    static uint16_t last_sat = 0xFFFF;
    uint8_t         curr_sat = (rgb_matrix_get_sat() * 360) / 100;
    if (last_sat != curr_sat) {
        last_sat = curr_sat;
        lv_event_send(ui_satVal, USER_EVENT_RGB_SAT_UPDATE, NULL);
    }

    static uint16_t last_brt = 0xFFFF;
    uint8_t         curr_brt = (rgb_matrix_get_val() * 360) / 100;
    if (last_brt != curr_brt) {
        last_brt = curr_brt;
        lv_event_send(ui_brtVal, USER_EVENT_RGB_BRT_UPDATE, NULL);
    }
}

bool display_init_kb(void) {
    wait_ms(50);

    painter_device_t display = qp_st7789_make_spi_device(240, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 3);

    if (!is_keyboard_left()) {
        qp_power(display, true);
        qp_init(display, QP_ROTATION_90);
        image = qp_load_image_mem(gfx_nvlogo_small);
        if (image != NULL) {
            print("image was not null\n");
            qp_drawimage(display, 0, 0, image);
        }
    }

    if (is_keyboard_left()) {
        if (!qp_init(display, QP_ROTATION_270) || !qp_lvgl_attach(display)) return false;
        qp_lvgl_attach(display);

        keyboard_post_init_user();
        ui_init();

        lv_obj_add_event_cb(ui_currRgb, ui_render_rgbmode, USER_EVENT_RGBMODE_UPDATE, NULL);
        lv_obj_add_event_cb(ui_hueVal, ui_render_rgbhsv, USER_EVENT_RGB_HUE_UPDATE, NULL);
        lv_obj_add_event_cb(ui_satVal, ui_render_rgbhsv, USER_EVENT_RGB_SAT_UPDATE, NULL);
        lv_obj_add_event_cb(ui_brtVal, ui_render_rgbhsv, USER_EVENT_RGB_BRT_UPDATE, NULL);
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
    }


    if (is_keyboard_left()) {
      toggle_state(ui_shiftIndicator, LV_STATE_PRESSED, MODS_SHIFT);
      toggle_state(ui_ctrlIndicator, LV_STATE_PRESSED, MODS_CTRL);
      toggle_state(ui_altIndicator, LV_STATE_PRESSED, MODS_ALT);
      toggle_state(ui_guiIndicator, LV_STATE_PRESSED, MODS_GUI);
      toggle_state(ui_capswordIndicator, LV_STATE_PRESSED, is_capsword_enabled);

      snprintf(layer_buf, sizeof(layer_buf), "%s", layer_name);
      lv_textarea_set_text(ui_currLayer, layer_buf);
    }
}
