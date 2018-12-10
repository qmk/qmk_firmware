#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "sendstring_dvorak.h"
#include "keymap_plover.h"
#include "keymap_plover_dvorak.h"


#define SCTL(kc) LSFT(LCTL(kc))

// Layers
enum layers {
    DVORAK_US = 0,
    PLOVER_US,
    GAMING_US,
    ARROWS_US,
    MOUSE_US,
    NUMPAD_US,
    LAYERS_US,
    DVORAK_DV,
    PLOVER_DV,
    GAMING_DV,
    ARROWS_DV,
    MOUSE_DV,
    NUMPAD_DV,
    LAYERS_DV,
    MEDIA_FN,
    HYPER_FN,
    MEH_FN,
    MEH_FN_PLUS,
    FIRMWARE
};

int CAPS_LOCK   = 0;
int NUM_LOCK    = 0;
int SCROLL_LOCK = 0;

enum tap_dances {
    TD_ESC_CAPS = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CLCK)
};


enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    RGB_GREEN  // to set default RGB layer as green once
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,--------------------------------------------------.    ,--------------------------------------------------.
     * |    0   |   1  |   2  |   3  |   4  |   5  |  6   |    |  38  |  39  |  40  |  41  |  42  |  43  |   44   |
     * |--------+------+------+------+------+------+------|    |------+------+------+------+------+------+--------|
     * |    7   |   8  |   9  |  10  |  11  |  12  |  13  |    |  45  |  46  |  47  |  48  |  49  |  50  |   51   |
     * |--------+------+------+------+------+------|      |    |      |------+------+------+------+------+--------|
     * |   14   |  15  |  16  |  17  |  18  |  19  |------|    |------|  52  |  53  |  54  |  55  |  56  |   57   |
     * |--------+------+------+------+------+------|  26  |    |  58  |------+------+------+------+------+--------|
     * |   20   |  21  |  22  |  23  |  24  |  25  |      |    |      |  59  |  60  |  61  |  62  |  63  |   64   |
     * `--------+------+------+------+------+-------------'    `-------------+------+------+------+------+--------'
     *   |  27  |  28  |  29  |  30  |  31  |                                |  65  |  66  |  67  |  68  |  69  |
     *   `----------------------------------'                                `----------------------------------'
     *                                       ,-------------.  ,-------------.
     *                                       |  32  |  33  |  |  70  |  71  |
     *                                ,------+------+------|  |------+------+------.
     *                                |      |      |  34  |  |  72  |      |      |
     *                                |  35  |  36  |------|  |------|  74  |  75  |
     *                                |      |      |  37  |  |  73  |      |      |
     *                                `--------------------'  `--------------------'
     */
    [DVORAK_US] = LAYOUT_ergodox(
        // left hand
        KC_ESC,     KC_LABK,         KC_LCBR,         KC_LBRC,             KC_LPRN,             KC_EXLM, KC_AMPR,
        KC_TAB,     KC_QUOT,         SCMD_T(KC_COMM), MEH_T(KC_DOT),       ALL_T(KC_P),         KC_Y,    KC_AT,
        KC_EQL,     CTL_T(KC_A),     SFT_T(KC_O),     LT(NUMPAD_US, KC_E), LT(ARROWS_US, KC_U), KC_I,
        KC_BSLS,    ALGR_T(KC_SCLN), ALT_T(KC_Q),     LT(MEDIA_FN, KC_J),  GUI_T(KC_K),         KC_X,    KC_PERC,
        MO(MEH_FN), TG(LAYERS_US),   KC_CIRC,         KC_PLUS,             KC_COLN,

        // left thumb
                KC_LEFT, KC_RGHT,
                         KC_HOME,
        KC_SPC, KC_BSPC, KC_END,

        // right hand
        KC_PIPE, KC_QUES, KC_RPRN,            KC_RBRC,            KC_RCBR,      KC_RABK,       KC_ASTR,
        KC_HASH, KC_F,    ALL_T(KC_G),        MEH_T(KC_C),        SCMD_T(KC_R), KC_L,          KC_SLSH,
                 KC_D,    LT(MOUSE_US, KC_H), LT(HYPER_FN, KC_T), SFT_T(KC_N),  CTL_T(KC_S),   KC_MINS,
        KC_DLR,  KC_B,    GUI_T(KC_M),        LT(MEDIA_FN, KC_W), ALT_T(KC_V),  ALGR_T(KC_Z),  KC_GRV,
                          KC_DQUO,            KC_UNDS,            KC_TILD,      TG(DVORAK_DV), MO(MEH_FN_PLUS),

        // right thumb
        KC_UP,   KC_DOWN,
        KC_PGUP,
        KC_PGDN, KC_DEL,  KC_ENT
    ),

    [PLOVER_US] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,    XXXXXXX,       KC_MS_BTN2, KC_MS_UP,   KC_MS_BTN1,  KC_MS_BTN3, GUI_T(KC_NO),
        KC_ESC,     KC_MS_BTN4,    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN5, PV_NUM,
        KC_TAB,     PV_LS,         PV_LT,      PV_LP,      PV_LH,       PV_STAR,
        KC_CLCK,    PV_LS,         PV_LK,      PV_LW,      PV_LR,       PV_STAR,    PV_STAR,
        MO(MEH_FN), TG(LAYERS_US), PV_NUM,     PV_NUM,     PV_NUM,

        // left thumb
              KC_SPACE, KC_BSPACE,
                        KC_HOME,
        PV_A, PV_O,     KC_END,

        // right hand
        KC_MS_ACCEL2, KC_MS_ACCEL1,  KC_MS_ACCEL0, KC_UP,   KC_APPLICATION, XXXXXXX,        KC_MS_WH_UP,
        PV_NUM,       KC_MS_WH_LEFT, KC_LEFT,      KC_DOWN, KC_RIGHT,       KC_MS_WH_RIGHT, KC_MS_WH_DOWN,
                      PV_STAR,       PV_RF,        PV_RP,   PV_RL,          PV_RT,          PV_RD,
        PV_STAR,      PV_STAR,       PV_RR,        PV_RB,   PV_RG,          PV_RS,          PV_RZ,
                                     PV_NUM,       PV_NUM,  PV_NUM,         PV_NUM,         MO(MEH_FN_PLUS),

        // right thumb
        KC_DELETE, KC_ENTER,
        KC_PGUP,
        KC_PGDOWN, PV_E,     PV_U
    ),

    [GAMING_US] = LAYOUT_ergodox(
        // left hand
        KC_ESCAPE,            GUI_T(KC_MINS), KC_I,     KC_O,   KC_P,   ALGR_T(KC_EQL), KC_T,
        KC_TAB,               KC_LALT,        KC_Q,     KC_W,   KC_E,   ALL_T(KC_R),    KC_G,
        LT(MOUSE_US, KC_GRV), KC_LCTRL,       KC_A,     KC_S,   KC_D,   MEH_T(KC_F),
        KC_BSLS,              KC_LSHIFT,      KC_Z,     KC_X,   KC_C,   SCMD_T(KC_V),   KC_M,
        MO(MEH_FN),           TG(LAYERS_US),  KC_COMM, KC_DOT, KC_LBRC,

        // left thumb
                   MO(MEDIA_FN), KC_NLCK,
                                 KC_SCLN,
         KC_SPACE, KC_ENTER,     KC_BSPACE,

        // right hand
        KC_QUOT,       KC_Y,       KC_K,        KC_U,        KC_KP_7, KC_KP_8,  KC_KP_9,
        KC_MS_WH_UP,   KC_H,       KC_J,        KC_L,        KC_KP_4, KC_KP_2,  KC_KP_6,
                       KC_B,       KC_MS_UP,    KC_N,        KC_KP_1, KC_KP_5,  KC_KP_3,
        KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT, KC_UP,   KC_KP_0,  KC_SLASH,
                                   KC_RBRC,     KC_LEFT,     KC_DOWN, KC_RIGHT, MO(MEH_FN_PLUS),

        // right thumb
        KC_MS_BTN5, MO(HYPER_FN),
        KC_MS_BTN4,
        KC_MS_BTN3, KC_MS_BTN2,   KC_MS_BTN1
    ),

    [ARROWS_US] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, SCMD_T(KC_NO), MEH_T(KC_NO), ALL_T(KC_NO), XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTRL,      KC_LSHIFT,    XXXXXXX,      _______,    XXXXXXX,
        XXXXXXX, KC_RALT,       KC_LALT,      GUI_T(KC_NO), XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPACE, KC_END,

        // right hand
        LGUI(KC_X), XXXXXXX,       LCTL(KC_X), KC_MS_WH_UP,   XXXXXXX,       XXXXXXX,        XXXXXXX,
        LGUI(KC_C), XXXXXXX,       LCTL(KC_C), KC_UP,         SCTL(KC_C),    LCTL(KC_Z),     LGUI(KC_Z),
                    KC_MS_WH_LEFT, KC_LEFT,    KC_DOWN,       KC_RIGHT,      KC_MS_WH_RIGHT, KC_APPLICATION,
        LGUI(KC_V), XXXXXXX,       LCTL(KC_V), KC_MS_WH_DOWN, SCTL(KC_V),    LCTL(KC_Y),     SGUI(KC_Z),
        XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,       KC_SLCK,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDOWN, KC_DELETE, KC_ENTER
    ),

    [MOUSE_US] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,       XXXXXXX,       XXXXXXX,    KC_MS_WH_UP,   LCTL(KC_X),  XXXXXXX,        LGUI(KC_X),
        LGUI(KC_Z),    LCTL(KC_Z),    SCTL(KC_C), KC_MS_UP,      LCTL(KC_C),  KC_MS_BTN4,     LGUI(KC_C),
        KC_MS_BTN3,    KC_MS_WH_LEFT, KC_MS_LEFT, KC_MS_DOWN,    KC_MS_RIGHT, KC_MS_WH_RIGHT,
        LGUI(KC_Z),    LCTL(KC_Y),    SCTL(KC_V), KC_MS_WH_DOWN, LCTL(KC_V),  KC_MS_BTN5,     LGUI(KC_V),
        KC_SLCK, XXXXXXX,       XXXXXXX,    XXXXXXX,       XXXXXXX,

        // left thumb
                    XXXXXXX,    XXXXXXX,
                                XXXXXXX,
        KC_MS_BTN1, KC_MS_BTN2, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, ALL_T(KC_NO), MEH_T(KC_NO), SCMD_T(KC_NO), XXXXXXX,
                 XXXXXXX, _______, KC_MS_ACCEL1, KC_LSHIFT,    KC_LCTRL,      KC_MS_ACCEL2,
        XXXXXXX, XXXXXXX, XXXXXXX, GUI_T(KC_NO), KC_LALT,      KC_RALT,       XXXXXXX,
                          XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MS_ACCEL0
    ),

    [NUMPAD_US] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  GUI_T(KC_NO), XXXXXXX, ALL_T(KC_NO),  XXXXXXX, XXXXXXX,
        _______, KC_LCTRL, KC_LSHIFT,    _______, MEH_T(KC_NO),  XXXXXXX,
        XXXXXXX, KC_RALT,  KC_LALT,      XXXXXXX, SCMD_T(KC_NO), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPACE, KC_END,

        // right hand
        KC_X, KC_A, KC_B,   KC_C, KC_D,     KC_E,    KC_F,
        KC_O, KC_I, KC_1,   KC_2, KC_3,     KC_SLSH, KC_PERC,
              KC_M, KC_4,   KC_5, KC_6,     KC_PLUS, KC_MINS,
        KC_L, KC_J, KC_7,   KC_8, KC_9,     KC_ASTR, KC_CIRC,
                    KC_DOT, KC_0, KC_COMM, KC_UNDS,  KC_BSLS,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDOWN, KC_DELETE, KC_ENTER
    ),

    [LAYERS_US] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                 XXXXXXX, TO(DVORAK_US), TO(PLOVER_US), TO(GAMING_US), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [DVORAK_DV] = LAYOUT_ergodox(
        // left hand
        KC_ESC,     DV_LABK,         DV_LCBR,         DV_LBRC,             DV_LPRN,             DV_EXLM, DV_AMPR,
        KC_TAB,     DV_QUOT,         SCMD_T(DV_COMM), MEH_T(DV_DOT),       ALL_T(DV_P),         DV_Y,    DV_AT,
        DV_EQL,     CTL_T(DV_A),     SFT_T(DV_O),     LT(NUMPAD_DV, DV_E), LT(ARROWS_DV, DV_U), DV_I,
        DV_BSLS,    ALGR_T(DV_SCLN), ALT_T(DV_Q),     LT(MEDIA_FN, DV_J),  GUI_T(DV_K),         DV_X,    DV_PERC,
        MO(MEH_FN), TG(LAYERS_DV),   DV_CIRC,         DV_PLUS,             DV_COLN,

        // left thumb
                KC_LEFT, KC_RGHT,
                         KC_HOME,
        KC_SPC, KC_BSPC, KC_END,

        // right hand
        DV_PIPE, DV_QUES, DV_RPRN,            DV_RBRC,            DV_RCBR,      DV_RABK,      DV_ASTR,
        DV_HASH, DV_F,    ALL_T(DV_G),        MEH_T(DV_C),        SCMD_T(DV_R), DV_L,         DV_SLSH,
                 DV_D,    LT(MOUSE_DV, DV_H), LT(HYPER_FN, DV_T), SFT_T(DV_N),  CTL_T(DV_S),  DV_MINS,
        DV_DLR,  DV_B,    GUI_T(DV_M),        LT(MEDIA_FN, DV_W), ALT_T(DV_V),  ALGR_T(DV_Z), DV_GRV,
                          DV_DQUO,            DV_UNDS,            DV_TILD,      _______,      MO(MEH_FN_PLUS),

        // right thumb
        KC_UP,   KC_DOWN,
        KC_PGUP,
        KC_PGDN, KC_DEL,  KC_ENT
    ),

    [PLOVER_DV] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,    XXXXXXX,       KC_MS_BTN2, KC_MS_UP,   KC_MS_BTN1,  KC_MS_BTN3, GUI_T(KC_NO),
        KC_ESC,     KC_MS_BTN4,    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN5, PD_NUM,
        KC_TAB,     PD_LS,         PD_LT,      PD_LP,      PD_LH,       PD_STAR,
        KC_CLCK,    PD_LS,         PD_LK,      PD_LW,      PD_LR,       PD_STAR,    PD_STAR,
        MO(MEH_FN), TG(LAYERS_DV), PD_NUM,     PD_NUM,     PD_NUM,

        // left thumb
              KC_SPACE, KC_BSPACE,
                        KC_HOME,
        PD_A, PD_O,     KC_END,

        // right hand
        KC_MS_ACCEL2, KC_MS_ACCEL1,  KC_MS_ACCEL0, KC_UP,   KC_APPLICATION, XXXXXXX,        KC_MS_WH_UP,
        PD_NUM,       KC_MS_WH_LEFT, KC_LEFT,      KC_DOWN, KC_RIGHT,       KC_MS_WH_RIGHT, KC_MS_WH_DOWN,
                      PD_STAR,       PD_RF,        PD_RP,   PD_RL,          PD_RT,          PD_RD,
        PD_STAR,      PD_STAR,       PD_RR,        PD_RB,   PD_RG,          PD_RS,          PD_RZ,
                                     PD_NUM,       PD_NUM,  PD_NUM,         PD_NUM,         MO(MEH_FN_PLUS),

        // right thumb
        KC_DELETE, KC_ENTER,
        KC_PGUP,
        KC_PGDOWN, PD_E,     PD_U
    ),

    [GAMING_DV] = LAYOUT_ergodox(
        // left hand
        KC_ESCAPE,            GUI_T(DV_MINS), DV_I,    DV_O,   DV_P,    ALGR_T(DV_EQL), DV_T,
        KC_TAB,               KC_LALT,        DV_Q,    DV_W,   DV_E,    ALL_T(DV_R),    DV_G,
        LT(MOUSE_DV, DV_GRV), KC_LCTRL,       DV_A,    DV_S,   DV_D,    MEH_T(DV_F),
        DV_BSLS,              KC_LSHIFT,      DV_Z,    DV_X,   DV_C,    SCMD_T(DV_V),   DV_M,
        MO(MEH_FN),           TG(LAYERS_DV),  DV_COMM, DV_DOT, DV_LBRC,

        // left thumb
                   MO(MEDIA_FN), KC_NLCK,
                                 DV_SCLN,
         KC_SPACE, KC_ENTER,     KC_BSPACE,

        // right hand
        DV_QUOT,       DV_Y,       DV_K,       DV_U,        KC_KP_7, KC_KP_8,  KC_KP_9,
        KC_MS_WH_UP,   DV_H,       DV_J,       DV_L,        KC_KP_4, KC_KP_2,  KC_KP_6,
                       DV_B,       KC_MS_UP,   DV_N,        KC_KP_1, KC_KP_5,  KC_KP_3,
        KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_UP,   KC_KP_0,  DV_SLSH,
                                   DV_RBRC,    KC_LEFT,     KC_DOWN, KC_RIGHT, MO(MEH_FN_PLUS),

        // right thumb
        KC_MS_BTN5, MO(HYPER_FN),
        KC_MS_BTN4,
        KC_MS_BTN3, KC_MS_BTN2,   KC_MS_BTN1
    ),

    [ARROWS_DV] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, SCMD_T(KC_NO), MEH_T(KC_NO), ALL_T(KC_NO), XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTRL,      KC_LSHIFT,    XXXXXXX,      _______, XXXXXXX,
        XXXXXXX, KC_RALT,       KC_LALT,      GUI_T(KC_NO), XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPACE, KC_END,

        // right hand
        LGUI(DV_X), XXXXXXX,       LCTL(DV_X), KC_MS_WH_UP,   XXXXXXX,       XXXXXXX,        XXXXXXX,
        LGUI(DV_C), XXXXXXX,       LCTL(DV_C), KC_UP,         SCTL(DV_C),    LCTL(DV_Z),     LGUI(DV_Z),
                    KC_MS_WH_LEFT, KC_LEFT,    KC_DOWN,       KC_RIGHT,      KC_MS_WH_RIGHT, KC_APPLICATION,
        LGUI(DV_V), XXXXXXX,       LCTL(DV_V), KC_MS_WH_DOWN, SCTL(DV_V),    LCTL(DV_Y),     SGUI(DV_Z),
        XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,       KC_SLCK,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDOWN, KC_DELETE, KC_ENTER
    ),

    [MOUSE_DV] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,       XXXXXXX,       XXXXXXX,    KC_MS_WH_UP,   LCTL(DV_X),  XXXXXXX,        LGUI(DV_X),
        LGUI(DV_Z),    LCTL(DV_Z),    SCTL(DV_C), KC_MS_UP,      LCTL(DV_C),  KC_MS_BTN4,     LGUI(DV_C),
        KC_MS_BTN3,    KC_MS_WH_LEFT, KC_MS_LEFT, KC_MS_DOWN,    KC_MS_RIGHT, KC_MS_WH_RIGHT,
        LGUI(DV_Z),    LCTL(DV_Y),    SCTL(DV_V), KC_MS_WH_DOWN, LCTL(DV_V),  KC_MS_BTN5,     LGUI(DV_V),
        KC_SLCK, XXXXXXX,       XXXXXXX,    XXXXXXX,       XXXXXXX,

        // left thumb
                    XXXXXXX,    XXXXXXX,
                                XXXXXXX,
        KC_MS_BTN1, KC_MS_BTN2, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, ALL_T(KC_NO), MEH_T(KC_NO), SCMD_T(KC_NO), XXXXXXX,
                 XXXXXXX, _______, KC_MS_ACCEL1, KC_LSHIFT,    KC_LCTRL,      KC_MS_ACCEL2,
        XXXXXXX, XXXXXXX, XXXXXXX, GUI_T(KC_NO), KC_LALT,      KC_RALT,       XXXXXXX,
                          XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MS_ACCEL0
    ),

    [NUMPAD_DV] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  GUI_T(KC_NO), XXXXXXX, ALL_T(KC_NO),  XXXXXXX, XXXXXXX,
        _______, KC_LCTRL, KC_LSHIFT,    _______, MEH_T(KC_NO),  XXXXXXX,
        XXXXXXX, KC_RALT,  KC_LALT,      XXXXXXX, SCMD_T(KC_NO), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPACE, KC_END,

        // right hand
        DV_X, DV_A, DV_B,   DV_C, DV_D,    DV_E,    DV_F,
        DV_O, DV_I, DV_1,   DV_2, DV_3,    DV_SLSH, DV_PERC,
              DV_M, DV_4,   DV_5, DV_6,    DV_PLUS, DV_MINS,
        DV_L, DV_J, DV_7,   DV_8, DV_9,    DV_ASTR, DV_CIRC,
                    DV_DOT, DV_0, DV_COMM, DV_UNDS, DV_BSLS,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDOWN, KC_DELETE, KC_ENTER
    ),

    [LAYERS_DV] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                 XXXXXXX, TO(DVORAK_DV), TO(PLOVER_DV), TO(GAMING_DV), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MEDIA_FN] = LAYOUT_ergodox(
        // left hand
        KC_AUDIO_VOL_DOWN,   KC_AUDIO_MUTE, RGB_TOG,    XXXXXXX, KC_MAIL,      KC_FIND, KC_WWW_REFRESH,
        KC_MEDIA_PREV_TRACK, KC_F9,         KC_F7,      KC_F5,   KC_F3,        KC_F1,   KC_WWW_HOME,
        KC_PAUSE,            KC_F19,        KC_F17,     KC_F15,  KC_F13,       KC_F11,
        RGB_HUD,             XXXXXXX,       XXXXXXX,    _______, KC_F23,       KC_F21,  KC_WWW_BACK,
        RGB_VAD,             KC_CLCK,       KC_PSCREEN, XXXXXXX, MO(FIRMWARE),

        // left thumb
                 _______, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MEDIA_EJECT,

        // right hand
        KC_WWW_FAVORITES, KC_MY_COMPUTER, KC_CALCULATOR,   XXXXXXX, RGB_MOD,         RGB_M_P,        KC_AUDIO_VOL_UP,
        KC_WWW_SEARCH,    KC_F2,          KC_F4,           KC_F6,   KC_F8,           KC_F10,         KC_MEDIA_NEXT_TRACK,
                          KC_F12,         KC_F14,          KC_F16,  KC_F18,          KC_F20,         KC_MEDIA_PLAY_PAUSE,
        KC_WWW_FORWARD,   KC_F22,         KC_F24,          _______, XXXXXXX,         XXXXXXX,        RGB_HUI,
                                          KC_SYSTEM_POWER, XXXXXXX, KC_SYSTEM_SLEEP, KC_SYSTEM_WAKE, RGB_VAI,

        // right thumb
        XXXXXXX,   XXXXXXX,
        XXXXXXX,
        RGB_GREEN, XXXXXXX, XXXXXXX
    ),

    [HYPER_FN] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, HYPR(KC_F1),  HYPR(KC_F2),  HYPR(KC_F3),  HYPR(KC_F4),  HYPR(KC_F5),  XXXXXXX,
        XXXXXXX, HYPR(KC_F6),  HYPR(KC_F7),  HYPR(KC_F8),  HYPR(KC_F9),  HYPR(KC_F10), XXXXXXX,
        XXXXXXX, HYPR(KC_F11), HYPR(KC_F12), HYPR(KC_F13), HYPR(KC_F14), HYPR(KC_F15),
        XXXXXXX, HYPR(KC_F16), HYPR(KC_F17), HYPR(KC_F18), HYPR(KC_F19), HYPR(KC_F20), XXXXXXX,
        XXXXXXX, HYPR(KC_F21), HYPR(KC_F22), HYPR(KC_F23), HYPR(KC_F24),

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, _______,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MEH_FN] = LAYOUT_ergodox(
        // left hand
        LCA(KC_F11),  LCA(KC_F9),  LCA(KC_F7),  LCA(KC_F5),  LCA(KC_F3),  LCA(KC_F1),  XXXXXXX,
        LCAG(KC_F11), LCAG(KC_F9), LCAG(KC_F7), LCAG(KC_F5), LCAG(KC_F3), LCAG(KC_F1), XXXXXXX,
        MEH(KC_F11),  MEH(KC_F9),  MEH(KC_F7),  MEH(KC_F5),  MEH(KC_F3),  MEH(KC_F1),
        SGUI(KC_F11), SGUI(KC_F9), SGUI(KC_F7), SGUI(KC_F5), SGUI(KC_F3), SGUI(KC_F1), XXXXXXX,
        _______,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, LCA(KC_F2),  LCA(KC_F4),  LCA(KC_F6),  LCA(KC_F8),  LCA(KC_F10),  LCA(KC_F12),
        XXXXXXX, LCAG(KC_F2), LCAG(KC_F4), LCAG(KC_F6), LCAG(KC_F8), LCAG(KC_F10), LCAG(KC_F12),
                 MEH(KC_F2),  MEH(KC_F4),  MEH(KC_F6),  MEH(KC_F8),  MEH(KC_F10),  MEH(KC_F12),
        XXXXXXX, SGUI(KC_F2), SGUI(KC_F4), SGUI(KC_F6), SGUI(KC_F8), SGUI(KC_F10), SGUI(KC_F12),
                              XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,      XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MEH_FN_PLUS] = LAYOUT_ergodox(
        // left hand
        LCA(KC_F23),  LCA(KC_F21),  LCA(KC_F19),  LCA(KC_F17),  LCA(KC_F15),  LCA(KC_F13),  XXXXXXX,
        LCAG(KC_F23), LCAG(KC_F21), LCAG(KC_F19), LCAG(KC_F17), LCAG(KC_F15), LCAG(KC_F13), XXXXXXX,
        MEH(KC_F23),  MEH(KC_F21),  MEH(KC_F19),  MEH(KC_F17),  MEH(KC_F15),  MEH(KC_F13),
        SGUI(KC_F23), SGUI(KC_F21), SGUI(KC_F19), SGUI(KC_F17), SGUI(KC_F15), SGUI(KC_F13), XXXXXXX,
        XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, LCA(KC_F14),  LCA(KC_F16),  LCA(KC_F18),  LCA(KC_F20),  LCA(KC_F22),  LCA(KC_F24),
        XXXXXXX, LCAG(KC_F14), LCAG(KC_F16), LCAG(KC_F18), LCAG(KC_F20), LCAG(KC_F22), LCAG(KC_F24),
                 MEH(KC_F14),  MEH(KC_F16),  MEH(KC_F18),  MEH(KC_F20),  MEH(KC_F22),  MEH(KC_F24),
        XXXXXXX, SGUI(KC_F14), SGUI(KC_F16), SGUI(KC_F18), SGUI(KC_F20), SGUI(KC_F22), SGUI(KC_F24),
                               XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      _______,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FIRMWARE] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,

        // left thumb
               XXXXXXX, XXXXXXX,
                        XXXXXXX,
        RESET, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, EEP_RST
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_GREEN:
            if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                    rgblight_enable();
                    rgblight_mode(1);
                    rgblight_sethsv_red();
                #endif
            }

            return false;

        case KC_CLCK:
            if (record->event.pressed) {
                if (!(CAPS_LOCK)) {
                    ergodox_right_led_1_on();
                    CAPS_LOCK = 1;
                } else {
                    ergodox_right_led_1_off();
                    CAPS_LOCK = 0;
                }
            }

            return true;

        case KC_NLCK:
            if (record->event.pressed) {
                if (!(NUM_LOCK)) {
                    ergodox_right_led_2_on();
                    NUM_LOCK = 1;
                } else {
                    ergodox_right_led_2_off();
                    NUM_LOCK = 0;
                }
            }

            return true;

        case KC_SLCK:
            if (record->event.pressed) {
                if (!(SCROLL_LOCK)) {
                    ergodox_right_led_3_on();
                    SCROLL_LOCK = 1;
                } else {
                    ergodox_right_led_3_off();
                    SCROLL_LOCK = 0;
                }
            }

        case KC_MS_WH_LEFT:
            if (record->event.pressed) {
                if (SCROLL_LOCK) {
                    return false;
                } else {
                    return true;
                }
            }

        case KC_MS_WH_UP:
            if (record->event.pressed) {
                if (SCROLL_LOCK) {
                    return false;
                } else {
                    return true;
                }
            }

        case KC_MS_WH_DOWN:
            if (record->event.pressed) {
                if (SCROLL_LOCK) {
                    return false;
                } else {
                    return true;
                }
            }

        case KC_MS_WH_RIGHT:
            if (record->event.pressed) {
                if (SCROLL_LOCK) {
                    return false;
                } else {
                    return true;
                }
            }

        default:
            return true;
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);

    switch (layer) {
        case DVORAK_US:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

            break;

        case PLOVER_US:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);

            break;

        case GAMING_US:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);

            break;

        case ARROWS_US:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case MOUSE_US:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case NUMPAD_US:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case LAYERS_US:
            rgblight_sethsv_noeeprom_cyan();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case DVORAK_DV:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;

        case PLOVER_DV:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);

            break;

        case GAMING_DV:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);

            break;

        case ARROWS_DV:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case MOUSE_DV:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case NUMPAD_DV:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case LAYERS_DV:
            rgblight_sethsv_noeeprom_cyan();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case MEDIA_FN:
            rgblight_sethsv_noeeprom_yellow();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case HYPER_FN:
            rgblight_sethsv_noeeprom_magenta();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        case MEH_FN:
            rgblight_sethsv_noeeprom_magenta();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 4);

            break;

        case MEH_FN_PLUS:
            rgblight_sethsv_noeeprom_magenta();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 5);

            break;

        case FIRMWARE:
            rgblight_sethsv_noeeprom_pink();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            break;

        default:
            break;
    }

    return state;
};
