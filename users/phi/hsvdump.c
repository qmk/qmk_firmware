void dump_uint (uint8_t n) {
    if (n) {
        dump_uint(n / 10);
        tap_code(KC_1 + (n - 1) % 10);
    }
}

bool process_hsvdump (keyrecord_t *record) {
    if (record->event.pressed) {
        tap_code(KC_H);
        dump_uint(rgb_matrix_config.hsv.h);
        tap_code(KC_SPC);
        tap_code(KC_S);
        dump_uint(rgb_matrix_config.hsv.s);
        tap_code(KC_SPC);
        tap_code(KC_V);
        dump_uint(rgb_matrix_config.hsv.v);
    }
    return false;
}
