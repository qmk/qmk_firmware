#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN 1
#define _ULCK 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define HYP_TIC ALL_T(KC_GRV)
#define EQ_LOCK TD(TD_EQ_LOCK)
#define MIN_ULK TD(TD_MIN_ULOCK)

//Tap Dance Declarations
enum {
  TD_EQ_LOCK = 0,
  TD_MIN_ULOCK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------.
   * |   =  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  FN  |   `  | Alt  | LGUI | Back | ESC  |ENTER | SPCE | RGUI |   [  |  ]   |  FN  |
   * `-----------------------------------------------------------------------------------'
   */
  [_QWERTY] = {
    {EQ_LOCK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    MIN_ULK },
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
    {KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC },
    {MO(_FN), HYP_TIC, KC_LALT, KC_LGUI, KC_BSPC, KC_ESC,  KC_ENT,  KC_SPC,  KC_RGUI, KC_LBRC, KC_RBRC, MO(_FN) }
  },

  /* Fn
   * ,-----------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |      |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      | VOL- | VOL+ | MUTE |BLtogg|      | LEFT | DOWN |  UP  | RGHT |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      | BL-  | BL+  |Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |Voice-|Voice+|Mus on|MusOff|      |      |PLY/PS|      | PREV | NEXT |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_FN] = {
    {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ },
    {_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______ },
    {_______, KC_VOLD, KC_VOLU, KC_MUTE, BL_TOGG, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______ },
    {_______, BL_DEC,  BL_INC,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______ },
    {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  _______, _______, KC_MPLY, _______, KC_MPRV, KC_MNXT, _______ }
  }

};

float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {*/
  /*return true;*/
  /*[>switch (keycode) {<]*/
    /*[>case QWERTY:<]*/
      /*[>return true;<]*/
  /*[>}<]*/
/*};*/

void matrix_init_user(void) {
  startup_user();
}

void startup_user()
{
  _delay_ms(20); // gets rid of tick
  PLAY_SONG(tone_startup);
}

void shutdown_user()
{
  PLAY_SONG(tone_goodbye);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}


qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for equal, twice for hyper + X (alfred lock)
  [TD_EQ_LOCK] = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  HYPR(KC_X)),
  //Tap once for minus, twice for time.heals.nothing
  [TD_MIN_ULOCK] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, M(_ULCK))
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case _ULCK:
      if (record->event.pressed) {
        /* time.heals.nothing */
        return MACRO( I(220), T(T), T(I), T(M), T(E), T(DOT), T(H), T(E), T(A), T(L), T(S), T(DOT), T(N), T(O), T(T), T(H), T(I), T(N), T(G), END);
      }
      break;
  }
  return MACRO_NONE;
};
