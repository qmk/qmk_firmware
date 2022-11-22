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
static bool is_trans_mode = false;     //  By default, shift mode is chosen.

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

//  use led indicator or not.
static bool led_indicator_enable = true;

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

    _TRANS,                   //  Transpose feature is enabled instead of shift mode,

    _FLIP_MIN,
    _FLIP = _FLIP_MIN,        //  MIDI chromatic scale (flipped)
    _FLIPCHORDS,              //  MIDI chords (flipped)
    _FLIPBASEANDCHORDS,       //  MIDI Base + Chords (flipped)
    _FLIPHEPTA,               //  MIDI heptatonic scale (flipped)
    _FLIPPENTA,               //  MIDI pentatonic scale (flipped)
    _FLIP_MAX = _FLIPPENTA,

    _FLIPTRANS,               //  Transpose feature is enabled instead of shift mode (flipped)

    _FN                  //  FN layer
};

//  Layer State
#define _LS_BASE                 (1UL << _BASE)
#define _LS_CHORDS               (1UL << _CHORDS)
#define _LS_BASEANDCHORDS        (1UL << _BASEANDCHORDS)
#define _LS_HEPTATONIC           (1UL << _HEPTATONIC)
#define _LS_PENTATONIC           (1UL << _PENTATONIC)

#define _LS_FLIP                 (1UL << _FLIP)
#define _LS_FLIPCHORDS           (1UL << _FLIPCHORDS)
#define _LS_FLIPBASEANDCHORDS    (1UL << _FLIPBASEANDCHORDS)
#define _LS_FLIPHEPTA            (1UL << _FLIPHEPTA)
#define _LS_FLIPPENTA            (1UL << _FLIPPENTA)

#define _LS_TRANS                (1UL << _BASE              | 1UL << _TRANS)
#define _LS_CHORDS_T             (1UL << _CHORDS            | 1UL << _TRANS)
#define _LS_BASEANDCHORDS_T      (1UL << _BASEANDCHORDS     | 1UL << _TRANS)
#define _LS_HEPTATONIC_T         (1UL << _HEPTATONIC        | 1UL << _TRANS)
#define _LS_PENTATONIC_T         (1UL << _PENTATONIC        | 1UL << _TRANS)

#define _LS_FLIP_T               (1UL << _FLIP              | 1UL << _FLIPTRANS)
#define _LS_FLIPCHORDS_T         (1UL << _FLIPCHORDS        | 1UL << _FLIPTRANS)
#define _LS_FLIPBASEANDCHORDS_T  (1UL << _FLIPBASEANDCHORDS | 1UL << _FLIPTRANS)
#define _LS_FLIPHEPTA_T          (1UL << _FLIPHEPTA         | 1UL << _FLIPTRANS)
#define _LS_FLIPPENTA_T          (1UL << _FLIPPENTA         | 1UL << _FLIPTRANS)

#define _LS_FN                   (1UL << _FN)
#define _LS_MAX                  (_LS_FN << 1)

//  Don't change the DEFAULT_SCALE_COL value below. It must be 0.
#define DEFAULT_SCALE_COL 0
static uint8_t scale_indicator_col = DEFAULT_SCALE_COL;

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

    BASELAY,                //  BASE LAYer
    CHORDSB,                //  CHORDS Base
    BASECHO,                //  BASE CHOrds
    HEPTATO,                //  HEPTATOnic
    PENTATO,                //  PENTATOnic

    FLIPBAS,                //  FLIP BASe
    FLIPCHO,                //  FLIP CHOrds
    FLIPBAC,                //  FLIP BAse Chords
    FLIPHEP,                //  FLIP HEPtatonic
    FLIPPEN,                //  FLIP PENtatonic


    TGLTRNS = USER00,       //  ToGgLe TRaNS and shift mode
    SHIFT_L,                //  SHIFT led indicator Left
    SHIFT_R,                //  SHIFT led indicator Right
    SHLAYER,                //  SHift LAYER
    TGLINDI,                //  ToGgLe INDIcator
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

