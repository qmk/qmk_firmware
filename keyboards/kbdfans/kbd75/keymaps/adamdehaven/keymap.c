#include QMK_KEYBOARD_H

// Compile from qmk_firmware folder with the following command:
// $ make kbdfans/kbd75/rev2:adamdehaven

// Each layer gets a name for readability. The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, and you can also skip them entirely and just use numbers.
#define _QWERTY 0
#define _FN1 1

extern rgblight_config_t rgblight_config;
static bool RGB_user_wants_enabled;
uint16_t RGB_current_mode;
uint16_t RGB_current_hue;
uint16_t RGB_current_sat;
uint16_t RGB_current_val;

// Setup RGB
void keyboard_post_init_user(void) {
    RGB_user_wants_enabled = rgblight_config.enable;
    RGB_current_mode = rgblight_config.mode;
    RGB_current_hue  = rgblight_config.hue;
    RGB_current_sat  = rgblight_config.sat;
    RGB_current_val  = rgblight_config.val;
};

// Restore user settings
void restore_user_rgb_settings(void) {
    // First, enable RGB
    if (RGB_user_wants_enabled && !rgblight_config.enable) {
        rgblight_enable();
    } else if (!RGB_user_wants_enabled && rgblight_config.enable) {
        rgblight_disable();
    }

    // Restore settings
    rgblight_sethsv(RGB_current_hue, RGB_current_sat, RGB_current_val); // Restore underglow RGB color
    rgblight_mode(RGB_current_mode); // Restore RGB mode
};

// Tap Dance Definitions
enum tapdance {
    TD_PGUP = 0,
    TD_PGDN
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for PageUp, twice for Home
    [TD_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
    // Tap once for PageDown, twice for End
    [TD_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END)
};

// Fire on keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (!record->event.pressed) {
                // on keyup
                RGB_user_wants_enabled = rgblight_config.enable;
            }
            break;
        case RGB_MOD:
            if (!record->event.pressed) {
                // on keyup
                RGB_current_mode = rgblight_config.mode;
            }
            break;
        case RGB_HUI:
        case RGB_HUD:
            if (!record->event.pressed) {
                // on keyup
                RGB_current_hue = rgblight_config.hue;
            }
            break;
        case RGB_SAI:
        case RGB_SAD:
            if (!record->event.pressed) {
                // on keyup
                RGB_current_sat = rgblight_config.sat;
            }
            break;
        case RGB_VAI:
        case RGB_VAD:
            if (!record->event.pressed) {
                // on keyup
                RGB_current_val = rgblight_config.val;
            }
            break;
    }
    return true;
};


/*
 *  You can use _______ in place for KC_TRNS (transparent)
 *  Or you can use XXXXXXX for KC_NO (NOOP)
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: _QWERTY
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │ KC_ESC  │ KC_F1   │ KC_F2   │ KC_F3   │ KC_F4   │ KC_F5   │ KC_F6   │ KC_F7   │ KC_F8   │ KC_F9   │ KC_F10  │ KC_F11  │ KC_F12  │ KC_PSCR │KC_INSERT│ KC_DEL  │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤
     * │ KC_GRV  │ KC_1    │ KC_2    │ KC_3    │ KC_4    │ KC_5    │ KC_6    │ KC_7    │ KC_8    │ KC_9    │ KC_0    │ KC_MINS │ KC_EQL  │      KC_BSPC      │ KC_HOME │
     * ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤
     * │   KC_TAB     │ KC_Q    │ KC_W    │ KC_E    │ KC_R    │ KC_T    │ KC_Y    │ KC_U    │ KC_I    │ KC_O    │ KC_P    │ KC_LBRC │ KC_RBRC │   KC_BSLS    │ KC_END  │
     * ├──────────────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴──────────────┼─────────┤
     * │    KC_CAPS     │ KC_A    │ KC_S    │ KC_D    │ KC_F    │ KC_G    │ KC_H    │ KC_J    │ KC_K    │ KC_L    │ KC_SCLN │ KC_QUOT │       KC_ENT         │ TD_PGUP │
     * ├────────────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────────────┬─────────┼─────────┤
     * │     KC_LSFT (2)     │ KC_Z    │ KC_X    │ KC_C    │ KC_V    │ KC_B    │ KC_N    │ KC_M    │ KC_COMM │ KC_DOT  │ KC_SLSH │     KC_RSFT     │ KC_UP   │ TD_PGDN │
     * ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬┴────────┬─┴───────┬─────────┼─────────┼─────────┤
     * │  KC_LCTL  │  KC_LGUI  │  KC_LALT  │                            KC_SPC                             │ KC_RALT │MO(_FN1) │ KC_RCTL │ KC_LEFT │ KC_DOWN │ KC_RGHT │
     * └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [_QWERTY] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_INSERT, KC_DEL,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, TD(TD_PGUP),
        KC_LSFT, _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, TD(TD_PGDN),
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* 1: _FN1
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ KC_MUTE │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤
     * │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │      _______      │ _______ │
     * ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤
     * │   _______    │ RGB_TOG │ RGB_MOD │ RGB_HUI │ RGB_HUD │ RGB_SAI │ RGB_SAD │ RGB_VAI │ RGB_VAD │ _______ │ _______ │ _______ │ _______ │   _______    │ _______ │
     * ├──────────────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴─┬───────┴──────────────┼─────────┤
     * │    _______     │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │ _______ │       _______        │ KC_VOLU │
     * ├────────────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────────────┬─────────┼─────────┤
     * │     _______ (2)     │ _______ │ _______ │ BL_DOWN │ BL_TOGG │ BL_UP   │ BL_STEP │ _______ │ _______ │ _______ │ _______ │     _______     │ KC_MPLY │ KC_VOLD │
     * ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤
     * │  _______  │  _______  │  _______  │                            _______                            │ _______ │ _______ │ _______ │ KC_MPRV │ KC_MPLY │ KC_MNXT │
     * └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [_FN1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,
        _______, _______, _______, _______, BL_DOWN,BL_TOGG, BL_UP,  BL_STEP, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
    )
};

void toggle_rgb_caps_lock(bool isActive) {
    if (isActive) {
        if (!rgblight_config.enable) {
            rgblight_enable();
        }

        // Set underglow color if CAPS_LOCK enabled
        rgblight_sethsv(HSV_RED);
        // Set to breathe
        rgblight_mode(5);
    } else {
        restore_user_rgb_settings();
    }
};

bool led_update_user(led_t led_state) {
    toggle_rgb_caps_lock(led_state.caps_lock);
    return true;
};
