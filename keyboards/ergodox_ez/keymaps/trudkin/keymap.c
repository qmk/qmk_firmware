#include QMK_KEYBOARD_H
#include "version.h"


#include "tap.h"
#include "wrappers.h"
#include "print.h" 


#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define FN(km)  LM(5, km)


enum my_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _MOUSE,
 _FUNCTION,
};

#define MOUSE TT(_MOUSE)
#define NUMPAD TT(_NUMPAD)

#define MY_LOW TD(MOD_LOW)
#define MY_RAI TD(MOD_RAI)

#define LAYOUT_ergodox_pretty_base( \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
  ) \
  LAYOUT_ergodox_pretty_wrapper( \
      KC_GESC, ________________NUMBER_LEFT________________, KC_MINS,    KC_EQL, ________________NUMBER_RIGHT_______________,  KC_BSPACE,  \
      KC_TAB,  K11, K12, K13,      K14,     K15,    KC_LBRC,           KC_RBRC, K16,     K17,     K18,     K19,     K1A,  KC_BSLS,  \
      KC_DEL, K21, K22, K23,      K24,     K25,                                K26,     K27,     K28,     K29,     K2A,  KC_QUOT,  \
      KC_LSPO, K31, K32, K33,      K34,     K35,     MY_LOW,           MY_RAI,  K36,     K37,     K38,     K39,     K3A,  KC_RSPC,   \
      LCTL_T(KC_LBRC), LGUI_T(KC_RBRC), MY_PIPE,KC_PIPE,KC_UNDS,                      KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_GRAVE, \
                                                  KC_INS, MEH_T( KC_PGUP),   HYPR_T(KC_PGDOWN),KC_DEL,                         \
                                                           NUMPAD,                 TT(5),                                  \
                                KC_SPACE,LALT_T(KC_HOME), MY_LOW,           MY_RAI, RALT_T(KC_END), KC_ENTER     )       

#define LAYOUT_ergodox_pretty_base_wrapper(...)       LAYOUT_ergodox_pretty_base(__VA_ARGS__)







const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: COLEMAK layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC/` |   1  |   2  |   3  |   4  |   5  | - _  |           |  = + |   6  |   7  |   8  |   9  |   0  |  BkSp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  | [ {  |           |  ] } |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Lead   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |  O   |   '    |
 * |--------+------+------+------+------+------| OVER |           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  MEH | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Ins  | PgUp |       | PgDn | Del  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| Home |------|       |------|  End   |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [_COLEMAK] = LAYOUT_ergodox_pretty_base_wrapper(
      _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
      _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
      _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
),


    [_QWERTY] = LAYOUT_ergodox_pretty_base_wrapper(
         _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
         _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
         _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
),

    [_DVORAK] = LAYOUT_ergodox_pretty_base_wrapper(
         _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, 
         _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, 
         _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |  F1  |  F2  |   F3 |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | BKSP |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  INS |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | DEL  |      |      |      |      |      |      |      |   {  |   }  |   _  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |NUMPAD|  #   |  !   |  /   |  *   |ISO | |ISO > |   <  |   >  | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | F11  |      |      |      |      | F12  | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT_ergodox_pretty_base_wrapper(
       _________________LOWER_L1__________________, _________________LOWER_R1__________________,
       _________________LOWER_L2__________________, _________________LOWER_R2__________________,
       _________________LOWER_L3__________________, _________________LOWER_R3__________________
                     ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  ESC | C_F1 | C_F2 | C_F3 | C_F4 | C_F5 | C_F6 | C_F7 | C_F8 | C_F9 |C_F10 | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |      | BTN1 | BTN3 | BTN2 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      | up   |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | MS < | DN   | MS > |      |      |      | Prev | Next | Vol+ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | C_F11|      |             |      | C_F12| Stop | Vol- |Pause |
 * `-----------------------------------------------------------------------------------'
 */
    [_RAISE] = LAYOUT_ergodox_pretty_base_wrapper(
          _________________RAISE_L1__________________, _________________RAISE_R1__________________, 
          _________________RAISE_L2__________________, _________________RAISE_R2__________________, 
          _________________RAISE_L3__________________, _________________RAISE_R3__________________),

    [_ADJUST] = LAYOUT_ergodox_pretty_wrapper(
          _______, _________________FUNC_LEFT_________________, UC_MOD,                  _______, _________________FUNC_RIGHT________________, _______,
          KC_MAKE, _________________ADJUST_L1_________________, _______,                 _______, _________________FUNC_RIGHT________________, _______,
          _______, _________________ADJUST_L2_________________,                                   _________________ADJUST_R2_________________, _______,
          _______, _________________ADJUST_L3_________________, _______,                 _______, _________________ADJUST_R3_________________, _______,
          _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______,
                                          RGB_MOD,        HSV_0_255_255,                RGB_TOG,        RGB_SLD,
                                                         HSV_86_255_128,                HSV_27_255_255,
                              RGB_VAI,    RGB_VAD,       HSV_172_255_255,               HSV_215_255_128,RGB_HUD,        RGB_HUI
     ),
   


    [_NUMPAD] = LAYOUT_ergodox_pretty_wrapper(
            _______,_________________NUMPAD_1__________________,_______,                 _______, _________________NUMPAD_1__________________, _______,
            _______,_________________NUMPAD_2__________________,_______,                 _______, _________________NUMPAD_2__________________, _______,
            _______,_________________NUMPAD_3__________________,                                  _________________NUMPAD_3__________________, _______,
            _______, _______, _______NUMPAD_4________, _______, _______,                 _______, _______, _______NUMPAD_4________, _______, _______,
            _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______,
                                       KC_INS, MEH_T( KC_PGUP),   HYPR_T(KC_PGDOWN),KC_DEL,                        
                                              NUMPAD,                 TT(5),
                                KC_SPACE,LALT_T(KC_HOME), MY_LOW,           MY_RAI, RALT_T(KC_END), KC_ENTER  
        ),

