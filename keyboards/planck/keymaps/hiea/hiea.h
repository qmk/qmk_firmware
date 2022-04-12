
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
  // |   Q  |   Y  |   [  |   ]  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   ^  |   <  |   >  |   ~  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   !  |   =  |   `  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | ↑Tab |  f() |  Ins | Left |   _  |  Del | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), KC_LBRC, KC_RBRC, S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    SM_H,    KC_CIRC, TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_Z), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  S_TAB,   ___fn__, LT_INS,  S_LEFT,  KC_UNDS, SP_DEL,  S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   {  |   }  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   ?  |Cursor| Mouse|   |  |   (  |   )  |   $  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   K  |   /  |  Num | Regex|   \  |   *  |   .  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Tab |   -  |  Ins | Left |  f() | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), KC_LCBR, KC_RCBR, S(KC_M), S(KC_X),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  SM_W   ,
    S(KC_J), TD_COLN, TD_DQOT, S(KC_K), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_ASTR, KC_DOT,  S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_TAB,  KC_MINS, LT_INS,  S_LEFT,  ___fn__, SP_BSPC, S_DOWN,  S_UP,    S_RGHT
  ),
#endif
