#pragma once

#define COMBO_COUNT 5      // number of combos
#define COMBO_TERM 25      // ms; tighter than default 50
#define TAPPING_TERM 200   // 200ms window for double tap

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define LAYOUT_callum LAYOUT_split_3x5_2
#define UNDO G(KC_Z)         // Cmd+Z
#define REDO G(S(KC_Z))      // Cmd+Shift+Z

