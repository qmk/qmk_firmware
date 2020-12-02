/* Copyright 2016-2017 Jack Humbert
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
#ifndef QUANTUM_KEYCODES_H
#define QUANTUM_KEYCODES_H

#if defined(SEQUENCER_ENABLE)
#    include "sequencer.h"
#endif

#ifndef MIDI_ENABLE_STRICT
#    define MIDI_ENABLE_STRICT 0
#endif

#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_ADVANCED))
#    ifndef MIDI_TONE_KEYCODE_OCTAVES
#        define MIDI_TONE_KEYCODE_OCTAVES 3
#    endif
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum quantum_keycodes {
    // Ranges used in shortcuts - not to be used directly
    QK_BASIC                = 0x0000,
    QK_BASIC_MAX            = 0x00FF,
    QK_MODS                 = 0x0100,
    QK_LCTL                 = 0x0100,
    QK_LSFT                 = 0x0200,
    QK_LALT                 = 0x0400,
    QK_LGUI                 = 0x0800,
    QK_RMODS_MIN            = 0x1000,
    QK_RCTL                 = 0x1100,
    QK_RSFT                 = 0x1200,
    QK_RALT                 = 0x1400,
    QK_RGUI                 = 0x1800,
    QK_MODS_MAX             = 0x1FFF,
    QK_FUNCTION             = 0x2000,
    QK_FUNCTION_MAX         = 0x2FFF,
    QK_MACRO                = 0x3000,
    QK_MACRO_MAX            = 0x3FFF,
    QK_LAYER_TAP            = 0x4000,
    QK_LAYER_TAP_MAX        = 0x4FFF,
    QK_TO                   = 0x5000,
    QK_TO_MAX               = 0x50FF,
    QK_MOMENTARY            = 0x5100,
    QK_MOMENTARY_MAX        = 0x51FF,
    QK_DEF_LAYER            = 0x5200,
    QK_DEF_LAYER_MAX        = 0x52FF,
    QK_TOGGLE_LAYER         = 0x5300,
    QK_TOGGLE_LAYER_MAX     = 0x53FF,
    QK_ONE_SHOT_LAYER       = 0x5400,
    QK_ONE_SHOT_LAYER_MAX   = 0x54FF,
    QK_ONE_SHOT_MOD         = 0x5500,
    QK_ONE_SHOT_MOD_MAX     = 0x55FF,
    QK_TAP_DANCE            = 0x5700,
    QK_TAP_DANCE_MAX        = 0x57FF,
    QK_LAYER_TAP_TOGGLE     = 0x5800,
    QK_LAYER_TAP_TOGGLE_MAX = 0x58FF,
    QK_LAYER_MOD            = 0x5900,
    QK_LAYER_MOD_MAX        = 0x59FF,
#ifdef STENO_ENABLE
    QK_STENO        = 0x5A00,
    QK_STENO_BOLT   = 0x5A30,
    QK_STENO_GEMINI = 0x5A31,
    QK_STENO_MAX    = 0x5A3F,
#endif
#ifdef SWAP_HANDS_ENABLE
    QK_SWAP_HANDS     = 0x5B00,
    QK_SWAP_HANDS_MAX = 0x5BFF,
#endif
    QK_MOD_TAP     = 0x6000,
    QK_MOD_TAP_MAX = 0x7FFF,
#ifdef UNICODE_ENABLE
    QK_UNICODE     = 0x8000,
    QK_UNICODE_MAX = 0xFFFF,
#endif
#ifdef UNICODEMAP_ENABLE
    QK_UNICODEMAP          = 0x8000,
    QK_UNICODEMAP_MAX      = 0xBFFF,
    QK_UNICODEMAP_PAIR     = 0xC000,
    QK_UNICODEMAP_PAIR_MAX = 0xFFFF,
#endif

    // Loose keycodes - to be used directly

    RESET = 0x5C00,
    DEBUG,
    MAGIC_SWAP_CONTROL_CAPSLOCK,
    MAGIC_CAPSLOCK_TO_CONTROL,
    MAGIC_SWAP_LALT_LGUI,
    MAGIC_SWAP_RALT_RGUI,
    MAGIC_NO_GUI,
    MAGIC_SWAP_GRAVE_ESC,
    MAGIC_SWAP_BACKSLASH_BACKSPACE,
    MAGIC_HOST_NKRO,
    MAGIC_SWAP_ALT_GUI,
    MAGIC_UNSWAP_CONTROL_CAPSLOCK,
    MAGIC_UNCAPSLOCK_TO_CONTROL,
    MAGIC_UNSWAP_LALT_LGUI,
    MAGIC_UNSWAP_RALT_RGUI,
    MAGIC_UNNO_GUI,
    MAGIC_UNSWAP_GRAVE_ESC,
    MAGIC_UNSWAP_BACKSLASH_BACKSPACE,
    MAGIC_UNHOST_NKRO,
    MAGIC_UNSWAP_ALT_GUI,
    MAGIC_TOGGLE_NKRO,
    MAGIC_TOGGLE_ALT_GUI,
    GRAVE_ESC,

// Leader key
#ifdef LEADER_ENABLE
    KC_LEAD,
#endif

// Auto Shift setup
#ifndef AUTO_SHIFT_NO_SETUP
    KC_ASUP,
    KC_ASDN,
    KC_ASRP,
#endif
    KC_ASTG,
    KC_ASON,
    KC_ASOFF,

    // Audio on/off/toggle
    AU_ON,
    AU_OFF,
    AU_TOG,

    // Faux clicky as part of main audio feature
    CLICKY_TOGGLE,
    CLICKY_ENABLE,
    CLICKY_DISABLE,
    CLICKY_UP,
    CLICKY_DOWN,
    CLICKY_RESET,

#ifdef FAUXCLICKY_ENABLE
    // Faux clicky
    FC_ON,
    FC_OFF,
    FC_TOG,
#endif

    // Music mode on/off/toggle
    MU_ON,
    MU_OFF,
    MU_TOG,

    // Music mode cycle
    MU_MOD,

    // Music voice iterate
    MUV_IN,
    MUV_DE,

// Midi
#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
    MI_ON,
    MI_OFF,
    MI_TOG,
#endif

#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_ADVANCED))
    MIDI_TONE_MIN,

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 0
    MI_C = MIDI_TONE_MIN,
    MI_Cs,
    MI_Db = MI_Cs,
    MI_D,
    MI_Ds,
    MI_Eb = MI_Ds,
    MI_E,
    MI_F,
    MI_Fs,
    MI_Gb = MI_Fs,
    MI_G,
    MI_Gs,
    MI_Ab = MI_Gs,
    MI_A,
    MI_As,
    MI_Bb = MI_As,
    MI_B,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 1
    MI_C_1,
    MI_Cs_1,
    MI_Db_1 = MI_Cs_1,
    MI_D_1,
    MI_Ds_1,
    MI_Eb_1 = MI_Ds_1,
    MI_E_1,
    MI_F_1,
    MI_Fs_1,
    MI_Gb_1 = MI_Fs_1,
    MI_G_1,
    MI_Gs_1,
    MI_Ab_1 = MI_Gs_1,
    MI_A_1,
    MI_As_1,
    MI_Bb_1 = MI_As_1,
    MI_B_1,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 2
    MI_C_2,
    MI_Cs_2,
    MI_Db_2 = MI_Cs_2,
    MI_D_2,
    MI_Ds_2,
    MI_Eb_2 = MI_Ds_2,
    MI_E_2,
    MI_F_2,
    MI_Fs_2,
    MI_Gb_2 = MI_Fs_2,
    MI_G_2,
    MI_Gs_2,
    MI_Ab_2 = MI_Gs_2,
    MI_A_2,
    MI_As_2,
    MI_Bb_2 = MI_As_2,
    MI_B_2,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 3
    MI_C_3,
    MI_Cs_3,
    MI_Db_3 = MI_Cs_3,
    MI_D_3,
    MI_Ds_3,
    MI_Eb_3 = MI_Ds_3,
    MI_E_3,
    MI_F_3,
    MI_Fs_3,
    MI_Gb_3 = MI_Fs_3,
    MI_G_3,
    MI_Gs_3,
    MI_Ab_3 = MI_Gs_3,
    MI_A_3,
    MI_As_3,
    MI_Bb_3 = MI_As_3,
    MI_B_3,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 4
    MI_C_4,
    MI_Cs_4,
    MI_Db_4 = MI_Cs_4,
    MI_D_4,
    MI_Ds_4,
    MI_Eb_4 = MI_Ds_4,
    MI_E_4,
    MI_F_4,
    MI_Fs_4,
    MI_Gb_4 = MI_Fs_4,
    MI_G_4,
    MI_Gs_4,
    MI_Ab_4 = MI_Gs_4,
    MI_A_4,
    MI_As_4,
    MI_Bb_4 = MI_As_4,
    MI_B_4,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 5
    MI_C_5,
    MI_Cs_5,
    MI_Db_5 = MI_Cs_5,
    MI_D_5,
    MI_Ds_5,
    MI_Eb_5 = MI_Ds_5,
    MI_E_5,
    MI_F_5,
    MI_Fs_5,
    MI_Gb_5 = MI_Fs_5,
    MI_G_5,
    MI_Gs_5,
    MI_Ab_5 = MI_Gs_5,
    MI_A_5,
    MI_As_5,
    MI_Bb_5 = MI_As_5,
    MI_B_5,
#    endif

#    if !MIDI_ENABLE_STRICT || MIDI_TONE_KEYCODE_OCTAVES > 5
    MIDI_TONE_MAX = MI_B_5,
#    elif MIDI_TONE_KEYCODE_OCTAVES > 4
    MIDI_TONE_MAX = MI_B_4,
#    elif MIDI_TONE_KEYCODE_OCTAVES > 3
    MIDI_TONE_MAX = MI_B_3,
#    elif MIDI_TONE_KEYCODE_OCTAVES > 2
    MIDI_TONE_MAX = MI_B_2,
#    elif MIDI_TONE_KEYCODE_OCTAVES > 1
    MIDI_TONE_MAX = MI_B_1,
#    elif MIDI_TONE_KEYCODE_OCTAVES > 0
    MIDI_TONE_MAX = MI_B,
#    endif

    MIDI_OCTAVE_MIN,
    MI_OCT_N2 = MIDI_OCTAVE_MIN,
    MI_OCT_N1,
    MI_OCT_0,
    MI_OCT_1,
    MI_OCT_2,
    MI_OCT_3,
    MI_OCT_4,
    MI_OCT_5,
    MI_OCT_6,
    MI_OCT_7,
    MIDI_OCTAVE_MAX = MI_OCT_7,
    MI_OCTD,  // octave down
    MI_OCTU,  // octave up

    MIDI_TRANSPOSE_MIN,
    MI_TRNS_N6 = MIDI_TRANSPOSE_MIN,
    MI_TRNS_N5,
    MI_TRNS_N4,
    MI_TRNS_N3,
    MI_TRNS_N2,
    MI_TRNS_N1,
    MI_TRNS_0,
    MI_TRNS_1,
    MI_TRNS_2,
    MI_TRNS_3,
    MI_TRNS_4,
    MI_TRNS_5,
    MI_TRNS_6,
    MIDI_TRANSPOSE_MAX = MI_TRNS_6,
    MI_TRNSD,  // transpose down
    MI_TRNSU,  // transpose up

    MIDI_VELOCITY_MIN,
    MI_VEL_0 = MIDI_VELOCITY_MIN,
    MI_VEL_1,
    MI_VEL_2,
    MI_VEL_3,
    MI_VEL_4,
    MI_VEL_5,
    MI_VEL_6,
    MI_VEL_7,
    MI_VEL_8,
    MI_VEL_9,
    MI_VEL_10,
    MIDI_VELOCITY_MAX = MI_VEL_10,
    MI_VELD,  // velocity down
    MI_VELU,  // velocity up

    MIDI_CHANNEL_MIN,
    MI_CH1 = MIDI_CHANNEL_MIN,
    MI_CH2,
    MI_CH3,
    MI_CH4,
    MI_CH5,
    MI_CH6,
    MI_CH7,
    MI_CH8,
    MI_CH9,
    MI_CH10,
    MI_CH11,
    MI_CH12,
    MI_CH13,
    MI_CH14,
    MI_CH15,
    MI_CH16,
    MIDI_CHANNEL_MAX = MI_CH16,
    MI_CHD,  // previous channel
    MI_CHU,  // next channel

    MI_ALLOFF,  // all notes off

    MI_SUS,   // sustain
    MI_PORT,  // portamento
    MI_SOST,  // sostenuto
    MI_SOFT,  // soft pedal
    MI_LEG,   // legato

    MI_MOD,    // modulation
    MI_MODSD,  // decrease modulation speed
    MI_MODSU,  // increase modulation speed

    MI_BENDD,  // Bend down
    MI_BENDU,  // Bend up
#endif         // MIDI_ADVANCED

    // Backlight functionality
    BL_ON,
    BL_OFF,
    BL_DEC,
    BL_INC,
    BL_TOGG,
    BL_STEP,
    BL_BRTG,

    // RGB functionality
    RGB_TOG,
    RGB_MODE_FORWARD,
    RGB_MODE_REVERSE,
    RGB_HUI,
    RGB_HUD,
    RGB_SAI,
    RGB_SAD,
    RGB_VAI,
    RGB_VAD,
    RGB_SPI,
    RGB_SPD,
    RGB_MODE_PLAIN,
    RGB_MODE_BREATHE,
    RGB_MODE_RAINBOW,
    RGB_MODE_SWIRL,
    RGB_MODE_SNAKE,
    RGB_MODE_KNIGHT,
    RGB_MODE_XMAS,
    RGB_MODE_GRADIENT,
    RGB_MODE_RGBTEST,

    // Momentum matching toggle
    VLK_TOG,

    // Left shift, open paren
    KC_LSPO,

    // Right shift, close paren
    KC_RSPC,

    // Shift, Enter
    KC_SFTENT,

    // Printing
    PRINT_ON,
    PRINT_OFF,

    // output selection
    OUT_AUTO,
    OUT_USB,
#ifdef BLUETOOTH_ENABLE
    OUT_BT,
#endif

#ifdef KEY_LOCK_ENABLE
    KC_LOCK,
#endif

#ifdef TERMINAL_ENABLE
    TERM_ON,
    TERM_OFF,
#endif

    EEPROM_RESET,

    UNICODE_MODE_FORWARD,
    UNICODE_MODE_REVERSE,
    UNICODE_MODE_MAC,
    UNICODE_MODE_LNX,
    UNICODE_MODE_WIN,
    UNICODE_MODE_BSD,
    UNICODE_MODE_WINC,

    HPT_ON,
    HPT_OFF,
    HPT_TOG,
    HPT_RST,
    HPT_FBK,
    HPT_BUZ,
    HPT_MODI,
    HPT_MODD,
    HPT_CONT,
    HPT_CONI,
    HPT_COND,
    HPT_DWLI,
    HPT_DWLD,

    // Left control, open paren
    KC_LCPO,

    // Right control, close paren
    KC_RCPC,

    // Left control, open paren
    KC_LAPO,

    // Right control, close paren
    KC_RAPC,

    CMB_ON,
    CMB_OFF,
    CMB_TOG,

    MAGIC_SWAP_LCTL_LGUI,
    MAGIC_SWAP_RCTL_RGUI,
    MAGIC_UNSWAP_LCTL_LGUI,
    MAGIC_UNSWAP_RCTL_RGUI,
    MAGIC_SWAP_CTL_GUI,
    MAGIC_UNSWAP_CTL_GUI,
    MAGIC_TOGGLE_CTL_GUI,
    MAGIC_EE_HANDS_LEFT,
    MAGIC_EE_HANDS_RIGHT,

    // Dynamic Macros
    DYN_REC_START1,
    DYN_REC_START2,
    DYN_REC_STOP,
    DYN_MACRO_PLAY1,
    DYN_MACRO_PLAY2,

    JS_BUTTON0,
    JS_BUTTON_MIN = JS_BUTTON0,
    JS_BUTTON1,
    JS_BUTTON2,
    JS_BUTTON3,
    JS_BUTTON4,
    JS_BUTTON5,
    JS_BUTTON6,
    JS_BUTTON7,
    JS_BUTTON8,
    JS_BUTTON9,
    JS_BUTTON10,
    JS_BUTTON11,
    JS_BUTTON12,
    JS_BUTTON13,
    JS_BUTTON14,
    JS_BUTTON15,
    JS_BUTTON16,
    JS_BUTTON17,
    JS_BUTTON18,
    JS_BUTTON19,
    JS_BUTTON20,
    JS_BUTTON21,
    JS_BUTTON22,
    JS_BUTTON23,
    JS_BUTTON24,
    JS_BUTTON25,
    JS_BUTTON26,
    JS_BUTTON27,
    JS_BUTTON28,
    JS_BUTTON29,
    JS_BUTTON30,
    JS_BUTTON31,
    JS_BUTTON_MAX = JS_BUTTON31,

#if defined(SEQUENCER_ENABLE)
    SQ_ON,
    SQ_OFF,
    SQ_TOG,

    SQ_TMPD,  // Decrease tempo
    SQ_TMPU,  // Increase tempo

    SEQUENCER_RESOLUTION_MIN,
    SEQUENCER_RESOLUTION_MAX = SEQUENCER_RESOLUTION_MIN + SEQUENCER_RESOLUTIONS,
    SQ_RESD,  // Decrease resolution
    SQ_RESU,  // Increase resolution

    SQ_SALL,  // All steps on
    SQ_SCLR,  // All steps off
    SEQUENCER_STEP_MIN,
    SEQUENCER_STEP_MAX = SEQUENCER_STEP_MIN + SEQUENCER_STEPS,

    SEQUENCER_TRACK_MIN,
    SEQUENCER_TRACK_MAX = SEQUENCER_TRACK_MIN + SEQUENCER_TRACKS,

/**
 * Helpers to assign a keycode to a step, a resolution, or a track.
 * Falls back to NOOP if n is out of range.
 */
