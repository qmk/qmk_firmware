/* Copyright 2020 3araht
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
#include "print.h"

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#ifndef PARTY_REACTIVE_FOCUSED_MODE
#   define DF_QWER  DF(_QWERTY)
#   define DF_COLE  DF(_COLEMAK)
#else
#   define DF_QWER  XXXXXXX
#   define DF_COLE  XXXXXXX
#endif  //  PARTY_REACTIVE_FOCUSED_MODE

#define MO_ADJ   MO(_ADJUST)
// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define SHIF_UP  RSFT_T(KC_UP)
#define ADJ_EIS  LT(_ADJUST,KC_LANG2)
#define MIS_KAN  LT(_MISC,KC_LANG1)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;
uint8_t midi_base_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

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
  };
} user_config_t;
user_config_t user_config;

#define IS_SINGLE_BASS()   (user_config.isSingleBass)

#ifdef RGBLIGHT_ENABLE
/* used to specify there is no LED on the keylocation. */
#    define NO_LED 255
#endif  //  RGBLIGHT_ENABLE


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _C_SYSTEM_BASE,      //  MIDI C-system
#ifndef PARTY_REACTIVE_FOCUSED_MODE
    _FAKE_B_SYSTEM,      //  MIDI fake B-system doesn't have correct assignments on top two rows. The bottom 3 rows are B-system.
#endif  //  PARTY_REACTIVE_FOCUSED_MODE
    _C_SYSTEM_BASS2ROW,  //  counter bass system
#ifndef PARTY_REACTIVE_FOCUSED_MODE
    _C_SYSTEM_ENTIRELY,  //  single notes for both left and right keybaords.
    _CHROMATONE,
    _CFLIP_BASS2ROW,     //  180 degree flipped layout on right side keyboard
    _QWERTY,
    _COLEMAK,
#endif  //  PARTY_REACTIVE_FOCUSED_MODE
    _ADJUST,             //  for Fn keys, etc.
    _FN                  //  for changing layers, octaves, etc.
};

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
//
// const uint8_t convert_led_location2number[DRIVER_LED_TOTAL] = {
//     74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63,
//     75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
//     98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87,
//     99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
//     122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111,
//
//     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
//     25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13,
//     26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,     12,
//     50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38,
//     51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62
// };
#endif

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

    CSYSTEM,  // C-SYSTEM layout
    BSYSTEM,  // B-SYSTEM layout
    CNTBASC,  // CouNTer BASe C-system layout
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
    MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
      MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
        MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
          MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,
            MI_CH_DbDim7, MI_CH_AbDim7, MI_CH_EbDim7, MI_CH_BbDim7, MI_CH_FDim7, MI_CH_CDim7, MI_CH_GDim7, MI_CH_DDim7, MI_CH_ADim7, MI_CH_EDim7, MI_CH_BDim7, MI_CH_FsDim7,

    MI_Fs_2,                                                                                                    KC_VOLD, KC_VOLU,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,    FN_MUTE,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5
  ),

#ifndef PARTY_REACTIVE_FOCUSED_MODE
  /* fake B-system */
  [_FAKE_B_SYSTEM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    MI_Ab_2,                                                                                                    _______, _______,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Gb_3, MI_A_3, MI_C_4,  MI_Eb_4, MI_Gb_4, MI_A_4, MI_C_5,  MI_Eb_5, MI_Gb_5,     _______,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3, MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4, MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3, MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4, MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5
  ),
#endif  //  PARTY_REACTIVE_FOCUSED_MODE

  /* BASS2row */
  [_C_SYSTEM_BASS2ROW] = LAYOUT(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

    MI_Fs_2,                                                                                                    _______, _______,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,    _______,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5
  ),

