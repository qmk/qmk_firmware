#include <stdio.h>
#include "quantum.h"
#include "rhruiz.h"

__attribute__((weak)) void rhruiz_update_layer_colors(layer_state_t state) {}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) { return rhruiz_layer_state_set_user(state); }

__attribute__((weak)) bool rhruiz_process_record(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

__attribute__((weak)) void matrix_init_keymap(void) {}

__attribute__((weak)) bool rhruiz_is_layer_indicator_led(uint8_t index) {
#ifdef RGBLIGHT_ENABLE
    return index == 0 || index == RGBLED_NUM / 2 - 1;
#else
    return false;
#endif
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
#               ifndef NO_ACTION_ONESHOT
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_oneshot_mods();
#               else
                uint8_t temp_osm = 0U;
#               endif

                bool should_flash = ((temp_mod | temp_osm) & MOD_MASK_SHIFT);

#ifndef BOOTLOADER_CATERINA
                if (should_flash) {
                    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
                    char env[26];
                    sprintf(env, " && VID=%04hx PID=%04hx ", VENDOR_ID, PRODUCT_ID);
                    send_string(env);
                    SEND_STRING("~/dev/keyboard/hid_send/hid_send bootloader && ");
                }
#endif

                SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);

                if (should_flash) {
                    SEND_STRING(":flash");
                }

                if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                    SEND_STRING(" -j8 --output-sync");
                }

                SEND_STRING(SS_TAP(X_ENTER));
                set_mods(temp_mod);
            }
            break;
    }
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
            case _VIM_EMACS:
            case _MOUSE:
            case _KEY_OVERRIDE:
                state = state & ~(1UL << _VIM_EMACS) & ~(1UL << _MOUSE) & ~(1UL << _KEY_OVERRIDE);
                break;

            case _FN1:
            case _FN2:
                state = state | (1UL << _VIM_EMACS) | (1UL << _MOUSE) | (1UL << _KEY_OVERRIDE);
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
