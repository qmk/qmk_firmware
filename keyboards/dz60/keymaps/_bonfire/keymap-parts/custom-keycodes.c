/**
 * Custom Keycodes
 * https://beta.docs.qmk.fm/detailed-guides/custom_quantum_functions#custom-keycodes
 * 
 * Held Escape (for gaming)
 */

// Specify the Keycodes
enum custom_keycodes { 
    HLD_ESC = SAFE_RANGE
};

// held escape
bool esc_held = false;
uint16_t held_esc_timer = 0;

// Called on every keyup and keydown
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case HLD_ESC:
            if(record->event.pressed) {
                esc_held = true;
                held_esc_timer = timer_read(); 
            } else {
                esc_held = false;
                unregister_code(KC_ESC);
            }
            return true;
            break;

        default:
            return true;
            break;
    }
}

// checking the held escape timer
void matrix_scan_user(void)
{
    if(esc_held && timer_elapsed(held_esc_timer) > 470) {
        register_code(KC_ESC);
    }
}
