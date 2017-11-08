#include "drashna.h"
#include "quantum.h"
#include "action.h"
#include "version.h"

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();

  rgblight_enable();

  if (true) {
    if (default_layer & (1UL << _COLEMAK)) {
      rgblight_set_magenta;
    }
    else if (default_layer & (1UL << _DVORAK)) {
      rgblight_set_green;
    }
    else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_set_purple;
    }
    else {
      rgblight_set_teal;
    }
  }
  else
  {
    rgblight_set_red;
    rgblight_mode(5);
  }
#endif
  matrix_init_keymap();
}

void matrix_scan_user(void) {
  matrix_scan_keymap();
}

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_workman[][2]    = SONG(PLOVER_SOUND);
#endif


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  uint16_t kc;
  if (is_overwatch) {
    kc = KC_BSPC;
  }
  else {
    kc = KC_ENTER;
  }
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
#endif

  switch (keycode) {
  case KC_QWERTY:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      persistent_default_layer_set(1UL << _QWERTY);
    }
    return false;
    break;
  case KC_COLEMAK:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_colemak);
#endif
      persistent_default_layer_set(1UL << _COLEMAK);
    }
    return false;
    break;
  case KC_DVORAK:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_dvorak);
#endif
      persistent_default_layer_set(1UL << _DVORAK);
    }
    return false;
    break;
  case KC_WORKMAN:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_workman);
#endif
      persistent_default_layer_set(1UL << _WORKMAN);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    }
    else {
      layer_off(_ADJUST);
    }
    return false;
    break;
  case KC_OVERWATCH:
    if (record->event.pressed) {
      is_overwatch = !is_overwatch;
    }
#ifdef RGBLIGHT_ENABLE
    is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
#endif
    return false;
    break;
  case KC_SALT:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Salt, salt, salt...");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_MORESALT:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Please sir, can I have some more salt?!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_SALTHARD:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Your salt only makes my penis that much harder, and even more aggressive!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_GOODGAME:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Good game, everyone!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
  }
    return false;
    break;
  case KC_GLHF:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Good luck, have fun!!!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_SYMM:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Left click to win!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_DOOMFIST:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("Hey, look at me.  I'm Doomfist, and I'm overpowered!  All I do is spam punches all day!   I'm DPS, tank and defense, rolled into one! All I need is team healing to be complete!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_JUSTGAME:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("It may be a game, but if you don't want to actually try, please go play AI, so that people that actually want to take the game seriously and \"get good\" have a place to do so without trolls like you throwing games.");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_TORB:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("That was positively riveting!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_AIM:
    if (!record->event.pressed) {
      register_code(kc);
      unregister_code(kc);
      _delay_ms(50);
      SEND_STRING("That aim is absolutely amazing. It's almost like you're a machine!" SS_TAP(X_ENTER));
      _delay_ms(50);
      SEND_STRING("Wait! That aim is TOO good!  You're clearly using an aim hack! CHEATER!" SS_TAP(X_ENTER));
    }
    return false;
    break;
  case KC_MAKE:
    if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
      SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP " RGBLIGHT_ENABLE=yes" SS_TAP(X_ENTER));
#else
      SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP " RGBLIGHT_ENABLE=no"SS_TAP(X_ENTER));
#endif
    }
    return false;
    break;
  case KC_RESET:
    if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb(0xff, 0x00, 0x00);
#endif
      reset_keyboard();
    }
    return false;
    break;
  case EPRM:
    if (record->event.pressed) {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  case KC_P00:
    if (!record->event.pressed) {
      register_code(KC_P0);
      unregister_code(KC_P0);
      register_code(KC_P0);
      unregister_code(KC_P0);
    }
    return false;
    break;
  }
  return process_record_keymap(keycode, record);
}


uint32_t layer_state_set_kb(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();

  switch (biton32(state)) {
  case _NAV:
    rgblight_set_blue;
    rgblight_mode(1);
    break;
  case _SYMB:
    rgblight_set_blue;
    rgblight_mode(2);
    break;
  case _MOUS:
    rgblight_set_yellow;
    rgblight_mode(1);
    break;
  case _MACROS:
    rgblight_set_orange;
    is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
    rgblight_mode(18);
    break;
  case _MEDIA:
    rgblight_set_green;
    rgblight_mode(22);
    break;
  case _OVERWATCH:
    rgblight_set_orange;
    rgblight_mode(17);
    break;
  case _DIABLO:
    rgblight_set_red;
    rgblight_mode(5);
    break;
  case _RAISE:
    rgblight_set_yellow;
    rgblight_mode(5);
    break;
  case _LOWER:
    rgblight_set_orange;
    rgblight_mode(5);
    break;
  case _ADJUST:
    rgblight_set_red;
    rgblight_mode(23);
    break;
  case _COVECUBE:
    rgblight_set_green;
    rgblight_mode(2);
  default:
    if (default_layer & (1UL << _COLEMAK)) {
      rgblight_set_magenta;
    }
    else if (default_layer & (1UL << _DVORAK)) {
      rgblight_set_green;
    }
    else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_set_purple;
    }
    else {
      rgblight_set_teal;
    }
    rgblight_mode(1);
    break;
  }
#endif
  return state;
}
