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
#include "version.h"

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define DF_QWER  DF(_QWERTY)
#define DF_COLE  DF(_COLEMAK)
#define MO_ADJ   MO(_ADJUST)
// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define SHIF_UP  RSFT_T(KC_UP)
#define ADJ_EIS  LT(_ADJUST,KC_LNG2)
#define MIS_KAN  LT(_MISC,KC_LNG1)

// Used to set octave to 0
extern midi_config_t midi_config;
uint8_t midi_bass_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

// UNISON flags
static bool melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
static bool melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.

static bool melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

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

    VERSION,
    CSYSTEM,  // C-SYSTEM layout
    BSYSTEM,  // B-SYSTEM layout
    CNTBASC,  // CouNTer BASs C-system layout
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

    MI_Fs2,
      MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,    FN_MUTE,
    MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,
      MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5
  ),

  /* fake B-system */
  [_FAKE_B_SYSTEM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    MI_Ab2,
      MI_A2,  MI_C3,  MI_Eb3, MI_Gb3, MI_A3, MI_C4,  MI_Eb4, MI_Gb4, MI_A4, MI_C5,  MI_Eb5, MI_Gb5,     _______,
    MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3, MI_Bb3, MI_Db4, MI_E4,  MI_G4, MI_Bb4, MI_Db5, MI_E5,  MI_G5,
      MI_Ab2, MI_B2,  MI_D3,  MI_F3, MI_Ab3, MI_B3,  MI_D4,  MI_F4, MI_Ab4, MI_B4,  MI_D5,  MI_F5
  ),

  /* BASS2row */
  [_C_SYSTEM_BASS2ROW] = LAYOUT(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

    MI_Fs2,
      MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,    _______,
    MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,
      MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5
  ),

  /* C-system entirely */
  [_C_SYSTEM_ENTIRELY] = LAYOUT(
    MI_BNDU, XXXXXXX, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db1, MI_E1,  MI_G1,  MI_Bb1, MI_Db2,
      MI_BNDD, XXXXXXX, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C1,  MI_Eb1, MI_Fs1, MI_A1,  MI_C2,  MI_Eb2,
        XXXXXXX, XXXXXXX, MI_D,    MI_F,    MI_Ab,   MI_B,    MI_D1,  MI_F1,  MI_Ab1, MI_B1,  MI_D2,  MI_F2,
          XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db1, MI_E1,  MI_G1,  MI_Bb1, MI_Db2, MI_E2,  MI_G2,
            MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C1,  MI_Eb1, MI_Fs1, MI_A1,  MI_C2,  MI_Eb2, MI_Fs2, MI_A2,

    MI_Fs2,
      MI_Ab2, MI_B2,  MI_D3,  MI_F3,  MI_Ab3, MI_B3,  MI_D4,  MI_F4,  MI_Ab4, MI_B4,  MI_D5,  MI_F5,    FN_MUTE,
    MI_G2,  MI_Bb2, MI_Db3, MI_E3,  MI_G3,  MI_Bb3, MI_Db4, MI_E4,  MI_G4,  MI_Bb4, MI_Db5, MI_E5,  MI_G5,
      MI_A2,  MI_C3,  MI_Eb3, MI_Fs3, MI_A3,  MI_C4,  MI_Eb4, MI_Fs4, MI_A4,  MI_C5,  MI_Eb5, MI_Fs5
  ),

  /* Chromatone */
  [_CHROMATONE] = LAYOUT(
    MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,
      MI_D,    MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C1,  MI_D1,  MI_E1,  MI_Fs1, MI_Ab1, MI_Bb1, MI_C2,
        MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,  MI_Db2,
          MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C1,  MI_D1,  MI_E1,  MI_Fs1, MI_Ab1, MI_Bb1, MI_C2,  MI_D2,
            MI_F,    MI_G,    MI_A,    MI_B,    MI_Db1, MI_Eb1, MI_F1,  MI_G1,  MI_A1,  MI_B1,  MI_Db2, MI_Eb2,

    MI_C2,
      MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2,  MI_Db3, MI_Eb3, MI_F3,  MI_G3,  MI_A3,  MI_B3,    FN_MUTE,
    MI_C2,  MI_D2,  MI_E2,  MI_Gb2, MI_Ab2, MI_Bb2, MI_C3,  MI_D3,  MI_E3,  MI_Gb3, MI_Ab3, MI_Bb3, MI_C4,
      MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2,  MI_Db3, MI_Eb3, MI_F3,  MI_G3,  MI_A3,  MI_B3
  ),

  [_CFLIP_BASS2ROW] = LAYOUT(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,

    MI_G5,
      MI_F5,  MI_D5,  MI_B4,  MI_Ab4, MI_F4,  MI_D4,  MI_B3,  MI_Ab3, MI_F3,  MI_D3,  MI_B2,  MI_Ab2,   FN_MUTE,
    MI_Fs5, MI_Eb5, MI_C5,  MI_A4,  MI_Fs4, MI_Eb4, MI_C4,  MI_A3,  MI_Fs3, MI_Eb3, MI_C3,  MI_A2,  MI_Fs2,
      MI_E5,  MI_Db5, MI_Bb4, MI_G4,  MI_E4,  MI_Db4, MI_Bb3, MI_G3,  MI_E3,  MI_Db3, MI_Bb2, MI_G2
  ),

  /* QWERTY */
  [_QWERTY] = LAYOUT_wrapper(
    QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_DEL,
        KC_CAPS, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_ENT,
          KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
            KC_LCTL, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LNG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

    _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* COLEMAK */
  [_COLEMAK] = LAYOUT_wrapper(
    QK_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      KC_TAB,  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_DEL,
        KC_LCTL, _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_ENT,
          KC_LSFT, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, SHIF_UP,
            KC_CAPS, KC_LGUI, KC_LALT, ADJ_EIS, KC_SPC,  KC_SPC,  KC_LNG1, KC_APP, MO_ADJ,  KC_LEFT, KC_DOWN, KC_RGHT,

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
    CSYSTEM, BSYSTEM, CNTBASC, CSYSALL, CHRTONE, CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UG_TOGG,
      DF_QWER, TGLBASS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TGLMICH,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    XXXXXXX,
      MI_OCN2, MI_OCN1, MI_OC0,  MI_OC1,  MI_OC2,  XXXXXXX, XXXXXXX, MI_OCTD, MI_OCTU, XXXXXXX, VERSION, EE_CLR, _______,
    CSYSTEM, BSYSTEM,  CNTBASC,  CSYSALL,  CHRTONE,  CFLIP2B, XXXXXXX, XXXXXXX, XXXXXXX, MI_VELD, MI_VELU, XXXXXXX, UG_TOGG,
      XXXXXXX,   TGLBASS,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, MI_TRSD, MI_TRSU, TGLUVEL, MELDYAL, MELODYS, MELDYAH
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_C_SYSTEM_BASE]        = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FAKE_B_SYSTEM]        = { ENCODER_CCW_CW(_______, _______) },
    [_C_SYSTEM_BASS2ROW]    = { ENCODER_CCW_CW(_______, _______) },
    [_C_SYSTEM_ENTIRELY]    = { ENCODER_CCW_CW(_______, _______) },
    [_CHROMATONE]           = { ENCODER_CCW_CW(_______, _______) },
    [_CFLIP_BASS2ROW]       = { ENCODER_CCW_CW(_______, _______) },
    [_QWERTY]               = { ENCODER_CCW_CW(_______, _______) },
    [_COLEMAK]              = { ENCODER_CCW_CW(_______, _______) },
    [_ADJUST]               = { ENCODER_CCW_CW(_______, _______) },
    [_FN]                   = { ENCODER_CCW_CW(_______, _______) },
};
#endif

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
                                                                         {11,  1, HSV_RED},         //  UG_TOGG
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
                                                                         {96,  1, HSV_PINK},        //  EE_CLR
                                                                         {98,  6, HSV_ORANGE},      //  MIDI layouts
                                                                         {107, 1, HSV_YELLOW},      //  MI_VELD
                                                                         {108, 1, HSV_GREEN},       //  MI_VELU
                                                                         {110, 1, HSV_RED},         //  UG_TOGG
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