#    define SQ_S(n) (n < SEQUENCER_STEPS ? SEQUENCER_STEP_MIN + n : XXXXXXX)
#    define SQ_R(n) (n < SEQUENCER_RESOLUTIONS ? SEQUENCER_RESOLUTION_MIN + n : XXXXXXX)
#    define SQ_T(n) (n < SEQUENCER_TRACKS ? SEQUENCER_TRACK_MIN + n : XXXXXXX)

#endif

    // always leave at the end
    SAFE_RANGE
};

// Ability to use mods in layouts
#define LCTL(kc) (QK_LCTL | (kc))
#define LSFT(kc) (QK_LSFT | (kc))
#define LALT(kc) (QK_LALT | (kc))
#define LGUI(kc) (QK_LGUI | (kc))
#define LOPT(kc) LALT(kc)
#define LCMD(kc) LGUI(kc)
#define LWIN(kc) LGUI(kc)
#define RCTL(kc) (QK_RCTL | (kc))
#define RSFT(kc) (QK_RSFT | (kc))
#define RALT(kc) (QK_RALT | (kc))
#define RGUI(kc) (QK_RGUI | (kc))
#define ALGR(kc) RALT(kc)
#define ROPT(kc) RALT(kc)
#define RCMD(kc) RGUI(kc)
#define RWIN(kc) RGUI(kc)

