
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// .............................................................. Colemak Mod-DH
#ifdef COLEMAK
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   ;  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   ,  |   .  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    CNTR_TL, CNTR_TR, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    CNTR_HL, CNTR_HR, KC_M,    KC_N,    KC_E,    KC_I,    KC_O   ,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    CNTR_BL, CNTR_BR, KC_K,    KC_H,    KC_COMM, KC_DOT,  TD_QUOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), KC_SCLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), CNTR_HL, CNTR_HR, S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), CNTR_BL, CNTR_BR, S(KC_K), S(KC_H), KC_COMM, KC_DOT,  TD_QUOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   /  |   ?  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), CNTR_HL, CNTR_HR, S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), CNTR_BL, CNTR_BR, S(KC_K), S(KC_H), KC_SLSH, KC_QUES, TD_DQOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_MINS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   ~  |   `  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), CNTR_HL, CNTR_HR, S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), CNTR_BL, CNTR_BR, S(KC_K), S(KC_H), TD_TILD, TD_GRV,  TD_DQOT,
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_UNDS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif

// ..................................................................... ColemaX
#ifdef COLEMAX
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   C  |   G  |   Z  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   ;  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   B  | ↑Alt | ↑GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   X  |   V  |   F  |   D  |   P  | Caps |^Shift|   M  |   H  |   ,  |   .  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_C,    KC_G,    KC_Z,    CNTR_TL, CNTR_TR, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_B,    CNTR_HL, CNTR_HR, KC_K,    KC_N,    KC_E,    KC_I,    KC_O   ,
    KC_X,    KC_V,    KC_F,    KC_D,    KC_P,    CNTR_BL, CNTR_BR, KC_M,    KC_H,    KC_COMM, KC_DOT,  TD_QUOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_C), S(KC_G), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), KC_SCLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_B), CNTR_HL, CNTR_HR, S(KC_K), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_X), S(KC_V), S(KC_F), S(KC_D), S(KC_P), CNTR_BL, CNTR_BR, S(KC_M), S(KC_H), KC_COMM, KC_DOT,  TD_QUOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   C  |   G  |   Z  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   B  | ↑Alt | ↑GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   X  |   V  |   F  |   D  |   P  | Caps |^Shift|   M  |   H  |   /  |   ?  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_C), S(KC_G), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_B), CNTR_HL, CNTR_HR, S(KC_K), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_X), S(KC_V), S(KC_F), S(KC_D), S(KC_P), CNTR_BL, CNTR_BR, S(KC_M), S(KC_H), KC_SLSH, KC_QUES, TD_DQOT,
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___fn__, LT_TAB,  KC_DEL,  KC_MINS, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   C  |   G  |   Z  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   B  | ↑Alt | ↑GUI |   K  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   X  |   V  |   F  |   D  |   P  | Caps |^Shift|   M  |   H  |   ~  |   `  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_planck_grid(
    S(KC_Q), S(KC_W), S(KC_C), S(KC_G), S(KC_Z), CNTR_TL, CNTR_TR, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_B), CNTR_HL, CNTR_HR, S(KC_K), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_X), S(KC_V), S(KC_F), S(KC_D), S(KC_P), CNTR_BL, CNTR_BR, S(KC_M), S(KC_H), TD_TILD, TD_GRV,  TD_DQOT,
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, KC_UNDS, SL_TAB,  LT_BSPC, ___fn__, SL_LEFT, S_DOWN,  S_UP,    S_RGHT
  ),
#endif
