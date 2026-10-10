// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include QMK_KEYBOARD_H

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
    KC_CYCLE_LAYERS = QK_USER,
    KC_ENCODER_CCW,
    KC_ENCODER_CW,
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   {ENCODER_CCW_CW(KC_ENCODER_CCW, KC_ENCODER_CW),},
    [1] =   {ENCODER_CCW_CW(KC_ENCODER_CCW, KC_ENCODER_CW),},
    [2] =   {ENCODER_CCW_CW(KC_ENCODER_CCW, KC_ENCODER_CW),},
    [3] =   {ENCODER_CCW_CW(KC_ENCODER_CCW, KC_ENCODER_CW),},
};
#endif

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Hexboard Harmonic table layout (landscape)
     *       ___   ___   ___
     *      ❬BnU ᚛-᚜   ᚛-᚜VlM❭__
     *   ❬BnD᚛-᚜Mod᚛-᚜VlL᚛-᚜VlH❭
     *    ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾
     *  ___   ___   ___   ___   ___   ___   ___
     * ❬F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5᚛-᚜A 5᚛-᚜Bb5᚛-᚜B 5❭__
     *  ᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5❭
     * ❬Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜
     *  ᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5❭
     * ❬Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜
     *  ᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4❭
     * ❬Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜
     *  ᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3❭
     * ❬Db3᚛-᚜D 3᚛-᚜Eb3᚛-᚜E 3᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜
     *  ᚛-᚜Bb2᚛-᚜B 2᚛-᚜C 3᚛-᚜Db3᚛-᚜D 3᚛-᚜Eb3᚛-᚜E 3❭
     * ❬Gb2᚛-᚜G 2᚛-᚜Ab2᚛-᚜A 2᚛-᚜Bb2᚛-᚜B 2᚛-᚜C 3᚛-᚜
     *  ᚛-᚜Eb2᚛-᚜E 2᚛-᚜F 2᚛-᚜Gb2᚛-᚜G 2᚛-᚜Ab2᚛-᚜A 2❭
     * ❬B 1᚛-᚜C 2᚛-᚜Db2᚛-᚜D 2᚛-᚜Eb2᚛-᚜E 2᚛-᚜F 2᚛-᚜
     *  ᚛-᚜Ab1᚛-᚜A 1᚛-᚜Bb1᚛-᚜B 1᚛-᚜C 2᚛-᚜Db2᚛-᚜D 2❭
     * ❬E 1᚛-᚜F 1᚛-᚜Gb1᚛-᚜G 1᚛-᚜Ab1᚛-᚜A 1᚛-᚜Bb1᚛-᚜
     *  ᚛-᚜Db1᚛-᚜D 1᚛-᚜Eb1᚛-᚜E 1᚛-᚜F 1᚛-᚜Gb1᚛-᚜G 1❭
     * ❬A  ᚛-᚜Bb ᚛-᚜B  ᚛-᚜C 1᚛-᚜Db1᚛-᚜D 1᚛-᚜Eb1᚛-᚜
     *  ᚛-᚜Gb ᚛-᚜G  ᚛-᚜Ab ᚛-᚜A  ᚛-᚜Bb ᚛-᚜B  ᚛-᚜C 1❭
     * ❬D  ᚛-᚜Eb ᚛-᚜E  ᚛-᚜F  ᚛-᚜Gb ᚛-᚜G  ᚛-᚜Ab ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾
     */
    [0] = LAYOUT_landscape(
              MI_BNDU,KC_CYCLE_LAYERS,MI_VL5,
          MI_BNDD,MI_MOD,          MI_VL2,MI_VL10,


      MI_F5,   MI_Gb5, MI_G5,   MI_Ab5,  MI_A5,  MI_Bb5, MI_B5,
          MI_D5,  MI_Eb5,  MI_E5,   MI_F5,   MI_Gb5, MI_G5,   MI_Ab5,
      MI_Bb4,  MI_B4,  MI_C5,   MI_Db5,  MI_D5,  MI_Eb5, MI_E5,
          MI_G4,  MI_Ab4,  MI_A4,   MI_Bb4,  MI_B4,  MI_C5,   MI_Db5,
      MI_Eb4,  MI_E4,  MI_F4,   MI_Gb4,  MI_G4,  MI_Ab4, MI_A4,
          MI_C4,  MI_Db4,  MI_D4,   MI_Eb4,  MI_E4,  MI_F4,   MI_Gb4,
      MI_Ab3,  MI_A3,  MI_Bb3,  MI_B3,  MI_C4,   MI_Db4, MI_D4,
          MI_F3,  MI_Gb3,  MI_G3,   MI_Ab3,  MI_A3,  MI_Bb3,  MI_B3,
      MI_Db3,  MI_D3,  MI_Eb3,  MI_E3,  MI_F3,   MI_Gb3, MI_G3,
          MI_Bb2,  MI_B2,  MI_C3,   MI_Db3,  MI_D3,  MI_Eb3,  MI_E3,
      MI_Gb2,  MI_G2,  MI_Ab2,  MI_A2,  MI_Bb2,  MI_B2,  MI_C3,
          MI_Eb2,  MI_E2,  MI_F2,   MI_Gb2,  MI_G2,  MI_Ab2,  MI_A2,
      MI_B1,   MI_C2,  MI_Db2,  MI_D2,  MI_Eb2,  MI_E2,  MI_F2,
          MI_Ab1,  MI_A1,  MI_Bb1,  MI_B1,   MI_C2,  MI_Db2,  MI_D2,
      MI_E1,   MI_F1,  MI_Gb1,  MI_G1,  MI_Ab1,  MI_A1,  MI_Bb1,
          MI_Db1,  MI_D1,  MI_Eb1,  MI_E1,   MI_F1,  MI_Gb1,  MI_G1,
      MI_A,     MI_Bb,   MI_B,     MI_C1,  MI_Db1,  MI_D1,  MI_Eb1,
          MI_Gb,  MI_G,      MI_Ab,    MI_A,     MI_Bb,   MI_B,     MI_C1,
      MI_D,     MI_Eb,   MI_E,     MI_F,  MI_Gb1,    MI_G,    MI_Ab
    ),
    // wickiHaydenLayout
    // ./makeLayout.py 79 2 -7 qmk
    [1] = LAYOUT_portrait(
MI_VL10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
MI_VL5,  MI_G5, MI_A5, MI_B5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      MI_C5, MI_D5, MI_E5, MI_Gb5, MI_Ab5, MI_Bb5, KC_NO, KC_NO, KC_NO, KC_NO,
MI_VL2,  MI_G4, MI_A4, MI_B4, MI_Db5, MI_Eb5, MI_F5, MI_G5, MI_A5, MI_B5,
      MI_C4, MI_D4, MI_E4, MI_Gb4, MI_Ab4, MI_Bb4, MI_C5, MI_D5, MI_E5, MI_Gb5,
QK_USER, MI_G3, MI_A3, MI_B3, MI_Db4, MI_Eb4, MI_F4, MI_G4, MI_A4, MI_B4,
      MI_C3, MI_D3, MI_E3, MI_Gb3, MI_Ab3, MI_Bb3, MI_C4, MI_D4, MI_E4, MI_Gb4,
MI_MOD,  MI_G2, MI_A2, MI_B2, MI_Db3, MI_Eb3, MI_F3, MI_G3, MI_A3, MI_B3,
      MI_C2, MI_D2, MI_E2, MI_Gb2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Gb3,
MI_BNDU, MI_G1, MI_A1, MI_B1, MI_Db2, MI_Eb2, MI_F2, MI_G2, MI_A2, MI_B2,
      MI_C1, MI_D1, MI_E1, MI_Gb1, MI_Ab1, MI_Bb1, MI_C2, MI_D2, MI_E2, MI_Gb2,
MI_BNDD, MI_G, MI_A, MI_B, MI_Db1, MI_Eb1, MI_F1, MI_G1, MI_A1, MI_B1,
      MI_C, MI_D, MI_E, MI_Gb, MI_Ab, MI_Bb, MI_C1, MI_D1, MI_E1, MI_Gb1
    ),
    // gerhardLayout
    // ./makeLayout.py 62 -1 -3 qmk
    [2] = LAYOUT_portrait(
MI_VL10, MI_D5, MI_Db5, MI_C5, MI_B4, MI_Bb4, MI_A4, MI_Ab4, MI_G4, MI_Gb4,
      MI_B4, MI_Bb4, MI_A4, MI_Ab4, MI_G4, MI_Gb4, MI_F4, MI_E4, MI_Eb4, MI_D4,
MI_VL5,  MI_G4, MI_Gb4, MI_F4, MI_E4, MI_Eb4, MI_D4, MI_Db4, MI_C4, MI_B3,
      MI_E4, MI_Eb4, MI_D4, MI_Db4, MI_C4, MI_B3, MI_Bb3, MI_A3, MI_Ab3, MI_G3,
MI_VL2,  MI_C4, MI_B3, MI_Bb3, MI_A3, MI_Ab3, MI_G3, MI_Gb3, MI_F3, MI_E3,
      MI_A3, MI_Ab3, MI_G3, MI_Gb3, MI_F3, MI_E3, MI_Eb3, MI_D3, MI_Db3, MI_C3,
QK_USER, MI_F3, MI_E3, MI_Eb3, MI_D3, MI_Db3, MI_C3, MI_B2, MI_Bb2, MI_A2,
      MI_D3, MI_Db3, MI_C3, MI_B2, MI_Bb2, MI_A2, MI_Ab2, MI_G2, MI_Gb2, MI_F2,
MI_MOD,  MI_Bb2, MI_A2, MI_Ab2, MI_G2, MI_Gb2, MI_F2, MI_E2, MI_Eb2, MI_D2,
      MI_G2, MI_Gb2, MI_F2, MI_E2, MI_Eb2, MI_D2, MI_Db2, MI_C2, MI_B1, MI_Bb1,
MI_BNDU, MI_Eb2, MI_D2, MI_Db2, MI_C2, MI_B1, MI_Bb1, MI_A1, MI_Ab1, MI_G1,
      MI_C2, MI_B1, MI_Bb1, MI_A1, MI_Ab1, MI_G1, MI_Gb1, MI_F1, MI_E1, MI_Eb1,
MI_BNDD, MI_Ab1, MI_G1, MI_Gb1, MI_F1, MI_E1, MI_Eb1, MI_D1, MI_Db1, MI_C1,
      MI_F1, MI_E1, MI_Eb1, MI_D1, MI_Db1, MI_C1, MI_B, MI_Bb, MI_A, MI_Ab
    ),
    // "Full" layout -- notably not full in qmk
    // ./makeLayout.py 132 -1 -9 qmk
    [3] = LAYOUT_portrait(
MI_VL10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
MI_VL5,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
MI_VL2,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
QK_USER, KC_NO, KC_NO, KC_NO, KC_NO, MI_B5, MI_Bb5, MI_A5, MI_Ab5, MI_G5,
      MI_Gb5, MI_F5, MI_E5, MI_Eb5, MI_D5, MI_Db5, MI_C5, MI_B4, MI_Bb4, MI_A4,
MI_MOD,  MI_Ab4, MI_G4, MI_Gb4, MI_F4, MI_E4, MI_Eb4, MI_D4, MI_Db4, MI_C4,
      MI_B3, MI_Bb3, MI_A3, MI_Ab3, MI_G3, MI_Gb3, MI_F3, MI_E3, MI_Eb3, MI_D3,
MI_BNDU, MI_Db3, MI_C3, MI_B2, MI_Bb2, MI_A2, MI_Ab2, MI_G2, MI_Gb2, MI_F2,
      MI_E2, MI_Eb2, MI_D2, MI_Db2, MI_C2, MI_B1, MI_Bb1, MI_A1, MI_Ab1, MI_G1,
MI_BNDD, MI_Gb1, MI_F1, MI_E1, MI_Eb1, MI_D1, MI_Db1, MI_C1, MI_B, MI_Bb,
      MI_A, MI_Ab, MI_G, MI_Gb, MI_F, MI_E, MI_Eb, MI_D, MI_Db, MI_C
    ),
};

