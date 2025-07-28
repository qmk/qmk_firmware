#include QMK_KEYBOARD_H

// Buffer to store the last 3 keycodes
static uint16_t last_keycodes[3] = {KC_NO, KC_NO, KC_NO};

// Function to update keycode history
void update_keycode_history(uint16_t keycode) {
    // Shift older keycodes
    last_keycodes[2] = last_keycodes[1]; // hold KC_A etc
    last_keycodes[1] = last_keycodes[0];
    last_keycodes[0] = keycode;
}

// Optionally: print keycodes to console
void print_keycode_history(void) {
    uprintf("Recent keycodes: %d, %d, %d\n", last_keycodes[0], last_keycodes[1], last_keycodes[2]);
}

// Hook into key processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        update_keycode_history(keycode);
        print_keycode_history();  // Optional: debug output
    }
    return true; // Continue processing key
}
