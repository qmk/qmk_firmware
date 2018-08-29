
 #include "planck.h"
 #include "action_layer.h"


extern keymap_config_t keymap_config;

#define EXCEL_HOME LALT(KC_H)
#define EXCEL_COL LCTL(KC_SPC)
#define EXCEL_ROW LSFT(KC_SPC)
#define DESK_LEFT LCTL(LGUI(KC_LEFT))
#define WIN_LEFT LSFT(KC_TAB)
#define WIN_CLOSE LALT(KC_F4)
#define WIN_RIGHT KC_TAB
#define DESK_RIGHT LCTL(LGUI(KC_RGHT))
#define DOCS LGUI(KC_E)
#define SNAP_RIGHT LGUI(KC_LEFT)
#define SNAP_UP LGUI(KC_UP)
#define SNAP_LEFT LGUI(KC_RGHT)
#define SNAP_DOWN LGUI(KC_DOWN)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define CUT LCTL(KC_X)
#define UNDO LCTL(KC_Z)
#define FIND LCTL(KC_F)




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  KEYMAP(
    KC_ESC,     KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,       KC_P,           KC_BSPC, 
    KC_TAB,     KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT, 
    KC_LSFT,    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_UP,          SFT_T(KC_ENT), 
    MO(1),      KC_LCTL,        KC_LALT,        KC_LGUI,        MO(2),          LT(5,KC_ENT),   LT(4,KC_SPC),   MO(3),          KC_SLSH,        KC_LEFT,        KC_DOWN,        CTL_T(KC_RGHT)),

  KEYMAP(
    KC_ESC,     KC_NLCK,        LCTL(KC_SPC),   KC_UP,          LSFT(KC_SPC),   KC_DLR,         KC_EQL,         KC_P7,          KC_P8,          KC_P9,          KC_PPLS,        LCTL(KC_BSPC), 
    KC_TAB,     FIND,           KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_PERC,        KC_CIRC,        KC_P4,          KC_P5,          KC_P6,          KC_PMNS,        KC_BSLS, 
    KC_LSFT,    UNDO,           CUT,            COPY,           PASTE,          EXCEL_HOME,     KC_PSCR,        KC_P1,          KC_P2,          KC_P3,          KC_PSLS,        KC_LSFT, 
    KC_TRNS,    KC_LCTL,        KC_LALT,        KC_LGUI,        TO(1),          KC_ENT,         KC_SPC,         KC_PENT,        KC_P0,          KC_PDOT,        KC_PAST,        KC_LCTL),

  KEYMAP(
    KC_TILD,    KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_DEL, 
    KC_CAPS,    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_UNDS,        KC_EQL,         KC_LBRC,        KC_LCBR,        KC_LPRN, 
    KC_LSFT,    KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_MUTE,        KC_MPLY,        KC_MNXT,        KC_PGUP,        SFT_T(KC_VOLU), 
    TO(0),      KC_LCTL,        KC_LALT,        KC_LGUI,        KC_TRNS,        KC_ENT,         KC_SPC,         MO(3),          KC_PSCR,        KC_MPRV,        KC_PGDOWN,      CTL_T(KC_VOLD)),

  KEYMAP(
    KC_TILD,    DESK_LEFT,      WIN_LEFT,       KC_F4,          WIN_RIGHT,      DESK_RIGHT,     DOCS,           SNAP_LEFT,  SNAP_UP,        SNAP_RIGHT,     SNAP_DOWN,      KC_DEL, 
    KC_CAPS,    KC_QUOT,        KC_LBRC,        KC_LCBR,        KC_LPRN,        KC_BSLS,        KC_SLSH,        KC_RPRN,    KC_RCBR,        KC_RBRC,        KC_DQUO,        KC_QUOT, 
    KC_PWR,     KC_SLEP,        KC_WAKE,        KC_HOME,        BL_BRTG,        BL_STEP,        KC_TRNS,        KC_CALC,    KC_COMM,        KC_DOT,         KC_COLON,       KC_LSFT, 
    TO(0),      KC_LCTL,        KC_LALT,        KC_LGUI,        KC_LALT,        KC_LCTL,        KC_TRNS,        KC_TRNS,    AU_TOG,         MU_TOG,         MU_MOD,         LCTL(KC_RGHT)),

  KEYMAP(
    TO(0),      KC_LSCR,        WIN_LEFT,       KC_MS_WH_UP,    WIN_RIGHT,      KC_TRNS,        KC_TRNS,        KC_MS_BTN1,     KC_MS_U,        KC_MS_BTN2,     KC_TRNS,        KC_TRNS, 
    KC_TRNS,    KC_INS,     KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_TRNS,        KC_TRNS,        KC_MS_L,        KC_MS_D,        KC_MS_R,        KC_TRNS,        KC_TRNS, 
    RESET,      KC_APP,     KC_MS_ACCEL0,   KC_MS_ACCEL0,   KC_MS_ACCEL0,   KC_TRNS,        KC_TRNS,        TO(0),          TO(1),          TO(2),          TO(3),          TO(4), 
    TO(0),      KC_MENU,        KC_TRNS,        KC_TRNS,        KC_LALT,        KC_ENT,         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_LEFT,        KC_DOWN,    KC_RCTL),

  KEYMAP(
    KC_BSPC,    KC_P,           KC_O,           KC_I,           KC_U,           KC_Y,           KC_T,           KC_R,           KC_E,           KC_W,           KC_Q,       KC_BSPC, 
    KC_TAB,     KC_SCLN,    KC_L,           KC_K,           KC_J,           KC_H,           KC_G,           KC_F,           KC_D,           KC_S,           KC_A,           KC_QUOT, 
    KC_LSFT,    KC_ENT,     KC_DOT,     KC_COMM,    KC_M,           KC_N,           KC_B,           KC_V,           KC_C,       KC_X,           KC_Z,           SFT_T(KC_ENT), 
    TO(0),      KC_LCTL,        KC_LALT,        KC_LGUI,        MO(2),          KC_TRNS,    KC_TRNS,        MO(3),          KC_SLSH,        KC_LEFT,        KC_DOWN,    LCTL(KC_RGHT)),
 
  

};




