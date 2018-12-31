#include "klackygears.h"


#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"
#include "dynamic_macro.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


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
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void sftswap (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_Z); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_T); break;
    case DOUBLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void reset_sftswap (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_T); break;
    case DOUBLE_HOLD: unregister_code(KC_LGUI);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting MDIA layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

  #if defined(KEYBOARD_helix)
    switch (keycode) {

      return false;
      break;

    case _DVRK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVRK);
      }
      return false;
      break;
    case _SYMB:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_SYMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_SYMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
      }
      return false;
      break;
    case _NUMB:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_NUMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_NUMB);
        TOG_STATUS = false;
        update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
      }
      return false;
      break;
    case _MDIA:
        if (record->event.pressed) {
          layer_on(_MDIA);
        } else {
          layer_off(_MDIA);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    // case EISU:
    //   if (record->event.pressed) {
    //     if(keymap_config.swap_lalt_lgui==false){
    //       register_code(KC_LANG2);
    //     }else{
    //       SEND_STRING(SS_LALT("`"));
    //     }
    //   } else {
    //     unregister_code(KC_LANG2);
    //   }
    //   return false;
    //   break;
    // case KANA:
    //   if (record->event.pressed) {
    //     if(keymap_config.swap_lalt_lgui==false){
    //       register_code(KC_LANG1);
    //     }else{
    //       SEND_STRING(SS_LALT("`"));
    //     }
    //   } else {
    //     unregister_code(KC_LANG1);
    //   }
    //   return false;
    //   break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }

  #endif

  return true;
}

// void matrix_init_user(void) {
//     #ifdef AUDIO_ENABLE
//         startup_user();
//     #endif
//     #ifdef RGBLIGHT_ENABLE
//       RGB_current_mode = rgblight_config.mode;
//     #endif
//     //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
//     #ifdef SSD1306OLED
//         iota_gfx_init(!has_usb());   // turns on the display
//     #endif
// }
/*
case maker:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!record->event.pressed) {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      clear_mods(); clear_oneshot_mods();
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
      if (temp_mod & MODS_SHIFT_MASK || temp_osm & MODS_SHIFT_MASK) {
        #if defined(__ARM__)
          send_string_with_delay_P(PSTR(":dfu-util"), 10);
        #elif defined(BOOTLOADER_DFU)
          send_string_with_delay_P(PSTR(":dfu"), 10);
        #elif defined(BOOTLOADER_HALFKAY)
          send_string_with_delay_P(PSTR(":teensy"), 10);
        #elif defined(BOOTLOADER_CATERINA)
          send_string_with_delay_P(PSTR(":avrdude"), 10);
        #endif // bootloader options
      }
      #if defined(KEYBOARD_viterbi)
        send_string_with_delay_P(PSTR(":dfu"), 10);
      #endif
      if (temp_mod & MODS_CTRL_MASK || temp_osm & MODS_CTRL_MASK) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10); }
      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
      set_mods(temp_mod);
    }
    break;
*/
void macroTogKey(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY1, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START1, &kr );
  }
}


void macroTogKey2(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY2, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START2, &kr );
  }
}

void pstinsrt(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_I);
    unregister_code(KC_I);
    register_code(KC_E);
    unregister_code(KC_E);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void ccopy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void pstspecial(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_V);
    unregister_code(KC_V);
  }
  else
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_T);
    unregister_code(KC_T);
  }
  reset_tap_dance(state);
}

void deldel(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_D);
    unregister_code(KC_D);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_DEL);
    unregister_code(KC_DEL);
  }
  reset_tap_dance(state);
}

void findreplace(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_H);
    unregister_code(KC_H);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F);
    unregister_code(KC_F);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void cyclawin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}


void SCRNSNP(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_PSCR);
    unregister_code(KC_PSCR);
    unregister_code(KC_LALT);
  }
  else
  {
    SEND_STRING(SS_TAP(X_LGUI));
    SEND_STRING("SN");
    register_code(KC_LCTL);
    register_code(KC_N);
    unregister_code(KC_N);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}


void mcccpy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

void mcpstin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_I);
    unregister_code(KC_I);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [SSWAP]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,sftswap, reset_sftswap),
  [TD_MCROTOG]  = ACTION_TAP_DANCE_FN(macroTogKey),
  [TD_MCROTG2] = ACTION_TAP_DANCE_FN(macroTogKey2),
  [TD_PSTI] = ACTION_TAP_DANCE_FN(pstinsrt),
  [TD_PTSP] = ACTION_TAP_DANCE_FN(pstspecial),
  [TD_FNDR] = ACTION_TAP_DANCE_FN(findreplace),
  [TD_CCPY] = ACTION_TAP_DANCE_FN(ccopy),
  [TD_DDEL] = ACTION_TAP_DANCE_FN(deldel),
  [TD_ACCW] = ACTION_TAP_DANCE_FN(cyclawin),
  [TD_CAPESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC,KC_CAPS),
  [TD_DTEX] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EXLM),
  [TD_COMQUES] = ACTION_TAP_DANCE_DOUBLE(KC_COMM,KC_QUES),
  [TD_MINPLS] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS,KC_PPLS),
  [TD_DIVMLT] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS,KC_PAST),
  [TD_DOTEQL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EQL),
  [TD_SCNSP]  = ACTION_TAP_DANCE_FN(SCRNSNP),
  [TD_MCCCPY] = ACTION_TAP_DANCE_FN(mcccpy),
  [TD_MCPSTIN] = ACTION_TAP_DANCE_FN(mcpstin)

};