#define HYPR(kc) (QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI | (kc))
#define MEH(kc) (QK_LCTL | QK_LSFT | QK_LALT | (kc))
#define LCAG(kc) (QK_LCTL | QK_LALT | QK_LGUI | (kc))
#define SGUI(kc) (QK_LGUI | QK_LSFT | (kc))
#define SCMD(kc) SGUI(kc)
#define SWIN(kc) SGUI(kc)
#define LCA(kc) (QK_LCTL | QK_LALT | (kc))
#define LSA(kc) (QK_LSFT | QK_LALT | (kc))
#define RSA(kc) (QK_RSFT | QK_RALT | (kc))
#define RCS(kc) (QK_RCTL | QK_RSFT | (kc))
#define SAGR(kc) RSA(kc)

#define MOD_HYPR 0xF
#define MOD_MEH 0x7

// Aliases for shifted symbols
// Each key has a 4-letter code, and some have longer aliases too.
// While the long aliases are descriptive, the 4-letter codes
// make for nicer grid layouts (everything lines up), and are
// the preferred style for Quantum.
#define KC_TILD LSFT(KC_GRV)  // ~
#define KC_TILDE KC_TILD

#define KC_EXLM LSFT(KC_1)  // !
#define KC_EXCLAIM KC_EXLM

