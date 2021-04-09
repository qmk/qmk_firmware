/**
 * Custom Keycodes
 * https://beta.docs.qmk.fm/detailed-guides/custom_quantum_functions#custom-keycodes
 * 
 */

// Called on every keyup and keydown
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case HLD_ESC:
            if(record->event.pressed) {
                is_esc_held = true;
                held_esc_timer = timer_read(); 
            } else {
                is_esc_held = false;
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
    if(is_esc_held && timer_elapsed(held_esc_timer) > held_esc_threshold) {
        register_code(KC_ESC);
    }
}
