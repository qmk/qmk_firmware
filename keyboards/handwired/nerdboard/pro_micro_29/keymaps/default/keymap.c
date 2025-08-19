/* Copyright 2025 Jon Hull, aka (@thelowprokill)
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

enum custom_layers {
    _GAME,
    _JONMAK,
    _JM_EXT,
    _SYMBOL,
    _MOUSE,
    _FUNC
};

// layer keys
#define JONMAK  TG(_JONMAK)
#define GJONMAK MO(_JONMAK)
#define JM_EXT  MO(_JM_EXT)
#define MOUSE   MO(_MOUSE)
#define SYMBOL  MO(_SYMBOL)
#define MOUSE   MO(_MOUSE)
#define T_GAME  TO(_GAME)
#define FUNC    MO(_FUNC)

// alternate keys
#define L       KC_LEFT 
#define D       KC_DOWN
#define U       KC_UP 
#define R       KC_RIGHT 
#define TERM    LCA(KC_T)
#define PLUS    LSFT(KC_EQL)
#define STAR    LSFT(KC_8)
#define WS_L    G(KC_PGUP)
#define WS_R    G(KC_PGDN)
#define T_TAB_L LCTL(KC_PGUP)
#define T_TAB_R LCTL(KC_PGDN)
#define T_TAB_N LSFT(LCTL(KC_T))
#define T_TAB_C LSFT(LCTL(KC_W))

// mod taps
#define CTL_ENT CTL_T(KC_ENT)
#define MT_A    SFT_T(KC_A)
#define MT_R    CTL_T(KC_R)
#define MT_S    ALT_T(KC_S)
#define MT_T    SFT_T(KC_T)

#define MTQ_A   SFT_T(KC_A)
#define MTQ_S   CTL_T(KC_S)
#define MTQ_D   ALT_T(KC_D)
#define MTQ_F   SFT_T(KC_F)

// layer tap
#define MO_TAB LT(MOUSE, KC_TAB)
#define SY_GRV LT(SYMBOL, KC_GRV)

#ifdef OLED_ENABLE
  #ifdef VERSION
    #if VERSION == 61
      char splash_screen[36] = "NerdBoard V6.1 29 Key\n\nBy: Jon Hull";
    #elif VERSION == 63
      char splash_screen[36] = "NerdBoard V6.3 29 Key\n\nBy: Jon Hull";
    #else 
      char splash_screen[34] = "NerdBoard V6 29 Key\n\nBy: Jon Hull";
    #endif
  #else
    char splash_screen[34] = "NerdBoard V6 29 Key\n\nBy: Jon Hull";
  #endif
  uint32_t timer             = 0;
  uint8_t  show_splash       = 1;
  
  
  static void regular_use(void) {
    oled_clear();
    oled_set_cursor(0, 0);
  
    oled_write("Layer: ", false);
    switch (get_highest_layer(layer_state)) {
      case _GAME:
        oled_write("GAME", false);
        break;
      case _JONMAK:
        oled_write("Jon MAC 29", false);
        break;
      case _JM_EXT:
        oled_write("Jon MAC Cont.", false);
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

void keyboard_pre_init_user(void) { layer_move(_JONMAK); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // needs a KC_R, and KC_F
  [_GAME] = LAYOUT(
    KC_TAB , KC_1  , KC_2  , KC_3  ,       KC_BTN3, KC_4  , KC_F  , JONMAK,
    KC_LSFT, KC_A  , KC_W  , KC_D  ,       KC_BTN4,KC_BTN5, KC_R  , SYMBOL,
    KC_LALT, KC_Q  , KC_S  , KC_E  ,       KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
            KC_ESC ,KC_LCTL, KC_SPC,       SYMBOL ,GJONMAK
  ),

  // decide on having KC_ENT or KC_ESC here
  [_JONMAK] = LAYOUT(
    KC_D   , KC_W  , KC_F  , KC_P  ,       KC_M  , KC_U  , KC_Y  ,KC_SCLN,
    MT_A   , MT_R  , MT_S  , MT_T  ,       KC_N  , KC_E  , KC_I  , KC_O  ,
    KC_G   , KC_X  , KC_C  , KC_V  ,       KC_H  , KC_J  , KC_K  , KC_L  ,
            CTL_ENT, MO_TAB, KC_SPC,       SY_GRV, JM_EXT
  ),

  [_JM_EXT] = LAYOUT(
    _______,_______,_______,KC_LCBR,       KC_RCBR,_______,_______,_______,
    KC_Z   , KC_Q  , KC_B  ,KC_LBRC,       KC_RBRC,KC_COMM, KC_DOT,KC_SLSH,
    _______,_______,KC_BSLS,KC_LPRN,       KC_RPRN,_______,_______,_______,
            KC_LCTL,KC_LSFT,KC_SPC ,       SYMBOL ,_______
  ),

  [_SYMBOL] = LAYOUT(
    _______, KC_7  , KC_8  , KC_9  ,       KC_MINS, PLUS  , STAR  ,KC_SLSH,
    KC_LSFT, KC_4  , KC_5  , KC_6  ,       KC_BSPC, KC_DEL,KC_QUOT,KC_DQUO,
    KC_0   , KC_1  , KC_2  , KC_3  ,       L      , D     , U     , R     ,
            KC_PEQL, FUNC  , KC_ESC,       FUNC   , FUNC
  ),

  [_MOUSE] = LAYOUT(
    T_TAB_C,T_TAB_N,_______,G(KC_T),       KC_BTN3,_______,_______,_______,
    T_TAB_L,T_TAB_R, WS_L  , WS_R  ,       KC_BTN4,KC_BTN5,KC_RCTL,_______,
    KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI,       KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
            _______, FUNC  ,_______,       FUNC   ,_______
  ),

  [_FUNC] = LAYOUT(
    QK_BOOT,KC_VOLU, KC_F5 ,G(KC_L),       KC_INS ,KC_PSCR,QK_BOOT, T_GAME,
    KC_LSFT,KC_MUTE, KC_F11, TERM  ,       KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,
    KC_LSFT,KC_VOLD,KC_HOME, KC_END,       G(L)   , G(D)  , G(U)  , G(R)  ,
            _______,_______,_______,       _______,_______
  )
};
