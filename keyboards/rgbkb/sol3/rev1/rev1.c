/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "rev1.h"
#include "split_util.h"

#define NUMBER_OF_TOUCH_ENCODERS 2
#define TOUCH_ENCODER_OPTIONS TOUCH_SEGMENTS + 2

#define NUMBER_OF_ENCODERS 6
#define ENCODER_OPTIONS 2

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

// this maps encoders and then touch encoders to their respective electrical matrix entry
// mapping is row (y) then column (x) when looking at the electrical layout
const encodermap_t encoder_map[NUMBER_OF_ENCODERS][ENCODER_OPTIONS] = 
{
    { {  5, 0 }, {  5, 1 } }, // Encoder 0 matrix entries
    { {  5, 2 }, {  5, 3 } }, // Encoder 1 matrix entries
    { {  5, 4 }, {  5, 5 } }, // Encoder 2 matrix entries
    { { 11, 0 }, { 11, 1 } }, // Encoder 3 matrix entries
    { { 11, 2 }, { 11, 3 } }, // Encoder 4 matrix entries
    { { 11, 4 }, { 11, 5 } }  // Encoder 5 matrix entries
};

const encodermap_t touch_encoder_map[NUMBER_OF_TOUCH_ENCODERS][TOUCH_ENCODER_OPTIONS] = 
{
    { { 1, 7 }, { 0, 7 }, { 2, 7 }, {  5, 6 }, {  5, 7 }, }, // Touch Encoder 0 matrix entries
    { { 7, 7 }, { 6, 7 }, { 8, 7 }, { 11, 6 }, { 11, 7 }, }  // Touch Encoder 1 matrix entries
};

static bool limit_lightning = true;

RGB rgb_matrix_hsv_to_rgb(HSV hsv) {
    if (limit_lightning) hsv.v /= 2;
    return hsv_to_rgb(hsv); 
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active))
        return false;

    switch(index) {
        case 0: {
            limit_lightning = active;
            break;
        }
        case 1: {
            // Handle RGB Encoder switch press
            action_exec(MAKE_KEYEVENT(isLeftHand ? 4 : 10, 6, active));
            break;
        }
    }
    return false;
}

