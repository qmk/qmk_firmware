#include "kuchosauronad0.h"

uint16_t copy_paste_timer;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Defines actions for my global custom keycodes. Defined in kuchosauronad0.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
  #if defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_keebio_iris_rev2)
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.row, record->event.key.col, record->event.pressed);
  #else
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
#endif //KEYLOGGER_ENABLE

  switch (keycode) {
  case KC_QWERTY ... KC_PLOVER:
    if (record->event.pressed) {
      set_single_persistent_default_layer(keycode - KC_QWERTY);
    }
    break;

  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!record->event.pressed) {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      clear_mods(); clear_oneshot_mods();
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
      if ( ( temp_mod | temp_osm ) & MOD_MASK_SHIFT )
#endif
      {
        #if defined(__arm__)
          send_string_with_delay_P(PSTR(":dfu-util"), TAP_CODE_DELAY);
        #elif defined(BOOTLOADER_DFU)
          send_string_with_delay_P(PSTR(":dfu"), TAP_CODE_DELAY);
        #elif defined(BOOTLOADER_HALFKAY)
          send_string_with_delay_P(PSTR(":teensy"), TAP_CODE_DELAY);
        #elif defined(BOOTLOADER_CATERINA)
          send_string_with_delay_P(PSTR(":avrdude"), TAP_CODE_DELAY);
        #endif // bootloader options
       }
      if ( ( temp_mod | temp_osm ) & MOD_MASK_CTRL) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), TAP_CODE_DELAY); }
      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
    }
    break;
// FLEDERMAUSLAND
  case MC_QT1:  // ""
    if(record->event.pressed){
      SEND_STRING("\"\"");
      tap_code(KC_LEFT);
    }
    break;
    case MC_QT2:  // ''
      if(record->event.pressed){
        SEND_STRING("''");
        tap_code(KC_LEFT);
      }
      break;
    case MC_QT3:  // `'
      if(record->event.pressed){
        SEND_STRING("`'");
        tap_code(KC_LEFT);
      }
      break;
    case MC_PAR:  // Parenthesis
      if(record->event.pressed){
        SEND_STRING("()");
        tap_code(KC_LEFT);
      }
      break;
    case MC_CUR:  // Curly bracket
      if(record->event.pressed){
        SEND_STRING("{}");
        tap_code(KC_LEFT);
      }
      break;
    case MC_SQR:  // Square bracket
      if(record->event.pressed){
        SEND_STRING("[]");
        tap_code(KC_LEFT);
      }
      break;
    case MC_ABR:  // Angle bracket
      if(record->event.pressed){
        SEND_STRING("<>");
        tap_code(KC_LEFT);
      }
      break;
    case MCT_NEW: // New Tmux Session
      if(record->event.pressed){
        tmux_prefix();
        SEND_STRING(":neww");
        tap_code(KC_ENT);
      }
      break;
    case MCT_SH:  // Tmux horizontal split
      if(record->event.pressed){
        tmux_prefix();
        SEND_STRING("%");
      }
      break;
    case MCT_SV:  // Tmux vertical split
      if(record->event.pressed){
        tmux_prefix();
        SEND_STRING("\"");
      }
      break;
    case MCT_ZM:  // Tmux zoom
      if(record->event.pressed){
        tmux_prefix();
        tap_code(KC_Z);
      }
      break;
    case MCT_SCR: // Tmux scroll mode
      if(record->event.pressed){
        tmux_prefix();
        tap_code(KC_PGUP);
      }
      break;
    case MCT_UP:  // Tmux up
      break;
    case MCT_DW:  // Tmux down
      break;
    case MCT_LFT: // Tmux left
      break;
    case MCT_RGT: // Tmux right
      tmux_prefix();
      tap_code(KC_RIGHT);
      break;
    case MCV_B:   // Vim begin of line
      if(record->event.pressed){
        tap_code(KC_0);
      }
      break;
    case MCV_E:   // Vim end of line
      if(record->event.pressed){
        SEND_STRING(":vsplit");
        tap_code(KC_ENT);
      }
      break;
    case MCT_F:   // Vim for loop
      if(record->event.pressed){
        SEND_STRING(":help");
        tap_code(KC_ENT);
      }
      break;
  case VRSN: // Prints firmware version
    if (record->event.pressed) {
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
    }
    break;
// These are a series of gaming macros.
// Only enables for the viterbi, basically,
// to save on firmware space, since it's limited.
#ifdef MACROS_ENABLED
  case KC_OVERWATCH: // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
    if (record->event.pressed) { userspace_config.is_overwatch ^= 1; eeconfig_update_user(userspace_config.raw); }
#ifdef RGBLIGHT_ENABLE
//    userspace_config.is_overwatch ? rgblight_mode_noeeprom(17) : rgblight_mode_noeeprom(18);
#endif //RGBLIGHT_ENABLE
    break;
  case KC_SALT:
    return send_game_macro("Salt, salt, salt...", record, false);
  case KC_MORESALT:
    return  send_game_macro("Please sir, can I have some more salt?!", record, false);
  case KC_SALTHARD:
    return send_game_macro("Your salt only makes me harder, and even more aggressive!", record, false);
  case KC_GOODGAME:
    return send_game_macro("Good game, everyone!", record, false);
  case KC_GLHF:
    return send_game_macro("Good luck, have fun!!!", record, false);
  case KC_SYMM:
    return send_game_macro("Left click to win!", record, false);
  case KC_JUSTGAME:
    return send_game_macro("It may be a game, but if you don't want to actually try, please go play AI, so that people that actually want to take the game seriously and \"get good\" have a place to do so without trolls like you throwing games.", record, false);
  case KC_TORB:
    return send_game_macro("That was positively riveting!", record, false);
  case KC_AIM:
    send_game_macro("That aim is absolutely amazing. It's almost like you're a machine!", record, true);
    return send_game_macro("Wait! That aim is TOO good!  You're clearly using an aim hack! CHEATER!", record, false);
  case KC_C9:
    return send_game_macro("OMG!!!  C9!!!", record, false);
  case KC_GGEZ:
    return send_game_macro("That was a fantastic game, though it was a bit easy. Try harder next time!", record, false);
#endif // MACROS_ENABLED

 case KC_CCCV:                                    // One key copy/paste
    if(record->event.pressed){
      copy_paste_timer = timer_read();
    } else {
      if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {   // Hold, copy
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
      } else {                                // Tap, paste
        register_code(KC_LCTL);
        tap_code(KC_V);
        unregister_code(KC_LCTL);
      }
    }
    break;

// Unicode
#ifdef UNICODE_ENABLE
  case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
    if (record->event.pressed) {
      send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
    }
    break;
  case UC_TABL: // ┬┬ノ( º _ ºノ)
    if (record->event.pressed) {
      send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029");
    }
    break;
  case UC_SHRG: // ¯\_(ツ)_/¯
    if (record->event.pressed) {
      send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
    }
    break;
  case UC_DISA: // ಠ_ಠ
    if (record->event.pressed) {
      send_unicode_hex_string("0CA0 005F 0CA0");
    }
    break;
#endif //!Unicode
}
  return process_record_keymap(keycode, record) &&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    process_record_user_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE
    process_record_secrets(keycode, record);
}
