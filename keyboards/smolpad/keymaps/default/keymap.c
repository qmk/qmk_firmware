// Copyright 2025 Wolf Yuan <me at wolf-yuan.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "bitmaps.c"

#define LED_START 0
#define LED_END   11
#define TRANSITION_MS 500
#define OLED_FRAME_RATE_MS 33  // ~30 FPS

enum custom_keycode {
    MODE_SW = SAFE_RANGE,
    WORKSPACE_RIGHT,
    WORKSPACE_LEFT,
    SHORTCUT_COPY,
    SHORTCUT_SELECT,
    SHORTCUT_PASTE
};
enum encoder_mode {
    MODE_GAME,
    MODE_CHAT,
    MODE_MEDIA,
    MODE_AUX,
    MODE_MAX
};
enum action_mode {
    VOL_UP,
    VOL_DOWN,
    PREV,
    NEXT,
    PLAYPAUSE,
    NEXT_SPACE,
    PREV_SPACE,
    COPIED,
    SELECTED,
    PASTED,
    NONE
};
enum menu_state {
    MENU_NONE,
    MENU_ACTIVE
};
enum setting_option {
    SETTING_STEELSERIES,
    SETTING_NATIVE,
    SETTING_MAX
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    ┌────────────┬─────┬─────┐
    │ EC11 (SW9) │ SW8 │ SW7 │
    ├────────────┼─────┼─────┤
    │    SW6     │ SW5 │ SW4 │
    ├────────────┼─────┼─────┤
    │    SW3     │ SW2 │ SW1 │
    └────────────┴─────┴─────┘
     */
    [0] = LAYOUT(
        MODE_SW, WORKSPACE_LEFT, WORKSPACE_RIGHT,
        SHORTCUT_SELECT, SHORTCUT_COPY, SHORTCUT_PASTE,
        KC_MPRV, KC_MPLY, KC_MNXT
    )
};

static enum encoder_mode current_mode = MODE_GAME;
static enum action_mode current_action = NONE;
static enum menu_state current_menu = MENU_NONE;
static enum setting_option current_setting = SETTING_STEELSERIES; // Default
static enum setting_option selected_option = SETTING_STEELSERIES;
static uint16_t action_timer = 0;
static uint16_t kc1_timer = 0;
static uint16_t oled_timer = 0;
static bool oled_needs_update = true;
static bool first_boot = true;

const uint16_t mode_up[]   = {KC_F13, KC_F20, KC_F15, KC_F17};
const uint16_t mode_down[] = {KC_F14, KC_F19, KC_F16, KC_F18};

static uint8_t led_current_r[LED_END - LED_START + 1] = {0};
static uint8_t led_current_g[LED_END - LED_START + 1] = {0};
static uint8_t led_current_b[LED_END - LED_START + 1] = {0};
static uint8_t led_target_r[LED_END - LED_START + 1] = {0};
static uint8_t led_target_g[LED_END - LED_START + 1] = {0};
static uint8_t led_target_b[LED_END - LED_START + 1] = {0};
static uint16_t led_timer = 0;
static bool transitioning = false;

void set_mode_rgb_target(void) {
    uint8_t r, g, b;

    if (current_setting == SETTING_NATIVE) {
        // Lime green for native mode
        r = 50;  g = 205; b = 50;
    } else {
        switch (current_mode) {
            case MODE_GAME:  r = 0  * 0.5; g = 128 * 0.5; b = 255 * 0.5; break;  // Bright blue → dimmed
            case MODE_CHAT:  r = 255 * 0.5; g = 255 * 0.5; b = 0   * 0.5; break;  // Yellow → dimmed
            case MODE_MEDIA: r = 0  * 0.5; g = 255 * 0.5; b = 128 * 0.5; break;  // Mint green → dimmed
            case MODE_AUX:   r = 255 * 0.5; g = 0   * 0.5; b = 128 * 0.5; break;  // Magenta → dimmed
            default: r=0; g=0; b=0; break;
        }
    }

    bool same_color = true;
    for (uint8_t i = 0; i <= LED_END - LED_START; i++) {
        if (led_current_r[i] != r || led_current_g[i] != g || led_current_b[i] != b) {
            same_color = false;
            break;
        }
    }

    if (same_color) return;

    for (uint8_t i = 0; i <= LED_END - LED_START; i++) {
        led_target_r[i] = r;
        led_target_g[i] = g;
        led_target_b[i] = b;
    }

    led_timer = timer_read();
    transitioning = true;
}

