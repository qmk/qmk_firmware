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

#pragma once

#include "sequencer.h"

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
    QK_SWAP_HANDS           = 0x5600,
    QK_SWAP_HANDS_MAX       = 0x56FF,
    QK_TAP_DANCE            = 0x5700,
    QK_TAP_DANCE_MAX        = 0x57FF,
    QK_LAYER_TAP_TOGGLE     = 0x5800,
    QK_LAYER_TAP_TOGGLE_MAX = 0x58FF,
    QK_LAYER_MOD            = 0x5900,
    QK_LAYER_MOD_MAX        = 0x59FF,
    QK_STENO                = 0x5A00,
    QK_STENO_BOLT           = 0x5A30,
    QK_STENO_GEMINI         = 0x5A31,
    QK_STENO_MAX            = 0x5A3F,
    // 0x5C00 - 0x5FFF are reserved, see below
    QK_MOD_TAP             = 0x6000,
    QK_MOD_TAP_MAX         = 0x7FFF,
    QK_UNICODE             = 0x8000,
    QK_UNICODE_MAX         = 0xFFFF,
    QK_UNICODEMAP          = 0x8000,
    QK_UNICODEMAP_MAX      = 0xBFFF,
    QK_UNICODEMAP_PAIR     = 0xC000,
    QK_UNICODEMAP_PAIR_MAX = 0xFFFF,

    // Loose keycodes - to be used directly
    RESET = 0x5C00,
    DEBUG,  // 5C01

    // Magic
    MAGIC_SWAP_CONTROL_CAPSLOCK,       // 5C02
    MAGIC_CAPSLOCK_TO_CONTROL,         // 5C03
    MAGIC_SWAP_LALT_LGUI,              // 5C04
    MAGIC_SWAP_RALT_RGUI,              // 5C05
    MAGIC_NO_GUI,                      // 5C06
    MAGIC_SWAP_GRAVE_ESC,              // 5C07
    MAGIC_SWAP_BACKSLASH_BACKSPACE,    // 5C08
    MAGIC_HOST_NKRO,                   // 5C09
    MAGIC_SWAP_ALT_GUI,                // 5C0A
    MAGIC_UNSWAP_CONTROL_CAPSLOCK,     // 5C0B
    MAGIC_UNCAPSLOCK_TO_CONTROL,       // 5C0C
    MAGIC_UNSWAP_LALT_LGUI,            // 5C0D
    MAGIC_UNSWAP_RALT_RGUI,            // 5C0E
    MAGIC_UNNO_GUI,                    // 5C0F
    MAGIC_UNSWAP_GRAVE_ESC,            // 5C10
    MAGIC_UNSWAP_BACKSLASH_BACKSPACE,  // 5C11
    MAGIC_UNHOST_NKRO,                 // 5C12
    MAGIC_UNSWAP_ALT_GUI,              // 5C13
    MAGIC_TOGGLE_NKRO,                 // 5C14
    MAGIC_TOGGLE_ALT_GUI,              // 5C15

    // Grave Escape
    GRAVE_ESC,  // 5C16

    // Auto Shift
    KC_ASUP,   // 5C17
    KC_ASDN,   // 5C18
    KC_ASRP,   // 5C19
    KC_ASTG,   // 5C1A
    KC_ASON,   // 5C1B
    KC_ASOFF,  // 5C1C

    // Audio
    AU_ON,   // 5C1D
    AU_OFF,  // 5C1E
    AU_TOG,  // 5C1F

    // Audio Clicky
    CLICKY_TOGGLE,   // 5C20
    CLICKY_ENABLE,   // 5C21
    CLICKY_DISABLE,  // 5C22
    CLICKY_UP,       // 5C23
    CLICKY_DOWN,     // 5C24
    CLICKY_RESET,    // 5C25

    // Music mode
    MU_ON,   // 5C26
    MU_OFF,  // 5C27
    MU_TOG,  // 5C28
    MU_MOD,  // 5C29
    MUV_IN,  // 5C2A
    MUV_DE,  // 5C2B

    // MIDI
    MI_ON,   // 5C2C
    MI_OFF,  // 5C2D
    MI_TOG,  // 5C2E

    MI_C,   // 5C2F
    MI_Cs,  // 5C30
    MI_Db = MI_Cs,
    MI_D,   // 5C31
    MI_Ds,  // 5C32
    MI_Eb = MI_Ds,
    MI_E,   // 5C33
    MI_F,   // 5C34
    MI_Fs,  // 5C35
    MI_Gb = MI_Fs,
    MI_G,   // 5C36
    MI_Gs,  // 5C37
    MI_Ab = MI_Gs,
    MI_A,   // 5C38
    MI_As,  // 5C39
    MI_Bb = MI_As,
    MI_B,  // 5C3A

    MI_C_1,   // 5C3B
    MI_Cs_1,  // 5C3C
    MI_Db_1 = MI_Cs_1,
    MI_D_1,   // 5C3D
    MI_Ds_1,  // 5C3E
    MI_Eb_1 = MI_Ds_1,
    MI_E_1,   // 5C3F
    MI_F_1,   // 5C40
    MI_Fs_1,  // 5C41
    MI_Gb_1 = MI_Fs_1,
    MI_G_1,   // 5C42
    MI_Gs_1,  // 5C43
    MI_Ab_1 = MI_Gs_1,
    MI_A_1,   // 5C44
    MI_As_1,  // 5C45
    MI_Bb_1 = MI_As_1,
    MI_B_1,  // 5C46

    MI_C_2,   // 5C47
    MI_Cs_2,  // 5C48
    MI_Db_2 = MI_Cs_2,
    MI_D_2,   // 5C49
    MI_Ds_2,  // 5C4A
    MI_Eb_2 = MI_Ds_2,
    MI_E_2,   // 5C4B
    MI_F_2,   // 5C4C
    MI_Fs_2,  // 5C4D
    MI_Gb_2 = MI_Fs_2,
    MI_G_2,   // 5C4E
    MI_Gs_2,  // 5C4F
    MI_Ab_2 = MI_Gs_2,
    MI_A_2,   // 5C50
    MI_As_2,  // 5C51
    MI_Bb_2 = MI_As_2,
    MI_B_2,  // 5C52

    MI_C_3,   // 5C53
    MI_Cs_3,  // 5C54
    MI_Db_3 = MI_Cs_3,
    MI_D_3,   // 5C55
    MI_Ds_3,  // 5C56
    MI_Eb_3 = MI_Ds_3,
    MI_E_3,   // 5C57
    MI_F_3,   // 5C58
    MI_Fs_3,  // 5C59
    MI_Gb_3 = MI_Fs_3,
    MI_G_3,   // 5C5A
    MI_Gs_3,  // 5C5B
    MI_Ab_3 = MI_Gs_3,
    MI_A_3,   // 5C5C
    MI_As_3,  // 5C5D
    MI_Bb_3 = MI_As_3,
    MI_B_3,  // 5C5E

    MI_C_4,   // 5C5F
    MI_Cs_4,  // 5C60
    MI_Db_4 = MI_Cs_4,
    MI_D_4,   // 5C61
    MI_Ds_4,  // 5C62
    MI_Eb_4 = MI_Ds_4,
    MI_E_4,   // 5C63
    MI_F_4,   // 5C64
    MI_Fs_4,  // 5C65
    MI_Gb_4 = MI_Fs_4,
    MI_G_4,   // 5C66
    MI_Gs_4,  // 5C67
    MI_Ab_4 = MI_Gs_4,
    MI_A_4,   // 5C68
    MI_As_4,  // 5C69
    MI_Bb_4 = MI_As_4,
    MI_B_4,  // 5C6A

    MI_C_5,   // 5C6B
    MI_Cs_5,  // 5C6C
    MI_Db_5 = MI_Cs_5,
    MI_D_5,   // 5C6D
    MI_Ds_5,  // 5C6E
    MI_Eb_5 = MI_Ds_5,
    MI_E_5,   // 5C6F
    MI_F_5,   // 5C70
    MI_Fs_5,  // 5C71
    MI_Gb_5 = MI_Fs_5,
    MI_G_5,   // 5C72
    MI_Gs_5,  // 5C73
    MI_Ab_5 = MI_Gs_5,
    MI_A_5,   // 5C74
    MI_As_5,  // 5C75
    MI_Bb_5 = MI_As_5,
    MI_B_5,  // 5C76

    MI_OCT_N2,  // 5C77
    MI_OCT_N1,  // 5C78
    MI_OCT_0,   // 5C79
    MI_OCT_1,   // 5C7A
    MI_OCT_2,   // 5C7B
    MI_OCT_3,   // 5C7C
    MI_OCT_4,   // 5C7D
    MI_OCT_5,   // 5C7E
    MI_OCT_6,   // 5C7F
    MI_OCT_7,   // 5C80
    MI_OCTD,    // 5C81
    MI_OCTU,    // 5C82

    MI_TRNS_N6,  // 5C83
    MI_TRNS_N5,  // 5C84
    MI_TRNS_N4,  // 5C85
    MI_TRNS_N3,  // 5C86
    MI_TRNS_N2,  // 5C87
    MI_TRNS_N1,  // 5C88
    MI_TRNS_0,   // 5C89
    MI_TRNS_1,   // 5C8A
    MI_TRNS_2,   // 5C8B
    MI_TRNS_3,   // 5C8C
    MI_TRNS_4,   // 5C8D
    MI_TRNS_5,   // 5C8E
    MI_TRNS_6,   // 5C8F
    MI_TRNSD,    // 5C90
    MI_TRNSU,    // 5C91

    MI_VEL_0,  // 5C92
