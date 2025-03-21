#include QMK_KEYBOARD_H

enum layer_names {
    _QW,
    _LW,
    _HI,
    _NAV,
    _CUR,
    _FKEYS,
    _TRNS
};

enum custom_keycodes {
    M_MUL = SAFE_RANGE,
    M_MDL,
    M_MDR,
    M_MUR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * ,-----------------------------------------.             .-----------------------------------------.
     * | NAV  | ` ~  |   W  |   E  |   R  |   T  |             |  Y   |   U  |   I  |   O  |  -   |  =   |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  |   Q  |   S  |   D  |   F  |   G  |             |  H   |  J   |   K  |   L  |   P  |  \   |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |ctrl/esc|  A |   X  |   C  |   V  |   B  |             |  N   |  M   |   ,  |   .  |   ;  |  '   |
     * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
     * | Shift|   Z  | Del  | GUI  | Low  | Bspc | Ctrl | Enter| Spc  | Hi   | GUI  | Alt  |  /   |Shift |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_QW] = LAYOUT(
        TG(_NAV),      KC_GRV, KC_W,   KC_E,    KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_MINS, KC_EQL,
        KC_TAB,        KC_Q,   KC_S,   KC_D,    KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    KC_P,    KC_BSLS,
        CTL_T(KC_ESC), KC_A,   KC_X,   KC_C,    KC_V,    KC_B,                      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SCLN, KC_QUOT,
        KC_LSFT,       KC_Z,   KC_DEL, KC_LGUI, MO(_LW), KC_BSPC, KC_RCTL, KC_ENT,  KC_SPC, MO(_HI), KC_RGUI, KC_RALT, KC_SLSH, KC_RSFT
    ),

    /* LOW  - numbers, missing or awkward programming keys
     Doubled 1 key allows lazy reach with ring finger.
     * ,-----------------------------------------.             .-----------------------------------------.
     * | FKeys|   1  |   2  |  3   |   4  |   5  |             |  6   |  7   |   8  |   9  |   0  |Ctrl-alt-del|
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  |   1  |  ]   |  (   |  )   |      |             |   *  |   (  |   )  |   [  |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Caps |  [   |      |  {   |   }  |  `   |             |   #  |   {  |   }  |      | ]    |      |
     * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
     * | Shift|      |      |      | Low  |      |      |      |      |  Hi  |      |      |      |Shift |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_LW] = LAYOUT(
        TG(_FKEYS), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    LCTL(LALT(KC_DEL)),
        _______,    KC_1,    KC_RBRC, KC_LPRN, KC_RPRN, XXXXXXX,                   KC_ASTR, KC_LPRN, KC_RPRN, KC_LBRC, XXXXXXX, XXXXXXX,
        KC_CAPS,    KC_LBRC, XXXXXXX, KC_LCBR, KC_RCBR, KC_TILD,                   KC_HASH, KC_LCBR, KC_RCBR, XXXXXXX, KC_RBRC, XXXXXXX,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* HI - Punctuation, shell and
     * url ://@.com  row on bottom,    && is opposite ||       ^$ are in regex order: ^.*$
     * Right hand nav keys work pretty well chorded with the Right hand Hi Key
     * ,-----------------------------------------.             .-----------------------------------------.
     * |FKEYS |   !  |   @  |   #  |   $  |   %  |             |  ^   |   &  |   *  |   (  |   )  |   +  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |  !   |  &   |  "|" |   $  |   %  |             |  Vol+|  Mute|      |      |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | CAPS |  ^   |   :  |   .  |   *  |   -  |             |  Vol-| Play | PgUp | Home | Up   | End  |
     * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
     * |      |   /  |      |      | Low  |      |      |      |      |  Hi  | PgDn | Left | Down |Right |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_HI] = LAYOUT(
        TG(_FKEYS), KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
        _______,    KC_EXLM, KC_AMPR, KC_PIPE, KC_DLR,  KC_PERC,                   KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_CAPS,    KC_CIRC, KC_COLN, KC_DOT,  KC_ASTR, KC_MINS,                   KC_VOLD, KC_PPLS, KC_PGUP, KC_HOME, KC_UP,   KC_END,
        _______,    KC_SLSH, _______, _______, TT(_LW), _______, _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* NAV - mouse &  navigation
     * gui left and right are line home/end, or fore & back in browser
     * Mouse buttons are reversed for comfort - bigger stretch is to the right button.
     *
     * ,-----------------------------------------.             .-----------------------------------------.
     * | NAV  |      |      | Up   |      |Gui-> |             | MwU  | MS_UL| MS_U |MS_UR |      |MsNorm|
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |Gui<- | Left | Down |Right | C^E  |             | BTN3 | MS_L |MS Up | MS_R |      |MsFast|
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      | C^A  | GUI X| GUI C| GUI_V|      |             | MWD  | M_DL |MS Dwn|MS_DR | Up   |MsSlow|
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | GuiZ |      |      | Low  |      |Enter | ButnR|ButnL |  Hi  |      | Left | Down | Right|
     * `-------------------------------------------------------------------------------------------------'
     */
    [_NAV] = LAYOUT(
        TG(_NAV), XXXXXXX,       XXXXXXX,    KC_UP,      XXXXXXX,    RGUI(KC_RGHT),                   KC_WH_U, M_MUL,   KC_MS_U, M_MUR,   XXXXXXX, KC_ACL2,
        _______,  RGUI(KC_LEFT), KC_LEFT,    KC_DOWN,    KC_RGHT,    LCTL(KC_E),                      KC_BTN3, KC_MS_L, KC_MS_U, KC_MS_R, XXXXXXX, KC_ACL1,
        _______,  LCTL(KC_A),    LGUI(KC_X), RGUI(KC_C), RGUI(KC_V), XXXXXXX,                         KC_WH_D, M_MDL,   KC_MS_D, M_MDR,   KC_UP,   KC_ACL0,
        _______,  RGUI(KC_Z),    _______,    _______,    _______,    _______,       KC_ENT,  KC_BTN2, KC_BTN1, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* FKEYS - Funtion keys & mac stuff
     * ,-----------------------------------------.             .-----------------------------------------.
     * | FKEYS| F1   | F2   | F3   |  F4  | F5   |             | F6   | F7   | F8   | F9   | F10  | Ctrl |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |  F11 | F12  |  F13 | F14  |  F15 | Alt  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |Qwerty|      |      |      |      |      |             |      |      |      |      |      | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |    . |RGBTog|  .   |      | LO   | Bspc |      |      |      | HI   |      |      |      |      |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_FKEYS] = LAYOUT(
        TG(_FKEYS), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_RCTL,
        _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_LALT,
        TO(_QW),    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        _______,    UG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* TRNS - skeleton for laters
     * ,-----------------------------------------.             .-----------------------------------------.
     * |   .  |   .  |   .  |   .  |   .  |   .  |             |  ^   |   &  |   *  |   (  |   )  |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |   .  |   .  |   .  |   .  |   .  |   .  |             |  6   |  7   |   8  |   9  |   0  |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |   .  |   .  |   .  |   .  |   .  |   .  |             |      |      |      |   .  |   ;  |  "   |
     * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
     * |    . |   .  |  .   | GUI  |  LO  |   .  |      |      | Spc  |  HI  | GUI  |  M0  |  /   | LSFT |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_TRNS] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // from  algernon's ErgoDox EZ layout,
        case M_MUL:
            if (record->event.pressed) {
                mousekey_on(KC_MS_UP);
                mousekey_on(KC_MS_LEFT);
            } else {
                mousekey_off(KC_MS_UP);
                mousekey_off(KC_MS_LEFT);
            }
            mousekey_send();
            return false;
        case M_MUR:
            if (record->event.pressed) {
                mousekey_on(KC_MS_UP);
                mousekey_on(KC_MS_RIGHT);
            } else {
                mousekey_off(KC_MS_UP);
                mousekey_off(KC_MS_RIGHT);
            }
            mousekey_send();
            return false;
        case M_MDL:
            if (record->event.pressed) {
                mousekey_on(KC_MS_DOWN);
                mousekey_on(KC_MS_LEFT);
            } else {
                mousekey_off(KC_MS_DOWN);
                mousekey_off(KC_MS_LEFT);
            }
            mousekey_send();
            return false;
        case M_MDR:
            if (record->event.pressed) {
                mousekey_on(KC_MS_DOWN);
                mousekey_on(KC_MS_RIGHT);
            } else {
                mousekey_off(KC_MS_DOWN);
                mousekey_off(KC_MS_RIGHT);
            }
            mousekey_send();
            return false;
        default:
            return true;
    }

    return true;
};

void LayerLEDSet(uint8_t layr) {
    switch (layr) {
        case _QW:
            // dim green
            rgblight_setrgb(0, 20, 0);
            break;
        case _LW:
            // deep purple
            rgblight_setrgb(20, 0, 35);
            break;
        case _HI:
            // light blue
           rgblight_setrgb(0, 20, 20);
            break;
        case _NAV:
            // yellowy orange
            rgblight_setrgb(25, 20, 0);
            break;
        case _FKEYS:
            // red
           rgblight_setrgb(20, 0, 0);
            break;
        default:
            // error
            rgblight_setrgb(20,2,20);
            break;
    }

    return;
}

// Bleah globals need to be initialized.
uint8_t old_layer = _QW;

void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    if (old_layer != layer) {
        LayerLEDSet(layer);
        old_layer = layer;
    }
}
