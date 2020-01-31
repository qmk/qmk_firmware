#include "danielo515.h"

bool onMac = true;
// Send control or GUI depending if we are on windows or mac
bool CMD(uint16_t kc) {
  if(onMac){ tap_code16(LGUI(kc)); } else { tap_code16(LCTL(kc)); }
  return false;
}

//**************** Handle keys function *********************//
bool altPressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  bool pressed = record->event.pressed;
  if(pressed){
    refresh_incremental_macros(keycode);
    if(process_incremental_macro(keycode)){
      return false;
    }
    if(is_macro(keycode)){
      return handle_macro(keycode);
    }
   switch (keycode) {
        case MAC_TGL:
        onMac = !onMac;
        onMac ? SEND_STRING("On mac") : SEND_STRING("Not on MAC");
        return false;
      }
  }

  switch (keycode)
  {
    case QWERTY:
        if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_qwerty);
        #endif
        layer_on(_QWERTY);
        }
        return false;
    case LOWER:
        if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case RAISE:
        if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case ADJUST:
    if (record->event.pressed) {
        layer_on(_ADJUST);
        } else {
        layer_off(_ADJUST);
        }
        return false;
 // == Macros START ===
  case ARROW:
    if (record->event.pressed) SEND_STRING("->");
    return false;
  case F_ARROW:
    if (record->event.pressed) SEND_STRING("=>");
    return false;
  case GREP:
    if (record->event.pressed) SEND_STRING(" | grep "); return false;
 // == Macros END ===
 // == Multi Os START ===
  case KC_HOME:// make the home behave the same on OSX
    if (record->event.pressed && onMac) {
        SEND_STRING(SS_LCTRL("a"));
        return false;
    }
  case KC_END:// make the end behave the same on OSX
    if (record->event.pressed && onMac) {
        tap_code16(C(KC_E));
        return false;
    }
  case AC_A:// Accent á
    if (record->event.pressed) SEND_STRING(SS_LALT("e") "a"); return false;
  case AC_E:// Accent é
    if (record->event.pressed) SEND_STRING(SS_LALT("e") "e"); return false;
  case AC_I:// Accent í
    if (record->event.pressed) SEND_STRING(SS_LALT("e") "i"); return false;
  case AC_O:// Accent ó
    if (record->event.pressed) SEND_STRING(SS_LALT("e") "o"); return false;
  case CUT: if (record->event.pressed) return CMD(KC_X);
  case COPY:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LGUI("c")) : SEND_STRING(SS_LCTRL("c"));
    }
    return false;
  case PASTE:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LGUI("v")) : SEND_STRING(SS_LCTRL("v"));
    }
    return false;
  case SAVE:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LGUI("s")) : SEND_STRING(SS_LCTRL("s"));
    }
    return false;
  case UNDO:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LGUI("z")) : SEND_STRING(SS_LCTRL("z"));
    }
    return false;
  case FIND:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LGUI("f")) : SEND_STRING(SS_LCTRL("f"));
    }
    return false;
  case CHG_LAYOUT:
    if (record->event.pressed) {
     onMac ?  SEND_STRING(SS_LCTRL(" ")) : SEND_STRING(SS_LCTRL("f"));
    }
    return false;
 // == Multi Os END ===
#ifdef RGBLIGHT_ENABLE
  case RGB_SLD:
    if (record->event.pressed) { rgblight_mode(1); }
    return false;
    break;
    //First time alt + tab, and alt stays sticky. Next press we just send tab. Any other key releases the alt
#endif
  case ALT_TAB:
    if (record->event.pressed)
    {
      if (altPressed)
      {
        tap_code(KC_TAB);
      }
      else
      {
        altPressed = true;
        layer_on(7); // go to movement layer
        onMac ? register_code(KC_LGUI) : register_code(KC_LALT);
        tap_code(KC_TAB);
      }
    }
    return false;
  // avoid alt releasing if the key is of movement
  case KC_RIGHT ... KC_UP:
    if (altPressed)
    {
      return true; // yes QMK, do your stuff
    }
  }
  // Reset sticky alt tab
  if (altPressed)
  {
    onMac ?  unregister_code(KC_LGUI) : unregister_code(KC_LALT);
    altPressed = false;
    layer_off(7);
    return false;
  }
  return true;
};

//**************** LEADER *********************//
#ifdef LEADER_ENABLE
LEADER_EXTERNS();
#ifdef RGBLIGHT_ENABLE

void leader_start() {
  rgblight_setrgb_range(5, 100, 199, 10,15);
};

void leader_end(){
  rgblight_setrgb_range(200, 200, 255, 10,15);
};
#endif

