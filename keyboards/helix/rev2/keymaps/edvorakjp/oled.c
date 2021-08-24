#include <stdio.h>
#include <string.h>
#include "oled.h"

#ifdef OLED_DRIVER_ENABLE
void render_host_led_state(void) {
    char    led_state_str[24];
    uint8_t leds = host_keyboard_leds();

    bool is_num_lock_enabled    = leds & (1 << USB_LED_NUM_LOCK);
    bool is_caps_lock_enabled   = leds & (1 << USB_LED_CAPS_LOCK);
    bool is_scroll_lock_enabled = leds & (1 << USB_LED_SCROLL_LOCK);

    snprintf(led_state_str, sizeof(led_state_str), "NL:%s CL:%s SL:%s", is_num_lock_enabled ? "on" : "- ", is_caps_lock_enabled ? "on" : "- ", is_scroll_lock_enabled ? "on" : "- ");
    oled_write(led_state_str, false);
}

void render_layer_state(void) {
    char layer_name[17];
    oled_write_P(PSTR("Layer: "), false);

    switch (biton32(layer_state)) {
        case L_EDVORAKJP_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_EDVORAKJP_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_EDVORAKJP_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        default:
            snprintf(layer_name, sizeof(layer_name), "Undef-%ld", layer_state);
            oled_write_ln(layer_name, false);
    }
}

void render_logo(void) {
    static const char helix_logo[] PROGMEM = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(helix_logo, false);
}

void render_mode_icon(bool is_windows) {
    static const char logo[][2][3] = {
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
    };
    static char mode_icon[10];

    snprintf(mode_icon, sizeof(mode_icon), "%s\n%s ", logo[is_windows][0], logo[is_windows][1]);
    oled_write(mode_icon, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // flips the display 180 degrees if offhand
    return is_keyboard_left() ? rotation : rotation ^ OLED_ROTATION_180;
}

void oled_task_user(void) {
    if (is_keyboard_left()) {
        render_mode_icon(!get_enable_kc_lang());
        render_layer_state();
        render_host_led_state();
    } else {
        render_logo();
    }
}
#endif  // OLED_DRIVER_ENABLE
