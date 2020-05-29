#pragma once

#include "keycodes.h"

#ifdef ENCODER_ENABLE
#    include "encoder.c"
#endif

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 192, 224, 240, 112, 120, 56,  60,  28, 30, 14, 14, 14, 7,  7,   7,   7,   7,  7, 7,   7,   7, 7,  7,   7,   7,   7,  7,  7,  14, 14, 14,  30,  28,  60,  56,  120, 112, 240, 224, 192, 128, 128, 0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   192, 224, 240, 124, 62,  31,  15,  7,   3,   1,   128, 192, 224, 240, 120, 56,  60, 28, 30, 14, 14, 7,   7,   135, 231, 127, 31,  255, 255, 31,  127, 231, 135, 7,  7,  14,
                                              14, 30, 28,  60,  56,  120, 240, 224, 192, 128, 1,   3,   7,   15,  31,  62,  124, 240, 224, 192, 0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   240, 252, 255, 31,  7,   1,  0,   0,   192, 240, 252, 254, 255, 247, 243, 177, 176, 48,  48,  48,  48,  48,  48,  48,  120, 254, 135, 1,   0,   0,   255, 255, 0,   0,   1,   135, 254, 120, 48,  48,  48, 48, 48,  48,  48,  176, 177, 243, 247, 255, 254, 252, 240, 192, 0,   0,   1,   7,   31,  255, 252, 240, 0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                              0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   254, 255, 255, 1,   1,   7,  30, 120, 225, 129, 131, 131, 134, 134, 140, 140, 152, 152, 177, 183, 254, 248, 224, 255, 255, 224, 248, 254, 183, 177, 152, 152, 140, 140, 134, 134, 131, 131, 129, 225, 120, 30, 7,   1,   1,   255, 255, 254, 0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   255, 255, 0,   0,   192, 192, 48,  48,  0,   0,   240, 240, 0,   0,   0,   0,   0,  0,  240, 240, 0,   0,   240, 240, 192, 192, 48,  48,  48,  48,  192, 192, 0,   0,   48,  48,  243, 243, 0,  0,  0,  0,  0,  0,   48,  48,  48,  48,  48,  48,  192, 192, 0,   0,   0,   0,  0,  0,
                                              0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   127, 255, 255, 128, 128, 224, 120, 30,  135, 129, 193, 193, 97, 97, 49, 49, 25, 25, 141, 237, 127, 31, 7, 255, 255, 7, 31, 127, 237, 141, 25, 25, 49, 49, 97, 97,  193, 193, 129, 135, 30,  120, 224, 128, 128, 255, 255, 127, 0,  0,  0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   63,  63,  3,   3,   12,  12,  48,  48,  0,   0,   0,   0,   51,  51,  51,  51,  51,  51,  15,  15,  0,   0,   63,  63,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  48,  63,  63,  48,  48,  0,   0,   12,  12,  51,  51,  51,  51,  51,  51,  63,  63,  0,   0,   0,   0,   0,   0,   0,   0,  0,  15,  63,  255, 248, 224, 128, 0,   0,   3,   15,  63,  127, 255, 239, 207, 141, 13,  12,  12,  12,  12, 12, 12, 12, 30, 127, 225, 128, 0,   0,   255, 255, 0,   0,   128, 225, 127, 30, 12, 12,
                                              12, 12, 12,  12,  12,  13,  141, 207, 239, 255, 127, 63,  15,  3,   0,   0,   128, 224, 248, 255, 63,  15,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   7,   15,  62, 124, 248, 240, 224, 192, 128, 1,   3,   7,   15,  30,  28,  60,  56,  120, 112, 112, 224, 224, 225, 231, 254, 248, 255, 255, 248, 254, 231, 225, 224, 224, 112, 112, 120, 56, 60, 28,  30,  15,  7,   3,   1,   128, 192, 224, 240, 248, 124, 62,  15,  7,   3,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                              0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   3,   7,   15, 14, 30,  28,  60,  56,  120, 112, 112, 112, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 112, 112, 112, 120, 56,  60,  28,  30,  14,  15,  7,  3,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_layer(void) {
    oled_write_P(PSTR("\nLayer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}

#ifdef ENCODER_ENABLE
static void render_encoder(encoder_mode_t mode) {
    switch (mode) {
        case ENC_MODE_VOLUME:
            oled_write_P(PSTR("Volume\n"), false);
            break;
        case ENC_MODE_WORD_NAV:
            oled_write_P(PSTR("Word Nav\n"), false);
            break;
        case ENC_MODE_LEFT_RIGHT:
            oled_write_P(PSTR("Left / Right\n"), false);
            break;
        case ENC_MODE_UP_DOWN:
            oled_write_P(PSTR("Up / Down\n"), false);
            break;
        case ENC_MODE_PAGING:
            oled_write_P(PSTR("PgUp / PgDwn\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}
#endif

#ifdef THUMBSTICK_ENABLE
static void render_thumbstick(thumbstick_mode_t mode) {
    switch (mode) {
        case THUMBSTICK_MODE_MOUSE:
            oled_write_P(PSTR("Mouse"), false);
            break;
        case THUMBSTICK_MODE_ARROWS:
            oled_write_P(PSTR("Arrows"), false);
            break;
        case THUMBSTICK_MODE_SCROLL:
            oled_write_P(PSTR("Scroll"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}
#endif

static void render_status(void) {
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        render_layer();
#ifdef ENCODER_ENABLE
        // Encoder state
        oled_write_P(PSTR("L-Enc: "), false);
        render_encoder(encoder_left_mode);
        oled_write_P(PSTR("R-Enc: "), false);
        render_encoder(encoder_right_mode);
#endif
#ifdef THUMBSTICK_ENABLE
        if (!isLeftHand) {
            // Thumbstick state
            oled_write_P(PSTR("Joystick: "), false);
            render_thumbstick(thumbstick_state.config.mode);
        }
#endif
        // Host Keyboard LED Status
        uint8_t led_usb_state = host_keyboard_leds();
        oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // QMK Logo and version information
        render_kyria_logo();
    }
}
