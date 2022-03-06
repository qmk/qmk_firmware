/* Copyright 2018 mtei
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

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define kc5(a,b,c,d,e) KC_##a, KC_##b, KC_##c, KC_##d, KC_##e

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _EUCALYN,
    _NUML,
    _NUMR,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  EUCALYN,
  NUML,
  NUMR,
  xEISU,
  xKANA,
  ZERO2,
  RGBRST
};

// clang-format off

//Macros
#define LT_NUML_SP  LT(_NUML,KC_SPC)
#define LT_NUMR_SP  LT(_NUMR,KC_SPC)
#define LT_RA_BSPC  LT(_RAISE,KC_BSPC)
#define LT_RA_ENT   LT(_RAISE,KC_ENT)
#define ___       _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty */
#define Q_____W_____E_____R_____T  kc5( Q, W, E, R, T )
#define Y_____U_____I_____O_____P  kc5( Y, U, I, O, P )
#define A_____S_____D_____F_____G  kc5( A, S, D, F, G )
#define H_____J_____K_____L__SCLN  kc5( H, J, K, L, SCLN )
#define Z_____X_____C_____V_____B  kc5( Z, X, C, V, B )
#define N_____M__COMM___DOT__SLSH  kc5( N, M, COMM, DOT, SLSH )
#define LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS  MO(_LOWER), MO(_LOWER), KC_CAPS, KC_LALT, KC_LGUI, LT_NUML_SP, LT_RA_BSPC
#define RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER     LT_RA_ENT,  LT_NUMR_SP, KC_RGUI, KC_RALT, KC_APP,  MO(_LOWER), MO(_LOWER)
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_wrapper(
       KC_ESC,    Q_____W_____E_____R_____T,               Y_____U_____I_____O_____P, KC_BSLS,
      KC_LCTL,    A_____S_____D_____F_____G,               H_____J_____K_____L__SCLN, KC_RCTL,
      KC_LSFT,    Z_____X_____C_____V_____B,               N_____M__COMM___DOT__SLSH, KC_RSFT,
      LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS, RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER
   ),

  /* Colemak */
#define Q_____W_____F_____P_____G  kc5( Q, W, F, P, G )
#define J_____L_____U_____Y__SCLN  kc5( J, L, U, Y, SCLN )
#define A_____R_____S_____T_____D  kc5( A, R, S, T, D )
#define H_____N_____E_____I_____O  kc5( H, N, E, I, O )
#define K_____M__COMM___DOT__SLSH  kc5( K, M, COMM, DOT, SLSH )
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | \    |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  | Ctrl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   K  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_wrapper(
       KC_ESC,    Q_____W_____F_____P_____G,               J_____L_____U_____Y__SCLN, KC_BSLS,
      KC_LCTL,    A_____R_____S_____T_____D,               H_____N_____E_____I_____O, KC_RCTL,
      KC_LSFT,    Z_____X_____C_____V_____B,               K_____M__COMM___DOT__SLSH, KC_RSFT,
      LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS, RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER
   ),

  /* Dvorak */
#define  QUOT__COMM___DOT_____P_____Y  kc5( QUOT, COMM, DOT, P, Y )
#define    F_____G_____C_____R_____L  kc5( F, G, C, R, L )
#define    A_____O_____E_____U_____I  kc5( A, O, E, U, I )
#define    D_____H_____T_____N_____S  kc5( D, H, T, N, S )
#define SCLN_____Q_____J_____K_____X  kc5( SCLN, Q, J, K, X )
#define    B_____M_____W_____V_____Z  kc5( B, M, W, V, Z )
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  | Ctrl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_wrapper(
      KC_ESC,  QUOT__COMM___DOT_____P_____Y,               F_____G_____C_____R_____L, KC_BSLS,
      KC_LCTL,    A_____O_____E_____U_____I,               D_____H_____T_____N_____S, KC_RCTL,
      KC_LSFT, SCLN_____Q_____J_____K_____X,               B_____M_____W_____V_____Z, KC_RSFT,
      LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS, RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER
   ),

  /* Eucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout) */
#define Q_____W__COMM___DOT__SCLN  kc5( Q, W, COMM, DOT, SCLN )
#define M_____R_____D_____Y_____P  kc5( M, R, D, Y, P )
#define A_____O_____E_____I_____U  kc5( A, O, E, I, U )
#define G_____T_____K_____S_____N  kc5( G, T, K, S, N )
#define Z_____X_____C_____V_____F  kc5( Z, X, C, V, F )
#define B_____H_____J_____L__SLSH  kc5( B, H, J, L, SLSH )
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  | Ctrl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |             |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALYN] = LAYOUT_wrapper(
       KC_ESC,    Q_____W__COMM___DOT__SCLN,               M_____R_____D_____Y_____P, KC_BSLS,
      KC_LCTL,    A_____O_____E_____I_____U,               G_____T_____K_____S_____N, KC_RCTL,
      KC_LSFT,    Z_____X_____C_____V_____F,               B_____H_____J_____L__SLSH, KC_RSFT,
      LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS, RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER
  ),

  /* Num */
