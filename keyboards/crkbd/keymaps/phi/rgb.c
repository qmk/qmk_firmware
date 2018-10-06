typedef struct rgb_color { uint8_t r; uint8_t g; uint8_t b; } rgb_color_t;
typedef rgb_color_t rgb_image_t[RGBLED_NUM];

void rgb_send_image (rgb_image_t *image) {
    for (int i = 0; i < RGBLED_NUM; i++) {
        rgblight_setrgb_at(image[i]->r, image[i]->g, image[i]->b, i);
    }
}

void rgb_render_gradient (rgb_image_t *image, uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;
    sethsv(h, s, 255, &from);
    sethsv(h2, s2, 255, &to);
    for (int i = 0; i < RGBLED_NUM; i++) {
        image[i]->r = (to.r * i + from.r * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1);
        image[i]->g = (to.g * i + from.g * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1);
        image[i]->b = (to.b * i + from.b * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1);
    }
}

void update_rgblight (void) {
    static bool rgb_initialized = false;
    static rgb_image_t image;
    if (!rgb_initialized) {
        rgb_render_gradient(&image, 250, 135, 1, 130);
        rgb_send_image(&image);
        rgb_initialized = true;
    }
}
