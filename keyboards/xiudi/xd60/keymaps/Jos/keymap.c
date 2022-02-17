#include QMK_KEYBOARD_H
#include "action_layer.h"

// TODO: THOSE ARE IDEAS:
// TODO:
// TODO: - Proper support for "GUI+TAB" application switching, with the GUI holding and shift, etc.
// TODO:     - Maybe implement a process_record instead of a tap-dance, or complex tap dance?
// TODO: - Media keys on Fn1 layer, *hjklm,.* or arrow cluster?
// TODO: - What more than NumPad + RGB on the Fn3 toggled layer?
// TODO: - Add an in-keymap way to toggle LGUI/F(0) key, HELD_ESC_IS_SHIFT and BSPC_BLOCKS_DEL.
// TODO:
// TODO: THOSE ARE BUGS TO FIX:
// TODO: - None (found so far)

// Adjusting process_record_user functionnalities, comment to disable.
#define ISOLIKE_ALT_ENTER
#define TWO_SFT_CAPS
#define APP_IS_RALT_RCTRL
#define HELD_ESC_IS_SHIFT
#define BSPC_BLOCKS_DEL
#define ALT_MINSEQL_IS_ALT_78

// Cases where the GUI key will actually do what the GUI key normally does.
#define AC_G_W    LGUI(KC_W)   // Ubuntu: Shows windows on current desktop
#define AC_G_S    LGUI(KC_S)   // Ubuntu: Overview of all desktops
#define AC_G_D    LGUI(KC_D)   // Windows: Show/Toggle desktop
#define AC_G_L    LGUI(KC_L)   // Ubuntu/Windows: Lock session
#define AC_G_T    LGUI(KC_T)   // Ubuntu: Shows Trash // elementary: Opens terminal
#define AC_G_E    LGUI(KC_E)   // Windows: Opens file explorer
#define AC_G_H    LGUI(KC_H)   // Windows: Show/Hide hidden files
#define AC_G_SPC  LGUI(KC_SPC) // elementary: Shows application launcher


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  LAYOUT_all(
      KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,   KC_DEL,    \
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,   KC_RBRC,             KC_BSLS,   \
      KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,   KC_NO,               KC_ENT,    \
      KC_LSFT,  KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSFT,  KC_UP,     MO(1),     \
      KC_LCTL,  TD(0),   KC_LALT,                            KC_SPC ,                             KC_RALT,  KC_RCTRL,  KC_LEFT,  KC_DOWN,   KC_RIGHT),
                                                                                                                                           
  // 1: Function 1 Layers                                                                                                                  
  LAYOUT_all(                                                                                                                                  
      RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PAUS,   KC_PSCR,    \
      KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,             KC_TRNS,    \
      KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT,  KC_MSTP,  KC_TRNS,   KC_NO,               KC_TRNS,    \
      KC_TRNS, TG(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD,  KC_VOLU,  KC_TRNS,   KC_TRNS,  KC_PGUP,   KC_TRNS,    \
      KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS,  KC_TRNS,   KC_HOME,  KC_PGDOWN, KC_END),
                                                                                                                                           
  // 2: GUI/Function 2 Layer                                                                                                                   
  LAYOUT_all(                                                                                                                                  
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PAUS,    KC_PSCR,   \
      KC_TRNS, KC_TRNS, AC_G_W,  AC_G_E,  KC_TRNS, AC_G_T,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,              KC_TRNS,   \
      KC_TRNS, KC_TRNS, AC_G_S,  AC_G_D,  KC_TRNS, KC_TRNS, AC_G_H,  KC_TRNS, KC_TRNS, AC_G_L,   KC_TRNS,  KC_TRNS,   KC_NO,                KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_PGUP,    KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS,                            AC_G_SPC,                            KC_TRNS,  KC_TRNS,   KC_HOME,  KC_PGDOWN,  KC_END),
                                                                                                                                           
  // 3: NumPad/Function 3 Toggle Layer                                                                                                                   
  LAYOUT_all(                                                                                                                                  
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,     KC_PSLS,  KC_PMNS,   KC_PPLS,  KC_TRNS,    KC_TRNS,   \
      KC_TRNS, KC_NO,   KC_NO,   RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,   KC_4,    KC_5,    KC_6,     KC_PAST,  KC_NO,     KC_NO,                KC_NO,     \
      KC_TRNS, KC_NO,   KC_NO,   RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,   KC_1,    KC_2,    KC_3,     KC_PMNS,  KC_PENT,   KC_NO,                KC_TRNS,   \
      KC_NO,   KC_TRNS, KC_NO,   KC_NO,   RGB_TOG, RGB_MOD, KC_NO,   KC_NO,   KC_0,    KC_COMM,  KC_DOT,   KC_PPLS,   KC_NO,    KC_TRNS,    KC_TRNS,   \
      KC_NO,   KC_TRNS, KC_NO,                              KC_TRNS,                             KC_PENT,  KC_PENT,   KC_TRNS,  KC_TRNS,    KC_TRNS)  ,

// TRaNSparent layer for reference
/*  LAYOUT_all(                                                                                                                                  
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,              KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_NO,                KC_TRNS,   \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,   \
/      KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS), */
};

