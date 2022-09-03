/* Copyright 2022 3araht
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

// Long press: go to _FN , tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;

//  define which MIDI ch to use.
//  Note that (actual MIDI ch# - 1) -> 0 .. 15 is used for coding.
//  ch1
#define DEFAULT_MAIN_CH_NUMBER 0

//  Channel settings for the Accordion Bass .
//  The bass and chord channels are separated as shown below by default.
//  Or Channel 1 (=0 in the coding) will be used for all.
//  ch2
#define SEPARATION_CHORD_CH_NUMBER  1
//  ch3
#define SEPARATION_BASS_CH_NUMBER   2
uint8_t midi_bass_ch = DEFAULT_MAIN_CH_NUMBER, midi_chord_ch = DEFAULT_MAIN_CH_NUMBER;  // By default, all use the same channel.

// UNISON flags
static bool melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
static bool melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.


static bool melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

// To record the status of Bass Chord (single or dyad, default: dyad.)
typedef union {
    uint32_t raw;
    struct {
        bool isSingleBass:1;
        uint8_t chord_ch:4;
        uint8_t bass_ch:4;
    };
} user_config_t;
user_config_t user_config;

#define IS_SINGLE_BASS()   (user_config.isSingleBass)

// Defines names for use in  keycodes and the keymap
enum _names {
    _BASE_MIN,
    _BASE = _BASE_MIN,        //  MIDI chromatic scale
    _CHORDS,                  //  MIDI chords
    _BASEANDCHORDS,           //  MIDI Base + Chords
    _HEPTATONIC,              //  MIDI heptatonic scale
    _PENTATONIC,              //  MIDI pentatonic scale
    _BASE_MAX = _PENTATONIC,
    _FN,                      //  FN layer
};

//  Layer State
#define _LS_BASE                 (1UL << _BASE)
#define _LS_CHORDS               (1UL << _CHORDS)
#define _LS_BASEANDCHORDS        (1UL << _BASEANDCHORDS)
#define _LS_HEPTATONIC           (1UL << _HEPTATONIC)
#define _LS_PENTATONIC           (1UL << _PENTATONIC)

#define _LS_FN                   (1UL << _FN)
#define _LS_MAX                  (_LS_FN << 1)

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    // MIDI Chord Keycodes - Root notes
    MY_CHORD_MIN = SAFE_RANGE,

    MI_CH_Cr = MY_CHORD_MIN,
    MI_CH_Csr,
    MI_CH_Dbr = MI_CH_Csr,
    MI_CH_Dr,
    MI_CH_Dsr,
    MI_CH_Ebr = MI_CH_Dsr,
    MI_CH_Er,
    MI_CH_Fr,
    MI_CH_Fsr,
    MI_CH_Gbr = MI_CH_Fsr,
    MI_CH_Gr,
    MI_CH_Gsr,
    MI_CH_Abr = MI_CH_Gsr,
    MI_CH_Ar,
    MI_CH_Asr,
    MI_CH_Bbr = MI_CH_Asr,
    MI_CH_Br,

    // MIDI Chord Keycodes - Major

    MI_CH_C,
    MI_CH_Cs,
    MI_CH_Db = MI_CH_Cs,
    MI_CH_D,
    MI_CH_Ds,
    MI_CH_Eb = MI_CH_Ds,
    MI_CH_E,
    MI_CH_F,
    MI_CH_Fs,
    MI_CH_Gb = MI_CH_Fs,
    MI_CH_G,
    MI_CH_Gs,
    MI_CH_Ab = MI_CH_Gs,
    MI_CH_A,
    MI_CH_As,
    MI_CH_Bb = MI_CH_As,
    MI_CH_B,

    // MIDI Chord Keycodes Minor

    MI_CH_Cm,
    MI_CH_Csm,
    MI_CH_Dbm = MI_CH_Csm,
    MI_CH_Dm,
    MI_CH_Dsm,
    MI_CH_Ebm = MI_CH_Dsm,
    MI_CH_Em,
    MI_CH_Fm,
    MI_CH_Fsm,
    MI_CH_Gbm = MI_CH_Fsm,
    MI_CH_Gm,
    MI_CH_Gsm,
    MI_CH_Abm = MI_CH_Gsm,
    MI_CH_Am,
    MI_CH_Asm,
    MI_CH_Bbm = MI_CH_Asm,
    MI_CH_Bm,

    //MIDI Chord Keycodes Dominant Seventh

    MI_CH_CDom7,
    MI_CH_CsDom7,
    MI_CH_DbDom7 = MI_CH_CsDom7,
    MI_CH_DDom7,
    MI_CH_DsDom7,
    MI_CH_EbDom7 = MI_CH_DsDom7,
    MI_CH_EDom7,
    MI_CH_FDom7,
    MI_CH_FsDom7,
    MI_CH_GbDom7 = MI_CH_FsDom7,
    MI_CH_GDom7,
    MI_CH_GsDom7,
    MI_CH_AbDom7 = MI_CH_GsDom7,
    MI_CH_ADom7,
    MI_CH_AsDom7,
    MI_CH_BbDom7 = MI_CH_AsDom7,
    MI_CH_BDom7,

    // MIDI Chord Keycodes Diminished Seventh

    MI_CH_CDim7,
    MI_CH_CsDim7,
    MI_CH_DbDim7 = MI_CH_CsDim7,
    MI_CH_DDim7,
    MI_CH_DsDim7,
    MI_CH_EbDim7 = MI_CH_DsDim7,
    MI_CH_EDim7,
    MI_CH_FDim7,
    MI_CH_FsDim7,
    MI_CH_GbDim7 = MI_CH_FsDim7,
    MI_CH_GDim7,
    MI_CH_GsDim7,
    MI_CH_AbDim7 = MI_CH_GsDim7,
    MI_CH_ADim7,
    MI_CH_AsDim7,
    MI_CH_BbDim7 = MI_CH_AsDim7,
    MI_CH_BDim7,

    MY_CHORD_MAX = MI_CH_BDim7,


    BASELAY = USER00,       //  BASE LAYer
    CHORDSB,                //  CHORDS Base
    BASECHO,                //  BASE CHOrds
    HEPTATO,                //  HEPTATOnic
    PENTATO,                //  PENTATOnic

    SHLAYER,                //  SHift LAYER
    TGLBASS,                //  ToGgLe BASS unison
    TGLMICH,                //  ToGgLe MIdi CHannel separation
    MELDYAL,                //  MELody DYad Low
    MELODYS,                //  MELODY Single
    MELDYAH,                //  MELody DYad High
    TGLUVEL,                //  ToGgLe Unison VELocity

    VERSION
};

#define MY_CHORD_COUNT (MY_CHORD_MAX - MY_CHORD_MIN + 1)
static uint8_t chord_status[MY_CHORD_COUNT];
static uint8_t my_tone_status[MIDI_TONE_COUNT];

static uint8_t current_default_layer = _BASE;       //  locally saves the default layer value.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        FN_MUTE,
        MI_C_1,         MI_Db_1,        MI_D_1,         MI_Eb_1,        MI_E_1,         MI_F_1,         MI_Fs_1,        MI_G_1,         MI_Ab_1,        MI_A_1,         MI_Bb_1,        MI_B_1,
        MI_C_2,         MI_Db_2,        MI_D_2,         MI_Eb_2,        MI_E_2,         MI_F_2,         MI_Fs_2,        MI_G_2,         MI_Ab_2,        MI_A_2,         MI_Bb_2,        MI_B_2,
        MI_C_3,         MI_Db_3,        MI_D_3,         MI_Eb_3,        MI_E_3,         MI_F_3,         MI_Fs_3,        MI_G_3,         MI_Ab_3,        MI_A_3,         MI_Bb_3,        MI_B_3,
        MI_C_4,         MI_Db_4,        MI_D_4,         MI_Eb_4,        MI_E_4,         MI_F_4,         MI_Fs_4,        MI_G_4,         MI_Ab_4,        MI_A_4,         MI_Bb_4,        MI_B_4,
        MI_C_5,         MI_Db_5,        MI_D_5,         MI_Eb_5,        MI_E_5,
        SHLAYER,
        MI_SUS
    ),

    [_CHORDS] = LAYOUT(
        _______,
        MI_CH_Cr,       MI_CH_Dbr,      MI_CH_Dr,       MI_CH_Ebr,      MI_CH_Er,       MI_CH_Fr,       MI_CH_Fsr,      MI_CH_Gr,       MI_CH_Abr,      MI_CH_Ar,       MI_CH_Bbr,      MI_CH_Br,
        MI_CH_C,        MI_CH_Db,       MI_CH_D,        MI_CH_Eb,       MI_CH_E,        MI_CH_F,        MI_CH_Fs,       MI_CH_G,        MI_CH_Ab,       MI_CH_A,        MI_CH_Bb,       MI_CH_B,
        MI_CH_Cm,       MI_CH_Dbm,      MI_CH_Dm,       MI_CH_Ebm,      MI_CH_Em,       MI_CH_Fm,       MI_CH_Fsm,      MI_CH_Gm,       MI_CH_Abm,      MI_CH_Am,       MI_CH_Bbm,      MI_CH_Bm,
        MI_CH_CDom7,    MI_CH_DbDom7,   MI_CH_DDom7,    MI_CH_EbDom7,   MI_CH_EDom7,    MI_CH_FDom7,    MI_CH_FsDom7,   MI_CH_GDom7,    MI_CH_AbDom7,   MI_CH_ADom7,    MI_CH_BbDom7,   MI_CH_BDom7,
        MI_CH_CDim7,    MI_CH_DbDim7,   MI_CH_DDim7,    MI_CH_EbDim7,   MI_CH_EDim7,
        _______,
        _______
    ),

    [_BASEANDCHORDS] = LAYOUT(
        _______,
        MI_C_2,         MI_Db_2,        MI_D_2,         MI_Eb_2,        MI_E_2,         MI_F_2,         MI_Fs_2,        MI_G_2,         MI_Ab_2,        MI_A_2,         MI_Bb_2,       MI_B_2,
        MI_C_3,         MI_Db_3,        MI_D_3,         MI_Eb_3,        MI_E_3,         MI_F_3,         MI_Fs_3,        MI_G_3,         MI_Ab_3,        MI_A_3,         MI_Bb_3,       MI_B_3,
        MI_CH_C,        MI_CH_Db,       MI_CH_D,        MI_CH_Eb,       MI_CH_E,        MI_CH_F,        MI_CH_Fs,       MI_CH_G,        MI_CH_Ab,       MI_CH_A,        MI_CH_Bb,      MI_CH_B,
        MI_CH_Cm,       MI_CH_Dbm,      MI_CH_Dm,       MI_CH_Ebm,      MI_CH_Em,       MI_CH_Fm,       MI_CH_Fsm,      MI_CH_Gm,       MI_CH_Abm,      MI_CH_Am,       MI_CH_Bbm,     MI_CH_Bm,
        MI_CH_CDom7,    MI_CH_DbDom7,   MI_CH_DDom7,    MI_CH_EbDom7,   MI_CH_EDom7,
        _______,
        _______
    ),

    [_HEPTATONIC] = LAYOUT(
        _______,
        MI_C,           MI_D,           MI_E,           MI_F,           MI_G,           MI_A,           MI_B,
        MI_C_1,         MI_D_1,         MI_E_1,         MI_F_1,         MI_G_1,         MI_A_1,         MI_B_1,
        MI_C_2,         MI_D_2,         MI_E_2,         MI_F_2,         MI_G_2,         MI_A_2,         MI_B_2,
        MI_C_3,         MI_D_3,         MI_E_3,         MI_F_3,         MI_G_3,         MI_A_3,         MI_B_3,
        MI_C_4,         MI_D_4,         MI_E_4,         MI_F_4,         MI_G_4,         MI_A_4,         MI_B_4,
        MI_C_5,         MI_D_5,         MI_E_5,         MI_F_5,         MI_G_5,         MI_A_5,         MI_B_5,
        MI_CH_C,        MI_CH_D,        MI_CH_E,        MI_CH_F,        MI_CH_G,        MI_CH_A,        MI_CH_B,
        MI_CH_Cm,       MI_CH_Dm,       MI_CH_Em,       MI_CH_Fm,
        _______,
        _______
    ),

    [_PENTATONIC] = LAYOUT(
        _______,
        MI_C,           MI_D,           MI_E,           MI_G,           MI_A,
        MI_C_1,         MI_D_1,         MI_E_1,         MI_G_1,         MI_A_1,
        MI_C_2,         MI_D_2,         MI_E_2,         MI_G_2,         MI_A_2,
        MI_C_3,         MI_D_3,         MI_E_3,         MI_G_3,         MI_A_3,
        MI_C_4,         MI_D_4,         MI_E_4,         MI_G_4,         MI_A_4,
        MI_C_5,         MI_D_5,         MI_E_5,         MI_G_5,         MI_A_5,
        MI_CH_C,        MI_CH_D,        MI_CH_E,        MI_CH_G,        MI_CH_A,
        MI_CH_Cr,       MI_CH_Dr,       MI_CH_Er,       MI_CH_Gr,       MI_CH_Ar,
        MI_CH_Cm,       MI_CH_Dm,       MI_CH_Em,       MI_CH_Gm,       MI_CH_Am,
        MI_CH_CDom7,    MI_CH_DDom7,    MI_CH_EDom7,    MI_CH_GDom7,    MI_CH_ADom7,
        MI_CH_CDim7,    MI_CH_DDim7,    MI_CH_EDim7,
        _______,
        _______
    ),

    [_FN] = LAYOUT(
        _______,
        TGLBASS,        TGLMICH,        MELDYAL,        MELODYS,        MELDYAH,        TGLUVEL,        XXXXXXX,
        BASELAY,        CHORDSB,        BASECHO,        HEPTATO,        PENTATO,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        RGB_SAD,        RGB_SAI,        RGB_HUD,        RGB_HUI,        RGB_SPD,        RGB_SPI,        RGB_VAD,
        RGB_VAI,        RGB_RMOD,       RGB_MOD,        RGB_TOG,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        VERSION,        EEP_RST,
        XXXXXXX,
        XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]          = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(MI_TRNSD, MI_TRNSU) },
    [_CHORDS]        = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_BASEANDCHORDS] = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_HEPTATONIC]    = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_PENTATONIC]    = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FN]            = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(MI_OCTD,  MI_OCTU)  },
};
#endif

void reset_scale_indicator(void) {
    midi_config.transpose = 0;
}

void my_init(void){
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

    reset_scale_indicator();
}

void _load_eeprom_data(void){
    // no need to load isSingleBass since it's called directly by IS_SINGLE_BASS() macro.
    midi_chord_ch = user_config.chord_ch;
    midi_bass_ch = user_config.bass_ch;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();
    my_init();

    // Used to set octave to MI_OCT_0
    midi_bass_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

    // UNISON flags
    melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
    melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.
    melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

    //  Reset Bass setting
    user_config.raw = 0;  // default: dyad
    eeconfig_update_user(user_config.raw);
    _load_eeprom_data();

    //  Reset the midi keyboard layout
    default_layer_set(_LS_BASE);
    layer_state_set(_LS_BASE);
    current_default_layer = _BASE;

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(HSV_BLUE);
    //  party mode (for LED soldering test.)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
}

void keyboard_post_init_user(void) {
    my_init();

    for (uint8_t i = 0; i < MY_CHORD_COUNT; i++) {
        chord_status[i] = MIDI_INVALID_NOTE;
    }

    for (uint8_t i = 0; i < MIDI_TONE_COUNT; i++) {
        my_tone_status[i] = MIDI_INVALID_NOTE;
    }
    //  load EEPROM data for isSingleBass
    user_config.raw = eeconfig_read_user();

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(HSV_BLUE);
    //  party mode (for LED soldering test.)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
};


#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    uint8_t i;

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        switch (layer_state) {
            case _LS_FN ... _LS_MAX:  //  When Mute Button is long-pressed, the previous layers are still active.
                rgb_matrix_set_color(1,  RGB_DARKCORAL);        //  TGLBASS
                rgb_matrix_set_color(2,  RGB_DARKTEAL);         //  TGLMICH
                rgb_matrix_set_color(3,  RGB_DARKCYAN);         //  MELDYAL
                rgb_matrix_set_color(4,  RGB_DARKGOLD);         //  MELODYS
                rgb_matrix_set_color(5,  RGB_DARKSPRINGGREEN);  //  MELDYAH
                rgb_matrix_set_color(6,  RGB_DARKCORAL);        //  TGLUVEL

                for (i = 8; i < 16; i++) {
                    rgb_matrix_set_color(i, RGB_DARKBLUE);      //  Base layers
                }

                for (i = 22; i < 32; i++) {
                    rgb_matrix_set_color(i, RGB_DARKBLUE);      //  RGB related settings
                }
                rgb_matrix_set_color(32,  RGB_DARKRED);         //  RGB_TOG

                rgb_matrix_set_color(52, RGB_DARKGOLD);         //  VESRION
                rgb_matrix_set_color(53, RGB_DARKPINK);         //  EEP_RST
                break;
        }
    }
}
#endif

void toggle_isSingleBass(void) {
    user_config.isSingleBass = !user_config.isSingleBass;

    eeconfig_update_user(user_config.raw);
}

void toggle_MIDI_channel_separation(void) {
    if (midi_chord_ch > DEFAULT_MAIN_CH_NUMBER) {
        midi_chord_ch = DEFAULT_MAIN_CH_NUMBER;
        midi_bass_ch  = DEFAULT_MAIN_CH_NUMBER;
    } else {
        midi_chord_ch = SEPARATION_CHORD_CH_NUMBER;
        midi_bass_ch  = SEPARATION_BASS_CH_NUMBER;
    }

    user_config.chord_ch = midi_chord_ch;
    user_config.bass_ch =  midi_bass_ch;
    eeconfig_update_user(user_config.raw);
}

void select_layer_state_set(void){
    switch (current_default_layer) {
        case _BASE:
            layer_state_set(_LS_BASE);
            break;

        case _CHORDS:
            layer_state_set(_LS_CHORDS);
            break;

        case _BASEANDCHORDS:
            layer_state_set(_LS_BASEANDCHORDS);
            break;

        case _HEPTATONIC:
            layer_state_set(_LS_HEPTATONIC);
            break;

        case _PENTATONIC:
            layer_state_set(_LS_PENTATONIC);
            break;

        default:
            layer_state_set(_LS_BASE);
            current_default_layer = _BASE;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t root_note = MIDI_INVALID_NOTE;  // Starting value for the root note of each chord

    uint8_t chord        = keycode - MY_CHORD_MIN;

    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            break;

        //  set default layer and save it to EEPROM when MIDI key layers are selected.
        case BASELAY:
            if (record->event.pressed) {
                current_default_layer = _BASE;
                set_single_persistent_default_layer(current_default_layer);  // write it to eeprom.
                reset_scale_indicator();
                select_layer_state_set();                                    // this is rewuired.
            }
            break;

        case CHORDSB:
            if (record->event.pressed) {
                current_default_layer = _CHORDS;
                set_single_persistent_default_layer(current_default_layer);  // write it to eeprom.
                reset_scale_indicator();
                select_layer_state_set();                                    // this is rewuired.
            }
            break;

        case BASECHO:
            if (record->event.pressed) {
                current_default_layer = _BASEANDCHORDS;
                set_single_persistent_default_layer(current_default_layer);  // write it to eeprom.
                reset_scale_indicator();
                select_layer_state_set();                                    // this is rewuired.
            }
            break;

        case HEPTATO:
            if (record->event.pressed) {
                current_default_layer = _HEPTATONIC;
                set_single_persistent_default_layer(current_default_layer);  // write it to eeprom.
                reset_scale_indicator();
                select_layer_state_set();                                    // this is rewuired.
            }
            break;

        case PENTATO:
            if (record->event.pressed) {
                current_default_layer = _PENTATONIC;
                set_single_persistent_default_layer(current_default_layer);  // write it to eeprom.
                reset_scale_indicator();
                select_layer_state_set();                                    // this is rewuired.
            }
            break;


        case SHLAYER:
            if (record->event.pressed) {
                //  base mode
                if (++current_default_layer > _BASE_MAX) {
                    current_default_layer = _BASE_MIN;
                }
                reset_scale_indicator();
                select_layer_state_set();
            }
            break;

        case TGLBASS:
            if (record->event.pressed) {
                toggle_isSingleBass();
            };
            break;

        case TGLMICH:
            if (record->event.pressed) {
                toggle_MIDI_channel_separation();
            };
            break;

        case MELDYAL:
            if (record->event.pressed) {
                melody_dyad_low  = true;
                melody_dyad_high = false;
            };
            break;

        case MELODYS:
            if (record->event.pressed) {
                melody_dyad_low  = false;
                melody_dyad_high = false;
            };
            break;

        case MELDYAH:
            if (record->event.pressed) {
                melody_dyad_low  = false;
                melody_dyad_high = true;
            };
            break;

        case TGLUVEL:
            if (record->event.pressed) {
                melody_unison_suppress = !melody_unison_suppress;
            };
            break;

        // MIDI Chord Keycodes, on the left side.
        case MI_CH_Cr ... MI_CH_Br:  // Root Notes
            root_note = keycode - MI_CH_Cr + MI_C_1;
            my_process_midi4Bass(midi_bass_ch, record, chord_status, chord, root_note, IS_SINGLE_BASS());
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C_2;
            // Root, Major Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 4, 7);
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C_2;
            // Root, Minor Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 7);
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C_2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7, 10);
            break;

        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C_2;
            // Root, Minor Third, and Diminished 5th Note
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 6);
            break;

        case MIDI_TONE_MIN ... MIDI_TONE_MAX:
            //  root_note is played by process_midi().
            if ( melody_dyad_high == true ) {        //  play 1 octave higher as well.
                my_process_midi(0, keycode, record, my_tone_status, 12, melody_unison_suppress);
            } else if ( melody_dyad_low == true ) {  //  play 1 octave lower as well.
                my_process_midi(0, keycode, record, my_tone_status, -12, melody_unison_suppress);
            }
            break;

    }
    return true;
}
