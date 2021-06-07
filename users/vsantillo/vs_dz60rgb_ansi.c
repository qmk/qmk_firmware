#include "vs_dz60rgb_ansi.h"
#include "tap_dances/tap_dance.h"
#include "tap_dances/tap_dance_controller.h"
#include "tap_dances/dances/quick_mute.h"
#include "tap_dances/dances/quick_redo.h"
#include "tap_dances/dances/quick_undo.h"
#include "tap_dances/dances/space_cadet_pro.h"

void matrix_init_user(void) {
    rgblight_mode(RGB_MATRIX_CUSTOM_berryLerp);
}

layer_state_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case MAC_BASE:
      autoshift_enable();
      break;
    default:
      autoshift_disable();
      break;
  }
  return state;
}

// Tap dances
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSCP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_space_cadet_pro_on_finish, left_space_cadet_pro_on_reset),
    [TD_RSCP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_space_cadet_pro_on_finish, right_space_cadet_pro_on_reset),
    [TD_QUICK_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quick_undo_on_finish, quick_undo_on_reset),
    [TD_QUICK_REDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quick_redo_on_finish, quick_redo_on_reset),
    [TD_QUICK_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, quick_mute, NULL, 100),
};

__attribute__ ((weak))
void rgb_matrix_indicators_kb(void) {
    if (layer_state_is(MAC_BASE) || layer_state_is(MAC_SPACEFN) || layer_state_is(MAC_FN1)) {
        if (layer_state_is(MAC_SPACEFN)) {
            rgb_matrix_set_color(40, RGB_SPRINGGREEN); // Set Caps Lock to Gold
        } else if (layer_state_is(MAC_FN1)) {
            rgb_matrix_set_color(40, RGB_GOLD); // Set Caps Lock to Gold
            rgb_matrix_set_color(60, RGB_RED); // Set Ctrl to Red for RESET
        }
        rgb_matrix_set_color(27, RGB_WHITE); // Set Tab to White
    } else if (layer_state_is(WINDOWS_BASE)) {
        if (layer_state_is(WINDOWS_FN1)) {
            rgb_matrix_set_color(40, RGB_GOLD); // Set Caps Lock to Gold
        }
        rgb_matrix_set_color(27, RGB_CYAN);  // Set tab to blue
    } else if (layer_state_is(WINDOWS_GAMING)) {
        if (layer_state_is(WINDOWS_GAMING_FN)) {
            rgb_matrix_set_color(40, RGB_GOLD); // Set Caps Lock to Gold
        }
        rgb_matrix_set_color(27, RGB_GREEN);  // Set tab to green
    }
}
