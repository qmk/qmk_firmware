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

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper_giabaRInaix2(...) LAYOUT_giabaRInaix2(__VA_ARGS__)

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define DFCBASE DF(_C_SYSTEM_BASE)
#define DF_QWER DF(_QWERTY)
// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;
uint8_t midi_base_ch = 0, midi_chord_ch = 0;  // By default, all use the same channel.
extern MidiDevice midi_device;

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
    0,  12,  24,  36,  48,  11,  23,  35,  47,  59,
    1,  13,  25,  37,  49,  10,  22,  34,  46,  58,
    2,  14,  26,  38,  50,  9,   21,  33,  45,  57,
    3,  15,  27,  39,  51,  8,   20,  32,  44,  56,
    4,  16,  28,  40,  52,  7,   19,  31,  43,  55,
    5,  17,  29,  41,  53,  6,   18,  30,  42,  54,

  119, 107,  95,  83,  71, 108,  96,  84,  72,  60,
  118, 106,  94,  82,  70, 109,  97,  85,  73,  61,
  117, 105,  93,  81,  69, 110,  98,  86,  74,  62,
  116, 104,  92,  80,  68, 111,  99,  87,  75,  63,
  115, 103,  91,  79,  67, 112, 100,  88,  76,  64,
  114, 102,  90,  78,  66, 113, 101,  89,  77,  65
};


#endif  //  RGBLIGHT_ENABLE
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _C_SYSTEM_BASE,      //  MIDI C-system
    _C_SYSTEM_BASS2ROW,  //  counter bass system
    _C_SYSTEM_ENTIRELY,  //  single notes for both left and right keybaords.
    _CHROMATONE,
    _QWERTY,             //  just in case
    _FN
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

    CSYSTEM,
    CNTBASC,
    CSYSALL,
    CHRTONE,
    TGLMISW
};