#ifdef VIA_ENABLE
    MI_VEL_1 = MI_VEL_0,
#else
    MI_VEL_1,  // 5C93
#endif
    MI_VEL_2,   // 5C94
    MI_VEL_3,   // 5C95
    MI_VEL_4,   // 5C96
    MI_VEL_5,   // 5C97
    MI_VEL_6,   // 5C98
    MI_VEL_7,   // 5C99
    MI_VEL_8,   // 5C9A
    MI_VEL_9,   // 5C9B
    MI_VEL_10,  // 5C9C
    MI_VELD,    // 5C9D
    MI_VELU,    // 5C9E

    MI_CH1,   // 5C9F
    MI_CH2,   // 5CA0
    MI_CH3,   // 5CA1
    MI_CH4,   // 5CA2
    MI_CH5,   // 5CA3
    MI_CH6,   // 5CA4
    MI_CH7,   // 5CA5
    MI_CH8,   // 5CA6
    MI_CH9,   // 5CA7
    MI_CH10,  // 5CA8
    MI_CH11,  // 5CA9
    MI_CH12,  // 5CAA
    MI_CH13,  // 5CAB
    MI_CH14,  // 5CAC
    MI_CH15,  // 5CAD
    MI_CH16,  // 5CAE
    MI_CHD,   // 5CAF
    MI_CHU,   // 5CB0

    MI_ALLOFF,  // 5CB1

    MI_SUS,   // 5CB2
    MI_PORT,  // 5CB3
    MI_SOST,  // 5CB4
    MI_SOFT,  // 5CB5
    MI_LEG,   // 5CB6

    MI_MOD,    // 5CB7
    MI_MODSD,  // 5CB8
    MI_MODSU,  // 5CB9

    MI_BENDD,  // 5CBA
    MI_BENDU,  // 5CBB

    // Backlight
    BL_ON,    // 5CBC
    BL_OFF,   // 5CBD
    BL_DEC,   // 5CBE
    BL_INC,   // 5CBF
    BL_TOGG,  // 5CC0
    BL_STEP,  // 5CC1
    BL_BRTG,  // 5CC2

    // RGB underglow/matrix
    RGB_TOG,            // 5CC3
    RGB_MODE_FORWARD,   // 5CC4
    RGB_MODE_REVERSE,   // 5CC5
    RGB_HUI,            // 5CC6
    RGB_HUD,            // 5CC7
    RGB_SAI,            // 5CC8
    RGB_SAD,            // 5CC9
    RGB_VAI,            // 5CCA
    RGB_VAD,            // 5CCB
    RGB_SPI,            // 5CCC
    RGB_SPD,            // 5CCD
    RGB_MODE_PLAIN,     // 5CCE
    RGB_MODE_BREATHE,   // 5CCF
    RGB_MODE_RAINBOW,   // 5CD0
    RGB_MODE_SWIRL,     // 5CD1
    RGB_MODE_SNAKE,     // 5CD2
    RGB_MODE_KNIGHT,    // 5CD3
    RGB_MODE_XMAS,      // 5CD4
    RGB_MODE_GRADIENT,  // 5CD5
    RGB_MODE_RGBTEST,   // 5CD6

    // Velocikey
    VLK_TOG,  // 5CD7

    // Space Cadet
    KC_LSPO,    // 5CD8
    KC_RSPC,    // 5CD9
    KC_SFTENT,  // 5CDA

    // Thermal Printer
    PRINT_ON,   // 5CDB
    PRINT_OFF,  // 5CDC

    // Bluetooth: output selection
    OUT_AUTO,  // 5CDD
    OUT_USB,   // 5CDE

    // Clear EEPROM
    EEPROM_RESET,  // 5CDF

    // Unicode
    UNICODE_MODE_FORWARD,  // 5CE0
    UNICODE_MODE_REVERSE,  // 5CE1
    UNICODE_MODE_MAC,      // 5CE2
    UNICODE_MODE_LNX,      // 5CE3
    UNICODE_MODE_WIN,      // 5CE4
    UNICODE_MODE_BSD,      // 5CE5
    UNICODE_MODE_WINC,     // 5CE6

    // Haptic
    HPT_ON,    // 5CE7
    HPT_OFF,   // 5CE8
    HPT_TOG,   // 5CE9
    HPT_RST,   // 5CEA
    HPT_FBK,   // 5CEB
    HPT_BUZ,   // 5CEC
    HPT_MODI,  // 5CED
    HPT_MODD,  // 5CEE
    HPT_CONT,  // 5CEF
    HPT_CONI,  // 5CF0
    HPT_COND,  // 5CF1
    HPT_DWLI,  // 5CF2
    HPT_DWLD,  // 5CF3

    // Space Cadet (continued)
    KC_LCPO,  // 5CF4
    KC_RCPC,  // 5CF5
    KC_LAPO,  // 5CF6
    KC_RAPC,  // 5CF7

    // Combos
    CMB_ON,   // 5CF8
    CMB_OFF,  // 5CF9
    CMB_TOG,  // 5CFA

    // Magic (continued)
    MAGIC_SWAP_LCTL_LGUI,    // 5CFB
    MAGIC_SWAP_RCTL_RGUI,    // 5CFC
    MAGIC_UNSWAP_LCTL_LGUI,  // 5CFD
    MAGIC_UNSWAP_RCTL_RGUI,  // 5CFE
    MAGIC_SWAP_CTL_GUI,      // 5CFF
    MAGIC_UNSWAP_CTL_GUI,    // 5D00
    MAGIC_TOGGLE_CTL_GUI,    // 5D01
    MAGIC_EE_HANDS_LEFT,     // 5D02
    MAGIC_EE_HANDS_RIGHT,    // 5D03

    // Dynamic Macros
    DYN_REC_START1,   // 5D04
    DYN_REC_START2,   // 5D05
    DYN_REC_STOP,     // 5D06
    DYN_MACRO_PLAY1,  // 5D07
    DYN_MACRO_PLAY2,  // 5D08

    // Joystick
    JS_BUTTON0,   // 5D09
    JS_BUTTON1,   // 5D0A
    JS_BUTTON2,   // 5D0B
    JS_BUTTON3,   // 5D0C
    JS_BUTTON4,   // 5D0D
    JS_BUTTON5,   // 5D0E
    JS_BUTTON6,   // 5D0F
    JS_BUTTON7,   // 5D10
    JS_BUTTON8,   // 5D11
    JS_BUTTON9,   // 5D12
    JS_BUTTON10,  // 5D13
    JS_BUTTON11,  // 5D14
    JS_BUTTON12,  // 5D15
    JS_BUTTON13,  // 5D16
    JS_BUTTON14,  // 5D17
    JS_BUTTON15,  // 5D18
    JS_BUTTON16,  // 5D19
    JS_BUTTON17,  // 5D1A
    JS_BUTTON18,  // 5D1B
    JS_BUTTON19,  // 5D1C
    JS_BUTTON20,  // 5D1D
    JS_BUTTON21,  // 5D1E
    JS_BUTTON22,  // 5D1F
    JS_BUTTON23,  // 5D20
    JS_BUTTON24,  // 5D21
    JS_BUTTON25,  // 5D22
    JS_BUTTON26,  // 5D23
    JS_BUTTON27,  // 5D24
    JS_BUTTON28,  // 5D25
    JS_BUTTON29,  // 5D26
    JS_BUTTON30,  // 5D27
    JS_BUTTON31,  // 5D28

    // Leader Key
    KC_LEAD,  // 5D29

    // Bluetooth: output selection (continued)
    OUT_BT,  // 5D2A

    // Lock Key
    KC_LOCK,  // 5D2B

    // Terminal
    TERM_ON,   // 5D2C
    TERM_OFF,  // 5D2D

    // Sequencer
    SQ_ON,   // 5D2E
    SQ_OFF,  // 5D2F
    SQ_TOG,  // 5D30

    SQ_TMPD,  // 5D31
    SQ_TMPU,  // 5D32

    SQ_RESD,  // 5D33
    SQ_RESU,  // 5D34

    SQ_SALL,  // 5D35
    SQ_SCLR,  // 5D36

    SEQUENCER_STEP_MIN,  // 5D37
    SEQUENCER_STEP_MAX = SEQUENCER_STEP_MIN + SEQUENCER_STEPS,

    SEQUENCER_RESOLUTION_MIN,
    SEQUENCER_RESOLUTION_MAX = SEQUENCER_RESOLUTION_MIN + SEQUENCER_RESOLUTIONS,

    SEQUENCER_TRACK_MIN,
    SEQUENCER_TRACK_MAX = SEQUENCER_TRACK_MIN + SEQUENCER_TRACKS,

