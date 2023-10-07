// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include QMK_KEYBOARD_H

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
                MI_BNDU,_______,MI_VL5,
          MI_BNDD,MI_MOD,  MI_VL2,MI_VL8,


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
    )
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
                uint8_t brightness = rgb_matrix_config.hsv.v - abs(vlev * 12 - midi_config.velocity);
                // Highest velocity is red.
                rgb_matrix_set_hsv(index, (10 - (vlev)) * 20, 255, brightness);
            }
        }
    }
    return false;
}
