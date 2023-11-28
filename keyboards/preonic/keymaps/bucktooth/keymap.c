#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define L_QWERTSPLITLY 0
#define L_FN 1

// Defines for Mac specific key accelerators used in map. Some of these are very awkward to type.
// These are the default bindings for Mac, some of which may be turned off or changed, check your
// settings in System Preferences
#define LS_TAB LSFT(KC_TAB) // Shift-TAB
#define MF_MENU LCTL(KC_F2) // Move focus to menu bar default keybinding in MacOS
#define MF_DOCK LCTL(KC_F3) // Move focus to dock
#define MF_TOOL LCTL(KC_F5) // Move focus to window toolbar
#define MF_STAT LCTL(KC_F8) // Move focus to status bar side of menu bar
#define MF_DRWR LALT(LGUI(KC_QUOTE)) // Move focus to window drawer
#define MF_LPAD LALT(LGUI(KC_Q)) // Show Launchpad
#define MF_NOTI LALT(LGUI(LCTL(KC_B))) // Show Notification Center
#define MF_DASH LALT(LGUI(LCTL(KC_C))) // Show Dashboard
#define MF_HELP LSFT(LGUI(KC_SLASH)) // Position in menu Help search box

// Momentary/Tap Combos used by this layout
#define LT_FNESC LT(L_FN, KC_ESC) // ESC when tapped, Fn layer when held
#define MT_RGENT MT(MOD_RGUI, KC_ENTER) // Enter when tapped, right GUI when held
#define LT_FNLFT LT(L_FN, KC_LEFT) // Left when tapped, Fn layer when held
#define MT_RSDOT MT(MOD_RSFT, KC_DOT) // Dot when tapped, right shift when held

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QwertSplitly
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   =  |   `  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  |   [  |   ]  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |   -  |   '  |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   \  |   /  |   B  |   N  |   M  |   ,  |./RSft|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ESC/fn|LCtrl | LOpt | LCmd |Space | Tab  | BkSp |Space |En/Cmd|<-/fn |CRSR v|CRSR->|
 * `-----------------------------------------------------------------------------------'
 */
[L_QWERTSPLITLY] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_EQL  ,KC_GRAVE,KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINUS,KC_QUOTE,KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_BSLS, KC_SLASH,KC_B,    KC_N,    KC_M,    KC_COMM, MT_RSDOT,
  LT_FNESC,KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_TAB,  KC_BSPC, KC_SPC,  MT_RGENT,LT_FNLFT,KC_DOWN, KC_RIGHT
),

/* Fn
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  | Vol+ | Mute |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F11 |  F12 |  F13 |  F14 |  F15 |Track-|Track+|M:WhUp|M:Lclk| M:Up |M:Rclk| PgUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |^LPad |^DashB|^Help |^Drawr| Vol- | |>|| |M:WhDn|M:Left|M:Down|M:Rght| PgDn |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |RShift|^Menu |^SMenu|^Dock |^Tools|^Notif|  Ins |M:Slow|M:Norm|M:Fast| Home | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |[ESC] |RCtrl | ROpt | RCmd |Space |Sh-Tab|  Del |Space |PadEnt| [fn] |  Up  | Left |
 * `-----------------------------------------------------------------------------------'
 */
[L_FN] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_VOLU, KC_MUTE, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_MRWD, KC_MFFD, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_PGUP,
  KC_CAPS, MF_LPAD, MF_DASH, MF_HELP, MF_DRWR, KC_VOLD, KC_MPLY, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN,
  KC_RSFT, MF_MENU, MF_STAT, MF_DOCK, MF_TOOL, MF_NOTI, KC_INS,  KC_ACL0, KC_ACL1, KC_ACL2, KC_HOME, KC_END,
  _______, KC_RCTL, KC_RALT, KC_RGUI, _______, LS_TAB,  KC_DEL,  _______, KC_PENT, _______, KC_UP,   KC_LEFT
)

};
