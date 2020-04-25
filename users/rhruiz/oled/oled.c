#include "oled.h"
#include "rhruiz.h"

static uint32_t oled_timer = 0;

// clang-format off
const char rhruiz_logo_lines[][21] PROGMEM = {
    {0x20, 0x94, 0x95, 0x96, 0x97, 0x98, 0x20, 0x20, 0x20, 0x20, 0x20, 0x88, 0x20, 0x20, 0x20, 0x20, 0x20, 0x16, 0x20, 0x20, 0},
    {0x20, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0x20, 0x20, 0x20, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xc9, 0xae, 0xaf, 0},
    {0x20, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0x20, 0x20, 0x20, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xc9, 0xce, 0xcf, 0}
};

static const char lc[][4][3] PROGMEM = {
    [_BL]      = {{0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}},
    [_FN1]     = {{0x20, 0x20, 0}, {0xb2, 0xb3, 0}, {0x92, 0x93, 0}, {0x20, 0x20, 0}},
    [_FN2]     = {{0x20, 0x20, 0}, {0x92, 0x93, 0}, {0xb2, 0xb3, 0}, {0x20, 0x20, 0}},
    [_CFG]     = {{0x82, 0x83, 0}, {0xa2, 0xa3, 0}, {0xc2, 0xc3, 0}, {0x82, 0x83, 0}},
    [_NUM]     = {{0xae, 0xaf, 0}, {0xce, 0xcf, 0}, {0x20, 0x20, 0}, {0xd2, 0xd3, 0}},
    [_GAME]    = {{0x20, 0x20, 0}, {0xb0, 0xb1, 0}, {0xd0, 0xd1, 0}, {0x20, 0x20, 0}},
    [_GAMEFN1] = {{0x20, 0x20, 0}, {0xb0, 0xb1, 0}, {0xd0, 0xd1, 0}, {0x11, 0x11, 0}},
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

void rhruiz_render_oled(void) {
    layer_state_t layer = biton32(layer_state);

    switch (layer) {
        case _FN1:
        case _FN2:
            for (uint8_t i = 0; i < 4; i++) {
                oled_write_P(PSTR("          "), false);

                for (uint8_t j = 0; j < 3; j++) {
                    oled_write_P(lc[layer][i], false);
                }

                oled_write_P(PSTR("\n"), false);
            }

            break;

        case _CFG:
            for (uint8_t i = 0; i < 4; i++) {
                for (uint8_t j = 0; j < 10; j++) {
                    oled_write_P(lc[layer][i], false);
                }

                oled_write_P(PSTR("\n"), false);
            }
            break;

        case _GAME:
        case _GAMEFN1:
        default:
            for (uint8_t i = 0; i < 4; i++) {
                oled_write_P(PSTR("           "), false);
                oled_write_ln_P(lc[layer][i], false);
            }

            break;
    }
}

void rhruiz_oled_activity(void) {
    oled_timer = timer_read32();
}
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

