// KEYCODE DEFINITIONS
#define NO_CHNG KC_TRNS // Note for me for keys I need to leave as Pass-through

#define FW_CAPS LT(_FUNCWIN, KC_CAPS) // _FUNCWIN when held, Caps Lock when tapped
#define FM_CAPS LT(_FUNCMAC, KC_CAPS) // _FUNCMAC when held, Caps Lock when tapped
#define Q2_CAPS LT(_FUNCQ2, KC_CAPS)  // _FUNCQ2 when held, Caps Lock when tapped

#define WN_SALL LCTL(KC_A)       // Windows/Linux Select All
#define WN_UNDO LCTL(KC_Z)       // Windows/Linux Undo
#define WN_CUT  LCTL(KC_X)       // Windows/Linux Cut
#define WN_COPY LCTL(KC_C)       // Windows/Linux Copy
#define WN_PSTE LCTL(KC_V)       // Windows/Linux Paste

#define MC_PSCR LGUI(LSFT(KC_3)) // MacOS Print Screen (Command + Shift + 3)
#define MC_HOME LGUI(KC_LEFT)    // MacOS Home (Command + Left Arrow)
#define MC_END  LGUI(KC_RGHT)    // MacOS End (Command + Right Arrow)
#define MC_SALL LGUI(KC_A)       // MacOS Select All
//#define MC_UNDO LGUI(KC_Z)       // MacOS Undo // replaced by macro
#define MC_CUT  LGUI(KC_X)       // MacOS Cut
#define MC_COPY LGUI(KC_C)       // MacOS Copy
//#define MC_PSTE LGUI(KC_V)       // MacOS Paste // replaced by macro


// MACRO DEFINITIONS
enum custom_keycodes {
  F_CAPS = SAFE_RANGE,
  M_WIN,
  M_MAC,
  T_L3DED,
  G_PUSH,
  G_FTCH,
  G_COMM,
  G_RST,
  G_C10R,
  G_BRCH,
  SIGNA,
  GO_Q2,
  Q2_ON,
  Q2_OFF,
  Q2_ESC,
  Q2_GRV,
  MC_UNDO,
  MC_PSTE
};


//define modifiers
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK   (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK    (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK    (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t modifiers = get_mods();
  switch(keycode) {
    // these are our macros!
    case F_CAPS:
      /*
        Objective: write a macro that checks the current layers that are
        enabled, and activates the appropriate function layer.
      */
      if ( biton32(layer_state) == _MAC ) {
        if (record->event.pressed) {
          layer_on(_FUNCMAC);
        } else {
          layer_off(_FUNCMAC);
        }
      } else if ( biton32(layer_state) == _WIN ) {
        if (record->event.pressed) {
          layer_on(_FUNCWIN);
        } else {
          layer_off(_FUNCWIN);
        }
      };
      return false; break;
    case M_WIN:
      if (record->event.pressed) {
        layer_move(BASE); // TO(_DVORAK);
        layer_on(_WIN);
      };
      return false; break;
    case M_MAC:
      if (record->event.pressed) {
        layer_move(BASE); // TO(_DVORAK);
        layer_on(_MAC);
      };
      return false; break;
    case T_L3DED:
      if (record->event.pressed) {
        SEND_STRING("lavak3DED ");
      };
      return false; break;
    case G_PUSH:
      if (record->event.pressed) {
        SEND_STRING("git push origin ");
      };
      return false; break;
    case G_FTCH:
      if (record->event.pressed) {
        SEND_STRING("git fetch upstream");
      };
      return false; break;
    case G_COMM:
      if (record->event.pressed) {
        SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
        layer_off(_MACROS);
      };
      return false; break;
    case G_RST:
      if (record->event.pressed) {
        SEND_STRING("git histt -n 10" SS_TAP(X_ENTER) "git reset --soft ");
        layer_off(_MACROS);
      };
      return false; break;
    case G_C10R:
      if (record->event.pressed) {
        SEND_STRING("cf/");
        layer_off(_MACROS);
      };
      return false; break;
    case G_BRCH:
      if (record->event.pressed) {
        SEND_STRING("$(git branch-name)");
        layer_off(_MACROS);
      };
      return false; break;
    case SIGNA:
      if (record->event.pressed) {
        SEND_STRING("\\- @noroadsleft" SS_TAP(X_ENTER));
        layer_off(_MACROS);
      };
      return false; break;
    case GO_Q2:
      if (record->event.pressed) {
        //default_layer_set(_QWERTY);
        layer_move(_QWERTY); // TO(_QWERTY);
        layer_on(_QUAKE2);
        //layer_off(_SYSTEM);
      };
      return false; break;
    case Q2_ON:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER));
        layer_on(_DVORAK);
        layer_on(_QUAKE2_DVORAK);
      };
      return false; break;
    case Q2_OFF:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER));
        layer_move(_QWERTY); // TO(_QWERTY);
        layer_on(_QUAKE2);
      };
      return false; break;
    case Q2_ESC:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE));
        layer_move(_QWERTY); // TO(_QWERTY);
        layer_on(_QUAKE2);
      };
      return false; break;
    case Q2_GRV:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_GRAVE));
        layer_on(_DVORAK);
        layer_on(_QUAKE2_DVORAK);
        layer_on(_QUAKE2_CONSOLE);
      };
      return false; break;
    case MC_UNDO:
      if (record->event.pressed) {
        if ( modifiers & MODS_SHIFT_MASK ) {
          register_code(KC_LSFT);
          register_code(KC_LGUI);
          SEND_STRING("z");
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        } else {
          register_code(KC_LGUI);
          SEND_STRING("z");
          unregister_code(KC_LGUI);
        }
      };
      return false; break;
    case MC_PSTE:
      if (record->event.pressed) {
        if ( modifiers & MODS_SHIFT_MASK ) {
          register_code(KC_LSFT);
          register_code(KC_LGUI);
          register_code(KC_LALT);
          SEND_STRING("v");
          unregister_code(KC_LALT);
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        } else {
          register_code(KC_LGUI);
          SEND_STRING("v");
          unregister_code(KC_LGUI);
        }
      };
      return false; break;
  } // switch()
  return true;
};
