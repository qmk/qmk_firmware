bool rgb_overriden = false;

void rgb_set_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;

    sethsv(h * 256 / 360, s, 255, &from);
    sethsv(h2 * 256 / 360, s2, 255, &to);

    for (int i = 0; i < RGBLED_NUM; i++) {
        rgblight_setrgb_at(
            (to.r * i + from.r * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.g * i + from.g * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.b * i + from.b * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            i
        );
    }
}

void rgb_set_disabled (void) {
    rgblight_sethsv(0, 0, 0);
}

void update_rgblight (bool force) {
    static uint32_t last_layer_state = ~0;
    if ((layer_state != last_layer_state || force) && !rgb_overriden) {
        if (layer_state & L_GARAKE) {
            if (is_master) {
                rgb_set_disabled();
            } else {
                rgb_set_gradient(1, 130, 1, 130);
            }
        } else {
            rgb_set_gradient(1, 130, 250, 135);
        }
        last_layer_state = layer_state;
    }
}

void rgb_override_color (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    rgb_overriden = true;
    rgb_set_gradient(h, s, h2, s2);
}

void rgb_unoverride_color (void) {
    rgb_overriden = false;
    update_rgblight(true);
}
