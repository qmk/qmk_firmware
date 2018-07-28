/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ericgebhart.h"

#include "quantum.h"
#include "version.h"
#include "action.h"
#include "action_layer.h"
#include "process_keycode/process_tap_dance.h"
#include "keymap_bepo.h"

float tone_copy[][2]            = SONG(SCROLL_LOCK_ON_SOUND);
float tone_paste[][2]           = SONG(SCROLL_LOCK_OFF_SOUND);

static uint16_t copy_paste_timer;
userspace_config_t userspace_config;

void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };


// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  //ACTION_DEFAULT_LAYER_SET(DVORAK) ;
}

// check default layerstate to see which layer we are on.
// if (biton32(layer_state) == _DIABLO) {  --- current layer
// if (biton32(default_layer_state) == _DIABLO) { --- current default layer
// check for left shift on.
// if (mods & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);

static void switch_default_layer(uint8_t layer) {
  default_layer_set(1UL<<layer);
  clear_keyboard();
}

// so the keyboard remembers which layer it's in after power disconnect.
/*
  uint32_t default_layer_state_set_kb(uint32_t state) {
  eeconfig_update_default_layer(state);
  return state;
  }
*/

// These are the keys for dvorak on bepo.  column one is the keycode and mods for
// the unshifted key, the second column is the keycode and mods for the shifted key.
// GR is Good Range.  It subtracts SAFE_RANGE from the keycode so we can make a
// reasnably sized array without difficulties. The macro is for the constant declarations
// the function is for when we use it.
const uint8_t key_translations[][2][2] = {
  [GR(DB_1)] =      {{BP_DQOT, MOD_LSFT},      {BP_DCRC, MOD_LSFT}},
  [GR(DB_2)] =      {{BP_LGIL, MOD_LSFT},      {BP_AT, MOD_NONE}},
  [GR(DB_3)] =      {{BP_RGIL, MOD_LSFT},      {BP_DLR, MOD_LSFT}},
  [GR(DB_4)] =      {{BP_LPRN, MOD_LSFT},      {BP_DLR, MOD_NONE}},
  [GR(DB_5)] =      {{BP_RPRN, MOD_LSFT},      {BP_PERC, MOD_NONE}},
  [GR(DB_6)] =      {{BP_AT, MOD_LSFT},        {BP_AT, MOD_BIT(KC_RALT)}},
  [GR(DB_7)] =      {{BP_PLUS, MOD_LSFT},      {BP_P, MOD_BIT(KC_RALT)}},
  [GR(DB_8)] =      {{BP_MINS, MOD_LSFT},      {BP_ASTR, MOD_NONE}},
  [GR(DB_9)] =      {{BP_SLASH, MOD_LSFT},     {BP_LPRN, MOD_NONE}},
  [GR(DB_0)] =      {{BP_ASTR, MOD_LSFT},      {BP_RPRN, MOD_NONE}},
  [GR(DB_GRV)] =    {{BP_PERC, MOD_LSFT},      {BP_K, MOD_BIT(KC_RALT)}},
  [GR(DB_SCOLON)] = {{BP_COMM, MOD_LSFT},      {BP_DOT, MOD_LSFT}},
  [GR(DB_SLASH)] =  {{BP_SLASH, MOD_NONE},     {BP_APOS, MOD_LSFT}},
  [GR(DB_BACKSLASH)] = {{BP_AGRV, MOD_BIT(KC_RALT)}, {BP_B, MOD_BIT(KC_RALT)}},
  [GR(DB_EQL)] =    {{BP_EQL, MOD_NONE},       {BP_PLUS, MOD_NONE}},
  [GR(DB_COMM)] =   {{BP_COMMA, MOD_NONE},     {BP_LGIL, MOD_BIT(KC_RALT)}},
  [GR(DB_DOT)] =    {{BP_DOT, MOD_NONE},       {BP_RGIL, MOD_BIT(KC_RALT)}},
  [GR(DB_QUOT)] =   {{BP_APOS, MOD_NONE},      {BP_DQOT, MOD_NONE}},
  [GR(DB_MINUS)] =  {{BP_MINUS, MOD_NONE},     {KC_SPC, MOD_BIT(KC_RALT)}},
  [GR(DB_LPRN)] =   {{BP_LPRN, MOD_NONE},      {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RPRN)] =   {{BP_RPRN, MOD_NONE},      {BP_RPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_LBRC)] =   {{BP_Y, MOD_BIT(KC_RALT)}, {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RBRC)] =   {{BP_X, MOD_BIT(KC_RALT)}, {BP_RPRN, MOD_BIT(KC_RALT)}},
  // For the symbol layer
  [GR(DB_HASH)] =   {{BP_DLR, MOD_LSFT}, {BP_DLR, MOD_LSFT}},
  [GR(DB_LCBR)] =   {{BP_LPRN, MOD_BIT(KC_RALT)}, {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RCBR)] =   {{BP_LPRN, MOD_BIT(KC_RALT)}, {BP_RPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_PIPE)] =   {{BP_B, MOD_BIT(KC_RALT)}, {BP_B, MOD_BIT(KC_RALT)}},
  [GR(DB_TILD)] =   {{BP_K, MOD_BIT(KC_RALT)}, {BP_K, MOD_BIT(KC_RALT)}},
  [GR(DB_CIRC)] =   {{BP_AT, MOD_BIT(KC_RALT)}, {BP_AT, MOD_BIT(KC_RALT)}},
  [GR(DB_LESS)] =   {{BP_LGIL, MOD_BIT(KC_RALT)}, {BP_LGIL, MOD_BIT(KC_RALT)}},
  [GR(DB_GRTR)] =   {{BP_RGIL, MOD_BIT(KC_RALT)}, {BP_RGIL, MOD_BIT(KC_RALT)}},


};


