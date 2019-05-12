#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _FN,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  PLOVER = SAFE_RANGE,
  EXT_PLV,
  DYNAMIC_MACRO_RANGE
};

enum planck_macros {
  KC_M_FIND,
  KC_M_AGAIN,
  KC_M_UNDO,
  KC_M_CUT,
  KC_M_COPY,
  KC_M_PASTE,
};

#define DYNAMIC_MACRO_SIZE 256
#include "dynamic_macro.h"

#define LOWER  LT(_LOWER, KC_BSPC)
#define RAISE  LT(_RAISE, KC_DEL)
#define FN_SPC LT(_FN, KC_SPC)

#define CAG_ESC MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_ESC)

#define LS_PGUP LSFT_T(KC_PGUP)
#define LS_HOME LSFT_T(KC_HOME)

#define LC_PGDN LCTL_T(KC_PGDN)
#define LC_END  LCTL_T(KC_END)

#define RS_TAB  RSFT_T(KC_TAB)
#define RS_ENT  RSFT_T(KC_ENT)

#define M_UNDO  M(KC_M_UNDO)
#define M_CUT   M(KC_M_CUT)
#define M_COPY  M(KC_M_COPY)
#define M_PSTE  M(KC_M_PASTE)
#define M_FIND  M(KC_M_FIND)
#define M_AGAIN M(KC_M_AGAIN)

#define M_RECD1 DYN_REC_START1
#define M_STOP1 DYN_REC_STOP
#define M_PLAY1 DYN_MACRO_PLAY1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    CAG_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LS_PGUP, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
    LC_PGDN, KC_LALT, KC_LGUI, KC_LSFT, LOWER,   FN_SPC,  FN_SPC,  RAISE,   RS_TAB,  RS_ENT,  XXXXXXX, XXXXXXX
),

[_FN] = LAYOUT_planck_grid(
    XXXXXXX, M_RECD1, M_STOP1, M_PLAY1, KC_MPRV, KC_MPLY, KC_MNXT, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, XXXXXXX,
    _______, KC_LCTL, KC_LALT, KC_LGUI, M_FIND , M_AGAIN, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, XXXXXXX,
    LS_HOME, M_UNDO , M_CUT  , M_COPY , M_PSTE , XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_BSLS, KC_PIPE,
    LC_END , _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    STN_N1 , STN_N2 , STN_N3 , STN_N4 , STN_N5 , STN_N6 , STN_N7 , STN_N8 , STN_N9 , STN_NA , STN_NB , STN_NC ,
    XXXXXXX, STN_S1 , STN_TL , STN_PL , STN_HL , STN_ST1, STN_ST3, STN_FR , STN_PR , STN_LR , STN_TR , STN_DR ,
    XXXXXXX, STN_S2 , STN_KL , STN_WL , STN_RL , STN_ST2, STN_ST4, STN_RR , STN_BR , STN_GR , STN_SR , STN_ZR ,
    EXT_PLV, XXXXXXX, XXXXXXX, STN_A  , STN_O  , XXXXXXX, XXXXXXX, STN_E  , STN_U  , XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, XXXXXXX,
    XXXXXXX, XXXXXXX, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, XXXXXXX, XXXXXXX, XXXXXXX,
    PLOVER , XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    // case QWERTY:
    //   if (record->event.pressed) {
    //     print("mode just switched to qwerty and this is a huge string\n");
    //     set_single_persistent_default_layer(_QWERTY);
    //   }
    //   return false;
    //   break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_init_user() {
  eeconfig_init();
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id) {
    case KC_M_UNDO:
      return MACRODOWN( D(LGUI), T(Z), U(LGUI), END );
    case KC_M_CUT:
      return MACRODOWN( D(LGUI), T(X), U(LGUI), END );
    case KC_M_COPY:
      return MACRODOWN( D(LGUI), T(C), U(LGUI), END );
    case KC_M_PASTE:
      return MACRODOWN( D(LGUI), T(V), U(LGUI), END );
    case KC_M_FIND:
      return MACRODOWN( D(LGUI), T(F), U(LGUI), END );
    case KC_M_AGAIN:
      return MACRODOWN( D(LGUI), T(G), U(LGUI), END );
  }

  return MACRO_NONE;
}
