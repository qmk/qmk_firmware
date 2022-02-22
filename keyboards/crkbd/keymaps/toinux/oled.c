#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "oled.h"
#include "drivers/oled/oled_driver.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_mod_status(void) {

    const uint8_t modifiers = get_mods() | get_oneshot_mods();

    for (uint8_t i = 0; i < 2; i++) {
        oled_set_cursor(9,i);
        oled_write_P(gui_icon[(modifiers & MOD_MASK_GUI) ? 1 : 0][i], false);
        oled_write_P(ctrl_icon[(modifiers & MOD_MASK_CTRL) ? 1 : 0][i], false);
        oled_set_cursor(9,i+2);
        oled_write_P(alt_icon[(modifiers & MOD_MASK_ALT) ? 1 : 0][i], false);
        oled_write_P(shift_icon[(modifiers & MOD_MASK_SHIFT) ? 1 : 0][i], false);
    }

}

void oled_render_layer_state(void) {

    char c = 0x9F - get_highest_layer(layer_state|default_layer_state);

    oled_set_cursor(20,0);
    oled_write_char(0X00, false);

    oled_set_cursor(20,1);
    oled_write_char(c, false);
    c += 32;
    oled_set_cursor(20,2);
    oled_write_char(c, false);
    c += 32;
    oled_set_cursor(20,3);
    oled_write_char(c, false);

}

void oled_render_led_state(void) {
    // oled_advance_page(false) instead of oled_write_ln_P to not break OLED_TIMEOUT
    oled_write_P(PSTR("NUM"), host_keyboard_led_state().num_lock);
    oled_advance_page(false);
    oled_write_P(PSTR("CAP"), host_keyboard_led_state().caps_lock);
    oled_advance_page(false);
    oled_write_P(PSTR("SCL"), host_keyboard_led_state().scroll_lock);
    oled_advance_page(false);
}

char keylog_str[5] = {};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d", record->event.key.row, record->event.key.col);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void oled_render_logo(void) {
    static const char PROGMEM kpu_logo[][3] = {
        {0x82, 0x83, 0},
        {0x80, 0x81, 0},
        {0xa0, 0xa1, 0},
        {0xc0, 0xc1, 0}
    };
    for (uint8_t i = 0; i < 4; i++) {
        oled_write_ln_P(kpu_logo[i], false);
    }

}

bool oled_task_user(void) {
    if (is_keyboard_master ()) {
        oled_render_led_state();
        oled_render_keylog();
        oled_render_mod_status();
        oled_render_layer_state();
    } else {
        oled_render_logo();
        oled_scroll_right();
        oled_scroll_set_speed(4);
    }
    return false;
}
