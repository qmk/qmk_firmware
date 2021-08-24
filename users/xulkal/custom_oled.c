#include "custom_oled.h"
#include "process_records.h"

#include <stdio.h>

#ifdef RGBLIGHT_ENABLE
rgblight_config_t rgblight_config;
#endif

static void render_logo(void)
{
    static const char PROGMEM font_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    oled_write_P(font_logo, false);
}

static void render_icon(void)
{
#ifdef OLED_90ROTATION
    static const char PROGMEM font_icon[] = {
        0x9b,0x9c,0x9d,0x9e,0x9f,
        0xbb,0xbc,0xbd,0xbe,0xbf,
        0xdb,0xdc,0xdd,0xde,0xdf,0
    };
#else
    static const char PROGMEM font_icon[] = {
        // Use \r (0x0d) to jump to the next line without clearing the rest of the current line
        0x9b,0x9c,0x9d,0x9e,0x9f,0x0d,
        0xbb,0xbc,0xbd,0xbe,0xbf,0x0d,
        0xdb,0xdc,0xdd,0xde,0xdf,0
    };
#endif
    oled_write_P(font_icon, false);
}

static void render_layer(void)
{
    uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state);
#ifdef OLED_90ROTATION
    oled_write_P(PSTR("Layer"), false);
#else
    oled_write_P(PSTR("Layer: "), false);
#endif

    switch (layer)
    {
        case _QWERTY:
            oled_write_P(PSTR("BASE "), false);
            break;
#ifndef GAMELAYER_DISABLE
        case _GAME:
            oled_write_P(PSTR("GAME "), false);
            break;
#endif
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
#ifdef TRILAYER_ENABLED
        case _ADJUST:
            oled_write_P(PSTR("ADJST"), false);
            break;
#endif
    }
}

static void render_keyboard_leds(void)
{
    // Host Keyboard LED Status
    uint8_t led_state = host_keyboard_leds();
#ifdef OLED_90ROTATION
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false);
#else
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRL") : PSTR("    "), false);
#endif
}

#ifdef RGB_OLED_MENU
extern uint8_t rgb_encoder_state;
#endif

#if defined(OLED_90ROTATION)

#ifdef RGB_ENABLE
static void render_rgb_state(void)
{
    // TODO: need to do a bit more handling here for horizontal rendering
#if defined(RGB_MATRIX_ENABLE)
    static char buffer[31] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d e%3d ", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_get_flags());
#elif defined(RGBLIGHT_ENABLE)
    static char buffer[26] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d ", rgblight_config.hue, rgblight_config.sat, rgblight_config.val, rgblight_config.speed, rgblight_config.mode);
#endif

#ifdef RGB_OLED_MENU
    buffer[4 + rgb_encoder_state * 5] = '<';
#endif
    oled_write(buffer, false);
}
#endif

static void render_status(void)
{
    render_icon();
    render_layer();

    // Host Keyboard LED Status
    oled_write_P(PSTR("-----"), false);
    render_keyboard_leds();

    oled_write_P(PSTR("-----"), false);
#ifdef RGB_ENABLE
    render_rgb_state();
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#if KEYBOARD_helix_rev2
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  return rotation;
#else
  if (is_keyboard_master())
    return OLED_ROTATION_90;
  return rotation;
#endif
}

#else  // OLED_90ROTATION

#ifdef RGB_ENABLE
static void render_rgb_state(void)
{
    // TODO: need to do a bit more handling here for horizontal rendering
#if defined(RGB_MATRIX_ENABLE)
    static char buffer[37] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d       s%3d m%3d e%3d ", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_get_flags());
#elif defined(RGBLIGHT_ENABLE)
    static char buffer[32] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d       s%3d m%3d ", rgblight_config.hue, rgblight_config.sat, rgblight_config.val, rgblight_config.speed, rgblight_config.mode);
#endif

#ifdef RGB_OLED_MENU
    buffer[4 + rgb_encoder_state * 5] = '<';
#endif
    oled_write(buffer, false);
}
#endif

static void render_status(void)
{
    render_icon();

    // Host Layer Status
    oled_set_cursor(6, 0);
    render_layer();

    // Host Keyboard LED Status
    oled_set_cursor(6, 1);
    render_keyboard_leds();

#ifdef RGB_ENABLE
    oled_set_cursor(6, 2);
    render_rgb_state();
#endif
}

#endif // OLED_90ROTATION

void oled_task_user(void)
{
    if (is_keyboard_master())
        render_status();
    else
    {
        render_logo();
        oled_scroll_left();
    }
}
