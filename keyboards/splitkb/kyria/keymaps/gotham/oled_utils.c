#include "oled_utils.h"

  void render_qmk_logo(void) {
      static const char PROGMEM qmk_logo[] = {
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
          0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
          0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
      };

      oled_write_P(qmk_logo, false);
  }

void render_layer(void) {
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
void render_encoder(encoder_mode_t mode) {
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
void render_thumbstick(thumbstick_mode_t mode) {
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

void render_status(void) {
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
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // QMK Logo and version information
        render_qmk_logo();
        oled_write_P(PSTR("\n      Kyria v1.0\n"), false);
    }
}
