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

//  define which MIDI ch to use.
//  Note that (actual MIDI ch# - 1) -> 0 .. 15 is used for coding.
//  ch1
#define DEFAULT_MAIN_CH_NUMBER 0
//  ch3
#define DEFAULT_SUB_CH_NUMBER  2
//  ch2
#define ALT_MAIN_CH_NUMBER     1
//  ch4
#define ALT_SUB_CH_NUMBER      3
static uint8_t midi_left_ch = DEFAULT_SUB_CH_NUMBER;       //  By default, DEFAULT_SUB_CH_NUMBER is used for left side when separated.

//  Channel settings for the Accordion Bass layer.
//  The bass and chord channels are separated as shown below by default.
//  Or Channel 1 (=0 in the coding) will be used for all.
//  Note that (actual MIDI ch# - 1) -> 0 .. 15 is used for coding.
//  ch2
#define SEPARATION_BASS_CH_NUMBER   2
//  ch3
#define SEPARATION_CHORD_CH_NUMBER  1
uint8_t midi_bass_ch = DEFAULT_MAIN_CH_NUMBER, midi_chord_ch = DEFAULT_MAIN_CH_NUMBER;  // By default, all use the same channel.

//  By default( when use_alt_ch_gr == false), DEFAULT ch group (DEFAULT_MAIN_CH_NUMBER for entirely, or right side when separated, DEFAULT_SUB_CH_NUMBER for left side) is used.
//  When false, ALT ch group (ALT_MAIN_CH_NUMBER for entirely, or right side when separated, ALT_SUB_CH_NUMBER for left side) is used.
static bool use_alt_ch_gr = false;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,              //  Base layer, shift mode, single channel.
    _SEPALEFTOCT,       //  1st oct channel separated version. Shift mode.
    _SEPAHALF,          //  Half channel separated version. Shift mode.
    _SEPARIGHTOCT,      //  2nd oct channel separated version. Shift mode.
    _CSYSTEM,           //  C-base chromatic button accordion
    _BSYSTEM,           //  B-base chromatic button accordion
    _TRANS,             //  Transpose feature is enabled instead of shift mode, single channel.
    _FLIPBASE,          //  Horizontal flipped version entirely. single channel.
    _FLIPTRANS,         //  Horizontal flipped version entirely. Transpose is used. single channel.
    _ACCORDIONBASS,     //  Accordion Bass layer.
    _QWERTY,            //  QWERTY keyboard layout.
    _FN                 //  FuNction layer. This must be at the end of the enumurate to use the range from _LS_FN ... _LS_FN_MAX for FN layer LED settings.
};

#define _LS_BASE           (1UL << _BASE)
#define _LS_SEPALEFTOCT    (1UL << _SEPALEFTOCT)
#define _LS_SEPAHALF       (1UL << _SEPAHALF)
#define _LS_SEPARIGHTOCT   (1UL << _SEPARIGHTOCT)
#define _LS_FLIPBASE       (1UL << _FLIPBASE)
#define _LS_ACCORDIONBASS  (1UL << _ACCORDIONBASS)

#define _LS_TRANS          (1UL << _BASE         | 1UL << _TRANS)
#define _LS_SEPALEFTOCT_T  (1UL << _SEPALEFTOCT  | 1UL << _TRANS)
#define _LS_SEPAHALF_T     (1UL << _SEPAHALF     | 1UL << _TRANS)
#define _LS_SEPARIGHTOCT_T (1UL << _SEPARIGHTOCT | 1UL << _TRANS)
#define _LS_FLIPTRANS      (1UL << _FLIPBASE     | 1UL << _FLIPTRANS)

#define _LS_QWERTY         (1UL << _QWERTY)
#define _LS_CSYSTEM        (1UL << _CSYSTEM)
#define _LS_BSYSTEM        (1UL << _BSYSTEM)

