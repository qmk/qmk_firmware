#include QMK_KEYBOARD_H
#include "keymap_plover.h"

extern keymap_config_t keymap_config;

// Keymap layers
enum planck_layers {
  BASE_QWERTY_LAYER,
  BASE_COLEMAK_LAYER,
  BASE_STENO_LAYER,
  LOWER_LAYER,
  RAISE_LAYER,
  NAVIGATION_LAYER,
  GUI_LAYER,
  KEYBOARD_LAYER
};

// Key aliases for legibility
#define ___x___ KC_NO

// Macros
enum planck_macros {
  LALT_BRACE,
  RALT_BRACE
};

// Dashes (macOS)
#define KC_NDSH LALT(KC_MINS)
#define KC_MDSH S(LALT(KC_MINS))

// Window manager keys
#define WM_FULL LALT(LGUI(KC_F))
#define WM_NEXT LCTL(LALT(LGUI(KC_RGHT)))
#define WM_PREV LCTL(LALT(LGUI(KC_LEFT)))
#define WM_NW   LCTL(LGUI(KC_LEFT))
#define WM_N    LALT(LGUI(KC_UP))
#define WM_NE   LCTL(LGUI(KC_RGHT))
#define WM_E    LALT(LGUI(KC_RGHT))
#define WM_SE   S(LCTL(LGUI(KC_RGHT)))
#define WM_S    LALT(LGUI(KC_DOWN))
#define WM_SW   S(LCTL(LGUI(KC_LEFT)))
#define WM_W    LALT(LGUI(KC_LEFT))
#define WM_CNTR LALT(LGUI(KC_C))

#define LT_NAVS LT(NAVIGATION_LAYER, KC_SCLN)
#define LT_NAVO LT(NAVIGATION_LAYER, KC_O)
#define LT_GUIL LT(GUI_LAYER, KC_LBRC)
#define LT_GUIR LT(GUI_LAYER, KC_RBRC)

// Special key codes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  STENO,
  LOWER,
  RAISE,
  PV_EXIT,
  PV_LOOK
};

