#include QMK_KEYBOARD_H

enum custom_keycodes {
	SONG_SU = SAFE_RANGE,
	SONG_SC,
	SONG_GB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		RGB_TOG,        RGB_SAI,        RGB_VAI, \
		        RGB_HUD,        RGB_HUI,         \
		RGB_MOD,        RGB_SAD,        RGB_VAD, \
		BL_STEP,                                 \
		SONG_SU,SONG_SC,SONG_GB                  \
	)
};

#ifdef AUDIO_ENABLE

float tone_startup[][2] = SONG(STARTUP_SOUND);
float tone_qwerty[][2] = SONG(QWERTY_SOUND);
float tone_dvorak[][2] = SONG(DVORAK_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);
float tone_plover[][2] = SONG(PLOVER_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
#ifdef AUDIO_ENABLE
    case SONG_SU:
      if (record->event.pressed) {
        PLAY_SONG(tone_startup);
      }

      return false;

    case SONG_SC:
      if (record->event.pressed) {
        PLAY_SONG(music_scale);
      }

      return false;

    case SONG_GB:
      if (record->event.pressed) {
        PLAY_SONG(tone_goodbye);
      }

      return false;
#endif
    default:
      return true;
  }
}

void led_set_user(uint8_t usb_led) {
}