#define _LS_CSYSTEM_T      (1UL << _CSYSTEM      | 1UL << _TRANS)
#define _LS_BSYSTEM_T      (1UL << _BSYSTEM      | 1UL << _TRANS)

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
    // MY tone for _FLIPHALF and _FLIPLEFTOCT layers to distinguish the notes to avoid sustain effect, etc.
    // Since they are flipped, their subscripts are not MY_ but YM_, to make them easier to tell.
    YM_TONE_MIN = SAFE_RANGE,

    YM_C = YM_TONE_MIN,
    YM_Cs,
    YM_Db = YM_Cs,
    YM_D,
    YM_Ds,
    YM_Eb = YM_Ds,
    YM_E,
    YM_F,
    YM_Fs,
    YM_Gb = YM_Fs,
    YM_G,
    YM_Gs,
    YM_Ab = YM_Gs,
    YM_A,
    YM_As,
    YM_Bb = YM_As,
    YM_B,

    YM_C_1,
    YM_Cs_1,
    YM_Db_1 = YM_Cs_1,
    YM_D_1,
    YM_Ds_1,
    YM_Eb_1 = YM_Ds_1,
    YM_E_1,
    YM_F_1,
    YM_Fs_1,
    YM_Gb_1 = YM_Fs_1,
    YM_G_1,
    YM_Gs_1,
    YM_Ab_1 = YM_Gs_1,
    YM_A_1,
    YM_As_1,
    YM_Bb_1 = YM_As_1,
    YM_B_1,

    YM_C_2,
    YM_Cs_2,
    YM_Db_2 = YM_Cs_2,
    YM_D_2,
    YM_Ds_2,
    YM_Eb_2 = YM_Ds_2,
    YM_E_2,
    YM_F_2,
    YM_Fs_2,
    YM_Gb_2 = YM_Fs_2,
    YM_G_2,
    YM_Gs_2,
    YM_Ab_2 = YM_Gs_2,
    YM_A_2,
    YM_As_2,
    YM_Bb_2 = YM_As_2,
    YM_B_2,

    YM_C_3,
    YM_Cs_3,
    YM_Db_3 = YM_Cs_3,
    YM_D_3,
    YM_Ds_3,
    YM_Eb_3 = YM_Ds_3,
    YM_E_3,
    YM_F_3,
    YM_Fs_3,
    YM_Gb_3 = YM_Fs_3,
    YM_G_3,
    YM_Gs_3,
    YM_Ab_3 = YM_Gs_3,
    YM_A_3,
    YM_As_3,
    YM_Bb_3 = YM_As_3,
    YM_B_3,

    YM_C_4,
    YM_Cs_4,
    YM_Db_4 = YM_Cs_4,
    YM_D_4,
    YM_Ds_4,
    YM_Eb_4 = YM_Ds_4,
    YM_E_4,
    YM_F_4,
    YM_Fs_4,
    YM_Gb_4 = YM_Fs_4,
    YM_G_4,
    YM_Gs_4,
    YM_Ab_4 = YM_Gs_4,
    YM_A_4,
    YM_As_4,
    YM_Bb_4 = YM_As_4,
    YM_B_4,

    YM_C_5,
    YM_Cs_5,
    YM_Db_5 = YM_Cs_5,
    YM_D_5,
    YM_Ds_5,
    YM_Eb_5 = YM_Ds_5,
    YM_E_5,
    YM_F_5,
    YM_Fs_5,
    YM_Gb_5 = YM_Fs_5,
    YM_G_5,
    YM_Gs_5,
    YM_Ab_5 = YM_Gs_5,
    YM_A_5,
    YM_As_5,
    YM_Bb_5 = YM_As_5,
    YM_B_5,

    YM_C_6,
    YM_TONE_MAX = YM_C_6,


    // MIDI Chord Keycodes - Root notes
    MY_CHORD_MIN,

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

    B_BASE,            //  border set to the left end.
    B_LEFT,            //  border set to the 1st left octave.
    B_CENTER,          //  border set to the center.
    B_RIGHT,           //  border set to the 1st right octave.
    B_FLIP,            //  border set to the right end.

    SHIFT_L = USER00,
    SHIFT_R,
    TGLINDI,  //  ToGgLe INDIcator
    TGLINTR,  //  ToGgLe INdicator location {(_KEY01, _KEY13, _KEY25, _KEY37) or (_KEY02, _KEY14, _KEY26) / (_KEY12, _KEY24, _KEY36)}in TRans mode
    TGLTRNS,  //  ToGgLe TRaNS and shift
    TGLCHGR,  //  ToGgLe CH GRoup

    TGLBASS,  // ToGgLe BASS unison for the Accordion Bass layer.
    TGLMICH,  // ToGgLe MIdi CHannel separation for the Accordion Bass layer.
    ACCOBAS,  // ACCOdion BASs layer.
    QWERTY,
    CSYSTEM,
    BSYSTEM,
    VERSION
};

#define MY_CHORD_COUNT (MY_CHORD_MAX - MY_CHORD_MIN + 1)
static uint8_t chord_status[MY_CHORD_COUNT];
#define MY_TONE_COUNT (YM_TONE_MAX - YM_TONE_MIN + 1)
static uint8_t my_tone_status[MY_TONE_COUNT];

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;
static bool is_trans_mode = false;     //  By default, shift mode is chosen.

