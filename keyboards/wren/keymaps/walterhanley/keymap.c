/* Copyright 2021 Walter Hanley
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Cmd-tab tablesetting
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

// Alt-tab tablesetting
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Defines keycode alias
#define ECTL LCTL_T(KC_ESC)
#define EGUI LGUI_T(KC_ESC)
#define DELSYM LT(_SYMBOL, KC_DEL)
#define SCLNAV LT(_NAV, KC_SCLN)
#define TGNLCK TG(_NLCK)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MAC,
    _WIN,
    _NLCK,
    _SYMBOL,
    _NAV
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    NSEAL = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Mac */
    [_MAC] = LAYOUT(
     KC_PSLS, KC_7,    KC_8,    KC_9,    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  KC_INS,  KC_HOME, KC_PGUP, KC_NO,
     KC_PAST, KC_4,    KC_5,    KC_6,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_NO,
     KC_PMNS, KC_1,    KC_2,    KC_3,    ECTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    SCLNAV,  KC_QUOT, KC_NO,   KC_UP,   KC_NO,   KC_NO,
     KC_PPLS, KC_0,    KC_DOT,  KC_ENT,  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                                                           TGNLCK,  KC_LALT, KC_LGUI, KC_BSPC, KC_ENT,  KC_SPC,  DELSYM,  KC_RGUI, KC_RALT, KC_MUTE
    ),

    /* Windows */
    [_WIN] = LAYOUT(
     KC_PSLS, KC_7,    KC_8,    KC_9,    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  KC_INS,  KC_HOME, KC_PGUP, KC_NO,
     KC_PAST, KC_4,    KC_5,    KC_6,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_NO,
     KC_PMNS, KC_1,    KC_2,    KC_3,    EGUI,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    SCLNAV,  KC_QUOT, KC_NO,   KC_UP,   KC_NO,   KC_NO,
     KC_PPLS, KC_0,    KC_DOT,  KC_ENT,  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                                                           TGNLCK,  KC_LALT, KC_LCTL, KC_BSPC, KC_ENT,  KC_SPC,  DELSYM,  KC_RCTL, KC_RALT, KC_MUTE
    ),

    /* In-Keyboard Numlock */
    [_NLCK] = LAYOUT(
     KC_PSLS, KC_HOME, KC_UP,   KC_PGUP, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     KC_PAST, KC_LEFT, KC_5,    KC_RGHT, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     KC_PMNS, KC_END,  KC_DOWN, KC_PGDN, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     KC_PPLS, KC_INS,  KC_DOT,  KC_ENT,  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                           TGNLCK,  _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Symbols, F-Keys, and Text Macros */
    [_SYMBOL] = LAYOUT(
     NSEAL,   _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, KC_UNDS, KC_LCBR, KC_LBRC, _______,                   _______, KC_RBRC, KC_RCBR, KC_MINS, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Nav Cluster and Settings*/
    [_NAV] = LAYOUT(
     DF(_MAC), _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     DF(_WIN), _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______,  _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        // Encoder functionality for _MAC layer
        if (IS_LAYER_ON(_MAC))
        {
            if (clockwise) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                tap_code16(KC_TAB);
            } else {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
        }
        // Encoder functionality for _WIN layer
        else if (IS_LAYER_ON(_WIN)) {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NSEAL:
            if (record->event.pressed) {
                // when keycode NSEAL is pressed
                SEND_STRING("What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little 'clever' comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.");
            } else {
                // when keycode NSEAL is released
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_cmd_tab_active = false;
        }
    }
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
