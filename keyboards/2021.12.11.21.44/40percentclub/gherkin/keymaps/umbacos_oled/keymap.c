#include QMK_KEYBOARD_H
#include "keymap_italian.h"
#include <print.h>

//umbacos
#include <Mouse.h>
int horzPin = A0;  // Analog output of horizontal joystick pin
int vertPin = A1;  // Analog output of vertical joystick pin
int selPin = 9;  // select button pin of joystick

int vertZero, horzZero;  // Stores the initial value of each axis, usually around 512
int vertValue, horzValue;  // Stores current analog output of each axis
const int sensitivity = 200;  // Higher sensitivity value = slower mouse, should be <= about 500
int mouseClickFlag = 0;

//int invertMouse = 1;        //Invert joystick based on orientation
int invertMouse = -1;         //Noninverted joystick based on orientation






#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

static void render_logo(void);

extern keymap_config_t keymap_config;
bool alt_tab_enabled;
uint32_t alt_tab_timer;

// custom keycodes
enum gherkin_tapcodes {
  TD_Q_ESC,
  TD_P_BKSP,
  TD_I_UP,
  TD_K_DOWN,
  TD_J_LEFT,
  TD_L_RIGHT
};

//Friendly Layer Names
enum gherkin_layers {
  _QWERTY,
  _SUPER,
  _SHIFT_SUPER,
  _LOWER,
  _ACCENT,
  _ALT_TAB,
  _MUSIC
};

// custom keycodes
enum gherkin_keycodes {
  QWERTY = SAFE_RANGE,
  SUPER,
  LOWER,
  BOOT,
  BACKLIT,
  ALT_TAB,
  PLAY_1,
  PLAY_2,
  PLAY_3,
  MUSIC,
  MUSIC_OFF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_3x10(
    TD(TD_Q_ESC),   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,   KC_U,  KC_I,     KC_O,    TD(TD_P_BKSP),
    LGUI_T(KC_A),   LT(_ALT_TAB,KC_S),  KC_D,  KC_F,  KC_G,  KC_H,   KC_J,  KC_K,     KC_L,  RGUI_T(KC_ENT),
    LSFT_T(KC_Z),   LCTL_T(KC_X), LALT_T(KC_C), LT(_ACCENT,KC_V),  LT(_SHIFT_SUPER, KC_BSPC),  LT(_SUPER, KC_SPC),  LT(_ACCENT, KC_B), RALT_T(KC_N),  RCTL_T(KC_M),  RSFT_T(IT_COMM)
  ),
  [_SUPER] = LAYOUT_ortho_3x10(
    KC_1,  KC_2,  KC_3,  IT_MINS,  IT_EQL,   IT_BKSL,  KC_HOME,  KC_UP,    KC_END,    KC_BSPC,
    KC_4,  KC_5,  KC_6,  IT_LBRC,  IT_RBRC,  IT_SLSH,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_DEL ,
    LT(_SHIFT_SUPER, KC_7), KC_8,  KC_9,     KC_0,  MO(_LOWER),   _______,  IT_QST,  IT_LESS,  IT_APOS,   IT_DOT
  ),
  [_SHIFT_SUPER] = LAYOUT_ortho_3x10(
    IT_EXLM, IT_AT,   IT_SHRP, IT_UNDS,  IT_PLUS,   IT_PIPE,  S(KC_HOME),  S(KC_UP),    S(KC_END),    _______,
    IT_DLR,  IT_PERC, IT_CRC,  IT_LCBR,  IT_RCBR,  IT_MORE, S(KC_LEFT),  S(KC_DOWN),  S(KC_RIGHT),  _______ ,
    IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN,  _______,   MO(_LOWER),  IT_SCLN,  IT_MORE,  IT_DQOT,   IT_COLN
  ),
  [_LOWER] = LAYOUT_ortho_3x10(
    MUSIC,   BL_TOGG,  PLAY_1,  KC_MUTE,  RGB_TOG,  KC_WH_U,  KC_MS_BTN1,  KC_MS_U,  KC_MS_BTN2,  KC_PGUP,
    KC_TAB,  BL_STEP,  PLAY_2,  KC_VOLU,  RGB_MOD,  KC_WH_D,  KC_MS_L,     KC_MS_D,  KC_MS_R,     KC_PGDN,
    KC_LSFT, BL_BRTG,  PLAY_3,  KC_VOLD,  _______,  KC_DOT,   BOOT,       XXXXXXX,  KC_LGUI,     KC_RSFT
  ),
  [_ACCENT] = LAYOUT_ortho_3x10(
    IT_EURO, XXXXXXX, IT_EACC, KC_F1,   KC_F2,   KC_F3,   IT_UACC, IT_IACC, IT_OACC, XXXXXXX,
    IT_AACC, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_RALT, KC_RCTL, KC_RSFT
  ),
  [_ALT_TAB] = LAYOUT_ortho_3x10(
    ALT_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  [_MUSIC] = LAYOUT_ortho_3x10(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MUSIC_OFF
  ),
};

#ifdef AUDIO_ENABLE

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_3x10(
    19, 20, 21, 22, 23, 29, 30, 31, 32, 33,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
     0,  1,  2,  3,  4,  5,  6,  7,  15, 16
);

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float tone_1[][2]     = SONG(ODE_TO_JOY);
float tone_2[][2]  = SONG(CAMPANELLA);
float tone_3[][2]     = SONG(FANTASIE_IMPROMPTU);

#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);

//umbacos
  pinMode(horzPin, INPUT);  // Set both analog pins as inputs
pinMode(vertPin, INPUT);
pinMode(selPin, INPUT);  // set button select pin as input
digitalWrite(selPin, HIGH);  // Pull button select pin high
delay(1000);  // short delay to let outputs settle
vertZero = analogRead(vertPin);  // get the initial values
horzZero = analogRead(horzPin);  // Joystick should be in neutral position when reading these

Mouse.begin(); //Init mouse emulation
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        alt_tab_enabled = true;
        register_code(KC_LGUI);
        tap_code(KC_TAB);
      }
      break;
    case BOOT:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
          wait_ms(500);
        #endif
        reset_keyboard();
      }
      return false;
      break;
    case MUSIC:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
          music_on();
          layer_on(_MUSIC);
        #endif
      }
      return false;
      break;
    case PLAY_1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_1);
        #endif
      }
      return false;
      break;
    case PLAY_2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_2);
        #endif
      }
      return false;
      break;
    case PLAY_3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_3);
        #endif
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE

        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
        #endif

          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    }
    return true;
}