#define SQ_S(n) (n < SEQUENCER_STEPS ? SEQUENCER_STEP_MIN + n : KC_NO)
#define SQ_R(n) (n < SEQUENCER_RESOLUTIONS ? SEQUENCER_RESOLUTION_MIN + n : KC_NO)
#define SQ_T(n) (n < SEQUENCER_TRACKS ? SEQUENCER_TRACK_MIN + n : KC_NO)

    // One Shot
    ONESHOT_ENABLE,
    ONESHOT_DISABLE,
    ONESHOT_TOGGLE,

    // RGB underglow/matrix (continued)
    RGB_MODE_TWINKLE,

    // Start of custom keycode range for keyboards and keymaps - always leave at the end
    SAFE_RANGE
};

// Keycode modifiers & aliases
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
#define LSG(kc) (QK_LSFT | QK_LGUI | (kc))
#define SGUI(kc) LSG(kc)
#define SCMD(kc) LSG(kc)
#define SWIN(kc) LSG(kc)
#define LAG(kc) (QK_LALT | QK_LGUI | (kc))
#define RSG(kc) (QK_RSFT | QK_RGUI | (kc))
#define RAG(kc) (QK_RALT | QK_RGUI | (kc))
#define LCA(kc) (QK_LCTL | QK_LALT | (kc))
#define LSA(kc) (QK_LSFT | QK_LALT | (kc))
#define RSA(kc) (QK_RSFT | QK_RALT | (kc))
#define RCS(kc) (QK_RCTL | QK_RSFT | (kc))
#define SAGR(kc) RSA(kc)

