#define BG_GRADIENT_VALUE 96
#define UNDERGLOW_VALUE 96
#define RGB_REFRESH_INTERVAL 66 /* 15fps */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

LED_TYPE bg[BACKLIGHT_NUM];

bool fg[BACKLIGHT_NUM];
LED_TYPE fg_color = { .r = 24, .g = 16, .b = 16 };

LED_TYPE led[RGBLED_NUM];
int dirty_led_count = 0;

/* ------ */

void rgb_send (void) {
    if (dirty_led_count) {
        ws2812_setleds(led, dirty_led_count);
        dirty_led_count = 0;
    }
}

void rgb_set_bg_cell_hsv (uint16_t h, uint8_t s, uint8_t v, int i) {
    sethsv(h, s, v, &bg[i]);

    if (!fg[i]) {
        sethsv(h, s, v, &led[i]);
    }

    dirty_led_count = BACKLIGHT_NUM;
}

void rgb_set_bg_cell (uint8_t r, uint8_t g, uint8_t b, int i) {
    setrgb(r, g, b, &bg[i]);

    if (!fg[i]) {
        setrgb(r, g, b, &led[i]);
    }

    dirty_led_count = BACKLIGHT_NUM;
}

void rgb_set_fg_cell (bool value, int i) {
    fg[i] = value;

    if (value) {
        setrgb(fg_color.r, fg_color.g, fg_color.b, &led[i]);
    } else {
        setrgb(bg[i].r, bg[i].g, bg[i].b, &led[i]);
    }

    dirty_led_count = MAX(dirty_led_count, i + 1);
}

void rgb_set_underglow_cell_hsv (uint16_t h, uint8_t s, uint8_t v, int i) {
    sethsv(h, s, v, &led[i + BACKLIGHT_NUM]);
    dirty_led_count = MAX(dirty_led_count, i + BACKLIGHT_NUM + 1);
}

void rgb_set_underglow_cell (uint8_t r, uint8_t g, uint8_t b, int i) {
    setrgb(r, g, b, &led[i + BACKLIGHT_NUM]);
    dirty_led_count = MAX(dirty_led_count, i + BACKLIGHT_NUM + 1);
}

void rgb_set_bg_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    for (int i = 0; i < BACKLIGHT_NUM; i++) {
        rgb_set_bg_cell_hsv(
            (h * i + h2 * (BACKLIGHT_NUM - 1 - i)) / (BACKLIGHT_NUM - 1),
            (s * i + s2 * (BACKLIGHT_NUM - 1 - i)) / (BACKLIGHT_NUM - 1),
            BG_GRADIENT_VALUE,
            i
        );
    }
}

void rgb_set_underglow_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    for (int i = 0; i < UNDERGLOW_NUM; i++) {
        rgb_set_underglow_cell_hsv(
            (h * i + h2 * (UNDERGLOW_NUM - 1 - i)) / (UNDERGLOW_NUM - 1),
            (s * i + s2 * (UNDERGLOW_NUM - 1 - i)) / (UNDERGLOW_NUM - 1),
            UNDERGLOW_VALUE,
            i
        );
    }
}

void rgb_set_bg_disabled (void) {
    for (int i = 0; i < BACKLIGHT_NUM; i++) {
        rgb_set_bg_cell(0, 0, 0, i);
    }
}

/* ---------- */

const uint8_t pos_to_lednum[MATRIX_ROWS][MATRIX_COLS] = {
    { 0,  1,  2,  3,  4,  5,  6  },
    { 7,  8,  9,  10, 11, 12, 0  },
    { 13, 14, 15, 16, 17, 18, 19 },
    { 0,  0,  0,  0,  0,  20, 21 },
    { 0,  1,  2,  3,  4,  5,  6  },
    { 7,  8,  9,  10, 11, 12, 0  },
    { 13, 14, 15, 16, 17, 18, 19 },
    { 20, 21, 0,  0,  0,  0,  0  }
};

void rgb_process_record (uint16_t keycode, keyrecord_t* record) {
    int row = record->event.key.row;
    int col = record->event.key.col;

    if (row >= 4) {
        if (is_master) return;
    } else {
        if (!is_master) return;
    }

    rgb_set_fg_cell(record->event.pressed, pos_to_lednum[row][col]);
}

void rgb_update (bool force) {
    static int last_update = 0;
    static uint32_t last_layer_state = ~0;

    if (last_update && timer_elapsed(last_update) < RGB_REFRESH_INTERVAL && !force) return;
    last_update = timer_read();

    if (layer_state != last_layer_state || force) {
        rgb_set_bg_gradient(180, 30, 180, 30);
        if (is_master) {
            rgb_set_underglow_gradient(90, 100, 270, 100);
        } else {
            rgb_set_underglow_gradient(90, 100, 270, 100);
        }
        last_layer_state = layer_state;
    }

    rgb_send();
}
