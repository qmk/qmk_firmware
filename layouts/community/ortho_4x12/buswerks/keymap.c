#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _GAME,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    LOWER,
    RAISE,
    GAME,
    ADJUST
};

#define GAME TG(_GAME)
#define RSE_ENT LT(_RAISE, KC_ENT)
#define ESC_CTL LCTL_T(KC_ESC) // for Linux
#define ESC_CMD LGUI_T(KC_ESC) // for macOS

// Use these to switch desktops on macOS
#define DESK_L LCTL(KC_LEFT)
#define DESK_R LCTL(KC_RGHT)

// Use these to switch desktops on Gnome
#define DESK_UP LGUI(KC_PGUP)
#define DESK_DN LGUI(KC_PGDN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Use QWERTY on macOS (Colemak mapped using software)
    [_QWERTY] = LAYOUT_ortho_4x12(
            KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I,    KC_O   , KC_P   , KC_BSPC,
            ESC_CMD, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K,    KC_L   , KC_SCLN, KC_QUOT,
            SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC,
            XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_SPC , RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
            ),

    // Use Colemak on Linux (No native Colemak mapping)
    [_COLEMAK] = LAYOUT_ortho_4x12(
            KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
            ESC_CTL, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
            SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC,
            XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_SPC , RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
            ),

    [_DVORAK] = LAYOUT_ortho_4x12(
            KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
            ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
            KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
            XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_SPC , RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
            ),

    [_LOWER] = LAYOUT_ortho_4x12(
            KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_7,    KC_8,    KC_9,    KC_MINS, _______,
            KC_TILD, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_PIPE,
            _______, _______, _______, KC_UNDS, KC_EQL,  _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,
            _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  KC_COMM, _______, _______
            ),

    [_RAISE] = LAYOUT_ortho_4x12(
            KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_INS,  KC_DEL,
            KC_TILD, _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BSLS,
            _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, DESK_R,  DESK_DN, DESK_UP, DESK_L
            ),

    [_GAME] = LAYOUT_ortho_4x12(
            KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
            ESC_CMD, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
            KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT,
            XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER  , KC_SPC , KC_SPC , RSE_ENT, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
            ),

    [_ADJUST] = LAYOUT_ortho_4x12(
            _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______,  _______, _______, KC_DEL ,
            _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  GAME,    _______,
            _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______,  _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
            )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_RAISE) || IS_LAYER_ON(_LOWER)) {
        if (clockwise) {
            register_code(KC_VOLU);
            unregister_code(KC_VOLU);
        } else {
            register_code(KC_VOLD);
            register_code(KC_VOLD);
        }
    } else {
        if (clockwise) {
            #ifdef MOUSEKEY_ENABLE
                register_code(KC_MS_WH_DOWN);
                unregister_code(KC_MS_WH_DOWN);
            #else
                register_code(KC_PGDN);
                unregister_code(KC_PGDN);
            #endif
        } else {
            #ifdef MOUSEKEY_ENABLE
                register_code(KC_MS_WH_UP);
                unregister_code(KC_MS_WH_UP);
            #else
                register_code(KC_PGUP);
                unregister_code(KC_PGUP);
            #endif
        }
    }
    return true;
}