void my_init(void){
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

void eeconfig_init_user(void) {
    midi_init();
    my_init();

    // Used to set octave to 0
    midi_bass_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.

    // UNISON flags
    melody_dyad_high = false;  //  true when +1 octave unison dyad is enabled.
    melody_dyad_low  = false;  //  true when -1 octave unison dyad is enabled.
    melody_unison_suppress  = true;  //  true: velocity of octave unison note is suppressd to UNISON_VELOCITY_RATIO

    //  Reset Bass setting
    user_config.raw = 0;  // default: dyad
    eeconfig_update_user(user_config.raw);

    //  Reset the midi keyboard layout
    set_single_persistent_default_layer(_C_SYSTEM_BASS2ROW);
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

void toggle_MIDI_channel_separation(void) {
    if (midi_chord_ch > 0) {
        midi_chord_ch = 0;
        midi_bass_ch  = 0;
    } else {
        midi_chord_ch = 1;
        midi_bass_ch  = 2;
    }
}

#ifdef RGBLIGHT_ENABLE
void switch_keylight_color4bass(keyrecord_t *record, uint8_t keylocation){
    switch (biton32(default_layer_state)) {
        case _C_SYSTEM_BASE:
            keylight_manager(record, HSV_GREEN, keylocation);
            break;
        case _FAKE_B_SYSTEM:
            keylight_manager(record, HSV_ORANGE, keylocation);
            break;
        case _C_SYSTEM_BASS2ROW:
            keylight_manager(record, HSV_YELLOW, keylocation);
            break;
        case _CFLIP_BASS2ROW:
            keylight_manager(record, HSV_PURPLE, keylocation);
            break;
    }
}
void switch_keylight_color4chords(keyrecord_t *record, uint8_t keylocation){
    switch (biton32(default_layer_state)) {
        case _C_SYSTEM_BASE:
            keylight_manager(record, HSV_SPRINGGREEN, keylocation);
            break;
        case _FAKE_B_SYSTEM:
            keylight_manager(record, HSV_YELLOW, keylocation);
            break;
        case _C_SYSTEM_BASS2ROW:
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
        case _CFLIP_BASS2ROW:
            keylight_manager(record, HSV_MAGENTA, keylocation);
            break;
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
#ifdef RGBLIGHT_ENABLE
            switch_keylight_color4bass(record, keylocation);
#endif
            break;

        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C2;
            // Root, Major Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 4, 7);
#ifdef RGBLIGHT_ENABLE
            switch_keylight_color4chords(record, keylocation);
#endif
            break;

        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C2;
            // Root, Minor Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 7);
#ifdef RGBLIGHT_ENABLE
            switch_keylight_color4chords(record, keylocation);
#endif
            break;

        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 4, 7, 10);
#ifdef RGBLIGHT_ENABLE
            switch_keylight_color4chords(record, keylocation);
#endif
            break;

        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C2;
            // Root, Minor Third, and Diminished 5th Note
            my_process_midi4TriadChords(midi_chord_ch, record, chord_status, chord, root_note, 0, 3, 6);
#ifdef RGBLIGHT_ENABLE
            switch_keylight_color4chords(record, keylocation);
#endif
            break;

#ifdef RGBLIGHT_ENABLE
        case KC_A ... KC_RGUI:                // for QWERTY
        case QK_GRAVE_ESCAPE:
        case ADJ_EIS:
        case MO_ADJ:
        case SHIF_UP:
            keylight_manager(record, HSV_RED, keylocation);
            break;
#endif

        // Keycodes on the right side.
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:  // notes on the right side keyboard.
            //  root_note is played by process_midi().
            if ( melody_dyad_high == true ) {        //  play 1 octave higher as well.
                my_process_midi(0, keycode, record, my_tone_status, 12, melody_unison_suppress);
#ifdef RGBLIGHT_ENABLE
                keylight_manager(record, HSV_RED, keylocation);
                keylight_manager(record, HSV_RED, keylocation2);
#endif
            } else if ( melody_dyad_low == true ) {  //  play 1 octave lower as well.
                my_process_midi(0, keycode, record, my_tone_status, -12, melody_unison_suppress);
#ifdef RGBLIGHT_ENABLE
                keylight_manager(record, HSV_CYAN, keylocation);
                keylight_manager(record, HSV_CYAN, keylocation2);
#endif
            } else {
                uprintf("layer=%u, default_layer_state = %u\n", biton32(default_layer_state), default_layer_state);
#ifdef RGBLIGHT_ENABLE
                keylight_manager(record, HSV_GOLDENROD, keylocation);
                keylight_manager(record, HSV_GOLDENROD, keylocation2);
#endif
            }
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
