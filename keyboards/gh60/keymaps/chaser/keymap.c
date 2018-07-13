#include QMK_KEYBOARD_H
#include <util/delay.h>


extern keymap_config_t keymap_config;


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _FL 1
#define _MC 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

bool git_duet = false;
bool backlight_arrows = false;
bool backlight_gaming = false;
enum custom_keycodes {
  /* GIT related keycodes */
  G_ADD = SAFE_RANGE, G_BRN, G_COM, G_COU, G_CLO,
  G_DFF, G_DUE, G_DUT, G_FTC, G_LOG, G_MAG, G_MRG,
  G_MRT, G_PSH, G_PLL, G_RBS, G_STH, G_STS, G_TIG,

  /* Multi-media related keycodes */
  A_MUTE, A_NEXT, A_PLPA, A_PREV, A_VOUP, A_VDWN,

  /* System related shortcuts */
  F_BTN, M_WAPP, K_ARR, K_WASD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |FN     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  FN  |Up |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space           |Alt |Left |Down|Right|
   * `-----------------------------------------------------------'
   *
   * Note: right FN triggers function layer,
   *       left FN is a one-shot button for the macro layer
   */
  /* Layer 0: Qwerty */
  [_QW] = LAYOUT_60_ansi_split_rshift( \
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    OSL(_MC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          F_BTN,   KC_UP,   \
    KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /*
   * ,-----------------------------------------------------------.
   * |GRV|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|   DEL |
   * |-----------------------------------------------------------|
   * |  MB3|MB2|MUP|MB1|MWU|   |   |   |INS|   |RST|   |   |Print|
   * |-----------------------------------------------------------|
   * |      | ML|MDN|MR |MWD|   |   |       |   |   |   |        |
   * |-----------------------------------------------------------|
   * |CAPS    |   |   |   |   |   |   |   |   |   |   |PGUP|     |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |Ctrl|HOME|PGD |END |
   * `-----------------------------------------------------------'
   */
  /* Layer 1: Functions */
  [_FL] = LAYOUT_60_ansi_split_rshift(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, _______, _______, _______, KC_INS,  _______, RESET,   _______, _______, KC_PSCR, \
    KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, _______, _______, _______, _______,          KC_TILD, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, \
    _______, _______, _______,                   _______,                                     KC_RCTL, KC_HOME, KC_PGDN, KC_END   \
  ),

