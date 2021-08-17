/* Copyright 2021 kuenhlee and Don Kjer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Layer shorthand
enum _layer {
    _WBL,
    _WFL,
    _WSL,
    _MBL,
    _MFL,
    _MSL
};

#ifndef DEFAULT_LAYOUT
# define DEFAULT_LAYOUT _WBL // Change to _MBL to boot into Mac layout.
#endif
#ifndef ALT_LAYOUT
# define ALT_LAYOUT     _MBL // Layout to display 'MR' led when active.
#endif

static bool win_key_locked = false;
static bool mac_media_locked = false;
static bool win_appkey_pressed = false;
static bool mac_fnkey_pressed = false;


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_TGUI = SAFE_RANGE,  // Toggle between GUI Lock or Unlock (Windows)
    KC_TMED,               // Toggle between Fx keys or Media keys (Mac)
    KC_WFN,                // Windows function key
    KC_MFN,                // Mac function key
    MO_WSL,                // Windows system key
    MO_MSL,                // Mac system key
    DF_W2MBL,              // Change layout from Windows to Mac
    DF_M2WBL               // Change layout from Mac to Windows
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _WBL: Windows Base Layer (Default Layer)
   * ,-----------------------------------------------------------.  ,--------------.
   * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
   * |-----------------------------------------------------------|  |--------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
   * |-----------------------------------------------------------|  |--------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
   * |-----------------------------------------------------------|  `--------------'
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| #|Ret |
   * |-----------------------------------------------------------|        ,----.
   * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
   * |-----------------------------------------------------------|   ,-------------.
   * |Ctrl|Gui |Alt |      Space            |Alt |Func |App|Ctrl |   |Lft| Dn |Rig |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_WBL] = LAYOUT_all( /* Windows Base Layer */
      KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,      KC_PSCR,  KC_SLCK,  KC_PAUS,
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,     KC_INS,   KC_HOME,  KC_PGUP,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,     KC_DEL,   KC_END,   KC_PGDN,
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
      KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,               KC_UP,
      KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_WFN,   KC_APP,   KC_RCTL,     KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  /* Keymap _WFL: Windows Function Layer
   * ,-----------------------------------------------------------.  ,--------------.
   * |   |Play|Stop|Prev|Next| |Mute|Vol+|Vol-|    | |  |  |  |  |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |  |    |    |    |
   * |-----------------------------------------------------------|  `--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |
   * |-----------------------------------------------------------|        ,----.
   * |     |  |   |   |   |   |   |   |   |   |   |   |          |        |    |
   * |-----------------------------------------------------------|   ,-------------.
   * |    |Lock|    |                       |    |Func |Sys|     |   |   |    |    |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_WFL] = LAYOUT_all( /* Windows First Layer */
      _______,            KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,               _______,
      _______,  KC_TGUI,  _______,                                _______,                                _______,  _______,  MO_WSL,   _______,     _______,  _______,  _______
  ),
  /* Keymap _WSL: Windows System Layer
   * ,-----------------------------------------------------------.  ,--------------.
   * |Reset |Sleep|     |     |Power| |  |  |  |  | |  |  |  |MAC|  |              |
   * |-----------------------------------------------------------|  |--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |  |    |    |    |
   * |-----------------------------------------------------------|  `--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |
   * |-----------------------------------------------------------|        ,----.
   * |     |  |   |   |   |   |   |   |   |   |   |   |          |        |    |
   * |-----------------------------------------------------------|   ,-------------.
   * |    |    |    |                       |    |Func |Sys|     |   |   |    |    |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_WSL] = LAYOUT_all( /* Windows Second / System Layer */
      RESET,              KC_SLEP,  XXXXXXX,  XXXXXXX,  KC_PWR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DF_W2MBL,    XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  DEBUG,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,               XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  _______,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  /* Keymap _MBL: Mac Base Layer (Alternate Layout)
   * ,-----------------------------------------------------------.  ,--------------.
   * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  | f13| f14| f15|
   * |-----------------------------------------------------------|  |--------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
   * |-----------------------------------------------------------|  |--------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
   * |-----------------------------------------------------------|  `--------------'
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| #|Ret |
   * |-----------------------------------------------------------|        ,----.
   * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
   * |-----------------------------------------------------------|   ,-------------.
   * |Ctrl|Alt |Gui |      Space            |Gui |Alt|Func |Ctrl |   |Lft| Dn |Rig |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_MBL] = LAYOUT_all( /* Mac Base Layer */
      KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,      KC_F13,   KC_F14,   KC_F15,
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,     KC_INS,   KC_HOME,  KC_PGUP,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,     KC_DEL,   KC_END,   KC_PGDN,
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
      KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,               KC_UP,
      KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RGUI,  KC_RALT,  KC_MFN,   KC_RCTL,     KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  /* Keymap _MFL: Mac Function Layer
   * ,-----------------------------------------------------------.  ,--------------.
   * |  |Bri-|Bri+|MCon|LPad| |  |  |Prv|Ply| |Nxt|Mute|Vol-|Vol+|  |TMed|    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |  |    |    |    |
   * |-----------------------------------------------------------|  `--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |
   * |-----------------------------------------------------------|        ,----.
   * |     |  |   |   |   |   |   |   |   |   |   |   |          |        |    |
   * |-----------------------------------------------------------|   ,-------------.
   * |    |    |    |                       |    |Sys|Func |     |   |   |    |    |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_MFL] = LAYOUT_all( /* Mac First Layer */
      _______,            KC_BRID,  KC_BRIU,  _______,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,     KC_TMED,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,               _______,
      _______,  _______,  _______,                                _______,                                _______,  MO_MSL,   _______,  _______,     _______,  _______,  _______
  ),
  /* Keymap _MSL: Mac System Layer
   * ,-----------------------------------------------------------.  ,--------------.
   * |Reset |   |    |     |Sleep| |  |  |  |  | |  |  |  |WIN|  |              |
   * |-----------------------------------------------------------|  |--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |  |    |    |    |
   * |-----------------------------------------------------------|  `--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |  |    |
   * |-----------------------------------------------------------|        ,----.
   * |     |  |   |   |   |   |   |   |   |   |   |   |          |        |    |
   * |-----------------------------------------------------------|   ,-------------.
   * |    |    |    |                       |    |Sys|Func |     |   |   |    |    |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_MSL] = LAYOUT_all( /* Mac Second / System Layer */
      RESET,              XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_SLEP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DF_M2WBL,    XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  DEBUG,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,               XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  _______,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX
  )
};

