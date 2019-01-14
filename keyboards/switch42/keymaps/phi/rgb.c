LED_TYPE bg[RGBLED_NUM];

bool fg[RGBLED_NUM];
LED_TYPE fg_color = { .r = 255, .g = 255, .b = 255 };

LED_TYPE led[RGBLED_NUM];

/* ------ */

void rgb_send (void) {
    ws2812_setleds(led, RGBLED_NUM);
}

void rgb_set_bg_cell (uint8_t r, uint8_t g, uint8_t b, int i) {
    bg[i].r = r;
    bg[i].g = g;
    bg[i].b = b;
    led[i].r = fg[i] ? fg_color.r : r;
    led[i].g = fg[i] ? fg_color.g : g;
    led[i].b = fg[i] ? fg_color.b : b;
}

void rgb_set_fg_cell (bool value, int i) {
    fg[i] = value;
    led[i].r = value ? fg_color.r : bg[i].r;
    led[i].g = value ? fg_color.g : bg[i].g;
    led[i].b = value ? fg_color.b : bg[i].b;
}

void rgb_set_bg_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;

    sethsv(h, s, 255, &from);
    sethsv(h2, s2, 255, &to);

    for (int i = 0; i < RGBLED_NUM; i++) {
        rgb_set_bg_cell(
            (to.r * i + from.r * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.g * i + from.g * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            (to.b * i + from.b * (RGBLED_NUM - 1 - i)) / (RGBLED_NUM - 1),
            i
        );
    }
}

void rgb_set_bg_disabled (void) {
    for (int i = 0; i < RGBLED_NUM; i++) {
        rgb_set_bg_cell(0, 0, 0, i);
    }
}

/* ---------- */

bool temporary_bg_enabled = false;

void rgb_process_record (uint16_t keycode, keyrecord_t* record) {
    int row = record->event.key.row;
    int col = record->event.key.col;

    if (row >= 4) {
        if (is_master) return;
        row -= 4;
    } else {
        if (!is_master) return;
    }

    if (row == 4) {
        col %= 3;
    }

    rgb_set_fg_cell(record->event.pressed, row * 6 + col);
    rgb_send();
}

void rgb_update (bool force) {
    static uint32_t last_layer_state = ~0;
    if ((layer_state != last_layer_state || force) && !temporary_bg_enabled) {
        if (layer_state & L_GARAKE) {
            if (is_master) {
                rgb_set_bg_disabled();
            } else {
                rgb_set_bg_gradient(1, 130, 1, 130);
            }
        } else {
            rgb_set_bg_gradient(1, 130, 250, 135);
        }
        last_layer_state = layer_state;
        rgb_send();
    }
}

void rgb_override_color (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    temporary_bg_enabled = true;
    rgb_set_bg_gradient(h, s, h2, s2);
    rgb_send();
}

void rgb_unoverride_color (void) {
    temporary_bg_enabled = false;
    rgb_update(true);
}
