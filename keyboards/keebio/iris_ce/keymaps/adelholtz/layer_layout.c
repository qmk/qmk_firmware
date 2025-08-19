
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
     QK_GESC, KC_1, KC_2,  KC_3,          KC_4,           KC_5,                        KC_6,      KC_7,            KC_8,      KC_9,       KC_0,    KC_BSPC,
     TD(MAGIC_TAB),  DE_Q, DE_W,  TRL_SPECIAL_F, TRL_MEDIA_P,    DE_G,                        DE_J,      TRL_MEDIA_L,     DE_U,       DE_Y,    XXXXXXX, XXXXXXX,
     KC_LCTL, DE_A, DE_R,  HRM_ALT_S,     HRL_BRACKETS_T, HRM_GUI_D,                   HRM_GUI_H, HRL_BRACKETS_N,  HRM_CTRL_E, DE_I,    DE_O,    KC_ENTER,
     KC_LSFT, DE_Z, DE_X,  DE_C,          DE_V, DE_B,                KC_HOME, KC_END,  DE_K,      DE_M,            DE_COMM,    KC_DOT,  KC_SLSH, CW_TOGG,
                                            GAME, TD(NAV_LMAGIC), TD(SPACE_TAB), OSM(MOD_LSFT), TD(XTRA_RMAGIC), GAME // MO(_EXTRA)
  ),
  [_GAME] = LAYOUT(
     QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0,    KC_BSPC,
     KC_TAB,  DE_Q, DE_W, DE_F, DE_P, DE_G,                  DE_J, DE_L, DE_U, DE_Y,  XXXXXXX, XXXXXXX,
     KC_LCTL, DE_A, DE_R, DE_S, DE_T, DE_D,                  DE_H, DE_N, DE_E, DE_I, DE_O, KC_ENTER,
     KC_LSFT, DE_Z, DE_X, DE_C, DE_V, DE_B, KC_HOME, KC_END, DE_K, DE_M, DE_COMM, KC_DOT, KC_SLSH, KC_CAPS,
                COLEMAK, TD(NAV_LMAGIC), LT(_BRACKETS,KC_SPC), KC_LSFT,  TD(XTRA_RMAGIC), COLEMAK
  ),
  [_NAVIGATION] = LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX,                       XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN,
     _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                        KC_RCBR, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_PIPE,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    TO(0), _______,    KC_RBRC, KC_1,    KC_2,    KC_3,    DE_SS,   _______,
                                         XXXXXXX, XXXXXXX,  KC_DEL, KC_DEL, XXXXXXX, KC_P0
  ),
  [_BRACKETS] = LAYOUT(
     KC_F12,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,
     _______, XXXXXXX, XXXXXXX, XXXXXXX,  DE_LABK, XXXXXXX,                      XXXXXXX, DE_RABK, XXXXXXX,  XXXXXXX, XXXXXXX, QK_BOOT,
     _______, XXXXXXX, LCURLY,  LBRACKET, DE_LPRN, XXXXXXX,                      XXXXXXX, DE_RPRN, RBRACKET, RCURLY,  XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,   TO(0), _______,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         XXXXXXX, XXXXXXX, KC_BSPC, KC_BSPC, QK_AREP, _______
  ),
  [_EXTRA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                      XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, KC_GRV,  KC_TILD, KC_PLUS, DE_SECT,                      XXXXXXX, LSA(DE_7), KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, DE_EQL,  DE_PERC, DE_EXLM, DE_DQUO, DE_DLR,                       DE_AMPR, DE_SLSH,   DE_QUES, DE_HASH, PIPE_,   XXXXXXX,
     _______, DE_ADIA, DE_ODIA, DE_UDIA, KC_PIPE, XXXXXXX,    TO(0), _______,   XXXXXXX, DE_BSLS,   XXXXXXX, XXXXXXX, DE_PIPE, XXXXXXX,
                                          XXXXXXX, _______, _______, _______, _______, _______
  ),
  [_MEDIA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, KC_MUTE, KC_MSTP, KC_VOLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG, XXXXXXX,
     _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                      XXXXXXX, RM_NEXT, RM_VALU, RM_HUEU, RM_SPDU, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX,    TO(0), _______,   XXXXXXX, RM_PREV, RM_VALD, RM_HUED, RM_SPDD, XXXXXXX,
                                          XXXXXXX, _______, _______, _______, _______, _______
  ),
  [_SPECIAL] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, KC_PASTE, KC_COPY, KC_CUT,                      XXXXXXX, RELOAD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    TO(0), _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          XXXXXXX, _______, _______, _______, _______, _______
  )
};
// clang-format on
