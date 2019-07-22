#include "custom_oled.h"
#include "process_records.h"

#include <stdio.h>

#ifdef OLED_DRIVER_ENABLE

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

#if defined(OLED_90ROTATION)

// TODO: Need to define this function / extern only for helix based split common keyboards
extern uint8_t is_master;
bool is_keyboard_master(void)
{
    return is_master;
}

static void render_layer(uint8_t layer)
{
    switch (layer)
    {
        case _QWERTY:
            oled_write_P(PSTR("DFLT "), false);
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

static void render_status(void)
{
    // Render to mode icon
    static const char PROGMEM mode_logo[2][4] = {
        {0x97,0x98,0x0a,0},
        {0xb7,0xb8,0x0a,0} };

    oled_write_P(mode_logo[0], false);
    oled_write_P(mode_logo[1], false);

    oled_write_P(PSTR("Layer"), false);
    uint8_t layer = biton(layer_state);
    if (layer != _QWERTY)
        render_layer(layer);
    else
        render_layer(biton32(default_layer_state));

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("-----NUMLK") : PSTR("-----     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false);

#if defined(RGB_MATRIX_ENABLE)
    oled_set_cursor(0, oled_max_lines() - 7);
    oled_write_P(PSTR("-----"), false);
    static char buffer[26] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d\n", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode);
    oled_write(buffer, false);
#elif defined(RGBLIGHT_ENABLE)
    oled_set_cursor(0, oled_max_lines() - 7);
    oled_write_P(PSTR("-----"), false);
    static char buffer[31] = {0};
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val, rgblight_config.speed, rgblight_config.mode);
    oled_write(buffer, false);
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  return OLED_ROTATION_180;
}

#else  // OLED_90ROTATION

static void render_layer(uint8_t layer)
{
    switch (layer)
    {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
#ifndef GAMELAYER_DISABLE
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            break;
#endif
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
#ifdef TRILAYER_ENABLED
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
#endif
    }
}

static void render_status(void)
{
    // Render to mode icon
    static const char PROGMEM mode_logo[2][3] = {
        {0x97,0x98,0},
        {0xb7,0xb8,0}
    };

    oled_write_P(mode_logo[0], false);

#if defined(RGB_MATRIX_ENABLE)
    static char buffer[20] = {0};
    snprintf(buffer, sizeof(buffer), "    h%3d s%3d v%3d\n", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
    oled_write(buffer, false);
#elif defined(RGBLIGHT_ENABLE)
    static char buffer[20] = {0};
    snprintf(buffer, sizeof(buffer), "    h%3d s%3d v%3d\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
    oled_write(buffer, false);
#else
    oled_write_P(PSTR("\n"));
#endif

    oled_write_P(mode_logo[1], false);

#if defined(RGB_MATRIX_ENABLE)
    snprintf(buffer, sizeof(buffer), "         s%3d m%3d\n", rgb_matrix_config.speed, rgb_matrix_config.mode);
    oled_write(buffer, false);
#elif defined(RGBLIGHT_ENABLE)
    snprintf(buffer, sizeof(buffer), "         s%3d m%3d\n", rgblight_config.speed, rgblight_config.mode);
    oled_write(buffer, false);
#else
    oled_write_P(PSTR("\n"));
#endif

    // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    oled_write_P(PSTR("Layer: "), false);
    uint8_t layer = biton(layer_state);
    if (layer != _QWERTY)
        render_layer(layer);
    else
        render_layer(biton32(default_layer_state));

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
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

#endif
