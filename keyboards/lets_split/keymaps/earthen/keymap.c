#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_extras/keymap_german_ch.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 1
#define JOAN 2
#define MARC 0
#define SYMB 3
#define SYMBUS 4
#define LOWER 5
#define RAISE 6
#define CODE 7
#define ADJUST 8
#define MOUSE 9


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Macros
#define CLOSEFILE M(0)
#define COPYPATH M(1)
#define REVEAL M(2)
#define WORKINGFILES M(3)
#define MARK M(4)
#define DELETEMARK M(5)
#define SELECTOMARK M(6)

// Tap Dance declarations
enum {
  TD_Y_COPY = 0,
  TD_F_PASTE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_SPC),   LT(RAISE,KC_BSPC),  LT(LOWER,KC_DELT),  LT(RAISE,KC_ENT),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* JOAN
 * ,---------------------------------------------------------------------------------------.
 * | § /CODE|   ü  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   T  |   Z  |PtS/Code|
 * |--------+------+------+------+------+-------------+------+------+------+------+--------|
 * |Tab/SYMB|   A  |   O  |   E  |   I  |   U  |   H  |   D  |   R  |   N  |   S  |L/SYMB  |
 * |--------+------+------+------+------+------|------+------+------+------+------+--------|
 * |ä/Shift |   ö  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   -  |Shift/ESC|
 * |--------+------+------+------+------+------+------+------+------+------+------+--------|
 * | Ctrl   | Alt  | GUI  |MOUSE |Space/| Bksp/| Del/ |Enter/| Up   | Down | Left |Right   |
 * |        |      |      |      | RAISE| LOWER| RAISE| LOWER|      |      |      |        |
 * `---------------------------------------------------------------------------------------'
 */
[JOAN] = KEYMAP( \
  LT(CODE,CH_PARA),   CH_UE,          CH_COMM, CH_DOT,  CH_P,               TD(TD_Y_COPY),      TD(TD_F_PASTE),     CH_G,               CH_C,    CH_T,    CH_Z,    LT(CODE,KC_PSCR), \
  LT(SYMB, KC_TAB),  SFT_T(CH_A),    CH_O,    CH_E,    CH_I,               CH_U,               CH_H,               CH_D,               CH_R,    CH_N,    SFT_T(CH_S),    LT(SYMB,CH_L), \
  SFT_T(CH_AE),      CH_OE,          CH_Q,    CH_J,    CH_K,               CH_X,               CH_B,               CH_M,               CH_W,    CH_V,    CH_MINS, SFT_T(KC_ESC) , \
  KC_LCTL,           KC_LALT,        KC_LGUI, TT(MOUSE), LT(RAISE,KC_BSPC),  LT(LOWER,KC_SPC),  LT(RAISE,KC_ENT),  LT(LOWER,KC_DELT),   KC_UP, KC_DOWN, KC_LEFT,   KC_RGHT \
),
/* Marc
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |Right |Lower | Bksp |Space |Raise |  Up  | Down |  GUI |Ctrl |
 * `-----------------------------------------------------------------------------------'
 */

