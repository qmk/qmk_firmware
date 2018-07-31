#include "pvinis.h"
#include "version.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#endif // AUDIO_ENABLE


#ifdef AUDIO_ENABLE
float tone_katamari_rolling_star[][2] = SONG(KATAMARI_ROLLING_STAR);
#endif // AUDIO_ENABLE


// functions for the individual keymaps to implement if they need something extra
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


// handle my own keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PV_VERSION:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case PV_KATAMARI:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        PLAY_SONG(tone_katamari_rolling_star);
#endif
      }
      return false;
  }
  return process_record_keymap(keycode, record);
}


#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
};
#endif // TAP_DANCE_ENABLE