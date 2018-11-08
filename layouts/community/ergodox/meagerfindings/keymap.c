#include QMK_KEYBOARD_H
#include "version.h"

enum {
  BASE = 0,
  OLD_BASE,
  SYMBL,
  MEDIA,
  MKDWN,
  ARROWS,
  NUM,
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  MD_LINK,
  XKCD,
  DBLE_ZER0,
  L_ID_0,
  L_ID_1,
  L_ID_2,
  PAST_PS,
  TODO,
  RUBYMINE,
  ZENDESK,
  DBLE_ASTR,
  TRPLE_GRAVE,
  H_ONE,
  H_TWO,
  H_THREE,
  H_FOUR,
  H_FIVE,
  M_LINK,
  M_GREATER,
  TD_COPY_CUT = 6,
  TD_SNAGIT = 8,
  TD_B_L_SEL = 10,
  CT_LBP = 11,
  CT_RBP = 12
};

//Redefine Key Names for Readaibilty
#define XXXXXXX KC_NO
#define SCRN_CLIPB LCTL(LGUI(LSFT(KC_4)))
#define CHRM_L LALT(LGUI(KC_LEFT)) //Move left one tab in Chrome
#define CHRM_R LALT(LGUI(KC_RIGHT)) //Move right one tab in Chrome
#define S_CMD_S LGUI_T(KC_S) //`S` when typing `CMD` when held
#define D_CMD_OPT LGUI_T(LALT_T(KC_D)) //`D` when typing `CMD + Opt` when held