void unlock_win_key(void) {
    win_key_locked = false;
    mac_media_locked = false;
    writePinHigh(LED_WIN_LOCK_PIN);
}

void toggle_lock_win_key(void) {
    win_key_locked = !win_key_locked;
    writePin(LED_WIN_LOCK_PIN, !win_key_locked);
}

void toggle_lock_media_key(void) {
  mac_media_locked = !mac_media_locked;
  writePin(LED_WIN_LOCK_PIN, !mac_media_locked);
}

#ifdef CONSOLE_ENABLE
void dprint_global_layers(void) {
    dprint("Global Layers:");
    if (IS_LAYER_ON(_WFL)) { dprint(" _WFL"); }
    if (IS_LAYER_ON(_WSL)) { dprint(" _WSL"); }
    if (IS_LAYER_ON(_MFL)) { dprint(" _MFL"); }
    if (IS_LAYER_ON(_MSL)) { dprint(" _MSL"); }
    dprintf("\n");
}

void dprint_layers(layer_state_t state) {
    dprint("Layers:");
    if (IS_LAYER_ON_STATE(state, _WFL)) { dprint(" _WFL"); }
    if (IS_LAYER_ON_STATE(state, _WSL)) { dprint(" _WSL"); }
    if (IS_LAYER_ON_STATE(state, _MFL)) { dprint(" _MFL"); }
    if (IS_LAYER_ON_STATE(state, _MSL)) { dprint(" _MSL"); }
    dprintf("\n");
}
#endif

layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    dprintf("default_layer_state_set_user: 0x%x\n", state);
    dprint_global_layers();
