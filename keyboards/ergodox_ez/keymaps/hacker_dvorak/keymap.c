#include QMK_KEYBOARD_H       // Includes the QMK-verse.
#include "keymap_plover.h"    // Includes the Plover keymap for easier readability.


// TODO: No eeprom changes unless needed, custom rgb settings for animations.
#include "keycodes/aliases_definitions.c"
#include "layers/layers_definitions.c"
#include "tap_dance/tap_dance_setup.c"
#include "tap_dance/tap_dances.c"
#include "user/matrix_scan_user.c"
#include "tap_dance/mod_tap_layer_dances/none_lead.c"
#include "tap_dance/mod_tap_layer_dances/dot_comm.c"
#include "tap_dance/mod_tap_layer_dances/quot_dquot.c"
#include "tap_dance/mod_tap_layer_dances/scln_coln.c"
#include "tap_dance/mod_tap_layer_dances/u_arrows_gui.c"
#include "tap_dance/mod_tap_layer_dances/h_mouse_gui.c"
#include "tap_dance/mod_tap_layer_dances/j_media_meh.c"
#include "tap_dance/mod_tap_layer_dances/w_media_meh.c"
#include "tap_dance/mod_tap_layer_dances/k_numpad_hyper.c"
#include "tap_dance/mod_tap_layer_dances/m_chords_hyper.c"
#include "tap_dance/tap_dance_actions.c"
#include "keycodes/custom_keycodes.c"
#include "dynamic_macro.h"    // Includes dynamic macro definitions, needed *after* the custom keycodes.
#include "hacker_dvorak.c"
#include "user/eeconfig_init_user.c"
#include "user/process_record_user.c"
#include "plover/plover_mode.c"
#include "user/layer_set_state_user.c"