// To record the status of Bass Chord (single or dyad, default: dyad.)
typedef union {
    uint32_t raw;
    struct {
        bool    isSingleBass:1;
        uint8_t chord_ch:4;
        uint8_t bass_ch:4;
    };
} user_config_t;
user_config_t user_config;

#define IS_SINGLE_BASS()   (user_config.isSingleBass)

static uint8_t key_separator_col = _KEY01;  //  (_KEY01 .. _KEY37).     By default, _KEY01 (= _BASE layer) is chosen. _KEY13 = *LEFT, _KEY19 = *HALF, _KEY25 = *RIGHT, _KEY37 = _FLIPBASE and _FLIPTRANS.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
            MI_SUS,          MI_C_2, MI_D_2, MI_E_2,  MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
                                MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2, MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
            FN_MUTE,         MI_C_2, MI_D_2, MI_E_2,  MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            MI_BENDU,           MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2, MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
        SHIFT_L, SHIFT_R,    MI_C_2, MI_D_2, MI_E_2,  MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            MI_BENDD,           MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2, MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4
    ),

    /* 1 octave on the left side is ch2, others are ch1 (normal) */
    [_SEPALEFTOCT] = LAYOUT(
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2,     MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
                                YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2,     MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2,     MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2,     MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
        SHIFT_L, SHIFT_R,     YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2,     MI_C_3, MI_D_3, MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2,     MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4
    ),

    /* Half ch2, half ch1 (normal) */
    [_SEPAHALF] = LAYOUT(
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3,       MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
                                YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,    MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3,       MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,    MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
        SHIFT_L, SHIFT_R,     YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3,       MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,    MI_G_3, MI_A_3,  MI_B_3, MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4
    ),

    /* 2 octave on the left side is ch2, others are ch1 (normal) */
    [_SEPARIGHTOCT] = LAYOUT(
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3, YM_Fs_3, YM_Ab_3, YM_Bb_3,      MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
                                YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,  YM_G_3, YM_A_3,  YM_B_3,     MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
            _______,          YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3, YM_Fs_3, YM_Ab_3, YM_Bb_3,      MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,  YM_G_3, YM_A_3,  YM_B_3,     MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,
        SHIFT_L, SHIFT_R,     YM_C_2, YM_D_2, YM_E_2,  YM_Fs_2, YM_Ab_2, YM_Bb_2, YM_C_3, YM_D_3, YM_E_3, YM_Fs_3, YM_Ab_3, YM_Bb_3,      MI_C_4,  MI_D_4,  MI_E_4, MI_Fs_4, MI_Ab_4, MI_Bb_4, MI_C_5,
            _______,            YM_Db_2, YM_Eb_2, YM_F_2,  YM_G_2,  YM_A_2,  YM_B_2, YM_Db_3, YM_Eb_3, YM_F_3,  YM_G_3, YM_A_3,  YM_B_3,     MI_Db_4, MI_Eb_4, MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4
    ),

    /* C-System chromatic accordion */
    [_CSYSTEM] = LAYOUT(
            _______,         MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,  MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,  MI_Ab_5,
                                MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,   MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
            _______,         MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Fs_2, MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5, MI_A_5,
            _______,            MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,   MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,  MI_Ab_5,
        SHIFT_L, SHIFT_R,    MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,  MI_Bb_5,
            _______,            MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Fs_2,  MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5, MI_A_5
    ),

    /* B-System chromatic accordion */
    [_BSYSTEM] = LAYOUT(
            _______,         MI_C_1,  MI_Eb_1, MI_Gb_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Gb_2, MI_A_2,  MI_C_3,  MI_Eb_3, MI_Gb_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Gb_4,  MI_A_4,  MI_C_5, MI_Eb_5, MI_Gb_5,
                                MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,   MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,   MI_Bb_4, MI_Db_5, MI_E_5,
            _______,         MI_B,  MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,  MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,
            _______,            MI_C_1,  MI_Eb_1, MI_Gb_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Gb_2,  MI_A_2,  MI_C_3,  MI_Eb_3, MI_Gb_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Gb_4,  MI_A_4,  MI_C_5,  MI_Eb_5,
        SHIFT_L, SHIFT_R,    MI_Bb, MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,
            _______,            MI_B,  MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,   MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,   MI_Ab_4, MI_B_4,  MI_D_5
    ),

    /* TRANS   This layer must locate 1 layer below _FN layer. */
    [_TRANS] = LAYOUT(
            _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        MI_TRNSD, MI_TRNSU,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Flip Base    SFIFTUP and SHIFT_L are swapped. */
    [_FLIPBASE] = LAYOUT(
            MI_SUS,           MI_C_5, MI_Bb_4, MI_Ab_4,  MI_Fs_4, MI_E_4, MI_D_4, MI_C_4, MI_Bb_3, MI_Ab_3, MI_Fs_3, MI_E_3, MI_D_3, MI_C_3,  MI_Bb_2,  MI_Ab_2, MI_Fs_2, MI_E_2, MI_D_2, MI_C_2,
                                MI_B_4, MI_A_4, MI_G_4,  MI_F_4,  MI_Eb_4,  MI_Db_4, MI_B_3, MI_A_3, MI_G_3,  MI_F_3, MI_Eb_3,  MI_Db_3, MI_B_2, MI_A_2, MI_G_2,  MI_F_2,  MI_Eb_2,  MI_Db_2,
            _______,          MI_C_5, MI_Bb_4, MI_Ab_4,  MI_Fs_4, MI_E_4, MI_D_4, MI_C_4, MI_Bb_3, MI_Ab_3, MI_Fs_3, MI_E_3, MI_D_3, MI_C_3,  MI_Bb_2,  MI_Ab_2, MI_Fs_2, MI_E_2, MI_D_2, MI_C_2,
            MI_BENDU,           MI_B_4, MI_A_4, MI_G_4,  MI_F_4,  MI_Eb_4,  MI_Db_4, MI_B_3, MI_A_3, MI_G_3,  MI_F_3, MI_Eb_3,  MI_Db_3, MI_B_2, MI_A_2, MI_G_2,  MI_F_2,  MI_Eb_2,  MI_Db_2,
        SHIFT_L, SHIFT_R,     MI_C_5, MI_Bb_4, MI_Ab_4,  MI_Fs_4, MI_E_4, MI_D_4, MI_C_4, MI_Bb_3, MI_Ab_3, MI_Fs_3, MI_E_3, MI_D_3, MI_C_3,  MI_Bb_2,  MI_Ab_2, MI_Fs_2, MI_E_2, MI_D_2, MI_C_2,
            MI_BENDD,           MI_B_4, MI_A_4, MI_G_4,  MI_F_4,  MI_Eb_4,  MI_Db_4, MI_B_3, MI_A_3, MI_G_3,  MI_F_3, MI_Eb_3,  MI_Db_3, MI_B_2, MI_A_2, MI_G_2,  MI_F_2,  MI_Eb_2,  MI_Db_2
    ),

    /* Flip Trans   This layer must locate 1 layer above _FLIPBASE layer.  MI_TRNSU and MI_TRNSD are swapped. */
    [_FLIPTRANS] = LAYOUT(
            _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        MI_TRNSU, MI_TRNSD,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Accordion Bass */
    [_ACCORDIONBASS] = LAYOUT(
            MI_SUS,          MI_CH_Ar,  MI_CH_Er,    MI_CH_Br,     MI_CH_Gbr,    MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,   MI_CH_Bbr  , MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,     MI_CH_Gbr,    MI_CH_Dbr,    MI_CH_Abr,  MI_CH_Ebr,
                                MI_CH_Fr,  MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,     MI_CH_Er,     MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,   MI_CH_Fr,    MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,     MI_CH_Er,
            FN_MUTE,         MI_CH_Gbr, MI_CH_Dbr,   MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,     MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,    MI_CH_Dsr,    MI_CH_Asr,    MI_CH_Fr,   MI_CH_Cr,
            MI_OCTU,            MI_CH_Gb,  MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,      MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,    MI_CH_Cs,     MI_CH_Gs,     MI_CH_Ds,     MI_CH_As,     MI_CH_F,
        MI_VELD, MI_VELU,    MI_CH_Bm,  MI_CH_Gbm,   MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,   MI_CH_Csm,    MI_CH_Gsm,    MI_CH_Dsm,    MI_CH_Asm,  MI_CH_Fm,
            MI_OCTD,            MI_CH_BDom7, MI_CH_GbDom7, MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7, MI_CH_CsDom7, MI_CH_GsDom7, MI_CH_DsDom7, MI_CH_AsDom7
    ),

    [_QWERTY] = LAYOUT(
            XXXXXXX,          KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,
                                KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,   KC_9,      KC_0,    KC_MINS, KC_EQL,   KC_BSLS, KC_BSPC, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
            _______,          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_PSLS, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
            KC_UP,              KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,   KC_K,      KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LEFT,   KC_RGHT,   KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_RSFT, KC_RSFT, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
            KC_DOWN,            KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, KC_LANG2, KC_SPC, KC_SPC, KC_SPC, KC_LANG1,  KC_APP,  KC_RALT, KC_RGUI,  KC_RCTL, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PENT
    ),

    [_FN] =  LAYOUT(
            XXXXXXX,          B_BASE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, B_LEFT, XXXXXXX, XXXXXXX, B_CENTER, XXXXXXX, XXXXXXX, B_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, B_FLIP,
                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            _______,          B_BASE,  XXXXXXX, CSYSTEM, XXXXXXX, BSYSTEM, XXXXXXX, B_LEFT, XXXXXXX, XXXXXXX, B_CENTER, XXXXXXX, XXXXXXX, B_RIGHT, XXXXXXX, XXXXXXX,  QWERTY, XXXXXXX, XXXXXXX, B_FLIP,
            MI_VELD,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MI_OCTD, MI_OCTU,     B_BASE,  XXXXXXX, TGLBASS, ACCOBAS, TGLMICH, XXXXXXX, B_LEFT, XXXXXXX, XXXXXXX, B_CENTER, XXXXXXX, XXXXXXX, B_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, VERSION, XXXXXXX, B_FLIP,
            MI_VELD,            TGLINTR, TGLTRNS, TGLCHGR, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, RGB_SPD, RGB_SPI, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, EEP_RST, TGLINDI, RGB_TOG
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]          = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SEPALEFTOCT]   = { ENCODER_CCW_CW(_______, _______) },
    [_SEPAHALF]      = { ENCODER_CCW_CW(_______, _______) },
    [_SEPARIGHTOCT]  = { ENCODER_CCW_CW(_______, _______) },
    [_CSYSTEM]       = { ENCODER_CCW_CW(_______, _______) },
    [_BSYSTEM]       = { ENCODER_CCW_CW(_______, _______) },
    [_TRANS]         = { ENCODER_CCW_CW(_______, _______) },
    [_FLIPBASE]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FLIPTRANS]     = { ENCODER_CCW_CW(_______, _______) },
    [_ACCORDIONBASS] = { ENCODER_CCW_CW(_______, _______) },
    [_QWERTY]        = { ENCODER_CCW_CW(_______, _______) },
    [_FN]            = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
};
#endif

