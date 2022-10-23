#include <stdio.h>
#include <string.h>
#include "oled.h"

#ifdef OLED_ENABLE
void render_host_led_state(void) { oled_write(read_host_led_state(), false); }

void render_layer_state(void) {
    char layer_name[17];
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
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

void render_logo(void) { oled_write(read_logo(), false); }

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

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_mode_icon(!get_enable_kc_lang());
        render_layer_state();
        render_host_led_state();
    } else {
        render_logo();
    }
    return false;
}
#endif  // OLED_ENABLE
