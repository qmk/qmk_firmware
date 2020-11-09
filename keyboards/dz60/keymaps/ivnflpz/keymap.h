#include QMK_KEYBOARD_H

#define ______ KC_NO
#define VS_TGL LCTL(KC_GRV)

enum layers {
  _WINDOWS,
  _MAC,
  _FN,
  _MOUSE,
  _NAV
};

enum custom_keycodes {
  DLT_LN = SAFE_RANGE, // delete line
  VS_CMD,   // VS Code cmd line
  HL_WD,    // highlight word
  HL_NWD,   // highlight next word
  CP_LN,    // copy line
  CT_LN,    // cut line
  PT_LN,     // paste line

  // base layers
  WINDOWS_LY,
  MAC_LY,

  // window shortcuts
  W_LEFT,
  W_UP,
  W_DOWN,
  W_RIGHT,
  W_CLOSE,
  W_FULL,

  // screen shortcuts
  SCRN_LEFT,
  SCRN_RGHT,

  // other
  TSK_MGR
};

#define RGB_STATIC_MODE     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT)
#define RGB_BL_LIGHT        rgblight_sethsv(HSV_RED);   //rgb light for BL layer
#define RGB_FL_LIGHT        rgblight_sethsv(HSV_BLUE);      //rgb light for FL layer

#define PROCESS_OS_CMD(windows_cmd, mac_cmd) process_os_cmd(PSTR(windows_cmd), PSTR(mac_cmd))
#define WINDOW_NAV(string) window_nav(PSTR(SS_TAP(string)))

void close_window(void);
void highlight_line(bool);
void open_task_manager(void);
void process_os_cmd(const char*, const char*);
void window_nav(const char*);
void highlight_word(void);
void highlight_next_word(void);
void full_screen(void);