// LGUI acts as F(1) if held or as a tapped LGUI if tapped. Adapted from https://goo.gl/WnqGNS
// Commented lines are for the "sticky" layer on two presses. Left it here for reference.
static const int GUILAY = 2; // GUI Layer is layer #2

typedef struct {
  bool layer_toggle;
  bool sticky;
} td_ta_state_t;

static void ang_tap_dance_ta_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

//  if (td_ta->sticky) {
//    td_ta->sticky = false;
//    td_ta->layer_toggle = false;
//    layer_off (GUILAY);
//    return;
//  }
//
  if (state->count == 1 && !state->pressed) {
    register_code (KC_LGUI);
//    td_ta->sticky = false;
    td_ta->layer_toggle = false;
  } else {
    td_ta->layer_toggle = true;
    layer_on(GUILAY);
//    td_ta->sticky = (state->count == 2);
  }
}

// Added this one to make it more reactive on keyup
static void ang_tap_dance_ta_each (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle) {   // Braces added for clarity
    unregister_code (KC_LGUI);
  }
}


static void ang_tap_dance_ta_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle) {   // Braces added for clarity
    unregister_code (KC_LGUI);
  }
//  if (!td_ta->sticky)
    layer_off (GUILAY); // We don't verify it was swithed on, switching off regardless
}


qk_tap_dance_action_t tap_dance_actions[] = {
   [0]  = {
     .fn = { ang_tap_dance_ta_each, ang_tap_dance_ta_finished, ang_tap_dance_ta_reset },
     .user_data = (void *)&((td_ta_state_t) { false, false })
   }
};

#if defined ISOLIKE_ALT_ENTER  || defined TWO_SFT_CAPS  || defined APP_IS_RALT_RCTRL || defined ALT_MINSEQL_IS_ALT_78
// Function for the special modifiers actions below, makes it cleaner and yields smaller firmware.
static bool special_mods(uint16_t keycode, keyrecord_t *record, uint16_t modifier) {
  if (record->event.pressed && (keyboard_report->mods & MOD_BIT(modifier))) {
    register_code(keycode);
    return false;
  } else {
    unregister_code(keycode);
    return true;
  }
}
#endif

#ifdef BSPC_BLOCKS_DEL
static bool del_blocked = false; // Static as to not be defined elsewhere
#endif

// This function is processed before the key events on each key press/release.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode){
    #ifdef ISOLIKE_ALT_ENTER
    // RALT + ENT is the same as RALT+BSLS. 
    // For logical placement of *{* and *}* (the former being RALT+BSLS) with ANSI enter on 
    // ISO-based Canadian Multilingual layout (or any other ISO layout on ANSI keyboards).
    case KC_ENT:    return special_mods(KC_BSLS, record, KC_RALT);  // RALT + ENT -> RALT + BSLS            // See comment above
    #endif
    #ifdef TWO_SFT_CAPS
    case KC_LSFT:   return special_mods(KC_CAPS, record, KC_RSFT);  // Both shifts together -> Caps Lock    // RSFT  pressed first case
    case KC_RSFT:   return special_mods(KC_CAPS, record, KC_LSFT);  // Both shifts together -> Caps Lock    // LSFT  pressed first case
    #endif
    #ifdef APP_IS_RALT_RCTRL
    case KC_RCTRL:  return special_mods(KC_APP,  record, KC_RALT);  // RALT + RCTRL -> APP                  // RCTRL pressed first case
    case KC_RALT:   return special_mods(KC_APP,  record, KC_RCTRL); // RALT + RCTRL -> APP                  // RALT  pressed first case
    #endif
    #ifdef ALT_MINSEQL_IS_ALT_78
    case KC_MINS:  return special_mods(KC_7,  record, KC_RALT); // RALT + MINS -> RALT+7                  // {} in CAN Mult. softawre layout
    case KC_EQL:   return special_mods(KC_8,  record, KC_RALT); // RALT + EQL  -> RALT+8                  // ½¬ normally... Less finger stretch.
    #endif
    #ifdef HELD_ESC_IS_SHIFT
    case KC_ESC:    // Physically *ESC* is *CAPS*                   // Holding ESC -> SHIFT  (0 delay)      // Less awkward *<ESC>:wq* in vim
      if (record->event.pressed) {
        register_code(KC_ESC);      // Tapping ESC
        unregister_code(KC_ESC);
        register_code(KC_LSFT);     // Holding LSFT
        return false;
      } else {
        unregister_code(KC_LSFT);   // Releasing LSFT
        return false;
      }
    #endif
    #ifdef BSPC_BLOCKS_DEL
    // If BSPC is held, we flag DEL as disabled. To avoids acidental presses of DEL with split backspace key.
    case KC_BSPC:
      del_blocked = record->event.pressed;
      return true;
    // We don't handle DEL if it is pressed and flagged as disabled
    case KC_DEL:
      if (del_blocked && record->event.pressed) {
        return false;
      } else {
        return true;
      }
    #endif
    default: return true;   // Let QMK handle the rest as usual
  }
}


