/* Copyright 2021 Takeshi Nishio
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

static void display_sequencer_steps(uint8_t, uint8_t);
static uint8_t step_frame_index;

#define UNISON_MIDI_OCTAVE_MAX MIDI_OCTAVE_MAX - 1
#define UNISON_MIDI_OCTAVE_MIN MIDI_OCTAVE_MIN - 1

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

// Sequencer Tracks
const uint16_t unison_sequencer_track_notes[SEQUENCER_TRACKS] = {
    MI_C_1,
    MI_D_1,
    MI_Fs_1,
    MI_As_1,
    MI_Cs_2,
    MI_Ds_2,
    MI_D_2,
    MI_A_1,
};

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
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define SLS_LOW LT(_LOWER, KC_SLSH)
#define SFT_SLS RSFT_T(KC_SLSH)
#define C_SLSH  RCTL_T(KC_SLSH)
#define C_ESC   LCTL_T(KC_ESC)
#define CT_E    LCTL(KC_E)
#define CT_A    LCTL(KC_A)
#define ALT_GRV LALT(KC_GRV)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define HENKAN  LGUI(KC_GRV)
#define MIDI    DF(_MIDI)
#define ALT_EN  LALT_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define GUI_JA  LGUI_T(KC_LANG1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        XXXXXXX,XXXXXXX,KC_MUTE,XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,KC_MUTE,XXXXXXX,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
        C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,    KC_ENT,
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
        XXXXXXX,XXXXXXX,KC_MUTE,XXXXXXX,KC_1,   KC_2,   KC_3,   KC_4,   XXXXXXX,MI_VEL_9,XXXXXXX,MI_OCT_0,XXXXXXX,MI_TRNS_0,XXXXXXX,MI_CH1,XXXXXXX,
        MI_TRNSD,   MI_TRNS_0,MI_TRNSU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        MI_VELD,    MI_VEL_9,MI_VELU,  MI_Fs_1,MI_Gs_1,MI_As_1,XXXXXXX,MI_Cs_2,MI_Ds_2,XXXXXXX,MI_Fs_2,MI_Gs_2,MI_As_2,XXXXXXX,MI_Cs_3,    MI_Ds_3,
        _______,_______,_______,MI_F_1, MI_G_1, MI_A_1, MI_B_1, MI_C_2, MI_D_2, MI_E_2, MI_F_2, MI_G_2, MI_A_2, MI_B_2, MI_C_3, MI_D_3, MI_E_3,
        MI_OCTD,MI_OCT_0,MI_OCTU,XXXXXXX,XXXXXXX,LOWER,  LOWER,  XXXXXXX,XXXXXXX,XXXXXXX,RAISE,  RAISE,  RAISE,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
    ),
    [_SEQUENCER] = LAYOUT(
        _______, _______, _______, _______, SEQ_TOG, _______, SQ_TMPD, SQ_TMPU, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        SQ_S(0),     SQ_S(1), SQ_S(2), SQ_S(3), SQ_S(4), SQ_S(5), SQ_S(6), SQ_S(7), SQ_S(8), SQ_S(9), SQ_S(10),SQ_S(11),SQ_S(12),SQ_S(13),SQ_S(14),     SQ_S(15),
        SQ_S(16),    SQ_S(17),SQ_S(18),SQ_S(19),SQ_S(20),SQ_S(21),SQ_S(22),SQ_S(23),SQ_S(24),SQ_S(25),SQ_S(26),SQ_S(27),SQ_S(28),SQ_S(29),SQ_S(30),     SQ_S(31),
        SQ_T(0), SQ_T(0), SQ_T(1), SQ_T(2), SQ_T(3), SQ_T(4), SQ_T(5), SQ_T(6), SQ_T(7), _______, _______, _______, _______, _______, _______, _______, _______,
        SQ_SALL, SQ_SCLR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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

#define SEQ_LED_DIMMER 100
#define SEQ_LED_STEP_OFF_DIMMER 200


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC:
            if (record->event.pressed) {
                // revert LED animation
                rgblight_reload_from_eeprom();
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_MAC);
            }
            return false;
            break;
        case WIN:
            if (record->event.pressed) {
                // revert LED animation
                rgblight_reload_from_eeprom();
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_WIN);
            }
            return false;
            break;
        case M_PSCR: // Mac's advanced screen capture
            if (record->event.pressed) {
                tap_code16(LSFT(LGUI(KC_5)));
            } else {
                tap_code(KC_PSCR);
            }
            return false;
            break;
        case SEQ:
            if (record->event.pressed) {
                // Stop LED animation for Sequencer display.
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv_noeeprom(HSV_BLACK);
                // Change default layer
                default_layer_set(1UL << _SEQUENCER);
            }
            return false;
            break;
        case SEQ_TOG: // Toggle Sqeuencer playback on/off
            if (record->event.pressed) {
                if(is_sequencer_on()) {
                    sequencer_off();
                    rgblight_set_layer_state(_SEQPLAYBACK, false);
                    // 再生を停止したら、右4LEDにstepを表示
                } else {
                    sequencer_on();
                    rgblight_set_layer_state(_SEQPLAYBACK, true);
                }
            }
            return false;
            break;
        case SEQUENCER_TRACK_MIN ... SEQUENCER_TRACK_MAX:
            if (record->event.pressed) {
                if(is_sequencer_track_active(keycode - SEQUENCER_TRACK_MIN)) {
                    rgblight_sethsv_at(HSV_WHITE - SEQ_LED_DIMMER, 0);
                } else {
                    switch (keycode - SEQUENCER_TRACK_MIN) {
                    case 0:
                        rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, 0);
                        break;
                    case 1:
                        rgblight_sethsv_at(HSV_ORANGE - SEQ_LED_DIMMER, 0);
                        break;
                    case 2:
                        rgblight_sethsv_at(HSV_CHARTREUSE - SEQ_LED_DIMMER, 0);
                        break;
                    case 3:
                        rgblight_sethsv_at(HSV_GREEN - SEQ_LED_DIMMER, 0);
                        break;
                    case 4:
                        rgblight_sethsv_at(HSV_SPRINGGREEN - SEQ_LED_DIMMER, 0);
                        break;
                    case 5:
                        rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, 0);
                        break;
                    case 6:
                        rgblight_sethsv_at(HSV_PURPLE - SEQ_LED_DIMMER, 0);
                        break;
                    case 7:
                        rgblight_sethsv_at(HSV_MAGENTA - SEQ_LED_DIMMER, 0);
                        break;
                    default:
                        break;
                    }

                    // reset display frame index
                   if(!is_sequencer_on()) {
                        step_frame_index = 0;
                    }
                }
            }
            return true;  // continue processing keycode.
            break;
        default:
            break;
    }
    return true;
}

void display_sequencer_steps(uint8_t track, uint8_t index) {
    sequencer_activate_track(track);

    uint8_t hue;
    switch (step_frame_index) {
        case 0:
            hue = 0;    // red
            break;
        case 1:
            hue = 28;   // orange
            break;
        case 2:
            hue = 64;   // chartreuse
            break;
        case 3:
            hue = 85;   // green
            break;
        case 4:
            hue = 106;  // spring green
            break;
        case 5:
            hue = 170;  // blue
            break;
        case 6:
            hue = 191;  // purple
            break;
        case 7:
            hue = 213;  // magenta
            break;
    }

    if (is_sequencer_step_on(index * 4 + 0)) {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_DIMMER, 4);
    } else {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_STEP_OFF_DIMMER, 4);
    }

    if (is_sequencer_step_on(index * 4 + 1)) {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_DIMMER, 5);
    } else {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_STEP_OFF_DIMMER, 5);
    }

    if (is_sequencer_step_on(index * 4 + 2)) {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_DIMMER, 6);
    } else {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_STEP_OFF_DIMMER, 6);
    }

    if (is_sequencer_step_on(index * 4 + 3)) {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_DIMMER, 7);
    } else {
        rgblight_sethsv_at(hue, 255, 255 - SEQ_LED_STEP_OFF_DIMMER, 7);
    }
}

void matrix_scan_user(void) {
    if (biton32(default_layer_state) == _SEQUENCER) {
        if (is_sequencer_on()) {
            switch (sequencer_get_current_step()) {
            case 0:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, 4);
                break;
            case 4:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, 5);
                break;
            case 8:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, 6);
                break;
            case 12:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, 7);
                break;
            case 16:
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, 4);
                break;
            case 20:
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, 5);
                break;
            case 24:
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, 6);
                break;
            case 28:
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, 7);
                break;
            }
        } else {
            for (uint8_t i = 0; i < SEQUENCER_TRACKS; i++) {
                if (is_sequencer_track_active(i)) {
                    display_sequencer_steps(i, step_frame_index);
                }
            }
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
    if (index == 0) { /* 1st encoder, Left side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* 2nd encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    if (midi_config.velocity < 127) {
                        if (midi_config.velocity < 115) {
                            midi_config.velocity += 13;
                        } else {
                            midi_config.velocity = 127;
                        }
                    }
                } else {
                    if (midi_config.velocity > 0) {
                        if (midi_config.velocity == 127) {
                            midi_config.velocity -= 10;
                        } else if (midi_config.velocity > 12) {
                            midi_config.velocity -= 13;
                        } else {
                            midi_config.velocity = 0;
                        }
                    }
                }
                break;
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
    } else if (index == 2) { /* 3rd encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    // TODO オクターブ変化、上端、下端の判定がおかしい
                    // if(midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN)) {
                    if(midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN - 2)) {
                        midi_config.octave++;
                    }
                } else {
                    // if (midi_config.octave > 0) {
                    if (midi_config.octave > 0) {
                        midi_config.octave--;
                    }
                }
                break;
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
    } else if (index == 3) { /* 4th encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    if (midi_config.transpose < (MIDI_TRANSPOSE_MAX - MI_TRNS_0)) {
                        const bool positive = midi_config.transpose > 0;
                        midi_config.transpose++;
                        if (positive && midi_config.transpose < 0) {
                            midi_config.transpose--;
                        }
                    }
                } else {
                    if (midi_config.transpose > (MIDI_TRANSPOSE_MIN - MI_TRNS_0)) {
                        midi_config.transpose--;
                    }
                }
                break;
            case _SEQUENCER:
                if (clockwise) {
                    if (step_frame_index < (SEQUENCER_STEPS / 4 - 1) ) {
                        step_frame_index++;
                    }
                } else {
                    if (step_frame_index > 0) {
                        step_frame_index--;
                    }
                }
                break;
            default:
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    } else if (index == 4) { /* 5th encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    midi_config.channel++;
                } else {
                    midi_config.channel--;
                }
                break;
            default:
                if (clockwise) {
                    rgblight_step();
                    // tap_code(KC_MS_WH_UP);
                } else {
                    rgblight_step_reverse();
                    // tap_code(KC_MS_WH_DOWN);
                }
                break;
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

void keyboard_post_init_user(void) {
    // for debugging
    // debug_enable=true;

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#endif

    // Set effect range to non-indicator led range.
    // rgblight_set_effect_range(3, 5);

    // Reset the octave offset to 0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // Configure the sequencer to use the notes defined in the beginning of this file
    sequencer_set_track_notes(unison_sequencer_track_notes);

    // Sets the initial tempo to something that is closer to what I expect
    sequencer_set_tempo(100);
}
