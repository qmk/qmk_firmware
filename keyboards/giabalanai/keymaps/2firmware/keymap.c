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
#include "split_util.h"
#include "print.h"

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

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

#define DF_QWER  DF(_QWERTY)
#define DF_COLE  DF(_COLEMAK)
#define MO_ADJ   MO(_ADJUST)
// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define SHIF_UP  RSFT_T(KC_UP)
#define ADJ_EIS  LT(_ADJUST,KC_LANG2)
#define MIS_KAN  LT(_MISC,KC_LANG1)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;

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

  /* Conversion map from keylocation (MATRIX_ROWS x2(split) x MATRIX_COLS) to led IDs.
    led IDs are the number starts "0" from upper left corner of left side,
    enumerated from left to right, from top to bottom.
    Then emumeration follows to the right side, starting from "60".

    Note that the conversion from physical LED serial alighment to
      the led IDs is done with RGBLIGHT_LED_MAP beforehand.                          */
const uint8_t PROGMEM convert_key_to_led[] =
{
  0,      12,    24,    36,    48,      11,    23,    35,     47,     59,
  1,      13,    25,    37,    49,      10,    22,    34,     46,     58,
  2,      14,    26,    38,    50,      9,     21,    33,     45,     57,
  3,      15,    27,    39,    51,      8,     20,    32,     44,     56,
  4,      16,    28,    40,    52,      7,     19,    31,     43,     55,
  5,      17,    29,    41,    53,      6,     18,    30,     42,     54,

  85,     86,    87,    88,    89,      90,    91,    NO_LED, NO_LED, NO_LED,
  98,     99,    100,   101,   102,     103,   104,   NO_LED, NO_LED, NO_LED,
  NO_LED, 111,   112,   113,   114,     115,   116,   NO_LED, NO_LED, NO_LED,
  NO_LED, 97,    96,    95,    94,      93,    92,    NO_LED, NO_LED, NO_LED,
  NO_LED, 110,   109,   108,   107,     106,   105,   NO_LED, NO_LED, NO_LED,
  NO_LED, 122,   121,   120,   119,     118,   117,   NO_LED, NO_LED, NO_LED
};

/* Top 2 rows on the right side (LED:60-84) are
   duplicates of the bottom 2 rows (LED:85-122).
   LED:97 = Encoder,
   LED:110 don't have a duplicate on the top row,
   LED:72 is used when r20 is pressed (not a duplicate) */
const uint8_t PROGMEM convert_key_to_led2[] =
{
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,

  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  60,     61,     62,     63,     64,       65,     66,     NO_LED, NO_LED, NO_LED,
  72,     73,     74,     75,     76,       77,     78,     NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
  NO_LED, NO_LED, 71,     70,     69,       68,     67,     NO_LED, NO_LED, NO_LED,
  NO_LED, 84,     83,     82,     81,       80,     79,     NO_LED, NO_LED, NO_LED
};