#ifdef AUDIO_ENABLE


#define ZELDA_PUZZLE \
    Q__NOTE(_G5),     \
    Q__NOTE(_FS5),    \
    Q__NOTE(_DS5),     \
    Q__NOTE(_A4),    \
    Q__NOTE(_GS4),     \
    Q__NOTE(_E5),     \
    Q__NOTE(_GS5),     \
    HD_NOTE(_C6),

#define KC_ZELDA_TREASURE \
    Q__NOTE(_A4 ), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4 ), \
    HD_NOTE(_C5 ), \

#define MARIO_THEME \
    Q__NOTE(_E5), \
    H__NOTE(_E5), \
    H__NOTE(_E5), \
    Q__NOTE(_C5), \
    H__NOTE(_E5), \
    W__NOTE(_G5), \
    Q__NOTE(_G4),

#define MARIO_GAMEOVER \
    HD_NOTE(_C5 ), \
    HD_NOTE(_G4 ), \
    H__NOTE(_E4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_B4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_AF4), \
    H__NOTE(_BF4), \
    H__NOTE(_AF4), \
    WD_NOTE(_G4 ),

#define SONIC_RING \
    E__NOTE(_E6),  \
    E__NOTE(_G6),  \
    HD_NOTE(_C7),

    #define IMPERIAL_MARCH \
  HD_NOTE(_A4), HD_NOTE(_A4), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), \
  HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4), \
  HD_NOTE(_E5), HD_NOTE(_E5), HD_NOTE(_E5), QD_NOTE(_F5), QD_NOTE(_C5), \
  HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4)

  #define ONE_UP_SOUND \
    Q__NOTE(_E6  ),  \
    Q__NOTE(_G6  ),  \
    Q__NOTE(_E7  ),  \
    Q__NOTE(_C7  ),  \
    Q__NOTE(_D7  ),  \
    Q__NOTE(_G7  ),

    #define NUMBER_ONE \
    HD_NOTE(_F4 ), \
    Q__NOTE(_C5 ), \
    E__NOTE(_B4 ), \
    E__NOTE(_C5 ), \
    E__NOTE(_B4 ), \
    E__NOTE(_C5 ), \
    Q__NOTE(_B4 ), \
    Q__NOTE(_C5 ), \
    H__NOTE(_AF4), \
    HD_NOTE(_F4 ), \
    Q__NOTE(_F4 ), \
    Q__NOTE(_AF4), \
    Q__NOTE(_C5 ), \
    H__NOTE(_DF5), \
    H__NOTE(_AF4), \
    H__NOTE(_DF5), \
    H__NOTE(_EF5), \
    Q__NOTE(_C5 ), \
    Q__NOTE(_DF5), \
    Q__NOTE(_C5 ), \
    Q__NOTE(_DF5), \
    H__NOTE(_C5 ),

float tone_my_startup[][2] = SONG(ZELDA_PUZZLE);
float tone_my_goodbye[][2] = SONG(MARIO_GAMEOVER);

float tone_audio_on[][2]   = SONG(MARIO_THEME);
float tone_music_on[][2]   = SONG(SONIC_RING);
float music_scale[][2]     = SONG(ONE_UP_SOUND);

float tone_caps_on[][2]    = SONG(ZELDA_TREASURE);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(ONE_UP_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(IMPERIAL_MARCH);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#endif /* AUDIO_ENABLE */



#ifdef AUDIO_ENABLE

void matrix_init_user(void)
{
    set_voice(default_voice);
    startup_user();
    println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if (!is_playing_notes())
    {
        if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning on...
                PLAY_SONG(tone_caps_on);
        }
        else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning off...
                PLAY_SONG(tone_caps_off);
        }
        else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LK LED is turning on...
                PLAY_SONG(tone_numlk_on);
        }
        else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LED is turning off...
                PLAY_SONG(tone_numlk_off);
        }
        else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LK LED is turning on...
                PLAY_SONG(tone_scroll_on);
        }
        else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LED is turning off...
                PLAY_SONG(tone_scroll_off);
        }
    }

    old_usb_led = usb_led;
}


void startup_user()
{
    _delay_ms(30); // gets rid of tick
    PLAY_SONG(tone_my_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_my_goodbye);
    _delay_ms(3000);
    stop_all_notes();
}

void audio_on_user(void)
{
  PLAY_SONG(tone_audio_on);
}

void music_on_user(void)
{
  PLAY_SONG(tone_music_on);
}

#endif /* AUDIO_ENABLE */