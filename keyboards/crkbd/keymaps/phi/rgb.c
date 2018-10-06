void rgb_render_gradient (uint16_t h, uint8_t s, uint8_t v, uint16_t h2, uint8_t s2, uint8_t v2) {
    rgblight_sethsv_at(h, s, v, 0);
    rgblight_sethsv_at((h * 3 + h2) / 4, (s * 3 + s2) / 4, (v * 3 + v2) / 4, 3);
    rgblight_sethsv_at((h + h2) / 2, (s + s2) / 2, (v + v2) / 2, 2);
    rgblight_sethsv_at((h + h2 * 3) / 4, (s + s2 * 3) / 4, (v + v2 * 3) / 4, 3);
    rgblight_sethsv_at(h2, s2, v2, 4);
}

void rgblight_task (void) {
    static bool rgb_initialized = false;
    if (!rgb_initialized) {
        rgb_render_gradient(341, 201, 223, 285, 145, 135);
        rgb_initialized = true;
    }
}
