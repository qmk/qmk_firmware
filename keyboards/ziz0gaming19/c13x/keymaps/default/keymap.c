#include QMK_KEYBOARD_H

// Layers
enum layers {
    _BASE,
    _FN,
    _LAYER2,
    _LAYER3
};

// Custom keycodes
enum custom_keycodes {
    RESET_QMK = SAFE_RANGE,
    NEXT_LAYER
};

static uint8_t current_layer = 0; // 0=_BASE, 1=_LAYER2, 2=_LAYER3

// Combo definitions
const uint16_t PROGMEM combo_qp[] = {KC_Q, KC_P, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_qp, RESET_QMK),
};

uint8_t get_combo_count(void) {
    return ARRAY_SIZE(key_combos);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case RESET_QMK:
            reset_keyboard();
            return false;

        case NEXT_LAYER:
            // Turn off previous active layer above _BASE
            if (current_layer == 1) layer_off(_LAYER2);
            else if (current_layer == 2) layer_off(_LAYER3);

            // Cycle next layer index
            current_layer = (current_layer + 1) % 3;

            // Turn on new layer above _BASE (except 0 means just _BASE)
            if (current_layer == 1) layer_on(_LAYER2);
            else if (current_layer == 2) layer_on(_LAYER3);
            // if current_layer == 0, only _BASE active

            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    set_single_persistent_default_layer(_BASE);
}

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_10x4(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
        KC_Z, KC_X, KC_C, KC_V, KC_B, NEXT_LAYER, KC_N, KC_M, KC_SLSH, KC_TAB,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),

    [_FN] = LAYOUT_10x4(
        KC_ESC, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_PSCR, KC_NO, KC_MINUS, KC_EQUAL, KC_BSPC,
        KC_TAB, KC_MPLY, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_SCLN, KC_QUOT, KC_ENT,
        KC_CAPS, KC_LBRC, KC_RBRC, KC_NUBS, KC_GRV, KC_NO, KC_COMM, KC_DOT, KC_SLSH, KC_TAB,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),

    [_LAYER2] = LAYOUT_10x4(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NEXT_LAYER, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    ),

    [_LAYER3] = LAYOUT_10x4(
        KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_INSERT, KC_HOME, KC_PGUP, KC_NO, KC_NO,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_DELETE, KC_END, KC_PGDN, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NEXT_LAYER, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LALT, KC_SPC, MO(_FN), KC_LGUI, KC_RSFT
    )
};
