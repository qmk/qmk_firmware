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
#define _______ KC_TRANSPARENT
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
    QK_STENO_COMB           = 0x5A32,
    QK_STENO_COMB_MAX       = 0x5A3C,
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
    QK_BOOTLOADER = 0x5C00,
    QK_DEBUG_TOGGLE, // 5C01

    // Magic
    MAGIC_SWAP_CONTROL_CAPSLOCK,      // 5C02
    MAGIC_CAPSLOCK_TO_CONTROL,        // 5C03
    MAGIC_SWAP_LALT_LGUI,             // 5C04
    MAGIC_SWAP_RALT_RGUI,             // 5C05
    MAGIC_NO_GUI,                     // 5C06
    MAGIC_SWAP_GRAVE_ESC,             // 5C07
    MAGIC_SWAP_BACKSLASH_BACKSPACE,   // 5C08
    MAGIC_HOST_NKRO,                  // 5C09
    MAGIC_SWAP_ALT_GUI,               // 5C0A
    MAGIC_UNSWAP_CONTROL_CAPSLOCK,    // 5C0B
    MAGIC_UNCAPSLOCK_TO_CONTROL,      // 5C0C
    MAGIC_UNSWAP_LALT_LGUI,           // 5C0D
    MAGIC_UNSWAP_RALT_RGUI,           // 5C0E
    MAGIC_UNNO_GUI,                   // 5C0F
    MAGIC_UNSWAP_GRAVE_ESC,           // 5C10
    MAGIC_UNSWAP_BACKSLASH_BACKSPACE, // 5C11
    MAGIC_UNHOST_NKRO,                // 5C12
    MAGIC_UNSWAP_ALT_GUI,             // 5C13
    MAGIC_TOGGLE_NKRO,                // 5C14
    MAGIC_TOGGLE_ALT_GUI,             // 5C15

    // Grave Escape
    QK_GRAVE_ESCAPE, // 5C16

    // Auto Shift
    KC_ASUP,  // 5C17
    KC_ASDN,  // 5C18
    KC_ASRP,  // 5C19
    KC_ASTG,  // 5C1A
    KC_ASON,  // 5C1B
    KC_ASOFF, // 5C1C

    // Audio
    AU_ON,  // 5C1D
    AU_OFF, // 5C1E
    AU_TOG, // 5C1F

    // Audio Clicky
    CLICKY_TOGGLE,  // 5C20
    CLICKY_ENABLE,  // 5C21
    CLICKY_DISABLE, // 5C22
    CLICKY_UP,      // 5C23
    CLICKY_DOWN,    // 5C24
    CLICKY_RESET,   // 5C25

    // Music mode
    MU_ON,  // 5C26
    MU_OFF, // 5C27
    MU_TOG, // 5C28
    MU_MOD, // 5C29
    MUV_IN, // 5C2A
    MUV_DE, // 5C2B

    // MIDI
    MI_ON,  // 5C2C
    MI_OFF, // 5C2D
    MI_TOG, // 5C2E

    MI_C,  // 5C2F
    MI_Cs, // 5C30
    MI_Db = MI_Cs,
    MI_D,  // 5C31
    MI_Ds, // 5C32
    MI_Eb = MI_Ds,
    MI_E,  // 5C33
    MI_F,  // 5C34
    MI_Fs, // 5C35
    MI_Gb = MI_Fs,
    MI_G,  // 5C36
    MI_Gs, // 5C37
    MI_Ab = MI_Gs,
    MI_A,  // 5C38
    MI_As, // 5C39
    MI_Bb = MI_As,
    MI_B, // 5C3A

    MI_C_1,  // 5C3B
    MI_Cs_1, // 5C3C
    MI_Db_1 = MI_Cs_1,
    MI_D_1,  // 5C3D
    MI_Ds_1, // 5C3E
    MI_Eb_1 = MI_Ds_1,
    MI_E_1,  // 5C3F
    MI_F_1,  // 5C40
    MI_Fs_1, // 5C41
    MI_Gb_1 = MI_Fs_1,
    MI_G_1,  // 5C42
    MI_Gs_1, // 5C43
    MI_Ab_1 = MI_Gs_1,
    MI_A_1,  // 5C44
    MI_As_1, // 5C45
    MI_Bb_1 = MI_As_1,
    MI_B_1, // 5C46

    MI_C_2,  // 5C47
    MI_Cs_2, // 5C48
    MI_Db_2 = MI_Cs_2,
    MI_D_2,  // 5C49
    MI_Ds_2, // 5C4A
    MI_Eb_2 = MI_Ds_2,
    MI_E_2,  // 5C4B
    MI_F_2,  // 5C4C
    MI_Fs_2, // 5C4D
    MI_Gb_2 = MI_Fs_2,
    MI_G_2,  // 5C4E
    MI_Gs_2, // 5C4F
    MI_Ab_2 = MI_Gs_2,
    MI_A_2,  // 5C50
    MI_As_2, // 5C51
    MI_Bb_2 = MI_As_2,
    MI_B_2, // 5C52

    MI_C_3,  // 5C53
    MI_Cs_3, // 5C54
    MI_Db_3 = MI_Cs_3,
    MI_D_3,  // 5C55
    MI_Ds_3, // 5C56
    MI_Eb_3 = MI_Ds_3,
    MI_E_3,  // 5C57
    MI_F_3,  // 5C58
    MI_Fs_3, // 5C59
    MI_Gb_3 = MI_Fs_3,
    MI_G_3,  // 5C5A
    MI_Gs_3, // 5C5B
    MI_Ab_3 = MI_Gs_3,
    MI_A_3,  // 5C5C
    MI_As_3, // 5C5D
    MI_Bb_3 = MI_As_3,
    MI_B_3, // 5C5E

    MI_C_4,  // 5C5F
    MI_Cs_4, // 5C60
    MI_Db_4 = MI_Cs_4,
    MI_D_4,  // 5C61
    MI_Ds_4, // 5C62
    MI_Eb_4 = MI_Ds_4,
    MI_E_4,  // 5C63
    MI_F_4,  // 5C64
    MI_Fs_4, // 5C65
    MI_Gb_4 = MI_Fs_4,
    MI_G_4,  // 5C66
    MI_Gs_4, // 5C67
    MI_Ab_4 = MI_Gs_4,
    MI_A_4,  // 5C68
    MI_As_4, // 5C69
    MI_Bb_4 = MI_As_4,
    MI_B_4, // 5C6A

    MI_C_5,  // 5C6B
    MI_Cs_5, // 5C6C
    MI_Db_5 = MI_Cs_5,
    MI_D_5,  // 5C6D
    MI_Ds_5, // 5C6E
    MI_Eb_5 = MI_Ds_5,
    MI_E_5,  // 5C6F
    MI_F_5,  // 5C70
    MI_Fs_5, // 5C71
    MI_Gb_5 = MI_Fs_5,
    MI_G_5,  // 5C72
    MI_Gs_5, // 5C73
    MI_Ab_5 = MI_Gs_5,
    MI_A_5,  // 5C74
    MI_As_5, // 5C75
    MI_Bb_5 = MI_As_5,
    MI_B_5, // 5C76

    MI_OCT_N2, // 5C77
    MI_OCT_N1, // 5C78
    MI_OCT_0,  // 5C79
    MI_OCT_1,  // 5C7A
    MI_OCT_2,  // 5C7B
    MI_OCT_3,  // 5C7C
    MI_OCT_4,  // 5C7D
    MI_OCT_5,  // 5C7E
    MI_OCT_6,  // 5C7F
    MI_OCT_7,  // 5C80
    MI_OCTD,   // 5C81
    MI_OCTU,   // 5C82

    MI_TRNS_N6, // 5C83
    MI_TRNS_N5, // 5C84
    MI_TRNS_N4, // 5C85
    MI_TRNS_N3, // 5C86
    MI_TRNS_N2, // 5C87
    MI_TRNS_N1, // 5C88
    MI_TRNS_0,  // 5C89
    MI_TRNS_1,  // 5C8A
    MI_TRNS_2,  // 5C8B
    MI_TRNS_3,  // 5C8C
    MI_TRNS_4,  // 5C8D
    MI_TRNS_5,  // 5C8E
    MI_TRNS_6,  // 5C8F
    MI_TRNSD,   // 5C90
    MI_TRNSU,   // 5C91

    MI_VEL_0, // 5C92
