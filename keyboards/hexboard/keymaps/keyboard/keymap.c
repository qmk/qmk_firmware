// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only
#include QMK_KEYBOARD_H
#include "quantum/color.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Hexboard Keyboard layout (landscape)
     *       ___   ___   ___
     *      ❬BnU ᚛-᚜AuTg᚛-᚜MiO❭__
     *   ❬BnD᚛-᚜MuT᚛-᚜Pnc᚛-᚜Pnc❭
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
     *  ᚛-᚜   ᚛-᚜ E ᚛-᚜   ᚛-᚜   ᚛-᚜ I ᚛-᚜   ᚛-᚜   ❭
     * ❬TAB᚛-᚜ W ᚛-᚜ R ᚛-᚜   ᚛-᚜ U ᚛-᚜ O ᚛-᚜⌫  ᚛-᚜
     *  ᚛-᚜ Q ᚛-᚜ D ᚛-᚜ T ᚛-᚜ Y ᚛-᚜ K ᚛-᚜ P ᚛-᚜   ❭
     * ❬Esc᚛-᚜ S ᚛-᚜ F ᚛-᚜   ᚛-᚜ J ᚛-᚜ L ᚛-᚜ ' ᚛-᚜
     *  ᚛-᚜ A ᚛-᚜ C ᚛-᚜ G ᚛-᚜ H ᚛-᚜ , ᚛-᚜ ; ᚛-᚜   ❭
     * ❬sft᚛-᚜ X ᚛-᚜ V ᚛-᚜   ᚛-᚜ M ᚛-᚜ . ᚛-᚜ ⏎ ᚛-᚜
     *  ᚛-᚜ Z ᚛-᚜   ᚛-᚜ B ᚛-᚜ N ᚛-᚜   ᚛-᚜ / ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜Ctl᚛-᚜Sup᚛-᚜   ᚛-᚜   ᚛-᚜ 🡐 ᚛-᚜ 🡑 ᚛-᚜ ⏎ ❭
     * ❬   ᚛-᚜Alt᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ 🡓 ᚛-᚜ 🡒 ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾
     */
    [0] = LAYOUT_landscape(
                MI_BNDU,AU_TOGG,  RGB_HUI,
          MI_BNDD,MU_TOGG,  RGB_VAD,   RGB_MOD,


MI_F5, MI_Gb5, MI_G5,   MI_Ab5,  MI_A5,  MI_Bb5, MI_B5,
    MI_D5, MI_Eb5,  MI_E5,   MI_F5,   MI_Gb5, MI_G5, MI_Ab5,
MI_Bb4,MI_B4,  MI_C5,   MI_Db5,  MI_D5,  MI_Eb5, MI_E5,
    MI_G4, MI_Ab4,  MI_A4,   MI_Bb4,  MI_B4,  MI_C5, MI_Db5,
MI_Eb4,MI_E4,  MI_F4,   MI_Gb4,  MI_G4,  MI_Ab4, MI_A4,
    MI_C4, MI_Db4,  MI_D4,   MI_Eb4,  MI_E4,  MI_F4, MI_Gb4,
MI_Ab3,MI_A3,  MI_Bb3,  MI_B3,  MI_C4,   MI_Db4, MI_D4,
    MI_F3, MI_Gb3,  MI_G3,   MI_Ab3,  MI_A3,  MI_Bb3,MI_B3,
MI_Db3,MI_D3,  MI_Eb3,  MI_E3,  MI_F3,   MI_Gb3, MI_G3,
    _______,KC_E,     _______,  _______,  KC_I,    _______,_______,
KC_TAB, KC_W,    KC_R,  _______,    KC_U,     KC_O,   KC_BSPC,
    KC_Q,   KC_D,    KC_T,     KC_Y,     KC_K,    KC_P,   _______,
KC_ESC, KC_S,    KC_F,  _______,     KC_J,     KC_L,   KC_QUOT,
    KC_A,   KC_C,     KC_G,    KC_H,     KC_COMM, KC_SCLN,_______,
KC_LSFT,KC_X,    KC_V,   _______,   KC_M,     KC_DOT,  KC_ENT, 
    KC_Z,  _______,  KC_B,     KC_N,     _______, KC_SLSH,_______,
_______,_______, _______, _______,  _______,  _______, _______,
    KC_LCTL,KC_LGUI, _______, _______,   KC_LEFT,   KC_UP,KC_ENT,
_______,KC_LALT, MO(1),    KC_SPC,  MO(2),    KC_DOWN,   KC_RGHT
    ),


    // "lower"
    /**
     *  ... top rows fall through to other layer.
     *     ___   ___   ___   ___   ___   ___   ___
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ + ᚛-᚜   ᚛-᚜   ❭
     * ❬ ~ ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ _ ᚛-᚜ { ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜ # ᚛-᚜   ᚛-᚜   ᚛-᚜ * ᚛-᚜ } ᚛-᚜   ❭
     * ❬ ⌦ ᚛-᚜ @ ᚛-᚜ $ ᚛-᚜   ᚛-᚜ & ᚛-᚜ ( ᚛-᚜ | ᚛-᚜
     *  ᚛-᚜ ! ᚛-᚜   ᚛-᚜ % ᚛-᚜ ^ ᚛-᚜   ᚛-᚜ ) ᚛-᚜   ❭
     * ❬sft᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜ ⇑ ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ ⇓ ᚛-᚜ ⇲ ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾
     */

    [1] = LAYOUT_landscape(
                MI_BNDU,AU_TOGG,  RGB_M_SN,
          MI_BNDD,MU_TOGG,  RGB_M_B,RGB_M_SW,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_PLUS,_______,_______,
KC_TILD,_______,_______,_______,KC_UNDS,KC_LCBR,_______,
    _______,KC_HASH,_______,_______,KC_ASTR,KC_RCBR,_______,
KC_DEL, KC_AT,  KC_DLR,_______, KC_AMPR,KC_LPRN,KC_PIPE,
    KC_EXLM,_______,KC_PERC,KC_CIRC,_______,KC_RPRN,_______,
KC_LSFT,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_HOME,KC_PGUP,_______,
_______,_______,_______,_______,_______,KC_PGDN,KC_END
    ),
    // "raise"
    /**
     *  ... top rows fall through to other layer.
     *     ___   ___   ___   ___   ___   ___   ___
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ = ᚛-᚜   ᚛-᚜   ❭
     * ❬ ~ ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ _ ᚛-᚜ [ ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜ 3 ᚛-᚜   ᚛-᚜   ᚛-᚜ 8 ᚛-᚜ ] ᚛-᚜   ❭
     * ❬ ⌦ ᚛-᚜ 2 ᚛-᚜ 4 ᚛-᚜   ᚛-᚜ 7 ᚛-᚜ 9 ᚛-᚜ \ ᚛-᚜
     *  ᚛-᚜ 1 ᚛-᚜   ᚛-᚜ 5 ᚛-᚜ 6 ᚛-᚜   ᚛-᚜ 0 ᚛-᚜   ❭
     * ❬sft᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜ ⇑ ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ ⇓ ᚛-᚜ ⇲ ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾
     */
    [2] = LAYOUT_landscape(
                MI_BNDU,AU_TOGG,  RGB_HUI,
          MI_BNDD,MU_TOGG,  RGB_VAD,RGB_MOD,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_EQL ,_______,_______,
KC_GRV ,_______,_______,_______,KC_MINS,KC_LBRC,_______,
    _______, KC_3  ,_______,_______, KC_8  ,KC_RBRC,_______,
KC_DEL , KC_2  , KC_4  ,_______, KC_7  , KC_9  ,KC_BSLS,
     KC_1  ,_______, KC_5  , KC_6  ,_______, KC_0  ,_______,
KC_LSFT,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_HOME,KC_PGUP,_______,
_______,_______,_______,_______,_______,KC_PGDN,KC_END
    )


};

