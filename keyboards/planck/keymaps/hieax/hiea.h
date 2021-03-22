
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// .................................................................. BEAKL HIEA
#ifdef DEFAULT
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   .  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   K  |   ,  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Ins | Left |  Ent | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    HOME_H,  HOME_I,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_R,  HOME_S,  HOME_W ,
    KC_J,    KC_SCLN, TD_QUOT, KC_K,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_INS,  SP_LEFT, TD_ENT,  SP_BSPC, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_K), KC_COMM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_INS,  SP_LEFT, TD_ENT,  SP_BSPC, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   ?  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   K  |   /  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | ↑Tab |  f() |  Ins | Left |   _  |  Del | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  S_TAB,   ___fn__, LT_INS,  S_LEFT,  KC_UNDS, SP_DEL,  S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   ?  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   K  |   /  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Tab |   -  |  Ins | Left |  f() | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_TAB,  KC_MINS, LT_INS,  S_LEFT,  ___fn__, SP_BSPC, S_DOWN,  S_UP,    S_RGHT
  ),
#ifdef HOME_MODS
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   `  |   [  |   ]  |   ^  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |  f() |   ?  |Cursor| Mouse|   |  |   (  |   )  |   $  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   K  |   /  |  Num | Regex|   \  |   {  |   }  |   #  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Ins | Left |   +  | Space| Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSYMBOL] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, TD_GRV,  KC_LBRC, KC_RBRC, KC_CIRC, S(KC_X),
    HOME_H,  HOME_I,  HOME_E,  ___fn__, KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_LCBR, KC_RCBR, KC_HASH, S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_INS,  SP_LEFT, KC_PLUS, SL_SPC,  AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   .  |   *  |   &  |   ~  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   <  |   %  |   >  |   ?  |Cursor| Mouse|   C  |  f() |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   @  |   !  |   /  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | ↑Tab |   =  |  Ins | Left |  Ent | Bksp | Down |  Up  | Right|
  // |                           | ↑Tab |   =  |  Ent | Bksp |                           |
  // `-----------------------------------------------------------------------------------'

  [_RSYMBOL] = LAYOUT_planck_grid(
    S(KC_Q), KC_DOT,  KC_ASTR, KC_AMPR, TD_TILD, CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_H), TD_LT,   KC_PERC, TD_GT,   KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), ___fn__, HOME_R,  HOME_S,  HOME_W ,
    S(KC_J), TD_COLN, KC_AT,   KC_EXLM, KC_SLSH, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  S_TAB,   TD_EQL,  LT_INS,  SP_LEFT, TD_ENT,  LT_BSPC, AT_DOWN, GT_UP,   CT_RGHT
  ),
#endif
#endif