#ifdef VIA_ENABLE
    MI_VEL_1 = MI_VEL_0,
#else
    MI_VEL_1, // 5C93
#endif
    MI_VEL_2,  // 5C94
    MI_VEL_3,  // 5C95
    MI_VEL_4,  // 5C96
    MI_VEL_5,  // 5C97
    MI_VEL_6,  // 5C98
    MI_VEL_7,  // 5C99
    MI_VEL_8,  // 5C9A
    MI_VEL_9,  // 5C9B
    MI_VEL_10, // 5C9C
    MI_VELD,   // 5C9D
    MI_VELU,   // 5C9E

    MI_CH1,  // 5C9F
    MI_CH2,  // 5CA0
    MI_CH3,  // 5CA1
    MI_CH4,  // 5CA2
    MI_CH5,  // 5CA3
    MI_CH6,  // 5CA4
    MI_CH7,  // 5CA5
    MI_CH8,  // 5CA6
    MI_CH9,  // 5CA7
    MI_CH10, // 5CA8
    MI_CH11, // 5CA9
    MI_CH12, // 5CAA
    MI_CH13, // 5CAB
    MI_CH14, // 5CAC
    MI_CH15, // 5CAD
    MI_CH16, // 5CAE
    MI_CHD,  // 5CAF
    MI_CHU,  // 5CB0

    MI_ALLOFF, // 5CB1

    MI_SUS,  // 5CB2
    MI_PORT, // 5CB3
    MI_SOST, // 5CB4
    MI_SOFT, // 5CB5
    MI_LEG,  // 5CB6

    MI_MOD,   // 5CB7
    MI_MODSD, // 5CB8
    MI_MODSU, // 5CB9

    MI_BENDD, // 5CBA
    MI_BENDU, // 5CBB

    // Backlight
    BL_ON,   // 5CBC
    BL_OFF,  // 5CBD
    BL_DEC,  // 5CBE
    BL_INC,  // 5CBF
    BL_TOGG, // 5CC0
    BL_STEP, // 5CC1
    BL_BRTG, // 5CC2

    // RGB underglow/matrix
    RGB_TOG,           // 5CC3
    RGB_MODE_FORWARD,  // 5CC4
    RGB_MODE_REVERSE,  // 5CC5
    RGB_HUI,           // 5CC6
    RGB_HUD,           // 5CC7
    RGB_SAI,           // 5CC8
    RGB_SAD,           // 5CC9
    RGB_VAI,           // 5CCA
    RGB_VAD,           // 5CCB
    RGB_SPI,           // 5CCC
    RGB_SPD,           // 5CCD
    RGB_MODE_PLAIN,    // 5CCE
    RGB_MODE_BREATHE,  // 5CCF
    RGB_MODE_RAINBOW,  // 5CD0
    RGB_MODE_SWIRL,    // 5CD1
    RGB_MODE_SNAKE,    // 5CD2
    RGB_MODE_KNIGHT,   // 5CD3
    RGB_MODE_XMAS,     // 5CD4
    RGB_MODE_GRADIENT, // 5CD5
    RGB_MODE_RGBTEST,  // 5CD6

    // Velocikey
    QK_VELOCIKEY_TOGGLE, // 5CD7

    // Space Cadet
    QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN,   // 5CD8
    QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE, // 5CD9
    QK_SPACE_CADET_RIGHT_SHIFT_ENTER,             // 5CDA

    // Thermal Printer
    PRINT_ON,  // 5CDB
    PRINT_OFF, // 5CDC

    // Bluetooth: output selection
    OUT_AUTO, // 5CDD
    OUT_USB,  // 5CDE

    // Clear EEPROM
    QK_CLEAR_EEPROM, // 5CDF

    // Unicode
    UNICODE_MODE_FORWARD, // 5CE0
    UNICODE_MODE_REVERSE, // 5CE1
    UNICODE_MODE_MAC,     // 5CE2
    UNICODE_MODE_LNX,     // 5CE3
    UNICODE_MODE_WIN,     // 5CE4
    UNICODE_MODE_BSD,     // 5CE5
    UNICODE_MODE_WINC,    // 5CE6

    // Haptic
    HPT_ON,   // 5CE7
    HPT_OFF,  // 5CE8
    HPT_TOG,  // 5CE9
    HPT_RST,  // 5CEA
    HPT_FBK,  // 5CEB
    HPT_BUZ,  // 5CEC
    HPT_MODI, // 5CED
    HPT_MODD, // 5CEE
    HPT_CONT, // 5CEF
    HPT_CONI, // 5CF0
    HPT_COND, // 5CF1
    HPT_DWLI, // 5CF2
    HPT_DWLD, // 5CF3

    // Space Cadet (continued)
    QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN,   // 5CF4
    QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE, // 5CF5
    QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN,    // 5CF6
    QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE,  // 5CF7

    // Combos
    QK_COMBO_ON,     // 5CF8
    QK_COMBO_OFF,    // 5CF9
    QK_COMBO_TOGGLE, // 5CFA

    // Magic (continued)
    MAGIC_SWAP_LCTL_LGUI,   // 5CFB
    MAGIC_SWAP_RCTL_RGUI,   // 5CFC
    MAGIC_UNSWAP_LCTL_LGUI, // 5CFD
    MAGIC_UNSWAP_RCTL_RGUI, // 5CFE
    MAGIC_SWAP_CTL_GUI,     // 5CFF
    MAGIC_UNSWAP_CTL_GUI,   // 5D00
    MAGIC_TOGGLE_CTL_GUI,   // 5D01
    MAGIC_EE_HANDS_LEFT,    // 5D02
    MAGIC_EE_HANDS_RIGHT,   // 5D03

    // Dynamic Macros
    DYN_REC_START1,  // 5D04
    DYN_REC_START2,  // 5D05
    DYN_REC_STOP,    // 5D06
    DYN_MACRO_PLAY1, // 5D07
    DYN_MACRO_PLAY2, // 5D08

    // Joystick
    QK_JOYSTICK_BUTTON_0,  // 5D09
    QK_JOYSTICK_BUTTON_1,  // 5D0A
    QK_JOYSTICK_BUTTON_2,  // 5D0B
    QK_JOYSTICK_BUTTON_3,  // 5D0C
    QK_JOYSTICK_BUTTON_4,  // 5D0D
    QK_JOYSTICK_BUTTON_5,  // 5D0E
    QK_JOYSTICK_BUTTON_6,  // 5D0F
    QK_JOYSTICK_BUTTON_7,  // 5D10
    QK_JOYSTICK_BUTTON_8,  // 5D11
    QK_JOYSTICK_BUTTON_9,  // 5D12
    QK_JOYSTICK_BUTTON_10, // 5D13
    QK_JOYSTICK_BUTTON_11, // 5D14
    QK_JOYSTICK_BUTTON_12, // 5D15
    QK_JOYSTICK_BUTTON_13, // 5D16
    QK_JOYSTICK_BUTTON_14, // 5D17
    QK_JOYSTICK_BUTTON_15, // 5D18
    QK_JOYSTICK_BUTTON_16, // 5D19
    QK_JOYSTICK_BUTTON_17, // 5D1A
    QK_JOYSTICK_BUTTON_18, // 5D1B
    QK_JOYSTICK_BUTTON_19, // 5D1C
    QK_JOYSTICK_BUTTON_20, // 5D1D
    QK_JOYSTICK_BUTTON_21, // 5D1E
    QK_JOYSTICK_BUTTON_22, // 5D1F
    QK_JOYSTICK_BUTTON_23, // 5D20
    QK_JOYSTICK_BUTTON_24, // 5D21
    QK_JOYSTICK_BUTTON_25, // 5D22
    QK_JOYSTICK_BUTTON_26, // 5D23
    QK_JOYSTICK_BUTTON_27, // 5D24
    QK_JOYSTICK_BUTTON_28, // 5D25
    QK_JOYSTICK_BUTTON_29, // 5D26
    QK_JOYSTICK_BUTTON_30, // 5D27
    QK_JOYSTICK_BUTTON_31, // 5D28

    // Leader Key
    QK_LEADER, // 5D29

    // Bluetooth: output selection (continued)
    OUT_BT, // 5D2A

    // Lock Key
    QK_LOCK, // 5D2B

    // Unused slots
    UNUSED_000, // 5D2C
    UNUSED_001, // 5D2D

    // Sequencer
    SQ_ON,  // 5D2E
    SQ_OFF, // 5D2F
    SQ_TOG, // 5D30

    SQ_TMPD, // 5D31
    SQ_TMPU, // 5D32

    SQ_RESD, // 5D33
    SQ_RESU, // 5D34

    SQ_SALL, // 5D35
    SQ_SCLR, // 5D36

    SEQUENCER_STEP_MIN, // 5D37
    SEQUENCER_STEP_MAX = SEQUENCER_STEP_MIN + SEQUENCER_STEPS,

    SEQUENCER_RESOLUTION_MIN,
    SEQUENCER_RESOLUTION_MAX = SEQUENCER_RESOLUTION_MIN + SEQUENCER_RESOLUTIONS,

    SEQUENCER_TRACK_MIN,
    SEQUENCER_TRACK_MAX = SEQUENCER_TRACK_MIN + SEQUENCER_TRACKS,