[MARC] = KEYMAP ( \
  LT(CODE, KC_ESC),  KC_QUOT, KC_COMM, KC_DOT,             KC_P,              KC_Y,             KC_F,             KC_G,              KC_C,    KC_R,    KC_L,    LT(CODE,KC_MINS),\
  LT(SYMBUS,KC_TAB), KC_A,    KC_O,    KC_E,               KC_U,              KC_I,             KC_D,             KC_H,              KC_T,    KC_N,    KC_S,    LT(SYMBUS,KC_SLSH), \
  KC_LSFT,           KC_SCLN, KC_Q,    KC_J,               KC_K,              KC_X,             KC_B,             KC_M,              KC_W,    KC_V,    KC_Z,    KC_RSFT, \
  KC_LCTL,           KC_LALT, KC_RGUI, TT(MOUSE), LT(LOWER,KC_BSPC), LT(RAISE,KC_ENT), LT(RAISE,KC_SPC), LT(LOWER,KC_DELT), KC_UP,   KC_DOWN, KC_RGUI, KC_LCTL \
                  ),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |ADJUST|     |      |      |  ESC  |COPY  |      | HOME |  UP  |  END |  *   |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |     |      |MOUSE2| MOUSE1|CUT   |      | LEFT | DOWN | RIGHT|   +  |      |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |      |      |DELETE| ENTER| PASTE|      |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[MOUSE] = KEYMAP( \
  TG(ADJUST),  XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC, LCTL(KC_C), XXXXXXX, KC_WH_U,    KC_MS_UP, KC_WH_D,XXXXXXX,_______, \
  _______, XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN1, LCTL(KC_X), KC_WH_L, KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT, KC_WH_R, _______, \
  _______, XXXXXXX, XXXXXXX, KC_DELT, KC_ENT, LCTL(KC_P), XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______ \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   {  |   }  |   |  |   ç |   "  |   '  |   &   |  *   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   `  |  ´   |   \  |   /  |   ?  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |   §  |   <  |   >  |      |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[SYMB] = KEYMAP( \
  _______, CH_EXLM,CH_AT,  CH_LCBR,CH_RCBR,CH_PIPE, CH_CELA,   CH_DQOT,   CH_QUOT,    CH_AMPR,    CH_PAST, _______, \
  _______,  CH_HASH,CH_DLR, CH_LPRN,CH_RPRN,CH_GRV,  CH_ACUT, CH_BSLS,   CH_SLSH,    CH_QST,    KC_PPLS,  _______, \
  _______, CH_PERC,CH_CARR,CH_LBRC,CH_RBRC,CH_TILD, CH_PARA, CH_LESS,   CH_MORE,    CH_PLUS,    KC_PSLS,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______ \
),

[SYMBUS] = KEYMAP( \
  _______, KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE, LSFT(KC_4),   LSFT(KC_2),   KC_QUOT,    KC_AMPR,    KC_ASTR, KC_BSPC, \
  _______,  KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV, ALGR(KC_MINS), KC_BSLS,   KC_SLSH,    KC_PAST,    KC_PPLS,  _______, \
  _______, KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD, LSFT(KC_DOT), LSFT(KC_COMMA), LSFT(KC_DOT) ,    KC_PLUS,    KC_PSLS,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |  F4 |  F3  |   F2 |  F1   |      |  DEL |   7  |   8  |   9  |  *   |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |  F8 |   F7 |   F6 |   F5  |      |      |   4  |   5  |   6  |   +  |  -   |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |  12  | F11  |  F10 |  F9  |      |   0  |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |  ,   |   .  |   =  |      |
 * `-----------------------------------------------------------------------------------'
 */
[LOWER] = KEYMAP( \
  _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   XXXXXXX, KC_DELT, KC_7,    KC_8,    KC_9,    KC_PAST,    _______, \
  _______, KC_F8,   KC_F7,   KC_F6,   KC_F5,   XXXXXXX, XXXXXXX, KC_4, KC_5,  KC_6, KC_PPLS, KC_PMNS, \
  _______, KC_F12,  KC_F11,  KC_F10,  KC_F9,   XXXXXXX,    KC_0, KC_1, KC_2, KC_3, KC_PSLS, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_PCMM, KC_DOT, CH_EQL, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |ADJUST| Lock|      |      |WinCls |      |INSERT| HOME |  UP  |  END |      |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |     | Run  |WinExp|AdrBar |      |TaskVw| LEFT | DOWN | RIGHT|      |      |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |      |      |PrvTab|NexTab|      |NexWin| Undo | Redo |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[RAISE] = KEYMAP( \
  TG(ADJUST), LGUI(CH_L), XXXXXXX, XXXXXXX,            LALT(KC_F4),  XXXXXXX, KC_INS,       KC_HOME,    KC_UP,      KC_END,   XXXXXXX, _______, \
  _______,    XXXXXXX,    LGUI(KC_R), KC_MYCM,            LCTL(CH_L),   XXXXXXX, LGUI(KC_TAB), KC_LEFT,    KC_DOWN,    KC_RIGHT, XXXXXXX, _______, \
  _______,    XXXXXXX,    XXXXXXX, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), XXXXXXX, LALT(KC_TAB), LCTL(CH_Z), LCTL(CH_Y), XXXXXXX,  XXXXXXX, _______, \
  _______,    _______,    _______,            _______, _______,      _______, _______,      _______,    _______,    _______,  _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |UnfolA|FoldA |UnfolS|FoldS |CloseF|Coment|F_Prev| Find |F_Next|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |SeltoM|DelMark| Mark |JFunc| LProj|G_Symb|G_File|LWorkF|G_Line|PeekDef|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Reveal|CopyPh|DeLine|S_Srnk|S_Expd| MCase| MWord|MRegex|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[CODE] =  KEYMAP( \
  _______, LCTL(LSFT(LALT(KC_A))),   LCTL(LSFT(LALT(KC_O))), LCTL(LSFT(LALT(KC_E))), LCTL(LSFT(LALT(KC_I))), CLOSEFILE, LCTL(CH_PARA), LSFT(KC_F3), LCTL(CH_F), KC_F3, XXXXXXX, _______, \
  _______, XXXXXXX, SELECTOMARK, DELETEMARK,   MARK,  LCTL(CH_M), LCTL(LALT(CH_P)),    LCTL(CH_R),          LCTL(KC_P),    WORKINGFILES,  LCTL(KC_G),      LALT(KC_F12), \
  _______, XXXXXXX, XXXXXXX, REVEAL,        COPYPATH,      LCTL(LSFT(CH_K)), LSFT(LALT(KC_LEFT)), LSFT(LALT(KC_RIGHT)),LALT(CH_C),    LALT(CH_W),    LALT(CH_R), _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),
/*
  Name 	Description
  RGB_TOG 	toggle on/off
  RGB_MOD 	cycle through modes
  RGB_HUI 	hue increase
  RGB_HUD 	hue decrease
  RGB_SAI 	saturation increase
  RGB_SAD 	saturation decrease
  RGB_VAI 	value increase
  RGB_VAD 	value decrease
*/
/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|LOnOff|LedMod|      |      |      |      | led- | led+ |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[ADJUST] =  KEYMAP( \
  _______, RESET , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, KC_DEL, \
  _______, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, TO(QWERTY),  TO(JOAN), TO(MARC),  XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)

};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_Y_COPY] = ACTION_TAP_DANCE_DOUBLE(CH_Y, LCTL(CH_C)),
  [TD_F_PASTE] = ACTION_TAP_DANCE_DOUBLE(CH_F, LCTL(CH_V))
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case 0: { // CLOSEFILE
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), U(LCTL), T(W), END);
      }
      break;
    }
    case 1: { // Copy Path of Active File
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), U(LCTL), T(P), END);
      }
      break;
    }
    case 2: { // Reveal Active File in Windows
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), U(LCTL), T(R), END);
      }
      break;
    }
    case 3: { // List Working Files
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), T(P), U(LCTL), END);
      }
      break;
    }
    case 4: { // Set Mark
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), T(SPC), U(LCTL), END);
      }
      break;
    }
    case 5: { // Remove Mark
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), T(G), U(LCTL), END);
      }
      break;
    }
    case 6: { // Mark til mark
      if (record->event.pressed){
        return MACRO( D(LCTL), T(K), T(A), U(LCTL), END);
      }
      break;
    }
  }
  return MACRO_NONE;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case LOWER:
      //COLOR 1
      break;
    case SYMB:
    case SYMBUS:
      //COLOR 2
      break;
    case RAISE:
      //COLOR 3
      break;
    case CODE:
      //COLOR 4
      break;
    default:
      // none
      break;
  }
  
};