void rgb_matrix_set_hsv(uint8_t i, uint8_t h, uint8_t s, uint8_t v) {
    HSV hsv = {h, s, v};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) < 0) {
        return false;
    }
    uint8_t layer = get_highest_layer(layer_state);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index < led_min || index >= led_max || index == NO_LED) continue;
            uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (keycode >= QK_MIDI_NOTE_C_0 && keycode <= QK_MIDI_NOTE_B_5) {
                rgb_matrix_set_hsv(index, ((keycode - QK_MIDI_NOTE_C_0) % 12) * 21, 255, rgb_matrix_config.hsv.v);
            } else if (keycode == QK_MIDI_PITCH_BEND_DOWN || keycode == QK_MIDI_PITCH_BEND_UP) {
                // TODO: Make this reflect the internal pitch bend value.
                rgb_matrix_set_hsv(index, 0, 255, rgb_matrix_config.hsv.v);
            } else if (keycode == QK_MIDI_MODULATION) {
                // TODO: Make this reflect the internal modulation value.
                rgb_matrix_set_hsv(index, 85, 255, rgb_matrix_config.hsv.v);
            } else if (keycode >= QK_MIDI_VELOCITY_0 && keycode <= QK_MIDI_VELOCITY_10) {
                uint8_t vlev = keycode - QK_MIDI_VELOCITY_0; // 0-10
                // Set brightness based on which is closest.
                uint8_t brightness = 127 - abs((vlev * 12) - midi_config.velocity);
                if (brightness > rgb_matrix_config.hsv.v) brightness = rgb_matrix_config.hsv.v;
                // Highest velocity is red.
                rgb_matrix_set_hsv(index, (10 - (vlev)) * 20, 255, brightness);
            }
        }
    }
    return false;
}
uint16_t held_keycode = 0;
// Add the behaviour of this new keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CYCLE_LAYERS:
            // Our logic will happen on presses, nothing is done on releases
            if (!record->event.pressed) {
                // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
                return false;
            }

            uint8_t current_layer = get_highest_layer(layer_state);

            // Check if we are within the range, if not quit
            if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;
            }

            uint8_t next_layer = current_layer + 1;
            if (next_layer > LAYER_CYCLE_END) {
                next_layer = LAYER_CYCLE_START;
            }
            layer_move(next_layer);
            return false;
        // Track the option buttons so they can modify the behavior of the encoder.
        case MI_BNDU:
        case MI_BNDD:
        case MI_MOD:
        case MI_VL2:
        case MI_VL5:
        case MI_VL10:
            if (record->event.pressed) {
                held_keycode = keycode;
            } else if (held_keycode == keycode) {
                held_keycode = 0;
            }
            // process normally
            return true;
        case KC_ENCODER_CCW:
        case KC_ENCODER_CW:
            switch (held_keycode) {
                case MI_MOD:
                    if (keycode == KC_ENCODER_CW ? midi_config.modulation_interval != 255 : midi_config.modulation_interval != 0) {
                        midi_config.modulation_interval += (keycode == KC_ENCODER_CW ? 1 : -1);
                    }
                    break;
                case MI_VL2:
                case MI_VL5:
                case MI_VL10:
                    if (keycode == KC_ENCODER_CW ? midi_config.velocity != 127 : midi_config.velocity != 0) {
                        midi_config.velocity += (keycode == KC_ENCODER_CW ? 1 : -1);
                    }
                    break;
                default:
                    break;
            }
            // done processing.
            return false;
        // Process other keycodes normally
        default:
            return true;
    }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            // skip the space because this fill the OLED width
            oled_write_ln_P(PSTR("Harmonic Table"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR(" Wicki-Hayden"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR(" Gerhard"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR(" 'Full'"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR("Velocity: "), held_keycode >= MI_VL0 && held_keycode <= MI_VL10);
    oled_write_ln(get_u8_str(midi_config.velocity, ' '), false);
    oled_write_P(PSTR("Octave: "), held_keycode >= MI_OCN2 && held_keycode <= MI_OCTU);
    oled_write_ln(get_u8_str(midi_config.octave, ' '), false);
    oled_write_P(PSTR("Transposition: "), held_keycode >= MI_TRN6 && held_keycode <= MI_TRSU);
    oled_write_ln(get_u8_str(midi_config.transpose, ' '), false);
    oled_write_P(PSTR("Mod Int: "), held_keycode >= MI_MOD && held_keycode <= MI_MODU);
    oled_write_ln(get_u8_str(midi_config.modulation_interval, ' '), false);
    return false;
}
#endif