static bool layerFlipMode = false;                  //  flip (true) or base (false)
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

    [_TRANS] = LAYOUT(
        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,
        _______,
        _______
    ),

    [_FLIP] = LAYOUT(
        _______,
        MI_C_5,         MI_B_4,         MI_Bb_4,        MI_A_4,         MI_Ab_4,        MI_G_4,         MI_Fs_4,        MI_F_4,         MI_E_4,         MI_Eb_4,        MI_D_4,         MI_Db_4,
        MI_C_4,         MI_B_3,         MI_Bb_3,        MI_A_3,         MI_Ab_3,        MI_G_3,         MI_Fs_3,        MI_F_3,         MI_E_3,         MI_Eb_3,        MI_D_3,         MI_Db_3,
        MI_C_3,         MI_B_2,         MI_Bb_2,        MI_A_2,         MI_Ab_2,        MI_G_2,         MI_Fs_2,        MI_F_2,         MI_E_2,         MI_Eb_2,        MI_D_2,         MI_Db_2,
        MI_C_2,         MI_B_1,         MI_Bb_1,        MI_A_1,         MI_Ab_1,        MI_G_1,         MI_Fs_1,        MI_F_1,         MI_E_1,         MI_Eb_1,        MI_D_1,         MI_Db_1,
        MI_C_1,         MI_B,           MI_Bb,          MI_A,           MI_Ab,
        _______,
        _______
    ),

    [_FLIPCHORDS] = LAYOUT(
        _______,
        MI_CH_Cr,       MI_CH_Br,       MI_CH_Bbr,      MI_CH_Ar,       MI_CH_Abr,      MI_CH_Gr,       MI_CH_Fsr,      MI_CH_Fr,       MI_CH_Er,       MI_CH_Ebr,      MI_CH_Dr,       MI_CH_Dbr,
        MI_CH_C,        MI_CH_B,        MI_CH_Bb,       MI_CH_A,        MI_CH_Ab,       MI_CH_G,        MI_CH_Fs,       MI_CH_F,        MI_CH_E,        MI_CH_Eb,       MI_CH_D,        MI_CH_Db,
        MI_CH_Cm,       MI_CH_Bm,       MI_CH_Bbm,      MI_CH_Am,       MI_CH_Abm,      MI_CH_Gm,       MI_CH_Fsm,      MI_CH_Fm,       MI_CH_Em,       MI_CH_Ebm,      MI_CH_Dm,       MI_CH_Dbm,
        MI_CH_CDom7,    MI_CH_BDom7,    MI_CH_BbDom7,   MI_CH_ADom7,    MI_CH_AbDom7,   MI_CH_GDom7,    MI_CH_FsDom7,   MI_CH_FDom7,    MI_CH_EDom7,    MI_CH_EbDom7,   MI_CH_DDom7,    MI_CH_DbDom7,
        MI_CH_CDim7,    MI_CH_BDim7,    MI_CH_BbDim7,   MI_CH_ADim7,    MI_CH_AbDim7,
        _______,
        _______
    ),

    [_FLIPBASEANDCHORDS] = LAYOUT(
        _______,
        MI_C_4,         MI_B_3,         MI_Bb_3,        MI_A_3,         MI_Ab_3,        MI_G_3,         MI_Fs_3,        MI_F_3,         MI_E_3,         MI_Eb_3,        MI_D_3,         MI_Db_3,
        MI_C_3,         MI_B_2,         MI_Bb_2,        MI_A_2,         MI_Ab_2,        MI_G_2,         MI_Fs_2,        MI_F_2,         MI_E_2,         MI_Eb_2,        MI_D_2,         MI_Db_2,
        MI_CH_Cr,       MI_CH_Br,       MI_CH_Bbr,      MI_CH_Ar,       MI_CH_Abr,      MI_CH_Gr,       MI_CH_Fsr,      MI_CH_Fr,       MI_CH_Er,       MI_CH_Ebr,      MI_CH_Dr,       MI_CH_Dbr,
        MI_CH_C,        MI_CH_B,        MI_CH_Bb,       MI_CH_A,        MI_CH_Ab,       MI_CH_G,        MI_CH_Fs,       MI_CH_F,        MI_CH_E,        MI_CH_Eb,       MI_CH_D,        MI_CH_Db,
        MI_CH_Cm,       MI_CH_Bm,       MI_CH_Bbm,      MI_CH_Am,       MI_CH_Abm,
        _______,
        _______
    ),

    [_FLIPHEPTA] = LAYOUT(
        _______,
        MI_C_5,         MI_B_4,         MI_A_4,         MI_G_4,         MI_F_4,         MI_E_4,         MI_D_4,
        MI_C_4,         MI_B_3,         MI_A_3,         MI_G_3,         MI_F_3,         MI_E_3,         MI_D_3,
        MI_C_3,         MI_B_2,         MI_A_2,         MI_G_2,         MI_F_2,         MI_E_2,         MI_D_2,
        MI_C_2,         MI_B_1,         MI_A_1,         MI_G_1,         MI_F_1,         MI_E_1,         MI_D_1,
        MI_C_1,         MI_B,           MI_A,           MI_G,           MI_F,           MI_E,           MI_D,
        MI_CH_C,        MI_CH_B,        MI_CH_A,        MI_CH_G,        MI_CH_F,        MI_CH_E,        MI_CH_D,
        MI_CH_Cm,       MI_CH_Bm,       MI_CH_Am,       MI_CH_Gm,       MI_CH_Fm,       MI_CH_Em,       MI_CH_Dm,
        MI_CH_CDom7,    MI_CH_BDom7,    MI_CH_ADom7,    MI_CH_GDom7,
        _______,
        _______
    ),

    [_FLIPPENTA] = LAYOUT(
        _______,
        MI_C_5,         MI_A_4,         MI_G_4,         MI_E_4,         MI_D_4,
        MI_C_4,         MI_A_3,         MI_G_3,         MI_E_3,         MI_D_3,
        MI_C_3,         MI_A_2,         MI_G_2,         MI_E_2,         MI_D_2,
        MI_C_2,         MI_A_1,         MI_G_1,         MI_E_1,         MI_D_1,
        MI_C_1,         MI_A,           MI_G,           MI_E,           MI_D,
        MI_CH_C,        MI_CH_A,        MI_CH_G,        MI_CH_E,        MI_CH_D,
        MI_CH_Cr,       MI_CH_Ar,       MI_CH_Gr,       MI_CH_Er,       MI_CH_Dr,
        MI_CH_Cm,       MI_CH_Am,       MI_CH_Gm,       MI_CH_Em,       MI_CH_Dm,
        MI_CH_CDom7,    MI_CH_ADom7,    MI_CH_GDom7,    MI_CH_EDom7,    MI_CH_DDom7,
        MI_CH_CDim7,    MI_CH_ADim7,    MI_CH_GDim7,    MI_CH_EDim7,    MI_CH_DDim7,
        XXXXXXX,        XXXXXXX,        XXXXXXX,
        _______,
        _______
    ),

    [_FLIPTRANS] = LAYOUT(
        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,
        _______,
        _______
    ),

    [_FN] = LAYOUT(
        _______,
        TGLBASS,        TGLMICH,        MELDYAL,        MELODYS,        MELDYAH,        TGLUVEL,        TGLTRNS,
        BASELAY,        CHORDSB,        BASECHO,        HEPTATO,        PENTATO,        XXXXXXX,        XXXXXXX,
        FLIPBAS,        FLIPCHO,        FLIPBAC,        FLIPHEP,        FLIPPEN,        XXXXXXX,        XXXXXXX,
        RGB_SAD,        RGB_SAI,        RGB_HUD,        RGB_HUI,        RGB_SPD,        RGB_SPI,        RGB_VAD,
        RGB_VAI,        RGB_RMOD,       RGB_MOD,        RGB_TOG,        TGLINDI,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        XXXXXXX,        VERSION,        EE_CLR,
        XXXXXXX,
        XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]              = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU), ENCODER_CCW_CW(SHIFT_L,  SHIFT_R)  },
    [_CHORDS]            = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_BASEANDCHORDS]     = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_HEPTATONIC]        = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_PENTATONIC]        = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_TRANS]             = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(MI_TRNSD, MI_TRNSU) },
    [_FLIP]              = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FLIPCHORDS]        = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FLIPBASEANDCHORDS] = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FLIPHEPTA]         = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FLIPPENTA]         = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FLIPTRANS]         = { ENCODER_CCW_CW(_______,  _______), ENCODER_CCW_CW(MI_TRNSU, MI_TRNSD) },
    [_FN]                = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(MI_OCTD,  MI_OCTU)  }
};
#endif


