
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// .................................................................... BEAKL EZ
#ifdef BEAKLEZ
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   K  | ^Alt | ^GUI |   F  |   G  |   R  |   C  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   "  | ↑Alt | ↑GUI |   L  |   S  |   T  |   N  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   ;  |   ,  |   J  |   .  |   X  | Caps |^Shift|   B  |   D  |   M  |   P  |   Z  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_K,    CNTR_TL, CNTR_TR, KC_F,    KC_G,    KC_R,    KC_C,    KC_V   ,
    KC_H,    KC_I,    KC_E,    HOME_A,  TD_QUOT, CNTR_HL, CNTR_HR, KC_L,    KC_S,    KC_T,    KC_N,    KC_W   ,
    KC_SCLN, KC_COMM, KC_J,    KC_DOT,  KC_X,    CNTR_BL, CNTR_BR, KC_B,    KC_D,    KC_M,    KC_P,    KC_Z   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_K), CNTR_TL, CNTR_TR, S(KC_F), S(KC_G), S(KC_R), S(KC_C), S(KC_V),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), TD_QUOT, CNTR_HL, CNTR_HR, S(KC_L), S(KC_S), S(KC_T), S(KC_N), S(KC_W),
    KC_SCLN, KC_COMM, S(KC_J), KC_DOT,  S(KC_X), CNTR_BL, CNTR_BR, S(KC_B), S(KC_D), S(KC_M), S(KC_P), S(KC_Z),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   K  | ^Alt | ^GUI |   F  |   G  |   R  |   C  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   "  | ↑Alt | ↑GUI |   L  |   S  |   T  |   N  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   :  |   ~  |   J  |   `  |   X  | Caps |^Shift|   B  |   D  |   M  |   P  |   Z  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_K), CNTR_TL, CNTR_TR, S(KC_F), S(KC_G), S(KC_R), S(KC_C), S(KC_V),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), TD_DQOT, CNTR_HL, CNTR_HR, S(KC_L), S(KC_S), S(KC_T), S(KC_N), S(KC_W),
    TD_COLN, TD_TILD, S(KC_J), TD_GRV,  S(KC_X), CNTR_BL, CNTR_BR, S(KC_B), S(KC_D), S(KC_M), S(KC_P), S(KC_Z),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   K  | ^Alt | ^GUI |   F  |   G  |   R  |   C  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   H  |   I  |   E  |   A  |   "  | ↑Alt | ↑GUI |   L  |   S  |   T  |   N  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   :  |   /  |   J  |   ?  |   X  | Caps |^Shift|   B  |   D  |   M  |   P  |   Z  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_K), CNTR_TL, CNTR_TR, S(KC_F), S(KC_G), S(KC_R), S(KC_C), S(KC_V),
    S(KC_H), S(KC_I), S(KC_E), S(KC_A), TD_DQOT, CNTR_HL, CNTR_HR, S(KC_L), S(KC_S), S(KC_T), S(KC_N), S(KC_W),
    TD_COLN, KC_SLSH, S(KC_J), KC_QUES, S(KC_X), CNTR_BL, CNTR_BR, S(KC_B), S(KC_D), S(KC_M), S(KC_P), S(KC_Z),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// ..................................................................... BEAKL 8
