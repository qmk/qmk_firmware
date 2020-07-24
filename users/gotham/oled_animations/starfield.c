#ifdef OLED_ANIM_STARFIELD
#    include "starfield.h"

static uint8_t  n_stars = 0;
static uint8_t  star_ang[STAR_COUNT_MAX];
static uint8_t  star_rad[STAR_COUNT_MAX];
static uint8_t  zoom_speed          = STAR_ZOOM_SPEED_MIN;
static uint16_t star_lifetime_timer = 0;
static uint16_t star_update_timer   = 0;
static uint16_t center_x            = OLED_DISPLAY_WIDTH / 2;
static uint16_t center_y            = OLED_DISPLAY_HEIGHT / 2;

void oled_init_starfield(void) { set_starfield_center(); }

uint8_t inline starfield_speed_get(void) { return zoom_speed; }

void starfield_speed_set(uint8_t value) {
    bool in_range = ((value >= STAR_ZOOM_SPEED_MIN) && (value <= STAR_ZOOM_SPEED_MAX));
    zoom_speed    = in_range * value + !in_range * zoom_speed;
}

static void spawn_star(void) {
    star_ang[n_stars] = random8();
    star_rad[n_stars] = random8_min_max(STAR_SPAWN_RANGE, 16);
    n_stars++;
}

static inline uint8_t get_star_x(uint8_t index) { return center_x + (cos8(star_ang[index]) - 128) * star_rad[index] / 128; }

static inline uint8_t get_star_y(uint8_t index) { return center_y + (sin8(star_ang[index]) - 128) * star_rad[index] / 128; }

static void update_star(uint8_t index) {
#    ifdef OLED_ANIM_STARFIELD_DUALLAYER
    if (index % 2 == 0) {
        star_rad[index] += 1;
    } else
#    endif
    {
        star_rad[index] += map8(cubicwave8(star_rad[index]), 1, zoom_speed);
    }
    if (point_out_of_bounds(get_star_x(index), get_star_y(index), 24)) {
        star_ang[index] = random8();
        star_rad[index] = random8_min_max(STAR_SPAWN_RANGE, 16);
    }
}

void set_starfield_center(void) {
    center_x = random8_max(OLED_DISPLAY_WIDTH);
    center_y = random8_max(OLED_DISPLAY_HEIGHT);
}

void erase_stars(void) {
    for (uint8_t i = 0; i < n_stars; i++) {
        oled_write_pixel(get_star_x(i), get_star_y(i), false);
    }
}

void render_starfield(void) {
    uint16_t now = timer_read();
    if ((n_stars < STAR_COUNT_MAX) && (timer_elapsed(star_lifetime_timer) >= STAR_SPAWN_DELAY)) {
        spawn_star();
        star_lifetime_timer = now;
    }
    if (timer_elapsed(star_update_timer) >= UPDATE_DELAY) {
        zoom_speed -= 2 * (zoom_speed > STAR_ZOOM_SPEED_MIN);
        for (uint8_t i = 0; i < n_stars; i++) {
            oled_write_pixel(get_star_x(i), get_star_y(i), false);
            update_star(i);
            oled_write_pixel(get_star_x(i), get_star_y(i), true);
        }
        star_update_timer = now;
    }
}
#endif
