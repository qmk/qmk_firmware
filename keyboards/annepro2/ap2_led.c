/* Copyright 2021 OpenAnnePro community
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdio.h>
#include "hal.h"
#include "annepro2.h"
#include "ap2_led.h"
#include "protocol.h"

ap2_led_t       led_mask[KEY_COUNT];
ap2_led_t       led_colors[KEY_COUNT];
ap2_led_status_t ap2_led_status;

void led_command_callback(const message_t *msg) {
    switch (msg->command) {
        case CMD_LED_STATUS:
            ap2_led_status.amount_of_profiles = msg->payload[0];
            ap2_led_status.current_profile    = msg->payload[1];
            ap2_led_status.matrix_enabled     = msg->payload[2];
            ap2_led_status.is_reactive        = msg->payload[3];
            ap2_led_status.led_intensity      = msg->payload[4];
            ap2_led_status.errors             = msg->payload[5];
            break;

#ifdef CONSOLE_ENABLE
        case CMD_LED_DEBUG:
            /* TODO: Don't use printf. */
            printf("LED:");
            for (int i = 0; i < msg->payload_size; i++) {
                printf("%02x ", msg->payload[i]);
            }
            for (int i = 0; i < msg->payload_size; i++) {
                printf("%c", msg->payload[i]);
            }
            printf("\n");
            break;
#endif
    }
}

void ap2_set_IAP(void) { proto_tx(CMD_LED_IAP, NULL, 0, 3); }

void ap2_led_disable(void) { proto_tx(CMD_LED_OFF, NULL, 0, 3); }

void ap2_led_enable(void) { proto_tx(CMD_LED_ON, NULL, 0, 3); }

void ap2_led_set_profile(uint8_t prof) { proto_tx(CMD_LED_SET_PROFILE, &prof, sizeof(prof), 3); }

void ap2_led_get_status(void) { proto_tx(CMD_LED_GET_STATUS, NULL, 0, 3); }

void ap2_led_next_profile(void) { proto_tx(CMD_LED_NEXT_PROFILE, NULL, 0, 3); }

void ap2_led_next_intensity(void) { proto_tx(CMD_LED_NEXT_INTENSITY, NULL, 0, 3); }

void ap2_led_next_animation_speed(void) { proto_tx(CMD_LED_NEXT_ANIMATION_SPEED, NULL, 0, 3); }

void ap2_led_prev_profile(void) { proto_tx(CMD_LED_PREV_PROFILE, NULL, 0, 3); }

void ap2_led_mask_set_key(uint8_t row, uint8_t col, ap2_led_t color) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha};
    proto_tx(CMD_LED_MASK_SET_KEY, payload, sizeof(payload), 1);
}

/* Push a whole local row to the shine */
void ap2_led_mask_set_row(uint8_t row) {
    uint8_t payload[NUM_COLUMN * sizeof(ap2_led_t) + 1];
    payload[0] = row;
    memcpy(payload + 1, &led_mask[ROWCOL2IDX(row, 0)], sizeof(*led_mask) * NUM_COLUMN);
    proto_tx(CMD_LED_MASK_SET_ROW, payload, sizeof(payload), 1);
}

/* Synchronize all rows */
void ap2_led_mask_set_all(void) {
    for (int row = 0; row < 5; row++) ap2_led_mask_set_row(row);
}

/* Set all keys to a given color */
void ap2_led_mask_set_mono(const ap2_led_t color) { proto_tx(CMD_LED_MASK_SET_MONO, (uint8_t *)&color, sizeof(color), 1); }

void ap2_led_colors_set_key(uint8_t row, uint8_t col, ap2_led_t color) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha};
    proto_tx(CMD_LED_COLOR_SET_KEY, payload, sizeof(payload), 1);
}

/* Push a whole local row to the shine */
void ap2_led_colors_set_row(uint8_t row) {
    uint8_t payload[NUM_COLUMN * sizeof(ap2_led_t) + 1];
    payload[0] = row;
    memcpy(payload + 1, &led_colors[ROWCOL2IDX(row, 0)], sizeof(*led_colors) * NUM_COLUMN);
    proto_tx(CMD_LED_COLOR_SET_ROW, payload, sizeof(payload), 1);
}

/* Synchronize all rows */
void ap2_led_colors_set_all(void) {
    for (int row = 0; row < 5; row++) ap2_led_colors_set_row(row);
}

/* Set all keys to a given color */
void ap2_led_colors_set_mono(const ap2_led_t color) { proto_tx(CMD_LED_COLOR_SET_MONO, (uint8_t *)&color, sizeof(color), 1); }

void ap2_led_set_manual_control(uint8_t manual) {
    uint8_t payload[] = {manual};
    proto_tx(CMD_LED_SET_MANUAL, payload, sizeof(payload), 1);
}

void ap2_led_blink(uint8_t row, uint8_t col, ap2_led_t color, uint8_t count, uint8_t hundredths) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha, count, hundredths};
    proto_tx(CMD_LED_KEY_BLINK, payload, sizeof(payload), 1);
}

void ap2_led_set_foreground_color(uint8_t red, uint8_t green, uint8_t blue) {
    ap2_led_t color = {.p.red = red, .p.green = green, .p.blue = blue, .p.alpha = 0xff};
    ap2_led_mask_set_mono(color);
}

void ap2_led_reset_foreground_color(void) {
    ap2_led_t color = {
        .p.red   = 0,
        .p.green = 0,
        .p.blue  = 0,
        .p.alpha = 0,
    };
    ap2_led_mask_set_mono(color);
}

void ap2_led_sticky_set_key(uint8_t row, uint8_t col, ap2_led_t color) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha};
    proto_tx(CMD_LED_STICKY_SET_KEY, payload, sizeof(payload), 1);
}

void ap2_led_unset_sticky_key(uint8_t row, uint8_t col) {
    uint8_t payload[] = {row, col};
    proto_tx(CMD_LED_STICKY_UNSET_KEY, payload, sizeof(payload), 1);
}

void ap2_led_unset_sticky_row(uint8_t row) {
    uint8_t payload[] = {row};
    proto_tx(CMD_LED_STICKY_UNSET_ROW, payload, sizeof(payload), 1);
}
void ap2_led_unset_sticky_all(void) {
    proto_tx(CMD_LED_STICKY_UNSET_ALL, NULL, 0, 1);
}

/*
 * Currently keypresses are unified with other messages, still with single 1
 * byte payload. Transfer is normally fast enough for that to not be a problem -
 * especially with asynchronous message reading.
 *
 *
 * Previous description:
 * If enabled, this data is sent to LED MCU on every keypress.
 * In order to improve performance, both row and column values
 * are packed into a single byte.
 * Row range is [0, 4] and requires only 3 bits.
 * Column range is [0, 13] and requires 4 bits.
 *
 * In order to differentiate this command from regular commands,
 * the leftmost bit is set to 1 (0b10000000).
 * Following it are 3 bits of row and 4 bits of col.
 * 1 + 3 + 4 = 8 bits - only a single byte is sent for every keypress.
 */
void ap2_led_forward_keypress(uint8_t row, uint8_t col) {
    const uint8_t payload = row << 4 | col;
    proto_tx(CMD_LED_KEY_DOWN, &payload, 1, 1);
}
