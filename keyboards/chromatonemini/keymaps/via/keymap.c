/* Copyright 2021 3araht
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
#include QMK_KEYBOARD_H
#include "version.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,              //  Base layer, shift mode, single channel.
    _TRANS,             //  Transpose feature is enabled instead of shift mode, single channel.
    _RESERVE,           //  RESERVE
    _FN                 //  FuNction layer. This must be at the end of the enumurate to use the range from _LS_FN ... _LS_FN_MAX for FN layer LED settings.
};

//  Layer State
#define _LS_BASE           (1UL << _BASE)
#define _LS_TRANS          (1UL << _BASE         | 1UL << _TRANS)

#define _LS_FN             (1UL << _FN)
#define _LS_MAX            (_LS_FN << 1)

//  Don't change the DEFAULT_SCALE_COL value below. It must be 0.
#define DEFAULT_SCALE_COL 0
static uint8_t scale_indicator_col = DEFAULT_SCALE_COL;
static bool trans_mode_indicator_loc_sel = true;  // when it is true, the location is _KEY01, _KEY13, ...

//  use led indicator or not.
static bool led_indicator_enable = true;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    SHIFT_L = QK_KB_0,
    SHIFT_R,
    TGLINDI,  //  ToGgLe INDIcator
    TGLINTR,  //  ToGgLe INdicator location {(_KEY01, _KEY13, _KEY25, _KEY37) or (_KEY02, _KEY14, _KEY26) / (_KEY12, _KEY24, _KEY36)}in TRans mode
    TGLTRNS,  //  ToGgLe TRaNS and shift

    B_BASE,            //  border set to the left end.
    VERSION
};

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to 0
extern midi_config_t midi_config;
static bool is_trans_mode = false;     //  By default, shift mode is chosen.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
            FN_MUTE,         MI_SUST,
            MI_BNDU,
        SHIFT_L, SHIFT_R,    MI_C2, MI_D2, MI_E2,  MI_Fs2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Fs3, MI_Ab3, MI_Bb3, MI_C4,  MI_D4,  MI_E4, MI_Fs4, MI_Ab4, MI_Bb4, MI_C5,
            MI_BNDD,            MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2, MI_Db3, MI_Eb3, MI_F3,  MI_G3, MI_A3,  MI_B3, MI_Db4, MI_Eb4, MI_F4,  MI_G4,  MI_A4,  MI_B4
    ),

    /* TRANS   This layer must locate 1 layer below _FN layer. */
    [_TRANS] = LAYOUT(
            _______,           _______,
            _______,
        MI_TRSD,  MI_TRSU,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* RESERVE */
    [_RESERVE] = LAYOUT(
            _______,          _______,
            _______,
        _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] =  LAYOUT(
            _______,          XXXXXXX,
            MI_VELU,
        MI_OCTD, MI_OCTU,     B_BASE, DF(_RESERVE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VERSION, XXXXXXX, XXXXXXX,
            MI_VELD,              TGLINTR,    TGLTRNS, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, RGB_SPD, RGB_SPI, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, EE_CLR, TGLINDI, RGB_TOG
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]         = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_TRANS]        = { ENCODER_CCW_CW(_______, _______)  },
    [_RESERVE]      = { ENCODER_CCW_CW(_______, _______)  },
    [_FN]           = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
};
#endif

// commom codes called from eeconfig_init_user() and keyboard_post_init_user().
void my_init(void){
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
    default_layer_set(_LS_BASE);
    layer_state_set(_LS_BASE);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_solid_reactive_col);
#endif  // RGB_MATRIX_ENABLE
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_sethsv(HSV_BLUE);
#endif  // RGB_MATRIX_ENABLE
    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
}

void keyboard_post_init_user(void) {
    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
}

void reset_scale_indicator(void) {
    //  reset transpose value and scale_indicator_col to default.
    midi_config.transpose = 0;
    scale_indicator_col = DEFAULT_SCALE_COL;
    trans_mode_indicator_loc_sel = true;
}

void reset_all(void) {
    reset_scale_indicator();
    is_trans_mode = false;      //  trans mode is disabled by default.
}