uint8_t gr(uint8_t kc){
  return (kc - SAFE_RANGE);
}
// send the right keycode for the right mod.
// remove the mods we are taking care of,
// send our keycodes then restore them.
// all so we can make dvorak keys from bepo keycodes.
void send_keycode(uint8_t kc){
  uint8_t tmp_mods = get_mods();
  bool is_shifted = ( tmp_mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
  //uint8_t key[2][2] = key_translations[GR(kc)];
  // need to turn of the shift if it is on.
  unregister_mods((MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)));
  if(is_shifted){
    register_mods(SHIFTED_MODS(kc));
    register_code(SHIFTED_KEY(kc));
    unregister_code(SHIFTED_KEY(kc));
    unregister_mods(SHIFTED_MODS(kc));
  } else{
    register_mods(UNSHIFTED_MODS(kc));
    register_code(UNSHIFTED_KEY(kc));
    unregister_code(UNSHIFTED_KEY(kc));
    unregister_mods(UNSHIFTED_MODS(kc));
  }
  clear_mods();
  register_mods(tmp_mods);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
#endif //KEYLOGGER_ENABLE

// still dont know how to make #&_  And RALT is not ALTGR, That isn't working in the bepo keyboard
// either.   No {} either probably for the same reasons.  ALtGR is the key to some of these.
    switch (keycode) {
      // Handle the key translations for Dvorak on bepo. It's best if these are the first
      // enums after SAFE_RANGE.
    case DB_1:
    case DB_2:
    case DB_3:
    case DB_4:
    case DB_5:
    case DB_6:
    case DB_7:
    case DB_8:
    case DB_9:
    case DB_0:
    case DB_GRV:
    case DB_SCOLON:
    case DB_SLASH:
    case DB_BACKSLASH:
    case DB_EQL:
    case DB_DOT:
    case DB_COMM:
    case DB_QUOT:
    case DB_MINUS:
    case DB_LPRN:
    case DB_RPRN:
    case DB_LBRC:
    case DB_RBRC:
      if(record->event.pressed)
        send_keycode(keycode);
      unregister_code(keycode);
    break;

    case KC_QWERTY:
    if (record->event.pressed) {
        set_single_persistent_default_layer(QWERTY);
    }
    return false;
    break;
    case KC_COLEMAK:
    if (record->event.pressed) {
    set_single_persistent_default_layer(COLEMAK);
    }
    return false;
    break;
    case KC_DVORAK:
    if (record->event.pressed) {
        set_single_persistent_default_layer(DVORAK);
    }
    return false;
    break;
    case KC_WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(WORKMAN);
      }
    return false;
    break;

    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                    ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
                    ":teensy"
#elif defined(BOOTLOADER_CATERINA)
                    ":avrdude"
#endif // bootloader options
                    SS_TAP(X_ENTER));
      }
    return false;
    break;


    case KC_RESET: // Custom RESET code
      if (!record->event.pressed) {
        reset_keyboard();
      }
    return false;
    break;


    case EPRM: // Resets EEPROM
      if (record->event.pressed) {
        eeconfig_init();
        default_layer_set(1UL<<eeconfig_read_default_layer());
        layer_state_set(layer_state);
      }
      return false;
      break;
    case VRSN: // Prints firmware version
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
      }
    return false;
    break;

    /*  Code has been depreciated
        case KC_SECRET_1 ... KC_SECRET_5: // Secrets!  Externally defined strings, not stored in repo
        if (!record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string(decoy_secret[keycode - KC_SECRET_1]);
        }
        return false;
        break;
    */

    // These are a serious of gaming macros.
    // Only enables for the viterbi, basically,
    // to save on firmware space, since it's limited.
