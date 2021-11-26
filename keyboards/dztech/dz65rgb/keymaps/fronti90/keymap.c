#include QMK_KEYBOARD_H

#define DEFAULT_LAYER 0
#define GAMING_LAYER 1
#define FN_LAYER 2

unsigned char r_orange=0xFF;
unsigned char g_orange=0x80;
unsigned char b_orange=0x00;

unsigned char r_green=0x44;
unsigned char g_green=0xaa;
unsigned char b_green=0x77;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT_65_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        MO(2),          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_DEL,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_NLCK,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, KC_RGUI,   MO(2), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [GAMING_LAYER] = LAYOUT_65_ansi(
        KC_GRV,        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_ESC,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,        KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [FN_LAYER] = LAYOUT_65_ansi(
        KC_GRV,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,  KC_PGUP,
        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_PGDN,
        KC_CAPS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS,          KC_TRNS, KC_PSCR,
        KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_INS,
        KC_TRNS,        KC_TRNS, KC_TRNS,                            KC_MPLY,                   MAGIC_TOGGLE_NKRO, TG(1), KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT
    )
};

int FNC_A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
int FNC_B[] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};

int FNC_A_SIZE = *(&FNC_A + 1) - FNC_A;
int FNC_B_SIZE = *(&FNC_B + 1) - FNC_B;

void loop_colorset_A(int *indices, int array_size, char r_color, char g_color, char b_color) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], r_color, g_color, b_color);
  }
}

void loop_colorset_B(int *indices, int array_size, char r_color, char g_color, char b_color) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], r_color, g_color, b_color);
  }
}

void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
    case DEFAULT_LAYER:
      loop_colorset_A(FNC_A, FNC_A_SIZE, r_green, g_green, b_green);
      loop_colorset_B(FNC_B, FNC_B_SIZE, r_green, g_green, b_green);
      break;
    case GAMING_LAYER:
      loop_colorset_A(FNC_A, FNC_A_SIZE, r_orange, g_orange, b_orange);
      loop_colorset_B(FNC_B, FNC_B_SIZE, r_green, g_green, b_green);
      break;
    case FN_LAYER:
      loop_colorset_A(FNC_A, FNC_A_SIZE, r_orange, g_orange, b_orange);
      loop_colorset_B(FNC_B, FNC_B_SIZE, r_orange, g_orange, b_orange);
      break;
  } 
  #endif
}