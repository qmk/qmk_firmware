#include "oled.h"
#include "rhruiz.h"

static uint32_t oled_timer = 0;

// clang-format off

#ifdef OLED_ROTATE
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

#else

const char _spacer[] PROGMEM = "          ";

static const char lc[][4][3] PROGMEM = {
    [_BL]      = {{0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}},
    [_FN1]     = {{0x20, 0x20, 0}, {0xb2, 0xb3, 0}, {0x92, 0x93, 0}, {0x20, 0x20, 0}},
    [_FN2]     = {{0x20, 0x20, 0}, {0x92, 0x93, 0}, {0xb2, 0xb3, 0}, {0x20, 0x20, 0}},
    [_CFG]     = {{0x80, 0x81, 0}, {0xa0, 0xa1, 0}, {0xc0, 0xc1, 0}, {0x80, 0x81, 0}},
    [_NUM]     = {{0xae, 0xaf, 0}, {0xce, 0xcf, 0}, {0x20, 0x20, 0}, {0xd2, 0xd3, 0}},
    [_GAME]    = {{0x20, 0x20, 0}, {0x82, 0x83, 0}, {0xa2, 0xa3, 0}, {0xc2, 0xc3, 0}},
    [_GAMEFN1] = {{0x20, 0x20, 0}, {0xb0, 0xb1, 0}, {0xd0, 0xd1, 0}, {0x11, 0x11, 0}},
};

static const char _game_layer_logo[][4] PROGMEM = {
    {0x20, 0x20, 0x20, 0},
    {0x82, 0x83, 0x84, 0},
    {0xa2, 0xa3, 0xa4, 0},
    {0xc2, 0xc3, 0xc4, 0},
};

#endif

// clang-format on

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
#ifdef OLED_ROTATE
    return OLED_ROTATION_270;
#else
    return rotation;
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return oled_init_keymap(rotation);
}

#ifdef OLED_ROTATE
void oled_clear_half_except(uint8_t lines) {
    for (uint8_t j = 0; j < (oled_max_lines() - lines) / 2; j++) {
        oled_write("\n", false);
    }
}

void rhruiz_render_oled(void) {
    layer_state_t layer = biton32(layer_state);

    switch (layer) {
        case _NUM:
            oled_clear_half_except(1);
            oled_write_ln_P(PSTR("\x88\x89\x8a"), false);
            oled_clear_half_except(1);
            break;

        case _FN1:
            oled_clear_half_except(6);
            for (uint8_t i = 0 ; i < 6; i++) {
                oled_write_ln_P(_down_arrow_logo[i % 3], false);
            }
            oled_clear_half_except(6);
            break;

        case _FN2:
            oled_clear_half_except(6);
            for (uint8_t i = 0 ; i < 6; i++) {
                oled_write_ln_P(_up_arrow_logo[i % 3], false);
            }
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
            oled_write("\x1f", false);
            oled_write_P(_game_layer_logo[1], false);
            oled_write("\x1f", false);

            oled_clear_half_except(2);
            break;

        case _GAME:
            oled_clear_half_except(2);

            oled_write_ln_P(_game_layer_logo[0], false);
            oled_write_ln_P(_game_layer_logo[1], false);

            oled_clear_half_except(2);
            break;

        default:
            oled_clear_half_except(0);
            oled_clear_half_except(0);
            break;
    }
}
#else
void rhruiz_render_oled(void) {
    layer_state_t layer = biton32(layer_state);

    switch (layer) {
        case _FN1:
        case _FN2:
            for (uint8_t i = 0; i < 4; i++) {
                oled_write_P(_spacer, false);

                for (uint8_t j = 0; j < 3; j++) {
                    oled_write_P(lc[layer][i], false);
                }

                oled_write("\n", false);
            }

            break;

        case _CFG:
            for (uint8_t i = 0; i < 4; i++) {
                for (uint8_t j = 0; j < 10; j++) {
                    oled_write_P(lc[layer][i], false);
                }

                oled_write("\n", false);
            }
            break;

        case _GAME:
            for (uint8_t i = 0; i < 4; i++) {
                oled_write_P(_spacer, false);
                oled_write_P(_game_layer_logo[i], false);
                oled_write("\n", false);
            }
            break;

        case _GAMEFN1:
            oled_write_P(_spacer, false);
            oled_write_P(lc[layer][3], false);
            oled_write("\n", false);

            for (uint8_t i = 1; i < 4; i++) {
                oled_write_P(_spacer, false);
                oled_write_P(_game_layer_logo[i], false);
                oled_write("\n", false);
            }
            break;


        default:
            for (uint8_t i = 0; i < 4; i++) {
                oled_write_P(_spacer, false);
                oled_write_ln_P(lc[layer][i], false);
            }

            break;
    }
}
#endif

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
    }

    rhruiz_render_oled();
}

void suspend_power_down_user(void) { oled_off(); }

void suspend_wakeup_init_user(void) { oled_on(); }