/* Define below to set C_SYSTEM layer as default. */
// #define C_SYSTEM_DEFAULT_MODE
/* Define below to tone down the LED appearance.  */
// #define LED_STANDARD_MODE
// commom codes called from eeconfig_init_user() and keyboard_post_init_user().
void my_init(void){
    //  Set octave to MI_OCT_1
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

    default_layer_set(_LS_BASE);
#ifdef C_SYSTEM_DEFAULT_MODE
    layer_state_set(_LS_CSYSTEM);
#else
    layer_state_set(_LS_BASE);
#endif

#ifdef RGB_MATRIX_ENABLE
    led_indicator_enable = false;
#   ifdef LED_STANDARD_MODE
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
#   else
    //  party mode (for LED soldering test. Enable rainbow color effect, and disable led_indicator to check all LEDs)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#   endif
#endif  // RGB_MATRIX_ENABLE
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD);
    rgb_matrix_sethsv(HSV_BLUE);
#endif  // RGB_MATRIX_ENABLE

    //  Reset Bass setting
    user_config.raw = 0;  // default: dyad
    eeconfig_update_user(user_config.raw);

    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
}

void keyboard_post_init_user(void) {
    for (uint8_t i = 0; i < MY_CHORD_COUNT; i++) {
        chord_status[i] = MIDI_INVALID_NOTE;
    }

    for (uint8_t i = 0; i < MY_TONE_COUNT; i++) {
        my_tone_status[i] = MIDI_INVALID_NOTE;
    }
    //  load EEPROM data for isSingleBass
    user_config.raw = eeconfig_read_user();

    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
}

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

