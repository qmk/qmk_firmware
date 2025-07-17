enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
  MACLCURLY, // defined in keymap.c process_record_user
  MACRCURLY, // defined in keymap.c process_record_user
  HRM_GUI_D,
  HRM_GUI_H,
  HRM_ALT_S,
  HRM_CTRL_E,
  HRL_BRACKETS_T,
  HRL_BRACKETS_N,
  TRL_MEDIA_L,
  TRL_MEDIA_P,
  RELOAD // defined in keymap.c process_record_user
};

#define TAPPING_TERM_PER_KEY

// #define MACLCURLY ALGR(DE_8)
// #define MACRCURLY ALGR(DE_9)
#define HRM_GUI_D MT(MOD_LGUI, DE_D)
#define HRM_ALT_S MT(MOD_LALT | MOD_RALT, DE_S)
#define HRM_GUI_H MT(MOD_LGUI, DE_H)
#define HRM_CTRL_E MT(MOD_LCTL, DE_E)
#define HRL_BRACKETS_T LT(_BRACKETS, DE_T)
#define HRL_BRACKETS_N LT(_BRACKETS, DE_N)
#define TRL_MEDIA_L LT(_MEDIA, DE_L)
#define TRL_MEDIA_P LT(_MEDIA, DE_P)
#define HRM_SPECIAL_F LT(_SPECIAL, DE_F)
