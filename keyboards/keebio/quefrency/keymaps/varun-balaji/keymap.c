#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NORMIE 0
#define _SOCD 1  // normie layer but with SOCD
#define _MIRYOKU 2
#define _APPLE 3
#define _L1 4
#define _L1APPLE 5
#define _L2 6
#define _L3 7

// Mod tap
// Caps lock is escape when tapped, control when held
#define ESC_CTL LCTL_T(KC_ESC)
// Left space is backspace when tapped, gui/super/win/command when held
#define BSP_GUI LGUI_T(KC_BSPC)
// Right space is space when tapped, shift when held
#define SPC_SFT LSFT_T(KC_SPC)

// Layer tap
// Left mod key is tab when tapped, layer when held
#define TAB_L1 LT(_L1, KC_TAB)
// Separate layer 1 for apple
#define TAB_L1A LT(_L1APPLE, KC_TAB)
// Right mod key is enter when tapped, layer when held
#define ENT_L2 LT(_L2, KC_ENT)

// Tap dance
// Tap Dance declarations
enum {
    TD_SHIFT_CAPS,
};
// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Double tap shift to caps lock
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
// Assign easier to read definitions
# define SFT_CAP TD(TD_SHIFT_CAPS)

// One shot shift 
//# define OS_LSFT OSM(MOD_LSFT)

// Home row mods on miryoku layer
// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)
// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCL RGUI_T(KC_SCLN)
// Additional binds for apple layer, swapping Ctrl and Gui
#define CTL_A LCTL_T(KC_A)
#define GUI_D LGUI_T(KC_D)
#define GUI_K RGUI_T(KC_K)
#define CTL_SCL RCTL_T(KC_SCLN)

// Switch base layer
// Switch to normal layer
#define SW_NORM DF(_NORMIE)
// Switch to miryoku layer
#define SW_MIRY DF(_MIRYOKU)
// Switch to apple layer
#define SW_APPL DF(_APPLE)
// Switch to SOCD layer
#define SW_SOCD DF(_SOCD)

// Do we even need this?
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  // SOCD custom keycodes
  SOCD_UP,
  SOCD_DO,
  SOCD_LE,
  SOCD_RI,
};

// SOCD mappings
#define SOCD_MAPPED_UP KC_SPACE
#define SOCD_MAPPED_DOWN KC_S
#define SOCD_MAPPED_LEFT KC_A
#define SOCD_MAPPED_RIGHT KC_D

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NORMIE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
      KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,     KC_BSPC     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,            KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,KC_LBRC ,KC_RBRC ,KC_BSLS , KC_DEL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     KC_CAPS ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,            KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,KC_QUOT ,     KC_ENT      ,KC_PGUP ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     KC_LSFT ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,            KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,KC_SLSH ,KC_RSFT ,_______ , KC_UP  ,KC_PGDN ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT ,MO(_L1) ,     KC_SPC      ,               KC_SPC      ,MO(_L2) ,KC_RALT ,KC_RGUI ,KC_RCTL ,KC_LEFT ,KC_DOWN ,KC_RGHT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SOCD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
      KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,     KC_BSPC     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,            KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,KC_LBRC ,KC_RBRC ,KC_BSLS , KC_DEL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     KC_CAPS ,SOCD_LE ,SOCD_DO ,SOCD_RI ,  KC_F  ,  KC_G  ,            KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,KC_QUOT ,     KC_ENT      ,KC_PGUP ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     KC_LSFT ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,            KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,KC_SLSH ,KC_RSFT ,_______ , KC_UP  ,KC_PGDN ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT ,MO(_L1) ,     SOCD_UP     ,               SOCD_UP     ,MO(_L2) ,KC_RALT ,KC_RGUI ,KC_RCTL ,KC_LEFT ,KC_DOWN ,KC_RGHT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_MIRYOKU] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
     KC_GESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,     KC_BSPC     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,            KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,KC_LBRC ,KC_RBRC ,KC_BSLS , KC_DEL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     ESC_CTL , GUI_A  , ALT_S  , CTL_D  , SFT_F  ,  KC_G  ,            KC_H  , SFT_J  , CTL_K  , ALT_L  ,GUI_SCL ,KC_QUOT ,     KC_ENT      ,KC_PGUP ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     SFT_CAP ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,            KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,KC_SLSH ,KC_RSFT ,_______ , KC_UP  ,KC_PGDN ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT , TAB_L1 ,     BSP_GUI     ,               SPC_SFT     , ENT_L2 ,KC_RALT ,KC_RGUI ,KC_RCTL ,KC_LEFT ,KC_DOWN ,KC_RGHT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_APPLE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
     KC_GESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,     KC_BSPC     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
      KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,            KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,KC_LBRC ,KC_RBRC ,KC_BSLS , KC_DEL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     ESC_CTL , CTL_A  , ALT_S  , GUI_D  , SFT_F  ,  KC_G  ,            KC_H  , SFT_J  , GUI_K  , ALT_L  ,CTL_SCL ,KC_QUOT ,     KC_ENT      ,KC_PGUP ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     SFT_CAP ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,            KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,KC_SLSH ,KC_RSFT ,_______ , KC_UP  ,KC_PGDN ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_LALT ,TAB_L1A ,     BSP_GUI     ,               SPC_SFT     , ENT_L2 ,KC_RALT ,KC_RGUI ,KC_RCTL ,KC_LEFT ,KC_DOWN ,KC_RGHT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_L1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
      KC_GRV , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,           KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,     _______     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
    A(KC_TAB),  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,_______ ,KC_MUTE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,_______ ,          KC_LEFT ,KC_DOWN , KC_UP  ,KC_RGHT ,_______ ,_______ ,     _______     ,KC_HOME ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     _______ ,C(KC_Z) ,C(KC_X) ,C(KC_C) ,C(KC_V) ,_______ ,          KC_HOME ,KC_PGDN ,KC_PGUP , KC_END ,_______ ,_______ ,KC_MPLY ,KC_VOLU , KC_END ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______     ,               _______     ,MO(_L3) ,_______ ,_______ ,_______ ,KC_MPRV ,KC_VOLD ,KC_MNXT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_L1APPLE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
      KC_GRV , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,           KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,     _______     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
    A(KC_TAB),  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,            KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,_______ ,KC_MUTE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     _______ ,KC_LCTL ,KC_LALT ,KC_LGUI ,KC_LSFT ,_______ ,          KC_LEFT ,KC_DOWN , KC_UP  ,KC_RGHT ,_______ ,_______ ,     _______     ,KC_HOME ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     _______ ,G(KC_Z) ,G(KC_X) ,G(KC_C) ,G(KC_V) ,_______ ,          KC_HOME ,KC_PGDN ,KC_PGUP , KC_END ,_______ ,_______ ,KC_MPLY ,KC_VOLU , KC_END ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______     ,               _______     ,MO(_L3) ,_______ ,_______ ,_______ ,KC_MPRV ,KC_VOLD ,KC_MNXT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_L2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,     _______     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
     _______ ,_______ ,KC_UNDS ,KC_PLUS ,KC_LBRC ,KC_RBRC ,          KC_BTN1 ,KC_BTN2 ,KC_BTN3 ,KC_BTN4 ,KC_SLSH ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     _______ ,_______ ,KC_MINS , KC_EQL ,KC_LPRN ,KC_RPRN ,          KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,_______ ,_______ ,     _______     ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     _______ ,_______ ,KC_BSLS ,KC_PIPE ,KC_LCBR ,KC_RCBR ,          KC_WH_L ,KC_WH_D ,KC_WH_U ,KC_WH_R ,_______ ,_______ ,KC_MPLY ,KC_VOLU , KC_END ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,MO(_L3) ,     _______     ,               _______     ,_______ ,_______ ,_______ ,_______ ,KC_MPRV ,KC_VOLD ,KC_MNXT  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_L3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬─────────────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,     _______     ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┤
     _______ ,SW_APPL ,SW_SOCD ,_______ ,_______ ,SW_NORM ,          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,     _______     ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ , RESET  ,           RESET  ,SW_MIRY ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┴────────┤         ├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______     ,               _______     ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______  
  //└────────┴────────┴────────┴────────┴─────────────────┘         └─────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),
};

// Tap repeat hold for homerow keys
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_A:
            return true;
        case ALT_S:
            return true;
        case CTL_D:
            return true;
        case SFT_F:
            return true;
        case GUI_SCL:
            return true;
        default:
            return false;
    }
}

// SOCD processing
// The function processes the SOCD custom keycodes and outputs the cleaned normal keycode according to the SOCD mappings
bool socd_pressed_up = false;
bool socd_pressed_down = false;
bool socd_pressed_left = false;
bool socd_pressed_right = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SOCD_UP:
            if (record -> event.pressed) {
                socd_pressed_up = true;
                if (socd_pressed_down) {
                    unregister_code(SOCD_MAPPED_DOWN); // overwrite with up
                }
                register_code(SOCD_MAPPED_UP);
            } else {
                socd_pressed_up = false;
                unregister_code(SOCD_MAPPED_UP);
                if (socd_pressed_down) {
                    register_code(SOCD_MAPPED_DOWN); // return back to down
                }
            }
            return false;
        case SOCD_DO:
            if (record -> event.pressed) {
                socd_pressed_down = true;
                if (socd_pressed_up) {
                    // do nothing
                } else {
                    register_code(SOCD_MAPPED_DOWN); // if up not pressed, write down
                }
            } else {
                socd_pressed_down = false;
                if (socd_pressed_up) {
                    // do nothing
                } else {
                    unregister_code(SOCD_MAPPED_DOWN); // if up is not pressed, return to neutral
                }
            }
            return false;
        case SOCD_LE:
            if (record -> event.pressed) {
                socd_pressed_left = true;
                if (socd_pressed_right) {
                    unregister_code(SOCD_MAPPED_RIGHT); // left + right = neutral
                } else {
                    register_code(SOCD_MAPPED_LEFT); // only left
                }
            } else {
                socd_pressed_left = false;
                if (socd_pressed_right) {
                    register_code(SOCD_MAPPED_RIGHT); // back to right
                } else {
                    unregister_code(SOCD_MAPPED_LEFT); // back to neutral
                }
            }
            return false;
        case SOCD_RI:
            if (record -> event.pressed) {
                socd_pressed_right = true;
                if (socd_pressed_left) {
                    unregister_code(SOCD_MAPPED_LEFT); // left + right = neutral
                } else {
                    register_code(SOCD_MAPPED_RIGHT); // only right
                }
            } else {
                socd_pressed_right = false;
                if (socd_pressed_left) {
                    register_code(SOCD_MAPPED_LEFT); // back to left
                } else {
                    unregister_code(SOCD_MAPPED_RIGHT); // back to neutral
                }
            }
            return false;
        default:
            return true;
    }
}
