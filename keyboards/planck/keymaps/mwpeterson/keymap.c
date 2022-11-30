// from <https://github.com/noahfrederick/dots/tree/master/planck

#include QMK_KEYBOARD_H
#include "keymap_plover.h"
#include "version.h"

extern keymap_config_t keymap_config;

// Keymap layers
enum planck_layers {
  QWERTY_LAYER,
  LOWER_LAYER,
  RAISE_LAYER,
  NAV_LAYER,
  GUI_LAYER,
  STENO_LAYER,
  ADJUST_LAYER
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

#define SFT_INS LSFT(KC_INS)

// Unicode
#ifdef UNICODEMAP_ENABLE
enum unicode_name {
  IBANG // ‽
};

const uint32_t PROGMEM unicode_map[] = {
  [IBANG]      = 0x0203D // ‽
};
#endif // UNICODEMAP_ENABLE

// Custom key codes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  STENO,
  PV_EXIT,
  PV_LOOK,
  SEND_VERSION,
  SEND_MAKE
};

#define LOWER MO(LOWER_LAYER)
#define RAISE MO(RAISE_LAYER)

#define GUI_L LT(GUI_LAYER, KC_LBRC)
#define GUI_R LT(GUI_LAYER, KC_RBRC)

#define NAV_SCLN LT(NAV_LAYER, KC_SCLN)
#define NAV_O    LT(NAV_LAYER, KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer (Qwerty)
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *                │  ⇥  │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  '  │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * Tap for Esc -- │  ⌃  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │; Nav│  ⌃  │ -- Tap for Enter
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *   Tap for ( -- │  ⇧  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  ⇧  │ -- Tap for )
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *   Tap for [ -- │ GUI │Hyper│  ⌥  │  ⌘  │  ↓  │   Space   │  ↑  │  ⌘  │  ⌥  │Hyper│ GUI │ -- Tap for ]
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   *                        /                                                     /
   *   Tap for ] [ --------'-----------------------------------------------------'
   */
  [QWERTY_LAYER] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,           KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,           KC_QUOT,
    CTL_T(KC_ESC), KC_A,           KC_S,    KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    NAV_SCLN,       CTL_T(KC_ENT),
    SC_LSPO,       KC_Z,           KC_X,    KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH,        SC_RSPC,
    GUI_L,         ALL_T(KC_RBRC), KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_RGUI, KC_RALT, ALL_T(KC_LBRC), GUI_R
  ),

  /* Numeric layer
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * Application -- │  `  │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │  #  │
   *      window    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *    switcher    │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │  -  │  +  │  `  │SFTIN│  :  │  |  │  ‽  │  ,  │  .  │  \  │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │     │     │     │     │ Backspace │     │     │     │     │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [LOWER_LAYER] = LAYOUT_planck_grid(
    KC_GRV,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  S(KC_3),
    _______,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______,  KC_MINS, KC_PLUS,  KC_GRV,  SFT_INS, KC_COLN, KC_PIPE, X(IBANG), KC_COMM, KC_DOT,  KC_BSLS, _______,
    _______,  _______, _______, _______, _______,  KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
  ),

  /* Symbol layer
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *                │  ~  │ F11 │ F12 │ F13 │ F14 │ F15 │ F16 │ F17 │ F18 │ F19 │ F20 │  #  │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  '  │  "  │     │ \
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤  |-- Mostly shifted version
   *                │     │  _  │  =  │  ~  │SFTIN│  :  │  |  │     │  ,  │  .  │  /  │     │ /    of lower layer
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │     │     │     │     │  Delete   │     │     │     │     │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RAISE_LAYER] = LAYOUT_planck_grid(
    S(KC_GRV), KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,     S(KC_3),
    _______,   S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), KC_QUOT, S(KC_QUOT), _______,
    _______,   KC_UNDS, KC_EQL,  KC_TILD, SFT_INS, KC_COLN, KC_PIPE, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH,    _______,
    _______,   _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______,    _______
  ),

  /* Directional navigation layer
   *
   *         Large movements -----/```````````````````\   /```````````````````\----- Vim-style arrow keys
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *                │     │     │     │     │     │     │     │     │     │     │     │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │     │Home │PgUp │PgDn │ End │  ←  │  ↓  │  ↑  │  →  │     │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │     │     │     │     │     │     │     │     │     │     │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │     │     │     │     │           │     │     │     │     │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [NAV_LAYER] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, NAV_SCLN, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______,
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,  _______
  ),

  /* GUI (window management/mouse/media controls) layer
   *
   *        Mouse keys -----/```````````````````\               /```````````````````\----- Window manager
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *                │     │Ms B2│Ms Up│Ms B1│Ms WD│     │     │Prev │ NW  │  N  │ NE  │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │Ms L │Ms Dn│Ms R │Ms WU│     │     │Full │  W  │Centr│  E  │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │Undo │ Cut │Copy │Paste│     │     │Next │ SW  │  S  │ SE  │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │     │Prev │Play │Next │     │   Sleep   │     │Mute │Vol- │Vol+ │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   *                        \___ Media ___/   \___ Screen/sleep __/   \___ Volume __/
   */
  [GUI_LAYER] = LAYOUT_planck_grid(
    _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, XXXXXXX, XXXXXXX, WM_PREV, WM_NW,   WM_N,    WM_NE,   _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, XXXXXXX, XXXXXXX, WM_FULL, WM_W,    WM_CNTR, WM_E,    _______,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX, WM_NEXT, WM_SW,   WM_S,    WM_SE,   _______,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_SLEP, KC_WAKE, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, _______
  ),

  /* Base layer (Qwerty-Steno)
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *                │  #  │  #  │  #  │  #  │  #  │  #  │  #  │  #  │  #  │  #  │  #  │  #  │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │Look │     │  T  │  P  │  H  │           │  F  │  P  │  L  │  T  │  D  │
   *                │ -up │  S  ├─────┼─────┼─────┤     *     ├─────┼─────┼─────┼─────┼─────┤
   *                │     │     │  K  │  W  │  R  │           │  R  │  B  │  G  │  S  │  Z  │
   *                ├─────┼─────┼─────┼─────┼─────┼───────────┼─────┼─────┼─────┼─────┼─────┤
   *                │Exit │     │     │  A  │  O  │           │  E  │  U  │     │     │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [STENO_LAYER] = LAYOUT_planck_grid(
    PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM,  PV_NUM,
    PV_LOOK, PV_LS,   PV_LT,   PV_LP,  PV_LH,  PV_STAR, PV_STAR, PV_RF,  PV_RP,  PV_RL,   PV_RT,   PV_RD,
    PV_LOOK, PV_LS,   PV_LK,   PV_LW,  PV_LR,  PV_STAR, PV_STAR, PV_RR,  PV_RB,  PV_RG,   PV_RS,   PV_RZ,
    PV_EXIT, XXXXXXX, XXXXXXX, PV_A,   PV_O,   KC_SPC,  KC_BSPC, PV_E,   PV_U,   XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* Keyboard settings layer
   *                ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   *    Firmware -- │     │Reset│Make │     │     │     │     │     │     │     │Vers │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *             -- │Qwert│     │     │     │     │     │     │     │     │     │     │     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   *       Audio -- │     │Voic-│Voic+│Mus +│Mus -│MIDI+│MIDI-│     │     │Aud +│Aud -│     │
   *                ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   *                │Steno│     │Swap │Norm │     │           │     │     │     │     │     │
   *                └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   *               Swap GUI/Alt _/________/             \_____________\_           _/
   */
  [ADJUST_LAYER] = LAYOUT_planck_grid(
    XXXXXXX, QK_BOOT, SEND_MAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SEND_VERSION, XXXXXXX,
    QWERTY,  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
    XXXXXXX, AU_PREV, AU_NEXT,   MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,       XXXXXXX,
    STENO,   XXXXXXX, AG_SWAP,   AG_NORM, LOWER,   XXXXXXX, XXXXXXX, RAISE,   XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX
  )
};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

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

void matrix_init_user(void) {
    set_unicode_input_mode(UNICODE_MODE_LINUX);
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LOWER_LAYER, RAISE_LAYER, ADJUST_LAYER);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case STENO:
      if (record->event.pressed) {
#ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(plover_song);
#endif
        layer_off(RAISE_LAYER);
        layer_off(LOWER_LAYER);
        layer_off(ADJUST_LAYER);
        layer_on(STENO_LAYER);
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
#ifdef AUDIO_ENABLE
        PLAY_SONG(plover_gb_song);
#endif
        plover_suspend();
        layer_off(STENO_LAYER);
      }
      return false;
    case PV_LOOK:
      if (record->event.pressed) {
        plover_lookup();
      }
      return false;
    case SEND_VERSION:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION " (" QMK_BUILDDATE ")");
      }
      return false;
    case SEND_MAKE:
      if (record->event.pressed) {
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":dfu\n");
      }
      return false;
  }
  return true;
}