//  LAYOUT_ergodox_pretty(
//  KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_MINUS,                                       KC_EQUAL,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPACE,
//  KC_TAB,         KC_Q,           KC_W,           KC_F,           KC_P,           KC_G,           KC_LBRACKET,                                    KC_RBRACKET,    KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCOLON,      KC_BSLASH,
//  LCTL_T(KC_BSPACE),KC_A,           KC_R,           KC_S,           KC_T,           KC_D,                                                                           KC_H,           KC_N,           KC_E,           KC_I,           KC_O,           KC_QUOTE,
//  KC_LSPO,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           NUMPAD,                                          MOUSE,          KC_K,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RSPC,
//  LCTL_T(KC_SLASH),LGUI_T(KC_KP_PLUS),LALT_T(KC_KP_ASTERISK),KC_PIPE,        KC_UNDS,                                                                                                        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_UP,          KC_GRAVE,
//                                                                                                  KC_INSERT,      MT(MOD_MEH, KC_PGUP),MT(MOD_HYPR, KC_PGDOWN),KC_DELETE,
//                                                                                                                  FN(MOD_LSFT),          TT(5),
//                                                                                  KC_SPACE,       LALT_T(KC_HOME),FN(MOD_LCTL),          FN(MOD_LALT),          RALT_T(KC_END), KC_ENTER
//),
/*  [_QWERTY] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_MINUS,                                       KC_EQUAL,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPACE,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_LBRACKET,                                    KC_RBRACKET,    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
    LCTL_T(KC_BSPACE),KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
    KC_LSPO,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           NUMPAD,                                          MOUSE,          KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RSPC,
    LCTL_T(KC_SLASH),LGUI_T(KC_KP_PLUS),LALT_T(KC_KP_ASTERISK),KC_PIPE,        KC_UNDS,                                                                                                        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_UP,          KC_GRAVE,
                                                                                                    KC_INSERT,      MT(MOD_MEH, KC_PGUP),MT(MOD_HYPR, KC_PGDOWN),KC_DELETE,
                                                                                                                    FN(MOD_LSFT),          TT(5),
                                                                                    KC_SPACE,       LCTL_T(KC_HOME),FN(MOD_LCTL),          FN(MOD_LALT),          RALT_T(KC_END), KC_ENTER
  ),
  [_MOUSE] = LAYOUT_ergodox_pretty(
    _______, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F11,                                         KC_F12,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_WWW_BACK,
    _______, _______, KC_MS_BTN1,     KC_MS_BTN3,     KC_MS_BTN2,     _______, _______,                                 LCTL(LSFT(KC_T)),_______, _______, _______, KC_LBRACKET,    KC_RBRACKET,    _______,
    _______, _______, KC_MS_LEFT,     KC_MS_UP,       KC_MS_RIGHT,    _______,                                                                 _______, LCTL(LSFT(KC_N)),_______, _______, KC_QUOTE,       _______,
    _______, _______, _______, KC_MS_DOWN,     _______, _______, _______,                                          _______, _______, _______, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_PAUSE,       _______,
    _______, _______, _______, _______, _______,                                                                                                 KC_MEDIA_STOP,  KC_AUDIO_VOL_DOWN,KC_MEDIA_PLAY_PAUSE,KC_AUDIO_VOL_UP,_______,
                                                                                                    KC_MS_ACCEL0,   _______, _______, LGUI(KC_L),
                                                                                                                    _______, _______,
                                                                                    _______, _______, _______, _______, _______, _______
  ),
  [_NUMPAD] = LAYOUT_ergodox_pretty(
    KC_NUMLOCK,     _______, _______, _______, _______, _______, _______,                                 _______, _______, KC_7,           KC_8,           KC_9,           KC_KP_PLUS,     _______,
    _______, _______, _______, _______, _______, _______, _______,                                 _______, _______, KC_4,           KC_5,           KC_6,           KC_KP_MINUS,    _______,
    _______, LCTL(KC_A),     _______, _______, _______, LCTL(KC_D),                                                                     _______, KC_1,           KC_2,           KC_3,           KC_KP_ASTERISK, _______,
    _______, KC_PC_UNDO,     KC_PC_CUT,      KC_PC_COPY,     KC_PC_PASTE,    _______, _______,                                 _______,          _______, KC_0,           KC_0,           KC_KP_DOT,      KC_KP_SLASH,    _______,
    _______, _______, _______, _______, _______,                                                                                                 _______, _______, _______, _______, KC_NUMLOCK,
                                                                                                    _______, _______, _______, _______,
                                                                                                                    _______, _______,
                                                                                    _______, _______, _______, _______, KC_CALCULATOR,  _______
  ),
  [_ADJUST] = LAYOUT_ergodox_pretty(
    KC_SYSTEM_WAKE, _______, _______, _______, _______, _______, DYN_REC_START2,                                 DYN_REC_START1, DYN_REC_STOP,   _______, _______, _______, _______, WEBUSB_PAIR,
    _______, QWERTY,          _______, _______, _______, _______, DYN_MACRO_PLAY2,                                DYN_MACRO_PLAY1,_______, _______, _______, _______, _______, RESET,
    _______, _______, _______, _______, AG_TOGG, _______,                                                                 _______, KC_MINUS,       KC_EQUAL,       KC_LBRACKET,    KC_RBRACKET,    KC_BSLASH,
    _______, ST_MACRO_0,     ST_MACRO_1,     COLEMAK,          _______, _______, _______,                                 _______, _______, KC_UNDS,        KC_PLUS,        KC_LCBR,        KC_RCBR,        KC_PIPE,
    _______, _______, _______, ST_MACRO_2,     ST_MACRO_3,                                                                                                     _______, KC_BRIGHTNESS_DOWN,_______, KC_BRIGHTNESS_UP,LED_LEVEL,
                                    RGB_MOD,        HSV_0_255_255,  RGB_TOG,        RGB_SLD,
                                                    HSV_86_255_128, HSV_27_255_255,
                    RGB_VAI,        RGB_VAD,        HSV_172_255_255,HSV_215_255_128,RGB_HUD,        RGB_HUI
  ),
  [_FUNCTION] = LAYOUT_ergodox_pretty(
    _______, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          _______,                                 _______, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         _______,
    _______, KC_F11,         KC_F12,         KC_F13,         KC_F14,         KC_F15,         _______,                                 _______, KC_F16,         KC_F17,         KC_F18,         KC_F19,         KC_F20,         _______,
    _______, KC_F21,         KC_F22,         KC_F23,         KC_F24,         _______,                                                                 _______, _______, _______, _______, _______, _______,
    KC_LSHIFT,      KC_MAC_UNDO,    KC_MAC_CUT,     KC_MAC_COPY,    KC_MAC_PASTE,   _______, _______,                                 _______, _______, _______, _______, _______, _______, _______,
    KC_LCTRL,       KC_LGUI,        KC_RALT,        _______, _______,                                                                                                 _______, _______, _______, _______, _______,
                                                                                                    _______, KC_MEH,         KC_HYPR,        _______,
                                                                                                                    _______, _______,
                                                                                    _______, _______, _______, _______, _______, _______
  ),
    */
};





extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
//  debug_enable=true;
//  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},
            {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255},
            {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255},
            {169,120,255}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},
            {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},
            {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},
            {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {134,255,213},
            {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255},
            {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},
            {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213} },

    [2] = { {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {35,255,255},
            {249,228,255}, {35,255,255}, {105,255,255}, {14,255,255},
            {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255},
            {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0},
            {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0},
            {0,0,0}, {0,0,0}, {141,255,233}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {243,222,234}, {243,222,234}, {243,222,234}, {134,255,213},
            {0,0,0}, {243,222,234}, {243,222,234}, {243,222,234}, {134,255,213},
            {0,0,0}, {243,222,234}, {243,222,234}, {243,222,234}, {134,255,213},
            {0,0,0}, {243,222,234}, {243,222,234}, {243,222,234}, {134,255,213},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255},
            {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255}, {205,255,255},
            {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217},
            {0,0,0}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 5:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_W) SS_DELAY(100) SS_TAP(X_Q)  SS_DELAY(100) SS_TAP(X_ENTER));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_Q) SS_DELAY(100) SS_LSFT(SS_TAP(X_1))  SS_DELAY(100) SS_TAP(X_ENTER));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SLASH) SS_DELAY(100) SS_LSFT(SS_TAP(X_8)) SS_DELAY(100) SS_TAP(X_SPACE));

    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_8)) SS_DELAY(100) SS_TAP(X_SLASH) SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_LEFT));

    }
    break;
  case RGB_SLD:
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false;
  case HSV_0_255_255:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(0,255,255);
    }
    return false;
  case HSV_86_255_128:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(86,255,128);
    }
    return false;
  case HSV_172_255_255:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(172,255,255);
    }
    return false;
  case HSV_27_255_255:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(27,255,255);
    }
    return false;
  case HSV_215_255_128:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(215,255,128);
    }
    return false;
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
#ifndef MAKE_BOOTLOADER
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
#endif
                send_string_with_delay_P(PSTR("qmk"), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    send_string_with_delay_P(PSTR(" flash "), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                } else {
                    send_string_with_delay_P(PSTR(" compile "), TAP_CODE_DELAY);
#endif
                }
                send_string_with_delay_P(PSTR("-kb " QMK_KEYBOARD " -km " QMK_KEYMAP), TAP_CODE_DELAY);
#ifdef RGB_MATRIX_SPLIT_RIGHT
                send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);
