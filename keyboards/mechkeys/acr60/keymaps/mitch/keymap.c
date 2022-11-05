#include QMK_KEYBOARD_H

#define _DFT 0
#define _NGUI 1
#define _FN 2
#define _SFX 3

// Fillers to make layering more clear
#define ______ KC_TRNS
#define bbbbbb KC_NO
#define GUIOFF MAGIC_NO_GUI
#define GUION MAGIC_UNNO_GUI

/* TODO: create handy quick-ref list here for easy grokking of the actual shortcuts in place */

/*
 * This is Mitch's default ACR60 layout (also DZ60, on which the ACR60 is based). This is a
 * Mac-oriented layout, as noted by the GUI keys immediately next to the space bar area of the
 * lower modifier row. This uses the LAYOUT_mitchsplit keymap as defined in arc60.h, which
 * uses a 3-split space bar and a split right shift. Otherwise it's a standard 60% layout (for
 * now).
 *
 * For me, this is a great place to start getting used to a split key setup and still mostly
 * sticking to a standard staggered 60% layout so my entire game isn't thrown off.
 *
 * Layers (0-based index because we're devs!):
 *
 *    0: Default QWERTY layer
 *      Note Fn and Alt keys on the right side of the spacebar, not sure if those are
 *      normal position but that's what I'm used to at this point. YMMV
 *
 *    1: Function Layer
 *      Function keys, Grave Key, Delete, Caps lock on the tab, media keys, and directional
 *      keys. Also you can hit the Alt key position to switch (and lock) into the 3rd layer
 *      if you really want to mess with your SFX for a bit.
 *
 *    2: Special Effects Layer
 *      RGB and backlight settings access. RGB cycle on "S" key position and if locked into
 *      the third layer you can hold shift to cycle backwards (see notes below). Bootloader
 *      access is on this layer. If layer locked, hit right Alt key to get back to layer 0.
 *
 * The keymap layer definitions below look pretty bad when soft-wrapped by your IDE / text editor.
 * Be sure to disable wrapping to make things more readable with lines preserved.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \     |
 * |-----------------------------------------------------------------------------------------+
 * |   Fn   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter     |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  / | RShift     | FN  |
 * |-----------------------------------------------------------------------------------------+
 * | LCtrl | LAlt | LGUI  |      Space      | Space|   Space    | RGUI |  Fn  | RAlt | RCtrl |
 * `-----------------------------------------------------------------------------------------'
 */
/* Qwerty gui/alt/space/alt/gui /
 *
 * Hit MO(_FN) and Alt in that order to lock into the _FN layer.
 */
  [_DFT] = LAYOUT_mitchsplit( /* Basic QWERTY */
      QK_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  \
      MO(_FN), KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN), \
      KC_LCTL, KC_LALT, KC_LGUI,        KC_SPC, KC_SPC, KC_SPC,                  KC_RGUI, MO(_FN), LT(_SFX, KC_RALT),KC_RCTL \
      ),

/* Gaming
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * |        |     |     |     |     |    |     |     |     |     |     |     |     |         |
 * |-----------------------------------------------------------------------------------------+
 * |         |     |     |     |     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |      |    |     |           |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |      |BLOCKED|               |       |             |BLOCKED|      |       |      |
 * `-----------------------------------------------------------------------------------------'
 */
/* I disable the GUI / System key for gaming, as usually that's windows and I hit that at the most
 * inopportune moments. And games don't use the windows key. I'd use the Bootmagic MAGIC_NO_GUI and
 * MAGIC_UNNO_GUI keycodes, but that actually disables it and has it persist beyond disconnection
 * of the board. That's less convenient (and more confusing) for me than this approach, which is
 * basically just blocking the GUI keys when this layer is active and not letting them flow through
 * to the default layer.
 */
 /* Layer 2: "special effects": RGB lighting, backlighting, bootloader */
  [_NGUI] = LAYOUT_mitchsplit(
      ______,  ______, ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,  ______, ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,  ______, ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,  ______, ______,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,  ______, bbbbbb,          ______, ______, ______,                 bbbbbb, ______, ______, ______   \
      ),

