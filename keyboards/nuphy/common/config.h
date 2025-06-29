#include <stdint.h>

#ifndef DEFAULT_SLEEP_TOGGLE
#    define DEFAULT_SLEEP_TOGGLE 1
#endif

#ifndef DEFAULT_USB_SLEEP_TOGGLE
#    define DEFAULT_USB_SLEEP_TOGGLE 1
#endif

#ifndef DEFAULT_DEEP_SLEEP_TOGGLE
#    define DEFAULT_DEEP_SLEEP_TOGGLE 1
#endif

#ifndef DEFAULT_SLEEP_TIMEOUT
#    define DEFAULT_SLEEP_TIMEOUT 15
#endif

#ifndef PRESS_DEBOUNCE
#    define PRESS_DEBOUNCE (DEBOUNCE)
#endif

#ifndef RELEASE_DEBOUNCE
#    define RELEASE_DEBOUNCE (DEBOUNCE)
#endif

#ifndef DEFAULT_CAPS_INDICATOR_TYPE
#    define DEFAULT_CAPS_INDICATOR_TYPE CAPS_INDICATOR_BOTH
#endif

#ifndef DEFAULT_EFFECT_MODE
#    define DEFAULT_EFFECT_MODE SIDE_WAVE
#endif

#ifndef DEFAULT_EFFECT_BRIGHTNESS
#    define DEFAULT_EFFECT_BRIGHTNESS 4
#endif

#ifndef DEFAULT_EFFECT_SPEED
#    define DEFAULT_EFFECT_SPEED 2
#endif

#ifndef DEFAULT_EFFECT_RGB
#    define DEFAULT_EFFECT_RGB 1
#endif

#ifndef DEFAULT_EFFECT_COLOR
#    define DEFAULT_EFFECT_COLOR 6 //  FIXME: what is this value?
#endif

#ifndef DEFAULT_AMBIENT_MODE
#    define DEFAULT_AMBIENT_MODE EFFECT_WAVE
#endif

#ifndef DEFAULT_AMBIENT_BRIGHTNESS
#    define DEFAULT_AMBIENT_BRIGHTNESS 4
#endif

#ifndef DEFAULT_AMBIENT_SPEED
#    define DEFAULT_AMBIENT_SPEED 2
#endif

#ifndef DEFAULT_AMBIENT_RGB
#    define DEFAULT_AMBIENT_RGB 1
#endif

#ifndef DEFAULT_AMBIENT_COLOR
#    define DEFAULT_AMBIENT_COLOR 6 //  FIXME: what? is this value?
#endif

typedef struct {
    uint8_t sleep_toggle : 1;
    uint8_t usb_sleep_toggle : 1;
    uint8_t deep_sleep_toggle : 1;
    uint8_t debounce_press_ms;
    uint8_t debounce_release_ms;
    uint8_t sleep_timeout;
    uint8_t caps_indicator_type;
} common_config_t;

typedef struct {
    uint8_t toggle_custom_keys_highlight : 1;
    uint8_t detect_numlock_state : 1;
    uint8_t battery_indicator_numeric : 1;
    uint8_t show_socd_indicator : 1;
    uint8_t battery_indicator_brightness;
} custom_config_t;

typedef struct {
    // (top) side light config
    uint8_t side_mode;
    uint8_t side_brightness;
    uint8_t side_speed;
    uint8_t side_rgb;
    uint8_t side_color;

    // ambient light config
    uint8_t ambient_mode;
    uint8_t ambient_brightness;
    uint8_t ambient_speed;
    uint8_t ambient_rgb;
    uint8_t ambient_color;
} lights_config_t;

typedef struct {
    uint8_t been_initiated;
    common_config_t common;
    custom_config_t custom;
    lights_config_t lights;
} keyboard_config_t;

keyboard_config_t keyboard_config;

enum via_common_ids {
    id_usb_sleep_toggle    = 0,
    id_debounce_press      = 1,
    id_debounce_release    = 2,
    id_sleep_timeout       = 3,
    id_caps_indicator_type = 4,
    id_sleep_toggle        = 5,
    id_deep_sleep_toggle   = 6,
};

enum via_custom_ids {
    // side brightness controls
    id_battery_indicator_brightness = 31,
    id_toggle_custom_keys_highlight = 32,
    id_toggle_detect_numlock_state  = 33,
    id_battery_indicator_numeric    = 34,
    id_toggle_socd_indicator        = 35
};

enum via_non_matrix_lights_ids {
    // side light controls
    id_side_light_mode       = 10,
    id_side_light_speed      = 11,
    id_side_light_color      = 12,
    id_side_light_brightness = 13,
    // ambient light controls
    id_ambient_light_mode       = 20,
    id_ambient_light_speed      = 21,
    id_ambient_light_color      = 22,
    id_ambient_light_brightness = 23,
};

enum work_mode {
    WIRED    = 0,
    WIRELESS = 1,
};

typedef enum {
    CAPS_INDICATOR_SIDE = 0,
    CAPS_INDICATOR_UNDER_KEY,
    CAPS_INDICATOR_BOTH,
    CAPS_INDICATOR_OFF,
} CAPS_LOCK_INDICATION;

enum NonMatrixEffects {
    EFFECT_WAVE = 0,
    EFFECT_MIX,
    EFFECT_STATIC,
    EFFECT_BREATH,
    EFFECT_OFF,
} non_matrix_effects;

void custom_eeprom_init(void);
void init_keyboard_config(void);
void save_config_to_eeprom(void);
void load_config_from_eeprom(void);
