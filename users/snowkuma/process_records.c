#include "snowkuma.h"

uint16_t copy_paste_timer;

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

#ifdef OLED_DRIVER_ENABLE
__attribute__((weak))
bool process_record_oled(uint16_t keycode, keyrecord_t *record) { return true; }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case M_BRAVE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("Brave.app\n");
      }
      break;

    case M_ITERM:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("Iterm.app\n");
      }
      break;

    case M_KRAKEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("GitKraken.app\n");  
      }
      break;

    case M_MONEY:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("MoneyDance.app\n");
      }
      break;

    case M_SPOTIFY:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("Spotify.app\n");
      }
      break;

    case M_TYPE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("TypeFu.app\n");
      }
      break;
  
  }

  return process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
         #ifdef OLED_DRIVER_ENABLE
         && process_record_oled(keycode, record)
         #endif
         ; // Close return
}