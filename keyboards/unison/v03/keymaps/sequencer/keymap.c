/* Copyright 2020 Takeshi Nishio
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
#include "muse.h"

// MIDI: Used to set octave to MI_OCT_0
// extern midi_config_t midi_config;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _MAC = 0,
    _WIN,
    _MIDI,
    _SEQUENCER,
    _LOWER,
    _RAISE,
    _ADJUST,
    _CAPS, // This is not a "REAL" layer. Define here to use for RGB light layer.
    _SEQPLAYBACK, // This is not a "REAL" layer. Define here to use for RGB light layer.
};

// Sequencer
enum unison_sequencer_tracks {
    KICK = 0,   // Kick
    SNARE,  // Snare
    HIHAT1, // Hihat closed
    HIHAT2, // Hihat open
    CRASH,  // Crash
    RIDE,    // Ride
};

const uint16_t unison_sequencer_track_notes[SEQUENCER_TRACKS] = {[KICK] = MI_C_1, [SNARE] = MI_D_1, [HIHAT1] = MI_Fs_1, [HIHAT2] = MI_As_1, [CRASH] = MI_Cs_2, [RIDE] = MI_Ds_2};

// Tap Dance
enum tap_dances{
    TD_LSFT_CAPS = 0,
};

// Tap Dance state
enum {
    SINGLE_TAP = 1,
    DOUBLE_TAP,
    TRIPLE_TAP,
    TAP_HOLD,
};

// Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
// };

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MAC = SAFE_RANGE,
    WIN,
    MIDI,
    SEQ,
    LOWER,
    RAISE,
    M_PSCR,
    ALT_EN,
    ALT_JA,
    GUI_EN,
    GUI_JA,
    SEQ_TOG,
    SEQ_TT0,
    SEQ_TT1,
    SEQ_TT2,
    SEQ_TT3,
    SEQ_TT4,
    SEQ_TT5,
    SEQ_TT6,
    SEQ_TT7,
};

// Key Macro
// #define S_CAP   TD(TD_LSFT_CAPS)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define SLS_LOW LT(_LOWER, KC_SLSH)
#define SFT_SLS RSFT_T(KC_SLSH)
#define C_SLSH  RCTL_T(KC_SLSH)
#define CT_E    LCTL(KC_E)
#define CT_A    LCTL(KC_A)
#define ALT_GRV LALT(KC_GRV)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define HENKAN  LGUI(KC_GRV)
#define MIDI    DF(_MIDI)
#define SEQ     DF(_SEQUENCER)
#define ALT_EN  LALT_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define GUI_JA  LGUI_T(KC_LANG1)
// Key Macro for Sequencer
#define SQ_0    SQ_S(0)
#define SQ_1    SQ_S(1)
#define SQ_2    SQ_S(2)
#define SQ_3    SQ_S(3)
#define SQ_4    SQ_S(4)
#define SQ_5    SQ_S(5)
#define SQ_6    SQ_S(6)
#define SQ_7    SQ_S(7)
#define SQ_8    SQ_S(8)
#define SQ_9    SQ_S(9)
#define SQ_10   SQ_S(10)
#define SQ_11   SQ_S(11)
#define SQ_12   SQ_S(12)
#define SQ_13   SQ_S(13)
#define SQ_14   SQ_S(14)
#define SQ_15   SQ_S(15)
#define SQ_16   SQ_S(16)
#define SQ_17   SQ_S(17)
#define SQ_18   SQ_S(18)
#define SQ_19   SQ_S(19)
#define SQ_20   SQ_S(20)
#define SQ_21   SQ_S(21)
#define SQ_22   SQ_S(22)
#define SQ_23   SQ_S(23)
#define SQ_24   SQ_S(24)
#define SQ_25   SQ_S(25)
#define SQ_26   SQ_S(26)
#define SQ_27   SQ_S(27)
#define SQ_28   SQ_S(28)
#define SQ_29   SQ_S(29)
#define SQ_30   SQ_S(30)
#define SQ_31   SQ_S(31)
#define SQT_BD  SQ_T(KICK)
#define SQT_SN  SQ_T(SNARE)
#define SQT_HC  SQ_T(HIHAT1)
#define SQT_HO  SQ_T(HIHAT2)
#define SQT_CR  SQ_T(CRASH)
#define SQT_RD  SQ_T(RIDE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_MUTE,XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
        KC_LCTL,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,    KC_ENT,
        KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_P1,  KC_P2,  KC_P3,  KC_PENT,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_UP,  SFT_SLS,
        KC_CAPS,KC_CAPS,ALT_JA, XXXXXXX,GUI_EN, SP_LOW, SP_LOW, KC_P0,  KC_P0,  KC_PDOT,SP_RAI, SP_RAI, SP_RAI, KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_WIN] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,GUI_JA, _______,ALT_EN, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    [_MIDI] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_MUTE,XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   XXXXXXX,MI_VEL_9,XXXXXXX,MI_OCT_0,XXXXXXX,MI_TRNS_0,XXXXXXX,KC_MUTE,XXXXXXX,
        MI_TRNSD,   MI_TRNS_0,MI_TRNSU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        MI_VELD,    MI_VEL_9,MI_VELU,MI_Fs_2,MI_Gs_2,MI_As_2,XXXXXXX,MI_Cs_3,MI_Ds_3,XXXXXXX,MI_Fs_3,MI_Gs_3,MI_As_3,XXXXXXX,MI_Cs_4,    MI_Ds_4,
        _______,_______,_______,MI_F_2, MI_G_2, MI_A_2, MI_B_2, MI_C_3, MI_D_3, MI_E_3, MI_F_3, MI_G_3, MI_A_3, MI_B_3, MI_C_4, MI_D_4, MI_E_4,
        MI_OCTD,MI_OCT_0,MI_OCTU,XXXXXXX,XXXXXXX,LOWER,  LOWER,  XXXXXXX,XXXXXXX,XXXXXXX,RAISE,  RAISE,  RAISE,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
    ),
    [_SEQUENCER] = LAYOUT(
        _______,_______,_______,_______,SEQ_TOG,_______,SQ_TMPD,SQ_TMPU,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        SQ_0,       SQ_1,   SQ_2,   SQ_3,   SQ_4,   SQ_5,   SQ_6,   SQ_7,   SQ_8,   SQ_9,   SQ_10,  SQ_11,  SQ_12,  SQ_13,  SQ_14,      SQ_15,
        SQ_16,      SQ_17,  SQ_18,  SQ_19,  SQ_20,  SQ_21,  SQ_22,  SQ_23,  SQ_24,  SQ_25,  SQ_26,  SQ_27,  SQ_28,  SQ_29,  SQ_30,      SQ_31,
        SQT_BD, SQT_BD, SQT_SN, SQT_HC, SQT_HO, SQT_CR, SQT_RD, _______,_______,SEQ_TT0,SEQ_TT1,SEQ_TT2,SEQ_TT3,SEQ_TT4,SEQ_TT5,SEQ_TT6,SEQ_TT7,
        SQ_SALL,SQ_SCLR,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    [_LOWER] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        KC_ESC,     KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_PSLS,KC_PSLS,KC_PAST,_______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,    KC_DEL,
        _______,    M_PSCR, _______,_______,_______,_______,_______,_______,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,    KC_BSLS,
        _______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,_______,_______,_______,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
        _______,_______,KC_APP, _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END
    ),
    [_RAISE] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        KC_ESC,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,_______,_______,_______,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,       KC_DEL,
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,    KC_QUOT,
        _______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_COLN,KC_DQUO,
        _______,_______,KC_F11, _______,KC_F12,_______,_______,_______,_______,_______,_______,_______,_______,KC_ESC,  _______,_______,_______
    ),
    [_ADJUST] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        SEQ,        MAC,    WIN,    MIDI,   RESET,  _______,_______,_______,_______,_______,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_RMOD,   _______,
        _______,    AU_TOG, CK_TOGG,MU_TOG, MU_MOD, _______,_______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,    _______,
        _______,_______,CK_RST, CK_DOWN,CK_UP,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MAC);
            }
            return false;
            break;
        case WIN: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WIN);
            }
            return false;
            break;
        case M_PSCR: // Mac's advanced screen capture
            if (record->event.pressed) {
                tap_code16(LSFT(LGUI(KC_5)));
            }
            return false;
            break;
        case SEQ_TOG: // Toggle Sqeuencer on/off
            if (record->event.pressed) {
                if(is_sequencer_on()) {
                    sequencer_off();
                    rgblight_set_layer_state(_SEQPLAYBACK, false);
                } else {
                    sequencer_on();
                    rgblight_set_layer_state(_SEQPLAYBACK, true);
                }
            }
            return false;
            break;
        case SEQ_TT0 ... SEQ_TT7:
            if (record->event.pressed) {
                sequencer_toggle_track_activation(keycode - SEQ_TT0);
                // if (is_sequencer_track_active(keycode - SEQ_TT0)) {
                //     sequencer_deactivate_track(keycode - SEQ_TT0);
                // } else {
                //     sequencer_activate_track(keycode - SEQ_TT0);
                // }
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_sequencer_on()) {
        switch (sequencer_get_current_step()) {
        case 0:
            rgblight_sethsv_at(HSV_RED, 4);
            break;
        case 16:
            rgblight_sethsv_at(HSV_BLUE, 4);
            break;
        case 4:
            rgblight_sethsv_at(HSV_RED, 5);
            break;
        case 20:
            rgblight_sethsv_at(HSV_BLUE, 5);
            break;
        case 8:
            rgblight_sethsv_at(HSV_RED, 6);
            break;
        case 24:
            rgblight_sethsv_at(HSV_BLUE, 6);
            break;
        case 12:
            rgblight_sethsv_at(HSV_RED, 7);
            break;
        case 28:
            rgblight_sethsv_at(HSV_BLUE, 7);
            break;
        default:
        // rgblight_sethsv_at(hsv_BLACK, 6);
            break;
        }
    }
 }

//------------------------------------------------------------------------------
// RGB Light settings
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define INDICATOR_INDEX 1        // where to start indicator
#define INDICATOR_COUNT 3         // how many leds for indicator
#define INDICATOR_CHANGE_COUNT 1  // how meny leds to change color for temporally layer
#define DIMMER_LEVEL 230          // brightness dimmer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_WHITE - DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_BLUE - DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_midi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_ORANGE - DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_sequencer_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_SPRINGGREEN - DIMMER_LEVEL}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_GREEN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_CYAN - DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_RED - DIMMER_LEVEL}
);

// for Lock indicator
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX + 2 , INDICATOR_CHANGE_COUNT, HSV_MAGENTA - DIMMER_LEVEL}
);

// for Sequencer Playback indicator
const rgblight_segment_t PROGMEM my_seqplayback_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX + 2 , INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_win_layer,
    my_midi_layer,
    my_sequencer_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer,
    my_caps_layer,
    my_seqplayback_layer
);

void keyboard_post_init_user(void) {
    debug_enable=true;
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    // Set effect range to non-indicator led range.
    // rgblight_set_effect_range(3, 5);

    // MIDI: Set octave to MI_OCT_0
    // midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // Reset the octave offset to 0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // Configure the sequencer to use the notes defined in the beginning of this file
    sequencer_set_track_notes(unison_sequencer_track_notes);

    // Sets the initial tempo to something that is closer to what I expect
    sequencer_set_tempo(100);
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_ADJUST, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_MAC, layer_state_cmp(state, _MAC));
    rgblight_set_layer_state(_WIN, layer_state_cmp(state, _WIN));
    rgblight_set_layer_state(_MIDI, layer_state_cmp(state, _MIDI));
    rgblight_set_layer_state(_SEQUENCER, layer_state_cmp(state, _SEQUENCER));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_CAPS, led_state.caps_lock);
    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {

        // case _MIDI:
        //     if (index == 0) { /* First encoder, Right side */
        //         if (clockwise) {
        //             tap_code(KC_VOLU);
        //         } else {
        //             tap_code(KC_VOLD);
        //         }
        //     } else if (index == 1) { /* Second encoder, Left side */
        //         if (clockwise) {
        //             if (midi_config.velocity < 127) {
        //                 if (midi_config.velocity < 115) {
        //                     midi_config.velocity += 13;
        //                 } else {
        //                     midi_config.velocity = 127;
        //                 }
        //             }
        //         } else {
        //             if (midi_config.velocity > 0) {
        //                 if (midi_config.velocity == 127) {
        //                     midi_config.velocity -= 10;
        //                 } else if (midi_config.velocity > 12) {
        //                     midi_config.velocity -= 13;
        //                 } else {
        //                     midi_config.velocity = 0;
        //                 }
        //             }
        //         }
        //     } else if (index == 2) {
        //         if (clockwise) {
        //             // TODO オクターブ変化、上端、下端の判定がおかしい
        //             if(midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN)) {
        //                 midi_config.octave++;
        //             }
        //         } else {
        //             if (midi_config.octave > 0) {
        //                 midi_config.octave--;
        //             }
        //         }
        //     } else if (index == 3) {
        //         if (clockwise) {
        //             if (midi_config.transpose < (MIDI_TRANSPOSE_MAX - MI_TRNS_0)) {
        //                 const bool positive = midi_config.transpose > 0;
        //                 midi_config.transpose++;
        //                 if (positive && midi_config.transpose < 0) {
        //                     midi_config.transpose--;
        //                 }
        //             }
        //         } else {
        //             if (midi_config.transpose > (MIDI_TRANSPOSE_MIN - MI_TRNS_0)) {
        //                 midi_config.transpose--;
        //             }
        //         }
        //     } else if (index == 4) {
        //         if (clockwise) {
        //             // rgblight_step();
        //             tap_code(KC_MS_WH_UP);
        //         } else {
        //             tap_code(KC_MS_WH_DOWN);
        //             // rgblight_step_reverse();
        //         }
        //     }
        //     break;

    if (index == 0) { /* First encoder, Left side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _SEQUENCER:
                if (clockwise) {
                    sequencer_increase_tempo();
                } else {
                    sequencer_decrease_tempo();
                }
                break;
            default:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
        }
    } else if (index == 2) {
        switch(biton32(default_layer_state)) {
            case _SEQUENCER:
                if (clockwise) {
                    sequencer_increase_resolution();
                } else {
                    sequencer_decrease_resolution();
                }
                break;
            default:
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    } else if (index == 3) {
        if (clockwise) {
            rgblight_increase_sat();
        } else {
            rgblight_decrease_sat();
        }
    } else if (index == 4) {
        if (clockwise) {
            rgblight_step();
            // tap_code(KC_MS_WH_UP);
        } else {
            rgblight_step_reverse();
            // tap_code(KC_MS_WH_DOWN);
        }
    }
}
#endif

        // switch(biton32(layer_state)) {
        //     case _LOWER:
        //         if (clockwise) {
        //             rgblight_decrease_hue();
        //         } else {
        //             rgblight_increase_hue();
        //         }
        //         break;
        //     case _RAISE:
        //         if (clockwise) {
        //             rgblight_decrease_val();
        //         } else {
        //             rgblight_increase_val();
        //         }
        //         break;
        //     case _ADJUST:
        //         if (clockwise) {
        //             rgblight_step_reverse();
        //         } else {
        //             rgblight_step();
        //         }
        //         break;
        //     default:
        //         if (clockwise) {
        //             tap_code(KC_VOLD);
        //         } else {
        //             tap_code(KC_VOLU);
        //         }
        //         break;
        // }
