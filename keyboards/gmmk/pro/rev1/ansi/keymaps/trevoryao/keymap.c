/* Copyright 2022 Trevor J. Yao @trevoryao

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "encoder.h"
#include "rgb_matrix_map.h"

#include QMK_KEYBOARD_H

enum layer_names {
    _MAC,    // Mac Keys Layout: The main keyboard layout for macOS
    _FUNC1,  // Function Layout: FN Keys and git commands
    _WIN     // Windows Keys Layout: The main keyboard layout for Windows
};

enum keycodes {
    ENC = SAFE_RANGE,
    LINE_UP,
    LINE_DOWN,
    G_PUSH,
    G_ADD,
    G_C,
    G_MERGE,
    G_BRANCH,
    G_FETCH,
    G_REBASE
};

// custom mod masks
#define MOD_MASK_CMD (MOD_BIT(KC_LCMD) | MOD_BIT(KC_RCMD))
#define MOD_MASK_OPT (MOD_BIT(KC_LOPT) | MOD_BIT(KC_ROPT))
#define MOD_MASK_CMD_S (MOD_MASK_CMD | MOD_MASK_SHIFT)

#define SCRSHT (LCMD(LSFT(KC_5)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        KC_ESC,  KC_F14,  KC_F15, RCTL(KC_UP), SCMD(KC_5), RCTL(KC_LEFT), RCTL(KC_RIGHT), KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,    SCRSHT,              ENC,
        KC_GRV,  KC_1,    KC_2,   KC_3,        KC_4,       KC_5,          KC_6,           KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC,             KC_DEL,
        KC_TAB,  KC_Q,    KC_W,   KC_E,        KC_R,       KC_T,          KC_Y,           KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_BSLS,             KC_POWER,
        KC_CAPS, KC_A,    KC_S,   KC_D,        KC_F,       KC_G,          KC_H,           KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,              LINE_UP,
        KC_LSFT,          KC_Z,   KC_X,        KC_C,       KC_V,          KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT, KC_UP,      LINE_DOWN,
        KC_LCTL, KC_LOPT, KC_LCMD,                                        KC_SPC,                                    KC_RCMD, KC_ROPT, MO(_FUNC1), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * git commands:
     * push (P)
     * add (A)
     * add all (cmd + A)
     * commit (cmd + C)
     * force push (cmd + P)
     * merge (M)
     * set-upstream (opt + P)
     * pr create (cmd + shift + P)
     * pull (shift + P)
     * fetch (F)
     * checkout -b (B)
     * checkout (C)
     * rebase -i (R)
    */
    [_FUNC1] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,              _______,
        _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______,              _______,
        _______, _______, _______, _______, G_REBASE, _______, _______,  _______, _______, _______, G_PUSH,  _______, _______, _______,              QK_BOOT,
        _______, G_ADD,   _______, _______, G_FETCH,  _______, _______,  _______, _______, _______, _______, _______,          _______,              _______,
        _______,          _______, _______, G_C,      _______, G_BRANCH, NK_TOGG, G_MERGE, _______, _______, _______,          _______, _______,     _______,
        _______, _______, _______,                             _______,                            _______, _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ENC:
            if (record->event.pressed) {
                if ((get_mods() & MOD_MASK_CMD) == MOD_MASK_CMD) {
                    // rgb on/off
                    rgb_matrix_toggle_noeeprom();
                } else if ((get_mods() & MOD_MASK_OPT) == MOD_MASK_OPT) {
                    // breathing on/off
                    switch (rgb_matrix_get_mode()) {
                        case RGB_MATRIX_SOLID_COLOR:
                            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
                            break;
                        case RGB_MATRIX_BREATHING:
                            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                            break;
                        default: break;
                    }
                } else {
                    register_code(KC_ENTER);
                }

                return false;
            }
            break;
        case LINE_UP:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_OPT) register_code16(LCMD(LSFT(KC_K)));
                else register_code16(LSFT(KC_UP));
                return false;
            }
            break;
        case LINE_DOWN:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_OPT) register_code16(LCMD(KC_L));
                else register_code16(LSFT(KC_DOWN));
                return false;
            }
            break;
        case G_PUSH:
            if (record->event.pressed) {
                char *cmd = NULL;

                if ((get_mods() & MOD_MASK_CMD_S) == MOD_MASK_CMD_S)
                    cmd = "gh pr create\n";
                else if ((get_mods() & MOD_MASK_CMD) == MOD_MASK_CMD)
                    cmd = "git push --force ";
                else if ((get_mods() & MOD_MASK_OPT) == MOD_MASK_OPT)
                    cmd = "git push --set-upstream origin $(git rev-parse --symbolic-full-name --abbrev-ref HEAD)\n";
                else if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT)
                    cmd = "git pull\n";
                else
                    cmd = "git push\n";

                SEND_STRING(cmd);
                return false;
            }
            break;
        case G_ADD:
            if (record->event.pressed) {
                char *cmd = NULL;

                if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT)
                    cmd = "git add --all";
                else
                    cmd = "git add --patch";

                SEND_STRING(cmd);
                return false;
            }
            break;
        case G_C:
            if (record->event.pressed) {
                char *cmd = NULL;

                if ((get_mods() & MOD_MASK_CMD) == MOD_MASK_CMD)
                    cmd = "git commit -m \"";
                else
                    cmd = "git checkout ";

                SEND_STRING(cmd);
                return false;
            }
            break;
        case G_MERGE:
            if (record->event.pressed) {
                SEND_STRING("git merge origin/");
                return false;
            }
            break;
        case G_FETCH:
            if (record->event.pressed) {
                SEND_STRING("git fetch origin\n");
                return false;
            }
            break;
        case G_BRANCH:
            if (record->event.pressed) {
                SEND_STRING("git checkout -b ");
                return false;
            }
            break;
        case G_REBASE:
            if (record->event.pressed) {
                SEND_STRING("git rebase -i\n");
                return false;
            }
            break;
    }

    return true;
}

