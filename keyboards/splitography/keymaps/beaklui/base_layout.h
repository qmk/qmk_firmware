
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// .................................................................... BEAKL TI

  // ,-----------------------------------------------------------------------------------.
  // |   :  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Q  |   H  |   E  |   A  |   .  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   -  |   '  |   K  |   ,  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |  Esc |   I  | Space| Bksp |                           |
  // | Ctrl |  GUI |  Alt |  Esc |   I  |  Ins | Left | Space| Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = {
    {TD_COLM, KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   },
    {HOME_Q,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_R,  HOME_S,  HOME_W },
    {KC_J,    KC_MINS, KC_QUOT, KC_K,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   },
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, LT_ESC,  LT_I,    TD_SPC,  TD_BSPC, _______, _______, _______, _______},
#else
    {OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  LT_I,    LT_INS,  LT_LEFT, TD_SPC,  TD_BSPC, AT_DOWN, GT_UP,   CT_RGHT},
#endif
  },

  [_SHIFT] = {
    {KC_COLN, S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X)},
    {S(KC_Q), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W)},
    {S(KC_J), KC_UNDS, KC_DQT,  S(KC_K), KC_EXLM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V)},
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, KC_ESC,  S(KC_I), KC_SPC,  KC_BSPC, _______, _______, _______, _______},
#else
    {OS_CTL,  OS_GUI,  OS_ALT,  KC_ESC,  S(KC_I), LT_INS,  LT_LEFT, KC_SPC,  KC_BSPC, AT_DOWN, GT_UP,   CT_RGHT},
#endif
  },

  // ,-----------------------------------------------------------------------------------.
  // |   :  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Q  |   H  |   E  |   A  |   ~  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   -  |   '  |   K  |   `  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |  Tab |  f() |  Del | Enter|                           |
  // | Ctrl |  GUI |  Alt |  Tab |  f() |  Ins | Left |  Del | Enter| Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'
  // thumb side lower case to ovoid triggering same hand upper case

  [_LSHIFT] = {
    {KC_COLN, KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X)},
    {KC_Q,    KC_H,    KC_E,    KC_SPC,  TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W)},
    {KC_J,    KC_MINS, KC_QUOT, KC_K,    KC_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V)},
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, KC_TAB,  ___fn__, TD_DEL,  KC_ENT,  _______, _______, _______, _______},
#else
    {OS_CTL,  OS_GUI,  OS_ALT,  KC_TAB,  ___fn__, LT_INS,  S_LEFT,  TD_DEL,  LT_ENT,  S_DOWN,  S_UP,    S_RGHT },
#endif
  },

  // ,-----------------------------------------------------------------------------------.
  // |   ;  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Q  |   H  |   E  |   A  |   ?  |Cursor| Mouse|   C  | Enter|   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   _  |   "  |   K  |   /  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |  Tab |   I  |  f() | Bksp |                           |
  // | Ctrl |  GUI |  Alt |  Tab |   I  |  Ins | Left |  f() | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'
  // thumb side lower case to ovoid triggering same hand upper case

  [_RSHIFT] = {
    {KC_SCLN, S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   },
    {S(KC_Q), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_C,  KC_ENT,    KC_R,    KC_S,    KC_W   },
    {S(KC_J), KC_UNDS, KC_DQT,  S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   },
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, KC_TAB,  SL_I,    ___fn__, KC_BSPC, _______, _______, _______, _______},
#else
    {OS_CTL,  OS_GUI,  OS_ALT,  KC_TAB,  S(KC_I), LT_INS,  S_LEFT,  ___fn__, KC_BSPC, S_DOWN,  S_UP,    S_RGHT },
#endif
  },

  // ,-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |   *  |   [  |   ^  |   ]  |      |
  // |--------------------+---------------------------+------+------+------+------+------|
  // |      |      |      |      |      |      |      |   |  |   (  |   $  |   )  |      |
  // |------|-------------+------|------|-------------+------+------+------+------+------|
  // |      |      |      |      |      |      |      |   /  |   {  |   #  |   }  |      |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |                           |  f() |      |   \  | Enter|                           |
  // |      |      |      |  f() |      |      |      |   \  | Enter|      |      |      |
  // `-----------------------------------------------------------------------------------'

  [_LSYMBOL] = {
    {_______, _______, _______, _______, _______, ___x___, ___x___, TD_ASTR, KC_LBRC, KC_CIRC, KC_RBRC, _______},
    {_______, _______, _______, _______, _______, ___x___, ___x___, KC_PIPE, KC_LPRN, KC_DLR,  KC_RPRN, _______},
    {_______, _______, _______, _______, _______, ___x___, ___x___, KC_SLSH, KC_LCBR, KC_HASH, KC_RCBR, _______},
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, ___fn__, ___x___, KC_BSLS, SL_ENT,  _______, _______, _______, _______},
#else
    {_______, _______, _______, ___fn__, ___x___, _______, _______, KC_BSLS, SL_ENT,  _______, _______, _______},
#endif
  },

  // ,-----------------------------------------------------------------------------------.
  // |   :  |   .  |   *  |   &  |      |      |      |      | Home |  Up  |  End | PgUp |
  // |------+------+------+------+------+------------------------------------------------|
  // |   ~  |   <  |   %  |   >  |   ?  |      |      |      | Left | Down | Right| PgDn |
  // |------+------+------+------+------+------|-----------------------------------------|
  // |      |   +  |   @  |   !  |   /  |      |      |      |      |      |      |      |
  // |------+------+------+------+------+------+-----------------------------------------|
  // |                           | ↑Tab |   =  |      |  f() |                           |
  // |      |      |      | ↑Tab |   =  |      |      |      |  f() |      |      |      |
  // `-----------------------------------------------------------------------------------'

  [_RSYMBOL] = {
    {HS_COLN, KC_DOT,  KC_ASTR, KC_AMPR, _______, ___x___, ___x___, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP},
    {SG_TILD, HS_LT,   TD_PERC, HS_GT,   KC_QUES, ___x___, ___x___, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN},
    {_______, KC_PLUS, KC_AT,   KC_EXLM, KC_SLSH, ___x___, ___x___, _______, _______, _______, _______, _______},
#ifdef SPLITOGRAPHY
    {_______, _______, _______, _______, SL_TAB,  HS_EQL,  ___x___, ___fn__, _______, _______, _______, _______},
#else
    {_______, _______, _______, SL_TAB,  HS_EQL,  _______, _______, ___x___, ___fn__, _______, _______, _______},
#endif
  },
