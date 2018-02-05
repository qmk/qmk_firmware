/* Copyright 2016 Jack Humbert
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

#include "api.h"
#include "quantum.h"

void dword_to_bytes(uint32_t dword, uint8_t * bytes) {
    bytes[0] = (dword >> 24) & 0xFF;
    bytes[1] = (dword >> 16) & 0xFF; 
    bytes[2] = (dword >> 8) & 0xFF; 
    bytes[3] = (dword >> 0) & 0xFF; 
}

uint32_t bytes_to_dword(uint8_t * bytes, uint8_t index) {
    return ((uint32_t)bytes[index + 0] << 24) | ((uint32_t)bytes[index + 1] << 16) | ((uint32_t)bytes[index + 2] << 8) | (uint32_t)bytes[index + 3];
}

__attribute__ ((weak))
bool process_api_quantum(uint8_t length, uint8_t * data) {
    return process_api_keyboard(length, data);
}

__attribute__ ((weak))
bool process_api_keyboard(uint8_t length, uint8_t * data) {
    return process_api_user(length, data);
}

__attribute__ ((weak))
bool process_api_user(uint8_t length, uint8_t * data) {
    return true;
}

void process_api(uint16_t length, uint8_t * data) {
    // SEND_STRING("\nRX: ");
    // for (uint8_t i = 0; i < length; i++) {
    //     send_byte(data[i]);
    //     SEND_STRING(" ");
    // }
    if (!process_api_quantum(length, data))
        return;

    switch (data[0]) {
        case MT_SET_DATA:
            switch (data[1]) {
                case DT_DEFAULT_LAYER: {
                    eeconfig_update_default_layer(data[2]);
                    default_layer_set((uint32_t)(data[2]));
                    break;
                }
                case DT_KEYMAP_OPTIONS: {
                    eeconfig_update_keymap(data[2]);
                    break;
                }
                case DT_RGBLIGHT: {
                    #ifdef RGBLIGHT_ENABLE
                        uint32_t rgblight = bytes_to_dword(data, 2);
                        rgblight_update_dword(rgblight);
                    #endif
                    break;
                }
            }
        case MT_GET_DATA:
            switch (data[1]) {
                case DT_HANDSHAKE: {
                    MT_GET_DATA_ACK(DT_HANDSHAKE, NULL, 0);
                    break;
                }
                case DT_DEBUG: {
                    uint8_t debug_bytes[1] = { eeprom_read_byte(EECONFIG_DEBUG) };
                    MT_GET_DATA_ACK(DT_DEBUG, debug_bytes, 1);
                    break;
                }
                case DT_DEFAULT_LAYER: {
                    uint8_t default_bytes[1] = { eeprom_read_byte(EECONFIG_DEFAULT_LAYER) };
                    MT_GET_DATA_ACK(DT_DEFAULT_LAYER, default_bytes, 1);
                    break;
                }
                case DT_CURRENT_LAYER: {
                    uint8_t layer_state_bytes[4];
                    dword_to_bytes(layer_state, layer_state_bytes);
                    MT_GET_DATA_ACK(DT_CURRENT_LAYER, layer_state_bytes, 4);
                    break;
                }
                case DT_AUDIO: {
                    #ifdef AUDIO_ENABLE
                        uint8_t audio_bytes[1] = { eeprom_read_byte(EECONFIG_AUDIO) };
                        MT_GET_DATA_ACK(DT_AUDIO, audio_bytes, 1);
                    #else
                        MT_GET_DATA_ACK(DT_AUDIO, NULL, 0);
                    #endif
                    break;
                }
                case DT_BACKLIGHT: {
                    #ifdef BACKLIGHT_ENABLE
                        uint8_t backlight_bytes[1] = { eeprom_read_byte(EECONFIG_BACKLIGHT) };
                        MT_GET_DATA_ACK(DT_BACKLIGHT, backlight_bytes, 1);
                    #else
                        MT_GET_DATA_ACK(DT_BACKLIGHT, NULL, 0);
                    #endif
                    break;
                }
                case DT_RGBLIGHT: {
                    #ifdef RGBLIGHT_ENABLE
                        uint8_t rgblight_bytes[4];
                        dword_to_bytes(eeconfig_read_rgblight(), rgblight_bytes);
                        MT_GET_DATA_ACK(DT_RGBLIGHT, rgblight_bytes, 4);
                    #else
                        MT_GET_DATA_ACK(DT_RGBLIGHT, NULL, 0);
                    #endif
                    break;
                }
                case DT_KEYMAP_OPTIONS: {
                    uint8_t keymap_bytes[1] = { eeconfig_read_keymap() };
                    MT_GET_DATA_ACK(DT_KEYMAP_OPTIONS, keymap_bytes, 1);
                    break;
                }
                case DT_KEYMAP_SIZE: {
                    uint8_t keymap_size[2] = {MATRIX_ROWS, MATRIX_COLS};
                    MT_GET_DATA_ACK(DT_KEYMAP_SIZE, keymap_size, 2);
                    break;
                }
                // This may be too much
                // case DT_KEYMAP: {
                //     uint8_t keymap_data[MATRIX_ROWS * MATRIX_COLS * 4 + 3];
                //     keymap_data[0] = data[2];
                //     keymap_data[1] = MATRIX_ROWS;
                //     keymap_data[2] = MATRIX_COLS;
                //     for (int i = 0; i < MATRIX_ROWS; i++) {
                //         for (int j = 0; j < MATRIX_COLS; j++) {
                //             keymap_data[3 + (i*MATRIX_COLS*2) + (j*2)] = pgm_read_word(&keymaps[data[2]][i][j]) >> 8;
                //             keymap_data[3 + (i*MATRIX_COLS*2) + (j*2) + 1] = pgm_read_word(&keymaps[data[2]][i][j]) & 0xFF;
                //         }
                //     }
                //     MT_GET_DATA_ACK(DT_KEYMAP, keymap_data, MATRIX_ROWS * MATRIX_COLS * 4 + 3);
                //     // uint8_t keymap_data[5];
                //     // keymap_data[0] = data[2];
                //     // keymap_data[1] = data[3];
                //     // keymap_data[2] = data[4];
                //     // keymap_data[3] = pgm_read_word(&keymaps[data[2]][data[3]][data[4]]) >> 8;
                //     // keymap_data[4] = pgm_read_word(&keymaps[data[2]][data[3]][data[4]]) & 0xFF;

                //     // MT_GET_DATA_ACK(DT_KEYMAP, keymap_data, 5);
                //     break;
                // }
                default:
                    break;
            }
            break;
        case MT_SET_DATA_ACK:
        case MT_GET_DATA_ACK:
            break;
        case MT_SEND_DATA:
            break;
        case MT_SEND_DATA_ACK:
            break;
        case MT_EXE_ACTION:
            break;
        case MT_EXE_ACTION_ACK:
            break;
        case MT_TYPE_ERROR:
            break;
        default: ; // command not recognised
            SEND_BYTES(MT_TYPE_ERROR, DT_NONE, data, length);
            break;

        // #ifdef RGBLIGHT_ENABLE
        // case 0x27: ; // RGB LED functions
        //     switch (*data++) {
        //         case 0x00: ; // Update HSV
        //             rgblight_sethsv((data[0] << 8 | data[1]) % 360, data[2], data[3]);
        //             break;
        //         case 0x01: ; // Update RGB
        //             break;
        //         case 0x02: ; // Update mode
        //             rgblight_mode(data[0]);
        //             break;
        //     }
        //     break;
        // #endif
    }

}
