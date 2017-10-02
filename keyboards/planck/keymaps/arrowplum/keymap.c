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
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _PLOVER 5
#define _NAV 6
#define _MUSIC 7
#define _ADJUST 16

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  NAV,
  MUSIC1,
  MUSIC2,
  MUSIC3,
  MUSIC4,
  BACKLIT,
  EXT_PLV
};
// Func macro definitions.
#define LWR_SPC FUNC(0) // Tap for space, hold for LOWER
#define RSE_SPC FUNC(1) // Tap for space, hold for RAISE
#define CTL_ESC FUNC(2) // Tap for tab, hold for Control
#define CTL_ENT FUNC(3) //tap for enter, hold for control
#define SLH_GUI FUNC(4) //tap for slash, hold for RGUI
// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CTLESC|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |ctl/ent|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  | Ctrl | Alt  |  CMD | LOWER| RAISE| RAISE| LOWER| /CMD | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTL_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_ENT},
  {KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_UP, KC_RSPC },
  {NAV, KC_CAPS, KC_LALT, KC_LGUI, LWR_SPC, RSE_SPC, RSE_SPC, LWR_SPC, SLH_GUI,  KC_LEFT, KC_DOWN,  KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   =  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | C+tab|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   (  |   )  |   '  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   |  |  [   |   ]  | pgup  |Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  SPC |  SPC | SPC  |  SPC |      | home | pgdwn| end  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,   KC_ASTR,   KC_MINS, KC_EQL,   KC_BSPC},
  {M(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,   KC_LPRN,   KC_RPRN, KC_QUOTE, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS),KC_LBRC,   KC_RBRC, KC_PGUP,  _______},
  {_______, _______, _______, _______, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,    KC_RGUI,   KC_HOME, KC_PGDN,  KC_END}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |   +  |   -  |   {  |   }  |   "  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Next | Vol- | Vol+ | Play |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |       |      |      |      |      |      |      |     |     |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,            KC_BSPC},
  {M(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PLUS,   KC_MINS, KC_LCBR, KC_RCBR, KC_DOUBLE_QUOTE, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,         _______},
  {_______, _______, _______, _______, KC_SPC, KC_SPC, KC_SPC, KC_SPC, _______, KC_HOME, KC_PGDN,         KC_END},
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
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},

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
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_NAV] = {
  { MU_ON,   MUSIC1, MUSIC2,  MUSIC3, MUSIC4,  XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, MU_ON,   MU_OFF},
  {M(0), M(2), M(1), KC_END, KC_HOME, KC_END,  KC_HOME, KC_LEFT, KC_DOWN,  KC_RGHT, XXXXXXX, _______},
  {XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, KC_PGDN, KC_PGUP, XXXXXXX, KC_MS_BTN3, KC_MS_BTN1, KC_MS_U, KC_MS_BTN2},
  {_______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R}
}

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float close_encounters[][2] = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float tone_flint[][2] = SONG(IN_LIKE_FLINT);
float tone_zelda_puzzle[][2] = SONG(ZELDA_PUZZLE);
float tone_coin[][2] = SONG(COIN_SOUND);
float tone_1up[][2] = SONG(ONE_UP_SOUND);
float tone_ode_to_joy[][2] = SONG(ODE_TO_JOY);
#endif

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),
    [1] = ACTION_LAYER_TAP_KEY(_RAISE, KC_SPC),
    [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),
    [4] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_SLSH),
};
void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NAV:
        if (record->event.pressed) {
          layer_on(_NAV);
        } else {
            #ifdef AUDIO_ENABLE
              //PLAY_NOTE_ARRAY(close_encounters, false, 0);
            #endif
          layer_off(_NAV);
        }
        return false;
        break;


    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
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
          PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
    switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
        if (record->event.pressed) {
            return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
        }
        break;

        case 1: //¯\_(ツ)_/¯
            if (record->event.pressed) {
                return MACRO(I(10), D(LALT), T(0), T(0), T(A), T(F), U(LALT), T(BSLASH), D(LSHIFT), T(MINUS), T(9), U(LSHIFT), D(LALT), T(3), T(0), T(C), T(4), U(LALT), D(LSHIFT), T(0), T(MINUS), U(LSHIFT), T(SLASH), D(LALT), T(0), T(0), T(A), T(F), U(LALT), END);
            }
        break;
        case 2:
        if (record->event.pressed) {
            return MACRO(I(10), D(LSHIFT), T(7), U(LSHIFT), T(S), T(H), T(R), T(U), T(G), T(SCLN), END);
        }
    }
    return MACRO_NONE;
};
void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
        //PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
