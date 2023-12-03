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

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif
extern volatile bool isLeftHand;

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define DF_CBAS  DF(_C_SYSTEM_BASE)
#define DF_CNTC  DF(_C_SYSTEM_BASS2ROW)
#define DF_CENT  DF(_C_SYSTEM_ENTIRELY)
#define DF_CHRO  DF(_CHROMATONE)

#define DF_QWER  DF(_QWERTY)
#define DF_COLE  DF(_COLEMAK)
#define MO_ADJ   MO(_ADJUST)
// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define SHIF_UP  RSFT_T(KC_UP)
#define ADJ_EIS  LT(_ADJUST,KC_LNG2)
#define MIS_KAN  LT(_MISC,KC_LNG1)

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC__L___________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC__R___________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

// Used to set octave to QK_MIDI_OCTAVE_0
extern midi_config_t midi_config;
uint8_t midi_bass_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

// UNISON flags
static bool melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
static bool melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.


static bool melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;

led_config_t g_led_config = {
    {
        { NO_LED, NO_LED, 11,  10,  9,   8,   7  },
        { NO_LED, NO_LED, 12,  13,  14,  15,  16 },
        { NO_LED, NO_LED, 35,  34,  33,  32,  31 },
        { NO_LED, NO_LED, 36,  37,  38,  39,  40 },
        { NO_LED, NO_LED, 59,  58,  57,  56,  55 },

        { 0,      1,      2,   3,   4,   5,   6  },
        { 23,     22,     21,  20,  19,  18,  17 },
        { 24,     25,     26,  27,  28,  29,  30 },
        { 47,     46,     45,  44,  43,  42,  41 },
        { 48,     49,     50,  51,  52,  53,  54 },


        { 60,     61,     62,  63,  64,  65,  66  },
        { 84,     83,     82,  81,  80,  79,  78  },
        { 85,     86,     87,  88,  89,  90,  91  },
        { 110,    109,    108, 107, 106, 105, 104 },
        { NO_LED, 111,    112, 113, 114, 115, 116 },

        { NO_LED, NO_LED, 71,  70,  69,  68,  67  },
        { NO_LED, 72,     73,  74,  75,  76,  77  },
        { NO_LED, 97,     96,  95,  94,  93,  92  },
        { NO_LED, 98,     99,  100, 101, 102, 103 },
        { NO_LED, 122,    121, 120, 119, 118, 117 }
    }, {
        {  88,  0 }, {  80,  0 }, {  72,  0 }, {  64,  0 }, {  56,  0 }, {  48,  0 }, {  40,  0 }, {  32,  0 }, {  24,  0 }, {  16,  0 }, {   8,  0 }, {   0,  0 },
        {   4, 16 }, {  12, 16 }, {  20, 16 }, {  28, 16 }, {  36, 16 }, {  44, 16 }, {  52, 16 }, {  60, 16 }, {  68, 16 }, {  76, 16 }, {  84, 16 }, {  92, 16 },
        {  96, 32 }, {  88, 32 }, {  80, 32 }, {  72, 32 }, {  64, 32 }, {  56, 32 }, {  48, 32 }, {  40, 32 }, {  32, 32 }, {  24, 32 }, {  16, 32 }, {   8, 32 },
        {  12, 48 }, {  20, 48 }, {  28, 48 }, {  36, 48 }, {  44, 48 }, {  52, 48 }, {  60, 48 }, {  68, 48 }, {  76, 48 }, {  84, 48 }, {  92, 48 }, { 100, 48 },
        { 104, 64 }, {  96, 64 }, {  88, 64 }, {  80, 64 }, {  72, 64 }, {  64, 64 }, {  56, 64 }, {  48, 64 }, {  40, 64 }, {  32, 64 }, {  24, 64 }, {  16, 64 },

        { 120,  0 }, { 128,  0 }, { 136,  0 }, { 144,  0 }, { 152,  0 }, { 160,  0 }, { 168,  0 }, { 176,  0 }, { 184,  0 }, { 192,  0 }, { 200,  0 }, { 208,  0 },
        { 212, 16 }, { 204, 16 }, { 196, 16 }, { 188, 16 }, { 180, 16 }, { 172, 16 }, { 164, 16 }, { 156, 16 }, { 148, 16 }, { 140, 16 }, { 132, 16 }, { 124, 16 }, { 116, 16 },
        { 120, 32 }, { 128, 32 }, { 136, 32 }, { 144, 32 }, { 152, 32 }, { 160, 32 }, { 168, 32 }, { 176, 32 }, { 184, 32 }, { 192, 32 }, { 200, 32 }, { 208, 32 },        { 224, 32 },
        { 212, 48 }, { 204, 48 }, { 196, 48 }, { 188, 48 }, { 180, 48 }, { 172, 48 }, { 164, 48 }, { 156, 48 }, { 148, 48 }, { 140, 48 }, { 132, 48 }, { 124, 48 }, { 116, 48 },
        { 120, 64 }, { 128, 64 }, { 136, 64 }, { 144, 64 }, { 152, 64 }, { 160, 64 }, { 168, 64 }, { 176, 64 }, { 184, 64 }, { 192, 64 }, { 200, 64 }, { 208, 64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

#endif

// To record the status of Bass Chord (single or dyad, default: dyad.)
typedef union {
    uint32_t raw;
    struct {
        bool isSingleBass:1;
    };
} user_config_t;
user_config_t user_config;

#define IS_SINGLE_BASS()   (user_config.isSingleBass)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _C_SYSTEM_BASE,      //  C-system
    _B_SYSTEM,           //  B-system
    _C_SYSTEM_BASS2ROW,  //  counter bass C-system
    _B_SYSTEM_BASS2ROW,  //  counter bass B-system
    _C_SYSTEM_ENTIRELY,  //  single notes for both left and right keybaords.
    _CHROMATONE,
    _CFLIP_BASS2ROW,     //  180 degree flipped layout on right side keyboard
    _QWERTY,
    _COLEMAK,
    _ADJUST,             //  for Fn keys, etc.
    _FN,                 //  for changing layers, octaves, etc.
    _RESERVED            //  Reserved
};

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

    VERSION = QK_KB_0,
    CSYSTEM,  // C-SYSTEM layout
    BSYSTEM,  // B-SYSTEM layout
    CNTBASC,  // CouNTer BASs C-system layout
    CNTBASB,  // CouNTer BASs B-system layout
    CSYSALL,  // C-SYStem ALL layout
    CHRTONE,  // CHRomaTONE layout
    CFLIP2B,  // C-system FLIPped 2(to) Backwards
    TGLBASS,  // ToGgLe BASS unison
    TGLMICH,  // ToGgLe MIdi CHannel separation
    MELDYAL,  // MELody DYad Low
    MELODYS,  // MELODY Single
    MELDYAH,  // MELody DYad High
    TGLUVEL   // ToGgLe Unison VELocity
};

#define MY_CHORD_COUNT (MY_CHORD_MAX - MY_CHORD_MIN + 1)
static uint8_t chord_status[MY_CHORD_COUNT];
static uint8_t my_tone_status[MIDI_TONE_COUNT];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* C-system Base */
  [_C_SYSTEM_BASE] = LAYOUT(
    DF_CBAS, DF_CNTC, MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
      DF_CENT, DF_CHRO, MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
        TGLMICH, DF_QWER, MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
          TGLBASS, KC_VOLU, MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,
            FN_MUTE, KC_VOLD, MI_CH_DbDim7, MI_CH_AbDim7, MI_CH_EbDim7, MI_CH_BbDim7, MI_CH_FDim7, MI_CH_CDim7, MI_CH_GDim7, MI_CH_DDim7, MI_CH_ADim7, MI_CH_EDim7, MI_CH_BDim7, MI_CH_FsDim7,

              MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,             MI_OCTD,  MI_OCTU,
            MI_Fs2, MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,               MI_BNDU,
              MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,    FN_MUTE,
            MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,                MI_BNDD,
    MI_SUST,   MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,            MI_TRSD, MI_TRSU
  ),

  /* B-system */
  [_B_SYSTEM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

              MI_Bb2, MI_Db3, MI_E3,  MI_G3, MI_Bb3, MI_Db4, MI_E4,  MI_G4, MI_Bb4, MI_Db5, MI_E5,  MI_G5,               _______, _______,
            MI_Ab2, MI_B2,  MI_D3,  MI_F3, MI_Ab3, MI_B3,  MI_D4,  MI_F4, MI_Ab4, MI_B4,  MI_D5,  MI_F5, MI_Ab5,                 _______,
              MI_A2,  MI_C3,  MI_Eb3, MI_Gb3, MI_A3, MI_C4,  MI_Eb4, MI_Gb4, MI_A4, MI_C5,  MI_Eb5, MI_Gb5,     _______,
            MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3, MI_Bb3, MI_Db4, MI_E4,  MI_G4, MI_Bb4, MI_Db5, MI_E5,  MI_G5,                 _______,
    _______,  MI_Ab2, MI_B2,  MI_D3,  MI_F3, MI_Ab3, MI_B3,  MI_D4,  MI_F4, MI_Ab4, MI_B4,  MI_D5,  MI_F5,               _______, _______
  ),

  /* BASS2row */
  [_C_SYSTEM_BASS2ROW] = LAYOUT(
    _______, _______, MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      _______, _______, MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        _______, _______, MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          _______, _______, MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            _______, _______, MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,


              MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,             _______, _______,
            MI_Fs2, MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,              _______,
              MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,    _______,
            MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,               _______,
    _______,  MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,            _______, _______
  ),

  /* BASS2row */
  [_B_SYSTEM_BASS2ROW] = LAYOUT(
    _______, _______, MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      _______, _______, MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        _______, _______, MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          _______, _______, MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            _______, _______, MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

              MI_Bb2, MI_Db3, MI_E3,  MI_G3, MI_Bb3, MI_Db4, MI_E4,  MI_G4, MI_Bb4, MI_Db5, MI_E5,  MI_G5,               _______, _______,
            MI_Ab2, MI_B2,  MI_D3,  MI_F3, MI_Ab3, MI_B3,  MI_D4,  MI_F4, MI_Ab4, MI_B4,  MI_D5,  MI_F5, MI_Ab5,                 _______,
              MI_A2,  MI_C3,  MI_Eb3, MI_Gb3, MI_A3, MI_C4,  MI_Eb4, MI_Gb4, MI_A4, MI_C5,  MI_Eb5, MI_Gb5,     _______,
            MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3, MI_Bb3, MI_Db4, MI_E4,  MI_G4, MI_Bb4, MI_Db5, MI_E5,  MI_G5,                 _______,
    _______,  MI_Ab2, MI_B2,  MI_D3,  MI_F3, MI_Ab3, MI_B3,  MI_D4,  MI_F4, MI_Ab4, MI_B4,  MI_D5,  MI_F5,               _______, _______
  ),

  /* C-system entirely */
  [_C_SYSTEM_ENTIRELY] = LAYOUT(
    _______, _______, MI_BNDU, XXXXXXX, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db1, MI_E1,  MI_G1,  MI_Bb1, MI_Db2,
      _______, _______, MI_BNDD, XXXXXXX, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C1,  MI_Eb1, MI_Fs1, MI_A1,  MI_C2,  MI_Eb2,
        _______, _______, XXXXXXX, XXXXXXX, MI_D,    MI_F,    MI_Ab,   MI_B,    MI_D1,  MI_F1,  MI_Ab1, MI_B1,  MI_D2,  MI_F2,
          _______, _______, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db1, MI_E1,  MI_G1,  MI_Bb1, MI_Db2, MI_E2,  MI_G2,
            _______, _______, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C1,  MI_Eb1, MI_Fs1, MI_A1,  MI_C2,  MI_Eb2, MI_Fs2, MI_A2,

              MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,                _______, _______,
            MI_Fs2, MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,                 _______,
              MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,       _______,
            MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,                  _______,
    _______,  MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5,               _______, _______
  ),

  /* Chromatone */
  [_CHROMATONE] = LAYOUT(
    _______, _______, MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,
      _______, _______, MI_D,    MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C1,  MI_D1,  MI_E1,  MI_Fs1, MI_Ab1, MI_Bb1, MI_C2,
        _______, _______, MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,  MI_Db2,
          _______, _______, MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C1,  MI_D1,  MI_E1,  MI_Fs1, MI_Ab1, MI_Bb1, MI_C2,  MI_D2,
            _______, _______, MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,  MI_Db2, MI_Eb2,

              MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2,  MI_Db3, MI_Eb3, MI_F3,  MI_G3,  MI_A3,  MI_B3,                _______, _______,
            MI_C2,  MI_D2,  MI_E2,  MI_Gb2, MI_Ab2, MI_Bb2, MI_C3,  MI_D3,  MI_E3,  MI_Gb3, MI_Ab3, MI_Bb3, MI_C4,                  _______,
              MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2,  MI_Db3, MI_Eb3, MI_F3,  MI_G3,  MI_A3,  MI_B3,       _______,
            MI_C2,  MI_D2,  MI_E2,  MI_Gb2, MI_Ab2, MI_Bb2, MI_C3,  MI_D3,  MI_E3,  MI_Gb3, MI_Ab3, MI_Bb3, MI_C4,                  _______,
    _______,  MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2,  MI_Db3, MI_Eb3, MI_F3,  MI_G3,  MI_A3,  MI_B3,                _______, _______
  ),

  [_CFLIP_BASS2ROW] = LAYOUT(
    _______, _______, MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      _______, _______, MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        _______, _______, MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          _______, _______, MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            _______, _______, MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

              MI_Fs5, MI_Eb5, MI_C5,  MI_A4,  MI_Fs4, MI_Eb4, MI_C4,  MI_A3,  MI_Fs3, MI_Eb3, MI_C3,  MI_A2,               _______, _______,
            MI_G5,  MI_E5,  MI_Db5, MI_Bb4, MI_G4,  MI_E4,  MI_Db4, MI_Bb3, MI_G3,  MI_E3,  MI_Db3, MI_Bb2, MI_G2,                 _______,
              MI_F5,  MI_D5,  MI_B4,  MI_Ab4, MI_F4,  MI_D4,  MI_B3,  MI_Ab3, MI_F3,  MI_D3,  MI_B2,  MI_Ab2,     _______,
            MI_Fs5, MI_Eb5, MI_C5,  MI_A4,  MI_Fs4, MI_Eb4, MI_C4,  MI_A3,  MI_Fs3, MI_Eb3, MI_C3,  MI_A2,  MI_Fs2,                _______,
    _______,  MI_E5,  MI_Db5, MI_Bb4, MI_G4,  MI_E4,  MI_Db4, MI_Bb3, MI_G3,  MI_E3,  MI_Db3, MI_Bb2, MI_G2,               _______, _______
  ),

  /* QWERTY */
  [_QWERTY] = LAYOUT_wrapper(
    _______, _______, QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      _______, _______, KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_DEL,
        _______, _______, KC_CAPS, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_ENT,
          _______, _______, KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
            _______, _______, KC_LCTL, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LNG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

               QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,            _______, _______,
             KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_MINS, KC_DEL,               _______,
               KC_LCTL, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_ENT,    _______,
             KC_CAPS, KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,              _______,
    _______,   KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC, KC_SPC, KC_LNG1,  KC_APP,  KC_RALT, KC_RGUI,  KC_RCTL,           _______, _______
  ),

  /* COLEMAK */
  [_COLEMAK] = LAYOUT_wrapper(
    _______, _______, QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      _______, _______, KC_TAB,  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_DEL,
        _______, _______, KC_LCTL, _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_ENT,
          _______, _______, KC_LSFT, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, SHIF_UP,
            _______, _______, KC_CAPS, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LNG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

               QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,           _______, _______,
            KC_TAB,  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_MINS, KC_DEL,               _______,
               KC_LCTL, _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_ENT,   _______,
            KC_CAPS, KC_LSFT, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, KC_RSFT,              _______,
    _______,   KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC, KC_SPC, KC_LNG1,  KC_APP,  KC_RALT, KC_RGUI,  KC_RCTL,          _______, _______
  ),

  /* ADJUST */
  [_ADJUST] = LAYOUT_wrapper(
    _______, _______, _______, _________________FUNC__L___________________, _________________FUNC__R___________________, _______,
      _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  _______,
        _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  _______,
          _______, _______, _______, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_BSLS, _______,

               _______, _________________FUNC__L___________________, _________________FUNC__R___________________, _______,             _______, _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL, _______, _______,                _______,
               _______, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV, _______,     _______,
             _______, _______, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, _______,               _______,
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT,   KC_BSLS,            _______, _______
  ),


  /* Fn */
  [_FN] = LAYOUT(
    _______, _______, CSYSTEM, BSYSTEM, CNTBASC, CSYSALL, CHRTONE, CFLIP2B, CNTBASB, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_TOG,
      _______, _______, DF_QWER, TGLBASS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        _______, _______, DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TGLMICH,
          _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

               CSYSTEM,   BSYSTEM,   CNTBASC,  CSYSALL,  CHRTONE,  CFLIP2B,  CNTBASB, XXXXXXX, XXXXXXX, MI_VELD, MI_VELU, RGB_MOD,            _______, _______,
             XXXXXXX, DF_QWER,   TGLBASS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, MI_TRSD, MI_TRSU, TGLUVEL, MELDYAL, MELODYS, MELDYAH,                _______,
               MI_OCN2, MI_OCN1, MI_OC0, MI_OC1, MI_OC2, XXXXXXX,  XXXXXXX, MI_OCTD, MI_OCTU, XXXXXXX, VERSION, EE_CLR,    _______,
             CSYSTEM, BSYSTEM,   CNTBASC,  CSYSALL,  CHRTONE,  CFLIP2B,  CNTBASB, XXXXXXX, XXXXXXX, MI_VELD, MI_VELU, RGB_MOD, RGB_TOG,                _______,
    _______,   DF_QWER,   TGLBASS,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MI_TRSD, MI_TRSU, TGLUVEL, MELDYAL, MELODYS, MELDYAH,            _______, _______
  ),

  [_RESERVED] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______,
               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______,
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_C_SYSTEM_BASE]        = { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_B_SYSTEM]             = { ENCODER_CCW_CW(_______,  _______) },
    [_C_SYSTEM_BASS2ROW]    = { ENCODER_CCW_CW(_______,  _______) },
    [_B_SYSTEM_BASS2ROW]    = { ENCODER_CCW_CW(_______,  _______) },
    [_C_SYSTEM_ENTIRELY]    = { ENCODER_CCW_CW(_______,  _______) },
    [_CHROMATONE]           = { ENCODER_CCW_CW(_______,  _______) },
    [_CFLIP_BASS2ROW]       = { ENCODER_CCW_CW(_______,  _______) },
    [_QWERTY]               = { ENCODER_CCW_CW(_______,  _______) },
    [_COLEMAK]              = { ENCODER_CCW_CW(_______,  _______) },
    [_ADJUST]               = { ENCODER_CCW_CW(_______,  _______) },
    [_FN]                   = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
    [_RESERVED]             = { ENCODER_CCW_CW(_______,  _______) }
};
#endif