  /*
   * ,-----------------------------------------------------------.
   * |DEF|   |DUE|   |   |   |   |   |   |   |   |   |GAM|    ARR|
   * |-----------------------------------------------------------|
   * |     |MAG|CLO|DUT|RBS|TIG|MRT|   |   |COU|PSH|   |   |     |
   * |-----------------------------------------------------------|
   * |      |ADD|STS|DFF|FTC|PLL|MRG|   |STH|LOG|   |   |   F_OFF|
   * |-----------------------------------------------------------|
   * |         |   |   |COM|   |BRN|   |   |   |   |MUT|VOL+|PLPA|
   * |-----------------------------------------------------------|
   * |    |    |    |                        |APP |PREV|VOL-|NEXT|
   * `-----------------------------------------------------------'
   *
   * Abbreviations:
   * --------------
   * DEF  - return to default layer
   * DUE  - enable git duet mode
   * CLO  - git clone
   * DUT  - git duet (when in duet mode)
   * RBS  - git rebase
   * MAG  - git submodule sync --recursive && git submodule update --init --recursive && git submodule foreach --recursive "git co . && git reset --hard && git clean -dffx"
   * TIG  - tig
   * MRG  - git merge
   * MRT  - git mergetool
   * COU  - git checkout
   * PSH  - git push
   * ADD  - git add
   * STS  - git status
   * DFF  - git diff
   * FTC  - git fetch
   * PLL  - git pull
   * STH  - git stash
   * LOG  - git log
   * COM  - git commit (or git duet commit if in duet mode)
   * BRN  - git branch
   * APP  - application (windows menu key)
   * MUT  - audio mute
   * VOL+ - increase volume
   * VOL- - decrease volume
   * PLPA - play/pause
   * PREV - previous song
   * NEXT - next song
   * ARR  - backlight arrow keys
   * GAM  - backlight WASD
   *
   * Note: git commands are SEND_STRING macros sent to the
   *       currently focused window Make sure it is your terminal :)
   */
  /* Layer 2: Macros (Git & Multimedia) */
  [_MC] = LAYOUT_60_ansi_split_rshift( \
    TO(_QW), XXXXXXX, G_DUE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, K_WASD,  K_ARR,   \
    XXXXXXX, G_MAG,   G_CLO,   G_DUT,   G_RBS,   G_TIG,   G_MRT,   XXXXXXX, XXXXXXX, G_COU,   G_PSH,   XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, G_ADD,   G_STS,   G_DFF,   G_FTC,   G_PLL,   G_MRG,   XXXXXXX, G_STH,   G_LOG,   XXXXXXX, XXXXXXX,          XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, G_COM,   XXXXXXX, G_BRN,   XXXXXXX, XXXXXXX, XXXXXXX, A_MUTE,           A_PLPA,  A_VOUP,  \
    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                                     M_WAPP,  A_PREV,  A_VDWN,  A_NEXT   \
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      /*
       * Begin git layer
       */
      case G_ADD:
        SEND_STRING("git add ");
        layer_off(_MC);
        return false;break;
      case G_BRN:
        SEND_STRING("git branch\n");
        layer_off(_MC);
        return false;break;
      case G_CLO:
        SEND_STRING("git clone ");
        layer_off(_MC);
        return false;break;
      case G_COM:
        if(git_duet) {
          SEND_STRING("git duet-commit ");
        } else {
          SEND_STRING("git commit ");
        }
        layer_off(_MC);
        return false;break;
      case G_COU:
        SEND_STRING("git checkout ");
        layer_off(_MC);
        return false;break;
      case G_DFF:
        SEND_STRING("git diff\n");
        layer_off(_MC);
        return false;break;
      case G_DUE:
        git_duet = !git_duet;
        if(git_duet) {
          gh60_esc_led_on();
        } else {
          gh60_esc_led_off();
        }
        layer_off(_MC);
        return false;break;
      case G_DUT:
        if(git_duet) {
          SEND_STRING("git duet ");
        }
        layer_off(_MC);
        return false; break;
      case G_FTC:
        SEND_STRING("git fetch ");
        layer_off(_MC);
        return false;break;
      case G_LOG:
        SEND_STRING("git log --graph\n");
        layer_off(_MC);
        return false;break;
      case G_MAG:
        // This is some git-magic to resync recursive submodule structures inside git projects (thx to https://github.com/jimmykarily)
        SEND_STRING("git submodule sync --recursive && git submodule update --init --recursive && git submodule foreach --recursive \" git co . && git reset --hard && git clean -dffx \" \n");
        layer_off(_MC);
        return false; break;
      case G_MRG:
        SEND_STRING("git merge ");
        layer_off(_MC);
        return false;break;
      case G_MRT:
        SEND_STRING("git mergetool ");
        layer_off(_MC);
        return false;break;
      case G_PLL:
        SEND_STRING("git pull ");
        layer_off(_MC);
        return false;break;
      case G_PSH:
        SEND_STRING("git push ");
        layer_off(_MC);
        return false;break;
      case G_RBS:
        SEND_STRING("git rebase ");
        layer_off(_MC);
        return false;break;
      case G_STH:
        SEND_STRING("git stash ");
        layer_off(_MC);
        return false;break;
      case G_STS:
        SEND_STRING("git status\n");
        layer_off(_MC);
        return false;break;
      case G_TIG:
        SEND_STRING("tig\n");
        layer_off(_MC);
        return false;break;
      /*
       * End git layer
       */

      /*
       * Begin multimedia keys
       */
      case A_MUTE:
        register_code(KC_AUDIO_MUTE);
        unregister_code(KC_AUDIO_MUTE);
        layer_off(_MC);
        return false;break;
      case A_PLPA:
        register_code(KC_MEDIA_PLAY_PAUSE);
        unregister_code(KC_MEDIA_PLAY_PAUSE);
        layer_off(_MC);
        return false;break;
      case A_VOUP:
        register_code(KC_AUDIO_VOL_UP);
        return false;break;
      case A_VDWN:
        register_code(KC_AUDIO_VOL_DOWN);
        return false;break;
      case A_PREV:
        register_code(KC_MEDIA_PREV_TRACK);
        unregister_code(KC_MEDIA_PREV_TRACK);
        layer_off(_MC);
        return false;break;
      case A_NEXT:
        register_code(KC_MEDIA_NEXT_TRACK);
        unregister_code(KC_MEDIA_NEXT_TRACK);
        layer_off(_MC);
        return false;break;
      /*
       * End multimedia keys
       */

      // Tap dance to get the app button mapped
      case M_WAPP:
        register_code(KC_APP);
        unregister_code(KC_APP);
        layer_off(_MC);
        return false;break;

      /*
       * Begin multimedia keys
       */
      case K_ARR:
        backlight_arrows = !backlight_arrows;
        if(backlight_arrows) {
          gh60_poker_leds_on();
        } else {
          gh60_poker_leds_off();
        }
        layer_off(_MC);
        return false;break;
      case K_WASD:
        backlight_gaming = !backlight_gaming;
        if(backlight_gaming) {
          gh60_wasd_leds_on();
        } else {
          gh60_wasd_leds_off();
        }
        layer_off(_MC);
        return false; break;
      case F_BTN:
        gh60_fn_led_on();
        layer_on(_FL);
        return false;break;
    }
    /*
     * End multimedia keys
     */

  } else {
    switch(keycode) {
      /*
       * Oneshots that will switch back to the default layer on KEY_UP
       */
      case A_VOUP:
        unregister_code(KC_AUDIO_VOL_UP);
        layer_off(_MC);
        return false;break;
      case A_VDWN:
        unregister_code(KC_AUDIO_VOL_DOWN);
        layer_off(_MC);
        return false;break;
      case F_BTN:
        layer_off(_FL);
        gh60_fn_led_off();
        return false;break;
    }
  }
  return true;
};