#define KC_AT LSFT(KC_2)  // @

#define KC_HASH LSFT(KC_3)  // #

#define KC_DLR LSFT(KC_4)  // $
#define KC_DOLLAR KC_DLR

#define KC_PERC LSFT(KC_5)  // %
#define KC_PERCENT KC_PERC

#define KC_CIRC LSFT(KC_6)  // ^
#define KC_CIRCUMFLEX KC_CIRC

#define KC_AMPR LSFT(KC_7)  // &
#define KC_AMPERSAND KC_AMPR

#define KC_ASTR LSFT(KC_8)  // *
#define KC_ASTERISK KC_ASTR

#define KC_LPRN LSFT(KC_9)  // (
#define KC_LEFT_PAREN KC_LPRN

#define KC_RPRN LSFT(KC_0)  // )
#define KC_RIGHT_PAREN KC_RPRN

#define KC_UNDS LSFT(KC_MINS)  // _
#define KC_UNDERSCORE KC_UNDS

#define KC_PLUS LSFT(KC_EQL)  // +

#define KC_LCBR LSFT(KC_LBRC)  // {
#define KC_LEFT_CURLY_BRACE KC_LCBR

#define KC_RCBR LSFT(KC_RBRC)  // }
#define KC_RIGHT_CURLY_BRACE KC_RCBR

