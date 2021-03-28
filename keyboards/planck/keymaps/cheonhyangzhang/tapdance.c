// Tap Dance declarations
enum {
    TD_SEMICOLON,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SEMICOLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_LSFT(KC_SCLN)),
};

// Add tap dance item to your keymap in place of a keycode
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ...
    TD(TD_SEMICOLON)
    // ...
};
