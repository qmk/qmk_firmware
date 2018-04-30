#include "card.h"
#ifdef AUDIO_ENABLE
	#include "audio.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = KEYMAP(
		RGB_TOG,        RGB_SAI,        RGB_VAI, \
		        RGB_HUD,        RGB_HUI,         \
		RGB_MOD,        RGB_SAD,        RGB_VAD, \
		BL_STEP,                                 \
		F(0),   F(1),   F(2)                     \
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

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_FUNCTION(0),
	[1] = ACTION_FUNCTION(1),
	[2] = ACTION_FUNCTION(2)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch (id) {
			case 0:
				PLAY_SONG(tone_startup);
				break;
			case 1:
				PLAY_SONG(music_scale);
				break;
			case 2:
				PLAY_SONG(tone_goodbye);
				break;
		}
	}
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
