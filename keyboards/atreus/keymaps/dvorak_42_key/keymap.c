
#include QMK_KEYBOARD_H

// layers
#define BASE      0
#define KEYNAV    1
#define KEYSEL    2
#define COMBINED  3
#define BROWSER_CONTROL 4

// aliases
// shell
#define SHELL_DEL_WORD RCTL(KC_W)

// comment out to use android studio macros instead
#define USE_VSCODE_MACROS

// android studio shortcuts
#define AS_TABLEFT LALT(KC_LEFT)
#define AS_TABRIGHT LALT(KC_RIGHT)
#define AS_SYMBOL LCTL(LALT(KC_N))
#define AS_CLASS LCTL(KC_N)
#define AS_FINDUSAGE LALT(KC_F7)
#define AS_BACK LCTL(LALT(KC_LEFT))
#define AS_GO_DECLARATION LCTL(KC_B)
#define AS_GO_IMPLEMENTATION LCTL(LALT(KC_B))
#define AS_CLOSETAB LCTL(KC_F4)
#define AS_CLOSETOOLWINDOW LCTL(LSFT(KC_F4))
#define AS_ALTENTER LALT(KC_ENTER)

// visual studio code shortcuts
#define VS_FILE LCTL(KC_P)
#define VS_LINE LCTL(KC_G)
#define VS_SYMBOLEDITOR LCTL(LSFT(KC_O))
#define VS_DEFINITION KC_F12
#define VS_IMPLEMENTATION LCTL(KC_F12)
#define VS_REFERENCES LSFT(KC_F12)
#define VS_BACK LALT(KC_LEFT)
#define VS_BRACKET LCTL(LSFT(KC_BSLS))
#define VS_TABLEFT LCTL(KC_PGUP)
#define VS_TABRIGHT LCTL(KC_PGDN)
#define VS_CLOSETAB LCTL(KC_W)
#define VS_CLOSEPANEL LCTL(LSFT(KC_W))
#define VS_TERMINAL LCTL(KC_GRAVE)
#define VS_BUILD LCTL(LSFT(KC_B))
#define VS_COMMANDS LCTL(LSFT(KC_P))
#define VS_CMT_BLOCK LSFT(LALT(KC_A))
#define VS_CMT_LINE LCTL(KC_SLSH)
#define VS_DEL_LINE LCTL(LSFT(KC_K))
#define VS_COPYLINEDOWN LSFT(LALT(KC_DOWN))
// visual studio bookmark commands
#define VS_BM_LIST LCTL(LALT(KC_L))
#define VS_BM_LISTALL LCTL(LALT(KC_A))
#define VS_BM_PREV LCTL(LALT(KC_P))
#define VS_BM_NEXT LCTL(LALT(KC_N))
#define VS_BM_TOGGLE LCTL(LALT(KC_K))
#define VS_BM_LABEL LCTL(LALT(KC_B))

/*
// VS code bookmark prev/next requires the following in vscode shortcuts config
    {
        "key": "ctrl+alt+p",
        "command": "bookmarks.jumpToPrevious"
    },
    {
        "key": "ctrl+alt+n",
        "command": "bookmarks.jumpToNext"
    },
*/

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here

  // Windows 10 macros
  W10_TASKVIEW,
  W10_WORKSPACE_LEFT,
  W10_WORKSPACE_RIGHT,

};

// building/flashing instructions:
// make atreus/astar:dvorak_42_key:flash

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_QUOTE,      KC_COMMA,      KC_DOT,     KC_P,                KC_Y,                                 KC_F,       KC_G,      KC_C,    KC_R,          KC_L,
    KC_A,          KC_O,          KC_E,       KC_U,                KC_I,                                 KC_D,       KC_H,      KC_T,    KC_N,          KC_S,
    KC_SCOLON,     KC_Q,          KC_J,       KC_K,                KC_X,                                 KC_B,       KC_M,      KC_W,    KC_V,          KC_Z,
    OSM(MOD_LSFT), OSM(MOD_LCTL), MO(KEYSEL), MO(BROWSER_CONTROL), MO(COMBINED), MO(KEYNAV), KC_ENTER,   KC_SPACE,  KC_BSPC, RCTL(KC_BSPC), KC_CAPSLOCK, OSM(MOD_LSFT)
  ),