#define EXLM__AT__HASH___DLR__PERC  kc5( EXLM, AT,   HASH, DLR,  PERC )
#define CIRC_AMPR_ASTR__LPRN__RPRN  kc5( CIRC, AMPR, ASTR, LPRN, RPRN )
#define _1_____2_____3_____4_____5  kc5( 1,    2,    3,    4,    5 )
#define _6_____7_____8_____9_____0  kc5( 6,    7,    8,    9,    0 )
#define F1____F2____F3____F4____F5  kc5( F1,  F2,   F3,   F4,    F5 )
#define F6____F7____F8____F9___F10  kc5( F6,  F7,   F8,   F9,    F10 )
#define ____z_____z_____z_____z      _______, _______, _______, _______
#define ____z_____z_____z            _______, _______, _______
#define ____z_____z                  _______, _______
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUML] = LAYOUT_wrapper(
    _______,   EXLM__AT__HASH___DLR__PERC,                 CIRC_AMPR_ASTR__LPRN__RPRN,  _______,
    _______,   _1_____2_____3_____4_____5,                 _6_____7_____8_____9_____0,  KC_F12,
    _______,   F1____F2____F3____F4____F5,                 F6____F7____F8____F9___F10,  KC_F11,
    _______, ____z_____z_____z_____z,____z_____z_____z,KC_SPC, ____z_____z_____z_____z, _______
   ),
  [_NUMR] = LAYOUT_wrapper(
    _______,   EXLM__AT__HASH___DLR__PERC,                 CIRC_AMPR_ASTR__LPRN__RPRN,  _______,
    _______,   _1_____2_____3_____4_____5,                 _6_____7_____8_____9_____0,  KC_F12,
    _______,   F1____F2____F3____F4____F5,                 F6____F7____F8____F9___F10,  KC_F11,
    _______, ____z_____z_____z_____z,KC_SPC, ____z_____z_____z,____z_____z_____z_____z, _______
   ),
  /* Lower */
#define XXXX__PAUS__SLCK___INS__XXXX   XXXXXXX, KC_PAUS, KC_SLCK, KC_INS,  XXXXXXX
#define XXXX___INS__SLCK__PAUS__XXXX   XXXXXXX, KC_INS,  KC_SLCK, KC_PAUS, XXXXXXX
#define HOME__XXXX____UP___DEL__PGUP   KC_HOME, XXXXXXX, KC_UP,   KC_DEL,  KC_PGUP
#define PGUP___DEL____UP__XXXX__HOME   KC_PGUP, KC_DEL,  KC_UP,   XXXXXXX, KC_HOME
#define END___LEFT__DOWN__RGHT__PGDN   kc5( END,  LEFT,  DOWN,    RGHT,    PGDN )
#define PGDN__LEFT__DOWN__RGHT___END   kc5( PGDN, LEFT,  DOWN,    RGHT,    END )
#define ______PSCR__________________   _______, KC_PSCR, _______, _______, _______
#define __________________PSCR______   _______, _______, _______, KC_PSCR, _______
#define ADJ___ADJ  MO(_ADJUST), MO(_ADJUST)
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Home |      | Up   |Delete| PgUp |             | PgUp |Delete| Up   |      | Home |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | End  | Left | Down | Right| PgDn |             | PgDn | Left | Down | Right| End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |Adjust|Adjust|      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_wrapper(
    XXXXXXX, XXXX__PAUS__SLCK___INS__XXXX,            XXXX___INS__SLCK__PAUS__XXXX, _______,
    _______, HOME__XXXX____UP___DEL__PGUP,            PGUP___DEL____UP__XXXX__HOME, _______,
    _______, END___LEFT__DOWN__RGHT__PGDN,            PGDN__LEFT__DOWN__RGHT___END, _______,
    _______, ______PSCR__________________, ADJ___ADJ, __________________PSCR______, _______
  ),
  /* Raise */
#define XXXX__XXXX__XXXX__UNDS__MINS   XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_MINS
#define  EQL__PLUS__XXXX__XXXX__XXXX   KC_EQL,  KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX__XXXX__XXXX__LCBR__LBRC   XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC
#define RBRC__RCBR__XXXX__XXXX__XXXX   KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX__XXXX__XXXX__TILD___GRV   XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,  KC_GRV
#define QUOT___DQT__XXXX__XXXX__XXXX   KC_QUOT, KC_DQT,  XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX______________XXXX         XXXXXXX, _______, _______, XXXXXXX
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | TAB  |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | EISU |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      | KANA |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  ~   |  `   |             |  '   |   "  |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_wrapper(
     KC_TAB, XXXX__XXXX__XXXX__UNDS__MINS,               EQL__PLUS__XXXX__XXXX__XXXX, XXXXXXX,
      xEISU, XXXX__XXXX__XXXX__LCBR__LBRC,              RBRC__RCBR__XXXX__XXXX__XXXX, xKANA,
    XXXXXXX, XXXX__XXXX__XXXX__TILD___GRV,              QUOT___DQT__XXXX__XXXX__XXXX, XXXXXXX,
        ADJ___ADJ, XXXX______________XXXX, ____z_____z, XXXX______________XXXX,  ADJ___ADJ
  ),
  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |      |Qwerty|Euclyn|Colemk|Dvorak|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,          AG_SWAP, XXXXXXX, QWERTY,  EUCALYN, COLEMAK,  DVORAK, \
    RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,          AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
   )
};

#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

static int current_default_layer;

uint32_t default_layer_state_set_kb(uint32_t state) {
    // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
    // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
    current_default_layer = state - 1;
    // 1<<_DVORAK  - 2 == 4 - 2 == _DVORAK (=2)
    if ( current_default_layer == 3 ) current_default_layer -= 1;
    // 1<<_EUCALYN - 5 == 8 - 5 == _EUCALYN (=3)
    if ( current_default_layer == 7 ) current_default_layer -= 4;
    return state;
}

void update_base_layer(int base)
{
    if( current_default_layer != base ) {
        eeconfig_update_default_layer(1UL<<base);
        default_layer_set(1UL<<base);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        update_base_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        update_base_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_DVORAK);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_EUCALYN);
      }
      return false;
      break;
    case xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
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
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
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