void reset_scale_indicator(void) {
    //  reset transpose value and scale_indicator_col to default.
    midi_config.transpose = 0;
    scale_indicator_col = DEFAULT_SCALE_COL;
}

void my_init(void){
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

    reset_scale_indicator();
    is_trans_mode = false;      //  trans mode is disabled by default.
}

void _load_eeprom_data(void){
    // no need to load isSingleBass since it's called directly by IS_SINGLE_BASS() macro.
    midi_chord_ch = user_config.chord_ch;
    midi_bass_ch = user_config.bass_ch;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();  // in midi_init(), octave is set to MI_OCT_2.
    my_init();    // Octave is set to MI_OCT_0, velocity is set to MIDI_INITIAL_VELOCITY. etc.

    // UNISON flags
    melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
    melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.
    melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

    //  Reset Bass setting
    user_config.raw = 0;  // default: dyad, chord_ch and bass_ch are DEFAULT_MAIN_CH_NUMBER.
    eeconfig_update_user(user_config.raw);
    _load_eeprom_data();

    //  Reset the midi keyboard layout
    default_layer_set(_LS_BASE);
    layer_state_set(_LS_BASE);
    current_default_layer = _BASE;
    layerFlipMode = false;

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
    _load_eeprom_data();

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(HSV_BLUE);
    //  party mode (for LED soldering test.)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
};


