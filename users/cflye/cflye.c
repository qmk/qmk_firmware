#include "cflye.h"
#include "print.h"

const uint32_t unicode_map[] PROGMEM = {
    [AE_L]  = 0x00E6,  // æ
    [AE_U]  = 0x00C6,  // Æ
    [OE_L]  = 0x00F8,  // ø
    [OE_U]  = 0x00D8,  // Ø
    [AA_L]  = 0x00E5,  // å
    [AA_U]  = 0x00C5,  // Å
    [SNEK]  = 0x1F40D, // 🐍
};

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  #ifdef CONSOLE_ENABLE
    char A[32];
    switch (get_highest_layer(layer_state)) {
        case _BASE:
          strcpy(A, "_BASE" );
          break;
        case _ALT:
          strcpy(A, "_ALT" );
          break;
        case _GAMING:
          strcpy(A, "_GAMING" );
          break;
        case _SYM:
          strcpy(A, "_SYM" );
          break;
        case _NUM:
          strcpy(A, "_NUM" );
          break;
        case _NAV:
          strcpy(A, "_NAV" );
          break;
        case _MEDIA:
          strcpy(A, "_MEDIA" );
         break;
        case _MOUSE:
          strcpy(A, "_MOUSE" );
          break;
        case _FUN:
          strcpy(A, "_FUN" );
          break;
    }

    uprintf("KL: layer(%s) kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", A, keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
  #endif 
  
  switch (keycode) {
    case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
    case U_BASE: 
        default_layer_set((layer_state_t)1 << _BASE);
        return false; 
    case U_ALT: 
        default_layer_set((layer_state_t)1 << _ALT);
        return false;   
    case U_GAMING: 
        default_layer_set((layer_state_t)1 << _GAMING);
        return false;  
    case SHRUG:
        if (record->event.pressed) {
            send_unicode_string("¯\\_(ツ)_/¯");
        }
        return false;  
  }
  return process_record_keymap(keycode, record);
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

void fn_eeclear(tap_dance_state_t *state, void *user_data) {
  if (state->count == 4) {
    eeconfig_init();
  }
}

void fn_base(tap_dance_state_t *state, void *user_data){
    if (state ->count == 2){
        default_layer_set((layer_state_t)1 << _BASE);
    }
}

void fn_alt(tap_dance_state_t *state, void *user_data){
    if (state ->count == 2){
        default_layer_set((layer_state_t)1 << _ALT);
    }
}

void fn_gaming(tap_dance_state_t *state, void *user_data){
    if (state ->count == 2){
        default_layer_set((layer_state_t)1 << _GAMING);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(fn_boot),
    [TD_BASE] = ACTION_TAP_DANCE_FN(fn_base),
    [TD_ALT] = ACTION_TAP_DANCE_FN(fn_alt),
    [TD_GAMING] = ACTION_TAP_DANCE_FN(fn_gaming),
    [TD_EECLEAR] = ACTION_TAP_DANCE_FN(fn_eeclear),
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        // colemak - shift
        case HOME_COL_P:
        case HOME_COL_L:
          return TAPPING_TERM - 80;

        // colemak - wln
        case HOME_COL_Q:
        case HOME_COL_SCLN:
          return TAPPING_TERM + 180;

        default:
          return TAPPING_TERM;
    }
}
#endif