#    ifndef OLED_DRIVER_ENABLE
                send_string_with_delay_P(PSTR(" OLED_DRIVER_ENABLE=no"), TAP_CODE_DELAY);
#    endif
#endif
                send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
            }

            break;
  }
  return true;
}



uint32_t layer_state_set_user(uint32_t state) {

 
    state = update_tri_layer_state(state,  _LOWER, _RAISE, _ADJUST);
  uint8_t layer = biton32(state);



  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case _LOWER:
      ergodox_right_led_1_on();
      break;
    case _RAISE:
      ergodox_right_led_3_on();
      break;
    case _ADJUST:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case _FUNCTION:
      ergodox_right_led_2_on();
      break;
//  case _QWERTY:
//    ergodox_right_led_1_on();
//    ergodox_right_led_2_on();
//    ergodox_right_led_3_on();
//    break;
    default:
      break;
  }


  return state;
};



// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
//    [NUM_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, nl_finished, nl_reset, 275),
//    [MOD_LOW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mod_low_finished, mod_low_reset, 275),
    [MOD_LOW] = MOD_LAYER( 1,KC_SPACE, _LOWER, KC_RALT, KC_RSFT),
    [MOD_RAI] = MOD_LAYER( 2,KC_ENT, _RAISE, KC_RCTL, KC_RSFT),
    [LBRC_9] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_brc_finished, l_brc_reset, 275),
    [RBRC_0] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_brc_finished, r_brc_reset, 275),
    // Tap Dance definitions

      // Tap once for Escape, twice for Caps Lock
   [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),      
    [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT), 
      [TD_CUT] = ACTION_TAP_DANCE_DOUBLE(KC_X,RSFT(KC_DEL)),
     [TD_COPY] = ACTION_TAP_DANCE_DOUBLE(KC_C,LCTL(KC_INS)),
    [TD_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V,RSFT(KC_INS)),
    [TD_PIPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pipe_finished, pipe_reset)

};