void matrix_init_user(void) {

  #ifdef OLED_DRIVER_ENABLE
      render_logo();
  #endif
  wait_ms(2000); // gets rid of tick


    #ifdef AUDIO_ENABLE
        set_tempo(255);
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    wait_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    wait_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

bool music_mask_user(uint16_t keycode) {

  switch (keycode) {
    case MUSIC_OFF:
      music_off();
      layer_state_set(_QWERTY);
      return false;

    default:
      return true;
  }
}

#endif

void matrix_scan_user(void) {

  if (alt_tab_enabled && (get_highest_layer(layer_state)==_QWERTY)) {
    unregister_code(KC_LGUI);
    alt_tab_enabled=false;
   }

//umbacos
   vertValue = analogRead(vertPin) - vertZero;  // read vertical offset
horzValue = analogRead(horzPin) - horzZero;  // read horizontal offset

if (vertValue != 0)
  Mouse.move(0, (invertMouse * (vertValue / sensitivity)), 0); // move mouse on y axis
if (horzValue != 0)
  Mouse.move((invertMouse * (horzValue / sensitivity)), 0, 0); // move mouse on x axis

if ((digitalRead(selPin) == 0) && (!mouseClickFlag))  // if the joystick button is pressed
{
  mouseClickFlag = 1;
  Mouse.press(MOUSE_LEFT);  // click the left button down
}
else if ((digitalRead(selPin)) && (mouseClickFlag)) // if the joystick button is not pressed
{
  mouseClickFlag = 0;
  Mouse.release(MOUSE_LEFT);  // release the left button
}
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_Q_ESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [TD_P_BKSP]  = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_BSPC),
  [TD_I_UP]    = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_UP),
  [TD_K_DOWN]  = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_DOWN),
  [TD_J_LEFT]  = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_LEFT),
  [TD_L_RIGHT] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RIGHT),
};


#ifdef OLED_DRIVER_ENABLE

const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };


void render_logo(void) {
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _SUPER:
            oled_write_P(PSTR("SUPER\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM \n") : PSTR("no NUM \n"), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP \n") : PSTR("no CAP \n"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR \n") : PSTR("no SCR \n"), false);
}
#endif