#define MOD_HYPR 0xF
#define MOD_MEH 0x7

// US ANSI shifted keycode aliases
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

// Modified keycode aliases
#define C(kc) LCTL(kc)
#define S(kc) LSFT(kc)
#define A(kc) LALT(kc)
#define G(kc) LGUI(kc)

// Deprecated - do not use
#define F(kc) (QK_FUNCTION | (kc))
#define M(kc) (QK_MACRO | (kc))
#define MACROTAP(kc) (QK_MACRO | (FUNC_TAP << 8) | (kc))
#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

#define KC_GESC GRAVE_ESC

#define EEP_RST EEPROM_RESET

// Audio Clicky aliases
#define CK_TOGG CLICKY_TOGGLE
#define CK_RST CLICKY_RESET
#define CK_UP CLICKY_UP
#define CK_DOWN CLICKY_DOWN
#define CK_ON CLICKY_ENABLE
#define CK_OFF CLICKY_DISABLE
// Fauxclicky (deprecated) redirects to Audio Clicky
#define FC_ON CLICKY_ENABLE
#define FC_OFF CLICKY_DISABLE
#define FC_TOGG CLICKY_TOGGLE

// RGB aliases
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
#define RGB_M_TW RGB_MODE_TWINKLE

// Magic aliases
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

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))

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

