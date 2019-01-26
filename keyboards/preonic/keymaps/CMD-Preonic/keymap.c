#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _GAME 3
#define _ARROW 12
#define _NUMPAD 13
#define _LOWER 14
#define _RAISE 15
#define _ADJUST 16

// Macro name shortcuts
#define QWERTY M(_QWERTY)
#define COLEMAK M(_COLEMAK)
#define DVORAK M(_DVORAK)
#define GAME M(_GAME)
#define ARROW M(_ARROW)
#define NUMPAD M(_NUMPAD)
#define LOWER M(_LOWER)
#define RAISE M(_RAISE)
#define M_BL 5

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    | Raise|   -  |  =  |   [   |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_1x2uC( \
  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC, \
  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLASH, \
  LT(_RAISE, KC_ENT), KC_A,    KC_S,    KC_D,    KC_F,                KC_G,    KC_H,    KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT, \
  KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT, \
  M(M_BL),   KC_LCTL, KC_LALT, KC_LGUI, LOWER,       LT(_LOWER, KC_SPC),       RAISE,   KC_MINUS, KC_EQUAL, KC_LBRC,  KC_RBRC  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    | Raise|   -  |  =  |   [   |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
  _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______  \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    | Raise|   -  |  =  |   [   |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______, \
  _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______, \
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______, \
  _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______  \
),

/* GAME
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | XXX | Lower |    Space    | Raise|   -  |  =   |   [  |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_preonic_1x2uC( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC,  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLASH,\
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,   \
  _______, _______, _______, XXXXXXX, _______,     _______,      _______, _______, _______,   _______,  _______   \
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   /  |   *  |   -  |   4  |   5  |   6  |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   7  |   8  |   9  |   +  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   4  |   5  |   6  |   +  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   1  |   2  |   3  | Enter|   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   0  |   0  |  .   | Enter| Lower|    Space    | Raise|   -  |  =   |   [  |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_1x2uC( \
  KC_ESC, KC_PSLS, KC_PAST, KC_PMNS,  _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_P7,  KC_P8,   KC_P9,   KC_PPLS,  _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_P4,  KC_P5,   KC_P6,   KC_PPLS,  _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_P1,  KC_P2,   KC_P3,   KC_PENT,  _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_P0,  KC_P0,   KC_PDOT, KC_PENT,  _______,     _______,      _______, _______, _______, _______, _______  \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   F1 |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute | BkSpc|   Up |  Del | Forwd| MBtn1|   MUp| MBtn2|   /  |   7  |   8  |  9   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right| Refr  MLeft|  MDn  |MRight|   *  |   4  |   5  |  6   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Vol+| Prev | Play | Next | Back |  MWDn| MBtn3| MWUp |  -   |   1  |  2   |  3   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Vol- |      |      |      |      |             |      |   +  | Enter|  0   |  .   |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_1x2uC( \
  KC_GRV,  KC_F1,    KC_F2,   KC_F3,    KC_F4,          KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL, \
  KC_MUTE, KC_BSPC,  KC_UP,   KC_DEL,   KC_WWW_FORWARD, KC_BTN1, KC_MS_U, KC_BTN2, KC_PSLS,  KC_P7,   KC_P8,  KC_P9,  \
  _______, KC_LEFT,  KC_DOWN, KC_RIGHT, KC_WWW_REFRESH, KC_MS_L, KC_MS_D, KC_MS_R, KC_PAST,  KC_P4,   KC_P5,  KC_P6,  \
  KC_VOLU, KC_MPRV,  KC_MPLY, KC_MNXT,  KC_WWW_BACK,    KC_WH_D, KC_BTN3, KC_WH_U, KC_PMNS,  KC_P1,   KC_P2,  KC_P3,  \
  KC_VOLD, _______,  _______, _______,  _______,           _______,       _______, KC_PPLS,  KC_PENT, KC_P0,  KC_PDOT \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bksp | PgUp |  Del |      |      |      | PgUp |  Up  | PgDn |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Home | PgDn |  End |      |      | Home | Left | Down | Right|   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Pause| Ins  |      |      | Print|Screen| End  |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_1x2uC( \
  KC_GRV, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_BSPC, \
  _______, KC_BSPC, KC_PGUP, KC_DEL,  _______, _______, _______, KC_PGUP, KC_UP,   _______,  _______, _______, \
  _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, \
  _______, KC_PAUSE, KC_INS, _______, KC_PSCR, KC_PSCR, _______, KC_END,  _______, _______,  _______, _______, \
  _______, _______, _______, _______,     _______,      _______, _______, _______, _______,  _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |qwerty|ColMak|Dvorak|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |AGNorm|AGSwap|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud On|AudOff|MidiOn|MdiOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus On|MusOff| Sleep| Wake | Arrow| Game |NUMPAD|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Reset   |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_1x2uC( \
  _______, _______,  QWERTY, COLEMAK,  DVORAK, _______,          _______,        _______, _______, _______, _______, _______, \
  _______, RESET,   _______, AG_NORM, AG_SWAP, _______,          _______,        _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, AU_ON,   AU_OFF,  MI_ON,            MI_OFF,         QWERTY,  COLEMAK,  DVORAK, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  KC_SYSTEM_SLEEP,  KC_SYSTEM_WAKE, ARROW,      GAME,  NUMPAD, _______, _______, \
  _______, _______, _______, _______, _______,              RESET,                _______, _______, _______, _______, _______  \
)


};

#ifdef AUDIO_ENABLE
float start_up[][2] = {
   MUSICAL_NOTE(_B5, 20),
   MUSICAL_NOTE(_B6, 8),
   MUSICAL_NOTE(_DS6, 20),
   MUSICAL_NOTE(_B6, 8),
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          break;
        case _COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          break;
        case _DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          break;
        case _GAME:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_GAME);
          }
          break;
        case _NUMPAD:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_NUMPAD);
          }
          break;
        case _ARROW:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_LOWER);
          }
          break;
        case _LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
        case _RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
        case M_BL:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(start_up);
  #endif
}

#ifdef AUDIO_ENABLE

void play_goodbye_tone(void)
{
  PLAY_SONG(goodbye);
  _delay_ms(150);
}

#endif