#ifdef BEAKL8
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   X  | ^Alt | ^GUI |   G  |   C  |   R  |   F  |   Z  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  | ↑Alt | ↑GUI |   D  |   S  |   T  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   I  |   ,  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_X,    CNTR_TL, CNTR_TR, KC_G,    KC_C,    KC_R,    KC_F,    KC_Z   ,
    KC_K,    KC_H,    KC_E,    HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_D,    KC_S,    KC_T,    KC_N,    KC_B   ,
    KC_J,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_W,    KC_M,    KC_L,    KC_P,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), S(KC_C), S(KC_R), S(KC_F), S(KC_Z),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_D), S(KC_S), S(KC_T), S(KC_N), S(KC_B),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   X  | ^Alt | ^GUI |   G  |   C  |   R  |   F  |   Z  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ~  | ↑Alt | ↑GUI |   D  |   S  |   T  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   `  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), S(KC_C), S(KC_R), S(KC_F), S(KC_Z),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), TD_TILD, CNTR_HL, CNTR_HR, S(KC_D), S(KC_S), S(KC_T), S(KC_N), S(KC_B),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), TD_GRV,  CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT ,
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   X  | ^Alt | ^GUI |   G  |   C  |   R  |   F  |   Z  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  | ↑Alt | ↑GUI |   D  |   S  |   T  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   /  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), S(KC_C), S(KC_R), S(KC_F), S(KC_Z),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_D), S(KC_S), S(KC_T), S(KC_N), S(KC_B),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// .................................................................... BEAKL 8P
#ifdef BEAKL8P
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | ^Alt | ^GUI |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  | ↑Alt | ↑GUI |   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   I  |   ,  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_R,    KC_F,    KC_X   ,
    KC_K,    KC_H,    KC_E,    HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    KC_T,    KC_S,    KC_N,    KC_B   ,
    KC_J,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_W,    KC_M,    KC_L,    KC_P,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ,

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ,

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   {  |   }  |   $  | ^Alt | ^GUI |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   <  |   >  |   ~  | ↑Alt | ↑GUI |   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   !  |   =  |   `  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), KC_LCBR, KC_RCBR, KC_DLR,  CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), S(KC_H), TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_J), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | ^Alt | ^GUI |   ^  |   [  |   ]  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  | ↑Alt | ↑GUI |   |  |   (  |   )  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   /  | Caps |^Shift|   \  |   $  |   *  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, KC_CIRC, KC_LBRC, KC_RBRC, S(KC_F), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, S(KC_N), S(KC_B),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_DLR,  KC_ASTR, S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// ................................................................... BEAKL 8TX
#ifdef BEAKL8TX
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   J  | ^Alt | ^GUI |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  | ↑Alt | ↑GUI |   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   ;  |   "  |   I  |   ,  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_J,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_R,    KC_F,    KC_X   ,
    HOME_K,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_S,  HOME_N,  HOME_B ,
    KC_Z,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_W,    KC_M,    KC_L,    KC_P,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_Z), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   $  |   {  |   }  |   J  | ^Alt | ^GUI |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   /  |   <  |   >  |   ~  | ↑Alt | ↑GUI |   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   :  |   !  |   =  |   `  | Caps |^Shift|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), KC_DLR,  KC_LCBR, KC_RCBR, S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), KC_SLSH, TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_Z), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   J  | ^Alt | ^GUI |   G  |   [  |   ]  |   ^  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  | ↑Alt | ↑GUI |   |  |   (  |   )  |   $  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   :  |   "  |   I  |   /  | Caps |^Shift|   \  |   *  |   .  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), KC_LBRC, KC_RBRC, KC_CIRC, S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  S(KC_B),
    S(KC_Z), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_ASTR, KC_DOT,  S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// ................................................................... BEAKL 8TT
#ifdef BEAKL8TT
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   J  |   Fn | Caps |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  |Cursor| Mouse|   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   ;  |   "  |   I  |   ,  |  Num | Regex|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_J,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_R,    KC_F,    KC_X   ,
    HOME_K,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_S,  HOME_N,  HOME_B ,
    KC_Z,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_W,    KC_M,    KC_L,    KC_P,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_Z), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   $  |   {  |   }  |   J  |   Fn | Caps |   G  |   D  |   R  |   F  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   /  |   <  |   >  |   ~  |Cursor| Mouse|   C  |   T  |   S  |   N  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   :  |   !  |   =  |   `  |  Num | Regex|   W  |   M  |   L  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), KC_DLR,  KC_LCBR, KC_RCBR, S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_R), S(KC_F), S(KC_X),
    S(KC_K), KC_SLSH, TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_S), S(KC_N), S(KC_B),
    S(KC_Z), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_W), S(KC_M), S(KC_L), S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   J  |   Fn | Caps |   G  |   [  |   ]  |   ^  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  |Cursor| Mouse|   |  |   (  |   )  |   $  |   B  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   :  |   "  |   I  |   /  |  Num | Regex|   \  |   *  |   .  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_J), CNTR_TL, CNTR_TR, S(KC_G), KC_LBRC, KC_RBRC, KC_CIRC, S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  S(KC_B),
    S(KC_Z), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_ASTR, KC_DOT,  S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// .................................................................... BEAKL 10