#ifndef PARTY_REACTIVE_FOCUSED_MODE
  /* C-system entirely */
  [_C_SYSTEM_ENTIRELY] = LAYOUT(
    MI_BENDU, XXXXXXX, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2,
      MI_BENDD, XXXXXXX, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2,
        XXXXXXX, XXXXXXX, MI_D,    MI_F,    MI_Ab,   MI_B,    MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,
          XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,
            MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Fs_2, MI_A_2,

    MI_Fs_2,                                                                                                    _______, _______,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,    FN_MUTE,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5
  ),

  /* Chromatone */
  [_CHROMATONE] = LAYOUT(
    MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1, MI_Eb_1, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1,
      MI_D,    MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C_1,  MI_D_1,  MI_E_1,  MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2,
        MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1, MI_Eb_1, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1,  MI_Db_2,
          MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C_1,  MI_D_1,  MI_E_1,  MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2,  MI_D_2,
            MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1, MI_Eb_1, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1,  MI_Db_2, MI_Eb_2,

    MI_C_2,                                                                                                    _______, _______,
      MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,    FN_MUTE,
    MI_C_2,  MI_D_2,  MI_E_2,  MI_Gb_2, MI_Ab_2, MI_Bb_2, MI_C_3,  MI_D_3,  MI_E_3,  MI_Gb_3, MI_Ab_3, MI_Bb_3, MI_C_4,
      MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3
  ),

  [_CFLIP_BASS2ROW] = LAYOUT(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

    MI_G_5,                                                                                                    _______, _______,
      MI_F_5,  MI_D_5,  MI_B_4,  MI_Ab_4, MI_F_4,  MI_D_4,  MI_B_3,  MI_Ab_3, MI_F_3,  MI_D_3,  MI_B_2,  MI_Ab_2,   FN_MUTE,
    MI_Fs_5, MI_Eb_5, MI_C_5,  MI_A_4,  MI_Fs_4, MI_Eb_4, MI_C_4,  MI_A_3,  MI_Fs_3, MI_Eb_3, MI_C_3,  MI_A_2,  MI_Fs_2,
      MI_E_5,  MI_Db_5, MI_Bb_4, MI_G_4,  MI_E_4,  MI_Db_4, MI_Bb_3, MI_G_3,  MI_E_3,  MI_Db_3, MI_Bb_2, MI_G_2
  ),

  /* QWERTY */
  [_QWERTY] = LAYOUT_wrapper(
    KC_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_DEL,
        KC_CAPS, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_ENT,
          KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
            KC_LCTL, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LANG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

    _______,                                                                                                    _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* COLEMAK */
  [_COLEMAK] = LAYOUT_wrapper(
    KC_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      KC_TAB,  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_DEL,
        KC_LCTL, _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_ENT,
          KC_LSFT, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, SHIF_UP,
            KC_CAPS, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LANG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

    _______,                                                                                                    _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
#endif //  PARTY_REACTIVE_FOCUSED_MODE

  /* ADJUST */
  [_ADJUST] = LAYOUT_wrapper(
    _______, _________________FUNC__L___________________, _________________FUNC__R___________________, _______,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  _______,
          _______, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_BSLS, _______,

    _______,                                                                                                    _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),


  /* Fn */
  [_FN] = LAYOUT(
    CSYSTEM, BSYSTEM, CNTBASC, CSYSALL, CHRTONE, CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_TOG,
      DF_QWER, TGLBASS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TGLMICH,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    XXXXXXX,                                                                                                    XXXXXXX, XXXXXXX,
      MI_OCT_N2, MI_OCT_N1, MI_OCT_0, MI_OCT_1, MI_OCT_2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,   _______,
    CSYSTEM, BSYSTEM,  CNTBASC,  CSYSALL,  CHRTONE,  CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, MI_VELD, MI_VELU, RGB_MOD, RGB_TOG,
      XXXXXXX,   TGLBASS,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, TGLUVEL, MELDYAL, MELODYS, MELDYAH
  )
};

#ifdef RGBLIGHT_ENABLE

// Light up adjust layer keys (left keyboard)
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({1,  10, HSV_ORANGE},
                                                                             {21,  2, HSV_ORANGE},
                                                                             {25,  3, HSV_ORANGE},
                                                                             {30,  5, HSV_ORANGE},
                                                                             {37,  2, HSV_ORANGE},
                                                                             {45,  2, HSV_ORANGE},
                                                                             {57,  2, HSV_ORANGE}
);

// Light up fn layer keys
const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(                           //  left keyboard
                                                                         {0,   6, HSV_ORANGE},      //  MIDI layouts
                                                                         {11,  1, HSV_RED},         //  RGB_TOG
                                                                         {12,  1, HSV_WHITE},       //  DF_QWER
                                                                         {13,  1, HSV_CORAL},       //  TGLBASS
                                                                         {24,  1, HSV_WHITE},       //  DF_COLE
                                                                         {35,  1, HSV_TEAL},        //  TGLMICH
#if 0  //  Color Test
                                                                         {36,  1, HSV_WHITE},
                                                                         {37,  1, HSV_RED},
                                                                         {38,  1, HSV_CORAL},
                                                                         {39,  1, HSV_ORANGE},
                                                                         {40,  1, HSV_GOLDENROD},
                                                                         {41,  1, HSV_GOLD},
                                                                         {42,  1, HSV_YELLOW},
                                                                         {43,  1, HSV_CHARTREUSE},
                                                                         {44,  1, HSV_GREEN},
                                                                         {45,  1, HSV_SPRINGGREEN},
                                                                         {46,  1, HSV_TURQUOISE},
                                                                         {47,  1, HSV_TEAL},
                                                                         {48,  1, HSV_CYAN},
                                                                         {49,  1, HSV_AZURE},
                                                                         {50,  1, HSV_BLUE},
                                                                         {51,  1, HSV_PURPLE},
                                                                         {52,  1, HSV_MAGENTA},
                                                                         {53,  1, HSV_PINK},
#endif
                                                                                                    //  right keyboard
                                                                         {60,  6, HSV_ORANGE},      //  MIDI layouts
                                                                         {74,  1, HSV_CORAL},       //  TGLBASS
                                                                         {85,  1, HSV_BLUE},        //  MIDI Oct
                                                                         {86,  1, HSV_CYAN},        //  MIDI Oct
                                                                         {87,  1, HSV_SPRINGGREEN}, //  MIDI Oct
                                                                         {88,  1, HSV_GREEN},       //  MIDI Oct
                                                                         {89,  1, HSV_CHARTREUSE},  //  MIDI Oct
                                                                         {96,  1, HSV_PINK},        //  EEP_RST
                                                                         {98,  6, HSV_ORANGE},      //  MIDI layouts
                                                                         {107, 1, HSV_YELLOW},      //  MI_VELD
                                                                         {108, 1, HSV_GREEN},       //  MI_VELU
                                                                         {110, 1, HSV_RED},         //  RGB_TOG
                                                                         {112, 1, HSV_CORAL},       //  TGLBASS
                                                                         {119, 1, HSV_CORAL},       //  TGLUVEL
                                                                         {120, 1, HSV_CYAN},        //  MELDYAL
                                                                         {121, 1, HSV_GOLD},        //  MELODYS
                                                                         {122, 1, HSV_SPRINGGREEN}  //  MELDYAH
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_fn_layer, my_adjust_layer);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(1, layer_state_cmp(state, _ADJUST));
    return state;
};