#endif
    // Disable windows key lock on default layer transition.
    unlock_win_key();
    win_appkey_pressed = false;
    mac_fnkey_pressed = false;
    writePin(LED_MR_LOCK_PIN, !IS_LAYER_ON_STATE(state, ALT_LAYOUT));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    dprintf("layer_state_set_user: 0x%x\n", state);
    dprint_layers(state);
#endif
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TGUI:
            if (!record->event.pressed) {
                // Toggle GUI lock on key release
                toggle_lock_win_key();
            }
            break;
        case KC_TMED:
            // Only trigger when Fn key is also held down, to avoid accidental unlock.
            if (!mac_fnkey_pressed) { return false; }
            if (!record->event.pressed) {
                // Toggle Media Lock on key release
                toggle_lock_media_key();
            }
            break;
        case KC_LGUI:
            if (win_key_locked) { return false; }
            break;
        case KC_WFN:
            // Like MO(_WFL), but also enables _WSL if KC_APP is already pressed down.
            if (record->event.pressed) {
                layer_on(_WFL);
                if (win_appkey_pressed) {
                    // Also enable Secondary layer if App key is being held down.
                    win_appkey_pressed = false;
                    layer_on(_WSL);
                }
            } else {
                if (IS_LAYER_ON(_WFL)) { layer_off(_WFL); }
                if (IS_LAYER_ON(_MSL)) { layer_off(_MSL); }
            }
            break;
        case KC_APP:
            if (record->event.pressed) {
                // Don't actually press down the app menu key
                win_appkey_pressed = true;
            } else {
                if (IS_LAYER_ON(_WSL)) { layer_off(_WSL); }
                if (IS_LAYER_ON(_MFL)) { layer_off(_MFL); }
                if (win_appkey_pressed) {
                    win_appkey_pressed = false;
                    // Tap the KC_APP key on key release.
                    tap_code(KC_APP);
                }
            }
            return false;
            break;
        case KC_MFN:
            // Mac Fn key.  Emit Fn keycode, and also transition layers similar to KC_WFN.
            if (record->event.pressed) {
                mac_fnkey_pressed = true;
                layer_on(_MFL);
                // Also enable Secondary layer if Right-Alt key is being held down.
                if (get_mods() & MOD_BIT(KC_RALT)) {
                    layer_on(_MSL);
                }
            } else {
                mac_fnkey_pressed = false;
                if (!mac_media_locked) {
                    if (IS_LAYER_ON(_MFL)) { layer_off(_MFL); }
                    if (IS_LAYER_ON(_WSL)) { layer_off(_WSL); }
                }
            }
            break;
        case KC_RALT:
            // Disable MSL/WFL layer on key-up.
            if (!record->event.pressed) {
                if (IS_LAYER_ON(_MSL)) { layer_off(_MSL); }
                if (IS_LAYER_ON(_WFL)) { layer_off(_WFL); }
            }
            break;
        case MO_WSL:
            if (record->event.pressed) {
                layer_on(_WSL);
            } else {
                if (IS_LAYER_ON(_WSL)) { layer_off(_WSL); }
                if (IS_LAYER_ON(_MFL)) { layer_off(_MFL); }
            }
            break;
        case MO_MSL:
            if (record->event.pressed) {
                layer_on(_MSL);
            } else {
                if (IS_LAYER_ON(_MSL)) { layer_off(_MSL); }
                if (IS_LAYER_ON(_WFL)) { layer_off(_WFL); }
            }
            break;
        case DF_W2MBL:
            if (!record->event.pressed) {
                // Switch base layer, but preserve first/secondary layers.
                default_layer_set(1UL<<_MBL);
                layer_state_set(1UL<<_MFL | 1UL<<_MSL);
            }
            break;
        case DF_M2WBL:
            if (!record->event.pressed) {
                // Switch base layer, but preserve first/secondary layers.
                default_layer_set(1UL<<_WBL);
                layer_state_set(1UL<<_WFL | 1UL<<_WSL);
            }
            break;
        case RESET:
            if (record->event.pressed) {
                // Flash LEDs to indicate bootloader mode is enabled.
                on_all_leds();
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    default_layer_set(1UL<<DEFAULT_LAYOUT);
}

