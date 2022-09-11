/*
Copyright 2021 gregorio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rubi.h"

void change_encoder_mode(bool reverse) {
    if (reverse) {
        if (encoder_mode == 0) {
            encoder_mode = _NUM_ENCODER_MODES - 1;
        } else {
            encoder_mode = encoder_mode - 1;
        }
    } else {
        encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
    }
}

uint16_t handle_encoder_cw(void) {
    uint16_t mapped_code = 0;

    if (oled_mode == OLED_MODE_CALC) {
        layer_on(2);
        return mapped_code;
    }

    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            mapped_code = KC_VOLU;
            break;
        case ENC_MODE_MEDIA:
            mapped_code = KC_MEDIA_NEXT_TRACK;
            break;
        case ENC_MODE_BRIGHTNESS:
            mapped_code = KC_BRIGHTNESS_UP;
            break;
    }

    return mapped_code;
}

uint16_t handle_encoder_ccw(void) {
    uint16_t mapped_code = 0;

    if (oled_mode == OLED_MODE_CALC) {
        layer_off(2);
        return mapped_code;
    }

    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            mapped_code = KC_VOLD;
            break;
        case ENC_MODE_MEDIA:
            mapped_code = KC_MEDIA_PREV_TRACK;
            break;
        case ENC_MODE_BRIGHTNESS:
            mapped_code = KC_BRIGHTNESS_DOWN;
            break;
    }

    return mapped_code;
}

uint16_t handle_encoder_press(void) {
    uint16_t mapped_code = 0;
    if (get_highest_layer(layer_state) == 1) {
        if (oled_mode == OLED_MODE_CALC) {
            layer_on(3);
        }
        layer_off(1);
        return mapped_code;
    } else if (get_highest_layer(layer_state) == 2) {
        if (oled_mode == OLED_MODE_CALC) {
            layer_off(1);
            layer_on(3);
        } else {
            layer_on(1);
        }
        layer_off(2);
        return mapped_code;
    } else if (get_highest_layer(layer_state) == 3) {
        if (oled_mode == OLED_MODE_OFF) {
            layer_off(3);
        }
        return mapped_code;
    }

    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            mapped_code = KC_MUTE;
            break;
        case ENC_MODE_MEDIA:
            mapped_code = KC_MEDIA_PLAY_PAUSE;
            break;
    }

    return mapped_code;
}