void update_led_transition(void) {
    if (!transitioning) return;

    uint16_t elapsed = timer_elapsed(led_timer);
    if (elapsed >= TRANSITION_MS) {
        // End transition
        for (uint8_t i = 0; i <= LED_END - LED_START; i++) {
            rgblight_setrgb_at(led_target_r[i], led_target_g[i], led_target_b[i], i + LED_START);

            led_current_r[i] = led_target_r[i];
            led_current_g[i] = led_target_g[i];
            led_current_b[i] = led_target_b[i];
        }
        transitioning = false;
    } else {
        for (uint8_t i = 0; i <= LED_END - LED_START; i++) {
            uint8_t r = led_current_r[i] + ((led_target_r[i] - led_current_r[i]) * elapsed / TRANSITION_MS);
            uint8_t g = led_current_g[i] + ((led_target_g[i] - led_current_g[i]) * elapsed / TRANSITION_MS);
            uint8_t b = led_current_b[i] + ((led_target_b[i] - led_current_b[i]) * elapsed / TRANSITION_MS);

            rgblight_setrgb_at(r, g, b, i + LED_START);
        }
    }
}

void enter_settings_menu(void) {
    current_menu = MENU_ACTIVE;
    selected_option = current_setting;
    oled_clear();
    oled_needs_update = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MODE_SW:
            if (record->event.pressed) {
                kc1_timer = timer_read();
            } else {
                uint16_t held = timer_elapsed(kc1_timer);
                if (held > 3000) {
                    // Very long press (>3s) - Enter bootloader
                    oled_clear();
                    oled_set_cursor(0,0);
                    reset_keyboard();
                } else if (held >= 800) {
                    // Medium press (800ms-3s) - Enter/exit menu
                    if (current_menu == MENU_ACTIVE) {
                        // Save setting and exit menu
                        current_setting = selected_option;
                        current_menu = MENU_NONE;
                        set_mode_rgb_target(); // Update LEDs based on new setting
                    } else {
                        // Enter menu
                        enter_settings_menu();
                    }
                } else {
                    // Short press (<800ms)
                    if (current_menu == MENU_ACTIVE) {
                        // In menu mode, short press confirms selection and exits
                        current_setting = selected_option;
                        current_menu = MENU_NONE;
                        set_mode_rgb_target(); // Update LEDs based on new setting
                    } else if (current_setting == SETTING_NATIVE) {
                        // In native mode, short press enters settings
                        enter_settings_menu();
                    } else {
                        // In SteelSeries mode, short press cycles through encoder modes
                        current_mode = (current_mode + 1) % MODE_MAX;
                        set_mode_rgb_target();
                    }
                    oled_needs_update = true;
                }
            }
            return false;

        case WORKSPACE_RIGHT:
            if (record->event.pressed) {
                current_action = NEXT_SPACE;
                action_timer = timer_read();
                oled_needs_update = true;

                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_RIGHT);

                wait_ms(10);

                unregister_code(KC_RIGHT);
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;

        case WORKSPACE_LEFT:
            if (record->event.pressed) {
                current_action = PREV_SPACE;
                action_timer = timer_read();
                oled_needs_update = true;

                register_code(KC_LCTL);
                register_code(KC_LGUI);
                register_code(KC_LEFT);

                wait_ms(10);

                unregister_code(KC_LEFT);
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;

        case SHORTCUT_COPY:
            if (record->event.pressed) {
                current_action = COPIED;
                action_timer = timer_read();
                oled_needs_update = true;

                register_code(KC_LCTL);
                register_code(KC_C);

                wait_ms(10);

                unregister_code(KC_C);
                unregister_code(KC_LCTL);
            }
            return false;

        case SHORTCUT_SELECT:
            if (record->event.pressed) {
                current_action = SELECTED;
                action_timer = timer_read();
                oled_needs_update = true;

                register_code(KC_LCTL);
                register_code(KC_A);

                wait_ms(10);

                unregister_code(KC_A);
                unregister_code(KC_LCTL);
            }
            return false;

        case SHORTCUT_PASTE:
            if (record->event.pressed) {
                current_action = PASTED;
                action_timer = timer_read();
                oled_needs_update = true;

                register_code(KC_LCTL);
                register_code(KC_V);

                wait_ms(10);

                unregister_code(KC_V);
                unregister_code(KC_LCTL);
            }
            return false;

        case KC_MPLY:
            if (record->event.pressed) {
                current_action = PLAYPAUSE;
                action_timer = timer_read();
                oled_needs_update = true;
            }
            break;
        case KC_MPRV:
            if (record->event.pressed) {
                current_action = PREV;
                action_timer = timer_read();
                oled_needs_update = true;
            }
            break;
        case KC_MNXT:
            if (record->event.pressed) {
                current_action = NEXT;
                action_timer = timer_read();
                oled_needs_update = true;
            }
            break;

        default:
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    update_led_transition();

    if (current_action != NONE && timer_elapsed(action_timer) >= 1500) {
        current_action = NONE;
        oled_needs_update = true;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (current_menu == MENU_ACTIVE) {
        if (!clockwise) {
            selected_option = (selected_option + 1) % SETTING_MAX;
        } else {
            selected_option = (selected_option > 0) ? (selected_option - 1) : (SETTING_MAX - 1);
        }
        oled_needs_update = true;
        return false;
    }

    if (current_setting == SETTING_STEELSERIES) {
        if (!clockwise) {
            tap_code(mode_up[current_mode]);
            current_action = VOL_UP;
        } else {
            tap_code(mode_down[current_mode]);
            current_action = VOL_DOWN;
        }
    } else {
        if (!clockwise) {
            tap_code(KC_VOLU);
            current_action = VOL_UP;
        } else {
            tap_code(KC_VOLD);
            current_action = VOL_DOWN;
        }
    }

    action_timer = timer_read();
    oled_needs_update = true;
    return false;
}

void display_menu(void) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Volume adjust method:"), false);

    oled_set_cursor(0, 1);
    if (selected_option == SETTING_STEELSERIES) {
        oled_write_P(PSTR("> SteelSeries GG"), true);
    } else {
        oled_write_P(PSTR("  SteelSeries GG"), false);
    }

    oled_set_cursor(0, 2);
    if (selected_option == SETTING_NATIVE) {
        oled_write_P(PSTR("> Native"), true);
    } else {
        oled_write_P(PSTR("  Native"), false);
    }

    oled_set_cursor(0, 3);
    oled_write_P(PSTR("(Press 3s to flash)"), false);
}

void display_normal_mode(void) {
    if (current_action != NONE) {
        oled_set_cursor(0, 0);
        switch (current_action) {
            case VOL_UP:  oled_write_raw_P((const char *)vol_up, 512); break;
            case VOL_DOWN:  oled_write_raw_P((const char *)vol_down, 512); break;
            case PLAYPAUSE: oled_write_raw_P((const char *)playpause_logo, 512); break;
            case NEXT: oled_write_raw_P((const char *)next_logo, 512); break;
            case PREV: oled_write_raw_P((const char *)prev_logo, 512); break;
            case NEXT_SPACE: oled_write_raw_P((const char *)next_space_logo, 512); break;
            case PREV_SPACE: oled_write_raw_P((const char *)prev_space_logo, 512); break;
            case COPIED: oled_write_raw_P((const char *)copied_logo, 512); break;
            case SELECTED: oled_write_raw_P((const char *)selected_logo, 512); break;
            case PASTED: oled_write_raw_P((const char *)pasted_logo, 512); break;
            case NONE: break;
        }
    } else {
        oled_set_cursor(0, 0);
        if (current_setting == SETTING_NATIVE) {
            oled_write_raw_P((const char *)smolpad_logo, 512);
        } else {
            switch (current_mode) {
                case MODE_GAME:  oled_write_raw_P((const char *)game_text, 512); break;
                case MODE_CHAT:  oled_write_raw_P((const char *)chat_text, 512); break;
                case MODE_MEDIA: oled_write_raw_P((const char *)media_text, 512); break;
                case MODE_AUX:   oled_write_raw_P((const char *)aux_text, 512); break;
                default: break;
            }
        }
    }
}

bool oled_task_user(void) {
    if (first_boot) {
        first_boot = false;
        oled_needs_update = true;
    }

    if (timer_elapsed(oled_timer) < OLED_FRAME_RATE_MS && !oled_needs_update) {
        return false;
    }
    oled_timer = timer_read();

    if (oled_needs_update) {
        if (current_menu == MENU_ACTIVE) {
            display_menu();
        } else {
            display_normal_mode();
        }
        oled_needs_update = false;
    }

    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_timer = timer_read();
    return OLED_ROTATION_180;
}

void suspend_wakeup_init_user(void) {
    set_mode_rgb_target();
    oled_needs_update = true;
}

void keyboard_post_init_user(void) {
    for (uint8_t i = 0; i < 12; i++) {
        rgblight_setrgb_at(0, 0, 0, i);
        if (i >= LED_START && i <= LED_END) {
            uint8_t idx = i - LED_START;
            led_current_r[idx] = 0;
            led_current_g[idx] = 0;
            led_current_b[idx] = 0;
        }
    }
    set_mode_rgb_target();
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    oled_set_cursor(0, 0);
    if (bootloader) {
        oled_write_P(PSTR("Awaiting New Firmware"), true);
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("Copy new firmware"), false);
        oled_set_cursor(0, 3);
        oled_write_P(PSTR("to RPI-RP2 drive"), false);
    } else {
        oled_write_P(PSTR("Rebooting "), false);
    }

    oled_render_dirty(true);

    for (uint8_t i = LED_START; i <= LED_END; i++) {
        rgblight_setrgb_at(100, 10, 10, i);
    }
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
