

enum my_layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _THUMB,
    _LOWER,
    _RAISE,
    _NUMPAD,
    _MOUSE,
    _FUNCTION,
    _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  KC_MAKE,
    KC_R2C1,
    KC_R2C2,
    KC_R2C3,
    KC_R2C4,
    KC_R2C5,
    KC_R3C1,
    KC_R3C2,
    KC_R3C3,
    KC_R3C4,
    KC_R3C5,
};
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_5x12(GRAVE_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPACE, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLASH, KC_DELETE, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, (QK_MOD_TAP | (((MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)&0x1F) << 8) | ((KC_UP)&0xFF)), (QK_MOD_TAP | (((MOD_RSFT)&0x1F) << 8) | ((KC_SLASH)&0xFF)), KC_LCTRL, KC_LGUI,KC_LALT, (QK_LAYER_TAP_TOGGLE | ((_LOWER)&0xFF)), KC_SPACE, KC_SPACE, KC_ENTER, KC_ENTER, (QK_LAYER_TAP_TOGGLE | ((_RAISE)&0xFF)), (QK_MOD_TAP | (((MOD_RALT)&0x1F) << 8) | ((KC_LEFT)&0xFF)), (QK_MOD_TAP | (((MOD_RGUI)&0x1F) << 8) | ((KC_DOWN)&0xFF)), (QK_MOD_TAP | (((MOD_RCTL)&0x1F) << 8) | ((KC_RIGHT)&0xFF)))





          ,
    [_COLEMAK] = LAYOUT_ortho_5x12(GRAVE_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPACE, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCOLON, KC_BSLASH, KC_DELETE, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOTE, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMMA, KC_DOT, (QK_MOD_TAP | (((MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)&0x1F) << 8) | ((KC_UP)&0xFF)), (QK_MOD_TAP | (((MOD_RSFT)&0x1F) << 8) | ((KC_SLASH)&0xFF)), KC_LCTRL, KC_LGUI,KC_LALT, (QK_LAYER_TAP_TOGGLE | ((_LOWER)&0xFF)), KC_SPACE, KC_SPACE, KC_ENTER, KC_ENTER, (QK_LAYER_TAP_TOGGLE | ((_RAISE)&0xFF)), (QK_MOD_TAP | (((MOD_RALT)&0x1F) << 8) | ((KC_LEFT)&0xFF)), (QK_MOD_TAP | (((MOD_RGUI)&0x1F) << 8) | ((KC_DOWN)&0xFF)), (QK_MOD_TAP | (((MOD_RCTL)&0x1F) << 8) | ((KC_RIGHT)&0xFF)))





 ,
    [_DVORAK] = LAYOUT_ortho_5x12(GRAVE_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPACE, KC_TAB, KC_QUOTE, KC_COMMA, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLASH, KC_DELETE, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_QUOTE, KC_LSHIFT, KC_SCOLON, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, (QK_MOD_TAP | (((MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)&0x1F) << 8) | ((KC_UP)&0xFF)), (QK_MOD_TAP | (((MOD_RSFT)&0x1F) << 8) | ((KC_Z)&0xFF)), KC_LCTRL, KC_LGUI,KC_LALT, (QK_LAYER_TAP_TOGGLE | ((_LOWER)&0xFF)), KC_SPACE, KC_SPACE, KC_ENTER, KC_ENTER, (QK_LAYER_TAP_TOGGLE | ((_RAISE)&0xFF)), (QK_MOD_TAP | (((MOD_RALT)&0x1F) << 8) | ((KC_LEFT)&0xFF)), (QK_MOD_TAP | (((MOD_RGUI)&0x1F) << 8) | ((KC_DOWN)&0xFF)), (QK_MOD_TAP | (((MOD_RCTL)&0x1F) << 8) | ((KC_RIGHT)&0xFF)))





 ,
    [_THUMB] = LAYOUT_ortho_5x12(GRAVE_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPACE, KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLASH, KC_DELETE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOTE, KC_LSHIFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, (QK_MOD_TAP | (((MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)&0x1F) << 8) | ((KC_UP)&0xFF)), (QK_MOD_TAP | (((MOD_RSFT)&0x1F) << 8) | ((_______)&0xFF)), KC_LCTRL, KC_LGUI,KC_LALT, KC_MINUS, (QK_LAYER_TAP_TOGGLE | ((_LOWER)&0xFF)), KC_SPACE, KC_ENTER, (QK_LAYER_TAP_TOGGLE | ((_RAISE)&0xFF)), KC_EQUAL, (QK_MOD_TAP | (((MOD_RALT)&0x1F) << 8) | ((KC_LEFT)&0xFF)), (QK_MOD_TAP | (((MOD_RGUI)&0x1F) << 8) | ((KC_DOWN)&0xFF)), (QK_MOD_TAP | (((MOD_RCTL)&0x1F) << 8) | ((KC_RIGHT)&0xFF)))





 ,
    [_LOWER] = LAYOUT_ortho_5x12(KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_BSPACE, KC_INSERT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_EQUAL, KC_DELETE, (QK_LCTL | (KC_A)),_______, _______, _______,(QK_LCTL | (KC_D)), _______, (QK_LSFT | (KC_MINUS)), (QK_LSFT | (KC_EQUAL)), (QK_LSFT | (KC_LBRACKET)), (QK_LSFT | (KC_RBRACKET)), (QK_LSFT | (KC_EQUAL)), KC_PASTE, (QK_LCTL | (KC_Z)),(QK_LSFT | (KC_DELETE)),(QK_LCTL | (KC_INSERT)),(QK_LSFT | (KC_INSERT)),(QK_LCTL | (KC_B)), (QK_LSFT | (KC_NONUS_HASH)), (QK_LSFT | (KC_NONUS_BSLASH)), (QK_LSFT | (KC_COMMA)), (QK_LSFT | (KC_DOT)), KC_PGUP, KC_NO, _______,(QK_TOGGLE_LAYER | ((_NUMPAD)&0xFF)) ,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDOWN,KC_END)




                                                                                                      ,
    [_RAISE] = LAYOUT_ortho_5x12(KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPACE, KC_INSERT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_DELETE, (QK_LCTL | (KC_A)),_______, _______, _______,(QK_LCTL | (KC_D)), _______, KC_MINUS, KC_EQUAL, KC_LBRACKET, KC_RBRACKET, KC_BSLASH, _______, (QK_LCTL | (KC_Z)),(QK_LSFT | (KC_DELETE)),(QK_LCTL | (KC_INSERT)),(QK_LSFT | (KC_INSERT)),(QK_LCTL | (KC_B)), _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_UP, RGB_TOG, _______, (QK_TOGGLE_LAYER | ((_NUMPAD)&0xFF)) , _______,_______, _______, _______, _______, _______, _______, KC_MEDIA_STOP, KC_AUDIO_VOL_DOWN, KC_MEDIA_PLAY_PAUSE)




                                                                                                                   ,

    [_FUNCTION] = LAYOUT_ortho_5x12(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, _______, _______, KC_R2C1, KC_R2C2, KC_R2C3, KC_R2C4, KC_R2C5, _______, _______, _______, _______, _______, _______, _______, KC_R3C1, KC_R3C2, KC_R3C3, KC_R3C4, KC_R3C5, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)




                                                                                                                  ,


    [_NUMPAD] = LAYOUT_ortho_5x12(_______, _______, _______, _______, _______, _______, KC_NUMLOCK, KC_KP_7, KC_KP_8, KC_KP_9, (QK_TOGGLE_LAYER | ((_NUMPAD)&0xFF)), _______, _______, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, KC_MS_WH_UP, _______, KC_KP_SLASH, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN, _______, KC_KP_MINUS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_PLUS, _______, _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, _______, _______, _______, KC_KP_ENTER, KC_KP_0, KC_KP_DOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)




                                                                                                                  ,

    [_ADJUST] = LAYOUT_ortho_5x12(KC_ESCAPE, QWERTY, COLEMAK, DVORAK, KC_PSCREEN, KC_NUMLOCK, RGB_SPI, RGB_SPD, RGB_MODE_FORWARD, RGB_MODE_REVERSE, RGB_TOG, _______, KC_MAKE, RESET, DEBUG, KC_NO, KC_NO, KC_NO, RGB_VAI, RGB_VAD, RGB_MODE_RAINBOW, RGB_MODE_PLAIN, RGB_MODE_BREATHE, _______, _______, CMB_ON, MU_MOD, AU_ON, AU_OFF, MAGIC_UNSWAP_ALT_GUI, RGB_HUI, RGB_HUD, RGB_MODE_KNIGHT, RGB_MODE_SWIRL, RGB_MODE_SNAKE, _______, _______, MUV_DE, MUV_IN, MU_ON, MU_OFF, MAGIC_SWAP_ALT_GUI, RGB_SAI, RGB_SAD, RGB_MODE_RGBTEST, RGB_MODE_XMAS, RGB_MODE_GRADIENT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)




                                                                                                                   ,

};
