/* Copyright 2018 darm
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _LMOUSE 3
#define _RMOUSE 4
#define _EMOJI 5

enum emoji_map {
  UNAM, // unamused 😒
  HEYE, // smiling face with heart shaped eyes 😍
  OK, // ok hand sign 👌
  SMIR, // smirk 😏
  PRAY, // pray 🙏
  CELE, // celebration 🙌
  COOL, // smile with sunglasses 😎
  EYES, // eyes
  THNK, // BIG THONK
  NAIL, // Nailcare
  SOS, // Vuile sos
  REDB, // Red B
  HNDR, // 100
  MONY,
  FIRE,
  CAR,
  BUTT,
  BNIS,
  CUM,
  CLAP,
  TRIU, // Fart from nose
  SCRM,
  VOMI,
  DTIV, // Detective
  EXPL, // Brainsplosion
  HAIR, // Haircut
  DANC, // Salsa dancer
  STRN, // Stronk
  LEFT, // Point Left
  RGHT, // Point Right
};

const uint32_t PROGMEM unicode_map[] = {
  [UNAM] = 0x1F612,
  [HEYE] = 0x1f60d,
  [OK]   = 0x1F44C,
  [SMIR] = 0x1F60F,
  [PRAY] = 0x1F64F,
  [CELE] = 0x1F64C,
  [COOL] = 0x1F60E,
  [EYES] = 0x1F440,
  [THNK] = 0x1F914,
  [NAIL] = 0x1F485,
  [SOS] = 0x1F198,
  [REDB] = 0x1F171,
  [HNDR] = 0x1F4AF,
  [MONY] = 0x1F480,
  [FIRE] = 0x1F525,
  [CAR] = 0x1F697,
  [BUTT] = 0x1F351,
  [BNIS] = 0x1F346,
  [CUM] = 0x1F4A6,
  [CLAP] = 0x1F44F,
  [TRIU] = 0x1F624,
  [SCRM] = 0x1F631,
  [VOMI] = 0x1F92E,
  [DTIV] = 0x1F575,
  [EXPL] = 0x1F92F,
  [HAIR] = 0x2640,
  [DANC] = 0x1F483,
  [STRN] = 0x1F4AA,
  [LEFT] = 0x1F448,
  [RGHT] = 0x1F449,
};

enum custom_keycodes {
  CTRL_Z = SAFE_RANGE,
  CTRL_X,
  CTRL_C,
  CTRL_V
};

#define SP_LMS LT(_LMOUSE, KC_SPC)
#define SP_RMS LT(_RMOUSE, KC_SPC)
#define LOW TT(_LOWER)
#define RAI TT(_RAISE)
#define EMO TT(_EMOJI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------. ,-----------------------------------------.
   * | GEsc |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U  |   I  |   O  |   P  | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | LOW  |   A  |   S  |   D  |   F  |   G  | |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft |   Z  |   X  |   C  |   V  |   B  | |   N  |   M  |   ,  |   .  |   /  | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl | EMO  | Alt  | GUI  | SPCE |SP_LMS| |SP_RMS|SP_RMS| GUI  | Alt  | RAI  | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */
  [_BASE] = LAYOUT( \
    KC_GESC ,   KC_1  ,   KC_2    ,   KC_3    ,   KC_4    ,   KC_5    , /**/    KC_6    ,   KC_7    ,   KC_8    ,   KC_9    , KC_0    ,   KC_BSPC , \
    KC_TAB  ,   KC_Q  ,   KC_W    ,   KC_E    ,   KC_R    ,   KC_T    , /**/    KC_Y    ,   KC_U    ,   KC_I    ,   KC_O    , KC_P    ,   KC_ENT  , \
    LOW     ,   KC_A  ,   KC_S    ,   KC_D    ,   KC_F    ,   KC_G    , /**/    KC_H    ,   KC_J    ,   KC_K    ,   KC_L    , KC_SCLN ,   KC_QUOT , \
    KC_LSFT ,   KC_Z  ,   KC_X    ,   KC_C    ,   KC_V    ,   KC_B    , /**/    KC_N    ,   KC_M    ,   KC_COMM ,   KC_DOT  , KC_SLSH ,   KC_RSFT , \
    KC_LCTL ,   EMO   ,   KC_LALT ,   KC_LGUI ,   KC_SPC  ,   SP_LMS  , /**/    SP_RMS  ,   KC_SPC  ,   KC_RGUI ,   KC_RALT , RAI     ,   KC_RCTL  \
  ),


  /* Lower
   * ,-----------------------------------------. ,-----------------------------------------.
   * | GESC |   !  |   @  |   #  |   $  |   %  | |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  |   !  |   @  |   #  |   $  |   %  | |   ^  |   &  |   *  |   (  |   )  | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |  \   |  -   |  =   |  [   |  ]   | |  [   |  ]   |  -   |  =   |  \   | Del  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft |  ^Z  |  ^X  |  ^C  |  ^V  |      | | Play | Vol+ | Vol- | Mute | Next | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |      |      | |      |      | GUI  | Alt  |      | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    TO(0)   ,   KC_EXLM ,   KC_AT   ,   KC_HASH ,   KC_DLR  ,   KC_PERC , /**/    KC_CIRC ,   KC_AMPR ,   KC_ASTR ,   KC_LPRN , KC_RPRN ,   _______ , \
    _______ ,   KC_EXLM ,   KC_AT   ,   KC_HASH ,   KC_DLR  ,   KC_PERC , /**/    KC_CIRC ,   KC_AMPR ,   KC_ASTR ,   KC_LPRN , KC_RPRN ,   _______ , \
    _______ ,   KC_RCBR ,   KC_MINS ,   KC_EQL  ,   KC_LBRC ,   KC_RBRC , /**/    KC_LBRC ,   KC_RBRC ,   KC_MINS ,   KC_EQL  , KC_BSLS ,   KC_DEL  , \
    _______ ,   CTRL_Z  ,   CTRL_X  ,   CTRL_C  ,   CTRL_V  ,   XXXXXXX , /**/    KC_MPLY ,   KC_VOLU ,   KC_VOLD ,   KC_MUTE , KC_MNXT ,   _______ , \
    _______ ,   XXXXXXX ,   _______ ,   _______ ,   _______ ,   XXXXXXX , /**/    XXXXXXX ,   _______ ,   _______ ,   _______ , XXXXXXX ,   _______  \
  ),

  /* Raise
   * ,-----------------------------------------. .-----------------------------------------.
   * | GESC |      |      |      |      |      | |      |   =  |   /  |   *  |   -  | Bksp  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  |  F9  |  F10 | F11  | F12  |      | |      |   7  |   8  |   9  |   +  | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |  F5  |  F6  |  F7  |  F8  |      | |      |   4  |   5  |   6  |  ,   | Del  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft |  F1  |  F2  |  F3  |  F4  |      | |      |   1  |   2  |   3  |  .   | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |      |      | |      |  0   | GUI  | Alt  |      | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [_RAISE] = LAYOUT( \
    TO(0)   ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , /**/  XXXXXXX ,   KC_EQL  ,   KC_SLSH ,   KC_ASTR ,   KC_MINS , _______ , \
    _______ ,   KC_F9   ,   KC_F10  ,   KC_F11  ,   KC_F12  ,   XXXXXXX , /**/  XXXXXXX ,   KC_7    ,   KC_8    ,   KC_9    ,   KC_PLUS , _______ , \
    XXXXXXX ,   KC_F5   ,   KC_F6   ,   KC_F7   ,   KC_F8   ,   XXXXXXX , /**/  XXXXXXX ,   KC_4    ,   KC_5    ,   KC_6    ,   KC_COMM , KC_DEL  , \
    _______ ,   KC_F1   ,   KC_F2   ,   KC_F3   ,   KC_F4   ,   XXXXXXX , /**/  XXXXXXX ,   KC_1    ,   KC_2    ,   KC_3    ,   KC_DOT  , _______ , \
    _______ ,   XXXXXXX ,   _______ ,   _______ ,   _______ ,   XXXXXXX , /**/  XXXXXXX ,   KC_0    ,   _______ ,   _______ ,   _______ , _______  \
  ),

  /* LMOUSE (Lower + Raise)
   * ,-----------------------------------------. ,-----------------------------------------.
   * | GESC |      | Home | End  | PGUP | PGDN | |      |      |      |      |      | Bksp |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  | WH_L | BTN1 | MS_U | BTN2 | WH_U | |      |      |      |      |      | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      | WH_R | MS_L | MS_D | MS_R | WH_D | |      |      |      |      |      | Del  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft | LEFT | DOWN |  UP  |RIGHT |      | |      |      |      |      |      | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |      |      | |      |      | GUI  | Alt  |      | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [_LMOUSE] = LAYOUT( \
    TO(0)   ,   XXXXXXX ,   KC_HOME ,   KC_END  ,   KC_PGUP ,   KC_PGDN , /**/  XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , _______ , \
    _______ ,   KC_WH_L ,   KC_BTN1 ,   KC_MS_U ,   KC_BTN2 ,   KC_WH_U , /**/  XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , _______ , \
    XXXXXXX ,   KC_WH_R ,   KC_MS_L ,   KC_MS_D ,   KC_MS_R ,   KC_WH_D , /**/  XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , KC_DEL  , \
    _______ ,   KC_LEFT ,   KC_DOWN ,   KC_UP   ,   KC_RGHT ,   XXXXXXX , /**/  XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , _______ , \
    _______ ,   XXXXXXX ,   _______ ,   _______ ,   _______ ,   _______ , /**/  XXXXXXX ,   _______ ,   _______ ,   _______ ,   XXXXXXX , _______  \
  ),

  /* RMOUSE (Lower + Raise)
   * ,-----------------------------------------. ,-----------------------------------------.
   * | GESC |      |      |      |      |      | | PGUP | PGDN | Home | End  |      | Bksp |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  |      |      |      |      |      | | WH_U | BTN1 | MS_U | BTN2 | WH_L | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | | WH_D | MS_L | MS_D | MS_R | WH_R | Del  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft |      |      |      |      |      | |      | LEFT | DOWN |  UP  |RIGHT | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |      |      | |      |      | GUI  | Alt  |      | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [_RMOUSE] = LAYOUT( \
    TO(0)   , XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , /**/  KC_PGUP ,   KC_PGDN ,   KC_HOME ,   KC_END  ,   XXXXXXX ,   _______ , \
    _______ , XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , /**/  KC_WH_U ,   KC_BTN1 ,   KC_MS_U ,   KC_BTN2 ,   KC_WH_L ,   _______ , \
    XXXXXXX , XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , /**/  KC_WH_D ,   KC_MS_L ,   KC_MS_D ,   KC_MS_R ,   KC_WH_R ,   KC_DEL  , \
    _______ , XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX ,   XXXXXXX , /**/  XXXXXXX ,   KC_LEFT ,   KC_DOWN ,   KC_UP   ,   KC_RGHT ,   _______ , \
    _______ , XXXXXXX ,   _______ ,   _______ ,   _______ ,   XXXXXXX , /**/  _______ ,   _______ ,   _______ ,   _______ ,   XXXXXXX ,   _______  \
  ),

  /* Emojis
   * ,-----------------------------------------. ,-----------------------------------------.
   * | GESC |      |      |      |      |      | | RSET |      |      |      |      | Bksp |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Tab  | CLAP | CUM  | BNIS | BUTT | CAR  | | FIRE | REDB | MONY | 100  | SOS | Entr |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      | CELE | PRAY | NAIL |  OK  | THNK | | UNAM | HEYE | COOL | EYES | SMIR | Del  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Shft | TRIU | SCRM | VOMI | DTIV | EXPL | | HAIR | DANC | STRN | LEFT | RGHT | Shft |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |      |      | |      |      | GUI  | Alt  |      | Ctrl |
   * `-----------------------------------------' `-----------------------------------------'
   */

  [_EMOJI] = LAYOUT( \
    TO(0)   , XXXXXXX     ,   XXXXXXX     ,   XXXXXXX     ,   XXXXXXX     ,   XXXXXXX     , /**/  RESET       ,   XXXXXXX     ,   XXXXXXX     ,   XXXXXXX     ,   XXXXXXX     ,   _______   , \
    _______ , X(CLAP)     ,   X(CUM)      ,   X(BNIS)     ,   X(BUTT)     ,   X(CAR)      , /**/  X(FIRE)     ,   X(REDB)     ,   X(MONY)     ,   X(HNDR)     ,   X(SOS)      ,   _______   , \
    XXXXXXX , X(CELE)     ,   X(PRAY)     ,   X(NAIL)     ,   X(OK)       ,   X(THNK)     , /**/  X(UNAM)     ,   X(HEYE)     ,   X(COOL)     ,   X(EYES)     ,   X(SMIR)     ,   KC_DEL    , \
    _______ , X(TRIU)     ,   X(SCRM)     ,   X(VOMI)     ,   X(DTIV)     ,   X(EXPL)     , /**/  X(HAIR)     ,   X(DANC)     ,   X(STRN)     ,   X(LEFT)     ,   X(RGHT)     ,   _______   , \
    _______ , _______     ,   _______     ,   _______     ,   _______     ,   XXXXXXX     , /**/  XXXXXXX     ,   _______     ,   _______     ,   _______     ,   XXXXXXX     ,   _______     \
  ),

};

void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    switch(keycode) {
      case CTRL_Z:
        SEND_STRING(SS_LCTRL("z"));
        return false;
      case CTRL_X:
        SEND_STRING(SS_LCTRL("x"));
        return false;
      case CTRL_C:
        SEND_STRING(SS_LCTRL("c"));
        return false;
      case CTRL_V:
        SEND_STRING(SS_LCTRL("v"));
        return false;
    }
  }

  return true;
}
