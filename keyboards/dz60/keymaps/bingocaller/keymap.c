#include QMK_KEYBOARD_H

enum custom_keycodes {
    WORD_BACK = SAFE_RANGE,
    WORD_FORWARD,
    DELETE_WORD_BACK,
    DELETE_WORD_FORWARD,
    FINE_VOLUP,
    FINE_VOLDOWN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case WORD_BACK:
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
                return false;
            case WORD_FORWARD:
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
                return false;
            case DELETE_WORD_BACK:
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_BSPACE) SS_UP(X_LALT));
                return false;
            case DELETE_WORD_FORWARD:
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_DELETE) SS_UP(X_LALT));
                return false;
            case FINE_VOLUP:
                SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) SS_TAP(X__VOLUP) SS_UP(X_LALT) SS_UP(X_LSHIFT));
                return false;
            case FINE_VOLDOWN:
                SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) SS_TAP(X__VOLDOWN) SS_UP(X_LALT) SS_UP(X_LSHIFT));
                return false;
            default:
                return true;  // Process all other keycodes normally
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Default layer:
        * Space Cadet shifts (parentheses on tap)
        * Caps Lock is Control on hold, Esc on tap
        * Hyper/Caps Lock on Control
        * Hold D to activate layer 1
        * Hold Space to activate layer 3 (Mouse keys)
        * Hold FN to activate layer 4
    */
    LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LCTL_T(KC_ESC), KC_A, KC_S, LT(1, KC_D), KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSPO, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_NO,
        ALL_T(KC_CAPS), KC_LALT, KC_LGUI, LT(3, KC_SPC), LT(3, KC_SPC), LT(3, KC_SPC), KC_RGUI, KC_RALT, KC_NO, MO(3), ALL_T(KC_CAPS)),

    /*  Layer 1:
        * Vim arrows (HJKL)
        * Vim-like move across words with W(ord), and B(eginning)
        * Media controls (fine volume controls using Option+Shift)
        * Backspace/Del on N/M
        * Hold F to activate layer 2
    */
    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, WORD_FORWARD, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE, FINE_VOLDOWN, FINE_VOLUP, _______,
        _______, _______, _______, _______, LT(2, _______), _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, WORD_BACK, KC_BSPC, KC_DEL, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*  Layer 2:
        * Home, End, Page Up, Page Down
        * Delete word forward/back on W/B
    */
    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, DELETE_WORD_FORWARD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, DELETE_WORD_BACK, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*  Layer 3:
        * Mouse keys
            * Cursor movement: HJKL
            * MB 1, 2, and 3 on F, D, and S, respectively
            * Mouse wheel: U(p) and D(own)
    */
    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, _______,
        _______, _______, _______, _______, KC_WH_D, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*  Layer 4:
        * F1-12
        * Del on backspace
        * RGB (underglow) controls
        * RESET firmware on backslash
        * Screen brightness: Z (decrease), X (increase)
    */
    LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_DEL,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_BRMD, KC_BRMU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    // TEMPLATE
    // LAYOUT(
        // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};