#define SQ_S(n) (n < SEQUENCER_STEPS ? SEQUENCER_STEP_MIN + n : KC_NO)
#define SQ_R(n) (n < SEQUENCER_RESOLUTIONS ? SEQUENCER_RESOLUTION_MIN + n : KC_NO)
#define SQ_T(n) (n < SEQUENCER_TRACKS ? SEQUENCER_TRACK_MIN + n : KC_NO)

    // One Shot
    QK_ONE_SHOT_ON,
    QK_ONE_SHOT_OFF,
    QK_ONE_SHOT_TOGGLE,

    // RGB underglow/matrix (continued)
    RGB_MODE_TWINKLE,

    // Key Overrides
    QK_KEY_OVERRIDE_TOGGLE,
    QK_KEY_OVERRIDE_ON,
    QK_KEY_OVERRIDE_OFF,

    // Additional magic key
    MAGIC_TOGGLE_GUI,

    // Adjust tapping term on the fly
    DT_PRNT,
    DT_UP,
    DT_DOWN,

    // Programmable Button
    QK_PROGRAMMABLE_BUTTON_1,
    QK_PROGRAMMABLE_BUTTON_2,
    QK_PROGRAMMABLE_BUTTON_3,
    QK_PROGRAMMABLE_BUTTON_4,
    QK_PROGRAMMABLE_BUTTON_5,
    QK_PROGRAMMABLE_BUTTON_6,
    QK_PROGRAMMABLE_BUTTON_7,
    QK_PROGRAMMABLE_BUTTON_8,
    QK_PROGRAMMABLE_BUTTON_9,
    QK_PROGRAMMABLE_BUTTON_10,
    QK_PROGRAMMABLE_BUTTON_11,
    QK_PROGRAMMABLE_BUTTON_12,
    QK_PROGRAMMABLE_BUTTON_13,
    QK_PROGRAMMABLE_BUTTON_14,
    QK_PROGRAMMABLE_BUTTON_15,
    QK_PROGRAMMABLE_BUTTON_16,
    QK_PROGRAMMABLE_BUTTON_17,
    QK_PROGRAMMABLE_BUTTON_18,
    QK_PROGRAMMABLE_BUTTON_19,
    QK_PROGRAMMABLE_BUTTON_20,
    QK_PROGRAMMABLE_BUTTON_21,
    QK_PROGRAMMABLE_BUTTON_22,
    QK_PROGRAMMABLE_BUTTON_23,
    QK_PROGRAMMABLE_BUTTON_24,
    QK_PROGRAMMABLE_BUTTON_25,
    QK_PROGRAMMABLE_BUTTON_26,
    QK_PROGRAMMABLE_BUTTON_27,
    QK_PROGRAMMABLE_BUTTON_28,
    QK_PROGRAMMABLE_BUTTON_29,
    QK_PROGRAMMABLE_BUTTON_30,
    QK_PROGRAMMABLE_BUTTON_31,
    QK_PROGRAMMABLE_BUTTON_32,

    // Dedicated macro keys for Configurator and VIA
    MACRO_0,
    MACRO_1,
    MACRO_2,
    MACRO_3,
    MACRO_4,
    MACRO_5,
    MACRO_6,
    MACRO_7,
    MACRO_8,
    MACRO_9,
    MACRO_10,
    MACRO_11,
    MACRO_12,
    MACRO_13,
    MACRO_14,
    MACRO_15,
    MACRO_16,
    MACRO_17,
    MACRO_18,
    MACRO_19,
    MACRO_20,
    MACRO_21,
    MACRO_22,
    MACRO_23,
    MACRO_24,
    MACRO_25,
    MACRO_26,
    MACRO_27,
    MACRO_28,
    MACRO_29,
    MACRO_30,
    MACRO_31,

    MAGIC_TOGGLE_CONTROL_CAPSLOCK,

    QK_MAKE,
    QK_REBOOT,

    QK_SECURE_LOCK,
    QK_SECURE_UNLOCK,
    QK_SECURE_TOGGLE,
    QK_SECURE_REQUEST,

    QK_CAPS_WORD_TOGGLE,

    MAGIC_SWAP_ESCAPE_CAPSLOCK,
    MAGIC_UNSWAP_ESCAPE_CAPSLOCK,
    MAGIC_TOGGLE_ESCAPE_CAPSLOCK,

    UNICODE_MODE_EMACS,

    QK_AUTOCORRECT_ON,
    QK_AUTOCORRECT_OFF,
    QK_AUTOCORRECT_TOGGLE,

    MAGIC_TOGGLE_BACKSLASH_BACKSPACE,

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
#include "keymap_us.h"

