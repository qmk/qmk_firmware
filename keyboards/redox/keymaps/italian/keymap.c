#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.            ,------------------------------------------------.
 * |\-Lyr2|   1  |   2  |   3  |   4  |   5  | Lyr1 |            | Lyr1 |   6  |   7  |   8  |   9  |   0  |'-Lyr2|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  [   |            |   ]  |   Y  |   U  |   I  |   O  |   P  |   è  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  | PgUp |            | End  |   H  |   J  |   K  |   L  |   ò  |   à  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | PgDn |            | Home |   N  |   M  |   ,  |   .  |   ù  |-(Sft)|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * |<(Gui)|   +  |   -  |*(Alt)|/(Ctr)|Bcksp | Del  |            |Enter |Space |ì(AlG)| Left | Down |  Up  | Right|
 * `------------------------------------------------'            `------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----+----.                                                         ,----+----+----+----+----+----+----.
     LT(_NAV, KC_GRV) , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,MO(_SYMB),                           MO(_SYMB), KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,LT(_NAV, KC_MINS),
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,RALT(KC_LBRC),                            RALT(KC_RBRC) , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_LBRC,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_ESC , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , LT(_ADJUST, KC_PGUP),                                 LT( _ADJUST, KC_END) , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_PGDN,                                      KC_HOME , KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_BSLASH,RSFT_T(KC_SLSH),
  //|----+----+----+----+----+----+----|                                                         |----+----+----+----+----+----+----|
     LGUI_T(KC_NONUS_BSLASH),KC_PPLS,KC_PMNS,LALT_T(KC_PAST),LCTL_T(KC_PSLS),KC_BSPC,KC_DEL ,                     KC_ENT , KC_SPC, RALT_T(KC_EQL),KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`----+----+----+----+----+----+----'                                                         `----+----+----+----+----+----+----'
  ),

/* Symbols
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |      |      |      |      |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   #  |   $  |   [  |   ]  |   ~  |      |      |      |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   (  |   )  |   `  |      |      |      |      |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   0  |   0  |   .  |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */

  [_SYMB] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, 
    _______, KC_EXLM, RALT(KC_SCLN), RALT(KC_LCBR), RALT(KC_RCBR), KC_TILD, _______,          _______, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX, 
    _______, RALT(KC_QUOT), KC_DLR , RALT(KC_LBRC), RALT(KC_RBRC), RALT(KC_EQL), _______,     _______, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX, 
    _______, KC_PERC, LSFT(KC_EQL) , LSFT(KC_8), LSFT(KC_9), RALT(KC_MINS), _______,          _______, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX, 
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, KC_KP_0, KC_KP_0, KC_PDOT, XXXXXXX, XXXXXXX 
  ),

/* Navigation
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |MOUS_U|      |WHEL_U|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |MOUS_L|MOUS_D|MOUS_R|WHEL_D|      |      |      |      | LEFT | DOWN |  UP  |RIGHT |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |MOUS_1|MOUS_2|      |      |      |      |      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
    XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, _______,                            _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
    XXXXXXX, RESET  , RGB_M_P, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,                            RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, KC_DEL,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

