#include QMK_KEYBOARD_H

typedef union {
  uint32_t raw;
  struct {
    bool thumb_alt :1;
    bool iso       :1;
  };
} user_config_t;

user_config_t user_config;

#ifdef STENO_ENABLE
#include "keymap_steno.h"
#endif // STENO_ENABLE


#define QWERTY_base  KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define DVORAK_base  KC_GRV, KC_QUOT, KC_COMM, KC_DOT,KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_LBRC, KC_RBRC, \
                             KC_A,    KC_O,    KC_E,  KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH, \
                             KC_SCLN, KC_Q,    KC_J,  KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z
#define COLEMAK_base KC_GRV, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, \
                             KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define WORKMAN_base KC_GRV, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U,    KC_P,   KC_SCLN, KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_H, KC_T, KC_G, KC_Y, KC_N, KC_E,    KC_O,   KC_I,    KC_QUOT, \
                             KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH
#ifdef ALT_LAYOUTS_ENABLE
#include "keymap_dvorak.h"
#include "keymap_colemak.h"
#include "keymap_workman.h"
#define DVK2QWE_base DV_GRV, DV_Q, DV_W, DV_E, DV_R, DV_T, DV_Y, DV_U, DV_I,    DV_O,   DV_P,    DV_LBRC, DV_RBRC, \
                             DV_A, DV_S, DV_D, DV_F, DV_G, DV_H, DV_J, DV_K,    DV_L,   DV_SCLN, DV_QUOT, \
                             DV_Z, DV_X, DV_C, DV_V, DV_B, DV_N, DV_M, DV_COMM, DV_DOT, DV_SLSH
#define CMK2QWE_base KC_GRV, CM_Q, CM_W, CM_E, CM_R, CM_T, CM_Y, CM_U, CM_I,    CM_O,   CM_P,    KC_LBRC, KC_RBRC, \
                             CM_A, CM_S, CM_D, CM_F, CM_G, CM_H, CM_J, CM_K,    CM_L,   CM_SCLN, KC_QUOT, \
                             CM_Z, CM_X, CM_C, CM_V, CM_B, CM_N, CM_M, CM_COMM, CM_DOT, CM_SLSH
#define WMN2QWE_base KC_GRV, WK_Q, WK_W, WK_E, WK_R, WK_T, WK_Y, WK_U, WK_I,    WK_O,   WK_P,    KC_LBRC, KC_RBRC, \
                             WK_A, WK_S, WK_D, WK_F, WK_G, WK_H, WK_J, WK_K,    WK_L,   WK_SCLN, KC_QUOT, \
                             WK_Z, WK_X, WK_C, WK_V, WK_B, WK_N, WK_M, KC_COMM, KC_DOT, KC_SLSH
#define CMK2DVK_base KC_GRV, KC_QUOT, KC_COMM, KC_DOT,CM_P, CM_Y, CM_F, CM_G, CM_C, CM_R, CM_L, KC_LBRC, KC_RBRC, \
                             CM_A,    CM_O,    CM_E,  CM_U, CM_I, CM_D, CM_H, CM_T, CM_N, CM_S, CM_SLSH, \
                             CM_SCLN, CM_Q,    CM_J,  CM_K, CM_X, CM_B, CM_M, CM_W, CM_V, CM_Z
#define WMN2DVK_base KC_GRV, KC_QUOT, KC_COMM, KC_DOT,WK_P, WK_Y, WK_F, WK_G, WK_C, WK_R, WK_L, KC_LBRC, KC_RBRC, \
                             WK_A,    WK_O,    WK_E,  WK_U, WK_I, WK_D, WK_H, WK_T, WK_N, WK_S, KC_SLSH, \
                             WK_SCLN, WK_Q,    WK_J,  WK_K, WK_X, WK_B, WK_M, WK_W, WK_V, WK_Z
#define DVK2CMK_base DV_GRV, DV_Q, DV_W, DV_F, DV_P, DV_G, DV_J, DV_L, DV_U,    DV_Y,   DV_SCLN, DV_LBRC, DV_RBRC, \
                             DV_A, DV_R, DV_S, DV_T, DV_D, DV_H, DV_N, DV_E,    DV_I,   DV_O,    DV_QUOT, \
                             DV_Z, DV_X, DV_C, DV_V, DV_B, DV_K, DV_M, DV_COMM, DV_DOT, DV_SLSH
