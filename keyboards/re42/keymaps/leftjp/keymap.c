/* Copyright 2020 kushima8
 * Copyright 2020 utubo
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
#include "keymap_jp.h"

enum layer_number {
    _FIRST = 0,
    _SECOND,
    _TENKEY,
    _CONFIG,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    RT_ENT = SAFE_RANGE, // Hold=>RAISE, Tap=>Enter
    LT_MHEN, // Hold=>LOWER, Dance=>RAISE, Tap=>Mukenkan
    LT_HENK  // Hold=>LOWER, Dance=>RAISE, Tap=>Henkan
};

#define FIRST  TO(_FIRST)
#define SECOND TO(_SECOND)
#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define TENKEY TO(_TENKEY)
#define CONFIG TO(_CONFIG)

#define GT_ESC  LGUI_T(KC_ESC)  // Hold=>GUI,   Tap=>ESC
#define GT_ZKHK LGUI_T(JP_ZKHK) // Hold=>GUI,   Tap=>JP_ZKHK
#define AT_CAPS LALT_T(KC_CAPS) // Hold=>ALT,   Tap=>Caps
#define AT_TAB  LALT_T(KC_TAB)  // Hold=>ALT,   Tap=>TAB
#define ST_MINS LSFT_T(JP_MINS) // Hold=>Shift, Tap=>-

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FIRST] = LAYOUT(
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        GT_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                             KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSPC,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        AT_TAB ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                             KC_H   ,KC_J   ,KC_K   ,KC_L   ,JP_SCLN,JP_QUOT,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                             KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,ST_MINS,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        KC_LCTL,                        LT_MHEN,KC_SPC ,CONFIG ,     SECOND ,RT_ENT ,LT_HENK                                ,KC_RCTL
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_SECOND] = LAYOUT( // TODO: Oekaki for Lefty
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        _______,_______,_______,_______,_______,_______,                             KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,_______,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,_______,_______,_______,_______,                             KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,RALT_T(KC_ESC),
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,_______,_______,_______,_______,                             KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,_______,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        _______,_______,_______,     _______,KC_LCTL,KC_LALT                                ,RCTL_T(KC_ENT)
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_TENKEY] = LAYOUT(
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        GT_ESC ,XXXXXXX,KC_UP  ,XXXXXXX,XXXXXXX,XXXXXXX,                             KC_7   ,KC_8   ,KC_9   ,KC_MINS,KC_SLSH,KC_BSPC,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        AT_TAB ,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,                             KC_4   ,KC_5   ,KC_6   ,KC_PPLS,KC_PAST,KC_TAB ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                             KC_1   ,KC_2   ,KC_3   ,KC_DOT ,KC_COMM,KC_ENT ,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        LOWER  ,KC_SPC ,XXXXXXX,     FIRST  ,KC_0   ,XXXXXXX                                ,_______
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_CONFIG] = LAYOUT(
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        FIRST  ,_______,_______,_______,_______,_______,                             _______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,                             _______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,                             _______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        _______,_______,FIRST  ,     _______,_______,_______                                ,_______
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_LOWER] = LAYOUT( // ESC and RALT are for lefty. KC_SLASH is for input a date.
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        GT_ZKHK,JP_1   ,JP_2   ,JP_3   ,JP_4   ,JP_5   ,                             JP_6   ,JP_7   ,JP_8   ,JP_9   ,JP_0   ,KC_ESC ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        KC_TAB ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5 ,                             KC_LEFT ,KC_DOWN,KC_UP  ,KC_RGHT,KC_DEL ,RALT_T(KC_INS),
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,_______,_______,_______,_______,                             KC_PSCR,KC_APP ,KC_HOME,KC_END ,KC_SLSH,_______,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        _______,RAISE  ,_______,     _______,_______,_______                                ,_______
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_RAISE] = LAYOUT(
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        KC_LGUI,JP_EXLM,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,                             JP_CIRC,JP_AMPR,JP_ASTR,JP_LPRN,JP_RPRN,JP_GRV ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,_______,_______,_______,_______,                             JP_EQL ,JP_LCBR,JP_RCBR,JP_LBRC,JP_RBRC,JP_YEN ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,_______,_______,_______,_______,_______,                             JP_PLUS,JP_UNDS,JP_LABK,JP_RABK,JP_QUES,_______,
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        _______,_______,_______,     _______,_______,_______                                ,_______
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
    [_ADJUST] = LAYOUT(
    // ,-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------.
        _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,                             KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,KC_VOLU,KC_VOLD,KC_MUTE,RGB_TOG,_______,                             KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,KC_F12 ,
    // |-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
        _______,KC_BTN1,KC_BTN2,_______,_______,FIRST  ,                             TENKEY ,SECOND ,_______,_______,_______,LSFT_T(KC_PWR),
    // |-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------|
        _______,                        _______,_______,KC_MUTE,     _______,_______,_______                                ,_______
    // `-------+-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------+-------+-------'
    ),
};

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

static char tap_count[] = "00000";
static uint16_t last_time = 0;
static uint16_t last_pressed;
static bool is_alt_pressed;
static bool is_lower_pressed;

bool tap_when_shift(uint16_t keycode) {
    uint8_t shift = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    if (shift) {
        unregister_mods(shift);
        tap_code16(keycode);
        register_mods(shift);
        return false;
    } else {
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool dance = false;
    if (record->event.pressed) {
        // Check tap dance
        if (last_pressed == keycode && record->event.time - last_time < TAPPING_TERM) {
            dance = true;
        }
        last_pressed = keycode;
        last_time = record->event.time;
        // Count up taps.
        for (int i = 4; i >= 0; i --) {
            if (tap_count[i] >= '9') {
                tap_count[i] = '0';
            } else {
                tap_count[i] = tap_count[i] + 1;
                break;
            }
        }
        // Replace Shift-Symbols like ANSI for JIS.
        switch (keycode) {
            case JP_2:    return tap_when_shift(JP_AT);
            case JP_6:    return tap_when_shift(JP_CIRC);
            case JP_7:    return tap_when_shift(JP_AMPR);
            case JP_8:    return tap_when_shift(JP_ASTR);
            case JP_9:    return tap_when_shift(JP_LPRN);
            case JP_0:    return tap_when_shift(JP_RPRN);
            case JP_GRV:  return tap_when_shift(JP_TILD);
            case JP_EQL:  return tap_when_shift(JP_PLUS);
            case JP_MINS: return tap_when_shift(JP_UNDS);
            case JP_QUOT: return tap_when_shift(JP_DQUO);
            case JP_SCLN: return tap_when_shift(JP_COLN);
        }
    }

    // tap-hold params
    uint16_t tapped_key = 0;
    enum layer_number hold_layer = 0;

    switch (keycode) {
        case KC_TAB:
            // LOWER-Tab => Alt-Tab
            if (record->event.pressed && is_lower_pressed && !is_alt_pressed) {
                register_code(KC_LALT);
                is_alt_pressed = true;
            }
            return true;
        case LOWER:
        case LT_MHEN:
        case LT_HENK:
            // dance LOWER
            if (dance) {
                layer_on(_RAISE);
                return false;
            }
            is_lower_pressed = record->event.pressed;
            if (is_lower_pressed) {
                layer_on(_LOWER);
                return false;
            }
            layer_off(_LOWER);
            layer_off(_RAISE);
            // Close the task switcher opened with Alt-Tab.
            if (is_alt_pressed) {
                unregister_code(KC_LALT);
                is_alt_pressed = false;
            }
            if (last_pressed != keycode) {
                return false;
            }
            // tap LOWER
            switch(keycode) {
                case LT_MHEN: tap_code(JP_MHEN); break;
                case LT_HENK: tap_code(JP_HENK); break;
            }
            return false;
        case RT_ENT:
            tapped_key = KC_ENT;
            hold_layer = _RAISE;
            break;
        default:
            return true;
    }

    // Tap-hold
    if (tapped_key) {
        if (record->event.pressed) {
            if (dance) {
                register_code(tapped_key);
                last_pressed = 0; // skip tap_code when unpressed
            } else {
                layer_on(hold_layer);
            }
        } else {
            layer_off(hold_layer);
            unregister_code(tapped_key);
            if (last_pressed == keycode) {
                tap_code(tapped_key);
            }
        }
        return false;
    }

    return true;
}

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {

    // Print current layer
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _FIRST:
            oled_write_ln_P(PSTR("1st"), false);
            break;
        case _SECOND:
            oled_write_ln_P(PSTR("2nd"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Low"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Rai"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adj"), false);
            break;
        case _TENKEY:
            oled_write_P(PSTR("10Key"), false);
            break;
        case _CONFIG:
            oled_write_ln_P(PSTR("Conf"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }

    // Print lock
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("NUM"), led_usb_state.num_lock);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("CAPS"), led_usb_state.caps_lock);
    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("SCROL"), led_usb_state.scroll_lock);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("KANA"), led_usb_state.kana);

    // Print tap count
    oled_write_ln_P(PSTR(""), false);
    oled_write(tap_count, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

#ifdef ENCODER_ENABLE

/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
    last_pressed = 0; // reset tap flag.
    if (index == 0) {
        // Left rotary
        switch (get_highest_layer(layer_state)) {
            case _FIRST:
                tap_code(clockwise ? KC_WH_D : KC_WH_U);
                break;
            case _LOWER:
                if (!is_alt_pressed) {
                    register_code(KC_LALT); // unregister in process_record_user().
                    is_alt_pressed = true;
                }
                tap_code16(clockwise ? KC_TAB : S(KC_TAB));
                break;
            case _ADJUST:
                tap_code(clockwise ? KC_VOLU : KC_VOLD);
                break;
            default:
                break;
        }
    } else if (index == 1) {
        // Right rotary
        switch (get_highest_layer(layer_state)) {
            case _FIRST:
                tap_code(clockwise ? KC_WH_U : KC_WH_D);
                break;
            case _SECOND: // TODO: Oekaki for Lefty
                tap_code(clockwise ? KC_DEL: KC_END);
                break;
            case _LOWER:
                tap_code(clockwise ? KC_PGUP : KC_PGDN);
                break;
            case _RAISE:
                tap_code16(clockwise ? A(KC_PGUP) : A(KC_PGDN));
                break;
            default:
                break;
        }
    }
}

#endif
