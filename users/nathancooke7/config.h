#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 220

#define COMBO_TERM 30

#define MACRO_TIMER 20

/* conserve space on MCU */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE


/* Homerow mod tap */
#define KC_CA LCTL_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_GD LGUI_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_GK RGUI_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_CSCLN RCTL_T(KC_SCLN)

/* Layer Tap */
#define DRAG_V LT(_DRAGSCRL, KC_V)
#define MISC_DEL LT(_MISC, KC_DELETE)
#define NAV_SPACE LT(_NAV, KC_SPC)
#define NAV_Z LT(_NAV, KC_Z)
#define SYM_ENT LT(_SYMBOLS, KC_ENT)
#define SYM_SLSH LT(_SYMBOLS, KC_SLSH)
#define MOU_X LT(_MOUSE_MAN, KC_X)
#define WORDS_BACK LT(_WORDS, KC_BACKSPACE)

/* Abbreviations */
#define CAPS KC_CAPSLOCK
#define DEL KC_DELETE
#define L_PAREN KC_LEFT_PAREN
#define LEFT KC_LEFT
#define R_PAREN KC_RIGHT_PAREN
#define RIGHT KC_RIGHT

/* TEXT NAV */
#define ALT_L RALT(KC_LEFT)
#define ALT_R RALT(KC_RIGHT)
#define GUI_L RGUI(KC_LEFT)
#define GUI_R RGUI(KC_RIGHT)
#define GUI_BSPC RGUI(KC_BSPC)

/* APP nav */
#define ALT_D RALT(KC_DOWN)
#define ALT_U RALT(KC_UP)
#define WEB_B RGUI(KC_LBRC)
#define WEB_F RGUI(KC_RBRC)

/* Shortcuts */
#define SCREEN_CAP LSFT(LGUI(KC_4))
#define SCRN_BRIT KC_F15
#define SCRN_DARK KC_F14
#define COPY LGUI(KC_C)
#define CUT LGUI(KC_X)
#define PASTE LGUI(KC_V)

/* Mission Control */
#define DESK_L RCTL(KC_LEFT)
#define DESK_R RCTL(KC_RIGHT)
#define DESKTOP KC_F11
#define MISSION RCTL(KC_UP)
/* Amethyst */
#define AM_1 KC_F4
#define AM_2 KC_F2
#define AM_RITE LALT(LCTL(LSFT(KC_2)))
#define AM_LEFT LALT(LCTL(LSFT(KC_1)))
#define AM_CYCLE LSFT(LALT(LCTL(KC_SPC)))
#define AM_CW LSFT(LALT(KC_J))
#define AM_CCW LSFT(LALT(KC_K))

/* MOUSE */
#define L_CLICK KC_MS_BTN1
#define R_CLICK KC_MS_BTN2
/* These are mapped in SteerMouse */
#define MS_BACK KC_MS_BTN4
#define MS_FORE KC_MS_BTN5

#define TAB_BACK LCTL(LSFT(KC_TAB))
#define TAB_FORE LCTL(KC_TAB)

/* Audio */
#define VOL_D KC_AUDIO_VOL_DOWN
#define VOL_U KC_AUDIO_VOL_UP
#define MUTE KC_AUDIO_MUTE

/* Google Meet */
#define MUTE_MIC LGUI(KC_D)
#define MUTE_CAM LGUI(KC_E)
#define RAZ_HAND LCTL(LGUI(KC_H))