//Tap Dance Declarations
enum {
  TD_ESC_GRV = 0
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Esc, twice for Backspace
  [TD_ESC_GRV]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV)
  // Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer (Qwerty)
   *                ,-----------------------------------------------------------------------.
   * Double tap 4 ~ | ESC | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | '   |
   *                |-----------------------------------------------------------------------|
   * Tap for Tab -- |Ctrl | A   | S   | D   | F   | G   | H   | J   | K   | L   |; Fn4|Ctrl | -- Tap for Enter
   *                |-----------------------------------------------------------------------|
   *   Tap for ( -- |Shift| Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |Shift| -- Tap for )
   *                |-----------------------------------------------------------------------|
   *   Tap for [ -- | Fn3 |Hyper| Alt |Super| Fn1 |   Space   | Fn2 |Super| Alt |Hyper| Fn3 | -- Tap for ]
   *                `-----------------------------------------------------------------------'
   *                        /                                                     /
   *   Tap for ] [ --------'-----------------------------------------------------'
   */
  [BASE_QWERTY_LAYER] = LAYOUT_planck_grid(
    TD(TD_ESC_GRV),  KC_Q,           KC_W,          KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,          KC_P,           KC_QUOT,
    MT(MOD_LCTL, KC_TAB),            KC_A,           KC_S,          KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,          LT_NAVS,        MT(MOD_RCTL, KC_ENT),
    KC_LSPO,         KC_Z,           KC_X,          KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,        KC_SLSH,        KC_RSPC,
    LT_GUIL,         ALL_T(KC_RBRC), M(LALT_BRACE), KC_LGUI, LOWER, KC_SPC, KC_BSPC, RAISE, KC_RGUI, M(RALT_BRACE), ALL_T(KC_LBRC), LT_GUIR
  ),

  /* Base layer (Colemak)
   *                ,-----------------------------------------------------------------------.
   *                |     | Q   | W   | F   | P   | G   | J   | L   | U   | Y   | ;   |     |
   *                |-----------------------------------------------------------------------|
   *                |     | A   | R   | S   | T   | D   | H   | N   | E   | I   |O Fn4|     |
   *                |-----------------------------------------------------------------------|
   *                |     | Z   | X   | C   | V   | B   | K   | M   |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |           |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [BASE_COLEMAK_LAYER] = LAYOUT_planck_grid(
    _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
    _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    LT_NAVO, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /* Base layer (Qwerty-Steno)
   *                ,-----------------------------------------------------------------------.
   *                |  #  |  #  |  #  |  #  |  #  |  #  |  #  |  #  |  #  |  #  |  #  |  #  |
   *                |-----------------------------------------------------------------------|
   *                |Look |     |  T  |  P  |  H  |           |  F  |  P  |  L  |  T  |  D  |
   *                | -up |  S  |-----+-----+-----|     *     |-----+-----+-----+-----+-----|
   *                |     |     |  K  |  W  |  R  |           |  R  |  B  |  G  |  S  |  Z  |
   *                |-----------------------------------------------------------------------|
   *                |Exit |     |     |  A  |  O  |           |  E  |  U  |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [BASE_STENO_LAYER] = LAYOUT_planck_grid(
    PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM,  PV_NUM,
    PV_LOOK, PV_LS,   PV_LT,   PV_LP,  PV_LH,  PV_STAR, PV_STAR, PV_RF,  PV_RP,  PV_RL,   PV_RT,   PV_RD,
    PV_LOOK, PV_LS,   PV_LK,   PV_LW,  PV_LR,  PV_STAR, PV_STAR, PV_RR,  PV_RB,  PV_RG,   PV_RS,   PV_RZ,
    PV_EXIT, ___x___, ___x___, PV_A,   PV_O,   _______, _______, PV_E,   PV_U,   ___x___, ___x___, ___x___
  ),

  /* Numeric layer
   *                ,-----------------------------------------------------------------------.
   * Application -- |D-Grv| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | #   |
   *      window    |-----------------------------------------------------------------------|
   *    switcher    |     | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   |     |
   *                |-----------------------------------------------------------------------|
   *                |     | -   | =   | `   | \   |     |ndash|mdash| ,   | .   | /   |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     | Backspace |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [LOWER_LAYER] = LAYOUT_planck_grid(
    LGUI(KC_GRV), KC_F1,          KC_F2,         KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,         KC_F10,         S(KC_3),
    MT(MOD_LCTL, KC_TAB),         KC_1,           KC_2,          KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,          KC_0,           MT(MOD_RCTL, KC_ENT),
    KC_LSPO,      KC_MINS,        KC_EQL,        KC_GRV,  KC_BSLS, ___x___, KC_NDSH, KC_MDSH, KC_COMM, KC_DOT,        KC_SLSH,        KC_RSPC,
    LT_GUIL,      ALL_T(KC_LBRC), M(LALT_BRACE), KC_LGUI, LOWER,   KC_BSPC, KC_BSPC, RAISE,   KC_RGUI, M(RALT_BRACE), ALL_T(KC_RBRC), LT_GUIR
  ),

  /* Symbol layer
   *                ,-----------------------------------------------------------------------.
   *                |     | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 | #   |
   *                |-----------------------------------------------------------------------|
   *                |     | !   | @   | #   | $   | %   | ^   | &   | *   | '   | "   |     | \
   *                |-----------------------------------------------------------------------|  |-- Mostly shifted version
   *                |     | _   | +   | ~   | |   |     |ndash|mdash| ,   | .   | /   |     | /    of lower layer
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |  Delete   |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [RAISE_LAYER] = LAYOUT_planck_grid(
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,     S(KC_3),
    _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), KC_QUOT, S(KC_QUOT), _______,
    _______, KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, ___x___, KC_NDSH, KC_MDSH, KC_COMM, KC_DOT,  KC_SLSH,    _______,
    _______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______,    _______
  ),

  /* Directional navigation layer
   *
   *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
   *                ,-----------------------------------------------------------------------.
   *                |     |     |     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |Home |PgUp |PgDn | End |Left |Down | Up  |Right|     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |           |     |     |     |     |     |
   *                `-----------------------------------------------------------------------'
   */
  [NAVIGATION_LAYER] = LAYOUT_planck_grid(
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,
    _______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, LT_NAVS, _______,
    _______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______,
    _______, _______, _______, _______, ___x___, ___x___, ___x___, ___x___, _______, _______, _______, _______
  ),

  /* GUI (window management/mouse/media controls) layer
   *
   *        Mouse keys -----/```````````````````\               /```````````````````\----- Window manager
   *                ,-----------------------------------------------------------------------.
   *                |     |Ms B2|Ms Up|Ms B1|Ms WD|     |     |Prev | NW  |  N  | NE  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Ms L |Ms Dn|Ms R |Ms WU|     |     |Full |  W  |Centr|  E  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Ms WL|Ms B3|Ms WR|     |     |     |Next | SW  |  S  | SE  |     |
   *                |-----------------------------------------------------------------------|
   *                |     |Prev |Play |Next |Brig-|   Sleep   |Brig+|Mute |Vol- |Vol+ |     |
   *                `-----------------------------------------------------------------------'
   *                        \___ Media ___/   \___ Screen/sleep __/   \___ Volume __/
   */
  [GUI_LAYER] = LAYOUT_planck_grid(
    _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, ___x___, ___x___, WM_PREV, WM_NW,   WM_N,    WM_NE,   _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, ___x___, ___x___, WM_FULL, WM_W,    WM_CNTR, WM_E,    _______,
    _______, KC_WH_L, KC_BTN3, KC_WH_R, ___x___, ___x___, ___x___, WM_NEXT, WM_SW,   WM_S,    WM_SE,   _______,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_SLCK, KC_SLEP, KC_SLEP, KC_PAUS, KC_MUTE, KC_VOLD, KC_VOLU, _______
  ),

  /* Keyboard settings layer
   *                ,-----------------------------------------------------------------------.
   *    Firmware -- |     |Reset|     |     |     |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *   Set layer -- |     |Qwert|Colem|Steno| ... |     |     |     |     |     |     |     |
   *                |-----------------------------------------------------------------------|
   *       Audio -- |     |Voic-|Voic+|Mus +|Mus -|MIDI+|MIDI-|     |     |Aud +|Aud -|     |
   *                |-----------------------------------------------------------------------|
   *                |     |     |     |     |     |  Toggle   |     |Toggl| BL- | BL+ |     |
   *                `-----------------------------------------------------------------------'
   *                                                    \_____________\_ Backlight _/
   */
  [KEYBOARD_LAYER] = LAYOUT_planck_grid(
    ___x___, RESET,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,
    ___x___, QWERTY,  COLEMAK, STENO,   ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,
    ___x___, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  ___x___, ___x___, AU_ON,   AU_OFF,  ___x___,
    ___x___, ___x___, ___x___, ___x___, LOWER,   BL_TOGG, BL_TOGG, RAISE,   BL_TOGG, BL_DEC,  BL_INC,  ___x___
  )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case LALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_LALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_LALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_LBRACKET);
          unregister_code(KC_LBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
    case RALT_BRACE:
      if (record->event.pressed) {
        register_mods(MOD_RALT);
        record->tap.interrupted = 0;
      } else {
        unregister_mods(MOD_RALT);

        if (record->tap.count && !record->tap.interrupted) {
          add_weak_mods(MOD_LSFT);
          register_code(KC_RBRACKET);
          unregister_code(KC_RBRACKET);
          del_weak_mods(MOD_LSFT);
        }

        record->tap.count = 0;
      }
      break;
  }
  return MACRO_NONE;
}