#endif  //  RGBLIGHT_ENABLE


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _C_SYSTEM_BASE,      //  MIDI C-system
    _FAKE_B_SYSTEM,      //  MIDI fake B-system doesn't have correct assignments on top two rows. The bottom 3 rows are B-system.
    _C_SYSTEM_BASS2ROW,  //  counter bass system
    _C_SYSTEM_ENTIRELY,  //  single notes for both left and right keybaords.
    _CHROMATONE,
    _CFLIP_BASS2ROW,     //  180 degree flipped layout on right side keyboard
    _QWERTY,
    _COLEMAK,
    _ADJUST,             //  for Fn keys, etc.
    _FN                  //  for changing layers, octaves, etc.
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {

    // MIDI Chord Keycodes - Root notes

    MI_CH_Cr = SAFE_RANGE,
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

    CSYSTEM,
    BSYSTEM,
    CNTBASC,
    CSYSALL,
    CHRTONE,
    CFLIP2B,
    TGLBASS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* C-system Base */
  [_C_SYSTEM_BASE] = LAYOUT(
    MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
      MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
        MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
          MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,
            MI_CH_DbDim7, MI_CH_AbDim7, MI_CH_EbDim7, MI_CH_BbDim7, MI_CH_FDim7, MI_CH_CDim7, MI_CH_GDim7, MI_CH_DDim7, MI_CH_ADim7, MI_CH_EDim7, MI_CH_BDim7, MI_CH_FsDim7,

    MI_Fs_2,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,    FN_MUTE,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5
  ),

  /* fake B-system */
  [_FAKE_B_SYSTEM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    MI_Ab_2,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Gb_3, MI_A_3, MI_C_4,  MI_Eb_4, MI_Gb_4, MI_A_4, MI_C_5,  MI_Eb_5, MI_Gb_5,     _______,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3, MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4, MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3, MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4, MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5
  ),

  /* BASS2row */
  [_C_SYSTEM_BASS2ROW] = LAYOUT(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

    MI_Fs_2,
      MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,    _______,
    MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
      MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5
  ),

  /* C-system entirely */
  [_C_SYSTEM_ENTIRELY] = LAYOUT(
    MI_BENDU, XXXXXXX, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2,
      MI_BENDD, XXXXXXX, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2,
        XXXXXXX, XXXXXXX, MI_D,    MI_F,    MI_Ab,   MI_B,    MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,
          XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,
            MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Fs_2, MI_A_2,

    MI_Fs_2,
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

    MI_C_2,
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

    MI_G_5,
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

    _______,
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

    _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* ADJUST */
  [_ADJUST] = LAYOUT_wrapper(
    _______, _________________FUNC__L___________________, _________________FUNC__R___________________, _______,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  _______,
          _______, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_BSLS, _______,

    _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),


  /* Fn */
  [_FN] = LAYOUT(
    CSYSTEM, BSYSTEM, CNTBASC, CSYSALL, CHRTONE, CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
      DF_QWER, TGLBASS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    XXXXXXX,
      MI_OCT_N2, MI_OCT_N1, MI_OCT_0, MI_OCT_1, MI_OCT_2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,   _______,
    CSYSTEM, BSYSTEM,  CNTBASC,  CSYSALL,  CHRTONE,  CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
      XXXXXXX,   TGLBASS,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
                                                                         {110, 1, HSV_RED},         //  RGB_TOG
                                                                         {112, 1, HSV_CORAL}        //  TGLBASS
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

void keyboard_post_init_user(void) {
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    //  load EEPROM data for isSingleBass
    user_config.raw = eeconfig_read_user();

    // When USB cable is connected to the left side keyboard, use QWERTY layout by default.
    if (is_keyboard_master() && isLeftHand) {
        default_layer_set(1UL << _QWERTY);
    }


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

void eeconfig_init_user(void) {
  //  Reset Bass setting
  user_config.raw = 0;  // default: dyad
  eeconfig_update_user(user_config.raw);

  //  Reset the midi keyboard layout
  set_single_persistent_default_layer(_C_SYSTEM_BASE);
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

    switch (keycode) {
        //  set default layer and save it to EEPROM when MIDI key layers are selected.
        case CSYSTEM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_C_SYSTEM_BASE);
            }
            break;

        case BSYSTEM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_FAKE_B_SYSTEM);
            }
            break;

        case CNTBASC:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_C_SYSTEM_BASS2ROW);
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

        // MIDI Chord Keycodes, on the left side.
        case MI_CH_Cr ... MI_CH_Br:  // Root Notes
            root_note = keycode - MI_CH_Cr + MI_C_1;
            if (IS_SINGLE_BASS()) {
              process_midi(root_note, record);
            } else {
              process_midi(root_note, record);
              process_midi(root_note + 12, record);  // +1 Octave
            }
            // process_midi(root_note + 24, record);  // +2 Octave
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C_2;
            process_midi(root_note, record);
            process_midi(root_note + 4, record);  // Major Third Note
            process_midi(root_note + 7, record);  // Fifth Note
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C_2;
            process_midi(root_note, record);
            process_midi(root_note + 3, record);  // Minor Third Note
            process_midi(root_note + 7, record);  // Fifth Note
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C_2;
            process_midi(root_note, record);
            process_midi(root_note + 4, record);   // Major Third Note
            process_midi(root_note + 10, record);  // Minor Seventh Note
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C_2;
            process_midi(root_note, record);
            process_midi(root_note + 3, record);  // Minor Third Note
            process_midi(root_note + 6, record);  // Diminished 5th Note
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

#ifdef RGBLIGHT_ENABLE
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:  // notes on the right side.
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            keylight_manager(record, HSV_GOLDENROD, keylocation2);
            break;

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

#ifdef ENCODER_ENABLE
void encoder_update_user(int8_t index, bool clockwise) {
#    ifdef CONSOLE_ENABLE
    uprintf("encoder_update_user, index = %d, clockwise = %u\n", index, clockwise);
#    endif
    if (index == 1) { /* An encoder on the right side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
#    ifdef CONSOLE_ENABLE
        uprintf("midi_config.octave = %u\n", midi_config.octave);
#    endif
}
#endif  // ENCODER_ENABLE
