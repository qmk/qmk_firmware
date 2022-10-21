#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define _BASE 0
#define _LMSE 1
#define _RMSE 2
#define _SYMB 3
#define _EMOJ 4

#define SP_LMS LT(_LMSE, KC_SPC)
#define SP_RMS LT(_RMSE, KC_SPC)
#define MO_SYMB TT(_SYMB)
#define MO_EMOJ TT(_EMOJ)


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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    QK_GESC , KC_1    , KC_2    , KC_3     , KC_4   , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS , KC_EQL  , KC_DEL  ,  KC_BSPC  , \
    KC_TAB  , KC_Q    , KC_W    , KC_E     , KC_R   , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_LBRC , KC_RBRC , KC_BSLS , \
    MO_EMOJ , KC_A    , KC_S    , KC_D     , KC_F   , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT , KC_ENT  , \
    KC_LSFT , KC_Z    , KC_X    , KC_C     , KC_V   , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT , KC_UP   , \
    KC_LCTL , KC_LALT , KC_LGUI , MO_SYMB  , SP_LMS ,           SP_RMS  , KC_BSPC , KC_RGUI , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
  ),

  [_LMSE] = LAYOUT(
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , \
    _______ , KC_WH_L , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_U , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , KC_WH_R , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
    _______ , _______ , KC_PGDN , KC_PGUP , KC_END  , KC_HOME , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_RMSE] = LAYOUT(
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_U , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_L , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_R , _______ , _______ ,\
    _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_END  , KC_PGUP , KC_PGDN , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_SYMB] = LAYOUT(
    QK_GESC , KC_F1   , KC_F12  , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_DEL  ,  KC_BSPC  , \
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ , _______ ,\
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_EMOJ] = LAYOUT(
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , \
    _______ , X(CLAP) , X(CUM)  , X(BNIS) , X(BUTT) , X(CAR)  , X(FIRE) , X(REDB) , X(MONY) , X(HNDR) , X(SOS)  , _______ , _______ , _______ , \
    _______ , X(CELE) , X(PRAY) , X(NAIL) , X(OK)   , X(THNK) , X(UNAM) , X(HEYE) , X(COOL) , X(EYES) , X(SMIR) , _______ , _______ ,\
    _______ , X(TRIU) , X(SCRM) , X(VOMI) , X(DTIV) , X(EXPL) , X(HAIR) , X(DANC) , X(STRN) , X(LEFT) , X(RGHT) , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ ,           _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

};

void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};