#define KC_LABK LSFT(KC_COMM)  // <
#define KC_LEFT_ANGLE_BRACKET KC_LABK

#define KC_RABK LSFT(KC_DOT)  // >
#define KC_RIGHT_ANGLE_BRACKET KC_RABK

#define KC_COLN LSFT(KC_SCLN)  // :
#define KC_COLON KC_COLN

#define KC_PIPE LSFT(KC_BSLS)  // |

#define KC_LT LSFT(KC_COMM)  // <

#define KC_GT LSFT(KC_DOT)  // >

#define KC_QUES LSFT(KC_SLSH)  // ?
#define KC_QUESTION KC_QUES

#define KC_DQT LSFT(KC_QUOT)  // "
#define KC_DOUBLE_QUOTE KC_DQT
#define KC_DQUO KC_DQT

#define KC_DELT KC_DELETE  // Del key (four letter code)

// Alias for function layers than expand past FN31
#define FUNC(kc) (QK_FUNCTION | (kc))

// Aliases
#define C(kc) LCTL(kc)
#define S(kc) LSFT(kc)
#define A(kc) LALT(kc)
#define G(kc) LGUI(kc)

#define F(kc) FUNC(kc)
#define M(kc) (QK_MACRO | (kc))

#define MACROTAP(kc) (QK_MACRO | (FUNC_TAP << 8) | (kc))
#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