#ifdef MACROS_ENABLED
  case KC_OVERWATCH: // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
    if (record->event.pressed) { userspace_config.is_overwatch ^= 1; eeprom_update_byte(EECONFIG_USERSPACE, userspace_config.raw); }
    return false; break;
#endif // MACROS_ENABLED

    case KC_CCCV:                                    // One key copy/paste
      if(record->event.pressed){
        copy_paste_timer = timer_read();
      } else {
        if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {   // Hold, copy
          register_code(KC_LCTL);
          tap(KC_C);
          unregister_code(KC_LCTL);
#ifdef AUDIO_ENABLE
          PLAY_SONG(tone_copy);
#endif
        } else {                                // Tap, paste
          register_code(KC_LCTL);
          tap(KC_V);
          unregister_code(KC_LCTL);
#ifdef AUDIO_ENABLE
          PLAY_SONG(tone_paste);
#endif
        }
      }
      return false;
      break;
      case CLICKY_TOGGLE:
#ifdef AUDIO_CLICKY
        userspace_config.clicky_enable = clicky_enable;
        eeprom_update_byte(EECONFIG_USERSPACE, userspace_config.raw);
#endif
        break;
#ifdef UNICODE_ENABLE
        case UC_FLIP: // (╯°□°)╯ ︵ ┻━┻
          if (record->event.pressed) {
            register_code(KC_RSFT);
            tap(KC_9);
            unregister_code(KC_RSFT);
            process_unicode((0x256F | QK_UNICODE), record); // Arm
            process_unicode((0x00B0 | QK_UNICODE), record); // Eye
            process_unicode((0x25A1 | QK_UNICODE), record); // Mouth
            process_unicode((0x00B0 | QK_UNICODE), record); // Eye
            register_code(KC_RSFT);
            tap(KC_0);
            unregister_code(KC_RSFT);
            process_unicode((0x256F | QK_UNICODE), record); // Arm
            tap(KC_SPC);
            process_unicode((0x0361 | QK_UNICODE), record); // Flippy
            tap(KC_SPC);
            process_unicode((0x253B | QK_UNICODE), record); // Table
            process_unicode((0x2501 | QK_UNICODE), record); // Table
            process_unicode((0x253B | QK_UNICODE), record); // Table
          }
          return false;
          break;
#endif // UNICODE_ENABLE

}

return true;
  //  return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}

void tap_dance_mouse_btns (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    register_code(KC_BTN1);
    break;
  case 2:
    register_code(KC_BTN2);
    break;
  case 3:
    register_code(KC_BTN3);
    break;
  case 4:
    register_code(KC_BTN4);
    break;
  case 5:
    register_code(KC_BTN5);
    break;
  default:
    break;
  }
  reset_tap_dance(state);
}

// counting on all the qwerty layers to be less than dvorak_on_bepo
int on_qwerty(){
  uint8_t deflayer = (biton32(default_layer_state));
  return (deflayer < DVORAK_ON_BEPO);
}

void tap_dance_df_bepo_layers_switch (qk_tap_dance_state_t *state, void *user_data) {
      switch(state->count){
      case 1:
        switch_default_layer(DVORAK_ON_BEPO);
        break;
      case 2:
        switch_default_layer(BEPO);
        break;
      case 3:
        layer_invert(LAYERS);
        break;
      default:
        break;
      }
      reset_tap_dance(state);
}

void tap_dance_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    if(on_qwerty())
      layer_invert(SYMB);
    else
         layer_invert(SYMB_ON_BEPO);
    break;
  case 2:
    layer_invert(MDIA);
    break;
  case 3:
    layer_invert(LAYERS);
  default:
    break;
  }
  reset_tap_dance(state);
}

void tap_dance_default_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    switch_default_layer(DVORAK);
    break;
  case 2:
    switch_default_layer(DVORAK_ON_BEPO);
    break;
  case 3:
    switch_default_layer(BEPO);
    break;
  default:
    break;
  }
  reset_tap_dance(state);
}

// switch the default layer to another qwerty based layer.
void switch_default_layer_on_qwerty(int count) {
  switch(count){
  case 1:
    switch_default_layer(DVORAK);
    break;
  case 2:
    switch_default_layer(QWERTY);
    break;
  case 3:
    switch_default_layer(COLEMAK);
    break;
  case 4:
    switch_default_layer(WORKMAN);
    break;
  case 5:
    switch_default_layer(NORMAN);
    break;
  default:
    switch_default_layer(DVORAK);
    break;
  }
}

