
enum custom_layers {
  _COLEMAK,
  _GAME,
  _NAVIGATION,
  _BRACKETS,
  _EXTRA,
  _MEDIA,
  _SPECIAL
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
     QK_GESC, KC_1, KC_2,  KC_3,          KC_4,           KC_5,                        KC_6,      KC_7,            KC_8,      KC_9,       KC_0,    KC_BSPC,
     KC_TAB,  DE_Q, DE_W,  HRM_SPECIAL_F, TRL_MEDIA_P,    DE_G,                        DE_J,      TRL_MEDIA_L,     DE_U,       DE_Y,    XXXXXXX, XXXXXXX,
     KC_LCTL, DE_A, DE_R,  HRM_ALT_S,     HRL_BRACKETS_T, HRM_GUI_D,                   HRM_GUI_H, HRL_BRACKETS_N,  HRM_CTRL_E, DE_I,    DE_O,    KC_ENTER,
     KC_LSFT, DE_Z, DE_X,  DE_C,          DE_V, DE_B,                KC_HOME, KC_END,  DE_K,      DE_M,            DE_COMM,    KC_DOT,  KC_SLSH, KC_CAPS,
                                            LMAGIC, MO(_NAVIGATION), TD(SPACE_TAB), OSM(MOD_LSFT), MO(_EXTRA), RMAGIC
  ),
  [_GAME] = LAYOUT(
     QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9,   KC_0,    KC_BSPC,
     KC_TAB,  DE_Q, DE_W, DE_E, DE_R, DE_T,                  DE_Z, DE_U, DE_I, DE_O,   DE_P, DE_UDIA,
     KC_LCTL, DE_A, DE_S, DE_D, DE_F, DE_G,                  DE_H, DE_J, DE_K, DE_L, DE_ODIA, DE_ADIA,
     KC_LSFT, DE_Y, DE_X, DE_C, DE_V, DE_B, KC_HOME, KC_END, DE_N, DE_M, DE_COMM, KC_DOT, KC_SLSH, KC_CAPS,
               LMAGIC,MO(_NAVIGATION), LT(_BRACKETS,KC_SPC), KC_LSFT,  LT(_EXTRA,KC_ENTER), TO(_COLEMAK)
  ),
  [_NAVIGATION] = LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______,  XXXXXXX, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX,                               XXXXXXX, KC_7,   KC_8,   KC_9,   KC_0,   KC_PGDN,
     _______,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                KC_RCBR, KC_4,   KC_5,   KC_6,   KC_PLUS, KC_PIPE,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         TO(0), _______,        KC_RBRC, KC_1,   KC_2,   KC_3,   DE_SS,   _______,
                                              _______, _______,  KC_DEL, KC_DEL, _______, KC_P0
  ),
  [_BRACKETS] = LAYOUT(
    KC_F12, KC_F1,    KC_F2,      KC_F3,      KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,      KC_F9,      KC_F10,  KC_F11,
     _______, XXXXXXX, XXXXXXX,    XXXXXXX,    DE_LABK, XXXXXXX,                         XXXXXXX, DE_RABK, XXXXXXX,    XXXXXXX,    XXXXXXX, QK_BOOT,
     _______, XXXXXXX, MACLCURLY,    ALGR(DE_5), DE_LPRN, XXXXXXX,                       XXXXXXX,  DE_RPRN, ALGR(DE_6), MACRCURLY, XXXXXXX, KC_BSLS,
     _______, XXXXXXX, ALGR(DE_7), XXXXXXX,    XXXXXXX, XXXXXXX,    TO(0), _______,      XXXXXXX, DE_EQL,  ALGR(DE_0), XXXXXXX,    XXXXXXX, XXXXXXX,
                                                _______, _______, KC_BSPC, KC_BSPC, QK_AREP, _______
  ),
  [_EXTRA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, KC_GRV, KC_TILD, KC_PLUS, DE_SECT,                       XXXXXXX, LSA(DE_7), KC_RCBR, XXXXXXX, XXXXXXX,  XXXXXXX,
     _______, DE_EQL,  DE_PERC, DE_EXLM, DE_DQUO, DE_DLR,                       DE_AMPR, DE_SLSH, DE_QUES, DE_HASH, ALGR(DE_7), XXXXXXX,
     _______, DE_ADIA, DE_ODIA, DE_UDIA, KC_PIPE, XXXXXXX,    TO(0), _______,   XXXXXXX, DE_BSLS, XXXXXXX, XXXXXXX, DE_PIPE,    XXXXXXX,
                                          _______, _______, _______, _______, _______, _______
  ),
  [_MEDIA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, KC_MUTE, KC_MSTP, KC_VOLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG,    XXXXXXX,
     _______, XXXXXXX,  KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                     XXXXXXX, RM_NEXT, RM_VALU, RM_HUEU, RM_SPDU,    XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX,    TO(0), _______,   XXXXXXX, RM_PREV, RM_VALD, RM_HUED, RM_SPDD,    XXXXXXX,
                                          _______, _______, _______, _______, _______, _______
  ),
  [_SPECIAL] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, XXXXXXX, KC_PASTE, KC_COPY, KC_CUT,                      XXXXXXX, RELOAD, KC_E, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    TO(0), _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
                                          _______, _______, _______, _______, _______, _______
  )
};
// clang-format on