#define MY_CHORD_COUNT (MY_CHORD_MAX - MY_CHORD_MIN + 1)
static uint8_t chord_status[MY_CHORD_COUNT];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* C-system Base */
  [_C_SYSTEM_BASE] = LAYOUT_giabaRInaix2(
    MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
      MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
        MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
          MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,
            MI_CH_DbDim7, MI_CH_AbDim7, MI_CH_EbDim7, MI_CH_BbDim7, MI_CH_FDim7, MI_CH_CDim7, MI_CH_GDim7, MI_CH_DDim7, MI_CH_ADim7, MI_CH_EDim7, MI_CH_BDim7, MI_CH_FsDim7,

    MI_Db_2,      MI_E_2,       MI_G_2,       MI_Bb_2,      MI_Db_3,     MI_E_3,      MI_G_3,      MI_Bb_3,     MI_Db_4,     MI_E_4,      MI_G_4,      MI_Bb_4,
      MI_Eb_2,      MI_Fs_2,      MI_A_2,       MI_C_3,       MI_Eb_3,     MI_Fs_3,     MI_A_3,      MI_C_4,      MI_Eb_4,     MI_Fs_4,     MI_A_4,      MI_C_5,
        MI_F_2,       MI_Ab_2,      MI_B_2,       MI_D_3,       MI_F_3,      MI_Ab_3,     MI_B_3,      MI_D_4,      MI_F_4,      MI_Ab_4,     MI_B_4,      MI_D_5,
          MI_G_2,       MI_Bb_2,      MI_Db_3,      MI_E_3,       MI_G_3,      MI_Bb_3,     MI_Db_4,     MI_E_4,      MI_G_4,      MI_Bb_4,     MI_Db_5,     MI_E_5,
            MI_A_2,       MI_C_3,       MI_Eb_3,      MI_Fs_3,      MI_A_3,      MI_C_4,      MI_Eb_4,     MI_Fs_4,     MI_A_4,      MI_C_5,      MI_Eb_5,     FN_MUTE
  ),

  /* BASS2row */
  [_C_SYSTEM_BASS2ROW] = LAYOUT_giabaRInaix2(
    MI_CH_Fr,     MI_CH_Cr,     MI_CH_Gr,     MI_CH_Dr,     MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,   MI_CH_Csr,   MI_CH_Gsr,   MI_CH_Dsr,   MI_CH_Asr,
      MI_CH_Dbr,    MI_CH_Abr,    MI_CH_Ebr,    MI_CH_Bbr,    MI_CH_Fr,    MI_CH_Cr,    MI_CH_Gr,    MI_CH_Dr,    MI_CH_Ar,    MI_CH_Er,    MI_CH_Br,    MI_CH_Fsr,
        MI_CH_Db,     MI_CH_Ab,     MI_CH_Eb,     MI_CH_Bb,     MI_CH_F,     MI_CH_C,     MI_CH_G,     MI_CH_D,     MI_CH_A,     MI_CH_E,     MI_CH_B,     MI_CH_Fs,
          MI_CH_Dbm,    MI_CH_Abm,    MI_CH_Ebm,    MI_CH_Bbm,    MI_CH_Fm,    MI_CH_Cm,    MI_CH_Gm,    MI_CH_Dm,    MI_CH_Am,    MI_CH_Em,    MI_CH_Bm,    MI_CH_Fsm,
            MI_CH_DbDom7, MI_CH_AbDom7, MI_CH_EbDom7, MI_CH_BbDom7, MI_CH_FDom7, MI_CH_CDom7, MI_CH_GDom7, MI_CH_DDom7, MI_CH_ADom7, MI_CH_EDom7, MI_CH_BDom7, MI_CH_FsDom7,


    MI_Db_2,      MI_E_2,       MI_G_2,       MI_Bb_2,      MI_Db_3,     MI_E_3,      MI_G_3,      MI_Bb_3,     MI_Db_4,     MI_E_4,      MI_G_4,      MI_Bb_4,
      MI_Eb_2,      MI_Fs_2,      MI_A_2,       MI_C_3,       MI_Eb_3,     MI_Fs_3,     MI_A_3,      MI_C_4,      MI_Eb_4,     MI_Fs_4,     MI_A_4,      MI_C_5,
        MI_F_2,       MI_Ab_2,      MI_B_2,       MI_D_3,       MI_F_3,      MI_Ab_3,     MI_B_3,      MI_D_4,      MI_F_4,      MI_Ab_4,     MI_B_4,      MI_D_5,
          MI_G_2,       MI_Bb_2,      MI_Db_3,      MI_E_3,       MI_G_3,      MI_Bb_3,     MI_Db_4,     MI_E_4,      MI_G_4,      MI_Bb_4,     MI_Db_5,     MI_E_5,
            MI_A_2,       MI_C_3,       MI_Eb_3,      MI_Fs_3,      MI_A_3,      MI_C_4,      MI_Eb_4,     MI_Fs_4,     MI_A_4,      MI_C_5,      MI_Eb_5,     FN_MUTE
  ),

  /* C-system entirely */
  [_C_SYSTEM_ENTIRELY] = LAYOUT_giabaRInaix2(
    XXXXXXX, XXXXXXX, XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2,
      XXXXXXX, XXXXXXX, MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2,
        XXXXXXX, XXXXXXX, MI_D,    MI_F,    MI_Ab,   MI_B,    MI_D_1,  MI_F_1,  MI_Ab_1, MI_B_1,  MI_D_2,  MI_F_2,
          XXXXXXX, MI_Db,   MI_E,    MI_G,    MI_Bb,   MI_Db_1, MI_E_1,  MI_G_1,  MI_Bb_1, MI_Db_2, MI_E_2,  MI_G_2,
            MI_C,    MI_Eb,   MI_Fs,   MI_A,    MI_C_1,  MI_Eb_1, MI_Fs_1, MI_A_1,  MI_C_2,  MI_Eb_2, MI_Fs_2, MI_A_2,

    MI_E_2,  MI_G_2,  MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,   MI_G_4, MI_Bb_4, MI_Db_5,
      MI_Fs_2, MI_A_2,  MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4,  MI_A_4, MI_C_5,  MI_Eb_5,
        MI_Ab_2, MI_B_2,  MI_D_3,  MI_F_3,  MI_Ab_3, MI_B_3,  MI_D_4,  MI_F_4,  MI_Ab_4, MI_B_4,  MI_D_5,  MI_F_5,
          MI_Bb_2, MI_Db_3, MI_E_3,  MI_G_3,  MI_Bb_3, MI_Db_4, MI_E_4,  MI_G_4,  MI_Bb_4, MI_Db_5, MI_E_5,  MI_G_5,
            MI_C_3,  MI_Eb_3, MI_Fs_3, MI_A_3,  MI_C_4,  MI_Eb_4, MI_Fs_4, MI_A_4,  MI_C_5,  MI_Eb_5, MI_Fs_5,  FN_MUTE
  ),

  /* Chromatone */
  [_CHROMATONE] = LAYOUT_giabaRInaix2(
    XXXXXXX, XXXXXXX, MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1,  MI_Eb_1,  MI_F_1,   MI_G_1,
        XXXXXXX,  MI_C,    MI_D,    MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C_1,  MI_D_1,  MI_E_1,  MI_Fs_1, MI_Ab_1,
             XXXXXXX, MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1,  MI_Eb_1,  MI_F_1,   MI_G_1,   MI_A_1,
                  MI_C,    MI_D,    MI_E,    MI_Fs,   MI_Ab,   MI_Bb,   MI_C_1,  MI_D_1,  MI_E_1,  MI_Fs_1, MI_Ab_1, MI_Bb_1,
                      MI_Db,   MI_Eb,   MI_F,    MI_G,    MI_A,    MI_B,    MI_Db_1,  MI_Eb_1,  MI_F_1,   MI_G_1,   MI_A_1,  MI_B_1,

    MI_A_1,  MI_B_1, MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_Db_3,  MI_Eb_3,  MI_F_3,   MI_G_3,
         MI_Bb_1, MI_C_2,  MI_D_2,  MI_E_2,  MI_Gb_2, MI_Ab_2, MI_Bb_2, MI_C_3,  MI_D_3,  MI_E_3,  MI_Gb_3, MI_Ab_3,
             MI_B_1, MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_Db_3,  MI_Eb_3,  MI_F_3,   MI_G_3,   MI_A_3,
                  MI_C_2,  MI_D_2,  MI_E_2,  MI_Gb_2, MI_Ab_2, MI_Bb_2, MI_C_3,  MI_D_3,  MI_E_3,  MI_Gb_3, MI_Ab_3, MI_Bb_3,
                     MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_Db_3,  MI_Eb_3,  MI_F_3,   MI_G_3,   MI_A_3,  FN_MUTE
  ),
  /* QWERTY */
  [_QWERTY] = LAYOUT_wrapper_giabaRInaix2(
    KC_GESC, _________________NUMBER_L__________________, _________________NUMBER_R__________________, KC_BSPC,
      KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_DEL,
        KC_CAPS, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_ENT,
          KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
            KC_LCTL, KC_LGUI, KC_LALT, KC_LANG2, KC_SPC,  KC_SPC, KC_SPC, KC_SPC, KC_LANG1, KC_RALT,  KC_RGUI, KC_RCTRL,

    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* Fn */
  [_FN] = LAYOUT_giabaRInaix2(
    CSYSTEM, CNTBASC, CSYSALL, CHRTONE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
      DF_QWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TGLMISW,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    CSYSTEM, CNTBASC, CSYSALL, CHRTONE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
      DF_QWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TGLMISW,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______
  )
};

