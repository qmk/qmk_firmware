#include "oled_util.h"
#include "split_util.h"
#include "rgb_util.h"
#include "images.h"

#ifdef OLED_ENABLE
void render_status_bar(void) {
    uint8_t modifiers = get_mods();
    led_t   led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\325\326"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("\327\330"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("\331\332"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("\333\334"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\275\276"), led_state.caps_lock);

    oled_write_P(PSTR(" "), false);

    render_kb();

    oled_write_P(PSTR("  "), false);

    render_capsword();
}

void render_capsword() {
    oled_write_P(PSTR("\235\236\237"), is_caps_word_on());
}

void render_kb() {
    if (isLeftHand) {
        oled_write_P(PSTR("\265\266\267\227\230"), false);
    } else {
        oled_write_P(PSTR("\225\226\267\270\271"), false);
    }
}

void render_rgb_animation_number(void) {
    oled_write_P(PSTR("\52:"), false);
    int  rgb_mode = rgblight_get_mode();
    char rgb_mode_str[10];
    sprintf(rgb_mode_str, (rgb_mode < 10) ? "0%d" : "%d", rgb_mode);
    oled_write(rgb_mode_str, false);
}

void render_qmk_logo(void) {
    oled_write_P(qmk_logo, false);
}

void render_kyria_logo(void) {
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

void render_layer() {
    oled_write_P(PSTR("\335\336:"), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("\272 QWERTY"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("\233 LOWER "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("\234 RAISE "), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("\274 ADJUST"), false);
            break;
        default:
            oled_write_P(PSTR(" Undef"), false);
    }
}

// Render
void render_master(void) {
    render_qmk_logo();
    oled_write_ln_P(PSTR("---------------------"), false);

    render_layer();

    oled_write_P(PSTR("      "), false);

    render_rgb_animation_number();

    oled_write_ln_P(PSTR(""), false);
    render_status_bar();
}

void render_slave(void) {
    render_kyria_logo();
}

void render_status(void) {
    if (is_keyboard_master()) {
        render_master();
    } else {
        render_slave();
    }
}

#endif
