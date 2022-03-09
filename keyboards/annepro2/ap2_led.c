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

annepro2Led_t       ledMask[KEY_COUNT];
annepro2LedStatus_t annepro2LedStatus;

void ledCommandCallback(const message_t *msg) {
    switch (msg->command) {
        case CMD_LED_STATUS:
            annepro2LedStatus.amountOfProfiles = msg->payload[0];
            annepro2LedStatus.currentProfile   = msg->payload[1];
            annepro2LedStatus.matrixEnabled    = msg->payload[2];
            annepro2LedStatus.isReactive       = msg->payload[3];
            annepro2LedStatus.ledIntensity     = msg->payload[4];
            annepro2LedStatus.errors           = msg->payload[5];
            break;

#ifdef CONSOLE_ENABLE
        case CMD_LED_DEBUG:
            /* TODO: Don't use printf. */
            printf("LED:");
            for (int i = 0; i < msg->payloadSize; i++) {
                printf("%02x ", msg->payload[i]);
            }
            for (int i = 0; i < msg->payloadSize; i++) {
                printf("%c", msg->payload[i]);
            }
            printf("\n");
            break;
#endif
    }
}

void annepro2SetIAP(void) { protoTx(CMD_LED_IAP, NULL, 0, 3); }

void annepro2LedDisable(void) { protoTx(CMD_LED_OFF, NULL, 0, 3); }

void annepro2LedEnable(void) { protoTx(CMD_LED_ON, NULL, 0, 3); }

void annepro2LedSetProfile(uint8_t prof) { protoTx(CMD_LED_SET_PROFILE, &prof, sizeof(prof), 3); }

void annepro2LedGetStatus() { protoTx(CMD_LED_GET_STATUS, NULL, 0, 3); }

void annepro2LedNextProfile() { protoTx(CMD_LED_NEXT_PROFILE, NULL, 0, 3); }

void annepro2LedNextIntensity() { protoTx(CMD_LED_NEXT_INTENSITY, NULL, 0, 3); }

void annepro2LedNextAnimationSpeed() { protoTx(CMD_LED_NEXT_ANIMATION_SPEED, NULL, 0, 3); }

void annepro2LedPrevProfile() { protoTx(CMD_LED_PREV_PROFILE, NULL, 0, 3); }

void annepro2LedMaskSetKey(uint8_t row, uint8_t col, annepro2Led_t color) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha};
    protoTx(CMD_LED_MASK_SET_KEY, payload, sizeof(payload), 1);
}

/* Push a whole local row to the shine */
void annepro2LedMaskSetRow(uint8_t row) {
    uint8_t payload[NUM_COLUMN * sizeof(annepro2Led_t) + 1];
    payload[0] = row;
    memcpy(payload + 1, &ledMask[ROWCOL2IDX(row, 0)], sizeof(*ledMask) * NUM_COLUMN);
    protoTx(CMD_LED_MASK_SET_ROW, payload, sizeof(payload), 1);
}

/* Synchronize all rows */
void annepro2LedMaskSetAll(void) {
    for (int row = 0; row < 5; row++) annepro2LedMaskSetRow(row);
}

/* Set all keys to a given color */
void annepro2LedMaskSetMono(const annepro2Led_t color) { protoTx(CMD_LED_MASK_SET_MONO, (uint8_t *)&color, sizeof(color), 1); }

void annepro2LedBlink(uint8_t row, uint8_t col, annepro2Led_t color, uint8_t count, uint8_t hundredths) {
    uint8_t payload[] = {row, col, color.p.blue, color.p.green, color.p.red, color.p.alpha, count, hundredths};
    protoTx(CMD_LED_KEY_BLINK, payload, sizeof(payload), 1);
}

void annepro2LedSetForegroundColor(uint8_t red, uint8_t green, uint8_t blue) {
    annepro2Led_t color = {.p.red = red, .p.green = green, .p.blue = blue, .p.alpha = 0xff};
    annepro2LedMaskSetMono(color);
}

void annepro2LedResetForegroundColor() {
    annepro2Led_t color = {
        .p.red   = 0,
        .p.green = 0,
        .p.blue  = 0,
        .p.alpha = 0,
    };
    annepro2LedMaskSetMono(color);
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
void annepro2LedForwardKeypress(uint8_t row, uint8_t col) {
    const uint8_t payload = row << 4 | col;
    protoTx(CMD_LED_KEY_DOWN, &payload, 1, 1);
}