// Modified keycode aliases
#define C(kc) LCTL(kc)
#define S(kc) LSFT(kc)
#define A(kc) LALT(kc)
#define G(kc) LGUI(kc)

#define QK_GESC QK_GRAVE_ESCAPE

#define QK_BOOT QK_BOOTLOADER
#define DB_TOGG QK_DEBUG_TOGGLE
#define EE_CLR QK_CLEAR_EEPROM
#define QK_RBT QK_REBOOT

// Audio Clicky aliases
#define CK_TOGG CLICKY_TOGGLE
#define CK_RST CLICKY_RESET
#define CK_UP CLICKY_UP
#define CK_DOWN CLICKY_DOWN
#define CK_ON CLICKY_ENABLE
#define CK_OFF CLICKY_DISABLE

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
#define CL_TOGG MAGIC_TOGGLE_CONTROL_CAPSLOCK

#define EC_SWAP MAGIC_SWAP_ESCAPE_CAPSLOCK
#define EC_NORM MAGIC_UNSWAP_ESCAPE_CAPSLOCK
#define EC_TOGG MAGIC_TOGGLE_ESCAPE_CAPSLOCK

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
#define GUI_TOG MAGIC_TOGGLE_GUI

#define GE_SWAP MAGIC_SWAP_GRAVE_ESC
#define GE_NORM MAGIC_UNSWAP_GRAVE_ESC

