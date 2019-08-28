#include "brandonschlack.h"
#include "rgb_theme.h"
#include "rgb_bs.h"

#if defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
#elif defined(RGB_MATRIX_ENABLE)
extern rgb_config_t rgb_matrix_config;
extern bool g_suspend_state;
extern led_config_t g_led_config;
#endif

#if defined(RGB_THEME_ENABLE)
static const HSV default_adjust = { HSV_SPRINGGREEN };

// Laser Color Constants
// Laser Colors
#define HSV_LSR_PURPLE   HSV_PURPLE
#define HSV_LSR_PINK     HSV_PINK
#define HSV_LSR_BLUE     HSV_BLUE
#define HSV_LSR_CYAN     HSV_CYAN
#define HSV_LSR_MAGENTA  HSV_MAGENTA
static const HSV laser_purple =  { HSV_LSR_PURPLE };
static const HSV laser_pink =    { HSV_LSR_PINK };
static const HSV laser_blue =    { HSV_LSR_BLUE };
static const HSV laser_cyan =    { HSV_LSR_CYAN };
static const HSV laser_magenta = { HSV_LSR_MAGENTA };
static const rgb_theme_t rgb_laser = { { &laser_purple, &laser_pink, &laser_blue, &laser_cyan, &laser_magenta } };

// Granite Color Constants
// Granite Colors
#define HSV_GNT_BLUE     HSV_BLUE
#define HSV_GNT_RED      HSV_RED
#define HSV_GNT_GREEN    HSV_GREEN
#define HSV_GNT_YELLOW   HSV_YELLOW
#define HSV_GNT_WHITE    HSV_WHITE
static const HSV granite_white =  { HSV_GNT_WHITE };
static const HSV granite_blue =   { HSV_GNT_BLUE };
static const HSV granite_red =    { HSV_GNT_RED };
static const HSV granite_green =  { HSV_GNT_GREEN };
static const HSV granite_yellow = { HSV_GNT_YELLOW };
static const rgb_theme_t rgb_granite = { { &granite_white, &granite_blue, &granite_red, &granite_green, &granite_yellow } };

// Oblique Color Constants
// Oblique Colors
#define HSV_OBQ_BLUE     130, 215, 255
#define HSV_OBQ_RED      10,  200, 255
#define HSV_OBQ_GREEN    58,  199, 255
#define HSV_OBQ_ORANGE   26,  215, 255
#define HSV_OBQ_PURPLE   186, 143, 255
#define HSV_OBQ_WHITE    HSV_WHITE
static const HSV oblique_white =  { HSV_OBQ_WHITE };
static const HSV oblique_purple = { HSV_OBQ_PURPLE };
static const HSV oblique_red =    { HSV_OBQ_RED };
static const HSV oblique_orange = { HSV_OBQ_ORANGE };
static const HSV oblique_green =  { HSV_OBQ_GREEN };
static const rgb_theme_t rgb_oblique = { { &oblique_white, &oblique_purple, &oblique_red, &oblique_orange, &oblique_green } };

// Set themes to be included
enum rgb_themes {
    LASER = 0,
    GRANITE,
    OBLIQUE
};
const rgb_theme_t *themes[] = { \
    [LASER] = &rgb_laser, \
    [GRANITE] = &rgb_granite, \
    [OBLIQUE] = &rgb_oblique, \
};
static const size_t rgb_theme_max = (sizeof themes / sizeof *themes);
#endif

void keyboard_post_init_rgb(void) {
    layer_state_set_user(layer_state);
#if defined(RGBLIGHT_ENABLE)
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
}

#if defined(RGB_THEME_ENABLE)
void set_rgb_theme(uint8_t index) {
    if (!user_config.rgb_layer_change) {
        user_config.rgb_layer_change = true;
    }
    user_config.rgb_theme = index;
    eeconfig_update_user(user_config.raw);
}

rgb_theme_t get_rgb_theme(void) {
    return *themes[user_config.rgb_theme];
}

void rgb_theme_step(void) {
    uint8_t current = user_config.rgb_theme;
    current = (current + 1) % rgb_theme_max;
    set_rgb_theme(current);
}

void rgb_theme_step_reverse(void) {
    uint8_t current = user_config.rgb_theme;
    current = (current - 1) % rgb_theme_max;
    set_rgb_theme(current);
}

HSV get_rgb_theme_color(uint8_t index) {
    rgb_theme_t theme = get_rgb_theme();
    size_t rgb_theme_color_max = sizeof theme.colors / sizeof *theme.colors;

    if (index == _ADJUST) {
        return default_adjust;
    } else {
        return **(theme.colors + (index % rgb_theme_color_max));
    }
};

void rgb_theme_layer(layer_state_t state) {
    uint8_t rgb_color_index = get_highest_layer(state);
    HSV color = get_rgb_theme_color(rgb_color_index);
#if defined(RGBLIGHT_ENABLE)
    color.v = rgblight_config.val;
#elif defined(RGB_MATRIX_ENABLE)
    color.v = rgb_matrix_config.hsv.v;
#endif
    rgb_layer_helper( color.h, color.s, color.v );
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}

void rgb_matrix_cycle_flag (void) {
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL:
            rgb_matrix_set_flags(LED_FLAG_KEYS);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_KEYS:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        default:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
    }
}
#endif

void rgb_layer_helper(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    rgblight_sethsv_noeeprom(hue, sat, val);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_layer_helper(0, 0, 0, rgb_matrix_get_flags());
#endif
}
#endif

layer_state_t layer_state_set_rgb(layer_state_t state) {
#if defined(RGB_THEME_ENABLE)
    if (user_config.rgb_layer_change) {
        rgb_theme_layer(state);
    }
#endif // RGBLIGHT_ENABLE
    return state;
}