#ifdef USE_VSCODE_MACROS
// use visual studio code macros on the KEYNAV layer
  [KEYNAV] = LAYOUT(
    KC_ESC,             VS_DEFINITION,       RCTL(KC_Z),      RCTL(KC_S),       MEH(KC_A),                           MEH(KC_B),     KC_HOME,    KC_UP,           KC_END,     KC_PGUP,
    VS_BACK,            VS_SYMBOLEDITOR,     RSFT(KC_TAB),    KC_TAB,           SHELL_DEL_WORD,                      LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT),
    VS_LINE,            VS_FILE,             VS_TABLEFT,      VS_TABRIGHT,      VS_CLOSETAB,                         KC_TRNS,       RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDOWN,
    VS_COMMANDS,        VS_CMT_LINE,         VS_BM_PREV,      VS_BM_NEXT,       VS_BM_TOGGLE,          KC_TRNS, KC_ENTER, KC_SPACE,      KC_BSPC,    RCTL(KC_BSPC),   KC_DELETE,  LCTL(KC_DELETE)
  ),
#else
// use android studio macros on the KEYNAV layer
  [KEYNAV] = LAYOUT(
    KC_ESC,             AS_GO_IMPLEMENTATION,  RCTL(KC_Z),      RCTL(KC_S),       MEH(KC_A),                           MEH(KC_B),     KC_HOME,    KC_UP,           KC_END,     KC_PGUP,
    AS_BACK,            AS_SYMBOL,             RSFT(KC_TAB),    KC_TAB,           SHELL_DEL_WORD,                      LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT),
    AS_FINDUSAGE,       AS_CLASS,              AS_TABLEFT,      AS_TABRIGHT,      AS_CLOSETAB,                         KC_TRNS,       RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDOWN,
    AS_CLOSETOOLWINDOW, AS_GO_DECLARATION,     KC_TRNS,         KC_TRNS,          AS_ALTENTER,          KC_TRNS, KC_ENTER, KC_SPACE,      KC_BSPC,    RCTL(KC_BSPC),   KC_DELETE,  LCTL(KC_DELETE)
  ),
#endif

  [KEYSEL] = LAYOUT(
    MEH(KC_G), MEH(KC_H),MEH(KC_I), MEH(KC_J), MEH(KC_K),                    KC_TRNS,             RSFT(KC_HOME), RSFT(KC_UP),   RSFT(KC_END),   RSFT(KC_PGUP),
    MEH(KC_L), MEH(KC_M),MEH(KC_N), MEH(KC_O), MEH(KC_P),                    RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)),
    MEH(KC_Q), MEH(KC_R),MEH(KC_S), MEH(KC_T), MEH(KC_U),                    KC_TRNS,             RCTL(KC_C),    RCTL(KC_X),    RCTL(KC_V),     RSFT(KC_PGDN),
    RESET,     KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_ENTER, KC_SPACE,            KC_BSPC,       RCTL(KC_BSPC), KC_DELETE,      LCTL(KC_DELETE)
  ),

  [COMBINED] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH,     KC_DLR,      KC_PERC,                   KC_PLUS,  KC_7, KC_8,   KC_9,    KC_ASTR,
    KC_LPRN, KC_RPRN, KC_LBRACKET, KC_RBRACKET, KC_UNDS,                   KC_MINS,  KC_4, KC_5,   KC_6,    KC_SLSH,
    KC_COLN, KC_DQUO, KC_LCBR,     KC_RCBR,     KC_AMPR,                   KC_EQUAL, KC_1, KC_2,   KC_3,    KC_QUES,
    KC_TRNS, KC_TILD, KC_GRAVE,    KC_CIRC,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_0, KC_DOT, KC_PIPE, KC_BSLS
  ),

  [BROWSER_CONTROL] = LAYOUT(
    MEH(KC_0), KC_BTN3,      KC_MS_U,            KC_BTN1,             KC_BTN2,                      KC_UP,      KC_PGUP,            KC_PGDN,      KC_MS_WH_UP,   MEH(KC_9),
    MEH(KC_1), KC_MS_L,      KC_MS_D,            KC_MS_R,             MEH(KC_6),                    KC_DOWN,    RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), KC_MS_WH_DOWN, LALT(KC_LEFT),
    MEH(KC_2), W10_TASKVIEW, W10_WORKSPACE_LEFT, W10_WORKSPACE_RIGHT, MEH(KC_7),                    MEH(KC_8),  RCTL(KC_1),         RCTL(KC_9),   KC_F6,         KC_F5,
    KC_TRNS,   KC_TRNS,      KC_TRNS,            KC_TRNS,             KC_TRNS, KC_TRNS, RCTL(KC_W), RCTL(KC_T), KC_TRNS,             KC_TRNS,     KC_TRNS,       KC_TRNS
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed) {
    switch (keycode) {
    // windows 10 workspace shortcuts
    case W10_TASKVIEW:
        tap_code16(G(KC_TAB));
        return true;
        break;
    case W10_WORKSPACE_LEFT:
        tap_code16(G(C(KC_LEFT)));
        return true;
        break;
    case W10_WORKSPACE_RIGHT:
        tap_code16(G(C(KC_RIGHT)));
        break;
	}
  }

  return true;
}