#define WMN2CMK_base KC_GRV, WK_Q, WK_W, WK_F, WK_P, WK_G, WK_J, WK_L, WK_U,    WK_Y,   WK_SCLN, KC_LBRC, KC_RBRC, \
                             WK_A, WK_R, WK_S, WK_T, WK_D, WK_H, WK_N, WK_E,    WK_I,   WK_O,    KC_QUOT, \
                             WK_Z, WK_X, WK_C, WK_V, WK_B, WK_K, WK_M, KC_COMM, KC_DOT, KC_SLSH
#define DVK2WMN_base DV_GRV, DV_Q, DV_D, DV_R, DV_W, DV_B, DV_J, DV_F, DV_U,    DV_P,   DV_SCLN, DV_LBRC, DV_RBRC, \
                             DV_A, DV_S, DV_H, DV_T, DV_G, DV_Y, DV_N, DV_E,    DV_O,   DV_I,    DV_QUOT, \
                             DV_Z, DV_X, DV_M, DV_C, DV_V, DV_K, DV_L, DV_COMM, DV_DOT, DV_SLSH
#define CMK2WMN_base KC_GRV, CM_Q, CM_D, CM_R, CM_W, CM_B, CM_J, CM_F, CM_U,    CM_P,   CM_SCLN, KC_LBRC, KC_RBRC, \
                             CM_A, CM_S, CM_H, CM_T, CM_G, CM_Y, CM_N, CM_E,    CM_O,   CM_I,    KC_QUOT, \
                             CM_Z, CM_X, CM_M, CM_C, CM_V, CM_K, CM_L, CM_COMM, CM_DOT, CM_SLSH
#endif // ALT_LAYOUTS_ENABLE

enum jian_layers {
  _QWERTY,
#ifdef ALT_LAYOUTS_ENABLE
  _DVORAK,
  _COLEMAK,
  _WORKMAN,
  _DVK2QWE,
  _DVK2CMK,
  _DVK2WMN,
  _CMK2QWE,
  _CMK2DVK,
  _CMK2WMN,
  _WMN2QWE,
  _WMN2DVK,
  _WMN2CMK,
#endif // ALT_LAYOUTS_ENABLE
  _ISO,
  _LOWER,
  _RAISE,
  _ADJUST,
  _BCKLT_ADJ,
  _THUMB_ALT,
#ifdef TRAINING_HALFES_LOCK
  _LEFT,
  _RIGHT,
#endif //TRAINING_HALFES_LOCK
#ifdef DIPS_ENABLE
  _DIPS,
#endif // DIPS_ENABLE
#ifdef STENO_ENABLE
  _PLOVER
#endif // STENO_ENABLE
};

enum jian_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  EXT_PLV,
  EXT_RGB,
  ISO,
  THUMB_ALT,
//ifdef ALT_LAYOUTS_ENABLE
  CH_WMN,
  CH_CMK,
  CH_QWE,
  CH_DVK,
//endif // ALT_LAYOUTS_ENABLE
#ifdef DIPS_ENABLE
  LAYOUT0,
  LAYOUT1,
  LAYOUT2,
  LAYOUT3,
  DIP_ISO,
  FLIP_TH,
  DIP6,
  DIP7,
  DIP8,
  DIP9,
  DIP10,
  DIP11,
#endif // DIPS_ENABLE
};

#ifdef TRAINING_HALFES_LOCK
static uint8_t lock_timeout = 1;
static uint8_t lock_cooldown = 0;
#endif //TRAINING_HALFES_LOCK
#ifdef DIPS_ENABLE
#ifdef ALT_LAYOUTS_ENABLE
static uint8_t layout_conversion_dip_state = 0;
#endif // ALT_LAYOUTS_ENABLE
#endif // DIPS_ENABLE

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define BL_ADJ  TG(_BCKLT_ADJ)
#define TG_LWR  TG(_LOWER)
#define TG_RSE  TG(_RAISE)

#define RBR_RGU MT(MOD_RGUI, KC_RBRC)
#define F12_RGU MT(MOD_RGUI, KC_F12)
#define EQL_LCT MT(MOD_LCTL, KC_EQL)
#define APP_LCT MT(MOD_LCTL, KC_APP)
#define EQL_RCT MT(MOD_RCTL, KC_EQL)
#define QUO_RCT MT(MOD_RCTL, KC_QUOT)
#define APP_RCT MT(MOD_RCTL, KC_APP)
#define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define PLS_LAL MT(MOD_LALT, KC_PPLS)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)

#define NBS_LCT MT(MOD_LCTL, KC_NUBS)
#define BSH_LAL MT(MOD_LALT, KC_BSLS)
#define APP_RAL MT(MOD_RALT, KC_APP)

#define BSP_LSH MT(MOD_LSFT, KC_BSPC)
#define BSP_RSH MT(MOD_RSFT, KC_BSPC)
#define SPC_LSH MT(MOD_LSFT, KC_SPC)
#define SPC_RSH MT(MOD_RSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

