/*
Copylight 2024 mentako_ya
SPDX-License-Identifier: GPL-2.0-or-later
*/

// #include "transactions.h"
#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <print.h>
#endif


//////////////////////////////////////////////////////////////////////////////

// clang-format off
const matrix_row_t matrix_mask[MATRIX_ROWS] = {

    0b01111110,
    0b01111101,
    0b01111011,
    0b01110111,
    0b01101111,
    0b01011111,
    0b00111111,

    0b01111110,
    0b01111101,
    0b01111011,
    0b01110111,
    0b01101111,
    0b01011111,
    0b00111111,

};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    if defined(POINTING_DEVICE_LEFT)
#        define POINTING_DEVICE_THIS_SIDE is_keyboard_left()
#    elif defined(POINTING_DEVICE_RIGHT)
#        define POINTING_DEVICE_THIS_SIDE !is_keyboard_left()
#    elif defined(POINTING_DEVICE_COMBINED)
#        define POINTING_DEVICE_THIS_SIDE true
#    endif
#endif

//////////////////////////////////////////////////////////////////////////////
// Configurations

#ifndef MTK_CPI_DEFAULT
#    define MTK_CPI_DEFAULT 1000
#endif

#ifndef MTK_SCROLL_DIV_MIN
#    define MTK_SCROLL_DIV_MIN 1
#endif

#ifndef MTK_SCROLL_DIV_DEFAULT
#    define MTK_SCROLL_DIV_DEFAULT 10
#endif

#ifndef MTK_SCROLL_DIV_MAX
#    define MTK_SCROLL_DIV_MAX 32
#endif

#ifndef MTK_SCROLLBALL_INHIVITOR
#    define MTK_SCROLLBALL_INHIVITOR 5
#endif

#ifndef MTK_SCROLLSNAP_ENABLE
#    define MTK_SCROLLSNAP_ENABLE 1
#endif

#ifndef MTK_SCROLLSNAP_RESET_TIMER
#    define MTK_SCROLLSNAP_RESET_TIMER 100
#endif

#ifndef MTK_SCROLLSNAP_TENSION_THRESHOLD
#    define MTK_SCROLLSNAP_TENSION_THRESHOLD 12
#endif

//////////////////////////////////////////////////////////////////////////////
// Constants

ee_config_t ee_config;
mtk_config_t mtk_config = {
    .cpi_value   = MTK_CPI_DEFAULT,
    .cpi_changed = false,
    .scroll_mode = false,
    .scroll_direction = false,
    .scroll_div  = MTK_SCROLL_DIV_DEFAULT,
    .auto_mouse_mode = true,
    .auto_mouse_time_out = AUTO_MOUSE_TIME,
};

mtk_motion_t remote_motion;

static void add_cpi(int16_t delta) {
    int16_t v = mtk_get_cpi() + delta;
    mtk_set_cpi(v < 1 ? 1 : v);
}

