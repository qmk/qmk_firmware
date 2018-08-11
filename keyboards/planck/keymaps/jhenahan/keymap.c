
#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WORKMAN 0
#define _DEAD 1
#define _QWERTY 2
#define _LOWER 3
#define _RAISE 4
#define _PLOVER 5
#define _ADJUST 16

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  DEAD,
  QWERTY,
  LOWER,
  RAISE,
  PLOVER,
  EXT_PLV,
  TOG_PLV
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  | Dead |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | RAlt | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = {
  {KC_TAB,              KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC},
  {MT(MOD_LCTL,KC_ESC), KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT},
  {KC_LSFT,             KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    DEAD,    KC_DOT,  KC_SLSH, KC_ENT},
  {KC_LCTL,             KC_RALT, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Workman Dead Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |   %  |   &  |   ?  |   +  |   @  |   $  |   _  |   [  |   ]  |   !  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   /  |   (  |   =  |   0  |   {  |   }  |   1  |   *  |   )  |   -  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   |  |   \  |   2  |   3  |   4  |   5  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   <  |   ~  |   `  |      ,      |   #  |   ^  |   >  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DEAD] = {
  {XXXXXXX,  KC_PERC, KC_AMPR, KC_QUES, KC_PLUS, KC_AT,   KC_DLR,  KC_UNDS, KC_LBRC, KC_RBRC,  KC_EXLM, XXXXXXX},
  {XXXXXXX,  KC_SLSH, KC_LPRN, KC_EQL,  KC_0,    KC_LCBR, KC_RCBR, KC_1,    KC_ASTR, KC_RPRN,  KC_MINS, XXXXXXX},
  {XXXXXXX,  KC_6,    KC_7,    KC_8,    KC_9,    KC_PIPE, KC_BSLS, KC_2,    KC_3,    KC_4,     KC_5,    XXXXXXX},
  {XXXXXXX,  XXXXXXX, KC_LT,   KC_TILD, KC_GRV,  KC_COMM, KC_COMM, KC_HASH, KC_CIRC, KC_GT,    XXXXXXX, XXXXXXX}
},

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | RAlt | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL, KC_RALT, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      | Vol+ |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Next | Vol- | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS), _______, KC_VOLU, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV,    KC_MNXT, KC_VOLD, KC_MPLY}
},

/* Raise - KWM Interaction
 * ,-----------------------------------------------------------------------------------.
 * |Restrt|      |TgSplt|Flotng|Parent|FlScrn|InsMrk| InsW | InsS | InsN | InsE |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Mark |Rotate|Prefix| Term | BSP  |SwpMrk|SwapW |SwapS |SwapN |SwapE |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |MarkW |MarkS |MarkN |MarkE |Monocl|Float |FocusW|FocusS|FocusN|FocusE|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {LCAG(KC_Q), XXXXXXX,    LCAG(KC_S),       LCAG(KC_W),   LCAG(KC_D), LCAG(KC_F),        LCTL(S(KC_X)),    LCTL(S(KC_H)),    LCTL(S(KC_J)),     LCTL(S(KC_K)),    LCTL(S(KC_L)),    XXXXXXX},
  {XXXXXXX,    LCAG(KC_M), LGUI(LCTL(KC_R)), LCAG(KC_DOT), LCAG(KC_T), LGUI(LCTL(KC_A)),  LCTL(LALT(KC_M)), LCTL(LALT(KC_H)), LCTL(LALT(KC_J)),  LCTL(LALT(KC_K)), LCTL(LALT(KC_L)), XXXXXXX},
  {_______,    LCAG(KC_H), LCAG(KC_J),       LCAG(KC_K),   LCAG(KC_L), LGUI(LCTL(KC_S)),  LGUI(LCTL(KC_D)), LGUI(LALT(KC_H)), LGUI(LALT(KC_J)),  LGUI(LALT(KC_K)), LGUI(LALT(KC_L)), _______},
  {_______,    _______,    _______,          _______,      _______,    _______,           _______,          _______,          _______,           _______,          _______,          _______}
},

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |TogOut|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC},
  {TOG_PLV, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_M,    KC_C,    XXXXXXX, XXXXXXX, KC_L,    KC_COMM, XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Workmn|Plover|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  WORKMAN, PLOVER,  _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_workman[][2]    = SONG(WORKMAN_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_workman);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case DEAD:
      if (record->event.pressed) {
        layer_on(_DEAD);
        set_oneshot_layer(_DEAD, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(tone_plover);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  case TOG_PLV:
    if (record->event.pressed) {
      register_code(KC_R);
      register_code(KC_W);
      register_code(KC_T);
      register_code(KC_C);
      register_code(KC_P);
      register_code(KC_O);
      clear_keyboard();
    }
    return false;
    break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

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

#endif
