#pragma once
#include "kuchosauronad0.h"

#if defined(KEYMAP_SAFE_RANGE)
#  define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#  define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes{
  VRSN = PLACEHOLDER_SAFE_RANGE,              // Prints QMK Firmware and board info
  KC_QWERTY,         // Sets default layer to QWERTY
  KC_COLEMAK,        // Sets default layer to COLEMAK
  KC_DVORAK,         // Sets default layer to DVORAK
  KC_WORKMAN,        // Sets default layer to WORKMAN
  KC_PLOVER,         // Sets default layer to PLOVER

  KC_MAKE,           // Run keyboard's customized make command
  KC_RGB_T,          // Toggles RGB Layer Indication mode
  KC_SECRET_1,       
  KC_SECRET_2,       
  KC_SECRET_3,       
  KC_SECRET_4,       
  KC_SECRET_5,       
  KC_CCCV,           // Hold to copy, tap to paste
  KC_NUKE,           // NUCLEAR LAUNCH DETECTED!!!
  UC_FLIP,           // (ಠ痊ಠ)┻━┻
  UC_TABL,           // ┬┬ノ( º _ ºノ)
  UC_SHRG,           // ¯\_(ツ)_/¯
  UC_DISA,           // ಠ_ಠ

  MC_QT1,            // ""
  MC_QT2,            // ''
  MC_QT3,            // `'
  MC_PAR,            // Parenthesis
  MC_CUR,            // Curly bracket
  MC_SQR,            // Square bracket
  MC_ABR,            // Angle bracket
  MCT_NEW,           // New Tmux Session
  MCT_SH,            // Tmux horizontal split
  MCT_SV,            // Tmux vertical split
  MCT_ZM,            // Tmux zoom
  MCT_SCR,           // Tmux scroll mode
  MCT_UP,            // Tmux up
  MCT_DW,            // Tmux down
  MCT_LFT,           // Tmux left
  MCT_RGT,           // Tmux right
  MCV_B,             // Vim begin of line
  MCV_E,             // Vim end of line
  MCT_F,             // Vim for loop
  MCG_A,             // Git add
  MCG_C,             // Git commit
  MCG_P,             // Git push
  MCG_R,             // Git revert
  MCG_L,             // Git log
  MCG_S,             // Git status

  NEW_SAFE_RANGE     //use "NEWPLACEHOLDER for keymap specific codes
  };

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define TG_MODS TG(_MODS)
#define TG_GAME TG(_GAMEPAD)
#define OS_LWR OSL(_LOWER)
#define OS_RSE OSL(_RAISE)
#define OS_UNI OSL(_UNICODE)

#define SEC1     KC_SECRET_1
#define SEC2     KC_SECRET_2
#define SEC3     KC_SECRET_3
#define SEC4     KC_SECRET_4
#define SEC5     KC_SECRET_5
#define SEC6     KC_SECRET_6

#define QWERTY   KC_QWERTY
#define DVORAK   KC_DVORAK
#define COLEMAK  KC_COLEMAK
#define WORKMAN  KC_WORKMAN
#define PLOVER   KC_PLOVER

#define KC_RESET RESET
#define KC_RST   KC_RESET

#define UC_IRNY  UC(0x2E2E)
#define UC_CLUE  UC(0x203D)