static uint16_t key_timer; //key timer for macros

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Copy, twice for Paste, three times for Cut.
  [TD_COPY_CUT]  = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_C),LGUI(KC_X)),
    //Tap once for Snagit, twice for Cmd + Shift + Opt + 4 (OS X cropping screenshot that is copied to the clipboard only.)
  [TD_SNAGIT] = ACTION_TAP_DANCE_DOUBLE(LCTL(LSFT(KC_C)), LCTL(LGUI(LSFT(KC_4)))),
  [CT_LBP] = ACTION_TAP_DANCE_DOUBLE (KC_LBRC, KC_LPRN),
  [CT_RBP] = ACTION_TAP_DANCE_DOUBLE (KC_RBRC, KC_RPRN)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap 0: Basic layer
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |   =    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -    |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * | Tab    |   Q  |   W  |   E  |   R  |   T  | "> " |           | []() |   Y  |   U  |   I  |   O  |   P  |   \    |
  * |--------+------+------+------+------+------|      |           | SCRN |------+------+------+------+------+--------|
  * | Hyper  |   A  |S /CMD|D/OPT | F /MD|   G  |------|           |------|   H  |   J  |K/OPT |L /CMD| ; /L2| '/Hyper|
  * |--------+------+------+------+------+------|   (  |           |   )  |------+------+------+------+------+--------|
  * |Shft Tab|Z/Ctrl|X/Alt |   C  |   V  |   B  | [  { |           | ]  } |   N  |   M  |   ,  | ./Alt|//Ctrl|CMD+SHFT|
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |  `   |Zendsk|RBMINE|CMD+S | ToDo |                                       |   _  |      |  00  |  00  |OLD BASE|
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,--------------.
  *                                        | Esc  | Home |       |Layer?| Esc   |
  *                                 ,------|------|------|       |------+-------+------.
  *                                 |      |      | End  |       | Undo |       |      |
  *                                 |Shift |Backsp|------|       |------| Return|Space/|
  *                                 | OSM  | /NUM | DEL  |       | Ctrl | /SYML |Arrows|
  *                                 `--------------------'       `---------------------'
  *
  *Copy/Cut key copies on tap, cut's on two taps.
  *
  *One tap on Snagit key = is Ctrl + Shift + C which is Snagit's selector.
  *Two taps on Snagit key = Cmd + Shift + Opt + 4 (OS X cropping screenshot that is copied to the clipboard only.)
  */

  [BASE] = LAYOUT_ergodox(
    //left hand
    KC_EQUAL,           KC_F1,    KC_F2,       KC_F3,       KC_F4,      KC_F5,    KC_F6,
    KC_TAB,             KC_Q,     KC_W,        KC_E,        KC_R,       KC_T,     M_GREATER,
    OSM(MOD_HYPR),      KC_A,  S_CMD_S,    ALT_T(KC_D), LT(MKDWN,KC_F), KC_G,
    LSFT(KC_TAB), CTL_T(KC_Z), ALT_T(KC_X),    KC_C,        KC_V,       KC_B,     TD(CT_LBP),
               KC_GRAVE, ZENDESK, RUBYMINE,   LGUI(KC_S),   TODO,
                                                          KC_ESCAPE,    KC_HOME,
                                                                        KC_END,
                                  OSM(MOD_LSFT), LT(NUM,KC_BSPACE),     LT(MKDWN,KC_DELETE),

    //right hand
    KC_F7,           KC_F8,     KC_F9,    KC_F10,   KC_F11,        KC_F12,           KC_MINUS,
    MD_LINK,          KC_Y,     KC_U,     KC_I,     KC_O,          KC_P,             KC_BSLASH,
                      KC_H,     KC_J, ALT_T(KC_K),  LGUI_T(KC_L),  LT(MEDIA,KC_SCOLON),  ALL_T(KC_QUOTE),
    TD(CT_RBP),       KC_N,     KC_M,     KC_COMMA, ALT_T(KC_DOT), CTL_T(KC_SLASH),  SCMD_T(_______),
                LSFT(KC_MINUS), _______,  DBLE_ZER0, DBLE_ZER0,   TO(OLD_BASE),
    L_ID_0,         KC_ESCAPE,
    LGUI(KC_Z),
    LT(MEDIA,KC_LCTL),  LT(SYMBL,KC_ENTER),  LT(ARROWS,KC_SPACE)),

    /* Keymap 1: OLD Base layer
    * ,--------------------------------------------------.           ,--------------------------------------------------.
    * |   =    |   1  |   2  |   3  |   4  |   5  | []() |           |Snagit|   6  |   7  |   8  |   9  |   0  |   -    |
    * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    * | Tab    |   Q  |   W  |   E  |   R  |   T  | "> " |           | []() |   Y  |   U  |   I  |   O  |   P  |   \    |
    * |--------+------+------+------+------+------|      |           | SCRN |------+------+------+------+------+--------|
    * | Hyper  |   A  |S /CMD|   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |L /CMD| ; /L2| '/Hyper|
    * |--------+------+------+------+------+------|   (  |           |   )  |------+------+------+------+------+--------|
    * |Shft Tab|Z/Ctrl|X/Alt |   C  |   V  |   B  | [  { |           | ]  } |   N  |   M  |   ,  | ./Alt|//Ctrl|CMD+SHFT|
    * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    *   |  `   |Zendsk|RBMINE|CMD+S | ToDo |                                       |   _  |      |  00  |  00  |ToBase|
    *   `----------------------------------'                                       `----------------------------------'
    *                                        ,-------------.       ,--------------.
    *                                        | Esc  | Home |       |Layer?| Esc   |
    *                                 ,------|------|------|       |------+-------+------.
    *                                 |      |      | End  |       | Undo |       |      |
    *                                 |Shift |Backsp|------|       |------| Return|Space/|
    *                                 | OSM  | /L5  | DEL  |       | Ctrl | /LT1  |Arrows|
    *                                 `--------------------'       `---------------------'
    *
    *Copy/Cut key copies on tap, cut's on two taps.
    *
    *One tap on Snagit key = is Ctrl + Shift + C which is Snagit's selector.
    *Two taps on Snagit key = Cmd + Shift + Opt + 4 (OS X cropping screenshot that is copied to the clipboard only.)
    */

    [OLD_BASE] = LAYOUT_ergodox(
      //left hand
      KC_EQUAL,           KC_1,     KC_2,    KC_3,        KC_4,     KC_5,     M_LINK,
      KC_TAB,             KC_Q,     KC_W,    KC_E,        KC_R,     KC_T,     M_GREATER,
      OSM(MOD_HYPR),      KC_A,  S_CMD_S, D_CMD_OPT, LT(MKDWN,KC_F),KC_G,
      LSFT(KC_TAB), CTL_T(KC_Z), ALT_T(KC_X),  KC_C,      KC_V,     KC_B,     TD(CT_LBP),
                 KC_GRAVE, ZENDESK, RUBYMINE, LGUI(KC_S), TODO,
                                                          KC_ESCAPE, KC_HOME,
                                                                     KC_END,
                                    OSM(MOD_LSFT), LT(NUM,KC_BSPACE),  LT(MKDWN,KC_DELETE),

      //right hand
      TD(TD_SNAGIT),    KC_6,     KC_7,     KC_8,     KC_9,          KC_0,             KC_MINUS,
      MD_LINK,          KC_Y,     KC_U,     KC_I,     KC_O,          KC_P,             KC_BSLASH,
                        KC_H,     KC_J,     KC_K,     LGUI_T(KC_L),  LT(MEDIA,KC_SCOLON),  ALL_T(KC_QUOTE),
      TD(CT_RBP),       KC_N,     KC_M,     KC_COMMA, ALT_T(KC_DOT), CTL_T(KC_SLASH),  SCMD_T(_______),
                  LSFT(KC_MINUS), _______,  DBLE_ZER0, DBLE_ZER0,   TO(BASE),
      L_ID_0,         KC_ESCAPE,
      LGUI(KC_Z),
      LT(MEDIA,KC_LCTL),  LT(SYMBL,KC_ENTER),  LT(ARROWS,KC_SPACE)),

    /* Keymap 2: Symbol
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |  1   |   2  |   3  |   4  |   5  | []() |           |Snagit|   6  |  7   |  8   |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |   $  |   &  |   `  |   |  | Cmd  |           |      |      |      |   *  |      |      |        |
     * |--------+------+------+------+------+------| + K  |           |      |------+------+------+------+------+--------|
     * |        |   #  |   $  |   &  |   !  |   @  |------|           |------|   -  |   [  |   ]  |   (  |   )  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   %  |   ^  |      |      |   ~  |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |Layer?|      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
  [SYMBL] = LAYOUT_ergodox(
    //left hand
    _______,          KC_1,        KC_2,           KC_3,         KC_4,        KC_5,      M_LINK,
    _______,        _______,     KC_DLR,        KC_AMPR,     KC_GRAVE,     KC_PIPE,  LGUI(KC_K),
    _______,        KC_HASH,     KC_DLR,        KC_AMPR,      KC_EXLM,       KC_AT,
    _______,        KC_PERC,     KC_CIRC,       _______,      _______,     KC_TILD,     _______,
                    _______,     _______,       _______,      _______,     _______,
                                                                                        _______,   _______,
                                                                                                   _______,
                                                                           _______,     _______,   _______,

    //right hand
   TD(TD_SNAGIT),    KC_6,        KC_7,         KC_8,         KC_9,        KC_0,   KC_MINUS,
    _______,      _______,     _______,      KC_PAST,      _______,     _______,    _______,
                  KC_MINUS,    KC_LBRC,      KC_RBRC,      KC_LPRN,     KC_RPRN,    _______,
    _______,      _______,     _______,      _______,      _______,     _______,    _______,
                  _______,     _______,      _______,      _______,     _______,
    L_ID_1,       _______,
    _______,
    _______,      _______,     _______),

  /* Keymap 3: Media and mouse keys
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |           | XKCD |      |      |      |      |      |  F15   |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |Whl Up| MsUp |Whl Dn|      |      |           |      |      |      |      |      |      |  F14   |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |Ctl L |MsLeft|MsDown|MsRght| Ctl R|------|           |------|      | Mute | VolDn| VolUp| TL 2 |  Play  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |WHL L |      |Whl R |      |      |           |      |      |      | Prev | Next |      |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       | Mute |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |LAYER?|      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 | Left |Right |      |       |      |Copy/ | paste|
   *                                 | Click|Click |------|       |------| cut  |/paste|
   *                                 |      |      |      |       |      |      |spcial|
   *                                 `--------------------'       `--------------------'
   */
  // MEDIA AND MOUSE

  [MEDIA] = LAYOUT_ergodox(
    //left hand
    _______,    _______,         _______,         _______,         _______,         _______,         _______,
    _______,    _______,         KC_MS_WH_UP,     KC_MS_UP,        KC_MS_WH_DOWN,   _______,         _______,
    _______,    LCTL(KC_LEFT),   KC_MS_LEFT,      KC_MS_DOWN,      KC_MS_RIGHT,     RCTL(KC_RIGHT),
    XXXXXXX,    _______,         KC_MS_WH_LEFT,   _______,         KC_MS_WH_RIGHT,  _______,         _______,
                _______,         _______,         _______,         _______,         _______,
                                                                                    _______,         _______,
                                                                                                     _______,
                                                                   KC_MS_BTN1,      KC_MS_BTN2,      _______,

    //right hand
    XKCD,       _______,       _______,         _______,         _______,    _______,    KC_F15,
    _______,    _______,       _______,         _______,         _______,    _______,    KC_F14,
                _______, KC_AUDIO_MUTE,     KC_AUDIO_VOL_DOWN,       KC_AUDIO_VOL_UP,    _______,    KC_MEDIA_PLAY_PAUSE,
   _______,     _______,       _______,   KC_MEDIA_PREV_TRACK,   KC_MEDIA_NEXT_TRACK,    _______,    XXXXXXX,
                               _______,         _______,         _______,    _______,    _______,
    L_ID_2,     _______,
    _______,
    _______,    TD(TD_COPY_CUT),    PAST_PS),

  /* Keymap 4: Markdown Symbols
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |      |      |      |      |      |      |           |SCRNCL|      |      |      |      |      |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           |      |      |  ``` |  **  |   _  |  `   |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      | TL MD|      |------|           |------|   -  |   [  |   ]  |   (  |   )  |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |           |      |   #  |  ##  |  ### | #### | #####|        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |      |      |      |      |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |Layer?|      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |      |      |------|       |------|      |      |
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  * Sc cp = OS X cropping screenshot that is copied to the clipboard only.
  */
  // Markdown  Layer
  [MKDWN] = LAYOUT_ergodox(
    //left hand
    _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,
                   _______,       _______,       _______,       _______,       _______,
                                                                               _______,       _______,
                                                                                              _______,
                                                _______,     _______, _______,

   //right hand
   SCRN_CLIPB,       _______,       _______,       _______,       _______,       _______,       _______,
   _______,          _______,   TRPLE_GRAVE,     DBLE_ASTR,LSFT(KC_MINUS),      KC_GRAVE,       _______,
                    KC_MINUS,       KC_LBRC,       KC_RBRC,       KC_LPRN,       KC_RPRN,       _______,
   _______,            H_ONE,         H_TWO,       H_THREE,        H_FOUR,        H_FIVE,       _______,
                     _______,       _______,       _______,       _______,       _______,
   _______,          _______,
   _______,
   _______,          _______,       _______),

   /* Keymap 5: Arrows
    *
    * ,--------------------------------------------------.           ,--------------------------------------------------.
    * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
    * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    * |        |      | Opt+L|  Up  |Opt+R |      |      |           |      |      | Opt+L|  Up  |Opt+R |      |        |
    * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    * |        |Ctrl+L| Left |  Dn  | Right|Ctrl+R|------|           |------|Ctrl+L| Left |  Dn  | Right|Ctrl+R|        |
    * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
    * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    *   |      |      |      |      |      |                                       |         |      |   |      |      |
    *   `----------------------------------'                                       `----------------------------------'
    *                                        ,-------------.       ,-------------.
    *                                        |      |      |       |      |      |
    *                                 ,------|------|------|       |------+------+------.
    *                                 |      |      |      |       |      |      |      |
    *                                 |      |      |------|       |------|      |      |
    *                                 |      |      |      |       |      |      |      |
    *                                 `--------------------'       `--------------------'
    *
    *
    *
    */
   // Movement  Layer

  [ARROWS] = LAYOUT_ergodox(
  //left hand
    RESET,       _______,       _______,       _______,        _______,         _______,       _______,
    _______,     _______,        CHRM_L,       KC_UP,           CHRM_R,         _______,       _______,
    _______,LCTL(KC_LEFT),      KC_LEFT,       KC_DOWN,       KC_RIGHT,    LCTL(KC_RIGHT),
    _______,    _______,       _______,       _______,        _______,         _______,       _______,
                 _______,       _______,       _______,        _______,         _______,
                                                                                _______,       _______,
                                                                                               _______,
                                                               _______,         _______,       _______,
  //right hand
    _______,     _______,       _______,       _______,        _______,         _______,       _______,
    _______,     _______,        CHRM_L,         KC_UP,         CHRM_R,         _______,       _______,
           LCTL(KC_LEFT),       KC_LEFT,       KC_DOWN,       LGUI_T(KC_RIGHT),  LCTL(KC_RIGHT),       _______,
    _______,     _______,       _______,       _______,        _______,         _______,       _______,
                 _______,       _______,       _______,        _______,         _______,
    _______,     _______,
    _______,
    _______,     _______,       _______),

    /* Keymap 6: Numpad
    * ,--------------------------------------------------.           ,--------------------------------------------------.
    * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
    * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
    * |        |      |      |      |      |      |      |           |      |   =  |   7  |   8  |   9  |   *  |        |
    * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    * |        |      |      |Cp/Cut|paste |      |------|           |------|   +  |   4  |   5  |   6  |   +  |        |
    * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
    * |        |      |      |      |      |      |      |           |      |   -  |   1  |   2  |   3  |   /  |        |
    * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
    *   |      |      |      |      |      |                                       |   0  |   .  |  00  |  00  | Enter|
    *   `----------------------------------'                                       `----------------------------------'
    *                                        ,-------------.       ,-------------.
    *                                        |      |      |       |      |      |
    *                                 ,------|------|------|       |------+------+------.
    *                                 |      |      |      |       |      |Nupmad|      |
    *                                 |      |      |------|       |------|Enter |      |
    *                                 |      |      |      |       |      |      |      |
    *                                 `--------------------'       `--------------------'
    */
    // Numpad  Layer
    [NUM] = LAYOUT_ergodox(
      //left hand
      _______,        _______,     _______,     _______,        _______,        _______,    _______,
      _______,        _______,     _______,     _______,        _______,        _______,    _______,
      _______,        _______,     _______,   TD(TD_COPY_CUT),  PAST_PS,        _______,
      _______,        _______,     _______,     _______,        _______,        _______,    _______,
                      _______,     _______,     _______,        _______,        _______,
                                                                                            _______,    _______,
                                                                                                        _______,
                                                                            _______,        _______,    _______,

      //right hand
      _______,      _______,      _______,       _______,     _______,     _______,        _______,
      _______,     KC_EQUAL,      KC_7,          KC_8,        KC_9,        KC_ASTR,        _______,
                    KC_PLUS,      KC_4,          KC_5,        KC_6,        KC_PLUS,        _______,
      _______,     KC_MINUS,      KC_1,          KC_2,        KC_3,        KC_KP_SLASH,    _______,
                    KC_KP_0,      KC_DOT,        DBLE_ZER0,   DBLE_ZER0,   KC_KP_ENTER,
      _______,      _______,
      _______,
      _______,      KC_PENT,      _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;

    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;

    case MD_LINK:
      if (record->event.pressed){
        key_timer = timer_read();
      } else {
        if (timer_elapsed(key_timer) > 150) {
          SEND_STRING ("([Video](");
        } else {
          SEND_STRING ("([Screenshot](");
        }
        SEND_STRING(SS_LGUI("v"));
        SEND_STRING("))");
      }
      break;

    case XKCD:
        if (record->event.pressed) {
        SEND_STRING ("https://xkcd.com/1319/");
      }
      break;

    case DBLE_ZER0:
      if (record->event.pressed){
        SEND_STRING ("00");
      }
      break;

    case DBLE_ASTR:
      if (record->event.pressed){
        SEND_STRING ("**");
        SEND_STRING ("**");
        SEND_STRING (SS_TAP(X_LEFT));
        SEND_STRING (SS_TAP(X_LEFT));
      }
      break;

    case TRPLE_GRAVE:
      if (record->event.pressed){
        SEND_STRING ("```");
      }
      break;

    case L_ID_0:
      if (record->event.pressed) {
        SEND_STRING (SS_LGUI(" "));
        SEND_STRING ("Layer 0: Base");
      }
      break;

    case L_ID_1:
      if (record->event.pressed) {
        SEND_STRING (SS_LGUI(" "));
        SEND_STRING ("Layer 1: Symbols");
      }
      break;

    case L_ID_2:
      if (record->event.pressed) {
        SEND_STRING (SS_LGUI(" "));
        SEND_STRING ("Layer 2: Media & Mousekeys");
      }
      break;

    case PAST_PS:
      if (record->event.pressed) {
        key_timer = timer_read();
      } else {
        if (timer_elapsed(key_timer) > 150) {
          SEND_STRING (SS_LGUI("V")); // Paste special
        } else {
          SEND_STRING (SS_LGUI("v")); // Paste
        }
      }
      break;

    case TODO:
      if (record->event.pressed) {
        key_timer = timer_read();
      } else {
        if (timer_elapsed(key_timer) > 150) { //switch to Todoist when held and released
          SEND_STRING (SS_LGUI(" "));
          SEND_STRING ("Todoist");
          SEND_STRING (SS_TAP(X_ENTER));
        } else {
          SEND_STRING (SS_LGUI(SS_LCTRL("a"))); //macro to open Todoist new task dialog
        }
      }
      break;

    case RUBYMINE:
      if (record->event.pressed){
        SEND_STRING (SS_LGUI(" "));
        SEND_STRING ("RUBYMINE");
        SEND_STRING (SS_TAP(X_ENTER));
      }
      break;

    case ZENDESK:
      if (record->event.pressed){
        SEND_STRING (SS_LGUI(" "));
        SEND_STRING ("||ZEN");
        SEND_STRING (SS_TAP(X_ENTER));
      }
      break;

    case H_ONE:
      if (record->event.pressed){
        SEND_STRING ("# ");
      }
      break;

    case H_TWO:
      if (record->event.pressed){
        SEND_STRING ("## ");
      }
      break;

    case H_THREE:
      if (record->event.pressed){
        SEND_STRING ("### ");
      }
      break;

    case H_FOUR:
      if (record->event.pressed){
        SEND_STRING ("#### ");
      }
      break;

    case H_FIVE:
      if (record->event.pressed){
        SEND_STRING ("##### ");
      }
      break;
    case M_LINK:
      if (record->event.pressed){
          SEND_STRING ("[]()");
        }
        break;
    case M_GREATER:
      if (record->event.pressed){
          SEND_STRING ("> ");
      }
      break;
    }
  return true;
};

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    default:
        break;
  }
};
