#include "_qmk_handwire.h"

#define _______ KC_TRNS

enum keyboard_layers {
    _BL,
    _FL,
    _CL
};

enum custom_keycodes {
    S_BSKTC = SAFE_RANGE,
    S_ODEJY,
    S_RCKBY,
    S_DOEDR,
    S_SCALE,
    S_ONEUP,
    S_COIN,
    S_SONIC,
    S_ZELDA
};

#ifdef AUDIO_ENABLE
  float song_basketcase[][2] = SONG(BASKET_CASE);
  float song_ode_to_joy[][2]  = SONG(ODE_TO_JOY);
  float song_rock_a_bye_baby[][2]  = SONG(ROCK_A_BYE_BABY);
  float song_doe_a_deer[][2]  = SONG(DOE_A_DEER);
  float song_scale[][2]  = SONG(MUSIC_SCALE_SOUND);
  float song_coin[][2]  = SONG(COIN_SOUND);
  float song_one_up[][2]  = SONG(ONE_UP_SOUND);
  float song_sonic_ring[][2]  = SONG(SONIC_RING);
  float song_zelda_puzzle[][2]  = SONG(ZELDA_PUZZLE);
#endif

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_0,    KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_HOME,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_END,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_N,
      KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_LGUI,
                                          KC_SPC, MO(2), MO(1),

      KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_PGUP, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
      KC_PGDN, KC_H,    KC_J,    KC_K,    KC_L,    KC_COLN, KC_QUOT,
               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                        KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
      MO(2), MO(1), KC_SPC
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_BSKTC:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_basketcase);
            }
            return false;
        case S_ODEJY:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_ode_to_joy);
            }
            return false;
        case S_RCKBY:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_rock_a_bye_baby);
            }
            return false;
        case S_DOEDR:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_doe_a_deer);
            }
            return false;
        case S_SCALE:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_scale);
            }
            return false;
        case S_ONEUP:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_one_up);
            }
            return false;
        case S_COIN:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_coin);
            }
            return false;
        case S_SONIC:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_sonic_ring);
            }
            return false;
        case S_ZELDA:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(song_zelda_puzzle);
            }
            return false;
    }
    return true;
}