#define BS_SWAP MAGIC_SWAP_BACKSLASH_BACKSPACE
#define BS_NORM MAGIC_UNSWAP_BACKSLASH_BACKSPACE
#define BS_TOGG MAGIC_TOGGLE_BACKSLASH_BACKSPACE

#define NK_ON MAGIC_HOST_NKRO
#define NK_OFF MAGIC_UNHOST_NKRO
#define NK_TOGG MAGIC_TOGGLE_NKRO

#define EH_LEFT MAGIC_EE_HANDS_LEFT
#define EH_RGHT MAGIC_EE_HANDS_RIGHT

#define AC_ON QK_AUTOCORRECT_ON
#define AC_OFF QK_AUTOCORRECT_OFF
#define AC_TOGG QK_AUTOCORRECT_TOGGLE

// Velocikey
#define VK_TOGG QK_VELOCIKEY_TOGGLE

// GOTO layer - 256 layer max
#define TO(layer) (QK_TO | ((layer)&0xFF))

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

#define C_S_T(kc) MT(MOD_LCTL | MOD_LSFT, kc)                        // Left Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT, kc)             // Meh is a less hyper version of the Hyper key -- doesn't include GUI, so just Left Control + Shift + Alt
#define LCAG_T(kc) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, kc)            // Left Control + Alt + GUI
#define RCAG_T(kc) MT(MOD_RCTL | MOD_RALT | MOD_RGUI, kc)            // Right Control + Alt + GUI
#define HYPR_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, kc) // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/
#define LSG_T(kc) MT(MOD_LSFT | MOD_LGUI, kc)                        // Left Shift + GUI
#define SGUI_T(kc) LSG_T(kc)
#define SCMD_T(kc) LSG_T(kc)
#define SWIN_T(kc) LSG_T(kc)
#define LAG_T(kc) MT(MOD_LALT | MOD_LGUI, kc) // Left Alt + GUI
#define RSG_T(kc) MT(MOD_RSFT | MOD_RGUI, kc) // Right Shift + GUI
#define RAG_T(kc) MT(MOD_RALT | MOD_RGUI, kc) // Right Alt + GUI
#define LCA_T(kc) MT(MOD_LCTL | MOD_LALT, kc) // Left Control + Alt
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc) // Left Shift + Alt
#define RSA_T(kc) MT(MOD_RSFT | MOD_RALT, kc) // Right Shift + Alt
#define RCS_T(kc) MT(MOD_RCTL | MOD_RSFT, kc) // Right Control + Shift
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
#define XP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7)) // 127 max i and j

