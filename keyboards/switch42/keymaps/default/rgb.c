#define BG_GRADIENT_VALUE 40
#define UNDERGLOW_VALUE 65
#define RGB_REFRESH_INTERVAL 66 /* 15fps */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

LED_TYPE bg[BACKLIGHT_NUM];

bool fg[BACKLIGHT_NUM];
LED_TYPE fg_color = { .r = 16, .g = 16, .b = 16 };

LED_TYPE led[RGBLED_NUM];
int dirty_led_count = 0;

/* ------ */

void rgb_send (void) {
    if (dirty_led_count) {
        ws2812_setleds(led, dirty_led_count);
        dirty_led_count = 0;
    }
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

void rgb_set_underglow_cell (uint8_t r, uint8_t g, uint8_t b, int i) {
    setrgb(r, g, b, &led[i + BACKLIGHT_NUM]);
    dirty_led_count = MAX(dirty_led_count, i + BACKLIGHT_NUM + 1);
}

void rgb_set_bg_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;

    sethsv(h, s, BG_GRADIENT_VALUE, &from);
    sethsv(h2, s2, BG_GRADIENT_VALUE, &to);

    for (int i = 0; i < BACKLIGHT_NUM; i++) {
        rgb_set_bg_cell(
            (to.r * i + from.r * (BACKLIGHT_NUM - 1 - i)) / (BACKLIGHT_NUM - 1),
            (to.g * i + from.g * (BACKLIGHT_NUM - 1 - i)) / (BACKLIGHT_NUM - 1),
            (to.b * i + from.b * (BACKLIGHT_NUM - 1 - i)) / (BACKLIGHT_NUM - 1),
            i
        );
    }
}

void rgb_set_underglow_gradient (uint16_t h, uint8_t s, uint16_t h2, uint8_t s2) {
    LED_TYPE from, to;

    sethsv(h, s, UNDERGLOW_VALUE, &from);
    sethsv(h2, s2, UNDERGLOW_VALUE, &to);

    for (int i = 0; i < UNDERGLOW_NUM; i++) {
        rgb_set_underglow_cell(
            (to.r * i + from.r * (UNDERGLOW_NUM - 1 - i)) / (UNDERGLOW_NUM - 1),
            (to.g * i + from.g * (UNDERGLOW_NUM - 1 - i)) / (UNDERGLOW_NUM - 1),
            (to.b * i + from.b * (UNDERGLOW_NUM - 1 - i)) / (UNDERGLOW_NUM - 1),
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


void rgb_process_record (uint16_t keycode, keyrecord_t* record) {
    int row = record->event.key.row;
    int col = record->event.key.col;

    if (row >= 4) {
        if (is_master) return;
        row -= 4;
    } else {
        if (!is_master) return;
    }

    if (row == 3) {
        col %= 3;
    }

    rgb_set_fg_cell(record->event.pressed, row * 6 + col);
}

void rgb_update (bool force) {
    static int last_update = 0;
    static uint32_t last_layer_state = ~0;

    if (last_update && timer_elapsed(last_update) < RGB_REFRESH_INTERVAL && !force) return;
    last_update = timer_read();

    if (layer_state != last_layer_state || force) {
        if (layer_state & L_GARAKE) {
            if (is_master) {
                rgb_set_bg_disabled();
            } else {
                rgb_set_bg_gradient(1, 90, 1, 90);
            }
        } else {
            rgb_set_bg_gradient(1, 90, 250, 95);
            rgb_set_underglow_gradient(1, 90, 250, 95);
        }
        last_layer_state = layer_state;
    }

    rgb_send();
}
