/**
 * TRL: Top Row Layer
 * HRL: Home Row Layer
 * HRM: Home Row Mod
 */
enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
  // Home Row Mod Buttons
  HRM_GUI_D,
  HRM_GUI_H,
  HRM_ALT_S,
  HRM_CTRL_E,
  // Home Row Layer Buttons
  HRL_BRACKETS_T,
  HRL_BRACKETS_N,
  // Tor Row Layer Buttons
  TRL_MEDIA_L,
  TRL_MEDIA_P,
  TRL_SPECIAL_F,
  // OS dependent buttons
  LCURLY, // OS specific { - defined in keymap.c process_record_user
  RCURLY, // OS specific } - defined in keymap.c process_record_user
  PIPE_,  // OS specific | - defined in keymap.c process_record_user
  LBRACKET,  // OS specific [ - defined in keymap.c process_record_user
  RBRACKET,  // OS specific ] - defined in keymap.c process_record_user
  RELOAD, // defined in keymap.c process_record_user
  GAME,
  COLEMAK
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

// used in layer_layout.c
enum custom_layers {
  _COLEMAK,
  _GAME,
  _NAVIGATION,
  _BRACKETS,
  _EXTRA,
  _MEDIA,
  _SPECIAL
};
// layers that can be used in a tap dance combination for layer changes
// used in tap_dance.c
enum custom_layers valid_tap_dance_layers[] = {
  _COLEMAK, _GAME, _NAVIGATION, _BRACKETS,
  _EXTRA, _MEDIA, _SPECIAL
};
enum tap_dance_keys{
  SPACE_TAB,
  MAGIC_TAB,
  NAV_LMAGIC,
  XTRA_RMAGIC,
};