#define UC_MOD UNICODE_MODE_FORWARD
#define UC_RMOD UNICODE_MODE_REVERSE

#define UC_M_MA UNICODE_MODE_MAC
#define UC_M_LN UNICODE_MODE_LNX
#define UC_M_WI UNICODE_MODE_WIN
#define UC_M_BS UNICODE_MODE_BSD
#define UC_M_WC UNICODE_MODE_WINC
#define UC_M_EM UNICODE_MODE_EMACS

// Leader key
#define QK_LEAD QK_LEADER

// Caps Word
#define CW_TOGG QK_CAPS_WORD_TOGGLE

// Key Overrides
#define KO_TOGG QK_KEY_OVERRIDE_TOGGLE
#define KO_ON QK_KEY_OVERRIDE_ON
#define KO_OFF QK_KEY_OVERRIDE_OFF

// Secure
#define SE_LOCK QK_SECURE_LOCK
#define SE_UNLK QK_SECURE_UNLOCK
#define SE_TOGG QK_SECURE_TOGGLE
#define SE_REQ QK_SECURE_REQUEST

// Space Cadet
#define SC_LSPO QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN
#define SC_RSPC QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE
#define SC_LCPO QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN
#define SC_RCPC QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE
#define SC_LAPO QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN
#define SC_RAPC QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE
#define SC_SENT QK_SPACE_CADET_RIGHT_SHIFT_ENTER

