// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// QWERTY Home Row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// COLEMAK Home Row mods
#define ALT_R LALT_T(KC_R)
#define SFT_S LSFT_T(KC_S)
// rename necessary, since CTL_H is already defined
#define CTL_TH LCTL_T(KC_T)

// Right-hand home row mods
#define CTL_N RCTL_T(KC_N)
#define SFT_E RSFT_T(KC_E)
#define ALT_I RALT_T(KC_I)
#define GUI_O RGUI_T(KC_O)

#define SFT_ENT LSFT_T(KC_ENT)

// LAYER SWITCHING
#define NUM_ALT LT(_NUM, KC_LALT)
#define FN_ALT LT(_FN, KC_RALT)

enum sofle_layers {
    _QWERTY,
    _COLEMAK,
    _SYM,
    _NAV,
    _FN,
    _NUM,
    _ADJUST,
};

enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                     |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                     |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * | LCTL |   A  |   S  |   D  |   F  |   G  |--------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |--------|    |-------|   N  |   M  |   ,  |   .  |   /  | ESC  |
 * `-----------------------------------------/        /     \      \-----------------------------------------'
 *     | LGUI | LAlt | (NUM, LAlt) |SYM   | /SFT(ENT)/       \Space \  |NAV   |(FN, RAlt)| RClt | RGUI |
 *     |      |      |             |      |/       /         \      \ |      |          |      |      |
 *     `------------------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
 XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          /**/             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          /**/             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
 KC_LCTL,   GUI_A,   ALT_S,   SFT_D,   CTL_F,    KC_G,          /**/             KC_H,   CTL_J,   SFT_K,   ALT_L,GUI_SCLN, KC_QUOT,
 KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, XXXXXXX, /**/ XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
		           KC_LGUI, KC_LCTL, NUM_ALT,MO(_SYM), SFT_ENT, /**/  KC_SPC,MO(_NAV),  FN_ALT,  KC_RCTL,KC_RGUI
),

/*
 * COLEMAK
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                     |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                     |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * | LCTL |   A  |   R  |   S  |   T  |   D  |--------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |--------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/        /     \      \-----------------------------------------'
 *     | LGUI | LAlt | (NUM, LAlt) |SYM   | /SFT(ENT)/       \Space \  |NAV   |(FN, RAlt)| RClt | RGUI |
 *     |      |      |             |      |/       /         \      \ |      |          |      |      |
 *     `------------------------------------------'           '------''---------------------------'
 */

[_COLEMAK] = LAYOUT(
KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,          /**/  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,          /**/  KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC,
KC_LCTL,  GUI_A,  ALT_R,   SFT_S,   CTL_TH,   KC_D,         /**/  KC_H,   CTL_N,   SFT_E,   ALT_I,   GUI_O,  KC_QUOT,
KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE, /**/  XXXXXXX, KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ESC,
		           KC_LGUI, KC_LCTL, NUM_ALT,MO(_SYM), SFT_ENT, /**/  KC_SPC,MO(_NAV),  FN_ALT,  KC_RCTL,KC_RGUI
),

/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   `  |   ~  |   #  |   &  |   |  |                    |   ^  |   {  |   }  |   [  |   ]  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   _  |   :  |   =  |   $  |-------.    ,-------|   @  |   (  |   )  |   _  |      |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |   %  |   /  |   *  |   +  |   \  |-------|    |-------|   /  |   -  |   <  |   >  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |      | /Enter  /       \Space \  | ADJ  | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYM] = LAYOUT(
KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                       /**/ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
KC_TRNS, KC_GRV, S(KC_GRV), S(KC_3), S(KC_7), S(KC_BSLS),        /**/ S(KC_6), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC, KC_DEL,
KC_TRNS, S(KC_1), S(KC_MINS), S(KC_SCLN), KC_EQL, S(KC_4),       /**/ S(KC_2), S(KC_9), S(KC_0), S(KC_MINS), KC_TRNS, KC_PIPE,
KC_TRNS, S(KC_5), KC_SLSH, S(KC_8), S(KC_EQL), KC_BSLS, KC_TRNS, /**/ KC_TRNS, KC_SLSH, KC_MINS, S(KC_COMM), S(KC_DOT), KC_BSLS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     /**/ KC_TRNS, MO(_ADJUST), KC_TRNS, KC_TRNS, KC_TRNS
),

/* NAVIGATION
 * ,----------------------------------------.                        ,-----------------------------------------.
 * |      |      |       |        |      |     |                     |      |      |      |      |      |      |
 * |------+------+-------+------+-------+------|                     |------+------+------+------+------+------|
 * |      |      |       | MS_UP | Home |     |                      | HOME |      |  Up  | F10  | F11  |      |
 * |------+------+-------+------+------+------|                      |------+------+------+------+------+------|
 * |      |      |MS_LEFT|MS_DOWN|MS_RGHT| Caps |-------.    ,-------|  END | Left | Down | Right|      |      |
 * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste| PrtSc|-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR | ADJ  | /Enter  /       \Space \  |      | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NAV] = LAYOUT(
_______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
_______, _______, _______,   MS_UP, KC_HOME, _______,          /**/          KC_HOME, _______,   KC_UP,  KC_F10,  KC_F11, _______,
_______, _______, MS_LEFT, MS_DOWN, MS_RGHT,  KC_CAPS,         /**/          KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
_______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_PSCR, _______, /**/ _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______,
              _______, _______, _______, MO(_ADJUST), _______, /**/ _______, _______, _______, _______, _______
),

/* FUNCTION
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  | F12  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F4  |  F5  |  F6  | F11  |-------.    ,-------|      | RCTL | RSFT | RALT | RGUI |      |
 * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
 * |     |       |  F1  |  F2  |  F3  | F10  |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |NAV   | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_FN] = LAYOUT(
_______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
_______, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F12,          /**/          _______, _______, _______, _______, _______, _______,
_______, _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11,          /**/          _______, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, _______,
_______, _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10, _______, /**/ _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,                   /**/          _______, _______, _______, _______, _______
),

/* NUMBER
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | F12  |  F7  |  F8  |  F9  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | F11  |  F4  |  F5  |  F6  |      |-------.    ,-------|      | RCTL | RSFT | RALT | RGUI |      |
 * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
 * |     |  F10  |  F1  |  F2  |  F3  |    |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |NAV   | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NUM] = LAYOUT(
_______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,          /**/          _______,    KC_7,    KC_8,    KC_9,    KC_0, _______,
_______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,          /**/          _______,    KC_4,    KC_5,    KC_6, _______, _______,
_______, _______, _______, _______, _______, _______, _______, /**/ _______, _______,    KC_1,    KC_2,    KC_3, _______, _______,
_______, _______, _______, _______, _______,                   /**/ _______, _______, _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | QK_BOOT|      |QWERTY|COLEMAK|      |      |                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_ADJUST] = LAYOUT(
XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
QK_BOOT, XXXXXXX, DF(_QWERTY), DF(_COLEMAK),XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
				_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
    }
    return true;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_custom_state(void) {

    oled_write_P(PSTR("\n\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt\n"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk\n"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }

    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _COLEMAK:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbl\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Func\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
            break;
    }


    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);

#ifdef WPM_ENABLE
	oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
#endif
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_custom_state();
    } else {
        render_logo();
    }

    return false;
}

