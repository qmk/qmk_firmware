// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"
#include "keymap_colemak.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _QWOC,
  _LOWER,
  _RAISE,
  _PLOVER,
  _SUPERDUPER,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  QWOC,
  PLOVER,
  SUPERDUPER,
  MOUSE,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
  SDTOGG, // Toggle SuperDuper
};

enum functions {
  M_GUI_UNDS, // Simulate GUI_T(KC_UNDS)
  M_SFT_PO, // SFT_T(KC_LPRN)
};

// Timer for custom mod tap
static uint16_t m_gui_unds_timer;
static uint16_t m_sft_po_timer;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Narze : Custom Macros
#define HPR_ESC ALL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)
#define SFT_PO F(M_SFT_PO)
#define GUI_MINS GUI_T(KC_MINS)
#define GUI_UNDS F(M_GUI_UNDS)

// Combo : SuperDuper layer from S+D (R+S in Colemak)
#define SUPERDUPER_COMBO_COUNT 3
#define EECONFIG_SUPERDUPER_INDEX (uint8_t *) 19

enum process_combo_event {
  CB_SUPERDUPER,
};

const uint16_t PROGMEM superduper_combos[SUPERDUPER_COMBO_COUNT][3] = {
  [_QWERTY] = {KC_S, KC_D, COMBO_END},
  [_COLEMAK] = {KC_R, KC_S, COMBO_END},
  [_QWOC] = {CM_S, CM_D, COMBO_END},
};

combo_t key_combos[COMBO_COUNT] = {
  [CB_SUPERDUPER] = COMBO_ACTION(superduper_combos[_QWERTY]),
};

volatile bool superduper_enabled = true;

const uint16_t empty_combo[] = {COMBO_END};