#ifdef RGBLIGHT_ENABLE

// Light up fn layer keys
const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(                           //  left keyboard
                                                                         {0,   4, HSV_ORANGE},      //  MIDI layouts
                                                                         {11,  1, HSV_RED},         //  RGB_TOG
                                                                         {12,  1, HSV_WHITE},       //  DF_QWER
                                                                         {35,  1, HSV_TEAL},        //  TGLMISW

                                                                                                    //  right keyboard
                                                                         {60,  4, HSV_ORANGE},      //  MIDI layouts
                                                                         {71 , 1, HSV_RED},         //  RGB_TOG
                                                                         {72,  1, HSV_WHITE},       //  DF_QWER
                                                                         {83,  1, HSV_TEAL}         //  TGLMISW
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_fn_layer);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, _FN));
    return state;
};

#endif  //  RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    //  Set otave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    for (uint8_t i = 0; i < MY_CHORD_COUNT; i++) {
        chord_status[i] = MIDI_INVALID_NOTE;
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
    }

    if (record->event.pressed) {
        rgblight_sethsv_at(hue, sat, val, keylocation);
    } else {
        rgblight_sethsv_at(HSV_BLACK, keylocation);
    }
}
#endif  // RGBLIGHT_ENABLE

void my_process_midi4TriadChords(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint16_t root_note,
                                 uint8_t offset1, uint8_t offset2, uint8_t offset3) {
    uint8_t chord    = keycode - MY_CHORD_MIN;
    uint8_t velocity = midi_config.velocity;
    if (record->event.pressed) {
        if (chord_status[chord] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(root_note);
            midi_send_noteon(&midi_device, channel, note + offset1, velocity);
            midi_send_noteon(&midi_device, channel, note + offset2, velocity);
            midi_send_noteon(&midi_device, channel, note + offset3, velocity);
            dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
            chord_status[chord] = note;  // store root_note status.
        }
    } else {
        uint8_t note = chord_status[chord];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note + offset1, velocity);
            midi_send_noteoff(&midi_device, channel, note + offset2, velocity);
            midi_send_noteoff(&midi_device, channel, note + offset3, velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
    chord_status[chord] = MIDI_INVALID_NOTE;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t root_note = MIDI_INVALID_NOTE;  // Starting value for the root note of each chord

    #ifdef RGBLIGHT_ENABLE
        /* prepare for turning on LEDs when keys are pressed. */
        uint8_t r            = record->event.key.row;
        uint8_t c            = record->event.key.col;
        uint8_t keylocation  = pgm_read_byte(&convert_key_to_led[MATRIX_COLS * r + c]);
    #endif  // RGBLIGHT_ENABLE

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

        case TGLMISW:
            if (record->event.pressed) {
                toggle_MIDI_channel_separation();
            };
            break;


        // MIDI Chord Keycodes, on the left side.
        case MI_CH_Cr ... MI_CH_Br:  // Root Notes
            root_note = keycode - MI_CH_Cr + MI_C_1;
        ////////////////////////////////////////////////////////////////////
            {
                uint8_t channel  = midi_base_ch;
                uint8_t chord    = keycode - MY_CHORD_MIN;
                uint8_t velocity = midi_config.velocity;
                if (record->event.pressed) {
                    if (chord_status[chord] == MIDI_INVALID_NOTE) {
                        uint8_t note = midi_compute_note(root_note);
                        midi_send_noteon(&midi_device, channel, note, velocity);
                        midi_send_noteon(&midi_device, channel, note + 12, velocity);  // +1 Octave
                        dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
                        chord_status[chord] = note;  // store root_note status.
                    }
                } else {
                    uint8_t note = chord_status[chord];
                    if (note != MIDI_INVALID_NOTE) {
                        midi_send_noteoff(&midi_device, channel, note, velocity);
                        midi_send_noteoff(&midi_device, channel, note + 12, velocity);  // +1 Octave
                        dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
                    }
                    chord_status[chord] = MIDI_INVALID_NOTE;
                }
                return false;
            }////////////////////////////////////////////////////////////////////
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;
        case MI_CH_C ... MI_CH_B:  // Major Chords
            root_note = keycode - MI_CH_C + MI_C_2;
            // Root, Major Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, keycode, record, root_note, 0, 4, 7);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;
        case MI_CH_Cm ... MI_CH_Bm:  // Minor Chord
            root_note = keycode - MI_CH_Cm + MI_C_2;
            // Root, Minor Third, and Fifth Notes
            my_process_midi4TriadChords(midi_chord_ch, keycode, record, root_note, 0, 3, 7);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;
        case MI_CH_CDom7 ... MI_CH_BDom7:  // Dominant 7th Chord
            root_note = keycode - MI_CH_CDom7 + MI_C_2;
            // Major Third, Major Fifth, and Minor Seventh Notes
            my_process_midi4TriadChords(midi_chord_ch, keycode, record, root_note, 4, 7, 10);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;
        case MI_CH_CDim7 ... MI_CH_BDim7:                // Diminished 7th Chord
            root_note = keycode - MI_CH_CDim7 + MI_C_2;
            // Root, Minor Third, and Diminished 5th Note
            my_process_midi4TriadChords(midi_chord_ch, keycode, record, root_note, 0, 3, 6);
#ifdef RGBLIGHT_ENABLE
            keylight_manager(record, HSV_GOLDENROD, keylocation);
#endif
            break;

#ifdef RGBLIGHT_ENABLE
        case KC_A ... KC_RGUI:                // for QWERTY
        case KC_GESC:
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
#endif
            // Keycodes on the right side.
#ifdef RGBLIGHT_ENABLE
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:  // notes on the right side.
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
        // case KC_MUTE:
        case FN_MUTE:
            keylight_manager(record, HSV_GOLDENROD, keylocation);
            break;
#endif
    }
    return true;
}
