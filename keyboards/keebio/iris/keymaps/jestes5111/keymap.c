#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FUNC 4

// Combinations of two keystrokes for easier reading
#define CSFT LCTL(KC_LSFT)
#define GSFT LGUI(KC_LSFT)

enum custom_keycodes {
    QWERTY = SAFE_RANGE, 
    LOWER, 
    RAISE, 
    ADJUST, 
    FUNC, 
    THUMB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
    // ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        QK_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                     KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                                     KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_APP,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_LCTL,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                                     KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RCTL,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_LALT,            KC_RALT,   KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
    // └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
                                              KC_LGUI,   LOWER,     KC_SPC,                        KC_ENT,    RAISE,     KC_RGUI
    //                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
    ), 
    
    [_LOWER] = LAYOUT(
    // ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,   KC_VOLU,   KC_VOLD,                                  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_INS,    KC_DEL,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_NO,     KC_F13,    KC_F14,    KC_F15,    KC_F16,    KC_NO,                                    THUMB,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_NO,     KC_F17,    KC_F18,    KC_F19,    KC_F20,    KC_NO,                                    KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   KC_NO,     RCS(KC_L),
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        CSFT,      KC_F21,    KC_F22,    KC_F23,    KC_F24,    KC_WHOM,   KC_NO,              KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    // └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
                                              KC_NO,     KC_NO,     KC_NO,                         KC_UNDS,   KC_NO,     KC_NO
    //                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
    ),

    [_RAISE] = LAYOUT(
    // ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        KC_F12,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,                                    KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_TAB,    KC_NO,     KC_NO,     KC_NO,     KC_AMPR,   KC_LPRN,                                  KC_RPRN,   KC_ASTR,   KC_EQL,    KC_MINS,   KC_PLUS,   KC_BSLS,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_ENT,    KC_NO,     KC_NO,     KC_NO,     KC_PIPE,   KC_LBRC,                                  KC_RBRC,   KC_NO,     KC_NO,     KC_NO,     KC_DQUO,   KC_QUOT,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_CAPS,   KC_NO,     KC_NO,     KC_NO,     KC_LABK,   KC_LCBR,   KC_MENU,            KC_NO,     KC_RCBR,   KC_RABK,   KC_NO,     KC_NO,     KC_NO,     KC_NO,
    // └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
                                              KC_NO,     KC_NO,     KC_UNDS,                       KC_NO,     KC_NO,     KC_NO
    //                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
    ),

    [_ADJUST] = LAYOUT(
    // ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        RGB_TOG,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                    KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        TO(FUNC),  KC_NO,     KC_NO,     KC_NO,     KC_NO,     LCA(KC_T),                                KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     QK_BOOT,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_NO,     KC_NO,     LCA(KC_V), LCA(KC_D), KC_NO,     LCA(KC_R),                                KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     QK_MAKE,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_LSFT,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,              KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     EE_CLR,
    // └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
                                              KC_NO,     KC_NO,     KC_NO,                         KC_NO,     KC_NO,     KC_NO
    //                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
    ),

    [_FUNC] = LAYOUT(
    // ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐                              ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        KC_ESC,    KC_SLSH,   KC_ASTR,   KC_MINS,   KC_PLUS,   KC_EQL,                                   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_BSPC,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_TAB,    KC_7,      KC_8,      KC_9,      KC_LPRN,   KC_RPRN,                                  KC_WH_L,   KC_WH_D,   KC_WH_U,   KC_WH_R,   KC_BTN3,   KC_NO,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤                              ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_LCTL,   KC_4,      KC_5,      KC_6,      KC_DOT,    KC_NUM,                                   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R,   KC_NO,     KC_NO,
    // ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐        ┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
        KC_LSFT,   KC_1,      KC_2,      KC_3,      KC_0,      KC_ENT,    KC_LALT,            KC_BTN2,   KC_BTN1,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    // └──────────┴──────────┴──────────┴────┬─────┴────┬─────┴────┬─────┴────┬─────┘        └────┬─────┴────┬─────┴────┬─────┴────┬─────┴──────────┴──────────┴──────────┘
                                             TO(QWERTY), KC_CIRC,   KC_SPC,                        KC_ENT,    KC_BTN5,   KC_BTN4
    //                                       └──────────┴──────────┴──────────┘                   └──────────┴──────────┴──────────┘
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Layers
        case QWERTY:
            if (record-> event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case FUNC:
            if (record->event.pressed) {
                layer_on(_FUNC);
            } else {
                layer_off(_FUNC);
            }
            return false;

        // Macros
        case THUMB:
            if (record->event.pressed) {
                SEND_STRING(":disguised_face: :thumbsup:");
                SEND_STRING(SS_DELAY(100) SS_TAP(X_ENTER));
            }
            return false;
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void eeconfig_init_user(void) {
    rgblight_enable();
    rgblight_sethsv(HSV_PURPLE);
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
        case _FUNC:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        default:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
    }
    return state;
}