#define C_S_T(kc) MT(MOD_LCTL | MOD_LSFT, kc)  // Left Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT, kc)  // Meh is a less hyper version of the Hyper key -- doesn't include GUI, so just Left Control + Shift + Alt
#define LCAG_T(kc) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, kc)  // Left Control + Alt + GUI
#define RCAG_T(kc) MT(MOD_RCTL | MOD_RALT | MOD_RGUI, kc)  // Right Control + Alt + GUI
#define HYPR_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, kc)  // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/
#define LSG_T(kc) MT(MOD_LSFT | MOD_LGUI, kc)  // Left Shift + GUI
#define SGUI_T(kc) LSG_T(kc)
#define SCMD_T(kc) LSG_T(kc)
#define SWIN_T(kc) LSG_T(kc)
#define LAG_T(kc) MT(MOD_LALT | MOD_LGUI, kc)  // Left Alt + GUI
#define RSG_T(kc) MT(MOD_RSFT | MOD_RGUI, kc)  // Right Shift + GUI
#define RAG_T(kc) MT(MOD_RALT | MOD_RGUI, kc)  // Right Alt + GUI
#define LCA_T(kc) MT(MOD_LCTL | MOD_LALT, kc)  // Left Control + Alt
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)  // Left Shift + Alt
#define RSA_T(kc) MT(MOD_RSFT | MOD_RALT, kc)  // Right Shift + Alt
#define RCS_T(kc) MT(MOD_RCTL | MOD_RSFT, kc)  // Right Control + Shift
#define SAGR_T(kc) RSA_T(kc)

