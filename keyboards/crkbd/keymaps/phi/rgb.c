void rgb_set_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;

    sethsv(h, s, 255, &from);
    sethsv(h2, s2, 255, &to);

    for (int i = 0; i < RGBLED_NUM; i++) {
        rgblight_setrgb_at(
            (to.r * i + from.r * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.g * i + from.g * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.b * i + from.b * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            i
        );
    }
}

void update_rgblight (void) {
    static bool rgb_initialized = false;
    if (!rgb_initialized) {
        rgb_set_gradient(250, 135, 1, 130);
        rgb_initialized = true;
    }
}