void matrix_scan_user(void)
{
  if (leading && leader_sequence_size > 0 && timer_elapsed(leader_time) > LEADER_TIMEOUT)
  {
    leading = false;
    SEQ_ONE_KEY(KC_T) {
      SEND_STRING("``" SS_TAP(X_LEFT));
    }
    // Triple ticks
    SEQ_TWO_KEYS(KC_T, KC_T) {
      SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP));
    }
    // ==== International spanish accent vowels ====
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LALT("e") "a");
    }
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING(SS_LALT("e") "e");
    }
    SEQ_ONE_KEY(KC_I) {
      SEND_STRING(SS_LALT("e") "i");
    }
    SEQ_ONE_KEY(KC_O) {
      SEND_STRING(SS_LALT("e") "o");
    }
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING(SS_LALT("e") "u");
    }
    SEQ_ONE_KEY(KC_N) { // ñ
      SEND_STRING(SS_LALT("n") "n");
    }
    // ==== MACROS ===
    SEQ_ONE_KEY(KC_G) { // grep
      SEND_STRING(" | grep ");
    }
    SEQ_ONE_KEY(KC_K) {
        onMac ?  SEND_STRING(SS_LCTRL(" ")) : SEND_STRING(SS_LCTRL("f"));
    }
    SEQ_TWO_KEYS(KC_D, KC_G) { // vim delete all
      if(onMac){
        SEND_STRING(SS_LGUI("a") SS_TAP(X_D));
      } else {
        SEND_STRING(SS_LCTRL("a") SS_TAP(X_D));
      }
    }
    SEQ_ONE_KEY(KC_BSPACE) { // tripe delete!
      SEND_STRING(SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE));
    }
    SEQ_TWO_KEYS(KC_P, KC_G) {
      SEND_STRING("ps -ef | grep ");
    }
    SEQ_TWO_KEYS(KC_J, KC_A) {
      SEND_STRING("() => {}"SS_TAP(X_LEFT) SS_TAP(X_LEFT)SS_TAP(X_LEFT) SS_TAP(X_LEFT)SS_TAP(X_LEFT) SS_TAP(X_LEFT)SS_TAP(X_LEFT));
    }
    SEQ_TWO_KEYS(KC_S, KC_S) {
      SEND_STRING("~/.ssh/ "); // this is a pain to type
    }
    SEQ_TWO_KEYS(KC_F, KC_T) {
      SEND_STRING("feat():" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    }
    // ### LAYER CHANGE
    SEQ_ONE_KEY(KC_1) {
      layer_on(1);
    }
    SEQ_ONE_KEY(KC_H) { // control enter, because yes
      SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_ENTER) SS_UP(X_LCTRL));
    }
    // paste all
    SEQ_ONE_KEY(KC_P) {
      if(onMac){
        SEND_STRING(SS_LGUI("a") SS_LGUI("v"));
      } else {
        SEND_STRING(SS_LCTRL("a") SS_LCTRL("v"));
      }
    }
    SEQ_THREE_KEYS(KC_M, KC_A, KC_C) {
      onMac = true;
    #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(255, 255, 255);
    #endif
    }
    SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
      onMac = false;
    #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(255, 255, 0);
    #endif
    }
    /*  Copy all */
    SEQ_ONE_KEY(KC_Y) {
      if(onMac){
        SEND_STRING(SS_LGUI("a") SS_LGUI("c"));
      } else {
        SEND_STRING(SS_LCTRL("a") SS_LCTRL("c"));
      }
    }
    //emoji bar
    SEQ_TWO_KEYS(KC_E, KC_E) {
      SEND_STRING(SS_DOWN(X_LGUI) SS_LCTRL(" ") SS_UP(X_LGUI));
    }

    SEQ_TWO_KEYS(KC_F, KC_F) {
      SEND_STRING("ps -ef | grep ");
    }
    SEQ_TWO_KEYS(KC_H, KC_T) {
      SEND_STRING("https://");
    }

    leader_end();
  }
}
#endif // LEADER

// ======== INCREMENTAL MACROS STUFF =============

#define MAX_INCREMENTAL_MACRO 20
#define TAP_ROTATION_TIMEOUT 400

uint16_t latest_kc = 0;
uint16_t latest_rotation = 0;
int key_count = 0;

const char incremental_macros[][MAX_INCREMENTAL_MACRO] = { "String1"SS_TAP(X_HOME)"X-", "String2"SS_TAP(X_HOME) };

bool process_incremental_macro (uint16_t kc) {

  if( kc < INC_MACROS_START || kc > INC_MACROS_END ){
    return false;
  }
  int macro_idx = (int) (kc - INC_MACROS_START) - 1;
  char tempstring[3] = {0};
  tempstring[0] = incremental_macros[macro_idx][key_count];
  // Special cases of SS_TAP SS_UP and SS_DOWN, they require two characters so get both once and skip on next iteration
  if( tempstring[0] == '\1' || tempstring[0] == '\2' || tempstring[0] == '\3'){
    tempstring[1] = incremental_macros[macro_idx][++key_count];
  }
  if( tempstring[0] == '\0'){
    key_count = 0;
  }
  send_string(tempstring);

  return true;
};

void refresh_incremental_macros (uint16_t kc) {
  if (kc == latest_kc)
    {
      if ( (timer_elapsed(latest_rotation) > TAP_ROTATION_TIMEOUT) || (key_count >= MAX_INCREMENTAL_MACRO) ) key_count = 0;
      else key_count++;
    } else {
      key_count = 0;
      latest_kc = kc;
    }

  latest_rotation = timer_read();
}


// ======== VISUAL STUDIO CODE SHORTCUTS STUFF

bool is_macro (uint16_t kc){
  return kc > MACRO_START && kc < MACRO_END;
};

bool command_shift_p (bool isMac) {
   isMac
   ? SEND_STRING(SS_DOWN(X_LSHIFT)SS_LGUI("p")SS_UP(X_LSHIFT))
   : SEND_STRING(SS_DOWN(X_LSHIFT)SS_LCTRL("p")SS_UP(X_LSHIFT));
   return false;
};

bool VSCommand(bool isMac, char *cmd)
{
  command_shift_p (isMac);
  send_string(cmd);
  SEND_STRING(SS_TAP(X_ENTER));
  return false;
};

bool handle_macro(uint16_t kc)
{
  switch (kc)
  {
    case T_TERM: return VSCommand(onMac, "toit");
    case FIX_ALL: return VSCommand(onMac, "faap");
    case BLK_CMNT: return VSCommand(onMac, "tbc");
    case LN_CMNT: return VSCommand(onMac, "tlic");
    case CMD_S_P: return command_shift_p(onMac);
    case TRI_TICKS: SEND_STRING("[[[ "); break;
  }
  return false;
};
