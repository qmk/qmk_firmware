#include QMK_KEYBOARD_H
#include "keymap.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#ifdef DEFAULT_LAYER_SONGS
extern float default_layer_songs[][16][2];
#endif
#endif

// New keycode KF_LAYO rotates between available default layers (for e.g.,
// selecting a base layout). Shift+KF_LAYO makes the current one persistent.
bool process_record_layout(uint16_t keycode, keyrecord_t *record) {
  uint8_t default_layer;
  uint8_t i;
  #if defined(AUDIO_ENABLE)
  float saved_song[][2] = SONG(COIN_SOUND);
  #endif

  if (keycode != KF_LAYO || !record->event.pressed) {
    return true;
  }

  if (get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))) { // shift pressed
    // save default layer. whatever the current default layer is, store that
    eeconfig_update_default_layer(default_layer_state);
    #if defined(AUDIO_ENABLE)
        PLAY_SONG(saved_song);
    #endif
  } else {
    // rotate default layer.
    // find the current default layer
    default_layer = biton32(default_layer_state);
    // find next valid default layer
    for (i = 1; i < defaultlayers_n; i++) {
      if (defaultlayers[(default_layer + i) % defaultlayers_n]) {
        break;
      }
    }
    if (i == defaultlayers_n) {
      // we fell out of the loop without finding another default layer to switch
      // to.
      return false;
    }
    default_layer = (default_layer + i) % defaultlayers_n;
    default_layer_set(1U<<default_layer);
    led_set(host_keyboard_leds());
    #if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
      PLAY_SONG(default_layer_songs[default_layer]);
    #endif
  }
  return false;
}
