// Keychron V1 ANSI Knob - Command Macro Firmware
// Encoder cycles through 4 command targets, press to execute

#include QMK_KEYBOARD_H

// ============================================================================
// CONFIGURATION
// ============================================================================

#define NUM_COMMANDS 4  // Number of commands to cycle through

// Current selected command index (0-3)
static uint8_t current_command = 0;

// ============================================================================
// CUSTOM KEYCODES
// ============================================================================

enum custom_keycodes {
    CMD_EXEC = SAFE_RANGE,  // Knob press → execute current command
};

// ============================================================================
// KEYMAPS
// ============================================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Base ANSI layout with encoder press mapped to CMD_EXEC */
    [0] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             CMD_EXEC,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    /* Layer 1: Function layer (access via MO(1) - typically right Alt) */
    [1] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  _______,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Layer 2: VIA layer (must exist for VIA compatibility) */
    [2] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* Layer 3: VIA layer (must exist for VIA compatibility) */
    [3] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______
    )
};

// ============================================================================
// ENCODER LOGIC
// ============================================================================

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

// Override encoder behavior for command cycling
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // Primary encoder (knob)
        if (clockwise) {
            // Rotate clockwise → next command
            current_command = (current_command + 1) % NUM_COMMANDS;
        } else {
            // Rotate counter-clockwise → previous command
            current_command = (current_command + NUM_COMMANDS - 1) % NUM_COMMANDS;
        }

        // Send hotkey to notify OS which command is selected
        // Hotkeys: Ctrl+Alt+F13, F14, F15, F16
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_F13 + current_command);
        wait_ms(10);
        unregister_code(KC_F13 + current_command);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);

        return false;  // Skip default encoder behavior
    }
    return true;
}

// ============================================================================
// CUSTOM KEYCODE HANDLER
// ============================================================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_EXEC:
            if (record->event.pressed) {
                // Knob pressed → send execution hotkey (Ctrl+Alt+Enter)
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_ENT);
                wait_ms(10);
                unregister_code(KC_ENT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false;
    }
    return true;
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void keyboard_post_init_user(void) {
    // Initialize to command 0 on boot
    current_command = 0;
}