#ifdef BEAKL10
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   H  |   O  |   U  |   X  | ^Alt | ^GUI |   G  |   D  |   N  |   M  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Y  |   I  |   E  |   A  |   .  | ↑Alt | ↑GUI |   C  |   S  |   R  |   T  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   ,  |   Z  | Caps |^Shift|   B  |   P  |   L  |   F  |   K  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_H,    KC_O,    KC_U,    KC_X,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_V   ,
    KC_Y,    KC_I,    KC_E,    HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    KC_S,    KC_R,    KC_T,    KC_W   ,
    KC_J,    KC_SCLN, TD_QUOT, KC_COMM, KC_Z,    CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_K   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_H), S(KC_O), S(KC_U), S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_V),
    S(KC_Y), S(KC_I), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_S), S(KC_R), S(KC_T), S(KC_W),
    S(KC_J), KC_SCLN, TD_QUOT, KC_COMM, S(KC_Z), CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_K),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   [  |   !  |   ]  |   X  | ^Alt | ^GUI |   G  |   D  |   N  |   M  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Y  |   <  |   =  |   >  |   ~  | ↑Alt | ↑GUI |   C  |   S  |   R  |   T  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   `  |   Z  | Caps |^Shift|   B  |   P  |   L  |   F  |   K  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), TD_LBRC, KC_EXLM, TD_RBRC, S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_V),
    S(KC_Y), TD_LT,   KC_EQL,  TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_S), S(KC_R), S(KC_T), S(KC_W),
    S(KC_J), KC_COLN, TD_DQOT, TD_GRV,  S(KC_Z), CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_K),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   H  |   O  |   U  |   X  | ^Alt | ^GUI |   G  |   {  |   +  |   }  |   V  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   Y  |   I  |   E  |   A  |   ?  | ↑Alt | ↑GUI |   C  |   (  |   *  |   )  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   /  |   Z  | Caps |^Shift|   B  |   P  |   L  |   F  |   K  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_H), S(KC_O), S(KC_U), S(KC_X), CNTR_TL, CNTR_TR, S(KC_G), TD_LCBR, KC_PLUS, TD_RCBR, S(KC_V),
    S(KC_Y), S(KC_I), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, S(KC_C), TD_LPRN, KC_ASTR, TD_RPRN, S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, KC_SLSH, S(KC_Z), CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_K),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// ............................................................... BEAKL Mash Up
#ifdef BEAKL810
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | ^Alt | ^GUI |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  | ↑Alt | ↑GUI |   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   I  |   ,  | Caps |^Shift|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    KC_K,    KC_H,    KC_E,    HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    KC_T,    KC_R,    KC_S,    KC_W   ,
    KC_J,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   {  |   }  |   $  | ^Alt | ^GUI |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   <  |   >  |   ~  | ↑Alt | ↑GUI |   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   !  |   =  |   `  | Caps |^Shift|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), KC_LCBR, KC_RCBR, KC_DLR,  CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | ^Alt | ^GUI |   ^  |   [  |   ]  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  | ↑Alt | ↑GUI |   |  |   (  |   )  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   /  | Caps |^Shift|   \  |   $  |   *  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, KC_CIRC, KC_LBRC, KC_RBRC, S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, S(KC_S), S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_DLR,  KC_ASTR, S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// .................................................................... BEAKL MU