#ifdef RGB_MATRIX_ENABLE
void set_led_c_indicator(uint8_t scaleID, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t i;
    if (led_indicator_enable) {  //  turn on indicators when enabled.
        for (i = 0; i < MAXCINDICATORLED; i++) {
            rgb_matrix_set_color(led_c_indicator[scaleID][scale_indicator_col][i], r, g, b);
        }
        // rgb_matrix_set_color(led_c_indicator[scaleID][scale_indicator_col][0], r, g, b);
    }
}

void rgb_matrix_indicators_user(void) {
    uint8_t i;

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        switch (layer_state) {
            case _LS_BASE:
            case _LS_CHORDS:
            case _LS_BASEANDCHORDS:
                set_led_c_indicator(0, BASE_LAYER_COLOR);
                break;

            case _LS_HEPTATONIC:
                set_led_c_indicator(1, BASE_LAYER_COLOR);
                break;

            case _LS_PENTATONIC:
                set_led_c_indicator(2, BASE_LAYER_COLOR);
                break;

            case _LS_FLIP:
            case _LS_FLIPCHORDS:
            case _LS_FLIPBASEANDCHORDS:
                set_led_c_indicator(0, FLIPB_LAYER_COLOR);
                break;

            case _LS_FLIPHEPTA:
                set_led_c_indicator(1, FLIPB_LAYER_COLOR);
                break;

            case _LS_FLIPPENTA:
                set_led_c_indicator(2, FLIPB_LAYER_COLOR);
                break;


            case _LS_TRANS:
            case _LS_CHORDS_T:
            case _LS_BASEANDCHORDS_T:
            case _LS_FLIP_T:
            case _LS_FLIPCHORDS_T:
            case _LS_FLIPBASEANDCHORDS_T:
                set_led_c_indicator(0, TRANS_LAYER_COLOR);
                break;

            case _LS_HEPTATONIC_T:
            case _LS_FLIPHEPTA_T:
                set_led_c_indicator(1, TRANS_LAYER_COLOR);
                break;

            case _LS_PENTATONIC_T:
            case _LS_FLIPPENTA_T:
                set_led_c_indicator(2, TRANS_LAYER_COLOR);
                break;

            case _LS_FN ... _LS_MAX:  //  When Mute Button is long-pressed, the previous layers are still active.
                rgb_matrix_set_color(1,  RGB_DARKCORAL);        //  TGLBASS
                rgb_matrix_set_color(2,  RGB_DARKTEAL);         //  TGLMICH
                rgb_matrix_set_color(3,  RGB_DARKCYAN);         //  MELDYAL
                rgb_matrix_set_color(4,  RGB_DARKGOLD);         //  MELODYS
                rgb_matrix_set_color(5,  RGB_DARKSPRINGGREEN);  //  MELDYAH
                rgb_matrix_set_color(6,  RGB_DARKCORAL);        //  TGLUVEL
                rgb_matrix_set_color(7,  RGB_DARKCHARTREUSE);   //  TGLTRNS
                for (i = 8; i < 13; i++) {
                    rgb_matrix_set_color(i, RGB_DARKBLUE);      //  Base layers
                }
                for (i = 15; i < 20; i++) {
                    rgb_matrix_set_color(i, RGB_DARKBLUE);      //  Flip layers
                }

                for (i = 22; i < 32; i++) {
                    rgb_matrix_set_color(i, RGB_DARKBLUE);      //  RGB related settings
                }
                rgb_matrix_set_color(32, RGB_DARKRED);          //  RGB_TOG
                rgb_matrix_set_color(33, RGB_DARKSPRINGGREEN);  //  TGLINDI

                rgb_matrix_set_color(52, RGB_DARKGOLD);         //  VESRION
                rgb_matrix_set_color(53, RGB_DARKPINK);         //  EE_CLR
                break;
        }
    }
}