void my_init(void){
    //  Set octave to QK_MIDI_OCTAVE_0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

    //  Reset the midi keyboard layout
    set_single_persistent_default_layer(_C_SYSTEM_BASS2ROW);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(HSV_BLUE);
    //  party mode (for LED soldering test.)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  midi_init();
  my_init();

  // Used to set octave to QK_MIDI_OCTAVE_0
  midi_bass_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

  // UNISON flags
  melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
  melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.
  melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

  //  Reset Bass setting
  user_config.raw = 0;  // default: dyad
  eeconfig_update_user(user_config.raw);
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    uint8_t i;

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        uint8_t layer = biton32(layer_state);

        switch (layer) {
            case _ADJUST:
                rgb_matrix_set_color(90, RGB_DARKORANGE);
                rgb_matrix_set_color(94, RGB_DARKORANGE);
                // rgb_matrix_set_color(72, RGB_DARKORANGE);
                break;
            case _FN:
                for (i = 0;i < 7;i++) {
                    rgb_matrix_set_color(11 - i, RGB_DARKORANGE);      //  MIDI layouts
                    //  right keyboard
                    rgb_matrix_set_color(60 + i, RGB_DARKORANGE);      //  MIDI layouts
                    rgb_matrix_set_color(110 - i, RGB_DARKORANGE);      //  MIDI layouts
                }

                // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.
                rgb_matrix_set_color(1,  RGB_DARKBLUE);          //  RGB_MOD
                rgb_matrix_set_color(0,  RGB_DARKRED);           //  RGB_TOG
                rgb_matrix_set_color(13,  RGB_DARKCORAL);        //  TGLBASS

                rgb_matrix_set_color(12,  RGB_DARKWHITE);        //  DF_QWER
                rgb_matrix_set_color(35,  RGB_DARKWHITE);        //  DF_COLE
                rgb_matrix_set_color(23,  RGB_DARKPINK);         //  EE_CLR
                rgb_matrix_set_color(24,  RGB_DARKTEAL);         //  TGLMICH

                rgb_matrix_set_color(82, RGB_DARKCORAL);         //  TGLBASS  // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(83, RGB_DARKWHITE);         //  DF_QWER
                rgb_matrix_set_color(85, RGB_DARKBLUE);          //  MIDI Oct // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(86, RGB_DARKCYAN);          //  MIDI Oct // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(87, RGB_DARKSPRINGGREEN);   //  MIDI Oct // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(88, RGB_DARKGREEN);         //  MIDI Oct // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(89, RGB_DARKCHARTREUSE);    //  MIDI Oct // giabalanai and giabalanaipico have different layouts on encoder LED location.
                rgb_matrix_set_color(97, RGB_DARKPINK);          //  EE_CLR
                rgb_matrix_set_color(101, RGB_DARKYELLOW);       //  MI_VELD
                rgb_matrix_set_color(100, RGB_DARKGREEN);        //  MI_VELU
                rgb_matrix_set_color(99, RGB_DARKBLUE);          //  RGB_MOD
                rgb_matrix_set_color(98, RGB_DARKRED);           //  RGB_TOG
                rgb_matrix_set_color(111, RGB_DARKWHITE);        //  DF_QWER
                rgb_matrix_set_color(112, RGB_DARKCORAL);        //  TGLBASS
                rgb_matrix_set_color(119, RGB_DARKCORAL);        //  TGLUVEL
                rgb_matrix_set_color(120, RGB_DARKCYAN);         //  MELDYAL
                rgb_matrix_set_color(121, RGB_DARKGOLD);         //  MELODYS
                rgb_matrix_set_color(122, RGB_DARKSPRINGGREEN);  //  MELDYAH
                break;
        }
    }
    return false;
}
#endif

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
};