void my_process_midi4single_note(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status) {
    uint8_t  mytone    = keycode - YM_TONE_MIN;
    uint16_t mykeycode = mytone + MIDI_TONE_MIN;
    // uint16_t mykeycode = keycode - YM_TONE_MIN;
    // uint8_t  mytone    = mykeycode - MIDI_TONE_MIN;
    uint8_t  velocity  = midi_config.velocity;
    // uprintf("keycode=%u,mykeycode=%u,mytone =%u,velo = %u\n", keycode, mykeycode, mytone, velocity);
    if (record->event.pressed) {
        if (my_tone_status[mytone] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(mykeycode);
            midi_send_noteon(&midi_device, channel, note, velocity);
            dprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            // uprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            my_tone_status[mytone] = note;  // store root_note status.
        }
    } else {
        uint8_t note = my_tone_status[mytone];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note, velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
            // uprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
        my_tone_status[mytone] = MIDI_INVALID_NOTE;
    }
}

void select_layer_state_set(void) {
    switch (key_separator_col) {
        case _KEY01:
            if (is_trans_mode) {
                layer_state_set(_LS_TRANS);
            } else {
                layer_state_set(_LS_BASE);
            }
            break;

        case _KEY05:  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
            if (is_trans_mode) {
                layer_state_set(_LS_CSYSTEM_T);
            } else {
                layer_state_set(_LS_CSYSTEM);
            }
            break;

        case _KEY07:  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
            layer_state_set(_LS_ACCORDIONBASS);
            break;

        case _KEY09:  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
            if (is_trans_mode) {
                layer_state_set(_LS_BSYSTEM_T);
            } else {
                layer_state_set(_LS_BSYSTEM);
            }
            break;

        case _KEY13:
            if (is_trans_mode) {
                layer_state_set(_LS_SEPALEFTOCT_T);
            } else {
                layer_state_set(_LS_SEPALEFTOCT);
            }
            break;

        case _KEY19:
            if (is_trans_mode) {
                layer_state_set(_LS_SEPAHALF_T);
            } else {
                layer_state_set(_LS_SEPAHALF);
            }
            break;

        case _KEY25:
            if (is_trans_mode) {
                layer_state_set(_LS_SEPARIGHTOCT_T);
            } else {
                layer_state_set(_LS_SEPARIGHTOCT);
            }
            break;

        case _KEY31:  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
            layer_state_set(_LS_QWERTY);
            break;

        case _KEY37:
            if (is_trans_mode) {
                layer_state_set(_LS_FLIPTRANS);
            } else {
                layer_state_set(_LS_FLIPBASE);
            }
            break;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t root_note = MIDI_INVALID_NOTE;  // Starting value for the root note of each chord

    uint8_t chord        = keycode - MY_CHORD_MIN;

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
                key_separator_col = _KEY01;
                select_layer_state_set();
            }
            break;

        case B_LEFT:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY13;
                select_layer_state_set();
            }
            break;

        case B_CENTER:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY19;
                select_layer_state_set();
            }
            break;

        case B_RIGHT:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY25;
                select_layer_state_set();
            }
            break;

        case B_FLIP:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY37;
                select_layer_state_set();
            }
            break;

        case QWERTY:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY31;  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
                select_layer_state_set();
            }
            break;

        case CSYSTEM:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY05;  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
                select_layer_state_set();
            }
            break;

        case BSYSTEM:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY09;  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
                select_layer_state_set();
            }
            break;

        case ACCOBAS:
            if (record->event.pressed) {
                reset_all();
                key_separator_col = _KEY07;  // Actually there is no separator for B_SYSTEM, C_SYSTEM, ACCOBAS and QWERTY. Used as a flag.
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
                switch (layer_state) {
                    case _LS_BASE:
                    case _LS_SEPALEFTOCT:
                    case _LS_SEPAHALF:
                    case _LS_SEPARIGHTOCT:
                    case _LS_FLIPBASE:
                    case _LS_CSYSTEM:
                    case _LS_BSYSTEM:
                        scale_indicator_col = shift_led_indicator_left(scale_indicator_col);
                        break;
                }
            }
            break;

        case SHIFT_R:
            if (record->event.pressed) {
                switch (layer_state) {
                    case _LS_BASE:
                    case _LS_SEPALEFTOCT:
                    case _LS_SEPAHALF:
                    case _LS_SEPARIGHTOCT:
                    case _LS_FLIPBASE:
                    case _LS_CSYSTEM:
                    case _LS_BSYSTEM:
                        scale_indicator_col = shift_led_indicator_right(scale_indicator_col);
                        break;
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
                    case _LS_SEPALEFTOCT_T  | (1UL << _FN):
                    case _LS_SEPAHALF_T     | (1UL << _FN):
                    case _LS_SEPARIGHTOCT_T | (1UL << _FN):
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

                    //  main function of the TGLINTR part 2. alternate the status of trans_mode_indicator_loc_sel.
                    case _LS_FLIPTRANS      | (1UL << _FN):
                        trans_mode_indicator_loc_sel = !trans_mode_indicator_loc_sel;

                        //  when trans_mode_indicator_loc_sel == false, change the scale indicator and transpose.
                        scale_indicator_col = trans_mode_indicator_loc_sel ? 0:11;
                        // when TGLINTR is pressed, it also change the initial transpose setting to follow the scale indicator.
                        if (scale_indicator_col == 11) {
                            midi_config.transpose = -1;
                        } else {
                            midi_config.transpose = 0;
                        }
                        break;

                    //  special treatment when TGLINTR is pressed in _LS_FLIPBASE layer.
                    case _LS_FLIPBASE       | (1UL << _FN):   // when in FLIPBASE layer && non-Trans mode, change it to Trans mode.
                        trans_mode_indicator_loc_sel = false;
                        scale_indicator_col = 11;
                        midi_config.transpose = -1;
                        is_trans_mode = true;
                        select_layer_state_set();
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

        case TGLCHGR:
            if (record->event.pressed) {
                use_alt_ch_gr = !use_alt_ch_gr;
                if (use_alt_ch_gr) {
                    midi_config.channel = ALT_MAIN_CH_NUMBER;
                    midi_left_ch = ALT_SUB_CH_NUMBER;
                } else {  //  default
                    midi_config.channel = DEFAULT_MAIN_CH_NUMBER;
                    midi_left_ch = DEFAULT_SUB_CH_NUMBER;
                }
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

        case  YM_TONE_MIN ... YM_TONE_MAX:  // MY tone
            // uprintf("keycode=%u, YM_C_3=%u, YM_Db_2 =%u, YM_MIN = %u, YM_MAX = %u\n", keycode, YM_C_3, YM_Db_2, YM_TONE_MIN, YM_TONE_MAX);
            //  DO NOT THROW BELOW into 'if (record->event.pressed) {}' STATEMENT SINCE IT IS USED IN THE FUNCTION BELOW.
            my_process_midi4single_note(midi_left_ch, keycode, record, my_tone_status);
            break;

        // MIDI Chord Keycodes, on the left side.
        case MI_CH_Cr ... MI_CH_Br:  // Root Notes
            root_note = keycode - MI_CH_Cr + MI_C_1;
            my_process_midi4Bass(midi_bass_ch, record, chord_status, chord, root_note, IS_SINGLE_BASS());
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C_2;
            // Major Third and Fifth Notes
            my_process_midi4DiadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7);
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C_2;
            // Minor Third and Fifth Notes
            my_process_midi4DiadChords(midi_chord_ch, record, chord_status, chord, root_note, 3, 7);
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C_2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7, 10);
            break;
    }
    return true;
}

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

