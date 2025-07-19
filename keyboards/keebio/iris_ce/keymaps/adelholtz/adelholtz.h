/**
 * TRL: Top Row Layer
 * HRL: Home Row Layer
 * HRM: Home Row Mod
 */
enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
  LCURLY, // defined in keymap.c process_record_user
  RCURLY, // defined in keymap.c process_record_user
  HRM_GUI_D,
  HRM_GUI_H,
  HRM_ALT_S,
  HRM_CTRL_E,
  HRL_BRACKETS_T,
  HRL_BRACKETS_N,
  TRL_MEDIA_L,
  TRL_MEDIA_P,
  TRL_SPECIAL_F,
  PIPE_,  // defined in keymap.c process_record_user
  LBRACKET,  // defined in keymap.c process_record_user
  RBRACKET,  // defined in keymap.c process_record_user
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
#define TRL_SPECIAL_F LT(_SPECIAL, DE_F)

enum custom_layers {
  _COLEMAK,
  _GAME,
  _NAVIGATION,
  _BRACKETS,
  _EXTRA,
  _MEDIA,
  _SPECIAL
};
enum custom_layers valid_tap_dance_layers[] = {
  _COLEMAK, _GAME, _NAVIGATION, _BRACKETS,
  _EXTRA, _MEDIA, _SPECIAL
};
enum tap_dance_keys{
  SPACE_TAB,
  NAV_LMAGIC,
  XTRA_RMAGIC,
};