#define RGU_RBR RGUI_T(KC_RBRC)
#define RCT_QUO RCTL_T(KC_QUOT)

#define LAYOUT_base( \
    GRV, Q, W, E, R, T, Y, U, I,    O,   P,    LBRC, RBRC, \
         A, S, D, F, G, H, J, K,    L,   SCLN, QUOT, \
         Z, X, C, V, B, N, M, COMM, DOT, SLSH \
  ) \
  LAYOUT( \
  KC_LGUI, GRV,     Q,       W,       E,       R,       T,            Y,       U,       I,       O,       P,       LBRC,    RGU_RBR, \
           KC_LCTL, A,       S,       D,       F,       G,            H,       J,       K,       L,       SCLN,    RCT_QUO, \
           KC_LALT, Z,       X,       C,       V,       B,            N,       M,       COMM,    DOT,     SLSH,    BSL_RAL, \
                                      TAB_RSE, SPC_LSH, ENT_LWR,      ESC_LWR, BSP_RSH, DEL_RSE \
  )
#define LAYOUT_base_wrapper(...) LAYOUT_base(__VA_ARGS__)

#ifdef SWAP_HANDS_ENABLE
#define SW_TG SH_TG
#else
#define SW_TG _______
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_base_wrapper(QWERTY_base),

#ifdef DIPS_ENABLE
[_DIPS] = LAYOUT_DIPS(\
  LAYOUT0, LAYOUT1, LAYOUT2, LAYOUT3, DIP_ISO, FLIP_TH, \
  LAYOUT0, LAYOUT1, LAYOUT2, LAYOUT3, DIP_ISO, FLIP_TH \
),
#endif // DIPS_ENABLE

[_LOWER] = LAYOUT(
  _______, KC_UNDS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  F12_RGU,
           EQL_LCT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, MIN_RCT,
           PLS_LAL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
                                      _______, _______, _______,      _______,  _______, _______
),

[_RAISE] = LAYOUT(
  _______, KC_NLCK, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SLCK, KC_CAPS, _______,
           EQL_LCT, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  APP_RCT,
           _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______,
                                      _______, _______, _______,      _______, _______, _______
),

[_ADJUST] = LAYOUT_symmetric(
  RESET,   DEBUG,   KC_ASUP, CH_WMN,  CH_CMK,  CH_QWE,  CH_DVK,
           KC_ASRP, KC_ASTG, XXXXXXX, XXXXXXX, QWERTY,  PLOVER,
           BL_ADJ,  KC_ASDN, XXXXXXX, XXXXXXX, ISO,     THUMB_ALT,
                                      _______, SW_TG,   _______
),
#if defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)
[_BCKLT_ADJ] = LAYOUT_symmetric(
  XXXXXXX, XXXXXXX, XXXXXXX, BL_INC,  RGB_VAI, RGB_HUD, RGB_HUI,
           XXXXXXX, XXXXXXX, BL_DEC,  RGB_VAD, RGB_SAD, RGB_SAI,
           BL_ADJ,  BL_BRTG, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD,
                                      _______, _______, _______
),
#endif // defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)
#ifdef TRAINING_HALFES_LOCK
[_LEFT] = LAYOUT_base(
  _______, _______, _______, _______, _______, _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
           _______, _______, _______, _______, _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
           _______, _______, _______, _______, _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_RIGHT] = LAYOUT_base(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      _______, _______, _______, _______, _______, _______, _______,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      _______, _______, _______, _______, _______, _______,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      _______, _______, _______, _______, _______
),
#endif // TRAINING_HALFES_LOCK

#ifdef STENO_ENABLE
[_PLOVER] = LAYOUT(
  EXT_PLV, STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,       STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,  EXT_PLV,
           STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,      STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
           XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,      STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
                                      XXXXXXX, STN_A,   STN_O,        STN_E,   STN_U,   XXXXXXX
),
#endif // STENO_ENABLE

[_THUMB_ALT] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
                                      DEL_RSE, BSP_LSH, ESC_LWR,      ENT_LWR, SPC_RSH, TAB_RSE
),

