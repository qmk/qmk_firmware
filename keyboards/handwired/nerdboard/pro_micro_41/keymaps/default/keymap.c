#include QMK_KEYBOARD_H

enum custom_layers {
    _QUERTY,
    _SYMBOL,
    _MOUSE,
    _FUNC
};

// layer keys
#define MOUSE   MO(_MOUSE)
#define SYMBOL  MO(_SYMBOL)
#define FUNC    MO(_FUNC)

// alternate keys
#define L       KC_LEFT
#define D       KC_DOWN
#define U       KC_UP
#define R       KC_RIGHT
#define PLUS    LSFT(KC_EQL)
#define STAR    LSFT(KC_8)
#define WS_L    G(KC_PGUP)
#define WS_R    G(KC_PGDN)
#define T_TAB_L LCTL(KC_PGUP)
#define T_TAB_R LCTL(KC_PGDN)
#define T_TAB_N LSFT(LCTL(KC_T))
#define T_TAB_C LSFT(LCTL(KC_W))

// layer tap
#define MO_TAB LT(MOUSE, KC_TAB)
#define SY_GRV LT(SYMBOL, KC_GRV)

#ifdef OLED_ENABLE
  char     splash_screen[36] = "NerdBoard V7 41 Key\n\nBy: Jon Hull";
  uint32_t timer             = 0;
  uint8_t  show_splash       = 1;


  static void regular_use(void) {
    oled_clear();
    oled_set_cursor(0, 0);

    oled_write("Layer: ", false);
    switch (get_highest_layer(layer_state)) {
      case _QUERTY:
        oled_write("QWERTY 41", false);
        break;
      case _SYMBOL:
        oled_write("SYMBOLS", false);
        break;
      case _MOUSE:
        oled_write("MOUSE", false);
        break;
      case _FUNC:
        oled_write("FUNCTION", false);
        break;
    }

    led_t led_state = host_keyboard_led_state();
    oled_write("\n\nMods:", false);

    uint8_t mod = get_mods();

    if (led_state.caps_lock)  { oled_write(" CAP", false); }
    if (mod & MOD_MASK_SHIFT) { oled_write(" SFT", false); }
    if (mod & MOD_MASK_CTRL)  { oled_write(" CTL", false); }
    if (mod & MOD_MASK_ALT)   { oled_write(" ALT", false); }
    if (mod & MOD_MASK_GUI)   { oled_write(" GUI", false); }

    return;
  }

  bool oled_task_user() {
    if (timer > 100) { regular_use(); }
    else { timer += 1; oled_write(splash_screen, false); }
    return false;
  }

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QUERTY] = LAYOUT(
    KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,       KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
    KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,       KC_H   , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_RSFT,
    KC_LALT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,       KC_N   , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_LCTL,
                             SYMBOL, MO_TAB, KC_SPC ,      SY_GRV , KC_ENT
  ),
  [_SYMBOL] = LAYOUT(
    _______,_______, KC_7  , KC_8  , KC_9  ,KC_LCBR,       KC_RCBR,KC_MINS, PLUS  , STAR  ,KC_SLSH,_______,
    KC_LSFT,_______, KC_4  , KC_5  , KC_6  ,KC_LBRC,       KC_RBRC,KC_BSPC, KC_DEL,KC_QUOT,KC_DQUO,KC_RSFT,
    KC_LALT, KC_0  , KC_1  , KC_2  , KC_3  ,KC_LPRN,       KC_RPRN, L     , D     , U     , R     ,KC_LCTL,
                             KC_EQL, FUNC  , KC_ESC,       FUNC   ,FUNC
  ),
  [_MOUSE] = LAYOUT(
    _______,T_TAB_C,T_TAB_N,_______,_______,_______,       _______,KC_BTN3,_______,_______,_______,_______,
    KC_LSFT,T_TAB_L,T_TAB_R, WS_L  , WS_R  ,_______,       _______,KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,KC_RSFT,
    KC_LALT,_______,_______,_______,_______,_______,       _______,KC_BTN4,KC_BTN5,_______,_______,KC_LCTL,
                            _______, FUNC  ,_______,       FUNC   ,_______
  ),
  [_FUNC] = LAYOUT(
    QK_BOOT,_______,KC_VOLU,_______,G(KC_L),_______,       _______, KC_INS,KC_PSCR,_______,_______,_______,
    KC_LSFT,_______,KC_MUTE,_______,_______,_______,       _______,KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,KC_RSFT,
    KC_LALT,_______,KC_VOLD,KC_HOME, KC_END,_______,       _______, G(L)  , G(D)  , G(U)  , G(R)  ,KC_LCTL,
                            _______,_______,_______,       _______,_______
  )
};