void set_superduper_key_combos(void);
void clear_superduper_key_combos(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hp/Ec|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Sft/(| Z/Mo |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | SD-/ |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Rse/[| Ctrl | Alt  | GUI/_|Lower |    Space    |Raise | GUI/-| Alt  | Ctrl | Low/]|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {HPR_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {SFT_PO, LT(_MOUSE, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LT(_SUPERDUPER, KC_SLSH), SFT_ENT},
  {LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC,  RAISE,   GUI_MINS, KC_RALT, KC_RCTL,   LT(_LOWER, KC_RBRC)}
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hp/Ec|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Sft/(| Z/Mo |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  | SD-/ |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI/_|Lower |    Space    |Raise | GUI/-| Alt  | Ctrl | Low/]|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC},
  {HPR_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,       KC_QUOT},
  {SFT_PO, LT(_MOUSE, KC_Z),  KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  LT(_SUPERDUPER, KC_SLSH), SFT_ENT},
  {LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC,  RAISE,   GUI_MINS, KC_RALT, KC_RCTL,   LT(_LOWER, KC_RBRC)}
},

/* Qwerty on software Colemak : Useful for gaming with qwerty keymaps! */
[_QWOC] = {
  {KC_TAB,  CM_Q,    CM_W,    CM_E,    CM_R,    CM_T,    CM_Y,    CM_U,    CM_I,    CM_O,    CM_P,    KC_BSPC},
  {HPR_ESC, CM_A,    CM_S,    CM_D,    CM_F,    CM_G,    CM_H,    CM_J,    CM_K,    CM_L,    CM_SCLN, KC_QUOT},
  {SFT_PO, LT(_MOUSE, CM_Z),    CM_X,    CM_C,    CM_V,    CM_B,    CM_N,    CM_M,    CM_COMM, CM_DOT,  LT(_SUPERDUPER, CM_SLSH), SFT_ENT},
  {LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC,  RAISE,   GUI_MINS, KC_RALT, KC_RCTL,   LT(_LOWER, KC_RBRC)}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |     |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |     |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
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

/* SuperDuper : https://gist.github.com/narze/861e2167784842d38771
 * /-----------------------------------------------------------------------------------\
 * |      |      |      |      |      |      |      |      |  T←  |  T→  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Alt  | [SuperDuper]| Bksp | Gui  |  ←   |  ↓   |   ↑  |  →   | Del  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |   Shift     |      |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_SUPERDUPER] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, S(LGUI(KC_LBRC)), S(LGUI(KC_RBRC)), _______, _______},
  {_______, KC_LALT, _______, _______, KC_BSPC, KC_LGUI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, KC_LSFT, KC_LSFT, _______, _______, _______, _______, _______}
},

/* Mouse
 * /-----------------------------------------------------------------------------------\
 * |      |      |  S↑  |  M↑  |  S↓  |      |      |      |  S↑  |  S↓  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  M←  |  M↓  |  M→  |      |  M←  |  M↓  |  M↑  |  M→  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |[Mouse|      |      |      |  M3  |  M3  |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |  M2  |  LeftClick  |  M2  |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_MOUSE] = {
  {_______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______, _______, KC_WH_U, KC_WH_D, _______, _______},
  {_______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______},
  {_______, _______, _______, _______, _______, KC_BTN3, KC_BTN3, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|QwOnCo|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|SDtogg|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, QWOC,    PLOVER,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  SDTOGG,  _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float tone_startup[][2]    = SONG(STARTUP_SOUND);
  float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
  float tone_qwoc[][2]       = SONG(DVORAK_SOUND);
  float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
  float tone_plover[][2]     = SONG(PLOVER_SOUND);
  float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
  float tone_coin[][2]       = SONG(COIN_SOUND);
  float tone_sonic_ring[][2] = SONG(SONIC_RING);

  float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);
  float tone_superduper[][2] = SONG(SUPER_DUPER_SOUND);
#endif

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

        key_combos[CB_SUPERDUPER].keys = superduper_combos[_QWERTY];
        eeprom_update_byte(EECONFIG_SUPERDUPER_INDEX, _QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);

        key_combos[CB_SUPERDUPER].keys = superduper_combos[_COLEMAK];
        eeprom_update_byte(EECONFIG_SUPERDUPER_INDEX, _COLEMAK);
      }
      return false;
      break;
    case QWOC:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwoc, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWOC);

        key_combos[CB_SUPERDUPER].keys = superduper_combos[_QWOC];
        eeprom_update_byte(EECONFIG_SUPERDUPER_INDEX, _QWOC);
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
    case SDTOGG:
      if (record->event.pressed) {
        superduper_enabled = !superduper_enabled;

        if (superduper_enabled) {
          set_superduper_key_combos();

          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_sonic_ring, false, 0);
          #endif
        } else {
          clear_superduper_key_combos();

          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_coin, false, 0);
          #endif
        }
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

void matrix_setup(void) {
  set_superduper_key_combos();
}

void set_superduper_key_combos(void) {
  uint8_t layer = eeprom_read_byte(EECONFIG_SUPERDUPER_INDEX);

  switch (layer) {
    case _QWERTY:
    case _COLEMAK:
    case _QWOC:
      key_combos[CB_SUPERDUPER].keys = superduper_combos[layer];
      break;
  }
}

void clear_superduper_key_combos(void) {
  key_combos[CB_SUPERDUPER].keys = empty_combo;
}

void matrix_scan_user(void) {
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
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

// Combos

void process_combo_event(uint8_t combo_index, bool pressed) {
  if (pressed) {
    switch(combo_index) {
      case CB_SUPERDUPER:
        layer_on(_SUPERDUPER);

        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_superduper, false, 0);
        #endif
        break;
    }
  } else {
    layer_off(_SUPERDUPER);
    unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)); // Sometimes mods are held, unregister them
  }
}

// Macros

const uint16_t PROGMEM fn_actions[] = {
  [M_GUI_UNDS] = ACTION_MACRO_TAP(M_GUI_UNDS),
  [M_SFT_PO] = ACTION_MACRO_TAP(M_SFT_PO),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  bool tap_not_interrupted = record->tap.count > 0 && !record->tap.interrupted;

  switch(id) {
    // Hold for LGUI, tap for Underscore
    case M_GUI_UNDS:
      if (record->event.pressed) {
        m_gui_unds_timer = timer_read();

        if (!tap_not_interrupted) {
          register_mods(MOD_BIT(KC_LGUI));
        }
      } else {
        if (tap_not_interrupted && timer_elapsed(m_gui_unds_timer) < TAPPING_TERM) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_superduper, false, 0);
          #endif

          add_weak_mods(MOD_BIT(KC_LSFT));
          send_keyboard_report();
          register_code(KC_MINS);
          unregister_code(KC_MINS);
          del_weak_mods(MOD_BIT(KC_LSFT));
          send_keyboard_report();
          record->tap.count = 0;  // ad hoc: cancel tap
        } else {
          unregister_mods(MOD_BIT(KC_LGUI));
        }
      }
      break;
    // Hold for LSHIFT, tap for Parens open
    case M_SFT_PO:
      if (record->event.pressed) {
        m_sft_po_timer = timer_read();

        if (!tap_not_interrupted) {
          register_mods(MOD_BIT(KC_LSFT));
        }
      } else {
        if (tap_not_interrupted && timer_elapsed(m_sft_po_timer) < TAPPING_TERM) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_superduper, false, 0);
          #endif

          record->tap.count = 0;
          return MACRO(D(RSFT), T(9), U(RSFT), END);
        } else {
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      break;
  }
  return MACRO_NONE;
};