void select_layer_state_set(void) {
    if (is_trans_mode) {
        layer_state_set(_LS_TRANS);
    } else {
        layer_state_set(_LS_BASE);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // uprintf("keycode=%u, YM_C_3=%u, YM_Db_2 =%u, YM_MIN = %u, YM_MAX = %u\n", keycode, YM_C_3, YM_Db_2, YM_TONE_MIN, YM_TONE_MAX);
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            break;

        //  Layer-related settings.
        //  reset_scale_indicator() first, followed by each modification, and then change the default layer.

        //  1, separator column modification
        case B_BASE:
            if (record->event.pressed) {
                reset_all();
                select_layer_state_set();
            }
            break;

        //  2, Toggle scale shift mode and transpose mode
        case TGLTRNS:
            if (record->event.pressed) {
                reset_scale_indicator();
                is_trans_mode = !is_trans_mode;
                select_layer_state_set();
            }
            break;

        //  SHIFT_L and SHIFT_R can be pressed only when layer is either _BASE, _FLIPBASE.
        case SHIFT_L:
            if (record->event.pressed) {
                if (layer_state ==  _LS_BASE) {
                        scale_indicator_col = shift_led_indicator_left(scale_indicator_col);
                }
            }
            break;

        case SHIFT_R:
            if (record->event.pressed) {
                if (layer_state == _LS_BASE ) {
                        scale_indicator_col = shift_led_indicator_right(scale_indicator_col);
                }
            }
            break;

        case TGLINDI:
            if (record->event.pressed) {
                led_indicator_enable = !led_indicator_enable;
            }
            break;

        case TGLINTR:
            if (record->event.pressed) {
                switch (layer_state) {
                    //  main function of the TGLINTR part 1. alternate the status of trans_mode_indicator_loc_sel.
                    case _LS_TRANS          | (1UL << _FN):
                        trans_mode_indicator_loc_sel = !trans_mode_indicator_loc_sel;

                        //  when trans_mode_indicator_loc_sel == false, change the scale indicator and transpose.
                        scale_indicator_col = trans_mode_indicator_loc_sel ? 0:1;
                        // when TGLINTR is pressed, it also change the initial transpose setting to follow the scale indicator.
                        if (scale_indicator_col == 1) {
                            midi_config.transpose = -1;
                        } else {
                            midi_config.transpose = 0;
                        }
                        break;

                    //  special treatment when TGLINTR is pressed in other non-Trans layer.
                    default :  // when other layers = non-Trans mode, change it to Trans mode.
                        trans_mode_indicator_loc_sel = false;
                        scale_indicator_col = 1;
                        midi_config.transpose = -1;
                        is_trans_mode = true;
                        select_layer_state_set();
                }
            }
            break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
void set_led_scale_indicator(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t max_scale_indicator_led_loop;
    uint8_t i;
    if (led_indicator_enable) {  //  turn on indicators when enabled.
        max_scale_indicator_led_loop = ( scale_indicator_col == DEFAULT_SCALE_COL ) ? 12 : 9;
        for (i = 0; i < max_scale_indicator_led_loop; i++) {
            rgb_matrix_set_color(led_scale_indicator[scale_indicator_col][i], r, g, b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    // uint32_t mode = rgblight_get_mode();

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        // uint8_t max_scale_indicator_led_loop;
        uint8_t i;

        switch (layer_state) {
            case _LS_BASE:
                set_led_scale_indicator(BASE_LAYER_COLOR);
                break;

            case _LS_TRANS:
                set_led_scale_indicator(TRANS_LAYER_COLOR);
                break;

            case _LS_FN ... _LS_MAX:  //  When Mute Button is long-pressed, the previous layers are still active.
                for (i = 1; i < 5; i++) {
                    rgb_matrix_set_color(i, RGB_DARKSPRINGGREEN);  //  up(1) down(4) left(3) right(2)  keys
                }
                rgb_matrix_set_color(led_single_col_indicator[_KEY02][0], RGB_DARKSPRINGGREEN);   //  TGLTRNS
                rgb_matrix_set_color(led_single_col_indicator[_KEY04][0], RGB_DARKSPRINGGREEN);   //  TGLINTR

                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY01][i], BASE_LAYER_COLOR);   //  B_BASE
                }

                for (i = _KEY12; i < _KEY37; i+=2){  //  even numbers from _KEY12 to _KEY36 are LED related settings.
                    // turn on the bottom row only to keep the visibility of the RGB MATRIX effects.
                    rgb_matrix_set_color(led_single_col_indicator[i][0], RGB_DARKSPRINGGREEN);  //       //  LED related settings.
                }
                break;
        }
    }
    return false;
}
#endif  // RGB_MATRIX_ENABLE