// Combos
#define CM_ON QK_COMBO_ON
#define CM_OFF QK_COMBO_OFF
#define CM_TOGG QK_COMBO_TOGGLE

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
#define JS_0 QK_JOYSTICK_BUTTON_0
#define JS_1 QK_JOYSTICK_BUTTON_1
#define JS_2 QK_JOYSTICK_BUTTON_2
#define JS_3 QK_JOYSTICK_BUTTON_3
#define JS_4 QK_JOYSTICK_BUTTON_4
#define JS_5 QK_JOYSTICK_BUTTON_5
#define JS_6 QK_JOYSTICK_BUTTON_6
#define JS_7 QK_JOYSTICK_BUTTON_7
#define JS_8 QK_JOYSTICK_BUTTON_8
#define JS_9 QK_JOYSTICK_BUTTON_9
#define JS_10 QK_JOYSTICK_BUTTON_10
#define JS_11 QK_JOYSTICK_BUTTON_11
#define JS_12 QK_JOYSTICK_BUTTON_12
#define JS_13 QK_JOYSTICK_BUTTON_13
#define JS_14 QK_JOYSTICK_BUTTON_14
#define JS_15 QK_JOYSTICK_BUTTON_15
#define JS_16 QK_JOYSTICK_BUTTON_16
#define JS_17 QK_JOYSTICK_BUTTON_17
#define JS_18 QK_JOYSTICK_BUTTON_18
#define JS_19 QK_JOYSTICK_BUTTON_19
#define JS_20 QK_JOYSTICK_BUTTON_20
#define JS_21 QK_JOYSTICK_BUTTON_21
#define JS_22 QK_JOYSTICK_BUTTON_22
#define JS_23 QK_JOYSTICK_BUTTON_23
#define JS_24 QK_JOYSTICK_BUTTON_24
#define JS_25 QK_JOYSTICK_BUTTON_25
#define JS_26 QK_JOYSTICK_BUTTON_26
#define JS_27 QK_JOYSTICK_BUTTON_27
#define JS_28 QK_JOYSTICK_BUTTON_28
#define JS_29 QK_JOYSTICK_BUTTON_29
#define JS_30 QK_JOYSTICK_BUTTON_30
#define JS_31 QK_JOYSTICK_BUTTON_31
#define QK_JOYSTICK_BUTTON_MIN QK_JOYSTICK_BUTTON_0
#define QK_JOYSTICK_BUTTON_MAX QK_JOYSTICK_BUTTON_31

