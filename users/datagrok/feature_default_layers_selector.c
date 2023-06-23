#include "feature_default_layers_selector.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#ifdef DEFAULT_LAYER_SONGS
extern float default_layer_songs[][16][2];
#endif
#endif

bool process_record_save_default_layer(uint16_t keycode, keyrecord_t *record) {

#if defined(AUDIO_ENABLE)
    float saved_song[][2] = SONG(COIN_SOUND);
#endif

    if (!(keycode == KF_LAYO
          && record->event.pressed
          && get_mods() & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)))) {
        return true;
    }

    eeconfig_update_default_layer(default_layer_state);
#if defined(AUDIO_ENABLE)
    PLAY_SONG(saved_song);
#endif
    return false;
}

bool process_record_select_default_layer(uint16_t keycode, keyrecord_t *record) {
    if (!(keycode == KF_LAYO
          && record->event.pressed)) {
        return true;
    }
    if (!default_layer_state) {
        default_layer_set(2);
    } else {
        default_layer_set(
                          (((1U<<(highest_base_layer+1))-1) & (default_layer_state<<1))
                          | (default_layer_state>>highest_base_layer));
    }
    led_set(host_keyboard_leds());
#if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
    PLAY_SONG(default_layer_songs[get_highest_layer(default_layer_state)]);
#endif
    return false;
}