#endif  //  RGBLIGHT_ENABLE

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  //  Reset Bass setting
  user_config.raw = 0;  // default: dyad
  eeconfig_update_user(user_config.raw);

  //  Reset the midi keyboard layout
  set_single_persistent_default_layer(_C_SYSTEM_BASE);

  #ifdef RGB_MATRIX_ENABLE
  rgb_matrix_sethsv(HSV_BLUE);
      //  party mode (for LED soldering test.)
  #   ifdef PARTY_REACTIVE_FOCUSED_MODE
  rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_solid_reactive_with_CnoteIndicator);
  #   else
  rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
  #   endif
  #endif
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
#ifndef PARTY_REACTIVE_FOCUSED_MODE
    uint8_t i;
#endif  //  PARTY_REACTIVE_FOCUSED_MODE
    // uint32_t mode = rgblight_get_mode();

    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.

        uint8_t layer = biton32(layer_state);

        switch (layer) {
            case _ADJUST:
                rgb_matrix_set_color(30, RGB_DARKORANGE);
                rgb_matrix_set_color(34, RGB_DARKORANGE);
                // rgb_matrix_set_color(72, RGB_DARKORANGE);
                break;
            case _FN:
#ifndef PARTY_REACTIVE_FOCUSED_MODE
                for (i = 0;i < 6;i++) {
                    rgb_matrix_set_color(74 - i, RGB_DARKORANGE);      //  MIDI layouts
                    //  right keyboard
                    rgb_matrix_set_color(i, RGB_DARKORANGE);      //  MIDI layouts
                    rgb_matrix_set_color(50 - i, RGB_DARKORANGE);      //  MIDI layouts
                }
#else
                //  BSYSTEM, CSYSALL, CHRTONE, CFLIP2B are disabled.
                rgb_matrix_set_color(74, RGB_DARKORANGE);      //  CSYSTEM
                rgb_matrix_set_color(72, RGB_DARKORANGE);      //  CNTBASC
                rgb_matrix_set_color(0,  RGB_DARKORANGE);      //  CSYSTEM
                rgb_matrix_set_color(2,  RGB_DARKORANGE);      //  CNTBASC
                rgb_matrix_set_color(50, RGB_DARKORANGE);      //  CSYSTEM
                rgb_matrix_set_color(48, RGB_DARKORANGE);      //  CNTBASC
#endif  //  PARTY_REACTIVE_FOCUSED_MODE

                // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.
                rgb_matrix_set_color(64,  RGB_DARKBLUE);         //  RGB_MOD
                rgb_matrix_set_color(63,  RGB_DARKRED);         //  RGB_TOG
                rgb_matrix_set_color(76,  RGB_DARKCORAL);       //  TGLBASS

#ifndef PARTY_REACTIVE_FOCUSED_MODE
                rgb_matrix_set_color(75,  RGB_DARKWHITE);       //  DF_QWER
                rgb_matrix_set_color(98,  RGB_DARKWHITE);       //  DF_COLE
#endif
                rgb_matrix_set_color(87,  RGB_DARKTEAL);        //  TGLMICH

                rgb_matrix_set_color(23, RGB_DARKCORAL);       //  TGLBASS
                rgb_matrix_set_color(26, RGB_DARKBLUE);        //  MIDI Oct
                rgb_matrix_set_color(27, RGB_DARKCYAN);        //  MIDI Oct
                rgb_matrix_set_color(28, RGB_DARKSPRINGGREEN); //  MIDI Oct
                rgb_matrix_set_color(29, RGB_DARKGREEN);       //  MIDI Oct
                rgb_matrix_set_color(30, RGB_DARKCHARTREUSE);  //  MIDI Oct
                rgb_matrix_set_color(37, RGB_DARKPINK);        //  EEP_RST
                rgb_matrix_set_color(41, RGB_DARKYELLOW);      //  MI_VELD
                rgb_matrix_set_color(40, RGB_DARKGREEN);       //  MI_VELU
                rgb_matrix_set_color(39, RGB_DARKBLUE);        //  RGB_MOD
                rgb_matrix_set_color(38, RGB_DARKRED);         //  RGB_TOG
                rgb_matrix_set_color(52, RGB_DARKCORAL);       //  TGLBASS
                rgb_matrix_set_color(59, RGB_DARKCORAL);       //  TGLUVEL
                rgb_matrix_set_color(60, RGB_DARKCYAN);        //  MELDYAL
                rgb_matrix_set_color(61, RGB_DARKGOLD);        //  MELODYS
                rgb_matrix_set_color(62, RGB_DARKSPRINGGREEN);  //  MELDYAH
                break;
        }
    }
}
#endif