// switch the default layer to another bepo based layer.
void switch_default_layer_on_bepo(int count) {
  switch(count){
  case 1:
    switch_default_layer(DVORAK_ON_BEPO);
    break;
  case 2:
    switch_default_layer(BEPO);
    break;
  default:
    switch_default_layer(DVORAK_ON_BEPO);
    break;
  }
}


// tap to change the default layer. Distinguishes between layers that are based on
// a qwerty software keyboard and a bepo software keyboard.
// if shifted, choose layers based on the other software keyboard, otherwise choose only
// layers that work on the current software keyboard.
void tap_dance_default_os_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  //uint8_t shifted = (get_mods() & MOD_BIT(KC_LSFT|KC_RSFT));
  bool shifted = ( keyboard_report->mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
  int qwerty = on_qwerty();


  // shifted, choose between layers on the other software keyboard
  if(shifted){
    if (qwerty)
      switch_default_layer_on_bepo(state->count);
    else
          switch_default_layer_on_qwerty(state->count);

    // not shifted, choose between layers on the same software keyboard
  } else {
    if (qwerty)
      switch_default_layer_on_qwerty(state->count);
    else
      switch_default_layer_on_bepo(state->count);
  }

  reset_tap_dance(state);
}


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
     */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}
//instanalize an instance of 'tap' for the 'x' tap dance.
static tdtap xtap_state = {
  .is_press_action = true,
  .state = 0
};
/*
  This so I can have a single key that acts like LGUI in DVORAK no
  matter which keymap is my current default.
  It also allows for the
  shift gui and ctl gui, on the same key,  So the same key is Escape,
  and the mostcommon modifiers in my xmonad control keymap, while also
  insuring that dvorak is active for the xmonad command key
  Single tap = ESC
  tap and hold = dvorak with L_GUI
  double tap = One shot dvorak layer with LSFT LGUI mods
  double hold = dvorak with LCTL LGUI
  double single tap = esc.
*/
int get_xmonad_layer(){
  int qwerty = on_qwerty();

  if (qwerty)
    return(XMONAD);
  else
    return(XMONAD_FR);
}


void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  int xmonad_layer = get_xmonad_layer();
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
  case SINGLE_TAP:
    register_code(KC_ESC);
    break;
  case SINGLE_HOLD:
    layer_on(xmonad_layer);
    set_oneshot_mods (MOD_LGUI);
    //set_oneshot_layer (DVORAK, ONESHOT_START);
    break;
  case DOUBLE_TAP:
    set_oneshot_mods ((MOD_LCTL | MOD_LGUI));
    layer_on (xmonad_layer);
    set_oneshot_layer (xmonad_layer, ONESHOT_START);
    break;
  case DOUBLE_HOLD:
    set_oneshot_mods (MOD_LSFT | MOD_LGUI);
    if (xmonad_layer != -1)
      layer_on(xmonad_layer);
    break;
  case DOUBLE_SINGLE_TAP:
    register_code(KC_ESC);
    unregister_code(KC_ESC);
    register_code(KC_ESC);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  int xmonad_layer = get_xmonad_layer();
  switch (xtap_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_ESC);
    break;
  case SINGLE_HOLD:
    layer_off(xmonad_layer);
    break;
  case DOUBLE_TAP:
    set_oneshot_layer (xmonad_layer, ONESHOT_PRESSED);
    break;
  case DOUBLE_HOLD:
    layer_off(xmonad_layer);
    break;
  case DOUBLE_SINGLE_TAP:
    unregister_code(KC_ESC);
  }
  xtap_state.state = 0;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_TAB_BKTAB] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LSFT(KC_TAB)),
  [TD_MDIA_SYMB] = ACTION_TAP_DANCE_FN(tap_dance_layer_switch),
  [TD_DVORAK_BEPO] = ACTION_TAP_DANCE_FN(tap_dance_df_bepo_layers_switch),
  [TD_DEF_LAYER_SW] = ACTION_TAP_DANCE_FN(tap_dance_default_layer_switch),
  [TD_DEF_OS_LAYER_SW] = ACTION_TAP_DANCE_FN(tap_dance_default_os_layer_switch),
  [TD_HOME_END]  = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TD_XMONAD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
  [TD_MOUSE_BTNS] = ACTION_TAP_DANCE_FN(tap_dance_mouse_btns)
};