// set_scale_upperlimit() is called from shift_led_indicator_left() and shift_led_indicator_right().
// It also tells whether the layer is capable of shifting the scale indicator.
// Shifting is allowed only for chromatic layer = base and flip layer.
uint8_t set_scale_upperlimit(uint8_t layer) {
    switch (layer) {
        // allow chromatic layer to shift the indicator.
        case _BASE:
        case _FLIP:
            return 11;
            break;

        // Other layers are not chromatic. It is why others are disabled.
        // case _HEPTATONIC:
        // case _FLIPHEPTA:
        //     return 6;
        //     break;

        // case _PENTATONIC:
        // case _FLIPPENTA:
        //     return 4;
        //     break;

        case _CHORDS:
        case _FLIPCHORDS:
        case _BASEANDCHORDS:
        case _FLIPBASEANDCHORDS:
        case _HEPTATONIC:
        case _FLIPHEPTA:
        case _PENTATONIC:
        case _FLIPPENTA:
        default:
            return DEFAULT_SCALE_COL;  // this will disable the indicator shift.
            break;
    }
    return DEFAULT_SCALE_COL;  // error status, keeps the indicator to the initial position.
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
            if (is_trans_mode) {
                layer_state_set(_LS_TRANS);
            } else {
                layer_state_set(_LS_BASE);
            }
            break;

        case _CHORDS:
            layer_state_set(_LS_CHORDS_T);
            break;

        case _BASEANDCHORDS:
            layer_state_set(_LS_BASEANDCHORDS_T);
            break;

        case _HEPTATONIC:
            layer_state_set(_LS_HEPTATONIC_T);
            break;

        case _PENTATONIC:
            layer_state_set(_LS_PENTATONIC_T);
            break;

        case _FLIP:
            if (is_trans_mode) {
                layer_state_set(_LS_FLIP_T);
            } else {
                layer_state_set(_LS_FLIP);
            }
            break;

        case _FLIPCHORDS:
            layer_state_set(_LS_FLIPCHORDS_T);
            break;

        case _FLIPBASEANDCHORDS:
            layer_state_set(_LS_FLIPBASEANDCHORDS_T);
            break;

        case _FLIPHEPTA:
            layer_state_set(_LS_FLIPHEPTA_T);
            break;

        case _FLIPPENTA:
            layer_state_set(_LS_FLIPPENTA_T);
            break;

        default:
            layer_state_set(_LS_BASE);
            current_default_layer = _BASE;
            layerFlipMode = false;
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
                if (is_trans_mode) {
                    layer_state_set(_LS_TRANS);
                } else {
                    layer_state_set(_LS_BASE);
                }
                current_default_layer = _BASE;
                layerFlipMode = false;
                reset_scale_indicator();
            }
            break;

        case CHORDSB:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_CHORDS_T);
                } else {
                    layer_state_set(_LS_CHORDS);
                }
                current_default_layer = _CHORDS;
                layerFlipMode = false;
                reset_scale_indicator();
            }
            break;

        case BASECHO:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_BASEANDCHORDS_T);
                } else {
                    layer_state_set(_LS_BASEANDCHORDS);
                }
                current_default_layer = _BASEANDCHORDS;
                layerFlipMode = false;
                reset_scale_indicator();
            }
            break;

        case HEPTATO:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_HEPTATONIC_T);
                } else {
                    layer_state_set(_LS_HEPTATONIC);
                }
                current_default_layer = _HEPTATONIC;
                layerFlipMode = false;
                reset_scale_indicator();
            }
            break;

        case PENTATO:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_PENTATONIC_T);
                } else {
                    layer_state_set(_LS_PENTATONIC);
                }
                current_default_layer = _PENTATONIC;
                layerFlipMode = false;
                reset_scale_indicator();
            }
            break;


        case FLIPBAS:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_FLIP_T);
                } else {
                    layer_state_set(_LS_FLIP);
                }
                current_default_layer = _FLIP;
                layerFlipMode = true;
                reset_scale_indicator();
            }
            break;

        case FLIPCHO:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_FLIPCHORDS_T);
                } else {
                    layer_state_set(_LS_FLIPCHORDS);
                }
                current_default_layer = _FLIPCHORDS;
                layerFlipMode = true;
                reset_scale_indicator();
            }
            break;

        case FLIPBAC:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_FLIPBASEANDCHORDS_T);
                } else {
                    layer_state_set(_LS_FLIPBASEANDCHORDS);
                }
                current_default_layer = _FLIPBASEANDCHORDS;
                layerFlipMode = true;
                reset_scale_indicator();
            }
            break;

        case FLIPHEP:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_FLIPHEPTA_T);
                } else {
                    layer_state_set(_LS_FLIPHEPTA);
                }
                current_default_layer = _FLIPHEPTA;
                layerFlipMode = true;
                reset_scale_indicator();
            }
            break;

        case FLIPPEN:
            if (record->event.pressed) {
                if (is_trans_mode) {
                    layer_state_set(_LS_FLIPPENTA_T);
                } else {
                    layer_state_set(_LS_FLIPPENTA);
                }
                current_default_layer = _FLIPPENTA;
                layerFlipMode = true;
                reset_scale_indicator();
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
                scale_indicator_col = shift_led_indicator_left(scale_indicator_col, set_scale_upperlimit(current_default_layer));
            }
            break;

        case SHIFT_R:
            if (record->event.pressed) {
                scale_indicator_col = shift_led_indicator_right(scale_indicator_col, set_scale_upperlimit(current_default_layer));
            }
            break;

        case SHLAYER:
            if (record->event.pressed) {
                if (!layerFlipMode) {
                    //  base mode
                    if (++current_default_layer > _BASE_MAX) {
                        current_default_layer = _BASE_MIN;
                    }
                } else {
                    //  flip mode
                    if (++current_default_layer > _FLIP_MAX) {
                        current_default_layer = _FLIP_MIN;
                    }
                }
                reset_scale_indicator();
                select_layer_state_set();
            }
            break;

        case TGLINDI:
            if (record->event.pressed) {
                led_indicator_enable = !led_indicator_enable;
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
