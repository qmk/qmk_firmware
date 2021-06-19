/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "common_oled.h"
#include "oled_driver.h"
#include "rgb_matrix.h"

// for memcpy
#include <string.h>
#include <transactions.h>

typedef struct {
    bool selecting;
    uint8_t selection;
} kb_menu_status_t;

static kb_menu_status_t rgb_menu = { false, 4 };
static bool rgb_menu_changed = false;

void render_logo(void) {
    static const char PROGMEM font_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    oled_write_P(font_logo, false);
}

void render_icon(void) {
    static const char PROGMEM font_icon[] = {
        0x9b,0x9c,0x9d,0x9e,0x9f,
        0xbb,0xbc,0xbd,0xbe,0xbf,
        0xdb,0xdc,0xdd,0xde,0xdf,0
    };
    oled_write_P(font_icon, false);
}

#define RGB_FUNCTION_COUNT 6
typedef void (*rgb_matrix_f)(void);
const rgb_matrix_f rgb_matrix_functions[RGB_FUNCTION_COUNT][2] = {
    { rgb_matrix_increase_hue,      rgb_matrix_decrease_hue     },
    { rgb_matrix_increase_sat,      rgb_matrix_decrease_sat     },
    { rgb_matrix_increase_val,      rgb_matrix_decrease_val     },
    { rgb_matrix_increase_speed,    rgb_matrix_decrease_speed   },
    { rgb_matrix_step,              rgb_matrix_step_reverse     },
    { rgb_matrix_toggle,            rgb_matrix_toggle           }
};

void render_rgb_menu(void) {
    static char buffer[63] = {0};
    snprintf(buffer, sizeof(buffer), "Hue    %3dSatrn  %3dValue  %3dSpeed  %3dMode   %3dEnbld  %3d", 
    rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_config.enable);

    if (rgb_menu.selecting) {
        buffer[5 + rgb_menu.selection * 10] = '*';
    }
    else {
        buffer[5 + rgb_menu.selection * 10] = '>';
    }
    oled_write(buffer, false);
}

void rgb_menu_selection(void) {
    if (!is_keyboard_master()) return;
    rgb_menu.selecting = !rgb_menu.selecting;
    rgb_menu_changed = true;
}

void rgb_menu_action(bool clockwise) {
    if (!is_keyboard_master()) return;
    if (rgb_menu.selecting)  {
        if (!clockwise) {
            rgb_menu.selection = (rgb_menu.selection - 1);
            if (rgb_menu.selection >= RGB_FUNCTION_COUNT)
                rgb_menu.selection = RGB_FUNCTION_COUNT - 1;
        }
        else {
            rgb_menu.selection = (rgb_menu.selection + 1) % RGB_FUNCTION_COUNT;
        }
    }
    else {
        (*rgb_matrix_functions[rgb_menu.selection][clockwise])();
    }
    rgb_menu_changed = true;
}

void rgb_menu_update(int8_t transaction_id) {
    if (!is_keyboard_master()) return;
    if (!rgb_menu_changed) return;
    rgb_menu_changed = false;
    transaction_rpc_send(transaction_id, sizeof(kb_menu_status_t), &rgb_menu);
}

void rgb_menu_slave_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    memcpy(&rgb_menu, initiator2target_buffer, sizeof(kb_menu_status_t));
}