#define ALL_T(kc) HYPR_T(kc)

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH MEH(KC_NO)

// Unicode aliases
// UNICODE_ENABLE - Allows Unicode input up to 0x7FFF
#define UC(c) (QK_UNICODE | (c))
// UNICODEMAP_ENABLE - Allows Unicode input up to 0x10FFFF, requires unicode_map
#define X(i) (QK_UNICODEMAP | (i))
#define XP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7))  // 127 max i and j

#define UC_MOD UNICODE_MODE_FORWARD
#define UC_RMOD UNICODE_MODE_REVERSE

#define UC_M_MA UNICODE_MODE_MAC
#define UNICODE_MODE_OSX UNICODE_MODE_MAC  // Deprecated alias
#define UC_M_OS UNICODE_MODE_MAC  // Deprecated alias
#define UC_M_LN UNICODE_MODE_LNX
#define UC_M_WI UNICODE_MODE_WIN
#define UC_M_BS UNICODE_MODE_BSD
#define UC_M_WC UNICODE_MODE_WINC

// Swap Hands
#define SH_T(kc) (QK_SWAP_HANDS | (kc))
#define SH_TG (QK_SWAP_HANDS | OP_SH_TOGGLE)
#define SH_TT (QK_SWAP_HANDS | OP_SH_TAP_TOGGLE)
#define SH_OS (QK_SWAP_HANDS | OP_SH_ONESHOT)
#define SH_MON (QK_SWAP_HANDS | OP_SH_ON_OFF)
#define SH_MOFF (QK_SWAP_HANDS | OP_SH_OFF_ON)
#define SH_ON (QK_SWAP_HANDS | OP_SH_ON)
#define SH_OFF (QK_SWAP_HANDS | OP_SH_OFF)

// MIDI aliases
#define MIDI_TONE_MIN MI_C
#define MIDI_TONE_MAX MI_B_5
#define MIDI_OCTAVE_MIN MI_OCT_N2
#define MIDI_OCTAVE_MAX MI_OCT_7
#define MIDI_TRANSPOSE_MIN MI_TRNS_N6
#define MIDI_TRANSPOSE_MAX MI_TRNS_6
#define MIDI_VELOCITY_MIN MI_VEL_0
#define MIDI_VELOCITY_MAX MI_VEL_10
#define MIDI_CHANNEL_MIN MI_CH1
#define MIDI_CHANNEL_MAX MI_CH16

// Dynamic Macros aliases
#define DM_REC1 DYN_REC_START1
#define DM_REC2 DYN_REC_START2
#define DM_RSTP DYN_REC_STOP
#define DM_PLY1 DYN_MACRO_PLAY1
#define DM_PLY2 DYN_MACRO_PLAY2

// Joystick aliases
#define JS_BUTTON_MIN JS_BUTTON0
#define JS_BUTTON_MAX JS_BUTTON31

// One Shot aliases
#define OS_TOGG ONESHOT_TOGGLE
#define OS_ON ONESHOT_ENABLE
#define OS_OFF ONESHOT_DISABLE