static void add_scroll_div(int16_t delta) {
    int8_t v = mtk_get_scroll_div() + delta;
    mtk_set_scroll_div(v < MTK_SCROLL_DIV_MIN ? MTK_SCROLL_DIV_MIN : v);
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
static void add_auto_mouse_time_out(int16_t delta) {
    int16_t v = mtk_get_auto_mouse_time_out() + delta;
    mtk_set_auto_mouse_time_out(v < 100 ? 100 : v);
}
#endif


//////////////////////////////////////////////////////////////////////////////
// Types

void eeconfig_init_kb(void) {
    mtk_config.cpi_value = MTK_CPI_DEFAULT;
    mtk_config.cpi_changed = false;
    mtk_config.scroll_mode = false;
    mtk_config.scroll_direction = false;
    mtk_config.scroll_div = MTK_SCROLL_DIV_DEFAULT;
    mtk_config.auto_mouse_mode = true;
    mtk_config.auto_mouse_time_out = AUTO_MOUSE_TIME;

    ee_config_t c = {
        .cpi  = mtk_config.cpi_value / PMW33XX_CPI_STEP,
        .sdir = mtk_config.scroll_direction,
        .sdiv = mtk_config.scroll_div,
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
        .auto_mouse = mtk_config.auto_mouse_mode,
        .auto_mouse_time_out = mtk_config.auto_mouse_time_out / 100,
#endif
    };
    eeconfig_update_kb(c.raw);
    eeconfig_init_user();
    load_mtk_config();
}

void load_mtk_config(void) {
    ee_config.raw = eeconfig_read_kb();
    mtk_set_cpi(ee_config.cpi * PMW33XX_CPI_STEP);
    mtk_set_scroll_direction(ee_config.sdir);
    mtk_set_scroll_div(ee_config.sdiv);
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    mtk_set_auto_mouse_mode(ee_config.auto_mouse);
    mtk_set_auto_mouse_time_out(ee_config.auto_mouse_time_out * 100);
#endif
}

void save_mtk_config(void) {
    ee_config.cpi  = mtk_config.cpi_value / PMW33XX_CPI_STEP;
    ee_config.sdir = mtk_config.scroll_direction;
    ee_config.sdiv = mtk_config.scroll_div;
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    ee_config.auto_mouse = mtk_config.auto_mouse_mode;
    ee_config.auto_mouse_time_out = mtk_config.auto_mouse_time_out / 100;
#endif
    eeconfig_update_kb(ee_config.raw);
}

void matrix_init_kb(void) {
    load_mtk_config();
    if (mtk_config.cpi_value > PMW33XX_CPI_MAX){
        eeconfig_init_kb();
    }
    matrix_init_user();
}

void pointing_device_init_kb(void) {
        pmw33xx_init(0);                                    // index 1 is the second device.
        pmw33xx_set_cpi(0, mtk_config.cpi_value);       // applies to first sensor
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
        set_auto_mouse_enable(mtk_config.auto_mouse_mode);
        set_auto_mouse_timeout(mtk_config.auto_mouse_time_out);
#endif
}

// Scroll Accumulation
static int16_t scroll_h;
static int16_t scroll_v;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    if(timer_elapsed(mtk_config.motion.active_time) > 300){
        //motionの同期
        // sync_motion_data();
        //motionカウントリセット
        mtk_config.motion.x = 0;
        mtk_config.motion.y = 0;
        mtk_config.motion.active_time = timer_read();
    }
    mtk_config.motion.x += mouse_report.x;
    mtk_config.motion.y += mouse_report.y;

    int16_t x_rev =  mouse_report.y * -1;
    int16_t y_rev =  mouse_report.x * -1;

    if (mtk_get_scroll_mode()) {
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // oddball accumulate scroll
        scroll_h += x_rev;
        scroll_v += y_rev;

        int8_t scaled_scroll_h = scroll_h / (mtk_get_scroll_div() * 8);
        int8_t scaled_scroll_v = scroll_v / (mtk_get_scroll_div() * 8);

        // clear accumulated scroll on assignment

        if (scaled_scroll_h != 0) {
            mouse_report.h = -scaled_scroll_h;
            scroll_h       = 0;
        }

        if (scaled_scroll_v != 0) {
            if (mtk_get_scroll_direction()){
                mouse_report.v = scaled_scroll_v;
            } else {
                mouse_report.v = -scaled_scroll_v;
            }
            scroll_v       = 0;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;

    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
        mouse_report.h = 0;
        mouse_report.v = 0;
    }

    return pointing_device_task_user(mouse_report);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    mtk_set_scroll_mode(get_highest_layer(state) == 3);

    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 1 ... 6:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            if(!mtk_get_auto_mouse_mode()){
                state = remove_auto_mouse_layer(state, false);
            }
            set_auto_mouse_enable(mtk_get_auto_mouse_mode());
            break;
    }
    #endif

    return layer_state_set_user(state);
}

#ifdef SPLIT_LAYER_STATE_ENABLE
static int oled_anim_elapsed = 0;
void housekeeping_task_kb(void) {
    housekeeping_task_user();
    // OLED animation
    if(get_highest_layer(layer_state) != 0){
        oled_anim_elapsed = timer_read();
    }
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_user(keycode, record)) {
        return false;
    }

    // strip QK_MODS part.
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        keycode &= 0xff;
    }

    switch (keycode) {
        case SCRL_MO:
            mtk_set_scroll_mode(record->event.pressed);
            break;
    }

    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
        switch (keycode) {
        // process events which works on pressed only.
            case KBC_LOAD:
                load_mtk_config();
                break;
            case KBC_SAVE:
                save_mtk_config();
                break;
            case CPI_I100:
                add_cpi(100);
                break;
            case CPI_D100:
                add_cpi(-100);
                break;
            case CPI_I1K:
                add_cpi(1000);
                break;
            case CPI_D1K:
                add_cpi(-1000);
                break;
            case SCRL_TO:
                mtk_set_scroll_mode(!mtk_config.scroll_mode);
                break;
            case SCRL_INV:
                mtk_set_scroll_direction(!mtk_config.scroll_direction);
                break;
            case SCRL_DVI:
                add_scroll_div(1);
                break;
            case SCRL_DVD:
                add_scroll_div(-1);
                break;
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
            case AM_TG:
                mtk_set_auto_mouse_mode(!mtk_config.auto_mouse_mode);
                break;
            case AM_TOUT_INC:
                add_auto_mouse_time_out(100);
                break;
            case AM_TOUT_DEC:
                add_auto_mouse_time_out(-100);
                break;
#endif
            default:
                return true;
        }
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// configration function

bool mtk_get_scroll_mode(void) {
    return mtk_config.scroll_mode;
}

void mtk_set_scroll_mode(bool mode) {
    mtk_config.scroll_mode = mode;
}

bool mtk_get_scroll_direction(void) {
    return mtk_config.scroll_direction;
}

void mtk_set_scroll_direction(bool direction) {
    mtk_config.scroll_direction = direction;
}