#define KC_GESC GRAVE_ESC

#define EEP_RST EEPROM_RESET

#define CK_TOGG CLICKY_TOGGLE
#define CK_RST CLICKY_RESET
#define CK_UP CLICKY_UP
#define CK_DOWN CLICKY_DOWN
#define CK_ON CLICKY_ENABLE
#define CK_OFF CLICKY_DISABLE

#define RGB_MOD RGB_MODE_FORWARD
#define RGB_RMOD RGB_MODE_REVERSE

#define RGB_M_P RGB_MODE_PLAIN
#define RGB_M_B RGB_MODE_BREATHE
#define RGB_M_R RGB_MODE_RAINBOW
#define RGB_M_SW RGB_MODE_SWIRL
#define RGB_M_SN RGB_MODE_SNAKE
#define RGB_M_K RGB_MODE_KNIGHT
#define RGB_M_X RGB_MODE_XMAS
#define RGB_M_G RGB_MODE_GRADIENT
#define RGB_M_T RGB_MODE_RGBTEST

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))

#define CL_SWAP MAGIC_SWAP_CONTROL_CAPSLOCK
#define CL_NORM MAGIC_UNSWAP_CONTROL_CAPSLOCK
#define CL_CTRL MAGIC_CAPSLOCK_TO_CONTROL
#define CL_CAPS MAGIC_UNCAPSLOCK_TO_CONTROL

