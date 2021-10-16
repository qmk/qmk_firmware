#include QMK_KEYBOARD_H

enum alt_keycodes {
    ALT_DEL = SAFE_RANGE // Added to map left alt + backspace to delete
};

// Friendly layer names
enum alt_layers {
    DEF = 0,
    ALT,
    FUNC,
    SUPR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, MO(SUPR),         KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, MO(FUNC),KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [ALT] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, _______, KC_LALT,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    ),
    [FUNC] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,    KC_END,  KC_VOLU,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, RGB_M_P, _______, _______, KC_PAUS, KC_PSCR, _______, _______, _______,             KC_MUTE, KC_VOLD,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_M_B, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_TOG, _______, _______, EEP_RST, RESET,   _______, _______, _______, TG(ALT), _______, _______, _______,             KC_PGUP,
        _______, _______, KC_LALT,          _______,          _______,          _______,          _______, _______, _______,             KC_HOME, KC_PGDN, KC_END
    ),
    [SUPR] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ALT_DEL, ALT_DEL,    KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, _______, _______,          _______,          _______,          _______,          _______, _______, _______,             KC_HOME, _______, KC_END
    )
};

// If the super alt layer is the active layer
bool super_alt_layer_active = false;

// If we need to unregister alt when leaving the super alt layer
bool need_to_unregister_alt = false;

// This runs code every time that the layers get changed
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case DEF:
            // When returning to the default layer, check if we need to unregister the left alt key
            if (super_alt_layer_active && need_to_unregister_alt) {
                unregister_code(KC_LALT);
            }

            super_alt_layer_active = false;
            need_to_unregister_alt = false;
            break;
        case SUPR:
            super_alt_layer_active = true;
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        // These are the keys we want to 'fall though' and behave as usual when pressed with the alt modifier
        case KC_A ... KC_Z:
        case KC_TAB:
        case KC_DEL:
        case KC_UP:
        case KC_DOWN:
        case MO(FUNC):
            if (super_alt_layer_active && record->event.pressed) {
                // Only activate the alt modifier for the first key press
                if ((get_mods() & MOD_BIT(KC_LALT)) == false) {
                    register_code(KC_LALT);
                    need_to_unregister_alt = true;
                }
            }
            // We still want to process the keycode normally
            return true;
        case KC_F4:
            // Map alt+shift+4 to alt+f4
            if (super_alt_layer_active && (get_mods() & MOD_BIT(KC_LSHIFT))) {
                if (record->event.pressed) {
                    register_code(KC_LALT);
                } else {
                    unregister_code(KC_LALT);
                }
            }
            return true;
        case ALT_DEL:
            if (record->event.pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            return false;
        case RESET:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case EEP_RST:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    eeconfig_init();
                }
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
