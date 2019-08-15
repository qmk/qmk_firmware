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

static const HSV default_magic = { HSV_SPRINGGREEN };

static const HSV laser_purple =  { HSV_LSR_PURPLE };
static const HSV laser_pink =    { HSV_LSR_PINK };
static const HSV laser_blue =    { HSV_LSR_BLUE };
static const HSV laser_cyan =    { HSV_LSR_CYAN };
static const HSV laser_magenta = { HSV_LSR_MAGENTA };
static const rgb_theme_t rgb_laser = { LASER, { &laser_purple, &laser_pink, &laser_blue, &laser_cyan, &laser_magenta } };

static const HSV granite_white =  { HSV_GNT_WHITE };
static const HSV granite_blue =   { HSV_GNT_BLUE };
static const HSV granite_red =    { HSV_GNT_RED };
static const HSV granite_green =  { HSV_GNT_GREEN };
static const HSV granite_yellow = { HSV_GNT_YELLOW };
static const rgb_theme_t rgb_granite = { GRANITE, { &granite_white, &granite_blue, &granite_red, &granite_green, &granite_yellow } };

static const HSV oblique_white =  { HSV_OBQ_WHITE };
static const HSV oblique_purple = { HSV_OBQ_PURPLE };
static const HSV oblique_red =    { HSV_OBQ_RED };
static const HSV oblique_orange = { HSV_OBQ_ORANGE };
static const HSV oblique_green =  { HSV_OBQ_GREEN };
static const rgb_theme_t rgb_oblique = { OBLIQUE, { &oblique_white, &oblique_purple, &oblique_red, &oblique_orange, &oblique_green } };

static const rgb_theme_t *themes[] = { &rgb_laser, &rgb_granite, &rgb_oblique };

void keyboard_post_init_rgb(void) {
    layer_state_set_user(layer_state);
#if defined(RGBLIGHT_ENABLE)
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
}

void set_rgb_theme(rgb_theme_name_t theme_name) {
    if (!user_config.rgb_layer_change) {
        user_config.rgb_layer_change = true;
    }
    user_config.rgb_theme = theme_name;
    eeconfig_update_user(user_config.raw);
}

rgb_theme_t get_rgb_theme(void) {
    return *themes[user_config.rgb_theme];
}

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
            rgb_matrix_set_flags(LED_FLAG_ALL_KEYS);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_ALL_KEYS:
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

HSV get_rgb_theme_color(uint8_t index) {
    rgb_theme_t theme = get_rgb_theme();
    size_t rgb_theme_color_max = sizeof theme.colors / sizeof *theme.colors;
    HSV color;

    if (index < rgb_theme_color_max) {
        color = *theme.colors[index];
    } else if (index == _MAGIC) {
        color = default_magic;
    } else {
#if defined(RGBLIGHT_ENABLE)
        rgblight_config.raw = eeconfig_read_rgblight();
        color = (HSV){ rgblight_config.hue, rgblight_config.sat, rgblight_config.val };
#elif defined(RGB_MATRIX_ENABLE)
        color = (HSV){ rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
#endif
    }
    return color;
};

void rgb_theme_layer(layer_state_t state) {
    uint8_t rgb_color_index = biton32(state);
    HSV color = get_rgb_theme_color(rgb_color_index);

    // if (index < MAX) {
    //     color = *(rgb_theme.colors[index]);
    // } else if (rgb_color_index == _MAGIC) {
    //     color = { HSV_THEME_M };
    // }
    rgb_layer_helper( color.h, color.s, color.v );
//     switch (biton32(state)) {
// #ifndef IS_MACROPAD
//         case _MACFN:
//             rgb_layer_helper(HSV_THEME_1);
//             break;
// #else
//         case _REEDER:
//             rgb_layer_helper(HSV_THEME_1);
//             break;
//         case _MEDIA:
//             rgb_layer_helper(HSV_THEME_2);
//             break;
//         case _KEYPAD:
//             rgb_layer_helper(HSV_THEME_3);
//             break;
// #endif
//         case _MAGIC:
//             rgb_layer_helper(HSV_THEME_M);
//             break;
//         default:
//             switch (biton32(default_layer_state)) {
//     #ifndef IS_MACROPAD
//                 case _MAC:
//                     rgb_layer_helper(HSV_THEME_0);
//                     break;
//     #else
//                 case _NAVI:
//                     rgb_layer_helper(HSV_THEME_0);
//                     break;
//     #endif
//             }
//             break;
//     }
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
    #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
//     switch (biton32(state)) {
// #ifndef IS_MACROPAD
//         case _MACFN:
//             rgb_layer_helper(HSV_THEME_1);
//             break;
// #else
//         case _REEDER:
//             rgb_layer_helper(HSV_THEME_1);
//             break;
//         case _MEDIA:
//             rgb_layer_helper(HSV_THEME_2);
//             break;
//         case _KEYPAD:
//             rgb_layer_helper(HSV_THEME_3);
//             break;
// #endif
//         case _MAGIC:
//             rgb_layer_helper(HSV_THEME_M);
//             break;
//         default:
//             switch (biton32(default_layer_state)) {
//     #ifndef IS_MACROPAD
//                 case _MAC:
//                     rgb_layer_helper(HSV_THEME_0);
//                     break;
//     #else
//                 case _NAVI:
//                     rgb_layer_helper(HSV_THEME_0);
//                     break;
//     #endif
//             }
//             break;
//     }
    rgb_theme_layer(state);
#endif // RGBLIGHT_ENABLE
    return state;
}