[_ISO] = LAYOUT(
  _______, _______,         _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
           LCTL_T(KC_NUBS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
           LALT_T(KC_NUHS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, KC_RALT,
                                              _______, _______, _______,      _______, _______, _______
),

#ifdef ALT_LAYOUTS_ENABLE
[_DVORAK] = LAYOUT_base_wrapper(DVORAK_base),
[_COLEMAK] = LAYOUT_base_wrapper(COLEMAK_base),
[_WORKMAN] = LAYOUT_base_wrapper(WORKMAN_base),
[_DVK2QWE] = LAYOUT_base_wrapper(DVK2QWE_base),
[_CMK2QWE] = LAYOUT_base_wrapper(CMK2QWE_base),
[_WMN2QWE] = LAYOUT_base_wrapper(WMN2QWE_base),
[_CMK2DVK] = LAYOUT_base_wrapper(CMK2DVK_base),
[_WMN2DVK] = LAYOUT_base_wrapper(WMN2DVK_base),
[_DVK2CMK] = LAYOUT_base_wrapper(DVK2CMK_base),
[_WMN2CMK] = LAYOUT_base_wrapper(WMN2CMK_base),
[_DVK2WMN] = LAYOUT_base_wrapper(DVK2WMN_base),
[_CMK2WMN] = LAYOUT_base_wrapper(CMK2WMN_base)
#endif // ALT_LAYOUTS_ENABLE
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef DIPS_ENABLE
#ifdef ALT_LAYOUTS_ENABLE
void layout_convert(uint8_t statuses) {
  switch (0b1111 & statuses) {
    case 0b0000:
      set_single_persistent_default_layer(_QWERTY);
      break;
    case 0b0001:
      set_single_persistent_default_layer(_DVORAK);
      break;
    case 0b0010:
      set_single_persistent_default_layer(_COLEMAK);
      break;
    case 0b0011:
      set_single_persistent_default_layer(_WORKMAN);
      break;
    case 0b0100:
      set_single_persistent_default_layer(_DVK2QWE);
      break;
    case 0b0101:
      set_single_persistent_default_layer(_QWERTY);
      break;
    case 0b0110:
      set_single_persistent_default_layer(_DVK2CMK);
      break;
    case 0b0111:
      set_single_persistent_default_layer(_DVK2WMN);
      break;
    case 0b1000:
      set_single_persistent_default_layer(_CMK2QWE);
      break;
    case 0b1001:
      set_single_persistent_default_layer(_CMK2DVK);
      break;
    case 0b1010:
      set_single_persistent_default_layer(_QWERTY);
      break;
    case 0b1011:
      set_single_persistent_default_layer(_CMK2WMN);
      break;
    case 0b1100:
      set_single_persistent_default_layer(_WMN2QWE);
      break;
    case 0b1101:
      set_single_persistent_default_layer(_WMN2DVK);
      break;
    case 0b1110:
      set_single_persistent_default_layer(_WMN2CMK);
      break;
    case 0b1111:
      set_single_persistent_default_layer(_QWERTY);
      break;
   }
}
#endif // ALT_LAYOUTS_ENABLE
#endif // DIPS_ENABLE

void matrix_init_user(void) {
#ifdef DIPS_ENABLE
  layer_on(_DIPS);
#endif // DIPS_ENABLE
}

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  if (user_config.thumb_alt) {
     layer_on(_THUMB_ALT);
  } else {
     layer_off(_THUMB_ALT);
  }
  if (user_config.iso) {
     layer_on(_ISO);
  } else {
     layer_off(_ISO);
  }
}

#ifdef ALT_LAYOUTS_ENABLE
static char change_layout_input = 0;
static bool change_layout_keystroke = 0;
void change_layout_conversion(uint16_t keycode) {
    switch (keycode) {
        case CH_WMN:
            change_layout_input |= 0b1000 << (change_layout_keystroke << 2);
            break;
        case CH_CMK:
            change_layout_input |= 0b0100 << (change_layout_keystroke << 2);
            break;
        case CH_DVK:
            change_layout_input |= 0b0010 << (change_layout_keystroke << 2);
            break;
        case CH_QWE:
            change_layout_input |= 0b0001 << (change_layout_keystroke << 2);
            break;
    }
    if (change_layout_keystroke == 1) {
        switch (change_layout_input) {
            case 0b00010001:
                set_single_persistent_default_layer(_QWERTY);
                break;
            case 0b00100001:
                set_single_persistent_default_layer(_DVORAK);
                break;
            case 0b01000001:
                set_single_persistent_default_layer(_COLEMAK);
                break;
            case 0b10000001:
                set_single_persistent_default_layer(_WORKMAN);
                break;
            case 0b00010010:
                set_single_persistent_default_layer(_DVK2QWE);
                break;
            case 0b00100010:
                set_single_persistent_default_layer(_QWERTY);
                break;
            case 0b01000010:
                set_single_persistent_default_layer(_DVK2CMK);
                break;
            case 0b10000010:
                set_single_persistent_default_layer(_DVK2WMN);
                break;
            case 0b00010100:
                set_single_persistent_default_layer(_CMK2QWE);
                break;
            case 0b00100100:
                set_single_persistent_default_layer(_CMK2DVK);
                break;
            case 0b01000100:
                set_single_persistent_default_layer(_QWERTY);
                break;
            case 0b10000100:
                set_single_persistent_default_layer(_CMK2WMN);
                break;
            case 0b00011000:
                set_single_persistent_default_layer(_WMN2QWE);
                break;
            case 0b00101000:
                set_single_persistent_default_layer(_WMN2DVK);
                break;
            case 0b01001000:
                set_single_persistent_default_layer(_WMN2CMK);
                break;
            case 0b10001000:
                set_single_persistent_default_layer(_QWERTY);
                break;
        }
        change_layout_input = 0;
    }
    change_layout_keystroke ^= 1;
}
#endif // ALT_LAYOUTS_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef TRAINING_HALFES_LOCK
  if (!record->event.pressed) {
      lock_cooldown = --lock_cooldown < 0 ? 0 : lock_cooldown;
  }
  if (lock_cooldown == 0) {
      layer_off(_LEFT);
      layer_off(_RIGHT);
  }
#endif // TRAINING_HALFES_LOCK
  switch (keycode) {
#ifdef TRAINING_HALFES_LOCK
    case SPC_RSH:
    case BSP_RSH:
    case DEL_RSE:
    case ESC_LWR:
    case BSL_RAL:
    case RGU_RBR:
    case RCT_QUO:
    if (record->event.pressed) {
        layer_on(_LEFT);
        lock_cooldown = lock_timeout;
    }
    else {
        lock_cooldown = 0;
        layer_off(_LEFT);
    }
    break;
    case BSP_LSH:
    case SPC_LSH:
    case TAB_RSE:
    case ENT_LWR:
    case KC_LCTL:
    case KC_LGUI:
    case KC_LALT:
    if (record->event.pressed) {
        layer_on(_RIGHT);
        lock_cooldown = lock_timeout;
    }
    else {
        lock_cooldown = 0;
        layer_off(_RIGHT);
    }
    break;
#endif // TRAINING_HALFES_LOCK
#ifdef STENO_ENABLE
    case PLOVER:
      if (!record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
#endif // STENO_ENABLE
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
#ifdef ALT_LAYOUTS_ENABLE
    case CH_WMN:
    case CH_CMK:
    case CH_QWE:
    case CH_DVK:
      if (record->event.pressed) {
        change_layout_conversion(keycode);
      }
      return false;
#endif // ALT_LAYOUTS_ENABLE
#ifdef DIPS_ENABLE
#ifdef ALT_LAYOUTS_ENABLE
    case LAYOUT0:
      if (record->event.pressed) {
        layout_conversion_dip_state |= 1 << 0;
      } else {
        layout_conversion_dip_state &= ~(1 << 0);
      }
      layout_convert(layout_conversion_dip_state);
      return false;
    case LAYOUT1:
      if (record->event.pressed) {
        layout_conversion_dip_state |= 1 << 1;
      } else {
        layout_conversion_dip_state &= ~(1 << 1);
      }
      layout_convert(layout_conversion_dip_state);
      return false;
    case LAYOUT2:
      if (record->event.pressed) {
        layout_conversion_dip_state |= 1 << 2;
      } else {
        layout_conversion_dip_state &= ~(1 << 2);
      }
      layout_convert(layout_conversion_dip_state);
      return false;
    case LAYOUT3:
      if (record->event.pressed) {
        layout_conversion_dip_state |= 1 << 3;
      } else {
        layout_conversion_dip_state &= ~(1 << 3);
      }
      layout_convert(layout_conversion_dip_state);
      return false;
#endif // ALT_LAYOUTS_ENABLE
    case DIP_ISO:
      if (record->event.pressed) {
          layer_on(_ISO);
      } else {
          layer_off(_ISO);
      }
      return false;
    case FLIP_TH:
      if (record->event.pressed) {
          layer_on(_THUMB_ALT);
      } else {
          layer_off(_THUMB_ALT);
      }
      return false;
#endif // DIPS_ENABLE
    case THUMB_ALT:
      if (record->event.pressed) {
        layer_invert(_THUMB_ALT);
        user_config.thumb_alt ^= 1;
        eeconfig_update_user(user_config.raw);
      }
      return false;
    case ISO:
      if (record->event.pressed) {
        layer_invert(_ISO);
        user_config.iso ^= 1;
        eeconfig_update_user(user_config.raw);
      }
      return false;
  }
  return true;
}