/* Fn Layer / Layer 1
 * ,-----------------------------------------------------------------------------------------.
 * |KC_GRV| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Del    |
 * |-----------------------------------------------------------------------------------------+
 * | CAPS  |     |     |     |     |     |Home | Pgup| Up  | PgDn| End |     |     |         |
 * |-----------------------------------------------------------------------------------------+
 * |        | Vol-| Vol+| Mute|     |     |     | Left| Down|Right|     |     |              |
 * |-----------------------------------------------------------------------------------------+
 * |           |Prev |Play |Next |     |     |     |     |     |     |     |          |      |
 * |-----------------------------------------------------------------------------------------+
 * |      |      |       |               |       |               |      |      | LrSfx |     |
 * `-----------------------------------------------------------------------------------------'
 */
/*
 * Pok3r-style layer switching on M and "," keys (_DFT and _NGUI layers, respectively). Note that
 * these don't enable/disable those layers (i.e. latching keys), they actually switch to that layer.
 * To go to the _NGUI layer, Fn+comma, to go to _DFT from _NGUI, hit Fn+M.
 */
 /* Layer 1: Functions, primary layer switching, media controls, directional */
  [_FN] = LAYOUT_mitchsplit(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10, KC_F11, KC_F12, KC_DEL, \
      KC_CAPS, bbbbbb,  bbbbbb,  bbbbbb,  bbbbbb, bbbbbb, KC_HOME, KC_PGUP, KC_UP ,  KC_PGDN,  KC_END, bbbbbb, bbbbbb, bbbbbb,  \
      ______,  KC_VOLD, KC_VOLU, KC_MUTE, bbbbbb, bbbbbb, bbbbbb,  KC_LEFT, KC_DOWN, KC_RIGHT, bbbbbb, bbbbbb, ______,   \
      ______,  KC_MPRV, KC_MPLY, KC_MNXT, bbbbbb, bbbbbb, bbbbbb,TO(_DFT),TO(_NGUI), bbbbbb,   bbbbbb, ______, ______,  \
      ______,  ______,  ______,           ______, ______, ______,                    ______,   ______,TG(_SFX),______  \
      ),

/* Special Effects Layer / Layer 2
 * ,-----------------------------------------------------------------------------------------.
 * |     |Plain|Brth |Rnbw |Swirl|Snake|Knght|Xmas |Grdnt|     |     |     |     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * |        | BL  |BLSTEP| BL- | BL+ |    |     |     |     |     |     |     |     |Bootldr |
 * |-----------------------------------------------------------------------------------------+
 * |         | RGBT| RGBM|     |     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |      |    |     |           |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |      |       |               |       |              |      |      |LrDflt |      |
 * `-----------------------------------------------------------------------------------------'
 */
/* Tap RAlt to get back to default layer (0).
 *
 * See https://docs.qmk.fm/feature_rgblight.html#rgblight-keycodes for details about
 * RGB codes. Quick summary, though:
 *
 *    RGB_MODE_PLAIN         RGB_M_P	    Switch to the static no animation mode
 *    RGB_MODE_BREATHE       RGB_M_B	    Switch to the breathing mode
 *    RGB_MODE_RAINBOW       RGB_M_R	    Switch to the rainbow mode (cycles through colors)
 *    RGB_MODE_SWIRL         RGB_M_SW	  Switch to the swirl mode (like an animated gradient)
 *    RGB_MODE_SNAKE         RGB_M_SN	  Switch to the snake mode
 *    RGB_MODE_KNIGHT        RGB_M_K	    Switch to the knight animation
 *    RGB_MODE_XMAS          RGB_M_X	    Switch to the Christmas animation
 *    RGB_MODE_GRADIENT      RGB_M_G	    Switch to the static gradient mode
 *
 *    Note that there are more animation variations, usually timer-based variations, by using the
 *    "S" key to cycle through modes. Use one of the deciated keys to get to
 *    the general mode where you want it, then cycle through variations of that mode to get
 *    something specific more quickly.
 */
 /* Layer 2: "special effects": RGB lighting, backlighting, bootloader */
  [_SFX] = LAYOUT_mitchsplit(
      ______,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G,______, ______, ______,  ______, ______,  \
      ______,  BL_TOGG, BL_STEP, BL_DOWN, BL_UP,   ______,  ______,  ______,  ______, ______, ______, ______,  ______,  QK_BOOT,  \
      ______,  RGB_TOG, RGB_MOD,______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______,  \
      ______,  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______,  ______, ______, ______, ______,  ______,  \
      ______,  ______,  ______,             ______, ______, ______,                   ______, ______,TO(_DFT),______   \
      )

};