void set_led_c_indicator(uint8_t layerNo, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t CorBsystem;
    uint8_t i;
    if (led_indicator_enable) {  //  turn on indicators when enabled.
        CorBsystem = ( layerNo == _BSYSTEM ) ? 1 : 0;
        for (i = 0; i < 10; i++) {
            rgb_matrix_set_color(led_c_indicator[CorBsystem][scale_indicator_col][i], r, g, b);
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    // uint32_t mode = rgblight_get_mode();

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        // uint8_t max_scale_indicator_led_loop;
        uint8_t i;

        switch (layer_state) {
            case _LS_BASE:
                set_led_scale_indicator(BASE_LAYER_COLOR);
                break;

            case _LS_FLIPBASE:
                set_led_scale_indicator(FLIPB_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY37][i], FLIP_BORDER_COLOR);    //  right end
                }
                break;

            case _LS_TRANS:
                set_led_scale_indicator(TRANS_LAYER_COLOR);
                break;

            case _LS_SEPALEFTOCT_T:
                set_led_scale_indicator(SEPALEFT_T_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY13][i], FLIP_BORDER_COLOR);    //  Left
                }
                break;

            case _LS_SEPAHALF_T:
                set_led_scale_indicator(SEPAHALF_T_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY19][i], FLIP_BORDER_COLOR);    //  Center
                }
                break;

            case _LS_SEPARIGHTOCT_T:
                set_led_scale_indicator(SEPARIGHT_T_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY25][i], FLIP_BORDER_COLOR);    //  Right
                }
                break;

            case _LS_FLIPTRANS:
                set_led_scale_indicator(FLIPT_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY37][i], FLIP_BORDER_COLOR);    //  right end
                }
                break;

            case _LS_SEPALEFTOCT:
                set_led_scale_indicator(SEPALEFT_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY13][i], FLIP_BORDER_COLOR);    //  Left
                }
                break;

            case _LS_SEPAHALF:
                set_led_scale_indicator(SEPAHALF_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY19][i], FLIP_BORDER_COLOR);    //  Center
                }
                break;

            case _LS_SEPARIGHTOCT:
                set_led_scale_indicator(SEPARIGHT_LAYER_COLOR);
                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY25][i], FLIP_BORDER_COLOR);    //  Right
                }
                break;

            case _LS_CSYSTEM:
                set_led_c_indicator(_CSYSTEM, BASE_LAYER_COLOR);
                break;

            case _LS_CSYSTEM_T:
                set_led_c_indicator(_CSYSTEM, TRANS_LAYER_COLOR);
                break;

            case _LS_BSYSTEM:
                set_led_c_indicator(_BSYSTEM, BASE_LAYER_COLOR);
                break;

            case _LS_BSYSTEM_T:
                set_led_c_indicator(_BSYSTEM, TRANS_LAYER_COLOR);
                break;

            case _LS_ACCORDIONBASS:
                // indicate C location
                if (led_indicator_enable) {  //  turn on indicators when enabled.
                    rgb_matrix_set_color(led_single_col_indicator[_KEY13][_MID37], BASE_LAYER_COLOR);         //  C
                    rgb_matrix_set_color(led_single_col_indicator[_KEY37][_MID37], BASE_LAYER_COLOR);         //  C
                }
                break;

            case _LS_FN ... _LS_MAX:  //  When Mute Button is long-pressed, the previous layers are still active.
                for (i = 1; i < 5; i++) {
                    rgb_matrix_set_color(i, RGB_DARKSPRINGGREEN);  //  up(1) down(4) left(3) right(2)  keys
                }
                rgb_matrix_set_color(led_single_col_indicator[_KEY02][_BTM37], RGB_DARKSPRINGGREEN);   //  TGLINTR
                rgb_matrix_set_color(led_single_col_indicator[_KEY04][_BTM37], RGB_DARKSPRINGGREEN);   //  TGLTRNS
                rgb_matrix_set_color(led_single_col_indicator[_KEY06][_BTM37], RGB_DARKSPRINGGREEN);   //  TGLCHGR

                rgb_matrix_set_color(led_single_col_indicator[_KEY05][_MID37], RGB_DARKCORAL);         //  CSYSTEM
                rgb_matrix_set_color(led_single_col_indicator[_KEY09][_MID37], RGB_DARKCORAL);         //  BSYSTEM
                rgb_matrix_set_color(led_single_col_indicator[_KEY31][_MID37], RGB_DARKCORAL);         //  QWERTY

                rgb_matrix_set_color(led_single_col_indicator[_KEY05][_BTM37], RGB_DARKTURQUOISE);     //  TGLBASS
                rgb_matrix_set_color(led_single_col_indicator[_KEY07][_BTM37], RGB_DARKCORAL);         //  ACCOBAS
                rgb_matrix_set_color(led_single_col_indicator[_KEY09][_BTM37], RGB_DARKTURQUOISE);     //  TGLMICH
                rgb_matrix_set_color(led_single_col_indicator[_KEY33][_BTM37], RGB_DARKGOLD);          //  VERSION

                for (i = 0; i < 3; i++) {
                    rgb_matrix_set_color(led_single_col_indicator[_KEY01][i], BASE_LAYER_COLOR);   //  B_BASE

                    rgb_matrix_set_color(led_single_col_indicator[_KEY13][i], SEPALEFT_LAYER_COLOR);   //  B_LEFT

                    rgb_matrix_set_color(led_single_col_indicator[_KEY19][i], SEPAHALF_LAYER_COLOR);   //  B_CENTER

                    rgb_matrix_set_color(led_single_col_indicator[_KEY25][i], SEPARIGHT_LAYER_COLOR);   //  B_RIGHT

                    rgb_matrix_set_color(led_single_col_indicator[_KEY37][i], FLIPB_LAYER_COLOR);   //  B_FLIP
                }

                for (i = _KEY12; i < _KEY37; i+=2){  //  even numbers from _KEY12 to _KEY36 are LED related settings.
                    // turn on the bottom row only to keep the visibility of the RGB MATRIX effects.
                    rgb_matrix_set_color(led_single_col_indicator[i][_BTM37], RGB_DARKSPRINGGREEN);  //       //  LED related settings.
                }
                break;
        }
    }
}
#endif  // RGB_MATRIX_ENABLE