void toggle_isSingleBass(void) {
#ifdef CONSOLE_ENABLE
    uprintf("isSingleBass(before) %u\n", user_config.isSingleBass);
#endif
    user_config.isSingleBass = !user_config.isSingleBass;
#ifdef CONSOLE_ENABLE
    uprintf("isSingleBass(after) %u\n", user_config.isSingleBass);
#endif

    eeconfig_update_user(user_config.raw);
}

void toggle_MIDI_channel_separation(void) {
    if (midi_chord_ch > 0) {
        midi_chord_ch = 0;
        midi_bass_ch  = 0;
    } else {
        midi_chord_ch = 1;
        midi_bass_ch  = 2;
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
        case CSYSTEM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_C_SYSTEM_BASE);
            }
            break;

        case CNTBASC:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_C_SYSTEM_BASS2ROW);
            }
            break;

        case BSYSTEM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_B_SYSTEM);
            }
            break;

        case CNTBASB:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_B_SYSTEM_BASS2ROW);
            }
            break;

        case CSYSALL:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_C_SYSTEM_ENTIRELY);
            }
            break;

        case CHRTONE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_CHROMATONE);
            }
            break;

        case CFLIP2B:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_CFLIP_BASS2ROW);
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
            root_note = keycode - MI_CH_Cr + MI_C1;
            my_process_midi4Bass(midi_bass_ch, record, chord_status, chord, root_note, IS_SINGLE_BASS());
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C2;
            // Root, Major Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 4, 7);
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C2;
            // Root, Minor Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 7);
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7, 10);
            break;

        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C2;
            // Root, Minor Third, and Diminished 5th Note
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 6);
            break;

        // Keycodes on the right side.
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:  // notes on the right side keyboard.
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
