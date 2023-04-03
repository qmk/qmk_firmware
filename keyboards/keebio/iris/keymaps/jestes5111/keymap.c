#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FUNC 4

// Combinations of two keystrokes for easier reading
#define CSFT LCTL(KC_LSFT)
#define GSFT LGUI(KC_LSFT)
#define ACTL LCTL(KC_LALT)

// Macros for keyboard shortcuts
#define TERMINAL LCA(KC_T)
#define VSCODE LCA(KC_R)
#define DISCORD LCA(KC_D)
#define SPOTIFY LCA(KC_V)
#define UNLOCK LCA(KC_DEL)
#define FILL_BW RCS(KC_L)

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
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_APP,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,          KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    // └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       KC_LGUI, LOWER,   KC_SPC,                    KC_ENT, RAISE, KC_RGUI
    //                                └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_LOWER] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV,  KC_NO,   KC_NO,   KC_NO,   KC_BRID, KC_BRIU,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_INS,  KC_DEL,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        FUNC,    KC_NO,   KC_NO,   KC_NO,   VSCODE,  TERMINAL,                           THUMB,   KC_NO,   KC_EQL,  KC_MINS, KC_PLUS, KC_BSLS,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        ACTL,    KC_NO,   KC_NO,   DISCORD, KC_NO,   KC_NO,                              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, KC_QUOT,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_CAPS, KC_NO,   KC_NO,   KC_NO,   SPOTIFY, KC_WHOM, KC_NO,            CSFT,    KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_PGDN, KC_END,
    // └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       KC_NO,   KC_NO,   KC_NO,                     KC_UNDS, KC_LOCK, KC_NO
    //                                └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_RAISE] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        RGB_TOG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LPRN,                            KC_RPRN, KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        FILL_BW, KC_MPRV, KC_MNXT, KC_VOLU, KC_NO,   KC_LBRC,                            KC_RBRC, KC_NO,   KC_NO,   KC_NO,   RGB_VAI, QK_MAKE,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_NO,   KC_LCBR, KC_MENU,          KC_NO,   KC_RCBR, KC_END,  RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,
    // └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       KC_NO,   UNLOCK,  KC_UNDS,                   KC_NO,   KC_NO,   KC_NO
    //                                └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),

    [_FUNC] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSPC,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        QWERTY,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, KC_NO,
    // ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,   KC_NO,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LALT,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    // └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       KC_NO,   KC_BTN4, KC_BTN1,                   KC_BTN2, KC_BTN5, KC_NO
    //                                └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QWERTY:
                layer_off(_FUNC);
                default_layer_set(_QWERTY);
                return false;

            case LOWER:
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;

            case RAISE:
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;

            case ADJUST:
                layer_on(_ADJUST);
                return false;

            case FUNC:
                layer_move(_FUNC);
                return false;

            case THUMB:
                SEND_STRING(":disguised_face: :thumbsup:");
                SEND_STRING(SS_DELAY(100) SS_TAP(X_ENTER));
                return false;
        }
    }

    else {
        switch (keycode) {
            case LOWER:
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;

            case RAISE:
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;

            case ADJUST:
                layer_off(_ADJUST);
                return false;
        }
    }

    return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif
