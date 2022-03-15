/*
Copyright 2020 Sekigon

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

#include <stdbool.h>
#include <stdint.h>

#include "action_layer.h"
#include "bmp.h"
#include "bmp_encoder_actions.h"
#include "bmp_config.h"

#include "quantum.h"

typedef struct {
    uint16_t action;
    uint8_t mods;
    uint8_t active_count;
} encoder_status_t;

static encoder_status_t
    current_status[sizeof(bmp_encoder_config_t) / sizeof(bmp_encoder_t)];

static uint16_t get_action(int8_t index, bool clockwise) {
    uint32_t                    layer          = biton32(layer_state);
    const bmp_encoder_config_t* encoder_config = get_bmp_encoder_config();

    if (encoder_config->encoder[index].action[0][0] == KC_TRNS) {
        uint8_t position =
            encoder_config->encoder[index].action[1][clockwise ? 1 : 0];
        if (position > 0) {
            position--;
        }
        const bmp_api_config_t* config = BMPAPI->app.get_config();
        const uint8_t           row    = position / config->matrix.cols;
        const uint8_t           col    = position % config->matrix.cols;
        return keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col});
    }

    if (layer > sizeof(encoder_config->encoder->action) /
                    sizeof(encoder_config->encoder->action[0])) {
        layer = 0;
    }

    return get_bmp_encoder_config()->encoder[index].action[layer]
                                                          [clockwise ? 1 : 0];
}

void encoder_update_bmp(int8_t index, bool clockwise) {
    if (!encoder_update_kb(index, clockwise)) {
        return;
    }

    uint16_t action = get_action(index, clockwise);

    if (action != current_status[index].action) {
        // delete mods, but not send at here
        del_mods(current_status[index].mods);
        current_status[index].mods = 0;
    }

    current_status[index].action       = action;
    current_status[index].active_count = 30;

    dprintf("<encoder>idx:%2d, act:%3d, rot:%c\n", index, action,
            clockwise ? 'R' : 'L');

    if (action <= QK_MODS_MAX) {
        uint8_t kc                 = action & 0xFF;
        current_status[index].mods = (action & 0x1F00) >> 8;

        register_mods(current_status[index].mods);
        tap_code16(kc);
    } else {
        keyevent_t event = {.key  = {.col = 255, .row = 255},
                            .time = (timer_read() | 1)};
        tap_code_ex(action, event);
    }
}

void encoder_key_interrupt_bmp(int8_t index) {
    if (current_status[index].action < SAFE_RANGE) {
        unregister_mods(current_status[index].mods);
        current_status[index].action       = KC_NO;
        current_status[index].mods         = 0;
        current_status[index].active_count = 0;
    } else {
        encoder_key_interrupt_kb(index);
    }
}

void encoder_no_move_bmp(int8_t index) {
    if (current_status[index].active_count > 0 &&
        --current_status[index].active_count == 0) {
        if (current_status[index].action < SAFE_RANGE) {
            unregister_mods(current_status[index].mods);
            current_status[index].action = KC_NO;
            current_status[index].mods   = 0;
        } else {
            encoder_no_move_kb(index);
        }
    }
}