// One Shot aliases
#define OS_TOGG QK_ONE_SHOT_TOGGLE
#define OS_ON QK_ONE_SHOT_ON
#define OS_OFF QK_ONE_SHOT_OFF

// Programmable Button aliases
#define PB_1 QK_PROGRAMMABLE_BUTTON_1
#define PB_2 QK_PROGRAMMABLE_BUTTON_2
#define PB_3 QK_PROGRAMMABLE_BUTTON_3
#define PB_4 QK_PROGRAMMABLE_BUTTON_4
#define PB_5 QK_PROGRAMMABLE_BUTTON_5
#define PB_6 QK_PROGRAMMABLE_BUTTON_6
#define PB_7 QK_PROGRAMMABLE_BUTTON_7
#define PB_8 QK_PROGRAMMABLE_BUTTON_8
#define PB_9 QK_PROGRAMMABLE_BUTTON_9
#define PB_10 QK_PROGRAMMABLE_BUTTON_10
#define PB_11 QK_PROGRAMMABLE_BUTTON_11
#define PB_12 QK_PROGRAMMABLE_BUTTON_12
#define PB_13 QK_PROGRAMMABLE_BUTTON_13
#define PB_14 QK_PROGRAMMABLE_BUTTON_14
#define PB_15 QK_PROGRAMMABLE_BUTTON_15
#define PB_16 QK_PROGRAMMABLE_BUTTON_16
#define PB_17 QK_PROGRAMMABLE_BUTTON_17
#define PB_18 QK_PROGRAMMABLE_BUTTON_18
#define PB_19 QK_PROGRAMMABLE_BUTTON_19
#define PB_20 QK_PROGRAMMABLE_BUTTON_20
#define PB_21 QK_PROGRAMMABLE_BUTTON_21
#define PB_22 QK_PROGRAMMABLE_BUTTON_22
#define PB_23 QK_PROGRAMMABLE_BUTTON_23
#define PB_24 QK_PROGRAMMABLE_BUTTON_24
#define PB_25 QK_PROGRAMMABLE_BUTTON_25
#define PB_26 QK_PROGRAMMABLE_BUTTON_26
#define PB_27 QK_PROGRAMMABLE_BUTTON_27
#define PB_28 QK_PROGRAMMABLE_BUTTON_28
#define PB_29 QK_PROGRAMMABLE_BUTTON_29
#define PB_30 QK_PROGRAMMABLE_BUTTON_30
#define PB_31 QK_PROGRAMMABLE_BUTTON_31
#define PB_32 QK_PROGRAMMABLE_BUTTON_32
#define QK_PROGRAMMABLE_BUTTON_MIN QK_PROGRAMMABLE_BUTTON_1
#define QK_PROGRAMMABLE_BUTTON_MAX QK_PROGRAMMABLE_BUTTON_32

#include "quantum_keycodes_legacy.h"
