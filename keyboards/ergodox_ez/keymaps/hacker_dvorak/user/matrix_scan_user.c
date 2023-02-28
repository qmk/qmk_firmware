bool MATRIX_SCANNED = false;

void matrix_scan_user(void) {
    if (!(MATRIX_SCANNED)) {
        rgblight_sethsv_noeeprom(HSV_GREEN);
        MATRIX_SCANNED = true;
    }
};

void leader_end_user(void) {
    if (leader_sequence_one_key(TD(APMR_PIPE))) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_U);

        unregister_code(KC_U);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }
}
