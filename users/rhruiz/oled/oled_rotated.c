#include "oled.h"
#include "rhruiz.h"

static uint32_t oled_timer = 0;

// clang-format off
const char rhruiz_logo_lines[][21] PROGMEM = {
    {0x20, 0x94, 0x95, 0x96, 0x97, 0x98, 0x20, 0x20, 0x20, 0x20, 0x20, 0x88, 0x20, 0x20, 0x20, 0x20, 0x20, 0x16, 0x20, 0x20, 0},
    {0x20, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0x20, 0x20, 0x20, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xc9, 0xae, 0xaf, 0},
    {0x20, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0x20, 0x20, 0x20, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xc9, 0xce, 0xcf, 0}
};

static const char _game_layer_logo[][5] PROGMEM = {
    {0xa8, 0xa9, 0xaa, 0xab, 0},
    {0xc8, 0xc9, 0xca, 0xcb, 0},
};

static const char _up_arrow_logo[][5] PROGMEM = {
    {0x20, 0x82, 0x83, 0x84, 0},
    {0x20, 0xa2, 0xa3, 0xa4, 0},
    {0x20, 0xc2, 0xc3, 0xc4, 0},
};

static const char _down_arrow_logo[][5] PROGMEM = {
    {0x20, 0x85, 0x86, 0x87, 0},
    {0x20, 0xa5, 0xa6, 0xa7, 0},
    {0x20, 0xc5, 0xc6, 0xc7, 0},
};

static const char _cfg_logo[][6] PROGMEM = {
    {0x80, 0x81, 0x80, 0x81, 0x80, 0},
    {0xa0, 0xa1, 0xa0, 0xa1, 0xa0, 0},
    {0xc0, 0xc1, 0xc0, 0xc1, 0xc0, 0}
};

// clang-format on

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return oled_init_keymap(rotation);
}

void rhruiz_render_logo_and_layer(void) {
    for (uint8_t i = 0; i < 4; i++) {
        oled_write_ln_P(rhruiz_logo_lines[i], false);
    }
}

void oled_clear_half_except(uint8_t lines) {
    for (uint8_t j = 0; j < (oled_max_lines() - lines) / 2; j++) {
        oled_write_P(PSTR("\n"), false);
    }
}

void rhruiz_render_oled(void) {
    layer_state_t layer = biton32(layer_state);
    /* static const char new_arrow[] = { 0x20, 0x85, 0xa5, 0x20 }; */

    oled_set_cursor(0, 0);

    switch (layer) {
        case _NUM:
            oled_clear_half_except(1);
            oled_write_ln_P(PSTR("\x88\x89\x8a"), false);
            oled_clear_half_except(1);
            break;

        case _FN1:
            oled_clear_half_except(6);
            oled_write_ln_P(_down_arrow_logo[0], false);
            oled_write_ln_P(_down_arrow_logo[1], false);
            oled_write_ln_P(_down_arrow_logo[2], false);
            oled_write_ln_P(_down_arrow_logo[0], false);
            oled_write_ln_P(_down_arrow_logo[1], false);
            oled_write_ln_P(_down_arrow_logo[2], false);
            oled_clear_half_except(6);
            break;

        case _FN2:
            oled_clear_half_except(6);
            oled_write_ln_P(_up_arrow_logo[0], false);
            oled_write_ln_P(_up_arrow_logo[1], false);
            oled_write_ln_P(_up_arrow_logo[2], false);
            oled_write_ln_P(_up_arrow_logo[0], false);
            oled_write_ln_P(_up_arrow_logo[1], false);
            oled_write_ln_P(_up_arrow_logo[2], false);
            oled_clear_half_except(6);
            break;

        case _CFG:
            for (uint8_t j = 0; j < oled_max_lines(); j++) {
                oled_write_P(_cfg_logo[j % 3], false);
            }
            break;

        case _GAMEFN1:
            oled_clear_half_except(2);

            oled_write_P(_game_layer_logo[0], false);
            oled_write_P(PSTR("\x1f"), false);
            oled_write_P(_game_layer_logo[1], false);
            oled_write_P(PSTR("\x1f"), false);

            oled_clear_half_except(2);
            break;

        case _GAME:
            oled_clear_half_except(2);

            oled_write_ln_P(_game_layer_logo[0], false);
            oled_write_ln_P(_game_layer_logo[1], false);

            oled_clear_half_except(2);
            break;

        default:
            oled_clear_half_except(2);
            oled_write_ln_P(PSTR("\x92\x93"), false);
            oled_write_ln_P(PSTR("\xb2\xb3\x16"), false);
            oled_clear_half_except(2);
            break;
    }
}

void rhruiz_oled_activity(void) { oled_timer = timer_read32(); }

__attribute__((weak))
void oled_task_user(void) {
    if (is_keyboard_master()) {
        if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
            oled_off();
            return;
        } else {
            oled_on();
        }

        rhruiz_render_oled();
    } else {
        // rhruiz_render_logo_and_layer();
        // oled_scroll_right();
        rhruiz_render_oled();
    }
}

void suspend_power_down_user(void) { oled_off(); }

void suspend_wakeup_init_user(void) { oled_on(); }