static void process_encoder_matrix(encodermap_t pos) {
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, true));
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, false));
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_update_kb(uint8_t index, bool clockwise) {
    if (!touch_encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(touch_encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) {
    if (!touch_encoder_tapped_user(index, section))
        return false;

    process_encoder_matrix(touch_encoder_map[index][section + 2]);
    return false;
}

void matrix_slave_scan_kb(void) {
    dip_switch_read(false);
    matrix_slave_scan_user();
}

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  41,  42,  43,  44,  45,  46,  47, NO_LED },
    {  54,  53,  52,  51,  50,  49,  48, NO_LED },
    {  55,  56,  57,  58,  59,  60,  61, NO_LED },
    {  68,  67,  66,  65,  64,  63,  62, NO_LED },
    {  69,  70,  71,  72,  73,  74,  75,  76 },
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { 119, 120, 121, 122, 123, 124, 125, NO_LED  },
    { 132, 131, 130, 129, 128, 127, 126, NO_LED  },
    { 133, 134, 135, 136, 137, 138, 139, NO_LED  },
    { 146, 145, 144, 143, 142, 141, 140, NO_LED  },
    { 147, 148, 149, 150, 151, 152, 153, 154 },
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, { // ALL XY VALUES DIVIDE BY 2, THEN ADD 5
    {   1,   6 }, {   1,  13 }, {   1,  19 }, {   1,  25 }, {   1,  31 }, {   1,  37 }, {   1,  43 }, {   1,  49 }, {   4,  52 }, {  11,  52 },
    {  17,  52 }, {  23,  52 }, {  29,  52 }, {  35,  52 }, {  41,  54 }, {  46,  57 }, {  52,  60 }, {  57,  63 }, {  62,  66 }, {  68,  69 },
    {  73,  67 }, {  76,  62 }, {  79,  57 }, {  78,  51 }, {  77,  45 }, {  76,  39 }, {  76,  33 }, {  76,  27 }, {  76,  21 }, {  76,  14 },
    {  76,   8 }, {  72,   3 }, {  59,   3 }, {  53,   3 }, {  46,   3 }, {  40,   3 }, {  34,   3 }, {  28,   3 }, {  22,   3 }, {  10,   3 }, {   3,   3 },
    {   9,   6 }, {  21,   6 }, {  30,   6 }, {  40,   6 }, {  49,   6 }, {  59,   6 }, {  71,   6 },
    {  71,  16 }, {  59,  16 }, {  49,  16 }, {  40,  16 }, {  30,  16 }, {  21,  16 }, {   9,  16 },
    {   9,  25 }, {  21,  25 }, {  30,  25 }, {  40,  25 }, {  49,  25 }, {  59,  25 }, {  71,  25 },
    {  71,  35 }, {  59,  35 }, {  49,  35 }, {  40,  35 }, {  30,  35 }, {  21,  35 }, {   9,  35 },
    {   9,  44 }, {  21,  44 }, {  30,  44 }, {  40,  44 }, {  49,  44 }, {  66,  50 }, {  75,  54 }, {  70,  62 }, {  60,  60 },

    { 160,   6 }, { 160,  13 }, { 160,  19 }, { 160,  25 }, { 160,  31 }, { 160,  37 }, { 160,  43 }, { 160,  49 }, { 157,  52 }, { 151,  52 },
    { 145,  52 }, { 138,  52 }, { 132,  52 }, { 126,  52 }, { 120,  54 }, { 115,  57 }, { 110,  60 }, { 105,  63 }, {  99,  66 }, {  94,  69 },
    {  89,  67 }, {  86,  62 }, {  83,  57 }, {  83,  51 }, {  85,  45 }, {  86,  39 }, {  86,  33 }, {  86,  27 }, {  86,  21 }, {  86,  14 },
    {  86,   8 }, {  90,   3 }, { 103,   3 }, { 109,   3 }, { 115,   3 }, { 121,   3 }, { 127,   3 }, { 133,   3 }, { 140,   3 }, { 152,   3 }, { 158,   3 },
    { 153,   6 }, { 141,   6 }, { 131,   6 }, { 122,   6 }, { 112,   6 }, { 103,   6 }, {  91,   6 },
    {  91,  16 }, { 103,  16 }, { 112,  16 }, { 122,  16 }, { 131,  16 }, { 141,  16 }, { 153,  16 },
    { 153,  25 }, { 141,  25 }, { 131,  25 }, { 122,  25 }, { 112,  25 }, { 103,  25 }, {  91,  25 },
    {  91,  35 }, { 103,  35 }, { 112,  35 }, { 122,  35 }, { 131,  35 }, { 141,  35 }, { 153,  35 },
    { 153,  44 }, { 141,  44 }, { 131,  44 }, { 122,  44 }, { 112,  44 }, {  96,  50 }, {  87,  54 }, {  92,  62 }, { 102,  60 },
}, {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1
} };
// clang-format on

void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif


__attribute__((weak)) 
void render_layer_status(void) {
    // Keymap specific, expected to be overridden
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    oled_write_ln_P(PSTR("Undef"), false);
}

__attribute__((weak))
void render_leds_status(void)
{
    // Host Keyboard LED Status
    static const char PROGMEM led_icon[] = {
        0x0F,0x3A,0
    };
    oled_write_P(led_icon, false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(   led_state.num_lock ? PSTR("N") : PSTR(" "), false);
    oled_write_P(  led_state.caps_lock ? PSTR("C") : PSTR(" "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

__attribute__((weak))
void render_touch_status(void)
{
    // Host Touch LED Status
    static const char PROGMEM touch_icon[] = {
        0x12,0x3A,0
    };
    oled_write_P(touch_icon, false);
    oled_write_P(         touch_encoder_is_on() ? PSTR("T") : PSTR(" "), false);
    oled_write_P(touch_encoder_is_calibrating() ? PSTR("C") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
}

__attribute__((weak))
void render_audio_status(void)
{
    // Host Audio Status
    static const char PROGMEM audio_icon[] = {
        0x0E,0x3A,0
    };
    oled_write_P(audio_icon, false);
    oled_write_P( audio_is_on() ? PSTR("A")  : PSTR(" "), false);
    oled_write_P(is_clicky_on() ? PSTR("C")  : PSTR(" "), false);
    oled_write_P( is_music_on() ? PSTR("M")  : PSTR(" "), false);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // Sol 3 uses OLED_ROTATION_270 for default rotation on both halves
    return oled_init_user(OLED_ROTATION_270);
}

bool oled_task_kb(void) {
    if (!oled_task_user())
        return false;
    
    if (is_keyboard_left()) {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_layer_status();
        oled_write_P(PSTR("     "), false);
        render_leds_status();
        oled_write_P(PSTR("     "), false);
        render_touch_status();
        oled_write_P(PSTR("     "), false);
        render_audio_status();
    }
    else {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_rgb_menu();
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record))
        return false;

    switch(keycode) {
#ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_increase_flags();
            }
            return false;
#endif
    }
    return true;
};