#define LCG_SWP MAGIC_SWAP_LCTL_LGUI
#define LCG_NRM MAGIC_UNSWAP_LCTL_LGUI
#define RCG_SWP MAGIC_SWAP_RCTL_RGUI
#define RCG_NRM MAGIC_UNSWAP_RCTL_RGUI
#define CG_SWAP MAGIC_SWAP_CTL_GUI
#define CG_NORM MAGIC_UNSWAP_CTL_GUI
#define CG_TOGG MAGIC_TOGGLE_CTL_GUI

#define LAG_SWP MAGIC_SWAP_LALT_LGUI
#define LAG_NRM MAGIC_UNSWAP_LALT_LGUI
#define RAG_SWP MAGIC_SWAP_RALT_RGUI
#define RAG_NRM MAGIC_UNSWAP_RALT_RGUI
#define AG_SWAP MAGIC_SWAP_ALT_GUI
#define AG_NORM MAGIC_UNSWAP_ALT_GUI
#define AG_TOGG MAGIC_TOGGLE_ALT_GUI

#define GUI_OFF MAGIC_NO_GUI
#define GUI_ON MAGIC_UNNO_GUI

#define GE_SWAP MAGIC_SWAP_GRAVE_ESC
#define GE_NORM MAGIC_UNSWAP_GRAVE_ESC

#define BS_SWAP MAGIC_SWAP_BACKSLASH_BACKSPACE
#define BS_NORM MAGIC_UNSWAP_BACKSLASH_BACKSPACE

#define NK_ON MAGIC_HOST_NKRO
#define NK_OFF MAGIC_UNHOST_NKRO
#define NK_TOGG MAGIC_TOGGLE_NKRO

#define EH_LEFT MAGIC_EE_HANDS_LEFT
#define EH_RGHT MAGIC_EE_HANDS_RIGHT

// GOTO layer - 16 layers max
// when:
// ON_PRESS    = 1
// ON_RELEASE  = 2
// Unless you have a good reason not to do so, prefer  ON_PRESS (1) as your default.
// In fact, we changed it to assume ON_PRESS for sanity/simplicity. If needed, you can add your own
// keycode modeled after the old version, kept below for this.
/* #define TO(layer, when) (QK_TO | (when << 0x4) | (layer & 0xFF)) */
#define TO(layer) (QK_TO | (ON_PRESS << 0x4) | ((layer)&0xFF))

// Momentary switch layer - 256 layer max
#define MO(layer) (QK_MOMENTARY | ((layer)&0xFF))

// Set default layer - 256 layer max
#define DF(layer) (QK_DEF_LAYER | ((layer)&0xFF))

// Toggle to layer - 256 layer max
#define TG(layer) (QK_TOGGLE_LAYER | ((layer)&0xFF))

// One-shot layer - 256 layer max
#define OSL(layer) (QK_ONE_SHOT_LAYER | ((layer)&0xFF))

// L-ayer M-od: Momentary switch layer with modifiers active - 16 layer max, left mods only
#define LM(layer, mod) (QK_LAYER_MOD | (((layer)&0xF) << 4) | ((mod)&0xF))

// One-shot mod
#define OSM(mod) (QK_ONE_SHOT_MOD | ((mod)&0xFF))

// Layer tap-toggle
#define TT(layer) (QK_LAYER_TAP_TOGGLE | ((layer)&0xFF))

// M-od, T-ap - 256 keycode max
#define MT(mod, kc) (QK_MOD_TAP | (((mod)&0x1F) << 8) | ((kc)&0xFF))

#define LCTL_T(kc) MT(MOD_LCTL, kc)
#define RCTL_T(kc) MT(MOD_RCTL, kc)
#define CTL_T(kc) LCTL_T(kc)

#define LSFT_T(kc) MT(MOD_LSFT, kc)
#define RSFT_T(kc) MT(MOD_RSFT, kc)
#define SFT_T(kc) LSFT_T(kc)