// Hue, Saturation, Config
#define HSC_AZURE       132, 102, rgb_matrix_config.hsv.v
#define HSC_BLUE        170, 255, rgb_matrix_config.hsv.v
#define HSC_CHARTREUSE   64, 255, rgb_matrix_config.hsv.v
#define HSC_CORAL        11, 176, rgb_matrix_config.hsv.v
#define HSC_CYAN        128, 255, rgb_matrix_config.hsv.v
#define HSC_GOLD         36, 255, rgb_matrix_config.hsv.v
#define HSC_GOLDENROD    30, 218, rgb_matrix_config.hsv.v
#define HSC_GREEN        85, 255, rgb_matrix_config.hsv.v
#define HSC_MAGENTA     213, 255, rgb_matrix_config.hsv.v
#define HSC_ORANGE       21, 255, rgb_matrix_config.hsv.v
#define HSC_PINK        234, 128, rgb_matrix_config.hsv.v
#define HSC_PURPLE      191, 255, rgb_matrix_config.hsv.v
#define HSC_RED           0, 255, rgb_matrix_config.hsv.v
#define HSC_SPRINGGREEN 106, 255, rgb_matrix_config.hsv.v
#define HSC_TEAL        128, 255, rgb_matrix_config.hsv.v>>1
#define HSC_TURQUOISE   123,  90, rgb_matrix_config.hsv.v>>1
#define HSC_WHITE         0,   0, rgb_matrix_config.hsv.v
#define HSC_YELLOW       43, 255, rgb_matrix_config.hsv.v
#define HSC_GRAY          0,   0, rgb_matrix_config.hsv.v>>1
// Categories
#define HSC_LETTERS HSC_GRAY
#define HSC_SLETTERS HSC_WHITE
#define HSC_NUMBERS HSC_YELLOW>>1
#define HSC_SNUMBERS HSC_YELLOW

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
            if (keycode >= KC_1 && keycode <= KC_0)
                rgb_matrix_set_hsv(index, HSC_NUMBERS);
            else if (keycode >= S(KC_1) && keycode <= S(KC_0))
                rgb_matrix_set_hsv(index, HSC_SNUMBERS);
            else if (keycode == KC_ENTER || keycode == KC_TAB || keycode == KC_SPACE)
                rgb_matrix_set_hsv(index, HSC_SPRINGGREEN);
            else if (keycode == KC_BACKSPACE || keycode == KC_DELETE)
                rgb_matrix_set_hsv(index, HSC_RED);
            else if (keycode == KC_CAPS_LOCK)
                rgb_matrix_set_hsv(index, HSC_BLUE);
            else if (keycode >= KC_A && keycode <= KC_SLASH)
                rgb_matrix_set_hsv(index, HSC_LETTERS);
            else if (keycode >= S(KC_A) && keycode <= S(KC_SLASH))
                rgb_matrix_set_hsv(index, HSC_SLETTERS);
            else if (keycode >= KC_F1 && keycode <= KC_NUM_LOCK)
                rgb_matrix_set_hsv(index, HSC_BLUE);
            // TODO: numpad keycodes
            else if (keycode >= KC_APPLICATION && keycode <= KC_MS_ACCEL2)
                rgb_matrix_set_hsv(index, HSC_BLUE);
            else if (keycode >= KC_LEFT_CTRL && keycode <= KC_RIGHT_GUI)
                rgb_matrix_set_hsv(index, HSC_PURPLE);
            // TODO: magic keycodes
            else if(keycode >= QK_MIDI_NOTE_C_0 && keycode <= QK_MIDI_NOTE_B_5) {
				rgb_matrix_set_hsv(index, ((keycode-QK_MIDI_NOTE_C_0)%12) * 21, 255, rgb_matrix_config.hsv.v);
            }
            // sequencer, joystick, programmable, settings...
            else if (keycode == MO(1) || keycode == MO(2)) rgb_matrix_set_hsv(index, HSC_PINK);
        }
    }
    return false;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