void keyboard_post_init_user(void) {
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

    for (uint8_t i = 0; i < MY_CHORD_COUNT; i++) {
        chord_status[i] = MIDI_INVALID_NOTE;
    }

    for (uint8_t i = 0; i < MIDI_TONE_COUNT; i++) {
        my_tone_status[i] = MIDI_INVALID_NOTE;
    }
    //  load EEPROM data for isSingleBass
    user_config.raw = eeconfig_read_user();

#ifdef RGBLIGHT_ENABLE

    rgblight_layers = my_rgb_layers;

    // Reset LED off
    rgblight_sethsv(HSV_BLACK);
#    if defined(RGBLIGHT_EFFECT_KNIGHT) || defined(RGBLIGHT_EFFECT_TWINKLE)
    rgblight_sethsv(30, 50, 40);
#        ifdef RGBLIGHT_EFFECT_KNIGHT
    rgblight_mode(RGBLIGHT_MODE_KNIGHT);
#        elif defined(RGBLIGHT_EFFECT_TWINKLE)
    rgblight_mode(RGBLIGHT_MODE_TWINKLE+3);
#        endif
#    endif
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(HSV_BLUE);
    // rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;  //  done in rgb_matrix_sethsv_eeprom_helper()
#endif
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
        midi_base_ch  = 0;
    } else {
        midi_chord_ch = 1;
        midi_base_ch  = 2;
    }
}