#define LALT_T(kc) MT(MOD_LALT, kc)
#define RALT_T(kc) MT(MOD_RALT, kc)
#define LOPT_T(kc) LALT_T(kc)
#define ROPT_T(kc) RALT_T(kc)
#define ALGR_T(kc) RALT_T(kc)
#define ALT_T(kc) LALT_T(kc)
#define OPT_T(kc) LOPT_T(kc)

#define LGUI_T(kc) MT(MOD_LGUI, kc)
#define RGUI_T(kc) MT(MOD_RGUI, kc)
#define LCMD_T(kc) LGUI_T(kc)
#define LWIN_T(kc) LGUI_T(kc)
#define RCMD_T(kc) RGUI_T(kc)
#define RWIN_T(kc) RGUI_T(kc)
#define GUI_T(kc) LGUI_T(kc)
#define CMD_T(kc) LCMD_T(kc)
#define WIN_T(kc) LWIN_T(kc)

#define C_S_T(kc) MT(MOD_LCTL | MOD_LSFT, kc)                         // Left Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT, kc)              // Meh is a less hyper version of the Hyper key -- doesn't include GUI, so just Left Control + Shift + Alt
#define LCAG_T(kc) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, kc)             // Left Control + Alt + GUI
#define RCAG_T(kc) MT(MOD_RCTL | MOD_RALT | MOD_RGUI, kc)             // Right Control + Alt + GUI
#define HYPR_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, kc)  // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/
#define SGUI_T(kc) MT(MOD_LGUI | MOD_LSFT, kc)                        // Left Shift + GUI
#define SCMD_T(kc) SGUI_T(kc)
#define SWIN_T(kc) SGUI_T(kc)
#define LCA_T(kc) MT(MOD_LCTL | MOD_LALT, kc)  // Left Control + Alt
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)  // Left Shift + Alt
#define RSA_T(kc) MT(MOD_RSFT | MOD_RALT, kc)  // Right Shift + Alt
#define RCS_T(kc) MT(MOD_RCTL | MOD_RSFT, kc)  // Right Control + Shift
#define SAGR_T(kc) RSA_T(kc)

#define ALL_T(kc) HYPR_T(kc)

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH MEH(KC_NO)

#ifdef UNICODE_ENABLE
// Allows Unicode input up to 0x7FFF
#    define UC(c) (QK_UNICODE | (c))
#endif
#ifdef UNICODEMAP_ENABLE
// Allows Unicode input up to 0x10FFFF, requires unicode_map
#    define X(i) (QK_UNICODEMAP | (i))
#    define XP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7))  // 127 max i and j
#endif

#define UC_MOD UNICODE_MODE_FORWARD
#define UC_RMOD UNICODE_MODE_REVERSE

#define UC_M_MA UNICODE_MODE_MAC
#define UNICODE_MODE_OSX UNICODE_MODE_MAC  // Deprecated alias
#define UC_M_OS UNICODE_MODE_MAC           // Deprecated alias
#define UC_M_LN UNICODE_MODE_LNX
#define UC_M_WI UNICODE_MODE_WIN
#define UC_M_BS UNICODE_MODE_BSD
#define UC_M_WC UNICODE_MODE_WINC

#ifdef SWAP_HANDS_ENABLE
#    define SH_T(kc) (QK_SWAP_HANDS | (kc))
#    define SH_TG (QK_SWAP_HANDS | OP_SH_TOGGLE)
#    define SH_TT (QK_SWAP_HANDS | OP_SH_TAP_TOGGLE)
#    define SH_OS (QK_SWAP_HANDS | OP_SH_ONESHOT)
#    define SH_MON (QK_SWAP_HANDS | OP_SH_ON_OFF)
#    define SH_MOFF (QK_SWAP_HANDS | OP_SH_OFF_ON)
#    define SH_ON (QK_SWAP_HANDS | OP_SH_ON)
#    define SH_OFF (QK_SWAP_HANDS | OP_SH_OFF)
#endif

// Dynamic Macros aliases
#define DM_REC1 DYN_REC_START1
#define DM_REC2 DYN_REC_START2
#define DM_RSTP DYN_REC_STOP
#define DM_PLY1 DYN_MACRO_PLAY1
#define DM_PLY2 DYN_MACRO_PLAY2

#endif  // QUANTUM_KEYCODES_H