uint8_t mtk_get_scroll_div(void) {
    return mtk_config.scroll_div == 0 ? MTK_SCROLL_DIV_DEFAULT : mtk_config.scroll_div;
}

void mtk_set_scroll_div(uint8_t div) {
    mtk_config.scroll_div = div > MTK_SCROLL_DIV_MAX ? MTK_SCROLL_DIV_MAX : div;
}

uint16_t mtk_get_cpi(void) {
    return mtk_config.cpi_value == 0 ? MTK_CPI_DEFAULT : mtk_config.cpi_value;
}

void mtk_set_cpi(uint16_t cpi) {
    if (cpi > PMW33XX_CPI_MAX) {
       cpi = PMW33XX_CPI_MAX;
    }else if (cpi < PMW33XX_CPI_MIN * 2) {
       cpi = PMW33XX_CPI_MIN * 2;
    }
    mtk_config.cpi_value   = cpi;
    mtk_config.cpi_changed = true;
    pointing_device_set_cpi(cpi == 0 ? MTK_CPI_DEFAULT - 1 : cpi - 1);
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool mtk_get_auto_mouse_mode(void) {
    return mtk_config.auto_mouse_mode;
}

void mtk_set_auto_mouse_mode(bool mode) {
    mtk_config.auto_mouse_mode = mode;
}

uint16_t mtk_get_auto_mouse_time_out(void){
    return mtk_config.auto_mouse_time_out;
}

void mtk_set_auto_mouse_time_out(uint16_t timeout){
    mtk_config.auto_mouse_time_out = timeout;
    set_auto_mouse_timeout(mtk_config.auto_mouse_time_out);
}
#endif

////////////////////////////////////////////////////////////////////////////
// oled function

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

char layer_str[22] = {};
void oled_render_layer(void) {
    snprintf(layer_str, sizeof(layer_str), "Layer:%-1d",
    get_highest_layer(layer_state));
    oled_write_ln_P(layer_str, false);
}

char keylog_str[22] = {};
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
            keycode = keycode & 0xFF;
    }

    if (keycode < 60) {
        name = code_to_name[keycode];
    }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "c:%-3dr:%-3dk:%04x %-c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write_ln_P(keylog_str, false);
}

char pointing_str[22] = {};
void oled_render_pointing(void) {
    snprintf(pointing_str, sizeof(pointing_str), "cp:%-5d dv:%-d sc:%-d",
    mtk_config.cpi_value, mtk_config.scroll_div, mtk_config.scroll_mode);
    oled_write_ln_P(pointing_str, mtk_get_scroll_mode());
}
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
char automouse_str[22] = {};
void oled_render_auto_mouse(void) {
    snprintf(automouse_str, sizeof(automouse_str), "h:%-3d o:%-3d m:%-3d",
    AUTO_MOUSE_THRESHOLD, mtk_get_auto_mouse_time_out(), abs(mtk_config.motion.x) + abs(mtk_config.motion.y));
    oled_write_ln_P(automouse_str, mtk_get_auto_mouse_mode());
}
#endif
char rgb_str[22] = {};
void oled_render_rgb(void) {
    snprintf(rgb_str, sizeof(rgb_str), "r:%-2d h:%-3ds:%-3dv:%-3d",
    rgblight_get_mode(), rgblight_get_hue(), rgblight_get_sat(),rgblight_get_val());
    oled_write_ln_P(rgb_str, false);
}

static int anim_frame = 0;
static int anim_frame_interval = 0;

static void render_logo(void) {

    static char indctr[3][6][22]=
    {
      {
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94},
        {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4},
        {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4},
      },
      {
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x93, 0x94},
        {0xA0, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xB3, 0xB4},
        {0xC0, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xD3, 0xD4},
      },
      {
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x80, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x93, 0x94},
        {0xA0, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xB3, 0xB4},
        {0xC0, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xD3, 0xD4},
      }
    };

    anim_frame += 1;
    if(anim_frame > 2){
        anim_frame = 0;
    }

    oled_write(indctr[anim_frame]  [0], false);
    oled_write(indctr[anim_frame]  [1], false);
    oled_write(indctr[anim_frame]  [2], false);
    oled_write(indctr[anim_frame]  [3], false);
    oled_write(indctr[anim_frame]  [4], false);
    oled_write(indctr[anim_frame]  [5], false);
}

bool oled_task_kb(void) {

    if (is_keyboard_master()) {
        oled_render_layer();
        oled_render_keylog();
        oled_render_rgb();
        oled_render_pointing();
        oled_render_auto_mouse();
    } else{
#ifdef SPLIT_LAYER_STATE_ENABLE
        if(timer_elapsed(oled_anim_elapsed) < 1000){
            if(timer_elapsed(anim_frame_interval) > 300){
                anim_frame_interval =  timer_read();
                render_logo();  // Renders a static logo
            }
        }
#endif
    }
    return false;
}
#endif
