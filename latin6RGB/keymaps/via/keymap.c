#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_2x3( 
        KC_P4, KC_P5, MO(1), 
        KC_P1, KC_P2, KC_P3),
    [1] = LAYOUT_numpad_2x3( 
        AU_ON,   AU_OFF, MO(1), 
        MU_ON,   MU_OFF,  MI_ON),
	[2] = LAYOUT_numpad_2x3( 
        KC_P4, KC_P5, MO(1), 
        KC_P1, KC_P2, KC_P3),
};

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_numpad_2x3(
     3,  4,  5,
     0,  1,  2
);

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif
