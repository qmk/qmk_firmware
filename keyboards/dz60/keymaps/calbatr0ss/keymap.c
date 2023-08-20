#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  LAYER 0
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │ TAB │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ BKSP│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │ CTRL │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │ SHIFT  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ SHIFT│LYR│
 * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │CAPS│ ALT│ OS │ SPACE    │ FN │ SPACE  │ OS │ ALT│MENU│CTRL│
 * └────┴────┴────┴──────────┴────┴────────┴────┴────┴────┴────┘
 */
  LAYOUT_60_calbatr0ss(
      KC_ESC,  KC_1,    KC_2, KC_3,    KC_4,   KC_5, KC_6,  KC_7, KC_8,   KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,           KC_Q, KC_W,    KC_E,   KC_R, KC_T,  KC_Y, KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      KC_LCTL,          KC_A, KC_S,    KC_D,   KC_F, KC_G,  KC_H, KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT,          KC_Z, KC_X,    KC_C,   KC_V, KC_B,  KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT, MO(3),
      KC_CAPS, KC_LALT,       KC_LGUI, KC_SPC,       MO(2),       KC_SPC, KC_RGUI,         KC_RALT, KC_APP,  KC_RCTL),

/*  LAYER 1
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │ TAB │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ BKSP│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │ CTRL │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │ SHIFT  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ SHIFT│LYR│
 * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │CAPS│ OS │ ALT│ SPACE    │ FN │ SPACE  │ ALT│ OS │MENU│CTRL│
 * └────┴────┴────┴──────────┴────┴────────┴────┴────┴────┴────┘
 */
  LAYOUT_60_calbatr0ss(
      KC_ESC,  KC_1,    KC_2, KC_3,    KC_4,   KC_5, KC_6,  KC_7, KC_8,   KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,           KC_Q, KC_W,    KC_E,   KC_R, KC_T,  KC_Y, KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      KC_LCTL,          KC_A, KC_S,    KC_D,   KC_F, KC_G,  KC_H, KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT,          KC_Z, KC_X,    KC_C,   KC_V, KC_B,  KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT, MO(3),
      KC_CAPS, KC_LGUI,       KC_LALT, KC_SPC,       MO(2),       KC_SPC, KC_RALT,         KC_RGUI, KC_APP,  KC_RCTL),

/*  LAYER 2
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │RGB│   │   │   │   │   │PDN│ UP│PUP│   │   │   │ DEL │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │HOM│LFT│DWN│RHT│END│   │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │        │   │   │   │   │VDN│VUP│MUT│PRV│NXT│PLY│      │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │RSET│    │    │          │    │        │    │    │    │    │
 * └────┴────┴────┴──────────┴────┴────────┴────┴────┴────┴────┘
 */
  LAYOUT_60_calbatr0ss(
      KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
      KC_TRNS,          RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_UP,   KC_PGUP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,  KC_TRNS, KC_TRNS,
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MNXT,  KC_MPLY,          KC_TRNS, KC_TRNS,
      QK_BOOT, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS),

/*  LAYER 3
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │WIN│   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │        │   │   │   │   │   │   │MAC│   │   │   │      │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬────┬┴───┤
 * │    │    │    │          │    │        │    │    │    │    │
 * └────┴────┴────┴──────────┴────┴────────┴────┴────┴────┴────┘
 */
  LAYOUT_60_calbatr0ss(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,          KC_TRNS, DF(1),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DF(0),   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS)
};
