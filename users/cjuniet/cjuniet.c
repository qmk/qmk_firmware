#include "cjuniet.h"

void render_status_bar(void) {
    uint8_t modifiers = get_mods();
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\325\326"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("\327\330"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("\331\332"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("\333\334"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("         "), false);
    oled_write_P(PSTR("\235\236"), led_state.caps_lock);
    oled_write_P(PSTR("\275\276"), led_state.num_lock);
}
