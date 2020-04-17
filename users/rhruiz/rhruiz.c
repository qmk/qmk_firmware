#include <stdio.h>
#include "quantum.h"
#include "rhruiz.h"

#define _I(x) __I(x)
#define __I(x) #x

#ifdef OLED_DRIVER_ENABLE
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
#endif

__attribute__((weak)) void rhruiz_update_layer_colors(layer_state_t state) {}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) { return rhruiz_layer_state_set_user(state); }

__attribute__((weak)) bool rhruiz_process_record(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }
#endif

__attribute__((weak)) void matrix_init_keymap(void) {}

__attribute__((weak)) bool rhruiz_is_layer_indicator_led(uint8_t index) {
#ifdef RGBLIGHT_ENABLE
    return index == 0 || index == RGBLED_NUM / 2 - 1;
#else
    return false;
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return oled_init_keymap(rotation);
}

void rhruiz_send_make_args(bool should_flash, bool parallel) {
    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    if (should_flash) {
        SEND_STRING(":flash");
    }
    if (parallel) {
        SEND_STRING(" -j8");
    }
#ifndef OLED_DRIVER_ENABLE
    SEND_STRING(" OLED_DRIVER_ENABLE=no");
#endif
}

void rhruiz_send_make(bool should_flash, bool parallel) {
#ifndef BOOTLOADER_CATERINA
    if (should_flash) {
        rhruiz_send_make_args(false, parallel);
        SEND_STRING(" && VID=" _I(VENDOR_ID) " PID=" _I(PRODUCT_ID));
        SEND_STRING(" ~/dev/keyboard/hid_send/hid_send bootloader && ");
    }
#endif
    rhruiz_send_make_args(should_flash, parallel);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_EPIP:
            if (!record->event.pressed) {
                switch (biton32(layer_state)) {
                    case _FN1:
                        SEND_STRING(" { || }");
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
                        break;

                    default:
                        SEND_STRING("|> ");
                        break;
                }
            }

            break;

        case KC_MAKE:
            if (!record->event.pressed) {
                uint8_t temp_mod = mod_config(get_mods());
                clear_mods();
#ifndef NO_ACTION_ONESHOT
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_oneshot_mods();
#else
                uint8_t temp_osm = 0U;
#endif

                bool should_flash = ((temp_mod | temp_osm) & MOD_MASK_SHIFT);
                bool parallel     = (temp_mod | temp_osm) & MOD_MASK_CTRL;

                rhruiz_send_make(should_flash, parallel);

                SEND_STRING(SS_TAP(X_ENTER));
                set_mods(temp_mod);
            }
            break;
    }

#   ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read32();

#   endif
    return rhruiz_process_record(keycode, record);
}

void matrix_init_user(void) { matrix_init_keymap(); }

void keyboard_post_init_user() {
    /* TODO: revisit this check if flashed promicros with dfu */
#ifdef BOOTLOADER_CATERINA
    setPinOutput(B0);
    writePinHigh(B0);

    setPinOutput(D5);
    writePinHigh(D5);
#endif
    keyboard_post_init_keymap();
}

layer_state_t rhruiz_layer_state_set_user(layer_state_t state) {
    static layer_state_t last_state = 0;

    if (state != last_state) {
        state = update_tri_layer_state(state, _FN1, _FN2, _CFG);

        switch (biton32(state)) {
            case _BL:
            case _KEY_OVERRIDE:
                state = state & ~(1UL << _KEY_OVERRIDE);
                break;

            case _FN1:
            case _FN2:
                state = state | (1UL << _KEY_OVERRIDE);
                break;

            case _GAMEFN1:
                state = update_tri_layer_state(state, _GAMEFN1, _FN2, _CFG);
                break;

            default:
                break;
        }

        rhruiz_update_layer_colors(state);

        last_state = state;
    }

    return state;
}

void rhruiz_rgblight_reset(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_config_t eeprom_config;
    eeprom_config.raw = eeconfig_read_rgblight();

    if (!eeprom_config.enable) {
        rgblight_disable_noeeprom();
    }

    rgblight_mode_noeeprom(eeprom_config.mode);
    rgblight_sethsv_noeeprom(eeprom_config.hue, eeprom_config.sat, eeprom_config.val);
#endif
}

void rhruiz_change_leds_to(uint16_t hue, uint8_t sat) {
#ifdef RGBLIGHT_ENABLE
    rgblight_config_t eeprom_config;
    eeprom_config.raw = eeconfig_read_rgblight();
    LED_TYPE *ledp;

#    ifdef RGBLIGHT_LED_MAP
    LED_TYPE led0[RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        led0[i] = led[pgm_read_byte(&led_map[i])];
    }
    ledp = led0;
#    else
    ledp = led;
#    endif

    bool rgbmode = rgblight_get_mode();

    for (uint8_t i = RGBLED_NUM; i-- > 0;) {
        if (rhruiz_is_layer_indicator_led(i)) {
            sethsv(hue, sat, eeprom_config.val, (LED_TYPE *)&ledp[i]);
        } else {
            if (rgbmode == false) {
                sethsv(0, 0, 0, (LED_TYPE *)&ledp[i]);
            }
        }
    }

#    ifdef RGBW
    ws2812_setleds_rgbw(ledp, RGBLED_NUM);
#    else
    ws2812_setleds(ledp, RGBLED_NUM);
#    endif
#endif
}

#ifdef OLED_DRIVER_ENABLE
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

#endif