/*
 * default -> up/down (cmd line)
 * cmd -> rgb light brightness
 * shift -> rgb layer
 * opt -> rgb breathing speed
*/
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MOD_MASK_CMD)
        encoder_action_rgb_brightness(clockwise);
    else if (get_mods() & MOD_MASK_SHIFT)
        encoder_action_rgb_layer(clockwise);
    else if (get_mods() & MOD_MASK_OPT)
        encoder_action_rgb_speed(clockwise);
    else
        encoder_action_cmd_scroll(clockwise);

    return false;
}
#endif // ENCODER_ENABLE

void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {
        indicator_set(LED_CAPS);
        indicator_set(LED_L2);
    }

    // highlight FUNC layer keys, different colours for different kinds
    // github: P, A, C, M, F, B, R
    // sys: N, POWER

    #define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

    switch (get_highest_layer(layer_state)) {
        case _FUNC1: {
            const uint8_t LED_GITHUB[] = {
                LED_P,
                LED_A,
                LED_C,
                LED_M,
                LED_F,
                LED_B,
                LED_R
            };
            const uint8_t LED_SYS[] = {LED_N, LED_POWER};

            for (uint16_t i = 0; i < ARR_LEN(LED_MAIN); ++i)
                rgb_matrix_set_color(LED_MAIN[i], RGB_WHITE);
            for (uint16_t i = 0; i < ARR_LEN(LED_GITHUB); ++i)
                rgb_matrix_set_color(LED_GITHUB[i], RGB_GREEN);
            for (uint16_t i = 0; i < ARR_LEN(LED_SYS); ++i)
                rgb_matrix_set_color(LED_GITHUB[i], RGB_RED);

            break;
        }
        default: break;
    }
}

void keyboard_post_init_user(void) {
    init_colour_layer();
}