#ifdef RGBLIGHT_ENABLE
void keylight_manager(keyrecord_t *record, uint8_t hue, uint8_t sat, uint8_t val, uint8_t keylocation) {
    if (keylocation == NO_LED) {
        return;  // do nothing.
#    ifdef CONSOLE_ENABLE
        uprintf("keylight_manager, NO_LED\n");
#    endif
    }

    if (record->event.pressed) {
        rgblight_sethsv_at(hue, sat, val, keylocation);
    } else {
        rgblight_sethsv_at(HSV_BLACK, keylocation);
    }
}
#endif  // RGBLIGHT_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t root_note = MIDI_INVALID_NOTE;  // Starting value for the root note of each chord

#ifdef RGBLIGHT_ENABLE
    /* prepare for turning on LEDs when keys are pressed. */
    uint8_t r            = record->event.key.row;
    uint8_t c            = record->event.key.col;
    // uint8_t keylocation  = convert_key_to_led[MATRIX_COLS * r + c];
    // uint8_t keylocation2 = convert_key_to_led2[MATRIX_COLS * r + c];
    uint8_t keylocation  = pgm_read_byte(&convert_key_to_led[MATRIX_COLS * r + c]);
    uint8_t keylocation2 = pgm_read_byte(&convert_key_to_led2[MATRIX_COLS * r + c]);
#endif  // RGBLIGHT_ENABLE

    uint8_t chord        = keycode - MY_CHORD_MIN;

    switch (keycode) {
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

#ifndef PARTY_REACTIVE_FOCUSED_MODE
        case BSYSTEM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_FAKE_B_SYSTEM);
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
#endif  //  PARTY_REACTIVE_FOCUSED_MODE

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
            my_process_midi4Base(midi_base_ch, record, chord_status, chord, root_note, IS_SINGLE_BASS());
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C_2;
            // Root, Major Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 4, 7);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C_2;
            // Root, Minor Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 7);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C_2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7, 10);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C_2;
            // Root, Minor Third, and Diminished 5th Note
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 6);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

#ifdef RGBLIGHT_ENABLE
        case KC_A ... KC_RGUI:                // for QWERTY
        case KC_GESC:
        case ADJ_EIS:
        case MO_ADJ:
        case SHIF_UP:
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
#endif

        // Keycodes on the right side.
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:  // notes on the right side keyboard.
            //  root_note is played by process_midi().
            if ( melody_dyad_high == true ) {        //  play 1 octave higher as well.
                my_process_midi(0, keycode, record, my_tone_status, 12, melody_unison_suppress);
            } else if ( melody_dyad_low == true ) {  //  play 1 octave lower as well.
                my_process_midi(0, keycode, record, my_tone_status, -12, melody_unison_suppress);
            }
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            keylight_manager(record, HSV_GOLDENROD, keylocation2);
#endif
            break;

#ifdef RGBLIGHT_ENABLE
        // case KC_MUTE:
        case FN_MUTE:
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
#endif
    }
    // If console is enabled, it will print the matrix position and status of each key pressed
#if defined(CONSOLE_ENABLE) && defined(RGBLIGHT_ENABLE)
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    uprintf("r=%d, c=%d, keyloc=%d, keyloc2=%d, matrix_col x r + c = %d\n", r, c, keylocation, keylocation2, MATRIX_COLS * r + c);
#endif
    return true;
}