#ifdef BEAKLMU
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   I  |   ,  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    HOME_K,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_R,  HOME_S,  HOME_W ,
    KC_J,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   $  |   {  |   }  |   Z  |  Fn  | Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   /  |   <  |   >  |   ~  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   !  |   =  |   `  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   _  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), KC_DLR,  KC_LCBR, KC_RCBR, S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), KC_SLSH, TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_Z), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_UNDS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  |  Fn  | Caps |   G  |   [  |   ]  |   ^  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  |Cursor| Mouse|   |  |   (  |   )  |   $  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   /  |  Num | Regex|   \  |   *  |   .  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   -  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), KC_LBRC, KC_RBRC, KC_CIRC, S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_ASTR, KC_DOT,  S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_MINS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// .................................................................... BEAKL SP
#ifdef BEAKLSP
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   .  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   ;  |   "  |   I  |   ,  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Ins | Left |  Ent | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_Y,    KC_O,    KC_U,    KC_Z,    CNTR_TL, CNTR_TR, KC_G,    KC_D,    KC_N,    KC_M,    KC_X   ,
    HOME_K,  HOME_H,  HOME_E,  HOME_A,  KC_DOT,  CNTR_HL, CNTR_HR, KC_C,    HOME_T,  HOME_R,  HOME_S,  HOME_W ,
    KC_J,    KC_SCLN, TD_QUOT, KC_I,    KC_COMM, CNTR_BL, CNTR_BR, KC_B,    KC_P,    KC_L,    KC_F,    KC_V   ,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_INS,  SP_LEFT, TD_ENT,  SP_BSPC, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_DOT,  CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_J), KC_SCLN, TD_QUOT, S(KC_I), KC_COMM, CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_INS,  SP_LEFT, TD_ENT,  SP_BSPC, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   [  |   ]  |   Z  | Shift| Caps |   G  |   D  |   N  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   ^  |   <  |   >  |   ~  |Cursor| Mouse|   C  |   T  |   R  |   S  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   !  |   =  |   `  |  Num | Regex|   B  |   P  |   L  |   F  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | ↑Tab |  f() |  Ins | Left |   _  |  Del | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), KC_LBRC, KC_RBRC, S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), S(KC_D), S(KC_N), S(KC_M), S(KC_X),
    S(KC_K), KC_CIRC, TD_LT,   TD_GT,   TD_TILD, CNTR_HL, CNTR_HR, S(KC_C), S(KC_T), S(KC_R), S(KC_S), S(KC_W),
    S(KC_Z), KC_COLN, KC_EXLM, KC_EQL,  TD_GRV,  CNTR_BL, CNTR_BR, S(KC_B), S(KC_P), S(KC_L), S(KC_F), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  S_TAB,   ___fn__, LT_INS,  S_LEFT,  KC_UNDS, SP_DEL,  S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   Y  |   O  |   U  |   Z  | Shift| Caps |   G  |   {  |   }  |   M  |   X  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   K  |   H  |   E  |   A  |   ?  |Cursor| Mouse|   |  |   (  |   )  |   $  |   W  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   J  |   :  |   "  |   I  |   /  |  Num | Regex|   \  |   *  |   .  |   P  |   V  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Tab |   -  |  Ins | Left |  f() | Bksp | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_Y), S(KC_O), S(KC_U), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_G), KC_LCBR, KC_RCBR, S(KC_M), S(KC_X),
    S(KC_K), S(KC_H), S(KC_E), S(KC_A), KC_QUES, CNTR_HL, CNTR_HR, KC_PIPE, KC_LPRN, KC_RPRN, KC_DLR,  S(KC_W),
    S(KC_J), TD_COLN, TD_DQOT, S(KC_I), KC_SLSH, CNTR_BL, CNTR_BR, KC_BSLS, KC_ASTR, KC_DOT,  S(KC_P), S(KC_V),
    OS_CTL,  OS_GUI,  OS_ALT,  KC_TAB,  KC_MINS, LT_INS,  S_LEFT,  ___fn__, SP_BSPC, S_DOWN,  S_UP,    S_RGHT
  ),
#endif