#ifdef AUDIO_ENABLE

float tone_startup[][2]   = SONG(STARTUP_SOUND);
float tone_qwerty[][2]    = SONG(QWERTY_SOUND);
float tone_colemak[][2]   = SONG(COLEMAK_SOUND);
float tone_plover[][2]    = SONG(PLOVER_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]    = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]   = SONG(GOODBYE_SOUND);

#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Send PHROPB ({PLOVER:RESUME}).
void plover_resume(void) {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RP);
  register_code(PV_RB);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RP);
  unregister_code(PV_RB);
}

// Send PHROF ({PLOVER:SUSPEND}).
void plover_suspend(void) {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RF);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RF);
}

// Send PHROBG ({PLOVER:LOOKUP}).
void plover_lookup(void) {
  register_code(PV_LP);
  register_code(PV_LH);
  register_code(PV_LR);
  register_code(PV_O);
  register_code(PV_RB);
  register_code(PV_RG);
  unregister_code(PV_LP);
  unregister_code(PV_LH);
  unregister_code(PV_LR);
  unregister_code(PV_O);
  unregister_code(PV_RB);
  unregister_code(PV_RG);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<BASE_QWERTY_LAYER);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<BASE_COLEMAK_LAYER);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case STENO:
      if (record->event.pressed) {
        layer_off(RAISE_LAYER);
        layer_off(LOWER_LAYER);
        layer_off(KEYBOARD_LAYER);
        layer_on(BASE_STENO_LAYER);
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        plover_resume();
      }
      return false;
    case PV_EXIT:
      if (record->event.pressed) {
        plover_suspend();
        layer_off(BASE_STENO_LAYER);
      }
      return false;
    case PV_LOOK:
      if (record->event.pressed) {
        plover_lookup();
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}
