#ifndef RAW_ENABLE
#    error this file requires RAW_ENABLE
#endif

#include "quantum.h"
#include "rhruiz.h"
#include "api.h"
#include "raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *command_id   = &(data[0]);
    uint8_t *command_data = &(data[1]);

    switch (*command_id) {
        case id_get_keyboard_value: {
            if (command_data[0] == id_uptime) {
                uint32_t value  = timer_read32();
                command_data[1] = (value >> 24) & 0xFF;
                command_data[2] = (value >> 16) & 0xFF;
                command_data[3] = (value >> 8) & 0xFF;
                command_data[4] = value & 0xFF;
            } else {
                *command_id = id_unhandled;
            }
            break;
        }

        case id_bootloader_jump: {
            raw_hid_send(data, length);
            wait_ms(100);
            bootloader_jump();
            break;
        }

        case id_rgblight_color: {
#ifdef RGBLIGHT_ENABLE
            uint16_t hue = ((uint16_t)command_data[0] << 8) | command_data[1];
            uint8_t  sat = command_data[2];
            rhruiz_change_leds_to(hue, sat);
#endif
            break;
        }

        case id_rgblight_reset: {
#ifdef RGBLIGHT_ENABLE
            rhruiz_rgblight_reset();
#endif
            break;
        }

        case id_backlight_toggle: {
#ifdef BACKLIGHT_ENABLE
            backlight_toggle();
#endif
            break;
        }

        case id_rgblight_toggle: {
#ifdef RGBLIGHT_ENABLE
            rgblight_toggle();
#endif
            break;
        }
    }

    raw_hid_send(data, length);
}
